void setup() {
  
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  //Test:
  Serial.println();
  Serial.print("shiftRight(5,1) should return 2:          ");
  Serial.println(shiftRight(5,1));
  Serial.print("shiftRight(7,4) should return 0:          ");
  Serial.println(shiftRight(7,4));

  Serial.println();
  Serial.print("shiftLeft(5,2) should return 20:          ");
  Serial.println(shiftLeft(5,2));
  Serial.print("shiftLeft(-1,1) should return -2:        ");
  Serial.println(shiftLeft(-1,1));

  Serial.println();
  Serial.print("hasAOne(4) should return 1:               ");
  Serial.println(hasAOne(4));
  Serial.print("hasAOne(0) should return 0:               ");
  Serial.println(hasAOne(0));

  Serial.println();
  Serial.print("hasAZero(5) should return 1:              ");
  Serial.println(hasAZero(5));
  Serial.print("hasAZero(-1) should return 0:             ");
  Serial.println(hasAZero(-1));
    
  Serial.println();
  Serial.print("leastSigHasAOne(255) should return 1:     ");
  Serial.println(leastSigHasAOne(255));
  Serial.print("leastSigHasAOne(256) should return 0:     ");
  Serial.println(leastSigHasAOne(256));

  Serial.println();
  Serial.print("isNegativeInt(-500) should return 1:      ");
  Serial.println(isNegativeInt(-500));
  Serial.print("isNegativeInt(500) should return 0:       ");
  Serial.println(isNegativeInt(500));

  Serial.println();
  Serial.print("isNegativeLong(-40000) should return 1:   ");
  Serial.println(isNegativeLong(-40000));
  Serial.print("isNegativeLong(40000) should return 0:    ");
  Serial.println(isNegativeLong(40000));

  Serial.println();
  Serial.print("isNegativeChar(-5) should return 1:       ");
  Serial.println(isNegativeChar(-5));
  Serial.print("isNegativeChar(1) should return 0:        ");
  Serial.println(isNegativeChar(1));

  Serial.println();
  Serial.print("negate(-500) should return 500:           ");
  Serial.println(negate(-500));
  Serial.print("negate(500) should return -500:          ");
  Serial.println(negate(500));


}

//
int shiftRight(int num, int n){
  num = num >> n;
  return num;
}

int shiftLeft(int num, int n){
  num = num << n;
  return num;
}

// Fix the following functions, using only the bitwise and Boolean operators
int hasAOne(int num) {
  // a number has at least a 1 when it is not 0
  int isZero = !num;
  int isOne = !isZero;
  return isOne;
}

int hasAZero(int num) {
  int notNum = ~num; // 0 becomes 1, 1 becomes 0
  int hasZero = hasAOne(notNum); 
  return hasZero;
}

int leastSigHasAOne(int num) {
  // 1 byte has 8 bits
  int isOne = num & 0b11111111; // 0b marks it as binary number
  int hasOne = hasAOne(isOne);
  return hasOne;
}

int isNegativeInt(int num) {
  // - 1 stored as signed binary value: 1111111111111111 (16 bits) 
  // -2: 1111111111111110
  // -3: 1111111111111101
  // -32768: 1000000000000000
  // 1: 1    -1 = (~1: 1111....0) +1
  // 2: 10   -2 = (~2: 111....01) +1
  // 3: 11
  // 32767: (0)111111111111111 (15 bits)
  // int negSign = num & 1000000000000000; // if it's positive number, the 16th bit is not 1, it returns 0; if it's negative, it returns 1000000000000000
  int negSign = num & -32768;
  int isPositive = !negSign;
  int isNegative = !isPositive;
  return isNegative;
}

int isNegativeLong(long num) {
  // long negSign = num & 10000000000000000000000000000000;
  long negSign = num & -2147483648; // notice: use long data type here
  int isPositive = !negSign;
  int isNegative = !isPositive;
  return isNegative;
}

int isNegativeChar(char num) {
  // int negSign = num & 10000000;
  int negSign = num & -128;
  int isPositive = !negSign;
  int isNegative = !isPositive;
  return isNegative;
}

int negate(int num) {
  int negNum = ~ num + 1;
  return negNum;
}

