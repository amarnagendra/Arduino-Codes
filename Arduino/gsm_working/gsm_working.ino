
  
  #include <SoftwareSerial.h>
  int i=1;
  SoftwareSerial mySerial(10, 11); // RX, TX
  
  void setup()  
  {
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    mySerial.begin(9600);
  
  }
  
  void loop()
  {
  //  if (mySerial.available())
  //    Serial.write(mySerial.read());
  //    
  //  if (Serial.available())
  //  { 
  //    while(Serial.available())
  //    {
  //      mySerial.write(Serial.read());
  //    }
  //    mySerial.println();
  //  }
  if(i==1)
  {
    mySerial.write("AT+CMGF=1\r\n");
    delay(500);
    mySerial.write("AT+CMGS=\"09739105068\"\r\n");
    delay(500);
    mySerial.write("hello");
    delay(500);
    mySerial.write((char)26);
    Serial.println("SMS Sent!");
    i++;
  }
  
  }
