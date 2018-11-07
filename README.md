# Chat Client and Server
This project consists of a chat server and chat client that work together to form a chat application with users, channels, direct messages, and other functions. The model is based off the IRC protocol.

## To compile and run server
In order to get the server up and running please ensure you are in the project directory then:
  - To compile: `make'
  - To run server: `./server`

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
