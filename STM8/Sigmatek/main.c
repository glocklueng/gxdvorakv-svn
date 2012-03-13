/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */

#include <stm8l10x.h>
#include <codes.h>
//#include <stm8_macro.h>
//#include <stm8_type.h>
//   --------  VARIABLES DEFINITION ---------

#define INIT_PER_H 	0xD2
#define INIT_PER_L 	0xF0
#define INIT_COMP_H 	0x8C
#define INIT_COMP_L 	0xA0
#define LOG_1_PER_H 	0x23
#define LOG_1_PER_L 	0x28
#define LOG_0_PER_H 	0x11
#define LOG_0_PER_L 	0x80
#define BITST_CMP_H 	0x08
#define BITST_CMP_L 	0xC0
#define REPEAT_PER_H	0xaf
#define REPEAT_PER_L	0x00

typedef struct{
	u8 *cmd;
	u8 bitSend;			//0 = init,1 = cmdx[0]:0,......
}SEND_STATUS_TYPE;
	


volatile SEND_STATUS_TYPE sendStatus;
volatile u8 zeroCounter;
volatile u8 pressedKey;		// filtered state of pressed key
volatile u8 repeatCounter;


// ---- prototypes -------
void SendCommand(u8 *command);

//   --------  CODE -------------

void Delay(u16 time)
{
	for (; time > 0; -- time){
		nop();		
	}
}


void CLK_Init(void)
{
		CLK->CKDIVR = 0x00;		// 16 MHz clock
		// peripheral clock enable
		CLK->PCKENR = CLK_PCKENR_TIM2 | CLK_PCKENR_TIM3|CLK_PCKENR_TIM4	;		
			
}

void GPIO_Init(void)
{
		GPIOA->DDR = 0x00;
		GPIOA->CR1 = 0x00;
		
		GPIOB->DDR = 0xFB;		//PB4..7  KB read out
		GPIOB->CR1 = 0xFB;
		
		GPIOC->DDR = 0x70;		//PC4..6  KB read out
		GPIOC->CR1 = 0x70;		
			
		GPIOD->DDR = 0x00;		// PD0..6 KB read IN
		GPIOD->CR1 = 0x7F;
		//GPIOD->CR2 = 0x7F;		// EI enable
		EXTI->CR3  = 0x08;	// PD - faling edge int
		EXTI->CONF |= 0x0C;		// PD used for EXTID
			
}

/**
*		timer for 38KHz generation
*/
void TIM2_Init(void)
{
		TIM2->CCMR1 = 0x60 | TIM_CCMR_OCxPE;
		TIM2->CCER1 = TIM_CCER1_CC1E | TIM_CCER1_CC1P;		
		TIM2->BKR |= TIM_BKR_MOE;
		TIM2->CR1 =  TIM_CR1_ARPE;
		TIM2->IER =  0x00;
		
		TIM2->PSCR = 0x00;	// f master/1

		TIM2->ARRH = 0x01;
		TIM2->ARRL = 0xA5;
			
		TIM2->CCR1H = 0x00;
		TIM2->CCR1L = 0xD2;
		TIM2->EGR |= 	TIM_EGR_UG;
		TIM2->CR1 |=  TIM_CR1_CEN; //start
	
}

/**
*  timer for bit stream timing
*/
void TIM3_Init(void)
{
		TIM3->CCMR1 = 0x40 | TIM_CCMR_OCxPE;
		TIM3->CCER1 = TIM_CCER1_CC1E;		
		TIM3->BKR |= TIM_BKR_MOE;		
		TIM3->CR1 =  TIM_CR1_ARPE;
		TIM3->IER =  0x00;		
		TIM3->PSCR = 0x02;	// f master/4 = 4MHz
		TIM3->ARRH = 0x8c;
		TIM3->ARRL = 0xA0;			
		TIM3->CCR1H = 0x23;
		TIM3->CCR1L = 0x00;
	//	TIM3->EGR |= 	TIM_EGR_UG;
	//	TIM3->CR1 |=  TIM_CR1_CEN; //start	
}

