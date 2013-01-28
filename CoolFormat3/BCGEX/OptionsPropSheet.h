#pragma once

//////////////////////////////////////////////////////////////////////////
// COptionsPropSheet

class COptionsPropSheet : public CBCGPPropertySheet
{
public:
	COptionsPropSheet (CWnd* pWndParent, UINT nSelectedPage = 0);

protected:
	virtual void OnDrawPageHeader (CDC* pDC, int nPage, CRect rectHeader);

	CBCGPToolBarImages	m_Icons;
public:
	virtual BOOL OnInitDialog();
};

