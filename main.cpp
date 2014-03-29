 #include <Wire.h>
 #include "trame.h"
 #include "gps.h"
 #include "defines.h"
 #include "accel.h"
 #include "humidity.h"
 #include "serial_out.h"
 #include "sd_out.h"
 #include "PWMServo.h"
 #include "capteur_analog.h"
 
 GPS gps = GPS(ID_CAPT_GPS);
 Accel accel = Accel(ID_CAPT_ACCEL);
 Hum hum = Hum(ID_CAPT_HUM);
 CapteurAnalog press = CapteurAnalog(ID_CAPT_PRESS, PIN_PRESS);
 CapteurAnalog pressext = CapteurAnalog(ID_CAPT_PRESSEXT, PIN_PRESSEXT);
 CapteurAnalog temp = CapteurAnalog(ID_CAPT_TEMP, PIN_TEMP);
 SerialOut so = SerialOut();
 SdOut sd = SdOut();
 CapteurAnalog pile (ID_CAPT_PILE, (byte)0);
 
 unsigned long int timer, timeralt;
 short int nb_trames = -1;
 bool refreshed = false, launched = false;
 byte check_alt = 0;
 PWMServo servo;
 
void setup() {
   pinMode((byte)10, OUTPUT);
   pinMode((byte)13, OUTPUT);
   pinMode((byte)PIN_SERVO, OUTPUT);
   pinMode ((byte)PIN_JACK, INPUT);
   digitalWrite((byte)PIN_JACK, HIGH);
   so.init();
   sd.init();
   press.init();
   pressext.init();
   gps.init();
   accel.init();
   hum.init();
   temp.init();
   accel.addOut(&so);
   press.addOut(&so);
   pressext.addOut(&so);
   temp.addOut(&so);
   hum.addOut(&so);
   gps.addOut(&so);
   pile.addOut(&so);
   accel.addOut(&sd);
   press.addOut(&sd);
   pressext.addOut(&sd);
   temp.addOut(&sd);
   hum.addOut(&sd);
   gps.addOut(&sd);
   pile.addOut(&sd);
   timer = millis();
   timeralt = millis();
   servo.attach((byte)PIN_SERVO);
   servo.write((byte)70);
   
}
           
void loop(){
   if ((digitalRead(PIN_JACK) == HIGH) && (nb_trames == -1)){
     nb_trames = 0;
   }
   
   if ( ((millis() - timer) >= (unsigned int)DELAY_SEND) && (refreshed) ){
     refreshed = false;
     gps.getTrame();
     accel.getTrame();
     hum.getTrame();
     press.getTrame();
     pressext.getTrame();
     temp.getTrame();
     pile.getTrame();

     timer = millis();
     if (nb_trames != -1) {
       nb_trames++;
     }
   } else if ( ((millis() - timer) >= (unsigned int)DELAY_REFRESH) && (!(refreshed)) ) {
     accel.refresh();
     hum.refresh();
     press.refresh();
     pressext.refresh();
     temp.refresh();
     pile.refresh();
     refreshed = true;
   } 
   if (Serial.available() > 0){
     gps.refresh();
   }
   
   if (((millis() - timeralt) >= (unsigned int)DELAY_CHECK_ALT) && (!(refreshed)) ){
     timeralt = millis();
     unsigned int altgps = atol(gps.getValue(ID_VAL_ALT));
     unsigned int altpress = atoi(press.getValue(0));

     if((altgps > (unsigned int)20000) || (altpress < 55)){
       check_alt++;
     } else {
       check_alt = 0;
     }
   }
   
   if (((check_alt > (byte)60) || (nb_trames > (int)NB_TRAMES_WATCHDOG)) && (!(launched))){
       check_alt = 0;
       servo.write((byte)40);
       launched = true;
       digitalWrite(13, HIGH);
   }
}

