/******************** (c) 2009 STMicroelectronics ****************************
VERSION  : 				$Revision: 1.2 $
DATE 		: 				$Date: 2009/09/23 12:16:55 $
AUTHOR 	: 				ABUE-AES  Vaclav Dvorak / $Author: Vaclav dvorak $

MODIFICATIONS :

					Detektor kabelu Varianta  A - 8 (9) kabelu  

*******************************************************************************/


//#include <stdlib.h>
#include <stm8_map.h>

#include "gpio.h"
#include "timer4.h"

/**
*		types for CLK source selection
*/
typedef enum {CLK_HSI = 0xE1, CLK_LSI = 0xD2, CLK_HSE = 0xB4} CLK_TYPE;




//group 1  PC1..PC4
#define OUT_A	0x02
#define OUT_B 0x04
#define OUT_C 0x08
#define OUT_D 0x10
//group 2  PD0..PD4
#define OUT_E 0x01
#define OUT_F 0x04
#define OUT_G 0x08
#define OUT_H 0x10
#define OUT_I 0x02

//group 1 PB2..PB0
#define IN_A	0x20
#define IN_B 	0x10
#define IN_C	0x08
#define IN_D 	0x04
#define IN_E	0x02
#define IN_F	0x01
//group 2 PC5..PC7
#define IN_G 	0x20
#define IN_H	0x40
#define IN_I	0x80

// test steps - output DR+DDR settings
u8 OUT_group1_mask[]={OUT_A ,OUT_B,OUT_C,OUT_D,  0,0,0,0};// PC1...PC4
u8 OUT_group2_mask[]={0,0,0,0, OUT_E,OUT_F,OUT_G,OUT_H};
// test steps - input mask for IDR
u8 IN_group1_mask[]={  0 ,IN_C,IN_F,IN_D,IN_A,IN_E,IN_B,0};// PC1...PC4
u8 IN_group2_mask[]={IN_H,  0 ,  0 , 0  ,  0 ,  0 , 0  ,IN_G};

#define OUT1_ODR GPIOC->ODR
#define OUT2_ODR GPIOD->ODR

#define OUT1_DDR GPIOC->DDR
#define OUT2_DDR GPIOD->DDR

#define OUT1_IDR GPIOC->IDR
#define OUT2_IDR GPIOD->IDR

#define IN1_IDR		GPIOB->IDR
#define IN2_IDR		GPIOC->IDR


#define IN_group1_BASE 0x3F		//1 tam kde je vstup
#define IN_group2_BASE 0x60

#define OUT_group1_BASE 0x00	// 0 = input, 1 = musi byt output
#define OUT_group2_BASE 0x00

#define OUT_group1_BASE_Mask  0x1E	// 1 tam kde je nekdy vystup
#define OUT_group2_BASE_Mask  0x1D


#define TEST_PAIRS 	8
/*

1. krok   Out A =  output, 1->0->1
2. 	      ostatni Out B. Out I  = vstupy
3.        testovat jestli je log 1 synchronni s Out A pouze na IN A
4. prekonfigurovat na OUT B........


/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description :
 *	Comments :  
 *****************************************************************************/
