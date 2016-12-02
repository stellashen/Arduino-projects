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
push r30
push r31
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
pop r30
pop r31
pop r10
pop r11
ret

.global avgArray
avgArray:
push r2
push r3
//store the length of array in call-saved register r2
mov r2,r22
call sumArray
//return 16-bit value in r24,r25
mov r22,r2
call divide

//store the higher byte (after left shift 7 times) in r3
// e.g. original r25: 0000 0001 ; r3: 1000 0000
lsl r25
lsl r25
lsl r25
lsl r25
lsl r25
lsl r25
lsl r25
mov r3,r25

//divide lower byte
call divide
mov r4,r24

//divide higher byte
mov r24,r3
call divide
//multiply by 10
ldi r20,2
mul r24,r20
add r24,r4
ldi r18,0
adc r25,r18
pop r2
pop r3
ret

.global dot
dot:
ret
