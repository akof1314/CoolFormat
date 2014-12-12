#pragma once
#include "SetPageBase.h"

//////////////////////////////////////////////////////////////////////////
// CSetPageJS ¶Ô»°¿ò

class CSetPageJS : public CSetPageBase
{
public:
	CSetPageJS(LPCTSTR lpszTitle, CString& strTidy);
	virtual ~CSetPageJS();

protected:
	void InitPropList();
};
