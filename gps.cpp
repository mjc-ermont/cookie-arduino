#include "gps.h"
#include "trame.h"
#include "defines.h"
#include "TinyGPS.h"

GPS::GPS(const byte &id) : Capteur::Capteur(id, NB_VAL_GPS){

}

bool GPS::init(){
  Serial1.begin(SERIAL_BAUDRATE_GPS);
}

bool GPS::refresh(){
      long flat, flon;
      unsigned long age, date, time, fix_age;
      while(Serial1.available()>0){
        _gps.encode(Serial1.read());
      }     
      _gps.get_position(&flat, &flon, &age);  
      _gps.get_datetime(&date, &time, &fix_age);

      String(flat).toCharArray(_val[ID_VAL_LAT_DEG], SIZE_VALUE+1);
      String(flon).toCharArray(_val[ID_VAL_LON_DEG], SIZE_VALUE+1);
      String(_gps.speed()).toCharArray(_val[ID_VAL_VIT], SIZE_VALUE+1);
      String(_gps.altitude()).toCharArray(_val[ID_VAL_ALT], SIZE_VALUE+1);
      String(time).toCharArray(_val[ID_VAL_UTIME], SIZE_VALUE+1);

}

/*void GPS::getTrame(){
  debug("dtg");
  for (byte i = 0 ; i < 6 ; i++){          // Pour chaque valeur envoyée par le GPS
    String id_capt, val_capt;                             // variables contenant respectivement l'id et la valeur de la donnee du GPS en cours d'envoi
    switch (i){                                           // On attribue a la variable temporaire la valeur et l'ID de la donnee du GPS en cours d'envoi
      case 0:
        id_capt = ID_VAL_LAT_DEG;
        val_capt = _lat_deg;
      break;
      case 1:
        id_capt = ID_VAL_LAT_MIN;
        val_capt = _lat_min;
      break;
      case 2:
        id_capt = ID_VAL_LON_DEG;
        val_capt = _lon_deg;
      break;
      case 3:
        id_capt = ID_VAL_LON_MIN;
        val_capt = _lon_min;
      break;
      case 4:
        id_capt = ID_VAL_VIT;
        val_capt = _vit;
      break;
      case 5:
        id_capt = ID_VAL_UTIME;
        val_capt = _utime;
      break;
      default:
      break;
    }
    debug("mtg");
    String trame = "#$";      // Debut + separateur
    trame += ID_CAPT_GPS;     // ID du capteur
    trame += "$";             // Separateur
    trame += id_capt;         // ID de la valeur en cours d'envoi
    trame += "$";             // Separateur
    for (byte j = 0 ;  j < SIZE_VALUE - val_capt.length() ; j++) trame += "0"; // remplissage de la taille maximale de la valeur pour que la trame envoyée ait une longueur constante
    trame += val_capt;        // Valeur du capteur a envoyer
    trame += "$";             // Separateur
    trame += String(get_checksum(trame), HEX); // Checksum
    trame += "$@";            // Separateur + fin
    for (byte k = 0 ; k < NB_REPET ; k++) { // repetition et envoi de la trame
      Serial.print(trame);
      Serial.flush();
    }
    debug("ftg");
  }
}*/
