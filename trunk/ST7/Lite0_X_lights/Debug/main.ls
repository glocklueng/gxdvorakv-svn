   1                     ; C Compiler for ST7 (COSMIC Software)
   2                     ; Generator V4.5b - 07 Sep 2004
 389                     .const:	section	.text
 390  0000               _PWM_MIN:
 391  0000 00c8          	dc.w	200
 392  0002               _PWM_MAX:
 393  0002 0898          	dc.w	2200
 394  0004               _PWM_L1:
 395  0004 0258          	dc.w	600
 396  0006               _PWM_L2:
 397  0006 0514          	dc.w	1300
 398  0008               _PWM_L3:
 399  0008 0708          	dc.w	1800
 400  000a               _PWM_L4:
 401  000a 07d0          	dc.w	2000
 402  000c               _DELAY:
 403  000c 012c          	dc.w	300
 438                     ; 38 volatile @interrupt void LT_OF_Interrupt(void)
 438                     ; 39 { 
 439                     	switch	.text
 440  0000               _LT_OF_Interrupt:
 444                     ; 40 	PADR ^= 0x20;
 446  0000 b600          	ld	a,_PADR
 447  0002 a820          	xor	a,#32
 448  0004 b700          	ld	_PADR,a
 449                     ; 41 	LTCSR;
 451  0006 b60b          	ld	a,_LTCSR
 452                     ; 42 	return;
 455  0008 80            	iret
 477                     ; 48 volatile @interrupt void AT_OF_Interrupt(void)
 477                     ; 49 { 
 478                     	switch	.text
 479  0009               _AT_OF_Interrupt:
 483                     ; 50 	return;
 486  0009 80            	iret
 513                     ; 56 volatile @interrupt void AT_CMP_Interrupt(void)
 513                     ; 57 {  
 514                     	switch	.text
 515  000a               _AT_CMP_Interrupt:
 519                     ; 58 		DCR0H = (uint8)(pwm >>8 );
 521  000a b601          	ld	a,_pwm
 522  000c b717          	ld	_DCR0H,a
 523                     ; 59 		DCR0L = (uint8)(pwm & 0x00ff);
 525  000e b602          	ld	a,_pwm+1
 526  0010 a4ff          	and	a,#255
 527  0012 b718          	ld	_DCR0L,a
 528                     ; 60 		PWM0CSR;
 530  0014 b613          	ld	a,_PWM0CSR
 531                     ; 61 		WDC_Refresh();
 533  0016 100b          	bset	_LTCSR,#0
 534                     ; 62 		return;
 537  0018 80            	iret
 578                     ; 68 volatile @interrupt void AWU_Interrupt(void)
 578                     ; 69 {  
 579                     	switch	.text
 580  0019               _AWU_Interrupt:
 582       00000001      OFST:	set	1
 583  0019 88            	push	a
 586                     ; 71 	AWUCSR;
 588  001a b64a          	ld	a,_AWUCSR
 589                     ; 72 	PADR &= ~0x20;
 591  001c 1b00          	bres	_PADR,#5
 593  001e               L103:
 594                     ; 73 	while(!(ADCCSR & 0x80));
 596  001e b634          	ld	a,_ADCCSR
 597  0020 a580          	bcp	a,#128
 598  0022 27fa          	jreq	L103
 599                     ; 74 	darknes = ADCDRH;
 601  0024 96            	ld	x,s
 602  0025 b635          	ld	a,_ADCDRH
 603  0027 e701          	ld	(OFST+0,x),a
 604                     ; 75 	if (darknes <  initial){
 606  0029 96            	ld	x,s
 607  002a e601          	ld	a,(OFST+0,x)
 608  002c b100          	cp	a,L712_initial
 609  002e 2407          	jruge	L503
 610                     ; 76 		AWUCSR |= 0x01;
 612  0030 104a          	bset	_AWUCSR,#0
 613                     ; 77 		PADR |= 0x20;		
 615  0032 1a00          	bset	_PADR,#5
 616                     ; 78 		Halt;
 619  0034 8e            HALT
 623  0035 2004          	jra	L703
 624  0037               L503:
 625                     ; 80 		ATCSR |= 0x01;
 627  0037 100d          	bset	_ATCSR,#0
 628                     ; 81 		PWMCR |= 0x01;		
 630  0039 1012          	bset	_PWMCR,#0
 631  003b               L703:
 632                     ; 83 	return;
 635  003b 84            	pop	a
 636  003c 80            	iret
 727                     ; 91 void main (void)
 727                     ; 92 {
 728                     	switch	.text
 730                     	xref.b	_main$L
 731  003d               _main:
 734                     ; 99 	AVDTHCR = 0x83;		//  fcpu  = frc /16
 736  003d a683          	ld	a,#131
 737  003f b73e          	ld	_AVDTHCR,a
 738                     ; 100 	RCCR = 0x70;		// 
 740  0041 a670          	ld	a,#112
 741  0043 b739          	ld	_RCCR,a
 742                     ; 102 	PADR = 0x00;
 744  0045 3f00          	clr	_PADR
 745                     ; 103 	PADDR |= 0x21;		
 747  0047 b601          	ld	a,_PADDR
 748  0049 aa21          	or	a,#33
 749  004b b701          	ld	_PADDR,a
 750                     ; 104 	PAOR  = 0x31;   	// push pull PA0, pullup PA4
 752  004d a631          	ld	a,#49
 753  004f b702          	ld	_PAOR,a
 754                     ; 106 	EICR2 = 0x02;		// PA4-EI3 falling edge
 756  0051 a602          	ld	a,#2
 757  0053 b73d          	ld	_EICR2,a
 758                     ; 108 	ADCCSR = 0x02;		// ch 2 = PA2
 760  0055 a602          	ld	a,#2
 761  0057 b734          	ld	_ADCCSR,a
 762                     ; 109 	ADCCSR |= 0x20;  //ADC ON
 764  0059 1a34          	bset	_ADCCSR,#5
 765                     ; 110 	initD = 0;
 767  005b 3ff9          	clr	_main$L-7
 768  005d 3ffa          	clr	_main$L-6
 769                     ; 113 	if (!(PADR & 0x10)){
 771  005f b600          	ld	a,_PADR
 772  0061 a510          	bcp	a,#16
 773  0063 2703          	jreq	L06
 774  0065 cc010b        	jp	L343
 775  0068               L06:
 776                     ; 114 		PAOR  &= ~0x10;   // disable interrupts
 778  0068 1902          	bres	_PAOR,#4
 779                     ; 116 		for (i = 0;i<8;++i){
 781  006a 3ffe          	clr	_main$L-2
 782  006c 3fff          	clr	_main$L-1
 783  006e               L553:
 784                     ; 118 			while(!(ADCCSR & 0x80));
 786  006e b634          	ld	a,_ADCCSR
 787  0070 a580          	bcp	a,#128
 788  0072 27fa          	jreq	L553
 789                     ; 119 			initD += ADCDRH;
 791  0074 b635          	ld	a,_ADCDRH
 792  0076 bbfa          	add	a,_main$L-6
 793  0078 b7fa          	ld	_main$L-6,a
 794  007a 2402          	jrnc	L61
 795  007c 3cf9          	inc	_main$L-7
 796  007e               L61:
 797                     ; 116 		for (i = 0;i<8;++i){
 799  007e 3cff          	inc	_main$L-1
 800  0080 2602          	jrne	L02
 801  0082 3cfe          	inc	_main$L-2
 802  0084               L02:
 805  0084 b6ff          	ld	a,_main$L-1
 806  0086 a008          	sub	a,#8
 807  0088 b6fe          	ld	a,_main$L-2
 808  008a a200          	sbc	a,#0
 809  008c 2be0          	jrmi	L553
 810                     ; 121 		initial = (uint8)(initD>>3);
 812  008e b6fa          	ld	a,_main$L-6
 813  0090 bef9          	ld	x,_main$L-7
 814  0092 54            	srl	x
 815  0093 46            	rrc	a
 816  0094 54            	srl	x
 817  0095 46            	rrc	a
 818  0096 54            	srl	x
 819  0097 46            	rrc	a
 820  0098 b700          	ld	L712_initial,a
 821                     ; 122 		if (initial > 10 ) initial -=10;
 823  009a b600          	ld	a,L712_initial
 824  009c a10b          	cp	a,#11
 825  009e 2506          	jrult	L163
 828  00a0 b600          	ld	a,L712_initial
 829  00a2 a00a          	sub	a,#10
 830  00a4 b700          	ld	L712_initial,a
 831  00a6               L163:
 832                     ; 123 		EECSR |= 0x02;
 834  00a6 1230          	bset	_EECSR,#1
 835                     ; 124 		EE_Bright = initial;
 837  00a8 b600          	ld	a,L712_initial
 838  00aa c71010        	ld	_EE_Bright,a
 839                     ; 125 		EECSR |= 0x01;
 841  00ad 1030          	bset	_EECSR,#0
 842                     ; 126 		WDC_Refresh();
 844  00af 100b          	bset	_LTCSR,#0
 846  00b1               L563:
 847                     ; 127 		while(EECSR & 0x01);
 849  00b1 b630          	ld	a,_EECSR
 850  00b3 a501          	bcp	a,#1
 851  00b5 26fa          	jrne	L563
 852                     ; 128 		WDC_Refresh();
 854  00b7 100b          	bset	_LTCSR,#0
 855                     ; 129 		for (i = 0; i< 5;++i){
 857  00b9 3ffe          	clr	_main$L-2
 858  00bb 3fff          	clr	_main$L-1
 859  00bd               L173:
 860                     ; 130 			PADR |= 0x01;
 862  00bd 1000          	bset	_PADR,#0
 863                     ; 131 			for (j = 1800; j>1; --j);
 865  00bf ae07          	ld	x,#7
 866  00c1 bffc          	ld	_main$L-4,x
 867  00c3 a608          	ld	a,#8
 868  00c5 b7fd          	ld	_main$L-3,a
 869  00c7               L773:
 873  00c7 3dfd          	tnz	_main$L-3
 874  00c9 2602          	jrne	L22
 875  00cb 3afc          	dec	_main$L-4
 876  00cd               L22:
 877  00cd 3afd          	dec	_main$L-3
 880  00cf b6fd          	ld	a,_main$L-3
 881  00d1 a002          	sub	a,#2
 882  00d3 b6fc          	ld	a,_main$L-4
 883  00d5 a200          	sbc	a,#0
 884  00d7 24ee          	jruge	L773
 885                     ; 132 			WDC_Refresh();
 887  00d9 100b          	bset	_LTCSR,#0
 888                     ; 133 				PADR &= ~0x01;
 890  00db 1100          	bres	_PADR,#0
 891                     ; 134 			for (j = 1800; j>1; --j);		
 893  00dd ae07          	ld	x,#7
 894  00df bffc          	ld	_main$L-4,x
 895  00e1 a608          	ld	a,#8
 896  00e3 b7fd          	ld	_main$L-3,a
 897  00e5               L504:
 901  00e5 3dfd          	tnz	_main$L-3
 902  00e7 2602          	jrne	L42
 903  00e9 3afc          	dec	_main$L-4
 904  00eb               L42:
 905  00eb 3afd          	dec	_main$L-3
 908  00ed b6fd          	ld	a,_main$L-3
 909  00ef a002          	sub	a,#2
 910  00f1 b6fc          	ld	a,_main$L-4
 911  00f3 a200          	sbc	a,#0
 912  00f5 24ee          	jruge	L504
 913                     ; 135 			WDC_Refresh();
 915  00f7 100b          	bset	_LTCSR,#0
 916                     ; 129 		for (i = 0; i< 5;++i){
 918  00f9 3cff          	inc	_main$L-1
 919  00fb 2602          	jrne	L62
 920  00fd 3cfe          	inc	_main$L-2
 921  00ff               L62:
 924  00ff b6ff          	ld	a,_main$L-1
 925  0101 a005          	sub	a,#5
 926  0103 b6fe          	ld	a,_main$L-2
 927  0105 a200          	sbc	a,#0
 928  0107 2bb4          	jrmi	L173
 930  0109 2005          	jra	L314
 931  010b               L343:
 932                     ; 138 		initial = EE_Bright;
 934  010b c61010        	ld	a,_EE_Bright
 935  010e b700          	ld	L712_initial,a
 936  0110               L314:
 937                     ; 145 	AWUCSR = 0x01;
 939  0110 a601          	ld	a,#1
 940  0112 b74a          	ld	_AWUCSR,a
 941                     ; 146 	AWUPR = 0xff;
 943  0114 a6ff          	ld	a,#255
 944  0116 b749          	ld	_AWUPR,a
 945                     ; 149 	ATRH = 0x06;
 947  0118 a606          	ld	a,#6
 948  011a b710          	ld	_ATRH,a
 949                     ; 150 	ATRL = 0x0A;
 951  011c a60a          	ld	a,#10
 952  011e b711          	ld	_ATRL,a
 953                     ; 151 	DCR0H = 0x06;
 955  0120 a606          	ld	a,#6
 956  0122 b717          	ld	_DCR0H,a
 957                     ; 152 	DCR0L = 0x0B;
 959  0124 a60b          	ld	a,#11
 960  0126 b718          	ld	_DCR0L,a
 961                     ; 153 	ATCSR = 0x11;				// CMP IE enable
 963  0128 a611          	ld	a,#17
 964  012a b70d          	ld	_ATCSR,a
 965                     ; 154 	PWM0CSR = 0x00;
 967  012c 3f13          	clr	_PWM0CSR
 968                     ; 155 	PWMCR = 0x01;
 970  012e a601          	ld	a,#1
 971  0130 b712          	ld	_PWMCR,a
 972                     ; 156 	pwm = 1550;
 974  0132 ae06          	ld	x,#6
 975  0134 bf01          	ld	_pwm,x
 976  0136 a60e          	ld	a,#14
 977  0138 b702          	ld	_pwm+1,a
 978                     ; 159 	EnableInterrupts;
 981  013a 9a            RIM
 983  013b               L514:
 984                     ; 162 		for (i = PWM_MIN; i<PWM_MAX;  ){			
 986  013b a6c8          	ld	a,#200
 987  013d b7ff          	ld	_main$L-1,a
 988  013f 3ffe          	clr	_main$L-2
 989  0141               L124:
 990                     ; 164 			for (j = DELAY; j>1; --j);			
 992  0141 ae01          	ld	x,#1
 993  0143 bffc          	ld	_main$L-4,x
 994  0145 a62c          	ld	a,#44
 995  0147 b7fd          	ld	_main$L-3,a
 996  0149               L724:
1000  0149 3dfd          	tnz	_main$L-3
1001  014b 2602          	jrne	L03
1002  014d 3afc          	dec	_main$L-4
1003  014f               L03:
1004  014f 3afd          	dec	_main$L-3
1007  0151 b6fd          	ld	a,_main$L-3
1008  0153 a002          	sub	a,#2
1009  0155 b6fc          	ld	a,_main$L-4
1010  0157 a200          	sbc	a,#0
1011  0159 24ee          	jruge	L724
1012                     ; 165 			pwm = i+1545;
1014  015b b6ff          	ld	a,_main$L-1
1015  015d befe          	ld	x,_main$L-2
1016  015f ab09          	add	a,#9
1017  0161 88            	push	a
1018  0162 9f            	ld	a,x
1019  0163 a906          	adc	a,#6
1020  0165 97            	ld	x,a
1021  0166 84            	pop	a
1022  0167 bf01          	ld	_pwm,x
1023  0169 b702          	ld	_pwm+1,a
1024                     ; 166 			if (i < PWM_L1) {i++;}
1026  016b b6ff          	ld	a,_main$L-1
1027  016d a058          	sub	a,#88
1028  016f b6fe          	ld	a,_main$L-2
1029  0171 a202          	sbc	a,#2
1030  0173 2408          	jruge	L534
1033  0175 3cff          	inc	_main$L-1
1034  0177 2602          	jrne	L23
1035  0179 3cfe          	inc	_main$L-2
1036  017b               L23:
1038  017b 204c          	jra	L734
1039  017d               L534:
1040                     ; 167 			else if (i <PWM_L2) {i+=2;}
1042  017d b6ff          	ld	a,_main$L-1
1043  017f a014          	sub	a,#20
1044  0181 b6fe          	ld	a,_main$L-2
1045  0183 a205          	sbc	a,#5
1046  0185 240c          	jruge	L144
1049  0187 b6ff          	ld	a,_main$L-1
1050  0189 ab02          	add	a,#2
1051  018b b7ff          	ld	_main$L-1,a
1052  018d 2402          	jrnc	L43
1053  018f 3cfe          	inc	_main$L-2
1054  0191               L43:
1056  0191 2036          	jra	L734
1057  0193               L144:
1058                     ; 168 				else if (i<PWM_L3){ i+=3;}
1060  0193 b6ff          	ld	a,_main$L-1
1061  0195 a008          	sub	a,#8
1062  0197 b6fe          	ld	a,_main$L-2
1063  0199 a207          	sbc	a,#7
1064  019b 240c          	jruge	L544
1067  019d b6ff          	ld	a,_main$L-1
1068  019f ab03          	add	a,#3
1069  01a1 b7ff          	ld	_main$L-1,a
1070  01a3 2402          	jrnc	L63
1071  01a5 3cfe          	inc	_main$L-2
1072  01a7               L63:
1074  01a7 2020          	jra	L734
1075  01a9               L544:
1076                     ; 169 					else if (i< PWM_L4){ i+=4;}
1078  01a9 b6ff          	ld	a,_main$L-1
1079  01ab a0d0          	sub	a,#208
1080  01ad b6fe          	ld	a,_main$L-2
1081  01af a207          	sbc	a,#7
1082  01b1 240c          	jruge	L154
1085  01b3 b6ff          	ld	a,_main$L-1
1086  01b5 ab04          	add	a,#4
1087  01b7 b7ff          	ld	_main$L-1,a
1088  01b9 2402          	jrnc	L04
1089  01bb 3cfe          	inc	_main$L-2
1090  01bd               L04:
1092  01bd 200a          	jra	L734
1093  01bf               L154:
1094                     ; 170 							else i+=5;										
1096  01bf b6ff          	ld	a,_main$L-1
1097  01c1 ab05          	add	a,#5
1098  01c3 b7ff          	ld	_main$L-1,a
1099  01c5 2402          	jrnc	L24
1100  01c7 3cfe          	inc	_main$L-2
1101  01c9               L24:
1102  01c9               L734:
1103                     ; 162 		for (i = PWM_MIN; i<PWM_MAX;  ){			
1105  01c9 b6ff          	ld	a,_main$L-1
1106  01cb a098          	sub	a,#152
1107  01cd b6fe          	ld	a,_main$L-2
1108  01cf a208          	sbc	a,#8
1109  01d1 2403          	jruge	L26
1110  01d3 cc0141        	jp	L124
1111  01d6               L26:
1112                     ; 173 		for (i = PWM_MAX-1; i>= PWM_MIN; ){						
1114  01d6 ae08          	ld	x,#8
1115  01d8 bffe          	ld	_main$L-2,x
1116  01da a697          	ld	a,#151
1117  01dc b7ff          	ld	_main$L-1,a
1118  01de               L554:
1119                     ; 174 			for (j = DELAY; j>1; --j);			
1121  01de ae01          	ld	x,#1
1122  01e0 bffc          	ld	_main$L-4,x
1123  01e2 a62c          	ld	a,#44
1124  01e4 b7fd          	ld	_main$L-3,a
1125  01e6               L364:
1129  01e6 3dfd          	tnz	_main$L-3
1130  01e8 2602          	jrne	L44
1131  01ea 3afc          	dec	_main$L-4
1132  01ec               L44:
1133  01ec 3afd          	dec	_main$L-3
1136  01ee b6fd          	ld	a,_main$L-3
1137  01f0 a002          	sub	a,#2
1138  01f2 b6fc          	ld	a,_main$L-4
1139  01f4 a200          	sbc	a,#0
1140  01f6 24ee          	jruge	L364
1141                     ; 175 			pwm = i+1545;
1143  01f8 b6ff          	ld	a,_main$L-1
1144  01fa befe          	ld	x,_main$L-2
1145  01fc ab09          	add	a,#9
1146  01fe 88            	push	a
1147  01ff 9f            	ld	a,x
1148  0200 a906          	adc	a,#6
1149  0202 97            	ld	x,a
1150  0203 84            	pop	a
1151  0204 bf01          	ld	_pwm,x
1152  0206 b702          	ld	_pwm+1,a
1153                     ; 176 			if (i < PWM_L1) --i;
1155  0208 b6ff          	ld	a,_main$L-1
1156  020a a058          	sub	a,#88
1157  020c b6fe          	ld	a,_main$L-2
1158  020e a202          	sbc	a,#2
1159  0210 240a          	jruge	L174
1162  0212 3dff          	tnz	_main$L-1
1163  0214 2602          	jrne	L64
1164  0216 3afe          	dec	_main$L-2
1165  0218               L64:
1166  0218 3aff          	dec	_main$L-1
1168  021a 204c          	jra	L374
1169  021c               L174:
1170                     ; 177 				else if (i <PWM_L2) i-=2;
1172  021c b6ff          	ld	a,_main$L-1
1173  021e a014          	sub	a,#20
1174  0220 b6fe          	ld	a,_main$L-2
1175  0222 a205          	sbc	a,#5
1176  0224 240c          	jruge	L574
1179  0226 b6ff          	ld	a,_main$L-1
1180  0228 a002          	sub	a,#2
1181  022a b7ff          	ld	_main$L-1,a
1182  022c 2402          	jrnc	L05
1183  022e 3afe          	dec	_main$L-2
1184  0230               L05:
1186  0230 2036          	jra	L374
1187  0232               L574:
1188                     ; 178 					else if (i<PWM_L3) i-=3;
1190  0232 b6ff          	ld	a,_main$L-1
1191  0234 a008          	sub	a,#8
1192  0236 b6fe          	ld	a,_main$L-2
1193  0238 a207          	sbc	a,#7
1194  023a 240c          	jruge	L105
1197  023c b6ff          	ld	a,_main$L-1
1198  023e a003          	sub	a,#3
1199  0240 b7ff          	ld	_main$L-1,a
1200  0242 2402          	jrnc	L25
1201  0244 3afe          	dec	_main$L-2
1202  0246               L25:
1204  0246 2020          	jra	L374
1205  0248               L105:
1206                     ; 179 						else if (i<PWM_L4) i-=4;
1208  0248 b6ff          	ld	a,_main$L-1
1209  024a a0d0          	sub	a,#208
1210  024c b6fe          	ld	a,_main$L-2
1211  024e a207          	sbc	a,#7
1212  0250 240c          	jruge	L505
1215  0252 b6ff          	ld	a,_main$L-1
1216  0254 a004          	sub	a,#4
1217  0256 b7ff          	ld	_main$L-1,a
1218  0258 2402          	jrnc	L45
1219  025a 3afe          	dec	_main$L-2
1220  025c               L45:
1222  025c 200a          	jra	L374
1223  025e               L505:
1224                     ; 180 							else i-=5;						
1226  025e b6ff          	ld	a,_main$L-1
1227  0260 a005          	sub	a,#5
1228  0262 b7ff          	ld	_main$L-1,a
1229  0264 2402          	jrnc	L65
1230  0266 3afe          	dec	_main$L-2
1231  0268               L65:
1232  0268               L374:
1233                     ; 173 		for (i = PWM_MAX-1; i>= PWM_MIN; ){						
1235  0268 b6ff          	ld	a,_main$L-1
1236  026a a0c8          	sub	a,#200
1237  026c b6fe          	ld	a,_main$L-2
1238  026e a200          	sbc	a,#0
1239  0270 2503          	jrult	L46
1240  0272 cc01de        	jp	L554
1241  0275               L46:
1242                     ; 182 		if(ADCCSR & 0x80){
1244  0275 b634          	ld	a,_ADCCSR
1245  0277 a580          	bcp	a,#128
1246  0279 2603          	jrne	L66
1247  027b cc013b        	jp	L514
1248  027e               L66:
1249                     ; 183 			darknes = ADCDRH;
1251  027e b635          	ld	a,_ADCDRH
1252  0280 b7fb          	ld	_main$L-5,a
1253                     ; 184 			if (darknes <  initial){
1255  0282 b6fb          	ld	a,_main$L-5
1256  0284 b100          	cp	a,L712_initial
1257  0286 2503          	jrult	L07
1258  0288 cc013b        	jp	L514
1259  028b               L07:
1260                     ; 185 				ATCSR &= ~0x03;
1262  028b b60d          	ld	a,_ATCSR
1263  028d a4fc          	and	a,#252
1264  028f b70d          	ld	_ATCSR,a
1265                     ; 186 				PWMCR &= ~0x01;
1267  0291 1112          	bres	_PWMCR,#0
1268                     ; 187 				PADR &= ~ 0x01;
1270  0293 1100          	bres	_PADR,#0
1271                     ; 188 				Halt;
1274  0295 8e            HALT
1277  0296 cc013b        	jp	L514
1381                     	xdef	_main
1382                     	xdef	_AWU_Interrupt
1383                     	xdef	_AT_CMP_Interrupt
1384                     	xdef	_AT_OF_Interrupt
1385                     	xdef	_LT_OF_Interrupt
1386                     	switch	.ubsct
1387  0000               L712_initial:
1388  0000 00            	ds.b	1
1389                     	xdef	_DELAY
1390                     	xdef	_PWM_L4
1391                     	xdef	_PWM_L3
1392                     	xdef	_PWM_L2
1393                     	xdef	_PWM_L1
1394                     	xdef	_PWM_MAX
1395                     	xdef	_PWM_MIN
1396  0001               _pwm:
1397  0001 0000          	ds.b	2
1398                     	xdef	_pwm
1418                     	end
