#pragma once
#include "kofColorButton.h"

//////////////////////////////////////////////////////////////////////////
// CSetHtmlDlg 对话框

class CSetHtmlDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetHtmlDlg)

public:
	CSetHtmlDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetHtmlDlg();

// 对话框数据
	enum { IDD = IDD_SYNHTML_SET };

protected:
	CBCGPFontComboBox m_htmlFont;
	CBCGPComboBox m_htmlStyle;
	CBCGPComboBox m_htmlSize;
	
	CBCGPComboBox m_borderStyle;
	CkofColorButton m_borderColor;
	CkofColorButton m_backgroundColor;
	CBCGPURLLinkButton m_btnDefaultLink;
	void InitLang();
	void InitFont();
	void InitStyle();
	void GetFont(void);
	void GetStyle(void);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckShowBorder();
	afx_msg void OnBnClickedCheckShowLinenumber();
	afx_msg void OnBnClickedCheckShowSidebar();
	afx_msg void OnBnClickedCheckShowLangtitle();
	afx_msg void OnBnClickedCheckShowAddtitle();
	afx_msg void OnBnClickedCheckAutoCopy();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
