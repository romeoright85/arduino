#include <UnoLoopback.h>


//Data Rates
#define BAUD_RATE 9600//baud rate
UnoLoopback unoLoopback(BAUD_RATE);

void setup() {
 
    unoLoopback.startComms();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  unoLoopback.startLoopback();
  
}
