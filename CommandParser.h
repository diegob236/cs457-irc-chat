#pragma once

#include <iostream>
#include <string>
#include <bits/stdc++.h> 


using namespace std;


// parseCommand(): read IRC command and perform action
int parseCommand(shared_ptr<Socket> clientSocket, int id, const string &msg) {

    // Get uppercase message for parsing commands
    string s = msg;
    transform(s.begin(), s.end(), s.begin(), ::toupper);

    // EXIT
    if (s == "/EXIT\n") {
        clientSocket.get()->sendString(s, false);
        cout << "client " << id << " has left the chat." << endl;
        clientSocket.get()->closeSocket();
        return -1;
    }

    // Regular message
    else cout << "[client " << id << "] " << msg;
    return 0;
}