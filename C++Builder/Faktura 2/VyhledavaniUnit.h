//---------------------------------------------------------------------------

#ifndef VyhledavaniUnitH
#define VyhledavaniUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TVyhledavaniForm : public TForm
{
__published:	// IDE-managed Components
   TDBGrid *DBGridOdb;
   TDBGrid *DBGridFaktury;
   TGroupBox *GroupBoxFakt;
   TButton *StornoBtn;
   TButton *ZobrazitBtn;
   TGroupBox *GroupBoxOdb;
   TDBNavigator *DBNavigator1;
   TDBNavigator *DBNavigator2;
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall StornoBtnClick(TObject *Sender);
   void __fastcall ZobrazitBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TVyhledavaniForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TVyhledavaniForm *VyhledavaniForm;
//---------------------------------------------------------------------------
#endif
