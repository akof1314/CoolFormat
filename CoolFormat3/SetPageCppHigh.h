#pragma once

//////////////////////////////////////////////////////////////////////////
// CSetPageCppHigh 对话框

class CSetPageCppHigh : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetPageCppHigh)
public:
	CSetPageCppHigh(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetPageCppHigh();

// 对话框数据
	enum { IDD = IDD_SET_CPP_HIGH };
	void SetViewEditWnd(CWnd *pWnd){m_pEditWnd = pWnd;};
	void SetTidyConfig(LPCTSTR lpszTidy);
	void GetTidyConfig(CString &strTidyValue);

protected:
	CWnd *m_pEditWnd; //保存预览框句柄
	void SetViewEdit(LPCTSTR lpszText);
	void InitLimit();
	void SetTidyControl(LPCTSTR lpszTidy, int nPos, int nSize);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnCbnSelchangeComboCppIndentTab();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckCppIndentClass();
	afx_msg void OnBnClickedCheckCppIndentSwitch();
	afx_msg void OnBnClickedCheckCppIndentCase();
	afx_msg void OnBnClickedCheckCppIndentNamespaces();
	afx_msg void OnBnClickedCheckCppIndentLabel();
	afx_msg void OnBnClickedCheckCppIndentPrepro();
	afx_msg void OnBnClickedCheckCppIndentCol1comment();
	afx_msg void OnBnClickedCheckCppBreakBlocks();
	afx_msg void OnBnClickedCheckCppBreakAllblocks();
	afx_msg void OnBnClickedCheckCppPadOper();
	afx_msg void OnBnClickedCheckCppPadParens();
	afx_msg void OnBnClickedCheckCppPadParensout();
	afx_msg void OnBnClickedCheckCppPadParensin();
	afx_msg void OnBnClickedCheckCppPadHeader();
	afx_msg void OnBnClickedCheckCppUnpadParens();
	afx_msg void OnBnClickedCheckCppDelEmptylines();
	afx_msg void OnBnClickedCheckCppFillEmptylines();
	afx_msg void OnBnClickedCheckCppBreakClosingbrackets();
	afx_msg void OnBnClickedCheckCppBreakElseifs();
	afx_msg void OnBnClickedCheckCppAddBrackets();
	afx_msg void OnBnClickedCheckCppAddOnelinebrackets();
	afx_msg void OnBnClickedCheckCppKeepOnelineblocks();
	afx_msg void OnBnClickedCheckCppKeepOnelinestate();
	afx_msg void OnBnClickedCheckCppConvertTabs();
	afx_msg void OnCbnSelchangeComboCppMinConditional();
	afx_msg void OnCbnSelchangeComboCppMaxInstatement();
	afx_msg void OnCbnSelchangeComboCppAlignPointer();
	afx_msg void OnCbnSelchangeComboCppAlignReference();
};
