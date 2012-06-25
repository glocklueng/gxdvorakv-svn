/************************************************************************************************
 	
	Task Name	:	
		
	Author		:	Vaclav Dvorak
	
	Description :   podpora grafiky GUI pro reakce na vsechny knofliky
	
	History		:	Version			Date			Name			Comment
													VD				created
************************************************************************************************/

#include <bur/plc.h> 
#include <bur/plctypes.h>
#include <visapi.h>
#include <operator.h>
#include <dataobj.h>
#include <gui_variables.h>
#include <system_variables.h>
#include "stdio.h"

_LOCAL UINT 				nastaveniLabelIndex; /* urcuje poradi popisku z textGoup AdjLabels*/
_LOCAL UINT 				nastBtnPressed;

_LOCAL UINT					ulozBtnPressed;


/* variables for dataobject handling*/
_LOCAL UINT       		 	wStatus;
_LOCAL UDINT       			dwIdent;
_LOCAL DatObjCreate_typ    	DOCreate;
_LOCAL DatObjWrite_typ 		DOWrite;
_LOCAL DatObjRead_typ  		DORead;
_LOCAL DatObjCopy_typ  		DOCopy;
_LOCAL DatObjInfo_typ  		DOInfo;
_LOCAL DatObjDelete_typ    	DODelete;



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


#define DAVKA_DIS	0x083B		/* davkovani btn disabled*/
#define DAVKA_ON	0x009B		/* davkovani btn ON - zelena*/
#define DAVKA_OFF	0x002c		/* davkovani btn OFF - cervena*/



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
*	procedure pro nastaveni vychozich parametru podle hodnot ve staticke pameti
*/
void nastaveniInit(){

	/* Initialize info structure */
	DOInfo.enable   = 1;
    DOInfo.pName    = (UDINT) "Nastaveni";
  
	/* Call  FUB  */
	DatObjInfo(&DOInfo);
  
	/* Get status */
	wStatus = DOInfo.status;
	if (wStatus == doERR_MODULNOTFOUND){                /* Data object not found -> create a new one */
	 	
	 	/* create new */
	 	/* Initialize create structure */
      	DOCreate.enable     = 1;
		DOCreate.grp        = 0;

        DOCreate.pName      = (UDINT) "Nastaveni";
        DOCreate.len        = sizeof (nastaveni);
        DOCreate.MemType    = doUSRROM;
        DOCreate.Option     = 0;
        DOCreate.pCpyData   = (UDINT) nastaveni;
  
       	/* Call FUB */
       	DatObjCreate(&DOCreate);
  
       	/* Get FUB output information */
       	wStatus = DOCreate.status;
        dwIdent = DOCreate.ident;
          
       	/* Verify status */
       	if (wStatus == 0){
       	
        }else if (wStatus != 0xFFFF){
        

      	}
	} else {
		/* read old one */
		
       	/* Get ident */
       	dwIdent = DOInfo.ident;
               
       	/* Initialize read structure */
       	DORead.enable       = 1;
       	DORead.ident        = dwIdent;
       	DORead.Offset       = 0;
       	DORead.pDestination = (UDINT) nastaveni;
       	DORead.len      = sizeof (nastaveni);
  
       	/* Call FUB */
       	DatObjRead(&DORead);
  
	   	/* Get status */
       	wStatus = DORead.status;
  
       	/* Verify status */
		if (wStatus == 0){      

		}
	}
}

