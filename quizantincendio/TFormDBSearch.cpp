/******************************************************************************
	NAME:			TFormDBRecord.cpp
	MAIN PROJECT:   Quiz Antincendio - Quiz per il Corso Sicurezza Antincendio
	DESCRIPTION:	Ricerca nel database per parole chiave
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

#include "TFormMain.h"
#include "TDataBanker.h"
#include "TFormDBSearch.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDBSearch *FormDBSearch;

//---------------------------------------------------------------------------

enum enSearchMode { smQuestions=1, smAnswers=2, smQuestionsAndAnswers=1+2 };

struct TagSMChoice {
	enSearchMode nMode;
    AnsiString strDescr;
} g_SMChoices[] =
{
	{ smQuestions, "Ricerca solo nelle domande la parola chiave specificata" },
    { smAnswers, "Ricerca solo nelle risposte la parola chiave specificata" },
    { smQuestionsAndAnswers, "Ricerca sia nelle domande che nelle risposte la parola chiave specificata" }
};


//---------------------------------------------------------------------------
//	SCOPO:	Costruttore
//---------------------------------------------------------------------------
__fastcall TFormDBSearch::TFormDBSearch(TComponent* Owner) : TForm(Owner)
{
	;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBSearch::FormCreate(TObject *Sender)
{
	this->Caption = AnsiString(APPNAME) +
    	" : Ricerca nel database i records contenenti la parola chiave specificata";

	this->BorderStyle = bsSizeable;
	this->Position = poScreenCenter;
	this->Constraints->MinWidth = 640;
    this->Constraints->MinHeight = 380;
	this->Width = 800;
    this->Height = 600;

	EditKeyword->Text = "estintore";

	RichEdit->Font->Size = 12;

    for(int i=0; i< sizeof(g_SMChoices)/sizeof(g_SMChoices[0]); i++)
    {
		ComboBoxSearch->Items->AddObject(
        	g_SMChoices[i].strDescr , (TObject*)(void*) g_SMChoices[i].nMode );
    }
	ComboBoxSearch->ItemIndex = 0;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBSearch::ButtonOkClick(TObject *Sender)
{
	ModalResult = mrOk;
    Visible = false;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBSearch::ButtonSearchClick(TObject *Sender)
{
	DoSearch();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBSearch::EditKeywordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if( Key == VK_RETURN )
    {
		DoSearch();
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBSearch::FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight,
          bool &Resize)
{
	assert(ButtonOk);

    ButtonOk->Left = (this->Width - ButtonOk->Width) / 2;
}

//---------------------------------------------------------------------------
//	SCOPO:	Previene l'uso di Ctrl-C , Ctrl-V, Ctrl-X dal RichEdit
//---------------------------------------------------------------------------
void __fastcall TFormDBSearch::RichEditSelectionChange(TObject *Sender)
{
	if( RichEdit->SelLength > 0 ) RichEdit->SelLength = 0;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBSearch::DoSearch()
{
	assert(FormMain);
	assert(DataBanker);

	AnsiString Labels[MAXANSWERS] = {"a", "b", "c", "d", "e" };

	TVecInt SelQuestions, SelAnswers;

	if( int(ComboBoxSearch->Items->Objects[ComboBoxSearch->ItemIndex]) & smQuestions )
    {
		DataBanker->SearchInQuestions( EditKeyword->Text, SelQuestions);
    }

	if( int(ComboBoxSearch->Items->Objects[ComboBoxSearch->ItemIndex]) & smAnswers)
    {
		DataBanker->SearchInAnswers( EditKeyword->Text, SelAnswers );
    }

	TVecInt SelIndices;
    TUtils::MergeUnique(SelQuestions, SelAnswers, SelIndices);

	TVecDBRecords SelRecs;
    DataBanker->GetRecords(SelIndices, SelRecs);

	RichEdit->Clear();
	for(int i=0; i<SelRecs.size(); i++)
    {
        RichEdit->Lines->Add("");
        RichEdit->Lines->Add( AnsiString("Domanda: ") + AnsiString(SelRecs[i].nId) );
        RichEdit->Lines->Add( SelRecs[i].strQuestion );

												// ricompone le risposte :
                                                // antepone un * per la risposta esatta
                                                // anteopne a, b, c ... a ciascuna risposta
        for(int j=0; j<MAXANSWERS; j++)
        {
			if( AnsiString(SelRecs[i].strAnswers[j]).Length() )
            {
                AnsiString strTemp = SelRecs[i].bAnswers[j] ? "*" : " ";
                RichEdit->Lines->Add( strTemp + Labels[j] + ") " + AnsiString(SelRecs[i].strAnswers[j]) );
			}
        }
    }

    AnsiString strTemp;
    strTemp.printf("Trovati: %d record(s)", SelRecs.size());
    StatusBar->Panels->Items[0]->Text = strTemp;
}

//---------------------------------------------------------------------------