/**
*  timer for repeat command sequence send
*/
void TIM4_Init(void)
{
		TIM4->CR1 =  TIM_CR1_ARPE | TIM_CR1_URS;
		TIM4->IER =  0;//TIM_IER_UIE;		
		TIM4->PSCR = 0x0d;	// f master/8192
		TIM4->ARR = 0xd6;			
		TIM4->EGR |= 	TIM_EGR_UG;
	//	TIM3->CR1 |=  TIM_CR1_CEN; //start	
}


/**
*  timer 3 interrupt - send next bit
*/
@far @interrupt void TIM3_UPD_OVF_Interrupt (void)
{
	u8 bitValue;
	
	//GPIOB->ODR |= 0x01; debug
	
	// bit send = 0 ===>>>  sent initialization part
	//								in ARR was 0bit value, which was stored to count 
	//								registers by UPD event, now the 0 bit is in proces 
	//								and new data should be prepared to ARR shadow register
	//								to be ready fo next Interrup by update event
	//++sendStatus.bitSend;   // prepare value for this bit to ARR
	
	if (sendStatus.bitSend < 8 ){
		bitValue = sendStatus.cmd[0] & (0x80U >> sendStatus.bitSend);
	}else if (sendStatus.bitSend < 16 ){
		bitValue = sendStatus.cmd[1] & (0x8000U >> sendStatus.bitSend);
	}else if (sendStatus.bitSend < 24 ){
		bitValue = sendStatus.cmd[2] & (0x800000U >> sendStatus.bitSend);
	}else if (sendStatus.bitSend < 32 ){
		bitValue = sendStatus.cmd[3] & (0x80000000U >> sendStatus.bitSend);
	}else if (sendStatus.bitSend == 32 ){ // wait to finish bit 31 
		bitValue = 1;	// send ending frame
	}else{	// last bit
		TIM3->IER |= 	TIM_IER_CC1IE; // enable interrup for OCMP where timer 
												// should be switched off - after ending part		
	}
	
	++sendStatus.bitSend;
	
	if (bitValue){
		TIM3->ARRH = 	LOG_1_PER_H;
		TIM3->ARRL = 	LOG_1_PER_L;			
	}else{
		TIM3->ARRH = 	LOG_0_PER_H;
		TIM3->ARRL = 	LOG_0_PER_L;			
	}
	TIM3->CCR1H = 	BITST_CMP_H;
	TIM3->CCR1L = 	BITST_CMP_L;
	
	TIM3->SR1 = 0;	// clr int flag
  //GPIOB->ODR &= ~0x01; debug
}
/**
*		timer 3 interrup - stop timer when last bit is send
*/
@far @interrupt void TIM3_CC_Interrupt (void)
{
	TIM3->CCMR1 = 	0x00;  // frozen mode
	TIM3->CR1 &= ~TIM_CR1_CEN; 	//stop of timer
	TIM3->SR1 = 0x00;	// clr int flag
	sendStatus.bitSend = 0;
}

/**
*  timer 4 interrupt - key still pressed - send repeat sequence
*/
@far @interrupt void TIM4_UPD_OVF_Interrupt (void)
{
		sendStatus.bitSend = 0xf0;	
		TIM3->CCMR1 = 	0x00;  // frozen mode
		TIM3->ARRH 	= 	REPEAT_PER_H;
		TIM3->ARRL 	= 	REPEAT_PER_L;			
		TIM3->CCR1H = 	INIT_COMP_H;
		TIM3->CCR1L = 	INIT_COMP_L;		
		TIM3->EGR 	|= 	TIM_EGR_UG;
		TIM3->CCMR1 = 	0x60 | TIM_CCMR_OCxPE;		// PWM 1 mode
		TIM3->SR1 	= 	0;						// clr IF flags
		TIM3->IER 	= 	TIM_IER_UIE;  // only overflow Int enable	
		TIM3->CR1 	|= 	TIM_CR1_CEN; 	//start of timer
// set first bit data to be ready for update event
// store data to shadow registers - this will be loaded to 
// timer in first update interrupt
		TIM3->ARRH = 	LOG_1_PER_H;
		TIM3->ARRL = 	LOG_1_PER_L;			
		TIM3->CCR1H = 	BITST_CMP_H;
		TIM3->CCR1L = 	BITST_CMP_L;
		
		TIM4->SR1 	= 	0;  // clear IF
}
/**
*
*/
void IR_Stop(void){
	TIM4->CR1 &=  ~TIM_CR1_CEN; //stop timer	
}

