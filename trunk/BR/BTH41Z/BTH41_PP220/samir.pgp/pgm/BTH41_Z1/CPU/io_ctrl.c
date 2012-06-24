/************************************************************************************************
 	
	Task Name	:	
		
	Author		:	Vaclav Dvorak		xdvorakv@centrum.cz
	
	Description :   Testovani a ovladani vstupu/vystupu, hlavni smycka funkci stroje
		
	History		:	Version			Date			Name			Comment
													VD				created
************************************************************************************************/


#include <bur/plc.h> 
#include <bur/plctypes.h>
#include <system_variables.h>
#include <gui_variables.h>





/* runtime variables */
unsigned int localTimer;
unsigned int podrazeniTimer;
unsigned int vystrkavaniTimer;
unsigned int dopravnikTimer;


_LOCAL BOOL odvijeniStartOld;
_LOCAL BOOL odvijeniStopOld;
_LOCAL BOOL davkaStavOld;
_LOCAL BOOL testModeStatus;

unsigned long VC_HANDLE;
/* end of definition */

_INIT void InitInputs(void) {
	testModeStatus = 0;
	pocetDavek = 0;
/*	otacky_nast = 15;*/
	stateMachine = SM_ON;
	localTimer = 0;
	odvijeniStartOld = i_odvijeniFolieStart;
	odvijeniStopOld = i_odvijeniFolieStop;	
	davkaVodySM   = 1;	
	davkaStavOld = o_releKA3_davkovacStart;
	if (otacky_nast <10 || otacky_nast >40) {
		otacky_nast = 10;
	}
}

/**
 *		testuje vsechny chybove stavy potrebne pro rozbeh
 */
BOOL checkReady(void){
	
	return ( i_totalStop && 
			 i_kryty && 
			 i_datovaniKoncak && 
			 /*i_tlakuVzduchu && */
			 i_tlakVzduchu_Filtered &&
			 (!topeni_St || i_teplotaDosazena || topeniImpuls_St) && 
			 (!CO2_St || i_pritomnostCO2) &&
			 !i_konecFolie
			  );	
}

/**
*	vraci 1 pokud je  SOFT ERROR, 0 = OK
*/
BOOL checkError(void){
	return (!(i_datovaniKoncak && (!topeni_St || i_teplotaDosazena || topeniImpuls_St)&& !i_konecFolie ));
}

/**
*	vraci 1 pokud je  CRITICAL ERROR, 0 = OK
*/
BOOL checkCriticalError(void){
/*	return (!(i_tlakuVzduchu && i_totalStop && i_kryty && i_poruchaMenice && i_zavzdusneni && i_pritomnostCO2  ));*/
	return (!(i_tlakVzduchu_Filtered && i_totalStop && i_kryty && i_poruchaMenice && i_zavzdusneni && (!CO2_St || i_pritomnostCO2) ));

}





/**
 *     	CYCLIC task for machine functionality controll
 * 		here are made all features (IO controll) during the run state
 */
