#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include "Socket.h"

using namespace std;

class ChatUser {

    public:
        ChatUser(shared_ptr<Socket> cSocket): clientSocket(cSocket) {}
		ChatUser(){}
        tuple<string,ssize_t> recvString();
        void sendString(const string& data);
        void disconnect();
        void setUsername(string& username);
        void setUsername(int& id);
        string getUsername();
        void setChannel(string& channel);
        string getChannel();
		shared_ptr<Socket> getSocketPointer();

    private:
        string username, realName;
        string password;
        string channel = "general";
        shared_ptr<Socket> clientSocket;

};
