// MulTextEditDlg.cpp : 实现文件

#include "stdafx.h"
#include "CoolFormat3.h"
#include "MulTextEditDlg.h"

// CMulTextEditDlg 对话框

IMPLEMENT_DYNAMIC(CMulTextEditDlg, CBCGPDialog)

CMulTextEditDlg::CMulTextEditDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CMulTextEditDlg::IDD, pParent)
{
}

CMulTextEditDlg::~CMulTextEditDlg()
{
}

void CMulTextEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LINE, m_strValue);
}

BEGIN_MESSAGE_MAP(CMulTextEditDlg, CBCGPDialog)
END_MESSAGE_MAP()

void CMulTextEditDlg::SetText(LPCTSTR lpszText)
{
	m_strValue = lpszText;
}

LPCTSTR CMulTextEditDlg::GetText()
{
	return m_strValue;
}

BOOL CMulTextEditDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	InitLang();

	if (!IsVisualManagerStyle())
	{
		EnableVisualManagerStyle(TRUE, TRUE);
	}
	return TRUE;
}

void CMulTextEditDlg::InitLang()
{
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDOK);
	ASSERT(bNameVaild);
	SetDlgItemText(IDOK, strTemp);

	bNameVaild = strTemp.LoadString(IDCANCEL);
	ASSERT(bNameVaild);
	SetDlgItemText(IDCANCEL, strTemp);

	bNameVaild = strTemp.LoadString(IDS_MULTEXT_EDIT_DLG);
	ASSERT(bNameVaild);
	SetWindowText(strTemp);

	GetDlgItem(IDC_LINE)->SetFocus();
}
