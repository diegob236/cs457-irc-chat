#pragma once

#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <strings.h>
#include <string> 
#include <tuple> 
#include <unistd.h>
#include <memory>


using namespace std; 


class Socket; 

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
    uint port; 
    string address; 
    int serverSocket;
    
    struct sockaddr_in serverAddress; 
    struct in_addr addr;
    
};



