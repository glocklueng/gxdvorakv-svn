/************************************************************************************************
 	
	Task Name	:	
		
	Author		:	Vaclav Dvorak	
	Description :   
	
		
	History		:	Version			Date			Name			Comment
									2/2012			VD				created
************************************************************************************************/

#include <bur/plc.h> 
#include <bur/plctypes.h>
/*#include <visapi.h>*/
#include <dataobj.h>
#include <system_variables.h>
#include <gui_variables.h>
#include "stdio.h"

_LOCAL TECHNOLOGIE technologies[10];


/**
*	GUI - stisknuto tlacitko ZVOLIT 
*/
_LOCAL BOOL  technologySelect;

/**
*	ulozi akualni zvolenou a zmenenou technologii 
*/
_LOCAL BOOL  storeActualTechnology;

/**
*	toto nenastavuje GUI, ale slouzi pouze pro nahrani technologie po spusteni
*/
_LOCAL BOOL loadActualTechnology;

/**
*	GUI - cislo tlacitka zvolene technologie
*/
_LOCAL USINT technologyGUISelected;
/**
*	GUI - storno zmeny technologie
*/
_LOCAL BOOL technologyGUIStorno;




_LOCAL DatObjCreate_typ    	DOCreate;
_LOCAL DatObjWrite_typ 		DOWrite;
_LOCAL DatObjRead_typ  		DORead;
_LOCAL DatObjCopy_typ  		DOCopy;
_LOCAL DatObjInfo_typ  		DOInfo;
_LOCAL DatObjDelete_typ    	DODelete;
_LOCAL UINT        			wStatus;
_LOCAL UDINT       			dwIdent;



/*--------------------------------------------------------------------------*/
/**
*	procedure pro ulozeni nastaveni parametru na flash
*/
BOOL StoreTechnology(void){
	/* Initialize info structure */
	DOInfo.enable   = 1;
    DOInfo.pName    = (UDINT) "TechnFLASH";
  
	/* Call  FUB  */
	DatObjInfo(&DOInfo);
  
	/* Get status */
	wStatus = DOInfo.status;
	if (wStatus == doERR_MODULNOTFOUND){                /* Data object not found -> create a new one */
	 	
	 	/* create new */
	 	/* Initialize create structure */
      	DOCreate.enable     = 1;
		DOCreate.grp        = 0;

        DOCreate.pName      = (UDINT) "TechnFLASH";
        DOCreate.len        = sizeof (technologies);
        DOCreate.MemType    = doUSRROM;
        DOCreate.Option     = 0;
        DOCreate.pCpyData   = technologies;
  
    	do {
	       	/* Call FUB */
    	   	DatObjCreate(&DOCreate);
  
       		/* Get FUB output information */
	       	wStatus = DOCreate.status;
    	    dwIdent = DOCreate.ident;
          
		   	/* Verify status */
       		if (wStatus == 0){
       			return 1;       	
	        }
      	}while (wStatus == 0xffff );
      	return 0;
	} else {
		/* store new one */
		
       	/* Get ident */
       	dwIdent = DOInfo.ident;
       	      	
       	/* Initialize write structure */
       	DOWrite.enable  = 1;
        DOWrite.ident   = dwIdent;
        DOWrite.Offset  = 0;
        DOWrite.pSource = technologies;
        DOWrite.len     = sizeof (technologies);
  	
  		do {
	       	/* Call FUB */
    	   	DatObjWrite(&DOWrite);
  
   			/* Get status */
	   		wStatus = DOWrite.status;
  
    	   /* Verify status */
			if (wStatus == 0){      
				return 1;
			}
		}while (wStatus == 0xffff );
		return 0;
	}    
}
 
