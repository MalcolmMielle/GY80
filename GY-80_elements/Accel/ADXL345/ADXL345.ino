/********************************************************************************
* ADXL345 Library Examples- pitch_roll.ino                                      *
*                                                                               *
* Copyright (C) 2012 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
*                                                                               *
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
* This is free software: you are free to change and redistribute it.            *
* There is NO WARRANTY, to the extent permitted by law.                         *
*                                                                               *
*********************************************************************************/

#include <Wire.h>
#include <ADXL345.h>

const float alpha = 0.5;

double fXg = 0;
double fYg = 0;
double fZg = 0;

ADXL345 acc(8,3300);

void setup()
{
        acc.init();
	//acc.begin();
	Serial.begin(9600);
	delay(100);
}


void loop()
{
	double pitch, roll, Xg, Yg, Zg;
	acc.read();

	//Low Pass Filter
	fXg = acc.x * alpha + (fXg * (1.0 - alpha));
	fYg = acc.y * alpha + (fYg * (1.0 - alpha));
	fZg = acc.z * alpha + (fZg * (1.0 - alpha));

	//Roll & Pitch Equations
	roll  = (atan2(-acc.y, acc.z)*180.0)/M_PI;
	pitch = (atan2(acc.x, sqrt(acc.y*acc.y+ acc.z*acc.z))*180.0)/M_PI;

	Serial.print(roll);
	Serial.print(":");
	Serial.print(pitch);
	Serial.print(":");
	Serial.print(acc.Vref);
	Serial.print(":");
	Serial.println(acc.sensitivity);


	delay(10);
}
