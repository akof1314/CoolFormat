#pragma once

//////////////////////////////////////////////////////////////////////////
// CKofBCGPListCtrl

class CKofBCGPListCtrl : public CBCGPListCtrl
{
	DECLARE_DYNAMIC(CKofBCGPListCtrl)
public:
	CKofBCGPListCtrl();
	virtual ~CKofBCGPListCtrl();

protected:
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};


