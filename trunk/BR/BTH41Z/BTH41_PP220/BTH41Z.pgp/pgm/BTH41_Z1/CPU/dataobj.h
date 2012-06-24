/* Automation Studio Generated Header File, Format Version 1.00 */
/* do not change */
#ifndef DATAOBJ_H_
#define DATAOBJ_H_
#define _WEAK	__attribute__((__weak__))

#include <bur/plc.h>
#include <bur/plctypes.h>



/* Constants */
_WEAK const unsigned short doERR_BRINSTALL = 20604;
_WEAK const unsigned short doERR_CHECKSUM_WARNING = 20630;
_WEAK const unsigned short doERR_DUPOBJECT = 20601;
_WEAK const unsigned short doERR_ILLEGALLENGTH = 20608;
_WEAK const unsigned short doERR_ILLMEMTYPE = 20602;
_WEAK const unsigned short doERR_ILLOBJECT = 20605;
_WEAK const unsigned short doERR_ILLOBJTYPE = 20606;
_WEAK const unsigned short doERR_ILLPARAMETER = 20600;
_WEAK const unsigned short doERR_ILLSTATE = 20611;
_WEAK const unsigned short doERR_MODULNOTFOUND = 20609;
_WEAK const unsigned short doERR_NOMEMORY = 20603;
_WEAK const unsigned short doERR_STARTHANDLER = 20612;
_WEAK const unsigned short doERR_TOOLONG_MODULNAME = 20613;
_WEAK const unsigned short doERR_WRONGOFFSET = 20607;
_WEAK const unsigned short doERR_WRONGTIME = 20610;
_WEAK const unsigned char doNO_CS = 1;
_WEAK const unsigned char doSYSROM = 0;
_WEAK const unsigned char doTEMP = 65;
_WEAK const unsigned char doUSRRAM = 3;
_WEAK const unsigned char doUSRROM = 2;


/* Datatypes */
typedef struct DatObjCreateInternal
{
	unsigned char byKennung;
	plcbit bReadyFlag;
	unsigned short wStatus;
	unsigned char szName[33];
	unsigned char ModulHeader[32];
	unsigned char DaMbSection[36];
	unsigned long pDaSection;
	unsigned long ulSectionLength;
	unsigned char byMemType;
	unsigned long pBrmModule;
	unsigned long ulIdent;
} DatObjCreateInternal;

typedef struct DatObjCopyInternal
{
	unsigned char byKennung;
	plcbit bReadyFlag;
	unsigned short wStatus;
	unsigned char szName[33];
	unsigned char byMemType;
	unsigned long pBrmSource;
	unsigned long ulOption;
	unsigned long pBrmModule;
	unsigned long ulIdent;
} DatObjCopyInternal;

typedef struct DatObjDeleteInternal
{
	unsigned char byKennung;
	plcbit bReadyFlag;
	unsigned short wStatus;
	unsigned long ulIdent;
} DatObjDeleteInternal;



/* Datatypes of function blocks */
typedef struct DatObjChangeDate
{
	/* VAR_INPUT (analogous) */
	unsigned long pName;
	DATE_AND_TIME SetDate;
	/* VAR_OUTPUT (analogous) */
	unsigned short status;
	/* VAR_INPUT (digital) */
	plcbit enable;
} DatObjChangeDate_typ;

typedef struct DatObjInfo
{
	/* VAR_INPUT (analogous) */
	unsigned long pName;
	/* VAR_OUTPUT (analogous) */
	unsigned short status;
	unsigned long ident;
	unsigned long pDatObjMem;
	unsigned long len;
	unsigned char MemType;
	unsigned long Option;
	DATE_AND_TIME ChangeDate;
	/* VAR_INPUT (digital) */
	plcbit enable;
} DatObjInfo_typ;

typedef struct DatObjCopy
{
	/* VAR_INPUT (analogous) */
	unsigned long ident;
	unsigned long pNameTarget;
	unsigned char MemTypeTarget;
	unsigned long OptionTarget;
	/* VAR_OUTPUT (analogous) */
	unsigned short status;
	unsigned long identNew;
	unsigned long pDatObjMemNew;
	/* VAR (analogous) */
	struct DatObjCopyInternal DatObjInternalStruct;
	unsigned char byState;
	/* VAR_INPUT (digital) */
	plcbit enable;
} DatObjCopy_typ;

typedef struct DatObjMove
{
	/* VAR_INPUT (analogous) */
	unsigned long ident;
	unsigned char MemType;
	unsigned long Option;
	/* VAR_OUTPUT (analogous) */
	unsigned short status;
	unsigned long identNew;
	unsigned long pDatObjMem;
	/* VAR (analogous) */
	struct DatObjCopyInternal DatObjInternalStruct;
	unsigned char byState;
	/* VAR_INPUT (digital) */
	plcbit enable;
} DatObjMove_typ;

typedef struct DatObjDelete
{
	/* VAR_INPUT (analogous) */
	unsigned long ident;
	/* VAR_OUTPUT (analogous) */
	unsigned short status;
	/* VAR (analogous) */
	struct DatObjDeleteInternal DatObjInternalStruct;
	unsigned char byState;
	/* VAR_INPUT (digital) */
	plcbit enable;
} DatObjDelete_typ;

typedef struct DatObjRead
{
	/* VAR_INPUT (analogous) */
	unsigned long ident;
	unsigned long Offset;
	unsigned long pDestination;
	unsigned long len;
	/* VAR_OUTPUT (analogous) */
	unsigned short status;
	/* VAR_INPUT (digital) */
	plcbit enable;
} DatObjRead_typ;

typedef struct DatObjWrite
{
	/* VAR_INPUT (analogous) */
	unsigned long ident;
	unsigned long Offset;
	unsigned long pSource;
	unsigned long len;
	/* VAR_OUTPUT (analogous) */
	unsigned short status;
	/* VAR_INPUT (digital) */
	plcbit enable;
} DatObjWrite_typ;

typedef struct DatObjCreate
{
	/* VAR_INPUT (analogous) */
	unsigned char grp;
	unsigned long pName;
	unsigned long len;
	unsigned char MemType;
	unsigned long Option;
	unsigned long pCpyData;
	/* VAR_OUTPUT (analogous) */
	unsigned short status;
	unsigned long ident;
	unsigned long pDatObjMem;
	/* VAR (analogous) */
	struct DatObjCreateInternal DatObjInternalStruct;
	unsigned char byState;
	/* VAR_INPUT (digital) */
	plcbit enable;
} DatObjCreate_typ;



/* Prototyping of functions and function blocks */
void DatObjChangeDate(DatObjChangeDate_typ* inst);
void DatObjInfo(DatObjInfo_typ* inst);
void DatObjCopy(DatObjCopy_typ* inst);
void DatObjMove(DatObjMove_typ* inst);
void DatObjDelete(DatObjDelete_typ* inst);
void DatObjRead(DatObjRead_typ* inst);
void DatObjWrite(DatObjWrite_typ* inst);
void DatObjCreate(DatObjCreate_typ* inst);



#endif /* DATAOBJ_H_ */