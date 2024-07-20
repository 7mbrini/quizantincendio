/******************************************************************************
	NAME:			Utils.cpp
	MAIN PROJECT:   Quiz Antincendio - Quiz per il Corso Antincendio VVFF Bari
	DESCRIPTION:    Utilities routines and algorithms
	EXETYPE:        For 32 & 64 bit Windows platforms.
	COMPILER:       Borland/CodeGear/Embarcadero Rad Studio XE.

	AUTHOR:         (C) 2024 Francesco Settembrini
					francesco.settembrini@poliba.it
					http://www.francescosettembrini.it

	DATA:           July 2024
	RELEASE:        1.0.0


	DETAILS:
	  Quiz di preparazione alla prova teorica per il Corso Antincendio
      svoltosi presso il Comando dei Vigili del Fuoco di Bari - Mungivacca

	NOTES:
	  - Il presente lavoro e` protetto dalle leggi internazionali
	  sui diritti d'autore. Nessuna parte puo` essere copiata
	  senza il permesso esplicito dell'autore.

	  - This work is protected by international laws on copy-rights.
	  No parts can be copied without explicit permission of the author.

******************************************************************************/

#include <vcl.h>
#pragma hdrstop

#include "utils.h"
#include "TFormMain.h"
#include "TFormDebug.h"
#include "TFormDBRecord.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)


//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TUtils::LoadDataTest()
{
	assert(FormMain);

	//FormMain->LoadDB();
    FormMain->MakeNewQuiz();
    //FormMain->PrintDB(FormMain->m_DB);
	//FormDebug->Print(FormMain->m_DB);
    //LoadDB(); ShowMessage(m_DB.size()); PrintDB(m_DB);
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
bool __fastcall TUtils::IsUnique(TVecInt& Ids)
{
	bool bResult = true;

if( Ids.size() )
{
	for(int i=0; i<Ids.size() - 1; i++)
    {

		for( int j = i+1; j < Ids.size(); j++ )
        {
			if( Ids[i] == Ids[j] )
            {
            	bResult = false;
                break;
        	}
        }
    }
}
    return bResult;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
bool __fastcall TUtils::IsUnique(int nId, TVecInt& Ids)
{
	bool bResult = true;

	for(int i=0; i<Ids.size(); i++)
    {
		if( Ids[i] == nId )
        {
        	bResult = false;
            break;
        }
    }

    return bResult;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TUtils::Remove(int nIndex, TVecInt& Ids)
{
	TVecInt Temp;

    for(int i=0; i<Ids.size(); i++)
    {
        if( i != nIndex )
        {
	        Temp.push_back( Ids[i] );
        }
    }

    Ids = Temp;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
bool __fastcall TUtils::IsIn(int nId, TVecInt& Ids)
{
	bool bResult = false;

	for(int i=0; i<Ids.size(); i++)
    {
		if( Ids[i] == nId )
        {
        	bResult = true;
            break;
        }
    }

    return bResult;
}

//---------------------------------------------------------------------------
//	SCOPO:
//---------------------------------------------------------------------------
void __fastcall TUtils::MergeUnique(TVecInt& A, TVecInt& B, TVecInt& C)
{
	//for(int i=0; i<
	C = A;

    for(int i=0; i<B.size(); i++)
    {
		if( !IsIn( B[i], A) )
        {
        	C.push_back(B[i]);
        }
    }
}

