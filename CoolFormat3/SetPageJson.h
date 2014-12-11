#pragma once
#include "SetPageBase.h"

//////////////////////////////////////////////////////////////////////////
// CSetPageJson ¶Ô»°¿ò

class CSetPageJson : public CSetPageBase
{
public:
	CSetPageJson();
	virtual ~CSetPageJson();

protected:
	void InitPropList();
	void InitTidyConfig();
	void EndTidyConfig();
	void SetTidyProp(LPCTSTR lpszParam, int nNumValue);
};
