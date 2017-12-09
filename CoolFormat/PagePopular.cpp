// PagePopular.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "PagePopular.h"


// CPagePopular 对话框

IMPLEMENT_DYNCREATE(CPagePopular, CBCGPPropertyPage)

CPagePopular::CPagePopular()
	: CBCGPPropertyPage(CPagePopular::IDD, IDS_STRING_POPULARTITLE)
	, m_nColorStyle(theApp.m_nAppLook - ID_VIEW_APPLOOK_2010_1)
	, m_nTooltipStyle(-1)
	, m_nLanguageStyle(theApp.m_nAppLanguageID - 1)
{
	if (!theApp.m_bShowToolTips)
	{
		m_nTooltipStyle = 2;
	}
	else
	{
		m_nTooltipStyle = theApp.m_bShowToolTipDescr ? 0 : 1;
	}
}

CPagePopular::~CPagePopular()
{
}

void CPagePopular::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_COLORSTYLE, m_nColorStyle);
	DDX_CBIndex(pDX, IDC_COMBO_TIPSTYLE, m_nTooltipStyle);
	DDX_CBIndex(pDX, IDC_COMBO_LANG, m_nLanguageStyle);
}


BEGIN_MESSAGE_MAP(CPagePopular, CBCGPPropertyPage)
END_MESSAGE_MAP()


// CPagePopular 消息处理程序

BOOL CPagePopular::OnInitDialog()
{
	CBCGPPropertyPage::OnInitDialog();

    SendMessageToDescendants(WM_SETFONT, (WPARAM)globalData.fontRegular.m_hObject, MAKELPARAM(FALSE, 0), FALSE);
    InitLang();

	m_nColorStyle = theApp.m_nAppLook - ID_VIEW_APPLOOK_2010_1;

	if (!theApp.m_bShowToolTips)
	{
		m_nTooltipStyle = 2;
	}
	else
	{
		m_nTooltipStyle = theApp.m_bShowToolTipDescr ? 0 : 1;
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPagePopular::OnOK()
{
	UpdateData();

	theApp.m_nAppLook = m_nColorStyle + ID_VIEW_APPLOOK_2010_1;

	switch (m_nTooltipStyle)
	{
	case 0:
		theApp.m_bShowToolTips = TRUE;
		theApp.m_bShowToolTipDescr = TRUE;
		break;

	case 1:
		theApp.m_bShowToolTips = TRUE;
		theApp.m_bShowToolTipDescr = FALSE;
		break;

	case 2:
		theApp.m_bShowToolTips = FALSE;
		theApp.m_bShowToolTipDescr = FALSE;
		break;
	}
	++m_nLanguageStyle;

	if (theApp.m_nAppLanguageID != (UINT)m_nLanguageStyle)
	{
		theApp.m_nAppLanguageID = m_nLanguageStyle;
		CString strTemp;
		BOOL bNameVaild = strTemp.LoadString(IDS_STRING_CHANGELANG);
		ASSERT(bNameVaild);
		CFMessageBox(strTemp, MB_OK | MB_ICONINFORMATION);
	}
	CBCGPPropertyPage::OnOK();
}

void CPagePopular::InitLang()
{
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STRING_POPULARCOLOR);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_STYLECOLOR, strTemp);
	SetDlgItemSizeToContent(GetDlgItem(IDC_STATIC_STYLECOLOR));

	bNameVaild = strTemp.LoadString(IDS_STRING_POPULARSCREEN);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_STYLESCREEN, strTemp);
	SetDlgItemSizeToContent(GetDlgItem(IDC_STATIC_STYLESCREEN));

	bNameVaild = strTemp.LoadString(IDS_STRING_POPULARTITLE);
	ASSERT(bNameVaild);
	SetWindowText(strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_POPULARLANG);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_STYLELANG, strTemp);
	SetDlgItemSizeToContent(GetDlgItem(IDC_STATIC_STYLELANG));

	bNameVaild = strTemp.LoadString(IDS_STRING_POPULARCOLORSTR);
	ASSERT(bNameVaild);
	CComboBox *pStyleColor = ((CComboBox *)GetDlgItem(IDC_COMBO_COLORSTYLE));
	pStyleColor->ResetContent();
	int nStart = 0;
	int nEnd = strTemp.Find(_T(";"), nStart);
	while (nEnd != -1)
	{
		pStyleColor->AddString(strTemp.Mid(nStart, nEnd - nStart));
		nStart = nEnd + 1;
		nEnd = strTemp.Find(_T(";"), nStart);
	}

	bNameVaild = strTemp.LoadString(IDS_STRING_POPULARSCRSTR);
	ASSERT(bNameVaild);
	pStyleColor = ((CComboBox *)GetDlgItem(IDC_COMBO_TIPSTYLE));
	pStyleColor->ResetContent();
	nStart = 0;
	nEnd = strTemp.Find(_T(";"), nStart);
	while (nEnd != -1)
	{
		pStyleColor->AddString(strTemp.Mid(nStart, nEnd - nStart));
		nStart = nEnd + 1;
		nEnd = strTemp.Find(_T(";"), nStart);
	}

	bNameVaild = strTemp.LoadString(IDS_STRING_POPULARCOMLANG);
	ASSERT(bNameVaild);
	pStyleColor = ((CComboBox *)GetDlgItem(IDC_COMBO_LANG));
	pStyleColor->ResetContent();
	nStart = 0;
	nEnd = strTemp.Find(_T(";"), nStart);
	while (nEnd != -1)
	{
		pStyleColor->AddString(strTemp.Mid(nStart, nEnd - nStart));
		nStart = nEnd + 1;
		nEnd = strTemp.Find(_T(";"), nStart);
	}
}