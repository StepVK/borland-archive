//$$---- Form HDR ----
//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <string.h>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <DBTables.hpp>
#include <Grids.hpp>
#include <time.h>
#include <Math.h>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TTimer *RenewalTimer;
	TTrayIcon *TrayIcon1;
	TTimer *IconTimer;
	TPopupMenu *TrayPMenu;
	TMenuItem *N1;
	TMenuItem *N2;
	TButton *Button1;
	TTable *Table1;
	TDataSource *DataSource1;
	TDBGrid *DBGrid1;
	TQuery *InsertQuery;
	TQuery *TempQuery;
	TQuery *UpdateQuery;
	TQuery *UpdateQuery2;
	TQuery *TempQuery2;
	TStringField *Table1Name;
	TIntegerField *Table1Score;
	TIntegerField *Table1UpdateTime;
	TIntegerField *Table1Change;
	TIntegerField *Table1Inactive;
	TQuery *MainQuery;
	TEdit *Edit1;
	TEdit *Edit2;
	TLabel *Label1;
	TLabel *Label3;
	TLabel *Label5;
	TButton *RefButton;
	TEdit *Edit3;
	TEdit *Edit4;
	TLabel *Label2;
	TLabel *Label4;
	TLabel *Label6;
	TDBGrid *DBGrid2;
	TDataSource *DataSource2;
	TCheckBox *CheckBox1;
	void __fastcall RenewalTimerTimer(TObject *Sender);
	void __fastcall IconTimerTimer(TObject *Sender);
	void __fastcall N1Click(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Table1CalcFields(TDataSet *DataSet);
	void __fastcall RefButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;

void GetBuffer(char*);
int pos(char*,char*);
int CheckBuf(char*);
void ParseBuffer(char*);
void RemoveDot(char*);
long StrToLong(char*);

//---------------------------------------------------------------------------
#endif
