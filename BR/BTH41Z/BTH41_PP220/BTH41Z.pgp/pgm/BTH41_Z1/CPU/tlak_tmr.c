/************************************************************************************************
 	
	Task Name	:	
		
	Author		:	Vaclav Dvorak
	
	Description :   fitr tlaku vzduchu
		
	History		:	Version			Date			Name			Comment
													VD				created
************************************************************************************************/


#include <bur/plc.h> 
#include <bur/plctypes.h>
#include <system_variables.h>


int counter ;



_INIT	void initTimerVzduchu(void){
	counter = 0;

}




_CYCLIC void vzduchTimer(void){
	
	if (i_tlakuVzduchu){
		i_tlakVzduchu_Filtered = 1;
		counter = 25;			/* 20ms * 25 = 500ms*/
	} else{
		if (counter <= 0 ){
			i_tlakVzduchu_Filtered = 0;
		}else counter--;
	}
}