#include "SocketMulticast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
	int bytes_recv;
	if (argc < 3)
	{
		cout << "Debe ingresar: " << endl;
		cout << "./receptor ipMulticast puerto" << endl;
		exit(1);
	}

    char ipRemota[50];
    strcpy(ipRemota, argv[1]);
	int puerto = atoi(argv[2]);

	SocketMulticast socket  = SocketMulticast(puerto);
	PaqueteDatagrama paquete_recv = PaqueteDatagrama(TAM_MAX_DATA);

	socket.unirseGrupo(ipRemota);

	while(1)
	{
		bytes_recv = socket.recibe(paquete_recv);

		cout << "Bytes recibidos: " << bytes_recv << endl;
        cout << "Cliente dijo: " << paquete_recv.obtieneDatos() << endl;
        cout << "Recibido desde ip: " <<  ipRemota << endl;
        cout << "Con puerto: " << puerto << endl;
	}
	
	return 0;
}