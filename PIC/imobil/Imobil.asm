		list	p=PIC16F84		F=inhx8m
				
#define		SP1		PORTA,1		;out
#define 	SP2		PORTA,0		;out
#define 	SP3		PORTB,6		;out
#define 	TEST1	PORTB,7		;in
#define 	TEST2	PORTB,5		;in
#define 	TEST3	PORTB,2		;in
#define 	LED		PORTB,4		;out
#define 	BZUCAK	PORTB,0		;out
#define 	klicek	PORTB,1		;in
#define 	K_OUT	PORTA,3		;out
#define 	K_IN	PORTA,2		;in
#define 	TIMER	PORTB,3		;in/out

LIMIT 			EQU		0x07			; linit

key				EQU		0x0c			;family
key1			EQU		0x0d
key2			EQU		0x0e
key3			EQU		0x0f
key4			EQU		0x10
key5			EQU		0x11
key6			EQU		0x12
key7			EQU		0x13			;CRC
regA			EQU		0x14
regB			EQU		0x15
count			EQU		0x16			; pro vysilani povelu a vypocet CRC
pushW			EQU		0x17
CRC				EQU		0x18
countx			EQU		0x19
buffer			EQU		0x1A
bliknuti		EQU		0x1b
bliknuti_hi		EQU		0x1c
STAV			EQU		0x1d

napadeni		EQU		1
odjisteno		EQU		2
prilozeno		EQU		3

regC			EQU		0x1e
timeout_reg_lo	EQU		0x1f
timeout_reg_hi	EQU		0x20
pushStatus		EQU		0x21
int_pushW		EQU		0x22

;*********************************************************************************************
; MACRO definitions
;

cekejx			macro	doba	; min je 12, max 256							
				movlw	doba			;1	
				andlw	0xFC			;1
				sublw	0x07			;1
				movwf	countx			;1
				comf	countx,f		;1	
				rrf		countx,f		;1
				rrf		countx,f		;1		vydeleno 4
				;(7)
				nop						;1
				decfsz	countx,f		;1
				goto	$-2				;2				
				ENDM

cekejy			macro 	doba	; min je 1   time = doba*3+2
				movlw	doba			;1
				movwf	countx			;1
				decfsz	countx,f		;1
				goto	$-1				;2		>> cykl 3us
				ENDM

movff			macro	odkud,kam
				movf	odkud,w
				movwf	kam
				ENDM

BANK_1			macro
				bsf		STATUS,RP0			; nastavi banku 1
				ENDM

BANK_0			macro
				bcf		STATUS,RP0			; nastavi banku 0
				ENDM

;********************************************************************************************
	
;	ORG			2007h					;			CP WDR	
;	data		0x0FF

;********************************************************************************************
; EEPROM		

offset_kodu			EQU		0
offset_kodu_2		EQU		0x10
offset_deaktivace	EQU		0x0a
offset_napadeni		EQU		0x1a

;	ORG			0x2000
;	data		'v','1','.','0'
	ORG			0x2100+offset_kodu
	data		0x01,0xb3,0xea,0x96,0x00,0x00,0x00,0xec,0,0,0,0,0,0,0,0
	ORG			0x2100+offset_kodu_2
	data		0x01,0x37,0x36,0x90,0x01,0x00,0x00,0x07,0,0,0x67,0x01,0,0,0,0

;********************************************************************************************


			ORG		0x000		; reset vector		
			goto	init

			ORG		0x004		; interrupt vector
			goto	prerus

;********************************************************************************************


init		BANK_1
			movlw	b'11110100'
			movfw	TRISA			; 0= out	1=in
			movlw	b'10101110'
			movwf	TRISB

			BANK_0
			movlw	b'11110100'
			movwf	PORTA			
			movlw	b'10111110'
			movwf	PORTB

			BANK_1			
			movlw	b'11011111'			; nastaveni OPTION
			movwf	OPTION_REG
			movlw	b'00100000'			; nastaveni	INTCON
			movwf	INTCON

			BANK_0
			clrf	STAV
			btfsc	STATUS,NOT_TO
			goto	neniWDT
			
			call	pip
			bcf		LED			

