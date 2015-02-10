#include "stdafx.h"
#include "CoolFormatLib.h"
#include "StrUseful.h"
#include "GlobalTidy.h"
#include "FormatterHelp.h"

bool g_InitTidy = false;

#ifdef _WIN32
HMODULE hCFModule;
	#ifndef USE_LOCAL_CONFIG_FILE
		PROCESS_INFORMATION g_piProcInfo = { 0 };
	#endif
#else
std::string g_strDllPath;
#endif


std::string GetDllPath()
{
#ifdef _WIN32
	char szBuff[MAX_PATH];
	GetModuleFileNameA(hCFModule, szBuff, sizeof(szBuff));
	std::string strFileName(szBuff);
#else
    std::string strFileName(g_strDllPath);
#endif
    std::string::size_type pos = strFileName.rfind('/');
    if (pos == std::string::npos)
    {
        return NULL;
    }
    strFileName.erase(pos);
    return strFileName;
}

void CheckInit()
{
#ifdef _WIN32
#ifndef USE_LOCAL_CONFIG_FILE
	if (g_piProcInfo.hProcess)
	{
		DWORD dwExitCode = STILL_ACTIVE;
		if (GetExitCodeProcess(g_piProcInfo.hProcess, &dwExitCode))
		{
			if (dwExitCode != STILL_ACTIVE)
			{
				CloseHandle(g_piProcInfo.hProcess);
				CloseHandle(g_piProcInfo.hThread);
				ZeroMemory(&g_piProcInfo, sizeof(PROCESS_INFORMATION));

				g_InitTidy = false;
			}
		}
	}
#endif
#endif

	if (g_InitTidy)
	{
		return;
	}
	g_GlobalTidy.InitGlobalTidy(GetDllPath());
	g_InitTidy = true;
}

bool DoFormatter(unsigned int nLanguage, const std::string &strTextIn, std::string &strTextOut, std::string &strMsgOut, unsigned int /*uCodepage*/)
{
	CheckInit();
	CFormatterHelp formatter;
	return formatter.DoFormatter(nLanguage, strTextIn, strTextOut, strMsgOut);
}

COOLFORMATLIB_API bool DoFormatter(unsigned int nLanguage, const char *pszTextIn, char *pszTextOut, int &nTextOut, char *pszMsgOut, int &nMsgOut, unsigned int uCodepage /*= 0*/, const char *pszEol /*= NULL*/, const char *pszInitIndent /*= NULL*/)
{
	static std::string strTextOut, strMsgOut;
	if (pszTextOut == NULL)
	{
		strTextOut.clear();
		strMsgOut.clear();

		std::string strTextIn(pszTextIn);
		if (pszEol)
		{
			std::string strEol(pszEol);
			if (strEol.compare("\r") == 0)
			{
				strTextIn = strreplace_all(strTextIn, "\r", "\n");
			}
		}

		bool bResult = DoFormatter(nLanguage, strTextIn, strTextOut, strMsgOut, uCodepage);
		if (bResult)
		{
			if (pszEol)
			{
				std::string strEol(pszEol);
				strTextOut = strreplace_all(strTextOut, "\r", "");
				strTextOut = strreplace_all(strTextOut, "\n", pszEol);

				if (pszInitIndent)
				{
					std::string strInitIndent(pszInitIndent);
					std::string::size_type nInitIndentLen = strInitIndent.size();
					std::string::size_type nPos = nInitIndentLen;
					std::string::size_type nEolLen = strEol.size();

					strTextOut = strtrim_right(strTextOut);
					strTextOut.insert(0, strInitIndent);
					nPos = strTextOut.find(strEol, nPos);
					while (nPos != std::string::npos)
					{
						if (nPos == (strTextOut.size() - nEolLen))
						{
							break;
						}
						strTextOut.insert(nPos + nEolLen, strInitIndent);
						nPos = strTextOut.find(strEol, nPos + nInitIndentLen + nEolLen);
					}
				}
            }

			nTextOut = strTextOut.size();
			nMsgOut = strMsgOut.size();
		}
		return bResult;
	}
	else
	{
#ifdef _MSC_VER
		strTextOut._Copy_s(pszTextOut, nTextOut, nTextOut, 0);
		strMsgOut._Copy_s(pszMsgOut, nMsgOut, nMsgOut, 0);
#else
        strTextOut.copy(pszTextOut, nTextOut, 0);
		strMsgOut.copy(pszMsgOut, nMsgOut, 0);
#endif
		return true;
	}
}

COOLFORMATLIB_API void ShowSettings()
{
#ifdef _WIN32
#ifndef USE_LOCAL_CONFIG_FILE
	STARTUPINFO siStartInfo;
	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&siStartInfo);
	siStartInfo.wShowWindow = SW_SHOW;
	siStartInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	std::wstring strFileName(s2ws(GetDllPath()));
	strFileName.append(TEXT("\\CoolFormat.exe"));

	ZeroMemory(&g_piProcInfo, sizeof(PROCESS_INFORMATION));
	if (!CreateProcess(strFileName.c_str(), TEXT(" -s"), NULL, NULL, FALSE, NULL, NULL, NULL, &siStartInfo, &g_piProcInfo))
	{
		return;
	}
#endif
#endif
}
