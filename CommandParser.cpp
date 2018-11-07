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
        if (command == "/INFO") return handleINFO();
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

//INFO
string handleINFO() {
    string info =   R"***(        ,     \    /      ,        )***" "\n"
                    R"***(       / \    )\__/(     / \       )***" "\n" 
                    R"***(      /   \  (_\  /_)   /   \      )***" "\n" 
                    R"***( ____/_____\__\@  @/___/_____\____ )***" "\n" 
                    R"***(|             |\../|              |)***" "\n" 
                    R"***(|              \VV/               |)***" "\n" 
                    R"***(|         IRC Chat CS 457         |)***" "\n" 
                    R"***(|            created by           |)***" "\n" 
                    R"***(|   Kat Moore and Diego Batres    |)***" "\n" 
                    R"***(|_________________________________|)***" "\n" 
                    R"***( |    /\ /      \\       \ /\    | )***" "\n" 
                    R"***( |  /   V        ))       V   \  | )***" "\n" 
                    R"***( |/     `       //        '     \| )***" "\n" 
                    R"***( `              V                ')***" "\n\n\n" 
                    "This IRC Chat was made possible through the hard work \nof two CS students at Colorado State University.\n\n"
                    "We couldn't have done it without the support of \nProfessor Francisco Ortega and Aditya.\n\n"
                    "*Disclaimer* Fortunately, no dragons contributed to the \ndevelopement of this project.\n";
                                 
    return info; 
}


