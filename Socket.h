#pragma once

#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <strings.h>
#include <string> 
#include <tuple> 
#include <unistd.h>
#include <assert.h>
#include <vector> 
#include <memory> 
#include <mutex>
#include <iostream>

using namespace std; 


class Socket {
    
    public: 
        Socket() {}
        struct sockaddr * getAddressPointer();
        socklen_t getAddressSize();
        void setSocket(int skct); 
        int connectSocket(string hostname, int port);
        int getSocket();
        int closeSocket(); 
        std::tuple<string,ssize_t> recvString(int bufferSize=4096, bool useMutex = true);
        void setUserInfoIPv4(string clientAddress, uint16_t port);

        ssize_t sendString(const string & data, bool useMutex = true);
        string getUniqueIdentifier();


    private:
        struct sockaddr_in userAddress;
        int userSocket;
        string clientAddressIPv4; 
        uint16_t clientPortIPv4;
        mutex sendMutex;
        mutex recvMutex; 
};
