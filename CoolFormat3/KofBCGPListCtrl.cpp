// KofBCGPListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "KofBCGPListCtrl.h"


// CKofBCGPListCtrl

IMPLEMENT_DYNAMIC(CKofBCGPListCtrl, CBCGPListCtrl)

CKofBCGPListCtrl::CKofBCGPListCtrl()
{

}

CKofBCGPListCtrl::~CKofBCGPListCtrl()
{
}


BEGIN_MESSAGE_MAP(CKofBCGPListCtrl, CBCGPListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)
END_MESSAGE_MAP()

void CKofBCGPListCtrl::OnColumnClick( NMHDR* pNMHDR, LRESULT* pResult )
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	ASSERT (pNMListView != NULL);
	*pResult = 0;
}


// CKofBCGPListCtrl 消息处理程序


