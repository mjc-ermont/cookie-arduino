#ifndef SDOUT_INCLUDED
#define SDOUT_INCLUDED
#include <Arduino.h>
#include "out.h"

class SdOut : public Out {
public:
	SdOut();
	virtual bool init();        // Initialisation du port serie
        virtual void writeQueue(char*);  // Ecriture de la sortie sur le port serie
private:
        //File &_file;
};

#endif // SDOUT_INCLUDED
