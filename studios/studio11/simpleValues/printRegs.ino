/* printRegs
* print out the contents of the registers
*/

/* temporary storage for register contents */
byte r[32];
byte s;

extern "C" {
  void printRegs();
}

void printRegs() {
// save registers 16 to 31 on the stack,
// then copy all registers into r[] and sreg
  asm volatile(
    "push r16 \n\t" "push r17 \n\t" "push r18 \n\t" "push r19 \n\t"
    "push r20 \n\t" "push r21 \n\t" "push r22 \n\t" "push r23 \n\t"
    "push r24 \n\t" "push r25 \n\t" "push r26 \n\t" "push r27 \n\t"
    "push r28 \n\t" "push r29 \n\t" "push r30 \n\t" "push r31 \n\t"
    "sts (r),r0 \n\t"     "sts (r+1),r1 \n\t"
    "sts (r+2),r2 \n\t"   "sts (r+3),r3 \n\t"
    "sts (r+4),r4 \n\t"   "sts (r+5),r5 \n\t"
    "sts (r+6),r6 \n\t"   "sts (r+7),r7 \n\t"
    "sts (r+8),r8 \n\t"   "sts (r+9),r9 \n\t"
    "sts (r+10),r10 \n\t" "sts (r+11),r11 \n\t"
    "sts (r+12),r12 \n\t" "sts (r+13),r13 \n\t"
    "sts (r+14),r14 \n\t" "sts (r+15),r15 \n\t"
    "sts (r+16),r16 \n\t" "sts (r+17),r17 \n\t"
    "sts (r+18),r18 \n\t" "sts (r+19),r19 \n\t"
    "sts (r+20),r20 \n\t" "sts (r+21),r21 \n\t"
    "sts (r+22),r22 \n\t" "sts (r+23),r23 \n\t"
    "sts (r+24),r24 \n\t" "sts (r+25),r25 \n\t"
    "sts (r+26),r26 \n\t" "sts (r+27),r27 \n\t"
    "sts (r+28),r28 \n\t" "sts (r+29),r29 \n\t"
    "sts (r+30),r30 \n\t" "sts (r+31),r31 \n\t"
    "in r16,0x3f \n\t" "sts (s),r16 \n\t"
    ::: "r16"
  );
  for (int i=0; i<32; i++) {
    Serial.print("r");
    if (i<10) {Serial.print(0);}
    Serial.print(i);
    Serial.print("=");
    Serial.print(r[i]>>4,HEX);
    Serial.print(r[i]&0x0f,HEX);
    if ((i+1)%8) {Serial.print(" ");}
    else {Serial.println("");}
  }
  Serial.print("sreg: C="); Serial.print(s&0x01);
  Serial.print(" Z="); Serial.print((s>>1)&0x01);
  Serial.print(" N="); Serial.print((s>>2)&0x01);
  Serial.print(" V="); Serial.print((s>>3)&0x01);
  Serial.print(" S="); Serial.print((s>>4)&0x01);
  Serial.print(" H="); Serial.print((s>>6)&0x01);
  Serial.print(" T="); Serial.print((s>>6)&0x01);
  Serial.print(" I="); Serial.println(s>>7);
  Serial.println("");
  //restore registers from the stack
  asm volatile(
    "lds r31,(s)\n\t" "out 0x3f,r31\n\t"
    "pop r31 \n\t" "pop r30 \n\t" "pop r29 \n\t" "pop r28 \n\t"
    "pop r27 \n\t" "pop r26 \n\t" "pop r25 \n\t" "pop r24 \n\t"
    "pop r23 \n\t" "pop r22 \n\t" "pop r21 \n\t" "pop r20 \n\t"
    "pop r19 \n\t" "pop r18 \n\t" "pop r17 \n\t" "pop r16 \n\t"
    :::
  );
}

