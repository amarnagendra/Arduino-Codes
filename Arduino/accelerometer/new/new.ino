int x;
int y;int  z;
int oldx;
int oldy;
int oldz;

void setup() {
  // put your setup code here, to run once:

Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  x= analogRead(A5);
  y=analogRead(A4);
  z=analogRead(A3);
  x=map(x,0,1023,0,255);
  y=map(x,0,1023,0,255);
  z=map(x,0,1023,0,255);
Serial.println(x);
  Serial.print(y);
  Serial.print(z);
  Serial.println();
  delay(1000);
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
    
}
