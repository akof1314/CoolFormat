// SetPageJS.cpp : 实现文件

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageJS.h"

//////////////////////////////////////////////////////////////////////////
// CSetPageJS 对话框

CSetPageJS::CSetPageJS(LPCTSTR lpszTitle, CString& strTidy)
: CSetPageBase(lpszTitle, _T(""), strTidy)
{
}

CSetPageJS::~CSetPageJS()
{
}

void CSetPageJS::InitPropList()
{
	CMyBCGPProp* pGrouBracket = new CMyBCGPProp(_T("Bracket"));
	CMyBCGPProp* pPropBracket = new CMyBCGPProp(_T("Bracket style"), _T("Attach"));
	pPropBracket->AddComboOption(_T("Attach"), _T(""),
		_T("if ('this_is' == /an_example/) {")
		_T("\r\n    of_beautifer();")
		_T("\r\n} else {")
		_T("\r\n    var a = b ? (c % d) : e[f];")
		_T("\r\n}"));
	pPropBracket->AddComboOption(_T("Break"), _T("nb"),
		_T("if ('this_is' == /an_example/)")
		_T("\r\n{")
		_T("\r\n    of_beautifer();")
		_T("\r\n}")
		_T("\r\nelse")
		_T("\r\n{")
		_T("\r\n    var a = b ? (c % d) : e[f];")
		_T("\r\n}"));
	pGrouBracket->AddSubItem(pPropBracket);
	m_wndPropList.AddProperty(pGrouBracket);

	CMyBCGPProp* pGrouIndentation = new CMyBCGPProp(_T("Indentation"));
	CMyBCGPProp* pPropIndent = new CMyBCGPProp(_T("Indent using"), _T("Spaces"));
	pPropIndent->AddComboOption(_T("Spaces"), _T("ci0"),
		_T("if ('this_is' == /an_example/) {")
		_T("\r\n****of_beautifer();")
		_T("\r\n} else {")
		_T("\r\n****var a = b ? (c % d) : e[f];")
		_T("\r\n}"));
	pPropIndent->AddComboOption(_T("Tab"), _T("ci1"),
		_T("if ('this_is' == /an_example/) {")
		_T("\r\n--->of_beautifer();")
		_T("\r\n} else {")
		_T("\r\n--->var a = b ? (c % d) : e[f];")
		_T("\r\n}"));
	pGrouIndentation->AddSubItem(pPropIndent);

	pPropIndent = new CMyBCGPProp(_T("Indent number"), (_variant_t)4);
	pPropIndent->SetNumberSpin(0, 100, _T("cn"),
		_T("//indent_number4")
		_T("\r\nif ('this_is' == /an_example/) {")
		_T("\r\n    of_beautifer();")
		_T("\r\n} else {")
		_T("\r\n    var a = b ? (c % d) : e[f];")
		_T("\r\n}")
		_T("\r\n")
		_T("\r\n//indent_number5")
		_T("\r\nif ('this_is' == /an_example/) {")
		_T("\r\n     of_beautifer();")
		_T("\r\n} else {")
		_T("\r\n     var a = b ? (c % d) : e[f];")
		_T("\r\n}"));
	pGrouIndentation->AddSubItem(pPropIndent);
	m_wndPropList.AddProperty(pGrouIndentation);
}
