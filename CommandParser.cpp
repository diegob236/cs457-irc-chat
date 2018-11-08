#include "CommandParser.h"



// Command arguments
vector<string> args;

// parseCommand(): read IRC command and perform action
string parseCommand(ChatUser &user, map<string, vector<ChatUser>> &channels, const string &msg) {

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
        if (command == "/DIE") return d; //handleDIE(user, channels);
        if (command == "/HELP") return handleHELP();
        if (command == "/INFO") return handleINFO();
        if (command == "/INVITE") return handleINVITE(user, channels);
        if (command == "/ISON") return handleISON(channels);
        if (command == "/JOIN") return handleJOIN(user, channels);
        if (command == "/KICK") return d;
        if (command == "/KILL") return d;
        if (command == "/KNOCK") return d;
        if (command == "/LIST") return handleLIST(channels);
        if (command == "/MODE") return d;
        if (command == "/NICK") return handleNICK(user);
        if (command == "/NOTICE") return handleNOTICE(user, channels);
        if (command == "/OPER") return handleOPER(channels);
        if (command == "/PART") return d;
        if (command == "/PING") return d;
        if (command == "/PONG") return d;
        if (command == "/PRIVMSG") return handlePRIVMSG(user, channels);
        if (command == "/QUIT") return handleQUIT(user, channels);
        if (command == "/RESTART") return d;
        if (command == "/RULES") return handleRULES();
        if (command == "/SETNAME") return d;
        if (command == "/SILENCE") return d;
        if (command == "/TIME") return handleTIME();
        if (command == "/TOPIC") return d;
        if (command == "/USER") return d;
        if (command == "/USERHOST") return d;
        if (command == "/USERIP") return d;
        if (command == "/USERS") return d;
        if (command == "/VERSION") return handleVERSION();
        if (command == "/WALLOPS") return d;
        if (command == "/WHO") return d;
        if (command == "/WHOIS") return d;
        else return "Command not recognized. For a list of commands type /HELP.\n";
    }

    // Regular message
    else sendToEveryone(user, channels, "[#" + user.getChannel() + ":" + user.getUsername() + "] " + msg);
    return "";
}

/*                                          COMMANDS                                                    */
/*######################################################################################################*/


// HELP: get list of commands
string handleHELP() {
    string help = "\nAvailable IRC commands: \n" +
    string("  /AWAY: \n") +
    string("      Parameters:   [message]\n") + 
    string("      Description:  If a message is given, marks you as being away, otherwise removes your away status and previous message.\n") +
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
    string("      Parameters:   <nickname>\n") + 
    string("      Description:  Shows if nickname is currently online.\n") +
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
    string("      Parameters:   <user>\n") + 
    string("      Description:  Tells you if user is an operator.\n") +
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
    string("      Parameters:   \n") + 
    string("      Description:  Returns the local time from the server.\n") +
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
    string("      Description:  Used to query information about particular user.\n\n");
    return help;
}


// INFO: get server information
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
                    "*Disclaimer* No dragons contributed to the \ndevelopement of this project.\n\n";                             
    return info; 
}


// INVITE: invite user to channel
string handleINVITE(ChatUser &user, map<string, vector<ChatUser>> &channels) {

    // Check for correct number of arguments
    if (args.size() == 2) {

        bool channelExists = false;
        string username = args[0];
        string channel = args[1];

        // Check if channel exists
        for(map<string, vector<ChatUser>>::iterator it = channels.begin(); it != channels.end(); it++)
            if ((it->first) == channel) channelExists = true;
        if (!channelExists) return "/INVITE: Channel " + channel + " does not exist. You can create it by running the command /JOIN " + channel + ".\n";

        // Search for user and send message
        for(map<string, vector<ChatUser>>::iterator it = channels.begin(); it != channels.end(); it++) {
            for (uint i = 0; i < it->second.size(); i++) {
                if ((it->second)[i].getUsername() == username) {
                    (it->second)[i].sendString(user.getUsername() + " has invited you to join #" + channel + "! Join by running the command /JOIN " + channel + ".\n");
                    return "Invite sent to " + username + ".\n";
                }
            }
        }

        // User was not found
        return "/INVITE: User " + args[0] + " was not found.\n";
    }
    else return "/INVITE: Please specify a user and a channel.\n";
}


