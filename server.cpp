#include <iostream>
#include <string> 
#include <tuple> 
#include <thread> 
#include <vector> 
#include <memory> 
#include "Socket.h"
#include "ServerSocket.h"
#include "CommandParser.h"

using namespace std;

bool ready = true; 


// cclient(): handle client connection
int cclient(shared_ptr<Socket> clientSocket, int id) {

    string msg;
    ssize_t val;

    // While client is connected
    while (true) {

        // Get message
        tie(msg,val) = clientSocket.get()->recvString();
        if (parseCommand(clientSocket, id, msg) < 0) break;

        // Send reply
        string s = "[SERVER] You sent message: " + msg;
        thread child(&Socket::sendString, clientSocket.get(), s, true);
        child.join();
    }
    return 1; 
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
    vector<unique_ptr<thread>> threadList;
  
    // Accept connections and add to thread list
    while (ready) { 
        shared_ptr<Socket> clientSocket;
        int val; 
        tie(clientSocket,val) = server.acceptSocket();
        cout << "\rclient " << id << " has joined the chat." << endl; 
        unique_ptr<thread> t = make_unique<thread>(cclient, clientSocket, id); 
        threadList.push_back(move(t)); 
        id++;
    }

    // Join threads
    for (auto& t: threadList) t.get()->join();
    
    // Shut down server
    return 0; 
}