#include "SocketMulticast.h"
#include "PaqueteDatagrama.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc < 6)
	{
		cout << "Debe ingresar: " << endl;
		cout << "./emisor ipMulticast puerto TTL int_1 int_2" << endl;
		exit(1);
	}

    char ipRemota[50], mensaje[200];
    strcpy(ipRemota, argv[1]);
	int puerto = atoi(argv[2]);
	unsigned char ttl = atoi(argv[3]);
	
	string args;
    args += argv[4];
    args += " ";
    args += argv[5];
    const char * cargs = args.c_str();


	SocketMulticast socket  = SocketMulticast(puerto);
	PaqueteDatagrama paquete_env = PaqueteDatagrama(mensaje, tam, ipRemota, puerto);

	int enviados = socket.envia(paquete_env, ttl);

	return 0;
}