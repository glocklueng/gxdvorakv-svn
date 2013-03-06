//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "polozkyUnit.h"
#include "data.h"
#include "mainUnit.h"
#include "fakturaTisk.h"
#include "stdio.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPolozkyForm *PolozkyForm;

//---------------------------------------------------------------------------
__fastcall TPolozkyForm::TPolozkyForm(TComponent* Owner)
        : TForm(Owner)
{
}

void __fastcall TPolozkyForm::FormCreate(TObject *Sender)
{
    SAZBA_DPH = 21.0;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TPolozkyForm::FormShow(TObject *Sender)
{
//    int id;
   TLocateOptions Opts;
   Opts.Clear();
   Opts << loPartialKey;
   int LocalCisloFaktury = CisloFaktury;
   Databaze->TableFakt->Active=false;
   Databaze->TablePol->Active=true;
   Databaze->TablePol->IndexName ="" ;
   Databaze->TablePol->MasterSource = NULL;
   Databaze->TablePol->Last();
   lastIdPolozky = Databaze->TablePol->FieldByName("IdPolozky")->AsInteger;

   Databaze->TablePol->MasterSource = Databaze->DataSourceFakt;
   Databaze->TablePol->IndexName ="FakturaCislo" ;
   Databaze->TableFakt->Active=true;
   Databaze->TableFakt->Locate("Cislo", LocalCisloFaktury,Opts);
   CisloFakturyLabel->Caption=Databaze->TableFakt->FieldByName("Cislo")->Value;
 //  DBMemoInfo->Enabled = true;
   cisloPolozky=1;
  // Databaze->TablePol->Edit();

  // DBGridPolozky->Fields[0]->AsInteger=++lastIdPolozky;     */
}
//---------------------------------------------------------------------------


void __fastcall TPolozkyForm::kg1Click(TObject *Sender)
{
    Databaze->TablePol->FieldByName("TypJednotky")->Value="kg";
}
//---------------------------------------------------------------------------

void __fastcall TPolozkyForm::mClick(TObject *Sender)
{
        Databaze->TablePol->FieldByName("TypJednotky")->Value="m";
}
//---------------------------------------------------------------------------

void __fastcall TPolozkyForm::ks1Click(TObject *Sender)
{
       Databaze->TablePol->FieldByName("TypJednotky")->Value="ks";
}
//---------------------------------------------------------------------------

void __fastcall TPolozkyForm::KonecBtnClick(TObject *Sender)
{

   Databaze->TablePol->Edit();
   Databaze->TablePol->Post();
   Databaze->TableFakt->Edit();
   Databaze->TableFakt->Post();

   if (MessageDlg("Vytisknout ?", mtConfirmation, TMsgDlgButtons() << mbYes
       << mbNo, 0)== mrYes ) {
        //
        tisk(CisloFaktury);
        //
   }
   PolozkyForm->Visible=false;
   MainForm->Visible=true;


   MainForm->DBNavigatorOdb->Visible=false;
   MainForm->GroupBoxF->Visible=false;
   MainForm->GroupBoxOdb->Visible=false;
   MainForm->DBGridOdb->Visible=false;
   MainForm->GroupBoxOdberatelHledani->Visible=false;

   Databaze->TableFakt->IndexName="";
   Databaze->TableFakt->MasterSource= NULL;
   Databaze->TableFakt->MasterFields="";
   Databaze->TableFakt->Active=false;

}
//---------------------------------------------------------------------------

void __fastcall TPolozkyForm::FormResize(TObject *Sender)
{
  //DBGridPolozky->Top= 205;
   DBGridPolozky->Invalidate();
   DBGridPolozky->Refresh();
   PolozkyForm->Invalidate();
   PolozkyForm->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TPolozkyForm::FormClose(TObject *Sender, TCloseAction &Action)
{
 if (MessageDlg("Zahodit zmìny  ?", mtConfirmation, TMsgDlgButtons() << mbYes
       << mbNo, 0)== mrNo ) {
      try{
         Databaze->TablePol->Edit();
         Databaze->TablePol->Post();
      }catch(const Exception& exception){
      //   printf("error");
      }
      try{
         Databaze->TableFakt->Edit();
         Databaze->TableFakt->Post();
      } catch (const Exception& exception1){
         //printf("error");
      }
   }
   MainForm->Visible=true;
}
//---------------------------------------------------------------------------

void __fastcall TPolozkyForm::EditBtnClick(TObject *Sender)
{
   TLocateOptions Opts;
   Opts.Clear();
   Opts << loPartialKey;

   Databaze->TablePol->Last();


   cisloPolozky=Databaze->TablePol->FieldByName("CisloPolozky")->AsInteger;
   CisloFaktury=Databaze->TableFakt->FieldByName("Cislo")->AsInteger;
  // cisloPolozky++;

   DBGridPolozky->Enabled=true;
   DBGridFaktury->Enabled=false;
   DBMemoInfo->Enabled = false;
   DBGridFaktury->Repaint();
   PolozkyForm->DBNavigator1->DataSource=Databaze->DataSourcePol;
   PolozkyForm->DBGridPolozky->Columns->Items[3]->ReadOnly =false;
   PolozkyForm->Paint();
   DBGridPolozky->SetFocus();
   Databaze->TablePol->Edit();
   if(Databaze->TablePolNazev->Value==NULL){
      Databaze->TablePolNazev->Value="";
   }

/*   Databaze->TablePol->MasterSource = NULL;
   Databaze-> TablePol->Last();
   PolozkyForm->lastIdPolozky = Databaze->TablePol->FieldByName("IdPolozky")->AsInteger;
   Databaze->TablePol->MasterSource = Databaze->DataSourceFakt;*/

}
//---------------------------------------------------------------------------


void __fastcall TPolozkyForm::DBMemoInfoDblClick(TObject *Sender)
{
   DBMemoInfo->ReadOnly = false;   
}
//---------------------------------------------------------------------------

void __fastcall TPolozkyForm::DBMemoInfoExit(TObject *Sender)
{
   DBMemoInfo->ReadOnly = true;   
}
//---------------------------------------------------------------------------

