/************************************************************************************************
 	
	Task Name	:	
		
	Author		:	Vaclav Dvorak
	
	Description :   Casovani davkovani vody
		
	History		:	Version			Date			Name			Comment
													VD				created
************************************************************************************************/


#include <bur/plc.h> 
#include <bur/plctypes.h>
#include <system_variables.h>





/*
	davkaVodySM   0 blokovano
				 1 ready
				 2 davkovani probiha*/

_CYCLIC void fastTimer(void){

	/* davkovani vody*/
	
	switch(davkaVodySM){
		case 0:
		case 1:
		default:
		break;
		case 2:
		if(--timerVoda < 1){
			o_releKA4_davkovacVody = 0;		
			davkaVodySM = 0;
		}
		break;
	}
	
	if (timerDavka >0 ){
		--timerDavka;
		o_releKA3_davkovacStart = 1;
	}else{
		o_releKA3_davkovacStart = 0;
	}




}