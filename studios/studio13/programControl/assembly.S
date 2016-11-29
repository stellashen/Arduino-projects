#include <avr/io.h>

.global greaterThan
greaterThan:
ldi r18,0
cp r22,r24
// r24: 4; r22: 6 — values in test 1
// r24 > r22 is equivalent to r22 < r24
//according to p21 of the manual: conditional branch summary table
// check if r22 >= r24
brge greateq
// excute the next line only if condition is met
// return 1 if r22 < r24
ldi r18,1
greateq:
// the next line will excute either way
// return 0 if r22 >= r24
mov r24,r18
  ret

.global slowMultiply
slowMultiply:
//sum = 0
ldi r18,0
//counter = 0
ldi r19,0
//store 1 in r20 to be used later
ldi r20,1
//compare counter (r19) and int a (r24)
loop:
cp r19,r24
brge exit
// if counter < a
// sum+ = b (b is in r22)
add r18,r22
// counter++
add r19,r20
// jump to the beginning of the loop
jmp loop
exit:
//copy the value in r18 into r24 to be returned
mov r24,r18
  ret

.global slowExponent
slowExponent:
//To see which registers are used for char
  //call printRegs
//same with the previous functions — r24 and r22

//sum = 1
ldi r18,1
//i = 0
ldi r19,0
//store 1
ldi r27,1
bigLoop:
//compare i and power
cp r19,r22
brge exitLoop
  //innersum = 0
  ldi r20,0
  //j=0
  ldi r21,0
  innerLoop:
  //compare j and a
  cp r21,r24
  brge exitInnerLoop
  add r20,r18
  add r21,r27
  jmp innerLoop
  exitInnerLoop:
  mov r18,r20
  add r19,r27
  jmp bigLoop
exitLoop:
mov r24,r18
  ret
