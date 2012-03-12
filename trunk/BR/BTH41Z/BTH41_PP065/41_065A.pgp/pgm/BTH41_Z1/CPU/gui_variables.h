#include <bur/plc.h> 
#include <bur/plctypes.h>

_GLOBAL INT nastaveniON;  /* variable to hold the ON angle an the timing adjust page */ 
_GLOBAL INT nastaveniON_2;  /* variable to hold the ON angle an the timing adjust page */ 

_GLOBAL INT nastaveniOFF;/* variable to hold the OFF angle an the timing adjust page */ 
_GLOBAL INT nastaveniOFF_Time;/* variable to hold the OFF time an the timing adjust page */ 

_GLOBAL INT nastaveniValue; /* hodnota brzdeni, rychlost posuvu */

_GLOBAL INT redraw1; /* variable to indicate the request to redraw the filled circle*/ 
/*_GLOBAL INT redraw2; /* pozadavek na  prekresleni vizualizace  - uhel sepnuti z Timing_Page_1+2*/
/*_GLOBAL INT redraw3; /* pozadavek na  prekresleni vizualizace  - uhel sepnuti z Timing_Page_3-brzda*/

_GLOBAL UINT actualGUIPage;  /* real page active on display */
_GLOBAL UINT setGUIPage;	 /*  page which will be set on display */

_GLOBAL UINT infoTextPointer;	/* pointer textu do textgrop info text na uvodni obrazovce */

_GLOBAL BOOL davkovaniBtnPressed;	/* stisknuto tlacitko davkovani*/