// ISON: returns online users
string handleISON(map<string, vector<ChatUser>> &channels) {
    if (args.size() > 0){
        string ison; bool found;

        // Search for user in active channels
        for(uint j = 0; j < args.size(); j++){
            found = false;
            for(map<string, vector<ChatUser>>::iterator it = channels.begin(); it != channels.end(); it++) {
                for (uint i = 0; i < it->second.size(); i++) {
                    if ((it->second)[i].getUsername() == args[j] && !found) {
                        ison += args[j] + " is online.\n";
                        found = true;
                    }
                }
            }
        }
        return ison;
    }
    else return "/ISON: Please specify one or more users.\n";   
}


// JOIN: join channel
string handleJOIN(ChatUser &user, map<string, vector<ChatUser>> &channels) {
    if (args.size() > 0) {

        // Create new channel if it doesn't exist
        if (channels[args[0]].empty()) cout << "New channel #" << args[0] << " created by " << user.getUsername() << "." << endl;
        user.setChannel(args[0]);

        // User is not in channel, send join message
        if (!userIsInChannel(user, channels)) {
            channels[user.getChannel()].push_back(user);
            sendToEveryone(user, channels, user.getUsername() + " has joined the #" + user.getChannel() + " channel!\n");
            return "You have now joined the #" + user.getChannel() + " channel!\n";
        }

        // User is already in channel, send switch message
        else {
            cout << user.getUsername() << " switched back to #" << user.getChannel() << "." << endl;
            return "Switched back to #" + user.getChannel() + ".\n";
        }

    }
    else return "/JOIN: Please specify a channel name.\n";
}


// LIST: list channels on server
string handleLIST(map<string, vector<ChatUser>> &channels) {
    string list = "Channels:\n";
    for(map<string, vector<ChatUser>>::const_iterator it = channels.begin(); it != channels.end(); it++)
        list += "  " + it->first + "\n";
    return list + "\n";
}


// NICK: changes username
string handleNICK(ChatUser &user){
    if (args.size() == 1){
        string newUsername = args[0];
        user.setUsername(newUsername);
        user.sendString("^" + user.getUsername() + "\n");
        return "Changed username to " + newUsername + ".\n";
    }
    else if (args.size() == 0){
        return "Your username is " + user.getUsername() + "\n";
    }
    else return "/NICK: To change username please run again and specify a username (1 word)\n or run with no args and see current username.\n";
}


// NOTICE: send notice to user
string handleNOTICE(ChatUser &user, map<string, vector<ChatUser>> &channels) {

    // Check for correct number of arguments
    if (args.size() > 1) {
        bool userFound = false;
        string username = args[0];
        string notice = "[NOTICE:" + user.getUsername() + "] ";
        for(uint i = 1; i < args.size(); i++) notice += args[i] + ' ';

        // Search for user and send message
        for(map<string, vector<ChatUser>>::iterator it = channels.begin(); it != channels.end(); it++) {
            for (uint i = 0; i < it->second.size(); i++) {
                if ((it->second)[i].getUsername() == username) {
                    (it->second)[i].sendString(notice + "\n");
                    userFound = true;
                }
            }
        }

        // User was not found
        if (!userFound) return "/NOTICE: User " + args[0] + " was not found.\n";
        else return "";
    }
    else return "/NOTICE: Please specify a target user and message.\n";
}


