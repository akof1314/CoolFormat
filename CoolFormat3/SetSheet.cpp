// SetSheet.cpp : 实现文件

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetSheet.h"

#include "SetPageCpp.h"
#include "SetPageJS.h"
#include "SetPageHtml.h"
#include "SetPagePHP.h"
#include "SetPageCSS.h"
#include "SetPageJson.h"
#include "SetPageSql.h"
#include "SetPageBase.h"

#define  IDC_SETSHEET_DEFAULT 501
// CSetSheet

//IMPLEMENT_DYNAMIC(CSetSheet, CPropertySheet)

CSetSheet::CSetSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CBCGPPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CSetSheet::CSetSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CBCGPPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

CSetSheet::~CSetSheet()
{
}


BEGIN_MESSAGE_MAP(CSetSheet, CBCGPPropertySheet)
END_MESSAGE_MAP()


// CSetSheet 消息处理程序

BOOL CSetSheet::OnInitDialog()
{
	BOOL bResult = CBCGPPropertySheet::OnInitDialog();

	CRect rc;
	GetClientRect(&rc);
	rc.left += 9;
	rc.top = rc.bottom - 24;
	rc.right = rc.left + 100;
	rc.bottom = rc.top + 15;
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDC_BUTTON_DEFAULTEXT);
	ASSERT(bNameVaild);	
	m_btnDefaultLink.Create(strTemp, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, rc, this, IDC_SETSHEET_DEFAULT);
	m_btnDefaultLink.SizeToContent();

	bNameVaild = strTemp.LoadString(IDOK);
	ASSERT(bNameVaild);
	SetDlgItemText(IDOK, strTemp);

	bNameVaild = strTemp.LoadString(IDCANCEL);
	ASSERT(bNameVaild);
	SetDlgItemText(IDCANCEL, strTemp);
	GetDlgItem(IDCANCEL)->SetFocus();
	return FALSE;
}

BOOL CSetSheet::PreTranslateMessage(MSG* pMsg)
{
	if (WM_LBUTTONDOWN == pMsg->message)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_SETSHEET_DEFAULT)->GetSafeHwnd())
		{
			CString strTemp;
			BOOL bNameVaild = strTemp.LoadString(IDS_MSG_GODEFAULTOUT);
			ASSERT(bNameVaild);
			if (CFMessageBox(strTemp, MB_YESNO | MB_ICONINFORMATION) == IDYES)
			{
				g_GlobalTidy.m_TidyCpp = g_GlobalTidy.m_TidyNames[SYN_CPP].tidyName;
				g_GlobalTidy.m_TidyJava = g_GlobalTidy.m_TidyNames[SYN_JAVA].tidyName;
				g_GlobalTidy.m_TidyCSharp = g_GlobalTidy.m_TidyNames[SYN_CS].tidyName;
				g_GlobalTidy.m_TidyHtml = g_GlobalTidy.m_TidyNames[SYN_HTML].tidyName;
				g_GlobalTidy.m_TidyXml = g_GlobalTidy.m_TidyNames[SYN_XML].tidyName;
				g_GlobalTidy.m_TidyPhp = g_GlobalTidy.m_TidyNames[SYN_PHP].tidyName;
				g_GlobalTidy.m_TidyJs = g_GlobalTidy.m_TidyNames[SYN_JAVASCRIPT].tidyName;
				g_GlobalTidy.m_TidyCss = g_GlobalTidy.m_TidyNames[SYN_CSS].tidyName;
				g_GlobalTidy.m_TidyJson = g_GlobalTidy.m_TidyNames[SYN_JSON].tidyName;
				g_GlobalTidy.m_TidySql = g_GlobalTidy.m_TidyNames[SYN_SQL].tidyName;
				g_GlobalTidy.m_TidyHtml_at.Empty();
				g_GlobalTidy.m_TidyHtml_cp.Empty();
				g_GlobalTidy.m_TidyHtml_nbt.Empty();
				g_GlobalTidy.m_TidyHtml_net.Empty();
				g_GlobalTidy.m_TidyHtml_nit.Empty();
				g_GlobalTidy.m_TidyHtml_npt.Empty();
				EndDialog(IDOK);
			}
			return TRUE;
		}
	}
	return CBCGPPropertySheet::PreTranslateMessage(pMsg);
}

