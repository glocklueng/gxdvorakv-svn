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
_GLOBAL BOOL	i_blokovaniDavky;





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





_GLOBAL INT 		incrementAngle;  /*uhel  inkrementalniho senzoru - udaj inkrementu prepocteny na stupne */

typedef struct {
	INT ON_angle;
	INT OFF_angle;
	/*	INT ; */
}NAST_PAR;

_GLOBAL NAST_PAR 	nastaveni[10];    /* promena pro ulozeni nastaveni uhlu*/


typedef struct{
	INT ON_angle;
	INT OFF_angle;
	INT value;
}NAST_BRZDA;

_GLOBAL NAST_BRZDA nastBrzda;		 /* promena pro ulozeni nastaveni uhlu*/


/* position of record in the  "nastaveni" array*/
#define davkovacZ 	0	
#define davkovacV 	1
#define posuvFolie	2
#define datovani	3
#define strihani	4
#define skladani	5
#define podrazeni	6
#define vystrkavani	7
#define fotonka		8
#define topeni      9

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

#define SM_PAUSE	6			/*  cekam na davkovac */

#define	SM_STOP_PRESSED  7 	/*	stop stisknuto behem provozu - cekam na dojeti do vychozi polohy, ale
								normalne pokracuju v cinnosti*/
#define	SM_SOFT_ERROR  8 	/*	nehavarijni chyba behem provozu - cekam na dojeti do vychozi polohy, ale
								normalne pokracuju v cinnosti*/
#define	SM_SOFT_ERR_NO_START  9	/*	ne-havarijni chybovy stav - cekam na dojeti do vychozi polohy
									ale neprovadim zadne akce, pouze zastavim ve vychozi poloze
									- pokud vynikla chyba pred stavem 4*/
#define	SM_CRITICAL_ERROR  10 	/*	kriticka chyba - okamzite zastaveni stroje*/
				 	
#define	SM_IO_TEST  11 			/*	testovani - ignoruje se vse ostatni*/
#define	SM_RUN_TEST  12 		/* 	testovani behu stroje */

/**
*	stavova masina stroje - podle toho se ridi cinnost
*/
_GLOBAL SINT stateMachine;
_GLOBAL UINT testMode;		/* nastaven do 1 kdyz se testuje beh stroje, 2 - ukoncuje beh, jinak 0*/
	
	

/* analog output */
_GLOBAL INT ao_menic;

_GLOBAL UINT tmp;
