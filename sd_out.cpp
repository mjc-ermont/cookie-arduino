#include "defines.h"
#include "sd_out.h"
#include <SD.h>

SdOut::SdOut(){
  
}

bool SdOut::init(){          // Initialisation de la carte sd
  if (!SD.begin(SD_CS_PIN)) {
    //Serial.println(F("Card failed, or not present"));
  } else {
    //Serial.println(F("INIT OK"));
  }
}

void SdOut::writeQueue(char* trame){    // Eccriture de la file sur la sortie
  File file = SD.open("l", FILE_WRITE);
  if(!(file)){
    //Serial.println(F("Can't write to file"));
  }
  file.print(millis());
  file.print(F(","));
  file.println(trame);                     // Ecriture de l'element courant
  file.flush();                          // attente de la fin de l'ecriture
  file.close();
}