/**
*
*/
void IR_Repeat(void)
{	
// typically do nothing - repeat is automatic until stop is call
		if ((pressedKey == 20) || (pressedKey == 16)){  // CH+ and CH-
			++repeatCounter;
			if (repeatCounter > 16){
					repeatCounter = 0;
					IR_Stop();
					SendCommand(keyToCmd[pressedKey]);
			}
		}
}

/**
*
*/
void SendCommand(u8 *command)
{
		sendStatus.cmd = command;
		sendStatus.bitSend = 0;	
		TIM3->CCMR1 = 	0x00;  // frozen mode
		TIM3->ARRH 	= 	INIT_PER_H;
		TIM3->ARRL 	= 	INIT_PER_L;			
		TIM3->CCR1H = 	INIT_COMP_H;
		TIM3->CCR1L = 	INIT_COMP_L;		
		TIM3->EGR 	|= 	TIM_EGR_UG;
		TIM3->CCMR1 = 	0x60 | TIM_CCMR_OCxPE;		// PWM 1 mode
		TIM3->SR1 	= 	0;						// clr IF flags
		TIM3->IER 	= 	TIM_IER_UIE;  // only overflow Int enable	
		TIM3->CR1 	|= 	TIM_CR1_CEN; 	//start of timer
		
		TIM4->IER 	= 	0;
		TIM4->EGR 	|= 	TIM_EGR_UG;
		TIM4->SR1 	= 	0;
		TIM4->IER 	= 	TIM_IER_UIE;				
		TIM4->CR1 	|=  TIM_CR1_CEN; //start	

// set first bit data to be ready for update event
	/*	if (sendStatus.cmd[0] & 0x80U){
			TIM3->ARRH = 	LOG_1_PER_H;
			TIM3->ARRL = 	LOG_1_PER_L;			
		}else{
			TIM3->ARRH = 	LOG_0_PER_H;
			TIM3->ARRL = 	LOG_0_PER_L;			
		}
		TIM3->CCR1H = 	BITST_CMP_H;
		TIM3->CCR1L = 	BITST_CMP_L;
		TIM3->EGR 	|= 	TIM_EGR_UG;*/
	
}

/**
*		0 = all active (0)
*     1..7   active only one from 1..7, rest is configured as INPUT
*/
void SetOutsState(u8 state)
{
	switch (state){
		case 0:		// all set Out and 0
				GPIOB->ODR &= ~0xf0;		//b4..7 LOW
				GPIOC->ODR &= ~0x70;		//c4..6 LOW
				GPIOB->DDR |= 0xF0;		// b4..7 out								
				GPIOC->DDR |= 0x70;		// c4..6 out
				
		break;
		case 1:			// b4..b7
		case 2:
		case 3:
		case 4:
				GPIOB->DDR &= ~0xF0;		// b4..7 inp
				GPIOC->DDR &= ~0x70;		// c4..6 inp
				GPIOB->ODR &= ~0xF0;		//b4..7 low
				GPIOC->ODR &= ~0x70;		//c4..6 low
				GPIOB->DDR |= (0x10 << (state-1));		// mask for 0x10 for  state =1    ..0x80 for state 4				
		break;
		case 5:
		case 6:
		case 7:
				GPIOB->DDR &= ~0xF0;		// b4..7 inp
				GPIOC->DDR &= ~0x70;		// c4..6 inp
				GPIOB->ODR &= ~0xf0;		//b4..7 low
				GPIOC->ODR &= ~0x70;		//c4..6 low
				GPIOC->DDR |= (0x10 << (state-5));		// mask for 0x10 for  state =1    ..0x40 for state 				
		default:
		break;
	}
}

