//Used for NAVI - 1

#include <RoverGpsSensor.h>
#include <math.h>


//Global Variables
RoverGpsSensor * roverGps = new RoverGpsSensor();


//Test Example:
//3916.2242, N, 07636.6542, W
//Result:
//Latitude: 39.27
//Longitude: 76.61

double latitude_data = 3916.2242;
double longitude_data = 07636.6542;


RoverReset * resetArray[] = {
  roverGps
};


void setup() {
  
  //resetting all objects
  for (byte i = 0; i < sizeof(resetArray) / sizeof(resetArray[0]); i++)
  {
    resetArray[i]->reset();
  }
  
  _PC_USB_SERIAL_.begin(PC_USB_BAUD_RATE);
  
}


void loop() {

  _PC_USB_SERIAL_.print("Latitude: ");
  _PC_USB_SERIAL_.println(roverGps->convertLatitudeToDecimalDegrees(latitude_data, "N"),4);//Print 4 Decimal Places
  _PC_USB_SERIAL_.print("Longitude: ");
  _PC_USB_SERIAL_.println(roverGps->convertLongitudeToDecimalDegrees(longitude_data, "W"),4);//Print 4 Decimal Places
  delay(1000);
  _PC_USB_SERIAL_.println(M_PI,510);//Math PI
}

