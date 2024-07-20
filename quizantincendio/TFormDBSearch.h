//---------------------------------------------------------------------------
#ifndef TFormDBSearchH
#define TFormDBSearchH

//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>


//---------------------------------------------------------------------------
class TFormDBSearch : public TForm
{
__published:	// IDE-managed Components
	TPanel *PanelTop;
	TPanel *PanelClient;
	TPanel *PanelBottom;
	TButton *ButtonOk;
	TEdit *EditKeyword;
	TButton *ButtonSearch;
	TLabel *Label1;
	TLabel *Label2;
	TComboBox *ComboBoxSearch;
	TStatusBar *StatusBar;
	TRichEdit *RichEdit;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ButtonOkClick(TObject *Sender);
	void __fastcall ButtonSearchClick(TObject *Sender);
	void __fastcall EditKeywordKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCanResize(TObject *Sender, int &NewWidth, int &NewHeight, bool &Resize);
	void __fastcall RichEditSelectionChange(TObject *Sender);

private:	// User declarations

public:		// User declarations
	__fastcall TFormDBSearch(TComponent* Owner);

protected:
	void __fastcall DoSearch();

};

//---------------------------------------------------------------------------
extern PACKAGE TFormDBSearch *FormDBSearch;
//---------------------------------------------------------------------------

#endif