neniWDT		bsf		STATUS,NOT_TO
			bcf 	SP1
			btfss	TEST1
			goto	$-2
			bcf		SP2
			btfss	TEST2
			goto 	$-2
			bcf		SP3
			btfss	TEST3
			goto 	$-2

			CLRWDT

; 	TEST na pripadnou stalou deaktivaci
			
			movlw	offset_deaktivace
			call	eecteni
			CLRWDT
			xorlw	0x76
			btfsc	STATUS,Z
			goto	stala_deaktivace_po_resetu

;	TEST na pripadne napadeni
			
			movlw	offset_napadeni
			call	eecteni
			CLRWDT
			xorlw	0x67
			btfsc	STATUS,Z
			bsf		STAV,napadeni

;*************************************************************************************************
;		S T A R T
;*************************************************************************************************

; smycka zajisteneho rezimu

start		CLRWDT					
			bsf		INTCON,GIE				; povoleni preruseni
			btfsc	STAV,odjisteno
			goto	start1

			btfsc	klicek					; zapnuty klicek
			call	poplach_klakson

start1		btfss	STAV,prilozeno			; pritomna button memory
			goto	neprilozeno

			bcf		INTCON,GIE				; zakaz peruseni
			btfsc	INTCON,GIE
			goto	$-2

			call	pritomen				;	01 - uspesna, 08 - napadeni
			CLRWDT
			movwf	pushW
			xorlw	0x01
			btfsc	STATUS,Z
			goto	odjisti_loop

			movf	pushW,w					; neautorizovany kod
			xorlw	0x08					; dalsi pokus po timeoutu
			btfsc	STATUS,Z
			call	long_cekej

neprilozeno	bsf		INTCON,GIE				; povoleni preruseni
			goto	start

;*************************************************************************************************
;	smycka programu pro odjisteny stav

odjisti_loop	
			bcf		INTCON,GIE
			btfsc	INTCON,GIE
			goto	$-2

			btfss	STAV,napadeni
			goto	OL02
			
			CLRWDT
			movlw	0						; smazani zaznamu z eeprom	
			movwf	EEDATA
			movlw	offset_napadeni
			movwf	EEADR
			call	eezapis
			bcf		STAV,napadeni

OL02		CLRWDT
			call	zahraj
			bsf		SP1
			btfsc	TEST1
			goto	$-2
			bsf		SP2
			btfsc	TEST2
			goto	$-2

			bsf		STAV,odjisteno
			bcf		LED
			bsf		INTCON,GIE				;povoleni preruseni
		
			movlw	0xff
			movwf	count

			clrf	timeout_reg_lo
			clrf	timeout_reg_hi

OL01		CLRWDT
			movf	timeout_reg_hi,w
			sublw	0x06
			btfss	STATUS,C
			call	vypis					; vypis poplachu, pokud je klic prilozen 3s
			btfsc	STAV,prilozeno
			goto	OL01					; cekam na oddaleni

OL03		btfsc	STAV,prilozeno
			goto	OL01
			decfsz	count,f
			goto	OL03
			
			clrf	timeout_reg_lo
			clrf	timeout_reg_hi

oddaleno	CLRWDT
			bsf		INTCON,GIE
			movf	timeout_reg_hi,w
			sublw	0x32					; doba akceptovani zadosti o stalou deaktivaci
			btfss	STATUS,C
			goto	klicek_nesepnuty		; zahajeni postupne deaktivace
		
			btfsc	klicek
			goto	klicek_sepnuty

			btfss	STAV,prilozeno
			goto	oddaleno

			bcf		INTCON,GIE
			btfsc	INTCON,GIE
			goto	$-2

			CLRWDT
			call	pritomen				; 01 autorize OK
			CLRWDT
			xorlw	0x01
			btfsc	STATUS,Z
			goto	stala_deaktivace

			bsf		INTCON,GIE
			goto 	oddaleno
	
			goto	$

