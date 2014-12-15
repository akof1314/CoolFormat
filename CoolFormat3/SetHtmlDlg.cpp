// SetHtmlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetHtmlDlg.h"


// CSetHtmlDlg 对话框

IMPLEMENT_DYNAMIC(CSetHtmlDlg, CBCGPDialog)

CSetHtmlDlg::CSetHtmlDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetHtmlDlg::IDD, pParent)
{

}

CSetHtmlDlg::~CSetHtmlDlg()
{
}

void CSetHtmlDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_HTMLFONT, m_htmlFont);
	DDX_Control(pDX, IDC_COMBO_HTMLSTYLE, m_htmlStyle);
	DDX_Control(pDX, IDC_COMBO_BORDER_STYLE, m_borderStyle);
	DDX_Control(pDX, IDC_COMBO_HTMLSIZE, m_htmlSize);
	DDX_Control(pDX, IDC_BUTTON_BORDER_COLOR, m_borderColor);
	DDX_Control(pDX, IDC_BUTTON_DEFAULTEXT, m_btnDefaultLink);
	DDX_Control(pDX, IDC_BUTTON_BACKGROUND_COLOR, m_backgroundColor);
}


BEGIN_MESSAGE_MAP(CSetHtmlDlg, CBCGPDialog)
	ON_BN_CLICKED(IDC_CHECK_SHOW_BORDER, &CSetHtmlDlg::OnBnClickedCheckShowBorder)
	ON_BN_CLICKED(IDC_CHECK_SHOW_LINENUMBER, &CSetHtmlDlg::OnBnClickedCheckShowLinenumber)
	ON_BN_CLICKED(IDC_CHECK_SHOW_SIDEBAR, &CSetHtmlDlg::OnBnClickedCheckShowSidebar)
	ON_BN_CLICKED(IDC_CHECK_SHOW_LANGTITLE, &CSetHtmlDlg::OnBnClickedCheckShowLangtitle)
	ON_BN_CLICKED(IDC_CHECK_SHOW_ADDTITLE, &CSetHtmlDlg::OnBnClickedCheckShowAddtitle)
	ON_BN_CLICKED(IDC_CHECK_AUTO_COPY, &CSetHtmlDlg::OnBnClickedCheckAutoCopy)
END_MESSAGE_MAP()

// CSetHtmlDlg 消息处理程序

