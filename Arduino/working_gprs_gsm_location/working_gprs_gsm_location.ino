/**
 *  ___ ___  _  _   _     ___  __  ___    ___ ___  ___
 * | __/ _ \| \| | /_\   ( _ )/  \( _ )  / __| _ \/ __|
 * | _| (_) | .` |/ _ \  / _ \ () / _ \ | (_ |  _/\__ \
 * |_| \___/|_|\_/_/ \_\ \___/\__/\___/  \___|_|  |___/
 *
 * This example is meant to work with the Adafruit
 * FONA 808 or 3G Shield or Breakout
 *
 * Copyright: 2015 Adafruit
 * Author: Todd Treece
 * Licence: MIT
 *
 */
#include "Adafruit_FONA.h"

// standard pins for the shield, adjust as necessary
#define FONA_RX 8
#define FONA_TX 9
#define FONA_RST 0
int onlyonce =1;
#define triggerpin 6
int detected;
// We default to using software serial. If you want to use hardware serial
// (because softserial isnt supported) comment out the following three lines 
// and uncomment the HardwareSerial line
#include <SoftwareSerial.h>
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

// Hardware serial is also possible!
//  HardwareSerial *fonaSerial = &Serial1;

Adafruit_FONA fona = Adafruit_FONA(FONA_RST);

// Have a FONA 3G? use this object type instead
//Adafruit_FONA_3G fona = Adafruit_FONA_3G(FONA_RST);


void setup() {
   
  while (! Serial);

  Serial.begin(115200);
  Serial.println(F("Adafruit FONA 808 & 3G GPS demo"));
  Serial.println(F("Initializing FONA... (May take a few seconds)"));

  fonaSerial->begin(4800);
  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while(1);
  }
  Serial.println(F("FONA is OK"));
  // Try to enable GPRS
  

  Serial.println(F("Enabling GPS..."));
  fona.enableGPS(true);
  fona.enableGPRS(true);
//attachInterrupt(digitalPinToInterrupt(triggerpin),sendloc,LOW);
//detected=0;
}

void loop() 
{
  
 if(digitalRead(triggerpin)== HIGH)
  {
 
  Serial.println("detected");
  float latitude, longitude, speed_kph, heading, speed_mph, altitude;
  
  // if you ask for an altitude reading, getGPS will return false if there isn't a 3D fix
  boolean gps_success = fona.getGPS(&latitude, &longitude, &speed_kph, &heading, &altitude);
  boolean gsmloc_success = fona.getGSMLoc(&latitude, &longitude);
  if (gps_success) 
  {
    Serial.print("GPS lat:");
    Serial.println(latitude, 6);
    Serial.print("GPS long:");
    Serial.println(longitude, 6);
    Serial.print("GPS speed KPH:");
    Serial.println(speed_kph);
    Serial.print("GPS speed MPH:");
    speed_mph = speed_kph * 0.621371192;
    Serial.println(speed_mph);
    Serial.print("GPS heading:");
    Serial.println(heading);
    Serial.print("GPS altitude:");
    Serial.println(altitude);
    if(onlyonce==1)
    {
      String one1 = String(latitude,6);
      String two1 = String(longitude,6);
      fonaSS.write("AT+CMGF=1\r\n");
      delay(500);
      fonaSS.write("AT+CMGS=\"9620588166\"\r\n");
      delay(500);
      fonaSS.println(one1);
      fonaSS.write((char)44);
      fonaSS.println(two1);
      delay(500);
      fonaSS.write((char)26);
      Serial.println("SMS Sent!");
      onlyonce++;
    }
  } 
 else if (gsmloc_success)
 {
    Serial.println("Waiting for FONA GPS 3D fix...");
//
//                                                                                                          // Fona 3G doesnt have GPRSlocation :/
//                                                                                                          if ((fona.type() == FONA3G_A) || (fona.type() == FONA3G_E))
//                                                                                                          return;
//                                                                                                           // Check for network, then GPRS 
//                                                                                                          Serial.println(F("Checking for Cell network..."));
//                                                                                                           if (fona.getNetworkStatus() == 1) {
//                                                                                                          // network & GPRS? Great! Print out the GSM location to co
      Serial.print("GSMLoc lat:");
      Serial.println(latitude, 6);
      Serial.print("GSMLoc long:");
      Serial.println(longitude, 6);
      String one = String(latitude,6);
      String two = String(longitude,6);
      if(onlyonce==1)
      {
        fonaSS.write("AT+CMGF=1\r\n");
        delay(500);
        fonaSS.write("AT+CMGS=\"9620588166\"\r\n");
        delay(500);
        fonaSS.println(one);
        fonaSS.write((char)44);
        fonaSS.print(two);
        delay(500);
        fonaSS.write((char)26);
        Serial.println("SMS Sent!");
        onlyonce++;
       }
    } 

}
}



  





