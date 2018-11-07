#include <iostream>
#include <string>
#include <vector> 
#include <memory>
#include <cstring> 
#include <thread>
#include <sys/socket.h>
#include <mutex>
#include "Socket.h"

using namespace std;


// Variables
string hostname;
string username = "unregistered";
int port;
string configFile;
string testFile;
string logFile;

int sock;
struct sockaddr_in addr;
char buffer[2048];
mutex sendMutex;
mutex recvMutex; 


// connectToServer(): connect to server
int connectToServer() {

    // Start client socket
    cout << endl << "Connecting to " << hostname << ":" << port << "... " << endl;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Unable to create socket. \n\n");
        return -1;
    }
    
    // Initialize sockaddr_in struct
    memset(&addr, '0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
       
    // Set host addr
    if(inet_pton(AF_INET, hostname.c_str(), &addr.sin_addr) <= 0) {
        printf("Invalid addr. \n\n");
        return -1;
    }
    
    // Connect to socket
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        printf("Unable to connect to server. \n\n");
        return -1;
    }
	
	// Send username to server
    write(sock, string(username+"\n").c_str(), string(username+"\n").size());

    // Connection successful!
    printf("Connected to server! \n\n");
    return 0;
}


// readData(): read data from server
void readData() {
    while (true) {
        memset(&buffer, 0, sizeof(buffer));
        recv(sock, (char *)&buffer, sizeof(buffer), 0);
        if (strcmp(buffer, "/QUIT\n") == 0) {
            cout << "Closing connection..." << endl << endl;
            exit(0);
        }
        cout << buffer;
    }
}


// writeData(): write data to server
void writeData() {
    while(true){
        string s;
        getline(cin, s);
        s += "\n";
        write(sock, s.c_str(), s.size());
    }
}


/* Main method */
int main(int argc, char *argv[]) {

    // Parse arguments
    int opt;
    cout << endl;
    while((opt = getopt(argc, argv, "h:u:p:c:t:L:")) != EOF) {
        switch(opt) {
            case 'h': hostname = optarg; cout << "hostname: " << hostname << endl; break;
            case 'u': username = optarg; cout << "username: " << username << endl; break;
            case 'p': port = stoi(optarg); cout << "server port: " << port << endl; break;
            case 'c': configFile = optarg; cout << "config file: " << configFile << endl; break;
            case 't': testFile = optarg; cout << "run test file: " << testFile << endl; break;
            case 'L': logFile = optarg; cout << "log file name: " << logFile << endl; break;
            case '?': fprintf(stderr, "usage is \n -h hostname \n -u username \n -p server port \n -c configuration file \n -t run test file \n -L log_file_name \n\n"); exit(-1);
        }
    }

    // Connect to server
    if (connectToServer() < 0) exit(-1);

    // Start read/write threads
    thread writeThread(&writeData);
    thread readThread(&readData);

    writeThread.join();
    readThread.join();

    return 0; 
}
