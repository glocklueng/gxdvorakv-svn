        list    F=inhx8m, p=pic12f629, r=dec        

#include <P12F629.inc>
__CONFIG 0x31c4

tmp			equ		0x20
sbuf		equ		0x22
rbuf		equ		0x23 

_delay		equ		0x25
_delay1		equ		0x26


_A			equ		0x28
_B			equ		0x29

tCountH		equ		0x30
tCountL		equ		0x31
kodIndex	equ		0x32
kod			equ		0x33  ; 4 byte
kod_1		equ		0x34
kod_2		equ		0x35
kod_3		equ		0x36
kod_pom		equ		0x37

MY_STATUS 	equ		0x5F
REC_RS		equ 	0			; bit signalizujici prijem znaku
IR_ACT		equ		1			; prijimam IR kod
IR_RC5		equ		5			; RC5 kodovani
IR_SIRC		equ		6			; SIRC kodovani
IR_NEC		equ		7			; NEC, Sharp kodovani
OPAK		equ		2			; nestaven, pokud jiz prijat jeden kod NEC
								; protoze se vysila jen jeden bit pri opakovani

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
_int_prijimam				; sem skoci, pokud je nastaven byt v MY_STSATUS ir_act
		btfsc	MY_STATUS,IR_RC5
		call	prijmi_RC5
		btfsc	MY_STATUS,IR_SIRC
		call	prijmi_SIRC
		btfsc	MY_STATUS,IR_NEC
		call	prijmi_NEC
		bcf		GPIO,GP1	
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
		btfss	MY_STATUS,OPAK
		goto	_int_timer1_01
		movlw	d'32'
		subwf	kodIndex,F
		btfss	STATUS,Z
		goto	_int_timer1_01

		; tady se zachyti opakovani u NEC
		bcf		MY_STATUS,IR_ACT
		bsf		MY_STATUS,OPAK	; nastavim priznak pro opakovani				
		clrf	TMR1L
		movlw	d'40'			; dostatecna doba, aby pri drzeni prisel impulz opak. posl.
		movwf	TMR1H			; prednastaveni citace na opakovani prenosu
		bsf  	T1CON,TMR1ON
		call	_nec_posli_1

		
	;	BCF		MY_STATUS,IR_ACT
		bcf		PIR1,TMR1IF
		goto	_int_end

_int_timer1_01
		bcf		MY_STATUS,OPAK
		BCF		MY_STATUS,IR_ACT
		BCF  	T1CON,TMR1ON
		bcf		PIR1,TMR1IF

_int_end		
		movlw	b'11111000'		; delete all flags
		andwf	INTCON,F
		bsf		INTCON,GIE		; povoly vsechny interrupty
		retfie
;-------------------------------
prijmi_RC5

		return


prijmi_SIRC
		btfss	GPIO,ir_in
		return
		;goto	_p_sirc_01		; jsem v prvni pulce, pokracuj dal 
		; tady je nabezna hrana, urcit jestli jsem prijmul 1 nebo 0
		bcf		T1CON,TMR1ON	; zastavim citac		
		movf	TMR1L,W
		movwf	tCountL
		movf	TMR1H,W
		movwf	tCountH
		clrf	TMR1L			; reset citace
		clrf	TMR1H	
		bsf		T1CON,TMR1ON	; start citac	- chyba 8 us
	
		bcf 	STATUS,C
		rlf		tCountL,F
		rlf		tCountH,F	
	
		movlw	d'7'
		subwf	tCountH,F
		btfss	STATUS,C		; <> 0
		goto	_sirc_error
		movlw	d'6'			;12 jeste akceptuju
		subwf	tCountH,F
		btfss	STATUS,C		; <> 0
		goto	_sirc_0
		movlw	d'5'			;17 jeste akceptuju
		subwf	tCountH,F
		btfss	STATUS,C		; <> 0
		goto	_sirc_1
		goto	_sirc_error
_sirc_1		
		bsf		STATUS,C
		rrf		kod,F
		rrf		kod_1,F		
		goto	p_sirc_konec
_sirc_0		
		bcf		STATUS,C
		rrf		kod,F
		rrf		kod_1,F
		goto	p_sirc_konec
_sirc_error
		bcf		MY_STATUS,IR_ACT
		bcf		T1CON,TMR1ON	; zastavim citac		
		movlw	's'
		movwf	sbuf
		call	send_RS
		return	
p_sirc_konec
		decfsz	kodIndex,F
		return

		bcf		MY_STATUS,IR_ACT
		bcf		T1CON,TMR1ON	; zastavim citac		
		bcf		STATUS,C
		rrf		kod,F
		rrf		kod_1,F	
		bcf		STATUS,C	
		rrf		kod,F
		rrf		kod_1,F		
		bcf		STATUS,C	
		rrf		kod,F
		rrf		kod_1,F		
		bcf		STATUS,C	; ted uz posunu jen jeden byte - prikaz
		rrf		kod_1,F
				
		movf	kod,W
		movwf	sbuf
		call	send_RS
		call	cekejS
		movf	kod_1,W
		movwf	sbuf
		call	send_RS
		call	cekejS
		return