BOOL CSetHtmlDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	InitLang();

	CBCGPFontComboBox::m_bDrawUsingFont = TRUE;
	m_htmlFont.Setup();
	m_htmlSize.SetItemHeight(-1, m_htmlSize.GetItemHeight(-1) + 3);
	m_htmlStyle.SetItemHeight(-1, m_htmlStyle.GetItemHeight(-1) + 3);	
	m_btnDefaultLink.SizeToContent();

	InitFont();
	InitStyle();

	GetDlgItem(IDCANCEL)->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSetHtmlDlg::InitLang()
{
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDOK);
	ASSERT(bNameVaild);
	SetDlgItemText(IDOK, strTemp);

	bNameVaild = strTemp.LoadString(IDCANCEL);
	ASSERT(bNameVaild);
	SetDlgItemText(IDCANCEL, strTemp);

	bNameVaild = strTemp.LoadString(IDD_SYNHTML_SET);
	ASSERT(bNameVaild);
	SetWindowText(strTemp);

	bNameVaild = strTemp.LoadString(IDC_BUTTON_DEFAULTEXT);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_BUTTON_DEFAULTEXT, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_EDITFONT);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_EDITFONT, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_EDITSTYLE);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_EDITSTYLE, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_EDITSIZE);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_EDITSIZE, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_FONT);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_FONT, strTemp);

	//////////////////////////////////////////////////////////////////////////
	bNameVaild = strTemp.LoadString(IDC_CHECK_SHOW_BORDER);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_CHECK_SHOW_BORDER, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_BORDER_WIDTH);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_BORDER_WIDTH, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_BORDER_STYLE);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_BORDER_STYLE, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_BORDER_COLOR);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_BORDER_COLOR, strTemp);

	bNameVaild = strTemp.LoadString(IDC_CHECK_SHOW_LINENUMBER);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_CHECK_SHOW_LINENUMBER, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_BACKGROUND_COLOR);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_BACKGROUND_COLOR, strTemp);	

	bNameVaild = strTemp.LoadString(IDC_CHECK_SHOW_SIDEBAR);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_CHECK_SHOW_SIDEBAR, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_BASIC_SET);
		ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_BASIC_SET, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_OTHER_SET);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_OTHER_SET, strTemp);

	bNameVaild = strTemp.LoadString(IDC_CHECK_SHOW_LANGTITLE);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_CHECK_SHOW_LANGTITLE, strTemp);

	bNameVaild = strTemp.LoadString(IDC_CHECK_SHOW_ADDTITLE);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_CHECK_SHOW_ADDTITLE, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_LINEHEIGHT);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_LINEHEIGHT, strTemp);

	bNameVaild = strTemp.LoadString(IDS_EDITSTYLE_DATA);
	ASSERT(bNameVaild);
	m_htmlStyle.ResetContent();
	int nStart = 0;
	int nEnd = strTemp.Find(_T(";"), nStart);
	while (nEnd != -1)
	{
		m_htmlStyle.AddString(strTemp.Mid(nStart, nEnd - nStart));
		nStart = nEnd + 1;
		nEnd = strTemp.Find(_T(";"), nStart);
	}

	bNameVaild = strTemp.LoadString(IDS_BORDERSTYLE_DATA);
	ASSERT(bNameVaild);
	m_borderStyle.ResetContent();
	nStart = 0;
	nEnd = strTemp.Find(_T(";"), nStart);
	while (nEnd != -1)
	{
		m_borderStyle.AddString(strTemp.Mid(nStart, nEnd - nStart));
		nStart = nEnd + 1;
		nEnd = strTemp.Find(_T(";"), nStart);
	}

	bNameVaild = strTemp.LoadString(IDS_STRING_HTML_AUTOCOPY);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_CHECK_AUTO_COPY, strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_COPYCODE);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_CHECK_COPY_CODE, strTemp);
}

void CSetHtmlDlg::InitFont()
{
	m_htmlFont.SelectFont(g_GlobalUtils.m_sStyleScheme.m_strHtmlFontName);	
	m_htmlStyle.SetCurSel(g_GlobalUtils.m_sStyleScheme.m_bHtmlFontBold + g_GlobalUtils.m_sStyleScheme.m_bHtmlFontItalic);
	CString strSize;
	strSize.Format(_T("%d"), g_GlobalUtils.m_sStyleScheme.m_uHtmlFontSize);
	if (CB_ERR == m_htmlSize.SelectString(-1, strSize))
	{
		m_htmlSize.SetCurSel(3);
	}
}

