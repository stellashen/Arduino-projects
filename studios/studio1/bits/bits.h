unsigned shiftLeft(unsigned num){
  return num << 1;
}
unsigned shiftRight(unsigned num){
  return num >> 1;
}
unsigned invert(unsigned num){
  return ~num;
}

void pprint(char* title, unsigned num){
  Serial.println("-----------------------");
  Serial.println(title);
  Serial.print("  DEC:  ");
  Serial.println(num);
  Serial.print("  HEX:  ");
  Serial.println(String(num,HEX));
  Serial.print("  BIN:  ");
  Serial.println(String(num,BIN));
  Serial.println("-----------------------");
}

