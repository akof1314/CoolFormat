#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CHtmlView。"
#endif 

//////////////////////////////////////////////////////////////////////////
// CSynHtmlView Html 视图

class CSynHtmlView : public CHtmlView
{
	DECLARE_DYNCREATE(CSynHtmlView)
protected:
	CSynHtmlView();           // 动态创建所使用的受保护的构造函数
	virtual ~CSynHtmlView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CString m_strHtmlSrc;
	CString m_strHtmlCode;
	LPDISPATCH glpDisp;
	void MakeCodeToHtml(const CString &strHtml, const CString &strLang, int iLineCount);
	BOOL CopyHtmlToClip(const CString &strHtml, const CString &strCode);
	BOOL CopyHtmlSrcToClip(const CString &strHtml);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	BOOL ShowCodeToHtml(const CString &strHtml, const CString &strCode, const CString &strLang, int iLineCount, BOOL bAlreadyShow = FALSE);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEditSelectAll();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnFileSave();
	afx_msg void OnCopyHtmlsrc();
	afx_msg void OnFileSaveAs();
	afx_msg void OnEditCopy();
	virtual void DocumentComplete(LPDISPATCH pDisp, VARIANT* URL);
	virtual void NavigateComplete2(LPDISPATCH pDisp, VARIANT* URL);
};


