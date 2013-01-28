// CoolFormat3Doc.h : interface of the CCoolFormat3Doc class
#pragma once

class CCoolFormat3Doc : public CDocument
{
protected: // create from serialization only
	CCoolFormat3Doc();
	DECLARE_DYNCREATE(CCoolFormat3Doc)

// Attributes
public:
	void CheckTitle();
// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CCoolFormat3Doc();
	virtual BOOL DoSave(LPCTSTR lpszPathName, BOOL bReplace = TRUE);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL m_bTitleMark;
	DECLARE_MESSAGE_MAP()

public:
	virtual void SetTitle(LPCTSTR lpszTitle);
	virtual BOOL SaveModified();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
};


