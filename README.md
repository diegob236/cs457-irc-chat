# CppSocketWraper
This is basic C++ wrapper for Posix Socket. It has been tested in Ubuntu 18.04 -- it can be improved. 

License is GNU General Public License's Version 3.  

Project1-Skeleton contains the code. Read the .vscode folder as it has my settings. Change them as needed. 

# To Compile Server
In order to get the server up and running please ensure you are in the project director then run

make; server

# To join as a Client
To join the server as a client run

client -h 127.0.0.1 -u <username> -p 2000 -c client.cpp
  
  -h is hostname 
  -u is username
  -p is port number
  -c is the config file

# Chat Rules
After you've joined the server as a client, you may
1). Type any text and hit enter to send a message to all other clients
2). Type /command (+ its optional or required parameters) to run a command
3). Type /help to see a list of available commands and their parameters
