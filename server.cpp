#include <iostream>
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


int guestid = 0;
bool ready = true;
vector<unique_ptr<thread>> threadList;

vector<ChatUser> activeUsers;                   // Active Users
map<string, vector<ChatUser>> channels;         // Channels


// removeActiveUser(): remove user from activeUsers when disconnected
void removeActiveUser(ChatUser user) {
    for (int i = 0; i < activeUsers.size(); i++) {
        if (activeUsers[i].getUsername() == user.getUsername()) activeUsers.erase(activeUsers.begin() + i); break;
    }
}


// cclient(): handle client connection
int cclient(shared_ptr<Socket> clientSocket) {

    string msg, reply, username;
    ssize_t val;
	
	// Create user and set username
	ChatUser user(clientSocket);
	tie(username, val) = user.recvString();
	if (username == "unregistered\n") user.setUsername(guestid);
	else user.setUsername(username);
    activeUsers.push_back(user);
    cout << user.getUsername() << " has joined the chat." << endl;

    // While client is connected
    while (true) {

        // Get message
        tie(msg, val) = user.recvString();
        reply = parseCommand(user, activeUsers, msg);

        // Disconnect client if prompted to quit
        if (reply == "/QUIT\n") {
            removeActiveUser(user);
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

    // Start server
    cout << "Server started on port 2000" << endl; 
    ServerSocket server(2000);
    server.bindSocket(); 
    server.listenSocket(); 
    cout << "Waiting for connections..." << endl << endl;

    // Make threadlist and id for client connections
    int id = 0; 
  
    // Accept connections and add to thread list
    while (ready) { 
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