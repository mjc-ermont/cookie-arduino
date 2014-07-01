#ifndef DEFINES_INCLUDED
#define DEFINES_INCLUDED

/*  ------- DEBUG -------  */

// Activation du mode debug

/*  ------- TRASMISSION -------  */

#define DELAY_SEND       1000
#define DELAY_REFRESH    800

#define SERIAL_BAUDRATE  57600 // baudrate de la liaison série avec le kiwi
#define NB_REPET         (byte)3    // Nombre de répéition de la trame
#define SIZE_VALUE       (byte)8    // Longueur maxi de la valeur dans la trame
#define ID_CAPT_GPS      (byte)0   // ID dans la trame du GPS
#define ID_CAPT_ACCEL    (byte)1    // ID dans la trame de l'accéléromètre
#define ID_CAPT_HUM      (byte)2    // ID dans la trame du capeur d'humidité
#define ID_CAPT_PRESS    (byte)3    // ID dans la trame du capeur de pression
#define ID_CAPT_TEMP     (byte)4    // ID dans la trame du capeur de temperature
#define ID_CAPT_PILE     (byte)5    // ID dans la trame du capeur de temperature
#define ID_CAPT_PRESSEXT (byte)6    // ID dans la trame du capeur de pression

// GPS
#define NB_VAL_GPS       (byte)5    // Nombre de valeurs du capteur GPS
#define ID_VAL_LAT_DEG   (byte)0    // No de la valeur "Degres latitude" dans la trame
#define ID_VAL_LON_DEG   (byte)1    // No de la valeur "Degres longitude" dans la trame
#define ID_VAL_VIT       (byte)2    // No de la valeur "Vitesse" dans la trame
#define ID_VAL_UTIME     (byte)3    // No de la valeur "temps UTC" dans la trame
#define ID_VAL_ALT       (byte)4    // No de la valeur "temps UTC" dans la trame


/*  ------- CAPTEUR HUMIDITE -------  */

#define HYT371_ADDR      0x28 // Adresse I2C Capteur Humidité

/*  ------- CAPTEUR PRESSION -------  */

#define PIN_PRESS        (byte)2
#define PIN_PRESSEXT     (byte)1

/*  ------- CAPTEUR TEMPERATURE -------  */

#define PIN_TEMP         (byte)3

/*  ------- CAPTEUR TEMPERATURE -------  */

#define SD_CS_PIN        (byte)8

#define DELAY_CHECK_ALT  1000

#define NB_TRAMES_WATCHDOG    337//4400000

#define PIN_SERVO        (byte)9

#define PIN_JACK         (byte)6

#endif
