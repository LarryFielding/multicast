#ifndef RESPUESTA_H_
#define RESPUESTA_H_

#include "SocketMulticast.h"

class Respuesta
{
public:
	Respuesta(int pl);

	struct mensaje * getRequest(void);

	void sendReply(char * respuesta);

private:
	SocketMulticast * socketLocal;

	unsigned int msjId;
	
};


#endif