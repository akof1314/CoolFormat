// PageResource.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "PageResource.h"
#include "TellBug.h"

// CPageResource 对话框

IMPLEMENT_DYNCREATE(CPageResource, CBCGPPropertyPage)

CPageResource::CPageResource()
	: CBCGPPropertyPage(CPageResource::IDD, IDS_STRING_RES_TITLE)
{

}

CPageResource::~CPageResource()
{
}

void CPageResource::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageResource, CBCGPPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_CHECKUPDATE, &CPageResource::OnBnClickedButtonCheckupdate)
	ON_BN_CLICKED(IDC_BUTTON_LINKME, &CPageResource::OnBnClickedButtonLinkme)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, &CPageResource::OnBnClickedButtonAbout)
END_MESSAGE_MAP()


// CPageResource 消息处理程序

void CPageResource::OnBnClickedButtonCheckupdate()
{
	ShellExecute(NULL, _T("open"), _T("http://blog.csdn.net/akof1314/archive/2010/03/08/5355948.aspx"), NULL, NULL, SW_SHOW);
}

void CPageResource::OnBnClickedButtonLinkme()
{
	CTellBug dlg;
	dlg.DoModal();
}

void CPageResource::OnBnClickedButtonAbout()
{
	((CCoolFormat3App *)AfxGetApp())->OnAppAbout();
}

BOOL CPageResource::OnInitDialog()
{
	CBCGPPropertyPage::OnInitDialog();

	InitLang();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CPageResource::InitLang()
{
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STRING_RES_UPDATE);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_RESUPDATE, strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_RES_LINKEME);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_LINKME, strTemp);
	SetDlgItemText(IDC_BUTTON_LINKME, strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_RES_TITLE);
	ASSERT(bNameVaild);
	SetWindowText(strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_RES_CHECKUP);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_BUTTON_CHECKUPDATE, strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_RES_ABOUTLB);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_ABOUT, strTemp);

	bNameVaild = strTemp.LoadString(IDS_STRING_RES_ABOUT);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_BUTTON_ABOUT, strTemp);
}