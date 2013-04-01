#pragma once
#include "bcgpdlgimpl.h"

class CMyBCGPDlgImpl :
	protected CBCGPDlgImpl
{
	friend class CMyBCGPFindReplaceDialog;	

	CMyBCGPDlgImpl(CWnd& dlg);

};
