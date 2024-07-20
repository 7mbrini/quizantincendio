//---------------------------------------------------------------------------
#ifndef TFormDBRecordH
#define TFormDBRecordH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>

#include <vector>

#include "commdefs.h"

using namespace std;

class TFormDBRecord;

typedef vector<TFormDBRecord*> TVecPtrFormDBRecords;


//---------------------------------------------------------------------------
class TFormDBRecord : public TForm
{
__published:	// IDE-managed Components
	TMemo *MemoQuestion;
	TMemo *MemoAnswer1;
	TMemo *MemoAnswer2;
	TMemo *MemoAnswer3;
	TImage *Image;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TLabel *LabelId;
	TLabel *LabelOrgId;
	TPopupMenu *PopupMenu;
	TMenuItem *PopupUpdateRecord;
	TMenuItem *PopupSaveDatabase;
	TRichEdit *RichEditComment;
	TSpeedButton *SpeedButtonHelp;
	TPopupMenu *DefPopupMenu;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall CheckBox2Click(TObject *Sender);
	void __fastcall CheckBox3Click(TObject *Sender);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall PopupUpdateRecordClick(TObject *Sender);
	void __fastcall SpeedButtonHelpClick(TObject *Sender);
	void __fastcall MemoQuestionMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall MemoAnswer2MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall MemoAnswer3MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall MemoAnswer1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall RichEditCommentSelectionChange(TObject *Sender);
	void __fastcall MemoQuestionKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall MemoQuestionMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);



private:	// User declarations

public:		// User declarations
	__fastcall TFormDBRecord(TComponent* Owner);

	bool __fastcall IsDirty();
	void __fastcall SetFontSize(int nFontSize);
	void __fastcall EnableComments(bool bEnable);

public:
	void __fastcall Clear();
	bool __fastcall CheckTheAnswer();

	TXDBRecord* __fastcall GetRecord() { return m_pRecord; }
	void __fastcall SetRecord(TXDBRecord* pRecord);
	void __fastcall SetLabels(AnsiString strLabelId, AnsiString strLabelOrgId);

    void __fastcall EnableCheckBoxes(bool bEnable);

    bool __fastcall HaveComment();

	void __fastcall Print(TBitmap* pBmp, AnsiString strLabel);
	void __fastcall PrintA(TBitmap* pBmp, AnsiString strLabel);

protected:
	bool m_bEditing;
	TXDBRecord* m_pRecord;


	bool __fastcall IsEditing() { return m_bEditing; }
	void __fastcall SetEditing(bool bEditing);
};

//---------------------------------------------------------------------------
extern PACKAGE TFormDBRecord *FormDBRecord;
//---------------------------------------------------------------------------
#endif
