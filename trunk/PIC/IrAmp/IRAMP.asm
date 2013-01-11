	list    F=inhx8m, p=pic12f629, r=dec        
#include <P12F629.inc>
	__CONFIG 0x31c4

; vysilaci retezce   x je 1 byte
;	SHARP  			SHP0xx 
;	RC5				RC50xx   	
;	SIRC			SIRCxx
;	PANASONIC		xxxxxx
;	NEC				NCxxxx
;	Mitsubishi-nove MBxxxx

waitTime			equ				0x48

tmp					equ             0x20
sbuf            	equ             0x22
rbuf            	equ             0x23 

_delay          	equ             0x25
_delay1       		equ             0x26

_A                  equ             0x28
_B                  equ             0x29

tCountH   			equ             0x30
tCountL        	 	equ             0x31
kodIndex       	 	equ             0x32
kod 				equ             0x33  ;6 byte
kod_1   	        equ             0x34
kod_2       	    equ             0x35
kod_3           	equ             0x36
kod_4    			equ             0x37
kod_5       	    equ             0x38
kod_pom         	equ             0x39
pomIndex			equ				0x3A
testIndex			equ				0x3b
testSample			equ				0x3c


RSTimeout			equ				0x40
RSTimeout_1			equ				0x41
RSTimeout_2			equ				0x42

MY_STATUS           equ             0x5E
REC_RS              equ 		    0                       ; bit signalizujici prijem znaku
IR_ACT              equ             1                       ; prijimam IR kod
IR_SHARP            equ             2                       ; stary SHARP   
IR_RC5              equ             3                       ; RC5 
IR_SIRC             equ             4                       ; SIRC
IR_PANASONIC		equ             5                       ; PANASONIC, Blaupunkt VCR
IR_MITSUBISHI		equ             6                       ; MITSUBISHI 
IR_NEC          	equ             7                       ; NEC, novy SHARP

IR_STATUS 			equ             0x5F
start2     			equ             0   		; pokud je startovaci posloupnost ze 2 casti
pulbit              equ             1           ; pozice: 1= pulka bitu RC5, 0 celej
inverze	  			equ             2           ; pokud se kod opakuje a je inverzni, tak ho muze testovat, ale posila se ven jen jeden format
prijato          	equ             3           ; podrzi hodnotu posledniho prijateho bitu
prijato_mask		equ				0x08		; jednicka na pozici prijato bitu
cekani				equ				4			; cekani na neaktivitu po chybe, pro nalezeni praveho zacatku
opak_povoleno		equ				5			; po prijate sekvenci povoli opakovani s prijmem jen jednoho bitu
start_kal			equ				7			; nastavi se, pokud merim citacem prvni cast start bitu


s_out  				equ     GP2
s_in    			equ             GP0
ir_in   			equ             GP3


				org     00h     ; tady zacina  PIC po resetu
;***************************************************************************
				goto    init    ; skok na zacatek programu
;***************************************************************************
				org     04h             ; tady skace interrupt
;***************************************************************************
_interupt
				bcf     INTCON,GIE              ;  1 globalni zakaz interruptu
	       		btfss   INTCON,GPIF             ;       1-2
	    	    goto    _int_next               ;       2
    	    	btfss   GPIO,s_in               ;       1-2
				goto    _int_IR                 ;       2
_int_RS 		call    receive_RS              ;       2
                bcf     MY_STATUS,REC_RS
                andlw   0xff                    ; test na spravny prijem
                btfsc   STATUS,Z        
                bsf     MY_STATUS,REC_RS
                movf    GPIO,F                  ; timhle zajistim dalsi interrupt az od 0-1 hrany
                goto    _int_next
_int_IR
                btfsc	IR_STATUS,cekani
				goto	_int_ir_cekej
				btfsc   MY_STATUS,IR_ACT                
		        goto    _int_prijimam							
				btfsc   IR_STATUS,start_kal				;T1CON,TMR1ON    ; test jestli uz citam
				goto    citac_jede
				;    tady je prvni rozpoznani typu ir
				btfsc   GPIO,ir_in              ; test na sestupnou hranu
				goto    neni_IR                 ; NENI platne IR, vstup je v log 1
				clrf    TMR1L
				clrf    TMR1H
				bsf     T1CON,TMR1ON  			  ; start citace  
				bsf   	IR_STATUS,start_kal		
				bsf     GPIO,GP1
				goto    _int_next
_int_ir_cekej	movf	GPIO,F				; zachyceni stavu IO
				clrf	TMR1L				; prisel pulz v dobe kdy cekam na klid, nuluj citac a cekej dal
				movlw	waitTime
				movwf	TMR1H				; prednastaveni na 10 ms
				bsf     T1CON,TMR1ON   		; start citace - pro jistotu
				goto 	_int_next

