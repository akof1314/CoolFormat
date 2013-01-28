// SetPageCpp.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageCpp.h"

//////////////////////////////////////////////////////////////////////////
// CSetPageCpp 对话框

IMPLEMENT_DYNCREATE(CSetPageCpp, CBCGPPropertyPage)

CSetPageCpp::CSetPageCpp(UINT nLangID, UINT nIDCaption)
	: CBCGPPropertyPage(CSetPageCpp::IDD, nIDCaption)
	, m_onlyCppJavaCS(nLangID)
{
}

CSetPageCpp::CSetPageCpp()
	: CBCGPPropertyPage(CSetPageCpp::IDD)
{
	m_onlyCppJavaCS = SYN_CPP;
}

CSetPageCpp::~CSetPageCpp()
{
}

void CSetPageCpp::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_CPPRECT, m_wndTabsArea);
}


BEGIN_MESSAGE_MAP(CSetPageCpp, CBCGPPropertyPage)
END_MESSAGE_MAP()

BOOL CSetPageCpp::OnInitDialog()
{
	CBCGPPropertyPage::OnInitDialog();

	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STR_VIEWFORMATTER);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_VIEWFORMATTER, strTemp);
	GetDlgItem(IDC_EDIT_VIEWFORMATTER)->SetFont(&g_GlobalUtils.m_fontWidth);

	CRect rectTabs;
	m_wndTabsArea.GetWindowRect(&rectTabs);
	ScreenToClient(&rectTabs);
	m_wndCppTabs.Create(CBCGPTabWnd::STYLE_3D, rectTabs, this, 1, CBCGPTabWnd::LOCATION_TOP);

	m_wndFast.Create(IDD_SET_CPP_FAST, &m_wndCppTabs);
	m_wndFast.SetViewEditWnd(GetDlgItem(IDC_EDIT_VIEWFORMATTER));

	m_wndHigh.Create(IDD_SET_CPP_HIGH, &m_wndCppTabs);
	m_wndHigh.SetViewEditWnd(GetDlgItem(IDC_EDIT_VIEWFORMATTER));
	
	switch (m_onlyCppJavaCS)
	{
	case SYN_CPP:
		{
			m_wndFast.SetTidyConfig(g_GlobalTidy.m_TidyCpp);
			m_wndHigh.SetTidyConfig(g_GlobalTidy.m_TidyCpp);
		}
		break;
	case SYN_JAVA:
		{
			m_wndFast.SetTidyConfig(g_GlobalTidy.m_TidyJava);
			m_wndHigh.SetTidyConfig(g_GlobalTidy.m_TidyJava);
		}
		break;
	case SYN_CS:
		{
			m_wndFast.SetTidyConfig(g_GlobalTidy.m_TidyCSharp);
			m_wndHigh.SetTidyConfig(g_GlobalTidy.m_TidyCSharp);
		}
		break;
	}

	m_wndCppTabs.AddTab(&m_wndFast, _T("Bracket Style "));
	m_wndCppTabs.AddTab(&m_wndHigh, _T("Tab, Indentation, Padding, Formatting "));
	m_wndCppTabs.EnableTabSwap(FALSE);

	m_wndCppTabs.ModifyTabStyle(CBCGPTabWnd::STYLE_3D_VS2005);
	m_wndCppTabs.RecalcLayout ();
	m_wndCppTabs.RedrawWindow ();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

CBCGPDlgTabWnd::CBCGPDlgTabWnd()
{
	m_bIsDlgControl = TRUE;
	m_bVisualManagerStyle = TRUE;
}

void CSetPageCpp::OnOK()
{
	CString strTidy = _T("-");

	m_wndFast.GetTidyConfig(strTidy);
	m_wndHigh.GetTidyConfig(strTidy);

	switch (m_onlyCppJavaCS)
	{
	case SYN_CPP:g_GlobalTidy.m_TidyCpp = strTidy;break;
	case SYN_JAVA:g_GlobalTidy.m_TidyJava = strTidy;break;
	case SYN_CS:g_GlobalTidy.m_TidyCSharp = strTidy;break;
	}

	CBCGPPropertyPage::OnOK();
}