void CSetHtmlDlg::InitStyle()
{
	((CButton *)GetDlgItem(IDC_CHECK_SHOW_BORDER))->SetCheck(g_GlobalUtils.m_sStyleScheme.m_bHtmlShowBorder);
	((CButton *)GetDlgItem(IDC_CHECK_SHOW_LINENUMBER))->SetCheck(g_GlobalUtils.m_sStyleScheme.m_bHtmlShowLineNumber);
	((CButton *)GetDlgItem(IDC_CHECK_SHOW_SIDEBAR))->SetCheck(g_GlobalUtils.m_sStyleScheme.m_bHtmlShowSidebar);
	((CButton *)GetDlgItem(IDC_CHECK_SHOW_LANGTITLE))->SetCheck(g_GlobalUtils.m_sStyleScheme.m_bHtmlShowLangTitle);
	((CButton *)GetDlgItem(IDC_CHECK_SHOW_ADDTITLE))->SetCheck(g_GlobalUtils.m_sStyleScheme.m_bHtmlShowAddTitle);
	((CButton *)GetDlgItem(IDC_CHECK_AUTO_COPY))->SetCheck(g_GlobalUtils.m_sStyleScheme.m_bHtmlAutoCopy);
	((CButton *)GetDlgItem(IDC_CHECK_COPY_CODE))->SetCheck(g_GlobalUtils.m_sStyleScheme.m_bHtmlCopyCode);

	CString strWidth;
	strWidth.Format(_T("%d"), g_GlobalUtils.m_sStyleScheme.m_iHtmlBorderWidth);
	SetDlgItemText(IDC_EDIT_BORDER_WIDTH, strWidth);
	m_borderStyle.SetCurSel(g_GlobalUtils.m_sStyleScheme.m_iHtmlBorderStyle);
	m_borderColor.SetColor(g_GlobalUtils.m_sStyleScheme.m_clrHtmlBorderColor);

	m_backgroundColor.SetColor(g_GlobalUtils.m_sStyleScheme.m_clrHtmlBackgroundColor);

	SetDlgItemText(IDC_EDIT_ADDTITLE, g_GlobalUtils.m_sStyleScheme.m_strHtmlAddTitle);

	strWidth.Format(_T("%d"), g_GlobalUtils.m_sStyleScheme.m_iHtmlLineHeight);
	SetDlgItemText(IDC_EDIT_LINEHEIGHT, strWidth);

	OnBnClickedCheckShowBorder();
	OnBnClickedCheckShowAddtitle();
	OnBnClickedCheckAutoCopy();
}
void CSetHtmlDlg::OnBnClickedCheckShowBorder()
{
	BOOL bShow = ((CButton *)GetDlgItem(IDC_CHECK_SHOW_BORDER))->GetCheck();
	GetDlgItem(IDC_STATIC_BORDER_WIDTH)->EnableWindow(bShow);
	GetDlgItem(IDC_STATIC_BORDER_STYLE)->EnableWindow(bShow);
	GetDlgItem(IDC_STATIC_BORDER_COLOR)->EnableWindow(bShow);
	GetDlgItem(IDC_EDIT_BORDER_WIDTH)->EnableWindow(bShow);
	GetDlgItem(IDC_SPIN_BORDER_WIDTH)->EnableWindow(bShow);
	GetDlgItem(IDC_COMBO_BORDER_STYLE)->EnableWindow(bShow);
	GetDlgItem(IDC_BUTTON_BORDER_COLOR)->EnableWindow(bShow);
}

void CSetHtmlDlg::OnBnClickedCheckShowLinenumber()
{

}

void CSetHtmlDlg::OnBnClickedCheckShowSidebar()
{

}

void CSetHtmlDlg::OnBnClickedCheckShowLangtitle()
{
}

void CSetHtmlDlg::OnBnClickedCheckShowAddtitle()
{
	BOOL bShow = ((CButton *)GetDlgItem(IDC_CHECK_SHOW_ADDTITLE))->GetCheck();
	GetDlgItem(IDC_EDIT_ADDTITLE)->EnableWindow(bShow);
}

