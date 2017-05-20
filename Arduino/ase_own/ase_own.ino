#include <AESLib.h>
void setup()
{
  int a= 12345;
  String a_s= String(a);
  Serial.println(a);
  Serial.begin(9600);
 encrypt("abcdefghijklmn"); 
 encrypt(a_s);
}
void loop()
{
  
}
void encrypt(String s)
  {
   uint8_t key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
   char strarray[16];
   
   for(int i=0;i<s.length();i++)
   {
    strarray[i] = s[i];
   }
   Serial.println(strarray);
   
   if((s.length())<16)
   {
    for(int k=(s.length());k<16;k++)
    {
      strarray[k]='*';
    }
   }
   Serial.println(strarray);
   
    aes128_enc_single(key,strarray);
    Serial.print("encrypted:");
    
  String str(strarray);
   Serial.println(str);
   
//    if(newline ==1)
//    {
//
//    myFile = SD.open("log.txt", FILE_WRITE);
//    myFile.println(str);
//    myFile.close();
//   
//    }
//    else
//    {
//       myFile = SD.open("log.txt", FILE_WRITE);
//       myFile.println(str);
//       myFile.close();
//    }

  }
