//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------



















USEFORM("TFormDBRecord.cpp", FormDBRecord);
USEFORM("TDlgSetup.cpp", DlgSetup);
USEFORM("TDlgAbout.cpp", DlgAbout);
USEFORM("TFormDBSearch.cpp", FormDBSearch);
USEFORM("TFormMain.cpp", FormMain);
USEFORM("TFormDebug.cpp", FormDebug);
USEFORM("TDatabanker.cpp", DataBanker); /* TDataModule: File Type */
//---------------------------------------------------------------------------
#ifdef _WIN64
WINAPI int _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
#else
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
#endif
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->CreateForm(__classid(TDataBanker), &DataBanker);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
