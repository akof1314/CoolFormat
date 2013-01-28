#pragma once

//////////////////////////////////////////////////////////////////////////
// CSetPageHtmlOne 对话框

class CSetPageHtmlOne : public CBCGPDialog
{
	DECLARE_DYNAMIC(CSetPageHtmlOne)
public:
	CSetPageHtmlOne(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetPageHtmlOne();

// 对话框数据
	enum { IDD = IDD_SET_HTML_ONE };
	void SetViewEditWnd(CWnd *pWnd){m_pEditWnd = pWnd;};
	void SetTidyConfig(LPCTSTR lpszTidy);
	void GetTidyConfig(CString &strTidyValue);

protected:
	CWnd *m_pEditWnd; //保存预览框句柄
	void SetViewEdit(LPCTSTR lpszText);
	void SetTidyControl(LPCTSTR lpszTidy, int nPos, int nSize);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitLimit();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedCheckHtmlAddXmlDecl();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckHtmlAddXmlSpace();
	afx_msg void OnBnClickedCheckHtmlAnchorAsName();
	afx_msg void OnBnClickedCheckHtmlAssumeXmlProcins();
	afx_msg void OnBnClickedCheckHtmlBare();
	afx_msg void OnBnClickedCheckHtmlClean();
	afx_msg void OnBnClickedCheckHtmlDecorateInferredUl();
	afx_msg void OnBnClickedCheckHtmlDropEmptyParas();
	afx_msg void OnBnClickedCheckHtmlDropFontTags();
	afx_msg void OnBnClickedCheckHtmlDropProprietaryAtts();
	afx_msg void OnBnClickedCheckHtmlEncloseBlockText();
	afx_msg void OnBnClickedCheckHtmlEncloseText();
	afx_msg void OnBnClickedCheckHtmlEscapeCdata();
	afx_msg void OnBnClickedCheckHtmlFixBackslash();
	afx_msg void OnBnClickedCheckHtmlFixBadComments();
	afx_msg void OnBnClickedCheckHtmlFixUri();
	afx_msg void OnBnClickedCheckHtmlHideComments();
	afx_msg void OnBnClickedCheckHtmlHideEndtags();
	afx_msg void OnBnClickedCheckHtmlIndentCdata();
	afx_msg void OnBnClickedCheckHtmlInputXml();
	afx_msg void OnBnClickedCheckHtmlJoinClasses();
	afx_msg void OnBnClickedCheckHtmlJoinStyles();
	afx_msg void OnBnClickedCheckHtmlLiteralAttributes();
	afx_msg void OnBnClickedCheckHtmlLogicalEmphasis();
	afx_msg void OnBnClickedCheckHtmlLowerLiterals();
	afx_msg void OnBnClickedCheckHtmlNcr();
	afx_msg void OnBnClickedCheckHtmlNumericEntities();
	afx_msg void OnBnClickedCheckHtmlOutputHtml();
	afx_msg void OnBnClickedCheckHtmlOutputXhtml();
	afx_msg void OnBnClickedCheckHtmlOutputXml();
	afx_msg void OnBnClickedCheckHtmlPreserveEntities();
	afx_msg void OnBnClickedCheckHtmlQuoteAmpersand();
	afx_msg void OnBnClickedCheckHtmlQuoteMarks();
	afx_msg void OnBnClickedCheckHtmlQuoteNbsp();
	afx_msg void OnBnClickedCheckHtmlReplaceColor();
	afx_msg void OnBnClickedCheckHtmlUppercaseAttributes();
	afx_msg void OnBnClickedCheckHtmlUppercaseTags();
	afx_msg void OnBnClickedCheckHtmlWord2000();
};
