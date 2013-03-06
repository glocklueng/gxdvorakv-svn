//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mainUnit.h"
#include "data.h"
#include "polozkyUnit.h"
#include "fakturaTisk.h"
#include "dodavatelUnit.h"
#include "tiskDialogUnit.h"
#include "poznamkaUnit.h"
#include "VyhledavaniUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::menuKonecClick(TObject *Sender)
{
    MainForm->Close();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormActivate(TObject *Sender)
{

    GroupBoxOdb->Enabled=false;
    GroupBoxF->Enabled=false;
    DBNavigatorOdb->Enabled=false;
    DBGridOdb->Enabled=true;
//    DBGridOdb->ReadOnly=true;
    PridatBtn->Enabled=true;
    UpravitBtn->Enabled=true;
    SmazatBtn->Enabled=true;
    StornoBtn->Enabled=false;
    UlozitBtn->Enabled=false;
    PokracovatBtn->Enabled=true;
    GroupBoxOdberatelHledani->Visible=false;
    DBNavigatorOdb->Visible=false;
    GroupBoxF->Visible=false;
    GroupBoxOdb->Visible=false;
    DBGridOdb->Visible=false;


}
//---------------------------------------------------------------------------



void __fastcall TMainForm::menuNovaClick(TObject *Sender)
{
   long cisloFaktury;
   GroupBoxF->Enabled=true;
   GroupBoxF->Visible=true;
   GroupBoxOdb->Enabled = true;
   GroupBoxOdb->Visible=true;
   GroupBoxOdberatelHledani->Visible=false;

   Databaze->TableOdb->Active=true;
   Databaze->TableOdb->IndexName = "firmName";
  // Databaze->DataSourceOdb->AutoEdit=true;
   DBGridOdb->Visible=true;
   DBGridOdb->Enabled=true;
   DBNavigatorOdb->Enabled=true;
   DBNavigatorOdb->Visible=true;
   Databaze->TableFakt->Active=true;
   Databaze->TableFakt->Last();
   if (Databaze->TableFakt->Eof && Databaze->TableFakt->Bof ){
      cisloFaktury=2004000;
   }else {
      cisloFaktury=Databaze->TableFakt->FieldByName("Cislo")->Value;
   }

   DateSplatnosti->Date=IncMonth(Date(),1);
   DateVystaveni->Date=Date();
   DateZdaneni->Date=Date();


   CisloFakturyEdit->Text=++cisloFaktury;
   DBEdit1->Enabled=false;
   DBEdit2->Enabled=false;
   DBEdit3->Enabled=false;
   DBEdit4->Enabled=false;
   DBEdit5->Enabled=false;
   DBEdit6->Enabled=false;
   DBEdit7->Enabled=false;

    PridatBtn->Enabled=true;
    UpravitBtn->Enabled=true;
    SmazatBtn->Enabled=true;
    StornoBtn->Enabled=false;
    UlozitBtn->Enabled=false;
    PokracovatBtn->Enabled=true;
    PokracovatBtn->Visible=true;
    KonecBtn->Enabled=false;
    KonecBtn->Visible=false;

}
//---------------------------------------------------------------------------



void __fastcall TMainForm::PridatBtnClick(TObject *Sender)
{
   int id;
   Databaze->TableOdb->IndexName = "";
   Databaze->TableOdb->Last();
   if (!Databaze->TableOdb->IsEmpty()){
           id= Databaze->TableOdb->FieldByName("Id")->Value;
   }else {
           id=0;
   }
   Databaze->TableOdb->Edit();
   Databaze->TableOdb->Append();
   Databaze->TableOdb->FieldByName("Id")->AsInteger =++id;
   GroupBoxOdb->Enabled=true;
   PridatBtn->Enabled=false;
   UpravitBtn->Enabled=false;
   SmazatBtn->Enabled=false;
   StornoBtn->Enabled=true;
   UlozitBtn->Enabled=true;
   PokracovatBtn->Enabled=false;
   DBNavigatorOdb->Enabled=false;

  // DBGridOdb->Enabled=false;

   DBEdit1->Enabled=true;
   DBEdit2->Enabled=true;
   DBEdit3->Enabled=true;
   DBEdit4->Enabled=true;
   DBEdit5->Enabled=true;
   DBEdit6->Enabled=true;
   DBEdit7->Enabled=true;


}
//---------------------------------------------------------------------------


void __fastcall TMainForm::StornoBtnClick(TObject *Sender)
{
 //  GroupBoxOdb->Enabled=false;
   PridatBtn->Enabled=true;
   UpravitBtn->Enabled=true;
   SmazatBtn->Enabled=true;
   StornoBtn->Enabled=false;
   UlozitBtn->Enabled=false;
   PokracovatBtn->Enabled=true;
   DBNavigatorOdb->Enabled=true;
   DBGridOdb->Enabled=true;
   Databaze->TableOdb->Cancel();
   DBEdit1->Enabled=false;
   DBEdit2->Enabled=false;
   DBEdit3->Enabled=false;
   DBEdit4->Enabled=false;
   DBEdit5->Enabled=false;
   DBEdit6->Enabled=false;
   DBEdit7->Enabled=false;
   Databaze->TableOdb->IndexName = "firmName";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SmazatBtnClick(TObject *Sender)
{
   if (MessageDlg("Opravdu smazat?", mtConfirmation, TMsgDlgButtons() << mbYes
       << mbNo, 0)== mrYes ) {
     Databaze->TableOdb->Delete();
   }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::UpravitBtnClick(TObject *Sender)
{
   GroupBoxOdb->Enabled=true;
   PridatBtn->Enabled=false;
   UpravitBtn->Enabled=false;
   SmazatBtn->Enabled=false;
   StornoBtn->Enabled=true;
   UlozitBtn->Enabled=true;
   PokracovatBtn->Enabled=false;
   DBNavigatorOdb->Enabled=false;
   DBGridOdb->Enabled=false;
   Databaze->TableOdb->Edit();
   DBEdit1->Enabled=true;
   DBEdit2->Enabled=true;
   DBEdit3->Enabled=true;
   DBEdit4->Enabled=true;
   DBEdit5->Enabled=true;
   DBEdit6->Enabled=true;
   DBEdit7->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::UlozitBtnClick(TObject *Sender)
{
   Databaze->TableOdb->Post();
   UpravitBtn->Enabled=true;
   SmazatBtn->Enabled=true;
   StornoBtn->Enabled=false;
   UlozitBtn->Enabled=false;
   PridatBtn->Enabled=true;
   PokracovatBtn->Enabled=true;
   DBNavigatorOdb->Enabled=true;
   DBGridOdb->Enabled=true;
   Databaze->TableOdb->IndexName = "firmName";
   DBEdit1->Enabled=false;
   DBEdit2->Enabled=false;
   DBEdit3->Enabled=false;
   DBEdit4->Enabled=false;
   DBEdit5->Enabled=false;
   DBEdit6->Enabled=false;
   DBEdit7->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PokracovatBtnClick(TObject *Sender)
{
   //int cislo;
   int idOdb;
   if (Databaze->TableOdb->FieldByName("Id")->IsNull) {
      return;
   } else {
   idOdb=Databaze->TableOdb->FieldByName("Id")->Value;
   }
   
   // id faktury, cislo faktury,id odberatele,datum splatnosti, vystaveni, zdaneni
   Databaze->TableFakt->Active=true;
   Databaze->TableFakt->Edit();
   Databaze->TableFakt->InsertRecord(ARRAYOFCONST((
                CisloFakturyEdit->Text,
                idOdb,
                CisloObjednavkyEdit->Text,
                (CheckBoxCash->Checked)?(AnsiString)"":DateToStr(DateSplatnosti->Date),
                DateToStr( DateVystaveni->Date),
                DateToStr( DateZdaneni->Date)
                )));

   Databaze->TableFakt->Edit();
   Databaze->TableFakt->Post();
 //  PolozkyForm->EditBtn->Visible=false;
   PolozkyForm->Position=poScreenCenter;
   PolozkyForm->Visible=true;
   Databaze->TableFakt->Last();


   PolozkyForm->CisloFaktury=StrToInt(CisloFakturyEdit->Text);
   PolozkyForm->GroupBoxFaktury->Visible=false;
   PolozkyForm->DBGridPolozky->Align=alClient;
   //PolozkyForm->DBGridPolozky->Enabled=true;
   PolozkyForm->DBGridPolozky->Enabled=false;
   //PolozkyForm->DBGridPolozky->Columns->Items[3]->ReadOnly =true;
   PolozkyForm->DBNavigator1->DataSource=NULL;//Databaze->DataSourceFakt;
   PolozkyForm->cisloPolozky = 0;
   PolozkyForm->DBMemoInfo->ReadOnly = false;
 /*
   Databaze->TablePol->Active=true;
   Databaze->TablePol->Edit();     */


   MainForm->Visible=false;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
     long cisloFaktury=StrToInt(CisloFakturyEdit->Text);
        if(Button== Comctrls::btNext){
           CisloFakturyEdit->Text=++cisloFaktury;
       }else if (Button == Comctrls::btPrev){
            CisloFakturyEdit->Text=--cisloFaktury;
       }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::menuTiskClick(TObject *Sender)
{
      // tisktisk(2004001);
    //  TiskDialogForm->setFakturaNumber(cisloFaktury);
      TiskDialogForm->Position=poDesktopCenter;
      TiskDialogForm->ShowModal();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::menuEditaceUlozenychClick(TObject *Sender)
{
   Databaze->TableFakt->Active = true;
   if (Databaze->TableFakt->IsEmpty()){
      return;
   }    
  // PolozkyForm->CisloFaktury=StrToInt(CisloFakturyEdit->Text);
   PolozkyForm->GroupBoxFaktury->Visible=true;
//   PolozkyForm->DBGridPolozky->Align=alBottom;
  // PolozkyForm->Invalidate();


//VD   PolozkyForm->DBGridPolozky->Align=alNone;
//VD  PolozkyForm->DBGridPolozky->Top=205;
//VD   PolozkyForm->DBGridPolozky->Height= ((PolozkyForm->Height)-235);
   PolozkyForm->DBGridPolozky->Anchors << akTop << akBottom << akLeft << akRight;

   PolozkyForm->DBGridPolozky->Enabled=false;
   PolozkyForm->DBGridFaktury->Enabled=true;
   PolozkyForm->DBMemoInfo->Enabled = true;
   PolozkyForm->Position=poScreenCenter;
   PolozkyForm->Visible=true;
   PolozkyForm->DBGridFaktury->SetFocus();
   PolozkyForm->DBNavigator1->DataSource=Databaze->DataSourceFakt;
   PolozkyForm->EditBtn->Visible=true;
   MainForm->Visible=false;


}
//---------------------------------------------------------------------------



void __fastcall TMainForm::menuDodavatelClick(TObject *Sender)
{
   Databaze->TableDod->Active=true;
   Databaze->TableDod->First();

   DodavatelForm->NazevEdit->Enabled=false;
   DodavatelForm->ICOEdit->Enabled=false;
   DodavatelForm->DICEdit->Enabled=false;
   DodavatelForm->Position=poDesktopCenter;
   DodavatelForm->ShowModal();
    //Visible=true;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::menuNastTiskClick(TObject *Sender)
{
   // Printer
  // PrinterSetupDialog1->Position=poDesktopCenter;
    PrinterSetupDialog1->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
      MainForm->Position=poScreenCenter;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Poznamka1Click(TObject *Sender)
{
   Databaze->TableDod->Active=true;
   Databaze->TableDod->First();

   PoznamkaForm->Position=poDesktopCenter;
   PoznamkaForm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OdbereteleClick(TObject *Sender)
{
   GroupBoxF->Enabled=false;
   GroupBoxF->Visible=false;
   GroupBoxOdb->Enabled=true;
   GroupBoxOdb->Visible=true;

   DBNavigatorOdb->Enabled=true;
   DBNavigatorOdb->Visible=true;
   DBGridOdb->Enabled=true;
   DBGridOdb->Visible=true;
   PridatBtn->Enabled=true;
   UpravitBtn->Enabled=true;
   SmazatBtn->Enabled=true;
   StornoBtn->Enabled=false;
   UlozitBtn->Enabled=false;
   PokracovatBtn->Enabled=false;

   Databaze->TableOdb->Active=true;
   Databaze->TableOdb->IndexName = "firmName";

   GroupBoxOdberatelHledani->Visible=true;
   DBEdit1->Enabled=false;
   DBEdit2->Enabled=false;
   DBEdit3->Enabled=false;
   DBEdit4->Enabled=false;
   DBEdit5->Enabled=false;
   DBEdit6->Enabled=false;
   DBEdit7->Enabled=false;
   PokracovatBtn->Visible=false;
   KonecBtn->Visible=true;
   KonecBtn->Enabled=true;

}
//---------------------------------------------------------------------------



void __fastcall TMainForm::NajdiBtnClick(TObject *Sender)
{
//
      Databaze->TableOdb->Active=true;
      TLocateOptions Opts;
      String value=FirmEdit->Text;

      Opts.Clear();
      Opts << loPartialKey<< loCaseInsensitive ;

      if (!Databaze->TableOdb->Locate("Firma",value , Opts)){
         if(!Databaze->TableOdb->Locate("Firma2",value , Opts)){
              ShowMessage("Záznam  "+FirmEdit->Text+"  nenalezen !");
         }
      }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::KonecBtnClick(TObject *Sender)
{
   MainForm->DBNavigatorOdb->Visible=false;
   MainForm->GroupBoxF->Visible=false;
   MainForm->GroupBoxOdb->Visible=false;
   MainForm->DBGridOdb->Visible=false;
   MainForm->GroupBoxOdberatelHledani->Visible=false;

   Databaze->TableDod->Edit();
   Databaze->TableDod->Post();
   
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::menuVyhleOdbClick(TObject *Sender)
{
      VyhledavaniForm->Position=poScreenCenter;
      VyhledavaniForm->Width=MainForm->Width;
      VyhledavaniForm->Height=MainForm->Height;
      VyhledavaniForm->Visible=true;
      MainForm->Visible=false;
       //   Databaze->TableOdb->Active=true;
   //   Databaze->TableOdb->IndexName = "firmName";
      Databaze->TableFakt->Active=true;
      Databaze->TableFakt->IndexFieldNames="IdOdberatele";
      Databaze->TableFakt->MasterSource=Databaze->DataSourceOdb;
      Databaze->TableFakt->MasterFields="Id";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::DateVystaveniChange(TObject *Sender)
{

   DATE tmp = DateVystaveni->Date;
   DateSplatnosti->Date =IncMonth(tmp,1);
   DateZdaneni->Date=tmp;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBoxCashClick(TObject *Sender)
{
   if (CheckBoxCash->Checked){
        DateSplatnosti->Enabled = false;
   }else{
        DateSplatnosti->Enabled = true;
   }
}
//---------------------------------------------------------------------------

