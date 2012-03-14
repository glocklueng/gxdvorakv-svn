//---------------------------------------------------------------------------

#ifndef dodavatelUnitH
#define dodavatelUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TDodavatelForm : public TForm
{
__published:	// IDE-managed Components
        TDBEdit *NazevEdit;
        TDBEdit *AdresaEdit;
        TDBEdit *TelefonEdit;
        TDBEdit *MobilEdit;
        TLabel *Label1;
        TDBEdit *ICOEdit;
        TDBEdit *DICEdit;
        TDBEdit *CisloUctuEdit;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
   TPopupMenu *PopupMenu1;
   TMenuItem *Povoliteditaci1;
   void __fastcall Povoliteditaci1Click(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);


private:	// User declarations
public:		// User declarations
        __fastcall TDodavatelForm(TComponent* Owner);
        void setEdit(String);
};
//---------------------------------------------------------------------------
extern PACKAGE TDodavatelForm *DodavatelForm;
//---------------------------------------------------------------------------
#endif
