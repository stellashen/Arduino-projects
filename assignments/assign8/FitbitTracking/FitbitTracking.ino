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
bool ledOn = true;
float fx;
float fy;
float fz;
float y[3] = {0,0,0};
int c;
float previousY;
float previousPreviousY;
int peak;  // peak  = step counts
unsigned long lastPeakTime;
bool startCountSteps = true;

float sx[100];
float sy[100];
float sz[100];
float sumx=0;
float sumy=0;
float sumz=0;
int valCounts = 0;

float avgx = 0;
float avgy = 0;
float avgz = 0;
int peakX = 0;
int peakY = 0;
int peakZ = 0;
int lastPeakX = 0;
int lastPeakY = 0;
int lastPeakZ = 0;

int peakSumX = 0;
int peakSumY = 0;
int peakSumZ = 0;
unsigned long accumulator3 = 0;
bool startNew = true;
unsigned long sleepTime = 0;

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

//debounce for mode button
int buttonState = 1;             // the current button state
int lastButtonState = 1;   // the previous button state

int reading = 1;           // input reading: 0 when pushed, 1 when not
int lastReading = 1;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

//debounce for reset button
int buttonState2 = 1;             // the current button state
int lastButtonState2 = 1;   // the previous button state

int reading2 = 1;           // input reading: 0 when pushed, 1 when not
int lastReading2 = 1;

unsigned long lastDebounceTime2 = 0;  // the last time the output pin was toggled

//rawbits
unsigned long rawBits; 
int r1=0;
int r2=0;
int r3=0;

void setup() {
	Serial.begin(9600);
	accel.init();
	// buttons
	pinMode(modePin, INPUT_PULLUP);
	pinMode(resetPin, INPUT_PULLUP);
	// temperature sensor set to 5V
	analogReference(DEFAULT);
	// led
	pinMode(ledPin, OUTPUT);
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
			//reset delta timing
			if (startCountSteps){
				lastPeakTime = millis();
				startCountSteps = false;
			}

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
		// check if there is no motion for every 500 iterations
		else{
			if(startNew){
				//reset delta timing
				accumulator3 = millis();
				startNew = false;
			}

			//led off: sleep tracking mode
			digitalWrite(ledPin, LOW);
			sumx = sumx + fx;
			sumy = sumy + fy;
			sumz = sumz + fz;
			sx[valCounts] = fx;
			sy[valCounts] = fy;
			sz[valCounts] = fz;

			if(valCounts == 99){
				avgx = sumx/valCounts;
				avgy = sumy/valCounts;
				avgz = sumz/valCounts;

				checkMotion();

				//reset
				valCounts = 0;
				sumx = 0;
				sumy = 0;
				sumz = 0;
				peakX = 0;
				peakY = 0;
				peakZ = 0;
				lastPeakX = 0;
				lastPeakY = 0;
				lastPeakZ = 0;
			}
			else{
				valCounts = valCounts + 1;
			}

		}
	}

	checkModeButton();
	checkResetStepCountButton();

	if(millis() - accumulator2 > interval/FILTER_COUNTS) { 
		accumulator2 += interval/FILTER_COUNTS; 
		val = analogRead(tempPin);
		voltage = val*5/1023.0;
		temperature = 100*voltage - 50;
		temps[count % FILTER_COUNTS] = temperature;
		count = count + 1;
	}

	timeStamp = millis();

	//send messages from Arduino to Java once per second
	if(timeStamp - accumulator > interval) { 
		accumulator += interval;
		send();
	}
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
				//				Serial.println(peak);
				//				Serial.println(lastPeakTime);
			}
		}
	}
}

