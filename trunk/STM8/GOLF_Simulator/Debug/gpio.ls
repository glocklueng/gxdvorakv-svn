   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.10.2 - 02 Nov 2011
   3                     ; Generator (Limited) V4.3.7 - 29 Nov 2011
  43                     ; 20 void GPIO_Init(void)
  43                     ; 21 {      
  45                     	switch	.text
  46  0000               _GPIO_Init:
  50                     ; 22 		GPIOA->ODR = 0x00;
  52  0000 725f5000      	clr	20480
  53                     ; 23 		GPIOA->DDR = 0x00;
  55  0004 725f5002      	clr	20482
  56                     ; 24 		GPIOA->CR1 = 0x00;
  58  0008 725f5003      	clr	20483
  59                     ; 26 		GPIOB->DDR = 0x00;				// 0010 0000
  61  000c 725f5007      	clr	20487
  62                     ; 27 		GPIOB->CR1 = 0x00;
  64  0010 725f5008      	clr	20488
  65                     ; 28 		GPIOB->ODR = 0x00;
  67  0014 725f5005      	clr	20485
  68                     ; 30 		GPIOC->ODR = 0x00;
  70  0018 725f500a      	clr	20490
  71                     ; 31 		GPIOC->DDR = 0x10;
  73  001c 3510500c      	mov	20492,#16
  74                     ; 32     GPIOC->CR1 = 0x10;
  76  0020 3510500d      	mov	20493,#16
  77                     ; 34 		GPIOD->ODR = 0x00;
  79  0024 725f500f      	clr	20495
  80                     ; 35 		GPIOD->DDR = 0x02;
  82  0028 35025011      	mov	20497,#2
  83                     ; 36     GPIOD->CR1 = 0x02;
  85  002c 35025012      	mov	20498,#2
  86                     ; 38 		GPIOE->ODR = 0x00;
  88  0030 725f5014      	clr	20500
  89                     ; 39 		GPIOE->DDR = 0x0A;					// 0001 0000
  91  0034 350a5016      	mov	20502,#10
  92                     ; 40 		GPIOE->CR1 = 0x0A;
  94  0038 350a5017      	mov	20503,#10
  95                     ; 42 		GPIOG->ODR = 0x01;
  97  003c 3501501e      	mov	20510,#1
  98                     ; 43 		GPIOG->DDR = 0x01;					// 0001 0000
 100  0040 35015020      	mov	20512,#1
 101                     ; 44 		GPIOG->CR1 = 0x01;
 103  0044 35015021      	mov	20513,#1
 104                     ; 45 		GPIOG->CR2 = 0x02;
 106  0048 35025022      	mov	20514,#2
 107                     ; 47 }       
 110  004c 81            	ret
 123                     	xdef	_GPIO_Init
 142                     	end
