//$$---- Form CPP ----
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
char chBufferLast[100000]="", chBufferCur[100000]="";
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void GetBuffer(char* chBuffer)
{
	if ( OpenClipboard(NULL) )//��������� ����� ������
	{

		HANDLE hData = GetClipboardData(CF_TEXT);//��������� ����� �� ������ ������
		GlobalUnlock(hData);//������������ ������
		char* chBuf= (char*)GlobalLock(hData);//��������� ������
		strncpy(chBuffer,chBuf,100000);
		GlobalUnlock(hData);//������������ ������
		CloseClipboard();//��������� ����� ������
	}
}

int pos(char* MainString,char* SubString)
{
	int i,j,k;
	for(i=0;MainString[i];i++)
	{
		for(j=0,k=i;MainString[k]==SubString[j]&&SubString[j];j++,k++);
	if(!SubString[j]) break;
	}
if (MainString[i]) return i;
return -1;
}

void __fastcall TForm1::RenewalTimerTimer(TObject *Sender)
{
	GetBuffer(chBufferCur);
	if ((strcmp(chBufferCur,chBufferLast))) {
		if (CheckBuf(chBufferCur)) {
			strcpy(chBufferLast,chBufferCur);
			Form1->TrayIcon1->Icon->LoadFromFile("active.ico");
			IconTimer->Enabled=true;
			ParseBuffer(chBufferLast);
		}
	}

}

int CheckBuf(char* chBuffer)
{
	if ((pos(chBuffer,"��������� 13")>-1)&&(pos(chBuffer,"������")>-1)&&(pos(chBuffer,"����������")>-1)) {
		return 1;
	}
	return 0;
}

void RemoveDot(char* chBuffer)
{
	char* tempaddr;
	char temp[10000]="";
	tempaddr=chBuffer;
	for (;chBuffer[0]!=0;) {
		if (chBuffer[0]!='.') {
			strncat(temp,chBuffer,1);
		}
		chBuffer=&chBuffer[1];
	}
	chBuffer=tempaddr;
	strcpy(chBuffer,temp);
}

long StrToLong(char* str)
{
	int k;
	long temp=0,osn=1;
	for(k=strlen(str)-1;k>=0;k--)
	{
		temp+=(str[k]-48)*osn;
		osn*=10;
	}
	return temp;
}

