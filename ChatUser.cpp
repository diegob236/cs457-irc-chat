#include "ChatUser.h"


// Receive string
string ChatUser::recvString() {
    return get<0>(clientSocket.get()->recvString());
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
void ChatUser::setUsername(string username) {
	username.erase(remove(username.begin(), username.end(), '\n'), username.end());
    this->username = username;
}
