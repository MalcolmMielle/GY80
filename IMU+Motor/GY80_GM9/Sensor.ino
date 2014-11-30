// Sensor I2C addresses
#define ACCEL_ADDRESS ((int) 0x53) // 0x53 = 0xA6 / 2
#define MAGN_ADDRESS  ((int) 0x1E) // 0x1E = 0x3C / 2
#define GYRO_ADDRESS  ((int) 0x68) // 0x68 = 0xD0 / 2

// Arduino backward compatibility macros
#define WIRE_SEND(b) Wire.write((byte) b) 
#define WIRE_RECEIVE() Wire.read() 

void I2C_Init()
{
  Wire.begin();
}

void Accel_Init()
{
   if (!accel.init())
  {
    Serial.println("Failed to autodetectaccel type!");
    while (1);
  }
}


void Gyro_Init()
{
  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }
  gyro.enableDefault();
}

void Magn_Init()
{
  Wire.beginTransmission(MAGN_ADDRESS);
  WIRE_SEND(0x02); 
  WIRE_SEND(0x00);  // Set continuous mode (default 10Hz)
  Wire.endTransmission();
  delay(5);

  Wire.beginTransmission(MAGN_ADDRESS);
  WIRE_SEND(0x00);
  WIRE_SEND(0b00011000);  // Set 50Hz
  Wire.endTransmission();
  delay(5);
}

void Bmp_Init(){
  bmp.begin();
}

void Read_Magn()
{
  compass.ReadScaledAxis();
}

void Read_Accel(){
  accel.read();
  accel.normalize();
  accYangle=getPitch(accel);
  accXangle=getRoll(accel);
  accYangle=TO_DEG(accYangle);
  accXangle=TO_DEG(accXangle);
}

void Read_Gyro(){
  gyro.read();
  gyroXrate = (double)gyro.x*0.0175; //131.0
  gyroYrate = -(double)gyro.y*0.0175;
  gyroZrate = -(double)gyro.z*0.0175;
}

void FF_Init(){
  accel.initAdvanced();
}


void FIR(int us) //Effectue un filtre à réponse fini... ok c'est juste une moyenne mais quand meme !
{
  int y=0;
  for(int i=1;i<10;i++)
  {
    y=y+buff_sonar[i];
    buff_sonar[i-1]=buff_sonar[i];
  }
  y=y+us;
  y=y/10;
  buff_sonar[9]=us;
}

void Read_sonar(){
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  int us2=uS / US_ROUNDTRIP_CM;
  FIR(us2); // la valeur est storé dans le buffer
  Serial.print("Sonar : ");
  
  Serial.print(buff_sonar[9]);

}