INT_PTR CSetSheet::DoModalAllPage()
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
	SetLook(CBCGPPropertySheet::PropSheetLook_List, 124);

	CSetPageBase pageCpp(_T("C/C++"), _T("CPP"), g_GlobalTidy.m_TidyCpp);
	CSetPageCpp pageJava(_T("Java"), g_GlobalTidy.m_TidyJava);
	CSetPageCpp pageCs(_T("C#"), g_GlobalTidy.m_TidyCSharp);
	CSetPageBase pageJS(_T("JavaScript"), _T("JavaScript"), g_GlobalTidy.m_TidyJs);
	CSetPageHtml pageHtml(SYN_HTML, IDS_STRING_SET_HTML);
	CSetPageHtml pageXml(SYN_XML, IDS_STRING_SET_XML);
	CSetPageBase pagePHP(_T("PHP"), _T("PHP"), g_GlobalTidy.m_TidyPhp);
	CSetPageCSS pageCSS;
	CSetPageBase pageJson(_T("JSON"), _T("JSON"), g_GlobalTidy.m_TidyJson);
	CSetPageBase pageSql(_T("SQL"), _T("SQL"), g_GlobalTidy.m_TidySql);
	AddPage(&pageCpp);
	AddPage(&pageCs);
	AddPage(&pageCSS);
	AddPage(&pageHtml);
	AddPage(&pageJava);
	AddPage(&pageJS);
	AddPage(&pageJson);
	AddPage(&pagePHP);
	AddPage(&pageSql);
	AddPage(&pageXml);

	EnableVisualManagerStyle(TRUE, TRUE);

	INT_PTR nResult = DoModal();
	if (nResult == IDOK)
	{
		SaveTidyToReg();
	}
	return nResult;
}

void CSetSheet::SaveTidyToReg()
{
	BOOL bRegVaild = TRUE;
	CString strTidy;
	LPCTSTR lpszSubSection = _T("SynTidy");
	CString strSection = theApp.GetRegSectionPath(lpszSubSection);

	CBCGPRegistrySP regSP;
	CBCGPRegistry& reg = regSP.Create (FALSE, FALSE);

	if (reg.CreateKey(strSection))
	{
		if (!reg.Write(g_GlobalTidy.m_TidyNames[SYN_CPP].langName, g_GlobalTidy.m_TidyCpp))
		{
			bRegVaild = FALSE;
		}
		if (!reg.Write(g_GlobalTidy.m_TidyNames[SYN_JAVA].langName, g_GlobalTidy.m_TidyJava))
		{
			bRegVaild = FALSE;
		}
		if (!reg.Write(g_GlobalTidy.m_TidyNames[SYN_CS].langName, g_GlobalTidy.m_TidyCSharp))
		{
			bRegVaild = FALSE;
		}
		if (!reg.Write(g_GlobalTidy.m_TidyNames[SYN_HTML].langName, g_GlobalTidy.m_TidyHtml))
		{
			bRegVaild = FALSE;
		}
		if (!reg.Write(g_GlobalTidy.m_TidyNames[SYN_XML].langName, g_GlobalTidy.m_TidyXml))
		{
			bRegVaild = FALSE;
		}
		if (!reg.Write(g_GlobalTidy.m_TidyNames[SYN_PHP].langName, g_GlobalTidy.m_TidyPhp))
		{
			bRegVaild = FALSE;
		}
		if (!reg.Write(g_GlobalTidy.m_TidyNames[SYN_JAVASCRIPT].langName, g_GlobalTidy.m_TidyJs))
		{
			bRegVaild = FALSE;
		}
		if (!reg.Write(g_GlobalTidy.m_TidyNames[SYN_CSS].langName, g_GlobalTidy.m_TidyCss))
		{
			bRegVaild = FALSE;
		}
		if (!reg.Write(g_GlobalTidy.m_TidyNames[SYN_JSON].langName, g_GlobalTidy.m_TidyJson))
		{
			bRegVaild = FALSE;
		}
		if (!reg.Write(g_GlobalTidy.m_TidyNames[SYN_SQL].langName, g_GlobalTidy.m_TidySql))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HTMLat"), g_GlobalTidy.m_TidyHtml_at))
		{
			bRegVaild = FALSE;
		}
		if (!reg.Write(_T("HTMLcp"), g_GlobalTidy.m_TidyHtml_cp))
		{
			bRegVaild = FALSE;
		}
		if (!reg.Write(_T("HTMLnbt"), g_GlobalTidy.m_TidyHtml_nbt))
		{
			bRegVaild = FALSE;
		}
		if (!reg.Write(_T("HTMLnet"), g_GlobalTidy.m_TidyHtml_net))
		{
			bRegVaild = FALSE;
		}
		if (!reg.Write(_T("HTMLnit"), g_GlobalTidy.m_TidyHtml_nit))
		{
			bRegVaild = FALSE;
		}
		if (!reg.Write(_T("HTMLnpt"), g_GlobalTidy.m_TidyHtml_npt))
		{
			bRegVaild = FALSE;
		}
	}
	else
	{
		bRegVaild = FALSE;
	}

	if (!bRegVaild)
	{
		bRegVaild = strTidy.LoadString(IDS_REG_ERROR);
		ASSERT(bRegVaild);
		CFMessageBox(strTidy, MB_ICONSTOP);
	}
}