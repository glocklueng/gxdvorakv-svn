//---------------------------------------------------------------------------

#ifndef mainFormH
#define mainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
//#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <ComCtrls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TMenuItem *Faktura1;
        TMenuItem *menuEditaceUlozenych;
        TMenuItem *menuNova;
        TMenuItem *Vyhledavanipodleodberatele1;
        TMenuItem *Dodavatel1;
        TMenuItem *menuOdbEdit;
        TMenuItem *Vyhledavani2;
        TMenuItem *Nastaveni1;
        TMenuItem *Dodavatel2;
        TMenuItem *Tisk1;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *Konec1;
        TMenuItem *Poznamka1;
        TGroupBox *GroupBoxF;
        TLabel *Label1;
        TEdit *CisloFakturyEdit;
        TUpDown *UpDown1;
        TDateTimePicker *DateVystaveni;
        TDateTimePicker *DateSplatnosti;
        TDateTimePicker *DateZdaneni;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TGroupBox *GroupBoxOdb;
        TDBGrid *DBGridOdb;
        TDBNavigator *DBNavigatorOdb;
        TDBEdit *DBEdit1;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label8;
        TDBEdit *DBEdit2;
        TDBEdit *DBEdit3;
        TDBEdit *DBEdit4;
        TDBEdit *DBEdit5;
        TLabel *Label7;
        TDBEdit *DBEdit6;
        TDBEdit *DBEdit7;
        TLabel *Label9;
        TLabel *Label10;
        TGroupBox *GroupBox3;
        TDBText *DBText1;
        TGroupBox *GroupBoxOdberatelHledani;
        TEdit *Edit2;
        TButton *NajdiBtn;
        TLabel *Firma;
        TButton *UpravitBtn;
        TButton *PridatBtn;
        TButton *SmazatBtn;
        TButton *StornoBtn;
        TButton *UlozitBtn;
        TButton *PokracovatBtn;
        void __fastcall Konec1Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall menuNovaClick(TObject *Sender);
        void __fastcall PridatBtnClick(TObject *Sender);
        void __fastcall StornoBtnClick(TObject *Sender);
        void __fastcall SmazatBtnClick(TObject *Sender);
        void __fastcall menuOdbEditClick(TObject *Sender);
        void __fastcall UpravitBtnClick(TObject *Sender);
        void __fastcall UlozitBtnClick(TObject *Sender);
        void __fastcall PokracovatBtnClick(TObject *Sender);
        void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
        void __fastcall Tisk1Click(TObject *Sender);
   void __fastcall menuEditaceUlozenychClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
