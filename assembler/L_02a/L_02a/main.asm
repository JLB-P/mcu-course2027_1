;
; L_02a.asm
;
; Created: 6/25/2021 1:50:16 PM
; Author : jlb
;
/*
	programa que genera números y los deposita en una área de memoria
*/

;Inicio de variables (RAM)
.dseg
.org 0x0100
tabla_aleatoria:	.byte	100 ;Reserva 100 bytes para esta variable
tabla_ordenada:		.byte	100 ;Reserva 100 bytes

; Inicia segmento de programa (FLASH)
.cseg
.org 0x0

;Inicia Stack
	ldi r16,high(RAMEND)
	out SPH,r16
	ldi r16,low(RAMEND)
	out SPL,r16		;I/O Direct Addressing
//Programa principal
start:
	rcall genera_numeros 
	//rcall ordena_numeros
	rjmp start

//Subrutinas
genera_numeros:
	ldi XH,high(tabla_aleatoria)
	ldi XL,low(tabla_aleatoria)
	ldi r16,5	;numero inicial
	ldi r18,20	;lo hace 20 veces
ciclo:
	ldi r17,2
	add r16,r17
	st X+,r16
	dec r18
	brne ciclo
	ret