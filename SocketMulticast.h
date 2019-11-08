#ifndef SOCKET_MULTICAST_H_
#define SOCKET_MULTICAST_H_

#include <netinet/in.h>

#include "PaqueteDatagrama.h"

class SocketMulticast
{
public:
    SocketMulticast(int);
    ~SocketMulticast();
    int recibe(PaqueteDatagrama & p);
    int envia(PaqueteDatagrama & p, unsigned char ttl);
    //Se une a un grupo multicast, recibe la IP multicast
    void unirseGrupo(char *);
    //Se sale de un grupo multicast, recibe la IP multicast
    void salirseGrupo(char *);

    // Funciones para envío de mensajes:
    int enviaMensaje(PaqueteDatagrama & p);

    int recibeMensaje(PaqueteDatagrama & p);

    int recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos);

    const void * obtieneDireccionForanea();

    int obtienePuertoForaneo();

private:
    int s; //ID socket
    int puerto;
    struct sockaddr_in addrLocal;
    struct sockaddr_in addrForanea;
    struct ip_mreq multicast;
    struct timeval timeout;
};

#endif
