   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  43                     ; 112 @far @interrupt void CAN_TX_ISR (void)
  43                     ; 113 {
  44                     	switch	.text
  45  0000               f_CAN_TX_ISR:
  49                     ; 116 }
  52  0000 80            	iret
  79                     ; 123 @far @interrupt void CAN_RX_ISR (void)
  79                     ; 124 {
  80                     	switch	.text
  81  0001               f_CAN_RX_ISR:
  83  0001 8a            	push	cc
  84  0002 84            	pop	a
  85  0003 a4bf          	and	a,#191
  86  0005 88            	push	a
  87  0006 86            	pop	cc
  88  0007 3b0002        	push	c_x+2
  89  000a be00          	ldw	x,c_x
  90  000c 89            	pushw	x
  91  000d 3b0002        	push	c_y+2
  92  0010 be00          	ldw	x,c_y
  93  0012 89            	pushw	x
  96                     ; 125     if (GetRxFifoStatus() > 0){
  98  0013 cd032b        	call	L5_GetRxFifoStatus
 100  0016 4d            	tnz	a
 101  0017 271d          	jreq	L15
 102                     ; 126 			CAN_Read(&RxMsgBuff[rxBuffPtr]);
 104  0019 b603          	ld	a,L71_rxBuffPtr
 105  001b 97            	ld	xl,a
 106  001c a612          	ld	a,#18
 107  001e 42            	mul	x,a
 108  001f 01            	rrwa	x,a
 109  0020 ab04          	add	a,#L51_RxMsgBuff
 110  0022 2401          	jrnc	L01
 111  0024 5c            	incw	x
 112  0025               L01:
 113  0025 5f            	clrw	x
 114  0026 97            	ld	xl,a
 115  0027 cd0201        	call	L11_CAN_Read
 117                     ; 127 			if (++rxBuffPtr >3) rxBuffPtr = 0;
 119  002a 3c03          	inc	L71_rxBuffPtr
 120  002c b603          	ld	a,L71_rxBuffPtr
 121  002e a104          	cp	a,#4
 122  0030 2509          	jrult	L55
 125  0032 3f03          	clr	L71_rxBuffPtr
 126  0034 2005          	jra	L55
 127  0036               L15:
 128                     ; 132     	CAN_Error(STOP_INTERRUPTSRVC);
 130  0036 a601          	ld	a,#1
 131  0038 cd0331        	call	L7_CAN_Error
 133  003b               L55:
 134                     ; 134     return;
 137  003b 85            	popw	x
 138  003c bf00          	ldw	c_y,x
 139  003e 320002        	pop	c_y+2
 140  0041 85            	popw	x
 141  0042 bf00          	ldw	c_x,x
 142  0044 320002        	pop	c_x+2
 143  0047 80            	iret
 166                     ; 142 void CAN_Init (void)
 166                     ; 143 {
 168                     	switch	.text
 169  0048               _CAN_Init:
 173                     ; 144     Flags.RxBuffFull = FALSE;
 175  0048 3f01          	clr	_Flags+1
 176                     ; 145     Flags.TxBuffFull = FALSE;
 178  004a 3f00          	clr	_Flags
 179                     ; 146 	DI();						// disable interrupts
 182  004c 9b            sim
 184                     ; 148     CAN->CMCR = 0x05;			// issue Initialization Mode entry request
 186  004d 35055420      	mov	21536,#5
 188  0051               L37:
 189                     ; 150     while (!(CAN->CMSR & 0x01));
 191  0051 c65421        	ld	a,21537
 192  0054 a501          	bcp	a,#1
 193  0056 27f9          	jreq	L37
 194                     ; 153 		CAN->CMCR |= 0x10;  // automatic retrasmission OFF
 196  0058 72185420      	bset	21536,#4
 197                     ; 157     CAN->CDGR = BIN8(0,0,0,1, 0,0,0,0);
 199  005c 35105426      	mov	21542,#16
 200                     ; 160 		CAN->CIER = BIN8(0,0,0,0, 1,0,1,0);  // FOVIE, FMPIE, TMEIE
 202  0060 350a5425      	mov	21541,#10
 203                     ; 162     REG_PAGE_SELECT(PAGE_CONFIGDIAG);
 205  0064 35065427      	mov	21543,#6
 206                     ; 164 		CAN_CEIER = BIN8(0,0,0,0, 0,0,0,0);		// KHG -> disable all errors
 208  0068 725f5429      	clr	21545
 209                     ; 170     CAN_CBTR1 = 0x10 | 0x04; // 3Tq + 4Tq
 211  006c 3514542d      	mov	21549,#20
 212                     ; 171 		CAN_CBTR1 |= 0x80;	//- XTAL as a CAN clock
 214  0070 721e542d      	bset	21549,#7
 215                     ; 176     CAN_CBTR0 = 0x00 | 3;
 217  0074 3503542c      	mov	21548,#3
 218                     ; 179     CAN_CFCR0 = 0x00; CAN_CFCR1 = 0x00; CAN_CFCR2 = 0x00; // deactivate all filter banks
 220  0078 725f5432      	clr	21554
 223  007c 725f5433      	clr	21555
 226  0080 725f5434      	clr	21556
 227                     ; 180     CAN_CFMR1 = BIN8(0,0,0,0, 0,0,0,0); // all banks in mask mode
 229  0084 725f5431      	clr	21553
 230                     ; 181     CAN_CFCR0 = BIN8(0,0,0,0, 0,1,1,0); // filter bank 0 as 32-bit filter
 232  0088 35065432      	mov	21554,#6
 233                     ; 182     REG_PAGE_SELECT(PAGE_ACCFILTER01);
 235  008c 35025427      	mov	21543,#2
 236                     ; 183     *((u8*)(&CAN_CF0R0 + 0)) = 0x00;
 238  0090 725f5428      	clr	21544
 239                     ; 184     *((u8*)(&CAN_CF0R0 + 1)) = 0x00;
 241  0094 725f5429      	clr	21545
 242                     ; 185     *((u8*)(&CAN_CF0R0 + 2)) = 0x00;
 244  0098 725f542a      	clr	21546
 245                     ; 186     *((u8*)(&CAN_CF0R0 + 3)) = 0x00;
 247  009c 725f542b      	clr	21547
 248                     ; 187     *((u8*)(&CAN_CF0R0 + 4)) = 0x00; // set bank 0 mask -> accept all messages
 250  00a0 725f542c      	clr	21548
 251                     ; 188     *((u8*)(&CAN_CF0R0 + 5)) = 0x00;
 253  00a4 725f542d      	clr	21549
 254                     ; 189     *((u8*)(&CAN_CF0R0 + 6)) = 0x00;
 256  00a8 725f542e      	clr	21550
 257                     ; 190     *((u8*)(&CAN_CF0R0 + 7)) = 0x00;
 259  00ac 725f542f      	clr	21551
 260                     ; 191     *((u8*)(&CAN_CF0R0 + 8)) = 0x00;
 262  00b0 725f5430      	clr	21552
 263                     ; 192     REG_PAGE_SELECT(PAGE_CONFIGDIAG);
 265  00b4 35065427      	mov	21543,#6
 266                     ; 194     CAN_CFCR0 |= BIN8(0,0,0,0, 0,0,0,1);
 268  00b8 72105432      	bset	21554,#0
 269                     ; 195     EI();
 272  00bc 9a            rim
 274                     ; 196 }
 277  00bd 81            	ret
 302                     ; 205 u8 CAN_Start(void)
 302                     ; 206 {		
 303                     	switch	.text
 304  00be               _CAN_Start:
 308                     ; 207 	rxBuffPtr = 0;
 310  00be 3f03          	clr	L71_rxBuffPtr
 311                     ; 208 	rxReadBuffPtr = 0;
 313  00c0 3f02          	clr	L12_rxReadBuffPtr
 314                     ; 209    CAN->CMCR &=0xFE;		    		// issue Normal Mode entry request
 316  00c2 72115420      	bres	21536,#0
 318  00c6               L521:
 319                     ; 210    while (RDBIT8(CAN->CMSR, 0));		// wait for Normal Mode (CMSR:INAK = 0)
 321  00c6 c65421        	ld	a,21537
 322  00c9 a501          	bcp	a,#1
 323  00cb 2704          	jreq	L61
 324  00cd a601          	ld	a,#1
 325  00cf 2001          	jra	L02
 326  00d1               L61:
 327  00d1 4f            	clr	a
 328  00d2               L02:
 329  00d2 4d            	tnz	a
 330  00d3 26f1          	jrne	L521
 331                     ; 211    return RET_OK;
 333  00d5 a601          	ld	a,#1
 336  00d7 81            	ret
 359                     ; 219 u8 CAN_Stop (void)
 359                     ; 220 {
 360                     	switch	.text
 361  00d8               _CAN_Stop:
 365                     ; 221     WRBIT8(CAN->CMCR, 1, 1);			// issue Sleep Mode entry request
 367  00d8 72125420      	bset	21536,#1
 369  00dc               L741:
 370                     ; 222     while (!RDBIT8(CAN->CMSR, 1));		// wait for Sleep Mode entry (CMSR:SLAK = 1)
 372  00dc c65421        	ld	a,21537
 373  00df a502          	bcp	a,#2
 374  00e1 2704          	jreq	L42
 375  00e3 a601          	ld	a,#1
 376  00e5 2001          	jra	L62
 377  00e7               L42:
 378  00e7 4f            	clr	a
 379  00e8               L62:
 380  00e8 4d            	tnz	a
 381  00e9 27f1          	jreq	L741
 382                     ; 224     return RET_OK;
 384  00eb a601          	ld	a,#1
 387  00ed 81            	ret
 512                     ; 233 u8 CAN_Write (tCANMsg *pTxMsgBuff)
 512                     ; 234 {
 513                     	switch	.text
 514  00ee               _CAN_Write:
 516  00ee 89            	pushw	x
 517  00ef 5207          	subw	sp,#7
 518       00000007      OFST:	set	7
 521                     ; 238     if (GetFirstEmptyTxMBoxNr(&MsgBoxID) == RET_BUSY)
 523  00f1 96            	ldw	x,sp
 524  00f2 1c0005        	addw	x,#OFST-2
 525  00f5 cd02e2        	call	L3_GetFirstEmptyTxMBoxNr
 527  00f8 a10a          	cp	a,#10
 528  00fa 2604          	jrne	L342
 529                     ; 239     	return RET_BUSY;
 531  00fc a60a          	ld	a,#10
 533  00fe 2012          	jra	L43
 534  0100               L342:
 535                     ; 243 	pgRegTmp = CAN->CPSR;
 537  0100 c65427        	ld	a,21543
 538  0103 6b06          	ld	(OFST-1,sp),a
 539                     ; 246 	switch (MsgBoxID)
 541  0105 7b05          	ld	a,(OFST-2,sp)
 543                     ; 251 	default: return RET_INVALID_ARGUMENT;
 544  0107 4d            	tnz	a
 545  0108 270b          	jreq	L152
 546  010a 4a            	dec	a
 547  010b 270e          	jreq	L552
 548  010d 4a            	dec	a
 549  010e 2711          	jreq	L162
 550  0110               L161:
 553  0110 a60b          	ld	a,#11
 555  0112               L43:
 557  0112 5b09          	addw	sp,#9
 558  0114 81            	ret
 559  0115               L152:
 560                     ; 248 	case 0: REG_PAGE_SELECT(PAGE_TXMBOX0); break;
 562  0115 725f5427      	clr	21543
 565  0119 200a          	jra	L742
 566  011b               L552:
 567                     ; 249 	case 1: REG_PAGE_SELECT(PAGE_TXMBOX1); break;
 569  011b 35015427      	mov	21543,#1
 572  011f 2004          	jra	L742
 573  0121               L162:
 574                     ; 250 	case 2: REG_PAGE_SELECT(PAGE_TXMBOX2); break;
 576  0121 35055427      	mov	21543,#5
 579  0125               L742:
 580                     ; 260 	CAN_MDLCR = pTxMsgBuff->Length;
 582  0125 1e08          	ldw	x,(OFST+1,sp)
 583  0127 e606          	ld	a,(6,x)
 584  0129 c75429        	ld	21545,a
 585                     ; 261 	if (pTxMsgBuff->rtr){ 
 587  012c 1e08          	ldw	x,(OFST+1,sp)
 588  012e 6d05          	tnz	(5,x)
 589  0130 2706          	jreq	L562
 590                     ; 262 		CAN_MIDR1 = 0x20;				// set remote request frame
 592  0132 3520542a      	mov	21546,#32
 594  0136 2004          	jra	L762
 595  0138               L562:
 596                     ; 264 		CAN_MIDR1 = 0;					// set standard frame, data frame
 598  0138 725f542a      	clr	21546
 599  013c               L762:
 600                     ; 266 	if(pTxMsgBuff->Xtd)
 602  013c 1e08          	ldw	x,(OFST+1,sp)
 603  013e 6d04          	tnz	(4,x)
 604  0140 2749          	jreq	L172
 605                     ; 268 		CAN_MIDR1 |= 0x40; 			// set extended frame
 607  0142 721c542a      	bset	21546,#6
 608                     ; 269 		CAN_MIDR1 |= (u8)((pTxMsgBuff->ID >>24) & 0x1F);// EXID28:24
 610  0146 1e08          	ldw	x,(OFST+1,sp)
 611  0148 cd0000        	call	c_ltor
 613  014b a618          	ld	a,#24
 614  014d cd0000        	call	c_lursh
 616  0150 b603          	ld	a,c_lreg+3
 617  0152 a41f          	and	a,#31
 618  0154 b703          	ld	c_lreg+3,a
 619  0156 3f02          	clr	c_lreg+2
 620  0158 3f01          	clr	c_lreg+1
 621  015a 3f00          	clr	c_lreg
 622  015c b603          	ld	a,c_lreg+3
 623  015e ca542a        	or	a,21546
 624  0161 c7542a        	ld	21546,a
 625                     ; 270 		CAN_MIDR2 = (u8)(pTxMsgBuff->ID >>16);			// EXID23:16
 627  0164 1e08          	ldw	x,(OFST+1,sp)
 628  0166 cd0000        	call	c_ltor
 630  0169 a610          	ld	a,#16
 631  016b cd0000        	call	c_lursh
 633  016e b603          	ld	a,c_lreg+3
 634  0170 c7542b        	ld	21547,a
 635                     ; 271 		CAN_MIDR3 = (u8)(pTxMsgBuff->ID >>8);			// EXID15:8
 637  0173 1e08          	ldw	x,(OFST+1,sp)
 638  0175 cd0000        	call	c_ltor
 640  0178 a608          	ld	a,#8
 641  017a cd0000        	call	c_lursh
 643  017d b603          	ld	a,c_lreg+3
 644  017f c7542c        	ld	21548,a
 645                     ; 272 		CAN_MIDR4 = (u8)(pTxMsgBuff->ID);				// EXID7:0
 647  0182 1e08          	ldw	x,(OFST+1,sp)
 648  0184 e603          	ld	a,(3,x)
 649  0186 c7542d        	ld	21549,a
 651  0189 2041          	jra	L372
 652  018b               L172:
 653                     ; 277 		CAN_MIDR1 &= ~0x40;
 655  018b 721d542a      	bres	21546,#6
 656                     ; 278 		CAN_MIDR1 |= (pTxMsgBuff->ID >>6) & 0x1F;		// SID10:6
 658  018f 1e08          	ldw	x,(OFST+1,sp)
 659  0191 cd0000        	call	c_ltor
 661  0194 a606          	ld	a,#6
 662  0196 cd0000        	call	c_lursh
 664  0199 b603          	ld	a,c_lreg+3
 665  019b a41f          	and	a,#31
 666  019d b703          	ld	c_lreg+3,a
 667  019f 3f02          	clr	c_lreg+2
 668  01a1 3f01          	clr	c_lreg+1
 669  01a3 3f00          	clr	c_lreg
 670  01a5 96            	ldw	x,sp
 671  01a6 1c0001        	addw	x,#OFST-6
 672  01a9 cd0000        	call	c_rtol
 674  01ac c6542a        	ld	a,21546
 675  01af b703          	ld	c_lreg+3,a
 676  01b1 3f02          	clr	c_lreg+2
 677  01b3 3f01          	clr	c_lreg+1
 678  01b5 3f00          	clr	c_lreg
 679  01b7 96            	ldw	x,sp
 680  01b8 1c0001        	addw	x,#OFST-6
 681  01bb cd0000        	call	c_lor
 683  01be b603          	ld	a,c_lreg+3
 684  01c0 c7542a        	ld	21546,a
 685                     ; 279 		CAN_MIDR2 = (pTxMsgBuff->ID <<2);				// SID5:0
 687  01c3 1e08          	ldw	x,(OFST+1,sp)
 688  01c5 e603          	ld	a,(3,x)
 689  01c7 48            	sll	a
 690  01c8 48            	sll	a
 691  01c9 c7542b        	ld	21547,a
 692  01cc               L372:
 693                     ; 281 	for (i = 0; i < pTxMsgBuff->Length; i++)			// write data to TX mailbox
 695  01cc 0f07          	clr	(OFST+0,sp)
 697  01ce 2018          	jra	L103
 698  01d0               L572:
 699                     ; 282 		*(&CAN_MDAR1+i) = pTxMsgBuff->Data[i];
 701  01d0 7b07          	ld	a,(OFST+0,sp)
 702  01d2 5f            	clrw	x
 703  01d3 97            	ld	xl,a
 704  01d4 89            	pushw	x
 705  01d5 7b0a          	ld	a,(OFST+3,sp)
 706  01d7 97            	ld	xl,a
 707  01d8 7b0b          	ld	a,(OFST+4,sp)
 708  01da 1b09          	add	a,(OFST+2,sp)
 709  01dc 2401          	jrnc	L23
 710  01de 5c            	incw	x
 711  01df               L23:
 712  01df 02            	rlwa	x,a
 713  01e0 e607          	ld	a,(7,x)
 714  01e2 85            	popw	x
 715  01e3 d7542e        	ld	(21550,x),a
 716                     ; 281 	for (i = 0; i < pTxMsgBuff->Length; i++)			// write data to TX mailbox
 718  01e6 0c07          	inc	(OFST+0,sp)
 719  01e8               L103:
 722  01e8 1e08          	ldw	x,(OFST+1,sp)
 723  01ea e606          	ld	a,(6,x)
 724  01ec 1107          	cp	a,(OFST+0,sp)
 725  01ee 22e0          	jrugt	L572
 726                     ; 284 	WRBIT8 (CAN_MCSR, 0, 1);							// request tx mailbox transmission
 728  01f0 72105428      	bset	21544,#0
 729                     ; 286 	CAN->CPSR = pgRegTmp;
 731  01f4 7b06          	ld	a,(OFST-1,sp)
 732  01f6 c75427        	ld	21543,a
 733                     ; 287 	Flags.TxBuffFull = FALSE;
 735  01f9 3f00          	clr	_Flags
 736                     ; 288 	return RET_OK;
 738  01fb a601          	ld	a,#1
 740  01fd ac120112      	jpf	L43
 796                     ; 296 static u8 CAN_Read (tCANMsg *pRxMsgBuff)
 796                     ; 297 {
 797                     	switch	.text
 798  0201               L11_CAN_Read:
 800  0201 89            	pushw	x
 801  0202 89            	pushw	x
 802       00000002      OFST:	set	2
 805                     ; 301     pgRegTmp = CAN->CPSR;
 807  0203 c65427        	ld	a,21543
 808  0206 6b01          	ld	(OFST-1,sp),a
 809                     ; 302     REG_PAGE_SELECT (PAGE_RXFIFO);
 811  0208 35075427      	mov	21543,#7
 812                     ; 303 		pRxMsgBuff->FilterID = CAN_MFMIR;				// fet Filter match
 814  020c 1e03          	ldw	x,(OFST+1,sp)
 815  020e c65428        	ld	a,21544
 816  0211 e711          	ld	(17,x),a
 817                     ; 304     pRxMsgBuff->Length = CAN_MDLCR;			    // get data length
 819  0213 1e03          	ldw	x,(OFST+1,sp)
 820  0215 c65429        	ld	a,21545
 821  0218 e706          	ld	(6,x),a
 822                     ; 305     pRxMsgBuff->Xtd = CAN_MIDR1 & 0x40;			// get frame ext. flag
 824  021a c6542a        	ld	a,21546
 825  021d a440          	and	a,#64
 826  021f 1e03          	ldw	x,(OFST+1,sp)
 827  0221 e704          	ld	(4,x),a
 828                     ; 306 		pRxMsgBuff->rtr = CAN_MIDR1 & 0x20;			// get frame ext. flag
 830  0223 c6542a        	ld	a,21546
 831  0226 a420          	and	a,#32
 832  0228 1e03          	ldw	x,(OFST+1,sp)
 833  022a e705          	ld	(5,x),a
 834                     ; 308     if (pRxMsgBuff->Xtd)						// get frame id
 836  022c 1e03          	ldw	x,(OFST+1,sp)
 837  022e 6d04          	tnz	(4,x)
 838  0230 2753          	jreq	L543
 839                     ; 310     	pRxMsgBuff->ID = (u32)(((u32)(CAN_MIDR1& 0x1F)) << 24);// EXID28:24
 841  0232 c6542a        	ld	a,21546
 842  0235 a41f          	and	a,#31
 843  0237 b703          	ld	c_lreg+3,a
 844  0239 3f02          	clr	c_lreg+2
 845  023b 3f01          	clr	c_lreg+1
 846  023d 3f00          	clr	c_lreg
 847  023f a618          	ld	a,#24
 848  0241 cd0000        	call	c_llsh
 850  0244 1e03          	ldw	x,(OFST+1,sp)
 851  0246 cd0000        	call	c_rtol
 853                     ; 311     	pRxMsgBuff->ID |= (u32)((u32)CAN_MIDR2 << 16);// EXID23:16
 855  0249 1e03          	ldw	x,(OFST+1,sp)
 856  024b c6542b        	ld	a,21547
 857  024e b703          	ld	c_lreg+3,a
 858  0250 3f02          	clr	c_lreg+2
 859  0252 3f01          	clr	c_lreg+1
 860  0254 3f00          	clr	c_lreg
 861  0256 a610          	ld	a,#16
 862  0258 cd0000        	call	c_llsh
 864  025b cd0000        	call	c_lgor
 866                     ; 312     	pRxMsgBuff->ID |= (u32)((u32)CAN_MIDR3 << 8);// EXID15:8
 868  025e 1e03          	ldw	x,(OFST+1,sp)
 869  0260 c6542c        	ld	a,21548
 870  0263 b703          	ld	c_lreg+3,a
 871  0265 3f02          	clr	c_lreg+2
 872  0267 3f01          	clr	c_lreg+1
 873  0269 3f00          	clr	c_lreg
 874  026b a608          	ld	a,#8
 875  026d cd0000        	call	c_llsh
 877  0270 cd0000        	call	c_lgor
 879                     ; 313     	pRxMsgBuff->ID |= (u32)(CAN_MIDR4);		// EXID7:0
 881  0273 1e03          	ldw	x,(OFST+1,sp)
 882  0275 c6542d        	ld	a,21549
 883  0278 b703          	ld	c_lreg+3,a
 884  027a 3f02          	clr	c_lreg+2
 885  027c 3f01          	clr	c_lreg+1
 886  027e 3f00          	clr	c_lreg
 887  0280 cd0000        	call	c_lgor
 890  0283 201f          	jra	L743
 891  0285               L543:
 892                     ; 317     	pRxMsgBuff->ID = (u32)((CAN_MIDR1 & 0x1F) << 6);	// STID10:6
 894  0285 c6542a        	ld	a,21546
 895  0288 a41f          	and	a,#31
 896  028a 97            	ld	xl,a
 897  028b a640          	ld	a,#64
 898  028d 42            	mul	x,a
 899  028e cd0000        	call	c_itolx
 901  0291 1e03          	ldw	x,(OFST+1,sp)
 902  0293 cd0000        	call	c_rtol
 904                     ; 318 			pRxMsgBuff->ID |= (u32)(CAN_MIDR2 >> 2);// STID5:0
 906  0296 c6542b        	ld	a,21547
 907  0299 44            	srl	a
 908  029a 44            	srl	a
 909  029b 5f            	clrw	x
 910  029c cd0000        	call	c_itol
 912  029f 1e03          	ldw	x,(OFST+1,sp)
 913  02a1 cd0000        	call	c_lgor
 915  02a4               L743:
 916                     ; 321     if (!(CAN_MIDR1 & CAN_FLAG_RTR)) {
 918  02a4 c6542a        	ld	a,21546
 919  02a7 a520          	bcp	a,#32
 920  02a9 2625          	jrne	L363
 921                     ; 322         for (i = 0; i < pRxMsgBuff->Length; i++)
 923  02ab 0f02          	clr	(OFST+0,sp)
 925  02ad 2019          	jra	L753
 926  02af               L353:
 927                     ; 323         	pRxMsgBuff->Data[i] = *(&CAN_MDAR1+i);
 929  02af 7b03          	ld	a,(OFST+1,sp)
 930  02b1 97            	ld	xl,a
 931  02b2 7b04          	ld	a,(OFST+2,sp)
 932  02b4 1b02          	add	a,(OFST+0,sp)
 933  02b6 2401          	jrnc	L04
 934  02b8 5c            	incw	x
 935  02b9               L04:
 936  02b9 02            	rlwa	x,a
 937  02ba 7b02          	ld	a,(OFST+0,sp)
 938  02bc 905f          	clrw	y
 939  02be 9097          	ld	yl,a
 940  02c0 90d6542e      	ld	a,(21550,y)
 941  02c4 e707          	ld	(7,x),a
 942                     ; 322         for (i = 0; i < pRxMsgBuff->Length; i++)
 944  02c6 0c02          	inc	(OFST+0,sp)
 945  02c8               L753:
 948  02c8 1e03          	ldw	x,(OFST+1,sp)
 949  02ca e606          	ld	a,(6,x)
 950  02cc 1102          	cp	a,(OFST+0,sp)
 951  02ce 22df          	jrugt	L353
 952  02d0               L363:
 953                     ; 326     WRBIT8(CAN->CRFR, 5, 1);     				// release RX mailbox
 955  02d0 721a5424      	bset	21540,#5
 956                     ; 328     CAN->CPSR = pgRegTmp;		
 958  02d4 7b01          	ld	a,(OFST-1,sp)
 959  02d6 c75427        	ld	21543,a
 960                     ; 329     Flags.RxBuffFull = TRUE;
 962  02d9 35ff0001      	mov	_Flags+1,#255
 963                     ; 331     return RET_OK;
 965  02dd a601          	ld	a,#1
 968  02df 5b04          	addw	sp,#4
 969  02e1 81            	ret
1005                     ; 341 static u8 GetFirstEmptyTxMBoxNr (u8 *pIDBox)
1005                     ; 342 {
1006                     	switch	.text
1007  02e2               L3_GetFirstEmptyTxMBoxNr:
1009  02e2 89            	pushw	x
1010       00000000      OFST:	set	0
1013                     ; 343     if (RDBIT8(CAN->CTPR, 2))
1015  02e3 c65423        	ld	a,21539
1016  02e6 a504          	bcp	a,#4
1017  02e8 2704          	jreq	L44
1018  02ea a601          	ld	a,#1
1019  02ec 2001          	jra	L64
1020  02ee               L44:
1021  02ee 4f            	clr	a
1022  02ef               L64:
1023  02ef 4d            	tnz	a
1024  02f0 2705          	jreq	L504
1025                     ; 345     	*pIDBox = 0;
1027  02f2 7f            	clr	(x)
1028                     ; 346     	return RET_OK;
1030  02f3 a601          	ld	a,#1
1032  02f5 2016          	jra	L06
1033  02f7               L504:
1034                     ; 348     if (RDBIT8(CAN->CTPR, 3))
1036  02f7 c65423        	ld	a,21539
1037  02fa a508          	bcp	a,#8
1038  02fc 2704          	jreq	L05
1039  02fe a601          	ld	a,#1
1040  0300 2001          	jra	L25
1041  0302               L05:
1042  0302 4f            	clr	a
1043  0303               L25:
1044  0303 4d            	tnz	a
1045  0304 2709          	jreq	L704
1046                     ; 350 		*pIDBox = 1;
1048  0306 1e01          	ldw	x,(OFST+1,sp)
1049  0308 a601          	ld	a,#1
1050  030a f7            	ld	(x),a
1051                     ; 351 		return RET_OK;
1053  030b a601          	ld	a,#1
1055  030d               L06:
1057  030d 85            	popw	x
1058  030e 81            	ret
1059  030f               L704:
1060                     ; 353     if (RDBIT8(CAN->CTPR, 4))
1062  030f c65423        	ld	a,21539
1063  0312 a510          	bcp	a,#16
1064  0314 2704          	jreq	L45
1065  0316 a601          	ld	a,#1
1066  0318 2001          	jra	L65
1067  031a               L45:
1068  031a 4f            	clr	a
1069  031b               L65:
1070  031b 4d            	tnz	a
1071  031c 2709          	jreq	L114
1072                     ; 355 		*pIDBox = 2;
1074  031e 1e01          	ldw	x,(OFST+1,sp)
1075  0320 a602          	ld	a,#2
1076  0322 f7            	ld	(x),a
1077                     ; 356 		return RET_OK;
1079  0323 a601          	ld	a,#1
1081  0325 20e6          	jra	L06
1082  0327               L114:
1083                     ; 358     return RET_BUSY;
1085  0327 a60a          	ld	a,#10
1087  0329 20e2          	jra	L06
1110                     ; 366 static u8 GetRxFifoStatus (void)
1110                     ; 367 {
1111                     	switch	.text
1112  032b               L5_GetRxFifoStatus:
1116                     ; 369     return CAN->CRFR & 0x03;
1118  032b c65424        	ld	a,21540
1119  032e a403          	and	a,#3
1122  0330 81            	ret
1156                     ; 378 static void CAN_Error(u8 code)
1156                     ; 379 {
1157                     	switch	.text
1158  0331               L7_CAN_Error:
1162                     ; 380     CAN->CIER = 0;
1164  0331 725f5425      	clr	21541
1165                     ; 381     REG_PAGE_SELECT(PAGE_CONFIGDIAG);
1167  0335 35065427      	mov	21543,#6
1168                     ; 382     CAN_CEIER = 0;
1170  0339 725f5429      	clr	21545
1171                     ; 385 		push cc
1174  033d 8a            push cc
1176                     ; 386 		pop a
1179  033e 84            pop a
1181                     ; 387 		and a,#0xD7
1184  033f a4d7          and a,#0xD7
1186                     ; 388 		or a,#0x20
1189  0341 aa20          or a,#0x20
1191                     ; 389 		push a
1194  0343 88            push a
1196                     ; 390 		pop cc
1199  0344 86            pop cc
1201  0345               L544:
1203  0345 20fe          	jra	L544
1253                     ; 404 u8 CAN_GetMsg(tCANMsg *pRxMsgBuff)
1253                     ; 405 {
1254                     	switch	.text
1255  0347               _CAN_GetMsg:
1257  0347 89            	pushw	x
1258  0348 88            	push	a
1259       00000001      OFST:	set	1
1262                     ; 411 if(Flags.RxBuffFull)
1264  0349 3d01          	tnz	_Flags+1
1265  034b 2603          	jrne	L67
1266  034d cc03e8        	jp	L574
1267  0350               L67:
1268                     ; 413 		pRxMsgBuff->ID = RxMsgBuff[rxReadBuffPtr].ID;
1270  0350 b602          	ld	a,L12_rxReadBuffPtr
1271  0352 97            	ld	xl,a
1272  0353 a612          	ld	a,#18
1273  0355 42            	mul	x,a
1274  0356 1602          	ldw	y,(OFST+1,sp)
1275  0358 e607          	ld	a,(L51_RxMsgBuff+3,x)
1276  035a 90e703        	ld	(3,y),a
1277  035d e606          	ld	a,(L51_RxMsgBuff+2,x)
1278  035f 90e702        	ld	(2,y),a
1279  0362 e605          	ld	a,(L51_RxMsgBuff+1,x)
1280  0364 90e701        	ld	(1,y),a
1281  0367 e604          	ld	a,(L51_RxMsgBuff,x)
1282  0369 90f7          	ld	(y),a
1283                     ; 414 		pRxMsgBuff->Xtd = RxMsgBuff[rxReadBuffPtr].Xtd;
1285  036b b602          	ld	a,L12_rxReadBuffPtr
1286  036d 97            	ld	xl,a
1287  036e a612          	ld	a,#18
1288  0370 42            	mul	x,a
1289  0371 e608          	ld	a,(L51_RxMsgBuff+4,x)
1290  0373 1e02          	ldw	x,(OFST+1,sp)
1291  0375 e704          	ld	(4,x),a
1292                     ; 415 		pRxMsgBuff->rtr = RxMsgBuff[rxReadBuffPtr].rtr;
1294  0377 b602          	ld	a,L12_rxReadBuffPtr
1295  0379 97            	ld	xl,a
1296  037a a612          	ld	a,#18
1297  037c 42            	mul	x,a
1298  037d e609          	ld	a,(L51_RxMsgBuff+5,x)
1299  037f 1e02          	ldw	x,(OFST+1,sp)
1300  0381 e705          	ld	(5,x),a
1301                     ; 416 		pRxMsgBuff->timeStamp = RxMsgBuff[rxReadBuffPtr].timeStamp;
1303  0383 b602          	ld	a,L12_rxReadBuffPtr
1304  0385 97            	ld	xl,a
1305  0386 a612          	ld	a,#18
1306  0388 42            	mul	x,a
1307  0389 1602          	ldw	y,(OFST+1,sp)
1308  038b 89            	pushw	x
1309  038c ee13          	ldw	x,(L51_RxMsgBuff+15,x)
1310  038e 90ef0f        	ldw	(15,y),x
1311  0391 85            	popw	x
1312                     ; 417 		pRxMsgBuff->Length = RxMsgBuff[rxReadBuffPtr].Length;
1314  0392 b602          	ld	a,L12_rxReadBuffPtr
1315  0394 97            	ld	xl,a
1316  0395 a612          	ld	a,#18
1317  0397 42            	mul	x,a
1318  0398 e60a          	ld	a,(L51_RxMsgBuff+6,x)
1319  039a 1e02          	ldw	x,(OFST+1,sp)
1320  039c e706          	ld	(6,x),a
1321                     ; 418 		pRxMsgBuff->FilterID = RxMsgBuff[rxReadBuffPtr].FilterID;
1323  039e b602          	ld	a,L12_rxReadBuffPtr
1324  03a0 97            	ld	xl,a
1325  03a1 a612          	ld	a,#18
1326  03a3 42            	mul	x,a
1327  03a4 e615          	ld	a,(L51_RxMsgBuff+17,x)
1328  03a6 1e02          	ldw	x,(OFST+1,sp)
1329  03a8 e711          	ld	(17,x),a
1330                     ; 419 		for (i = 0; i < 8; ++i){
1332  03aa 0f01          	clr	(OFST+0,sp)
1333  03ac               L774:
1334                     ; 420 			pRxMsgBuff->Data[i] = RxMsgBuff[rxReadBuffPtr].Data[i];
1336  03ac 7b02          	ld	a,(OFST+1,sp)
1337  03ae 97            	ld	xl,a
1338  03af 7b03          	ld	a,(OFST+2,sp)
1339  03b1 1b01          	add	a,(OFST+0,sp)
1340  03b3 2401          	jrnc	L07
1341  03b5 5c            	incw	x
1342  03b6               L07:
1343  03b6 02            	rlwa	x,a
1344  03b7 89            	pushw	x
1345  03b8 b602          	ld	a,L12_rxReadBuffPtr
1346  03ba 97            	ld	xl,a
1347  03bb a612          	ld	a,#18
1348  03bd 42            	mul	x,a
1349  03be 01            	rrwa	x,a
1350  03bf 1b03          	add	a,(OFST+2,sp)
1351  03c1 2401          	jrnc	L27
1352  03c3 5c            	incw	x
1353  03c4               L27:
1354  03c4 02            	rlwa	x,a
1355  03c5 e60b          	ld	a,(L51_RxMsgBuff+7,x)
1356  03c7 85            	popw	x
1357  03c8 e707          	ld	(7,x),a
1358                     ; 419 		for (i = 0; i < 8; ++i){
1360  03ca 0c01          	inc	(OFST+0,sp)
1363  03cc 7b01          	ld	a,(OFST+0,sp)
1364  03ce a108          	cp	a,#8
1365  03d0 25da          	jrult	L774
1366                     ; 423 	if (++rxReadBuffPtr > 3) rxReadBuffPtr = 0;
1368  03d2 3c02          	inc	L12_rxReadBuffPtr
1369  03d4 b602          	ld	a,L12_rxReadBuffPtr
1370  03d6 a104          	cp	a,#4
1371  03d8 2502          	jrult	L505
1374  03da 3f02          	clr	L12_rxReadBuffPtr
1375  03dc               L505:
1376                     ; 424 	if (rxReadBuffPtr	== rxBuffPtr) Flags.RxBuffFull = FALSE;
1378  03dc b602          	ld	a,L12_rxReadBuffPtr
1379  03de b103          	cp	a,L71_rxBuffPtr
1380  03e0 2602          	jrne	L705
1383  03e2 3f01          	clr	_Flags+1
1384  03e4               L705:
1385                     ; 425 		return RET_OK;
1387  03e4 a601          	ld	a,#1
1389  03e6 2001          	jra	L47
1390  03e8               L574:
1391                     ; 428 		return RET_ERR;
1393  03e8 4f            	clr	a
1395  03e9               L47:
1397  03e9 5b03          	addw	sp,#3
1398  03eb 81            	ret
1451                     ; 438 void CAN_SetBaudRate (u8 brp, u8 bs1, u8 bs2)
1451                     ; 439 {
1452                     	switch	.text
1453  03ec               _CAN_SetBaudRate:
1455  03ec 89            	pushw	x
1456  03ed 88            	push	a
1457       00000001      OFST:	set	1
1460                     ; 440    Flags.RxBuffFull = FALSE;
1462  03ee 3f01          	clr	_Flags+1
1463                     ; 441    Flags.TxBuffFull = FALSE;
1465  03f0 3f00          	clr	_Flags
1466                     ; 442 	DI();						// disable interrupts
1469  03f2 9b            sim
1471                     ; 444 	CAN->CMCR |= 0x01;			// issue Initialization Mode entry request
1473  03f3 72105420      	bset	21536,#0
1475  03f7               L345:
1476                     ; 446     while (!(CAN->CMSR & 0x01));
1478  03f7 c65421        	ld	a,21537
1479  03fa a501          	bcp	a,#1
1480  03fc 27f9          	jreq	L345
1481                     ; 448 	REG_PAGE_SELECT(PAGE_CONFIGDIAG);
1483  03fe 35065427      	mov	21543,#6
1484                     ; 453   CAN_CBTR1 = 0x80 | bs1 | ((u8)( bs2 << 4)); // 3Tq + 4Tq + EXT clock
1486  0402 7b06          	ld	a,(OFST+5,sp)
1487  0404 97            	ld	xl,a
1488  0405 a610          	ld	a,#16
1489  0407 42            	mul	x,a
1490  0408 9f            	ld	a,xl
1491  0409 6b01          	ld	(OFST+0,sp),a
1492  040b 7b03          	ld	a,(OFST+2,sp)
1493  040d aa80          	or	a,#128
1494  040f 1a01          	or	a,(OFST+0,sp)
1495  0411 c7542d        	ld	21549,a
1496                     ; 459   CAN_CBTR0 &= ~0x3FU	;
1498  0414 c6542c        	ld	a,21548
1499  0417 a4c0          	and	a,#192
1500  0419 c7542c        	ld	21548,a
1501                     ; 460 	CAN_CBTR0 |= brp	;	
1503  041c c6542c        	ld	a,21548
1504  041f 1a02          	or	a,(OFST+1,sp)
1505  0421 c7542c        	ld	21548,a
1506                     ; 461 	EI();	
1509  0424 9a            rim
1511                     ; 462 }
1514  0425 5b03          	addw	sp,#3
1515  0427 81            	ret
1551                     ; 470 void CAN_EnableRetrasnmit (u8 enable)
1551                     ; 471 {
1552                     	switch	.text
1553  0428               _CAN_EnableRetrasnmit:
1555  0428 88            	push	a
1556       00000000      OFST:	set	0
1559                     ; 472 	Flags.RxBuffFull = FALSE;
1561  0429 3f01          	clr	_Flags+1
1562                     ; 473   Flags.TxBuffFull = FALSE;
1564  042b 3f00          	clr	_Flags
1565                     ; 474 	DI();						// disable interrupts
1568  042d 9b            sim
1570                     ; 476   CAN->CMCR |= 0x01;			// issue Initialization Mode entry request
1572  042e 72105420      	bset	21536,#0
1574  0432               L375:
1575                     ; 478   while (!(CAN->CMSR & 0x01));
1577  0432 c65421        	ld	a,21537
1578  0435 a501          	bcp	a,#1
1579  0437 27f9          	jreq	L375
1580                     ; 480 	if (enable){
1582  0439 0d01          	tnz	(OFST+1,sp)
1583  043b 2706          	jreq	L775
1584                     ; 481 		CAN->CMCR &= ~0x10U;  // automatic retrasmission ON
1586  043d 72195420      	bres	21536,#4
1588  0441 2004          	jra	L106
1589  0443               L775:
1590                     ; 483 		CAN->CMCR |= 0x10U;  // automatic retrasmission OFF
1592  0443 72185420      	bset	21536,#4
1593  0447               L106:
1594                     ; 485 	EI();	
1597  0447 9a            rim
1599                     ; 486 }
1602  0448 84            	pop	a
1603  0449 81            	ret
1799                     ; 497 void CAN_FillFilterPageReg(tCAN_FLTR_REC* filterSet, u8 bankPart)
1799                     ; 498 {	 
1800                     	switch	.text
1801  044a               _CAN_FillFilterPageReg:
1803  044a 89            	pushw	x
1804  044b 88            	push	a
1805       00000001      OFST:	set	1
1808                     ; 500 	if (bankPart) i = 8;
1810  044c 0d06          	tnz	(OFST+5,sp)
1811  044e 2706          	jreq	L517
1814  0450 a608          	ld	a,#8
1815  0452 6b01          	ld	(OFST+0,sp),a
1817  0454 2002          	jra	L717
1818  0456               L517:
1819                     ; 501 	else i = 0;
1821  0456 0f01          	clr	(OFST+0,sp)
1822  0458               L717:
1823                     ; 502     *((u8*)(&CAN_CF0R0 + 0+i)) = filterSet->R1;
1825  0458 7b01          	ld	a,(OFST+0,sp)
1826  045a 5f            	clrw	x
1827  045b 97            	ld	xl,a
1828  045c 1602          	ldw	y,(OFST+1,sp)
1829  045e 90f6          	ld	a,(y)
1830  0460 d75428        	ld	(21544,x),a
1831                     ; 503     *((u8*)(&CAN_CF0R0 + 1+i)) = filterSet->R2;
1833  0463 7b01          	ld	a,(OFST+0,sp)
1834  0465 5f            	clrw	x
1835  0466 97            	ld	xl,a
1836  0467 1602          	ldw	y,(OFST+1,sp)
1837  0469 90e601        	ld	a,(1,y)
1838  046c d75429        	ld	(21545,x),a
1839                     ; 504     *((u8*)(&CAN_CF0R0 + 2+i)) = filterSet->R3;;
1841  046f 7b01          	ld	a,(OFST+0,sp)
1842  0471 5f            	clrw	x
1843  0472 97            	ld	xl,a
1844  0473 1602          	ldw	y,(OFST+1,sp)
1845  0475 90e602        	ld	a,(2,y)
1846  0478 d7542a        	ld	(21546,x),a
1847                     ; 505     *((u8*)(&CAN_CF0R0 + 3+i)) = filterSet->R4;
1850  047b 7b01          	ld	a,(OFST+0,sp)
1851  047d 5f            	clrw	x
1852  047e 97            	ld	xl,a
1853  047f 1602          	ldw	y,(OFST+1,sp)
1854  0481 90e603        	ld	a,(3,y)
1855  0484 d7542b        	ld	(21547,x),a
1856                     ; 506     *((u8*)(&CAN_CF0R0 + 4+i)) = filterSet->R5;
1858  0487 7b01          	ld	a,(OFST+0,sp)
1859  0489 5f            	clrw	x
1860  048a 97            	ld	xl,a
1861  048b 1602          	ldw	y,(OFST+1,sp)
1862  048d 90e604        	ld	a,(4,y)
1863  0490 d7542c        	ld	(21548,x),a
1864                     ; 507     *((u8*)(&CAN_CF0R0 + 5+i)) = filterSet->R6;
1866  0493 7b01          	ld	a,(OFST+0,sp)
1867  0495 5f            	clrw	x
1868  0496 97            	ld	xl,a
1869  0497 1602          	ldw	y,(OFST+1,sp)
1870  0499 90e605        	ld	a,(5,y)
1871  049c d7542d        	ld	(21549,x),a
1872                     ; 508     *((u8*)(&CAN_CF0R0 + 6+i)) = filterSet->R7;
1874  049f 7b01          	ld	a,(OFST+0,sp)
1875  04a1 5f            	clrw	x
1876  04a2 97            	ld	xl,a
1877  04a3 1602          	ldw	y,(OFST+1,sp)
1878  04a5 90e606        	ld	a,(6,y)
1879  04a8 d7542e        	ld	(21550,x),a
1880                     ; 509     *((u8*)(&CAN_CF0R0 + 7+i)) = filterSet->R8;
1882  04ab 7b01          	ld	a,(OFST+0,sp)
1883  04ad 5f            	clrw	x
1884  04ae 97            	ld	xl,a
1885  04af 1602          	ldw	y,(OFST+1,sp)
1886  04b1 90e607        	ld	a,(7,y)
1887  04b4 d7542f        	ld	(21551,x),a
1888                     ; 510     REG_PAGE_SELECT(PAGE_CONFIGDIAG);	
1890  04b7 35065427      	mov	21543,#6
1891                     ; 511 }
1894  04bb 5b03          	addw	sp,#3
1895  04bd 81            	ret
1933                     ; 522 void CAN_SetFilters(tCAN_FLTR_REC* filterSet)
1933                     ; 523 {
1934                     	switch	.text
1935  04be               _CAN_SetFilters:
1937  04be 89            	pushw	x
1938       00000000      OFST:	set	0
1941                     ; 542 		DI();
1944  04bf 9b            sim
1946                     ; 544 		CAN->CMCR |= 0x01;			// issue Initialization Mode entry request
1948  04c0 72105420      	bset	21536,#0
1950  04c4               L567:
1951                     ; 546     while (!(CAN->CMSR & 0x01));
1953  04c4 c65421        	ld	a,21537
1954  04c7 a501          	bcp	a,#1
1955  04c9 27f9          	jreq	L567
1956                     ; 548 	  REG_PAGE_SELECT(PAGE_CONFIGDIAG);
1958  04cb 35065427      	mov	21543,#6
1959                     ; 550 		switch (filterSet->BankID){
1961  04cf 1e01          	ldw	x,(OFST+1,sp)
1962  04d1 e609          	ld	a,(9,x)
1964                     ; 614 				default: return;			
1965  04d3 a010          	sub	a,#16
1966  04d5 2722          	jreq	L527
1967  04d7 a010          	sub	a,#16
1968  04d9 2774          	jreq	L727
1969  04db a010          	sub	a,#16
1970  04dd 2603          	jrne	L011
1971  04df cc05a8        	jp	L137
1972  04e2               L011:
1973  04e2 a010          	sub	a,#16
1974  04e4 2603          	jrne	L211
1975  04e6 cc05f7        	jp	L337
1976  04e9               L211:
1977  04e9 a010          	sub	a,#16
1978  04eb 2603          	jrne	L411
1979  04ed cc0650        	jp	L537
1980  04f0               L411:
1981  04f0 a010          	sub	a,#16
1982  04f2 2603          	jrne	L611
1983  04f4 cc069f        	jp	L737
1984  04f7               L611:
1985  04f7               L147:
1989  04f7 85            	popw	x
1990  04f8 81            	ret
1991  04f9               L527:
1992                     ; 551 				case 0x10:	// filter 0 page 2
1992                     ; 552 					CAN_CFCR0 &= ~0x07;
1994  04f9 c65432        	ld	a,21554
1995  04fc a4f8          	and	a,#248
1996  04fe c75432        	ld	21554,a
1997                     ; 553 					CAN_CFCR0 |= (filterSet->BankCfg << 1)& 0x06;
1999  0501 1e01          	ldw	x,(OFST+1,sp)
2000  0503 e608          	ld	a,(8,x)
2001  0505 a403          	and	a,#3
2002  0507 48            	sll	a
2003  0508 a406          	and	a,#6
2004  050a ca5432        	or	a,21554
2005  050d c75432        	ld	21554,a
2006                     ; 554 					CAN_CFMR0 &= ~0x03;
2008  0510 c65430        	ld	a,21552
2009  0513 a4fc          	and	a,#252
2010  0515 c75430        	ld	21552,a
2011                     ; 555 					if (filterSet->RegL_ID)
2013  0518 1e01          	ldw	x,(OFST+1,sp)
2014  051a e608          	ld	a,(8,x)
2015  051c a508          	bcp	a,#8
2016  051e 2704          	jreq	L1001
2017                     ; 556 						CAN_CFMR0 |= 0x01;
2019  0520 72105430      	bset	21552,#0
2020  0524               L1001:
2021                     ; 557 					if (filterSet->RegH_ID) 
2023  0524 1e01          	ldw	x,(OFST+1,sp)
2024  0526 e608          	ld	a,(8,x)
2025  0528 a504          	bcp	a,#4
2026  052a 2704          	jreq	L5001
2027                     ; 558 						CAN_CFMR0 |= 0x02;
2029  052c 72125430      	bset	21552,#1
2030  0530               L5001:
2031                     ; 559 					REG_PAGE_SELECT(PAGE_ACCFILTER01);
2033  0530 35025427      	mov	21543,#2
2034                     ; 560 					CAN_FillFilterPageReg(filterSet,0);
2036  0534 4b00          	push	#0
2037  0536 1e02          	ldw	x,(OFST+2,sp)
2038  0538 cd044a        	call	_CAN_FillFilterPageReg
2040  053b 84            	pop	a
2041                     ; 561 					if (filterSet->Enable)
2043  053c 1e01          	ldw	x,(OFST+1,sp)
2044  053e e608          	ld	a,(8,x)
2045  0540 a510          	bcp	a,#16
2046  0542 2603          	jrne	L021
2047  0544 cc06f1        	jp	L777
2048  0547               L021:
2049                     ; 562 							CAN_CFCR0 |= 0x01;
2051  0547 72105432      	bset	21554,#0
2052  054b acf106f1      	jpf	L777
2053  054f               L727:
2054                     ; 564 				case 0x20:	// filter 1 page 2
2054                     ; 565 					CAN_CFCR0 &= ~0x70;
2056  054f c65432        	ld	a,21554
2057  0552 a48f          	and	a,#143
2058  0554 c75432        	ld	21554,a
2059                     ; 566 					CAN_CFCR0 |= (filterSet->BankCfg << 5)& 0x60;				
2061  0557 1e01          	ldw	x,(OFST+1,sp)
2062  0559 e608          	ld	a,(8,x)
2063  055b a403          	and	a,#3
2064  055d 4e            	swap	a
2065  055e 48            	sll	a
2066  055f a4e0          	and	a,#224
2067  0561 a460          	and	a,#96
2068  0563 ca5432        	or	a,21554
2069  0566 c75432        	ld	21554,a
2070                     ; 567 					CAN_CFMR0 &= ~0x0C;
2072  0569 c65430        	ld	a,21552
2073  056c a4f3          	and	a,#243
2074  056e c75430        	ld	21552,a
2075                     ; 568 					if (filterSet->RegL_ID) CAN_CFMR0 |= 0x04;
2077  0571 1e01          	ldw	x,(OFST+1,sp)
2078  0573 e608          	ld	a,(8,x)
2079  0575 a508          	bcp	a,#8
2080  0577 2704          	jreq	L3101
2083  0579 72145430      	bset	21552,#2
2084  057d               L3101:
2085                     ; 569 					if (filterSet->RegH_ID) CAN_CFMR0 |= 0x08;
2087  057d 1e01          	ldw	x,(OFST+1,sp)
2088  057f e608          	ld	a,(8,x)
2089  0581 a504          	bcp	a,#4
2090  0583 2704          	jreq	L7101
2093  0585 72165430      	bset	21552,#3
2094  0589               L7101:
2095                     ; 570 					REG_PAGE_SELECT(PAGE_ACCFILTER01);
2097  0589 35025427      	mov	21543,#2
2098                     ; 571 					CAN_FillFilterPageReg(filterSet,1);
2100  058d 4b01          	push	#1
2101  058f 1e02          	ldw	x,(OFST+2,sp)
2102  0591 cd044a        	call	_CAN_FillFilterPageReg
2104  0594 84            	pop	a
2105                     ; 572 					if (filterSet->Enable) 
2107  0595 1e01          	ldw	x,(OFST+1,sp)
2108  0597 e608          	ld	a,(8,x)
2109  0599 a510          	bcp	a,#16
2110  059b 2603          	jrne	L221
2111  059d cc06f1        	jp	L777
2112  05a0               L221:
2113                     ; 573 							CAN_CFCR0 |= 0x10;
2115  05a0 72185432      	bset	21554,#4
2116  05a4 acf106f1      	jpf	L777
2117  05a8               L137:
2118                     ; 575 				case 0x30: 	// filter2 page 3
2118                     ; 576 					CAN_CFCR1 &= ~0x07;
2120  05a8 c65433        	ld	a,21555
2121  05ab a4f8          	and	a,#248
2122  05ad c75433        	ld	21555,a
2123                     ; 577 					CAN_CFCR1 |= (filterSet->BankCfg << 1)& 0x06;				
2125  05b0 1e01          	ldw	x,(OFST+1,sp)
2126  05b2 e608          	ld	a,(8,x)
2127  05b4 a403          	and	a,#3
2128  05b6 48            	sll	a
2129  05b7 a406          	and	a,#6
2130  05b9 ca5433        	or	a,21555
2131  05bc c75433        	ld	21555,a
2132                     ; 578 					CAN_CFMR0 &= ~0x30;
2134  05bf c65430        	ld	a,21552
2135  05c2 a4cf          	and	a,#207
2136  05c4 c75430        	ld	21552,a
2137                     ; 579 					if (filterSet->RegL_ID) CAN_CFMR0 |= 0x10;
2139  05c7 1e01          	ldw	x,(OFST+1,sp)
2140  05c9 e608          	ld	a,(8,x)
2141  05cb a508          	bcp	a,#8
2142  05cd 2704          	jreq	L5201
2145  05cf 72185430      	bset	21552,#4
2146  05d3               L5201:
2147                     ; 580 					if (filterSet->RegH_ID) CAN_CFMR0 |= 0x20;
2149  05d3 1e01          	ldw	x,(OFST+1,sp)
2150  05d5 e608          	ld	a,(8,x)
2151  05d7 a504          	bcp	a,#4
2152  05d9 2704          	jreq	L1301
2155  05db 721a5430      	bset	21552,#5
2156  05df               L1301:
2157                     ; 581 					REG_PAGE_SELECT(PAGE_ACCFILTER23);
2159  05df 35035427      	mov	21543,#3
2160                     ; 582 					CAN_FillFilterPageReg(filterSet,0);
2162  05e3 4b00          	push	#0
2163  05e5 1e02          	ldw	x,(OFST+2,sp)
2164  05e7 cd044a        	call	_CAN_FillFilterPageReg
2166  05ea 84            	pop	a
2167                     ; 583 					if (filterSet->Enable) 
2169  05eb 1e01          	ldw	x,(OFST+1,sp)
2170  05ed e608          	ld	a,(8,x)
2171  05ef a510          	bcp	a,#16
2172  05f1 2704          	jreq	L337
2173                     ; 584 							CAN_CFCR1 |= 0x01;
2175  05f3 72105433      	bset	21555,#0
2176  05f7               L337:
2177                     ; 585 				case 0x40:	// filter3 page 3
2177                     ; 586 					CAN_CFCR1 &= ~0x70;
2179  05f7 c65433        	ld	a,21555
2180  05fa a48f          	and	a,#143
2181  05fc c75433        	ld	21555,a
2182                     ; 587 					CAN_CFCR1 |= (filterSet->BankCfg << 5)& 0x60;				
2184  05ff 1e01          	ldw	x,(OFST+1,sp)
2185  0601 e608          	ld	a,(8,x)
2186  0603 a403          	and	a,#3
2187  0605 4e            	swap	a
2188  0606 48            	sll	a
2189  0607 a4e0          	and	a,#224
2190  0609 a460          	and	a,#96
2191  060b ca5433        	or	a,21555
2192  060e c75433        	ld	21555,a
2193                     ; 588 					CAN_CFMR0 &= ~0xC0;
2195  0611 c65430        	ld	a,21552
2196  0614 a43f          	and	a,#63
2197  0616 c75430        	ld	21552,a
2198                     ; 589 					if (filterSet->RegL_ID) CAN_CFMR0 |= 0x40;
2200  0619 1e01          	ldw	x,(OFST+1,sp)
2201  061b e608          	ld	a,(8,x)
2202  061d a508          	bcp	a,#8
2203  061f 2704          	jreq	L7301
2206  0621 721c5430      	bset	21552,#6
2207  0625               L7301:
2208                     ; 590 					if (filterSet->RegH_ID) CAN_CFMR0 |= 0x80;
2210  0625 1e01          	ldw	x,(OFST+1,sp)
2211  0627 e608          	ld	a,(8,x)
2212  0629 a504          	bcp	a,#4
2213  062b 2704          	jreq	L3401
2216  062d 721e5430      	bset	21552,#7
2217  0631               L3401:
2218                     ; 591 					REG_PAGE_SELECT(PAGE_ACCFILTER23);
2220  0631 35035427      	mov	21543,#3
2221                     ; 592 					CAN_FillFilterPageReg(filterSet,1);
2223  0635 4b01          	push	#1
2224  0637 1e02          	ldw	x,(OFST+2,sp)
2225  0639 cd044a        	call	_CAN_FillFilterPageReg
2227  063c 84            	pop	a
2228                     ; 593 					if (filterSet->Enable) CAN_CFCR1 |= 0x10;
2230  063d 1e01          	ldw	x,(OFST+1,sp)
2231  063f e608          	ld	a,(8,x)
2232  0641 a510          	bcp	a,#16
2233  0643 2603          	jrne	L421
2234  0645 cc06f1        	jp	L777
2235  0648               L421:
2238  0648 72185433      	bset	21555,#4
2239  064c acf106f1      	jpf	L777
2240  0650               L537:
2241                     ; 595 				case 0x50:	// filter4 page 4
2241                     ; 596 					CAN_CFCR2 &= ~0x07;
2243  0650 c65434        	ld	a,21556
2244  0653 a4f8          	and	a,#248
2245  0655 c75434        	ld	21556,a
2246                     ; 597 					CAN_CFCR2 |= (filterSet->BankCfg << 1)& 0x06;								
2248  0658 1e01          	ldw	x,(OFST+1,sp)
2249  065a e608          	ld	a,(8,x)
2250  065c a403          	and	a,#3
2251  065e 48            	sll	a
2252  065f a406          	and	a,#6
2253  0661 ca5434        	or	a,21556
2254  0664 c75434        	ld	21556,a
2255                     ; 598 					CAN_CFMR1 &= ~0x03;
2257  0667 c65431        	ld	a,21553
2258  066a a4fc          	and	a,#252
2259  066c c75431        	ld	21553,a
2260                     ; 599 					if (filterSet->RegL_ID) CAN_CFMR1 |= 0x01;
2262  066f 1e01          	ldw	x,(OFST+1,sp)
2263  0671 e608          	ld	a,(8,x)
2264  0673 a508          	bcp	a,#8
2265  0675 2704          	jreq	L1501
2268  0677 72105431      	bset	21553,#0
2269  067b               L1501:
2270                     ; 600 					if (filterSet->RegH_ID) CAN_CFMR1 |= 0x02;
2272  067b 1e01          	ldw	x,(OFST+1,sp)
2273  067d e608          	ld	a,(8,x)
2274  067f a504          	bcp	a,#4
2275  0681 2704          	jreq	L5501
2278  0683 72125431      	bset	21553,#1
2279  0687               L5501:
2280                     ; 601 					REG_PAGE_SELECT(PAGE_ACCFILTER45);
2282  0687 35045427      	mov	21543,#4
2283                     ; 602 					CAN_FillFilterPageReg(filterSet,0);
2285  068b 4b00          	push	#0
2286  068d 1e02          	ldw	x,(OFST+2,sp)
2287  068f cd044a        	call	_CAN_FillFilterPageReg
2289  0692 84            	pop	a
2290                     ; 603 					if (filterSet->Enable) CAN_CFCR2 |= 0x01;
2292  0693 1e01          	ldw	x,(OFST+1,sp)
2293  0695 e608          	ld	a,(8,x)
2294  0697 a510          	bcp	a,#16
2295  0699 2704          	jreq	L737
2298  069b 72105434      	bset	21556,#0
2299  069f               L737:
2300                     ; 604 				case 0x60:	// filter5 page 4
2300                     ; 605 					CAN_CFCR2 &= ~0x70;
2302  069f c65434        	ld	a,21556
2303  06a2 a48f          	and	a,#143
2304  06a4 c75434        	ld	21556,a
2305                     ; 606 					CAN_CFCR2 |= (filterSet->BankCfg << 5)& 0x60;				
2307  06a7 1e01          	ldw	x,(OFST+1,sp)
2308  06a9 e608          	ld	a,(8,x)
2309  06ab a403          	and	a,#3
2310  06ad 4e            	swap	a
2311  06ae 48            	sll	a
2312  06af a4e0          	and	a,#224
2313  06b1 a460          	and	a,#96
2314  06b3 ca5434        	or	a,21556
2315  06b6 c75434        	ld	21556,a
2316                     ; 607 					CAN_CFMR1 &= ~0x30;
2318  06b9 c65431        	ld	a,21553
2319  06bc a4cf          	and	a,#207
2320  06be c75431        	ld	21553,a
2321                     ; 608 					if (filterSet->RegL_ID) CAN_CFMR1 |= 0x04;
2323  06c1 1e01          	ldw	x,(OFST+1,sp)
2324  06c3 e608          	ld	a,(8,x)
2325  06c5 a508          	bcp	a,#8
2326  06c7 2704          	jreq	L3601
2329  06c9 72145431      	bset	21553,#2
2330  06cd               L3601:
2331                     ; 609 					if (filterSet->RegH_ID) CAN_CFMR1 |= 0x08;
2333  06cd 1e01          	ldw	x,(OFST+1,sp)
2334  06cf e608          	ld	a,(8,x)
2335  06d1 a504          	bcp	a,#4
2336  06d3 2704          	jreq	L7601
2339  06d5 72165431      	bset	21553,#3
2340  06d9               L7601:
2341                     ; 610 					REG_PAGE_SELECT(PAGE_ACCFILTER45);
2343  06d9 35045427      	mov	21543,#4
2344                     ; 611 					CAN_FillFilterPageReg(filterSet,1);
2346  06dd 4b01          	push	#1
2347  06df 1e02          	ldw	x,(OFST+2,sp)
2348  06e1 cd044a        	call	_CAN_FillFilterPageReg
2350  06e4 84            	pop	a
2351                     ; 612 					if (filterSet->Enable) CAN_CFCR2 |= 0x10;
2353  06e5 1e01          	ldw	x,(OFST+1,sp)
2354  06e7 e608          	ld	a,(8,x)
2355  06e9 a510          	bcp	a,#16
2356  06eb 2704          	jreq	L777
2359  06ed 72185434      	bset	21556,#4
2360  06f1               L777:
2361                     ; 616 		EI();
2364  06f1 9a            rim
2366                     ; 636 }
2369  06f2 85            	popw	x
2370  06f3 81            	ret
2405                     ; 643 void CAN_SilentMode (u8 enable)
2405                     ; 644 {
2406                     	switch	.text
2407  06f4               _CAN_SilentMode:
2409  06f4 88            	push	a
2410       00000000      OFST:	set	0
2413                     ; 645 	Flags.RxBuffFull = FALSE;
2415  06f5 3f01          	clr	_Flags+1
2416                     ; 646   Flags.TxBuffFull = FALSE;
2418  06f7 3f00          	clr	_Flags
2419                     ; 647 	DI();						// disable interrupts
2422  06f9 9b            sim
2424                     ; 649   CAN->CMCR |= 0x01;			// issue Initialization Mode entry request
2426  06fa 72105420      	bset	21536,#0
2428  06fe               L5111:
2429                     ; 651   while (!(CAN->CMSR & 0x01));
2431  06fe c65421        	ld	a,21537
2432  0701 a501          	bcp	a,#1
2433  0703 27f9          	jreq	L5111
2434                     ; 653 	if (enable){
2436  0705 0d01          	tnz	(OFST+1,sp)
2437  0707 2706          	jreq	L1211
2438                     ; 654 		CAN->CDGR &= ~0x02U;  // Silent
2440  0709 72135426      	bres	21542,#1
2442  070d 2004          	jra	L3211
2443  070f               L1211:
2444                     ; 656 		CAN->CDGR |= 0x02U;  // Acive
2446  070f 72125426      	bset	21542,#1
2447  0713               L3211:
2448                     ; 658 	EI();	
2451  0713 9a            rim
2453                     ; 659 }
2456  0714 84            	pop	a
2457  0715 81            	ret
2492                     ; 666 void CAN_LoopbackMode (u8 enable)
2492                     ; 667 {
2493                     	switch	.text
2494  0716               _CAN_LoopbackMode:
2496  0716 88            	push	a
2497       00000000      OFST:	set	0
2500                     ; 668 	Flags.RxBuffFull = FALSE;
2502  0717 3f01          	clr	_Flags+1
2503                     ; 669   Flags.TxBuffFull = FALSE;
2505  0719 3f00          	clr	_Flags
2506                     ; 670 	DI();						// disable interrupts
2509  071b 9b            sim
2511                     ; 672   CAN->CMCR |= 0x01;			// issue Initialization Mode entry request
2513  071c 72105420      	bset	21536,#0
2515  0720               L5411:
2516                     ; 674   while (!(CAN->CMSR & 0x01));
2518  0720 c65421        	ld	a,21537
2519  0723 a501          	bcp	a,#1
2520  0725 27f9          	jreq	L5411
2521                     ; 676 	if (enable){
2523  0727 0d01          	tnz	(OFST+1,sp)
2524  0729 2706          	jreq	L1511
2525                     ; 677 		CAN->CDGR &= ~0x01U;  // Silent
2527  072b 72115426      	bres	21542,#0
2529  072f 2004          	jra	L3511
2530  0731               L1511:
2531                     ; 679 		CAN->CDGR |= 0x01U;  // Acive
2533  0731 72105426      	bset	21542,#0
2534  0735               L3511:
2535                     ; 681 	EI();	
2538  0735 9a            rim
2540                     ; 682 }
2543  0736 84            	pop	a
2544  0737 81            	ret
2620                     	xdef	_CAN_FillFilterPageReg
2621                     	xdef	f_CAN_RX_ISR
2622                     	xdef	f_CAN_TX_ISR
2623                     	switch	.ubsct
2624  0000               _Flags:
2625  0000 0000          	ds.b	2
2626                     	xdef	_Flags
2627  0002               L12_rxReadBuffPtr:
2628  0002 00            	ds.b	1
2629  0003               L71_rxBuffPtr:
2630  0003 00            	ds.b	1
2631  0004               L51_RxMsgBuff:
2632  0004 000000000000  	ds.b	72
2633                     	xdef	_CAN_SilentMode
2634                     	xdef	_CAN_LoopbackMode
2635                     	xdef	_CAN_EnableRetrasnmit
2636                     	xdef	_CAN_SetFilters
2637                     	xdef	_CAN_SetBaudRate
2638                     	xdef	_CAN_GetMsg
2639                     	xdef	_CAN_Write
2640                     	xdef	_CAN_Stop
2641                     	xdef	_CAN_Start
2642                     	xdef	_CAN_Init
2643                     	xref.b	c_lreg
2644                     	xref.b	c_x
2645                     	xref.b	c_y
2665                     	xref	c_itol
2666                     	xref	c_itolx
2667                     	xref	c_lgor
2668                     	xref	c_llsh
2669                     	xref	c_lor
2670                     	xref	c_rtol
2671                     	xref	c_lursh
2672                     	xref	c_ltor
2673                     	end
