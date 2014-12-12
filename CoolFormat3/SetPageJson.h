#pragma once
#include "SetPageBase.h"

//////////////////////////////////////////////////////////////////////////
// CSetPageJson ¶Ô»°¿ò

class CSetPageJson : public CSetPageBase
{
public:
	CSetPageJson(LPCTSTR lpszTitle, CString& strTidy);
	virtual ~CSetPageJson();

protected:
	void InitPropList();
};
