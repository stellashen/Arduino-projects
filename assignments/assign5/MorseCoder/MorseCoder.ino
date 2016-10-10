#include"MorseCodes.h"

const int led = 13;

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
	// String words = incoming stream
	for(int i=0;i<words.length();i++){
	morseEncode(words[i]);
	}
}




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
