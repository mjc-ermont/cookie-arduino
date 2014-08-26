#include "ph.h"
#include "trame.h"
#include "defines.h"

pH::pH(const byte &id) : Capteur::Capteur(id, 1){

}

bool pH::init(){
  Serial2.begin(SERIAL_BAUDRATE_PH);
}

bool pH::refresh(){
  byte nbread = Serial2.readBytesUntil(13,_val[ID_VAL_LAT_DEG], SIZE_VALUE+1);
  _val[ID_VAL_LAT_DEG][nbread] = '\0';
}
