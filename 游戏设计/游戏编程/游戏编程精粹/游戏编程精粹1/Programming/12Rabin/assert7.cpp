/* Copyright (C) Steve Rabin, 2000. 
 * All rights reserved worldwide.
 *
 * This software is provided "as is" without express or implied
 * warranties. You may freely copy and compile this source into
 * applications you distribute provided that the copyright text
 * below is included in the resulting source code, for example:
 * "Portions Copyright (C) Steve Rabin, 2000"
 */

#include "Assert.h"

void Test7()
{
    if (OpenClipboard(NULL))
    {
        HGLOBAL hMem;
        char szAssert[256];
        char* pMem;

        sprintf_s(szAssert, "Put assert info here");
        hMem = GlobalAlloc(GHND | GMEM_DDESHARE, strlen(szAssert) + 1);

        if (hMem)
        {
            pMem = (char*)GlobalLock(hMem);
            sprintf_s(pMem, 256, szAssert);
            GlobalUnlock(hMem);
            EmptyClipboard();
            SetClipboardData(CF_TEXT, hMem);
        }

        CloseClipboard();
    }
}