citac_jede
				btfss   GPIO,ir_in              ; test na nabeznou hranu
				goto    neni_IR1                 ; NEPLATNY IR, Asi INT od jineho vstupu 
				;       bcf             T1CON,TMR1ON    ; zastavim citac                
				BCF    	GPIO,GP1
				call    vyhodnot_citac  
				bcf   	IR_STATUS,start_kal	
				goto    _int_next
_int_prijimam                           ; sem skoci, pokud je nastaven byt v MY_STSATUS ir_act
				btfsc   MY_STATUS,IR_RC5
				call    prijmi_RC5
				btfsc   MY_STATUS,IR_MITSUBISHI
				call    prijmi_MITSUBISHI
				btfsc   MY_STATUS,IR_PANASONIC
				call    prijmi_PANASONIC
				btfsc   MY_STATUS,IR_SHARP
				call    prijmi_SHARP
				btfsc   MY_STATUS,IR_SIRC
				call    prijmi_SIRC
				btfsc   MY_STATUS,IR_NEC
				call    prijmi_NEC
				bcf     GPIO,GP1        
				goto    _int_next                                       
neni_IR
		;		movlw   0xf0
		;		movwf   sbuf
		;		call    send_RS
				goto    _int_next                                       
neni_IR1
		;		movlw   0xf1
		;		movwf   sbuf
		;		call    send_RS
_int_next
				btfss   PIR1,TMR1IF
				goto    _int_end
_int_timer1_overflow
				bsf     GPIO,GP1
				btfsc	IR_STATUS,cekani
				goto	_int_konec_cekani

				BCF     MY_STATUS,IR_ACT
				bcf		IR_STATUS,opak_povoleno
				BCF     T1CON,TMR1ON
				bcf     PIR1,TMR1IF
				goto    _int_end
		;		movlw   'T'
		;		movwf   sbuf
		;		call    send_RS

_int_konec_cekani
				bcf		IR_STATUS,opak_povoleno
				bcf     MY_STATUS,IR_ACT
				bcf     T1CON,TMR1ON
				bcf		IR_STATUS,cekani				

_int_end                
				movlw   b'11111000'             ; delete all flags
				andwf   INTCON,F
				bsf     INTCON,GIE              ; povoli vsechny interrupty
				retfie
;-------------------------------
prijmi_NEC
				bcf		T1CON,TMR1ON    ; zastavim citac                
				movf    TMR1L,W
				movwf   tCountL
				movf    TMR1H,W
				movwf   tCountH
				clrf    TMR1L           ; reset citace
				clrf    TMR1H   
				bsf 	T1CON,TMR1ON    ; start citac   - chyba 8 us
				bcf     STATUS,C	
				rlf  	tCountL,F
				rlf 	tCountH,F       
				rlf 	tCountL,F
				rlf    	tCountH,F       
			
				btfsc   IR_STATUS,start2
				goto    _NEC_start2

				btfsc   GPIO,ir_in
				goto    _NEC_end              ; ted je nabezna hrana, tak zacnu merit cas     
											
				; pocitam dobu pulsu    
				movlw   d'8'
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _NEC_error
				movlw   d'6'                    ;
				subwf   tCountH,F
											
				rlf  	kod,F           
				rlf 	kod_1,F
				rlf 	kod_2,F
				rlf 	kod_3,F

				decfsz  kodIndex,F
				goto    _NEC_end
				goto    _NEC_prijato

_NEC_start2
				btfsc   GPIO,ir_in
				goto    _NEC_error   
				movlw   d'32'
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _NEC_error
				movlw   d'7'                    ;
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto	_NEC_startOpak             
				movlw   d'26'
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _NEC_error
				movlw   d'14'                    ;
				subwf   tCountH,F
				btfsc   STATUS,C
				goto    _NEC_error
				; start OK
				bcf     IR_STATUS,start2
				bcf		IR_STATUS,inverze
				goto    _NEC_end  
_NEC_startOpak
				bcf     IR_STATUS,start2
				btfsc	IR_STATUS,opak_povoleno
				goto    _NEC_prijato  
				bcf     T1CON,TMR1ON    ; stop citac
				bcf  	MY_STATUS,IR_ACT
				goto	_NEC_end

_NEC_prijato  	bcf     T1CON,TMR1ON    ; stop citac
				bsf		IR_STATUS,opak_povoleno
				bcf  	MY_STATUS,IR_ACT
				movlw	'N'
				movwf   sbuf
				call    send_RS
				call    cekejS
				movlw	'C'		
				movwf   sbuf
				call    send_RS
				call    cekejS

				movf    kod_3,W
				movwf   sbuf
				call    send_RS
				call    cekejS

				movf    kod_2,W
				movwf   sbuf
				call    send_RS
				call    cekejS

				movf    kod_1,W
				movwf   sbuf
				call    send_RS
				call    cekejS

				movf    kod,W
				movwf   sbuf    
				call    send_RS
				call    cekejS
				return

