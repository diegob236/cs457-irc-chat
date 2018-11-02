#include <iostream>
#include <string> 
#include <tuple> 
#include <thread> 
#include <vector> 
#include <memory> 
#include "Socket.h"
#include "ServerSocket.h"

using namespace std;

bool ready = true; 

// cclient(): handle client connection
int cclient(shared_ptr<Socket> clientSocket, int id) {

    string msg;
    ssize_t val;
    bool cont = true;

    // While client is connected
    while (cont) {

        // Get message
        tie(msg,val) = clientSocket.get()->recvString();

        // Print message and send send reply
        cout << "[client " << id << "] " << msg;
        string s = "[SERVER] You sent message: " + msg;
        //clientSocket.get()->sendString(s);
        thread childT1(&Socket::sendString, clientSocket.get(), s, true);

        // Exit command: EXIT
        if (msg.substr(0,4) == "EXIT") {
            cont = false;
        }

        // Join child threads
        childT1.join();
        //clientSocket.get()->sendString(msg); 
        //clientSocket.get()->sendString("\n");

        // SERVER command
        if (msg.substr(0,6) == "SERVER") {
            thread childTExit(&Socket::sendString, clientSocket.get(), "GOODBYE EVERYONE",false);
            thread childTExit2(&Socket::sendString, clientSocket.get(), "\n",false);
            ready = false;   
            cont = false;   
            childTExit.join(); 
            childTExit2.join();
        }
    }

    clientSocket.get()->sendString("[SERVER] Goodbye client " + to_string(id) + "\n");
    cout << "client " << id << " has left the chat." << endl;
    clientSocket.get()->closeSocket(); 
    return 1; 
}


/* Main method */
int main(int argc, char * argv[])
{
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
        cout << "client " << id << " has joined the chat." << endl; 
        unique_ptr<thread> t = make_unique<thread>(cclient,clientSocket,id); 
        threadList.push_back(move(t)); 
        id++;
    }

    // Join threads
    for (auto& t: threadList) t.get()->join();
    
    // Shut down server
    cout << "Server is shutting down after one client" << endl; 
    return 0; 
}