/**
*		return the Key index in evolved matrix
*   0xff =  more than 1 key pressed
*		0 = no key pressed
*  row index 1..7
*/
u8 CheckKbRow(u8 rowIdx, u8 inStates)
{
	u8 i, kIndex;;
		
	rowIdx = (rowIdx-1)* 7;
	kIndex = 0;
	for ( i = 1; i <8;++i){
		if (inStates & 0x01){
			if (kIndex == 0){
				kIndex = rowIdx+i;
			}	else return 0xFF;
		}
		inStates >>= 1;
	}	
	return kIndex;
}
/**
*
*
void Sleep()
{
	SetOutsState(kbStep);
	GPIOD->CR2 = 0x7F;		// EI enable
}


/**
*  Interrupt from input
*/
@far @interrupt void EXTID_Interrupt (void)
{
		// wakeup by pressed button	
	GPIOD->CR2 &= ~0x7F;		// EI disable
	EXTI->SR2 &= 0x02;
	return;
}
/**
*
*/
void main()
{
	u16 i;
	u8 kbStep = 0;
	u8 keyIndex;		// key pressed acros all matrix		
	u8 lastKeyIndex;	// key presed in previous reading
	u8 rowKeyIndex;   // pressed key inside one row
 
	u8 keyRdSM;			// SM for key reading and filterring

		
	disableInterrupts();
	CLK_Init();
	GPIO_Init();
	TIM2_Init();
	TIM3_Init();
	TIM4_Init();
	
	//IRTIM->CR = IRTIM_CR_EN |IRTIM_CR_HSEN;
	enableInterrupts();
	
	keyRdSM =0;
	sendStatus.bitSend	= 0;
	
	
		SendCommand(keyToCmd[pressedKey]);
	//	Delay (20000);
	//	IR_Stop();
	while (1){	}
	while (1){
	// check if any key is preesed
	/*	kbStep = 0;					
		SetOutsState(kbStep);		
		do {
			Delay(20);		
			if ((~GPIOD->IDR) & 0x7F){ // some button pressed
				kbStep = 1;					
			}
		}while (kbStep == 0);
	// end od check*/
#if 0		
		keyRdSM = 1;
		lastKeyIndex = 0;
		pressedKey = 0;
		zeroCounter = 0;
		do {
				keyIndex = 0;
				for (kbStep = 1 ;kbStep < 8; ++kbStep){
					SetOutsState(kbStep);
					Delay(20);				
					rowKeyIndex = CheckKbRow (kbStep,~GPIOD->IDR);
					if ((rowKeyIndex >0) && (rowKeyIndex < 50)){
						if (keyIndex == 0) keyIndex = rowKeyIndex;		// 1st key detected, next check if only 1 is pressed 		
						else keyIndex = 0xFF;									// 2 key together
					}else if (keyIndex > 50){
							keyIndex = 0xFF;	// error state  - 2 together
					}					
				}
				if (keyIndex <50){					
					switch (keyRdSM){
						case 1:	// first reading							
								lastKeyIndex = keyIndex;
								++keyRdSM	;	
							break;
						case 2:	// repeated check
						case 3:
								if (keyIndex== lastKeyIndex){
									++keyRdSM;
								}else{									
									keyRdSM = 1;
								}
								lastKeyIndex = keyIndex;
							break;
						case 4:	// change state
								if (keyIndex== lastKeyIndex){
									if (keyIndex != 0){
											if (pressedKey == keyIndex ){
													IR_Repeat();	
											}else{	
													pressedKey = keyIndex;
													IR_Stop();
													while (sendStatus.bitSend	!= 0);
										//	GPIOB->ODR |= 0x01;	// debug
													SendCommand(keyToCmd[pressedKey]);
													zeroCounter = 0;
													repeatCounter = 0;
											}											
											keyRdSM = 1;
									}else{  // nothing pressed
											pressedKey = keyIndex;
											IR_Stop();
											++zeroCounter;
											if (zeroCounter > 100){ // go to sleep
													keyRdSM = 0;
													zeroCounter = 0;
											}										
									}
								}else{
									keyRdSM = 1;
								}
								lastKeyIndex = keyIndex;
							break;					
						default :
							keyRdSM = 0;
							break;
					}
				}
				
				Delay(10000);
		
		}while ( keyRdSM != 0);
		
		//Sleep();
			kbStep = 0;					
			SetOutsState(kbStep);	
			GPIOD->CR2 = 0x7F;		// EI enable
			halt();
			GPIOD->CR2 &= ~0x7F;		// EI disable
#endif
	}
}