_NEC_error
				bcf		IR_STATUS,opak_povoleno
			;	movlw   'n'
			;	movwf   sbuf
			;;	call    send_RS
			;	call    cekejS		
				clrf	TMR1L			
				movlw	waitTime
				movwf	TMR1H				; prednastaveni na 10 ms
				bsf     T1CON,TMR1ON   	
				bsf		IR_STATUS,cekani
				
_NEC_end      
				return


;-------------------------------
prijmi_SHARP
				bcf		T1CON,TMR1ON    ; zastavim citac                
				movf    TMR1L,W
				movwf   tCountL
				movf    TMR1H,W
				movwf   tCountH
				clrf    TMR1L                   ; reset citace
				clrf    TMR1H   
				bsf 	T1CON,TMR1ON    ; start citac   - chyba 8 us
				bcf     STATUS,C	
				rlf  	tCountL,F
				rlf 	tCountH,F       
				rlf 	tCountL,F
				rlf    	tCountH,F       
			
				btfsc   IR_STATUS,start2
				goto    _SHARP_start2

				btfsc   GPIO,ir_in
				goto    _SHARP_end              ; ted je nabezna hrana, tak zacnu merit cas     
							
				
				; pocitam dobu pulsu    
				movlw   d'8'
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _SHARP_error
				movlw   d'6'                    ;
				subwf   tCountH,F
				
				bcf		IR_STATUS,prijato		; zapamatuju si prijatou hodnotu
				btfsc	STATUS,C
				bsf		IR_STATUS,prijato

_SHARP_inverzetest				
				decfsz 	pomIndex,F
				;movlw	0x04
				;subwf	pomIndex,W
				;btfss	STATUS,Z
				goto	_SHARP_notest
				bcf		IR_STATUS,inverze
				btfss	IR_STATUS,prijato
				bsf		IR_STATUS,inverze
			;	goto	_SHARP_noInvert								
_SHARP_notest
;				incf	pomIndex,F
				btfss	IR_STATUS,inverze
				goto 	_SHARP_noInvert
				movlw	prijato_mask
				xorwf	IR_STATUS,F
					
_SHARP_noInvert	bcf		STATUS,C
				btfsc	IR_STATUS,prijato
				bsf		STATUS,C				
							
				rlf  	kod,F           
				rlf 	kod_1,F

				; filtrace sekvence
				movf	testIndex,W
				xorwf	kodIndex,W
				btfss	STATUS,Z
				goto	_SHARP_nefiltrovat
				movf	kod,W
				xorwf	testSample,W
				btfss	STATUS,Z
				goto	_SHARP_error

_SHARP_nefiltrovat
				decfsz  kodIndex,F
				goto    _SHARP_end
				goto    _SHARP_prijato

_SHARP_start2
				btfsc   GPIO,ir_in
				goto    _SHARP_error   
				movlw   d'8'
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _SHARP_error
				movlw   d'6'                    ;
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto	_SHARP_startVCR             
				movlw   d'10'
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _SHARP_error
				movlw   d'7'                    ;
				subwf   tCountH,F
				btfsc   STATUS,C
				goto    _SHARP_error
				; start OK
				movlw	5
				movwf	pomIndex
				movlw	d'14'
				movwf	kodIndex
				bsf		STATUS,C
				rlf  	kod,F           
				rlf 	kod_1,F
				movlw	11
				movwf	testIndex
				movlw	b'010000'
				movwf	testSample
				bcf     IR_STATUS,start2
				bcf		IR_STATUS,inverze
				goto    _SHARP_end  
_SHARP_startVCR
				movlw	3
				movwf	pomIndex
				bcf     IR_STATUS,start2
				bcf		IR_STATUS,inverze
				movlw	d'11'
				movwf	kodIndex
				movlw	10
				movwf	testIndex
				movlw	b'010'
				movwf	testSample
				goto    _SHARP_end  

_SHARP_prijato  bcf     T1CON,TMR1ON    ; stop citac
				bcf  	MY_STATUS,IR_ACT
				movlw	'S'
				movwf   sbuf
				call    send_RS
				call    cekejS
				movlw	'H'		
				movwf   sbuf
				call    send_RS
				call    cekejS
				movlw	'P'
				movwf   sbuf
				call    send_RS
				call    cekejS
				movlw	'0'
				movwf   sbuf
				call    send_RS
				call    cekejS	

				movf    kod_1,W
				movwf   sbuf
				call    send_RS
				call    cekejS

				movf    kod,W
				movwf   sbuf    
				call    send_RS
				call    cekejS
				return

