
// Sigmatek codes


/** command list **/
const u8 KeyNbr1[4]={0x00,0xFD,0x4A,0xB5};
const u8 KeyNbr2[4]={0x00,0xFD,0x0A,0xF5};
const u8 KeyNbr3[4]={0x00,0xFD,0x08,0xF7};
const u8 KeyNbr4[4]={0x00,0xFD,0x6A,0x95};
const u8 KeyNbr5[4]={0x00,0xFD,0x2A,0xD5};
const u8 KeyNbr6[4]={0x00,0xFD,0x28,0xD7};
const u8 KeyNbr7[4]={0x00,0xFD,0x72,0x8D};
const u8 KeyNbr8[4]={0x00,0xFD,0x32,0xCD};
const u8 KeyNbr9[4]={0x00,0xFD,0x30,0xCF};
const u8 KeyNbr0[4]={0x00,0xFD,0xf0,0x0F};
const u8 KeyAudio[4]={0x00,0xFD,0x00,0xFF};
const u8 KeyBlue[4]={0x00,0xFD,0xE0,0x1F};
const u8 KeyDTV[4]={0x00,0xFD,0x98,0x67};
const u8 KeyEPG[4]={0x00,0xFD,0xAA,0x55};
const u8 KeySlow[4]={0x00,0xFD,0x18,0xE7};
const u8 KeyOK[4]={0x00,0xFD,0x58,0xA7};
const u8 KeyVolDn[4]={0x00,0xFD,0x5A,0xA5};
const u8 KeyVolUp[4]={0x00,0xFD,0xD8,0x27};
const u8 KeyChUp[4]={0x00,0xFD,0x60,0x9F};
const u8 KeyChDn[4]={0x00,0xFD,0x68,0x97};
const u8 KeySubt[4]={0x00,0xFD,0x10,0xEF};
const u8 KeyYellow[4]={0x00,0xFD,0x20,0xDF};
const u8 KeyFav[4]={0x00,0xFD,0xA8,0x57};
const u8 KeyFF[4]={0x00,0xFD,0x88,0x77};
const u8 KeyStop[4]={0x00,0xFD,0xB0,0x4F};
const u8 KeyExit[4]={0x00,0xFD,0xA0,0x5F};
const u8 KeyRec[4]={0x00,0xFD,0x48,0xB7};
const u8 KeyPause[4]={0x00,0xFD,0x70,0x8F};
const u8 KeyRecal[4]={0x00,0xFD,0xE8,0x17};
const u8 KeyGoto[4]={0x00,0xFD,0xC8,0x37};
const u8 KeyText[4]={0x00,0xFD,0xD0,0x2F};
const u8 KeyMute[4]={0x00,0xFD,0xC0,0x3F};
const u8 KeyRecLst[4]={0x00,0xFD,0x1A,0xE5};
const u8 KeyInfo[4]={0x00,0xFD,0x12,0xED};
const u8 KeyGreen[4]={0x00,0xFD,0x22,0xDD};
const u8 KeyLang[4]={0x00,0xFD,0x02,0xFD};
const u8 KeyStby[4]={0x00,0xFD,0x9A,0x65};
const u8 KeyFR[4]={0x00,0xFD,0x8A,0x75};
const u8 KeyPlay[4]={0x00,0xFD,0xB2,0x4D};
const u8 KeyMenu[4]={0x00,0xFD,0xA2,0x5D};
const u8 KeyPvrInfo[4]={0x00,0xFD,0x52,0xAD};
const u8 KeyRed[4]={0x00,0xFD,0x62,0x9D};
const u8 KeyRadio[4]={0x00,0xFD,0x42,0xBD};


u8 *keyToCmd[]={ 0,
		KeySlow,		KeyNbr6,		KeyNbr3,		KeyNbr9,		KeySubt,		KeyYellow,	KeyAudio ,
		KeyDTV, 		KeyFav,		KeyFF,		KeyStop,		0,				KeyExit,		0,
		KeyOK,		KeyChDn,		KeyRec,		KeyPause,	0,				KeyChUp,		0,
		KeyVolUp,	KeyRecal,	KeyGoto,		KeyNbr0,		KeyText,		KeyBlue,		KeyMute,
		KeyRecLst,	KeyNbr5,		KeyNbr2,		KeyNbr8,		KeyInfo,		KeyGreen,	KeyLang,
		KeyStby,		KeyEPG,		KeyFR,		KeyPlay,		0,				KeyMenu,		0,
		KeyVolDn,	KeyNbr4,		KeyNbr1,		KeyNbr7,		KeyPvrInfo,	KeyRed,		KeyRadio
}; 




