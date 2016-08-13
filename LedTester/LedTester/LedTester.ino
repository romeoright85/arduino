#include <UnderglowLeds.h>
#include <FoglightAssembly.h>


UnderglowLeds underglowLight = UnderglowLeds(UNDERGLOW_PIN);
FoglightAssembly fogLights = FoglightAssembly(FRONT_RIGHT_FOG_PIN, FRONT_LEFT_FOG_PIN);




void setup() {
	Serial.begin(9600);
}


void loop() {
	
	//blink all the lights
	underglowLight.ledOn();
	fogLights.allOn();
	delay(1000);
	underglowLight.ledOff();
	fogLights.allOff();
	delay(1000);
	

}
