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
			
			count = count + 1;
		}
	}

	//	for (int i=0; i<words.length(); i++){
	//		String letter = morseEncode(words[i]);
	//		//***print for testing****
	//		Serial.print("The morse code for ");
	//		Serial.print(words[i]);
	//		Serial.print(" is ");
	//		Serial.println(letter);

	//		Serial.print(letter);

	//		// ' ' indicates: between words		
	//		if(words[i]==' '){
	//			digitalWrite(led,LOW);
	//			if(millis() - accumulator > 4*timeUnit){
	//				Serial.println(millis());
	//				accumulator += 4*timeUnit; 
	//				ledBlink(letter);
	//			}
	//		}
	//		else {
	//			ledBlink(letter);
	//			digitalWrite(led, LOW);
	//			//two more units between the codes for two letters
	//		}
	//		

}

// added this function to make led blink
//void ledBlink(String letter){
//	for(int j=0; j<letter.length();j++){
//		//***print for testing****
//		Serial.print("Code");
//		Serial.print(j);
//		Serial.print(" is ");
//		Serial.println(letter[j]);
//
//		digitalWrite(led, HIGH);
//
//		if(letter[j]=='.'){
//			if(millis() - accumulator > timeUnit) { 
//				accumulator += timeUnit; 
//				digitalWrite(led, LOW);
//			}
//		}
//		if(letter[j]=='-'){
//			if(millis() - accumulator > 3*timeUnit) { 
//				accumulator += 3*timeUnit; 
//				digitalWrite(led, LOW);
//			}
//		}
//		// 1 unit between the codes within the same letter
//		if(millis() - accumulator > timeUnit) { 
//			accumulator += timeUnit; 
//		}
//	}
//}

/*
 * print testing output:
The morse code for H is ....
Code0 is .
Code1 is .
Code2 is .
Code3 is .
 * 
 */

void loop() {
	// No Need to Modify this.  Put most of your code in "convertIncomingCharsToMorseCode()"
	convertIncomingCharsToMorseCode();

	// test toUpper()
	//  char trya = 'a';
	//  char tryB = 'B';
	//  char try0 = '0';
	//  char tryOther = '!';
	//  Serial.println(toUpper(trya));
	//  Serial.println(toUpper(tryB));
	//  Serial.println(toUpper(try0));
	//  Serial.println(toUpper(tryOther));

}
