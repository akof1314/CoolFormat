#include "StdAfx.h"
#include "CoolFormat3.h"
#include "SynStyle.h"

CSynStyle::CSynStyle(void)
{
}

CSynStyle::~CSynStyle(void)
{
}

void CSynStyle::InitStyle( void )
{
	LPCTSTR lpszSubSection = _T("SynStyle");
	CString strSection = theApp.GetRegSectionPath(lpszSubSection);

	CBCGPRegistrySP regSP;
	CBCGPRegistry& reg = regSP.Create (FALSE, TRUE);

	if (reg.Open (strSection))
	{
		if (!reg.Read(_T("EdtFontName"), m_strEdtFontName))
		{
			m_strEdtFontName = _T("Consolas"); 
		}

		int iFontSize;
		if (!reg.Read(_T("EdtFontSize"), iFontSize))
		{
			iFontSize = 10;
		}
		m_uEdtFontSize = iFontSize;

		if (!reg.Read(_T("EdtFontBold"), m_bEdtFontBold))
		{
			m_bEdtFontBold = FALSE;
		}

		if (!reg.Read(_T("EdtFontItalic"), m_bEdtFontItalic))
		{
			m_bEdtFontItalic = FALSE;
		}

		if (!reg.Read(_T("HtmlFontName"), m_strHtmlFontName))
		{
			m_strHtmlFontName = _T("Consolas"); 
		}

		if (!reg.Read(_T("HtmlFontSize"), iFontSize))
		{
			iFontSize = 12;
		}
		m_uHtmlFontSize = iFontSize;

		if (!reg.Read(_T("HtmlFontBold"), m_bHtmlFontBold))
		{
			m_bHtmlFontBold = FALSE;
		}

		if (!reg.Read(_T("HtmlFontItalic"), m_bHtmlFontItalic))
		{
			m_bHtmlFontItalic = FALSE;
		}

		if (!reg.Read(_T("HtmlShowBorder"), m_bHtmlShowBorder))
		{
			m_bHtmlShowBorder = TRUE;
		}

		if (!reg.Read(_T("HtmlBorderWidth"), m_iHtmlBorderWidth))
		{
			m_iHtmlBorderWidth = 1;
		}

		if (!reg.Read(_T("HtmlBorderStyle"), m_iHtmlBorderStyle))
		{
			m_iHtmlBorderStyle = 1;
		}

		if (!reg.Read(_T("HtmlBorderColor"), m_clrHtmlBorderColor))
		{
			m_clrHtmlBorderColor = RGB(227, 227, 227);
		}

		if (!reg.Read(_T("HtmlShowLineNumber"), m_bHtmlShowLineNumber))
		{
			m_bHtmlShowLineNumber = TRUE;
		}

		if (!reg.Read(_T("HtmlBackgroundColor"), m_clrHtmlBackgroundColor))
		{
			m_clrHtmlBackgroundColor = RGB(239, 239, 239);
		}		

		if (!reg.Read(_T("HtmlShowSidebar"), m_bHtmlShowSidebar))
		{
			m_bHtmlShowSidebar = TRUE;
		}

		if (!reg.Read(_T("HtmlShowLangTitle"), m_bHtmlShowLangTitle))
		{
			m_bHtmlShowLangTitle = TRUE;
		}

		if (!reg.Read(_T("HtmlShowAddTitle"), m_bHtmlShowAddTitle))
		{
			m_bHtmlShowAddTitle = FALSE;
		}

		if (!reg.Read(_T("HtmlAddTitle"), m_strHtmlAddTitle))
		{
			m_strHtmlAddTitle = _T("By CoolFormat");
		}

		if (!reg.Read(_T("HtmlLineHeight"), m_iHtmlLineHeight))
		{
			m_iHtmlLineHeight = 15;
		}

		if (!reg.Read(_T("HtmlAutoCopy"), m_bHtmlAutoCopy))
		{
			m_bHtmlAutoCopy = FALSE;
		}

		if (!reg.Read(_T("HtmlCopyCode"), m_bHtmlCopyCode))
		{
			m_bHtmlCopyCode = FALSE;
		}
	}
	else
	{
		m_strEdtFontName = _T("Consolas");
		m_uEdtFontSize = 10;
		m_bEdtFontBold = FALSE;
		m_bEdtFontItalic = FALSE;

		m_strHtmlFontName = _T("Consolas");
		m_uHtmlFontSize = 12;
		m_bHtmlFontBold = FALSE;
		m_bHtmlFontItalic = FALSE;

		m_bHtmlShowBorder = TRUE;
		m_iHtmlBorderWidth = 1;
		m_iHtmlBorderStyle = 1;
		m_clrHtmlBorderColor = RGB(227, 227, 227);

		m_clrHtmlBackgroundColor = RGB(239, 239, 239);
		m_bHtmlShowLineNumber = TRUE;
		m_bHtmlShowSidebar = TRUE;
		m_iHtmlLineHeight = 15;

		m_bHtmlShowLangTitle = TRUE;
		m_bHtmlShowAddTitle = FALSE;
		m_strHtmlAddTitle = _T("By CoolFormat");
		m_bHtmlAutoCopy = FALSE;
		m_bHtmlCopyCode = FALSE;
	}	
}