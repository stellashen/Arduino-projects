// reference: println():
// https://www.arduino.cc/en/Serial/Println

void setup() {
	Serial.begin(9600);
	pinMode(11,OUTPUT);
	pinMode(10,OUTPUT);
	pinMode(9,OUTPUT);
	pinMode(8,OUTPUT);
}

//5.1 Reading from Serial Port
//char myVar = 0;

//5.2 Displaying on LEDs
int myVar=0;
int decVar=100;

void loop() {
	//5.1 Reading from Serial Port
	//	if(Serial.available() > 0){
	//		myVar = Serial.read();
	//		Serial.println(myVar);
	//	}

	//5.2 Displaying on LEDs
	//convert ASCII to decimal
	if(Serial.available() > 0){
		myVar = Serial.read();
		// ASCII 0 is decimal 48, ASCII 9 is decmial 57
		// ASCII A is decimal 65, Z is 90
		// a is 97, z is 122

		//convert 0 to 0... 9 to 9
		if (myVar >= 48 && myVar <= 57){
			decVar = myVar - 48;
		}
		//convert A to 10, B to 11,..., Z to 35 
		if (myVar >= 65 && myVar <= 90 ){
			decVar = myVar - 55;
		}
		//convert a to 36, b to 37,...,z to 61
		if (myVar >= 97 && myVar <=122) {
			decVar = myVar - 61;
		}
		// print only when the input is valid(letter or number)
		if (decVar >= 0 && decVar <=61){
			//Serial.println(decVar);
			Serial.println(myVar);
		}

		//set back to default (because this is a loop)
		//or it will always be valid (taking the previous value)
		decVar = 100;
	}
}
