#pragma once
#include <atlstr.h>

CString GetStartPath(HMODULE hModule = NULL);
BOOL Run(LPCTSTR lpszCmdLine);
CStringA GetCurrentTimeStr(LPCSTR lpszFormat = NULL);