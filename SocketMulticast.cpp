#include "SocketMulticast.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 

SocketMulticast::SocketMulticast(int puerto)
{
	unsigned char TTL = 0x01;

	/* Paso 1: crear el socket */
	s = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s < 0)
	{
		perror("No se pudo crear socket");
		exit(1);
	}

	/* Paso 2: llenar estructura (direccion local) */

	memset(&direccionLocal, 0, sizeof(direccionLocal));
	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_addr.s_addr = INADDR_ANY;
	direccionLocal.sin_port = htons(puerto);

	if (puerto > 0)
	{
		/* Paso 3.a : es emisor */
		if (setsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &TTL ,sizeof(TTL)) < 0)
		{
	        perror("setsockopt");
	        exit(1);
	    }
	}
	else
	{
		multicast.imr_multiaddr.s_addr = inet_addr(multicastIP);
		multicast.imr_interface.s_addr = htonl(INADDR_ANY);

		/* Paso 3.b : es receptor y desea unirse al grupo de receptores */
		if (setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicast, sizeof(multicast)) < 0)
		{
	        perror("setsockopt");
	        exit(1);
	    }
	}

	/* Paso 3: publicar direccion */

	if ((bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal))) < 0)
	{
		perror("Error al publicar");
		exit(1);
	}
}