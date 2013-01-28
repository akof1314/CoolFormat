#pragma once

//////////////////////////////////////////////////////////////////////////
// CSetPageCSS 对话框

class CSetPageCSS : public CBCGPPropertyPage
{
	DECLARE_DYNCREATE(CSetPageCSS)
public:
	CSetPageCSS();
	virtual ~CSetPageCSS();

// 对话框数据
	enum { IDD = IDD_SET_CSS };
	void SetTidyConfig(LPCTSTR lpszTidy);
	void GetTidyConfig(CString &strTidyValue);

protected:
	void InitLimit();
	void SetViewEdit(LPCTSTR lpszText);
	void SetTidyControl(LPCTSTR lpszTidy, int nPos, int nSize);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboCssCompression();
	afx_msg void OnEnSetfocusEditCssTemplate();
	afx_msg void OnBnClickedCheckCssPreserve();
	afx_msg void OnBnClickedCheckCssSelectors();
	afx_msg void OnBnClickedCheckCssProperties();
	afx_msg void OnBnClickedCheckCssRemovelast();
	afx_msg void OnBnClickedCheckCssRemoveslash();
	afx_msg void OnBnClickedCheckCssDiscard();
	afx_msg void OnBnClickedCheckCssSilent();
	afx_msg void OnBnClickedCheckCssColors();
	afx_msg void OnBnClickedCheckCssFontweight();
	afx_msg void OnBnClickedCheckCssLowercase();
	afx_msg void OnBnClickedCheckCssTimestamp();
	afx_msg void OnCbnSelchangeComboCssCase();
	afx_msg void OnCbnSelchangeComboCssOptimise();
	afx_msg void OnCbnSelchangeComboCssRegroup();
	virtual void OnOK();
};
