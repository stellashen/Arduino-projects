#include"MorseCodes.h"

const int led = 13;
int timeUnit = 1000;//testing
//int timeUnit = 500;
unsigned long accumulator = 0;
int count = 0;
String words = "";
bool first = true;

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
void convertIncomingCharsToMorseCode() {
	// TODO
	while(Serial.available() > 0){
		first = true;
		char ch = Serial.read();
		words = words + toUpper(ch);
		//array of accumulator reading at the start point of each round
	}
	// Serial.print(words);
	if(count<words.length()){
		/*Consider: How long does this letter take in total? 
		 * Total = 
		 * wait time between letters, 
		 *           which is numUnits = 3 or 7 (or 0, for the 0th letter only)
		 * + wait time between codes of this letter, 
		 *           which is 1 unit*(letter.length()-1)
		 * + time to process dash and dot, 
		 *           which is 1 unit * number of dots + 3 units * number of dashes
		 *           
		 * Therefore, do step1 & step2.
		 */
		String letter = morseEncode(words[count]);

		//Step1. get the time between letters
		int numUnits = 0;
		//special case: no wait for the 0th letter
		if(count==0){
			numUnits = 0;
		}
		else{
			// ' ' indicates: between words
			// wait 7 units instead
			if(words[count]==' '){
				numUnits = 7; 
			}
			else{
				numUnits = 3;
			}
		}

		//Step2. add other time
		//get the number of dot and dash in the morse codes of this letter
		int numDot = 0;
		int numDash = 0;
		for (int i = 0; i < letter.length(); i++){
			char m = letter[i];
			if(m=='.'){
				numDot = numDot+1;
			}
			if(m=='-'){
				numDash = numDash+1;
			}
		}

		// update the total time

		numUnits = numUnits + letter.length() - 1 + numDot + 3*numDash;

		if (count==0 && first==true){
			// only do this for the first time: set accumulator to the start time
			accumulator = millis();
			first = false;

			//testing
			Serial.println("Start");
			Serial.print("accumulator:");
			Serial.println(accumulator);
			Serial.println("End");

			ledBlinking(accumulator,letter);
		}

		// go to the next letter only after "the total time" used to process this letter
		if(millis() - accumulator >= numUnits*timeUnit){
			accumulator += numUnits*timeUnit;

			//testing results show the accumulator reading 
			//...after processing the letter on round count (starting from 0)
			Serial.println(words[count]);
			Serial.println(letter);
			Serial.print("accumulator:");
			Serial.println(accumulator);
			Serial.print("count: ");
			Serial.println(count);
			Serial.println("End");

			count = count + 1;

			ledBlinking(accumulator,letter);
		}
	}
}

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
}
	//	while (j < morseCodesForLetter.length()){
	//		// "time < startTime" ensures that we set time to startTime *only once* for each letter
	//		if(millis() - accumulator >= startTime && time < startTime){
	//			time = startTime;
	//			digitalWrite(led,HIGH);
	//		}
	//		//case1
	//		if(morseCodesForLetter[j]=='.'){
	//			// LED set to LOW after 1 time unit
	//			if(millis() - accumulator >= time+timeUnit){
	//				time += timeUnit;
	//				digitalWrite(led,LOW);
	//			}
	//			// go to the next code after adding 1 time unit between codes
	//			if(millis() - accumulator >= time+timeUnit){
	//				time += 2*timeUnit;
	//				j=j+1;
	//			}
	//		}
	//		//case2
	//		if(morseCodesForLetter[j]=='-'){
	//			if(millis() - accumulator >= time && millis() - accumulator < time+3*timeUnit){
	//				time += 3*timeUnit;
	//				digitalWrite(led,HIGH);
	//			}
	//			// go to the next code after adding 1 time unit between codes
	//			if(millis() - accumulator >= time+timeUnit && millis() - accumulator < time+timeUnit){
	//				time += timeUnit;
	//				j=j+1;
	//			}
	//		}
	//
	//	}
	//	else{
	//		j=0; //reset to 0 for the next letter
	//	}



void loop() {
	// No Need to Modify this.  Put most of your code in "convertIncomingCharsToMorseCode()"
	convertIncomingCharsToMorseCode();
}
