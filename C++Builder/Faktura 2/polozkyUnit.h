//---------------------------------------------------------------------------

#ifndef polozkyUnitH
#define polozkyUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TPolozkyForm : public TForm
{
__published:	// IDE-managed Components
        TDBGrid *DBGridPolozky;
        TGroupBox *GroupBox1;
        TButton *KonecBtn;
        TLabel *CisloFakturyLabel;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *pocetPolozek;
        TLabel *Label4;
        TLabel *cenaCelkem;
        TPopupMenu *PopupMenu1;
        TMenuItem *kg1;
        TMenuItem *m;
        TMenuItem *ks1;
        TDBNavigator *DBNavigator1;
        TGroupBox *GroupBoxFaktury;
        TDBGrid *DBGridFaktury;
        TButton *EditBtn;
   TGroupBox *GroupBox2;
   TDBMemo *DBMemoInfo;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall kg1Click(TObject *Sender);
        void __fastcall mClick(TObject *Sender);
        void __fastcall ks1Click(TObject *Sender);
        void __fastcall KonecBtnClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall EditBtnClick(TObject *Sender);
   void __fastcall DBMemoInfoDblClick(TObject *Sender);
   void __fastcall DBMemoInfoExit(TObject *Sender);
private:	// User declarations
public:		// User declarations
        int CisloFaktury;
        int lastIdPolozky;
        int cisloPolozky;
        float SAZBA_DPH;
__fastcall TPolozkyForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPolozkyForm *PolozkyForm;
//---------------------------------------------------------------------------
#endif
