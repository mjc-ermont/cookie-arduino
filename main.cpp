 #include <Wire.h>
 #include "trame.h"
 #include "gps.h"
 #include "ph.h"
 #include "defines.h"
 #include "serial_out.h"
 #include "sd_out.h"
 #include "capteur_analog.h"
 
 GPS gps = GPS(ID_CAPT_GPS);
 CapteurAnalog press = CapteurAnalog(ID_CAPT_PRESS, PIN_PRESS);
 CapteurAnalog pressext = CapteurAnalog(ID_CAPT_PRESSEXT, PIN_PRESSEXT);
 CapteurAnalog temp = CapteurAnalog(ID_CAPT_TEMP, PIN_TEMP);
 CapteurAnalog conduct = CapteurAnalog(ID_CAPT_CONDUCT, PIN_CONDUCT);
 CapteurAnalog chamallow = CapteurAnalog(ID_CAPT_CHAMALLOW, PIN_CHAMALLOW);
 CapteurAnalog co2 = CapteurAnalog(ID_CAPT_CO2, PIN_CO2);
 pH ph = pH(ID_CAPT_PH);
 SerialOut so = SerialOut();
 SdOut sd = SdOut();
 CapteurAnalog pile (ID_CAPT_PILE, PIN_PILE);
 unsigned long int timer;
 bool refreshed;
 
void setup() {
   pinMode((byte)10, OUTPUT);
   pinMode((byte)13, OUTPUT);
   so.init();
   sd.init();
   
   press.init();
   pressext.init();
   gps.init();
   temp.init();
   conduct.init();
   chamallow.init();
   ph.init();
   co2.init();
   
   press.addOut(&so);
   pressext.addOut(&so);
   temp.addOut(&so);
   gps.addOut(&so);
   pile.addOut(&so);
   conduct.addOut(&so);
   chamallow.addOut(&so);
   ph.addOut(&so);
   co2.addOut(&so);
   
   
   press.addOut(&sd);
   pressext.addOut(&sd);
   temp.addOut(&sd);
   gps.addOut(&sd);
   pile.addOut(&sd);
   conduct.addOut(&sd);
   chamallow.addOut(&sd);
   ph.addOut(&sd);
   co2.addOut(&sd);
   
}
           
void loop(){
   if ( ((millis() - timer) >= (unsigned int)DELAY_SEND) && (refreshed) ){
     refreshed = false;
     gps.getTrame();
     press.getTrame();
     pressext.getTrame();
     temp.getTrame();
     pile.getTrame();
     chamallow.getTrame();
     conduct.getTrame();
     ph.getTrame();
     co2.getTrame();

     timer = millis();
   } else if ( ((millis() - timer) >= (unsigned int)DELAY_REFRESH) && (!(refreshed)) ) {
     press.refresh();
     pressext.refresh();
     temp.refresh();
     pile.refresh();
     conduct.refresh();
     chamallow.refresh();
     co2.refresh();
     refreshed = true;
   } 
   if (Serial1.available() > 0){
     gps.refresh();
   }
   if (Serial2.available() > 0) {
     ph.refresh();
   }
}

