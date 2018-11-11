# Chat Client and Server
This project consists of a chat server and chat client that work together to form a chat application with users, channels, direct messages, and other functions. The model is based off the IRC protocol.

## To compile and run server
In order to get the server up and running please ensure you are in the project directory then:
  - To compile: `make'
  - To run server: `server`

## To join as a client
To join the server as a client run
  - `client -h 127.0.0.1 -u <username> -p 2000`
  - -h: hostname  (127.0.0.1)
  - -u: username
  - -p: port number (2000)

## Chat Rules
After you've joined the server as a client, you may    
1). Type any text and hit enter to send a message to all other clients    
2). Type `/command` (+ its optional or required parameters) to run a command    
3). Type `/help` to see a list of available commands and their parameters

## To Run Tests
We have two tests, 
1). test1 which goes through all implemented commands
2). test2 which displays client-client interaction

To run them simply type "make test1" or "make test2"

This will launch new terminals with the server and clients running, please separate these terminals so you can see all output.
Now watch what happens! We recommend launching these tests a few times so you can watch each output window, starting with the server. 

A final option to run the testCommands with any client is to append the -t option when compiling a client, this looks like 

client -h 127.0.0.1 -u newUser -p 2000 -t testCommands.txt

## List of Implemented Commands For Project 1
1. Help - displays list of implemented commands
2. Info - diplays information about the developers of this project
3. Ison [username] - checks to see if username is online
4. Users - Displays everyone online
5. Ping - checks server presence and sends back 'PONG'
6. Pong - sends back 'PING'
7. Oper [username] - Will check if username is online and returns what kind of privelege they have (user, admin, sysop, or channelop)
8. Notice [username] [message] - sends a private message to username
9. Privmsg [username] [message] - sends a private message that does not show up on the server to username
10. Rules - displays server rules
11. Setname [newUsername] - Changes your username and checks that its unique or tells you what it is if run without an argument
12. Nick [newNickname] - Changes your username and checks that its unique or tells you what it is if run without an argument. A future implementation will be differentiating 11 and 12
13. Join [channel] - Allows you to join a channel. A future implementation will be channel passwords.
14. Knock [channel] [message] - Knocks on a channel by sending the optional message or a default message to all users in the channel
15. List - displays a list of all channels
16. Kick [username] [reason] - Removes username from a channel and displays the optional reason
17. Time - displays the current time
18. Silence - displays a nice quote about silence
19. User - displays your username
20. Userhost - displays your hostname
21. Userip - displays your IP address
22. Version - displays the version of the chat server
23. Who - displays your username. In the future it will also display additional miscealaneous information about a user
24. Whois - displays your username and hostname.
25. Invite [username] [channel] - sends an invitation to username requesting they join channel
26. Kill [username] - removes the username from the chat if you are an admin or sysop
27. Die - shuts does the server if you are an admin
28. Quit [message] - ends the client connection and tells everyone in your channel that you left and displays the optional message
