/* sender
 *  
 *  CSE 132 - Assignment 4
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name: Yangchen Shen
 *  WUSTL Key: sheny
 *  
 *  and if two are partnered together
 *  
 *  Name:
 *  WUSTL Key:
 */

//potentiometer
const int potPin = A0;
int potVal = 0;
int p1 = 0;

//temperature sensor
const int tempPin = A1;
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
int r1=0;
int r2=0;
int r3=0;

void setup() {
	Serial.begin(9600);
	analogReference(DEFAULT);
}

void loop() {

	if(millis() - accumulator2 > interval/FILTER_COUNTS) { 
		accumulator2 += interval/FILTER_COUNTS; 
		val = analogRead(tempPin);
		voltage = val*5/1023.0;
		temperature = 100*voltage - 50;
		temps[count % FILTER_COUNTS] = temperature;
		count = count + 1;
	}

	timeStamp = millis();

	if(timeStamp - accumulator > interval) { 
		accumulator += interval; 
		//0. debugging string
		Serial.write(0x21);
		Serial.write(0x30);
		Serial.write(0x00);
		Serial.write(0x04);
		Serial.write("Test");
		//1. timestamp: timeStamp
		Serial.write(0x21);
		Serial.write(0x32);
		t1 = timeStamp >> 24;
		t2 = timeStamp >> 16;
		t3 = timeStamp >> 8;
		Serial.write(t1);
		Serial.write(t2);
		Serial.write(t3);
		Serial.write(timeStamp);
		//2. the potentiometer reading: potVal
		potVal = analogRead(potPin);
		Serial.write(0x21);
		Serial.write(0x33);
		p1 = potVal >> 8;
		Serial.write(p1);
		Serial.write(potVal);
		//3. unfiltered, raw temperature value: val
		val = analogRead(tempPin);
		Serial.write(0x21);
		Serial.write(0x34);
		v1 = val >> 8;
		Serial.write(v1);
		Serial.write(val);
		//4. unfiltered temp in Celsius: temperature
		// Vmeasured = analogRead()*5V/1023
		// Temp = Vmeasured*100-50
		voltage = val*5/1023.0;
		temperature = 100*voltage - 50;
//		Serial.print("raw:");
//		Serial.print(val);
//		Serial.print("voltage:");
//		Serial.print(voltage);
//		Serial.print("temperature:");
//		Serial.print(temperature);
		Serial.write(0x21);
		Serial.write(0x35);
		float f = temperature; unsigned long rawBits; rawBits = *(unsigned long *) &f; 
		Serial.write(rawBits>>24);
		Serial.write(rawBits>>16);
		Serial.write(rawBits>>8);
		Serial.write(rawBits);
		//5. filtered temp in Celsius: avg
		for (int i = 0; i < FILTER_COUNTS; i++){
			sum = sum + temps[i];
		}
		avg = sum/FILTER_COUNTS;
		sum = 0;
		count = 0;
		float f2 = avg; unsigned long rawBits2; rawBits2 = *(unsigned long *) &f2; 

		// Serial.print("Filtered temperature in Celsius: ");
		Serial.write(0x21);
		Serial.write(0x36);
		r1=rawBits2>>24;
		r2=rawBits2>>16;
		r3=rawBits2>>8;
		Serial.write(r1);
		Serial.write(r2);
		Serial.write(r3);
		Serial.write(rawBits2);

		//6.error string if the potentiometer reading is over 800
		if (potVal > 800){
			Serial.write(0x21);
			Serial.write(0x31);
			Serial.write(0x00);
			Serial.write(0x0A);
			Serial.write("High Alarm");
		}

	}
}