void checkMotion(){
	// count peaks during the past 100 iterations
	for(int k = 1; k<= 98; k++){
		if(sx[k]>avgx+0.2){
			if(sx[k]>sx[k-1] & sx[k]>sx[k+1]){
				// if two peaks are too close, don't count
				if (k - lastPeakX > 10){
					peakX = peakX + 1;
					lastPeakX = k;
					//					Serial.println("peakX");
					//					Serial.println(peakX);
				}
			}
		}
		if(sy[k]>avgy+0.2){
			if(sy[k]>sy[k-1] & sy[k]>sy[k+1]){
				// if two peaks are too close, don't count
				if (k - lastPeakY> 10){
					peakY = peakY + 1;
					lastPeakY = k;
					//					Serial.println("peakY");
					//					Serial.println(peakY);
				}
			}
		}
		if(sz[k]>avgz+0.2){
			if(sz[k]>sz[k-1] & sz[k]>sz[k+1]){
				// if two peaks are too close, don't count
				if (k - lastPeakZ > 10){
					peakZ = peakZ + 1;
					lastPeakZ = k;
					//					Serial.println("peakZ");
					//					Serial.println(peakZ);
				}
			}
		}
	}

	peakSumX = peakX + peakSumX;
	peakSumY = peakY + peakSumY;
	peakSumZ = peakZ + peakSumZ;

	//What is no motion? Answer: peak sum for all axis < 10  in 10 seconds
	if(millis() - accumulator3 > 10000) { 
		accumulator3 += 10000; 
		//		Serial.println(peakSumX);
		//		Serial.println(peakSumY);
		//		Serial.println(peakSumZ);
		//		Serial.println();

		// if there are too much peaks -> there are too much motion 
		// -> person is not asleep -> reset sleepTime to 0 
		if(peakSumX > 10 || peakSumY > 10 || peakSumZ > 10){
			sleepTime = 0;	
		}
		// if person is asleep, add 10 seconds
		else{
			sleepTime = sleepTime + 10000;
			//			Serial.println(sleepTime);
		}
		//reset sum to 0 for the next cycle
		peakSumX = 0;
		peakSumY = 0;
		peakSumZ = 0;
		startNew = true;
	}
}

void checkModeButton(){
	reading = digitalRead(modePin);

	// check to see if you just pressed the button
	// (i.e. the input went from LOW to HIGH),  and you've waited
	// long enough since the last press to ignore any noise:

	// If the switch changed, due to noise or pressing:
	if (reading != lastReading) {
		// reset the debouncing timer
		lastDebounceTime = millis();
	}

	// if wait long enough, take the reading as the real button state
	if (millis() - lastDebounceTime > debounceDelay) {
		buttonState = reading;

		if (buttonState==0 && lastButtonState==1){
			//button is really pushed once
			ledOn = !ledOn; //change mode

			if(ledOn==true){
				startCountSteps = true; 
			}
			else{
				startNew = true; 
				sleepTime = 0; 
			}

			lastButtonState = buttonState;
		}

		lastReading = reading;
	}
}

void checkResetStepCountButton(){
	reading2 = digitalRead(resetPin);

	// If the switch changed, due to noise or pressing:
	if (reading2 != lastReading2) {
		// reset the debouncing timer
		lastDebounceTime2 = millis();
	}

	// if wait long enough, take the reading as the real button state
	if (millis() - lastDebounceTime2 > debounceDelay) {
		buttonState2 = reading2;

		if (buttonState2==0 && lastButtonState2==1){
			peak = 0; // reset step counts to 0
			startCountSteps = true; 
		}

		lastButtonState2 = buttonState2;
	}

	lastReading2 = reading2;
}

void send(){
	if(timeStamp - accumulator > interval) { 
		accumulator += interval; 
		//magic number: 0x23 - ASCII '#'
		//0x30. debugging string
		Serial.write(0x23);
		Serial.write(0x30);
		Serial.write(0x00);
		Serial.write(0x04);
		Serial.write("Test");

		//0x32. filtered temp in Celsius: avg
		for (int i = 0; i < FILTER_COUNTS; i++){
			sum = sum + temps[i];
		}
		avg = sum/FILTER_COUNTS;
		sum = 0;
		count = 0;
		rawBits = *(unsigned long *) & avg; 
		Serial.write(0x23);
		Serial.write(0x32);
		r1=rawBits>>24;
		r2=rawBits>>16;
		r3=rawBits>>8;
		Serial.write(r1);
		Serial.write(r2);
		Serial.write(r3);
		Serial.write(rawBits);

		if(ledOn){
			//0x33. step counts
			Serial.write(0x23);
			Serial.write(0x33);
			Serial.write(peak>>8);
			Serial.write(peak);
		}
		else{
			//0x34. time spent asleep
			Serial.write(0x23);
			Serial.write(0x34);
			Serial.write(sleepTime>>24);
			Serial.write(sleepTime>>16);
			Serial.write(sleepTime>>8);
			Serial.write(sleepTime);
		}

		//0x35. timestamp: timeStamp
		Serial.write(0x23);
		Serial.write(0x35);
		t1 = timeStamp >> 24;
		t2 = timeStamp >> 16;
		t3 = timeStamp >> 8;
		Serial.write(t1);
		Serial.write(t2);
		Serial.write(t3);
		Serial.write(timeStamp);

		//0x31. error string if the temperature is less than 20
		if (avg < 20){
			Serial.write(0x23);
			Serial.write(0x31);
			Serial.write(0x00);
			Serial.write(0x0A);
			Serial.write("Low Temp!!");
		}
	}
}