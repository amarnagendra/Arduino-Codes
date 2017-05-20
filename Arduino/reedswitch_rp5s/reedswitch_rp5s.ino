int reed_pin=2;
int f=0;

int speed_count;
int to_count_minute=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

pinMode(reed_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 to_count_minute=0;
 speed_count=0;
    
    while(to_count_minute<=10)
    {
      f= digitalRead(A0);
      if(f==1023)
      {
//        Serial.println("switch closed");
        speed_count++;
      }
    delay(1000);
    to_count_minute++;
    if(to_count_minute==10)
    {
      
    Serial.println(speed_count*6);
    
    }
    
    }
    
    
  
  
  
}
