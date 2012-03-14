//---------------------------------------------------------------------------

#ifndef poznamkaUnitH
#define poznamkaUnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DBCtrls.hpp>
//---------------------------------------------------------------------------
class TPoznamkaForm : public TForm
{
__published:	// IDE-managed Components
   TDBMemo *DBMemo1;
   TLabel *Label9;
   TButton *OKBtn;
   void __fastcall OKBtnClick(TObject *Sender);
   void __fastcall FormDeactivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TPoznamkaForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPoznamkaForm *PoznamkaForm;
//---------------------------------------------------------------------------
#endif
