# Diego Batres & Kat Moore
# CS457 Project 1
# Makefile

CC = g++ -g
CFLAGS = -Wall -c
LFLAGS = -Wall -pthread
SOBJS = Socket.o ServerSocket.o CommandParser.o ChatUser.o
COBJS = Socket.o
INCLUDE = -I.


all: server client

server: $(SOBJS)
	$(CC) $(SOBJS) $(LFLAGS) $(INCLUDE) server.cpp -o server
	
client: $(COBJS)
	$(CC) $(COBJS) $(LFLAGS) $(INCLUDE) client.cpp -o client

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

test1:
	make
	gnome-terminal --execute /s/bach/c/under/katbrown/cs457/cs457-p1/server 
	sleep 3
	gnome-terminal --execute client -h 127.0.0.1 -u testClient1 -p 2000 -t testCommands.txt

test2:
	make
	gnome-terminal --execute /s/bach/c/under/katbrown/cs457/cs457-p1/server 
	sleep 3
	gnome-terminal --execute client -h 127.0.0.1 -u kat -p 2000 -t katsTestCommands.txt
	gnome-terminal --execute client -h 127.0.0.1 -u diegob -p 2000 -t diegosTestCommands.txt