;*******
klicek_sepnuty
			bcf		INTCON,GIE
			btfsc	INTCON,GIE
			goto	$-2
			
kst1		btfss	klicek
			goto 	vypnuty_zde
			CLRWDT		
			goto	kst1

; zde se vypnul klicek
vypnuty_zde
			clrf	timeout_reg_lo
			clrf	timeout_reg_hi

ks01		CLRWDT
			bsf		INTCON,GIE
			btfsc	klicek
			goto	klicek_sepnuty			; test zda se opet nezapnul
			movf	timeout_reg_hi,w
			sublw	0x37
			btfsc	STATUS,C
			goto	ks01					; zpozdeni asi 10 s

;**********
klicek_nesepnuty
			clrf	timeout_reg_lo
			clrf	timeout_reg_hi
			
			movlw	LIMIT
			movwf	regC

klicek_ne_loop
			CLRWDT
			btfsc	klicek
			goto	klicek_sepnuty
			
			btfss	STAV,prilozeno
			goto	knl2
			
			bcf		INTCON,GIE
			btfsc	INTCON,GIE
			goto	$-2
			
			CLRWDT
			call	pritomen				; 01 - autorizace OK
			CLRWDT
			xorlw 	0x01
			btfsc	STATUS,Z				; neuspesna autorizace
			goto	odjisti_loop

knl2		bsf		INTCON,GIE
			
			movf	timeout_reg_hi,w
			subwf	regC,w
			btfsc	STATUS,C
			goto	knl01					; zajisti 1 pipnuti pro kazde cislo
	
			movf	timeout_reg_hi,w
			sublw	regC
			incf	regC,f
			CLRWDT
			call	pip

knl01		movf	timeout_reg_hi,w
			sublw	LIMIT+0x1E   ;30 
			btfsc	STATUS,C
			goto 	klicek_ne_loop
	
			bcf		SP1
			btfss	TEST1
			goto	$-2
			
			bcf		SP2
			btfss	TEST2
			goto	$-2
	
			bcf		STAV,odjisteno			
			goto	start

;***************************************************************************************
;	S T A L A   D E A K T I V A C E 
;	zapisuje se do eeprom pro uchovani pri vypnuti napajeni
;	testuje se prilozeni klice pri kazdem probuzeni od WDT
;	po RESETU na zacatku programu otestuje, zda je navoleno deativovani a skoci sem
;	pozor, skok musi byt pres GOTO
;***************************************************************************************
stala_deaktivace
			CLRWDT
			movlw	0x76
			movwf	EEDATA
			movlw	offset_deaktivace
			movwf	EEADR
			call	eezapis
			call	zahraj2
			
			movlw	0x32
			movwf	count
			
sd01		CLRWDT
			call	test	
			xorlw	0x02
			btfss	STATUS,Z
			goto 	sd01				;neni prilozeno
			decfsz	count,f
			goto	sd01				; test na oddaleni alespon 50 cyklu

stala_deaktivace_po_resetu
			bsf		SP1
			btfsc	TEST1
			goto	$-2
			
			bsf		SP2
			btfsc	TEST2
			goto	$-2
			
			bsf		LED
			bcf		INTCON,GIE
			btfsc	INTCON,GIE
			goto	$-2

sd_loop		CLRWDT						; frekvence cca 1Hz
			cekejx	200
			call	test				;	0 = OK
			xorlw	0x00
			btfss	STATUS,Z
			goto	sd_loop				; neni prilozeno
			
			CLRWDT
			call	pritomen
			
			CLRWDT
			movwf	pushW
			xorlw	0x01
			btfsc	STATUS,Z
			goto	zruseni_deaktivace
		
			movf	pushW,w				; neautorizovany kod
			xorlw	0x08				; dalsi pokus po timeoutu
			btfsc	STATUS,Z
			call	long_cekej
			goto	sd_loop
			
			CLRWDT

zruseni_deaktivace
			movlw	0x00
			movwf	EEDATA
			movlw	offset_deaktivace
			movwf	EEADR
			call	eezapis
			bcf		LED
			bsf		INTCON,GIE
			goto	odjisti_loop

			goto 	$

