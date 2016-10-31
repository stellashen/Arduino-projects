/* sender
 *  
 *  CSE 132 - Assignment 8
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: Yangchen Shen
 *  WUSTL Key: sheny
 *  
 */

#include <Wire.h> // Must include Wire library for I2C
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library
MMA8452Q accel;

const int modePin = 8; // mode button: change between steps counting mode and sleep tracking mode
const int resetPin = 7; // reset button: reset steps
const int ledPin = 13;//led on: step counting mode; led off: sleep tracking mode
const int tempPin = A0; // temperature sensor

void setup() {
	Serial.begin(9600);
	accel.init();
	// buttons
	pinMode(modePin, INPUT_PULLUP);
	pinMode(resetPin, INPUT_PULLUP);
	// temperature sensor set to 1.1V
	analogReference(INTERNAL);
	// led
	pinMode(ledPin, OUTPUT);
}

void loop() {
	if (accel.available())
	{
		// First, use accel.read() to read the new variables:
		accel.read();
		Serial.write(accel.cx);
		Serial.write(accel.cy);
		Serial.write(accel.cz);
	}

}