/*--------------------------------------------------------------------------*/
/**
*	procedura pro nastaveni vychozich parametru podle hodnot na flash
*/
BOOL LoadTechnology(void){

	/* Initialize info structure */
	DOInfo.enable   = 1;
    DOInfo.pName    = (UDINT) "TechnFLASH";
  
	/* Call  FUB  */
	DatObjInfo(&DOInfo);
  
	/* Get status */
	wStatus = DOInfo.status;
	if (wStatus == doERR_MODULNOTFOUND){                /* Data object not found -> create a new one */
	 	
	 	/* create new */
	 	/* Initialize create structure */
      	DOCreate.enable     = 1;
		DOCreate.grp        = 0;

        DOCreate.pName      = (UDINT) "TechnFLASH";
        DOCreate.len        = sizeof (technologies);
        DOCreate.MemType    = doUSRROM;
        DOCreate.Option     = 0;
        DOCreate.pCpyData   = &technologies[0];
  
       	do {
	       	/* Call FUB */
    	   	DatObjCreate(&DOCreate);
  
       		/* Get FUB output information */
	       	wStatus = DOCreate.status;
    	    dwIdent = DOCreate.ident;
          
       		/* Verify status */
	       	if (wStatus == 0){
       			return 1;
	        }
    	}while (wStatus == 0xffff);
    	return 0;
	} else {
		/* read old one */
		
       	/* Get ident */
       	dwIdent = DOInfo.ident;
               
       	/* Initialize read structure */
       	DORead.enable       = 1;
       	DORead.ident        = dwIdent;
       	DORead.Offset       = 0;
       	DORead.pDestination = (UDINT) &technologies;
       	DORead.len      = sizeof (technologies);
  
       	do {
	       	/* Call FUB */
    	   	DatObjRead(&DORead);
  
	   		/* Get status */	   	
		   	wStatus = DORead.status;
  
    	   	/* Verify status */
			if (wStatus == 0){      
				return 1;
			}	
		}while (wStatus ==0xffff);

	}
	return 0;
}

/*--------------------------------------------------------------------------*/
/**
*
*/
_INIT void initTechnolgy(void){
	storeActualTechnology = 0;
	technologySelect = 0;

	if (technologieNumber > 8){
		technologieNumber = 1;
	}
	/*loadActualTechnology = 1;	*/
	technologyGUISelected = technologieNumber;
}

