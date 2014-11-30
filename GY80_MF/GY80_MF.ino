/* Copyright (C) 2012 Kristian Lauszus, TKJ Electronics. All rights reserved.
 
 This software may be distributed and modified under the terms of the GNU
 General Public License version 2 (GPL2) as published by the Free Software
 Foundation and appearing in the file GPL2.TXT included in the packaging of
 this file. Please note that GPL2 Section 2[b] requires that all works based
 on this software must also be made publicly available under the terms of
 the GPL2 ("Copyleft").
 // Source: https://github.com/TKJElectronics/KalmanFilter
 */

#include <Wire.h>
#include <L3G.h>
#include <Kalman.h>
#include <ADXL345.h>
#include <HMC5883L.h>
#include "BMP085.h"
 
BMP085 bmp; //Calpteur temp et pression

HMC5883L compass; //Magnéto

Kalman kalmanX; // Création des instances de Kalman
Kalman kalmanY;

double accXangle, accYangle, accZangle; // Angle donnés par l'accéléromètre
double temp; // Temperature
double gyroXangle, gyroYangle, gyroZangle; // Angles donnés par le gyroscope
double gyroXrate, gyroYrate, gyroZrate;
double compAngleX, compAngleY, compAngleZ; // Angles donnés par le filtre complémentaire
double kalAngleX, kalAngleY, kalAngleZ; // Angles donnés par Kalman

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
  Magn_Init();
  Bmp_Init();
  
  delay(100); // Wait for sensor to stabilize
  
  /************************************ Mise en place de Kalman *******************************************/
  Read_Accel();
  //accZangle=(atan2(accel.y,accel.z)+PI)*RAD_TO_DEG;
  kalmanX.setAngle(accXangle);
  kalmanY.setAngle(accYangle);
  //kalmanZ.setAngle(accZangle);
  gyroXangle=accXangle;
  gyroYangle=accYangle;
  
  /********************************** Debut du filtre compensateur *******************************/
  compAngleX=accXangle;
  compAngleY=accYangle;
  
  timer=micros();
}

void loop() {
  /* Update all the values */  
  Read_Accel(); //retourne pitch et roll
  Read_Gyro(); //Retourne les vitesse de rotations gyroXrate, gyroYrate, gyroZrate.
  Read_Magn();
   //GROS DRIFT...
  gyroXangle += gyroXrate*((double)(micros()-timer)/1000000); // Calcul de l'orientation donnée par le gyro !!OFFSET DE 2 FULL XPERIMENTAL
  gyroYangle += gyroYrate*((double)(micros()-timer)/1000000);
  gyroZangle += gyroZrate*((double)(micros()-timer)/1000000);
  //gyroXangle += kalmanX.getRate()*((double)(micros()-timer)/1000000); // Calcul de l'orientation du gyro en utilisant kalman
  //gyroYangle += kalmanY.getRate()*((double)(micros()-timer)/1000000);
  
  compAngleX = (0.93*(compAngleX+(gyroXrate*(double)(micros()-timer)/1000000)))+(0.07*accXangle); // Calul de l'angle en utilisant un filtre compensateur
  compAngleY = (0.93*(compAngleY+(gyroYrate*(double)(micros()-timer)/1000000)))+(0.07*accYangle);
  
  kalAngleX = kalmanX.getAngle(accXangle, gyroXrate, (double)(micros()-timer)/1000000); // Calcul de l'angle en utilisant Kalman
  kalAngleY = kalmanY.getAngle(accYangle, gyroYrate, (double)(micros()-timer)/1000000);
  timer = micros();
  affiche();
  delay(30);
}
