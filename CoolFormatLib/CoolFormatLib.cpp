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

COOLFORMATLIB_API bool DoFormatter(unsigned int nLanguage, const std::string &strTextIn, std::string &strTextOut, std::string &strMsgOut, unsigned int uCodepage)
{
	CheckInit();
	CFormatterHelp formatter;
	return formatter.DoFormatter(nLanguage, strTextIn, strTextOut, strMsgOut, uCodepage);
}

COOLFORMATLIB_API void ShowSettings()
{
	g_InitTidy = false;
}
