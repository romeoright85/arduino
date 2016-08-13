#include <UnderglowLeds.h>
#include <FoglightAssembly.h>
#include <SignalLightAssembly.h>


UnderglowLeds underglowLight = UnderglowLeds(UNDERGLOW_PIN);
FoglightAssembly fogLights = FoglightAssembly(FRONT_RIGHT_FOG_PIN, FRONT_LEFT_FOG_PIN);
SignalLightAssembly signalLightAssy = SignalLightAssembly(FRONT_RIGHT_SIGNAL_PIN, FRONT_LEFT_SIGNAL_PIN, SIDE_RIGHT_SIGNAL_PIN, SIDE_LEFT_SIGNAL_PIN);


void setup() {
	Serial.begin(9600);
}


void loop() {
	
	//blink all the lights
	underglowLight.ledOn();
	fogLights.turnOn(LEFT_FOG, RIGHT_FOG);
	signalLightAssy.turnOn(FRONT_RIGHT_SIGNAL_PIN, FRONT_LEFT_SIGNAL_PIN, SIDE_RIGHT_SIGNAL_PIN, SIDE_LEFT_SIGNAL_PIN);
	delay(1000);
	underglowLight.ledOff();
	fogLights.turnOff(LEFT_FOG, RIGHT_FOG);
	signalLightAssy.turnOff(FRONT_RIGHT_SIGNAL_PIN, FRONT_LEFT_SIGNAL_PIN, SIDE_RIGHT_SIGNAL_PIN, SIDE_LEFT_SIGNAL_PIN);
	delay(1000);	

}