TEST		movlw	't'
			movwf	sbuf
			call	send_RS
			call	cekejS
			return
TEST1		movlw	'T'
			movwf	sbuf
			call	send_RS
			call	cekejS
			movf	tCountH,W
			movwf	sbuf
			call	send_RS
			call	cekejS
			return


prijmi_NEC	
		btfss	kodIndex,7  ;	test, pokud je index>=128, je to prvni byte
		goto	_nec_byte		
		btfsc	GPIO,ir_in	; 	test na 2. pulku start impulsu....1 na 4.5 ms
		goto	_nec_error	
		bcf		T1CON,TMR1ON	; zastavim citac		
		movf	TMR1L,W
		movwf	tCountL
		movf	TMR1H,W
		movwf	tCountH
		clrf	TMR1L			; reset citace
		clrf	TMR1H	
		bsf		T1CON,TMR1ON	; start citac	- chyba 8 us	
		bcf 	STATUS,C
		rlf		tCountL,F
		rlf		tCountH,F	
		; test start impulsu "1"  ... 4.5ms
		movlw	d'10'	;d'31'   jen pro test mam 10
		subwf	tCountH,F
		btfss	STATUS,C		; <> 0
		goto	_nec_error1
		movlw	d'30'	;d'7'			;jeste akceptuju
		subwf	tCountH,F
		btfsc	STATUS,C		; <> 0
		goto	_nec_error
_nec_start_OK
		bcf		kodIndex,7
		return	
_nec_byte
		movf	GPIO,F
		btfss	GPIO,ir_in
		goto	_nec_mer_cas
		btfss	MY_STATUS,OPAK
		goto	_nec_byte1
		clrf	TMR1L	; pokud prijde startovaci posloupnost a nic
						; tak drzim tlacitko		
		movlw	d'230'	; VIC NEZ log. 1, mene nez OPAKOVANI
		movwf	TMR1H	; preteceni = opakovani posloupnosti
		return
_nec_byte1
		clrf	TMR1L
		clrf	TMR1H	; smazu citac a zacinam merit cas, abych poznal 0 nebo 1
		return			; tady je konec impulsu, ted budu merit cas mezery

_nec_mer_cas
		bsf		GPIO,GP1
		bcf		T1CON,TMR1ON	; zastavim citac		
		movf	TMR1L,W
		movwf	tCountL
		movf	TMR1H,W
		movwf	tCountH
		clrf	TMR1L			; reset citace
		clrf	TMR1H	
		bsf		T1CON,TMR1ON	; start citac	- chyba 8 us	

		bcf 	STATUS,C
		rlf		tCountL,F
		rlf		tCountH,F		; zvysim citlivost
		bcf 	STATUS,C
		rlf		tCountL,F
		rlf		tCountH,F		; zvysim citlivost 4*

	;	-------
	;	movf	tCountH,W
	;	movwf	sbuf
	;	call	send_RS
	;	call	cekejS
	;-----------------------
		movlw	d'5'
		subwf	tCountH,F
		btfss	STATUS,C		; <> 0
		goto	_nec_error	
		movlw	d'9'			; jeste akceptuju
		subwf	tCountH,F
		btfss	STATUS,C		; <> 0
		goto	_nec_0			; C=0
		movlw	d'15'			; jeste akceptuju
		subwf	tCountH,F
		btfsc	STATUS,C		; <> 0		
		goto	_nec_error

_nec_1	bsf		STATUS,C
_nec_0	rrf		kod,F
		rrf		kod_1,F		
		rrf		kod_2,F
		rrf		kod_3,F
		goto	_nec_konec

_nec_error
		bcf		MY_STATUS,IR_ACT
		bcf		T1CON,TMR1ON	; zastavim citac		
		movlw	'x'
		movwf	sbuf
		call	send_RS
		call	cekejS
		movf	tCountH,W
		movwf	sbuf
		call	send_RS
		call	cekejS
		return	
_nec_error1
		bcf		MY_STATUS,IR_ACT
		bcf		T1CON,TMR1ON	; zastavim citac		
		movlw	'X'
		movwf	sbuf
		call	send_RS
		call	cekejS
		movf	tCountH,W
		movwf	sbuf
		call	send_RS
		call	cekejS
		return	
_nec_konec
		decfsz	kodIndex,F
		return
		bcf		MY_STATUS,IR_ACT
		bsf		MY_STATUS,OPAK	; nastavim priznak pro opakovani				
		bsf		T1CON,TMR1ON	; zastavim citac
		clrf	TMR1L
		movlw	d'60'
		movwf	TMR1H			; prednastaveni citace na opakovani prenosu