_SHARP_error
				clrf	TMR1L			
				movlw	waitTime
				movwf	TMR1H				; prednastaveni na 10 ms
				bsf     T1CON,TMR1ON   	
				bsf		IR_STATUS,cekani
			;	movlw   'H'
			;	movwf   sbuf
			;	call    send_RS
			;	call    cekejS		
_SHARP_end      
				return
;--------------------------------------------------------------------
prijmi_PANASONIC
				bcf 	T1CON,TMR1ON    ; zastavim citac                
				movf    TMR1L,W
				movwf   tCountL
				movf    TMR1H,W
				movwf   tCountH
				clrf    TMR1L                   ; reset citace
				clrf    TMR1H   
				bsf		T1CON,TMR1ON    ; start citac   - chyba 8 us

				bcf     STATUS,C
				rlf     tCountL,F
				rlf     tCountH,F       
				rlf     tCountL,F
				rlf     tCountH,F       

				btfsc   IR_STATUS,start2
				goto    _PANASONIC_start2

				btfsc   GPIO,ir_in
				goto    _PANASONIC_end          ; ted je nabezna hrana, tak zacnu merit cas     
				; pocitam dobu pulsu    
				movlw   d'5'
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _PANASONIC_error
				movlw   d'10'                   ;
				subwf   tCountH,F

				rlf     kod,F           ; sestupna hrana = 1
				rlf     kod_1,F
				rlf     kod_2,F
				rlf     kod_3,F
				rlf     kod_4,F
				rlf     kod_5,F

				decfsz  kodIndex,F
				goto    _PANASONIC_end
				goto    _PANASONIC_prijato

_PANASONIC_start2
				btfsc   GPIO,ir_in
				goto    _PANASONIC_error                
				movlw   d'24'
				subwf   tCountH,	F
				btfss   STATUS,C                ; <> 0
				goto    _PANASONIC_error
				movlw   d'7'                    ;
				subwf   tCountH,F
				btfsc   STATUS,C
				goto    _PANASONIC_error
				; start OK
				bcf             IR_STATUS,start2
				goto    _PANASONIC_end  

_PANASONIC_prijato 
				bcf     T1CON,TMR1ON    ; stop citac
			   	bcf     MY_STATUS,IR_ACT
				movf    kod_5,W
				movwf   sbuf
				call    send_RS
				call    cekejS
				movf    kod_4,W
				movwf   sbuf
				call    send_RS
				call    cekejS
				movf    kod_3,W
				movwf   sbuf
				call    send_RS
				call    cekejS
				movf    kod_2,W
				movwf   sbuf
				call    send_RS
				call    cekejS
				movf    kod_1,W
				movwf   sbuf
				call    send_RS
				call    cekejS
				movf    kod,W
				movwf   sbuf    
				call    send_RS
				call    cekejS
				return

_PANASONIC_error 
				bcf    MY_STATUS,IR_ACT
				bcf    IR_STATUS,start2
				clrf	TMR1L			
				movlw	waitTime
				movwf	TMR1H				; prednastaveni na 10 ms
				bsf     T1CON,TMR1ON   	
				bsf		IR_STATUS,cekani
;				movlw   'p'
;				movwf   sbuf
;				call    send_RS
;				call    cekejS
_PANASONIC_end  
				return
;----------------------------------------------------------
prijmi_MITSUBISHI
				bcf     T1CON,TMR1ON    ; zastavim citac                
				movf    TMR1L,W
				movwf   tCountL
				movf    TMR1H,W
				movwf   tCountH
				clrf    TMR1L                   ; reset citace
				clrf    TMR1H   		
				bsf             T1CON,TMR1ON    ; start citac   - chyba 8 us

				bcf     STATUS,C
				rlf     tCountL,F
				rlf     tCountH,F       
				rlf     tCountL,F
				rlf     tCountH,F       

				btfsc   IR_STATUS,start2
				goto    _MITS_start2

				btfsc   GPIO,ir_in
				goto    _MITS_end               ; ted je nabezna hrana, tak zacnu merit cas     
				; pocitam dobu pulsu    
				movlw   d'5'
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _MITS_error
				movlw   d'10'                   ;
				subwf   tCountH,F

				rlf     kod,F           ; sestupna hrana = 1
				rlf     kod_1,F
				rlf     kod_2,F
				rlf     kod_3,F

				decfsz  kodIndex,F
				goto    _MITS_end
				goto    _MITS_prijato

_MITS_start2    btfsc   GPIO,ir_in
				goto    _MITS_error             
				movlw   d'65'
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _MITS_error
				movlw   d'14'                   ;
				subwf   tCountH,F
				btfsc   STATUS,C
				goto    _MITS_error
				; start OK
				bcf     IR_STATUS,start2
				goto    _MITS_end       

