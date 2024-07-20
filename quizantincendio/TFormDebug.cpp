/******************************************************************************
	NAME:			TFormDebug.cpp
	MAIN PROJECT:   Quiz Antincendio - Quiz per il Corso Sicurezza Antincendio
	DESCRIPTION:	Debug Form
	EXETYPE:        For 32 & 64 bit Windows platforms.

	AUTHOR:         (C) 2024 Francesco Settembrini
					francesco.settembrini@poliba.it

	DATA:           July 2024
	RELEASE:        1.0.0
	LAST UPDATE:

	COMPILER:       Borland/CodeGear/Embarcadero Rad Studio XE.

	DETAILS:

	NOTES:
	  - Il presente lavoro e` protetto dalle leggi internazionali
	  sui diritti d'autore. Nessuna parte puo` essere copiata
	  senza il permesso esplicito dell'autore.

	  - This work is protected by international laws on copy-rights.
	  No parts can be copied without explicit permission of the author.

******************************************************************************/

#include <vcl.h>
#pragma hdrstop

#include "TFormDebug.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDebug* FormDebug[FORMSDEBUG];


//---------------------------------------------------------------------------
//	SCOPO:	Costruttore
//---------------------------------------------------------------------------
__fastcall TFormDebug::TFormDebug(TComponent* Owner) : TForm(Owner)
{
	;
}

//---------------------------------------------------------------------------
//  SCOPO:  Clear the debug form
//---------------------------------------------------------------------------
void __fastcall TFormDebug::Clear()
{
	RichEdit->Lines->Clear();
}

//---------------------------------------------------------------------------
//  SCOPO:  Mostra un messaggio nella listbox
//---------------------------------------------------------------------------
void __fastcall TFormDebug::Add(AnsiString Msg)
{
	if( this->Visible )
    {
		RichEdit->Lines->Add(Msg);
    }
}

//---------------------------------------------------------------------------
//  SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDebug::Add(TStringList* pList)
{
	if( this->Visible )
    {
        for(int i=0; i<pList->Count; i++)
            RichEdit->Lines->Add(pList->Strings[i]);
	}
}

//---------------------------------------------------------------------------
//  SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDebug::ActionsClearClick(TObject *Sender)
{
	Clear();

}

//---------------------------------------------------------------------------
//  SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDebug::FileSaveAsClick(TObject *Sender)
{
	if( SaveDialog->Execute() == mrOk )
	{
		RichEdit->Lines->SaveToFile( SaveDialog->FileName );
	}
}

//---------------------------------------------------------------------------
//  SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDebug::SetOpMode(enDebugMode nOpMode)
{
	if( dmText == nOpMode )
    {
		Image->Visible = false;
        RichEdit->Visible = true;
    }
	else if ( dmBitmap == nOpMode )
    {
    	Image->Visible = true;
		RichEdit->Visible = false;
    }
    else
    {
		Image->Visible = false;
        RichEdit->Visible = true;
    }
}

//---------------------------------------------------------------------------
//  SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDebug::Print(TBitmap* pBmp)
{
    assert(pBmp);
	assert(Image);

	int nW = pBmp->Width;
    int nH = pBmp->Height;

    TRect Rect = TRect(0, 0, nW, nH);
	Image->Picture->Bitmap->Width = nW;
    Image->Picture->Bitmap->Height = nH;

    Image->Canvas->CopyRect(Rect, pBmp->Canvas, Rect);
	Image->Update();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDebug::ext1Click(TObject *Sender)
{
	SetOpMode(dmText);
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDebug::Images1Click(TObject *Sender)
{
	SetOpMode(dmBitmap);
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDebug::Print(TVecInt& Ints)
{
	AnsiString strTemp;

	for(int i=0; i<Ints.size(); i++)
    {
    	strTemp.printf("%d", Ints[i]);
		Add(strTemp);
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDebug::Print(TVecDBRecords& DB)
{
	assert(FormDebug);

    for(int i=0; i<DB.size(); i++)
    {
        this->Add(AnsiString(DB[i].strQuestion));
        this->Add(DB[i].strAnswers[0]);
        this->Add(DB[i].strAnswers[1]);
        this->Add(DB[i].strAnswers[2]);
        this->Add("");
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDebug::Print(TVecPtrXDBRecords& Records)
{
	assert(FormDebug);

    for(int i=0; i<Records.size(); i++)
    {
        this->Add(AnsiString(Records[i]->pDBRecord->strQuestion));
        this->Add(Records[i]->pDBRecord->strAnswers[0]);
        this->Add(Records[i]->pDBRecord->strAnswers[1]);
        this->Add(Records[i]->pDBRecord->strAnswers[2]);
		this->Add( Records[i]->bIsDirty ? "IsDirty = yes" : "IsDirty = no" );
        this->Add("");
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDebug::Print(TXDBRecord* pRecord)
{
	assert(pRecord);

	this->Add( AnsiString(pRecord->pDBRecord->strQuestion) );
	this->Add( AnsiString(pRecord->pDBRecord->strAnswers[0]) );
	this->Add( AnsiString(pRecord->pDBRecord->strAnswers[1]) );
	this->Add( AnsiString(pRecord->pDBRecord->strAnswers[2]) );

    this->Add("");
}

//---------------------------------------------------------------------------

