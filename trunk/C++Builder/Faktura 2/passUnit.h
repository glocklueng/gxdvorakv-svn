//----------------------------------------------------------------------------
#ifndef passUnitH
#define passUnitH
//----------------------------------------------------------------------------
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>

//----------------------------------------------------------------------------
class TPasswordForm : public TForm
{
__published:
	TLabel *Label1;
	TEdit *Password;
	TButton *OKBtn;
	TButton *CancelBtn;
   void __fastcall OKBtnClick(TObject *Sender);
   void __fastcall CancelBtnClick(TObject *Sender);
   void __fastcall FormShow(TObject *Sender);
private:
public:
	virtual __fastcall TPasswordForm(TComponent* AOwner);
   void __fastcall setSource(TForm *Source);
};
//----------------------------------------------------------------------------
extern PACKAGE TPasswordForm *PasswordForm;
//----------------------------------------------------------------------------
#endif    
