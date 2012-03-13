/************************************************************************************************
 	
	Task Name	:	
		
	Author		:	Vaclav Dvorak
	
	Description :   podpora grafiky GUI pro reakce na vsechny knofliky
	
	History		:	Version			Date			Name			Comment
													VD				created
************************************************************************************************/

#include <bur/plc.h> 
#include <bur/plctypes.h>
/*#include <visapi.h>*/
/*#include <operator.h>*/
#include <gui_variables.h>
#include <system_variables.h>
#include "stdio.h"

_LOCAL UINT 				nastaveniLabelIndex; /* urcuje poradi popisku z textGoup AdjLabels*/
_LOCAL UINT 				nastBtnPressed;
_LOCAL UINT					nastAktivniIndex;	/* index aktivniho paremetru pro editaci */
_LOCAL UINT					pouzitBtnPressed;


/*****************************************************************************************
*	colors and status of buttons on adjustment pages
*			xxx_st  .... function statut  -on / off
*			xxx_ZAP_BTN	 color of the ZAPNOUT button
*			xxx_VYP_BTN  color of the VYPNOUT button
****************************************************************************************/ 

#define ZAP_ON 		155			/* colors of zapnout btn in on state*/
#define ZAP_OFF 	0x9A3B		/* colors of zapnout btn in off state*/
#define VYP_ON		44			/* colors of vypnout btn in on state*/
#define VYP_OFF		0x333B		/* colors of vypnout btn in off state*/
#define ZAP_IMP_ON	112			/* colors of impulse btn in on state*/
/*#define NASTAV_ON	46			/* colors of vypnout btn in on state*/


#define DAVKA_DIS		0x083B		/* davkovani btn disabled*/
#define DAVKA_ON		0x009B		/* davkovani btn ON - zelena*/
#define DAVKA_OFF		0x002c		/* davkovani btn OFF - cervena*/
#define DAVKA_CHANGE	0x0030		/* davkovani btn CHANGE - oranzova*/




_LOCAL UINT davkovacZ_ZAP_Btn; /* button color */
_LOCAL UINT davkovacZ_VYP_Btn; /* button color */

_LOCAL UINT davkovacV_ZAP_Btn;
_LOCAL UINT davkovacV_VYP_Btn;

_LOCAL UINT podrazeni_ZAP_Btn;
_LOCAL UINT podrazeni_VYP_Btn;

_LOCAL UINT posuv_ZAP_Btn;
_LOCAL UINT posuv_VYP_Btn;

_LOCAL UINT datovani_ZAP_Btn;
_LOCAL UINT datovani_VYP_Btn;

_LOCAL UINT strihani_ZAP_Btn;
_LOCAL UINT strihani_VYP_Btn;

_LOCAL UINT skladani_ZAP_Btn;
_LOCAL UINT skladani_VYP_Btn;

_LOCAL UINT vystrkavani_ZAP_Btn;
_LOCAL UINT vystrkavani_VYP_Btn;

_LOCAL UINT dopravnik_ZAP_Btn;
_LOCAL UINT dopravnik_VYP_Btn;

_LOCAL UINT fotonka_ZAP_Btn;
_LOCAL UINT fotonka_VYP_Btn;

_LOCAL UINT CO2_ZAP_Btn;
_LOCAL UINT CO2_VYP_Btn;

_LOCAL UINT topeni_ZAP_Btn;
_LOCAL UINT topeni_VYP_Btn;

_LOCAL UINT brzda_ZAP_Btn;
_LOCAL UINT brzda_VYP_Btn;

_LOCAL UINT topeniImpuls_ZAP_Btn;

/* colors of the start and stop buttons */
_LOCAL UINT start_Btn_col;
_LOCAL UINT stop_Btn_col;

_LOCAL UINT davkovani_Btn_col;


