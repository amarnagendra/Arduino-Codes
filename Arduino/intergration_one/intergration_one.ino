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


#include <dht.h>


// standard pins for the shield, adjust as necessary






File myFile;
dht DHT;
void accelerometer();
void rtc_time();
void reed_speed();
void ldr();
void reedswitch();
void temperature();

#define vib_pin 6

#define reed_pin 2
#define DHT11_PIN 7





#define trigPin 2
#define echoPin 3


int collison_var=1;





void setup() 
 {
        pinMode(vib_pin,INPUT);
        pinMode(reed_pin, INPUT);
        pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
        pinMode(echoPin, INPUT); // Sets the echoPin as an Input
        
        
        
  
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
 int x,y,z;
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
    myFile.println(" ");
    
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
  
}

//void reed_speed()
//{
//  to_count_minute=0;
// speed_count=0;
//    
//    while(to_count_minute<=1)
//    {
//      f= analogRead(A0);
//      if(f==1023)
//      {
//        Serial.println("switch closed");
//        speed_count++;
//      }
//    delay(1000);
//    to_count_minute++;
//    if(to_count_minute==1)
//    {
//     myFile = SD.open("log.txt", FILE_WRITE);
//     myFile.println("the speed calculated is");
//     myFile.print(speed_count);
//     myFile.println("rps");
//     myFile.println(""); 
//     myFile.close();
//    
//    }
//}
//}


void ldr()
{
  int value_ldr=0;
    value_ldr= analogRead(A1);
      
    value_ldr =map (value_ldr,0,1023,0,255);
    Serial.println("reading ldr");
    if(value_ldr > 220)
    { 
      
      myFile = SD.open("log.txt", FILE_WRITE);
      myFile.println("ldr value"); 
      myFile.println(value_ldr);
      myFile.close();
    } 
    else
    {
       myFile = SD.open("log.txt", FILE_WRITE);
       myFile.println("ldr value is less than 220");
       myFile.close();
    }
}




void reedswitch()
{
 int speed_count;
int to_count_minute=0;
int f;
    
    while(to_count_minute<=1)
    {
      f= analogRead(A0);
      if(f==1023)
      {
//        Serial.println("switch closed");
        speed_count++;
      }
    delay(1000);
    to_count_minute++;
    if(to_count_minute==1)
    {
      Serial.println("reading speed");
      myFile = SD.open("log.txt", FILE_WRITE);
     myFile.println("speed in rpm"); 
    myFile.println(speed_count*60);
    myFile.close();
    
    }
    
    }
     
}




void temperature()
{
  int chk = DHT.read11(DHT11_PIN);
  Serial.write("reading temp");
  myFile = SD.open("log.txt", FILE_WRITE);
  myFile.print("Temperature = ");
  myFile.println(DHT.temperature);
  
  myFile.println(" ");
  myFile.close();
  
}



int distance_fun()
{
  long duration;
int distance;
  digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
// Calculating the distance
  distance= duration*0.034/2;
// Prints the distance on the Serial Monitor

  Serial.println("reading distance_fun");
  return distance;
}

void loop()
{
  
  
  int dis =  distance_fun();
  int vib_data= digitalRead(vib_pin);
  if(vib_data==HIGH && dis < 5)
  {
    Serial.println("collison detedcted");
    
    collison_var++;
  }
  else if(collison_var == 1)
  {
    
    rtc_time();
    accelerometer();
    reedswitch();
    ldr();
    temperature();
    myFile = SD.open("log.txt", FILE_WRITE);
    myFile.print("Distance = ");
    myFile.print(dis);
    myFile.close();
  
 }
}
  
  
  
  
  


