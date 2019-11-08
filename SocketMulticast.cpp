#include "SocketMulticast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <iostream>

using namespace std;

SocketMulticast::SocketMulticast(int p) : puerto(p)
{
	s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s < 0)
	{
		perror("No se pudo crear socket");
		exit(1);
	}

	memset(&addrLocal, 0, sizeof(addrLocal));
	addrLocal.sin_family = AF_INET;
	addrLocal.sin_addr.s_addr = INADDR_ANY; //htonl(INADDR_ANY)
	addrLocal.sin_port = htons(puerto);

	/* receive */
	if (bind(s, (struct sockaddr *) &addrLocal, sizeof(addrLocal)) < 0)
  	{
  		perror("bind");
  		exit(1);
  	}
}

SocketMulticast::~SocketMulticast() 
{
	close(s);
}

int SocketMulticast::recibe(PaqueteDatagrama &p)
{
	int bytes_recv;
	socklen_t tam_dir;
	char ipRemota[INET_ADDRSTRLEN];
	
	tam_dir = sizeof(addrLocal);
	cout << "Esperando mensaje..." << endl;
	
	bytes_recv = recvfrom(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &addrLocal, &tam_dir);
	if (bytes_recv < 0)
	{
		perror("Error al recibir");
		exit(1);
	}
	/* Imprimir en consola la dirección y puerto del host remoto (asignarlas a PaqueteDatagrama)*/
	
	inet_ntop(AF_INET, &(addrLocal.sin_addr), ipRemota, INET_ADDRSTRLEN);
	p.inicializaIp(ipRemota);
	p.inicializaPuerto(htons(addrLocal.sin_port));
	
	return bytes_recv;
}

int SocketMulticast::envia(PaqueteDatagrama &p, unsigned char tt)
{
	if (tt == 0x0)
	{
		tt = 0x01;
	}

	/* Paso 3.a : es emisor */
	/* Llenar estructura (direccion remota) */
	memset(&addrForanea, 0, sizeof(addrForanea));
	addrForanea.sin_family = AF_INET;
	addrForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
	addrForanea.sin_port = htons(p.obtienePuerto());

	if (setsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &tt ,sizeof(tt)) < 0)
	{
        perror("setsockopt");
        exit(1);
    }

	int bytes_env;
	socklen_t tam_dir;

	tam_dir = sizeof(addrForanea);

	bytes_env = sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &addrForanea, tam_dir);
	if (bytes_env < 0)
	{
		perror("Fallo en envio");
		exit(1);
	}

	return bytes_env;
}

void SocketMulticast::unirseGrupo(char *ipMulticast)
{
	

	/* 224.0.0.0 hasta la 239.255.255.255 */
	multicast.imr_multiaddr.s_addr = inet_addr(ipMulticast); /* Dirección IP del grupo multicast */
	multicast.imr_interface.s_addr = htonl(INADDR_ANY); /* Dirección IP de la interfaz local IP */

	
	if (setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicast, sizeof(multicast)) < 0)
	{
        perror("setsockopt");
        exit(1);
    }
}

void SocketMulticast::salirseGrupo(char *ipMulticast)
{
	/* 224.0.0.0 hasta la 239.255.255.255 */
	multicast.imr_multiaddr.s_addr = inet_addr(ipMulticast); /* Dirección IP del grupo multicast */
	multicast.imr_interface.s_addr = htonl(INADDR_ANY); /* Dirección IP de la interfaz local IP */

	if (setsockopt(s, IPPROTO_IP, IP_DROP_MEMBERSHIP, (void *) &multicast, sizeof(multicast)) < 0)
	{
        perror("setsockopt");
        exit(1);
    }
}