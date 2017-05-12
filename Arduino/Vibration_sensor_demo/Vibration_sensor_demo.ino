int a=5;
int f=0;
int led=13;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(a,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 f= digitalRead(a);
  if(f>0)
  {
    digitalWrite(led,LOW);
    Serial.println("detected");
  }
  
}
