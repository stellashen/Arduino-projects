#include"MorseCodes.h"

const int led = 13;
int timeUnit = 2000;//slow testing
//int timeUnit = 500;
unsigned long accumulator = 0;

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
	String words = "";
	while(Serial.available() > 0){
		char ch = Serial.read();
		words = words + toUpper(ch);
	}
	// Serial.print(words);
	for(int i=0;i<words.length();i++){
		String letter = morseEncode(words[i]);
		//***print for testing****
		//		Serial.print("The morse code for ");
		//		Serial.print(words[i]);
		//		Serial.print(" is ");
		//		Serial.println(letter);

		Serial.print(letter);

		// ' ' indicates: between words		
		if(words[i]==' '){
			if(millis() - accumulator > 4*timeUnit){
				accumulator += 4*timeUnit; 
				digitalWrite(led,LOW);
				ledBlink(words[i]);
			}
		}
		else {
			ledBlink(words[i]);
		}

	}
}

// added this function to make led blink
void ledBlink(String s){
	for(int j=0; j<s.length();j++){
		//***print for testing****
		//			Serial.print("Code");
		//			Serial.print(j);
		//			Serial.print(" is ");
		//			Serial.println(letter[i]);

		// 1 unit between the codes within the same letter
		if(millis() - accumulator > timeUnit){
			accumulator += timeUnit; 
			if(letter[i]=='.'){
				digitalWrite(led, HIGH);
				if(millis() - accumulator > timeUnit) { 
					accumulator += timeUnit; 
					digitalWrite(led, LOW);
				}
			}
			if(letter[i]=='-'){
				digitalWrite(led, HIGH);
				if(millis() - accumulator > 3*timeUnit) { 
					accumulator += 3*timeUnit; 
					digitalWrite(led, LOW);
				}
			}
			digitalWrite(led, LOW);
		}
		//two more units between the codes for two letters
		if(millis() - accumulator > 2*timeUnit){
			accumulator += 2*timeUnit; 
			digitalWrite(led, LOW);
		}
	}
}

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
