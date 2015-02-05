// CoolFormat3View.h : interface of the CCoolFormat3View class
#include "SynBCGPEditView.h"
#include "SynHtmlView.h"
#pragma once

class CCoolFormat3View : public CBCGPTabView
{
protected: // create from serialization only
	CCoolFormat3View();
	DECLARE_DYNCREATE(CCoolFormat3View)

// Attributes
public:
	CCoolFormat3Doc* GetDocument() const;
// Operations
public:
	
	/**
	 * 获取编辑器视图的指针
	 * @return CSynBCGPEditView * 获取不成功，返回NULL
	 */
	CSynBCGPEditView *GetSynView();
	void SaveEditFile(CString lpszPathName);
// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCoolFormat3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HICON m_DocIcon;
	HACCEL m_hAccel;
// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in CoolFormat3View.cpp
inline CCoolFormat3Doc* CCoolFormat3View::GetDocument() const
   { return reinterpret_cast<CCoolFormat3Doc*>(m_pDocument); }
#endif

