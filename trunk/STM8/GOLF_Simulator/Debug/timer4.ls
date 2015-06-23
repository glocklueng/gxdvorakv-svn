   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  15                     .const:	section	.text
  16  0000               _LED_ON_TIME:
  17  0000 01f4          	dc.w	500
  18  0002               _LED_OFF_TIME:
  19  0002 251c          	dc.w	9500
  20  0004               _CAN_MSG1_TIME:
  21  0004 0064          	dc.w	100
  22  0006               _SPEED_ADJ_TIME:
  23  0006 01f4          	dc.w	500
  58                     ; 46 void TIM4_Init(void)
  58                     ; 47 {      
  60                     	switch	.text
  61  0000               _TIM4_Init:
  65                     ; 48 		TIM4->PSCR = 0x04;           // fmaster / 16
  67  0000 35045345      	mov	21317,#4
  68                     ; 49 		TIM4->ARR = 100;          	// auto reload register			fMASTER = 16MHz		-> 100us
  70  0004 35645346      	mov	21318,#100
  71                     ; 50 		TIM4->IER |= TIM4_IER_UIE;	// interrupt enable
  73  0008 72105341      	bset	21313,#0
  74                     ; 51 		TIM4->CR1=0x81;							// timer enable	
  76  000c 35815340      	mov	21312,#129
  77                     ; 53 		ledCounter = LED_ON_TIME;
  79  0010 ae01f4        	ldw	x,#500
  80  0013 bf06          	ldw	_ledCounter,x
  81                     ; 54 		CAN_MSG1_counter = CAN_MSG1_TIME;
  83  0015 ae0064        	ldw	x,#100
  84  0018 bf04          	ldw	_CAN_MSG1_counter,x
  85                     ; 55 		SpeedAdjust_counter= SPEED_ADJ_TIME;
  87  001a ae01f4        	ldw	x,#500
  88  001d bf02          	ldw	_SpeedAdjust_counter,x
  89                     ; 56 }
  92  001f 81            	ret
 128                     ; 69 @far @interrupt void TIM4_UPD_OVF_Interrupt (void)
 128                     ; 70 {  
 130                     	switch	.text
 131  0020               f_TIM4_UPD_OVF_Interrupt:
 135                     ; 72 		TIM4->SR1 = 0;
 137  0020 725f5342      	clr	21314
 138                     ; 74 		if (!--ledCounter){
 140  0024 be06          	ldw	x,_ledCounter
 141  0026 1d0001        	subw	x,#1
 142  0029 bf06          	ldw	_ledCounter,x
 143  002b 261b          	jrne	L13
 144                     ; 75 			if (ledState){	
 146                     	btst	_ledState
 147  0032 240b          	jruge	L33
 148                     ; 76 				ledCounter = LED_OFF_TIME;
 150  0034 ae251c        	ldw	x,#9500
 151  0037 bf06          	ldw	_ledCounter,x
 152                     ; 77 				ledState = false;
 154  0039 72110003      	bres	_ledState
 156  003d 2009          	jra	L13
 157  003f               L33:
 158                     ; 79 				ledCounter = LED_ON_TIME;
 160  003f ae01f4        	ldw	x,#500
 161  0042 bf06          	ldw	_ledCounter,x
 162                     ; 80 				ledState = true;				
 164  0044 72100003      	bset	_ledState
 165  0048               L13:
 166                     ; 83 		if ( timeoutCounter ){
 168  0048 be00          	ldw	x,_timeoutCounter
 169  004a 270d          	jreq	L73
 170                     ; 84 			if (--timeoutCounter  == 0) {
 172  004c be00          	ldw	x,_timeoutCounter
 173  004e 1d0001        	subw	x,#1
 174  0051 bf00          	ldw	_timeoutCounter,x
 175  0053 2604          	jrne	L73
 176                     ; 85 				timeoutState = true;
 178  0055 72100000      	bset	_timeoutState
 179  0059               L73:
 180                     ; 89 		if (!--CAN_MSG1_counter){
 182  0059 be04          	ldw	x,_CAN_MSG1_counter
 183  005b 1d0001        	subw	x,#1
 184  005e bf04          	ldw	_CAN_MSG1_counter,x
 185  0060 2609          	jrne	L34
 186                     ; 90 			CAN_MSG1_counter = CAN_MSG1_TIME;
 188  0062 ae0064        	ldw	x,#100
 189  0065 bf04          	ldw	_CAN_MSG1_counter,x
 190                     ; 91 			CAN_MSG1_state = true;
 192  0067 72100002      	bset	_CAN_MSG1_state
 193  006b               L34:
 194                     ; 94 		if (!--SpeedAdjust_counter){
 196  006b be02          	ldw	x,_SpeedAdjust_counter
 197  006d 1d0001        	subw	x,#1
 198  0070 bf02          	ldw	_SpeedAdjust_counter,x
 199  0072 2609          	jrne	L54
 200                     ; 95 			SpeedAdjust_counter = SPEED_ADJ_TIME;
 202  0074 ae01f4        	ldw	x,#500
 203  0077 bf02          	ldw	_SpeedAdjust_counter,x
 204                     ; 96 			SpeedAdjust_state = true;
 206  0079 72100001      	bset	_SpeedAdjust_state
 207  007d               L54:
 208                     ; 99 }
 211  007d 80            	iret
 235                     ; 108 bool GetLedState(void)
 235                     ; 109 {
 237                     	switch	.text
 238  007e               _GetLedState:
 242                     ; 110 	return ledState;
 244                     	btst	_ledState
 245  0083 2404          	jruge	L21
 246  0085 a601          	ld	a,#1
 247  0087 2001          	jra	L41
 248  0089               L21:
 249  0089 4f            	clr	a
 250  008a               L41:
 253  008a 81            	ret
 278                     ; 119 bool IsCAN_MSG1_Send(void)
 278                     ; 120 {
 279                     	switch	.text
 280  008b               _IsCAN_MSG1_Send:
 284                     ; 121 	if (CAN_MSG1_state){
 286                     	btst	_CAN_MSG1_state
 287  0090 2407          	jruge	L76
 288                     ; 122 			CAN_MSG1_state = false;
 290  0092 72110002      	bres	_CAN_MSG1_state
 291                     ; 123 		return true;
 293  0096 a601          	ld	a,#1
 296  0098 81            	ret
 297  0099               L76:
 298                     ; 124 	}else return false;
 300  0099 4f            	clr	a
 303  009a 81            	ret
 328                     ; 134 bool IsSpeedAdjustTime(void)
 328                     ; 135 {
 329                     	switch	.text
 330  009b               _IsSpeedAdjustTime:
 334                     ; 136 	if (SpeedAdjust_state){
 336                     	btst	_SpeedAdjust_state
 337  00a0 2407          	jruge	L301
 338                     ; 137 			SpeedAdjust_state = false;
 340  00a2 72110001      	bres	_SpeedAdjust_state
 341                     ; 138 		return true;
 343  00a6 a601          	ld	a,#1
 346  00a8 81            	ret
 347  00a9               L301:
 348                     ; 139 	}else return false;
 350  00a9 4f            	clr	a
 353  00aa 81            	ret
 389                     ; 151 void SetTimeoutTime(const u16 time)
 389                     ; 152 {
 390                     	switch	.text
 391  00ab               _SetTimeoutTime:
 395                     ; 153 	timeoutCounter = time;
 397  00ab bf00          	ldw	_timeoutCounter,x
 398                     ; 154 	timeoutState = false;
 400  00ad 72110000      	bres	_timeoutState
 401                     ; 155 }
 404  00b1 81            	ret
 429                     ; 165 bool IsTimeoutExpired(void)
 429                     ; 166 {
 430                     	switch	.text
 431  00b2               _IsTimeoutExpired:
 435                     ; 167 	return timeoutState;	
 437                     	btst	_timeoutState
 438  00b7 2404          	jruge	L62
 439  00b9 a601          	ld	a,#1
 440  00bb 2001          	jra	L03
 441  00bd               L62:
 442  00bd 4f            	clr	a
 443  00be               L03:
 446  00be 81            	ret
 574                     	xdef	f_TIM4_UPD_OVF_Interrupt
 575                     .bit:	section	.data,bit
 576  0000               _timeoutState:
 577  0000 00            	ds.b	1
 578                     	xdef	_timeoutState
 579                     	switch	.ubsct
 580  0000               _timeoutCounter:
 581  0000 0000          	ds.b	2
 582                     	xdef	_timeoutCounter
 583                     	switch	.bit
 584  0001               _SpeedAdjust_state:
 585  0001 00            	ds.b	1
 586                     	xdef	_SpeedAdjust_state
 587                     	switch	.ubsct
 588  0002               _SpeedAdjust_counter:
 589  0002 0000          	ds.b	2
 590                     	xdef	_SpeedAdjust_counter
 591                     	switch	.bit
 592  0002               _CAN_MSG1_state:
 593  0002 00            	ds.b	1
 594                     	xdef	_CAN_MSG1_state
 595                     	switch	.ubsct
 596  0004               _CAN_MSG1_counter:
 597  0004 0000          	ds.b	2
 598                     	xdef	_CAN_MSG1_counter
 599                     	switch	.bit
 600  0003               _ledState:
 601  0003 00            	ds.b	1
 602                     	xdef	_ledState
 603                     	switch	.ubsct
 604  0006               _ledCounter:
 605  0006 0000          	ds.b	2
 606                     	xdef	_ledCounter
 607                     	xdef	_SPEED_ADJ_TIME
 608                     	xdef	_CAN_MSG1_TIME
 609                     	xdef	_LED_OFF_TIME
 610                     	xdef	_LED_ON_TIME
 611                     	xdef	_SetTimeoutTime
 612                     	xdef	_IsTimeoutExpired
 613                     	xdef	_IsSpeedAdjustTime
 614                     	xdef	_IsCAN_MSG1_Send
 615                     	xdef	_GetLedState
 616                     	xdef	_TIM4_Init
 636                     	end