_MITS_prijato  	bcf     T1CON,TMR1ON    ; stop citac
				bcf     MY_STATUS,IR_ACT
				movlw	'M'
				movwf   sbuf
				call    send_RS
				call    cekejS
				movlw	'B'
				movwf   sbuf
				call    send_RS
				call    cekejS
                movf    kod_3,W
                movwf   sbuf
                call    send_RS
                call    cekejS
                movf    kod_2,W
                movwf   sbuf
                call    send_RS
                call    cekejS
                movf    kod_1,W
                movwf   sbuf
                call    send_RS
                call    cekejS
 				movf    kod,W
				movwf   sbuf    
				call    send_RS
				call    cekejS
				return

_MITS_error     bcf     MY_STATUS,IR_ACT
				bcf     IR_STATUS,start2
				clrf	TMR1L			
				movlw	waitTime
				movwf	TMR1H				; prednastaveni na 10 ms
				bsf     T1CON,TMR1ON   	
				bsf		IR_STATUS,cekani
;				movlw   'M'
;				movwf   sbuf
;				call    send_RS
;				call    cekejS

_MITS_end       
				return
;--------------------------------------------------------
prijmi_RC5
				bcf     T1CON,TMR1ON    ; zastavim citac                
				movf    TMR1L,W
				movwf   tCountL
				movf    TMR1H,W
				movwf   tCountH
				clrf    TMR1L                   ; reset citace
				clrf    TMR1H   
				bsf     T1CON,TMR1ON    ; start citac   - chyba 8 us

				bcf     STATUS,C
				rlf     tCountL,F
				rlf     tCountH,F       
				rlf     tCountL,F
				rlf     tCountH,F       

				movlw   d'11'
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _RC5_error
				movlw   d'6'                    ;
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _RC5_0.5
				goto    _RC5_1

_RC5_0.5        btfsc   IR_STATUS,pulbit
				goto    _RC5_CELA                       ; predchozi byl v pulce bitu, ted jsem na celym 
				goto    _RC5_PULKA
_RC5_1      	btfsc   IR_STATUS,pulbit
				goto    _RC5_PULKA                      ;predchozi byl v pulce bitu, ted jsem zase na pulce
				goto    _RC5_error                      ; z celeho na celej je blbost

_RC5_CELA   	bcf 	IR_STATUS,pulbit
				goto    _RC5_end                        ; cela me nezajima


_RC5_PULKA		bsf		STATUS,C
				bsf    	IR_STATUS,pulbit
				btfss   GPIO,ir_in
				goto    _RC5_L
_RC5_H  		bcf   	STATUS,C        ; nabezna hrana = 0
_RC5_L          rlf   	kod,F           ; sestupna hrana = 1
				rlf		kod_1,F         

				decfsz  kodIndex,F	
				goto    _RC5_end
_RC5_prijato                                            
				bcf     T1CON,TMR1ON    ; stop citac
				bcf     MY_STATUS,IR_ACT
				movlw	'R'
				movwf   sbuf
				call    send_RS
				call    cekejS
				movlw	'C'
				movwf   sbuf
				call    send_RS
				call    cekejS
				movlw	'5'
				movwf   sbuf
				call    send_RS
				call    cekejS
				movlw	'0'
				movwf   sbuf
				call    send_RS
				call    cekejS

				movf    kod_1,W
				movwf   sbuf
				call    send_RS
				call    cekejS
				movf    kod,W
				movwf   sbuf    
				call    send_RS
				call    cekejS
				return

_RC5_error      bcf    MY_STATUS,IR_ACT
				clrf	TMR1L			
				movlw	waitTime
				movwf	TMR1H				; prednastaveni na 10 ms
				bsf     T1CON,TMR1ON   	
				bsf		IR_STATUS,cekani

_RC5_end  	    return


;--------------------------------------------------------------------------
prijmi_SIRC
				btfss   GPIO,ir_in
				goto	_SIRC_end
				; tady je nabezna hrana, urcit jestli jsem prijmul 1 nebo 0
				bcf     T1CON,TMR1ON    ; zastavim citac                
				movf    TMR1L,W
				movwf   tCountL
				movf    TMR1H,W
				movwf   tCountH
				clrf    TMR1L                   ; reset citace
				clrf    TMR1H   
				bsf 	T1CON,TMR1ON    ; start citac   - chyba 8 us

				bcf     STATUS,C
				rlf     tCountL,F
				rlf     tCountH,F       

				movlw   d'7'
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _SIRC_error
				movlw   d'6'                    ;12 jeste akceptuju
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _SIRC_0
				movlw   d'5'                    ;17 jeste akceptuju
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _SIRC_1
				goto    _SIRC_error

