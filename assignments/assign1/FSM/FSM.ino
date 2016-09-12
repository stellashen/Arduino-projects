/*
   FSM assignment
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
  up8,
  up9,
  up10,
  up11,
  up12,
  up13,
  up14,
  up15,
};

State counterState = up0;

bool bit1;
bool bit2;
bool bit3;
bool bit4;
bool change;

void setup() {
  Serial.begin(9600);
}

void loop() {
  counterState = nextState(counterState);
  delay(1000);
}


State nextState(State state){
    switch (state) {
    case up0:               //When state up0 , the FSM must:

      bit1 = 0;        //set the bits to match the Count
      bit2 = 0;
      bit3 = 0;
      bit4 = 0;

      pprint(state);
  state = up1;

      break;                       //Break to the end of the switch
    //So the next case won't run

    case up1:               //only if counterState == up1
      bit1 = 1;
      pprint(state);
      state = up2;
      break;

    case up2:
      bit1 = 0;
      bit2 = 1;
      pprint(state);
      state = up3;
      break;

    case up3:
      bit1 = 1;
      pprint(state);
      state = up4;
      break;

    case up4:
      bit1 = 0;
      bit2 = 0;
      bit3 = 1;
      pprint(state);
      if (change==1){
        state = up3;
      }
      else {
      state = up5;
      }
      break;

    case up5:
      bit1 = 1;
      pprint(state);
      if (checkReverse()){
        state = up4;
      }
      else {
      state = up6;
      }
      break;

    case up6:
      bit1 = 0;
      bit2 = 1;
      pprint(state);
      if (checkReverse()){
        state = up5;
      }
      else {
      state = up7;
      }
      break;

    case up7:
      bit1 = 1;
      pprint(state);
      if (checkReverse()){
        state = up6;
      }
      else {
      state = up8;
      }
      break;

    case up8:
      bit1 = 0;
      bit2 = 0;
      bit3 = 0;
      bit4 = 1;
      pprint(state);
      if (checkReverse()){
        state = up7;
      }
      else {
      state = up9;
      }
      break;
    
    case up9:
      bit1 = 1;
      pprint(state);
      if (checkReverse()){
        state = up8;
      }
      else {
      state = up10;
      }
      break;

    case up10:
      bit1 = 0;
      bit2 = 1;
      pprint(state);
      state = up11;
      break;

    case up11:
      bit1 = 1;
      pprint(state);
      state = up12;
      break;

    case up12:
      bit1 = 0;
      bit2 = 0;
      bit3 = 1;
      pprint(state);
      state = up13;
      break;

    case up13:
      bit1 = 1;
      pprint(state);
      state = up14;
      break;

    case up14:
      bit1 = 0;
      bit2 = 1;
      pprint(state);
      state = up15;
      break;

    case up15:
      bit1 = 1;
      pprint(state);
      state = up0;
      break;
  }
  return state;
}

bool checkReverse(){
  if (Serial.read() != -1){
    return 1;
  }
  return 0;
}

void pprint(State state) {
  Serial.print(state);
  Serial.print("  :  ");
  Serial.print(bit4);
  Serial.print(bit3);
  Serial.print(bit2);
  Serial.println(bit1);
}


