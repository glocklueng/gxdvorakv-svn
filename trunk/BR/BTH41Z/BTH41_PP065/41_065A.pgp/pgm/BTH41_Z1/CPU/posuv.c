/************************************************************************************************
 	
	Task Name	:	
		
	Author		:	Vaclav Dvorak
	
	Description :   podpora inkrementalniho citace pro posuv folie
	
	History		:	Version			Date			Name			Comment
													VD				created
************************************************************************************************/

#include <bur/plc.h> 
#include <bur/plctypes.h>
#include <system_variables.h>
#include <gui_variables.h>

/**
*
*/
_LOCAL USINT 	incrementPosMode;
_LOCAL USINT 	incrementPosStatus;
_LOCAL INT 		incrementPosValue;	
_LOCAL BOOL 	incrementPosRefOld;	/* polarity of reference bit*/
/*_LOCAL INT incrementAngle;  moved to system variables */

int counter;


#define  LENGTH_CONSTANT  0.20735

/**
 *  initialisation
 */
_INIT void initPosIncrement(void) {	
	incrementPosMode = 0x00;				/* 1100 0011 */	
	incrementPosMode = 0xC3;				/* 1100 0011 */	
 	o_resetInkrementPosuvu =1;
}



/**
 *		cyclic task
 */
_CYCLIC void checkSlideIncrement(void) {
	
	incrementLength = (int)(incrementPosValue * (float)LENGTH_CONSTANT);

	switch (posuvSM){
		case PSM_READY : /* 0  ready to go */
		default:
			/* do nothing */
			if (stateMachine != SM_IO_TEST)	o_resetInkrementPosuvu =1;
			counter = 0;
		break;
		case PSM_RESTART:
			o_resetInkrementPosuvu =1;
			posuvSM =PSM_START; 
		break;
		case PSM_START: /* 1 started */
			o_resetInkrementPosuvu =0;		
			if (incrementPosValue == 0)	{
				posuvSM = PSM_RUN;
				counter = 0;
			}else{
				++counter;
				if (counter >10) posuvSM = PSM_RESTART;
			}
				
		break;
		case PSM_RUN: /* 2 running */
			o_releKA2_posuvFolie = 1;
			
			ao_posuv = nastaveni.posuv_folie.rychlost * 32767/100.0;
			
			if (fotonka_St && (incrementLength > nastaveni.posuv_folie.FOT_start)){							
				posuvSM = PSM_FOT;								
			}
			
			if (incrementLength > nastaveni.posuv_folie.delka){	
					o_releKA2_posuvFolie = 0;
					posuvSM = PSM_FINISHED;
					ao_posuv = 0;
			}
		break;
		case PSM_FOT: /*jedu na fotonku */
			ao_posuv = nastaveni.posuv_folie.rychlost * 32767/100.0;
			if (i_fotonka || (incrementLength > nastaveni.posuv_folie.delka)){
				o_releKA2_posuvFolie = 0;
				ao_posuv = 0;
				posuvSM = PSM_FINISHED;			
			}		
		break;
		case PSM_FINISHED: /* posuv finished , po odjeti ze spinaciho uhlu se SM nastavi na 0*/
			/* do nothing, jenom cekam na reset */
		break;
	}
}