/**
*	Procedura pro nastaveni barev tlacitek na adjustment_page
*/
void SetAdjustmentButtons(){
	if (davkovacZ_St){
		davkovacZ_ZAP_Btn = ZAP_ON ;
		davkovacZ_VYP_Btn = VYP_OFF;
	}else{
		davkovacZ_ZAP_Btn = ZAP_OFF ;
		davkovacZ_VYP_Btn = VYP_ON;
	}	
	if (davkovacV_St){
		davkovacV_ZAP_Btn = ZAP_ON ;
		davkovacV_VYP_Btn = VYP_OFF;
	}else{
		davkovacV_ZAP_Btn = ZAP_OFF ;
		davkovacV_VYP_Btn = VYP_ON;
	}
	if (podrazeni_St){
		podrazeni_ZAP_Btn = ZAP_ON;
		podrazeni_VYP_Btn = VYP_OFF;
	}else{
		podrazeni_ZAP_Btn = ZAP_OFF;
		podrazeni_VYP_Btn = VYP_ON;
	}
	if (posuv_St){
		posuv_ZAP_Btn = ZAP_ON;
		posuv_VYP_Btn = VYP_OFF;
	}else{
		posuv_ZAP_Btn = ZAP_OFF;
		posuv_VYP_Btn = VYP_ON;
	}
	if (datovani_St){
		datovani_ZAP_Btn = ZAP_ON;
		datovani_VYP_Btn = VYP_OFF;
	}else{
		datovani_ZAP_Btn = ZAP_OFF;
		datovani_VYP_Btn = VYP_ON;
	}
	if (strihani_St){
		strihani_ZAP_Btn = ZAP_ON;
		strihani_VYP_Btn = VYP_OFF;
	}else{
		strihani_ZAP_Btn = ZAP_OFF;
		strihani_VYP_Btn = VYP_ON;
	}
	if (skladani_St){
		skladani_ZAP_Btn = ZAP_ON;
		skladani_VYP_Btn = VYP_OFF;
	}else{
		skladani_ZAP_Btn = ZAP_OFF;
		skladani_VYP_Btn = VYP_ON;
	}
	if (vystrkavani_St){
		vystrkavani_ZAP_Btn = ZAP_ON;
		vystrkavani_VYP_Btn = VYP_OFF;
	}else{
		vystrkavani_ZAP_Btn = ZAP_OFF;
		vystrkavani_VYP_Btn = VYP_ON;
	}
	if (dopravnik_St){
		dopravnik_ZAP_Btn = ZAP_ON;
		dopravnik_VYP_Btn = VYP_OFF;
	}else{
		dopravnik_ZAP_Btn = ZAP_OFF;
		dopravnik_VYP_Btn = VYP_ON;
	}
	if (fotonka_St){
		fotonka_ZAP_Btn = ZAP_ON ;
		fotonka_VYP_Btn = VYP_OFF;
	}else{
		fotonka_ZAP_Btn = ZAP_OFF;
		fotonka_VYP_Btn = VYP_ON;
	}	
	if (CO2_St){
		CO2_ZAP_Btn = ZAP_ON;
		CO2_VYP_Btn = VYP_OFF;
	}else{
		CO2_ZAP_Btn = ZAP_OFF;
		CO2_VYP_Btn = VYP_ON;
	}
	if (topeni_St){
		topeni_ZAP_Btn = ZAP_ON;
		topeni_VYP_Btn = VYP_OFF;
	}else{
		topeni_ZAP_Btn = ZAP_OFF;
		topeni_VYP_Btn = VYP_ON;
	}
/*	neni potreba, pouzil jsem     toggle datapoint
	if (topeniImpuls_St){
	 	topeniImpuls_ZAP_Btn = ZAP_IMP_ON;
	}else{
		topeniImpuls_ZAP_Btn = ZAP_OFF;
	}*/
	
	if (brzda_St){
		brzda_ZAP_Btn = ZAP_ON;
		brzda_VYP_Btn = VYP_OFF;
	}else{
		brzda_ZAP_Btn = ZAP_OFF;
		brzda_VYP_Btn = VYP_ON;
	}

}




/**
 *	procedure for initialization of variables
 */

_INIT void InitGui(void) {
	setGUIPage = 0;
	actualGUIPage = 0;
	/*davkovacZ_St = 0;
	davkovacV_St = 0;
	podrazeni_St = 0;
	posuv_St = 0; 
	datovani_St = 0;
	strihani_St = 0;
	skladani_St = 0;
	vystrkavani_St = 0;
	dopravnik_St = 0;
	fotonka_St = 0;
	CO2_St = 0;
	topeni_St = 0;
	brzda_St = 0;*/
	SetAdjustmentButtons();
	nastaveniLabelIndex = 0;
	nastAktivniIndex = 0;
	/* pouzivam permanent RAM */
	/*	nastaveniInit();*/  /* fill the start and end angle values for all functions  from the FLASH*/
	
	redraw1 = 0;
/*	redraw2 = 0;
	redraw3 = 0; 5.12.2011*/

	/*pageChanged = 0;*/
	start_Btn_col = ZAP_OFF ;
	stop_Btn_col = VYP_OFF;
	infoTextPointer = 0;
	
}


