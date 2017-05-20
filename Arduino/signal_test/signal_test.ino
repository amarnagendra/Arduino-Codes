#define pin 8
#define vib_pin 6
void setup() {
  // put your setup code here, to run once:
  pinMode(pin,OUTPUT);
  pinMode(pin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  while (digitalRead(vib_pin)==HIGH)
  {
    Serial.println("pin 8 made low");
    digitalWrite(pin,LOW);
  }
  while (digitalRead(vib_pin)==LOW)
  
  {
    Serial.println("pin 8 made high");
    digitalWrite(pin,HIGH);
  }
  
  // put your main code here, to run repeatedly:

}
