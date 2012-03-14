//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "poznamkaUnit.h"
#include "data.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPoznamkaForm *PoznamkaForm;
//---------------------------------------------------------------------------
__fastcall TPoznamkaForm::TPoznamkaForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPoznamkaForm::OKBtnClick(TObject *Sender)
{
      Databaze->TableDod->Edit();
      Databaze->TableDod->Post();
      PoznamkaForm->Close();   
}
//---------------------------------------------------------------------------
void __fastcall TPoznamkaForm::FormDeactivate(TObject *Sender)
{
    Databaze->TableDod->Cancel();
}
//---------------------------------------------------------------------------
