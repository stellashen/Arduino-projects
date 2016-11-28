#include "assembly.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Starting program...");

  // Test the functions
  Serial.print("4 > 6? ");
  Serial.println((int) greaterThan(4, 6));
  Serial.print("12 > 2? ");
  Serial.println((int) greaterThan(12, 2));

  
  Serial.print("1 * 5 = ");
  Serial.print((int) slowMultiply(1, 5));
  Serial.print(" = ");
  Serial.println((int) slowMultiply(5, 1));

  Serial.print("0 * 3 = ");
  Serial.print((int) slowMultiply(0, 5));
  Serial.print(" = ");
  Serial.println((int) slowMultiply(3, 0));
  
  Serial.print("4 * 7 = ");
  Serial.print((int) slowMultiply(4, 7));
  Serial.print(" = ");
  Serial.println((int) slowMultiply(7, 4));

  Serial.print("15 * 3 = ");
  Serial.print((int) slowMultiply(15, 3));
  Serial.print(" = ");
  Serial.println((int) slowMultiply(3, 15));

  
  Serial.print("3 ^ 0 = ");
  Serial.println((int) slowExponent(3, 0));
  Serial.print("1 ^ 5 = ");
  Serial.println((int) slowExponent(1, 5));
  Serial.print("3 ^ 4 = ");
  Serial.println((int) slowExponent(3, 4));
  Serial.print("6 ^ 3 = ");
  Serial.println((byte) slowExponent(6, 3));

  // Makes sure you returned from all your functions:
  Serial.println("Ended setup!");
}

void loop() { /* unused */ }
