;
; test.asm
;
; Created: 9/4/2026 4:23:10 PM
; Author : josel
;


; Replace with your application code
	ldi r16,36
start:
    inc r16
	cpi r16,37
	breq subrout
    rjmp start

subrout:
	ldi r17, 48
	call delay

delay:
    inc r17
	cpi r17,50
	breq start
    rjmp delay
	ret
	
