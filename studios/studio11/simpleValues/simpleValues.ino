#include "assembly.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Starting program...");

  // Run the assembly functions
  byte a = giveMeMax();
  //byte b = giveMeZero();

  // Print the results from the assembly functions
  Serial.print("a = ");
  Serial.println(a);
  //Serial.print("b = ");
  //Serial.println(b);

  /* add further code here */

  // Makes sure you returned from all your functions:
  Serial.println("Ended setup!");
}

void loop() { /* unused */ }
