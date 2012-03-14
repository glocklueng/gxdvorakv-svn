//---------------------------------------------------------------------------

#ifndef tiskDialogUnitH
#define tiskDialogUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TTiskDialogForm : public TForm
{
__published:	// IDE-managed Components
   TEdit *CisloFakturyEdit;
   TUpDown *UpDown1;
   TLabel *Label1;
   TBitBtn *TiskBtn;
   TBitBtn *CancelBtn;
   TPrintDialog *PrintDialog1;
   TGroupBox *GroupBox1;
   TDBEdit *DBEdit1;
   void __fastcall FormShow(TObject *Sender);
   void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
   void __fastcall CancelBtnClick(TObject *Sender);
   void __fastcall TiskBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TTiskDialogForm(TComponent* Owner);
   void __fastcall setFakturaNumber(long aNumber);
};
//---------------------------------------------------------------------------
extern PACKAGE TTiskDialogForm *TiskDialogForm;
//---------------------------------------------------------------------------
#endif
