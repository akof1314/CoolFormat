#pragma once

//////////////////////////////////////////////////////////////////////////
// CSetPageHtmlTwo 对话框

class CSetPageHtmlTwo : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetPageHtmlTwo)
public:
	CSetPageHtmlTwo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetPageHtmlTwo();

// 对话框数据
	enum { IDD = IDD_SET_HTML_TWO };
	void SetViewEditWnd(CWnd *pWnd){m_pEditWnd = pWnd;};
	void SetTidyConfig(LPCTSTR lpszTidy, UINT uLangID);
	void GetTidyConfig(CString &strTidyValue);

protected:
	CWnd *m_pEditWnd; //保存预览框句柄
	void SetViewEdit(LPCTSTR lpszText);
	void SetTidyControl(LPCTSTR lpszTidy, int nPos, int nSize);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitLimit();
	UINT m_onlyHtmlXml;
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckHtmlBreakBeforeBr();
	afx_msg void OnBnClickedCheckHtmlIndentAttributes();
	afx_msg void OnBnClickedCheckHtmlIndentSpaces();
	afx_msg void OnBnClickedCheckHtmlMarkup();
	afx_msg void OnBnClickedCheckHtmlPunctuationWrap();
	afx_msg void OnBnClickedCheckHtmlVerticalSpace();
	afx_msg void OnBnClickedCheckHtmlWrapAsp();
	afx_msg void OnBnClickedCheckHtmlWrapAttributes();
	afx_msg void OnBnClickedCheckHtmlWrapJste();
	afx_msg void OnBnClickedCheckHtmlWrapPhp();
	afx_msg void OnBnClickedCheckHtmlWrapScriptLiterals();
	afx_msg void OnBnClickedCheckHtmlWrapSections();
	afx_msg void OnBnClickedCheckHtmlAsciiChars();
	afx_msg void OnBnClickedCheckHtmlShowWarnings();
	afx_msg void OnEnSetfocusEditHtmlAltText();
	afx_msg void OnEnSetfocusEditHtmlCssPrefix();
	afx_msg void OnCbnSetfocusComboHtmlIndent();
	afx_msg void OnCbnSetfocusComboHtmlMergeDivs();
	afx_msg void OnEnSetfocusEditHtmlNewBlocklevelTags();
	afx_msg void OnEnSetfocusEditHtmlNewEmptyTags();
	afx_msg void OnEnSetfocusEditHtmlNewInlineTags();
	afx_msg void OnEnSetfocusEditHtmlNewPreTags();
	afx_msg void OnEnSetfocusEditHtmlShowErrors();
	afx_msg void OnEnSetfocusEditHtmlIndentSpaces();
	afx_msg void OnEnSetfocusEditHtmlTabSize();
	afx_msg void OnEnSetfocusEditHtmlWrap();
	afx_msg void OnCbnSetfocusComboHtmlMergeSpans();
	afx_msg void OnCbnSetfocusComboHtmlShowBodyOnly();
	afx_msg void OnCbnSetfocusComboHtmlDoctype();
	afx_msg void OnCbnSetfocusComboHtmlRepeatedAttributes();
	afx_msg void OnCbnSetfocusComboHtmlSortAttributes();
	afx_msg void OnCbnSetfocusComboHtmlCharEncoding();
	afx_msg void OnCbnSetfocusComboHtmlInputEncoding();
	afx_msg void OnCbnSetfocusComboHtmlOutputEncoding();
	afx_msg void OnBnClickedCheckHtmlForceOutput();
};
