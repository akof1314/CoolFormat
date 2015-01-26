// LangExtEditDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "LangExtEditDlg.h"


// CLangExtEditDlg 对话框

IMPLEMENT_DYNAMIC(CLangExtEditDlg, CBCGPDialog)

CLangExtEditDlg::CLangExtEditDlg(const CString &strLang, const CString &strExt, CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CLangExtEditDlg::IDD, pParent)
	, m_strLang(strLang)
	, m_strExt(strExt)
{

}

CLangExtEditDlg::~CLangExtEditDlg()
{
}

void CLangExtEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LANG, m_strLang);
	DDX_Text(pDX, IDC_EDIT_EXT, m_strExt);
}


BEGIN_MESSAGE_MAP(CLangExtEditDlg, CBCGPDialog)
END_MESSAGE_MAP()


// CLangExtEditDlg 消息处理程序

void CLangExtEditDlg::OnOK()
{
	UpdateData();

	CBCGPDialog::OnOK();
}

BOOL CLangExtEditDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	InitLang();

	if (!IsVisualManagerStyle())
	{
		EnableVisualManagerStyle(TRUE, TRUE);
	}

	GetDlgItem(IDCANCEL)->SetFocus();
	return FALSE;
}

void CLangExtEditDlg::InitLang()
{
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDOK);
	ASSERT(bNameVaild);
	SetDlgItemText(IDOK, strTemp);

	bNameVaild = strTemp.LoadString(IDCANCEL);
	ASSERT(bNameVaild);
	SetDlgItemText(IDCANCEL, strTemp);

	bNameVaild = strTemp.LoadString(IDS_LANGUAGE_EX);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_LANG, strTemp);

	bNameVaild = strTemp.LoadString(IDS_LANGUAGEEXT_EX);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_EXT, strTemp);

	bNameVaild = strTemp.LoadString(IDS_LANGEXT_EDIT_DLG);
	ASSERT(bNameVaild);
	SetWindowText(strTemp);
}