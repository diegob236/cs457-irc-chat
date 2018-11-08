#include <iostream>
#include <fstream>
#include <sstream>
#include <string> 
#include <tuple> 
#include <thread> 
#include <vector>
#include <map>
#include <memory>
#include "ChatUser.h"
#include "Socket.h"
#include "ServerSocket.h"
#include "CommandParser.h"

using namespace std;


int port;
string dbpath;
int guestid = 0;
vector<unique_ptr<thread>> threadList;

map<string, vector<string>> userList;
map<string, vector<ChatUser>> channels;


// init(): open and read config files
int init() {

    // Open configuration file
    ifstream conf; string line;
    conf.open("chatserver.conf");
    if (!conf) {
        cout << "ERROR: File not found: chatserver.conf" << endl;
        return -1;
    }

    // Read port number and dbpath
    conf >> line >> port >> line >> dbpath;

    // Read users.txt
    ifstream users;
    users.open(dbpath + "users.txt");
    if (!users) {
        cout << "ERROR: File not found: users.txt" << endl;
        return -1;
    }

    // Read registered users
    while(getline(users, line)) {
        istringstream ss(line);
        string user, password, level, banned;
        ss >> user >> password >> level >> banned;
        userList[user].push_back(password); 
        userList[user].push_back(level); 
        userList[user].push_back(banned);
    }

    return 0;
}


// removeUserFromChannel(): remove user from their channel when disconnected
void removeUserFromChannel(ChatUser &user) {
    for (uint i = 0; i < channels[user.getChannel()].size(); i++) {
        if (channels[user.getChannel()][i].getUsername() == user.getUsername()) {
            channels[user.getChannel()].erase(channels[user.getChannel()].begin() + i);
            break;
        }
    }
}


// loginUser(): log in existing user
void loginUser(ChatUser &user) {

    // Prevent banned users from logging in
    if(userList[user.getUsername()][2] == "true") {
        user.sendString("You are banned from this server! Access is denied!\n");
        user.disconnect();
        removeUserFromChannel(user);
        user.sendString("/QUIT\n");
    }

    // Get password
    user.sendString("Please enter your password:\n");
    string password = user.recvString();
    password = password.substr(0, password.size()-1);

    // Check if correct
    while (userList[user.getUsername()][0] != password) {
        user.sendString("Incorrect password, please try again:\n");
        password = user.recvString();
        password = password.substr(0, password.size()-1);
    }

    // User is logged in
    if (userList[user.getUsername()][1] == "admin") {
        user.sendString("Admin login successful!\n\n");
        user.setLevel("admin");
    }
    else user.sendString("Login successful!\n\n");
}


// registerUser(): register a new user
void registerUser(ChatUser &user) {

    // Set password
    user.sendString("Set a password for " + user.getUsername() + ":\n");
    string password = user.recvString();
    user.setPassword(password.substr(0, password.size()-1));

    // Add to users.txt
    ofstream out;
    out.open(dbpath + "users.txt", fstream::app);
    out << user.getUsername() << " " << user.getPassword() << " user false\n";

    // Add to users map
    userList[user.getUsername()].push_back(user.getPassword());
    userList[user.getUsername()].push_back("user");
    userList[user.getUsername()].push_back("false");

    // Send confirmation
    user.sendString("Registered on server as " + user.getUsername() + ".\n");
    user.sendString("Connected to server!\n\n");
}


// authenticateUser(): handle user authentication
void authenticateUser(ChatUser &user) {

    // Get username
    string username = user.recvString();

    // Create guest user
	if (username == "anonymous\n") {
        user.setUsername(guestid);
        user.sendString("^" + user.getUsername() + "\n");
        user.sendString("Connected to server!\n\n");
    }
    else {
        // Set username
        user.setUsername(username);

        // Register new user
        if (userList[user.getUsername()].empty()) registerUser(user);

        // Log in existing user
        else loginUser(user);
    }

    // Add to default channel
    channels[user.getChannel()].push_back(user);
    cout << user.getUsername() << " has joined the chat." << endl;
    for (uint i = 0; i < channels[user.getChannel()].size(); i++)
        if (channels[user.getChannel()][i].getUsername() != user.getUsername())
            channels[user.getChannel()][i].sendString(user.getUsername() + " has joined the chat.\n");
}


// cclient(): handle client connection
int cclient(shared_ptr<Socket> clientSocket) {

    string msg, reply;
	
	// Create user and register as guest or member
	ChatUser user(clientSocket);
	authenticateUser(user);

    // While client is connected
    while (true) {

        // Get message
        msg = user.recvString();
        reply = parseCommand(user, channels, msg);

        // Kill server if prompted to die
        if (reply == "/DIE\n") abort();

        // Disconnect client if prompted to quit
        if (reply == "/QUIT\n") {
            removeUserFromChannel(user);
            return 0;
        }

        // Send reply
        else if (reply != "") {
			thread child(&ChatUser::sendString, &user, reply);
            child.join();
        }
        
    }
    return 0;
}


/* Main method */
int main(int argc, char * argv[]) {

    // Read configuration files
    if (init() < 0) exit(0);

    // Start server
    cout << "Server started on port " << port << endl; 
    ServerSocket server(port);
    server.bindSocket(); server.listenSocket(); 
    cout << "Waiting for connections..." << endl << endl;
  
    // Accept connections and add to thread list
    while (true) { 
        shared_ptr<Socket> clientSocket;
        int val;
        tie(clientSocket,val) = server.acceptSocket();
        unique_ptr<thread> t = make_unique<thread>(cclient, clientSocket); 
        threadList.push_back(move(t));
    }

    // Join threads
    for (auto& t: threadList) t.get()->join();
    
    // Shut down server
    return 0; 
}