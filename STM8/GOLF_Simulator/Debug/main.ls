   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  91                     ; 67 void CLK_Init(CLK_TYPE target)
  91                     ; 68 {
  93                     	switch	.text
  94  0000               _CLK_Init:
  96  0000 88            	push	a
  97  0001 88            	push	a
  98       00000001      OFST:	set	1
 101                     ; 69 	const u8 CLK_DIVIDERS = 0x00;
 103  0002 0f01          	clr	(OFST+0,sp)
 104                     ; 71 	CLK->ECKR |=  0x01;
 106  0004 721050c1      	bset	20673,#0
 107                     ; 72 	CLK->CKDIVR = CLK_DIVIDERS;								// fCPU = fMASTER = 24 MHz
 109  0008 7b01          	ld	a,(OFST+0,sp)
 110  000a c750c6        	ld	20678,a
 111                     ; 73 	if ( CLK->CMSR != target){
 113  000d c650c3        	ld	a,20675
 114  0010 1102          	cp	a,(OFST+1,sp)
 115  0012 2715          	jreq	L54
 116                     ; 74 		CLK->SWCR = CLK_SWCR_SWEN;				// Enable CLK switch execution
 118  0014 350250c5      	mov	20677,#2
 119                     ; 75 		CLK->SWR = target;									// HSE selected as master CLK
 121  0018 7b02          	ld	a,(OFST+1,sp)
 122  001a c750c4        	ld	20676,a
 124  001d               L35:
 125                     ; 76 		while (!(CLK->SWCR & CLK_SWCR_SWIF));
 127  001d c650c5        	ld	a,20677
 128  0020 a508          	bcp	a,#8
 129  0022 27f9          	jreq	L35
 130                     ; 77 		if (CLK->CMSR != target	)			// check for CLK switch finished		
 132  0024 c650c3        	ld	a,20675
 133  0027 1102          	cp	a,(OFST+1,sp)
 134  0029               L54:
 135                     ; 83 	CLK->CANCCR = 0x00;		// can divider
 137  0029 725f50cb      	clr	20683
 138                     ; 84 }
 141  002d 85            	popw	x
 142  002e 81            	ret
 192                     ; 93 void main()
 192                     ; 94 {
 193                     	switch	.text
 194  002f               _main:
 196  002f 89            	pushw	x
 197       00000002      OFST:	set	2
 200                     ; 99 	CLK_Init(CLK_HSE);  
 202  0030 a6b4          	ld	a,#180
 203  0032 adcc          	call	_CLK_Init
 205                     ; 100 	disableInterrupts();
 208  0034 9b            sim
 210                     ; 101 	GPIO_Init();	
 213  0035 cd0000        	call	_GPIO_Init
 215                     ; 102 	TIM4_Init();
 217  0038 cd0000        	call	_TIM4_Init
 219                     ; 104 	TIM1_Init();
 221  003b cd0000        	call	_TIM1_Init
 223                     ; 105 	ADC_Init();
 225  003e cd0000        	call	_ADC_Init
 227                     ; 108   CAN_Init();												// init CAN - interface
 229  0041 cd0000        	call	_CAN_Init
 231                     ; 110 	enableInterrupts();	
 234  0044 9a            rim
 236                     ; 112 	CAN_Start();
 239  0045 cd0000        	call	_CAN_Start
 241                     ; 114 	CAN_TxMsg1.Length = 4;
 243  0048 35040013      	mov	_CAN_TxMsg1+6,#4
 244                     ; 115 	CAN_TxMsg1.Xtd = false;
 246  004c 3f11          	clr	_CAN_TxMsg1+4
 247                     ; 116 	CAN_TxMsg1.rtr = false;
 249  004e 3f12          	clr	_CAN_TxMsg1+5
 250                     ; 117 	CAN_TxMsg1.ID = 0x280;
 252  0050 ae0280        	ldw	x,#640
 253  0053 bf0f          	ldw	_CAN_TxMsg1+2,x
 254  0055 ae0000        	ldw	x,#0
 255  0058 bf0d          	ldw	_CAN_TxMsg1,x
 256                     ; 118 	CAN_TxMsg1.Data[0] =0 ;
 258  005a 3f14          	clr	_CAN_TxMsg1+7
 259                     ; 119 	CAN_TxMsg1.Data[1] =0;
 261  005c 3f15          	clr	_CAN_TxMsg1+8
 262  005e               L101:
 263                     ; 126 		if (	IsCAN_MSG1_Send()){
 265  005e cd0000        	call	_IsCAN_MSG1_Send
 267  0061 4d            	tnz	a
 268  0062 2733          	jreq	L501
 269                     ; 127 				tmp = ADC_GetValue(ADC_REV_CHANEL);
 271  0064 a607          	ld	a,#7
 272  0066 cd0000        	call	_ADC_GetValue
 274  0069 1f01          	ldw	(OFST-1,sp),x
 275                     ; 128 				tmp = tmp *24;
 277  006b 1e01          	ldw	x,(OFST-1,sp)
 278  006d 90ae0018      	ldw	y,#24
 279  0071 cd0000        	call	c_imul
 281  0074 1f01          	ldw	(OFST-1,sp),x
 282                     ; 129 				if ( tmp < 100 ){
 284  0076 1e01          	ldw	x,(OFST-1,sp)
 285  0078 a30064        	cpw	x,#100
 286  007b 2406          	jruge	L701
 287                     ; 130 					OIL_PRESS = false;
 289  007d 72175014      	bres	20500,#3
 291  0081 2004          	jra	L111
 292  0083               L701:
 293                     ; 132 					OIL_PRESS = true;
 295  0083 72165014      	bset	20500,#3
 296  0087               L111:
 297                     ; 135 				CAN_TxMsg1.Data[3] =(u8)(tmp >> 8) ;
 299  0087 7b01          	ld	a,(OFST-1,sp)
 300  0089 b717          	ld	_CAN_TxMsg1+10,a
 301                     ; 136 				CAN_TxMsg1.Data[2] =(u8)(tmp & 0x00FF);
 303  008b 7b02          	ld	a,(OFST+0,sp)
 304  008d a4ff          	and	a,#255
 305  008f b716          	ld	_CAN_TxMsg1+9,a
 306                     ; 137 				CAN_Write(&CAN_TxMsg1);
 308  0091 ae000d        	ldw	x,#_CAN_TxMsg1
 309  0094 cd0000        	call	_CAN_Write
 311  0097               L501:
 312                     ; 140 		if ( IsSpeedAdjustTime()){
 314  0097 cd0000        	call	_IsSpeedAdjustTime
 316  009a 4d            	tnz	a
 317  009b 2720          	jreq	L311
 318                     ; 141 				tmp = ADC_GetValue(ADC_SPEED_CHANEL);
 320  009d a605          	ld	a,#5
 321  009f cd0000        	call	_ADC_GetValue
 323  00a2 1f01          	ldw	(OFST-1,sp),x
 324                     ; 142 				tmp = tmp * 10;
 326  00a4 1e01          	ldw	x,(OFST-1,sp)
 327  00a6 90ae000a      	ldw	y,#10
 328  00aa cd0000        	call	c_imul
 330  00ad 1f01          	ldw	(OFST-1,sp),x
 331                     ; 143 				tmp = tmp/ 34;
 333  00af 1e01          	ldw	x,(OFST-1,sp)
 334  00b1 90ae0022      	ldw	y,#34
 335  00b5 65            	divw	x,y
 336  00b6 1f01          	ldw	(OFST-1,sp),x
 337                     ; 144 				PWM_SetFrequency(tmp);
 339  00b8 1e01          	ldw	x,(OFST-1,sp)
 340  00ba cd0000        	call	_PWM_SetFrequency
 342  00bd               L311:
 343                     ; 179 		if (GetLedState()){
 345  00bd cd0000        	call	_GetLedState
 347  00c0 4d            	tnz	a
 348  00c1 2706          	jreq	L511
 349                     ; 180 			LED_ON;
 351  00c3 72135014      	bres	20500,#1
 353  00c7 2095          	jra	L101
 354  00c9               L511:
 355                     ; 182 			LED_OFF;
 357  00c9 72125014      	bset	20500,#1
 358  00cd 208f          	jra	L101
 754                     	xdef	_main
 755                     	xdef	_CLK_Init
 756                     	switch	.ubsct
 757  0000               _BoardStatus:
 758  0000 0000          	ds.b	2
 759                     	xdef	_BoardStatus
 760  0002               _CAN_FilterRecStatus:
 761  0002 000000000000  	ds.b	10
 762                     	xdef	_CAN_FilterRecStatus
 763  000c               _CAN_MsgRecStatus:
 764  000c 00            	ds.b	1
 765                     	xdef	_CAN_MsgRecStatus
 766  000d               _CAN_TxMsg1:
 767  000d 000000000000  	ds.b	18
 768                     	xdef	_CAN_TxMsg1
 769                     	xref	_ADC_GetValue
 770                     	xref	_ADC_Init
 771                     	xref	_PWM_SetFrequency
 772                     	xref	_TIM1_Init
 773                     	xref	_IsSpeedAdjustTime
 774                     	xref	_IsCAN_MSG1_Send
 775                     	xref	_GetLedState
 776                     	xref	_TIM4_Init
 777                     	xref	_CAN_Write
 778                     	xref	_CAN_Start
 779                     	xref	_CAN_Init
 780                     	xref	_GPIO_Init
 781                     	xref.b	c_x
 801                     	xref	c_imul
 802                     	end
