// SetPageHtml.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageHtml.h"


// CSetPageHtml 对话框

IMPLEMENT_DYNCREATE(CSetPageHtml, CBCGPPropertyPage)

CSetPageHtml::CSetPageHtml()
	: CBCGPPropertyPage(CSetPageHtml::IDD)
{

}

CSetPageHtml::CSetPageHtml( UINT nLangID, UINT nIDCaption )
	: CBCGPPropertyPage(CSetPageHtml::IDD, nIDCaption)
	, m_onlyHtmlXml(nLangID)
{

}
CSetPageHtml::~CSetPageHtml()
{
}

void CSetPageHtml::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_HTMLRECT, m_wndTabsArea);
}

BEGIN_MESSAGE_MAP(CSetPageHtml, CBCGPPropertyPage)
END_MESSAGE_MAP()

BOOL CSetPageHtml::OnInitDialog()
{
	CBCGPPropertyPage::OnInitDialog();
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STRING_VIEWDESC);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_VIEWFORMATTER, strTemp);

	GetDlgItem(IDC_EDIT_VIEWFORMATTER)->SetFont(&globalData.fontRegular);

	CRect rectTabs;
	m_wndTabsArea.GetWindowRect(&rectTabs);
	ScreenToClient(&rectTabs);
	m_wndHtmlTabs.Create(CBCGPTabWnd::STYLE_3D, rectTabs, this, 1, CBCGPTabWnd::LOCATION_TOP);

	m_wndOne.Create(IDD_SET_HTML_ONE, &m_wndHtmlTabs);
	m_wndOne.SetViewEditWnd(GetDlgItem(IDC_EDIT_VIEWFORMATTER));

	m_wndTwo.Create(IDD_SET_HTML_TWO, &m_wndHtmlTabs);
	m_wndTwo.SetViewEditWnd(GetDlgItem(IDC_EDIT_VIEWFORMATTER));

	switch (m_onlyHtmlXml)
	{
	case SYN_HTML:
		{
			m_wndOne.SetTidyConfig(g_GlobalTidy.m_TidyHtml);
			m_wndTwo.SetTidyConfig(g_GlobalTidy.m_TidyHtml, SYN_HTML);
		}
		break;
	case SYN_XML:
		{
			m_wndOne.SetTidyConfig(g_GlobalTidy.m_TidyXml);
			m_wndTwo.SetTidyConfig(g_GlobalTidy.m_TidyXml, SYN_XML);
			m_wndTwo.GetDlgItem(IDC_EDIT_HTML_ALT_TEXT)->EnableWindow(FALSE);
			m_wndTwo.GetDlgItem(IDC_EDIT_HTML_CSS_PREFIX)->EnableWindow(FALSE);
			m_wndTwo.GetDlgItem(IDC_EDIT_HTML_NEW_BLOCKLEVEL_TAGS)->EnableWindow(FALSE);
			m_wndTwo.GetDlgItem(IDC_EDIT_HTML_NEW_EMPTY_TAGS)->EnableWindow(FALSE);
			m_wndTwo.GetDlgItem(IDC_EDIT_HTML_NEW_INLINE_TAGS)->EnableWindow(FALSE);
			m_wndTwo.GetDlgItem(IDC_EDIT_HTML_NEW_PRE_TAGS)->EnableWindow(FALSE);
		}
		break;
	}

	m_wndHtmlTabs.AddTab(&m_wndOne, _T("HTML, XHTML, XML  "));
	m_wndHtmlTabs.AddTab(&m_wndTwo, _T("Pretty Print, Character Encoding  "));
	m_wndHtmlTabs.EnableTabSwap(FALSE);

	m_wndHtmlTabs.ModifyTabStyle(CBCGPTabWnd::STYLE_3D_VS2005);
	m_wndHtmlTabs.RecalcLayout ();
	m_wndHtmlTabs.RedrawWindow ();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSetPageHtml::OnOK()
{
	CString strTidy;

	m_wndOne.GetTidyConfig(strTidy);
	m_wndTwo.GetTidyConfig(strTidy);
	
	switch (m_onlyHtmlXml)
	{
	case SYN_HTML:g_GlobalTidy.m_TidyHtml = strTidy;
		break;
	case SYN_XML:g_GlobalTidy.m_TidyXml = strTidy;
		break;
	}
	CBCGPPropertyPage::OnOK();
}
