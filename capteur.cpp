#include <Arduino.h>
#include "capteur.h"
#include "defines.h"
#include "trame.h"
#include "rs.h"
#include <mem.h>

Capteur::Capteur(const byte &id_capt, const byte &nb_val) : _id_capt(id_capt), _nb_val(nb_val) {
  _val = (char**) malloc(nb_val*sizeof(char*));
  for (byte i = 0 ; i < _nb_val ; i++){
    _val[i] = (char*)malloc(SIZE_VALUE + 1);
  }
  _rs = init_rs_char(8, 285, 1, 1, 20);
}

void Capteur::addOut(Out *out){
  _out.push_back(out);  // Ajout de la sortie au tableau des sorties
  _nb_out++;
}

void Capteur::getTrame(){
  char *trame = (char*)calloc(255, 1);          // Trame qui sera envoyee
  char ecc[20] = {'\0'};
  for (byte i = 0 ; i < _nb_val ; i++){
    char buffer[10];
    char *sep = "$";
    strcpy(trame, "#");
    strcat(trame, sep);
    if (_id_capt < 10){                         // Pour toujours garder une taille constante
      strcat(trame, "0");
    }
    itoa(_id_capt, buffer, 10);
    strcat(trame, buffer);                          // Ajout de l'ID du capteur
    strcat(trame, sep);                              // separaeur
    itoa(i, buffer, 10);
    strcat(trame, buffer);                                // No de la valeur
    strcat(trame, sep);                               // separateur
    for (byte j = 0 ;  j < ((byte)SIZE_VALUE) - ((byte)strlen(_val[i])) ; j++) {strcat(trame, "0");} // remplissage de la taille maximale de la valeur pour que la trame envoyée ait une longueur constante
    strcat(trame, _val[i]);// Ajout de la valeur
    strcat(trame, sep);    // separaeur
    itoa(get_checksum(trame), buffer, 16);
    strcat(trame, buffer);  // Ajout du checksum
    strcat(trame, sep);
    encode_rs_char(_rs, (unsigned char*)trame, (unsigned char*)ecc);
    trame[10] = 'u'; 
    memcpy(&trame[19], ecc, 20);
    strcat(trame, sep);
    strcat(trame, "@");                             // separaeur + fin

    
    for (byte j = 0 ; j < _nb_out ; j++){   // envoi de la trame a toutes les sorties (d'ou le for)
      _out[j]->writeQueue(trame);                    // écriture sur la sortie de la file d'envoi 
    }
  }
  free(trame);
}

char* Capteur::getValue(int i){
  if (i > _nb_val){
    return NULL;
  } else {
    return _val[i];
  }
}

Capteur::~Capteur(){
  for (byte i = 0 ; i < _nb_val ; i++){
    free(_val[i]);
  }
  free(_val);
}
