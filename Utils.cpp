
#include "stdafx.h"
#include <atlimage.h>
#include <time.h>
#include <Gdiplus.h>
#include "Utils.h"

using namespace Gdiplus;

#pragma comment(lib,"gdiplus") 


CString GetStartPath(HMODULE hModule/* = NULL*/)
{
	TCHAR szTemp[MAX_PATH];
	GetModuleFileName(hModule, szTemp, sizeof(szTemp) / sizeof(TCHAR));
	_tcsrchr(szTemp, '\\')[1] = 0;
	return (CString)szTemp;
}

BOOL Run(LPCTSTR lpszCmdLine)
{
	BOOL bSuccess = FALSE;
	CString strCmdLine = lpszCmdLine;
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	bSuccess = ::CreateProcess(NULL, (LPTSTR)(LPCTSTR)strCmdLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	return bSuccess;
}

CStringA GetCurrentTimeStr(LPCSTR lpszFormat/* = NULL*/) {
	time_t t;
	time(&t);
	char tmp[64] = {0};
	struct tm tmTemp;
	localtime_s(&tmTemp, &t);
	if (lpszFormat) {
		strftime(tmp, sizeof(tmp), lpszFormat, &tmTemp);
	} else {
		strftime(tmp, sizeof(tmp), "%Y-%m-%d_%H:%M:%S ", &tmTemp);
	}
	return tmp;
}