_CYCLIC void IO_Control(void) {

unsigned int tmpOn,tmpOff, tmpFotOn,tmpFotOff;
	

	switch (testMode){
		default:		
			testModeStatus = 0;		
		break;
		case 1:		/*startuji test mod*/
			if (testModeStatus	== 0){
				startActive = 1;
				stateMachine = SM_ON;
				testModeStatus  = 1;
			}
		break;
		case 2:		/* ukoncuji test mod*/
			if (testModeStatus == 1){
				startActive = 0;
				stopActive = 1;
				stateMachine = SM_IO_TEST;
				testModeStatus = 0;
			}
		break;
	}

	
		/* STATE MACHINE */

	switch (stateMachine){
		case SM_ON:		/* stroj v klidu*/
			if (actualGUIPage ==2) setGUIPage = 0;
			o_ventilStrihani = 0;
 			o_ventilDatum = 0;
		 	o_ventilPodrazeni = 0;
		 	o_ventilSevreniPosuvRem = 0;
		  	o_ventilTrojuhSkladani = 0;
		  	o_ventilVystrkSacku = 0;
		 /*	o_releKA1_topeni = 0;*/
		 	o_releKA2_posuvFolie = 0;
		 	o_stykacOdsDopravniku = 0;
		 	o_releKA3_davkovacStart = 0;
		 	o_releKA4_davkovacVody = 0;
		 	o_ventilCO2 = 0;
			o_odvijeniFolie = 0;
			o_impulsniTopeni = 0;
								
			if (checkReady()){		/* ready*/
				if (actualGUIPage != 12) setGUIPage = 2; /* neprepinej pri testovani*/
				stateMachine = SM_READY_NO_PREPARE;
			}else{
				o_zavzdusneni = 0;
			}
		break;
		case SM_READY_NO_PREPARE:
			if (actualGUIPage ==0) setGUIPage = 2;		/* zobrazi "stisknete pripravu" */
			o_zavzdusneni = 1;	
			if (actualGUIPage != 12) startActive = 0;		
			if (i_zavzdusneni){
				stateMachine = SM_READY;
			}	
		break;			
		case SM_READY:		/* cekam na START */
			if (actualGUIPage ==0) setGUIPage = 2;
			if (!checkReady()){		
				stateMachine = SM_ON;
				setGUIPage = 0;
				o_zavzdusneni = 0;
				
			}else  if (startActive){
			
				stateMachine = SM_START_PRESSED;
				localTimer = 100;	/* 1 s casovani*/				
				o_ventilSevreniPosuvRem = 1;
				o_ventilCO2 = 1;
				startActive = 0;
				stopActive = 0;
			}
			o_zavzdusneni = 1;
			
		break;
		case SM_START_PRESSED:		/* stisknuto START - pousteny reminky a pocitam 1s*/
			if (actualGUIPage ==0) setGUIPage = 2;

			if (--localTimer < 1){
				resetIncrementNow = 1;
				stateMachine = SM_PRE_START;	/* motor se automaticky zapne*/
			}
			
			/* dopravnik */
			if (dopravnik_St){
				o_stykacOdsDopravniku = 1;
				dopravnikTimer = 0;
			}else {
				o_stykacOdsDopravniku = 0;		
			}
			
			/* E R R O R    stavy */
			if (checkError()) 	stateMachine = SM_ON;							
			/* kriticke ERROR stavy */
			if (checkCriticalError()){
				stateMachine = SM_CRITICAL_ERROR;
				ao_menic = 0;
				localTimer = 1000;
			}
		break;
		case SM_PRE_START:		/* tento stav ovlada inkrement- prepne na 5 po 1. nulovacim impulsu*/
			if (actualGUIPage ==0) setGUIPage = 2;

			if (stopActive){
				stateMachine = SM_ON;
				stopActive = 0;				
			}

			/* E R R O R    stavy */
			if (checkError()) stateMachine = SM_SOFT_ERR_NO_START;							
			/* kriticke ERROR stavy */
			if (checkCriticalError()){
				stateMachine = SM_CRITICAL_ERROR;
				ao_menic = 0;
				localTimer = 1000;
			}		

		break;
		case SM_RUN :	/* beh stroje, vsechny funkce dle nastaveneho casovani*/							
 		case SM_PAUSE:
 			if (actualGUIPage ==0) setGUIPage = 2;
 		 			
			if (davkovaniActive){
				if (!i_blokovaniDavky){
					stateMachine = SM_PAUSE;
				}else{
					stateMachine = SM_RUN;
				}
			}					
			
			if (stopActive){				
				dopravnikTimer	= 1000;
				stateMachine = SM_STOP_PRESSED;
				stopActive = 0;				
			}			
			/* E R R O R    stavy */
			/* nema to vyznam v modu 5 a 9, protoze se stejne zastavi ve vychozi poloze 
			   jako pri techto chybach*/
			if (checkError()) {
				stateMachine = SM_SOFT_ERROR;
				dopravnikTimer	= 1000;
			}
			
		
		
		/* NO BREAK  pokracuje na case 5 */			
		case SM_STOP_PRESSED: /* prepnuti do 0 po prichodu nuloveho impulsu - ovladano inkrementem*/
		case SM_SOFT_ERROR :
		/*	if (actualGUIPage ==0) setGUIPage = 2;*/

			/* kriticke ERROR stavy */
			if (checkCriticalError()){
				stateMachine = SM_CRITICAL_ERROR ;
				ao_menic = 0;
				localTimer = 1000;
				break;
			}

			if (davkovaniActive){	/* davkuj*/				
				/* davkovac zeli */				
				if (davkovacZ_St){
					tmpOn = nastaveni[davkovacZ].ON_angle; 
					tmpOff = nastaveni[davkovacZ].OFF_angle;
					if (tmpOn > tmpOff){
						if (incrementAngle > tmpOn || incrementAngle < tmpOff){
							o_releKA3_davkovacStart = 1;		
						}else {
							o_releKA3_davkovacStart = 0;					
						}
					}else {
						if (incrementAngle > tmpOn && incrementAngle < tmpOff){
							o_releKA3_davkovacStart = 1;		
						}else {
							o_releKA3_davkovacStart = 0;					
						}
					}
					/* pocitani davek*/
					if (!davkaStavOld &&  o_releKA3_davkovacStart){  /* 0 - 1 */					
						pocetDavek++;
					}
					davkaStavOld = o_releKA3_davkovacStart;
				}else{
					o_releKA3_davkovacStart = 0;
				}	
				/* davkovac vody */	
					/* davkaVodySM   	0 blokovano
									 	1 ready
									 	2 davkovani probiha*/			
				if (davkovacV_St){
					switch (davkaVodySM){
						case 0:
							tmpOn = nastaveni[davkovacV].ON_angle; 
							if (incrementAngle > tmpOn+20 ){	/* blokuju vodu na 20 stupnu po nadavkovani*/
								davkaVodySM = 1;
							}
						break;
						case 1:
							tmpOn = nastaveni[davkovacV].ON_angle; 
							timerVoda = nastaveni[davkovacV].OFF_angle / 2;/* TIME !!!*/
							if (timerVoda>1){
								if (incrementAngle >= tmpOn && incrementAngle < tmpOn+3 ){
									o_releKA4_davkovacVody = 1;														
									davkaVodySM = 2;
								}
							}else {
								o_releKA4_davkovacVody = 0;	
							}
						break;
						case 2:
						default:
						break;
					}					
				}else {
					o_releKA4_davkovacVody = 0;					
				}	
			}else {
				o_releKA3_davkovacStart = 0;
				o_releKA4_davkovacVody = 0;
			}	/* konec davkuj*/
				
			/* posuv folie */
			if (posuv_St){
				if (fotonka_St){	/* podle fotonky*/
					tmpOn = nastaveni[posuvFolie].ON_angle;	
					tmpOff = nastaveni[posuvFolie].OFF_angle;	
					tmpFotOn = nastaveni[fotonka].ON_angle; 
					tmpFotOff = nastaveni[fotonka].OFF_angle;
					
					/* zapnuti podle inkrementu*/
					if (tmpOn < tmpFotOn){
						if (incrementAngle > tmpOn && incrementAngle < tmpFotOn ){
							o_releKA2_posuvFolie = 1;
						}				
					}else{  /*jedu pres nulu */
						if (incrementAngle > tmpOn || incrementAngle < tmpFotOn ){
							o_releKA2_posuvFolie = 1;
						}				
					}
					/* vypnuti podle inkrementu  kdyz neprijde fotonka */		
					if (tmpOn > tmpOff){
						if (incrementAngle > tmpOff && incrementAngle < tmpOn){
							o_releKA2_posuvFolie = 0;					
						}
					}else {
						if (incrementAngle > tmpOff){
							o_releKA2_posuvFolie = 0;					
						}
					}	
					/* vypinani fotonkou*/
					if (tmpFotOn > tmpFotOff){
						if (incrementAngle > tmpFotOn || incrementAngle < tmpFotOff){
							if (i_fotonka){
								o_releKA2_posuvFolie = 0;		
							}
						}
					}else {
						if (incrementAngle > tmpFotOn && incrementAngle < tmpFotOff){
							if (i_fotonka){
								o_releKA2_posuvFolie = 0;		
							}
						}
					}								
				}else {	/* pouze podle inkrementu*/
					tmpOn = nastaveni[posuvFolie].ON_angle; 
					tmpOff = nastaveni[posuvFolie].OFF_angle;
	
					if (tmpOn > tmpOff){
						if (incrementAngle > tmpOn || incrementAngle < tmpOff){
							o_releKA2_posuvFolie = 1;		
						}else {
							o_releKA2_posuvFolie = 0;					
						}
					}else {
						if (incrementAngle > tmpOn && incrementAngle < tmpOff){
							o_releKA2_posuvFolie = 1;		
						}else {
							o_releKA2_posuvFolie = 0;					
						}
					}	
				}
			}else {
					o_releKA2_posuvFolie = 0;					
			}			
			
			/* podazeni sacku */
			if (podrazeni_St){
				tmpOn = nastaveni[podrazeni].ON_angle; 
				
				/* zapnout*/	
				if (incrementAngle >= tmpOn && incrementAngle < tmpOn+3){/* citlivost 2 stupne*/
					o_ventilPodrazeni= 1;
					podrazeniTimer = 200;		
				}
				/* vypnout*/
				if (i_podrazeniSacku){
					o_ventilPodrazeni= 0;				
				}
				/* test na timeout*/
				if ( o_ventilPodrazeni){
					if (podrazeniTimer < 1){
						stateMachine = SM_SOFT_ERROR  ;	
						o_ventilPodrazeni= 0;				
					}else {
						podrazeniTimer--;
					}
				}				
			}else {	
				o_ventilPodrazeni = 0;					
			}
				
			/* vystrkavani */
			if (vystrkavani_St){
				tmpOn = nastaveni[vystrkavani].ON_angle; 

				/* zapnout*/	
				if (incrementAngle >= tmpOn && incrementAngle < tmpOn+3){/* citlivost 2 stupne*/
					o_ventilVystrkSacku= 1;	
					vystrkavaniTimer = 200;	
				}
				/* vypnout*/
				if (i_vysouvaniSacku){
					o_ventilVystrkSacku = 0;					
				}
				/* test na timeout*/
				if ( o_ventilVystrkSacku){
					if (vystrkavaniTimer < 1){
						stateMachine = SM_SOFT_ERROR  ;	
						o_ventilVystrkSacku = 0;					
					}else{
						vystrkavaniTimer--;
					}
				}				
			}else {
				o_ventilVystrkSacku = 0;					
			}	
			
			/* strihani */
			if (strihani_St){
				tmpOn = nastaveni[strihani].ON_angle; 
				tmpOff = nastaveni[strihani].OFF_angle;
	
					if (tmpOn > tmpOff){
					if (incrementAngle > tmpOn || incrementAngle < tmpOff){
						o_ventilStrihani = 1;		
					}else {
						o_ventilStrihani = 0;					
					}
				}else {
					if (incrementAngle > tmpOn && incrementAngle < tmpOff){
						o_ventilStrihani = 1;		
					}else {
						o_ventilStrihani = 0;					
					}
				}	
			}else {
				o_ventilStrihani = 0;					
			}

			/* datovani */
			if (datovani_St){
				tmpOn = nastaveni[datovani].ON_angle; 
				tmpOff = nastaveni[datovani].OFF_angle;
		
				if (tmpOn > tmpOff){
					if (incrementAngle > tmpOn || incrementAngle < tmpOff){
						o_ventilDatum = 1;		
					}else {
						o_ventilDatum = 0;					
					}
				}else {
					if (incrementAngle > tmpOn && incrementAngle < tmpOff){
						o_ventilDatum = 1;		
					}else {
						o_ventilDatum = 0;					
					}
				}	
			}else {
				o_ventilDatum = 0;					
			}

			/* skladani dna */
			if (skladani_St){
				tmpOn = nastaveni[skladani].ON_angle; 
				tmpOff = nastaveni[skladani].OFF_angle;
	
				if (tmpOn > tmpOff){
					if (incrementAngle > tmpOn || incrementAngle < tmpOff){
						o_ventilTrojuhSkladani= 1;		
					}else {
						o_ventilTrojuhSkladani = 0;					
					}
				}else {
					if (incrementAngle > tmpOn && incrementAngle < tmpOff){
						o_ventilTrojuhSkladani = 1;		
					}else {
						o_ventilTrojuhSkladani = 0;					
					}
				}			
			}else {
				o_ventilTrojuhSkladani = 0;					
			}
			
			/* impulsni topeni*/	
			if (topeni_St && topeniImpuls_St){
				tmpOn = nastaveni[topeni].ON_angle; 
				tmpOff = nastaveni[topeni].OFF_angle;
	
				if (tmpOn > tmpOff){
					if (incrementAngle > tmpOn || incrementAngle < tmpOff){
						o_impulsniTopeni = 1;		
					}else {
						o_impulsniTopeni = 0;					
					}
				}else {
					if (incrementAngle > tmpOn && incrementAngle < tmpOff){
						o_impulsniTopeni = 1;		
					}else {
						o_impulsniTopeni = 0;					
					}
				}
			}else {
				o_impulsniTopeni = 0;					
			}								
			
		break;	
		case SM_SOFT_ERR_NO_START:
		/* tento stav ovlada inkrement- prepne  na 0 po 1. nulovacim impulsu*/		

		/* kriticke ERROR stavy */
			if (checkCriticalError()){
				stateMachine = SM_CRITICAL_ERROR ;
				ao_menic = 0;
				localTimer = 1000;
			}

		break;
		case SM_CRITICAL_ERROR:
			o_zavzdusneni = 0;
			o_ventilStrihani = 0;
 			o_ventilDatum = 0;
		 	o_ventilPodrazeni = 0;
		 	o_ventilSevreniPosuvRem = 0;
		  	o_ventilTrojuhSkladani = 0;
		  	o_ventilVystrkSacku = 0;
		 /*	o_releKA1_topeni = 0; nevypinat */
		 	o_releKA2_posuvFolie = 0; 
		 	o_stykacOdsDopravniku = 0;
		 	o_releKA3_davkovacStart = 0;
		 	o_releKA4_davkovacVody = 0;
		 	o_ventilCO2 = 0;
			o_odvijeniFolie = 0;
			o_impulsniTopeni = 0;

			if (--localTimer < 1){
				setGUIPage = 1;										
			}
			if (checkReady() && actualGUIPage == 1){
				stateMachine = SM_ON;	
			}			

		break;
		case SM_IO_TEST:
			startActive = 0;
			stopActive = 1;
			break;
	/*	case SM_RUN_TEST:
			startActive = 1;
			stateMachine = SM_ON;
			break;*/
		default:
			stateMachine = SM_ON;	
		break;
	}/*   konec stateMachine*/ 
	
	
/* vypnuti dopravniku 10s po STOP*/
	if (stateMachine == SM_ON || stateMachine == SM_READY||stateMachine == SM_READY_NO_PREPARE ){
		if (o_stykacOdsDopravniku && dopravnikTimer > 0){
			dopravnikTimer--;
		}else {
			o_stykacOdsDopravniku = 0;
			dopravnikTimer = 0;
		}
	}
	
	if ( stateMachine != SM_IO_TEST && stateMachine != SM_CRITICAL_ERROR  )	{
	/* blokuju tyto fce v testovacim modu a pri kritickem stopu*/
		
	/* topeni*/
		if (topeni_St && !topeniImpuls_St ){
			o_releKA1_topeni = 1;
		}else {
			o_releKA1_topeni = 0;		
		}

	/* odvijeni folie*/
		if (!odvijeniStartOld && i_odvijeniFolieStart){ /* nabezna hrana*/
			o_odvijeniFolie = 1;
		}
		if(!odvijeniStopOld && i_odvijeniFolieStop){/* nabezna hrana*/
			o_odvijeniFolie = 0;
		}
		odvijeniStartOld = i_odvijeniFolieStart;
		odvijeniStopOld = i_odvijeniFolieStop;		
	}	
}