_CYCLIC void RunBtnControl(void) {
	
	SetAdjustmentButtons();	
	
	if (nastaveniON	== 360) nastaveniON = 0;
	else if (nastaveniON == -1) nastaveniON = 359;

	if (nastaveniON_2	== 360) nastaveniON_2 = 0;
	else if (nastaveniON_2 == -1) nastaveniON_2 = 359;
	
	if (nastaveniOFF	== 360) nastaveniOFF = 0;
	else if (nastaveniOFF == -1) nastaveniOFF = 359;
	
	/*if (nastaveniOFF_Time == -1) nastaveniOFF_Time =1000;*/
	
	if (nastBtnPressed) redraw1= 3;
	
	switch(nastBtnPressed){
		case DAVK_Z_IDX:
			nastaveniON = nastaveni.davkovani_zeli.ON1_angle;
			nastaveniON_2 = nastaveni.davkovani_zeli.ON2_angle;
			nastaveniOFF = nastaveni.davkovani_zeli.OFF_angle;
			nastAktivniIndex = nastBtnPressed;
			nastBtnPressed = 0;
		break;
		case DAVK_V_IDX:
			nastaveniON = nastaveni.davkovani_vody.ON_angle;
			nastaveniOFF_Time = nastaveni.davkovani_vody.OFF_time;
			nastAktivniIndex = nastBtnPressed;
			nastBtnPressed = 0;
		break;
		case POSUV_IDX:
			nastaveniON = nastaveni.posuv_folie.ON_angle;
			nastaveniOFF = nastaveni.posuv_folie.delka;
			nastaveniON_2 = nastaveni.posuv_folie.FOT_start;
			nastaveniValue = nastaveni.posuv_folie.rychlost;
			nastAktivniIndex = nastBtnPressed;
			nastBtnPressed = 0;
		break;				
		case STRIH_IDX:
			nastaveniON = nastaveni.strihani.ON_angle;
			nastaveniOFF = nastaveni.strihani.OFF_angle;
			nastAktivniIndex = nastBtnPressed;
			nastBtnPressed = 0;
		break;
		case SKLADANI_IDX:
			nastaveniON = nastaveni.skladani.ON_angle;
			nastaveniOFF = nastaveni.skladani.OFF_angle;
			nastAktivniIndex = nastBtnPressed;
			nastBtnPressed = 0;
		break;
		case PODRAZENI_IDX:
			nastaveniON = nastaveni.podrazeni.ON_angle;
			nastAktivniIndex = nastBtnPressed;
			nastBtnPressed = 0;
		break;
		case VYSTRKAVANI_IDX:
			nastaveniON = nastaveni.vystrkavani.ON_angle;
			nastAktivniIndex = nastBtnPressed;
			nastBtnPressed = 0;
		break;
		case DATOVANI_IDX:
			nastaveniON = nastaveni.datovani.ON_angle;
			nastaveniOFF = nastaveni.datovani.OFF_angle;
			nastAktivniIndex = nastBtnPressed;
			nastBtnPressed = 0;
		break;
		case TOPENI_IDX:
			nastaveniON = nastaveni.topeni.ON_angle;
			nastaveniOFF = nastaveni.topeni.OFF_angle;
			nastAktivniIndex = nastBtnPressed;
			nastBtnPressed = 0;
		break;
		case BRZDA_IDX:
			nastaveniON = nastaveni.brzda.ON_angle;
			nastaveniOFF = nastaveni.brzda.OFF_angle;
			nastaveniValue = nastaveni.brzda.value;
			nastAktivniIndex = nastBtnPressed;
			nastBtnPressed = 0;
		break;
	}
	
	if (pouzitBtnPressed){
		switch (nastAktivniIndex){
			case DAVK_Z_IDX:
				nastaveni.davkovani_zeli.ON1_angle= nastaveniON ;
				nastaveni.davkovani_zeli.ON2_angle=nastaveniON_2;
				nastaveni.davkovani_zeli.OFF_angle = nastaveniOFF;
				nastAktivniIndex = 0;
				pouzitBtnPressed = 0;
				/*	UlozNastaveni();   neni nutne pri pouzite permanentni RAM, tohle uklada na FLASH*/
			break;
			case DAVK_V_IDX:
				nastaveni.davkovani_vody.ON_angle = nastaveniON;
				nastaveni.davkovani_vody.OFF_time = nastaveniOFF_Time ;
				nastAktivniIndex = 0;
				pouzitBtnPressed = 0;
			break;
			case POSUV_IDX:
				nastaveni.posuv_folie.ON_angle = nastaveniON;
				nastaveni.posuv_folie.delka = nastaveniOFF;
				nastaveni.posuv_folie.FOT_start = nastaveniON_2;
				nastaveni.posuv_folie.rychlost = nastaveniValue;
				nastAktivniIndex = 0;
				pouzitBtnPressed = 0;
			break;				
			case STRIH_IDX:
				nastaveni.strihani.ON_angle = nastaveniON;
				nastaveni.strihani.OFF_angle = nastaveniOFF;
				nastAktivniIndex = 0;
				pouzitBtnPressed = 0;
			break;
			case SKLADANI_IDX:
				nastaveni.skladani.ON_angle = nastaveniON;
				nastaveni.skladani.OFF_angle = nastaveniOFF;
				nastAktivniIndex = 0;
				pouzitBtnPressed = 0;
			break;
			case PODRAZENI_IDX:
				nastaveni.podrazeni.ON_angle = nastaveniON;
				nastAktivniIndex = 0;
				pouzitBtnPressed = 0;
			break;
			case VYSTRKAVANI_IDX:
				nastaveni.vystrkavani.ON_angle = nastaveniON;
				pouzitBtnPressed = 0;
			break;
			case DATOVANI_IDX:
				nastaveni.datovani.ON_angle = nastaveniON;
				nastaveni.datovani.OFF_angle = nastaveniOFF;
				nastAktivniIndex = 0;
				pouzitBtnPressed = 0;
			break;
			case TOPENI_IDX:
				nastaveni.topeni.ON_angle = nastaveniON;
				nastaveni.topeni.OFF_angle = nastaveniOFF;
				nastAktivniIndex = 0;
				pouzitBtnPressed = 0;
			break;
			case BRZDA_IDX:
				nastaveni.brzda.ON_angle = nastaveniON;
				nastaveni.brzda.OFF_angle = nastaveniOFF;
				nastaveni.brzda.value = nastaveniValue;
				nastAktivniIndex = 0;
				pouzitBtnPressed = 0;
			break;
		}
	}



	/* barveni start a stop tlacitek*/
	switch(stateMachine){
		case SM_ON:			
			davkovani_Btn_col=DAVKA_DIS;
			davkovaniBtnPressed = 0;
			start_Btn_col = ZAP_OFF;
			stop_Btn_col = VYP_OFF;
			break;
		case SM_READY_NO_PREPARE:
			davkovani_Btn_col=DAVKA_DIS;
			davkovaniBtnPressed = 0;
			start_Btn_col = ZAP_OFF;
			stop_Btn_col = VYP_OFF;
			infoTextPointer = 6;
			davkovaniActive = 0;
			break;	
		case SM_READY:
			davkovani_Btn_col=DAVKA_DIS;
			davkovaniBtnPressed = 0;
			start_Btn_col = ZAP_ON;
			stop_Btn_col = VYP_OFF;
			infoTextPointer = 0;
			davkovaniActive = 0;
			break;
		case SM_START_PRESSED:
		case SM_PRE_START:
		case SM_RUN:
			if (davkovaniBtnPressed && !davkovaniActive){/* zapinani davkovani*/
				davkovaniActive = 1;	/* vypinani davkovani je v ovladani inkrementu*/
				zpomalCekamDavku = 0;
				davkovaniBtnPressed = 0;
			}
			
			if (!davkovaniActive){
				davkovani_Btn_col=DAVKA_ON; 
				infoTextPointer = 1;
			}else{
				if (davkovaniBtnPressed	){
					davkovani_Btn_col=DAVKA_CHANGE;
				}else{
					davkovani_Btn_col=DAVKA_OFF; 
				}
				if (zpomalCekamDavku >0 )infoTextPointer = 7;
				else infoTextPointer = 2;

			}
			start_Btn_col = ZAP_OFF;
			stop_Btn_col = VYP_ON;
			break;
		case SM_STOP_PRESSED:	
		case SM_WAIT_STOP:	
			davkovani_Btn_col=DAVKA_DIS;
			zpomalCekamDavku = 0; 
			davkovaniBtnPressed = 0;
			start_Btn_col = ZAP_OFF;
			stop_Btn_col = VYP_OFF;
			infoTextPointer = 3 ;
			break;
		case SM_SOFT_ERR_NO_START:
		case SM_SOFT_ERROR:
			davkovani_Btn_col=DAVKA_DIS;
			davkovaniBtnPressed = 0;
			zpomalCekamDavku = 0; 
			start_Btn_col = ZAP_OFF;
			stop_Btn_col = VYP_OFF;
			infoTextPointer = 4 ; 
			break;
		case SM_CRITICAL_ERROR:
		default:
			davkovani_Btn_col=DAVKA_DIS;
			davkovaniBtnPressed = 0;
			zpomalCekamDavku = 0; 
			start_Btn_col = ZAP_OFF;
			stop_Btn_col = VYP_OFF;
			infoTextPointer = 5 ;
			break;
				
	}

		
}


