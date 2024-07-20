//---------------------------------------------------------------------------
#ifndef _TFORMDEBUG_H_
#define _TFORMDEBUG_H_

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>

#include "commdefs.h"

#define FORMSDEBUG	2

enum enDebugMode { dmText, dmBitmap };

//---------------------------------------------------------------------------
class TFormDebug : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu;
	TMenuItem *MenuActions;
	TMenuItem *ActionsClear;
	TMenuItem *FileSaveAs;
	TRichEdit *RichEdit;
	TSaveDialog *SaveDialog;
	TMenuItem *MenuFile;
	TImage *Image;
	TMenuItem *OpMode1;
	TMenuItem *ext1;
	TMenuItem *Images1;
	TStatusBar *StatusBar;
	void __fastcall ActionsClearClick(TObject *Sender);
	void __fastcall FileSaveAsClick(TObject *Sender);
	void __fastcall ext1Click(TObject *Sender);
	void __fastcall Images1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormDebug(TComponent* Owner);

	void __fastcall SetOpMode(enDebugMode nMode);

public:
	void __fastcall Clear();
	void __fastcall Add(AnsiString strString);
	void __fastcall Add(TStringList* pList);

    void __fastcall Print(AnsiString strString) { Add(strString); }
    void __fastcall Print(TStringList* pList) { Add(pList); }

    void __fastcall Print(TVecInt& Ints);
	void __fastcall Print(TBitmap* pBmp);
	void __fastcall Print(TXDBRecord* pRecord);
    void __fastcall Print(TVecDBRecords& Records);
	void __fastcall Print(TVecPtrXDBRecords& pRecords);
};

//---------------------------------------------------------------------------
extern PACKAGE TFormDebug* FormDebug[FORMSDEBUG];
//---------------------------------------------------------------------------
#endif
