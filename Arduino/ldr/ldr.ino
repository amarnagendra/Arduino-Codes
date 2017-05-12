
int f=0;
int led=13;
int count;
int to_count_minute=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

 to_count_minute=0;
 count=0;
    
    while(to_count_minute<=10)
    {
      f= analogRead(A0);
      if(f==1023)
      {
        count++;
      }
    delay(1000);
    to_count_minute++;
    if(to_count_minute==10)
    {
      
    Serial.println(count);
    
    }
    
    }
    
    
  
  
  
}
