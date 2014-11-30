// Computes the cross product of two vectors
void Vector_Cross_Product(float vectorOut[3], float v1[3], float v2[3])
{
  vectorOut[0]= (v1[1]*v2[2]) - (v1[2]*v2[1]);
  vectorOut[1]= (v1[2]*v2[0]) - (v1[0]*v2[2]);
  vectorOut[2]= (v1[0]*v2[1]) - (v1[1]*v2[0]);
}

float getPitch(ADXL345 a){
  return atan2(a.x, sqrt(a.y*a.y+a.z*a.z));
}

float getRoll(ADXL345 a){
  float temp1[3];
  float temp2[3];
  float Accel[3]= {a.x, a.y, a.z};
  float xAxis[3] = {1.0f, 0.0f, 0.0f};
  Vector_Cross_Product(temp1,Accel,xAxis);
  Vector_Cross_Product(temp2,xAxis,temp1);
  return atan2(temp2[1], temp2[2]);
}
