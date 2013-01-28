// SetPageJson.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageJson.h"


// CSetPageJson 对话框

IMPLEMENT_DYNCREATE(CSetPageJson, CBCGPPropertyPage)

CSetPageJson::CSetPageJson()
	: CBCGPPropertyPage(CSetPageJson::IDD)
{

}

CSetPageJson::~CSetPageJson()
{
}

void CSetPageJson::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetPageJson, CBCGPPropertyPage)
	ON_EN_SETFOCUS(IDC_EDIT_JSON_INDENT_NUMBER, &CSetPageJson::OnEnSetfocusEditJsonIndentNumber)
END_MESSAGE_MAP()


// CSetPageJson 消息处理程序

BOOL CSetPageJson::OnInitDialog()
{
	CBCGPPropertyPage::OnInitDialog();
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STR_VIEWFORMATTER);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_VIEWFORMATTER, strTemp);
	GetDlgItem(IDC_EDIT_VIEWFORMATTER)->SetFont(&g_GlobalUtils.m_fontWidth);

	InitLimit();
	SetTidyConfig(g_GlobalTidy.m_TidyJson);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSetPageJson::InitLimit()
{
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_JSON_INDENT_NUMBER))->SetRange(0, 100);
	GetDlgItem(IDC_EDIT_JSON_INDENT_NUMBER)->SetWindowText(_T("3"));
}

void CSetPageJson::SetViewEdit( LPCTSTR lpszText )
{
	SetDlgItemText(IDC_EDIT_VIEWFORMATTER, lpszText);
}

void CSetPageJson::SetTidyControl( LPCTSTR lpszTidy, int nPos, int nSize )
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
		GetDlgItem(IDC_EDIT_JSON_INDENT_NUMBER)->SetWindowText(strNumValue);
	}
}

void CSetPageJson::SetTidyConfig( LPCTSTR lpszTidy )
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

void CSetPageJson::GetTidyConfig( CString &strTidyValue )
{
	CString strTidy, strValue;
	strTidy.Empty();

	GetDlgItemText(IDC_EDIT_JSON_INDENT_NUMBER, strValue);
	strTidy.Append(_T("-cn"));
	strTidy.Append(strValue);

	strTidyValue.Append(strTidy);
}

void CSetPageJson::OnEnSetfocusEditJsonIndentNumber()
{
	CString strText;
	strText = _T("//indent_number3")
		_T("\r\n{")
		_T("\r\n   \"test\" : 123")
		_T("\r\n}")
		_T("\r\n")
		_T("\r\n//indent_number4")
		_T("\r\n{")
		_T("\r\n    \"test\" : 123")
		_T("\r\n}");
	SetViewEdit(strText);
}

void CSetPageJson::OnOK()
{
	CString strTidy;
	GetTidyConfig(strTidy);
	g_GlobalTidy.m_TidyJson = strTidy;

	CBCGPPropertyPage::OnOK();
}
