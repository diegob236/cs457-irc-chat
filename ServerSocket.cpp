#include "ServerSocket.h"


ServerSocket::ServerSocket(uint portNumber): address(""), port(portNumber) {
    init(); 
    setSocketOptions();
} 


ServerSocket::ServerSocket(string networkAddress, uint portNumber): address(networkAddress), port(portNumber) {
    init(); 
    setSocketOptions();
}


int ServerSocket::bindSocket() {
    return bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));    
}

      
int ServerSocket::listenSocket() {
    return listen(serverSocket, 14);
}


tuple<shared_ptr<Socket>,int> ServerSocket::acceptSocket() {
    shared_ptr<Socket> userSocket = make_shared<Socket>(); 
    socklen_t len = userSocket.get()->getAddressSize();
    int client_fd = accept(serverSocket,(struct sockaddr *)userSocket.get()->getAddressPointer(), &len);
    userSocket.get()->setSocket(client_fd); 
    char userIPv4[16]; 
    sockaddr_in * userAddress =  (sockaddr_in *) userSocket.get()->getAddressPointer();
    inet_ntop(AF_INET, &(userAddress->sin_addr), userIPv4, INET_ADDRSTRLEN);
    auto clientPort = ntohs(userAddress->sin_port);
    userSocket.get()->setUserInfoIPv4(string(userIPv4),clientPort); 
    return make_tuple(userSocket,client_fd); 
}


void ServerSocket::init() {
    serverSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    const char * cstr = address.c_str();
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    if (address == "")
        addr.s_addr =  htonl(INADDR_ANY);
    else {
        inet_aton(cstr,&addr);
        serverAddress.sin_addr = addr;
        string addresscpy(inet_ntoa(addr));
        address = addresscpy;  
    }
    serverAddress.sin_port = htons(port);
}


void ServerSocket::setSocketOptions() {
    int optval = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval , sizeof(int));
}