BOOL CSetHtmlDlg::PreTranslateMessage(MSG* pMsg)
{
	if (WM_LBUTTONDOWN == pMsg->message)
	{
		if (pMsg->hwnd == GetDlgItem(IDC_BUTTON_DEFAULTEXT)->GetSafeHwnd())
		{
			CString strTemp;
			BOOL bNameVaild = strTemp.LoadString(IDS_MSG_GODEFAULT);
			ASSERT(bNameVaild);
			if (CFMessageBox(strTemp, MB_YESNO | MB_ICONINFORMATION) == IDYES)
			{
				m_htmlFont.SelectFont(_T("Consolas"));
				m_htmlStyle.SetCurSel(0);
				CString strSize = _T("12");
				m_htmlSize.SelectString(-1, strSize);

				((CButton *)GetDlgItem(IDC_CHECK_SHOW_BORDER))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_CHECK_SHOW_LINENUMBER))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_CHECK_SHOW_SIDEBAR))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_CHECK_SHOW_LANGTITLE))->SetCheck(TRUE);
				((CButton *)GetDlgItem(IDC_CHECK_SHOW_ADDTITLE))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_CHECK_AUTO_COPY))->SetCheck(FALSE);
				((CButton *)GetDlgItem(IDC_CHECK_COPY_CODE))->SetCheck(FALSE);

				CString strWidth;
				strWidth.Format(_T("%d"), 1);
				SetDlgItemText(IDC_EDIT_BORDER_WIDTH, strWidth);
				m_borderStyle.SetCurSel(1);
				m_borderColor.SetColor(RGB(227, 227, 227));

				m_backgroundColor.SetColor(RGB(239, 239, 239));

				SetDlgItemText(IDC_EDIT_LINEHEIGHT, _T("15"));
				SetDlgItemText(IDC_EDIT_ADDTITLE, _T("By CoolFormat"));

				OnBnClickedCheckShowBorder();			
				OnBnClickedCheckShowAddtitle();
				OnBnClickedCheckAutoCopy();
			}
			return TRUE;
		}
	}
	return CBCGPDialog::PreTranslateMessage(pMsg);
}

void CSetHtmlDlg::OnOK()
{
	GetFont();
	GetStyle();

	BOOL bRegVaild = TRUE;
	LPCTSTR lpszSubSection = _T("SynStyle");
	CString strSection = theApp.GetRegSectionPath(lpszSubSection);

	CBCGPRegistrySP regSP;
	CBCGPRegistry& reg = regSP.Create (FALSE, FALSE);

	if (reg.CreateKey(strSection))
	{
		if (!reg.Write(_T("HtmlFontName"), g_GlobalUtils.m_sStyleScheme.m_strHtmlFontName))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlFontBold"), g_GlobalUtils.m_sStyleScheme.m_bHtmlFontBold))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlFontItalic"), g_GlobalUtils.m_sStyleScheme.m_bHtmlFontItalic))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlFontSize"), (int)g_GlobalUtils.m_sStyleScheme.m_uHtmlFontSize))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlShowBorder"), g_GlobalUtils.m_sStyleScheme.m_bHtmlShowBorder))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlBorderWidth"), g_GlobalUtils.m_sStyleScheme.m_iHtmlBorderWidth))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlBorderStyle"), g_GlobalUtils.m_sStyleScheme.m_iHtmlBorderStyle))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlBorderColor"), g_GlobalUtils.m_sStyleScheme.m_clrHtmlBorderColor))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlShowLineNumber"), g_GlobalUtils.m_sStyleScheme.m_bHtmlShowLineNumber))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlBackgroundColor"), g_GlobalUtils.m_sStyleScheme.m_clrHtmlBackgroundColor))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlShowSidebar"), g_GlobalUtils.m_sStyleScheme.m_bHtmlShowSidebar))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlShowLangTitle"), g_GlobalUtils.m_sStyleScheme.m_bHtmlShowLangTitle))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlShowAddTitle"), g_GlobalUtils.m_sStyleScheme.m_bHtmlShowAddTitle))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlAddTitle"), g_GlobalUtils.m_sStyleScheme.m_strHtmlAddTitle))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlLineHeight"), g_GlobalUtils.m_sStyleScheme.m_iHtmlLineHeight))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlAutoCopy"), g_GlobalUtils.m_sStyleScheme.m_bHtmlAutoCopy))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("HtmlCopyCode"), g_GlobalUtils.m_sStyleScheme.m_bHtmlCopyCode))
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
		CString strTemp;
		bRegVaild = strTemp.LoadString(IDS_REG_ERROR);
		ASSERT(bRegVaild);
		CFMessageBox(strTemp, MB_ICONSTOP);
	}

	CBCGPDialog::OnOK();
}

