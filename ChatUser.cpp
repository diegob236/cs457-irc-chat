#include "ChatUser.h"


// Receive string
tuple<string,ssize_t> ChatUser::recvString() {
    return clientSocket.get()->recvString();
}


// Send string
void ChatUser::sendString(const string& data) {
    clientSocket.get()->sendString(data);
}


// Close socket
void ChatUser::disconnect() {
    clientSocket.get()->closeSocket();
}


// Set username (string)
void ChatUser::setUsername(string& username) {
	username.erase(remove(username.begin(), username.end(), '\n'), username.end());
    this->username = username;
}


// Set username (id)
void ChatUser::setUsername(int& id) {
    this->username = "guest " + to_string(id); id++;
}


// Get username
string ChatUser::getUsername() {
    return username;
}


// Get channel
string ChatUser::getChannel() {
    return channel;
}


// Set channel
void ChatUser::setChannel(string& channel) {
    this->channel = channel;
}


// Get socket
shared_ptr<Socket> ChatUser::getSocketPointer() {
    return clientSocket;
}