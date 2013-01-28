// SetPageJS.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageJS.h"

//////////////////////////////////////////////////////////////////////////
// CSetPageJS 对话框

IMPLEMENT_DYNCREATE(CSetPageJS, CBCGPPropertyPage)

CSetPageJS::CSetPageJS()
	: CBCGPPropertyPage(CSetPageJS::IDD)
{

}

CSetPageJS::~CSetPageJS()
{
}

void CSetPageJS::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetPageJS, CBCGPPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO_JS_INDENT_TAB, &CSetPageJS::OnCbnSelchangeComboJsIndentTab)
	ON_CBN_SELCHANGE(IDC_COMBO_JS_INDENT_STYLE, &CSetPageJS::OnCbnSelchangeComboJsIndentStyle)
	ON_EN_SETFOCUS(IDC_EDIT_JS_INDENT_NUMBER, &CSetPageJS::OnEnSetfocusEditJsIndentNumber)
END_MESSAGE_MAP()

BOOL CSetPageJS::OnInitDialog()
{
	CBCGPPropertyPage::OnInitDialog();
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STR_VIEWFORMATTER);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_VIEWFORMATTER, strTemp);
	GetDlgItem(IDC_EDIT_VIEWFORMATTER)->SetFont(&g_GlobalUtils.m_fontWidth);

	InitLimit();
	SetTidyConfig(g_GlobalTidy.m_TidyJs);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSetPageJS::SetTidyConfig( LPCTSTR lpszTidy )
{
	int lenTidy = _tcsclen(lpszTidy);
	if (lenTidy <= 0 || lpszTidy[0] != '-')
	{
		return;
	}

	int nOption = -1;
	for (int i = 0; i < lenTidy; ++i)
	{
		if (lpszTidy[i] == '-')
		{
			if (-1 != nOption)
			{
				SetTidyControl(lpszTidy, nOption, i - nOption);
			}
			nOption = i;
		}
	}
	SetTidyControl(lpszTidy, nOption, lenTidy - nOption);
}

void CSetPageJS::GetTidyConfig( CString &strTidyValue )
{
	CString strTidy, strValue;
	strTidy.Empty();

	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_JS_INDENT_TAB))->GetCurSel())
	{
		strTidy.AppendFormat(_T("-ci%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_JS_INDENT_TAB))->GetCurSel());
	}
	if (1 == ((CComboBox *)GetDlgItem(IDC_COMBO_JS_INDENT_STYLE))->GetCurSel())
	{
		strTidy.Append(_T("-nb"));
	}
	GetDlgItemText(IDC_EDIT_JS_INDENT_NUMBER, strValue);
	strTidy.Append(_T("-cn"));
	strTidy.Append(strValue);

	strTidyValue.Append(strTidy);
}

void CSetPageJS::InitLimit()
{
	((CComboBox *)GetDlgItem(IDC_COMBO_JS_INDENT_TAB))->SetCurSel(0);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_JS_INDENT_NUMBER))->SetRange(0, 100);
	GetDlgItem(IDC_EDIT_JS_INDENT_NUMBER)->SetWindowText(_T("4"));
	((CComboBox *)GetDlgItem(IDC_COMBO_JS_INDENT_STYLE))->SetCurSel(0);
}

void CSetPageJS::SetViewEdit( LPCTSTR lpszText )
{
	SetDlgItemText(IDC_EDIT_VIEWFORMATTER, lpszText);
}

void CSetPageJS::SetTidyControl( LPCTSTR lpszTidy, int nPos, int nSize )
{
	if (lpszTidy[nPos] != '-' || nSize < 2)
	{
		return;
	}

	int nNumValue = nSize;
	for (int i = nPos + 1; i < nPos + nSize; ++i)
	{
		if (!_istalpha(lpszTidy[i]))
		{
			nNumValue = i - nPos;
			break;
		}
	}
	CString strParam(lpszTidy + nPos + 1, nNumValue - 1);
	if (nNumValue != nSize)
	{
		CString strNum(lpszTidy + nPos + nNumValue, nSize - nNumValue);
		nNumValue = _ttoi(strNum);
	}
	else
	{
		nNumValue = 0;
	}
	CString strNumValue;
	strNumValue.Format(_T("%d"), nNumValue);

	if (_T("nb") == strParam)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_JS_INDENT_STYLE))->SetCurSel(1);
	} 
	else if (_T("ci") == strParam)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_JS_INDENT_TAB))->SetCurSel(nNumValue);
	}
	else if (_T("cn") == strParam)
	{
		GetDlgItem(IDC_EDIT_JS_INDENT_NUMBER)->SetWindowText(strNumValue);
	}
}
void CSetPageJS::OnCbnSelchangeComboJsIndentTab()
{
	CString strText;
	switch (((CComboBox *)GetDlgItem(IDC_COMBO_JS_INDENT_TAB))->GetCurSel())
	{
	case 0:strText = _T("if ('this_is' == /an_example/) {")
			   _T("\r\n****of_beautifer();")
			   _T("\r\n} else {")
			   _T("\r\n****var a = b ? (c % d) : e[f];")
			   _T("\r\n}");
		break;
	case 1:
		strText = _T("if ('this_is' == /an_example/) {")
			_T("\r\n--->of_beautifer();")
			_T("\r\n} else {")
			_T("\r\n--->var a = b ? (c % d) : e[f];")
			_T("\r\n}");
		break;
	}
	SetViewEdit(strText);
}

void CSetPageJS::OnCbnSelchangeComboJsIndentStyle()
{
	CString strText;
	switch (((CComboBox *)GetDlgItem(IDC_COMBO_JS_INDENT_STYLE))->GetCurSel())
	{
	case 0:strText = _T("if ('this_is' == /an_example/) {")
			   _T("\r\n    of_beautifer();")
			   _T("\r\n} else {")
			   _T("\r\n    var a = b ? (c % d) : e[f];")
			   _T("\r\n}");
		break;
	case 1:strText = _T("if ('this_is' == /an_example/)")
			   _T("\r\n{")
			   _T("\r\n    of_beautifer();")
			   _T("\r\n}")
			   _T("\r\nelse")
			   _T("\r\n{")
			   _T("\r\n    var a = b ? (c % d) : e[f];")
			   _T("\r\n}");
		break;
	}
	SetViewEdit(strText);
}

void CSetPageJS::OnEnSetfocusEditJsIndentNumber()
{
	CString strText;
	strText = _T("//indent_number4")
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
		_T("\r\n}");
	SetViewEdit(strText);
}

void CSetPageJS::OnOK()
{
	CString strTidy;
	GetTidyConfig(strTidy);
	g_GlobalTidy.m_TidyJs = strTidy;

	CBCGPPropertyPage::OnOK();
}
