// SetPageBase.cpp : 实现文件

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageBase.h"

//////////////////////////////////////////////////////////////////////////
// CSetPageBase 对话框

IMPLEMENT_DYNAMIC(CSetPageBase, CBCGPPropertyPage)

CSetPageBase::CSetPageBase(LPCTSTR lpszTitle, CString& strTidy)
	: CBCGPPropertyPage(CSetPageBase::IDD)
{
	m_psp.dwFlags |= PSP_USETITLE;
	m_psp.pszTitle = lpszTitle;
	m_strTidy = &strTidy;
}

CSetPageBase::~CSetPageBase()
{
}

void CSetPageBase::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSetPageBase, CBCGPPropertyPage)
END_MESSAGE_MAP()

// CSetPageBase 消息处理程序

BOOL CSetPageBase::OnInitDialog()
{
	CBCGPPropertyPage::OnInitDialog();

	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STR_VIEWFORMATTER);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_VIEWFORMATTER, strTemp);
	bNameVaild = strTemp.LoadString(IDS_STR_OPTIONFORMATTER);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_OPTIONFORMATTER, strTemp);
	GetDlgItem(IDC_EDIT_VIEWFORMATTER)->SetFont(&g_GlobalUtils.m_fontWidth);

	CRect rectPropList;
	GetDlgItem(IDC_PROPLIST_LOCATION)->GetClientRect(&rectPropList);
	GetDlgItem(IDC_PROPLIST_LOCATION)->MapWindowPoints(this, &rectPropList);
	GetDlgItem(IDC_PROPLIST_LOCATION)->ShowWindow(SW_HIDE);

	m_wndPropList.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectPropList, this, (UINT)-1);
	m_wndPropList.SetPreviewWnd(GetDlgItem(IDC_EDIT_VIEWFORMATTER));

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDesciptionArea(FALSE);
	m_wndPropList.SetVSDotNetLook(TRUE);
	m_wndPropList.MarkModifiedProperties(TRUE);
	m_wndPropList.SetNameAlign(DT_LEFT);
	m_wndPropList.SetAlphabeticMode(FALSE);
	m_wndPropList.SetShowDragContext(FALSE);
	m_wndPropList.EnableToolBar(TRUE);
	m_wndPropList.EnableSearchBox(TRUE);

	InitPropList();
	InitTidyConfig();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CSetPageBase::InitTidyConfig()
{
	ASSERT(m_wndPropList.ValidateShort());

	SetTidyConfig(*m_strTidy);
	m_wndPropList.CommitModifiedValues(FALSE);
}

void CSetPageBase::EndTidyConfig()
{
	CString strTidy;
	GetTidyConfig(strTidy);
	*m_strTidy = strTidy;
}

void CSetPageBase::SetTidyConfig(LPCTSTR lpszTidy)
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

void CSetPageBase::SetTidyControl(LPCTSTR lpszTidy, int nPos, int nSize)
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
		nNumValue = INT_MIN;
	}
	
	if (!SetTidyProp(strParam, nNumValue))
	{
		strParam.AppendFormat(_T("%d"), nNumValue);
		SetTidyProp(strParam, nNumValue);
	}
}

BOOL CSetPageBase::SetTidyProp(LPCTSTR lpszParam, int nNumValue)
{
	CBCGPProp* pProp = m_wndPropList.FindItemByShort(lpszParam);
	if (pProp)
	{
		CMyBCGPProp* pMyProp = DYNAMIC_DOWNCAST(CMyBCGPProp, pProp);
		if (pMyProp)
		{
			pMyProp->SetValueByShort(lpszParam, nNumValue);
		}
	}
	return pProp != NULL;
}

void CSetPageBase::GetTidyConfig(CString &strTidyValue)
{
	m_wndPropList.GetResultShorts(strTidyValue);
}

void CSetPageBase::OnOK()
{
	EndTidyConfig();
	CBCGPPropertyPage::OnOK();
}