void CSetHtmlDlg::GetFont( void )
{
	CBCGPFontDesc *pFontDesc = m_htmlFont.GetSelFont();
	if (pFontDesc)
	{
		g_GlobalUtils.m_sStyleScheme.m_strHtmlFontName = pFontDesc->m_strName;
	}
	g_GlobalUtils.m_sStyleScheme.m_bHtmlFontBold = m_htmlStyle.GetCurSel() == 1 || m_htmlStyle.GetCurSel() == 3 ? TRUE : FALSE;
	g_GlobalUtils.m_sStyleScheme.m_bHtmlFontItalic = m_htmlStyle.GetCurSel() == 2 || m_htmlStyle.GetCurSel() == 3 ? TRUE : FALSE;
	CString strSize;
	m_htmlSize.GetLBText(m_htmlSize.GetCurSel(), strSize);
	g_GlobalUtils.m_sStyleScheme.m_uHtmlFontSize = _ttoi(strSize);
}

void CSetHtmlDlg::GetStyle( void )
{
	CString strValue;
	g_GlobalUtils.m_sStyleScheme.m_bHtmlShowBorder = ((CButton *)GetDlgItem(IDC_CHECK_SHOW_BORDER))->GetCheck();
	if (g_GlobalUtils.m_sStyleScheme.m_bHtmlShowBorder)
	{
		GetDlgItemText(IDC_EDIT_BORDER_WIDTH, strValue);
		g_GlobalUtils.m_sStyleScheme.m_iHtmlBorderWidth = _ttoi(strValue);
		g_GlobalUtils.m_sStyleScheme.m_iHtmlBorderStyle = m_borderStyle.GetCurSel();
		g_GlobalUtils.m_sStyleScheme.m_clrHtmlBorderColor = m_borderColor.GetColor();
	}

	g_GlobalUtils.m_sStyleScheme.m_clrHtmlBackgroundColor = m_backgroundColor.GetColor();
	g_GlobalUtils.m_sStyleScheme.m_bHtmlShowLineNumber = ((CButton *)GetDlgItem(IDC_CHECK_SHOW_LINENUMBER))->GetCheck();
	g_GlobalUtils.m_sStyleScheme.m_bHtmlShowSidebar = ((CButton *)GetDlgItem(IDC_CHECK_SHOW_SIDEBAR))->GetCheck();
	GetDlgItemText(IDC_EDIT_LINEHEIGHT, strValue);
	g_GlobalUtils.m_sStyleScheme.m_iHtmlLineHeight = _ttoi(strValue);

	g_GlobalUtils.m_sStyleScheme.m_bHtmlShowLangTitle = ((CButton *)GetDlgItem(IDC_CHECK_SHOW_LANGTITLE))->GetCheck();
	g_GlobalUtils.m_sStyleScheme.m_bHtmlShowAddTitle = ((CButton *)GetDlgItem(IDC_CHECK_SHOW_ADDTITLE))->GetCheck();
	if (g_GlobalUtils.m_sStyleScheme.m_bHtmlShowAddTitle)
	{
		GetDlgItemText(IDC_EDIT_ADDTITLE, strValue);
		g_GlobalUtils.m_sStyleScheme.m_strHtmlAddTitle = strValue;
	}
	g_GlobalUtils.m_sStyleScheme.m_bHtmlAutoCopy = ((CButton *)GetDlgItem(IDC_CHECK_AUTO_COPY))->GetCheck();
	g_GlobalUtils.m_sStyleScheme.m_bHtmlCopyCode = ((CButton *)GetDlgItem(IDC_CHECK_COPY_CODE))->GetCheck();
}

void CSetHtmlDlg::OnBnClickedCheckAutoCopy()
{
	BOOL bShow = ((CButton *)GetDlgItem(IDC_CHECK_AUTO_COPY))->GetCheck();
	GetDlgItem(IDC_CHECK_COPY_CODE)->EnableWindow(bShow);
	if (FALSE == bShow)
	{
		((CButton *)GetDlgItem(IDC_CHECK_COPY_CODE))->SetCheck(0);
	}
}
