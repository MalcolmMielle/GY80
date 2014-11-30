void affiche(){
  /* Print Data */
    Serial.print("\n");
 
  Serial.print(accXangle);Serial.print(";");
  Serial.print(accYangle);Serial.print(";");
  Serial.print(0);Serial.print(";");
  
  Serial.print(gyroXangle);Serial.print(";");
  Serial.print(gyroYangle);Serial.print(";");
  Serial.print(gyroZangle);Serial.print(";");
  
  //Roll
  
  
  Serial.print(kalAngleX);Serial.print(";");
  Serial.print(kalAngleY);Serial.print(";");
  Serial.print(gyroZangle);Serial.print(";");
  //Serial.print("\t\t");
  
  Serial.print(compAngleX);Serial.print(";");
  Serial.print(compAngleY); Serial.print(";");
  Serial.print(gyroZangle);Serial.print(";");
  //Pitch
  
  //Magneto et temp et pression
  Serial.print(compass.getHead());Serial.print(";");
  Serial.print(bmp.readTemperature());Serial.print(";");
  Serial.print(bmp.readPressure());Serial.print(";");
  
  
  Serial.print('e');
}
