void moveMotor(){
  if (compAngleY>10 && compAngleY<180){
    Serial.print("Cas 1\n");
    mot2.gofront();
// set leg 2 of the H-bridge high
    mot1.ungo();
  }
  else if(compAngleY<-10 && compAngleY>-180){
    Serial.print("Cas 2\n");
    mot2.ungo();
 // set leg 2 of the H-bridge high
    mot1.gofront();  // set leg 2 of the H-bridge high
  }
  else{
    Serial.print("Cas 3\n");
    mot1.gofront();
    mot2.gofront();
  }
    Serial.print(compAngleY); Serial.print(";");
}  
