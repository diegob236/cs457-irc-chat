#pragma once

#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <strings.h>
#include <string> 
#include <tuple> 
#include <unistd.h>
#include <memory>
#include "Socket.h"

using namespace std; 


class ServerSocket {

public:
    ServerSocket(uint portNumber); 
    ServerSocket(string networkAddress, uint portNumber);
    int bindSocket();
    int listenSocket();
    tuple<shared_ptr<Socket>,int> acceptSocket();
    
private: 
    void init();
    void setSocketOptions();

    string address;
    uint port;
    int serverSocket;
    struct sockaddr_in serverAddress; 
    struct in_addr addr;
};
