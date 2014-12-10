// SetPageBase.cpp : 实现文件

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageBase.h"

//////////////////////////////////////////////////////////////////////////
// CSetPageBase 对话框

IMPLEMENT_DYNAMIC(CSetPageBase, CBCGPPropertyPage)

CSetPageBase::CSetPageBase()
	: CBCGPPropertyPage(CSetPageBase::IDD)
{

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
	GetDlgItem(IDC_EDIT_VIEWFORMATTER)->SetFont(&g_GlobalUtils.m_fontWidth);

	CRect rectPropList;
	GetDlgItem(IDC_PROPLIST_LOCATION)->GetClientRect(&rectPropList);
	GetDlgItem(IDC_PROPLIST_LOCATION)->MapWindowPoints(this, &rectPropList);
	GetDlgItem(IDC_PROPLIST_LOCATION)->ShowWindow(SW_HIDE);

	m_wndPropList.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectPropList, this, (UINT)-1);

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDesciptionArea();
	m_wndPropList.SetVSDotNetLook(TRUE);
	m_wndPropList.MarkModifiedProperties(TRUE);
	m_wndPropList.SetNameAlign(DT_LEFT);
	m_wndPropList.SetAlphabeticMode(FALSE);
	m_wndPropList.SetShowDragContext(FALSE);
	m_wndPropList.EnableToolBar(TRUE);
	m_wndPropList.EnableSearchBox(TRUE);

	CBCGPProp*			m_pGroupGeneral;
	// Add general properties:
	m_pGroupGeneral = new CBCGPProp(_T("General"));

	m_pGroupGeneral->AddSubItem(new CBCGPProp(_T("Boolean"), (_variant_t)false, _T("Property with TRUE or FALSE values")));

	CBCGPProp* pProp = new CBCGPProp(_T("Options"), _T("Option 1"), _T("Property with list of choises"));
	pProp->AddOption(_T("Option 1"));
	pProp->AddOption(_T("Option 2"));
	pProp->AddOption(_T("Option 3"));
	pProp->AddOption(_T("Option 4"));
	pProp->AllowEdit(FALSE);

	m_pGroupGeneral->AddSubItem(pProp);

	m_pGroupGeneral->AddSubItem(new CBCGPProp(_T("Text"), (_variant_t)_T("My text"), _T("Text Property")));
	m_pGroupGeneral->AddSubItem(new CBCGPProp(_T("Numeric"), (_variant_t)150l, _T("Numeric Property")));
	m_wndPropList.AddProperty(m_pGroupGeneral);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CSetPageBase::SetViewEdit(LPCTSTR lpszText)
{
	SetDlgItemText(IDC_EDIT_VIEWFORMATTER, lpszText);
}
