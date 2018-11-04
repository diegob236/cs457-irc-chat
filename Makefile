# Makefile

make:
	g++ -g Socket.cpp ServerSocket.cpp server.cpp CommandParser.cpp -pthread -o server
	g++ -g Socket.cpp client.cpp -pthread -o client

clean:
	-rm server client
