//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "tiskDialogUnit.h"
#include "data.h"
#include "fakturaTisk.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTiskDialogForm *TiskDialogForm;
//long cisloF;
//---------------------------------------------------------------------------
__fastcall TTiskDialogForm::TTiskDialogForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TTiskDialogForm::setFakturaNumber(long aNumber)
{
  //  cisloF=aNumber;
    CisloFakturyEdit->Text= IntToStr(aNumber);
}

//---------------------------------------------------------------------------

void __fastcall TTiskDialogForm::FormShow(TObject *Sender)
{
   Databaze->TableFakt->Active=true;
   Databaze->TableFakt->Last();
   if (Databaze->TableFakt->Eof && Databaze->TableFakt->Bof ){
      //cisloFaktury=2004000;
   }else {
     long cisloFaktury=Databaze->TableFakt->FieldByName("Cislo")->Value;
      CisloFakturyEdit->Text= IntToStr(cisloFaktury);
   }
   TLocateOptions Opts;
   Opts.Clear();
   Opts << loPartialKey;
   Databaze->TableFakt->Locate("Cislo",CisloFakturyEdit->Text,Opts);

   
}
//---------------------------------------------------------------------------
void __fastcall TTiskDialogForm::UpDown1Click(TObject *Sender,
      TUDBtnType Button)
{
    long cisloFaktury=StrToInt(CisloFakturyEdit->Text);
      if(Button== Comctrls::btNext){
          CisloFakturyEdit->Text=++cisloFaktury;
      }else if (Button == Comctrls::btPrev){
            CisloFakturyEdit->Text=--cisloFaktury;
      }
      TLocateOptions Opts;
      Opts.Clear();
      Opts << loPartialKey;
      Databaze->TableFakt->Locate("Cislo",CisloFakturyEdit->Text,Opts);


}
//---------------------------------------------------------------------------
void __fastcall TTiskDialogForm::CancelBtnClick(TObject *Sender)
{
    TiskDialogForm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TTiskDialogForm::TiskBtnClick(TObject *Sender)
{
      long cisloFaktury=StrToInt(CisloFakturyEdit->Text);
      boolean result=PrintDialog1->Execute();
      if (result){
         tisk(cisloFaktury);
      }
      TiskDialogForm->Close();
}
//---------------------------------------------------------------------------
