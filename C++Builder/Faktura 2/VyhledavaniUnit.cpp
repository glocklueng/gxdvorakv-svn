//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "VyhledavaniUnit.h"
#include "data.h"
#include "mainUnit.h"
#include "polozkyUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVyhledavaniForm *VyhledavaniForm;
//---------------------------------------------------------------------------
__fastcall TVyhledavaniForm::TVyhledavaniForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TVyhledavaniForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{

      Databaze->TableFakt->IndexName="";
      Databaze->TableFakt->MasterSource= NULL;
      Databaze->TableFakt->MasterFields="";
      Databaze->TableFakt->Active=false;
      MainForm->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TVyhledavaniForm::StornoBtnClick(TObject *Sender)
{
   MainForm->Visible=true;
   VyhledavaniForm->Visible=false;
   Databaze->TableFakt->IndexName="";
   Databaze->TableFakt->MasterSource= NULL;
   Databaze->TableFakt->MasterFields="";
   Databaze->TableFakt->Active=false;
}
//---------------------------------------------------------------------------

void __fastcall TVyhledavaniForm::ZobrazitBtnClick(TObject *Sender)
{

   PolozkyForm->CisloFaktury=Databaze->TableFakt->FieldByName("Cislo")->AsInteger;
//   StrToInt(CisloFakturyEdit->Text);
   PolozkyForm->GroupBoxFaktury->Visible=true;
   PolozkyForm->DBGridPolozky->Align=alNone;
   PolozkyForm->DBGridPolozky->Top=205;
   PolozkyForm->DBGridPolozky->Height= ((PolozkyForm->Height)-235);
   PolozkyForm->DBGridPolozky->Anchors << akTop << akBottom << akLeft << akRight;

   PolozkyForm->DBGridPolozky->Enabled=false;
   PolozkyForm->DBGridFaktury->Enabled=true;
   PolozkyForm->Position=poScreenCenter;
   PolozkyForm->Visible=true;
   PolozkyForm->DBGridFaktury->SetFocus();
   PolozkyForm->DBNavigator1->DataSource=Databaze->DataSourceFakt;
   PolozkyForm->EditBtn->Visible=true;
   MainForm->Visible=false;
   VyhledavaniForm->Visible=false;



}
//---------------------------------------------------------------------------

