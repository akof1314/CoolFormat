// MyTagManager.cpp : 实现文件

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

struct XEntity
{
	LPCTSTR szCode;
	LPCTSTR szSymbol;
};

static const XEntity s_EntityText[] =
{
	{ _T("&amp;"), _T("&") },
	{ _T("&lt;"), _T("<") },
	{ _T("&gt;"), _T(">") },
	{ _T("&quot;"), _T("\"") },
	{ _T("&apos;"), _T("\'") },
	//{ _T("&circ;"), _T("^") },
	//{ _T("&tilde;"), _T("~") },
	//{ _T("&#09;"), _T("\t") },
	//{ _T("&#0A;"), _T("\r") },
	//{ _T("&#0D;"), _T("\n") },
	{ NULL, NULL }
};

static const XEntity s_EntityCode[] =
{
	{ _T("\\n"), _T("\n") },
	{ _T("\\t"), _T("\t") },
	{ _T("\\r"), _T("\r") },
	{ NULL, NULL }
};

static CString Entity_Forward(const CString& value, const XEntity* entity)
{
	CString str(value);

	while (entity->szCode != NULL)
	{
		if (str.Find(entity->szSymbol) != -1)
		{
			str.Replace(entity->szSymbol, entity->szCode);
		}

		entity++;
	}

	return str;
}

static void Entity_Backward(CString& value, const XEntity* entity)
{
	while (entity->szCode != NULL)
	{
		if (value.Find(entity->szCode) != -1)
		{
			value.Replace(entity->szCode, entity->szSymbol);
		}

		entity++;
	}
}

CMyTagManager::CMyTagManager(LPCTSTR lpszBuffer /*= NULL*/)
	:CTagManager(lpszBuffer)
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

CString CMyTagManager::WriteEntityString(const CString& strTag, const CString& value, const CString& valueDefault /*= CString()*/, BOOL bEmpty /*= FALSE*/)
{
	return WriteString(strTag, Entity_ToTag(value), Entity_ToTag(valueDefault), bEmpty);
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

CString CMyTagManager::Entity_ToTag(const CString& value)
{
	return Entity_Forward(value, s_EntityText);
}

void CMyTagManager::Entity_FromTag(CString& value)
{
	Entity_Backward(value, s_EntityText);
}

BOOL CMyTagManager::ReadString(const CString& strValue, CString& value)
{
	BOOL bRes = FALSE;
	CString strItem;

	if (ExcludeTag(strValue, strItem))
	{
		value = strItem;
		bRes = TRUE;
	}

	return bRes;
}

BOOL CMyTagManager::ReadEntityString(const CString& strValue, CString& value)
{
	if (!ReadString(strValue, value))
	{
		return FALSE;
	}

	Entity_FromTag(value);
	return TRUE;
}
