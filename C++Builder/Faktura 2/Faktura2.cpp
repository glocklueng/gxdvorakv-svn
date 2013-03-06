//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Faktura2.res");
USEFORM("mainUnit.cpp", MainForm);
USEFORM("polozkyUnit.cpp", PolozkyForm);
USEFORM("data.cpp", Databaze); /* TDataModule: File Type */
USEUNIT("fakturaTisk.cpp");
USEFORM("dodavatelUnit.cpp", DodavatelForm);
USEFORM("passUnit.cpp", PasswordForm);
USEFORM("tiskDialogUnit.cpp", TiskDialogForm);
USEFORM("poznamkaUnit.cpp", PoznamkaForm);
USEFORM("VyhledavaniUnit.cpp", VyhledavaniForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Faktura2.1";
       Application->CreateForm(__classid(TMainForm), &MainForm);
       Application->CreateForm(__classid(TPolozkyForm), &PolozkyForm);
       Application->CreateForm(__classid(TDatabaze), &Databaze);
       Application->CreateForm(__classid(TDodavatelForm), &DodavatelForm);
       Application->CreateForm(__classid(TPasswordForm), &PasswordForm);
       Application->CreateForm(__classid(TTiskDialogForm), &TiskDialogForm);
       Application->CreateForm(__classid(TPoznamkaForm), &PoznamkaForm);
       Application->CreateForm(__classid(TVyhledavaniForm), &VyhledavaniForm);
       Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