bool TestStep(u8 testCaseNbr)
{
		bool result = false;

		// nastavim 1 output na vystup
		OUT1_DDR = OUT_group1_BASE |OUT_group1_mask[testCaseNbr];
		OUT2_DDR = OUT_group2_BASE |OUT_group2_mask[testCaseNbr];
		
		//nastavim 1 na jednom vystupu
		OUT1_ODR = OUT_group1_BASE |OUT_group1_mask[testCaseNbr];
		OUT2_ODR = OUT_group2_BASE |OUT_group2_mask[testCaseNbr];
		
		SetTimeoutTime(10);
		while (!IsTimeoutExpired());
		// test pruchodnosti - jeden vstup(maskovany podle zvoleneho vystupu musi byt nastaveny
		if (! ((IN1_IDR & IN_group1_BASE &  IN_group1_mask[testCaseNbr]) ||
				(IN2_IDR & IN_group2_BASE &  IN_group2_mask[testCaseNbr]))) {
				return false; //- neprochazi
		}
		// test zkratu na zadnem vstupu (ostatnich) nesmi byt 1 krome testovaneho
		if ((IN1_IDR & IN_group1_BASE &  ~IN_group1_mask[testCaseNbr]) ||
				(IN2_IDR & IN_group2_BASE &  ~IN_group2_mask[testCaseNbr])) {
			return false;// - zkrat
		}
		// test zkratu 2 - take na zadnem z ostatnich vystupu nesmi byt 1 ( v IN modu)
		if ((OUT1_IDR & OUT_group1_BASE_Mask &  ~OUT_group1_mask[testCaseNbr]) ||
				(OUT2_IDR & OUT_group2_BASE_Mask &  ~OUT_group2_mask[testCaseNbr])) {
			return false;// - zkrat
		}
		
		// test na nulovy stav - nastaveim 1 na vsechny vystupy krome testovaneho
		OUT1_DDR = OUT_group1_BASE_Mask; // vsechny vystupy jako vystupy
		OUT2_DDR = OUT_group2_BASE_Mask; 
		
		OUT1_ODR = OUT_group1_BASE_Mask & ~OUT_group1_mask[testCaseNbr]; // nastav vsechny vystup krome jednoho
		OUT2_ODR = OUT_group2_BASE_Mask & ~OUT_group2_mask[testCaseNbr]; 
		
		SetTimeoutTime(10);
		while (!IsTimeoutExpired());
		// test pruchodnosti  a zkratu - testovany vstup musi byt 0
		if ( ((IN1_IDR & IN_group1_BASE &  IN_group1_mask[testCaseNbr]) ||
				  (IN2_IDR & IN_group2_BASE &  IN_group2_mask[testCaseNbr]))) {
				return false;
		}
		 return true;
	
}




/*****************************************************************************
 * Name : 	   
 * Input:
 * Output:  
 * Description : Conigure of master clock
 *	Comments :  
 *****************************************************************************/
void CLK_Init(CLK_TYPE target)
{
	const u8 CLK_DIVIDERS = 0x00;
	
	CLK->ECKR |=  0x01;
	CLK->CKDIVR = CLK_DIVIDERS;								// fCPU = fMASTER = 16 MHz
	if ( CLK->CMSR != target){
		CLK->SWCR = CLK_SWCR_SWEN;				// Enable CLK switch execution
		CLK->SWR = target;									// HSE selected as master CLK
		while (!(CLK->SWCR & CLK_SWCR_SWIF));
		if (CLK->CMSR != target	)			// check for CLK switch finished		
		{
			// error in switching -- reset
		}
	}
}


	
/**
*
*/
void main()
{
	u16 tmp;
	u8 tmp8, tmp8_A,i;
	bool result;

	 //RC => fcp 
	//CLK_Init(CLK_HSI);  // internal RC as a clock source
	CLK->CKDIVR = 0;	
	disableInterrupts();
	GPIO_Init();	
	TIM4_Init();


	enableInterrupts();	
	OK = 0;
	FAIL = 0;
	
	do{
		
		if (START == 0){
			
				//nastavim 1 vystup do 0
				OUT1_ODR = OUT_group1_BASE;		
				OUT2_ODR = OUT_group2_BASE;
				
				SetTimeoutTime(10);
				while (!IsTimeoutExpired());
				
				// test zkratu na VCC - na zadnem vstupu nesmi byt 1 
				if ((IN1_IDR & IN_group1_BASE ) ||
						(IN2_IDR & IN_group2_BASE )) {
					 FAIL = 1;// - neni klidovy stav
					 OK = 1;
				}else	{
					
						result = true;
						for (i = 0; i < TEST_PAIRS; ++i){
								
								SetTimeoutTime(10);
								while (!IsTimeoutExpired());
								
								result  &= TestStep(i);
						
						}
						
						if (result){
								 OK = 1;
								 FAIL = 0;
						}	else {
								 OK = 0;
								 FAIL = 1;
						}
				}
				//SetTimeoutTime(7000);
				//while (!IsTimeoutExpired());
				while (!START);
				OK = 0;
				FAIL = 0;						
				SetTimeoutTime(2000);
				while (!IsTimeoutExpired());
		}
		
			
		
		/** LED Flashing **/
		if (GetLedState()){
			LED_ON;
			//CAN_Write(&CAN_TxMsg);
		}else {
			LED_OFF;
		}
		
	} while (1);

}

/*** (c) 2009  STMicroelectronics ****************** END OF FILE ***/