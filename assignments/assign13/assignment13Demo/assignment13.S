#include <avr/io.h>
//Call-used registers (r18-r27, r30-r31)
//Call-saved registers (r2-r17, r28-r29)

.global divide
divide:
//x: r24; y: r22; unsigned numbers
//return the int result of x divided by y
ldi r18,0
ldi r19,1
subloop:
cp r24,r22
//branch if less than
brlt less
sub r24,r22
add r18,r19
jmp subloop
less:
mov r24,r18
ret

.global sumArray
sumArray:
push r10
push r11
ldi r27,1
ldi r26,0
ldi r20,0
mov r10,r20
mov r11,r20
//copy the 2-byte location (pointer) from r24,r25 to Z
mov r30,r24
mov r31,r25
//length of array is stored in r22

loadArray:
//load the value at the current index into r18
ld r18,Z
//store the sum in r10,r11
add r10,r18
adc r11,r26
//increment the pointer by 1
add r30,r27
adc r31,r26
//i=i+1
add r20,r27
//do jmp only when i < length of array
cp r20,r22
brge greateq
jmp loadArray

greateq:
//return 16-bit
mov r24,r10
mov r25,r11
pop r10
pop r11
ret


//avg of bytes should be a byte
.global avgArray
avgArray:
push r2
//store the length of array in call-saved register r2
mov r2,r22
call sumArray
//return 16-bit value in r24,r25 (unsigned bytes)
//divide this value by the length (stored in r2)
//call printRegs

//***slow divide
//use r18 and r19 as constants 0 and 1
//use r26 as the result of divide (avg of bytes is just one byte)
ldi r18,0
ldi r19,1
ldi r26,0

//the dividend is divided by the divisor to get a quotient
//slow divide a two-byte number by substracting
beginsub:
//exit if dividend (r25:r24) < divisor (length of array) (r18:r2)
//quotient would be r26
//compare two-byte numbers using cpc
cp r24,r2
cpc r25,r18
brlt exitsub
//if r24 < r2,exitsub; otherwise,procceed
//substract r18:r2 from r24:r25
//substract low byte
sub r24,r2
//substract high byte with carry
sbc r25,r18
//add 1 to the result of divide
add r26,r19
jmp beginsub
exitsub:

mov r24,r26
pop r2
ret

.global dot
dot:
//the first array location: r24,r25
//the second array location: r22,r23
//the third byte: r20 (length of array)
push r28
push r29
push r6
push r7
push r8
// r6: i
ldi r18,0
mov r6,r18
// r7: lower byte of sum of products
// r8: higher byte
mov r7,r18
mov r8,r18

//load location to Z
mov r30,r24
mov r31,r25
//load location to Y
mov r28,r22
mov r29,r23

useArray:
ld r18,Z
ld r19,Y

//multiply r19,r18; copy result back in r19:r18
//and then store the sum of products in r8:r7
mul r19,r18
movw r18,r0
add r7,r18
adc r8,r19

//use r26 and r27 as constant 0 and 1
ldi r26,0
ldi r27,1
//increment the pointer by 1
add r30,r27
adc r31,r26
add r28,r27
adc r29,r26
//i=i+1
add r6,r27
//do jmp only when i < length of array
cp r6,r20
brge finish
jmp useArray

finish:
mov r24,r7
mov r25,r8

pop r6
pop r7
pop r8
pop r28
pop r29
ret

