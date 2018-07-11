//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
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
void __fastcall TForm1::FuckOFF1Click(TObject *Sender)
{
Form1->Close();	
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{
Form1->Hide();	
}
//---------------------------------------------------------------------------
void __fastcall TForm1::temp1Click(TObject *Sender)
{
Form1->Hide();	
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
if (Form1->Visible) {
    Form1->Hide();
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        hInternet = InternetOpen(
                                 "The Browser",
                                 INTERNET_OPEN_TYPE_PRECONFIG,
                                 NULL,NULL,0
                                );
        if (hInternet == NULL)
        MessageBox(0,"Ошибка инициализации интернета","AHTUNG!",0);	
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
        ::InternetCloseHandle(hInternet);	
}
//---------------------------------------------------------------------------
