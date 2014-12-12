#pragma once
#include "SetPageBase.h"

//////////////////////////////////////////////////////////////////////////
// CSetPageSql ¶Ô»°¿ò

class CSetPageSql : public CSetPageBase
{
public:
	CSetPageSql(LPCTSTR lpszTitle, CString& strTidy);
	virtual ~CSetPageSql();

protected:
	void InitPropList();
};
