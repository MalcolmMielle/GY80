/* Copyright (C) 2012 Kristian Lauszus, TKJ Electronics. All rights reserved.
 
 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").
 
 */

#include <Wire.h>
#include <L3G.h>
#include <Kalman.h>
#include <ADXL345.h>
// Source: https://github.com/TKJElectronics/KalmanFilter

Kalman kalmanX; // Create the Kalman instances
Kalman kalmanY;

double accXangle, accYangle, accZangle; // Angle calculate using the accelerometer
double temp; // Temperature
double gyroXangle, gyroYangle, gyroZangle; // Angle calculate using the gyro
double compAngleX, compAngleY, compAngleZ; // Calculate the angle using a complementary filter
double kalAngleX, kalAngleY, kalAngleZ; // Calculate the angle using a Kalman filter

uint32_t timer;
uint8_t i2cData[14]; // Buffer for I2C data

/******Declaration des capteurs**********/
L3G gyro;
ADXL345 accel(8,3300);

/*******Fonction de changement*********/
#define TO_RAD(x) (x * 0.01745329252)  // *pi/180
#define TO_DEG(x) (x * 57.2957795131)  // *180/pi

void setup() {  
  Serial.begin(115200);
  I2C_Init();
  Accel_Init();
  Gyro_Init();
  
  delay(100); // Wait for sensor to stabilize
  
  /*Mise en place de Kalman*/
  Read_Accel();
  //accZangle=(atan2(accel.y,accel.z)+PI)*RAD_TO_DEG;
  kalmanX.setAngle(accXangle);
  kalmanY.setAngle(accYangle);
  //kalmanZ.setAngle(accZangle);
  gyroXangle=accXangle;
  gyroYangle=accYangle;
  compAngleX=accXangle;
  compAngleY=accYangle;
  
  timer=micros();
}

void loop() {
  /* Update all the values */  
  Read_Accel();
  gyro.read();
  double gyroXrate = (double)gyro.x/256.0; //131.0
  double gyroYrate = -((double)gyro.y/256.0);
  //gyroXangle += gyroXrate*((double)(micros()-timer)/1000000); // Calculate gyro angle without any filter  
  //gyroYangle += gyroYrate*((double)(micros()-timer)/1000000);
  gyroXangle += kalmanX.getRate()*((double)(micros()-timer)/1000000); // Calculate gyro angle using the unbiased rate
  gyroYangle += kalmanY.getRate()*((double)(micros()-timer)/1000000);
  
  compAngleX = (0.93*(compAngleX+(gyroXrate*(double)(micros()-timer)/1000000)))+(0.07*accXangle); // Calculate the angle using a Complimentary filter
  compAngleY = (0.93*(compAngleY+(gyroYrate*(double)(micros()-timer)/1000000)))+(0.07*accYangle);
  
  kalAngleX = kalmanX.getAngle(accXangle, gyroXrate, (double)(micros()-timer)/1000000); // Calculate the angle using a Kalman filter
  kalAngleY = kalmanY.getAngle(accYangle, gyroYrate, (double)(micros()-timer)/1000000);
  timer = micros();
  
  /* Print Data */
  
  //Serial.print(accX);Serial.print(" ");
  //Serial.print(accY);Serial.print(" ");
  //Serial.print(accZ);Serial.print(" ");
  
  Serial.print((int)gyro.x/1000);Serial.print(";");
  Serial.print((int)gyro.y/1000); Serial.print(";");
  Serial.print((int)gyro.z/1000);Serial.print(";");
  
  //Serial.print(accXangle);Serial.print(";");
  //Serial.print(gyroXangle);Serial.print("\t");
  //Roll
  //Serial.print(compAngleX);Serial.print(";");
  //Serial.print(kalAngleX);Serial.print(";");
  //Serial.print(0);Serial.print(";");
  //Serial.print("\t\t");
  
  //Serial.print(accYangle);Serial.print(";");
  //Serial.print(gyroYangle);Serial.print("\t");
  //Pitch
  //Serial.print(compAngleY); Serial.print(";");
  //Serial.print(kalAngleY);Serial.print(";");
  //Serial.print(0);Serial.print(";");
  
  //Serial.print(temp);Serial.print("\t");
   
  Serial.print("\n");
  delay(30);
}
