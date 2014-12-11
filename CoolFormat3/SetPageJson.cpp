// SetPageJson.cpp : 实现文件

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageJson.h"

//////////////////////////////////////////////////////////////////////////
// CSetPageJson 对话框

CSetPageJson::CSetPageJson()
	: CSetPageBase()
{
	m_psp.dwFlags |= PSP_USETITLE;
	m_psp.pszTitle = _T("JSON");
}

CSetPageJson::~CSetPageJson()
{
}

void CSetPageJson::InitPropList()
{
	SetWindowText(_T("JSON"));
	CMyBCGPProp* pGrouIndentation = new CMyBCGPProp(_T("Indentation"));
	CMyBCGPProp* pPropIndent = new CMyBCGPProp(_T("Indent number"), (_variant_t)3);
	pPropIndent->SetNumberSpin(0, 100, _T("cn"), 
		_T("//indent_number3")
		_T("\r\n{")
		_T("\r\n   \"test\" : 123")
		_T("\r\n}")
		_T("\r\n")
		_T("\r\n//indent_number4")
		_T("\r\n{")
		_T("\r\n    \"test\" : 123")
		_T("\r\n}"));

	pGrouIndentation->AddSubItem(pPropIndent);
	m_wndPropList.AddProperty(pGrouIndentation);
}

void CSetPageJson::InitTidyConfig()
{
	SetTidyConfig(g_GlobalTidy.m_TidyJson);
}

void CSetPageJson::EndTidyConfig()
{
	CString strTidy;
	GetTidyConfig(strTidy);
	g_GlobalTidy.m_TidyJson = strTidy;
}

void CSetPageJson::SetTidyProp(LPCTSTR lpszParam, int nNumValue)
{
	CBCGPProp* pProp = m_wndPropList.FindItemByShort(lpszParam);
	if (pProp)
	{
		pProp->SetValue(nNumValue);
	}
}