;_nec_xz	btfss	GPIO,ir_in
;		goto	_nec_xz
		bsf		T1CON,TMR1ON	; pustim citac
		
_nec_posli
		movlw	'N'
		movwf	sbuf
		call	send_RS
		call	cekejS				
		movf	kod,W
		movwf	sbuf
		call	send_RS
		call	cekejS
		movf	kod_1,W
		movwf	sbuf
		call	send_RS
		call	cekejS
		movf	kod_2,W
		movwf	sbuf
		call	send_RS
		call	cekejS
		movf	kod_3,W
		movwf	sbuf
		call	send_RS
		call	cekejS

		return
_nec_posli_1
		movlw	'A'
		movwf	sbuf
		call	send_RS
		call	cekejS				
		movf	kod,W
		movwf	sbuf
		call	send_RS
		call	cekejS
		movf	kod_1,W
		movwf	sbuf
		call	send_RS
		call	cekejS
		movf	kod_2,W
		movwf	sbuf
		call	send_RS
		call	cekejS
		movf	kod_3,W
		movwf	sbuf
		call	send_RS
		call	cekejS

		return
	

;-------------------------------------
vyhodnot_citac
		bcf		T1CON,TMR1ON	; zastavim citac		
		movf	TMR1L,W
		movwf	tCountL
		movf	TMR1H,W
		movwf	tCountH
		clrf	TMR1L
		clrf	TMR1H
		bsf		T1CON,TMR1ON	; start citac	- chyba 8 us

		
		bcf 	STATUS,C
		rlf		tCountL,F
		rlf		tCountH,F			; deleno 128
		bcf 	STATUS,C
		rlf		tCountL,F
		rlf		tCountH,F			; deleno 64		
;----------
	;	movf	tCountH,W
	;	movwf	sbuf
	;	call	send_RS
	;	call	cekejS
;----------
		movlw	d'12'
		subwf	tCountH,F
		btfss	STATUS,C		; <> 0
		goto	_int_ir_error
		movlw	d'4'			;16
		subwf	tCountH,F
		btfss	STATUS,C		; <> 0
		goto	_int_ir_RC5

		movlw	d'16'			;32
		subwf	tCountH,F
		btfss	STATUS,C		; <> 0
		goto	_int_ir_error
		movlw	d'9'			;41
		subwf	tCountH,F
		btfss	STATUS,C		; <> 0
		goto	_int_ir_SIRC

		movlw	d'88'			;88  129
		subwf	tCountH,F
		btfss	STATUS,C		; <> 0
		goto	_int_ir_error
		movlw	d'25'			; 20  41
		subwf	tCountH,F
		btfss	STATUS,C		; <> 0
		goto	_int_ir_NEC
		goto	_int_ir_error

_int_ir_RC5						
		bsf		MY_STATUS,IR_ACT
		movlw	0x0f
		andwf	MY_STATUS,F
		bsf		MY_STATUS,IR_RC5
		return
_int_ir_SIRC
		movlw	d'12'
		movwf	kodIndex
		bsf		MY_STATUS,IR_ACT
		movlw	0x0f
		andwf	MY_STATUS,F
		bsf		MY_STATUS,IR_SIRC
		return

_int_ir_NEC		
		movlw	d'32'+d'128'
		movwf	kodIndex
		bsf		MY_STATUS,IR_ACT
		movlw	0x0f
		andwf	MY_STATUS,F
		bsf		MY_STATUS,IR_NEC
		return

_int_ir_error
		bcf		MY_STATUS,IR_ACT
		bcf		T1CON,TMR1ON	; zastavim citac		
		movlw	'E'
		movwf	sbuf
		call	send_RS
	   	call	cekejS
		movf	tCountH,W
		movwf	sbuf
		call	send_RS
		call	cekejS

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
		bcf		STATUS,RP0 		; prepne na banku 0
		clrf	T1CON			; nataveni konfigurace citace1
		clrf	MY_STATUS		; mazani pomocneho status registru	
		clrf	GPIO
_xi0	;btfss	GPIO,ir_in		; ceka na log 1 z cidla
		;goto	_xi0
		;movf	GPIO,F	
_xi1	btfsc	GPIO,s_in		; ceka na RS v log 1 -- uroven -12V
		goto	_xi1
		movf	GPIO,F			; cteni portu pro zajisteni spravne zmeny
		movlw	b'11111000'		
		andwf	INTCON,F		; delete all flags
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

;**********************************************************************
;*	 	cekaci smycka
;**********************************************************************      
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
	
; zpozdeni na odeslani 1-2 bitu po rs, pouziva se po odeslani znaku, na pockani 
; alespon dobu 1-2 bitu pred poslanim dalsiho...
cekejS
	movlw 	0xff
	movwf 	_B
_cekS	nop
	decfsz	_B,F
	goto 	_cekS
	return
	

        end
