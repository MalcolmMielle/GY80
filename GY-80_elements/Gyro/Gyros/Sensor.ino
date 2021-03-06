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
    Serial.println("Failed to autodetect gyro type!");
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


void Read_Accel(){
  
  accel.read();
  accel.normalize();
  accYangle=getPitch(accel);
  accXangle=getRoll(accel);
  accYangle=TO_DEG(accYangle);
  accXangle=TO_DEG(accXangle);
}
