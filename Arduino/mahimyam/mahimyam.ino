#define FONA_RX 11
#define FONA_TX 10
#define FONA_RST 4
#include <SoftwareSerial.h>
SoftwareSerial myserial = SoftwareSerial(FONA_TX, FONA_RX);
void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
    myserial.begin(115200);


}

void loop() {
  // put your main code here, to run repeatedly:

  myserial.write("AT+CMGF=1\r\n");
    delay(500);
    myserial.write("AT+CMGS=\"09008588025\"\r\n");
    delay(500);
    myserial.print("hello");
    myserial.write((char)44);
    delay(500);
   myserial.write((char)26);
    Serial.println("SMS Sent!");

}
