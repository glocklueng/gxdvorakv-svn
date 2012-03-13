#include <bur/plc.h> 
#include <bur/plctypes.h>


/* inputs definition */

_GLOBAL BOOL 	i_fotonka;  
_GLOBAL BOOL	i_podrazeniSacku;
_GLOBAL BOOL	i_datovaniKoncak;
_GLOBAL BOOL	i_tlakuVzduchu;
_GLOBAL BOOL    i_tlakVzduchu_Filtered;
_GLOBAL BOOL	i_pritomnostCO2;
_GLOBAL BOOL	i_teplotaDosazena;
_GLOBAL BOOL	i_totalStop;
_GLOBAL BOOL	i_kryty;
_GLOBAL BOOL 	i_zavzdusneni;
_GLOBAL BOOL 	i_poruchaMenice;
_GLOBAL BOOL	i_davkovacVodyRele;
_GLOBAL BOOL 	i_odvijeniFolieStart;
_GLOBAL BOOL 	i_odvijeniFolieStop;
_GLOBAL BOOL 	i_konecFolie;
_GLOBAL BOOL 	i_odvijeniFolieStart;
_GLOBAL BOOL 	i_vysouvaniSacku;
_GLOBAL BOOL	i_11;
_GLOBAL BOOL	i_davkaReady;

/* outputs definition */

_GLOBAL BOOL 	o_zavzdusneni;
_GLOBAL BOOL 	o_ventilStrihani;
_GLOBAL BOOL 	o_ventilDatum;
_GLOBAL BOOL 	o_ventilPodrazeni;
_GLOBAL BOOL 	o_ventilSevreniPosuvRem;
_GLOBAL BOOL 	o_ventilTrojuhSkladani;
_GLOBAL BOOL 	o_ventilVystrkSacku;
_GLOBAL BOOL 	o_releKA1_topeni;
_GLOBAL BOOL 	o_releKA2_posuvFolie;
_GLOBAL BOOL 	o_stykacOdsDopravniku;
_GLOBAL BOOL 	o_releKA3_davkovacStart;
_GLOBAL BOOL 	o_releKA4_davkovacVody;
_GLOBAL BOOL 	o_ventilCO2;
_GLOBAL BOOL 	o_odvijeniFolie;
_GLOBAL BOOL    o_impulsniTopeni;
_GLOBAL BOOL	o_resetInkrementPosuvu;


_GLOBAL INT 		incrementAngle;  /*uhel  inkrementalniho senzoru - udaj inkrementu prepocteny na stupne */
_GLOBAL INT 		incrementLength; /* delka posuvu folie z inkrementu */

typedef struct {
	INT ON_angle;
}NAST_PAR_ON;

typedef struct {
	INT ON_angle;
	INT OFF_angle;	
}NAST_PAR_ON_OFF;

typedef struct {
	INT ON_angle;
	INT OFF_time;
}NAST_PAR_ON_OFF_TIME;

typedef struct{
	INT ON_angle;
	INT OFF_angle;
	INT value;
}NAST_PAR_BRZDA;

typedef struct{
	INT ON1_angle;
	INT ON2_angle;
	INT OFF_angle;
}NAST_PAR_DAVKOVANI;

typedef struct{
	INT ON_angle;
	INT delka;
	INT FOT_start;
	INT rychlost;
}NAST_PAR_POSUV;

typedef struct {
	NAST_PAR_DAVKOVANI 		davkovani_zeli;
	NAST_PAR_ON_OFF_TIME	davkovani_vody;
	NAST_PAR_POSUV			posuv_folie;
	NAST_PAR_ON_OFF			strihani;
	NAST_PAR_ON_OFF			skladani;
	NAST_PAR_ON				podrazeni;
	NAST_PAR_ON				vystrkavani;
	NAST_PAR_ON_OFF			datovani;
	NAST_PAR_ON_OFF			topeni;
	NAST_PAR_BRZDA			brzda;	
} TECHNOLOGIE;

_GLOBAL TECHNOLOGIE nastaveni; 	/* aktualni nastaveni*/

/**
*	 cislo aktualni technologie 
*/
_GLOBAL USINT 	technologieNumber;


/* index identifikace buttonu "Nastav" v GUI */
#define NO_BTN			0
#define DAVK_Z_IDX 		1	
#define DAVK_V_IDX 		2
#define POSUV_IDX		3
#define STRIH_IDX		4
#define SKLADANI_IDX	5
#define PODRAZENI_IDX	6
#define VYSTRKAVANI_IDX	7
#define DATOVANI_IDX	8
#define TOPENI_IDX      9    
#define BRZDA_IDX		10

/* stav jestli je funkce zapnuta nebo vypnuta */

