#include "capteur_analog.h"

CapteurAnalog::CapteurAnalog(byte id, byte pin) : Capteur::Capteur(id, 1){
  _pin = pin;
}

bool CapteurAnalog::init(){
}

bool CapteurAnalog::refresh(){
  itoa(analogRead(_pin), _val[0], 10);
}
