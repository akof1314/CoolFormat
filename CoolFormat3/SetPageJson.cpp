// SetPageJson.cpp : 实现文件

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageJson.h"

//////////////////////////////////////////////////////////////////////////
// CSetPageJson 对话框

CSetPageJson::CSetPageJson(LPCTSTR lpszTitle, CString& strTidy)
: CSetPageBase(lpszTitle, _T(""), strTidy)
{
}

CSetPageJson::~CSetPageJson()
{
}

void CSetPageJson::InitPropList()
{
	CSetPageBase::InitPropList();
	return;
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
