
int value_ldr=0;


void setup() {
  
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

    
   
      value_ldr= analogRead(A1);
      
    value_ldr =map (value_ldr,0,1023,0,255);
    
    if(value_ldr > 220)
    { 
      Serial.println("ldr value"); 
      Serial.println(value_ldr);
    }
    else
    {
      Serial.println("not");
    }
    
    
    }
   
