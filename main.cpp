 #include <Wire.h>
 #include <SD.h>
 #include <Servo.h>
 #include "trame.h"
 #include "gps.h"
 #include "defines.h"
 #include "accel.h"
 #include "humidity.h"
 #include "pression.h"
 #include "temp.h"
 #include "serial_out.h"
 #include "sd_out.h"
 
 GPS gps = GPS(ID_CAPT_GPS);
 Accel accel = Accel(ID_CAPT_ACCEL);
 Hum hum = Hum(ID_CAPT_HUM);
 Press press = Press(ID_CAPT_PRESS, PIN_PRESS);
 Press pressext = Press(ID_CAPT_PRESSEXT, PIN_PRESSEXT);
 Temp temp = Temp(ID_CAPT_TEMP, PIN_TEMP);
 SerialOut so = SerialOut();
 SdOut sd = SdOut();
 CapteurAnalog pile (ID_CAPT_PILE, 0);
 
 unsigned long int timer, timeralt, timer_watchdog, delta_watchdog = 0;
 bool refreshed = false;
 
   byte check_alt = 0;
  Servo servo;
 
void setup() {
   pinMode(10, OUTPUT);
   pinMode(13, OUTPUT);
   pinMode(PIN_SERVO, OUTPUT);

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
   //Serial1.begin(GPS_BAUDRATE);
   timer = millis();
   timeralt = millis();
   servo.attach(PIN_SERVO);
   Serial.println(F("write"));
   servo.write(100);
   Serial.println(F("fin rite"));
}
           
void loop(){
   //debug("d");
   if ( ((millis() - timer) >= (unsigned long)DELAY_SEND) && (refreshed) ){
     refreshed = false;
     gps.getTrame();
     accel.getTrame();
     hum.getTrame();
     press.getTrame();
     pressext.getTrame();
     temp.getTrame();
     pile.getTrame();
     
     timer = millis();
   } else if ( ((millis() - timer) >= (unsigned long)DELAY_REFRESH) && (!(refreshed)) ) {
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
   if ( ((millis() - timeralt) >= (unsigned long)DELAY_CHECK_ALT) && (!(refreshed)) ){
     timeralt = millis();
     digitalWrite(13, HIGH);
     long unsigned int altgps = atol(gps.getValue(ID_VAL_ALT));
     int altpress = atoi(press.getValue(0));

     if((altgps > (unsigned long int)20000) || (altpress < 55)){
       check_alt++;
     } else {
       check_alt = 0;
     }
   }
   if ((check_alt > 60) || ((timer_watchdog - delta_watchdog) > (unsigned long)TIME_WATCHDOG )){
       check_alt = 0;
     servo.write(130);
     digitalWrite(13, HIGH);
   }
   
   //debug("f");
}

