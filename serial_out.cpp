#include <Arduino.h>
#include "defines.h"
#include "sws.h"
#include "serial_out.h"

SerialOut::SerialOut(){
}

bool SerialOut::init(){          // Initialisation du port serie (SERIAL_BAUDRATE defini dans defines.h)
  out = new SoftwareSerial(2,3);
  out->begin(600);
  Serial.begin(SERIAL_BAUDRATE);
}

void SerialOut::writeQueue(char* trame){    // Eccriture de la file sur la sortie
  //for(byte h = 0 ; h < queue.count() ; h++){    // Ecriture de la totalité de la file
    //char *trame = queue.pop();
    for (byte i = 0 ; i < NB_REPET ; i++){        // Plusieurs fois au cas ou le recepteur de receptionnerait pas les premieres fois
      out->print(trame);
      Serial.print(trame);
    }
    //free(trame);
  //}
}
