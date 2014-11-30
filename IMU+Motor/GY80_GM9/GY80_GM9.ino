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
#include <ADXL345.h>
#include <HMC5883L.h>
#include "BMP085.h"
#include <Motor.h>
#include <NewPing.h>

#define PING_PIN  11  // Arduino pin tied to both trigger and echo pins on the ultrasonic sensor. Need to be
#define MAX_DISTANCE 20 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(PING_PIN, PING_PIN, MAX_DISTANCE); // NewPing setup of pin and maximum distance.
 
BMP085 bmp; //Calpteur temp et pression

HMC5883L compass; //Magnéto


double accXangle, accYangle, accZangle; // Angle donnés par l'accéléromètre
double temp; // Temperature
double gyroXangle, gyroYangle, gyroZangle; // Angles donnés par le gyroscope
double gyroXrate, gyroYrate, gyroZrate;
double compAngleX, compAngleY, compAngleZ; // Angles donnés par le filtre complémentaire

uint32_t timer;
uint8_t i2cData[14]; // Buffer for I2C data

/******Declaration des capteurs**********/
L3G gyro;
ADXL345 accel(8,3300);

/*******Fonction de changement*********/
#define TO_RAD(x) (x * 0.01745329252)  // *pi/180
#define TO_DEG(x) (x * 57.2957795131)  // *180/pi

/***********VARIABLE DE SMOTEURS**********/
// switch input
Motor mot1(3,4);
Motor mot2(5,6);
int pin=9;
int var=1;
int led =13;
int enablePin = 2;    // H-bridge enable pin

/*****************************************************/

/************VARIABLE SONAR********************/
double buff_sonar[10]={0,0,0,0,0,0,0,0,0,0};//Buffer de filtrage

/**************************************************/

void setup() {  
  Serial.begin(9600);
  /***Setup motor***/
  // set all the other pins you're using as outputs:
  mot1.enable();
  mot2.enable();
  pinMode(enablePin, OUTPUT);
  pinMode(led,OUTPUT);
  pinMode(pin,INPUT);
  // set enablePin high so that motor can turn on:
  digitalWrite(enablePin, HIGH); 
  
  /***Setup sensor****/
  
  I2C_Init();
  Accel_Init();
  Gyro_Init();
  Magn_Init();
  Bmp_Init();
  FF_Init();
  
  delay(100); // Wait for sensor to stabilize
  
  /************************************ Mise en place de Kalman *******************************************/
  Read_Accel();

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
  if(accel.readAdvanced(pin)==1){
    var=-var;
  }
  Read_sonar();
  if(var==1 && buff_sonar[9]<2){
    //digitalWrite(led,HIGH);
    moveMotor();
  }
  else{
    //digitalWrite(led,LOW);
    mot1.ungo();
    mot2.ungo();
  }
 timer = micros();
  //affiche();
  delay(30);
}
