int a=10;
int f=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(a,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 f= digitalRead(a);
 int i=0;
  if(f==1)
  {
    
    Serial.println("detected");
    i++;
    Serial.println(i);
  }
  
}
