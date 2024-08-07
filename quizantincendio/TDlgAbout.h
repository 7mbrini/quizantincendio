//----------------------------------------------------------------------------
#ifndef TDlgAboutH
#define TDlgAboutH

//----------------------------------------------------------------------------
#include <vcl.h>
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Graphics.hpp>
#pragma hdrstop

//----------------------------------------------------------------------------
class TDlgAbout : public TForm
{
__published:
	TButton *OKBtn;
	TTimer *Timer;
	TImage *Image;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private:

public:
	virtual __fastcall TDlgAbout(TComponent* AOwner);

protected:
    void __fastcall PlaySound();

};

//----------------------------------------------------------------------------
extern PACKAGE TDlgAbout *DlgAbout;
//----------------------------------------------------------------------------
#endif
