#include "CommandParser.h"

// Command arguments
vector<string> args;


// parseCommand(): read IRC command and perform action
string parseCommand(shared_ptr<Socket> clientSocket, int id, const string &msg) {

    // Parse command and command arguments using a stringstream
    if (msg.at(0) == '/') {
        args.clear();
        istringstream ss(msg); string command, s;
        ss >> command;
        while (ss >> s) args.push_back(s);

        // Make command upper case
        transform(command.begin(), command.end(), command.begin(), ::toupper);
        string d = "You sent command: " + command + "\n";

        // Handle command
        if (command == "/AWAY") return d;
        if (command == "/CONNECT") return d;
        if (command == "/DIE") return d;
        if (command == "/HELP") return handleHELP();
        if (command == "/INFO") return d;
        if (command == "/INVITE") return d;
        if (command == "/ISON") return d;
        if (command == "/JOIN") return d;
        if (command == "/KICK") return d;
        if (command == "/KILL") return d;
        if (command == "/KNOCK") return d;
        if (command == "/LIST") return d;
        if (command == "/MODE") return d;
        if (command == "/NICK") return d;
        if (command == "/NOTICE") return d;
        if (command == "/OPER") return d;
        if (command == "/PART") return d;
        if (command == "/PING") return d;
        if (command == "/PONG") return d;
        if (command == "/PRIVMSG") return d;
        if (command == "/QUIT") return handleQUIT(clientSocket, id);
        if (command == "/RESTART") return d;
        if (command == "/RULES") return d;
        if (command == "/SETNAME") return d;
        if (command == "/SILENCE") return d;
        if (command == "/TIME") return d;
        if (command == "/TOPIC") return d;
        if (command == "/USER") return d;
        if (command == "/USERHOST") return d;
        if (command == "/USERIP") return d;
        if (command == "/USERS") return d;
        if (command == "/VERSION") return d;
        if (command == "/WALLOPS") return d;
        if (command == "/WHO") return d;
        if (command == "/WHOIS") return d;
        else return "Command not recognized. For a list of commands type /HELP.\n";
    }

    // Regular message
    else cout << "[client " << id << "] " << msg;
    return "You sent message: " + msg;
}


// HELP
string handleHELP() {
    string help = "\nAvailable IRC commands: \n" +
    string("  /AWAY: \n") +
    string("  /CONNECT: \n") +
    string("  /DIE: \n") +
    string("  /HELP: \n") +
    string("  /INFO: \n") +
    string("  /INVITE: \n") +
    string("  /ISON: \n") +
    string("  /JOIN: \n") +
    string("  /KICK: \n") +
    string("  /KILL: \n") +
    string("  /KNOCK: \n") +
    string("  /LIST: \n") +
    string("  /MODE: \n") +
    string("  /NICK: \n") +
    string("  /NOTICE: \n") +
    string("  /OPER: \n") +
    string("  /PART: \n") +
    string("  /PING: \n") +
    string("  /PONG: \n") +
    string("  /PRIVMSG: \n") +
    string("  /QUIT: \n") +
    string("  /RESTART: \n") +
    string("  /RULES: \n") +
    string("  /SETNAME: \n") +
    string("  /SILENCE: \n") +
    string("  /TIME: \n") +
    string("  /TOPIC: \n") +
    string("  /USER: \n") +
    string("  /USERHOST: \n") +
    string("  /USERIP: \n") +
    string("  /USERS: \n") +
    string("  /VERSION: \n") +
    string("  /WALLOPS: \n") +
    string("  /WHO: \n") +
    string("  /WHOIS: \n");

    return help;
}


// QUIT
string handleQUIT(shared_ptr<Socket> clientSocket, int id) {

    // Print goodbye message if specified
    if (args.size() > 0) {
        cout << "[client " << id << "] ";
        for(int i = 0; i < args.size(); i++) cout << args[i] << ' ';
        cout << endl;
    }

    // Disconnect client
    clientSocket.get()->sendString("/QUIT");
    cout << "client " << id << " has left the chat." << endl;
    clientSocket.get()->closeSocket();
    return "/QUIT";
}