_GLOBAL BOOL davkovacZ_St;
_GLOBAL BOOL davkovacV_St;
_GLOBAL BOOL podrazeni_St;
_GLOBAL BOOL posuv_St;
_GLOBAL BOOL datovani_St;
_GLOBAL BOOL strihani_St;
_GLOBAL BOOL skladani_St;
_GLOBAL BOOL vystrkavani_St;
_GLOBAL BOOL dopravnik_St;
_GLOBAL BOOL fotonka_St;
_GLOBAL BOOL CO2_St;
_GLOBAL BOOL topeni_St;
_GLOBAL BOOL brzda_St;
_GLOBAL BOOL topeniImpuls_St;
_GLOBAL BOOL davka1_St;
_GLOBAL BOOL davka2_St;



/* otacky stroje */
_GLOBAL UINT otacky_nast;
_GLOBAL REAL otacky_mer;

_GLOBAL UINT pocetDavek;

_GLOBAL BOOL resetIncrementNow;
_GLOBAL BOOL startActive;	/* stisknuto tlacitko START */
_GLOBAL BOOL stopActive;	/* stisknuto tlacitko STOP */
_GLOBAL BOOL davkovaniActive;	/* davkovani povoleno/zakazano - tlacitko nastavuje davkovaniBtnPressed*/


_GLOBAL UINT timerVzduch;	/* filtr tlaku vzchu*/
_GLOBAL UINT timerVoda;		/* casovac davkovcani vody*/
_GLOBAL UINT davkaVodySM;	/* spousti casovac na davkovani vody */
			/* davkaVodySM   	0 blokovano
							 	1 ready
							 	2 davkovani probiha*/
_GLOBAL UINT timerDavka;	/* casovac impuls davky */

_GLOBAL UINT posuvSM;	/* SM proPSM_READY posuv folie */
#define PSM_READY 		0 	/* 0 - stop - ready*/
#define PSM_RESTART		5	/* 5 - opakovany reset */
#define PSM_START		1	/* 1 - start    */
#define PSM_RUN			2	/* 2 - posun probiha    */
#define PSM_FOT			3	/* 3 - cekam na fotonku nebo delku    */
#define PSM_FINISHED	4	/* 4 - hotovo*/



/*	stavy stroje */
/*
   NEmuzu pouzit enum, protoze nelze ovladat a cist z GUI pokud neni _GLOBAL
   a global nemuze byt enum   :(   
typedef enum {		SM_ON = 0,
				 	SM_READY = 1, 
				 	SM_START_PRESSED = 2, 
				 	SM_PRE_START = 3,
				 	SM_RUN = 4, 
				 	SM_STOP_PRESSED = 5, 
				 	SM_SOFT_ERROR = 6, 
				 	SM_SOFT_ERR_NO_START = 7,
				 	SM_CRITICAL_ERROR = 8, 
				 	
				 	SM_IO_TEST = 10, 
				 	SM_RUN_TEST = 11 
				} STATE_MACHINE;			 	
STATE_MACHINE stateMachineNew ;*/


#define	SM_ON  0			/*	po zapnuti, nejsou splneny podminky spusteni*/
#define SM_READY_NO_PREPARE 1
#define	SM_READY  2 		/*	ready - stroj lze spustit */
#define	SM_START_PRESSED  3 /*	start stisknuto, rozbeh reminku 1s*/
#define	SM_PRE_START  4 	/*	tocim a cekam na prvni signal z inkrementu */
#define	SM_RUN  5 			/* 	v behu - normalni stav po nabehnuti a spusteni*/
#define	SM_STOP_PRESSED  6 	/*	stop stisknuto behem provozu - cekam na dojeti do vychozi polohy, ale
								normalne pokracuju v cinnosti*/
#define	SM_SOFT_ERROR  7 	/*	nehavarijni chyba behem provozu - cekam na dojeti do vychozi polohy, ale
								normalne pokracuju v cinnosti*/
#define	SM_SOFT_ERR_NO_START  8	/*	ne-havarijni chybovy stav - cekam na dojeti do vychozi polohy
									ale neprovadim zadne akce, pouze zastavim ve vychozi poloze
									- pokud vynikla chyba pred stavem 4*/
#define	SM_CRITICAL_ERROR  9 	/*	kriticka chyba - okamzite zastaveni stroje*/
				 	
#define	SM_IO_TEST  10 			/*	testovani - ignoruje se vse ostatni*/
#define	SM_RUN_TEST  11 		/* 	testovani behu stroje */

#define SM_WAIT_STOP	12		/* dekam na odvinuti folie pred zastavenim */

/**
*	stavova masina stroje - podle toho se ridi cinnost
*/
_GLOBAL SINT stateMachine;
_GLOBAL UINT testMode;		/* nastaven do 1 kdyz se testuje beh stroje, 2 - ukoncuje beh, jinak 0*/
	
	

/* analog output */
_GLOBAL INT ao_menic;
_GLOBAL INT ao_posuv;

_GLOBAL UINT tmp;


_GLOBAL USINT zpomalCekamDavku;