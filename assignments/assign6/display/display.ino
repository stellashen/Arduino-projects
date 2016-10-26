/* display
 *  
 *  CSE 132 - Assignment 6
 *  
 *  Fill this out so we know whose assignment this is.
 *  
 *  Name:Yangchen Shen
 *  WUSTL Key:sheny
 *  
 *  Name:
 *  WUSTL Key:
 *  
 */

#include "font.h"

int row[7] = {2,3,4,5,6,7,8};
int col[5] = {9,10,11,12,13};
const int buttonIn = A0; //push button to increment the current ASCII character by 1
const int buttonDe = A1; //decrement by 1
int numChar = 0x00;

//int count = 0;
//unsigned long accumulator = 0;

// button variables
int buttonStateIn = 1;             // the current button state
int buttonStateDe = 1; 
int lastButtonStateIn = 1;   // the previous button state
int lastButtonStateDe = 1;
int countPushIn = 0;         // number of times the button is pushed
int countPushDe = 0; 
int readingValIn = 1010;     // input reading raw value: <20 when pushed, >1000 when not
int readingValDe = 1010;
int readingIn = 1;           // input reading: 0 when pushed, 1 when not
int readingDe = 1; 
int lastReadingIn = 1;
int lastReadingDe = 1;
unsigned long lastDebounceTimeIn = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTimeDe = 0;
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
bool b = true; // is buttonIn? true/false

void setup ()
{
	Serial.begin(9600);
	pinMode(buttonIn, INPUT_PULLUP);
	pinMode(buttonDe, INPUT_PULLUP);

	for(int i = 0; i < 7; i++){
		pinMode(row[i], OUTPUT);
	}
	for(int i = 0; i < 5; i++){
		pinMode(col[i], OUTPUT);
	}

	// all LEDs off
	for(int i = 0; i < 7; i++){
		digitalWrite(row[i],LOW);
	}
	for(int i = 0; i < 5; i++){
		digitalWrite(col[i],HIGH);
	}
}

void loop ()
{
	readingValIn = analogRead(buttonIn);
	if (readingValIn < 20){
		readingIn = 0;
	}
	else{
		readingIn = 1;
	}

	readingValDe = analogRead(buttonDe);
	if (readingValIn < 20){
		readingDe = 0;
	}
	else{
		readingDe = 1;
	}

	numChar = calculateNumChar();

	Serial.println(numChar);
	//font_5x7[c][0]
}


int calculateNumChar() {
	countPushIn = debounce(b);	
	countPushDe = debounce(!b);
	return (numChar+countPushIn-countPushDe);
}

int debounce(b){
	if (b){
		int buttonState = buttonStateIn;            
		int lastButtonState = lastButtonStateIn;   
		int countPush = countPushIn;
		int reading = readingIn;           
		int lastReading = lastReadingIn;
		unsigned long lastDebounceTime = lastDebounceTimeIn;
	}
	else{
		int buttonState = buttonStateDe;            
		int lastButtonState = lastButtonStateDe;   
		int countPush = countPushDe;
		int reading = readingDe;           
		int lastReading = lastReadingDe;
		unsigned long lastDebounceTime = lastDebounceTimeDe;
	}

	// If the switch changed, due to noise or pressing:
	if (reading != lastReading) {
		// reset the debouncing timer
		lastDebounceTime = millis();
	}

	// if wait long enough, take the reading as the real button state
	if (millis() - lastDebounceTime > debounceDelay) {
		buttonState = reading;

		if (buttonState==0 && lastButtonState==1){
			countPush = countPush + 1;
			Serial.println(countPush);
		}

		lastButtonState = buttonState;
	}

	if(b){
		buttonStateIn = buttonState;            
		lastButtonStateIn = lastButtonState;    
		lastDebounceTimeIn = lastDebounceTime;
		lastReadingIn = reading;
	}
	else{
		buttonStateDe = buttonState;            
		lastButtonStateDe = lastButtonState;    
		lastDebounceTimeDe = lastDebounceTime;
		lastReadingDe = reading;
	}

	return countPush;
}
