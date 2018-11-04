#include "CommandParser.h"

// parseCommand(): read IRC command and perform action
int parseCommand(shared_ptr<Socket> clientSocket, int id, const string &msg) {

    // Parse command and command arguments using a stringstream
    if (msg.at(0) == '/') {
        vector<string> args;
        istringstream ss(msg); string command, s;
        ss >> command;
        while (ss >> s) args.push_back(s);

        // Make command upper case
        transform(command.begin(), command.end(), command.begin(), ::toupper);

        // Handle command
        if (command == "/AWAY") return 0;
        if (command == "/CONNECT") return 0;
        if (command == "/DIE") return 0;
        if (command == "/HELP") return 0;
        if (command == "/INFO") return 0;
        if (command == "/INVITE") return 0;
        if (command == "/ISON") return 0;
        if (command == "/JOIN") return 0;
        if (command == "/KICK") return 0;
        if (command == "/KILL") return 0;
        if (command == "/KNOCK") return 0;
        if (command == "/LIST") return 0;
        if (command == "/MODE") return 0;
        if (command == "/NICK") return 0;
        if (command == "/NOTICE") return 0;
        if (command == "/OPER") return 0;
        if (command == "/PART") return 0;
        if (command == "/PING") return 0;
        if (command == "/PONG") return 0;
        if (command == "/PRIVMSG") return 0;
        if (command == "/QUIT") return handleQUIT(clientSocket, id);
        if (command == "/RESTART") return 0;
        if (command == "/RULES") return 0;
        if (command == "/SETNAME") return 0;
        if (command == "/SILENCE") return 0;
        if (command == "/TIME") return 0;
        if (command == "/TOPIC") return 0;
        if (command == "/USER") return 0;
        if (command == "/USERHOST") return 0;
        if (command == "/USERIP") return 0;
        if (command == "/USERS") return 0;
        if (command == "/VERSION") return 0;
        if (command == "/WALLOPS") return 0;
        if (command == "/WHO") return 0;
        if (command == "/WHOIS") return 0;
        else return 2;
    }

    // Regular message
    else cout << "[client " << id << "] " << msg;
    return 1;
}


// QUIT
int handleQUIT(shared_ptr<Socket> clientSocket, int id) {
    clientSocket.get()->sendString("/QUIT\n", false);
    cout << "client " << id << " has left the chat." << endl;
    clientSocket.get()->closeSocket();
    return -1;
}