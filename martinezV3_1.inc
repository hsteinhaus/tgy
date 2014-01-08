;***************************************************************
;* For Martinez 4fach ESC  V3             	                   *
;* bearbeitet von imcoref                                      *
;* https://github.com/sim-/tgy                                 *
;***************************************************************



.equ	F_CPU			= 16000000
.equ	USE_INT0		= 1
.equ	USE_I2C			= 0	
.equ	USE_UART		= 0
.equ	USE_ICP			= 0


;*********************

; PORT D definitions *

;*********************

;.equ					= 7
;.equ	sense_star 		= 6 ;	defaults to PD6
;.equ					= 5
.equ	statusLed		= 4 ;	green LED
.equ	warnLed			= 3 ;	red LED
.equ	rcp_in			= 2 ;	PPM input from FlightControl
;.equ					= 1
;.equ					= 0
.equ	INIT_PD			= 0
.equ	DIR_PD			= (1<<statusLed)+(1<<warnLed) 


.MACRO rcp_int_enable
	ldi	@0, (1<<INT0)	; enable ext0int
	out	GICR, @0
.ENDMACRO
.MACRO rcp_int_disable
	out	GICR, ZH	; disable ext0int
.ENDMACRO
.MACRO rcp_int_rising_edge
	ldi	@0, (1<<ISC01)+(1<<ISC00)
	out	MCUCR, @0	; set next int0 to rising edge
.ENDMACRO
.MACRO rcp_int_falling_edge
	ldi	@0, (1<<ISC01)
	out	MCUCR, @0	; set next int0 to falling edge
.ENDMACRO

.MACRO RED_on
sbi PORTD, warnLed
.ENDMACRO

.MACRO RED_off
cbi PORTD, warnLed
.ENDMACRO

.MACRO GRN_on
sbi PORTD, statusLed
.ENDMACRO

.MACRO GRN_off
cbi PORTD, statusLed
.ENDMACRO



;*********************

; PORT C definitions *

;*********************
;.equ					= 7	
;.equ					= 6	
;.equ					= 5
;.equ					= 4
.equ	mux_a			= 3 ; ADC für MUX a
.equ	mux_b			= 2 ; ADC für MUX b	 
.equ	mux_c			= 1 ; ADC für MUX c	 
;.equ					= 0	

.equ	INIT_PC			= 0
.equ	DIR_PC			= 0 ; auf PortC ist alles auf IN


.MACRO comp_init
	in	@0, SFIOR
	sbr	@0, (1<<ACME)	; set Analog Comparator Multiplexer Enable
	out	SFIOR, @0
.ENDMACRO
.MACRO set_comp_phase_a
	ldi	@0, mux_a	; set comparator multiplexer to phase A
	out	ADMUX, @0
	cbi	ADCSRA, ADEN	; disable ADC
.ENDMACRO
.MACRO set_comp_phase_b
	ldi	@0, mux_b	; set comparator multiplexer to phase B
	out	ADMUX, @0
	cbi	ADCSRA, ADEN	; disable ADC
.ENDMACRO
.MACRO set_comp_phase_c
	ldi	@0, mux_c	; set comparator multiplexer to phase C
	out	ADMUX, @0
	cbi	ADCSRA, ADEN	; disable ADC
.ENDMACRO





;*********************

; PORT B definitions *

;*********************

;.equ					= 7
;.equ					= 6
.equ	CnFET			= 5	; SCK
.equ	CpFET			= 4	; MISO
.equ	BnFET			= 3	; MOSI
.equ	BpFET			= 2	; 
.equ	AnFET			= 1	;
.equ	ApFET			= 0
.equ	INIT_PB			= 0
.equ	DIR_PB			= (1<<CnFET)+(1<<CpFET)+(1<<BnFET)+(1<<BpFET)+(1<<AnFET)+(1<<ApFET)




.equ	AnFET_port	= PORTB
.equ	ApFET_port	= PORTB
.equ	BpFET_port	= PORTB
.equ	BnFET_port	= PORTB
.equ	CpFET_port	= PORTB
.equ	CnFET_port	= PORTB


.MACRO ApFET_on
	sbi	PORTB, ApFET
.ENDMACRO
.MACRO ApFET_off
	cbi	PORTB, ApFET
.ENDMACRO
.MACRO BpFET_on
	sbi	PORTB, BpFET
.ENDMACRO
.MACRO BpFET_off
	cbi	PORTB, BpFET
.ENDMACRO
.MACRO CpFET_on
	sbi	PORTB, CpFET
.ENDMACRO
.MACRO CpFET_off
	cbi	PORTB, CpFET
.ENDMACRO

.MACRO ApFET_on_reg
	sbr	@0, 1<<ApFET
.ENDMACRO
.MACRO ApFET_off_reg
	cbr	@0, 1<<ApFET
.ENDMACRO
.MACRO BpFET_on_reg
	sbr	@0, 1<<BpFET
.ENDMACRO
.MACRO BpFET_off_reg
	cbr	@0, 1<<BpFET
.ENDMACRO
.MACRO CpFET_on_reg
	sbr	@0, 1<<CpFET
.ENDMACRO
.MACRO CpFET_off_reg
	cbr	@0, 1<<CpFET
.ENDMACRO

.MACRO all_pFETs_off
	in	@0, PORTB
	cbr	@0, (1<<ApFET)+(1<<BpFET)+(1<<CpFET)
	out	PORTB, @0
.ENDMACRO

.MACRO AnFET_on
	sbi	PORTB, AnFET
.ENDMACRO
.MACRO AnFET_off
	cbi	PORTB, AnFET
.ENDMACRO
.MACRO BnFET_on
	sbi	PORTB, BnFET
.ENDMACRO
.MACRO BnFET_off
	cbi	PORTB, BnFET
.ENDMACRO
.MACRO CnFET_on
	sbi	PORTB, CnFET
.ENDMACRO
.MACRO CnFET_off
	cbi	PORTB, CnFET
.ENDMACRO

.MACRO AnFET_on_reg
	sbr	@0, 1<<AnFET
.ENDMACRO
.MACRO AnFET_off_reg
	cbr	@0, 1<<AnFET
.ENDMACRO
.MACRO BnFET_on_reg
	sbr	@0, 1<<BnFET
.ENDMACRO
.MACRO BnFET_off_reg
	cbr	@0, 1<<BnFET
.ENDMACRO
.MACRO CnFET_on_reg
	sbr	@0, 1<<CnFET
.ENDMACRO
.MACRO CnFET_off_reg
	cbr	@0, 1<<CnFET
.ENDMACRO

.MACRO nFET_brake
	in	@0, PORTB
	sbr	@0, (1<<AnFET)+(1<<BnFET)+(1<<CnFET)
	out	PORTB, @0
.ENDMACRO
.MACRO all_nFETs_off
	in	@0, PORTB
	cbr	@0, (1<<AnFET)+(1<<BnFET)+(1<<CnFET)
	out	PORTB, @0
.ENDMACRO

