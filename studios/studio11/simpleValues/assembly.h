// Function prototypes for assembly file.

// Extern "C" prevents C++ name-mangling, so we're guaranteed that our compiled
// code will look for the correct label in assembly when we call these
// functions elsewhere. Otherwise, the compiler might rewrite the function
// names and expect assembly code with a label for, say, `_ZxEgiveMeMax32`, not
// `giveMeMax`.
extern "C" {
  byte giveMeMax(void);
  byte giveMeZero(void);
  byte addFour(byte a);
  void turnOnLight(void);
}
