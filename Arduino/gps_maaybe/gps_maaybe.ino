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
// C program for implementation of ftoa()
#include<stdio.h>
#include<math.h>
#include <string.h> 

// standard pins for the shield, adjust as necessary
#define FONA_RX 11
#define FONA_TX 10
#define pin 4
boolean gsmloc_success;

// We default to using software serial. If you want to use hardware serial
// (because softserial isnt supported) comment out the following three lines 
// and uncomment the HardwareSerial line
#include <SoftwareSerial.h>
SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
SoftwareSerial *fonaSerial = &fonaSS;

// Hardware serial is also possible!
//  HardwareSerial *fonaSerial = &Serial1;

Adafruit_FONA fona = Adafruit_FONA(0);

// Have a FONA 3G? use this object type instead
//Adafruit_FONA_3G fona = Adafruit_FONA_3G(FONA_RST);
char res[20];
char hel[5];
int shata=1;

void setup() {
  pinMode(pin,INPUT);

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
}

void loop() {
  delay(2000);

  float latitude, longitude, speed_kph, heading, speed_mph, altitude;

  // if you ask for an altitude reading, getGPS will return false if there isn't a 3D fix
 // boolean gps_success = fona.getGPS(&latitude, &longitude, &speed_kph, &heading, &altitude);

//  if (gps_success && shata==1) {
//
//    Serial.print("GPS lat:");
//    Serial.println(latitude, 6);
//    Serial.print("GPS long:");
//    Serial.println(longitude, 6);
//    Serial.print("GPS speed KPH:");
//    Serial.println(speed_kph);
//    Serial.print("GPS speed MPH:");
//    speed_mph = speed_kph * 0.621371192;
//    Serial.println(speed_mph);
//    Serial.print("GPS heading:");
//    Serial.println(heading);
//    Serial.print("GPS altitude:");
//    Serial.println(altitude);
////    ftoa (latitude,res,6);
////    ftoa (longitude,hel,6);
//  String stringOne =  String(latitude, 6); 
//  String stringTwo =  String(longitude, 6); 



//if (!gps_success)

  Serial.println("Waiting for FONA GPS 3D fix...");
  

  // Fona 3G doesnt have GPRSlocation :/
  if ((fona.type() == FONA3G_A) || (fona.type() == FONA3G_E))
    return;
  // Check for network, then GPRS 
  Serial.println(F("Checking for Cell network..."));
  if (fona.getNetworkStatus() == 1) {
    // network & GPRS? Great! Print out the GSM location to compare
    gsmloc_success = fona.getGSMLoc(&latitude, &longitude);
  }

    if (gsmloc_success) 
    {
      
      Serial.print("GSMLoc lat:");
      Serial.println(latitude, 6);
      Serial.print("GSMLoc long:");
      Serial.println(longitude, 6);
      String stringOne =  String(latitude, 6); 
      String stringTwo =  String(longitude, 6);

       if(shata==1)
  {
      fonaSS.write("AT+CMGF=1\r\n");
    delay(500);
    fonaSS.write("AT+CMGS=\"09620588166\"\r\n");
    delay(500);
//    fonaSS.write("lat:");
    fonaSS.print(stringOne);
    fonaSS.write((char)44);
//    fonaSS.write("lon:");
   fonaSS.print(stringTwo);
    
    delay(500);
    fonaSS.write((char)26);
    Serial.println("SMS Sent!");
    shata++;
  }

    
    }
    else {
      Serial.println("GSM location failed...");
      Serial.println(F("Disabling GPRS"));
      fona.enableGPRS(false);
      Serial.println(F("Enabling GPRS"));
      if (!fona.enableGPRS(true)) {
        Serial.println(F("Failed to turn GPRS on"));  

//  if(digitalRead(pin)==HIGH)
//if(gsmloc_success)
//  {
//      fonaSS.write("AT+CMGF=1\r\n");
//    delay(500);
//    fonaSS.write("AT+CMGS=\"09620588166\"\r\n");
//    delay(500);
////    fonaSS.write("lat:");
//    fonaSS.print(stringOne);
//    fonaSS.write((char)44);
////    fonaSS.write("lon:");
//   fonaSS.print(stringTwo);
//    
//    delay(500);
//    fonaSS.write((char)26);
//    Serial.println("SMS Sent!");
//    shata++;
  //}
  }
}
}
  

    

//  } else {
//    Serial.println("Waiting for FONA GPS 3D fix...");
//  }
//
//  // Fona 3G doesnt have GPRSlocation :/
//  if ((fona.type() == FONA3G_A) || (fona.type() == FONA3G_E))
//    return;
//  // Check for network, then GPRS 
//  Serial.println(F("Checking for Cell network..."));
//  if (fona.getNetworkStatus() == 1) {
//    // network & GPRS? Great! Print out the GSM location to compare
//    boolean gsmloc_success = fona.getGSMLoc(&latitude, &longitude);
//
//    if (gsmloc_success) {
//      Serial.print("GSMLoc lat:");
//      Serial.println(latitude, 6);
//      Serial.print("GSMLoc long:");
//      Serial.println(longitude, 6);
//    } else {
//      Serial.println("GSM location failed...");
//      Serial.println(F("Disabling GPRS"));
//      fona.enableGPRS(false);
//      Serial.println(F("Enabling GPRS"));
//      if (!fona.enableGPRS(true)) {
//        Serial.println(F("Failed to turn GPRS on"));  
//      }
//    }
//  }
void ftoa(float n, char *res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
 
    // Extract floating part
    float fpart = n - (float)ipart;
 
    // convert integer part to string
    int i = intToStr(ipart, res, 0);
 
    // check for display option after point
    if (afterpoint != 0)
    {
        res[i] = '.';  // add dot
 
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter is needed
        // to handle cases like 233.007
        fpart = fpart * pow(10, afterpoint);
 
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x)
    {
        str[i++] = (x%10) + '0';
        x = x/10;
    }
 
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
 
    reverse(str, i);
    str[i] = '\0';
    return i;
}
void reverse(char *str, int len)
{
    int i=0, j=len-1, temp;
    while (i<j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++; j--;
    }
}
 
