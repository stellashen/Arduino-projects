#include <avr/io.h>

//When need to check values in registers, insert this line of code:
//call printRegs

.global hasAOne
hasAOne:
//copy the parameter value from r24 to r19
mov r19, r24
//set r24 to 0
ldi r24,0
//compare if r19 is 0
ldi r18, 0
cpse r19, r18
ldi r24, 1
ret

.global intToAscii
intToAscii:
ldi r18, 48
add r24, r18
ret

.global byteToInt
byteToInt:
//copy the original value from r24 to r20
mov r20, r24
//shift right for seven times
lsr r20
lsr r20
lsr r20
lsr r20
lsr r20
lsr r20
lsr r20
//if negative, value = 00000001; if positive, value = 00000000

//binary 10000000 = dec -128; 01111111 = 127
//value range [-128,127]
//1111 1111 0000 0000 = -256 < -128
//if it's negative, the higher byte must be 1111 1111 (signed binary) = -1
//if it's positve, the higher byte must be 0

ldi r22,0
sub r22,r20
//load it to r25 (higher byte)
mov r25,r22

//if it's positive, lower byte is the original value
//if it's negative, lower byte is the original value
//1111 1111 1000 0000 = -128
//1111 1111 1000 0001 = -127
//so no need to change r24
ret

//a: r24
//b: r22
.global addBytes
addBytes:
//store b in r17
push r17
mov r17,r22
call byteToInt
//get 16-bit for a (r24,r25), and save it to call-saved register r2 and r3
push r2
push r3
mov r2, r24
mov r3, r25

//move b to r24
mov r24,r17
call byteToInt
push r4
push r5
mov r4, r24
mov r5, r25

//add lower bytes of a and b together
add r2,r4
//use adc to make sure it's fine if lower bytes sum overflows
adc r3,r5

//copy lower byte to r24, higher byte to r25
mov r24,r2
mov r25,r3

//push call-saved registers before subroutine, pop call-saved registers after subroutine
//Alternative: push and pop call-used registers within the subroutine
pop r2
pop r3
pop r4
pop r5
pop r17
ret

.global average
average:
call addBytes
//divide by 2 (the signed bit doesn't change under asr)
asr r25
//with carry
ror r24
ret
