all: receptor emisor
receptor: receptor.cpp Respuesta.o SocketMulticast.o PaqueteDatagrama.o
	g++ receptor.cpp Respuesta.o SocketMulticast.o PaqueteDatagrama.o -o receptor
emisor: emisor.cpp Solicitud.o SocketMulticast.o PaqueteDatagrama.o
	g++ emisor.cpp Solicitud.o SocketMulticast.o PaqueteDatagrama.o -o emisor
Solicitud.o: Solicitud.cpp Solicitud.h mensaje.h SocketMulticast.o PaqueteDatagrama.o
	g++ Solicitud.cpp -c
Respuesta.o: Respuesta.cpp Respuesta.h SocketMulticast.o PaqueteDatagrama.o
	g++ Respuesta.cpp -c
SocketMulticast.o: SocketMulticast.cpp SocketMulticast.h PaqueteDatagrama.o
	g++ SocketMulticast.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c
