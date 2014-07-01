#include "Fat16.h"
#include "defines.h"
#include "sd_out.h"

SdOut::SdOut(){
  
}

bool SdOut::init(){          // Initialisation de la carte sd
  /*if (!SD.begin(SD_CS_PIN)) {
    Serial.println(F("Card failed, or not present"));
  } else {
    Serial.println(F("INIT OK"));
  }*/
  SdCard card;
  if (!card.init()) {
    //Serial.println(F("Card init. failed")); 
  }

  if (!Fat16::init(&card)) {
	//Serial.println(F("No partition!")); 
  }}

void SdOut::writeQueue(char* trame){    // Eccriture de la file sur la sortie
  /*File file = SD.open("l", FILE_WRITE);
  if(!(file)){
    Serial.println(F("Can't write to file"));
  }
  file.print(trame);                     // Ecriture de l'element courant
  //file.flush();                          // attente de la fin de l'ecriture
  file.close();*/
  Fat16 f;
  f.open("L", O_CREAT | O_WRITE | O_APPEND);
  /*if(!f.isOpen()) {
    Serial.println(F("couldnt create "));
  }*/
  f.write((uint8_t*) trame, strlen(trame));
}
