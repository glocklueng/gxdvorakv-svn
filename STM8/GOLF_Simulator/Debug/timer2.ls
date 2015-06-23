   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  15                     	bsct
  16  0000               _PWM_Duty1:
  17  0000 32            	dc.b	50
  18  0001               _counterValue:
  19  0001 04e2          	dc.w	1250
  20                     .const:	section	.text
  21  0000               _BASE_DIF:
  22  0000 20            	dc.b	32
  23  0001               _LF_DIV:
  24  0001 0100          	dc.w	256
  25  0003               _HF_DIV:
  26  0003 01            	dc.b	1
  58                     ; 46 void TIM2_Init(void)
  58                     ; 47 { 
  60                     	switch	.text
  61  0000               _TIM2_Init:
  65                     ; 50 	TIM2->PSCR = 	0x07;			// 128
  67  0000 3507530c      	mov	21260,#7
  68                     ; 51 	TIM2->ARRH = (u8)(counterValue>>8);
  70  0004 550001530d    	mov	21261,_counterValue
  71                     ; 52 	TIM2->ARRL = (u8)(counterValue & 0x00FF);
  73  0009 b602          	ld	a,_counterValue+1
  74  000b a4ff          	and	a,#255
  75  000d c7530e        	ld	21262,a
  76                     ; 54 	TIM2->IER = 0x00;
  78  0010 725f5301      	clr	21249
  79                     ; 56 	TIM2->CCMR1 = 0x68;			// PWM1 mode  ch1
  81  0014 35685305      	mov	21253,#104
  82                     ; 57 	TIM2->CCMR2 = 0x40;			// inactive mode  ch2
  84  0018 35405306      	mov	21254,#64
  85                     ; 58 	TIM2->CCMR3 = 0x40;			// inactive mode  ch3
  87  001c 35405307      	mov	21255,#64
  88                     ; 60 	TIM2->CCER1	= TIM2_CCER1_CC1E;		// only PWM chanel 1
  90  0020 35015308      	mov	21256,#1
  91                     ; 61 	TIM2->CCER2	= 0;
  93  0024 725f5309      	clr	21257
  94                     ; 70 	PWM_SetDuty(1,PWM_Duty1);
  96  0028 b600          	ld	a,_PWM_Duty1
  97  002a 97            	ld	xl,a
  98  002b a601          	ld	a,#1
  99  002d 95            	ld	xh,a
 100  002e ad09          	call	_PWM_SetDuty
 102                     ; 74 	TIM2->EGR |= TIM2_EGR_UG;
 104  0030 72105304      	bset	21252,#0
 105                     ; 75 	TIM2->CR1 = TIM2_CR1_ARPE |TIM2_CR1_CEN;				;		// 0 000 010
 107  0034 35815300      	mov	21248,#129
 108                     ; 80 }
 112  0038 81            	ret
 166                     ; 142 void PWM_SetDuty (u8 chanel, u8 duty)
 166                     ; 143 {
 167                     	switch	.text
 168  0039               _PWM_SetDuty:
 170  0039 89            	pushw	x
 171  003a 89            	pushw	x
 172       00000002      OFST:	set	2
 175                     ; 145 	switch (chanel){
 177  003b 9e            	ld	a,xh
 178  003c a101          	cp	a,#1
 179  003e 262f          	jrne	L32
 182  0040               L12:
 183                     ; 146 		case 1:
 183                     ; 147 			PWM_Duty1 = duty;
 185  0040 7b04          	ld	a,(OFST+2,sp)
 186  0042 b700          	ld	_PWM_Duty1,a
 187                     ; 148 			if (duty == 100){
 189  0044 7b04          	ld	a,(OFST+2,sp)
 190  0046 a164          	cp	a,#100
 191  0048 2607          	jrne	L75
 192                     ; 149 				tmpDuty = counterValue+1;
 194  004a be01          	ldw	x,_counterValue
 195  004c 5c            	incw	x
 196  004d 1f01          	ldw	(OFST-1,sp),x
 198  004f 2012          	jra	L16
 199  0051               L75:
 200                     ; 151 				tmpDuty = counterValue/100 * PWM_Duty1;
 202  0051 be01          	ldw	x,_counterValue
 203  0053 90ae0064      	ldw	y,#100
 204  0057 65            	divw	x,y
 205  0058 b600          	ld	a,_PWM_Duty1
 206  005a 905f          	clrw	y
 207  005c 9097          	ld	yl,a
 208  005e cd0000        	call	c_imul
 210  0061 1f01          	ldw	(OFST-1,sp),x
 211  0063               L16:
 212                     ; 153 			TIM2->CCR1H =	(u8)(tmpDuty >> 8); 		// duty 1			
 214  0063 7b01          	ld	a,(OFST-1,sp)
 215  0065 c7530f        	ld	21263,a
 216                     ; 154 			TIM2->CCR1L = (u8)(tmpDuty & 0x00FF);					
 218  0068 7b02          	ld	a,(OFST+0,sp)
 219  006a a4ff          	and	a,#255
 220  006c c75310        	ld	21264,a
 221                     ; 156 		break;
 222  006f               L55:
 223                     ; 159 }
 225  006f               L32:
 226                     ; 157 		default: return;		
 227  006f               L01:
 230  006f 5b04          	addw	sp,#4
 231  0071 81            	ret
 266                     ; 169 u8 PWM_GetDuty (u8 chanel)
 266                     ; 170 {
 267                     	switch	.text
 268  0072               _PWM_GetDuty:
 272                     ; 171 	switch (chanel){
 274  0072 a101          	cp	a,#1
 275  0074 2603          	jrne	L76
 278  0076               L56:
 279                     ; 172 		case 1:
 279                     ; 173 			return PWM_Duty1;	
 281  0076 b600          	ld	a,_PWM_Duty1
 284  0078 81            	ret
 285  0079               L76:
 286                     ; 174 		default: return 0;		
 288  0079 4f            	clr	a
 291  007a 81            	ret
 331                     ; 187 void PWM_SetFrequency( u16 frequency)
 331                     ; 188 {
 332                     	switch	.text
 333  007b               _PWM_SetFrequency:
 335  007b 89            	pushw	x
 336  007c 5204          	subw	sp,#4
 337       00000004      OFST:	set	4
 340                     ; 189  	if (frequency == 0){
 342  007e a30000        	cpw	x,#0
 343  0081 2615          	jrne	L131
 344                     ; 190 		TIM2->PSCR = 	0x0f;		
 346  0083 350f530c      	mov	21260,#15
 347                     ; 191 		counterValue = 0xFFFF;
 349  0087 aeffff        	ldw	x,#65535
 350  008a bf01          	ldw	_counterValue,x
 351                     ; 192 		TIM2->ARRH = 0xFF;
 353  008c 35ff530d      	mov	21261,#255
 354                     ; 193 		TIM2->ARRL = 0xFF;		
 356  0090 35ff530e      	mov	21262,#255
 358  0094 ac3d013d      	jpf	L331
 359  0098               L131:
 360                     ; 194 	}else if (frequency < 10) {
 362  0098 1e05          	ldw	x,(OFST+1,sp)
 363  009a a3000a        	cpw	x,#10
 364  009d 2433          	jruge	L531
 365                     ; 195 		TIM2->PSCR = 	LF_PRESC;		
 367  009f 3508530c      	mov	21260,#8
 368                     ; 196 		counterValue =(u16)((FOSC / LF_DIV) / frequency);
 370  00a3 1e05          	ldw	x,(OFST+1,sp)
 371  00a5 cd0000        	call	c_uitolx
 373  00a8 96            	ldw	x,sp
 374  00a9 1c0001        	addw	x,#OFST-3
 375  00ac cd0000        	call	c_rtol
 377  00af aef424        	ldw	x,#62500
 378  00b2 bf02          	ldw	c_lreg+2,x
 379  00b4 ae0000        	ldw	x,#0
 380  00b7 bf00          	ldw	c_lreg,x
 381  00b9 96            	ldw	x,sp
 382  00ba 1c0001        	addw	x,#OFST-3
 383  00bd cd0000        	call	c_ldiv
 385  00c0 be02          	ldw	x,c_lreg+2
 386  00c2 bf01          	ldw	_counterValue,x
 387                     ; 197 		TIM2->ARRH = (u8)(counterValue >> 8);
 389  00c4 550001530d    	mov	21261,_counterValue
 390                     ; 198 		TIM2->ARRL = (u8)(counterValue & 0x00FF);			
 392  00c9 b602          	ld	a,_counterValue+1
 393  00cb a4ff          	and	a,#255
 394  00cd c7530e        	ld	21262,a
 396  00d0 206b          	jra	L331
 397  00d2               L531:
 398                     ; 199 	}else if (frequency < 250){		
 400  00d2 1e05          	ldw	x,(OFST+1,sp)
 401  00d4 a300fa        	cpw	x,#250
 402  00d7 2433          	jruge	L141
 403                     ; 200 		TIM2->PSCR = 	BASE_PRESC;		
 405  00d9 3505530c      	mov	21260,#5
 406                     ; 201 		counterValue =(u16)((FOSC / BASE_DIF) / frequency);
 408  00dd 1e05          	ldw	x,(OFST+1,sp)
 409  00df cd0000        	call	c_uitolx
 411  00e2 96            	ldw	x,sp
 412  00e3 1c0001        	addw	x,#OFST-3
 413  00e6 cd0000        	call	c_rtol
 415  00e9 aea120        	ldw	x,#41248
 416  00ec bf02          	ldw	c_lreg+2,x
 417  00ee ae0007        	ldw	x,#7
 418  00f1 bf00          	ldw	c_lreg,x
 419  00f3 96            	ldw	x,sp
 420  00f4 1c0001        	addw	x,#OFST-3
 421  00f7 cd0000        	call	c_ldiv
 423  00fa be02          	ldw	x,c_lreg+2
 424  00fc bf01          	ldw	_counterValue,x
 425                     ; 202 		TIM2->ARRH = (u8)(counterValue >> 8);
 427  00fe 550001530d    	mov	21261,_counterValue
 428                     ; 203 		TIM2->ARRL = (u8)(counterValue & 0x00FF);			
 430  0103 b602          	ld	a,_counterValue+1
 431  0105 a4ff          	and	a,#255
 432  0107 c7530e        	ld	21262,a
 434  010a 2031          	jra	L331
 435  010c               L141:
 436                     ; 205 		TIM2->PSCR = 	HF_PRESC;		
 438  010c 725f530c      	clr	21260
 439                     ; 206 		counterValue =(u16)((FOSC / HF_DIV) / frequency);
 441  0110 1e05          	ldw	x,(OFST+1,sp)
 442  0112 cd0000        	call	c_uitolx
 444  0115 96            	ldw	x,sp
 445  0116 1c0001        	addw	x,#OFST-3
 446  0119 cd0000        	call	c_rtol
 448  011c ae2400        	ldw	x,#9216
 449  011f bf02          	ldw	c_lreg+2,x
 450  0121 ae00f4        	ldw	x,#244
 451  0124 bf00          	ldw	c_lreg,x
 452  0126 96            	ldw	x,sp
 453  0127 1c0001        	addw	x,#OFST-3
 454  012a cd0000        	call	c_ldiv
 456  012d be02          	ldw	x,c_lreg+2
 457  012f bf01          	ldw	_counterValue,x
 458                     ; 207 		TIM2->ARRH = (u8)(counterValue >> 8);
 460  0131 550001530d    	mov	21261,_counterValue
 461                     ; 208 		TIM2->ARRL = (u8)(counterValue & 0x00FF);			
 463  0136 b602          	ld	a,_counterValue+1
 464  0138 a4ff          	and	a,#255
 465  013a c7530e        	ld	21262,a
 466  013d               L331:
 467                     ; 210 	TIM2->EGR |= TIM2_EGR_UG;	
 469  013d 72105304      	bset	21252,#0
 470                     ; 211 	PWM_SetDuty(1, PWM_Duty1);
 472  0141 b600          	ld	a,_PWM_Duty1
 473  0143 97            	ld	xl,a
 474  0144 a601          	ld	a,#1
 475  0146 95            	ld	xh,a
 476  0147 cd0039        	call	_PWM_SetDuty
 478                     ; 212 }
 481  014a 5b06          	addw	sp,#6
 482  014c 81            	ret
 509                     ; 222 u16 PWM_GetFrequency( void )
 509                     ; 223 {
 510                     	switch	.text
 511  014d               _PWM_GetFrequency:
 513  014d 5204          	subw	sp,#4
 514       00000004      OFST:	set	4
 517                     ; 225 	switch (TIM2->PSCR){
 519  014f c6530c        	ld	a,21260
 521                     ; 232 		default: return 0;
 522  0152 4d            	tnz	a
 523  0153 274e          	jreq	L151
 524  0155 a005          	sub	a,#5
 525  0157 2729          	jreq	L741
 526  0159 a003          	sub	a,#3
 527  015b 2703          	jreq	L541
 528  015d               L351:
 531  015d 5f            	clrw	x
 533  015e 201f          	jra	L02
 534  0160               L541:
 535                     ; 226 		case LF_PRESC:
 535                     ; 227 				return ((u16)((FOSC / LF_DIV) /counterValue)); 
 537  0160 be01          	ldw	x,_counterValue
 538  0162 cd0000        	call	c_uitolx
 540  0165 96            	ldw	x,sp
 541  0166 1c0001        	addw	x,#OFST-3
 542  0169 cd0000        	call	c_rtol
 544  016c aef424        	ldw	x,#62500
 545  016f bf02          	ldw	c_lreg+2,x
 546  0171 ae0000        	ldw	x,#0
 547  0174 bf00          	ldw	c_lreg,x
 548  0176 96            	ldw	x,sp
 549  0177 1c0001        	addw	x,#OFST-3
 550  017a cd0000        	call	c_ldiv
 552  017d be02          	ldw	x,c_lreg+2
 554  017f               L02:
 556  017f 5b04          	addw	sp,#4
 557  0181 81            	ret
 558  0182               L741:
 559                     ; 228 		case BASE_PRESC:
 559                     ; 229 				return ((u16)((FOSC / BASE_DIF) /counterValue)); 
 561  0182 be01          	ldw	x,_counterValue
 562  0184 cd0000        	call	c_uitolx
 564  0187 96            	ldw	x,sp
 565  0188 1c0001        	addw	x,#OFST-3
 566  018b cd0000        	call	c_rtol
 568  018e aea120        	ldw	x,#41248
 569  0191 bf02          	ldw	c_lreg+2,x
 570  0193 ae0007        	ldw	x,#7
 571  0196 bf00          	ldw	c_lreg,x
 572  0198 96            	ldw	x,sp
 573  0199 1c0001        	addw	x,#OFST-3
 574  019c cd0000        	call	c_ldiv
 576  019f be02          	ldw	x,c_lreg+2
 578  01a1 20dc          	jra	L02
 579  01a3               L151:
 580                     ; 230 		case HF_PRESC:
 580                     ; 231 				return ((u16)((FOSC / HF_DIV) /counterValue)); 
 582  01a3 be01          	ldw	x,_counterValue
 583  01a5 cd0000        	call	c_uitolx
 585  01a8 96            	ldw	x,sp
 586  01a9 1c0001        	addw	x,#OFST-3
 587  01ac cd0000        	call	c_rtol
 589  01af ae2400        	ldw	x,#9216
 590  01b2 bf02          	ldw	c_lreg+2,x
 591  01b4 ae00f4        	ldw	x,#244
 592  01b7 bf00          	ldw	c_lreg,x
 593  01b9 96            	ldw	x,sp
 594  01ba 1c0001        	addw	x,#OFST-3
 595  01bd cd0000        	call	c_ldiv
 597  01c0 be02          	ldw	x,c_lreg+2
 599  01c2 20bb          	jra	L02
 659                     	xdef	_HF_DIV
 660                     	xdef	_LF_DIV
 661                     	xdef	_BASE_DIF
 662                     	xdef	_counterValue
 663                     	xdef	_PWM_Duty1
 664                     	xdef	_PWM_GetFrequency
 665                     	xdef	_PWM_SetFrequency
 666                     	xdef	_PWM_GetDuty
 667                     	xdef	_PWM_SetDuty
 668                     	xdef	_TIM2_Init
 669                     	xref.b	c_lreg
 670                     	xref.b	c_x
 689                     	xref	c_ldiv
 690                     	xref	c_rtol
 691                     	xref	c_uitolx
 692                     	xref	c_imul
 693                     	end