_SIRC_1        	bsf     STATUS,C
_SIRC_0         rrf     kod,F
				rrf     kod_1,F

				decfsz  kodIndex,F
				goto	_SIRC_end

_SIRC_prijato	bcf     MY_STATUS,IR_ACT
				bcf     T1CON,TMR1ON    ; zastavim citac                
				bcf     STATUS,C
				rrf     kod,F
				rrf     kod_1,F 
				bcf     STATUS,C        
				rrf     kod,F
				rrf     kod_1,F         
				bcf     STATUS,C        
				rrf     kod,F
				rrf     kod_1,F         
				bcf     STATUS,C        ; ted uz posunu jen jeden byte - prikaz
				rrf     kod_1,F			

				movlw	'S'
				movwf   sbuf
				call    send_RS
				call    cekejS				
				movlw	'I'
				movwf   sbuf
				call    send_RS
				call    cekejS
				movlw	'R'
				movwf   sbuf
				call    send_RS
				call    cekejS
				movlw	'C'
				movwf   sbuf
				call    send_RS
				call    cekejS
				movf    kod,W		; zarizeni
				movwf   sbuf
				call    send_RS
				call    cekejS
				movf    kod_1,W		; prikaz
				movwf   sbuf
				call    send_RS
				call    cekejS
				goto	_SIRC_end

_SIRC_error
				bcf     MY_STATUS,IR_ACT
				clrf	TMR1L			
				movlw	waitTime
				movwf	TMR1H				; prednastaveni na 10 ms
				bsf     T1CON,TMR1ON   	
				bsf		IR_STATUS,cekani
;				movlw   's'
;				movwf   sbuf
;				call    send_RS
_SIRC_end	
				return
          
;-------------------------------------
vyhodnot_citac
				bcf     T1CON,TMR1ON    ; zastavim citac                
				movf    TMR1L,W
				movwf   tCountL
				movf    TMR1H,W
				movwf   tCountH
				clrf    TMR1L
				clrf    TMR1H
				bsf		T1CON,TMR1ON    ; start citac   - chyba 8 us


				bcf     STATUS,C
				rlf  	tCountL,F
				rlf 	tCountH,F                       ; deleno 128
				bcf     STATUS,C
				rlf		tCountL,F
				rlf 	tCountH,F                       ; deleno 64             
			;----------
			;       movf    tCountH,W
			;       movwf   sbuf
			;       call    send_RS
			;       call    cekejS
			;----------
				movlw   d'4'
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _int_ir_error
				movlw   d'4'                    ;8   
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _int_ir_SHARP   ; 0,3ms

				movlw   d'4'                    ;12
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _int_ir_error   
				movlw   d'5'                    ;17
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _int_ir_RC5             ;0.89

				movlw   d'15'                   ;32
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _int_ir_error
				movlw   d'12'                   ;44
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _int_ir_SIRC    ; 2.4

				movlw   d'4'                    ;48
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _int_ir_error
				movlw   d'14'                   ;62
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _int_ir_PANASONIC       ; 3.5

				movlw   d'4'                    ;66 
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _int_ir_error
				movlw   d'12'                   ;78
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _int_ir_MITSUBISHI      ;4.5    

				movlw   d'47'                   ;125 
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _int_ir_error
				movlw   d'32'                   ;157
				subwf   tCountH,F
				btfss   STATUS,C                ; <> 0
				goto    _int_ir_NEC             ;9      
				goto    _int_ir_error

_int_ir_SHARP          
				bcf		IR_STATUS,opak_povoleno
				bsf		IR_STATUS,start2                           
;				movlw   d'14'
;				movwf   kodIndex
				bsf  	MY_STATUS,IR_ACT
				movlw   0x03
				andwf   MY_STATUS,F
				bsf		MY_STATUS,IR_SHARP
				clrf    kod
				clrf    kod_1
				bcf 	IR_STATUS,start_kal	
				return
_int_ir_RC5                     
				bcf		IR_STATUS,opak_povoleno
				bcf 	IR_STATUS,pulbit                        
				movlw   d'13'
				movwf   kodIndex
				bsf   	MY_STATUS,IR_ACT
				movlw   0x03
				andwf   MY_STATUS,F
				bsf  	MY_STATUS,IR_RC5
				clrf    kod
				clrf    kod_1
				bcf 	IR_STATUS,start_kal	
				return
_int_ir_SIRC
				bcf		IR_STATUS,opak_povoleno
				movlw   d'12'
				movwf   kodIndex
				bsf 	MY_STATUS,IR_ACT
				movlw   0x03
				andwf   MY_STATUS,F
				bsf  	MY_STATUS,IR_SIRC
				bcf 	IR_STATUS,start_kal	
				return
