// SetPageSql.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageSql.h"


// CSetPageSql 对话框

IMPLEMENT_DYNCREATE(CSetPageSql, CBCGPPropertyPage)

CSetPageSql::CSetPageSql()
	: CBCGPPropertyPage(CSetPageSql::IDD)
{

}

CSetPageSql::~CSetPageSql()
{
}

void CSetPageSql::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetPageSql, CBCGPPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO_SQL_INDENT_TAB, &CSetPageSql::OnCbnSelchangeComboSqlIndentTab)
	ON_EN_SETFOCUS(IDC_EDIT_SQL_INDENT_NUMBER, &CSetPageSql::OnEnSetfocusEditSqlIndentNumber)
	ON_BN_CLICKED(IDC_CHECK_SQL_ENDLINE, &CSetPageSql::OnBnClickedCheckSqlEndline)
	ON_EN_SETFOCUS(IDC_EDIT_SQL_SUB_NUMBER, &CSetPageSql::OnEnSetfocusEditSqlSubNumber)
END_MESSAGE_MAP()


// CSetPageSql 消息处理程序

BOOL CSetPageSql::OnInitDialog()
{
	CBCGPPropertyPage::OnInitDialog();
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STR_VIEWFORMATTER);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_VIEWFORMATTER, strTemp);
	GetDlgItem(IDC_EDIT_VIEWFORMATTER)->SetFont(&g_GlobalUtils.m_fontWidth);

	InitLimit();
	SetTidyConfig(g_GlobalTidy.m_TidySql);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSetPageSql::InitLimit()
{
	((CComboBox *)GetDlgItem(IDC_COMBO_SQL_INDENT_TAB))->SetCurSel(0);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_SQL_INDENT_NUMBER))->SetRange(0, 100);
	GetDlgItem(IDC_EDIT_SQL_INDENT_NUMBER)->SetWindowText(_T("2"));
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_SQL_SUB_NUMBER))->SetRange(0, 9999);
	GetDlgItem(IDC_EDIT_SQL_SUB_NUMBER)->SetWindowText(_T("100"));
}

void CSetPageSql::SetViewEdit( LPCTSTR lpszText )
{
	SetDlgItemText(IDC_EDIT_VIEWFORMATTER, lpszText);
}

void CSetPageSql::SetTidyControl( LPCTSTR lpszTidy, int nPos, int nSize )
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

	if (_T("cn") == strParam)
	{
		GetDlgItem(IDC_EDIT_SQL_INDENT_NUMBER)->SetWindowText(strNumValue);
	}
	else if (_T("ml") == strParam)
	{
		GetDlgItem(IDC_EDIT_SQL_SUB_NUMBER)->SetWindowText(strNumValue);
	}
	else if (_T("el") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_SQL_ENDLINE))->SetCheck(1);
	}
	else if (_T("ci") == strParam)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_SQL_INDENT_TAB))->SetCurSel(nNumValue);
	}
}

void CSetPageSql::SetTidyConfig( LPCTSTR lpszTidy )
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

void CSetPageSql::GetTidyConfig( CString &strTidyValue )
{
	CString strTidy, strValue;
	strTidy.Empty();

	if (((CButton *)GetDlgItem(IDC_CHECK_SQL_ENDLINE))->GetCheck())
	{
		strTidy.Append(_T("-el"));
	}
	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_SQL_INDENT_TAB))->GetCurSel())
	{
		strTidy.AppendFormat(_T("-ci"), ((CComboBox *)GetDlgItem(IDC_COMBO_SQL_INDENT_TAB))->GetCurSel());
	}
	GetDlgItemText(IDC_EDIT_SQL_INDENT_NUMBER, strValue);
	strTidy.Append(_T("-cn"));
	strTidy.Append(strValue);

	GetDlgItemText(IDC_EDIT_SQL_SUB_NUMBER, strValue);
	strTidy.Append(_T("-ml"));
	strTidy.Append(strValue);

	strTidyValue.Append(strTidy);
}
void CSetPageSql::OnCbnSelchangeComboSqlIndentTab()
{
	CString strText;
	switch (((CComboBox *)GetDlgItem(IDC_COMBO_SQL_INDENT_TAB))->GetCurSel())
	{
	case 0:strText = _T("select")
			   _T("\r\n****id")
			   _T("\r\nfrom")
			   _T("\r\n****a\r\nwhere\r\n****a.id = 1");
		break;
	case 1:strText = _T("select")
			   _T("\r\n--->id")
			   _T("\r\nfrom")
			   _T("\r\n--->a\r\nwhere\r\n--->a.id = 1");
		break;
	}
	SetViewEdit(strText);
}

void CSetPageSql::OnEnSetfocusEditSqlIndentNumber()
{
	CString strText;
	strText = _T("//indent_number2")
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
		_T("\r\n    a.id = 1");
	SetViewEdit(strText);
}

void CSetPageSql::OnBnClickedCheckSqlEndline()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_SQL_ENDLINE))->GetCheck())
	{
		strText = _T("select")
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
			_T("\r\n  )");
	} 
	else
	{
		strText = _T("select")
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
			_T("\r\n      b.id = 2)");
	}
	SetViewEdit(strText);
}

void CSetPageSql::OnEnSetfocusEditSqlSubNumber()
{
	CString strText;
	strText = _T("//len0")
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
		_T("\r\n  a.id = (select no from b where b.id = 2)");
	SetViewEdit(strText);
}

void CSetPageSql::OnOK()
{
	CString strTidy;
	GetTidyConfig(strTidy);
	g_GlobalTidy.m_TidySql = strTidy;
	CBCGPPropertyPage::OnOK();
}
