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
const int ledPin = 13;//led on: step counting mode (pedometer); led off: sleep tracking mode
const int tempPin = A0; // temperature sensor

//accelerometer (orientation is down with y pointing down when used as pedometer)
bool ledOn = false;
float fx;
float fy;
float fz;
float y[3] = {0,0,0};
float sumx=0;
float sumy=0;
float sumz=0;
int valCounts = 0;
unsigned long accumulator3 = 0;
float avgx = 0;
float avgy = 0;
float avgz = 0;

int c;
float previousY;
float previousPreviousY;
int peak;
unsigned long lastPeakTime;

//temperature sensor
int val = 0;
int v1 = 0;
float voltage = 0;
float temperature = 0;
const int FILTER_COUNTS = 10;
float temps[FILTER_COUNTS]; 
int count = 0;
float sum = 0;
float avg = 0;

//delta time
unsigned long timeStamp = 0;
unsigned long t1=0;
unsigned long t2=0;
unsigned long t3=0;
unsigned long accumulator = 0;
unsigned long accumulator2 = 0;
const int interval = 1000;//1 hz is 1 sec

//rawbits
unsigned long rawBits; 
int r1=0;
int r2=0;
int r3=0;

void setup() {
	Serial.begin(9600);
	accel.init();
	//	// buttons
	//	pinMode(modePin, INPUT_PULLUP);
	//	pinMode(resetPin, INPUT_PULLUP);
	//	// temperature sensor set to 5V
	//	analogReference(DEFAULT);
	//	// led
	//	pinMode(ledPin, OUTPUT);
}

void loop() {

	if (accel.available())
	{
		// First, use accel.read() to read the new variables:
		accel.read();
		fx = accel.cx; 
		fy = accel.cy;
		fz = accel.cz;

		if (ledOn){
			y[c] = fy;
			//Don't run when there is less than 3 values stored.
			if (y[2]!=0){
				// led on: counting steps		

				digitalWrite(ledPin, HIGH);
				//Compare three values (the current value and previous two values) every time,
				// to see if the middle value is a peak.
				countingSteps();
			}
			c = c + 1;
			if (c>2){
				c=0;
			}
		}
		// led off: sleep tracking
		else{
			digitalWrite(ledPin, LOW);
			sumx = sumx + fx;
			sumy = sumy + fy;
			sumz = sumz + fz;
			valCounts = valCounts + 1;
			// check if there is no motion every 5 seconds
			if(millis() - accumulator3 > 5*interval) { 
				accumulator3 += 5*interval; 
				avgx = sumx/valCounts;
				avgy = sumy/valCounts;
				avgz = sumz/valCounts;
				Serial.print(avgx);
				Serial.print(",");
				Serial.print(avgy);
				Serial.print(",");
				Serial.println(avgz);
				Serial.println();
			}
		}

	}

	if(millis() - accumulator2 > interval/FILTER_COUNTS) { 
		accumulator2 += interval/FILTER_COUNTS; 
		val = analogRead(tempPin);
		voltage = val*5/1023.0;
		temperature = 100*voltage - 50;
		temps[count % FILTER_COUNTS] = temperature;
		count = count + 1;
	}
	//
	//	timeStamp = millis();
	//
	//	if(timeStamp - accumulator > interval) { 
	//		accumulator += interval; 
	//		//magic number: 0x23 - ASCII '#'
	//		//0x30. debugging string
	//		Serial.write(0x23);
	//		Serial.write(0x30);
	//		Serial.write(0x00);
	//		Serial.write(0x04);
	//		Serial.write("Test");
	//
	//		//0x32. filtered temp in Celsius: avg
	//		for (int i = 0; i < FILTER_COUNTS; i++){
	//			sum = sum + temps[i];
	//		}
	//		avg = sum/FILTER_COUNTS;
	//		sum = 0;
	//		count = 0;
	//		rawBits = *(unsigned long *) & avg; 
	//		Serial.write(0x23);
	//		Serial.write(0x32);
	//		r1=rawBits>>24;
	//		r2=rawBits>>16;
	//		r3=rawBits>>8;
	//		Serial.write(r1);
	//		Serial.write(r2);
	//		Serial.write(r3);
	//		Serial.write(rawBits);
	//
	//		//0x33. step counts
	//
	//		//0x34. time spent asleep
	//
	//		//0x35. timestamp: timeStamp
	//		Serial.write(0x23);
	//		Serial.write(0x35);
	//		t1 = timeStamp >> 24;
	//		t2 = timeStamp >> 16;
	//		t3 = timeStamp >> 8;
	//		Serial.write(t1);
	//		Serial.write(t2);
	//		Serial.write(t3);
	//		Serial.write(timeStamp);
	//
	//		//0x31. error string if the temperature is over 26
	//		if (avg > 26){
	//			Serial.write(0x23);
	//			Serial.write(0x31);
	//			Serial.write(0x00);
	//			Serial.write(0x0A);
	//			Serial.write("High Temp!");
	//		}
	//
	//	}
}

void countingSteps(){
	if(c == 2){
		previousY = y[1]; 
		previousPreviousY = y[0];
	}
	if(c == 1){
		previousY = y[0]; 
		previousPreviousY = y[2];
	}
	if(c == 0){
		previousY = y[2]; 
		previousPreviousY = y[1];
	}
	if (previousY > previousPreviousY && previousY > y[c]){
		if(previousY > 1.1){
			// if two peaks are too close, don't count
			if (millis() - lastPeakTime > 500){
				peak = peak + 1; // one peak is one step
				lastPeakTime = millis();
				Serial.println(peak);
				Serial.println(lastPeakTime);
			}
		}
	}
}