/*--------------------------------------------------------------------------*/
_CYCLIC void setTechnology (void){
	
	if (technologyGUIStorno){
		technologyGUISelected = technologieNumber;
		technologyGUIStorno = 0;	
	}
	if (storeActualTechnology){
		technologies[technologieNumber-1].davkovani_zeli.ON1_angle 	= nastaveni.davkovani_zeli.ON1_angle;
		technologies[technologieNumber-1].davkovani_zeli.ON2_angle 	= nastaveni.davkovani_zeli.ON2_angle;
		technologies[technologieNumber-1].davkovani_zeli.OFF_angle 	= nastaveni.davkovani_zeli.OFF_angle;
		technologies[technologieNumber-1].davkovani_vody.ON_angle 	= nastaveni.davkovani_vody.ON_angle;
		technologies[technologieNumber-1].davkovani_vody.OFF_time	= nastaveni.davkovani_vody.OFF_time;				
		technologies[technologieNumber-1].posuv_folie.ON_angle 		= nastaveni.posuv_folie.ON_angle;
		technologies[technologieNumber-1].posuv_folie.delka			= nastaveni.posuv_folie.delka;
		technologies[technologieNumber-1].posuv_folie.FOT_start		= nastaveni.posuv_folie.FOT_start;
		technologies[technologieNumber-1].posuv_folie.rychlost		= nastaveni.posuv_folie.rychlost;
		technologies[technologieNumber-1].strihani.ON_angle			= nastaveni.strihani.ON_angle;
		technologies[technologieNumber-1].strihani.OFF_angle		= nastaveni.strihani.OFF_angle;
		technologies[technologieNumber-1].skladani.ON_angle			= nastaveni.skladani.ON_angle;
		technologies[technologieNumber-1].skladani.OFF_angle 		= nastaveni.skladani.OFF_angle;	
		technologies[technologieNumber-1].podrazeni.ON_angle 		= nastaveni.podrazeni.ON_angle;
		technologies[technologieNumber-1].vystrkavani.ON_angle 		= nastaveni.vystrkavani.ON_angle;
		technologies[technologieNumber-1].datovani.ON_angle 		= nastaveni.datovani.ON_angle;
		technologies[technologieNumber-1].datovani.OFF_angle	 	= nastaveni.datovani.OFF_angle;
		technologies[technologieNumber-1].topeni.ON_angle 	 		= nastaveni.topeni.ON_angle;
		technologies[technologieNumber-1].topeni.OFF_angle 			= nastaveni.topeni.OFF_angle;	
		technologies[technologieNumber-1].brzda.ON_angle			= nastaveni.brzda.ON_angle;
		technologies[technologieNumber-1].brzda.OFF_angle			= nastaveni.brzda.OFF_angle;
		technologies[technologieNumber-1].brzda.value				= nastaveni.brzda.value;
		technologies[technologieNumber-1].davkovacZ_St				= davkovacZ_St;
		technologies[technologieNumber-1].davkovacV_St				= davkovacV_St;
		technologies[technologieNumber-1].podrazeni_St				= podrazeni_St;
		technologies[technologieNumber-1].posuv_St					= posuv_St;
		technologies[technologieNumber-1].datovani_St				= datovani_St;
		technologies[technologieNumber-1].strihani_St				= strihani_St;
		technologies[technologieNumber-1].skladani_St				= skladani_St;
		technologies[technologieNumber-1].vystrkavani_St			= vystrkavani_St;
		technologies[technologieNumber-1].dopravnik_St				= dopravnik_St;
		technologies[technologieNumber-1].fotonka_St				= fotonka_St;
		technologies[technologieNumber-1].CO2_St					= CO2_St;
		technologies[technologieNumber-1].topeni_St					= topeni_St;
		technologies[technologieNumber-1].brzda_St					= brzda_St;
		technologies[technologieNumber-1].topeniImpuls_St			= topeniImpuls_St;
		technologies[technologieNumber-1].davka1_St					= davka1_St;
		technologies[technologieNumber-1].davka2_St					= davka2_St;
		technologies[technologieNumber-1].otacky					= otacky_nast;

	/*	if (StoreTechnology()){
		
		}else {
		/** error **
		}*/
		storeActualTechnology = 0;
	}
	
	
	if (technologySelect){
		if (technologyGUISelected >0 && technologyGUISelected <11){
			
			if (1/*LoadTechnology()*/){	/* load from the FLASH*/			
				technologieNumber	= technologyGUISelected;			
				nastaveni.davkovani_zeli.ON1_angle	=	technologies[technologieNumber-1].davkovani_zeli.ON1_angle;
				nastaveni.davkovani_zeli.ON2_angle	=	technologies[technologieNumber-1].davkovani_zeli.ON2_angle;
				nastaveni.davkovani_zeli.OFF_angle	=	technologies[technologieNumber-1].davkovani_zeli.OFF_angle;
				nastaveni.davkovani_vody.ON_angle	=	technologies[technologieNumber-1].davkovani_vody.ON_angle;
				nastaveni.davkovani_vody.OFF_time	=	technologies[technologieNumber-1].davkovani_vody.OFF_time;
				nastaveni.posuv_folie.ON_angle		=	technologies[technologieNumber-1].posuv_folie.ON_angle;
				nastaveni.posuv_folie.delka			=	technologies[technologieNumber-1].posuv_folie.delka;
				nastaveni.posuv_folie.FOT_start		=	technologies[technologieNumber-1].posuv_folie.FOT_start;
				nastaveni.posuv_folie.rychlost		=	technologies[technologieNumber-1].posuv_folie.rychlost;
				nastaveni.strihani.ON_angle			=	technologies[technologieNumber-1].strihani.ON_angle;
				nastaveni.strihani.OFF_angle		=	technologies[technologieNumber-1].strihani.OFF_angle;
				nastaveni.skladani.ON_angle			=	technologies[technologieNumber-1].skladani.ON_angle;
				nastaveni.skladani.OFF_angle		=	technologies[technologieNumber-1].skladani.OFF_angle;
				nastaveni.podrazeni.ON_angle		=	technologies[technologieNumber-1].podrazeni.ON_angle;
				nastaveni.vystrkavani.ON_angle		=	technologies[technologieNumber-1].vystrkavani.ON_angle;
				nastaveni.datovani.ON_angle			=	technologies[technologieNumber-1].datovani.ON_angle;
				nastaveni.datovani.OFF_angle		=	technologies[technologieNumber-1].datovani.OFF_angle;
				nastaveni.topeni.ON_angle			=	technologies[technologieNumber-1].topeni.ON_angle;
				nastaveni.topeni.OFF_angle			=	technologies[technologieNumber-1].topeni.OFF_angle;
				nastaveni.brzda.ON_angle			=	technologies[technologieNumber-1].brzda.ON_angle;
				nastaveni.brzda.OFF_angle			=	technologies[technologieNumber-1].brzda.OFF_angle;
				nastaveni.brzda.value				=	technologies[technologieNumber-1].brzda.value;
	 			davkovacZ_St 						=	technologies[technologieNumber-1].davkovacZ_St;
	 			davkovacV_St						=	technologies[technologieNumber-1].davkovacV_St;
				podrazeni_St						=	technologies[technologieNumber-1].podrazeni_St;
				posuv_St							=	technologies[technologieNumber-1].posuv_St;
				datovani_St							=	technologies[technologieNumber-1].datovani_St;
				strihani_St							=	technologies[technologieNumber-1].strihani_St;
				skladani_St							=	technologies[technologieNumber-1].skladani_St;
				vystrkavani_St						=	technologies[technologieNumber-1].vystrkavani_St;
				dopravnik_St						=	technologies[technologieNumber-1].dopravnik_St;
				fotonka_St							=	technologies[technologieNumber-1].fotonka_St; 
				CO2_St								=	technologies[technologieNumber-1].CO2_St;
				topeni_St							=	technologies[technologieNumber-1].topeni_St;
				brzda_St							=	technologies[technologieNumber-1].brzda_St;
				topeniImpuls_St						=	technologies[technologieNumber-1].topeniImpuls_St;
				davka1_St							=	technologies[technologieNumber-1].davka1_St;
				davka2_St							=	technologies[technologieNumber-1].davka2_St;
				otacky_nast								=	technologies[technologieNumber-1].otacky;
				
			}else {
			/** error **/					
			}
		}
		technologySelect = 0;
	}
	
	if (loadActualTechnology){
		if (1/*LoadTechnology()*/){	/* load from the FLASH*/	
			nastaveni.davkovani_zeli.ON1_angle	=	technologies[technologieNumber-1].davkovani_zeli.ON1_angle;
			nastaveni.davkovani_zeli.ON2_angle	=	technologies[technologieNumber-1].davkovani_zeli.ON2_angle;
			nastaveni.davkovani_zeli.OFF_angle	=	technologies[technologieNumber-1].davkovani_zeli.OFF_angle;
			nastaveni.davkovani_vody.ON_angle	=	technologies[technologieNumber-1].davkovani_vody.ON_angle;
			nastaveni.davkovani_vody.OFF_time	=	technologies[technologieNumber-1].davkovani_vody.OFF_time;
			nastaveni.posuv_folie.ON_angle		=	technologies[technologieNumber-1].posuv_folie.ON_angle;
			nastaveni.posuv_folie.delka			=	technologies[technologieNumber-1].posuv_folie.delka;
			nastaveni.posuv_folie.FOT_start		=	technologies[technologieNumber-1].posuv_folie.FOT_start;
			nastaveni.posuv_folie.rychlost		=	technologies[technologieNumber-1].posuv_folie.rychlost;
			nastaveni.strihani.ON_angle			=	technologies[technologieNumber-1].strihani.ON_angle;
			nastaveni.strihani.OFF_angle		=	technologies[technologieNumber-1].strihani.OFF_angle;
			nastaveni.skladani.ON_angle			=	technologies[technologieNumber-1].skladani.ON_angle;
			nastaveni.skladani.OFF_angle		=	technologies[technologieNumber-1].skladani.OFF_angle;
			nastaveni.podrazeni.ON_angle		=	technologies[technologieNumber-1].podrazeni.ON_angle;
			nastaveni.vystrkavani.ON_angle		=	technologies[technologieNumber-1].vystrkavani.ON_angle;
			nastaveni.datovani.ON_angle			=	technologies[technologieNumber-1].datovani.ON_angle;
			nastaveni.datovani.OFF_angle		=	technologies[technologieNumber-1].datovani.OFF_angle;
			nastaveni.topeni.ON_angle			=	technologies[technologieNumber-1].topeni.ON_angle;
			nastaveni.topeni.OFF_angle			=	technologies[technologieNumber-1].topeni.OFF_angle;
			nastaveni.brzda.ON_angle			=	technologies[technologieNumber-1].brzda.ON_angle;
			nastaveni.brzda.OFF_angle			=	technologies[technologieNumber-1].brzda.OFF_angle;
			nastaveni.brzda.value				=	technologies[technologieNumber-1].brzda.value;				
			davkovacZ_St 						=	technologies[technologieNumber-1].davkovacZ_St;
 			davkovacV_St						=	technologies[technologieNumber-1].davkovacV_St;
			podrazeni_St						=	technologies[technologieNumber-1].podrazeni_St;
			posuv_St							=	technologies[technologieNumber-1].posuv_St;
			datovani_St							=	technologies[technologieNumber-1].datovani_St;
			strihani_St							=	technologies[technologieNumber-1].strihani_St;
			skladani_St							=	technologies[technologieNumber-1].skladani_St;
			vystrkavani_St						=	technologies[technologieNumber-1].vystrkavani_St;
			dopravnik_St						=	technologies[technologieNumber-1].dopravnik_St;
			fotonka_St							=	technologies[technologieNumber-1].fotonka_St; 
			CO2_St								=	technologies[technologieNumber-1].CO2_St;
			topeni_St							=	technologies[technologieNumber-1].topeni_St;
			brzda_St							=	technologies[technologieNumber-1].brzda_St;
			topeniImpuls_St						=	technologies[technologieNumber-1].topeniImpuls_St;
			davka1_St							=	technologies[technologieNumber-1].davka1_St;
			davka2_St							=	technologies[technologieNumber-1].davka2_St;
			otacky_nast								=	technologies[technologieNumber-1].otacky;
		}else {
			/** error **/			
		}
		loadActualTechnology = 0;
	}
}