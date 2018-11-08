# Diego Batres & Kat Moore
# CS457 Project 1
# Makefile

CC = g++ -g
CFLAGS = -Wall -c
LFLAGS = -Wall -pthread
SOBJS = Socket.o ServerSocket.o CommandParser.o ChatUser.o server.o
COBJS = Socket.o client.o
INCLUDE = -I.


all: server client

server: $(SOBJS)
	$(CC) $(SOBJS) $(LFLAGS) $(INCLUDE) -o server
	
client: $(COBJS)
	$(CC) $(COBJS) $(LFLAGS) $(INCLUDE) -o client

server.o: server.cpp
	$(CC) server.cpp $(INCLUDE) $(CFLAGS)
	
client.o: client.cpp
	$(CC) client.cpp $(INCLUDE) $(CFLAGS)

Socket.o: Socket.cpp Socket.h
	$(CC) Socket.cpp $(INCLUDE) $(CFLAGS)

ServerSocket.o: ServerSocket.cpp ServerSocket.h
	$(CC) ServerSocket.cpp $(INCLUDE) $(CFLAGS)

CommandParser.o: CommandParser.cpp CommandParser.h
	$(CC) CommandParser.cpp $(INCLUDE) $(CFLAGS)
	
ChatUser.o: ChatUser.cpp ChatUser.h
	$(CC) ChatUser.cpp $(INCLUDE) $(CFLAGS)

clean:
	-rm *.o server client

test:
	make
	gnome-terminal --execute /s/bach/c/under/katbrown/cs457/cs457-p1/server 
	sleep 3
	gnome-terminal --execute client -h 127.0.0.1 -u client1 -p 2000 -t testCommands.txt

