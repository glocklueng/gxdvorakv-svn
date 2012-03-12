/************************************************************************************************
 	
	Task Name	:	
		
	Author		:	Vaclav Dvorak
	
	Description :   podpora inkrementalniho citace, ovladani a mereni rychlosti otaceni stroje
	
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
_LOCAL USINT 	incrementMode;
_LOCAL USINT 	incrementStatus;
_LOCAL INT 		incrementValue;	
_LOCAL BOOL 	incrementRefOld;	/* polarity of reference bit*/
/*_LOCAL INT incrementAngle;  moved to system variables */

/**
*	promenne pro vypocet rychlosti otaceni
*/
_LOCAL INT 		oldValue;   		/* predchozi pozice inkrementu*/
unsigned int 	cycleCounter;
unsigned char 	roundCounter;
unsigned char 	oldRoundCounter;
unsigned char 	roundCount;

unsigned int 	tmpOn,tmpOff;
unsigned char	brzdaAktivni;

/**
 *  initialisation
 */
_INIT void initIncrement(void) {
	incrementRefOld = incrementStatus & 0x08;
	incrementMode = 0x00;				/* 1100 0011 */	
	incrementMode = 0xC3;				/* 1100 0011 */	

}

/**
 *  reset inkrementu
 */
void resetIncrement(void) {
	incrementMode = 0x00;					
	incrementMode = 0xC3;				/* 1100 0011 */
}


/**
 *		cyclic task
 */
_CYCLIC void checkIncrement(void) {
	incrementAngle = incrementValue/4;
/*	incrementAngle = incrementValue*7.2/4;   /* pro novy inkrement. senzor*/

	if (incrementAngle <0){
		incrementAngle += 360;			
	}
	
	if (resetIncrementNow){
		resetIncrement();
		resetIncrementNow = 0;
	}
	
	/* test na pozadavek brzdeni */

	if (brzda_St){
		tmpOn = nastaveni.brzda.ON_angle; 
		tmpOff = nastaveni.brzda.OFF_angle;
			
		if (tmpOn > tmpOff){
			if (incrementAngle > tmpOn || incrementAngle < tmpOff){
				/*brzdi*/
				brzdaAktivni = 1;
			}else {
				/* nebrzdi*/
				brzdaAktivni = 0;
			}
		}else {
			if (incrementAngle > tmpOn && incrementAngle < tmpOff){
				/*brzdi*/
				brzdaAktivni = 1;
			}else {
				/*nebrzdi*/
				brzdaAktivni = 0;
			}
		}
	}else{
		brzdaAktivni = 0;
	}

	
/* 		VYPOCET nastaveni otacek
	   	10 ot  =  2.8  V    = 9175 dig
	   	40 ot  =  10.0 V	= 32767 dig
	 
	 	dig_out = 786,4*[ot/min] +1311
	
		rozliseni 12 bit ale musim poslat hodnotu jako pro 16bit(+- 10V)=> 32767   0..10V  
		pouzije se pouze hornich 12 ze 16   */
	
	/*	ovladani rychlosti otaceni*/
	switch (stateMachine){
		case SM_ON :
		case SM_READY:
		case SM_START_PRESSED:
		case SM_CRITICAL_ERROR:
		case SM_IO_TEST:
		case SM_RUN_TEST: 
		case SM_READY_NO_PREPARE:
		case SM_WAIT_STOP:
		default:
			ao_menic = 0;
		break;

		case SM_PRE_START:			
			if (brzdaAktivni == 0){
				ao_menic = 	786.4 * otacky_nast + 1311;
			}else{
				ao_menic = (786.4 * otacky_nast + 1311)* (100-nastaveni.brzda.value)/100.0;
			}
			
			if (incrementRefOld != (incrementStatus & 0x08)){
				stateMachine = SM_RUN;
			}
		break;
		
		case SM_STOP_PRESSED :		/* cekam na referencni znacku*/
		case SM_SOFT_ERR_NO_START :
		case SM_SOFT_ERROR :
			if (incrementRefOld != (incrementStatus & 0x08)){
			/* prisel referenci impuls */
				setGUIPage = 1;	
				actualGUIPage = 1;									
				stateMachine = SM_WAIT_STOP;
				break;
			}
			zpomalCekamDavku = 0;
		
		/* NO BREAK !!!!!!!*/
		case SM_RUN:
			if (davkovaniBtnPressed && davkovaniActive && (incrementRefOld != (incrementStatus & 0x08))){				
				davkovaniActive = 0;
				davkovaniBtnPressed = 0;
			}

			if (brzdaAktivni == 0){
				ao_menic = (786.4 * otacky_nast +1311)*(100-zpomalCekamDavku)/100.0;
			}else{
				ao_menic = (786.4 * otacky_nast + 1311)* (100-nastaveni.brzda.value)/100.0 *(100-zpomalCekamDavku)/100.0;
			}
		break;
			
	}

	incrementRefOld = (incrementStatus & 0x08);
	
	if ( ao_menic  < 400 ) 	ao_menic = 0; /*omezeni pasma kdy motor jeste nebezi */
		
	
		
	/* mereni otacek*/
	if (++cycleCounter >100){
	
		roundCounter = (incrementStatus & 0xE0 )>> 5 ;
		if (oldRoundCounter > roundCounter){
			roundCount = roundCounter - oldRoundCounter+8;
		}else{
			roundCount = roundCounter - oldRoundCounter;
		}

		/*   pocet impulsu za 1s * 60 = imp. za minutu
			 a pak /1440 protoze je 1440 ipulsu na otacku  ==   60/1440=  1/24*/
			otacky_mer =(incrementValue-oldValue+1440*roundCount)/24;
		oldValue = incrementValue;
		oldRoundCounter = roundCounter;
		cycleCounter = 0;
	}		
}


