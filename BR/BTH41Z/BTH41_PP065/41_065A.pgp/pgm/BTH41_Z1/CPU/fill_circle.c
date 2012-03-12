/************************************************************************************************
 	
	Task Name	:	
		
	Author		:	Vaclav Dvorak
	
	Description :   podpora grafiky pro kresleni vyplnene kruhove vysece
	
	History		:	Version			Date			Name			Comment
													VD				created
************************************************************************************************/



#include <bur/plc.h> 
#include <bur/plctypes.h>
#include <visapi.h>
#include <operator.h>
#include <gui_variables.h>
#include <system_variables.h>

double sin(double);
double cos(double);

int i,j;

unsigned long VC_HANDLE;

/* CIRCLE constants */
int center_x= 141;
int center_y= 141;
int radius = 39;
#define PI 3.14159265359

#define DEF_COLOR	116



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
				y = radius * cos (r*PI/180.0)+1;
				x = radius * sin (r*PI/180.0)-1;  
				VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,148);

			}
			for (r = 0;r < nastaveniOFF ;r++){		
				y = radius * cos (r*PI/180.0)+1;
				x = radius * sin (r*PI/180.0)-1;  
				VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,148);
			}
		}else {	 
			for (r = nastaveniON;r < nastaveniOFF && r < 360 ;r++){		
				y = radius * cos (r*PI/180.0)+1;
				x = radius * sin (r*PI/180.0)-1;  
				VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,148);
			}
		}
			
		y = (radius*1.3) * cos (nastaveniON*PI/180.0);
		x = (radius*1.3) * sin (nastaveniON*PI/180.0);  
		VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,116);
		y = (radius*1.3) * cos (nastaveniOFF*PI/180.0);
		x = (radius*1.3) * sin (nastaveniOFF*PI/180.0);  
		VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,44);

	 	VA_Line(1,VC_HANDLE,center_x-radius,center_y,center_x+radius,center_y,165);
 		VA_Line(1,VC_HANDLE,center_x,center_y-radius,center_x,center_y+radius,165);
		VA_Srelease(1,VC_HANDLE);
	}
}
/**
 *   function to fill circle by angle in variables nastaveniON, nastaveniOFF
 */
void paintFilledCircleSectorOnOff(int On, int Off){

	INT x,y,r;

	VC_HANDLE = VA_Setup(1,"GUI_01");
	if (VC_HANDLE){
		VA_Saccess(1,VC_HANDLE);
		VA_Redraw(1,VC_HANDLE);
		if (Off < On){
			for (r = On;r < 360;r++){		
				y = radius * cos (r*PI/180.0)+1;
				x = radius * sin (r*PI/180.0)-1;  
				VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,148);

			}
			for (r = 0;r < Off ;r++){		
				y = radius * cos (r*PI/180.0)+1;
				x = radius * sin (r*PI/180.0)-1;  
				VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,148);
			}
		}else {	 
			for (r = On;r < Off && r < 360 ;r++){		
				y = radius * cos (r*PI/180.0)+1;
				x = radius * sin (r*PI/180.0)-1;  
				VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,148);
			}
		}
			
		y = (radius*1.3) * cos (On*PI/180.0)+1;
		x = (radius*1.3) * sin (On*PI/180.0)-1;  
		VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,2);
		y = (radius*1.3) * cos (Off*PI/180.0)+1;
		x = (radius*1.3) * sin (Off*PI/180.0)-1;  
		VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,50);

	 	VA_Line(1,VC_HANDLE,center_x-radius,center_y,center_x+radius,center_y,165);
 		VA_Line(1,VC_HANDLE,center_x,center_y-radius,center_x,center_y+radius,165);
		VA_Srelease(1,VC_HANDLE);
	}
}

/*
 *  funkce na vykresleni zacatku - nastaveniON
 */
void paintStartAngle(INT angle,INT color){

	INT x,y;

	VC_HANDLE = VA_Setup(1,"GUI_01");
	if (VC_HANDLE){
		VA_Saccess(1,VC_HANDLE);
		VA_Redraw(1,VC_HANDLE);			
		y = (radius*1.3) * cos (angle*PI/180.0);
		x = (radius*1.3) * sin (angle*PI/180.0);  
		VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,color);
			 
		VA_Srelease(1,VC_HANDLE);
	}
}

/*
 *  funkce na vykresleni cary pod uhlem - no redraw !!*/
void paintAngleLine(INT angle,INT color){

	INT x,y;

	VC_HANDLE = VA_Setup(1,"GUI_01");
	if (VC_HANDLE){
		VA_Saccess(1,VC_HANDLE);
		y = (radius*1.3) * cos (angle*PI/180.0);
		x = (radius*1.3) * sin (angle*PI/180.0);  
		VA_Line(1,VC_HANDLE,center_x,center_y,center_x+x,center_y-y,color);			 
		VA_Srelease(1,VC_HANDLE);
	}
}



_INIT void graphicsSupport(void){
	redraw1 = 0;
/*	redraw2 = 0;
	redraw3 = 0; 4.12.2011*/
	/*pageChanged = 0;*/

}



_CYCLIC void graphics_refresh(void) {
	
	if (redraw1){
		redraw1--;
		switch (actualGUIPage){
			case 5:	/* Timing_Page */
				center_x= 141;
		 		center_y= 141;
		 		radius = 39;
				paintFilledCircleSector();				 
			break;
			case 11: /* Timing_Page1 */
			case 10: /* Timing_Page2 */
				center_x= 142;
				center_y= 142;
				radius = 39;
				paintStartAngle(nastaveniON,DEF_COLOR);
				
			break;
			case 9: /* Timing_Page3_Brzda */
				center_x= 67;
				center_y= 142;
				radius = 39;
				paintFilledCircleSector();		
			break;
			case 8: /* Timing_Page4_2davky */
				center_x= 160;
				center_y= 186;
				radius = 30;
				paintFilledCircleSectorOnOff(nastaveniON_2, nastaveniOFF);
				paintAngleLine(nastaveniON,133);				
			/*	paintAngleLine(nastaveniON,51);
				paintAngleLine(nastaveniON_2,1);*/
			break;
			case 14: /* Timing_Page5_posuv */
				center_x= 156;
				center_y= 206;
				radius = 25;
				paintStartAngle(nastaveniON,DEF_COLOR);
			break;
		} 	
	}
	/*if (redraw1 > 0 ){
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
	}*/

}