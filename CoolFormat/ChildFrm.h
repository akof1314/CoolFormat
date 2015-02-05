// ChildFrm.h : interface of the CChildFrame class
#pragma once
#include "OutputViewBar.h"

class CChildFrame : public CBCGPMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:
	COutputViewBar m_wndOutput;
	void AddOutputMsg(LPCTSTR lpszMsg);
// Operations
public:

// Overrides
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	/**
	 * 激活框架时最大化
	 * @param int nCmdShow 
	 * @return void 
	 */
	virtual void ActivateFrame(int nCmdShow);

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	
	/**
	 * 子窗体创建时，最大化框架
	 * @param LPCREATESTRUCT lpCreateStruct 
	 * @return int 
	 */
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	/**
	 * MDI标签切换时，语言label的变化
	 * @param BOOL bActivate 
	 * @param CWnd * pActivateWnd 
	 * @param CWnd * pDeactivateWnd 
	 * @return void 
	 */
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
};
