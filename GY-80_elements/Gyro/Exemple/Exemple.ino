#include <Wire.h>
#include <L3G.h>

L3G gyro;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();
}

void loop() {
  gyro.read();
  float X=(double)gyro.x*0.0175;
  Serial.print("G ");
  Serial.print((int)gyro.x);
  Serial.print(" X: ");
  Serial.print(X);
 /* Serial.print(" Y: ");
  Serial.print((int)gyro.y);
  Serial.print(" Z: ");
  Serial.println((int)gyro.z);*/
  Serial.print("\n");
  delay(100);
}
