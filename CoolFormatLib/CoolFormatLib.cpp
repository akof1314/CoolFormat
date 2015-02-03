// CoolFormatLib.cpp : 定义 DLL 应用程序的导出函数。
#include "stdafx.h"
#include "CoolFormatLib.h"
#include "GlobalTidy.h"
#include "FormatterHelp.h"

bool g_InitTidy = false;

void CheckInit()
{
	if (g_InitTidy)
	{
		return;
	}
	g_GlobalTidy.InitGlobalTidy();
	g_InitTidy = true;
}

bool DoFormatter(unsigned int nLanguage, const std::string &strTextIn, std::string &strTextOut, std::string &strMsgOut, unsigned int uCodepage)
{
	CheckInit();
	CFormatterHelp formatter;
	return formatter.DoFormatter(nLanguage, strTextIn, strTextOut, strMsgOut, uCodepage);
}

COOLFORMATLIB_API bool DoFormatter(unsigned int nLanguage, const char *pszTextIn, char *pszTextOut, int &nTextOut, char *pszMsgOut, int &nMsgOut, unsigned int uCodepage)
{
	static std::string strTextOut, strMsgOut;
	if (pszTextOut == NULL)
	{
		bool bResult = DoFormatter(nLanguage, pszTextIn, strTextOut, strMsgOut, uCodepage);
		if (bResult)
		{
			nTextOut = strTextOut.size();
			nMsgOut = strMsgOut.size();
		}
		return bResult;
	}
	else
	{
		strTextOut._Copy_s(pszTextOut, nTextOut, nTextOut, 0);
		strMsgOut._Copy_s(pszMsgOut, nMsgOut, nMsgOut, 0);
		return true;
	}
}

COOLFORMATLIB_API void ShowSettings()
{
	STARTUPINFO siStartInfo;
	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&siStartInfo);
	siStartInfo.wShowWindow = SW_SHOW;
	siStartInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	PROCESS_INFORMATION piProcInfo;
	ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

	TCHAR szBuff[MAX_PATH];
	GetModuleFileName(hCFModule, szBuff, sizeof(szBuff));
	std::wstring strFileName(szBuff);
	std::wstring::size_type pos = strFileName.rfind('\\');
	if (pos == std::wstring::npos)
	{
		return;
	}
	strFileName.erase(pos);
	strFileName.append(TEXT("\\CoolFormat.exe"));

	if (!CreateProcess(strFileName.c_str(), TEXT(" -s"), NULL, NULL, FALSE, NULL, NULL, NULL, &siStartInfo, &piProcInfo))
	{
		return;
	}

	g_InitTidy = false;
}
