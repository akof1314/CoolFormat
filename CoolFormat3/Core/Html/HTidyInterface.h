#pragma once
#ifdef _DEBUG
#pragma comment(lib, "tidylibd.lib")
#else
#pragma comment(lib, "tidylib.lib")
#endif // _DEBUG
#include "tidy.h"

class HTidyInterface
{
public:
	HTidyInterface();
	~HTidyInterface(void);

	bool formatSource(const char* textIn, const CString &strTidy, CString &strTextOut, CString &strMsg);

private:
	void SetTidyConfig(TidyDoc tdoc, const CString &strTidy);
	void SetTidyControl(TidyDoc tdoc, LPCTSTR lpszTidy, int nPos, int nSize);
	LPCSTR GetEncodeByIndex(int nIndex);
	void InitTidyDefault(TidyDoc tdoc);
};
