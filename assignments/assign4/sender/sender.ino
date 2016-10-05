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

//temperature sensor
const int tempPin = A1;
float val = 0;
float voltage = 0;
float temperature = 0;
const int FILTER_COUNTS = 10;
float temps[FILTER_COUNTS]; 
int count = 0;
float sum = 0;
float avg = 0;

//delta time
unsigned timeStamp = 0;
unsigned long accumulator = 0;
unsigned long accumulator2 = 0;
const int interval = 1000;//1 hz is 1 sec

void setup() {
	Serial.begin(9600);
	analogReference(DEFAULT);
}

void loop() {

	if(millis() - accumulator2 > interval/FILTER_COUNTS) { 
		accumulator2 += interval/FILTER_COUNTS; 
		val = analogRead(tempPin);
		voltage = val*5/1023;
		temperature = 100*voltage - 50;
		temps[count % FILTER_COUNTS] = temperature;
		count = count + 1;
	}

	timeStamp = millis();

	if(timeStamp - accumulator > interval) { 
		accumulator += interval; 
		//protocol: 6 things to send
		//1. timestamp: timeStamp
		Serial.print("Time: ");
		Serial.println(timeStamp);
		//2. the potentiometer reading: potVal
		potVal = analogRead(potPin);
		Serial.print("The potentiometer reading: ");
		Serial.println(potVal);
		//3. unfiltered, raw temperature value: val
		val = analogRead(tempPin);
		Serial.print("Unfiltered raw value of temperature: ");
		Serial.println(val);
		//4. unfiltered temp in Celsius: temperature
		// Vmeasured = analogRead()*5V/1023
		// Temp = Vmeasured*100-50
		voltage = val*5/1023;
		temperature = 100*voltage - 50;
		Serial.print("Unfiltered temperature in Celsius: ");
		Serial.println(temperature);
		//5. filtered temp in Celsius: avg
		for (int i = 0; i < FILTER_COUNTS; i++){
			sum = sum + temps[i];
		}
		avg = sum/FILTER_COUNTS;
		sum = 0;
		count = 0;
		Serial.print("Filtered temperature in Celsius: ");
		Serial.println(avg);

		//6.error string if the potentiometer reading is over 800
		if (potVal > 800){
			Serial.println("Error: Alarm! The potentiometer reading is over 800.");
		}
		
		//empty line
		Serial.println();
		
	}
}
