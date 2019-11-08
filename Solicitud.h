#ifndef SOLICITUD_H_
#define SOLICITUD_H_

#include "SocketMulticast.h"

class Solicitud
{
public:
	Solicitud();
	
	char * doOperation(char *IP, int puerto, int operationId, const char *arguments);

private:
	SocketMulticast * socketLocal;

	unsigned int msjId;
};


#endif