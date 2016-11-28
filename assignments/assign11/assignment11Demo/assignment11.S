#include <avr/io.h>

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
push r2
mov r2, r24
//binary 10000000 = dec -128
//binary 1000 0000 0000 0000 = dec -2^16 = -65536
//bitwise and: has 1 where both bits are 1
and r24, -128
//if negative, value = 10000000; if positive, value = 00000000
lsr r24
lsr r24
lsr r24
lsr r24
lsr r24
lsr r24
lsr r24
//if negative, value = 00000001; if positive, value = 00000000


//load it to r25 (higher byte)
lds r25, r24
//turn the first bit to 0, and load that value to r24 (lower byte)
lsl r2
lsr r2
lds r24,r2
pop r2
ret

.global addBytes
addBytes:
ret
.global average
average:
ret
