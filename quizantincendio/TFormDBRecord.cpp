/******************************************************************************
	NAME:			TFormDBRecord.cpp
	MAIN PROJECT:   Quiz Antincendio - Quiz per il Corso Sicurezza Antincendio
	DESCRIPTION:	Database Record Descriptor
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
#include <jpeg.hpp>
#include <graphics.hpp>
#include <clipbrd.hpp>
#pragma hdrstop

#include "TFormDebug.h"
#include "TFormMain.h"
#include "TFormDBRecord.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormDBRecord *FormDBRecord;


//---------------------------------------------------------------------------
//	SCOPO:	Costruttore
//---------------------------------------------------------------------------
__fastcall TFormDBRecord::TFormDBRecord(TComponent* Owner) : TForm(Owner)
{
	m_pRecord = NULL;
    m_bEditing = false;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::FormCreate(TObject *Sender)
{
    this->BorderStyle = bsNone;

	int nFontSize = 10;

	LabelId->Font->Style << fsBold;
    LabelId->Font->Size = nFontSize;

    MemoQuestion->ReadOnly = true;
	MemoQuestion->Font->Style << fsBold;
    MemoQuestion->Font->Size = nFontSize;

    MemoAnswer1->ReadOnly = true;
	MemoAnswer1->Font->Style << fsBold;
    MemoAnswer1->Font->Size = nFontSize;

    MemoAnswer2->ReadOnly = true;
	MemoAnswer2->Font->Style << fsBold;
    MemoAnswer2->Font->Size = nFontSize;

    MemoAnswer3->ReadOnly = true;
	MemoAnswer3->Font->Style << fsBold;
    MemoAnswer3->Font->Size = nFontSize;

	SpeedButtonHelp->Visible = false;
	SpeedButtonHelp->Enabled = false;
	RichEditComment->Visible = false;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::CheckBox1Click(TObject *Sender)
{
	assert(FormMain);

    SetEditing(true);
	CheckBox2->Checked = false;
    CheckBox3->Checked = false;
    SetEditing(false);

    if( m_pRecord && !IsEditing() )
    {
        m_pRecord->bIsDirty = true;
        m_pRecord->ClearTheAnswers();

		CheckBox1->Checked = true;
        m_pRecord->bAnswers[0] = true;

        ::SendMessage(FormMain->Handle, UM_QUESTION_CLICK,
        	(WPARAM)(LPVOID) this, (LPARAM)(LPVOID) m_pRecord);
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::CheckBox2Click(TObject *Sender)
{
	assert(FormMain);

    SetEditing(true);
    CheckBox1->Checked = false;
    CheckBox3->Checked = false;
    SetEditing(false);

    if( m_pRecord && !IsEditing() )
    {
        m_pRecord->bIsDirty = true;
        m_pRecord->ClearTheAnswers();

		CheckBox2->Checked = true;
        m_pRecord->bAnswers[1] = true;

        ::SendMessage(FormMain->Handle, UM_QUESTION_CLICK,
        	(WPARAM)(LPVOID) this, (LPARAM)(LPVOID) m_pRecord);
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::CheckBox3Click(TObject *Sender)
{
	assert(FormMain);

    SetEditing(true);
    CheckBox1->Checked = false;
    CheckBox2->Checked = false;
    SetEditing(false);

    if( m_pRecord && !IsEditing() )
    {
        m_pRecord->bIsDirty = true;
        m_pRecord->ClearTheAnswers();

		CheckBox3->Checked = true;
        m_pRecord->bAnswers[2] = true;

        ::SendMessage(FormMain->Handle, UM_QUESTION_CLICK,
        	(WPARAM)(LPVOID) this, (LPARAM)(LPVOID) m_pRecord);
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::EnableCheckBoxes(bool bEnable)
{
	CheckBox1->Enabled = bEnable;
    CheckBox2->Enabled = bEnable;
    CheckBox3->Enabled = bEnable;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::SetLabels(AnsiString strLabelId, AnsiString strLabelOrgId)
{
	LabelId->Caption = strLabelId;
	LabelOrgId->Caption = strLabelOrgId;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::Clear()
{
	m_pRecord = NULL;

	this->Color = clBtnFace;

	LabelId->Caption = "";
    LabelOrgId->Caption = "";

	MemoQuestion->Text = "";

    MemoAnswer1->Text = "";
    MemoAnswer2->Text = "";
    MemoAnswer3->Text = "";

	MemoQuestion->Color = clInfoBk;
    MemoAnswer1->Color = clCream;
    MemoAnswer2->Color = clCream;
    MemoAnswer3->Color = clCream;

    RichEditComment->Clear();
    RichEditComment->Visible = false;
    SpeedButtonHelp->Down = false;

    CheckBox1->Checked = false;
    CheckBox2->Checked = false;
    CheckBox3->Checked = false;

    Image->Picture->Bitmap = NULL;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
bool __fastcall TFormDBRecord::IsDirty()
{
	bool bIsDirty = false;

    if( m_pRecord )
    {
    	bIsDirty = m_pRecord->bIsDirty;
    }

    return bIsDirty;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::SetFontSize(int nFontSize)
{
	MemoQuestion->Font->Size = nFontSize;
	MemoAnswer1->Font->Size = nFontSize;
	MemoAnswer2->Font->Size = nFontSize;
	MemoAnswer3->Font->Size = nFontSize;

	LabelId->Font->Size = nFontSize;
    LabelOrgId->Font->Size = nFontSize;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::PrintA(TBitmap* pBmp, AnsiString strLabel)
{
	assert(pBmp);
	assert(m_pRecord);

    TRect Rect = this->ClientRect;
	int nW = Rect.Width();
    int nH = Rect.Height();

	pBmp->Width = nW;
    pBmp->Height = nH;
	pBmp->PixelFormat = pf24bit;

											// ripulisce lo sfondo
	pBmp->Canvas->Brush->Color = clWhite;
	pBmp->Canvas->Pen->Color = clBlack;
	pBmp->Canvas->Pen->Width = 0;
	pBmp->Canvas->FillRect(Rect);
	pBmp->Canvas->Rectangle(0,0,nW,nH);
											// imposta le dimensioni del font
	int nFontSize = MemoQuestion->Font->Size;
    pBmp->Canvas->Font->Size = nFontSize;
											// stampa le eventuali labels
    if( strLabel.Length() )
    {
        pBmp->Canvas->TextOutW(16, 16, strLabel);
    }

											// stampa l'immagine
	TRect BmpRect = Image->ClientRect;
    TRect DstRect = BmpRect;
    DstRect.SetLocation(16, 64);
	pBmp->Canvas->CopyRect(DstRect, Image->Canvas, BmpRect);

    int nX = 260;
    int nY = 16;
    float DY = 1.75f;
	int nPosY = nY;

    for(int i=0; i<MemoQuestion->Lines->Count; i++)
    {
		pBmp->Canvas->TextOutW(nX, nPosY, MemoQuestion->Lines->Strings[i]);
		nPosY += DY * nFontSize;
    }

    typedef vector<TMemo*> TVecPtrMemos;
    TVecPtrMemos pAnswers;

	vector<AnsiString> Labels;
    Labels.push_back(L"a)");
    Labels.push_back(L"b)");
    Labels.push_back(L"c)");

    pAnswers.push_back( MemoAnswer1 );
    pAnswers.push_back( MemoAnswer2 );
    pAnswers.push_back( MemoAnswer3 );

    nPosY += 2*DY;

    for(int i=0; i<pAnswers.size(); i++)
    {
        nPosY += 1 * DY;

        if( m_pRecord->bAnswers[i] == true )
        {
            pBmp->Canvas->TextOutW(nX - 72, nPosY, L"[x]");
        }

		pBmp->Canvas->TextOutW(nX - 32, nPosY, Labels[i] );

        for(int j=0; j<pAnswers[i]->Lines->Count; j++)
        {
            pBmp->Canvas->TextOutW(nX, nPosY, pAnswers[i]->Lines->Strings[j]);
            nPosY += DY * nFontSize;
        }
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::Print(TBitmap* pBmp, AnsiString strLabel)
{
	assert(pBmp);
	assert(m_pRecord);
											// imposta le dimensioni della Bitmap
                                            // a quelle del clientrect.
    TRect Rect = this->ClientRect;
	int nW = Rect.Width();
    int nH = Rect.Height();

	pBmp->Width = nW;
    pBmp->Height = nH;
	pBmp->PixelFormat = pf24bit;
											// ripulisce lo sfondo
	pBmp->Canvas->Brush->Color = clWhite;
	pBmp->Canvas->Pen->Color = clBlack;
	pBmp->Canvas->Pen->Width = 0;
	pBmp->Canvas->FillRect(Rect);
	pBmp->Canvas->Rectangle(0,0,nW,nH);

											// imposta le dimensioni del font
	int nFontSize = MemoQuestion->Font->Size;
    pBmp->Canvas->Font->Size = nFontSize;

											// stampa le eventuali labels
    if( strLabel.Length() )
    {
        pBmp->Canvas->TextOutW(64, 16, strLabel);
    }
											// stampa l'immagine
	TRect BmpRect = Image->ClientRect;
    TRect DstRect = BmpRect;
    DstRect.SetLocation(16, 64);
    DstRect.SetWidth(DstRect.Width()*2);
    DstRect.SetHeight(DstRect.Height()*2);
	pBmp->Canvas->CopyRect(DstRect, Image->Canvas, BmpRect);


											// stampa domande e risposte
	int nX = 400;		// text left
	int nY = 16;		// text top
	float DY = 1.75f;	// dimensioni dell'interlinea
	int nPosY = nY;
											// stampa la domanda
    for(int i=0; i<MemoQuestion->Lines->Count; i++)
    {
		pBmp->Canvas->TextOutW(nX, nPosY, MemoQuestion->Lines->Strings[i]);
		nPosY += DY * nFontSize;
    }

											// stampa le risposte
    typedef vector<TMemo*> TVecPtrMemos;
    TVecPtrMemos pAnswers;

	vector<AnsiString> Labels;
    Labels.push_back(L"a)");
    Labels.push_back(L"b)");
    Labels.push_back(L"c)");

    pAnswers.push_back( MemoAnswer1 );
    pAnswers.push_back( MemoAnswer2 );
    pAnswers.push_back( MemoAnswer3 );

											// interlinea fra domanda e risposte
	nPosY += 8.0*DY;

    for(int i=0; i<pAnswers.size(); i++)
    {
		nPosY += 4 * DY;

        if( m_pRecord->bAnswers[i] == true )
        {
			pBmp->Canvas->TextOutW(nX - 80, nPosY, L"[x]");
        }

		pBmp->Canvas->TextOutW(nX - 32, nPosY, Labels[i] );

        for(int j=0; j<pAnswers[i]->Lines->Count; j++)
        {
            pBmp->Canvas->TextOutW(nX, nPosY, pAnswers[i]->Lines->Strings[j]);
            nPosY += DY * nFontSize;
        }
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
#ifdef _DEBUG_
	if( Button == mbRight )
    {
		TPoint Pos = this->ClientToScreen(TPoint(X,Y));
		PopupMenu->Popup(Pos.X, Pos.Y);
    }
#endif
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::PopupUpdateRecordClick(TObject *Sender)
{
#ifdef _DEBUG_
	assert(m_pRecord);
	assert(m_pRecord->pDBRecord);

	wcscpy( m_pRecord->pDBRecord->strQuestion, UnicodeString(MemoQuestion->Lines->Text).c_str());
	wcscpy( m_pRecord->pDBRecord->strAnswers[0], UnicodeString(MemoAnswer1->Lines->Text).c_str());
	wcscpy( m_pRecord->pDBRecord->strAnswers[1], UnicodeString(MemoAnswer2->Lines->Text).c_str());
	wcscpy( m_pRecord->pDBRecord->strAnswers[2], UnicodeString(MemoAnswer3->Lines->Text).c_str());

    m_pRecord->pDBRecord->bAnswers[0] = CheckBox1->Checked;
    m_pRecord->pDBRecord->bAnswers[1] = CheckBox2->Checked;
    m_pRecord->pDBRecord->bAnswers[2] = CheckBox3->Checked;
#endif
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::SetRecord(TXDBRecord* pRecord)
{
	assert(pRecord);
	assert(pRecord->pDBRecord);

	m_pRecord = pRecord;

	Image->Picture->Bitmap = NULL;

										// un tocco di eleganza ...
	MemoQuestion->ScrollBars = ssNone;
    if( AnsiString(m_pRecord->pDBRecord->strQuestion).Length() > 220 )
    {
    	MemoQuestion->ScrollBars = ssVertical;
    }


    MemoQuestion->Text = m_pRecord->pDBRecord->strQuestion;
    MemoAnswer1->Text = m_pRecord->pDBRecord->strAnswers[0];
    MemoAnswer2->Text = m_pRecord->pDBRecord->strAnswers[1];
    MemoAnswer3->Text = m_pRecord->pDBRecord->strAnswers[2];


    AnsiString strId, strOrgId;
    strId.printf("  Q %03d", m_pRecord->nQueryId);
    strOrgId.printf("%d", m_pRecord->pDBRecord->nId);
    //SetLabels(strId, strOrgId);
    SetLabels(strId, "");

                                        // carica l'eventuale immagine
    if( m_pRecord->pDBRecord->bHaveImage )
    {
        TMemoryStream *pMs = new TMemoryStream;
        assert(pMs);

        pMs->Write(m_pRecord->pDBRecord->Image, m_pRecord->pDBRecord->nImgSize);
        pMs->Position = 0L;

        TJPEGImage *pImage = new TJPEGImage;
        assert(pImage);
        pImage->LoadFromStream(pMs);

        Image->Picture->Bitmap->Assign(pImage);
        Image->Update();

        delete pImage;
        delete pMs;
    }


    if( IsDirty() )
    {
						// !! Bisogna **DISABILITARE** gli **EVENTI** dei checkboxes ... !!
                        // !! ... altrimenti la modifica dei checkboxes **CAUSA** un evento "checked" fittizio!!
		SetEditing(true);

            this->CheckBox1->Checked = bool(m_pRecord->bAnswers[0]);
            this->CheckBox2->Checked = bool(m_pRecord->bAnswers[1]);
            this->CheckBox3->Checked = bool(m_pRecord->bAnswers[2]);

						// riattiva la gestione degli eventi dei checkboxes
        SetEditing(false);
    }
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
bool __fastcall TFormDBRecord::CheckTheAnswer()
{
	bool bResult = false;

    if( m_pRecord && IsDirty() )
    {
                                        // evidenzia, in verde, la/le risposta/e esatta/e
        if( m_pRecord->pDBRecord->bAnswers[0] ) MemoAnswer1->Color = clMoneyGreen;
        if( m_pRecord->pDBRecord->bAnswers[1] ) MemoAnswer2->Color = clMoneyGreen;
        if( m_pRecord->pDBRecord->bAnswers[2] ) MemoAnswer3->Color = clMoneyGreen;

        if( m_pRecord->CheckTheAnswer() )
        {
            this->Color = clMoneyGreen;
            bResult = true;
        }
        else
        {
            this->Color = clRed;
        }
    }
    else
    {
        this->Color = clGray;
    }

    return bResult;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::SpeedButtonHelpClick(TObject *Sender)
{
	RichEditComment->Visible = SpeedButtonHelp->Down;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
bool __fastcall TFormDBRecord::HaveComment()
{
	bool bResult = false;

	if( m_pRecord && m_pRecord->pDBRecord && AnsiString( m_pRecord->pDBRecord->strComment ).Length() )
    {
		bResult = true;
    }

    return bResult;
}

//---------------------------------------------------------------------------
//	SCOPO:	Attiva/Disattiva il pulsante per la visualizzazione dei commenti
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::EnableComments(bool bEnable)
{
	SpeedButtonHelp->Enabled = bEnable;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::RichEditCommentSelectionChange(TObject *Sender)
{
	if( RichEditComment->SelLength > 0 ) RichEditComment->SelLength = 0;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::MemoQuestionKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if( MemoQuestion->SelLength > 0 ) MemoQuestion->SelLength = 0;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::MemoQuestionMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if( MemoQuestion->SelLength > 0 ) MemoQuestion->SelLength = 0;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::MemoQuestionMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
	if( MemoQuestion->SelLength > 0 ) MemoQuestion->SelLength = 0;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::MemoAnswer1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
	if( MemoAnswer1->SelLength > 0 ) MemoAnswer1->SelLength = 0;

}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::MemoAnswer2MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
	if( MemoAnswer2->SelLength > 0 ) MemoAnswer2->SelLength = 0;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::MemoAnswer3MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
	if( MemoAnswer3->SelLength > 0 ) MemoAnswer3->SelLength = 0;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TFormDBRecord::SetEditing(bool bEditing)
{
	m_bEditing = bEditing;


    if( m_bEditing )
    {
        CheckBox1->OnClick = NULL;
        CheckBox2->OnClick = NULL;
        CheckBox3->OnClick = NULL;
    }
    else
    {
        CheckBox1->OnClick = CheckBox1Click;
        CheckBox2->OnClick = CheckBox2Click;
        CheckBox3->OnClick = CheckBox3Click;
    }
}

//---------------------------------------------------------------------------

