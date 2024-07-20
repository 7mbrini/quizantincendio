/******************************************************************************
	NAME:			TDlgSetup.cpp
	MAIN PROJECT:   Quiz Antincendio - Quiz per il Corso Sicurezza Antincendio
	DESCRIPTION:	Setup Dialog
	EXETYPE:        For 32 & 64 bit Windows platforms.

	AUTHOR:         (C) 2016 Francesco Settembrini
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

#include "TDlgSetup.h"
#include "commdefs.h"

#include "TFormDebug.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDlgSetup *DlgSetup;


//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
__fastcall TDlgSetup::TDlgSetup(TComponent* Owner) : TForm(Owner)
{
	m_nMaxQuestions = MAXQUESTIONS;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TDlgSetup::Reset()
{
	m_nMaxQuestions = MAXQUESTIONS;
	AnsiString strTemp;
    strTemp.printf("%d", m_nMaxQuestions);
    EditQuizCount->Text = strTemp;

    CheckBoxAutoScroll->Checked = true;
    CheckBoxCorrectInstantly->Checked = true;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TDlgSetup::ButtonOkClick(TObject *Sender)
{
	ValidateInput();

	ModalResult = mrOk;
    Visible = false;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TDlgSetup::FormCreate(TObject *Sender)
{
	this->Caption = AnsiString(APPNAME) + ":  Impostazione delle preferenze";

	Position = poScreenCenter;
	this->BorderStyle = bsSingle;

    EditQuizCount->Text = NUMQUESTIONS;
    CheckBoxAutoScroll->Checked = false;
    CheckBoxCorrectInstantly->Checked = false;


                                        	// utilizzo la proprieta` "Object"
                                        	// per memorizzare il TopicId
    ComboBoxChoice->Clear();

    ComboBoxChoice->Items->AddObject(
    	AnsiString("Selezione casuale delle domande"),
        (TObject*) qmSelectQuestionsRandomly);

    ComboBoxChoice->Items->AddObject(
    	AnsiString("Selezione sequenziale delle domande"),
        (TObject*) qmSelectQuestionsSequentially);

    ComboBoxChoice->Items->AddObject(
    	AnsiString("Simulazione d'esame (15 domande, massimo 5 errori, 30 min di tempo)"),
        (TObject*) qmExamSimulation);

    ComboBoxChoice->ItemIndex = 0;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
int __fastcall TDlgSetup::GetCount()
{
	return EditQuizCount->Text.ToInt();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TDlgSetup::EditQuizCountKeyDown(TObject *Sender,
	WORD &Key, TShiftState Shift)
{
	if( Key == VK_RETURN )
    {
		ValidateInput();
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TDlgSetup::ValidateInput()
{
	try
    {
        int nCount = EditQuizCount->Text.ToInt();

        if( nCount < MINQUESTIONS )
        {
            EditQuizCount->Text = MINQUESTIONS;

            AnsiString strTemp;
            strTemp.printf("Il numero minimo di domande per quiz e' %d !", MINQUESTIONS);
            ::MessageBoxA(0, strTemp.c_str(), "Errore: ", MB_OK | MB_TOPMOST | MB_ICONERROR );
        }

        if( nCount > m_nMaxQuestions )
        {
            EditQuizCount->Text = m_nMaxQuestions;

            AnsiString strTemp;
            strTemp.printf("Il numero massimo di domande per quiz e' %d !", m_nMaxQuestions);
            ::MessageBoxA(0, strTemp.c_str(), "Errore: ", MB_OK | MB_TOPMOST | MB_ICONERROR );
        }
	}
	catch(Exception& Err)
    {
		::MessageBox(0, Err.Message.w_str(),
            L"Error: ", MB_OK | MB_TOPMOST | MB_ICONERROR );
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TDlgSetup::EnableControls(bool bEnable)
{
	ComboBoxChoice->Enabled = bEnable;
	EditQuizCount->Enabled = bEnable;

    LabelChoice->Enabled = bEnable;
    LabelQuizCount->Enabled = bEnable;

    CheckBoxCorrectInstantly->Enabled = bEnable;

    if( bEnable == false )
    {
		ComboBoxChoice->ItemIndex = 0;
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TDlgSetup::ComboBoxChoiceChange(TObject *Sender)
{
#ifdef _DEBUG_
	assert(FormDebug);

    AnsiString strTemp;
    int nTopicId = GetTopicId();
	int nItem = ComboBoxTopicId->ItemIndex;

    strTemp.printf("Item= %d, Topic= %d", nItem, nTopicId);
    FormDebug[0]->Add(strTemp);
#endif
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TDlgSetup::SetMaxQuestions(int nMaxQuestions)
{
	m_nMaxQuestions = nMaxQuestions;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
enQuizModality __fastcall TDlgSetup::GetQuizModality()
{
    enQuizModality nResult = qmNone;

    int nChoice = ComboBoxChoice->ItemIndex;

    switch( nChoice )
    {
        case 0: nResult = qmSelectQuestionsRandomly; break;
        case 1: nResult = qmSelectQuestionsSequentially; break;
        case 2: nResult = qmExamSimulation; break;
    }


    return nResult;
}

//---------------------------------------------------------------------------


