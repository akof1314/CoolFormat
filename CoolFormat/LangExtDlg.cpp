// LangExtDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "LangExtDlg.h"
#include "GlobalUtils.h"
#include "LangExtEditDlg.h"
// CLangExtDlg 对话框

IMPLEMENT_DYNAMIC(CLangExtDlg, CBCGPDialog)

CLangExtDlg::CLangExtDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CLangExtDlg::IDD, pParent)
{

}

CLangExtDlg::~CLangExtDlg()
{
}

void CLangExtDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LANGEXT, m_listLangExt);
	DDX_Control(pDX, IDC_BUTTON_DEFAULTEXT, m_btnDefaultLink);
}


BEGIN_MESSAGE_MAP(CLangExtDlg, CBCGPDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_LANGEXT, &CLangExtDlg::OnNMDblclkListLangext)
END_MESSAGE_MAP()



BOOL CLangExtDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	InitLang();
	InitList();
	
	m_btnDefaultLink.SizeToContent();

	if (!IsVisualManagerStyle())
	{
		EnableVisualManagerStyle(TRUE, TRUE);
	}

	GetDlgItem(IDCANCEL)->SetFocus();
	return FALSE;
}

void CLangExtDlg::InitList()
{
	m_listLangExt.SetRedraw(FALSE);

	m_listLangExt.SetExtendedStyle(m_listLangExt.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//插入列头
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_LANGUAGE);
	ASSERT(bNameVaild);
	m_listLangExt.InsertColumn(0, strTemp, LVCFMT_LEFT, 82);
	bNameVaild = strTemp.LoadString(IDS_LANGUAGEEXT);
	ASSERT(bNameVaild);
	m_listLangExt.InsertColumn(1, strTemp, LVCFMT_LEFT, 370);

	//插入行
	CString strExt;
	for (UINT i = 0; i < MAX_SYN_LANG; ++i)
	{
		g_GlobalUtils.m_sLanguageExt.GetLanguageFilter(i, strExt);
		m_listLangExt.InsertItem(i, CSynExtension::m_LangNames[i].langName);
		m_listLangExt.SetItemText(i, 1, strExt);
		m_aryExt[i] = 0;
	}
	m_listLangExt.SetRedraw(TRUE);
}

void CLangExtDlg::OnNMDblclkListLangext(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (-1 != pNMItemActivate->iItem)
	{		
		CLangExtEditDlg dlg(m_listLangExt.GetItemText(pNMItemActivate->iItem, 0), m_listLangExt.GetItemText(pNMItemActivate->iItem, 1));
		 if (IDOK == dlg.DoModal())
		 {
			 m_listLangExt.SetItemText(pNMItemActivate->iItem, 1, dlg.GetStrExt());
			 m_aryExt[pNMItemActivate->iItem] = 1;
		 }
	}	
	*pResult = 0;
}

void CLangExtDlg::InitLang()
{
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDOK);
	ASSERT(bNameVaild);
	SetDlgItemText(IDOK, strTemp);

	bNameVaild = strTemp.LoadString(IDCANCEL);
	ASSERT(bNameVaild);
	SetDlgItemText(IDCANCEL, strTemp);

	bNameVaild = strTemp.LoadString(IDS_LANGEXT_DLG);
	ASSERT(bNameVaild);
	SetWindowText(strTemp);

	bNameVaild = strTemp.LoadString(IDS_LANGEXT_DLG_TIP);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_TIP, strTemp);

	bNameVaild = strTemp.LoadString(IDC_BUTTON_DEFAULTEXT);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_BUTTON_DEFAULTEXT, strTemp);
}

BOOL CLangExtDlg::PreTranslateMessage(MSG* pMsg)
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
				CString strExt;
				for (UINT i = 0; i < MAX_SYN_LANG; ++i)
				{
					g_GlobalUtils.m_sLanguageExt.GetLanguageFilter(i, strExt);
					if (!strExt.IsEmpty() && strExt.Compare(CSynExtension::m_LangNames[i].extName))
					{
						m_aryExt[i] = 1;
						m_listLangExt.SetItemText(i, 1, CSynExtension::m_LangNames[i].extName);
					}
					else
					{
						if (m_aryExt[i] == 1)
						{
							m_aryExt[i] = 0;
							m_listLangExt.SetItemText(i, 1, CSynExtension::m_LangNames[i].extName);
						}
					}
				}
			}
			return TRUE;
		}
	}

	return CBCGPDialog::PreTranslateMessage(pMsg);
}

void CLangExtDlg::OnOK()
{
	BOOL bRegVaild = TRUE;
	CString strExt;
	LPCTSTR lpszSubSection = _T("SynExt");
	CString strSection = theApp.GetRegSectionPath(lpszSubSection);

	CBCGPRegistrySP regSP;
	CBCGPRegistry& reg = regSP.Create (FALSE, FALSE);

	if (reg.CreateKey(strSection))
	{
		for (UINT i = 0; i < MAX_SYN_LANG; ++i)
		{
			if (m_aryExt[i] == 1)
			{
				strExt = m_listLangExt.GetItemText(i, 1);
				if (!reg.Write(CSynExtension::m_LangNames[i].langName, strExt))
				{
					bRegVaild = FALSE;
				}
				g_GlobalUtils.m_sLanguageExt.SetLanguageFilter(i, strExt);
			}
		}
	}
	else
	{
		bRegVaild = FALSE;
	}
	
	if (!bRegVaild)
	{
		bRegVaild = strExt.LoadString(IDS_REG_ERROR);
		ASSERT(bRegVaild);
		CFMessageBox(strExt, MB_ICONSTOP);
	}

	CBCGPDialog::OnOK();
}
