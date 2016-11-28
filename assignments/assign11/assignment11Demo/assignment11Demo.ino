#include "assignment11.h"

byte test(byte a, byte b) {
  byte c = 15;
  return a+b+c;
}

void setup() {
  int8_t a,b;  // Signed 8-bit ints
  
  Serial.begin(9600);
  Serial.println("Starting program...");

  Serial.print("Should be true: ");
  Serial.println(hasAOne(7));

  Serial.print("Should be false: ");
  Serial.println(hasAOne(0));

  for (int i = 0; i < 10; i ++)
  {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(intToAscii(i));
  }
//
//  Serial.print("Should be 12: ");
//  Serial.println(byteToInt(12));
//  Serial.print("Should be -12: ");
//  Serial.println(byteToInt(-12));
//  Serial.print("Should be 12: ");
//  Serial.println(byteToInt(12));
//
//  a = 122; b = 123;
//  Serial.print("Should be 245: ");  
//  Serial.println(addBytes(a, b));
//
//  a = 127; b=127;
//  Serial.print("Should be 254: ");  
//  Serial.println(addBytes(a, b));
//
//  a = -1; b=-1;
//  Serial.print("Should be -2: ");   
//  Serial.println(addBytes(a, b));
//
//
//  Serial.print("Should be 3: ");
//  Serial.println(average(2, 4));
//
//  Serial.print("Should be 10: ");
//  Serial.println(average(5, 16));
//  
//  Serial.print("Should be 64: ");
//  Serial.println(average(69, 60));
//
//  Serial.print("Should be -12: ");
//  Serial.println(average(431, 57));

  Serial.println("Ended setup!");
}

void loop() { /* unused */ }