_int_ir_PANASONIC
				bcf		IR_STATUS,opak_povoleno
				bsf		IR_STATUS,start2                        
				movlw   d'48'
				movwf   kodIndex
				bsf		MY_STATUS,IR_ACT
				movlw   0x03
				andwf   MY_STATUS,F
				bsf  	MY_STATUS,IR_PANASONIC
				clrf    kod
				clrf    kod_1
				clrf    kod_2
				clrf    kod_3
				clrf    kod_4
				clrf    kod_5
				bcf 	IR_STATUS,start_kal	
				return
_int_ir_MITSUBISHI
				bcf		IR_STATUS,opak_povoleno    ; zatim neumozneno
				bsf		IR_STATUS,start2                        
				movlw   d'32'
				movwf   kodIndex
				bsf		MY_STATUS,IR_ACT
				movlw   0x03
				andwf   MY_STATUS,F
				bsf 	MY_STATUS,IR_MITSUBISHI
				clrf    kod
				clrf    kod_1
				clrf    kod_2
				clrf    kod_3
				bcf 	IR_STATUS,start_kal	
				return
_int_ir_NEC             
			;	bcf		IR_STATUS,opak_povoleno  tady se nesmi zakazat, jinak to nebude brat opakovani s jednim bitem
				bsf		IR_STATUS,start2                        
				movlw   d'32'
				movwf   kodIndex
				bsf     MY_STATUS,IR_ACT
				movlw   0x03
				andwf   MY_STATUS,F
				bsf     MY_STATUS,IR_NEC
				bcf 	IR_STATUS,start_kal	
				return
_int_ir_error
				bcf 	MY_STATUS,IR_ACT
				bcf		IR_STATUS,opak_povoleno
				clrf	TMR1L			
				movlw	waitTime
				movwf	TMR1H				; prednastaveni na 10 ms
				bsf     T1CON,TMR1ON   	
				bsf		IR_STATUS,cekani
				bcf	   	IR_STATUS,start_kal	
		
		;		bcf		T1CON,TMR1ON    ; zastavim citac                
		;		movlw   'E'
		;		movwf   sbuf
		;		call    send_RS
		;		call    cekejS
		;		movf    tCountH,W
		;		movwf   sbuf
		;		call    send_RS
		;		call    cekejS

				return
;-------------------------------------

;***************************************************************************
init            
				clrf    GPIO
				movlw   0x07
				movwf   CMCON                   ; vypne komparator
				bsf     STATUS,RP0              ; prepne na banku 1     
				movlw   b'111001'               
	
				movwf   TRISIO                  ; nastaveni I/O   O= out
				movlw   b'111011'               

				movwf   WPU                     ; nastaveni pull-up

				bcf     OPTION_REG,NOT_GPPU     ; enable pull-up        
				movlw   b'001001'               

				movwf   IOC                                     ; interrupt on GP0 a GP3 change
				bsf  	INTCON,GPIE                     ; enable interrupt on GP0-GP4 change    
				bsf		INTCON,PEIE                     ; povoli interrupt periferii (timer 1)

				bsf 	PIE1,TMR1IE                     ; povoli int od timer1

				call    3ffh                    
		; 	    movlw   0xBf    ;!!!! natvrdo kal konstanta
				movwf   OSCCAL                          ; zapsani kalibracni konstanty

				bcf     STATUS,RP0              ; prepne na banku 0
				clrf    T1CON                   ; nataveni konfigurace citace1
				clrf    MY_STATUS               ; mazani pomocneho status registru      
				clrf    GPIO
_xi0    		btfss   GPIO,ir_in              ; ceka na log 1 z cidla
				goto    _xi0
				movf    GPIO,F  
_xi1 			btfsc   GPIO,s_in               ; ceka na RS v log 1 -- uroven -12V
				goto    _xi1
				movf    GPIO,F                  ; cteni portu pro zajisteni spravne zmeny
				movlw   b'11111000'             
				andwf   INTCON,F                ; delete all flags
				bsf     INTCON,GIE              ;xxxxxxxxxxxxx povoleni vsech interruptu     

				bcf     MY_STATUS,REC_RS
				bcf  	MY_STATUS,IR_ACT
				bcf   	IR_STATUS,start_kal	

;--------------------------------------------
				goto	prisloIR

start			
				clrf	RSTimeout
				clrf	RSTimeout_1
				clrf	RSTimeout_2
				incf	RSTimeout_2,F
				
cekamI			btfss   MY_STATUS,REC_RS
				goto    next1
				bcf		MY_STATUS,REC_RS
				movlw	'I'
				XORWF	rbuf,w
				btfss	STATUS,Z	
				goto	start
				
cekamR			btfss	MY_STATUS,REC_RS
				goto	cekamR1							
				bcf		MY_STATUS,REC_RS
				movlw	'R'
				XORWF	rbuf,w
				btfsc	STATUS,Z	
				goto	prisloIR
				goto	cekamR
