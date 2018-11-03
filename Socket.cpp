#include "Socket.h"
#include <memory> 
#include <cstring> 
#include <mutex> 

using namespace std; 


// connectSocket(): connect client to server
int Socket::connectSocket(string hostname, int port) {

    // Create socket
    if ((userSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Unable to create socket. \n\n");
        return -1;
    }
    
    // Initialize sockaddr_in struct
    memset(&userAddress, '0', sizeof(userAddress)); 
    userAddress.sin_family = AF_INET; 
    userAddress.sin_port = htons(port); 
       
    // Set host address
    if(inet_pton(AF_INET, hostname.c_str(), &userAddress.sin_addr) <= 0) {
        printf("Invalid address. \n\n");
        return -1;
    }
    
    // Connect to socket
    if (connect(userSocket, (struct sockaddr *)&userAddress, sizeof(userAddress)) < 0) {
        printf("Unable to connect to server. \n\n");
        return -1;
    }

    // Connection successful!
    printf("Connected to server! \n\n");
    return 0;
};


// Set/Get/Close socket
void Socket::setSocket(int sckt) {userSocket=sckt;};
int Socket::getSocket() {return userSocket;};
int Socket::closeSocket() {return close(userSocket);};


// getAddressSize(): get length of pointer
socklen_t Socket::getAddressSize() {
    return sizeof(userAddress);
};


// setUserInfoIPv4(): set IPv4 user information
void Socket::setUserInfoIPv4(string address, uint16_t port) {
    clientAddressIPv4 = address;
    clientPortIPv4 = port; 
};


// recvString(): receive message
tuple<string,ssize_t> Socket::recvString(int bufferSize, bool useMutex) {
    char stringBuffer[bufferSize]; 
    memset(stringBuffer, 0, sizeof(stringBuffer));
    ssize_t recvMsgSize;
    if (useMutex) {
        lock_guard<mutex> lock(recvMutex);
        recvMsgSize = recv(userSocket, stringBuffer, bufferSize, 0); 
    }    
    else {
        recvMsgSize = recv(userSocket, stringBuffer, bufferSize, 0); 
    }
    return make_tuple(string(stringBuffer),recvMsgSize);     
};


// sendString(): send message
ssize_t Socket::sendString(const string & data, bool useMutex) {

    const char *s = data.c_str();
    ssize_t rval; 
    if (useMutex) {
       lock_guard<mutex> lock(sendMutex);
       rval = send(userSocket, s, strlen(s), 0);
    }
    else {
       rval = send(userSocket, s, strlen(s), 0);     
    }

    return rval;
}


// getUniqueIdentifier(): get unique id
string Socket::getUniqueIdentifier() { 
    //this unique identifier is arbitrary 
    //and it may not be useful for chat program (see other classes)
    //it has not been tested to be unique but for now, we don't need it. 
     string identifier  = "[" + clientAddressIPv4 + "," + to_string(clientPortIPv4) + "]"; 
     return identifier; 
};


// getAddressPointer(): get address pointer
struct sockaddr * Socket::getAddressPointer() {
    return ((struct sockaddr *) &userAddress);
};