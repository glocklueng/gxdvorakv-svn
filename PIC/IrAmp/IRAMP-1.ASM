        list    F=inhx8m, p=pic12f629, r=dec        

#include <P12F629.inc>
__CONFIG 0x31c4

tmp		equ		0x20
sbuf	equ		0x22
rbuf	equ		0x23 

_delay	equ		0x25
_delay1	equ		0x26

_A		equ		0x28
_B		equ		0x29

tCountH	equ		0x30
tCountL	equ		0x31

MY_STATUS 	equ		0x5F
REC_RS		equ 	H'01'			; bit signalizujici prijem znaku
IR_ACT		equ		H'02'			; prijimam IR kod
IR_RC5		equ		H'20'			; RC5 kodovani
IR_SIRC		equ		H'40'			; SIRC kodovani
IR_NEC		equ		H'80'			; NEC, Sharp kodovani

s_out	equ 	GP2
s_in	equ		GP0
ir_in	equ		GP3


        org     00h     ; tady zacina  PIC po resetu
;***************************************************************************
        goto    init    ; skok na zacatek programu
;***************************************************************************
		org  	04h		; tady skace interrupt
;***************************************************************************
_interupt
		bcf 	INTCON,GIE		;  1 globalni zakaz interruptu
		btfss 	INTCON,GPIF		;	1-2
		goto	_int_next		;	2
		btfss	GPIO,s_in		;	1-2
		goto	_int_IR			;	2
_int_RS	call	receive_RS		;	2
		bcf		MY_STATUS,REC_RS
		andlw	0xff			; test na spravny prijem
		btfsc   STATUS,Z	
		bsf		MY_STATUS,REC_RS
		movf	GPIO,F			; timhle zajistim dalsi interrupt az od 0-1 hrany
		goto	_int_next
_int_IR
		btfsc	MY_STATUS,IR_ACT		
		goto	_int_prijimam
		btfsc	T1CON,TMR1ON	; test jestli uz citam
		goto	citac_jede
	;    tady je prvni rozpoznani typu ir
		btfsc	GPIO,ir_in		; test na sestupnou hranu
		goto	neni_IR			; NENI platne IR, vstup je v log 1
		clrf	TMR1L
		clrf	TMR1H
		bsf		T1CON,TMR1ON	; start citace	
		bsf		GPIO,GP1
		goto 	_int_next
citac_jede
		btfss	GPIO,ir_in		; test na nabeznou hranu
		goto	neni_IR			; NEPLATNY IR, Asi INT od jineho vstupu	
	;	bcf		T1CON,TMR1ON	; zastavim citac		
		BCF		GPIO,GP1
		call	vyhodnot_citac	
		goto	_int_next
_int_prijimam				; sem zkoci, pokud je nastaven byt v MY_STSATUS ir_act
		nop
		goto	_int_next					
neni_IR
		movlw	'Q'
		movwf	sbuf
		call	send_RS
_int_next
		btfss 	PIR1,TMR1IF
		goto	_int_end
_int_timer1_overflow
		bsf		GPIO,GP1
		BCF		MY_STATUS,IR_ACT
		BCF  	T1CON,TMR1ON
		bcf		PIR1,TMR1IF

_int_end		
		movlw	b'11111000'		; delete all flags
		andwf	INTCON,F
		bsf		INTCON,GIE		; povoly vsechny interrupty
		retfie
;-------------------------------------
vyhodnot_citac
		bcf 	STATUS,C
		rlf		TMR1L,F
		rlf		TMR1H,F			; deleno 128
		bcf 	STATUS,C
		rlf		TMR1L,F
		rlf		TMR1H,F			; deleno 64		
;----------
		movf	TMR1H,W
		movwf	sbuf
		call	send_RS
		call	cekejS
