#pragma once
#include "kofColorButton.h"

//////////////////////////////////////////////////////////////////////////
// CSetEditDlg 对话框

const int MAX_COLOR_EDIT = 18;

class CSetEditDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetEditDlg)

public:
	CSetEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetEditDlg();

// 对话框数据
	enum { IDD = IDD_SYNEDIT_SET };

protected:
	CBCGPFontComboBox m_editFont;
	CBCGPComboBox m_editSize;
	CBCGPComboBox m_editStyle;

	CkofColorButton m_colorBack;
	CkofColorButton m_colorLineOutLine;
	CkofColorButton m_colorSyn;
	CkofColorButton m_colorText;
	CkofColorButton m_colorBackOutLine;
	CkofColorButton m_colorType;
	CkofColorButton m_colorLineNumber;
	CkofColorButton m_colorBackSelActive;
	CkofColorButton m_colorString;
	CkofColorButton m_colorLineNumberBack;
	CkofColorButton m_colorBackSelInactive;
	CkofColorButton m_colorNumber;
	CkofColorButton m_colorSidebar;
	CkofColorButton m_colorTextSelActive;
	CkofColorButton m_colorChar;
	CkofColorButton m_colorLink;
	CkofColorButton m_colorTextSelInactive;
	CkofColorButton m_colorComment;
	CBCGPURLLinkButton m_btnDefaultLink;

	void InitLang();
	void InitColor();
	void GetColor();
	void InitFont();
	void GetFont();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnOK();
};
