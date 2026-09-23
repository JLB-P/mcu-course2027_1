;
; testarduino.asm
;
; Created: 3/30/2021 11:22:04 PM
; Author : jlb
;

; Replace with your application code
setup:
    ldi r16, 0b00000101 ; Set r16 with prescaler 1024 value
    out TCCR0B, r16     ; Set the TCCROB to 1024
    ldi r16, 0b00100000 ; Set r16 to the LED bit
    out DDRB, r16       ; Set LED pin to output
    clr r18             ; Clear the saved timer
loop:
    ldi r20, 5         ; Initialize our software counter
check_timer:
    in r17, TCNT0       ; Read the timer
    cp r17, r18         ; Compare with previous value
    mov r18, r17        ; Save current value
    brsh check_timer    ; unless the timer has decreased, repeat
decrement:
    dec r20             ; decrement the software counter
    brne check_timer    ; if not zero, go back to checking the timer
toggle:
    out PINB, r16       ; toggle the LED
    rjmp loop