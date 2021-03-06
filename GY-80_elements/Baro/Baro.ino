#include "Wire.h"
#include "BMP085.h"
 
BMP085 bmp;
 
void setup() {
  Serial.begin(9600);
  bmp.begin();  
}
 
void loop() {
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
 
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
 
    Serial.println();
    delay(500);
}