;************************************************************************************************************
; obsluzne procedury


;************************************************************************************************************
; Generovani pipnuti na piezo

pip			bcf		INTCON,GIE
			btfsc	INTCON,GIE
			goto 	$-2

			movlw	0x05
			movwf	pushW
			movlw	0xff
			movwf	count
pipa		bsf		BZUCAK
			cekejy	0x17
			bcf		BZUCAK
			cekejy	0x17
			decfsz	count,f
			goto	pipa
			decfsz	pushW,f
			goto	pipa
		
			CLRWDT	
			bsf		INTCON,GIE
			return

;************************************************************************************************************			
;	poplach klaksonem

poplach_klakson
			bcf		INTCON,GIE
			btfsc	INTCON,GIE
			goto 	$-2

			CLRWDT
			movlw	0x67
			movwf	EEDATA
			movlw	offset_napadeni
			movwf	EEADR
			call	eezapis

			CLRWDT
			movlw	offset_napadeni+1					; zapise pocet napadeni
			call	eecteni
			CLRWDT
			movwf	EEDATA
			incf	EEDATA,f
			movlw	offset_napadeni+1
			movwf	EEADR
			call	eezapis
			CLRWDT

			clrf	timeout_reg_lo
			clrf	timeout_reg_hi
			bsf		STAV,odjisteno
			bsf		INTCON,GIE

poplach_klakson_loop
			bsf		INTCON,GIE
			CLRWDT
			bsf		SP3
			bsf		LED
			call	cekej
			bcf		LED
			CLRWDT
			btfsc	STAV,prilozeno
			goto	poplach01
			call	cekej
			CLRWDT	
			bcf		SP3
			bcf		LED
			call	cekej
			CLRWDT
					
	
			movlw	0x78
			subwf	timeout_reg_hi,w
			btfsc	STATUS,C
			goto	konec_poplachu
			btfss	STAV,prilozeno
			goto	poplach_klakson_loop

poplach01	bcf		INTCON,GIE
			btfsc	INTCON,GIE
			goto	$-2
			CLRWDT
			call	test							; pro oziveni klice
			call	pritomen						; 01 = OK
			CLRWDT
			xorlw	0x01
			btfss	STATUS,Z						; neuspesna autorizace
			goto 	poplach_klakson_loop
			call	zahraj

konec_poplachu
			bsf		STAV,napadeni
			bcf		STAV,odjisteno
			CLRWDT
			bcf		SP3
			btfss	TEST3
			goto	$-2

			return

;************************************************************************************************************						
;	vypis poctu poplachu
; 	pocet bliknuti je pocet polachu od posledniho vymazani

vypis		call	pip	
			bcf		LED
			bcf		INTCON,GIE
			btfsc	INTCON,GIE
			goto 	$-2
			CLRWDT
			clrf	buffer
			movlw	offset_napadeni+1
			movwf	EEDATA
			call	eecteni
			movwf	buffer
			movf	buffer,f
			btfsc	STATUS,Z
			goto 	vypis02

vypis01		CLRWDT
			call	cekej
			bsf		LED
			CLRWDT
			call	cekej
			bcf		LED
			CLRWDT
			call	cekej
			decfsz	buffer,f
			goto	vypis01
vypis02		CLRWDT
			call	cekej
			CLRWDT
			call	cekej
			CLRWDT
			call	cekej
			CLRWDT
			movlw	0x00								; vymazani poctu napadeni
			movwf	EEDATA
			movlw	offset_napadeni+1
			movwf	EEADR
			call	eezapis
			CLRWDT
			bsf		INTCON,GIE
			return

;***************************************************************************************************************
;	MACRO pro generovani tonu

ton			macro 	delka, vyska		;doba periodz v us, min 12 = 10 kHz , max 3072
			movlw	delka/0xff
			movwf	pushW
			movlw	delka-(delka/0xff)*0xff
			CLRWDT
			movwf	count
			
			bsf		BZUCAK
			cekejy	vyska/0x0c			; parametr*3 = cyklu >> *2 = us
			bcf		BZUCAK
			cekejy	vyska/0x0c			; 4 radky
			decfsz	count,f
			goto	$-0x0b
			decfsz	pushW,f
			goto	$-0x0f
			ENDM
