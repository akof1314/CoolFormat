#include "StdAfx.h"
#include "FormatterHelp.h"
#include "CFCssTidy.h"
#include "CFSqlTidy.h"
#include "CFJsonTidy.h"
#include "CFJsTidy.h"
#include "CFPhpTidy.h"
#include "CFHtmlTidy.h"
#include "CFCppTidy.h"
#include "CFVerilogTidy.h"

#ifdef _DEBUG
#pragma comment(lib, "CssTidyLibd.lib")
#pragma comment(lib, "SqlFormatterLibd.lib")
#pragma comment(lib, "JsonCppLibd.lib")
#pragma comment(lib, "JsFormatterLibd.lib")
#pragma comment(lib, "PhpFormatterLibd.lib")
#pragma comment(lib, "tidylibd.lib")
#pragma comment(lib, "AStyleLibd.lib")
#pragma comment(lib, "VerilogFormatterLibd.lib")
#else
#pragma comment(lib, "CssTidyLib.lib")
#pragma comment(lib, "SqlFormatterLib.lib")
#pragma comment(lib, "JsonCppLib.lib")
#pragma comment(lib, "JsFormatterLib.lib")
#pragma comment(lib, "PhpFormatterLib.lib")
#pragma comment(lib, "tidylib.lib")
#pragma comment(lib, "AStyleLib.lib")
#pragma comment(lib, "VerilogFormatterLib.lib")
#endif // _DEBUG

CFormatterHelp::CFormatterHelp(void)
{
}

CFormatterHelp::~CFormatterHelp(void)
{
}

BOOL CFormatterHelp::DoFormatter(UINT nLanguage, const CString &strTextIn, CString &strTextOut, CString &strMsgOut, UINT uCodepage)
{
	CCFBaseTidy* pTidy = NULL;
	std::string strTidy;

	switch (nLanguage)
	{
	case SYN_CPP:
	{
		pTidy = new CCFCppTidy();
		CString strNewTidy(g_GlobalTidy.m_TidyCpp); 
		strNewTidy.Replace(_T("-"), _T(" -"));
		strTidy = CT2A(strNewTidy);
		strTidy.append(" --mode=c");
	}
	break;
	case SYN_CS:
	{
		pTidy = new CCFCppTidy();
		CString strNewTidy(g_GlobalTidy.m_TidyCSharp);
		strNewTidy.Replace(_T("-"), _T(" -"));
		strTidy = CT2A(strNewTidy);
		strTidy.append(" --mode=cs");
	}
	break;
	case SYN_JAVA:
	{
		pTidy = new CCFCppTidy();
		CString strNewTidy(g_GlobalTidy.m_TidyJava);
		strNewTidy.Replace(_T("-"), _T(" -"));
		strTidy = CT2A(strNewTidy);
		strTidy.append(" --mode=java");
	}
	break;
	case SYN_OBJECTIVEC:
	{
		pTidy = new CCFCppTidy();
		CString strNewTidy(g_GlobalTidy.m_TidyObjectiveC);
		strNewTidy.Replace(_T("-"), _T(" -"));
		strTidy = CT2A(strNewTidy);
		strTidy.append(" --mode=c");
	}
	break;
	case SYN_HTML:
	{
		pTidy = new CCFHtmlTidy();
		strTidy = CT2A(g_GlobalTidy.m_TidyHtml);
	}
	break;
	case SYN_XML:
	{
		pTidy = new CCFHtmlTidy();
		strTidy = CT2A(g_GlobalTidy.m_TidyXml);
	}
	break;
	case SYN_PHP:
	{
		pTidy = new CCFPhpTidy();
		strTidy = CT2A(g_GlobalTidy.m_TidyPhp);
	}
	break;
	case SYN_JAVASCRIPT:
	{
		pTidy = new CCFJsTidy();
		strTidy = CT2A(g_GlobalTidy.m_TidyJs);
	}
	break;
	case SYN_CSS:
	{
		pTidy = new CCFCssTidy();
		strTidy = CT2A(g_GlobalTidy.m_TidyCss);
	}
	break;
	case SYN_JSON:
	{
		pTidy = new CCFJsonTidy();
		strTidy = CT2A(g_GlobalTidy.m_TidyJson);
	}
	break;
	case SYN_SQL:
	{
		pTidy = new CCFSqlTidy();
		strTidy = CT2A(g_GlobalTidy.m_TidySql);
	}
	break;
    case SYN_VERILOG:
    {
        pTidy = new CCFVerilogTidy();
        strTidy = CT2A(g_GlobalTidy.m_TidyVerilog);
    }
    break;
	default:
		return FALSE;
	}
	
	std::string strOut, strErr;
	bool bTidyOk = pTidy->TidyMain(CT2A(strTextIn, uCodepage), strTidy.c_str(), strOut, strErr);
	strTextOut = CA2T(strOut.c_str(), uCodepage);
	strMsgOut = strErr.c_str();
	delete pTidy;
	return bTidyOk;
}
