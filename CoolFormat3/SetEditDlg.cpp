// SetEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetEditDlg.h"


// CSetEditDlg 对话框

IMPLEMENT_DYNAMIC(CSetEditDlg, CBCGPDialog)

CSetEditDlg::CSetEditDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetEditDlg::IDD, pParent)
{
	InitColor();
}

CSetEditDlg::~CSetEditDlg()
{
}

void CSetEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_EDITFONT, m_editFont);
	DDX_Control(pDX, IDC_COMBO_EDITSIZE, m_editSize);
	DDX_Control(pDX, IDC_COMBO_EDITSTYLE, m_editStyle);
	DDX_Control(pDX, IDC_BUTTON_COLOR_BACK, m_colorBack);
	DDX_Control(pDX, IDC_BUTTON_COLOR_BACK, m_colorBack);           
	DDX_Control(pDX, IDC_BUTTON_COLOR_LINEOUTLINE, m_colorLineOutLine);    
	DDX_Control(pDX, IDC_BUTTON_COLOR_SYN, m_colorSyn);
	DDX_Control(pDX, IDC_BUTTON_COLOR_TEXT, m_colorText);
	DDX_Control(pDX, IDC_BUTTON_COLOR_BACKOUTLINE, m_colorBackOutLine);
	DDX_Control(pDX, IDC_BUTTON_COLOR_TYPE, m_colorType);
	DDX_Control(pDX, IDC_BUTTON_COLOR_LINENUMBER, m_colorLineNumber);
	DDX_Control(pDX, IDC_BUTTON_COLOR_BACKSELACTIVE, m_colorBackSelActive);
	DDX_Control(pDX, IDC_BUTTON_COLOR_STRING, m_colorString);
	DDX_Control(pDX, IDC_BUTTON_COLOR_LINENUMBERBACK, m_colorLineNumberBack);
	DDX_Control(pDX, IDC_BUTTON_COLOR_BACKSELINACTIVE, m_colorBackSelInactive);
	DDX_Control(pDX, IDC_BUTTON_COLOR_NUMBER, m_colorNumber);
	DDX_Control(pDX, IDC_BUTTON_COLOR_SIDEBAR, m_colorSidebar);
	DDX_Control(pDX, IDC_BUTTON_COLOR_TEXTSELACTIVE, m_colorTextSelActive);
	DDX_Control(pDX, IDC_BUTTON_COLOR_CHAR, m_colorChar);
	DDX_Control(pDX, IDC_BUTTON_COLOR_LINK, m_colorLink);
	DDX_Control(pDX, IDC_BUTTON_COLOR_TEXTSELINACTIVE, m_colorTextSelInactive);
	DDX_Control(pDX, IDC_BUTTON_COLOR_COMMENT, m_colorComment);
	DDX_Control(pDX, IDC_BUTTON_DEFAULTEXT, m_btnDefaultLink);
}


BEGIN_MESSAGE_MAP(CSetEditDlg, CBCGPDialog)
	ON_BN_CLICKED(IDOK, &CSetEditDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetEditDlg 消息处理程序

BOOL CSetEditDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	InitLang();

	CBCGPFontComboBox::m_bDrawUsingFont = TRUE;
	m_editFont.Setup();
	m_editSize.SetItemHeight(-1, m_editSize.GetItemHeight(-1) + 3);
	m_editStyle.SetItemHeight(-1, m_editStyle.GetItemHeight(-1) + 3);	
	m_btnDefaultLink.SizeToContent();

	InitFont();

	GetDlgItem(IDCANCEL)->SetFocus();
	return FALSE;
}

void CSetEditDlg::OnBnClickedOk()
{
	OnOK();
}

void CSetEditDlg::InitLang()
{
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDOK);
	ASSERT(bNameVaild);
	SetDlgItemText(IDOK, strTemp);

	bNameVaild = strTemp.LoadString(IDCANCEL);
	ASSERT(bNameVaild);
	SetDlgItemText(IDCANCEL, strTemp);

	bNameVaild = strTemp.LoadString(IDD_SYNEDIT_SET);
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

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_BACK);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_BACK, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_LINEOUTLINE);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_LINEOUTLINE, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_SYN);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_SYN, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_TEXT);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_TEXT, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_BACKOUTLINE);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_BACKOUTLINE, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_TYPE);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_TYPE, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_LINENUMBER);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_LINENUMBER, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_BACKSELACTIVE);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_BACKSELACTIVE, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_STRING);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_STRING, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_LINENUMBERBACK);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_LINENUMBERBACK, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_BACKSELINACTIVE);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_BACKSELINACTIVE, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_NUMBER);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_NUMBER, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_SIDEBAR);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_SIDEBAR, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_TEXTSELACTIVE);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_TEXTSELACTIVE, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_CHAR);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_CHAR, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_LINK);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_LINK, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_TEXTSELINACTIVE);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_TEXTSELINACTIVE, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR_COMMENT);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR_COMMENT, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_FONT);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_FONT, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_COLOR);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_COLOR, strTemp);

	bNameVaild = strTemp.LoadString(IDS_EDITSTYLE_DATA);
	ASSERT(bNameVaild);
	m_editStyle.ResetContent();
	int nStart = 0;
	int nEnd = strTemp.Find(_T(";"), nStart);
	while (nEnd != -1)
	{
		m_editStyle.AddString(strTemp.Mid(nStart, nEnd - nStart));
		nStart = nEnd + 1;
		nEnd = strTemp.Find(_T(";"), nStart);
	}
}

