//---------------------------------------------------------------------------

#include <vcl.h>
#include<string>
#pragma hdrstop

#include "data.h"
#include "polozkyUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDatabaze *Databaze;
//---------------------------------------------------------------------------
__fastcall TDatabaze::TDatabaze(TComponent* Owner)
        : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TDatabaze::TablePolCalcFields(TDataSet *DataSet)
{

  float dph= TablePol->FieldByName("SazbaDPH")->AsFloat; //PolozkyForm->SAZBA_DPH;
  TablePolCenaCelkem->Value=TablePolPocetJednotek->Value * TablePolCenaJednotky->Value;
  TablePolDPHCelkem->Value=TablePolCenaCelkem->Value * dph/(100+dph);
}
//---------------------------------------------------------------------------


void __fastcall TDatabaze::TablePolNewRecord(TDataSet *DataSet)
{
  int id,cislo;


  PolozkyForm->lastIdPolozky++;
  PolozkyForm->pocetPolozek->Caption=IntToStr(PolozkyForm->cisloPolozky++);

  id = PolozkyForm->lastIdPolozky;         
  cislo = PolozkyForm->cisloPolozky;
  TablePol->FieldByName("IdPolozky")->AsInteger=id;
  TablePol->FieldByName("SazbaDPH")->AsFloat=PolozkyForm->SAZBA_DPH;
  TablePol->FieldByName("CisloPolozky")->AsInteger=cislo;
  TablePol->FieldByName("PocetJednotek")->AsFloat=0;
  TablePol->FieldByName("CenaJednotky")->AsFloat=0;



}
//---------------------------------------------------------------------------

void __fastcall TDatabaze::TablePolTypJednotkyChange(TField *Sender)
{
       String typ;

    typ=(TablePol->FieldByName("TypJednotky")->AsString).c_str();
    const char *a = typ.c_str();

  //cc= stary[0];
 if (a[0]=='k') {
        if ((a[1]=='s')||(a[1]=='g')){
                return;
        }
 }else if ((a[0]=='m')&&(a[1]=='\0')){
     return;
 }
   TablePol->FieldByName("TypJednotky")->AsString="ks";
}
//---------------------------------------------------------------------------

void __fastcall TDatabaze::TablePolAfterCancel(TDataSet *DataSet)
{
  //  PolozkyForm->lastIdPolozky--;
   // PolozkyForm->cisloPolozky--;
}
//---------------------------------------------------------------------------



void __fastcall TDatabaze::TablePolBeforeInsert(TDataSet *DataSet)
{
  TablePol->First();
  double sumaCen=0;
  while (!TablePol->Eof){
     sumaCen+=TablePol->FieldByName("CenaCelkem")->AsFloat;
     Databaze->TablePol->Next();
  }
  PolozkyForm->cenaCelkem->Caption=FloatToStrF(sumaCen,ffCurrency,15,2);
}
//---------------------------------------------------------------------------



void __fastcall TDatabaze::TablePolAfterEdit(TDataSet *DataSet)
{
   PolozkyForm->lastIdPolozky--;
   PolozkyForm->lastIdPolozky++;
   return;   
}
//---------------------------------------------------------------------------




void __fastcall TDatabaze::TableFaktAfterScroll(TDataSet *DataSet)
{
   TLocateOptions Opts;
   Opts.Clear();
   Opts << loPartialKey;
   int i = 0;

   long cislo = TableFakt->FieldByName("Cislo")->AsInteger;
   TablePol->Active=true;
   TablePol->Locate("CisloFaktury",cislo,Opts);
   do {
    i++;
   }  while (TablePol->FindNext());

   PolozkyForm->pocetPolozek->Caption = IntToStr(i);
   PolozkyForm->cenaCelkem->Caption= "---";
   PolozkyForm->CisloFaktury=TableFakt->FieldByName("Cislo")->AsInteger;
   PolozkyForm->CisloFakturyLabel->Caption = PolozkyForm->CisloFaktury;

  }
//---------------------------------------------------------------------------











