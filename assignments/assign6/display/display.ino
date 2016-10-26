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
//int countPushIn = 0;         // number of times the button is pushed
//int countPushDe = 0; 
int readingValIn = 1010;     // input reading raw value: <20 when pushed, >1000 when not
int readingValDe = 1010;
int readingIn = 1;           // input reading: 0 when pushed, 1 when not
int readingDe = 1; 
int lastReadingIn = 1;
int lastReadingDe = 1;
unsigned long lastDebounceTimeIn = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTimeDe = 0;
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

//unsigned long column0, column1, column2, column3, column4;
int led[5][7];
unsigned long columnVal = 0;

void setup ()
{
	Serial.begin(9600);
	pinMode(buttonIn, INPUT_PULLUP);
	pinMode(buttonDe, INPUT_PULLUP);

//	for(int i = 0; i < 7; i++){
//		pinMode(row[i], OUTPUT);
//	}
//	for(int i = 0; i < 5; i++){
//		pinMode(col[i], OUTPUT);
//	}
//
//	// all LEDs off
//	for(int i = 0; i < 7; i++){
//		digitalWrite(row[i],LOW);
//	}
//	for(int i = 0; i < 5; i++){
//		digitalWrite(col[i],HIGH);
//	}
}

void loop ()
{
	readingValIn = analogRead(buttonIn);
	if (readingValIn < 20){
		readingIn = 0;
	}
	if(readingValIn > 1000){
		readingIn = 1;
	}

	readingValDe = analogRead(buttonDe);
	if (readingValDe < 20){
		readingDe = 0;
	}
	if(readingValDe > 1000){
		readingDe = 1;
	}

	//Serial.println(readingValIn);
	//Serial.println(readingValDe);

	debounceIn();
	debounceDe();

	//Serial.println(numChar);

	//corresponding values for each column
	//	column0 = font_5x7[numChar][0];
	//	column1 = font_5x7[numChar][1];
	//	column2 = font_5x7[numChar][2];
	//	column3 = font_5x7[numChar][3];
	//	column4 = font_5x7[numChar][4];
	//Serial.println(column0,BIN);

	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 7; j++){
			numChar = 0x03;
			columnVal = font_5x7[numChar][i];
			led[i][j] =  (columnVal >> (7-j) ) & 1; 
			// returns 0 or 1
			// the most important bit is set to row 0
			// the least important bit is an extra useless bit
			
			Serial.print("Column ");
			Serial.println(i);
			Serial.print("Row ");
			Serial.println(j);
			Serial.println(led[i][j]);
		}
	}

}

void debounceIn(){

	// If the switch changed, due to noise or pressing:
	if (readingIn != lastReadingIn) {
		// reset the debouncing timer
		lastDebounceTimeIn = millis();
	}

	// if wait long enough, take the reading as the real button state
	if (millis() - lastDebounceTimeIn > debounceDelay) {
		buttonStateIn = readingIn;

		if (buttonStateIn==0 && lastButtonStateIn==1){
			//countPushIn = countPushIn + 1;
			//Serial.println(countPushIn);
			numChar = numChar + 1;
		}

		lastButtonStateIn = buttonStateIn;
	}

	lastReadingIn = readingIn;
}

void debounceDe(){

	// If the switch changed, due to noise or pressing:
	if (readingDe != lastReadingDe) {
		// reset the debouncing timer
		lastDebounceTimeDe = millis();
	}

	// if wait long enough, take the reading as the real button state
	if (millis() - lastDebounceTimeDe > debounceDelay) {
		buttonStateDe = readingDe;

		if (buttonStateDe==0 && lastButtonStateDe==1){
			//countPushDe = countPushDe + 1;
			//Serial.println(countPushDe);
			numChar = numChar - 1;
		}

		lastButtonStateDe = buttonStateDe;
	}

	lastReadingDe = readingDe;
}
