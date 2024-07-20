/******************************************************************************
	NAME:			TFormMain.cpp
	MAIN PROJECT:   Quiz Antincendio - Quiz per il Corso Sicurezza Antincendio
	DESCRIPTION:	Main Form
	EXETYPE:        For 32 & 64 bit Windows platforms.
	COMPILER:       Borland/CodeGear/Embarcadero Rad Studio XE.

	AUTHOR:         (C) 2024 Francesco Settembrini
					francesco.settembrini@poliba.it
					http://www.francescosettembrini.it

	DATA:           July 2024
	RELEASE:        1.0.0


	DETAILS:
        Quiz di preparazione alla prova teorica per il corso sulla
        Sicurezza Antincendio svoltosi presso il Comando dei Vigili
        del Fuoco di Bari Mungivacca nei mesi di maggio/giugno 2024
        per conto del Politecnico di Bari.

	NOTES:
	  - Il presente lavoro e` protetto dalle leggi internazionali
	  sui diritti d'autore. Nessuna parte puo` essere copiata
	  senza il permesso esplicito dell'autore.

	  - This work is protected by international laws on copy-rights.
	  No parts can be copied without explicit permission of the author.

******************************************************************************/

#include <vcl.h>
#include <jpeg.hpp>
#pragma hdrstop

#include "TFormMain.h"
#include "TDlgAbout.h"
#include "TDlgSetup.h"
#include "TFormDebug.h"
#include "TFormDBSearch.h"
#include "TFormDBRecord.h"

#include "TDatabanker.h"

#include "commdefs.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;


