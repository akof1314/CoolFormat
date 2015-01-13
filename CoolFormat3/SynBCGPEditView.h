#pragma once
#include "SynBCGPEditCtrl.h"

//////////////////////////////////////////////////////////////////////////
// CSynBCGPEditView 视图

class CSynBCGPEditView : public CBCGPEditView
{
	DECLARE_DYNCREATE(CSynBCGPEditView)
protected:
	CSynBCGPEditView();           // 动态创建所使用的受保护的构造函数
	virtual ~CSynBCGPEditView();

public:	
	/**
	 * 获取编辑器控件指针
	 * @return CSynBCGPEditCtrl* 控件制作
	 */
	CSynBCGPEditCtrl* GetEditCtrl () const
	{
		return m_pEdit;
	}
		
	/**
	 * 加载设置字体
	 * @param void 
	 * @return void 
	 */
	void LoadFont(void);
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
	virtual void OnInitialUpdate();
	virtual CBCGPEditCtrl* CreateEdit();

	void GetUndoActions(CStringList& lstActions) const;
	
	/**
	 * 重画语言标签
	 * @return void 
	 */
	void ReSetLangLabel();

	void ReSetEncodingLabel();

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	CSynBCGPEditCtrl *m_pEdit;
	CFont m_Font;
	
	/**
	 * 设置默认字体
	 * @return void 
	 */
	void ResetDefaultFont();

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	afx_msg void OnEditGotoLine();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateCursorPos(CCmdUI *pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnFastformat();

	afx_msg void OnEditHideselection();
	afx_msg void OnUpdateEditHideselection(CCmdUI *pCmdUI);
	afx_msg void OnEditStophidingcurrent();
	afx_msg void OnUpdateEditStophidingcurrent(CCmdUI *pCmdUI);
	afx_msg void OnEditToggleoutlining();
	afx_msg void OnUpdateEditToggleoutlining(CCmdUI *pCmdUI);
	afx_msg void OnEditTogglealloutlining();
	afx_msg void OnUpdateEditTogglealloutlining(CCmdUI *pCmdUI);
	afx_msg void OnEditCollapsetodefinitions();
	afx_msg void OnUpdateEditCollapsetodefinitions(CCmdUI *pCmdUI);
	afx_msg void OnEditStopoutlining();
	afx_msg void OnUpdateEditStopoutlining(CCmdUI *pCmdUI);
	afx_msg void OnLang();
	afx_msg void OnAActionscript();
	afx_msg void OnAAda();
	afx_msg void OnAAsm();
	afx_msg void OnAAsp();
	afx_msg void OnAAutohotkey();
	afx_msg void OnAAutoit();
	afx_msg void OnBatch();
	afx_msg void OnCCobol();
	afx_msg void OnCC();
	afx_msg void OnCC32893();
	afx_msg void OnCCss();
	afx_msg void OnD();
	afx_msg void OnFortran();
	afx_msg void OnHHaskell();
	afx_msg void OnHHtml();
	afx_msg void OnIni();
	afx_msg void OnJJava();
	afx_msg void OnJJavascript();
	afx_msg void OnJJson();
	afx_msg void OnJJsp();
	afx_msg void OnLLisp();
	afx_msg void OnLLua();
	afx_msg void OnNormaltext();
	afx_msg void OnObjective();
	afx_msg void OnPPascal();
	afx_msg void OnPPerl();
	afx_msg void OnPPhp();
	afx_msg void OnPPython();
	afx_msg void OnRuby();
	afx_msg void OnSql();
	afx_msg void OnVVb();
	afx_msg void OnVVerilog();
	afx_msg void OnVVhdl();
	afx_msg void OnXml();

	afx_msg void OnFilePrintPreview();
	afx_msg void OnHtmltoblog();
	afx_msg void OnIndentAdd();
	afx_msg void OnIndentMin();
	afx_msg void OnCommentDo();
	afx_msg void OnCommentNot();
	afx_msg void OnSelformat();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEncodingAnsi();
	afx_msg void OnEncodingUtf8();
	afx_msg void OnEncodingUtf8nb();
	afx_msg void OnEncodingUtf16le();
	afx_msg void OnEncodingUtf16be();
	afx_msg void OnEncodingBig5();
	afx_msg void OnEncodingGb2312();
	afx_msg void OnEncodingShiftjis();
	afx_msg void OnEncodingEuckr();
};


