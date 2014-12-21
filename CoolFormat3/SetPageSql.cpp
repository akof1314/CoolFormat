// SetPageSql.cpp : 实现文件

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageSql.h"

//////////////////////////////////////////////////////////////////////////
// CSetPageSql 对话框

CSetPageSql::CSetPageSql(LPCTSTR lpszTitle, CString& strTidy)
: CSetPageBase(lpszTitle, _T(""), strTidy)
{
}

CSetPageSql::~CSetPageSql()
{
}

void CSetPageSql::InitPropList()
{
	CMyBCGPProp* pGrouIndentation = new CMyBCGPProp(_T("Indentation"));
	CMyBCGPProp* pPropIndent = new CMyBCGPProp(_T("Indent using"), _T("Spaces"));
	pPropIndent->AddComboOption(_T("Spaces"), _T("ci0"),
		_T("select")
		_T("\r\n****id")
		_T("\r\nfrom")
		_T("\r\n****a\r\nwhere\r\n****a.id = 1"));
	pPropIndent->AddComboOption(_T("Tab"), _T("ci1"),
		_T("select")
		_T("\r\n--->id")
		_T("\r\nfrom")
		_T("\r\n--->a\r\nwhere\r\n--->a.id = 1"));
	pGrouIndentation->AddSubItem(pPropIndent);

	pPropIndent = new CMyBCGPProp(_T("Indent number"), (_variant_t)2);
	pPropIndent->SetNumberSpin(0, 100, _T("cn"),
		_T("//indent_number2")
		_T("\r\nselect")
		_T("\r\n  id")
		_T("\r\nfrom")
		_T("\r\n  a")
		_T("\r\nwhere")
		_T("\r\n  a.id = 1")
		_T("\r\n")
		_T("\r\n//indent_number4")
		_T("\r\nselect")
		_T("\r\n    id")
		_T("\r\nfrom")
		_T("\r\n    a")
		_T("\r\nwhere")
		_T("\r\n    a.id = 1"));
	pGrouIndentation->AddSubItem(pPropIndent);
	m_wndPropList.AddProperty(pGrouIndentation);

	CMyBCGPProp* pGrouSubquery = new CMyBCGPProp(_T("Subquery"));
	CMyBCGPProp* pPropSubquery = new CMyBCGPProp(_T("Endline on subquery"), _T("No"));
	pPropSubquery->AddComboOption(_T("Yes"), _T("el"),
		_T("select")
		_T("\r\n  id")
		_T("\r\nfrom")
		_T("\r\n  a")
		_T("\r\nwhere")
		_T("\r\n  a.id = ")
		_T("\r\n  (")
		_T("\r\n    select")
		_T("\r\n      no")
		_T("\r\n    from")
		_T("\r\n      b")
		_T("\r\n    where")
		_T("\r\n      b.id = 2")
		_T("\r\n  )"));
	pPropSubquery->AddComboOption(_T("No"), _T(""),
		_T("select")
		_T("\r\n  id")
		_T("\r\nfrom")
		_T("\r\n  a")
		_T("\r\nwhere")
		_T("\r\n  a.id = (")
		_T("\r\n    select")
		_T("\r\n      no")
		_T("\r\n    from")
		_T("\r\n      b")
		_T("\r\n    where")
		_T("\r\n      b.id = 2)"));
	pGrouSubquery->AddSubItem(pPropSubquery);

	pPropSubquery = new CMyBCGPProp(_T("Min subquery len"), (_variant_t)0);
	pPropSubquery->SetNumberSpin(0, 9999, _T("ml"),
		_T("//len0")
		_T("\r\nselect")
		_T("\r\n  id")
		_T("\r\nfrom")
		_T("\r\n  a")
		_T("\r\nwhere")
		_T("\r\n  a.id = (")
		_T("\r\n    select")
		_T("\r\n      no")
		_T("\r\n    from")
		_T("\r\n      b")
		_T("\r\n    where")
		_T("\r\n      b.id = 2)")
		_T("\r\n")
		_T("\r\n//len100")
		_T("\r\nselect")
		_T("\r\n  id")
		_T("\r\nfrom")
		_T("\r\n  a")
		_T("\r\nwhere")
		_T("\r\n  a.id = (select no from b where b.id = 2)"));
	pGrouSubquery->AddSubItem(pPropSubquery);
	m_wndPropList.AddProperty(pGrouSubquery);
}