BOOL CSetEditDlg::PreTranslateMessage(MSG* pMsg)
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
				m_colorBack.SetColor(GetSysColor (COLOR_WINDOW));
				m_colorText.SetColor(GetSysColor (COLOR_WINDOWTEXT));
				m_colorLineOutLine.SetColor(RGB (128, 128, 128));
				m_colorBackOutLine.SetColor(RGB (255, 255, 255));
				m_colorSidebar.SetColor(RGB (0, 130, 132));
				m_colorLineNumber.SetColor(RGB (0, 130, 132));
				m_colorBackSelActive.SetColor(g_GlobalUtils.m_sColorScheme.m_DefclrBackSelActive);
				m_colorBackSelInactive.SetColor(g_GlobalUtils.m_sColorScheme.m_DefclrBackSelInActive);
				m_colorTextSelActive.SetColor(g_GlobalUtils.m_sColorScheme.m_DefclrTextSelActive);
				m_colorTextSelInactive.SetColor(g_GlobalUtils.m_sColorScheme.m_DefclrTextSelInActive);
				m_colorLink.SetColor(RGB(0, 102, 204));
				m_colorLineNumberBack.SetColor(RGB (227, 227, 227));

				m_colorSyn.SetColor(RGB (0, 0, 255));
				m_colorType.SetColor(RGB (128, 0, 255));
				m_colorNumber.SetColor(RGB(255, 0, 0));
				m_colorString.SetColor(RGB(128, 0, 0));
				m_colorChar.SetColor(RGB(128, 0, 0));
				m_colorComment.SetColor(RGB(0, 128, 0));	

				m_editFont.SelectFont(_T("Consolas"));	
				m_editStyle.SetCurSel(0);
				CString strSize = _T("10");
				m_editSize.SelectString(-1, strSize);
			}
			return TRUE;
		}
	}
	return CBCGPDialog::PreTranslateMessage(pMsg);
}

void CSetEditDlg::InitColor()
{
	m_colorBack.SetColor(g_GlobalUtils.m_sColorScheme.m_clrBack);
	m_colorText.SetColor(g_GlobalUtils.m_sColorScheme.m_clrText);
	m_colorLineOutLine.SetColor(g_GlobalUtils.m_sColorScheme.m_clrLineOutline);
	m_colorBackOutLine.SetColor(g_GlobalUtils.m_sColorScheme.m_clrBackOutline);
	m_colorSidebar.SetColor(g_GlobalUtils.m_sColorScheme.m_clrBackSidebar);
	m_colorLineNumber.SetColor(g_GlobalUtils.m_sColorScheme.m_clrTextLineNumber);
	m_colorBackSelActive.SetColor(g_GlobalUtils.m_sColorScheme.m_clrBackSelActive);
	m_colorBackSelInactive.SetColor(g_GlobalUtils.m_sColorScheme.m_clrBackSelInActive);
	m_colorTextSelActive.SetColor(g_GlobalUtils.m_sColorScheme.m_clrTextSelActive);
	m_colorTextSelInactive.SetColor(g_GlobalUtils.m_sColorScheme.m_clrTextSelInActive);
	m_colorLink.SetColor(g_GlobalUtils.m_sColorScheme.m_clrHyperlink);
	m_colorLineNumberBack.SetColor(g_GlobalUtils.m_sColorScheme.m_clrBackLineNumber);

	m_colorSyn.SetColor(g_GlobalUtils.m_sColorScheme.m_clrSyn);
	m_colorType.SetColor(g_GlobalUtils.m_sColorScheme.m_clrType);
	m_colorString.SetColor(g_GlobalUtils.m_sColorScheme.m_clrString);
	m_colorNumber.SetColor(g_GlobalUtils.m_sColorScheme.m_clrNumber);
	m_colorChar.SetColor(g_GlobalUtils.m_sColorScheme.m_clrChar);
	m_colorComment.SetColor(g_GlobalUtils.m_sColorScheme.m_clrComment);
}

