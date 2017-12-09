// TellBug.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "GlobalUtils.h"
#include "TellBug.h"

//////////////////////////////////////////////////////////////////////////
// CTellBug 对话框

IMPLEMENT_DYNAMIC(CTellBug, CBCGPDialog)

CTellBug::CTellBug(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CTellBug::IDD, pParent)
{

}

CTellBug::~CTellBug()
{
}

void CTellBug::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LINK_EMAIL, m_btnLinkEmail);
	DDX_Control(pDX, IDC_LINK_CSDN, m_btnLinkCsdn);
	DDX_Control(pDX, IDC_LINK_QQ, m_btnLinkQQ);
}

BEGIN_MESSAGE_MAP(CTellBug, CBCGPDialog)
END_MESSAGE_MAP()

BOOL CTellBug::OnInitDialog()
{
    CBCGPDialog::OnInitDialog();

    SendMessageToDescendants(WM_SETFONT, (WPARAM)globalData.fontRegular.m_hObject, MAKELPARAM(FALSE, 0), FALSE);
	InitLang();
	SetLinkBtn();

	if (!IsVisualManagerStyle())
	{
		EnableVisualManagerStyle(TRUE, TRUE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTellBug::SetLinkBtn()
{
	m_btnLinkEmail.SetURL(_T("kof1234@sina.com"));
	m_btnLinkEmail.SetURLPrefix(_T("mailto:"));
	m_btnLinkEmail.SizeToContent();

	m_btnLinkCsdn.SetURL(_T("http://blog.csdn.net/akof1314/article/details/5355948"));
	m_btnLinkCsdn.SizeToContent();

	m_btnLinkQQ.SetURL(_T("https://github.com/akof1314/CoolFormat/issues"));
	m_btnLinkQQ.SizeToContent();
}

void CTellBug::InitLang()
{
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDOK);
	ASSERT(bNameVaild);
	SetDlgItemText(IDOK, strTemp);

	bNameVaild = strTemp.LoadString(IDD_TELL_BUG);
	ASSERT(bNameVaild);
	SetWindowText(strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_TELLBUG_TOP);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_TELLBUG_TOP, strTemp);

	bNameVaild = strTemp.LoadString(IDC_STATIC_TELLBUG_TIJIAO);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_TELLBUG_TIJIAO, strTemp);
	SetDlgItemSizeToContent(GetDlgItem(IDC_STATIC_TELLBUG_TIJIAO));

	bNameVaild = strTemp.LoadString(IDC_STATIC_EMAIL);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_EMAIL, strTemp);
	SetDlgItemSizeToContent(GetDlgItem(IDC_STATIC_EMAIL));

	bNameVaild = strTemp.LoadString(IDC_STATIC_CSDN);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_CSDN, strTemp);
	SetDlgItemSizeToContent(GetDlgItem(IDC_STATIC_CSDN));

	bNameVaild = strTemp.LoadString(IDC_STATIC_QQ);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_QQ, strTemp);
	SetDlgItemSizeToContent(GetDlgItem(IDC_STATIC_QQ));

	bNameVaild = strTemp.LoadString(IDS_EMAIL_TIP);
	ASSERT(bNameVaild);
	m_btnLinkEmail.SetTooltip(strTemp);

	bNameVaild = strTemp.LoadString(IDS_CSDN_TIP);
	ASSERT(bNameVaild);
	m_btnLinkCsdn.SetTooltip(strTemp);

    bNameVaild = strTemp.LoadString(IDS_CSDN_TIP);
	ASSERT(bNameVaild);
	m_btnLinkQQ.SetTooltip(strTemp);
}