// OPER: checks if a user is an admin/channelop/sysop
string handleOPER(map<string, vector<ChatUser>> &channels){
    if (args.size() > 0){
        string username = args[0];
        bool userFound = false;

        // Search through channels
        for(map<string, vector<ChatUser>>::iterator it = channels.begin(); it != channels.end(); it++) {
            for (uint i = 0; i < it->second.size(); i++) {
                if ((it->second)[i].getUsername() == username) {
                    userFound = true;
                    if ((it->second)[i].getLevel() != "user") return username + " has " + (it->second)[i].getLevel() + "privileges.\n";
                }
            }
        }
        if (!userFound) return "/OPER: User " + username + " was not found.\n";
        else return "User " + username + " has no special privileges.\n";
    }
    else return "/OPER: Please specify a single user to check operator privileges.\n";
}


// PRIVMSG: send private message to user
string handlePRIVMSG(ChatUser &user, map<string, vector<ChatUser>> &channels) {

    // Check for correct number of arguments
    if (args.size() > 1) {
        bool userFound = false;
        string username = args[0];
        string prvmsg = "[PRIVMSG:" + user.getUsername() + "] ";
        for(uint i = 1; i < args.size(); i++) prvmsg += args[i] + ' ';

        // Search for user and send message
        for(map<string, vector<ChatUser>>::iterator it = channels.begin(); it != channels.end(); it++) {
            for (uint i = 0; i < it->second.size(); i++) {
                if ((it->second)[i].getUsername() == username) {
                    (it->second)[i].sendString(prvmsg + "\n");
                    userFound = true;
                    return "";
                }
            }
        }

        // User was not found
        if (!userFound) return "/PRIVMSG: User " + args[0] + " was not found.\n";
        else return "";
    }
    else return "/PRIVMSG: Please specify a target user and message.\n";
}


// QUIT: disconnect from server
string handleQUIT(ChatUser &user, map<string, vector<ChatUser>> &channels) {

    // Print goodbye message if specified
    if (args.size() > 0) {
        string goodbye = "[#" + user.getChannel() + ":" + user.getUsername() + "] ";
        for(uint i = 0; i < args.size(); i++) goodbye += args[i] + ' ';
        sendToEveryone(user, channels, goodbye + "\n");
    }

    // Disconnect client
    user.sendString("/QUIT\n");
    sendToEveryone(user, channels, user.getUsername() + " has left the chat.\n");
    user.disconnect();
    return "/QUIT\n";
}


// RULES: get server rules
string handleRULES(){
    string rules = "Chat Rules are simple:\n" +
                    string("   1.) Don't be rude.\n") +
                    string("   2.) But if you are there are no consequences here.\n\n");
    return rules;
}


// TIME: get server time
string handleTIME(){
    if (args.size() < 1){
        time_t t = time(0);   // get time now
        struct tm  tstruct;   // Use a time struct for better format
        char       time[80];
        tstruct = *localtime(&t);
        strftime(time, sizeof(time), "%Y-%m-%d.%X\n", &tstruct);

        return time;
    }
    else return "/TIME: please specify no arguments to see current server time.\n";

}


// VERSION: get server version
string handleVERSION() {
    string version = "\nIRC Server Version 1.0\n\n";
    return version;
}


/*######################################################################################################*/


// userIsInChannel(): checks if a user is already in a channel
bool userIsInChannel(ChatUser &user, map<string, vector<ChatUser>> &channels) {
    for (uint i = 0; i < channels[user.getChannel()].size(); i++)
        if (channels[user.getChannel()][i].getUsername() == user.getUsername()) return true;
    return false;
}


// sendToEveryone(): send message to everyone in channel and display on server
void sendToEveryone(ChatUser user, map<string, vector<ChatUser>> &channels, string msg) {
    cout << msg;
    for (uint i = 0; i < channels[user.getChannel()].size(); i++)
        if (channels[user.getChannel()][i].getUsername() != user.getUsername())
            channels[user.getChannel()][i].sendString(msg);
}