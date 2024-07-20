//---------------------------------------------------------------------------
#ifndef utilsH
#define utilsH

#include <vcl.h>
#include <vector>

#include "commdefs.h"

using namespace std;

typedef vector<TBitmap*> TVecPtrBitmaps;

class TUtils
{
    public:
        static bool __fastcall IsUnique(TVecInt& Ids);
        static bool __fastcall IsUnique(int nId, TVecInt& Ids);

        static void __fastcall Remove(int nId, TVecInt& Ids);
		static void __fastcall MergeUnique(TVecInt& A, TVecInt& B, TVecInt& C);
		static bool __fastcall IsIn(int nId, TVecInt& Ids);

        static void __fastcall LoadDataTest();
};

//---------------------------------------------------------------------------
#endif