void CSetEditDlg::OnOK()
{
	GetColor();
	GetFont();
	BOOL bRegVaild = TRUE;
	LPCTSTR lpszSubSection = _T("SynColor");
	CString strSection = theApp.GetRegSectionPath(lpszSubSection);

	CBCGPRegistrySP regSP;
	CBCGPRegistry& reg = regSP.Create (FALSE, FALSE);

	if (reg.CreateKey(strSection))
	{
		if (!reg.Write(_T("clrBack"), g_GlobalUtils.m_sColorScheme.m_clrBack))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrText"), g_GlobalUtils.m_sColorScheme.m_clrText))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrBackSelActive"), g_GlobalUtils.m_sColorScheme.m_clrBackSelActive))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrBackSelInActive"), g_GlobalUtils.m_sColorScheme.m_clrBackSelInActive))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrTextSelActive"), g_GlobalUtils.m_sColorScheme.m_clrTextSelActive))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrTextSelInActive"), g_GlobalUtils.m_sColorScheme.m_clrTextSelInActive))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrBackOutline"), g_GlobalUtils.m_sColorScheme.m_clrBackOutline))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrLineOutline"), g_GlobalUtils.m_sColorScheme.m_clrLineOutline))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrBackLineNumber"), g_GlobalUtils.m_sColorScheme.m_clrBackLineNumber))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrTextLineNumber"), g_GlobalUtils.m_sColorScheme.m_clrTextLineNumber))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrBackSidebar"), g_GlobalUtils.m_sColorScheme.m_clrBackSidebar))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrHyperlink"), g_GlobalUtils.m_sColorScheme.m_clrHyperlink))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrSyn"), g_GlobalUtils.m_sColorScheme.m_clrSyn))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrType"), g_GlobalUtils.m_sColorScheme.m_clrType))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrNumber"), g_GlobalUtils.m_sColorScheme.m_clrNumber))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrString"), g_GlobalUtils.m_sColorScheme.m_clrString))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrChar"), g_GlobalUtils.m_sColorScheme.m_clrChar))
		{
			bRegVaild = FALSE;
		}

		if (!reg.Write(_T("clrComment"), g_GlobalUtils.m_sColorScheme.m_clrComment))
		{
			bRegVaild = FALSE;
		}
	}
	else
	{
		bRegVaild = FALSE;
	}

	lpszSubSection = _T("SynStyle");
	strSection = theApp.GetRegSectionPath(lpszSubSection);

	CBCGPRegistrySP regSPFont;
	CBCGPRegistry& regFont = regSPFont.Create(FALSE, FALSE);

	if (regFont.CreateKey(strSection))
	{
		if (!regFont.Write(_T("EdtFontName"), g_GlobalUtils.m_sStyleScheme.m_strEdtFontName))
		{
			bRegVaild = FALSE;
		}

		if (!regFont.Write(_T("EdtFontBold"), g_GlobalUtils.m_sStyleScheme.m_bEdtFontBold))
		{
			bRegVaild = FALSE;
		}

		if (!regFont.Write(_T("EdtFontItalic"), g_GlobalUtils.m_sStyleScheme.m_bEdtFontItalic))
		{
			bRegVaild = FALSE;
		}

		if (!regFont.Write(_T("EdtFontSize"), (int)g_GlobalUtils.m_sStyleScheme.m_uEdtFontSize))
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

void CSetEditDlg::GetColor()
{
	g_GlobalUtils.m_sColorScheme.m_clrBack = m_colorBack.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrText = m_colorText.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrLineOutline = m_colorLineOutLine.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrBackOutline = m_colorBackOutLine.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrBackSidebar = m_colorSidebar.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrTextLineNumber = m_colorLineNumber.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrBackSelActive = m_colorBackSelActive.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrBackSelInActive = m_colorBackSelInactive.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrTextSelActive = m_colorTextSelActive.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrTextSelInActive = m_colorTextSelInactive.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrHyperlink = m_colorLink.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrBackLineNumber = m_colorLineNumberBack.GetColor();

	g_GlobalUtils.m_sColorScheme.m_clrSyn = m_colorSyn.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrType = m_colorType.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrString = m_colorString.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrNumber = m_colorNumber.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrChar = m_colorChar.GetColor();
	g_GlobalUtils.m_sColorScheme.m_clrComment = m_colorComment.GetColor();
}

void CSetEditDlg::InitFont()
{
	m_editFont.SelectFont(g_GlobalUtils.m_sStyleScheme.m_strEdtFontName);	
	m_editStyle.SetCurSel(g_GlobalUtils.m_sStyleScheme.m_bEdtFontBold + g_GlobalUtils.m_sStyleScheme.m_bEdtFontItalic);
	CString strSize;
	strSize.Format(_T("%d"), g_GlobalUtils.m_sStyleScheme.m_uEdtFontSize);
	m_editSize.SelectString(-1, strSize);
}

void CSetEditDlg::GetFont()
{
	CBCGPFontDesc *pFontDesc = m_editFont.GetSelFont();
	if (pFontDesc)
	{
		g_GlobalUtils.m_sStyleScheme.m_strEdtFontName = pFontDesc->m_strName;
	}
	g_GlobalUtils.m_sStyleScheme.m_bEdtFontBold = m_editStyle.GetCurSel() == 1 || m_editStyle.GetCurSel() == 3 ? TRUE : FALSE;
	g_GlobalUtils.m_sStyleScheme.m_bEdtFontItalic = m_editStyle.GetCurSel() == 2 || m_editStyle.GetCurSel() == 3 ? TRUE : FALSE;
	CString strSize;
	m_editSize.GetLBText(m_editSize.GetCurSel(), strSize);
	g_GlobalUtils.m_sStyleScheme.m_uEdtFontSize = _ttoi(strSize);
}