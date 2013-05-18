#ifndef ACCEL_INCLUDED
#define ACCEL_INCLUDED

#define POWER_CTL 0x2D	//Power Control Register
#define DATA_FORMAT 0x31
#define DEVICE (0x53)


#include <Arduino.h>
#include "vector.h"
#include "out.h"
#include "capteur.h"

class Accel : public Capteur{
public:
	Accel(const byte &id_capt);
	bool init(); // methode de recuperation des donnees de l'accelerometre
	bool refresh(); // methode de recuperation des donnees de l'accelerometre
//        void getTrame(); // methode d'envoi de la trame

private:
        void writeTo(byte address, byte val);
        void readFrom(byte address, byte _buff[]);
};
#endif
