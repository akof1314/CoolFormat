#pragma once
#include "KofBCGPListCtrl.h"

//////////////////////////////////////////////////////////////////////////
// CLangExtDlg 对话框

class CLangExtDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CLangExtDlg)

public:
	CLangExtDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLangExtDlg();

// 对话框数据
	enum { IDD = IDD_LANG_EXT };

protected:
	CKofBCGPListCtrl m_listLangExt;
	CBCGPURLLinkButton m_btnDefaultLink;
	byte m_aryExt[MAX_SYN_LANG];
	void InitList();
	void InitLang();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkListLangext(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnOK();
};
