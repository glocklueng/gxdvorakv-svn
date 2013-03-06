//---------------------------------------------------------------------------

#ifndef dataH
#define dataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TDatabaze : public TDataModule
{
__published:	// IDE-managed Components
        TTable *TableDod;
        TTable *TableOdb;
        TTable *TableFakt;
        TTable *TablePol;
        TDataSource *DataSourceDod;
        TDataSource *DataSourceOdb;
        TDataSource *DataSourceFakt;
        TDataSource *DataSourcePol;
        TSmallintField *TableOdbId;
        TStringField *TableOdbFirma;
        TStringField *TableOdbFirma2;
        TStringField *TableOdbAdresa;
        TStringField *TableOdbICO;
        TStringField *TableOdbDIC;
        TStringField *TableOdbTelefon;
        TStringField *TableOdbMobil;
        TIntegerField *TableFaktCislo;
        TSmallintField *TableFaktIdOdberatele;
        TDateField *TableFaktSplatnost;
        TDateField *TableFaktVystaveni;
        TDateField *TableFaktZdaneni;
        TSmallintField *TablePolIdPolozky;
        TIntegerField *TablePolCisloFaktury;
        TSmallintField *TablePolCisloPolozky;
        TStringField *TablePolNazev;
        TFloatField *TablePolPocetJednotek;
        TStringField *TablePolTypJednotky;
        TFloatField *TablePolCenaJednotky;
        TFloatField *TablePolSazbaDPH;
        TCurrencyField *TablePolCenaCelkem;
        TFloatField *TablePolDPHCelkem;
   TSmallintField *TableDodId;
   TStringField *TableDodNazev;
   TStringField *TableDodAdresa;
   TStringField *TableDodTelefon;
   TStringField *TableDodMobil;
   TStringField *TableDodICO;
   TStringField *TableDodDIC;
   TStringField *TableDodCisloUctu;
   TStringField *TableDodPoznamka;
   TStringField *TableFaktOdbratelName;
   TStringField *TableFaktCisloObjednavky;
   TMemoField *TableFaktInformace;
        void __fastcall TablePolCalcFields(TDataSet *DataSet);
        void __fastcall TablePolNewRecord(TDataSet *DataSet);
        void __fastcall TablePolTypJednotkyChange(TField *Sender);
        void __fastcall TablePolAfterCancel(TDataSet *DataSet);
        void __fastcall TablePolBeforeInsert(TDataSet *DataSet);
   void __fastcall TablePolAfterEdit(TDataSet *DataSet);
   void __fastcall TableFaktAfterScroll(TDataSet *DataSet);
      
private:	// User declarations
public:		// User declarations
        __fastcall TDatabaze(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDatabaze *Databaze;
//---------------------------------------------------------------------------
#endif
