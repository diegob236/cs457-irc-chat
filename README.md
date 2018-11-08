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