;****************************************************************************************************************
;	generovani melodie
;
zahraj
			ton		1000,468
			ton		1000,425
			ton		1900,385
			ton		4000,363
			return

zahraj2
			ton		2000,363
			ton		1900,385
			ton		1000,425
			ton		1000,468
			return

;****************************************************************************************************************
;	obsluha 		I N T E R R U P T U 
;	neni potreba vetvit dle zdroju, pouziva se pouze jedno od T0
;	meni obsah countx, w, STATUS

prerus				; odjisteno >>> STAV, odjisteno=1
			movwf	int_pushW
			swapf	int_pushW,f
			
			swapf	STATUS,w
			movwf	pushStatus

			call	test					; 1 - zkrat	, 2 - neni , 0 - OK
			xorlw	0x00
			bcf		STAV,prilozeno
			btfsc	STATUS,Z
			bsf		STAV,prilozeno
	
			btfsc	STAV,odjisteno			;rozvetveni pro odjisteny stav
			goto	prerus_odjisteno

			incf	bliknuti,f
			btfss	STATUS,Z
			goto	prerus01				;nepretek
			incf	bliknuti_hi,f

			btfss	STAV,napadeni			;rychle blikani pri poplachu
			goto	prer00

			bcf		LED						;zhasni
			movlw	0x01
			xorwf	bliknuti_hi,w
			btfsc	STATUS,Z
			bsf		LED						; rozsvit		BLIK = 1

prer00		movlw	0x03
			subwf	bliknuti_hi,w
			btfsc	STATUS,C
			bsf		LED						; rozsvit		BLIK > 3

			movlw	0x05
			subwf	bliknuti_hi,w
			btfss	STATUS,C
			goto	prer01
			
			bcf		LED						;zhasni		>5
			clrf	bliknuti_hi

prer01		clrf	TMR0
			swapf	pushStatus,w
			movwf	STATUS					; obnoveni statusu
			swapf	int_pushW,w				; obnoveni W
			bcf		INTCON,T0IF
			retfie

prerus_odjisteno
			incf	timeout_reg_lo,f
			btfsc	STATUS,Z
			incf	timeout_reg_hi,f
prerus01

			clrf	TMR0
			swapf	pushStatus,W
			movwf	STATUS
			swapf	int_pushW,w
			bcf		INTCON,T0IF
			retfie	

;******************************************************************************************************************
;	procedury pro cteni a overovani kodu
;

pritomen
			bcf		INTCON,GIE
			; po testu je ve W  ...... 1 - zkrat, 2 - neni, 3 - OK
			call 	send_command
			call	read_kod
			call	vypocti_crc
			movf	key7,w
			xorwf	CRC,f
			btfss	STATUS,Z
			retlw	0xfd					; spatne prijmuty kod, chyba v CRC
			movlw	offset_kodu
			call	autorizace
			xorlw	0x01
			btfsc	STATUS,Z
			retlw	0x01				; prvni kod je OK
			movlw	offset_kodu_2
			call	autorizace	
			return

;---------------------------------------------------------------------------

autorizace	
			movwf	regA
			movlw	0x08
			movwf	count
			movlw	key
			movwf	FSR			
nacti_1		movf	regA,w
			call	eecteni
			xorwf	INDF,w
			btfss	STATUS,Z	
			retlw	0x08				; neutorizovany klic
			incf	FSR,f
			incf	regA,f
			decfsz	count,f
			goto	nacti_1
			retlw	0x01				; spravny kod
;-------------------------------------------------------------------------

read_kod								; nacteni kodu 1+6+1 byte
			movlw	0x08
			movwf	regB
			movlw	key
			movwf	FSR
read_byte
			clrf	buffer
			movlw	0x08
			movwf	count
