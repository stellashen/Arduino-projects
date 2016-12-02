#include "assignment13.h"

void setup() {

  Serial.begin(9600);

  byte a[] = {1, 2, 3};
  Serial.print("Should be 6: ");
  Serial.println(sumArray(a, 3));

  byte b[] = {50, 200, 100};
  Serial.print("Should be 350: ");
  Serial.println(sumArray(b, 3));

  byte c[] = {10, 2, 7, 4, 19, 80 , 72, 54, 96, 100};
  Serial.print("Should be 444: ");
  Serial.println(sumArray(c, 10));

  Serial.print("Should be 175: ");
  Serial.println(avgArray(b, 3));

  Serial.print("Should be 44: ");
  Serial.println(avgArray(c, 3));

  Serial.print("Should be 3: ");
  Serial.println(divide(21, 7));

  Serial.print("Should be 9: ");
  Serial.println(divide(95, 10));
//
//  byte d[] = {1, 2, 3};
//  byte e[] = {4, 5, 6};
//  Serial.print("Should be 32: ");
//  Serial.println(dot(d, e, 3));
//
//  byte f[] = {7, 20, 19, 11};
//  byte g[] = {132, 51, 0, 84, 30};
//  Serial.print("Should be 2988: ");
//  Serial.println(dot(f, g, 5));
}

void loop() { /* unused */ }
