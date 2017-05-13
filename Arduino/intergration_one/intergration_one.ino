/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

File myFile;
void accelerometer();
void rtc_time();
void reed_speed();
int x,y,z;
int vib_pin=10;
int vib_data=0;
int reed_pin=2;
int f=0;

int speed_count;
int to_count_minute=0;






void setup() 
 {
        pinMode(vib_pin,INPUT);
        pinMode(reed_pin, INPUT);
      // Open serial communications and wait for port to open:
         Serial.begin(9600);
         while (!Serial) 
         {
         ; // wait for serial port to connect. Needed for native USB port only
         }


         Serial.print("Initializing SD card...");

         if (!SD.begin(4)) 
         {
               Serial.println("initialization failed!");
               return;
         }
         Serial.println("initialization done.");

         // open the file. note that only one file can be open at a time,
          // so you have to close this one before opening another.
         myFile = SD.open("log.txt", FILE_WRITE);

           // if the file opened okay, write to it:
         if (myFile) 
         {
          Serial.print("file is now open");
          Serial.println("done.");
         } 
         else 
         {
                // if the file didn't open, print an error:
                Serial.println("error opening test.txt");
         }

//  // re-open the file for reading:
//  myFile = SD.open("mahimyam.txt");
//  if (myFile) {
//    Serial.println("mahimyam.txt:");
//
//    // read from the file until there's nothing else in it:
//    while (myFile.available()) {
//      Serial.write(myFile.read());
//    }
//    // close the file:
//    myFile.close();
//  } else {
//    // if the file didn't open, print an error:
//    Serial.println("error opening test.txt");
//  }
}














void accelerometer(){
 
  x= analogRead(A5);
  y=analogRead(A4);
  z=analogRead(A3);
  x=map(x,0,1023,0,255);
  y=map(x,0,1023,0,255);
  z=map(x,0,1023,0,255);
  myFile = SD.open("log.txt", FILE_WRITE);
  myFile.println("the accelerometer values in x y z co ordinates are");
   myFile.println(x);
   myFile.println(y);
   myFile.println(z);
   myFile.close();
//  
//    if(oldx-x>1 || oldy-y>1)
//     {  
//      Serial.println(oldx-x);
//      Serial.println("collison detected");
//     }
//    oldx=x;
//    oldy=y;
//    oldz=z;
//    
    
}
void rtc_time()
{
  tmElements_t tm;
  Serial.print("reading time");
  if (RTC.read(tm)) {
    myFile = SD.open("log.txt", FILE_WRITE);
    myFile.println("Ok, Time = ");
   int a=tm.Hour;
    myFile.print(a);
    myFile.print(":");
    myFile.print(tm.Minute);
    myFile.print(":");
    myFile.print(tm.Second);
    myFile.print(", Date (D/M/Y) = ");
    myFile.print(tm.Day);
    myFile.print("/");
    myFile.print(tm.Month);
    myFile.print("/");
    myFile.print(tmYearToCalendar(tm.Year));
    myFile.println("");
    myFile.close();
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}

void reed_speed()
{
  to_count_minute=0;
 speed_count=0;
    
    while(to_count_minute<=1)
    {
      f= analogRead(A0);
      if(f==1023)
      {
        Serial.println("switch closed");
        speed_count++;
      }
    delay(1000);
    to_count_minute++;
    if(to_count_minute==1)
    {
     myFile = SD.open("log.txt", FILE_WRITE);
     myFile.println("the speed calculated is");
     myFile.print(speed_count);
     myFile.println("rps");
     myFile.println(""); 
     myFile.close();
    
    }
}
}

void loop()
{
  rtc_time();
accelerometer();
reed_speed();
  
   
  vib_data= digitalRead(vib_pin);
  if(vib_data==1)
  {
    Serial.println("collison detedcted");
    
  }
  delay(1000);
  
  
  
  
}

