#ifndef OUT_INCLUDED
#define OUT_INCLUDED

#include <Arduino.h>



class Out {
public:
	Out();
	virtual bool init() = 0;        // Initialisation de la sortie
        virtual void writeQueue(char*) = 0;  // Ecriture de la file sur la sortie
protected:
};

#endif
