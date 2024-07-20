/******************************************************************************
	NAME:			TDlgABout.cpp
	MAIN PROJECT:   Quiz Antincendio - Quiz il Corso Sicurezza Antincendio
	DESCRIPTION:	AboutBox Dialog
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
#include <assert.h>
#include <mmsystem.h>
#pragma hdrstop

#include "commdefs.h"
#include "TDlgAbout.h"


//---------------------------------------------------------------------
#pragma resource "*.dfm"
TDlgAbout *DlgAbout;


//---------------------------------------------------------------------
//  SCOPO:  Costruttore
//---------------------------------------------------------------------
__fastcall TDlgAbout::TDlgAbout(TComponent* AOwner) : TForm(AOwner)
{

}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TDlgAbout::FormCreate(TObject *Sender)
{
	this->Caption = AnsiString("Informazioni su ") + APPNAME;

    TBitmap *pBmp = Image->Picture->Bitmap;
    assert(pBmp);

										// visualizza le info sulla release
    int nW = pBmp->Width;
    int nH = pBmp->Height;
    int nFontSize = 14;
    int nBorder = 8;
    AnsiString strFontName = "tahoma";

    pBmp->Canvas->Font->Name = strFontName;
    pBmp->Canvas->Font->Size = nFontSize;

	TSize Size = pBmp->Canvas->TextExtent(APPRELEASE);

    pBmp->Canvas->TextOutW((nW-Size.cx)/2, nH - 2*nFontSize - nBorder, APPRELEASE);
}

//---------------------------------------------------------------------
//  SCOPO:
//---------------------------------------------------------------------
void __fastcall TDlgAbout::FormShow(TObject *Sender)
{
    PlaySound();
}

//---------------------------------------------------------------------
//  SCOPO:
//---------------------------------------------------------------------------
void __fastcall TDlgAbout::FormHide(TObject *Sender)
{
    ::sndPlaySound(NULL, NULL);
}

//---------------------------------------------------------------------------
//  SCOPO:  Playsound
//---------------------------------------------------------------------------
void __fastcall TDlgAbout::PlaySound()
{
    wchar_t *Sound = L"SOUND_INNOVVFF";

    wchar_t* pBuf = NULL;

    HRSRC hFound = 0;
    HGLOBAL hRes = 0;

	hFound = ::FindResource(HInstance, Sound, RT_RCDATA );
    assert(hFound);

	hRes = LoadResource(HInstance, hFound);
    assert(hRes);

	pBuf = (wchar_t*) ::LockResource(hRes);
    assert(pBuf);

    ::sndPlaySound( (wchar_t*)pBuf, SND_MEMORY | SND_ASYNC);
}

//---------------------------------------------------------------------------

