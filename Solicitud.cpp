#include "Solicitud.h"
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

Solicitud::Solicitud() : msjId(0)
{
	socketLocal = new SocketDatagrama(0);
}

char * Solicitud::doOperation(char *IP, int puerto, int operationId, const char *arguments)
{
	int bytes_env, bytes_recv;

	// Crear mensaje que se envía:
	struct mensaje cmensaje;
    cmensaje.messageType = 0;
    cmensaje.requestId = ++msjId;
    cmensaje.operationId = suma;
    strcpy(cmensaje.arguments, arguments);
	// Adjuntar al paquete datagrama:
	PaqueteDatagrama paquete_env = PaqueteDatagrama(&cmensaje, sizeof(cmensaje), IP, puerto);

	// Enviar:
	bytes_env = socketLocal->enviaMensaje(paquete_env);

	if (bytes_env < 0)
    {
        perror("Fallo en envio");
        exit(1);
    }

    PaqueteDatagrama paquete_recv = PaqueteDatagrama(MAX_BUFF_TAM);

    bytes_recv = socketLocal->recibeMensaje(paquete_recv);

    if (bytes_recv < 0)
    {
        perror("Error al recibir");
        exit(1);
    }

    return paquete_recv.obtieneMensaje()->arguments;
}
