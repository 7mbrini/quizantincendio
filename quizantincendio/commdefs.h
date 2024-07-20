#ifndef _QUIZPN_COMMDEFS_H_
#define _QUIZPN_COMMDEFS_H_

#include <vcl.h>
#pragma hdrstop

#include <vector>

using namespace std;


#define APPNAME 	"Quiz Antincendio"
#define WAPPNAME 	L"Quiz Antincendio"
#define APPRELEASE 	"Release 1.0.0 July 2024"

const wchar_t *MAGIC = L"Quiz Antincendio - (C) 2024 Francesco Settembrini - http: www.francescosettembrini.it";

#ifdef _DEBUG_
    #define QUIZDBFILE	"quizantincendio.db"
    #define DATAPATH  	"Z:/shared/jobs/cppbuilder/quizantincendio/quizantincendio/data/"
#endif


#define UM_QUESTION_CLICK	(WM_USER + 200)

#define ERRBADDBFORMAT	100
#define ERREMPTYDB		110
#define ERREMPTYSEL		120
#define ERREMPTYERRLIST	130

#define LINESCROLL	1
#define PAGESCROLL	2

#define DBRECORDSPERPAGE	15
#define DBRECORDBORDER		24

#define NUMQUESTIONS	20						// default di domande per quiz
#define MINQUESTIONS	DBRECORDSPERPAGE		// minimo di domande per quiz

#define MAXQUESTIONS	15		// numero di domande per quiz

#define QUIZTHRESHOLD   66.6	// soglia d'errore per il superamento del quiz
								// almeno 10 risposte esatte su 15 domande (~ 66.6 %)

#define FORMDBWIDTH		850
#define FORMDBHEIGHT	270

								// 16 KB, piu' che sufficienti con un Jpeg
#define IMGSIZE			16384
#define MAXANSWERS 		5

#define APPWIDTH    800
#define APPHEIGHT	760


extern AnsiString g_strRelease;


typedef vector<int> TVecInt;
typedef vector<AnsiString> TVecStrings;


//---------------------------------------------------------------------------
enum enQuizModality {
    qmNone = -1,
    qmExamSimulation = -2,
    qmSelectQuestionsRandomly = -3,
	qmSelectQuestionsSequentially = -4
};


class TDBRecord
{
public:
	TDBRecord()
    {
		nId = nTopicId = -1;
        memset(strQuestion, 0, sizeof(strQuestion));
        nAnswers = 0;
		memset(bAnswers, false, sizeof(bAnswers));
		memset(strComment, 0, sizeof(strComment));
        bHaveImage = false;
        nImgSize = 0;
        memset(Image, 0, sizeof(Image));
    }

	int nId;
    int nTopicId;
	wchar_t strQuestion[1024];
    wchar_t strAnswers[MAXANSWERS][1024];
	wchar_t strComment[1024];
    int nAnswers;
    bool bAnswers[MAXANSWERS];
	bool bHaveImage;
	int nImgSize;
	BYTE Image[IMGSIZE];
};

typedef vector<TDBRecord> TVecDBRecords;
typedef vector<TDBRecord*> TVecPtrDBRecords;

class TXDBRecord
{
public:
	TXDBRecord()
    {
		this->pDBRecord = NULL;
		bIsDirty = false;
		nQueryId = -1;
        memset(&bAnswers[0], false, sizeof(bool)*MAXANSWERS);
    }

	TXDBRecord(TDBRecord* pDBRecord)
    {
		this->pDBRecord = pDBRecord;
        bIsDirty = false;
		nQueryId = -1;
        memset(&bAnswers[0], false, sizeof(bool)*MAXANSWERS);
    }

	bool __fastcall CheckTheAnswer()
    {
		assert(pDBRecord);

		bool bResult = true;
		for(int i=0; i<MAXANSWERS; i++)
        {
			if( pDBRecord->bAnswers[i] != this->bAnswers[i] )
            {
            	bResult = false;
                break;
            }
        }

        return bResult;
    }

    void __fastcall ClearTheAnswers()
    {
        memset(&bAnswers[0], false, sizeof(bool)* MAXANSWERS);
    }

	TDBRecord* pDBRecord;
	int nQueryId;
    bool bIsDirty, bAnswers[MAXANSWERS];
};

typedef vector<TXDBRecord> TVecXDBRecords;
typedef vector<TXDBRecord*> TVecPtrXDBRecords;

#endif


