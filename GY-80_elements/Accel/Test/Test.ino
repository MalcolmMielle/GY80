#include <ADXL345.h>
#include <Wire.h>

ADXL345 acc;

void setup(){
  Serial.begin(115200);
  Wire.begin();

  if (!acc.init())
  {
    Serial.println("Failed to autodetect accel type!");
    while (1);
  }
  acc.setSensitivity(8); //Voir dans le init de la cslasse ADXL
}

void loop(){
  acc.read();
  Serial.print("Acc ");
  Serial.print("X: ");
  Serial.print((float)acc.x/256);
  Serial.print(" Y: ");
  Serial.print((int)acc.y);
  Serial.print(" Z: ");
  Serial.println((float)acc.z);
  
  
}
