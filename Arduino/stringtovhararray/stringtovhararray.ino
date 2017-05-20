void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  char strarray[100];
  String str = "Hello";
  for(int i = 0;i < str.length();i++)
 {
  strarray[i] = str[i];
  Serial.println(strarray[i]);
 }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
