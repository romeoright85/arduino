#include <math.h>
#define EARTHS_RADIUS_KM 6371//in KM, will need to use data type double, since it's a big number
#define EARTHS_RADIUS_M 6371000//will need to use data type double, since it's a big number


void setup() {
  Serial.begin(9600);
}

void loop() {

  double lat1 = 39.268483;  
  double long1 = -76.611738;
  double lat2 = 39.268608;
  double long2 = -76.609257;


  Serial.println(calculateDistance(lat1,long1,lat2,long2),4);
  
}



double calculateDistance( double desired_latitudeDeg, double desired_longitudeDeg, double actual_latitudeDeg, double actual_longitudeDeg)
{
  
  
  //lat 1 - desired latitude  
  double desired_latitudeRad;
  
  //lat 2 - actual latitude
  double actual_latitudeRad;  
  
  //long 1 - desired longitude
  
  
  //long 2 - actual longitude 
    
  double delta_latitudeRad;
  double delta_longitudeRad;
  
  double varA;
  double varC;
  double distance;
  
  
  desired_latitudeRad = (desired_latitudeDeg * M_PI) / 180;
  
  actual_latitudeRad = (actual_latitudeDeg * M_PI) / 180;
  
  delta_latitudeRad = actual_latitudeRad - desired_latitudeRad;
  
  delta_longitudeRad = ((actual_longitudeDeg - desired_longitudeDeg) * M_PI) / 180;
  
  varA = sin(delta_latitudeRad/2) * sin(delta_latitudeRad/2) + cos(desired_latitudeRad) * cos(actual_latitudeRad) * sin(delta_longitudeRad/2) * sin(delta_longitudeRad/2);
  
  varC = 2 * atan2( sqrt(varA), sqrt(1-varA) );
  
  distance = EARTHS_RADIUS_KM * varC;//in km
  
  return distance;

}
