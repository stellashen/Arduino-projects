//from sender.ino
//potentiometer
const int potPin = A5;
int potVal = 0;
int p1 = 0;
//delta time
unsigned long timeStamp = 0;
unsigned long t1=0;
unsigned long t2=0;
unsigned long t3=0;
unsigned long accumulator2 = 0;
const int interval = 1000;

//***display****
#include "font.h"

// set led output pins, buttons
int row[7] = {2,3,4,5,6,7,8};
int col[5] = {9,10,11,12,13};
const int buttonIn = A0; //push button to increment the current ASCII character by 1
const int buttonDe = A1; //decrement by 1

//variable used for font array
int numChar = 0x00;

// variables used to translate numChar to led values
int led[5][7];
unsigned long columnVal = 0;
int numColumnsOn = 0; // the number of columns that are used in the current display
int columnsOn[5]; // the columns that are used in the current display

// delta timing variables used to cycle through the columns
unsigned long accumulator = 0;
//int interval = 10;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	analogReference(DEFAULT);
}

void loop() {
	timeStamp = millis();
	// put your main code here, to run repeatedly:
	if(timeStamp - accumulator2 > interval) { 
		accumulator2 += interval; 
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
	}
}
