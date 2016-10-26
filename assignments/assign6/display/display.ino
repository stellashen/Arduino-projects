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

// set led output pins, buttons
int row[7] = {2,3,4,5,6,7,8};
int col[5] = {9,10,11,12,13};
const int buttonIn = A0; //push button to increment the current ASCII character by 1
const int buttonDe = A1; //decrement by 1

//variable used for font array
int numChar = 0x00;

// button variables
int buttonStateIn = 1;             // the current button state
int buttonStateDe = 1; 
int lastButtonStateIn = 1;   // the previous button state
int lastButtonStateDe = 1;
int readingValIn = 1010;     // input reading raw value: <20 when pushed, >1000 when not
int readingValDe = 1010;
int readingIn = 1;           // input reading: 0 when pushed, 1 when not
int readingDe = 1; 
int lastReadingIn = 1;
int lastReadingDe = 1;
unsigned long lastDebounceTimeIn = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTimeDe = 0;
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// variables used to translate numChar to led values
int led[5][7];
unsigned long columnVal = 0;
int numColumnsOn = 0; // the number of columns that are used in the current display
int columnsOn[5]; // the columns that are used in the current display

// delta timing variables used to cycle through the columns
unsigned long accumulator = 0;
int interval = 10;
//int interval = 5000; // test


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
	//change numChar if buttons are pushed
	//debounce method used, so one button push is only calculated once
	debounceIn();
	debounceDe();

	// numChar needs to take a value between 0 and 127
	if (numChar < 0){
		numChar = 95;
	}
	if (numChar > 95){
		numChar = 0;
	}
	

	numColumnsOn = 0; // reset to 0 during every iteration
	for (int i = 0; i < 5; i++){
		columnVal = font_5x7[numChar][i];
		if (columnVal != 0){
			columnsOn[numColumnsOn] = i;
			numColumnsOn = numColumnsOn + 1;
		}
		for (int j = 0; j < 7; j++){
			led[i][j] =  (columnVal >> (7-j) ) & 1; 
			// returns 0 or 1
			// the most important bit is set to row 0
			// the least important bit is an extra useless bit
		}
	}

	if(numColumnsOn!=0){
		ledDisplay();
	}

}

void debounceIn(){
	readingValIn = analogRead(buttonIn);
	if (readingValIn < 20){
		readingIn = 0;
	}
	if(readingValIn > 1000){
		readingIn = 1;
	}

	// If the switch changed, due to noise or pressing:
	if (readingIn != lastReadingIn) {
		// reset the debouncing timer
		lastDebounceTimeIn = millis();
	}

	// if wait long enough, take the reading as the real button state
	if (millis() - lastDebounceTimeIn > debounceDelay) {
		buttonStateIn = readingIn;

		if (buttonStateIn==0 && lastButtonStateIn==1){
			numChar = numChar + 1;
		}

		lastButtonStateIn = buttonStateIn;
	}

	lastReadingIn = readingIn;
}

void debounceDe(){
	readingValDe = analogRead(buttonDe);
	if (readingValDe < 20){
		readingDe = 0;
	}
	if(readingValDe > 1000){
		readingDe = 1;
	}

	// If the switch changed, due to noise or pressing:
	if (readingDe != lastReadingDe) {
		// reset the debouncing timer
		lastDebounceTimeDe = millis();
	}

	// if wait long enough, take the reading as the real button state
	if (millis() - lastDebounceTimeDe > debounceDelay) {
		buttonStateDe = readingDe;

		if (buttonStateDe==0 && lastButtonStateDe==1){
			numChar = numChar - 1;
		}

		lastButtonStateDe = buttonStateDe;
	}

	lastReadingDe = readingDe;
}

int k = 0;//k: count the number of columns displayed (starting from 0)
//each column will display in turn
void ledDisplay(){	
	// all leds off
	for(int i = 0; i < 7; i++){
		digitalWrite(row[i],LOW);
	}
	for(int i = 0; i < 5; i++){
		digitalWrite(col[i],HIGH);
	}

	// set ONE column at display to LOW
	columnsDisplay();

	// set certain rows in the current column to HIGH
	rowsDisplay();

	//after waiting for a certain length of time (=interval/numColumnsOn),
	//proceed to the next column 
	if(millis() - accumulator > interval/numColumnsOn) { 
		accumulator += interval/numColumnsOn;
		k = k + 1;
	}

	//reset k to 0 after one cycle
	if (k+1 > numColumnsOn){
		k = 0;
	}

}

void columnsDisplay(){
	for(int i = 0; i < 5; i++){
		if(i==columnsOn[k]){
			digitalWrite(col[i],LOW);
		}
		else{
			digitalWrite(col[i],HIGH);
		}
	}
}

void rowsDisplay(){
	for(int j = 0; j < 7; j++){
		if(led[columnsOn[k]][j] == 1){
			digitalWrite(row[j], HIGH);
		}
		else{
			digitalWrite(row[j],LOW);
		}
	}
}