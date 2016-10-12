#include"MorseCodes.h"

const int led = 13;
int timeUnit = 1000;//testing
//int timeUnit = 500;
unsigned long accumulator = 0;
int count = 0;
//bool first = true;
int i = 0;

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

/* 
 * This function reads user input such as "hi morse".
 * Designed to send user input (in the Serial Monitor, type something and click "send" button).
 * Because String word and int count are outside of this funciton, 
 *         this would work for sending a second, third,... input.
 */

// Assume words.length() <= 25
String words = "";
int w = 0;
int numDot = 0;
int numDash = 0;
int numUnitsWait[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int numUnitsWithinLetter[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int numUnitsStart[25] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int r = 1;
void convertIncomingCharsToMorseCode() {
	// TODO
	while(Serial.available() > 0){
		char ch = Serial.read();
		words = words + toUpper(ch);

		//set the initial start time
		accumulator = millis();
	}
	//Serial.println(words);

	while(w < words.length()){
		//Step1. get the wait time between letters
		numUnitsWait[w] = 3;
		// ' ' indicates: between words, wait 7 units instead
		if(words[w] == ' '){
			numUnitsWait[w] = 7; 
		}

		// morse codes for the wth letter in the String words
		String letterCodes = morseEncode(words[w]);
		//Step2. add other time
		//get the number of dot and dash in the morse codes of this letter
		numDot = 0;
		numDash = 0;
		for (int j = 0; j < letterCodes.length(); j++){
			char m = letterCodes[j];
			if(m=='.'){
				numDot = numDot+1;
			}
			if(m=='-'){
				numDash = numDash+1;
			}
		}
		numUnitsWithinLetter[w] = letterCodes.length() - 1 + numDot + 3*numDash;

		//testing
		Serial.println(letterCodes);
		Serial.print("wait time before letter:");
		Serial.print(words[w]);
		Serial.print(" is ");
		Serial.println(numUnitsWait[w]);
		Serial.print("time to process letter:");
		Serial.print(words[w]);
		Serial.print(" is ");
		Serial.println(numUnitsWithinLetter[w]);

		w = w + 1;
	}


	// round initial value is 1
	while (r < words.length()){
		numUnitsStart[0] = numUnitsWait[0];
		numUnitsStart[r] = numUnitsStart[r-1]+numUnitsWithinLetter[r-1]+numUnitsWait[r];
		Serial.println(numUnitsStart[r]);
		r = r + 1;
	}


	while (count < words.length()){

		//blinking start time
		unsigned long start = numUnitsStart[count]*timeUnit;
		// wait for 3 units before start
		if (count == 0){
			start = 3*timeUnit;
		}

		// no need to change accumulator, because numUnitsStart[count] is rolling
		if(millis() - accumulator >= numUnitsStart[count]*timeUnit){
			String letter = morseEncode(words[count]);
			
			//test
			Serial.println(words[count]);
			Serial.print("Start of led blinking for '");
			Serial.print(letter);
			Serial.println("':");
			Serial.print("Start time: ");
			Serial.println(start);
			
			if(words[count]!=' '){
				ledBlinking(start,letter);
			}
			count = count + 1;
		}
	}	 
}

/*Consider: How long does this letter take in total? 
 * Total = 
 * wait time between letters, 
 *           which is numUnits = 3 or 7 
 *   (*****this is the time to start led blinking****)
 * + wait time between codes of this letter, 
 *           which is 1 unit*(letter.length()-1)
 * + time to process dash and dot, 
 *           which is 1 unit * number of dots + 3 units * number of dashes
 * 
 *           
 * Therefore, do step1 & step2.
 */


//According to the MorseCodeTable, morse codes for any letter are not longer than 6 chars
//This array stores the correspondent time length of led HIGH for each morse code '.' or '-'
int codes[6] = {0,0,0,0,0,0}; 
// the time dot or dash takes (for up to 6 chars) + time intervals between codes (for up to 5 intervals) + the end (1)
unsigned long time[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
// the time[] array will store the following values:
// time[0]:time to start && read the 0th code (light on),
// time[1]=time[0]+timeUnit*codes[0]:time to start interval(light off), 
// time[2]=time[1]+timeUnit:time to read the 1th code (light on), 
// time[3]=time[2]+timeUnit*codes[1]:time to start interval(light off),...
//...time[11]=time[10]+timeUnit*codes[5]
int ledOn[11] = {1,0,1,0,1,0,1,0,1,0,1};
int m = 0;

void ledBlinking(unsigned long startTime, String morseCodesForLetter){
	int numCodes = morseCodesForLetter.length();
	for (int j = 0; j < numCodes; j++){
		if(morseCodesForLetter[j]=='.'){
			codes[j] = 1;
		}
		if(morseCodesForLetter[j]=='-'){
			codes[j] = 3;
		}
	}

	time[0] = startTime;
	for (int k = 1; k < 2*numCodes; k++){
		if(k % 2 == 0){
			time[k]=time[k-1]+timeUnit;
		}
		else{
			time[k]=time[k-1]+timeUnit*codes[k/2];
		}
	}

	//testing
	for (int j = 0; j < numCodes; j++){
		Serial.print("codes[");
		Serial.print(j);
		Serial.print("] = ");
		Serial.println(codes[j]);
	}
	for (int k = 0; k < 2*numCodes; k++){
		Serial.print("time[");
		Serial.print(k);
		Serial.print("] = ");
		Serial.print(time[k]);
		Serial.print("  LED:");
		Serial.println(ledOn[k]);
	}

	while (m < 2*numCodes){
		if(millis() - accumulator >= time[m]){
			digitalWrite(led,ledOn[m]);

			//testing
			Serial.print("m: ");
			Serial.print(m);
			Serial.print("      Time to turn on/off the LED: ");
			Serial.print(time[m]);
			Serial.print( "     LED: ");
			Serial.println(ledOn[m]);

			m=m+1;
		}
	}
	m=0;//reset to 0
}


void loop() {
	// No Need to Modify this.  Put most of your code in "convertIncomingCharsToMorseCode()"
	convertIncomingCharsToMorseCode();
}
