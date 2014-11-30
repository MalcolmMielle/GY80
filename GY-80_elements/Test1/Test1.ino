
#include <Wire.h>

int reading = 0;
byte Buf[12];
void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  Wire.beginTransmission(0x68);
  Wire.requestFrom(0x53, 12);//demande 6 bits depuis l'adresse 0x1E
  int i=0;
  if(Wire.available()>=12)
  {
    reading=Wire.read();
    Serial.println(reading);
  }
  Wire.endTransmission();
  
  delay(250);


}
