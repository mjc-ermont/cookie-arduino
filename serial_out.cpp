#include <Arduino.h>
#include "defines.h"
#include "serial_out.h"

SerialOut::SerialOut(){
}

bool SerialOut::init(){          // Initialisation du port serie (SERIAL_BAUDRATE defini dans defines.h)
  /*out = new SoftwareSerial(0,1);
  out->begin(SERIAL_BAUDRATE);*/
  Serial.begin(SERIAL_BAUDRATE);
}

void SerialOut::writeQueue(char* trame){    // Eccriture de la file sur la sortie
  for (byte i = 0 ; i < NB_REPET ; i++){        // Plusieurs fois au cas ou le recepteur de receptionnerait pas les premieres fois
    for (byte j = 0; j < 41; j ++){
        //out->print(trame);
      Serial.write(trame[j]);
    }
  }
  //Serial.print("\n");
}