;----------
		movlw	d'12'
		bcf		STATUS,C
		subwf	TMR1H,F
		btfss	STATUS,C		; <> 0
		goto	_int_ir_error
		movlw	d'4'			;16
		bcf		STATUS,C
		subwf	TMR1H,F
		btfss	STATUS,C		; <> 0
		goto	_int_ir_RC5

		movlw	d'16'			;32
		bcf		STATUS,C
		subwf	TMR1H,F
		btfss	STATUS,C		; <> 0
		goto	_int_ir_error
		movlw	d'9'			;41
		bcf		STATUS,C
		subwf	TMR1H,F
		btfss	STATUS,C		; <> 0
		goto	_int_ir_SIRC

		movlw	d'88'			;129
		bcf		STATUS,C
		subwf	TMR1H,F
		btfss	STATUS,C		; <> 0
		goto	_int_ir_error
		movlw	d'22'			;41
		bcf		STATUS,C
		subwf	TMR1H,F
		btfss	STATUS,C		; <> 0
		goto	_int_ir_NEC
		goto	_int_ir_error

_int_ir_RC5						
		bsf		MY_STATUS,IR_ACT
		movlw	'R'
		movwf	sbuf
		call	send_RS
		call	cekejS
		call 	cekejS
		movf	TMR1H,W
		movwf	sbuf
		call	send_RS
;   TEST !!!
		BsF  	T1CON,TMR1ON

		return
_int_ir_SIRC	
		bsf		MY_STATUS,IR_ACT
		movlw	'S'
		movwf	sbuf
		call	send_RS
		call	cekejS
		call 	cekejS
		movf	TMR1H,W
		movwf	sbuf
		call	send_RS
;   TEST !!!
		BsF  	T1CON,TMR1ON

		return

_int_ir_NEC		
		bsf		MY_STATUS,IR_ACT
		movlw	'N'
		movwf	sbuf
		call	send_RS
		call	cekejS
		movf	TMR1H,W
		movwf	sbuf
		call	send_RS
;   TEST !!!
		BsF  	T1CON,TMR1ON

		return

_int_ir_error
		movlw	'E'
		movwf	sbuf
		call	send_RS
		bcf		MY_STATUS,IR_ACT
		return
;-------------------------------------

;***************************************************************************
init    	
		clrf	GPIO
		movlw	0x07
		movwf	CMCON			; vypne komparator
		bsf		STATUS,RP0 		; prepne na banku 1	
        movlw   b'111001'		
		movwf	TRISIO			; nastaveni I/O   O= out
       	movlw	b'111011' 		
      	movwf	WPU 			; nastaveni pull-up
		bcf		OPTION_REG,NOT_GPPU	; enable pull-up
	
		movlw	b'001001'   		
		movwf	IOC					; interrupt on GP0 a GP3 change
		bsf		INTCON,GPIE			; enable interrupt on GP0-GP4 change	

		bsf		INTCON,PEIE			; povoli interrupt periferii (timer 1)
		bsf		PIE1,TMR1IE			; povoli int od timer1
		call	3ffh			
		movwf	OSCCAL				; zapsani kalibracni konstanty

		; nastaveni citace	0

;	bcf	 	OPTION_REG,TOCS		; citaji se pulsy oscilatoru
;bcf		OPTION_REG,PSA		; citac s preddelickou
;	bcf		OPTION_REG,PS1		; predelicka 64*

		bcf		STATUS,RP0 		; prepne na banku 0
		; nastaveni Timer1  v bance 0
		clrf	T1CON			; nataveni konfigurace citace1

		clrf	MY_STATUS		; mazani pomocneho status registru
	
		clrf	GPIO
_xi0	btfss	GPIO,ir_in		; ceka na log 1 z cidla
		goto	_xi0
		movf	GPIO,F
	
_xi1	btfsc	GPIO,s_in		; ceka na RS v log 1 -- uroven -12V
		goto	_xi1
		movf	GPIO,F			; cteni portu pro zajisteni spravne zmeny
	
		movlw	b'11111000'		; delete all flags
		andwf	INTCON,F

		bsf		INTCON,GIE		;xxxxxxxxxxxxx povoleni vsech interruptu     

		bcf		MY_STATUS,REC_RS
		movlw	'O'
		movwf	sbuf
		call	send_RS
		call	cekejS
		movlw	'K'
		movwf	sbuf
		call	send_RS
		bcf		MY_STATUS,REC_RS
		bcf		MY_STATUS,IR_ACT

start
		btfss	MY_STATUS,REC_RS
		goto	next1
		movf	rbuf,W
		movwf	sbuf
        call	send_RS
		bcf		MY_STATUS,REC_RS		
