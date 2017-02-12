/*
Outputs Compass Gauss Values for X, Y, and Z
*/

#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

char report[80];

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  compass.enableDefault();
}

void loop()
{
     
  Serial.println("X:\tY:\tZ:");
  
  while(1)
  {
    
    compass.read();
    snprintf(report, sizeof(report), "%6d\t%6d\t%6d",
      
    compass.m.x, compass.m.y, compass.m.z);
    Serial.println(report);
  
    delay(100);
  }
}
