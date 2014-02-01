#include "accel.h"
#include "trame.h"
#include "defines.h"
#include <Arduino.h>
#include <Wire.h>
#include "capteur.h"

Accel::Accel(const byte &id_capt) : Capteur::Capteur(id_capt, 1){

}

bool Accel::init(){ // methode d'iniialisation de l'accelerometre
  Wire.begin();                  // initialisation de la bibliotheque I2C
  delay(100);
  this->writeTo(DATA_FORMAT, 0x01);
  this->writeTo(POWER_CTL, 0x08);
}

bool Accel::refresh(){ // methode de recuperation des donnees de l'accelerometre
  byte _buff[6];
  short int acc_data[3];             // Tableau des trois composantes du vecteur d'acceleration
  short int avg = 0;                 // Norme du vecteur d'acceleration
  
  this->readFrom(0x32, _buff);
  
  acc_data[0] = (((short int)_buff[1]) << 8) | _buff[0];   
  acc_data[1] = (((short int)_buff[3]) << 8) | _buff[2];
  acc_data[2] = (((short int)_buff[5]) << 8) | _buff[4];  
  
  for(byte i = 0; i < 3; i++){    // Calcul de la norme du vecteur d'acceleration
    avg += acc_data[i] * acc_data[i];
  }
  
  itoa((int)(100*sqrt(avg)), _val[0], 10);
  //Serial.println((int)(avg*100));
}

/*void Accel::getTrame(){ // methode d'envoi de la trame
    String trame = "#$";                     // debut +separaeur
    trame += ID_CAPT_ACCEL;                  // Ajout de l'ID du capteur
    trame += "$0$";                          // separaeur + ID valeur + separateur
    for (byte j = 0 ;  j < SIZE_VALUE - _avg.length() ; j++) trame += "0"; // remplissage de la taille maximale de la valeur pour que la trame envoyée ait une longueur constante
    trame += _avg;                           // Ajout de la valeuts
    trame += "$";                            // separaeur
    trame += String(get_checksum(trame), HEX);// Ajout du checksum
    trame += "$@";                           // separaeur + fin
    for (int i = 0 ; i < _out.size() ; i++){ // envoi de la trame a toutes les sorties (d'ou le for)
      _out[i].addTrame(trame);               // Ajout de la trame a la file d'envoi
      _out[i].writeQueue();                  // écriture sur la sortie de la file d'envoi 
    }
}*/

void Accel::writeTo(byte address, byte val) {
  Wire.beginTransmission(DEVICE); // start transmission to device 
  Wire.write(address);             // send register address
  Wire.write(val);                 // send value to write
  Wire.endTransmission();         // end transmission
}

// Reads num bytes starting from address register on device in to _buff array
void Accel::readFrom(byte address, byte _buff[]) {
  Wire.beginTransmission(DEVICE); // start transmission to device 
  Wire.write(address);             // sends address to read from
  Wire.endTransmission();         // end transmission

  Wire.beginTransmission(DEVICE); // start transmission to device
  Wire.requestFrom(DEVICE, 6);    // request 6 bytes from device

  int i = 0;
  while(Wire.available())         // device may send less than requested (abnormal)
  { 
    _buff[i] = Wire.read();    // receive a byte
    i++;
  }
  Wire.endTransmission();         // end transmission
}
