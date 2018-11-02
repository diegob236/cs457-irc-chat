#include <iostream>
#include "tcpClientSocket.h"

using namespace std;

int main(int argc, char * argv[]) {
    
    cout << "Starting client example" <<endl;
    string serverIP("127.0.0.1");
    int port = 2000;
    cs457::tcpClientSocket clientSocket(serverIP,port);
    
    int val = clientSocket.connectSocket();
    cout << "Client Socket Value after connect = " << val << endl;

    clientSocket.sendString("Hello Server. How are you? ",false);

    string msg;
    ssize_t v;
    tie(msg,v) =  clientSocket.recvString(4096,false);
    cout << "server said: " << msg << endl;

    cout << "Client will try to exit now" <<endl;

    clientSocket.sendString("EXIT",false);

    tie(msg,v) =  clientSocket.recvString(4096,false);
    cout << "server said: " << msg << endl;

    clientSocket.closeSocket();
    
    return 0;
}