read_bit	bsf		K_OUT
			goto	$+1					; 4 us
			bcf		K_OUT	
			cekejy	0x01				; 5 us
			bcf		STATUS,C
			btfsc	K_IN
			bsf		STATUS,C
			rrf		buffer,f
			cekejx	0x50
			decfsz	count,f
			goto	read_bit
			movf	buffer,w
			movwf	INDF
			incf	FSR,f
			decfsz	regB,f
			goto	read_byte
			return

; vyslani ridiciho prikazu

send_command
			movlw	0x00
			movwf	buffer
			movlw	0x08
			movwf	count
			bcf		STATUS,C
send_command1
			rrf		buffer,f
			btfss	STATUS,C
			goto	$+3
			call	write1	
			goto	$+2
			call	write0
			decfsz	count,f
			goto	send_command1
			return


; zapis 0 a 1 na kout

write1		bsf		K_OUT
			goto	$+1
			goto	$+1
			bcf		K_OUT
			cekejx	0x50			;160 us
			return

write0		bsf		K_OUT
			cekejx	0x32
			bcf		K_OUT
			cekejx	0x0c
			return

test				; je prilozeno ?
			bsf		K_OUT
			cekejx	0xfa
			cekejy	0x03			;	11us	
			bcf		K_OUT
			cekejy	0x05			;	17 us
			btfss	K_IN
			retlw	0x01			; zkrat na snimaci
			cekejx	0x23
			btfsc	K_IN
			retlw	0x02			; nic neni pritomno
			cekejx	0xfa			; konec presence pulse +  recovery time
			retlw	0x00			;l je pritomen a OK

;*******************************************************************************************************************************
; zacatek vypoctu CRC
vypocti_crc
			clrf	regB
			clrf	CRC
			clrf	pushW
			movlw	0x07
			movwf	count
			movlw	key
			movwf	FSR
loop		movf	INDF,w
			movwf	regA
			call	do_crc
			movf	CRC,w
			incf	FSR,f
			decfsz	count,f
			goto	loop
			return
		
do_crc		movwf	pushW		; zachova obsah W
			movwf	regA		; pom W
			movlw	0x08
			movwf	regB
crc_loop	movf	CRC,w		; ve w je CRC
			xorwf	regA,f		; crc xor vstup
			rrf		regA,f
			btfsc	STATUS,C
			xorlw	0x18
			movwf	CRC			; nove CRC
			rrf		CRC,f
			bcf		STATUS,C
			rrf		pushW,f
			btfsc	STATUS,C	; oprava na rotaci bez C
			bsf		pushW,7
			movf	pushW,w
			movwf	regA
			decfsz	regB,f
			goto	crc_loop
			return

;******************************************************************************************************************************
; procedury pro zapis a cteni EEPROM

eezapis					;	eedata, eeadr
			BANK_1
			bcf		INTCON,GIE
			btfsc	INTCON,GIE	
			goto	$-2
			
			bsf		EECON1,WREN
			movlw	0x55
			movwf	EECON2
			movlw	0xAA
			movwf	EECON2
			bsf		EECON1,WR
			btfsc	EECON1,WR
			goto 	$-1	
	
			btfss	EECON1,WRERR
			goto 	eezapisOK
			BANK_0
			retlw	1	
eezapisOK	BANK_0
			retlw	0
		
;--------------------------------------------------------

eecteni					; eeadr     ; data vraci do W
			movwf	EEADR
			BANK_1
			bsf		EECON1,RD
			BANK_0
			movf	EEDATA,w
			return

;******************************************************************************************************************
long_cekej	movlw	0x46
			movwf	count

long01		call	cekej
			CLRWDT
			decfsz	count,f
			goto	long01
			return
;--------------------------------------------------------
cekej		movwf	pushW
			movlw	0x50
			movwf	regA
cykl1		movlw	0xff
			movwf	regB
cykl		nop
			decfsz	regB,f
			goto	cykl
			decfsz	regA,f
			goto	cykl1
			movf	pushW,w
			return
			
							
;**********************************************************************************************************************
#include 	P16F84.inc	
			END
