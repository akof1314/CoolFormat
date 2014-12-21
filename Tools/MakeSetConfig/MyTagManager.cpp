// MyTagManager.cpp : 实现文件
//

#include "stdafx.h"
#include "MakeSetConfig.h"
#include "MyTagManager.h"

// CMyTagManager
LPCTSTR CMyTagManager::s_szXML_UTF8_Prefix = _T("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>");
LPCTSTR CMyTagManager::s_szSLFCR = _T("\n");
LPCTSTR CMyTagManager::s_szLFCR = _T("\r\n");
LPCTSTR CMyTagManager::s_szTab = _T("\t");
LPCTSTR CMyTagManager::s_szLFCRT = _T("\r\n\t");
BOOL CMyTagManager::s_bFormatTags = TRUE;

static LPCTSTR s_True = _T("TRUE");
static LPCTSTR s_False = _T("FALSE");

CMyTagManager::CMyTagManager()
{
}

CMyTagManager::~CMyTagManager()
{
}

void CMyTagManager::WriteItem(CString& strTag, const CString& strTagName, CString strAddTag, BOOL bEmpty /*= FALSE*/)
{
	if (strAddTag.IsEmpty() && !bEmpty)
	{
		return;
	}

	if (CMyTagManager::s_bFormatTags)
	{
		if (!strAddTag.IsEmpty())
		{
			strAddTag = s_szLFCR + strAddTag;
			strAddTag.Replace(s_szLFCR, s_szLFCRT);
			strAddTag += s_szLFCR;
		}

		if (!strTag.IsEmpty())
		{
			strTag += s_szLFCR;
		}
	}

	strTag += WriteString(strTagName, strAddTag, CString(), TRUE);
}

void CMyTagManager::WriteTag(CString& strTag, CString strAddTag)
{
	if (!strAddTag.IsEmpty())
	{
		if (CMyTagManager::s_bFormatTags && !strTag.IsEmpty())
		{
			strTag += s_szLFCR;
		}

		strTag += strAddTag;
	}
}

CString CMyTagManager::WriteString(const CString& strTag, const CString& value, const CString& valueDefault /*= CString()*/, BOOL bEmpty /*= FALSE*/)
{
	if (value == valueDefault)
	{
		return CString();
	}

	CString str;

	if (bEmpty || !value.IsEmpty())
	{
		str.Format(_T("<%s>%s</%s>"), strTag, value, strTag);
	}

	return str;
}

CString CMyTagManager::WriteSize(const CString& strTag, const CSize& value, const CSize& valueDefault)
{
	if (value == valueDefault)
	{
		return CString();
	}

	CString strValue;
	strValue.Format(_T("%d, %d"), value.cx, value.cy);

	return WriteString(strTag, strValue);
}

CString CMyTagManager::WriteBool(const CString& strTag, BOOL value, BOOL valueDefault)
{
	if (value == valueDefault)
	{
		return CString();
	}

	CString strValue;
	if (value)
	{
		strValue = s_True;
	}
	else
	{
		strValue = s_False;
	}

	return WriteString(strTag, strValue);
}

CString CMyTagManager::WriteInt(const CString& strTag, int value, int valueDefault)
{
	if (value == valueDefault)
	{
		return CString();
	}

	CString strValue;
	strValue.Format(_T("%d"), value);

	return WriteString(strTag, strValue);
}
