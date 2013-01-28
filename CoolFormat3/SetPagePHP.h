#pragma once

//////////////////////////////////////////////////////////////////////////
// CSetPagePHP 对话框

class CSetPagePHP : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CSetPagePHP)
public:
	CSetPagePHP();
	virtual ~CSetPagePHP();

// 对话框数据
	enum { IDD = IDD_SET_PHP };
	void SetTidyConfig(LPCTSTR lpszTidy);
	void GetTidyConfig(CString &strTidyValue);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitLimit();
	void SetViewEdit(LPCTSTR lpszText);
	void SetTidyControl(LPCTSTR lpszTidy, int nPos, int nSize);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnCbnSelchangeComboPhpIndentTab();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboPhpIndentStyle();
	afx_msg void OnEnSetfocusEditPhpIndentNumber();
	afx_msg void OnEnSetfocusEditPhpFirstNumber();
	afx_msg void OnBnClickedCheckPhpSpaceStructures();
	afx_msg void OnBnClickedCheckPhpIndentCase();
	afx_msg void OnBnClickedCheckPhpBrackets();
	afx_msg void OnBnClickedCheckPhpEmptyBrackets();
	afx_msg void OnBnClickedCheckPhpBlockBrackets();
	afx_msg void OnBnClickedCheckPhpEmptyBlock();
	afx_msg void OnBnClickedCheckPhpMathOperators();
	afx_msg void OnBnClickedCheckPhpLogicalOperators();
	afx_msg void OnBnClickedCheckPhpEqualityOperators();
	afx_msg void OnBnClickedCheckPhpRelationalOper();
	afx_msg void OnBnClickedCheckPhpBitwiseOper();
	afx_msg void OnBnClickedCheckPhpAssignmentOper();
	afx_msg void OnBnClickedCheckPhpMapOper();
	afx_msg void OnBnClickedCheckPhpRemoveComments();
	afx_msg void OnBnClickedCheckPhpCommentStructures();
	afx_msg void OnBnClickedCheckPhpAlignAssignments();
	afx_msg void OnBnClickedCheckPhpRemoveEmptylines();
	afx_msg void OnBnClickedCheckPhpRemoveSemicolon();
	afx_msg void OnBnClickedCheckPhpIndentEmptylines();
	afx_msg void OnBnClickedCheckPhpRewritePerlComm();
	afx_msg void OnBnClickedCheckPhpRewriteShortTag();
	afx_msg void OnBnClickedCheckPhpAspTags();
	afx_msg void OnBnClickedCheckPhpShortTags();
	afx_msg void OnBnClickedCheckPhpQuiet();
	virtual void OnOK();
};
