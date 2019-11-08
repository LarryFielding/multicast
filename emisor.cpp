#include "SocketMulticast.h"
#include "PaqueteDatagrama.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc < 5)
	{
		cout << "Debe ingresar: " << endl;
		cout << "./emisor ipMulticast puerto TTL \"Mensaje\"" << endl;
		exit(1);
	}

    char ipRemota[50], mensaje[200];
    strcpy(ipRemota, argv[1]);
	int puerto = atoi(argv[2]);
	unsigned char ttl = atoi(argv[3]);
	strcpy(mensaje, argv[4]);
	string sMensaje = string(mensaje);
	int tam = sMensaje.length() + 1;

	SocketMulticast socket  = SocketMulticast(puerto);
	PaqueteDatagrama paquete_env = PaqueteDatagrama(mensaje, tam, ipRemota, puerto);

	int enviados = socket.envia(paquete_env, ttl);

	return 0;
}