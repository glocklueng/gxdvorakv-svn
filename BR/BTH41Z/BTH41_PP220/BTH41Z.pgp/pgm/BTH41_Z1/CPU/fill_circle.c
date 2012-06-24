/************************************************************************************************
 	
	Task Name	:	
		
	Author		:	Vaclav Dvorak
	
	Description :   podpora grafiky pro kresleni vyplnen kruhove vysece
	
	History		:	Version			Date			Name			Comment
													VD				created
************************************************************************************************/



#include <bur/plc.h> 
#include <bur/plctypes.h>
#include <visapi.h>
#include <operator.h>
#include <gui_variables.h>

double sin(double);
double cos(double);

int i,j;

unsigned long VC_HANDLE;

/* CIRCLE constants */
int center_x= 141;
int center_y= 141;
int radius = 40;
#define PI 3.14159265359



/**
 *   function to fill circle by angle in variables nastaveniON, nastaveniOFF
 */
void paintFilledCircleSector(void){

	INT x,y,r;

	VC_HANDLE = VA_Setup(1,"GUI_01");
	if (VC_HANDLE){
		VA_Saccess(1,VC_HANDLE);
		VA_Redraw(1,VC_HANDLE);
		if (nastaveniOFF < nastaveniON){
			for (r = nastaveniON;r < 360;r++){		
				y = radius * cos (r*PI/180.0);
				x = radius * sin (r*PI/180.0);  
				VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,148);

			}
			for (r = 0;r < nastaveniOFF ;r++){		
				y = radius * cos (r*PI/180.0);
				x = radius * sin (r*PI/180.0);  
				VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,148);
			}
		}else {	 
			for (r = nastaveniON;r < nastaveniOFF && r < 360 ;r++){		
				y = radius * cos (r*PI/180.0);
				x = radius * sin (r*PI/180.0);  
				VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,148);
			}
		}
			
		y = (radius+10) * cos (nastaveniON*PI/180.0);
		x = (radius+10) * sin (nastaveniON*PI/180.0);  
		VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,116);
		y = (radius+10) * cos (nastaveniOFF*PI/180.0);
		x = (radius+10) * sin (nastaveniOFF*PI/180.0);  
		VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,44);
			 
		VA_Srelease(1,VC_HANDLE);
	}
}

/*
 *  funkce na vykresleni zacatku - nastaveniON
 */
void paintStartAngle(void){

	INT x,y;

	VC_HANDLE = VA_Setup(1,"GUI_01");
	if (VC_HANDLE){
		VA_Saccess(1,VC_HANDLE);
		VA_Redraw(1,VC_HANDLE);			
		y = (radius+10) * cos (nastaveniON*PI/180.0);
		x = (radius+10) * sin (nastaveniON*PI/180.0);  
		VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,116);
			 
		VA_Srelease(1,VC_HANDLE);
	}
}



_INIT void graphicsSupport(void){
	redraw1 = 0;
	redraw2 = 0;
	redraw3 = 0;
	/*pageChanged = 0;*/

}



_CYCLIC void graphics_refresh(void) {
		
	if (redraw1 > 0 ){
		center_x= 141;
	 	center_y= 141;
		paintFilledCircleSector();	 
		redraw1--;
	}
	
	if (redraw2 >0 ){
		center_x= 141;
		center_y= 141;
		paintStartAngle();
		redraw2--;
	}
	
	if (redraw3>0){
		center_x= 67;
		center_y= 142;
		paintFilledCircleSector();
		redraw3--;
	}

}