#include <SoftwareSerial.h>
 
SoftwareSerial rfid(16, 17);
unsigned char pesan[64];

void setup()
{
  rfid.begin(9600);
  Serial.begin(9600);
}
char c;
void loop()
{
  while(rfid.available())
    {
      pesan[c++]=rfid.read();
      if(c == 64)break;
    }
    Serial.write(pesan,c);
    clearPesanC();
    c = 0;
}

void clearPesanC()
{
  for (int i=0; i<c;i++)
    {pesan[i]=NULL;}
}
