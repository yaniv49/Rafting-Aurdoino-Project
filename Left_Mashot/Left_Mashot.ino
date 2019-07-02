#include<Wire.h>
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();
const int MPU=0x68; 
int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
boolean firstTime = true;
int lastZ = 0, lastY = 0;
int val;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0);    
  Wire.endTransmission(true);
  Serial.begin(9600);
  mySwitch.enableTransmit(2);
}
void loop(){
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU,12,true);  
  AcX=(Wire.read()<<8|Wire.read()) / 1000;    
  AcY=(Wire.read()<<8|Wire.read()) / 1000;  
  AcZ=(Wire.read()<<8|Wire.read()) / 1000;  
  GyX=(Wire.read()<<8|Wire.read()) / 1000;  
  GyY=(Wire.read()<<8|Wire.read()) / 1000;  
  GyZ=(Wire.read()<<8|Wire.read()) / 1000;  

   if(firstTime == true)
      {
        lastY = AcY;
        lastZ = AcZ;
        firstTime = false;
      }
  
 //Serial.print("Accelerometer: ");
Serial.print("Last Z: "); Serial.println(lastZ);
 Serial.print("Last Y: "); Serial.println(lastY);
 Serial.print("Y = "); Serial.print(AcY);
 Serial.print(" | Z = "); Serial.print(AcZ);
 //Serial.println(" ");

   int diffY = AcY - lastY; 
   int diffZ = AcZ - lastZ;
  if((abs(diffY) > 2) && (abs(diffZ) > 2))
  {
        Serial.println("Left!");
    val = 2;
    mySwitch.send(val,4);
  }
  else
  {
    val = 1;
    mySwitch.send(val ,4);
  }

   lastY = AcY;
   lastZ = AcZ;
   delay(270);
    
 }
