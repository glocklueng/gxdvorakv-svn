//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "passUnit.h"
#include "dodavatelUnit.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TPasswordForm *PasswordForm;
TForm *SourceForm;

//---------------------------------------------------------------------
__fastcall TPasswordForm::TPasswordForm(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------

void __fastcall TPasswordForm::OKBtnClick(TObject *Sender)
{
  dynamic_cast<TDodavatelForm*>(SourceForm)->setEdit(Password->Text);
  return;


}
//---------------------------------------------------------------------------

void __fastcall TPasswordForm::CancelBtnClick(TObject *Sender)
{
  Visible=false;   
}
//---------------------------------------------------------------------------



void __fastcall TPasswordForm::setSource(TForm *Source)
{
   SourceForm=Source;
}
void __fastcall TPasswordForm::FormShow(TObject *Sender)
{
   Password->Text="";   
}
//---------------------------------------------------------------------------

