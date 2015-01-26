// GotoLineDlg.cpp : 实现文件

#include "stdafx.h"
#include "CoolFormat3.h"
#include "GotoLineDlg.h"

// CGotoLineDlg 对话框

IMPLEMENT_DYNAMIC(CGotoLineDlg, CBCGPDialog)

CGotoLineDlg::CGotoLineDlg(CWnd* pParent /*=NULL*/, int nMaxLine)
	: CBCGPDialog(CGotoLineDlg::IDD, pParent)
	, m_nLineNumber(1)
{
	m_nMaxLine = nMaxLine;
}

CGotoLineDlg::~CGotoLineDlg()
{
}

void CGotoLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LINE, m_nLineNumber);
}

BEGIN_MESSAGE_MAP(CGotoLineDlg, CBCGPDialog)
END_MESSAGE_MAP()

// CGotoLineDlg 消息处理程序

BOOL CGotoLineDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	InitLang();

	if (!IsVisualManagerStyle())
	{
		EnableVisualManagerStyle(TRUE, TRUE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CGotoLineDlg::InitLang()
{
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDOK);
	ASSERT(bNameVaild);
	SetDlgItemText(IDOK, strTemp);

	bNameVaild = strTemp.LoadString(IDCANCEL);
	ASSERT(bNameVaild);
	SetDlgItemText(IDCANCEL, strTemp);

	bNameVaild = strTemp.LoadString(IDS_GOTOLINE_DLG);
	ASSERT(bNameVaild);
	SetWindowText(strTemp);

	bNameVaild = strTemp.LoadString(IDS_GOTOLINE_DLG_TIP);
	ASSERT(bNameVaild);
	CString strTip;
	strTip.Format(strTemp, m_nMaxLine);
	GetDlgItem(IDC_LINETIP)->SetWindowText(strTip);
	GetDlgItem(IDC_LINE)->SetFocus();
}
