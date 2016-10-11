#include"MorseCodes.h"

const int led = 13;
int timeUnit = 1000;//slow testing
//int timeUnit = 500;
unsigned long accumulator = 0;
int count = 0;
String words = "";
int letterCount = 0;

// Argument: Any character
// Return Value: Either:
//                  1) If the character is a letter, the upper case equivalent.  
//                  2) If the character is not a letter, the original value.
char toUpper(char c) {
	// TODO
	// c is a-z
	if (c>=97 && c<=122){
		return (char)(c-32);
	}
	// c is A-Z or not a letter
	else {
		return c;
	}
}

void setup() {
	Serial.begin(9600);
	pinMode(led, OUTPUT);
}


void convertIncomingCharsToMorseCode() {
	// TODO
	while(Serial.available() > 0){
		char ch = Serial.read();
		words = words + toUpper(ch);
	}
	// Serial.print(words);
	int numUnits = 3;
	if(count<words.length()){
		// ' ' indicates: between words
		if(words[count]==' '){
			numUnits = 7;
		}
		if(count==0){
			numUnits = 0;
		}
		// no wait for the 0th word
		// if it's between words, wait 7 units; else, wait 3 units
		if(millis() - accumulator >= numUnits*timeUnit){
			if (count==0){
				accumulator = millis();
			}
			accumulator += numUnits*timeUnit;

			//testing code for delta timing
			Serial.println(millis()); 
			Serial.println(words[count]);

			String letter = morseEncode(words[count]);
			Serial.println(letter);

			//start of one letter: go through morse codes of this letter
			if(letterCount<letter.length()){
				// 1 unit between the same letter's codes
				if(millis() - accumulator >= timeUnit){
					accumulator += timeUnit;

					Serial.print("start time: ");
					Serial.println(millis());

					char m = letter[letterCount];
					// if m==' ', do nothing
					if (m=='.'){
						//light LED for 1 unit
						digitalWrite(led,HIGH);
						if(millis() - accumulator >= timeUnit){
							accumulator += timeUnit;
							digitalWrite(led,LOW);
							Serial.print("end time: ");
							Serial.println(millis());
						}
					}
					if (m=="-"){
						//light LED for 3 units
						digitalWrite(led,HIGH);
						if(millis() - accumulator >= 3*timeUnit){
							accumulator += 3*timeUnit;
							digitalWrite(led,LOW);
							Serial.print("end time: ");
							Serial.println(millis());
						}
					}

					letterCount = letterCount + 1;
				}
			}
			else{
				letterCount = 0; //reset letterCount to 0 for processing the next letter
			}
			//end of one letter
			count = count + 1;
		}
	}


void loop() {
	// No Need to Modify this.  Put most of your code in "convertIncomingCharsToMorseCode()"
	convertIncomingCharsToMorseCode();
}
