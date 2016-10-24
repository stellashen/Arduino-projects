#include <Wire.h> // Must include Wire library for I2C
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library
MMA8452Q accel;

void setup() {
	Serial.begin(9600);
	accel.init();
}

void loop() {
	  if (accel.available())
	  {
	    // First, use accel.read() to read the new variables:
	    accel.read();
	    Serial.print(accel.cx);
	    Serial.print(",");
	    Serial.print(accel.cy);
	    Serial.print(",");
	    Serial.print(accel.cz);
	    Serial.println();
	  }
}