cekamR1			decfsz	RSTimeout,F
				goto	cekamR3
				decfsz	RSTimeout_1,F
				goto	cekamR3
				decfsz	RSTimeout_2,F
cekamR3			goto	cekamR
				goto	start

prisloIR		movlw	'O'
				movwf	sbuf
				call    send_RS
				call	cekejS
				movlw	'K'
				movwf	sbuf
				call    send_RS
				call	cekejS
next1			

				goto    start
	
;*****************************************************
; sending to RS 232     9600 Bd, 8 Bit, bez parity, 1 stopBit
;*****************************************************
send_RS
				bsf		GPIO,s_out                      ;startbit               
				movlw   32                              ;       1    << t >>
				movwf   _delay                  ;       1       
sendrs0                                                 ; 104 ==9+ 3*t-1  ->> t=(104-9+1)/3
				decfsz  _delay,F                ;       1-2
				goto    sendrs0                 ;       2    
				movlw   0x08                    ;       1
				movwf   tmp                             ;       1
sendrs1                                                 ; 104 = 11+3*t -> t=(104-11)/3=31                                                                   
				bcf		STATUS,C                ;       1
				rrf		sbuf,F                  ;       1
				BTFSS	STATUS,C                ;       1-2
				bsf		GPIO,s_out              ;       1               tohle se preskoci, pokud je C=1         
				BTFSC   STATUS,C                ;***    1-2             tady uz to bude oboje   
				bcf  	GPIO,s_out              ;       1               tohle se preskoci, pokud je C=0         
				movlw   31                      ;       1   << t >>
				movwf   _delay                  ;       1
sendrs2
				decfsz  _delay,F                ;       1-2 \
				goto    sendrs2                 ;       2        >  3*_delay
				nop                             ;   1   /

				decfsz  tmp,F                           ;       1-2
				goto    sendrs1                 ;       2

				nop                     
				nop
				nop             
				nop
				nop
				bcf		GPIO,s_out              ;  1    stopbit 104 = 6+3*t +5*nop
				return


;**********************************************************************
;*              Receiving from RS-232
;**********************************************************************
receive_RS              ; + cca 3 + 8= 11  od interruptu
;               bcf             STATUS,RP0              ; prepne na banku 0     
				movlw   13                              ;       1    << t >>
				movwf   _delay1                 ;       1       
receivers0                                                      ; 52 ==10+ 3*t-1  ->> t=(52-14+1)/3
				decfsz  _delay1,F               ;       1-2      testuju to uz pri 51, protoze pak mam
				goto    receivers0              ;       2        2 us navic pri zadavani 0x08   

				btfss   GPIO,s_in               ;       1-2 - test startbitu
				goto    receiversE              ;       2       - neni platny znak

				movlw   0x08                    ;       1
				movwf   tmp                             ;       1       
				nop                                             ;       1
				nop                                             ;       1
receivers1
				movlw   32                              ;       1    << t >>
				movwf   _delay1                 ;       1                       
receivers2                                              ; 104 ==9+ 3*t-1  ->> t=(104-9+1)/3
				decfsz  _delay1,F               ;       1-2
				goto    receivers2              ;       2   
				bcf 	STATUS,C                ;       1
				bsf     GPIO,GP1
	;  	       	movf    GPIO,F
				btfss   GPIO,s_in               ;       1-2
				bsf     STATUS,C                ;       1       - nezapomenu na inverzi RS      
				rrf     rbuf,F                  ;       1               
				BCF     GPIO,GP1
		;       movf    GPIO
				decfsz  tmp,F                           ;       1-2     
				goto    receivers1              ;       2
receivers3                                              ; test stop bitu
				movlw   32                              ;       1    << t >>
				movwf   _delay1                 ;       1                       
				nop
receivers4                                              ; 104 ==7+ 3*t-1  ->> t=(104-7+1)/3
				decfsz  _delay1,F               ;       1-2
				goto    receivers4              ;       2   
				btfsc   GPIO,s_in               ;       1-2
				goto    receiversE              ;       2
				retlw   0                               ; OK    
receiversE
				retlw   0xff                    ;error

;**********************************************************************
;*              cekaci smycka
;**********************************************************************      
cekej			movlw   0xff
				movwf   _A
cykl1  			movlw   0xff
				movwf   _B
cykl    		nop
				decfsz  _B,F
				goto    cykl
				decfsz  _A,F
				goto    cykl1
				return

; zpozdeni na odeslani 1 bitu po rs, pouziva se po odeslani znaku, je-li potreba, na pockani 
; alespon dobu 1 stop bitu pred poslanim dalsiho...
cekejS
				movlw   40
				movwf   _B
_cekS 		 	decfsz  _B,F
				goto    _cekS
				return


		end


