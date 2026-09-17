;
; freq_gen.asm
;
; Created: 9/7/2026 4:43:10 PM
; Author : josel
;
.cseg
.org 0x00	;Origen del código
.def temp = r16
.def counter = r17
.def multiplier = r18

;Programa principal
	;Inicia Stack
	ldi temp,high(RAMEND) ;Obtiene byte alto
	out SPH,Temp
	ldi temp,low(RAMEND) ;Obtiene byte bajo
	out SPL,Temp

	//PB3,PB4 entrada y PB5 salida
	ldi temp,0b1110_0111 
	out DDRB,Temp
start:
	in temp,PINB
	cpi temp,0
	brne freq2
	ldi counter,20  ;Frecuencia 1
	rcall on_off
	jmp start
freq2:
	ldi counter,50  ;Frecuencia 2
	rcall on_off
	jmp start

;Subrutinas
/****************************************
* Rutina para encender y apagar el bit0.
* Entrada: ninguna
* Salida: ninguna
*****************************************/
on_off:
	sbi PORTB,PB5 ;Enciende bit
	rcall delay ;Espera
	cbi PORTB,PB5 ;Apaga bit
	rcall delay ;Espera
	ret

/****************************************
* Rutina de retardo, dado por counter y
* el valor definido en temp.
* Entrada: counter, temp
* Salida: retardo= counter x temp
*****************************************/
delay:
		push counter
c2:		ldi temp,167
c1:		dec temp
		brne c1
		dec counter 
		brne c2
		pop counter
		ret