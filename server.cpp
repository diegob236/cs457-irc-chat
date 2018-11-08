#include <iostream>
#include <fstream>
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

map<string, vector<ChatUser>> channels;


// readConfig(): open and read config file
int readConfig() {

    // Open file
    ifstream conf; string line;
    conf.open("chatserver.conf");
    if (!conf) {
        cout << "Error reading configuration file." << endl;
        return -1;
    }

    // Read port number and dbpath
    conf >> line >> port >> line >> dbpath;
    return 0;
}


// removeUserFromChannel(): remove user from their channel when disconnected
void removeUserFromChannel(ChatUser user) {
    for (uint i = 0; i < channels[user.getChannel()].size(); i++) {
        if (channels[user.getChannel()][i].getUsername() == user.getUsername()) {
            channels[user.getChannel()].erase(channels[user.getChannel()].begin() + i);
            break;
        }
    }
}


// cclient(): handle client connection
int cclient(shared_ptr<Socket> clientSocket) {

    string msg, reply, username;
    ssize_t val;
	
	// Create user and set username
	ChatUser user(clientSocket);
	tie(username, val) = user.recvString();
	if (username == "unregistered\n") {
        user.setUsername(guestid);
        user.sendString("^" + user.getUsername() + "\n");
    }
	else user.setUsername(username);
    channels[user.getChannel()].push_back(user);
    cout << user.getUsername() << " has joined the chat." << endl;

    // While client is connected
    while (true) {

        // Get message
        tie(msg, val) = user.recvString();
        reply = parseCommand(user, channels, msg);

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

    // Read configuration file
    if (readConfig() < 0) exit(0);

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