   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  43                     ; 25 void ADC_Init(void)
  43                     ; 26 {      
  45                     	switch	.text
  46  0000               _ADC_Init:
  50                     ; 27 		ADC->CR1 = 0x00;
  52  0000 725f5401      	clr	21505
  53                     ; 28 		ADC->CR2 = 0x00 | ADC_CR2_ALIGN; // right alignment  (16bit usage)
  55  0004 35085402      	mov	21506,#8
  56                     ; 29 		ADC->CSR = 0x00;
  58  0008 725f5400      	clr	21504
  59                     ; 30 		ADC->CR1 |= ADC_CR1_ADON;
  61  000c 72105401      	bset	21505,#0
  62                     ; 31 }       
  65  0010 81            	ret
 109                     ; 41 const u16 ADC_GetValue(const u8 chanel)
 109                     ; 42 {
 110                     	switch	.text
 111  0011               _ADC_GetValue:
 113  0011 88            	push	a
 114  0012 89            	pushw	x
 115       00000002      OFST:	set	2
 118                     ; 43 		u16 result = 0;
 120                     ; 45 		ADC->CR2 |= ADC_CR2_ALIGN; // right alignment  (16bit usage)
 122  0013 72165402      	bset	21506,#3
 123                     ; 46 		ADC->CSR &= (u8)(~0x0F);  
 125  0017 c65400        	ld	a,21504
 126  001a a4f0          	and	a,#240
 127  001c c75400        	ld	21504,a
 128                     ; 47 		ADC->CSR |= (u8)(chanel & 0x0F);  
 130  001f 7b03          	ld	a,(OFST+1,sp)
 131  0021 a40f          	and	a,#15
 132  0023 ca5400        	or	a,21504
 133  0026 c75400        	ld	21504,a
 134                     ; 48 		NOP();
 137  0029 9d            nop
 139                     ; 49 		NOP();
 142  002a 9d            nop
 144                     ; 50 		NOP();
 147  002b 9d            nop
 149                     ; 51 		NOP();
 152  002c 9d            nop
 154                     ; 54 		ADC->CR1 |= ADC_CR1_ADON;
 156  002d 72105401      	bset	21505,#0
 158  0031               L54:
 159                     ; 56 		while (!(ADC->CSR & ADC_CSR_EOC));
 161  0031 c65400        	ld	a,21504
 162  0034 a580          	bcp	a,#128
 163  0036 27f9          	jreq	L54
 164                     ; 57 		result= ADC->DRL;
 166  0038 c65405        	ld	a,21509
 167  003b 5f            	clrw	x
 168  003c 97            	ld	xl,a
 169  003d 1f01          	ldw	(OFST-1,sp),x
 170                     ; 58 		result+= ((u16)ADC->DRH) <<8;
 172  003f c65404        	ld	a,21508
 173  0042 5f            	clrw	x
 174  0043 97            	ld	xl,a
 175  0044 4f            	clr	a
 176  0045 02            	rlwa	x,a
 177  0046 72fb01        	addw	x,(OFST-1,sp)
 178  0049 1f01          	ldw	(OFST-1,sp),x
 179                     ; 59 		ADC->CSR &= ~ADC_CSR_EOC;
 181  004b 721f5400      	bres	21504,#7
 182                     ; 60 		return result;
 184  004f 1e01          	ldw	x,(OFST-1,sp)
 187  0051 5b03          	addw	sp,#3
 188  0053 81            	ret
 231                     ; 71 const u8 ADC_GetValue8b(const u8 chanel)
 231                     ; 72 {
 232                     	switch	.text
 233  0054               _ADC_GetValue8b:
 235  0054 88            	push	a
 236  0055 88            	push	a
 237       00000001      OFST:	set	1
 240                     ; 73 		u8 result = 0;
 242                     ; 75 		ADC->CSR &= (u8)(~0x0F);  
 244  0056 c65400        	ld	a,21504
 245  0059 a4f0          	and	a,#240
 246  005b c75400        	ld	21504,a
 247                     ; 76 		ADC->CSR |= (u8)(chanel & 0x0F);  
 249  005e 7b02          	ld	a,(OFST+1,sp)
 250  0060 a40f          	and	a,#15
 251  0062 ca5400        	or	a,21504
 252  0065 c75400        	ld	21504,a
 253                     ; 77 		ADC->CR2 &= ~ADC_CR2_ALIGN; // left alignment  (8bit usage)
 255  0068 72175402      	bres	21506,#3
 256                     ; 81 		ADC->CR1 |= ADC_CR1_ADON;
 258  006c 72105401      	bset	21505,#0
 260  0070               L57:
 261                     ; 83 		while (!(ADC->CSR & ADC_CSR_EOC));
 263  0070 c65400        	ld	a,21504
 264  0073 a580          	bcp	a,#128
 265  0075 27f9          	jreq	L57
 266                     ; 84 		result= ADC->DRH;
 268  0077 c65404        	ld	a,21508
 269  007a 6b01          	ld	(OFST+0,sp),a
 270                     ; 85 		ADC->CSR &= ~ADC_CSR_EOC;
 272  007c 721f5400      	bres	21504,#7
 273                     ; 86 		return result;
 275  0080 7b01          	ld	a,(OFST+0,sp)
 278  0082 85            	popw	x
 279  0083 81            	ret
 292                     	xdef	_ADC_GetValue8b
 293                     	xdef	_ADC_GetValue
 294                     	xdef	_ADC_Init
 313                     	end
