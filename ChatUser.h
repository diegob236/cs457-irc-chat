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

        string recvString();
        void sendString(const string& data);
        void disconnect();

        void setUsername(string username);
        void setUsername(int& id) {username = "guest" + to_string(id); id++;}
        void setPassword(string pswd) {password = pswd;};
        void setChannel(string chn) {channel = chn;}
        void setLevel(string lvl) {level = lvl;}

        string getUsername() {return username;}
        string getPassword() {return password;}
        string getChannel() {return channel;}
        string getLevel() {return level;}
		shared_ptr<Socket> getSocketPointer() {return clientSocket;}

    private:
        string username, password, level;
        bool banned = false;
        string channel = "general";
        shared_ptr<Socket> clientSocket;

};
