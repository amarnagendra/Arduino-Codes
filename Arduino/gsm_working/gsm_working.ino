#include "Adafruit_FONA.h"

  
  #include <SoftwareSerial.h>
  int i=1;
  SoftwareSerial fonaSS(11, 10); // RX, TX
  SoftwareSerial *fonaSerial = &fonaSS;
  SoftwareSerial mySerial(11,10);
  int  onceonly =1;

Adafruit_FONA fona = Adafruit_FONA(0);
  
  void setup()  
  {
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    fonaSS.begin(9600);
    mySerial.begin(9600);
  
  }
  
  void loop()
  {
//    if (mySerial.available())
//      Serial.write(mySerial.read());
//      
//    if (Serial.available())
//    { 
//      while(Serial.available())
//      {
//        mySerial.write(Serial.read());
//      }
//      mySerial.println();
//    }
 
  float latitude, longitude, speed_kph, heading, speed_mph, altitude;

  // if you ask for an altitude reading, getGPS will return false if there isn't a 3D fix
  boolean gps_success = fona.getGPS(&latitude, &longitude, &speed_kph, &heading, &altitude);

  if (gps_success) {

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

    
    if(onceonly==1)
    {
    
    fonaSS.write("AT+CMGF=1\r\n");
    delay(500);
    fonaSS.write("AT+CMGS=\"09739105068\"\r\n");
    delay(500);
    fonaSS.print(latitude);
    fonaSS.write((char)44);
    fonaSS.print(longitude);
    delay(500);
    fonaSS.print((char)26);
    Serial.println("SMS Sent!");
    onceonly++;
    }

  } 
  else {
    Serial.println("Waiting for FONA GPS 3D fix...");
  

  // Fona 3G doesnt have GPRSlocation :/
  if ((fona.type() == FONA3G_A) || (fona.type() == FONA3G_E))
    return;
  // Check for network, then GPRS 
  Serial.println(F("Checking for Cell network..."));
  if (fona.getNetworkStatus() == 1) {
    // network & GPRS? Great! Print out the GSM location to compare
    boolean gsmloc_success = fona.getGSMLoc(&latitude, &longitude);

    if (gsmloc_success) {
      Serial.print("GSMLoc lat:");
      Serial.println(latitude, 6);
      Serial.print("GSMLoc long:");
      Serial.println(longitude, 6);
      if(onceonly==1)
      {
       fonaSS.write("AT+CMGF=1\r\n");
    delay(500);
    fonaSS.write("AT+CMGS=\"09739105068\"\r\n");
    delay(500);
    fonaSS.print(latitude);
    fonaSS.write((char)44);
    fonaSS.print(longitude);
    delay(500);
    fonaSS.write((char)26);
    Serial.println("SMS Sent!");
    onceonly++;
      }
    } else {
      Serial.println("GSM location failed...");
      Serial.println(F("Disabling GPRS"));
      fona.enableGPRS(false);
      Serial.println(F("Enabling GPRS"));
      if (!fona.enableGPRS(true)) {
        Serial.println(F("Failed to turn GPRS on"));  
      }
    }
  }
  }

  
  
    
    
   
  
  }
  
 