//---------------------------------------------------------------------------
//	SCOPO:	Costruttore
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner) : TForm(Owner)
{
	m_bIsTooLate = false;
	m_nScrollSize = m_nScrollPos = 0;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	this->Caption = APPNAME
		" - (C) 2024 Francesco Settembrini - http://www.francescosettembrini.it ";

	this->Left = 8;
    this->Top = 4;
	this->Width = APPWIDTH;
	this->Height = APPHEIGHT;
	this->Constraints->MinWidth = APPWIDTH;
	this->Constraints->MinHeight = APPHEIGHT;

#ifndef _DEBUG_
    this->Position = poScreenCenter;
#endif

	Image->Visible = true;
	ScrollBar->Visible = false;

    PanelScroller->Visible = false;
	PanelScroller->Color = clBtnFace;

    PanelScrollClient->BorderStyle = bsNone;
    PanelScrollClient->BorderWidth = 0;
    PanelScrollClient->BevelOuter = bvNone;
	PanelScrollClient->Align = alClient;

#ifdef _DEBUG_
	int nWDebug = 380;
    for(int i=0; i<FORMSDEBUG; i++)
    {
        FormDebug[i] = new TFormDebug(this);
        assert(FormDebug[i]);
        FormDebug[i]->Left = this->Left + this->Width + 0;
        FormDebug[i]->Top = this->Top + (this->Height/FORMSDEBUG)*i;
        FormDebug[i]->Width = nWDebug;
        FormDebug[i]->Height = this->Height/FORMSDEBUG;
    FormDebug[i]->Caption = AnsiString("Debug :  ") + AnsiString(i);

#ifdef _DEBUG_
	FormDebug[i]->Visible = true;
#else
	FormDebug[i]->Visible = false;
#endif
        if( !FormDebug[i]->Visible ) this->Position = poScreenCenter;
    }
#endif

	DataBanker = new TDataBanker(this);
    assert(DataBanker);

	FormDBSearch = new TFormDBSearch(this);
    assert(FormDBSearch);

	DlgSetup = new TDlgSetup(this);
    assert(DlgSetup);
	DlgSetup->Visible = false;

	DlgAbout = new TDlgAbout(this);
    assert(DlgAbout);
	DlgAbout->Visible = false;

	SetupPagedDBRecords();
										// disattiva alcuni elementi di interfaccia
	EnableControls(false);
										// inizializza il generatore di numeri casuali
    srand(::GetCurrentTime());
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormShow(TObject *Sender)
{
#ifdef _DEBUG_
	static bool bOneShot = false;
	if( !bOneShot ) debug_LoadDB();
    bOneShot = true;
#endif
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::debug_LoadDB()
{
#ifdef _DEBUG_
	assert(DataBanker);

    Reset();

    AnsiString strFileName = AnsiString(DATAPATH) + QUIZDBFILE;

    if( LoadDB(strFileName) )
    {
        EnableControls(true);
        MakeNewQuiz();
    }
#endif
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::EnableControls(bool bEnable)
{
	MainMenu->Items->Items[1]->Enabled = bEnable;
	MainMenu->Items->Items[2]->Enabled = bEnable;
	MainMenu->Items->Items[3]->Enabled = bEnable;

	SpeedButtonSetup->Enabled = bEnable;
	SpeedButtonNewQuiz->Enabled = bEnable;
    SpeedButtonResults->Enabled = bEnable;
	SpeedButtonFind->Enabled = bEnable;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::FileExitClick(TObject *Sender)
{
	Exit();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::Reset()
{
	TimerStop();

	DeleteRecords();

    DlgSetup->Reset();
	DataBanker->Clear();
	m_ErrorList.clear();
	PanelScroller->Visible = false;
	//PanelScrollClient->Visible = false;

	m_bIsTooLate = false;

	ShowInfo("");

	ResetScrolling();

}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::ResetScrolling()
{
	m_nScrollSize = m_nScrollPos = 0;
	ScrollBar->Position = m_nScrollPos;
	ScrollBar->Min = 0;
    ScrollBar->Max = 0;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::DeleteRecords()
{
	for(int i=0; i<m_pSelRecords.size(); i++)
    {
		delete m_pSelRecords[i];
    }

	m_pSelRecords.clear();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::ClearPagedRecords()
{
	for(int i=0; i<m_pPagedRecords.size(); i++)
    {
		m_pPagedRecords[i]->Clear();
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonOpenDBClick(TObject *Sender)
{
	OpenDB();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::OpenDB()
{
	Reset();

	if( LoadDB() )
    {
		MakeNewQuiz();
		EnableControls(true);
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
bool __fastcall TFormMain::LoadDB()
{
	assert(DlgSetup);
	assert(DataBanker);

	bool bResult = false;

    if( OpenDBDialog->Execute() == mrOk )
    {
        Reset();
		bResult = LoadDB( OpenDBDialog->FileName );
    }

    return bResult;
}

//---------------------------------------------------------------------------
//	SCOPO:	Restituisce true se e` una sessione di simulazione d'esame
//---------------------------------------------------------------------------
bool __fastcall TFormMain::IsExamSimulation()
{
	assert(DlgSetup);

    return DlgSetup->GetQuizModality() == qmExamSimulation;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
bool __fastcall TFormMain::LoadDB(AnsiString strFileName)
{
	bool bResult = false;

    if( DataBanker->LoadDB(strFileName) )
    {
        ScrollBar->Visible = true;
        PanelScroller->Visible = true;

        DlgSetup->EnableControls(true);
        DlgSetup->SetMaxQuestions(DataBanker->GetDBSize());

        AnsiString strTemp;
		strFileName = ExtractFileName(strFileName);

        strTemp.printf(" Database  \"%s\"  loaded,  %d records.",
        	strFileName.c_str(), DataBanker->GetDBSize());
        ShowStatus(strTemp);

        bResult = true;
    }
    else
    {
        ShowError(ERRBADDBFORMAT);
    }

    return bResult;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonNewQuizClick(TObject *Sender)
{
	MakeNewQuiz();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::ShowError(int nError)
{
	UnicodeString strError = "Errore :  ";

	switch(nError)
    {
		case ERRBADDBFORMAT: strError += "Formato di database non valido"; break;
		case ERREMPTYDB: strError += "Il database e' vuoto"; break;
        case ERREMPTYSEL: strError += "La selezione delle domande e` vuota"; break;
        case ERREMPTYERRLIST: strError += "La lista delle risposte errate e` vuota"; break;
    }

    ::MessageBox(0, strError.w_str(), WAPPNAME, MB_OK | MB_ICONWARNING);
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::HelpAboutClick(TObject *Sender)
{
	AboutBox();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::AboutBox()
{
    DlgAbout->ShowModal();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonAboutClick(TObject *Sender)
{
	AboutBox();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::Exit()
{
	if( ::MessageBox(0,
    	L"          Confermate di voler Uscire ?",
        WAPPNAME,
	    MB_YESNO | MB_ICONEXCLAMATION | MB_TOPMOST) == ID_YES )
    {
		PostQuitMessage(0);
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::FileOpenDatabaseClick(TObject *Sender)
{
	OpenDB();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::SettingsSetupClick(TObject *Sender)
{
	DoSettings();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::NewQuizClick(TObject *Sender)
{
	MakeNewQuiz();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonSetupClick(TObject *Sender)
{
	if( DataBanker->IsDBLoaded() )
    {
		DoSettings();
    }
    else
    {
		ShowError(ERREMPTYDB);
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::DoSettings()
{
	DlgSetup->ShowModal();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::ShowStatus(AnsiString strStatus)
{
	StatusBar->Panels->Items[0]->Text = strStatus;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonResultsClick(TObject *Sender)
{
	ShowTheResults();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::ShowTheResults()
{
	assert(DataBanker);

    if( DataBanker->IsDBLoaded() )
    {
        TimerStop();
        ShowResults();

        m_bIsTooLate = true;

		for(int i=0; i<m_pPagedRecords.size(); i++)
        {
			m_pPagedRecords[i]->EnableCheckBoxes(false);
        }
	}
    else
    {
		ShowError(ERREMPTYDB);
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::ShowInfo(AnsiString strInfo, TColor Color)
{
    LabelInfo->Font->Color = Color;
    LabelInfo->Caption = strInfo;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::AddError(TVecInt& ErrorList, int nDBIndex)
{
	bool bIsUnique = true;

    for(int i=0; i<ErrorList.size(); i++)
    {
		if( ErrorList[i] == nDBIndex )
        {
			bIsUnique = false;
            break;
        }
    }

    if( bIsUnique )
    {
		ErrorList.push_back(nDBIndex);
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::ShowResults()
{
	assert(DlgSetup);

	assert(m_pSelRecords.size());

	int nRightAnswers = 0, nErrors = 0;
	int nQuestions = m_pSelRecords.size();

	m_ErrorList.clear();

	for(int i=0; i<m_pPagedRecords.size(); i++)
    {
		m_pPagedRecords[i]->CheckTheAnswer();
    }

	for(int i=0; i<m_pSelRecords.size(); i++)
    {
		if( m_pSelRecords[i]->CheckTheAnswer() )
        {
			nRightAnswers++;
        }
		else
        {
			nErrors++;
			AddError(m_ErrorList, m_pSelRecords[i]->pDBRecord->nId);
        }
    }

	double Percent = double(nRightAnswers) / double(nQuestions) * 100.0f;

    AnsiString strTemp;
    strTemp.printf("Risultato: %d risposte esatte e %d errori su %d domande [%3.0f %% ].",
    	nRightAnswers, nErrors, nQuestions, Percent );

	TColor TheColor;

	if( Percent >= QUIZTHRESHOLD )
    {
		TheColor = clBlue;
    	strTemp += " Test SUPERATO.";
    }
    else
    {
		TheColor = clRed;
    	strTemp += " Test NON SUPERATO.";
    }

    ShowInfo(strTemp, TheColor);
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerStart()
{
	m_StartTime = TDateTime::CurrentTime();
	Timer->Enabled = true;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerStop()
{
	Timer->Enabled = false;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerUpdate()
{
	TDateTime CurTime = TDateTime::CurrentTime();
    TDateTime DTime  = CurTime - m_StartTime;

    unsigned short nHours, nMins, nSecs, nMSecs;
    DTime.DecodeTime(&nHours, &nMins, &nSecs, &nMSecs);

    AnsiString strTemp;
    strTemp.printf("%02d : %02d : %02d", nHours, nMins, nSecs);

    ShowInfo(strTemp);
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::TimerTimer(TObject *Sender)
{
	TimerUpdate();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::QuizShowResultsClick(TObject *Sender)
{
	ShowTheResults();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormMouseWheel(TObject *Sender, TShiftState Shift,
	int WheelDelta, TPoint &MousePos, bool &Handled)
{
	assert(DataBanker);

    Handled = true; // vip!

	if( DataBanker->IsDBLoaded() )
    {
		if( ::fabs(double(WheelDelta)) != 0)
        {
        	if( WheelDelta/::fabs(double(WheelDelta)) < 0)
            {
				if( Shift.Contains(ssCtrl) )
                {
                    ScrollPageDown();
                }
                else
                {
                    ScrollDown();
                }
            }
            else
            {
				if( Shift.Contains(ssCtrl) )
                {
                    ScrollPageUp();
                }
                else
                {
                    ScrollUp();
                }
            }
		}
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
int __fastcall TFormMain::GetPos(TVecPtrFormDBRecords& PagedRecords, TFormDBRecord *pDBRecord)
{
	int nPos = -1;

	for(int i=0; i<PagedRecords.size(); i++)
    {
		if( PagedRecords[i] == pDBRecord )
        {
        	nPos = i;
            break;
        }
    }

    return nPos;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::ScrollUp()
{
	m_nScrollPos -= LINESCROLL;

    if( m_nScrollPos < 0 ) m_nScrollPos = 0;

	UpdateTheScroll();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::ScrollDown()
{
	m_nScrollPos += LINESCROLL;

    if( m_nScrollPos >= m_nScrollSize - 1 ) m_nScrollPos = m_nScrollSize - 1;

	UpdateTheScroll();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::ScrollPageUp()
{
	m_nScrollPos -= PAGESCROLL;

    if( m_nScrollPos < 0 ) m_nScrollPos = 0;

	UpdateTheScroll();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::ScrollPageDown()
{
	m_nScrollPos += PAGESCROLL;

    if( m_nScrollPos >= m_nScrollSize ) m_nScrollPos = m_nScrollSize;

	UpdateTheScroll();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	assert(DataBanker);

	if( DataBanker->IsDBLoaded() )
    {
        if( Key == VK_PRIOR )
        {
            ScrollPageUp();
        }

        if( Key == VK_NEXT )
        {
            ScrollPageDown();
        }
	}
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::ShowPagedRecords(bool bShow)
{
	for(int i=0; i<m_pPagedRecords.size(); i++)
	{
		assert(m_pPagedRecords[i]);
		m_pPagedRecords[i]->Visible = bShow;
	}
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::LoadIndicesFromFile(AnsiString strFileName, TVecInt& nIndices)
{
	TStringList *pList = new TStringList;
    assert(pList);

    pList->LoadFromFile(strFileName);

    for(int i=0; i<pList->Count; i++)
    {
    										// salta righe vuote e commenti (#)
		if( (pList->Strings[i].Length() == 0)
        	|| ( pList->Strings[i].Pos("#")) ) continue;

		try
        {
			int nIndex = pList->Strings[i].ToInt();
			nIndices.push_back(nIndex);
        }
        catch(...)
        {
        	;
        }
	}
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::ScrollBarScroll(TObject *Sender, TScrollCode ScrollCode,
          int &ScrollPos)
{
	assert(DataBanker);

    if( DataBanker->IsDBLoaded() )
    {
		m_nScrollPos = ScrollPos;
    	UpdateTheScroll();
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::DeleteErrorList()
{
	m_ErrorList.clear();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::ToolsSearchClick(TObject *Sender)
{
	Find();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::SpeedButtonFindClick(TObject *Sender)
{
	Find();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::Find()
{
	assert(DataBanker);
	assert(FormDBSearch);

	if( DataBanker->IsDBLoaded() )
    {
    	FormDBSearch->ShowModal();
    }
    else
    {
		ShowError(ERREMPTYDB);
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::SetupPagedDBRecords()
{
	for(int i=0; i<DBRECORDSPERPAGE; i++)
    {
        TFormDBRecord *pRecord = new TFormDBRecord(PanelScroller);
		assert(pRecord);
        pRecord->Parent = PanelScroller;
        pRecord->Visible = false;
		pRecord->ClientWidth = FORMDBWIDTH;
		pRecord->ClientHeight = FORMDBHEIGHT;
		pRecord->Left = 0;
		pRecord->Top = DBRECORDBORDER + ( FORMDBHEIGHT + DBRECORDBORDER) * i;
		pRecord->OnKeyDown = this->OnKeyDown;
		pRecord->OnMouseWheel = this->OnMouseWheel;

		m_pPagedRecords.push_back(pRecord);
	}
}

//---------------------------------------------------------------------------
//	SCOPO:  Carica tutte le domande dal database
//---------------------------------------------------------------------------
void __fastcall TFormMain::LoadQuestions(TVecDBRecords& Records)
{
    int nSize = Records.size();

    if( nSize )
    {
        for(int i=0; i<nSize; i++)
        {
            TXDBRecord *pRecord = new TXDBRecord(&Records[i]);
            assert(pRecord);

            m_pSelRecords.push_back( pRecord );
        }
                                            // imposta l'Id per ciascuna domanda
        for(int i=0; i<m_pSelRecords.size(); i++)
        {
            m_pSelRecords[i]->nQueryId = i + 1;
        }
                                            // lo scrolling e` in funzione
                                            // del numero di records
        m_nScrollSize = m_pSelRecords.size();
    }
}

//---------------------------------------------------------------------------
//	SCOPO:  Carica dal database solo le domande selezionate in Indices
//---------------------------------------------------------------------------
void __fastcall TFormMain::LoadQuestions(TVecDBRecords& Records, TVecInt& Indices)
{
	assert(Records.size());
    assert(Indices.size());

    for(int i=0; i<Indices.size(); i++)
    {
        TXDBRecord *pRecord = new TXDBRecord( &Records[Indices[i]] );
        assert(pRecord);

		m_pSelRecords.push_back( pRecord );
    }
											// imposta l'Id per ciascuna domanda
	for(int i=0; i<m_pSelRecords.size(); i++)
    {
		m_pSelRecords[i]->nQueryId = i + 1;
    }
											// lo scrolling e` in funzione del numero di records
	m_nScrollSize = m_pSelRecords.size();
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::UpdateTheScroll()
{
	ClearPagedRecords();

    ShowPagedRecords(false);

#ifdef _DEBUG_
assert(FormDebug[0]);
AnsiString strTemp;
strTemp.printf("m_nScrollPos = %d", m_nScrollPos);
FormDebug[0]->Clear();
FormDebug[0]->Add(strTemp);
#endif

    SetPagedRecords(m_nScrollPos);

	ScrollBar->Position = m_nScrollPos;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::SetPagedRecords(int nIndex)
{
	assert(nIndex>=0);
	assert(m_pSelRecords.size());
	assert(m_pPagedRecords.size() == DBRECORDSPERPAGE);

	for(int i=0; i<DBRECORDSPERPAGE; i++)
    {
    	if( (nIndex + i) >= m_pSelRecords.size() ) break;

		m_pPagedRecords[i]->SetRecord( m_pSelRecords[nIndex+i] );

        if( IsTooLate() || (DlgSetup->IsInstantCorrection() && m_pPagedRecords[i]->IsDirty()) )
        {
            m_pPagedRecords[i]->CheckTheAnswer();
        }

										// inibisce la visualizzazione dei commenti
                                        // se il campo "strComment" e' vuoto.
		if( m_pPagedRecords[i]->HaveComment() )
        {
			m_pPagedRecords[i]->EnableComments(false);
        }

		m_pPagedRecords[i]->Visible = true;
    }

                                        // disattiva l'help se si e`
                                        // in una sessione di simulazione d'esame
	for(int i=0; i<DBRECORDSPERPAGE; i++)
    {
        if( IsExamSimulation() && !IsTooLate() )
        {
            m_pPagedRecords[i]->EnableComments(false);
        }
        else
        {
			if( m_pPagedRecords[i]->HaveComment() )
            {
            	m_pPagedRecords[i]->EnableComments(true);
            }
        }
	}


#ifdef _DEBUG_
AnsiString strTemp;
strTemp.printf("SetPagedRecords: index = %d", nIndex);
FormDebug[0]->Add(strTemp);
#endif

}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::UmDbRecord(TMessage& Message)
{
	assert(DlgSetup);

    TFormDBRecord* pDBRecord = (TFormDBRecord*) Message.WParam;
    assert(pDBRecord);

	TXDBRecord* pXDBRecord = (TXDBRecord*) Message.LParam;
    assert(pXDBRecord);

    if( DlgSetup->IsInstantCorrection() )
    {
		if( !pDBRecord->CheckTheAnswer() )
        {
			AddError(m_ErrorList, pXDBRecord->pDBRecord->nId );
        }
	}


	int nPos = GetPos(m_pPagedRecords, pDBRecord);

#ifdef _DEBUG_
assert(FormDebug);
AnsiString strTemp;
strTemp.printf("GetPos: %d", nPos);
FormDebug[0]->Add(strTemp);
#endif

	if( DlgSetup->IsAutoScroll() )
    {
										// scrolla, per comodita', la videata verso il basso
                                        // ( solo se si clicca dal secondo record in poi )
		if( nPos > 0 )
        {
    		ScrollDown();
        }
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::MakeNewQuiz()
{
	assert(DataBanker);

    if( DataBanker->IsDBLoaded() )
    {
		m_bIsTooLate = false;

		for(int i=0; i<m_pPagedRecords.size(); i++)
        {
			m_pPagedRecords[i]->EnableCheckBoxes(true);
        }

		ResetScrolling();

		BuildTheQuiz();
		TimerStart();
    }
    else
    {
		ShowError(ERREMPTYDB);
    }
}


//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormMain::BuildTheQuiz()
{
	assert(DlgSetup);
	assert(DataBanker);

	DeleteRecords();
	DeleteErrorList();

	Image->Visible = false; 				// ... per evitare il flickering

	TVecInt RecIds;
	int nCount = DlgSetup->GetCount();		// numero di domande per questionario

    enQuizModality nModality = DlgSetup->GetQuizModality();


    switch( nModality )
    {
    	case qmExamSimulation:
											// la prova d'esame richiede
                                            // di rispondere a 15 domande
            DataBanker->SelectRecordsRnd(RecIds, 15);
        break;

        case qmSelectQuestionsRandomly:
        	DataBanker->SelectRecordsRnd(RecIds, nCount);
        break;

        case qmSelectQuestionsSequentially:
			DataBanker->SelectRecords(RecIds, nCount);
		break;
    }


#if defined(_DEBUG_)
    assert(FormDebug);
	FormDebug[0]->Clear();
    FormDebug[0]->Print(RecIds);
    AnsiString strTemp;
    strTemp.printf("Unique Indices = %s", TUtils::IsUnique(RecIds) ? "yes" : "no" );
    FormDebug[0]->Add(strTemp);
#endif

	if( RecIds.size() )
    {
        LoadQuestions(*DataBanker->GetDB(), RecIds);

                                        	// visualizza i FormDBRecords
        if( m_pSelRecords.size() )
        {
			m_nScrollPos = 0;
            ScrollBar->Min = 0;
			ScrollBar->Max = m_nScrollSize - 1;

            ScrollUp();
        }
	}
    else
    {
		ShowError(ERREMPTYSEL);
    }
}

//---------------------------------------------------------------------------