/**
*	procedure pro ulozeni nastaveni parametru do staticke pameti
*/
void UlozNastaveni(){
	/* Initialize info structure */
	DOInfo.enable   = 1;
    DOInfo.pName    = (UDINT) "Nastaveni";
  
	/* Call  FUB  */
	DatObjInfo(&DOInfo);
  
	/* Get status */
	wStatus = DOInfo.status;
	if (wStatus == doERR_MODULNOTFOUND){                /* Data object not found -> create a new one */
	 	
	 	/* create new */
	 	/* Initialize create structure */
      	DOCreate.enable     = 1;
		DOCreate.grp        = 0;

        DOCreate.pName      = (UDINT) "Nastaveni";
        DOCreate.len        = sizeof (nastaveni);
        DOCreate.MemType    = doUSRROM;
        DOCreate.Option     = 0;
        DOCreate.pCpyData   = (UDINT) nastaveni;
  
       	/* Call FUB */
       	DatObjCreate(&DOCreate);
  
       	/* Get FUB output information */
       	wStatus = DOCreate.status;
        dwIdent = DOCreate.ident;
          
       	/* Verify status */
       	if (wStatus == 0){
       	
        }else if (wStatus != 0xFFFF){
        

      	}
	} else {
		/* store new one */
		
       	/* Get ident */
       	dwIdent = DOInfo.ident;
       	      	
       	/* Initialize write structure */
       	DOWrite.enable  = 1;
        DOWrite.ident   = dwIdent;
        DOWrite.Offset  = 0;
        DOWrite.pSource = (UDINT) nastaveni;
        DOWrite.len     = sizeof (nastaveni);
  
       	/* Call FUB */
       	DatObjWrite(&DOWrite);
  
   		/* Get status */
       	wStatus = DOWrite.status;
  
       /* Verify status */
		if (wStatus == 0){      

		}
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
	/* pouzivam permanent RAM */
	/*	nastaveniInit();*/  /* fill the start and end angle values for all functions  from the FLASH*/
	
	redraw1 = 0;
	redraw2 = 0;
	redraw3 = 0;

	/*pageChanged = 0;*/
	start_Btn_col = ZAP_OFF ;
	stop_Btn_col = VYP_OFF;
	infoTextPointer = 0;
	
}


_CYCLIC void RunBtnControl(void) {
	
	SetAdjustmentButtons();	
	
	if (nastaveniON	== 360) nastaveniON = 0;
	else if (nastaveniON == -1) nastaveniON = 359;
	
	if (nastaveniOFF	== 360) nastaveniOFF = 0;
	else if (nastaveniOFF == -1) nastaveniOFF = 359;
	
	if (nastaveniOFF_Time == -1) nastaveniOFF_Time =1000;
		 
	switch(nastBtnPressed){
	 	case 1:	/* standard on/off*/
			nastaveniON = nastaveni[nastaveniLabelIndex].ON_angle;
			nastaveniOFF = nastaveni[nastaveniLabelIndex].OFF_angle;
			nastBtnPressed = 0;
			redraw1 = 4;
		break;
		case 2:		/* standard s ON uhlem pouze*/
			nastaveniON = nastaveni[nastaveniLabelIndex].ON_angle;
			nastaveniOFF = nastaveniON;
			nastBtnPressed = 0;
			redraw2 = 4;
		break;
		case 3:		/* on uhel / off-time*/
			nastaveniON = nastaveni[nastaveniLabelIndex].ON_angle;
			nastaveniOFF_Time = nastaveni[nastaveniLabelIndex].OFF_angle;
			nastBtnPressed = 0;
			redraw2 = 4;	/* 4x ceka nez prekresli obrazovku*/
		break;
		case 4:
			nastaveniON = nastBrzda.ON_angle;
			nastaveniOFF = nastBrzda.OFF_angle;	
			nastaveniValue = nastBrzda.value;	
			nastBtnPressed = 0;
			redraw3 = 4;
		break;
	}
	
	
	switch (ulozBtnPressed){
		case 1:
			nastaveni[nastaveniLabelIndex].ON_angle = nastaveniON;
			nastaveni[nastaveniLabelIndex].OFF_angle = nastaveniOFF;
			ulozBtnPressed = 0;
		 /*	UlozNastaveni();   neni nutne pri pouzite permanentni RAM, tohle uklada na FLASH*/

		break;
		case 2:
			nastaveni[nastaveniLabelIndex].ON_angle = nastaveniON;
			ulozBtnPressed = 0;
		 /*	UlozNastaveni();   neni nutne pri pouzite permanentni RAM, tohle uklada na FLASH*/

		break;
		case 3:
			nastaveni[nastaveniLabelIndex].ON_angle = nastaveniON;
			nastaveni[nastaveniLabelIndex].OFF_angle = nastaveniOFF_Time;
 			ulozBtnPressed = 0;
		 /*	UlozNastaveni();   neni nutne pri pouzite permanentni RAM, tohle uklada na FLASH*/
 		break;
 		case 4:
 			nastBrzda.ON_angle = nastaveniON;
			nastBrzda.OFF_angle = nastaveniOFF;
			nastBrzda.value = nastaveniValue;
			ulozBtnPressed = 0;
		 /*	UlozNastaveni();   neni nutne pri pouzite permanentni RAM, tohle uklada na FLASH*/	 			
 		break;
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
			if (davkovaniBtnPressed && !davkovaniActive){
				davkovaniActive = 1;	/* vypinani davkovani je v ovladani inkrementu*/
				davkovaniBtnPressed = 0;
			}
			
			if (!davkovaniActive){
				davkovani_Btn_col=DAVKA_ON; 
				infoTextPointer = 1;
			}else{
				davkovani_Btn_col=DAVKA_OFF; 
				infoTextPointer = 2;
			}
			start_Btn_col = ZAP_OFF;
			stop_Btn_col = VYP_ON;
			break;
		case SM_STOP_PRESSED:		
			davkovani_Btn_col=DAVKA_DIS;
			davkovaniBtnPressed = 0;
			start_Btn_col = ZAP_OFF;
			stop_Btn_col = VYP_OFF;
			infoTextPointer = 3 ;
			break;
		case SM_SOFT_ERR_NO_START:
		case SM_SOFT_ERROR:
			davkovani_Btn_col=DAVKA_DIS;
			davkovaniBtnPressed = 0;
			start_Btn_col = ZAP_OFF;
			stop_Btn_col = VYP_OFF;
			infoTextPointer = 4 ;
			break;
		case SM_CRITICAL_ERROR:
		default:
			davkovani_Btn_col=DAVKA_DIS;
			davkovaniBtnPressed = 0;
			start_Btn_col = ZAP_OFF;
			stop_Btn_col = VYP_OFF;
			infoTextPointer = 5 ;
			break;
				
	}

		
}


