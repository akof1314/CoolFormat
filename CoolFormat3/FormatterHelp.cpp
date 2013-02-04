#include "StdAfx.h"
#include "FormatterHelp.h"
#include "Core\Cpp\AStyleInterface.h"
#include "Core\Html\HTidyInterface.h"
#include "Core\PHP\PhpTidy.h"
#include "Core\Js\JsTidy.h"
#include "Core\CSS\CssFormatter.h"
#include "Core\Json\JsonTidy.h"
#include "Core\SQL\SqlTidy.h"

CFormatterHelp::CFormatterHelp(void)
{
}

CFormatterHelp::~CFormatterHelp(void)
{
}

BOOL CFormatterHelp::DoFormatter( UINT nLanguage, const char *pTextIn, CString &strTextOut, CString &strMsgOut )
{
	switch (nLanguage)
	{
	case SYN_CPP:
		return FormatterCpp(pTextIn, strTextOut);
	case SYN_CS:
		return FormatterCs(pTextIn, strTextOut);
	case SYN_JAVA:
		return FormatterJava(pTextIn, strTextOut);
	case SYN_HTML:
		return FormatterHtml(pTextIn, strTextOut, strMsgOut);
	case SYN_XML:
		return FormatterXml(pTextIn, strTextOut, strMsgOut);
	case SYN_PHP:
		return FormatterPhp(pTextIn, strTextOut, strMsgOut);
	case SYN_JAVASCRIPT:
		return FormatterJs(pTextIn, strTextOut);
	case SYN_CSS:
		return FormatterCss(pTextIn, strTextOut, strMsgOut);
	case SYN_JSON:
		return FormatterJson(pTextIn, strTextOut, strMsgOut);
	case SYN_SQL:
		return FormatterSql(pTextIn, strTextOut);
	}
	return FALSE;
}

BOOL CFormatterHelp::FormatterCpp( const char *pTextIn, CString &strTextOut )
{
	AStyleInterface astyle;
	CStringA strTidy(g_GlobalTidy.m_TidyCpp);
	char *pTextOut = astyle.formatSource(pTextIn, strTidy);
	if (pTextOut == NULL)
	{
		return FALSE;
	}

	strTextOut = pTextOut;
	delete[] pTextOut;
	return TRUE;
}

BOOL CFormatterHelp::FormatterCs( const char *pTextIn, CString &strTextOut )
{
	AStyleInterface astyle;
	CStringA strTidy(g_GlobalTidy.m_TidyCSharp);
	strTidy.Append(" --mode=cs");
	char *pTextOut = astyle.formatSource(pTextIn, strTidy);
	if (pTextOut == NULL)
	{
		return FALSE;
	}

	strTextOut = pTextOut;
	delete[] pTextOut;
	return TRUE;
}

BOOL CFormatterHelp::FormatterJava( const char *pTextIn, CString &strTextOut )
{
	AStyleInterface astyle;
	CStringA strTidy(g_GlobalTidy.m_TidyJava);
	strTidy.Append(" --mode=java");
	char *pTextOut = astyle.formatSource(pTextIn, strTidy);
	if (pTextOut == NULL)
	{
		return FALSE;
	}

	strTextOut = pTextOut;
	delete[] pTextOut;
	return TRUE;
}

BOOL CFormatterHelp::FormatterHtml( const char *pTextIn, CString &strTextOut, CString &strMsgOut )
{
	HTidyInterface htidy;
	if (htidy.formatSource(pTextIn, strTextOut, strMsgOut))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CFormatterHelp::FormatterXml( const char *pTextIn, CString &strTextOut, CString &strMsgOut )
{
	HTidyInterface htidy(SYN_XML);
	if (htidy.formatSource(pTextIn, strTextOut, strMsgOut))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CFormatterHelp::FormatterPhp( const char *pTextIn, CString &strTextOut, CString &strMsgOut )
{
	PhpFormatter::PhpTidy ptidy;
	CStringA strTidy(g_GlobalTidy.m_TidyPhp);
	string strOut, strErr;
	bool bTidyOk = ptidy.PhpTidyMain(pTextIn, strTidy, strOut, strErr);	
	strTextOut = strOut.c_str();
	strMsgOut = strErr.c_str();
	return bTidyOk;
}

BOOL CFormatterHelp::FormatterJs( const char *pTextIn, CString &strTextOut )
{
	JsFormatter::JsTidy jtidy;
	CStringA strTidy(g_GlobalTidy.m_TidyJs);
	string strOut, strErr;
	bool bTidyOk = jtidy.JsTidyMain(pTextIn, strTidy, strOut);	
	strTextOut = strOut.c_str();
	return bTidyOk;
}

BOOL CFormatterHelp::FormatterCss( const char *pTextIn, CString &strTextOut, CString &strMsgOut )
{
	CssFormatterTidy::CssFormatter ctidy;
	CStringA strTidy(g_GlobalTidy.m_TidyCss);
	string strOut, strErr;
	bool bTidyOk = ctidy.CssTidyMain(pTextIn, strTidy, strOut, strErr);	
	strTextOut = strOut.c_str();
	strMsgOut = strErr.c_str();
	return bTidyOk;
}

BOOL CFormatterHelp::FormatterJson( const char *pTextIn, CString &strTextOut, CString &strMsgOut )
{
	JsonFormatter::JsonTidy jtidy;
	CStringA strTidy(g_GlobalTidy.m_TidyJson);
	string strOut, strErr;
	bool bTidyOk = jtidy.JsonTidyMain(pTextIn, strTidy, strOut, strErr);	
	strTextOut = strOut.c_str();
	strMsgOut = strErr.c_str();
	return bTidyOk;
}

BOOL CFormatterHelp::FormatterSql( const char *pTextIn, CString &strTextOut )
{
	SqlFormatter::SqlTidy stidy;
	CStringA strTidy(g_GlobalTidy.m_TidySql);
	string strOut, strErr;
	bool bTidyOk = stidy.SqlTidyMain(pTextIn, strTidy, strOut);	
	strTextOut = strOut.c_str();
	return bTidyOk;
}