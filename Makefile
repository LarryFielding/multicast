all: receptor emisor
receptor: receptor.cpp SocketMulticast.o PaqueteDatagrama.o
	g++ receptor.cpp SocketMulticast.o PaqueteDatagrama.o -o receptor
emisor: emisor.cpp SocketMulticast.o PaqueteDatagrama.o
	g++ emisor.cpp SocketMulticast.o PaqueteDatagrama.o -o emisor
SocketMulticast.o: SocketMulticast.cpp SocketMulticast.h PaqueteDatagrama.o
	g++ SocketMulticast.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c
