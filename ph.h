#ifndef PH_INCLUDED
#define PH_INCLUDED

#include <Arduino.h>
#include "capteur.h"

class pH : public Capteur {
public:
	pH(const byte &id);
	bool init();
	bool refresh();

};

#endif
