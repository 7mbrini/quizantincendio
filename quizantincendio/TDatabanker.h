//---------------------------------------------------------------------------
#ifndef TDatabankerH
#define TDatabankerH

#include <vcl.h>
#include <System.Classes.hpp>
#pragma hdrstop

#include "commdefs.h"


//---------------------------------------------------------------------------

#define MAXTOPICS	16

struct TagTopic
{
	TagTopics()
    {
    	nId = -1;
        memset(strTopic, 0, sizeof(strTopic));
        PercentInQuiz = 0;
    }

	int nId;
	wchar_t strTopic[1024];
    double PercentInQuiz;
};

typedef vector<TagTopic> TVecTopics;

struct TagFileHeader {
    wchar_t strMagic[256];
    int nRecords;
};


//---------------------------------------------------------------------------
class TDataBanker : public TDataModule
{

__published:	// IDE-managed Components

private:	// User declarations

public:		// User declarations
	__fastcall TDataBanker(TComponent* Owner);

public:

public:
	void __fastcall Clear();

	int __fastcall GetTopics(TVecTopics& Topics);

    bool __fastcall HaveTopics();
    int __fastcall GetQuestionsCount(TVecInt& nCount);
    int __fastcall GetQuestionsPerTopic(int nTopicId);
	int __fastcall GetDBSize() { return m_DB.size(); }
	TVecDBRecords * const __fastcall GetDB() { return &m_DB; }

	bool __fastcall LoadDB(AnsiString strFileName);
	bool __fastcall IsDBLoaded() { return bool(GetDBSize()); }
    void __fastcall SaveDB(AnsiString strFileName, TVecDBRecords& Records, TVecStrings strTopics);

    void __fastcall SelectRecords(TVecInt& SelRecs);
    void __fastcall SelectRecords(TVecInt& SelRecs, int nCount);
    void __fastcall SelectRecords(int nTopicId, TVecInt& SelRecs);
    void __fastcall SelectRecords(int nTopicId, TVecInt& SelRecs, int nCount);
    void __fastcall SelectRecordsRnd(TVecInt& SelRecs, int nCount);
    void __fastcall SelectRecordsWithFigures(TVecInt& SelRecs, int nCount);
    void __fastcall SelectRecordsWithFiguresRnd(TVecInt& SelRecs, int nCount);
    void __fastcall SelectRecordsRnd(int nTopicId, TVecInt& SelRecs, int nCount);
    void __fastcall SelectRecordsByIndices(TVecInt& Indices, TVecInt& SelRecs);

	void __fastcall GetRecords(TVecInt& Indices, TVecDBRecords& SelRecs);

	void __fastcall SearchInAnswers(AnsiString strKeyword, TVecInt& SelRecs, bool bCaseSensitive=false);
	void __fastcall SearchInQuestions(AnsiString strKeyword, TVecInt& SelRecs, bool bCaseSensitive=false);

protected:


protected:
    TVecDBRecords m_DB;
	TVecTopics m_Topics;

	bool __fastcall LoadDB(AnsiString strFileName, TVecDBRecords& Records, TVecTopics& Topics);

    void __fastcall SelectRecords(TVecDBRecords& Records, TVecInt& SelRecs);
    void __fastcall SelectRecords(TVecDBRecords& Records, TVecInt& SelRecs, int nCount);
    void __fastcall SelectRecords(TVecDBRecords& Records, int nTopicId, TVecInt& SelRecs);
    void __fastcall SelectRecords(TVecDBRecords& Records, int nTopicId, TVecInt& SelRecs, int nCount);
    void __fastcall SelectRecordsRnd(TVecDBRecords& Records, TVecInt& SelRecs, int nCount);
    void __fastcall SelectRecordsWithFigures(TVecDBRecords& Records, TVecInt& SelRecs, int nCount);
    void __fastcall SelectRecordsWithFiguresRnd(TVecDBRecords& Records, TVecInt& SelRecs, int nCount);
    void __fastcall SelectRecordsRnd(TVecDBRecords& Records, int nTopicId, TVecInt& SelRecs, int nCount);
    void __fastcall SelectRecordsByIndices(TVecDBRecords& Records, TVecInt& Indices, TVecInt& SelRecs);
};

//---------------------------------------------------------------------------
extern PACKAGE TDataBanker *DataBanker;
//---------------------------------------------------------------------------
#endif
