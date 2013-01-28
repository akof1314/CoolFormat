#pragma once
#ifdef _DEBUG
#pragma comment(lib, "libtidydb.lib")
#else
#pragma comment(lib, "libtidy.lib")
#endif // _DEBUG
#include "tidy.h"

class HTidyInterface
{
public:
	HTidyInterface(UINT nLangID = SYN_HTML);
	~HTidyInterface(void);

	bool formatSource(const char* textIn, CString &strTidy, CString &strMsg);

private:
	UINT m_onlyHtmlXml;
	void SetTidyConfig(TidyDoc tdoc);
	void SetTidyControl(TidyDoc tdoc, LPCTSTR lpszTidy, int nPos, int nSize);
	LPCSTR GetEncodeByIndex(int nIndex);
	void InitTidyDefault(TidyDoc tdoc);
};
