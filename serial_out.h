#ifndef SERIALOUT_INCLUDED
#define SERIALOUT_INCLUDED
#include <Arduino.h>
#include "out.h"
#include "sws.h"


class SerialOut : public Out {
public:
	SerialOut();
	virtual bool init();        // Initialisation du port serie
        virtual void writeQueue(char*);  // Ecriture de la sortie sur le port serie
private: 
        SoftwareSerial *out;
};

#endif // SERIALOUT_INCLUDED
