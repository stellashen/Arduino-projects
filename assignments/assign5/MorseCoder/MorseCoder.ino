#include"MorseCodes.h"

const int led = 13;

// Argument: Any character
// Return Value: Either:
//                  1) If the character is a letter, the upper case equivalent.  
//                  2) If the character is not a letter, the original value.
char toUpper(char c) {
  // TODO
}

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}


void convertIncomingCharsToMorseCode() {
  // TODO
}




void loop() {
  // No Need to Modify this.  Put most of your code in "convertIncomingCharsToMorseCode()"
  convertIncomingCharsToMorseCode();
}
