/*
   FSM assignment
 */

#include <Arduino.h>
#include <Wire.h>

enum State {
	// bit 3, bit 2, bit 1
	up0,        // 000
	up1,        // 100
	up2,        // 010
	up3,        // 110
	up4,        // 001
	up5,        // 101
	up6,        // 011
	up7,        // 111
	// Reverse circle 8 - 15
	up8,        // reverse to up6: 011
	up9,        // reverse to up7: 111
	up10,       // reverse to up0: 000
	up11,       // reverse to up1: 100
	up12,       // reverse to up2: 010
	up13,       // reverse to up3: 110
	up14,       // reverse to up4: 001
	up15,       // reverse to up5: 101
};

State counterState = up0; // current state

bool bit1;
bool bit2;
bool bit3;

void setup() {
	Serial.begin(9600);
}

void loop() {
	counterState = nextState(counterState);
	delay(1000);
}


State nextState(State state){
	switch (state) {
	case up0:             

		bit1 = 0;        
		bit2 = 0;
		bit3 = 0;

		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print(state);
			pprint(state);
			state = up9;
		}
		else {
			Serial.print(state);
			pprint(state);
			state = up1;
		}

		break;                       

	case up1:              
		bit1 = 1;
		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print(state);
			pprint(state);
			state = up10;
		}
		else {
			Serial.print(state);
			pprint(state);
			state = up2;
		}
		break;

	case up2:
		bit1 = 0;
		bit2 = 1;
		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print(state);
			pprint(state);
			state = up11;
		}
		else {
			Serial.print(state);
			pprint(state);
			state = up3;
		}
		break;

	case up3:
		bit1 = 1;
		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print(state);
			pprint(state);
			state = up12;
		}
		else {
			Serial.print(state);
			pprint(state);
			state = up4;
		}
		break;

	case up4:
		bit1 = 0;
		bit2 = 0;
		bit3 = 1;
		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print(state);
			pprint(state);
			state = up13;
		}
		else {
			Serial.print(state);
			pprint(state);
			state = up5;
		}
		break;

	case up5:
		bit1 = 1;
		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print(state);
			pprint(state);
			state = up14;
		}
		else {
			Serial.print(state);
			pprint(state);
			state = up6;
		}
		break;

	case up6:
		bit1 = 0;
		bit2 = 1;
		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print(state);
			pprint(state);
			state = up15;
		}
		else {
			Serial.print(state);
			pprint(state);
			state = up7;
		}
		break;

	case up7:
		bit1 = 1;
		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print(state);
			pprint(state);
			state = up8;
		}
		else {
			Serial.print(state);
			pprint(state);
			state = up0;
		}
		break;

	case up8:
		bit1 = 0;
		bit2 = 1;
		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print("6");
			pprint(state);
			state = up7;
		}
		else {
			Serial.print("6");
			pprint(state);
			state = up15;
		}
		break;

	case up9:
		bit1 = 1;

		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print("7");
			pprint(state);
			state = up0;
		}
		else {
			Serial.print("7");
			pprint(state);
			state = up8;
		}
		break;

	case up10:             

		bit1 = 0;        
		bit2 = 0;
		bit3 = 0;

		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print("0");
			pprint(state);
			state = up1;
		}
		else {
			Serial.print("0");
			pprint(state);
			state = up9;
		}

		break;                       

	case up11:              
		bit1 = 1;

		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print("1");
			pprint(state);
			state = up2;
		}
		else {
			Serial.print("1");
			pprint(state);
			state = up10;
		}
		break;

	case up12:
		bit1 = 0;
		bit2 = 1;
		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print("2");
			pprint(state);
			state = up3;
		}
		else {
			Serial.print("2");
			pprint(state);
			state = up11;
		}
		break;

	case up13:
		bit1 = 1;
		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print("3");
			pprint(state);
			state = up4;
		}
		else {
			Serial.print("3");
			pprint(state);
			state = up12;
		}
		break;

	case up14:
		bit1 = 0;
		bit2 = 0;
		bit3 = 1;		
		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print("4");
			pprint(state);
			state = up5;
		}
		else {
			Serial.print("4");
			pprint(state);
			state = up13;
		}
		break;

	case up15:
		bit1 = 1;
		if (checkReverse()){
			Serial.println("--Reverse--");
			Serial.print("5");
			pprint(state);
			state = up6;
		}
		else {
			Serial.print("5");
			pprint(state);
			state = up14;
		}
		break;

	}

	return state;
}

bool checkReverse(){
	int incomingByte = 0;
	if (Serial.available() > 0) {
		incomingByte = Serial.read();
	}

	if (incomingByte > 0){
		return true;
	}

	return false;
}

void pprint(State state) {
	Serial.print("  :  ");
	Serial.print(bit3);
	Serial.print(bit2);
	Serial.println(bit1);
}




