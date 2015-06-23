   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  15                     .const:	section	.text
  16  0000               _FOSC:
  17  0000 00f42400      	dc.l	16000000
  18                     	bsct
  19  0000               _PWM1_DC:
  20  0000 32            	dc.b	50
  50                     ; 30 void TIM1_Init(void)
  50                     ; 31 { 
  52                     	switch	.text
  53  0000               _TIM1_Init:
  57                     ; 38 	PWM_SetFrequency(0);
  59  0000 5f            	clrw	x
  60  0001 ad29          	call	_PWM_SetFrequency
  62                     ; 40 	TIM1->IER = 0x00;
  64  0003 725f5254      	clr	21076
  65                     ; 42 	TIM1->CCMR1 = 0x40;			// inactive mode  ch1
  67  0007 35405258      	mov	21080,#64
  68                     ; 43 	TIM1->CCMR2 = 0x40;			// inactive mode  ch2
  70  000b 35405259      	mov	21081,#64
  71                     ; 44 	TIM1->CCMR3 = 0x40;			// inactive mode  ch3
  73  000f 3540525a      	mov	21082,#64
  74                     ; 45 	TIM1->CCMR4 = 0x68;			// PWM1 mode  ch4
  76  0013 3568525b      	mov	21083,#104
  77                     ; 47 	TIM1->CCER1	= 0;
  79  0017 725f525c      	clr	21084
  80                     ; 48 	TIM1->CCER2	= TIM1_CCER2_CC4E;		// only PWM chanel 1
  82  001b 3510525d      	mov	21085,#16
  83                     ; 49 	TIM1->BKR |= 0x80;
  85  001f 721e526d      	bset	21101,#7
  86                     ; 52 	TIM1->EGR |= TIM1_EGR_UG;
  88  0023 72105257      	bset	21079,#0
  89                     ; 53 	TIM1->CR1 = TIM1_CR1_ARPE |TIM1_CR1_CEN;				;		// 0 000 010
  91  0027 35815250      	mov	21072,#129
  92                     ; 57 }
  96  002b 81            	ret
 168                     ; 70 void PWM_SetFrequency( u16 frequency)
 168                     ; 71 {
 169                     	switch	.text
 170  002c               _PWM_SetFrequency:
 172  002c 89            	pushw	x
 173  002d 520d          	subw	sp,#13
 174       0000000d      OFST:	set	13
 177                     ; 75 	bool ug = false;
 179  002f 4f            	clr	a
 180  0030 6b05          	ld	(OFST-8,sp),a
 181                     ; 77 	if (frequency == 0){
 183  0032 a30000        	cpw	x,#0
 184  0035 2614          	jrne	L75
 185                     ; 78 		TIM1->PSCRH = 	0xFF;		
 187  0037 35ff5260      	mov	21088,#255
 188                     ; 79 		TIM1->PSCRL = 	0xFF;				
 190  003b 35ff5261      	mov	21089,#255
 191                     ; 80 		TIM1->ARRH = 0xFF;
 193  003f 35ff5262      	mov	21090,#255
 194                     ; 81 		TIM1->ARRL = 0xFF;		
 196  0043 35ff5263      	mov	21091,#255
 198  0047 acd100d1      	jpf	L16
 199  004b               L75:
 200                     ; 83 		if (TIM1->PSCRH > 0x00 ) ug = true;
 202  004b 725d5260      	tnz	21088
 203  004f 2704          	jreq	L36
 206  0051 a601          	ld	a,#1
 207  0053 6b05          	ld	(OFST-8,sp),a
 208  0055               L36:
 209                     ; 84 		tmp_div = FOSC/frequency;
 211  0055 1e0e          	ldw	x,(OFST+1,sp)
 212  0057 cd0000        	call	c_uitolx
 214  005a 96            	ldw	x,sp
 215  005b 1c0001        	addw	x,#OFST-12
 216  005e cd0000        	call	c_rtol
 218  0061 ae2400        	ldw	x,#9216
 219  0064 bf02          	ldw	c_lreg+2,x
 220  0066 ae00f4        	ldw	x,#244
 221  0069 bf00          	ldw	c_lreg,x
 222  006b 96            	ldw	x,sp
 223  006c 1c0001        	addw	x,#OFST-12
 224  006f cd0000        	call	c_ludv
 226  0072 96            	ldw	x,sp
 227  0073 1c0006        	addw	x,#OFST-7
 228  0076 cd0000        	call	c_rtol
 230                     ; 87 		tmp_prsc = tmp_div/65536;
 232  0079 1e06          	ldw	x,(OFST-7,sp)
 233  007b 1f0a          	ldw	(OFST-3,sp),x
 234                     ; 88 		tmp_prsc++;
 236  007d 1e0a          	ldw	x,(OFST-3,sp)
 237  007f 1c0001        	addw	x,#1
 238  0082 1f0a          	ldw	(OFST-3,sp),x
 239                     ; 90 		tmp_cnt = tmp_div/tmp_prsc;
 241  0084 1e0a          	ldw	x,(OFST-3,sp)
 242  0086 cd0000        	call	c_uitolx
 244  0089 96            	ldw	x,sp
 245  008a 1c0001        	addw	x,#OFST-12
 246  008d cd0000        	call	c_rtol
 248  0090 96            	ldw	x,sp
 249  0091 1c0006        	addw	x,#OFST-7
 250  0094 cd0000        	call	c_ltor
 252  0097 96            	ldw	x,sp
 253  0098 1c0001        	addw	x,#OFST-12
 254  009b cd0000        	call	c_ludv
 256  009e be02          	ldw	x,c_lreg+2
 257  00a0 1f0c          	ldw	(OFST-1,sp),x
 258                     ; 92 		tmp_prsc--;
 260  00a2 1e0a          	ldw	x,(OFST-3,sp)
 261  00a4 1d0001        	subw	x,#1
 262  00a7 1f0a          	ldw	(OFST-3,sp),x
 263                     ; 94 		TIM1->ARRH = (u8)(tmp_cnt >> 8);
 265  00a9 7b0c          	ld	a,(OFST-1,sp)
 266  00ab c75262        	ld	21090,a
 267                     ; 95 		TIM1->ARRL = (u8)(tmp_cnt & 0x00FF);	
 269  00ae 7b0d          	ld	a,(OFST+0,sp)
 270  00b0 a4ff          	and	a,#255
 271  00b2 c75263        	ld	21091,a
 272                     ; 96 		TIM1->PSCRH = (u8)(tmp_prsc >> 8);		
 274  00b5 7b0a          	ld	a,(OFST-3,sp)
 275  00b7 c75260        	ld	21088,a
 276                     ; 97 		TIM1->PSCRL = (u8)(tmp_prsc & 0x00FF);		
 278  00ba 7b0b          	ld	a,(OFST-2,sp)
 279  00bc a4ff          	and	a,#255
 280  00be c75261        	ld	21089,a
 281                     ; 99 		tmp_cnt >>= 1;
 283  00c1 040c          	srl	(OFST-1,sp)
 284  00c3 060d          	rrc	(OFST+0,sp)
 285                     ; 101 		TIM1->CCR4H =	(u8)(tmp_cnt >> 8); 		// duty 1			
 287  00c5 7b0c          	ld	a,(OFST-1,sp)
 288  00c7 c7526b        	ld	21099,a
 289                     ; 102 		TIM1->CCR4L = (u8)(tmp_cnt & 0x00FF);						
 291  00ca 7b0d          	ld	a,(OFST+0,sp)
 292  00cc a4ff          	and	a,#255
 293  00ce c7526c        	ld	21100,a
 294  00d1               L16:
 295                     ; 106 	if (ug) {
 297  00d1 0d05          	tnz	(OFST-8,sp)
 298  00d3 2704          	jreq	L56
 299                     ; 107 		TIM1->EGR |= TIM1_EGR_UG;	
 301  00d5 72105257      	bset	21079,#0
 302  00d9               L56:
 303                     ; 109 }
 306  00d9 5b0f          	addw	sp,#15
 307  00db 81            	ret
 360                     ; 119 u16 PWM_GetFrequency( void )
 360                     ; 120 {
 361                     	switch	.text
 362  00dc               _PWM_GetFrequency:
 364  00dc 520c          	subw	sp,#12
 365       0000000c      OFST:	set	12
 368                     ; 125 	tmp_cnt = (u16)(TIM1->ARRH<<8)+TIM1->ARRL;
 370  00de c65262        	ld	a,21090
 371  00e1 5f            	clrw	x
 372  00e2 97            	ld	xl,a
 373  00e3 4f            	clr	a
 374  00e4 02            	rlwa	x,a
 375  00e5 01            	rrwa	x,a
 376  00e6 cb5263        	add	a,21091
 377  00e9 2401          	jrnc	L21
 378  00eb 5c            	incw	x
 379  00ec               L21:
 380  00ec 02            	rlwa	x,a
 381  00ed 1f0b          	ldw	(OFST-1,sp),x
 382  00ef 01            	rrwa	x,a
 383                     ; 126 	tmp_prsc = (u16)(TIM1->PSCRH<<8)+TIM1->PSCRL;
 385  00f0 c65260        	ld	a,21088
 386  00f3 5f            	clrw	x
 387  00f4 97            	ld	xl,a
 388  00f5 4f            	clr	a
 389  00f6 02            	rlwa	x,a
 390  00f7 01            	rrwa	x,a
 391  00f8 cb5261        	add	a,21089
 392  00fb 2401          	jrnc	L41
 393  00fd 5c            	incw	x
 394  00fe               L41:
 395  00fe 02            	rlwa	x,a
 396  00ff 1f09          	ldw	(OFST-3,sp),x
 397  0101 01            	rrwa	x,a
 398                     ; 127 	if (tmp_cnt > 0 && tmp_prsc > 0)	tmpFreq = FOSC/tmp_cnt/tmp_cnt;
 400  0102 1e0b          	ldw	x,(OFST-1,sp)
 401  0104 273a          	jreq	L511
 403  0106 1e09          	ldw	x,(OFST-3,sp)
 404  0108 2736          	jreq	L511
 407  010a 1e0b          	ldw	x,(OFST-1,sp)
 408  010c cd0000        	call	c_uitolx
 410  010f 96            	ldw	x,sp
 411  0110 1c0005        	addw	x,#OFST-7
 412  0113 cd0000        	call	c_rtol
 414  0116 1e0b          	ldw	x,(OFST-1,sp)
 415  0118 cd0000        	call	c_uitolx
 417  011b 96            	ldw	x,sp
 418  011c 1c0001        	addw	x,#OFST-11
 419  011f cd0000        	call	c_rtol
 421  0122 ae2400        	ldw	x,#9216
 422  0125 bf02          	ldw	c_lreg+2,x
 423  0127 ae00f4        	ldw	x,#244
 424  012a bf00          	ldw	c_lreg,x
 425  012c 96            	ldw	x,sp
 426  012d 1c0001        	addw	x,#OFST-11
 427  0130 cd0000        	call	c_ludv
 429  0133 96            	ldw	x,sp
 430  0134 1c0005        	addw	x,#OFST-7
 431  0137 cd0000        	call	c_ludv
 433  013a be02          	ldw	x,c_lreg+2
 434  013c 1f0b          	ldw	(OFST-1,sp),x
 436  013e 2005          	jra	L711
 437  0140               L511:
 438                     ; 128 	else tmpFreq = 0xFFFF;
 440  0140 aeffff        	ldw	x,#65535
 441  0143 1f0b          	ldw	(OFST-1,sp),x
 442  0145               L711:
 443                     ; 129 	return (tmpFreq); 
 445  0145 1e0b          	ldw	x,(OFST-1,sp)
 448  0147 5b0c          	addw	sp,#12
 449  0149 81            	ret
 482                     	xdef	_PWM1_DC
 483                     	xdef	_FOSC
 484                     	xdef	_PWM_GetFrequency
 485                     	xdef	_PWM_SetFrequency
 486                     	xdef	_TIM1_Init
 487                     	xref.b	c_lreg
 488                     	xref.b	c_x
 507                     	xref	c_ltor
 508                     	xref	c_ludv
 509                     	xref	c_rtol
 510                     	xref	c_uitolx
 511                     	end
