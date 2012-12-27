 #include <Wire.h>
 #include <SD.h>
 #include "trame.h"
 #include "gps.h"
 #include "defines.h"
 #include "accel.h"
 #include "humidity.h"
 #include "pression.h"
 #include "temp.h"
 #include "serial_out.h"
 #include "debug.h"
 
 GPS gps = GPS();
 Accel accel = Accel(ID_CAPT_ACCEL);
 Hum hum = Hum();
 Press press = Press(ID_CAPT_PRESS, PIN_PRESS);
 Temp temp = Temp(ID_CAPT_TEMP, PIN_TEMP);
 SerialOut so = SerialOut();;
 unsigned long timer;
 
  
void setup() {
#if SERIAL_DEBUG
   Serial.begin(SERIAL_BAUDRATE);
#endif
   press.init();
   gps.init();
   accel.init();
   hum.init();
   temp.init();
   accel.addOut(so);
   press.addOut(so);
   temp.addOut(so);
   Serial1.begin(GPS_BAUDRATE);
   timer = millis();
}
           
void loop(){
   debug("d");
   if ((millis() - timer) >= (unsigned long)DELAY_SEND){
     
     debug("dt");
     gps.getTrame();
     Serial.flush();
     accel.getTrame();
     Serial.flush();
     hum.getTrame();
     Serial.flush();
     press.getTrame();
     Serial.flush();
     temp.getTrame();
     Serial.flush();
     timer = millis();
     debug("ft");
   } else if ((millis() - timer) >= (unsigned long)DELAY_REFRESH) {
     debug("dr");
     accel.refresh();
     hum.refresh();
     press.refresh();
     temp.refresh();
     debug("fr");
   } else if (Serial1.available() > 0){
     debug("drg");
     gps.refresh();
     debug("frg");  
 }
   debug("f");
}

