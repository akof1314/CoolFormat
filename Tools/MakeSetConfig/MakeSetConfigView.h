
// MakeSetConfigView.h : interface of the CMakeSetConfigView class
//

#pragma once


class CMakeSetConfigView : public CEditView
{
protected: // create from serialization only
	CMakeSetConfigView();
	DECLARE_DYNCREATE(CMakeSetConfigView)

// Attributes
public:
	CMakeSetConfigDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMakeSetConfigView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MakeSetConfigView.cpp
inline CMakeSetConfigDoc* CMakeSetConfigView::GetDocument() const
   { return reinterpret_cast<CMakeSetConfigDoc*>(m_pDocument); }
#endif

