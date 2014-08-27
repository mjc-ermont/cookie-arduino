#ifndef DEFINES_INCLUDED
#define DEFINES_INCLUDED

/*  ------- DEBUG -------  */

// Activation du mode debug

/*  ------- TRASMISSION -------  */

#define DELAY_SEND       1000
#define DELAY_REFRESH    800
#define SERIAL_BAUDRATE  600
#define SERIAL_BAUDRATE_GPS 9600 // baudrate de la liaison série avec le kiwi
#define SERIAL_BAUDRATE_PH 38400 // baudrate de la liaison série avec le kiwi


#define NB_REPET          (byte)1    // Nombre de répéition de la trame
#define SIZE_VALUE        (byte)8    // Longueur maxi de la valeur dans la trame
#define ID_CAPT_GPS       (byte)0   // ID dans la trame du GPS
#define ID_CAPT_PH        (byte)1    // ID dans la trame de l'accéléromètre
#define ID_CAPT_CHAMALLOW (byte)2    // ID dans la trame du capeur d'humidité
#define ID_CAPT_PRESS     (byte)3    // ID dans la trame du capeur de pression
#define ID_CAPT_TEMP      (byte)4    // ID dans la trame du capeur de temperature
#define ID_CAPT_PILE      (byte)5    // ID dans la trame du capeur de temperature
#define ID_CAPT_PRESSEXT  (byte)6    // ID dans la trame du capeur de pression
#define ID_CAPT_CONDUCT   (byte)7
#define ID_CAPT_CO2       (byte)8
#define ID_CAPT_TEMPEXT   (byte)9

// GPS
#define NB_VAL_GPS        (byte)4    // Nombre de valeurs du capteur GPS
#define ID_VAL_LAT_DEG    (byte)0    // No de la valeur "Degres latitude" dans la trame
#define ID_VAL_LON_DEG    (byte)1    // No de la valeur "Degres longitude" dans la trame
#define ID_VAL_VIT        (byte)2    // No de la valeur "Vitesse" dans la trame
#define ID_VAL_ALT        (byte)3    // No de la valeur "temps UTC" dans la trame


/*  ------- CAPTEUR HUMIDITE -------  */

#define HYT371_ADDR       0x28 // Adresse I2C Capteur Humidité

/*  ------- CAPTEUR PRESSION -------  */

#define PIN_PILE          (byte)0
#define PIN_PRESS         (byte)2
#define PIN_PRESSEXT      (byte)1
#define PIN_TEMP          (byte)3
#define PIN_CONDUCT       (byte)4
#define PIN_CHAMALLOW     (byte)5
#define PIN_CO2           (byte)6
#define PIN_TEMPEXT       (byte)7
/*  ------- CAPTEUR TEMPERATURE -------  */

#define SD_CS_PIN         (byte)53

#endif
