/*
   Circuits Intro
*/

#include <Arduino.h>
#include <Wire.h>

enum State {
  up0,        // 0
  up1,        // 1
  up2,        // 2
  up3,        // 3
  up4,        // 4
  up5,        // 5
  up6,        // 6
  up7,        // 7
};

State counterState = up0; 

void setup() {
	pinMode(2,OUTPUT); 
	digitalWrite(2,LOW);
	pinMode(3,OUTPUT); 
    digitalWrite(3,LOW);
	pinMode(4,OUTPUT); 
	digitalWrite(4,LOW);
}

void loop() {
	counterState = nextState(counterState);
	delay(1000);
}

State nextState(State state) {
  switch (state) {
    case up0:               
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      state = up1;

      break;                       

    case up1:               
      digitalWrite(2,HIGH);
      state = up2;
      break;

    case up2:
      digitalWrite(2,LOW);
      digitalWrite(3,HIGH);
      state = up3;
      break;

    case up3:
      digitalWrite(2,HIGH);
      state = up4;
      break;

    case up4:
      digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,HIGH);
      state = up5;
      break;

    case up5:
      digitalWrite(2,HIGH);
      state = up6;
      break;

    case up6:
      digitalWrite(2,LOW);
      digitalWrite(3,HIGH);
      state = up7;
      break;

    case up7:
      digitalWrite(2,HIGH);
      state = up0;
      break;
  }
  return state;
}