next1
	;	movlw	0xff
	;	movwf	GPIO
	;	bsf		GPIO,GPIO0
	;	call	cekej
;		movlw	0x00
;		movwf	GPIO

	;	bsf		GPIO,GPIO0
	;	call	cekej
		goto	start
        
;*****************************************************
; sending to RS 232     9600 Bd, 8 Bit, bez parity, 1 stopBit
;*****************************************************
send_RS
		bsf		GPIO,s_out			;startbit		
		movlw	32				;	1    << t >>
		movwf	_delay			;	1	
sendrs0							; 104 ==9+ 3*t-1  ->> t=(104-9+1)/3
		decfsz	_delay,F		;	1-2
		goto	sendrs0			;	2    

		movlw	0x08			;	1
		movwf	tmp				;	1
sendrs1							; 104 = 11+3*t -> t=(104-11)/3=31					
		bcf		STATUS,C		;	1
		rrf		sbuf,F			;	1
		BTFSS	STATUS,C		;	1-2
		bsf		GPIO,s_out		; 	1		tohle se preskoci, pokud je C=1		
		BTFSC	STATUS,C		;***	1-2		tady uz to bude oboje	
		bcf		GPIO,s_out		; 	1		tohle se preskoci, pokud je C=0		
	
		movlw	31			;	1   << t >>
		movwf	_delay			;	1
			
sendrs2
		decfsz	_delay,F		;	1-2 \
		goto	sendrs2			;	2	 >  3*_delay
		nop						;   1	/

		decfsz	tmp,F				;	1-2
		goto	sendrs1			;	2
		
		nop			
		nop
		nop		
		nop
		nop
		bcf		GPIO,s_out		;  1	stopbit 104 = 6+3*t +5*nop
		return

				
;**********************************************************************
;*	 	Receiving from RS-232
;**********************************************************************
receive_RS		; + cca 3 + 8= 11  od interruptu
;		bcf		STATUS,RP0 		; prepne na banku 0	
		movlw	13				;	1    << t >>
		movwf	_delay1			;	1	
receivers0							; 52 ==10+ 3*t-1  ->> t=(52-14+1)/3
		decfsz	_delay1,F		;	1-2      testuju to uz pri 51, protoze pak mam
		goto	receivers0		;	2    	 2 us navic pri zadavani 0x08	

		btfss	GPIO,s_in		; 	1-2 - test startbitu
		goto	receiversE		;	2	- neni platny znak

		movlw	0x08			;	1
		movwf	tmp				;	1	
		nop						;	1
		nop						;	1

receivers1
		movlw 	32				;	1    << t >>
		movwf	_delay1			;	1			
receivers2						; 104 ==9+ 3*t-1  ->> t=(104-9+1)/3
		decfsz	_delay1,F		;	1-2
		goto	receivers2		;	2   
		bcf		STATUS,C		;	1
		bsf		GPIO,GP1
	;	movf	GPIO,F
		btfss	GPIO,s_in		;	1-2
		bsf		STATUS,C		;	1	- nezapomenu na inverzi RS	
		rrf		rbuf,F			;	1		
		BCF		GPIO,GP1
	;	movf	GPIO
		decfsz	tmp,F				;	1-2	
		goto	receivers1		;	2

receivers3						; test stop bitu
		movlw 	32				;	1    << t >>
		movwf	_delay1			;	1			
		nop
receivers4						; 104 ==7+ 3*t-1  ->> t=(104-7+1)/3
		decfsz	_delay1,F		;	1-2
		goto	receivers4		;	2   
		btfsc	GPIO,s_in		;	1-2
		goto	receiversE		;	2
		retlw	0				; OK	
receiversE
		retlw	0xff			;error






        
cekej
	movlw	0xff
	movwf	_A
cykl1	movlw 	0xff
	movwf 	_B
cykl	nop
	decfsz	_B,F
	goto 	cykl
	decfsz	_A,F
	goto 	cykl1
	return
	
cekejS
	movlw 	0xff
	movwf 	_B
_cekS	nop
	decfsz	_B,F
	goto 	_cekS
	return
	

        end
