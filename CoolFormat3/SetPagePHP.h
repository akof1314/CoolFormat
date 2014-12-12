#pragma once
#include "SetPageBase.h"

//////////////////////////////////////////////////////////////////////////
// CSetPagePHP ¶Ô»°¿ò

class CSetPagePHP : public CSetPageBase
{
public:
	CSetPagePHP(LPCTSTR lpszTitle, CString& strTidy);
	virtual ~CSetPagePHP();

protected:
	void InitPropList();
};
