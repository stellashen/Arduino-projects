#include <avr/io.h>

; AVR assembly comments start with a semicolon 
// (or a double slash, like C)
; Lines without labels should be indented once.

.global giveMeMax
giveMeMax:
//  ldi r24, 1 // Load the value 1 into register 24
  ldi r24, 128 // Load the value 128 into register 24
  ret

 // Define further "functions" below:
 // .global functionName
 // functionName:
 //   *code*
 //   ret

 .global giveMeZero
 giveMeZero:
 call printRegs
   ldi r24, 0
 call printRegs
   ret

 .global addFour
 addFour:
   ldi r23, 4
   add r24, r23
//   adc r24, r23
 call printRegs
   ret

.global turnOnLight
turnOnLight:
sbi _SFR_IO_ADDR(DDRB),PIN5
sbi _SFR_IO_ADDR(PORTB),1
//cbi PORTB,
ret