void ParseBuffer (char* chBuffer)
{
	char temp[10000];
	char temp2[10000];
	char newone[10000]="";
	char etalon[]="0123456789.";
	int i;
	strcpy(temp,&chBuffer[pos(chBuffer,"����")+6]);
	for(;pos(temp,"<")>-1;)
	{
		strcpy(temp2,&temp[pos(temp,"<")+3]);
	//���� ��� - ���, ������� �� �����.
		if ((pos(temp2,"mus1k ")>-1)&&(pos(temp2,"mus1k")<10)) {
			goto metka1;
		}
		strncat(newone,temp2,pos(temp2,"�������� ���������")-2);
		strcat(newone,"=");
	//���, ��� ����. ������ ������ � ������ � �������� ����.
		strcpy(temp,&temp2[pos(temp2,"�������� ���������")+15]);
		for (i=pos(temp,"\r")-1; strspn(&temp[i],etalon)!=0; i--);
		strncat(newone,&temp[i+1],pos(temp,"\r")-1-i);
		strcat(newone,",");
		metka1:
		strcpy(temp2,&temp[pos(temp,"\n")+2]);
		strcpy(temp,temp2);
	}
	RemoveDot(newone);
	//��� newone ���� �������� � �������!
	//���������...
	char name[60],tempscore[100];
	long score, curtime;
	for (;(i=pos(newone,"="))>-1;) {
		curtime=(long)time(NULL);
		strncpy(name,newone,i);
		name[i]=0;
		strcpy(temp,&newone[i+1]);
		strncpy(tempscore,temp,i=pos(temp,","));
		tempscore[i]=0;
		score=StrToLong(tempscore);
		strcpy(newone,&temp[i+1]);
//  ������ ��������. It's SQL time!
		Form1->TempQuery->Close();
		Form1->TempQuery->ParamByName("name")->AsString=name;
		if (!Form1->TempQuery->Prepared)
			Form1->TempQuery->Prepare();
		Form1->TempQuery->Open();
		if (Form1->TempQuery->Eof) {
		//������ � ����� ������ �� �������. ������� �� ������ ������ �����.
			Form1->InsertQuery->Close();
			Form1->InsertQuery->ParamByName("name")->AsString=name;
			Form1->InsertQuery->ParamByName("Score")->AsInteger=score;
			Form1->InsertQuery->ParamByName("Time")->AsInteger=curtime;
			if (!Form1->InsertQuery->Prepared)
				Form1->InsertQuery->Prepare();
			Form1->InsertQuery->ExecSQL();
			//����� ��� ����� �����. ��� �������� =) � - ���!
		}
		else
		{
		//������ � ����� ������ �������. ������� ������.
		//������ �� ��������� ������, ���� ���� � ����� � ����� ������ �����. (�� ���� �� �������)
			Form1->TempQuery2->Close();
			Form1->TempQuery2->ParamByName("Name")->AsString=name;
			Form1->TempQuery2->ParamByName("Score")->AsInteger=score;
			if (!Form1->TempQuery2->Prepared)
				Form1->TempQuery2->Prepare();
			Form1->TempQuery2->Open();
			if (Form1->TempQuery2->Eof) {
				//����, ������ �������. ������ ��� ����� ����, � ������������ ��� �������.
				Form1->UpdateQuery->Close();
				Form1->UpdateQuery->ParamByName("Name")->AsString=name;
				Form1->UpdateQuery->ParamByName("Score")->AsInteger=score;
				Form1->UpdateQuery->ParamByName("Time")->AsInteger=curtime;
				if (!Form1->UpdateQuery->Prepared)
					Form1->UpdateQuery->Prepare();
				Form1->UpdateQuery->ExecSQL();
			}
			else
			{
			//�����, ������ ������� � ���������! ���! ������ ��� ����� ���� (��� ����� �����������), � ������� ����� ���������� =)
				Form1->UpdateQuery2->Close();
				Form1->UpdateQuery2->ParamByName("Name")->AsString=name;
				Form1->UpdateQuery2->ParamByName("Score")->AsInteger=score;
				Form1->UpdateQuery2->ParamByName("Time")->AsInteger=curtime;
				if (!Form1->UpdateQuery2->Prepared)
					Form1->UpdateQuery2->Prepare();
				Form1->UpdateQuery2->ExecSQL();
			}
			Form1->TempQuery2->Close();
		}
	Form1->TempQuery->Close();
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::IconTimerTimer(TObject *Sender)
{
	Form1->TrayIcon1->Icon->LoadFromFile("standard.ico");
	IconTimer->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N1Click(TObject *Sender)
{
	Form1->Close();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{
	Form1->Show();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	Form1->Hide();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormCreate(TObject *Sender)
{
	Table1->Active=true;
	Form1->MainQuery->Close();
	Form1->MainQuery->SQL->Clear();
	Form1->MainQuery->SQL->Add("SELECT Name as ���, Score FROM Scores");
	Form1->MainQuery->SQL->Add("Where Score>=:minscore and Score<=:maxscore  and (UpdateTime-Change)>=:mininactive and (UpdateTime-Change)<=:maxinactive");
	Form1->MainQuery->ParamByName("minscore")->AsInteger=0;
	Form1->MainQuery->ParamByName("maxscore")->AsInteger=10000000;
	Form1->MainQuery->ParamByName("mininactive")->AsInteger=0;
	Form1->MainQuery->ParamByName("maxinactive")->AsInteger=360000;
	if (!Form1->MainQuery->Prepared)
		Form1->MainQuery->Prepare();
	Form1->MainQuery->Open();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	Table1->Active=false;	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Table1CalcFields(TDataSet *DataSet)
{
	Table1->FieldByName("Inactive")->Value = Table1->FieldByName("Change")->Value - Table1->FieldByName("UpdateTime")->Value;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RefButtonClick(TObject *Sender)
{
	if (Form1->CheckBox1->Checked) {
	//��������� �� �����
		Form1->MainQuery->Close();
		Form1->MainQuery->SQL->Clear();
		Form1->MainQuery->SQL->Add("SELECT Name as ���, Score FROM Scores");
		Form1->MainQuery->SQL->Add("Where Score>=:minscore and Score<=:maxscore  and (UpdateTime-Change)>=:mininactive and (UpdateTime-Change)<=:maxinactive");
		Form1->MainQuery->SQL->Add("ORDER BY Score DESC");
	}
	else
	{
	//��������� �� ����� (�� �������)
		Form1->MainQuery->Close();
		Form1->MainQuery->SQL->Clear();
		Form1->MainQuery->SQL->Add("SELECT Name as ���, Score FROM Scores");
		Form1->MainQuery->SQL->Add("Where Score>=:minscore and Score<=:maxscore  and (UpdateTime-Change)>=:mininactive and (UpdateTime-Change)<=:maxinactive");
	}
	Form1->MainQuery->ParamByName("minscore")->AsInteger=StrToInt(Edit1->Text);
	Form1->MainQuery->ParamByName("maxscore")->AsInteger=StrToInt(Edit2->Text);
	Form1->MainQuery->ParamByName("mininactive")->AsInteger=(StrToInt(Edit3->Text)*3600);
	Form1->MainQuery->ParamByName("maxinactive")->AsInteger=(StrToInt(Edit4->Text)*3600);
	if (!Form1->MainQuery->Prepared)
		Form1->MainQuery->Prepare();
	Form1->MainQuery->Open();

}
//---------------------------------------------------------------------------