// HELP
string handleHELP() {
    string help = "\nAvailable IRC commands: \n" +
    string("  /AWAY: \n") +
    string("      Parameters:   [message]\n") + 
    string("      Description:  If a message is given, marks you as being away, otherwise removes your away status and previous message.\n") +
    string("  /CONNECT:\n") + 
    string("      Parameters:   <target server> [<port> [<remote server>]]\n") +
    string("      Description:  Use to try and force a connection to another server. Only available to IRC Operators.\n") +
    string("  /DIE: \n") +
    string("      Parameters:   [password]\n") + 
    string("      Description:  If the correct password is provided, and you are an operator, this command will shut down the local server.\n") +
    string("  /HELP: \n") +
    string("      Parameters:   none\n") + 
    string("      Description:  Displays the list of available commands\n") +
    string("  /INFO: \n") +
    string("      Parameters:   none\n") + 
    string("      Description:  Returns information on the developers and supporters who made this IRC server possible.\n") +
    string("  /INVITE: \n") +
    string("      Parameters:   <nickname> <channel>\n") + 
    string("      Description:  Invite <nickname> to <channel>. If channel is invite only, the client doing the inviting must be recognised as being a channel operator.\n") +
    string("  /ISON: \n") +
    string("      Parameters:   <nickname>{<space><nickname>}\n") + 
    string("      Description:  Returns a subset of the nicknames you give, showing only those that are currently online.\n") +
    string("  /JOIN: \n") +
    string("      Parameters:   <channel>{,<channel>} [<key>{,<key>}]\n") + 
    string("      Description:  Joins one or more channels you provide the names for. The key is optional.\n") +
    string("  /KICK: \n") +
    string("      Parameters:   <channel> <user> [<comment>]\n") + 
    string("      Description:  Kicks a user from a channel you specify. \n") +
    string("  /KILL: \n") +
    string("      Parameters:   <nickname> <comment>\n") + 
    string("      Description:  This command will disconnect a user from IRC with the given reason. You may provide the nicknames of multiple users as a list seperated by commas.\n") +
    string("  /KNOCK: \n") +
    string("      Parameters:   <channel>[message]\n") + 
    string("      Description:  With this command you can request to join a channel with the +I (invite only) flag on it.\n") +
    string("  /LIST: \n") +
    string("      Parameters:   [<channel>{,<channel>} [<server>]]\n") + 
    string("      Description:  List channels and their topics.  If  the <channel>  parameter  is  used,  only  the  status  of  that  channel is displayed.\n") +
    string("  /MODE: \n") +
    string("      Parameters:   <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]\n") + 
    string("      Description:  Allows both usernames and channels to have their mode changed.\n") +
    string("  /NICK: \n") +
    string("      Parameters:   <new nickname>\n") + 
    string("      Description:  Changes your nickname to new nickname.\n") +
    string("  /NOTICE: \n") +
    string("      Parameters:   <nickname> <text>\n") + 
    string("      Description:  Sends a private message to nickname.\n") +
    string("  /OPER: \n") +
    string("      Parameters:   <user> [password]\n") + 
    string("      Description:  Used by a normal user to obtain operator privileges.\n") +
    string("  /PART: \n") +
    string("      Parameters:   <channel>{,<channel>}\n") + 
    string("      Description:  Causes the client sending the message to be removed from the list of active users for all given channels.\n") +
    string("  /PING: \n") +
    string("      Parameters:   <server1> [<server2>]\n") + 
    string("      Description:  Used to test the presence of an active client at the other end of the connection.\n") +
    string("  /PONG: \n") +
    string("      Parameters:   <daemon> [<daemon2>]\n") + 
    string("      Description:  A reply to ping message.  If parameter <daemon2> is given this message must be forwarded to given daemon.\n") +
    string("  /PRIVMSG: \n") +
    string("      Parameters:   <receiver>{,<receiver>} [message]\n") + 
    string("      Description:  Send a private message between users\n") +
    string("  /QUIT: \n") +
    string("      Parameters:   [message]\n") + 
    string("      Description:  A client session is ended with an optional quit message.\n") +
    string("  /RESTART: \n") +
    string("      Parameters:   none\n") + 
    string("      Description:  Can only be used by an operator to force a server restart itself.\n") +
    string("  /RULES: \n") +
    string("      Parameters:   none\n") + 
    string("      Description:  Show the rules file for the local server.\n") +
    string("  /SETNAME: \n") +
    string("      Parameters:   [new name]\n") + 
    string("      Description:  Changes the client's real name.\n") +
    string("  /SILENCE: \n") +
    string("      Parameters:   \n") + 
    string("      Description:  \n") +
    string("  /TIME: \n") +
    string("      Parameters:   [server]\n") + 
    string("      Description:  Returns the local time from the server. If no parameter is given it checks the hosting server.\n") +
    string("  /TOPIC: \n") +
    string("      Parameters:   <channel> [<topic>]\n") + 
    string("      Description:  Used to change or view the topic of a channel.\n") +
    string("  /USER: \n") +
    string("      Parameters:   unknown\n") + 
    string("      Description:  \n") +
    string("  /USERHOST: \n") +
    string("      Parameters:   [nickname]\n") + 
    string("      Description:  Returns the hostname and nickname of a user, and some other miscellanious information.\n") +
    string("  /USERIP: \n") +
    string("      Parameters:   unknown\n") + 
    string("      Description:  \n") +
    string("  /USERS: \n") +
    string("      Parameters:   [server]\n") + 
    string("      Description:  Returns a list of users logged into the server.\n") +
    string("  /VERSION: \n") +
    string("      Parameters:   [<server>]\n") + 
    string("      Description:  Used  to  query  the  version  of  the  server program. Parameter is optional.\n") +
    string("  /WALLOPS: \n") +
    string("      Parameters:   [message for all operators]\n") + 
    string("      Description:  Sends  a  message  to  all   operators   currently   online.\n") +
    string("  /WHO: \n") +
    string("      Parameters:   [<name> [<o>]]\n") + 
    string("      Description:  Used by a client to generate a query which returns a list of information which 'matches' the <name> parameter given by the client.\n") +
    string("  /WHOIS: \n") +
    string("      Parameters:   [<server>] <nickname>\n") + 
    string("      Description:  Used to query information about particular user.\n");
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