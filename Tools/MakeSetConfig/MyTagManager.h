#pragma once
#include "afxtagmanager.h"

// CMyTagManager ÃüÁîÄ¿±ê

class CMyTagManager : public CTagManager
{
public:
	CMyTagManager();
	virtual ~CMyTagManager();

	static void WriteTag(CString& strTag, CString strAddTag);
	static void WriteItem(CString& strTag, const CString& strTagName, CString strAddTag, BOOL bEmpty = FALSE);

	static CString WriteString(const CString& strTag, const CString& value, const CString& valueDefault = CString(), BOOL bEmpty = FALSE);
	static CString WriteSize(const CString& strTag, const CSize& value, const CSize& valueDefault);
	static CString WriteBool(const CString& strTag, BOOL value, BOOL valueDefault);
	static CString WriteInt(const CString& strTag, int value, int valueDefault);

	static LPCTSTR	s_szXML_UTF8_Prefix;
	static LPCTSTR	s_szSLFCR;
	static LPCTSTR	s_szLFCR;
	static LPCTSTR	s_szTab;
	static LPCTSTR	s_szLFCRT;
	static BOOL		s_bFormatTags;
};


