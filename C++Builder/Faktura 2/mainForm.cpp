//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mainForm.h"
#include "data.h"
#include "fakturaForm.h"
#include "fakturaTisk.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Konec1Click(TObject *Sender)
{
    Form1->Close();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormActivate(TObject *Sender)
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



void __fastcall TForm1::menuNovaClick(TObject *Sender)
{
   long cisloFaktury;
   GroupBoxF->Enabled=true;
   GroupBoxF->Visible=true;
   GroupBoxOdb->Enabled = true;
   GroupBoxOdb->Visible=true;
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
   CisloFakturyEdit->Text=++cisloFaktury;
   DBEdit1->Enabled=false;
   DBEdit2->Enabled=false;
   DBEdit3->Enabled=false;
   DBEdit4->Enabled=false;
   DBEdit5->Enabled=false;
   DBEdit6->Enabled=false;
   DBEdit7->Enabled=false;

}
//---------------------------------------------------------------------------



void __fastcall TForm1::PridatBtnClick(TObject *Sender)
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


void __fastcall TForm1::StornoBtnClick(TObject *Sender)
{
 //  GroupBoxOdb->Enabled=false;
   PridatBtn->Enabled=true;
   UpravitBtn->Enabled=true;
   SmazatBtn->Enabled=true;
   StornoBtn->Enabled=false;
   UlozitBtn->Enabled=false;
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

void __fastcall TForm1::SmazatBtnClick(TObject *Sender)
{
   if (MessageDlg("Opravdu smazat?", mtConfirmation, TMsgDlgButtons() << mbYes
       << mbNo, 0)== mrYes ) {
     Databaze->TableOdb->Delete();
   }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::menuOdbEditClick(TObject *Sender)
{
    GroupBoxOdb->Enabled=true;
  //  GroupBoxF->Enabled=false;
    DBNavigatorOdb->Enabled=true;
    DBGridOdb->Enabled=true;
    PridatBtn->Enabled=true;
    UpravitBtn->Enabled=true;
    SmazatBtn->Enabled=true;
    StornoBtn->Enabled=false;
    UlozitBtn->Enabled=false;
    PokracovatBtn->Enabled=false;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::UpravitBtnClick(TObject *Sender)
{
   GroupBoxOdb->Enabled=true;
   PridatBtn->Enabled=false;
   UpravitBtn->Enabled=false;
   SmazatBtn->Enabled=false;
   StornoBtn->Enabled=true;
   UlozitBtn->Enabled=true;
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

void __fastcall TForm1::UlozitBtnClick(TObject *Sender)
{
   Databaze->TableOdb->Post();
   UpravitBtn->Enabled=true;
   SmazatBtn->Enabled=true;
   StornoBtn->Enabled=false;
   UlozitBtn->Enabled=false;
   PridatBtn->Enabled=true;
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

void __fastcall TForm1::PokracovatBtnClick(TObject *Sender)
{
  //int cislo;
  int idOdb;

   idOdb=Databaze->TableOdb->FieldByName("Id")->Value;
   // id faktury, cislo faktury,id odberatele,datum splatnosti, vystaveni, zdaneni
   Databaze->TableFakt->Active=true;
   Databaze->TableFakt->Edit();
 //  Databaze->TablePol->Active=true;
   Databaze->TableFakt->InsertRecord(ARRAYOFCONST((
                CisloFakturyEdit->Text,
                idOdb,
                DateToStr(DateSplatnosti->Date),
                DateToStr( DateVystaveni->Date),
                DateToStr( DateZdaneni->Date) )));

   Form2->CisloFaktury=StrToInt(CisloFakturyEdit->Text);
   Form2->GroupBoxFaktury->Visible=false;
   Form2->DBGridPolozky->Align=alClient;
   Form1->Visible=false;
   Form2->Visible=true;
   Form2->DBGridPolozky->Enabled=true;
   Databaze->TablePol->Edit();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
     long cisloFaktury=StrToInt(CisloFakturyEdit->Text);
        if(Button== Comctrls::btNext){
           CisloFakturyEdit->Text=++cisloFaktury;
       }else if (Button == Comctrls::btPrev){
            CisloFakturyEdit->Text=--cisloFaktury;
       }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Tisk1Click(TObject *Sender)
{
       tisk(2004001);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::menuEditaceUlozenychClick(TObject *Sender)
{
   Form2->CisloFaktury=StrToInt(CisloFakturyEdit->Text);
   Form2->GroupBoxFaktury->Visible=true;
//   Form2->DBGridPolozky->Align=alBottom;
  // Form2->Invalidate();
   Form2->DBGridPolozky->Align=alNone;
   Form2->DBGridPolozky->Anchors << akTop << akBottom << akLeft << akRight;
   Form2->DBGridPolozky->Top=205;
   Form2->DBGridPolozky->Height= (Form2->Height)-205;

   Form2->Visible=true;
   Form2->DBGridPolozky->Enabled=false;
   Form2->DBGridFaktury->Enabled=true;
   Form1->Visible=false;
   Form2->DBGridFaktury->SetFocus();
   Form2->DBNavigator1->DataSource=Databaze->DataSourceFakt;
}
//---------------------------------------------------------------------------

