//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "dodavatelUnit.h"
#include "data.h"
#include "passUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDodavatelForm *DodavatelForm;
//---------------------------------------------------------------------------
__fastcall TDodavatelForm::TDodavatelForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void TDodavatelForm::setEdit(String aPass)

{
  if (aPass=="0167"){
      ICOEdit->Enabled=true;
      DICEdit->Enabled=true;
      NazevEdit->Enabled=true;
  }
}

//---------------------------------------------------------------------------
void __fastcall TDodavatelForm::Povoliteditaci1Click(TObject *Sender)
{


   PasswordForm->setSource(this);
   PasswordForm->ShowModal();

}

void __fastcall TDodavatelForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
      Databaze->TableDod->Edit();
      Databaze->TableDod->Post();
      ICOEdit->Enabled=false;
      DICEdit->Enabled=false;
      NazevEdit->Enabled=false;
}
//---------------------------------------------------------------------------



