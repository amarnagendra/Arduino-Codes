#define dig_pin 10
void setup() {
  // put your setup code here, to run once:
  pinMode(dig_pin,INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  boolean s;
  s=digitalRead(dig_pin);
  
  Serial.println(s);
  delay(1000);
  

}
