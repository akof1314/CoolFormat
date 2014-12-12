// MyBCGPProp.cpp : 实现文件

#include "stdafx.h"
#include "MyBCGPProp.h"

//////////////////////////////////////////////////////////////////////////
// CMyBCGPProp

#define PROP_HAS_LIST	0x0001
#define PROP_HAS_BUTTON	0x0002
#define PROP_HAS_SPIN	0x0004

IMPLEMENT_DYNAMIC(CMyBCGPProp, CBCGPProp)

CMyBCGPProp::CMyBCGPProp(const CString& strGroupName, DWORD_PTR dwData /*= 0*/, BOOL bIsValueList /*= FALSE*/)
	:CBCGPProp(strGroupName, dwData, bIsValueList),
	m_pBuddyProp(NULL)
{
}

CMyBCGPProp::CMyBCGPProp(const CString& strName, const _variant_t& varValue, LPCTSTR lpszDescr /*= NULL*/, DWORD_PTR dwData /*= 0*/, LPCTSTR lpszEditMask /*= NULL*/, LPCTSTR lpszEditTemplate /*= NULL*/, LPCTSTR lpszValidChars /*= NULL*/)
	:CBCGPProp(strName, varValue, lpszDescr, dwData, lpszEditMask, lpszEditTemplate, lpszValidChars),
	m_pBuddyProp(NULL)
{
}

CMyBCGPProp::~CMyBCGPProp()
{
}

// CMyBCGPProp 消息处理程序

BOOL CMyBCGPProp::AddComboOption(LPCTSTR lpszOption, LPCTSTR lpszShort, LPCTSTR lpszPreview, BOOL bInsertUnique /*= TRUE*/)
{
	AllowEdit(FALSE);
	if (CBCGPProp::AddOption(lpszOption, bInsertUnique))
	{
		ASSERT(m_lstShortOptions.Find(lpszOption) == NULL);

		m_lstShortOptions.AddTail(lpszShort);
		m_lstPreviewOptions.AddTail(lpszPreview);
		return TRUE;
	}
	return FALSE;
}

BOOL CMyBCGPProp::SetNumberSpin(int nMin, int nMax, LPCTSTR lpszShort, LPCTSTR lpszPreview, CMyBCGPProp* pBuddyToProp /*= NULL*/)
{
	EnableSpinControl(TRUE, nMin, nMax);
	m_lstShortOptions.RemoveAll();
	m_lstPreviewOptions.RemoveAll();
	m_lstShortOptions.AddTail(lpszShort);
	m_lstPreviewOptions.AddTail(lpszPreview);
	if (pBuddyToProp)
	{
		pBuddyToProp->m_pBuddyProp = this;
	}
	return TRUE;
}

BOOL CMyBCGPProp::SetEditText(LPCTSTR lpszShort, LPCTSTR lpszPreview)
{
	AllowEdit(TRUE);
	m_lstShortOptions.RemoveAll();
	m_lstPreviewOptions.RemoveAll();
	m_lstShortOptions.AddTail(lpszShort);
	m_lstPreviewOptions.AddTail(lpszPreview);
	return TRUE;
}

LPCTSTR CMyBCGPProp::GetSelectedPreviewOption() const
{
	if (m_lstPreviewOptions.GetCount() == 0)
	{
		return NULL;
	}

	if (IsList())
	{
		POSITION pos = m_lstPreviewOptions.FindIndex(GetSelectedOption());
		if (pos == NULL)
		{
			ASSERT(FALSE);
			return NULL;
		}

		return m_lstPreviewOptions.GetAt(pos);
	}
	return m_lstPreviewOptions.GetHead();
}

BOOL CMyBCGPProp::TextToVar(const CString& strText)
{
	BOOL bRet = CBCGPProp::TextToVar(strText);
	if (bRet && (m_dwFlags & PROP_HAS_SPIN) && m_varValue.vt == VT_INT)
	{
		if (m_varValue.intVal < m_nMinValue)
		{
			m_varValue.intVal = m_nMinValue;
		}
		if (m_varValue.intVal > m_nMaxValue)
		{
			m_varValue.intVal = m_nMaxValue;
		}
	}
	return bRet;
}

CBCGPProp* CMyBCGPProp::FindSubItemByShort(LPCTSTR lpszShort) const
{
	for (POSITION pos = m_lstSubItems.GetHeadPosition(); pos != NULL;)
	{
		CBCGPProp* pProp = m_lstSubItems.GetNext(pos);
		ASSERT_VALID(pProp);

		CMyBCGPProp* pMyProp = DYNAMIC_DOWNCAST(CMyBCGPProp, pProp);
		if (pMyProp == NULL)
		{
			continue;
		}

		if (pMyProp->IsExistShort(lpszShort))
		{
			return pMyProp;
		}

		pProp = pMyProp->FindSubItemByShort(lpszShort);

		if (pProp != NULL)
		{
			return pProp;
		}
	}

	return NULL;
}

BOOL CMyBCGPProp::IsExistShort(LPCTSTR lpszShort)
{
	return m_lstShortOptions.Find(lpszShort) != NULL;
}

void CMyBCGPProp::SetValueByShort(LPCTSTR lpszShort, const _variant_t& varValue)
{
	POSITION pos = m_lstShortOptions.Find(lpszShort);
	if (pos == NULL)
	{
		return;
	}

	if (IsList())
	{
		int nIndex = 0;
		for (POSITION pos = m_lstShortOptions.GetHeadPosition(); pos != NULL; nIndex++)
		{
			if (lpszShort == m_lstShortOptions.GetNext(pos))
			{
				break;
			}
		}

		SetValue(GetOption(nIndex));

		if (m_pBuddyProp)
		{
			m_pBuddyProp->SetValue(varValue);
		}
	}
	else
	{
		SetValue(varValue);
	}
}

void CMyBCGPProp::GetSubResultShorts(CString& strValue)
{
	for (POSITION pos = m_lstSubItems.GetHeadPosition(); pos != NULL;)
	{
		CBCGPProp* pProp = m_lstSubItems.GetNext(pos);
		ASSERT_VALID(pProp);

		CMyBCGPProp* pMyProp = DYNAMIC_DOWNCAST(CMyBCGPProp, pProp);
		if (pMyProp == NULL)
		{
			continue;
		}

		pMyProp->GetResultShort(strValue);
		pMyProp->GetSubResultShorts(strValue);
	}
}

void CMyBCGPProp::GetResultShort(CString& strValue)
{
	if (m_lstShortOptions.GetCount() == 0)
	{
		return;
	}

	CString strShort;
	if (IsList())
	{
		POSITION pos = m_lstShortOptions.FindIndex(GetSelectedOption());
		if (pos == NULL)
		{
			ASSERT(FALSE);
			return;
		}

		strShort = m_lstShortOptions.GetAt(pos);
	}
	else
	{
		strShort = m_lstShortOptions.GetHead();

	}

	if (!strShort.IsEmpty())
	{
		strValue += _T("-") + strShort + (IsList() ? _T("") : FormatProperty());
	}

	if (m_pBuddyProp)
	{
		strValue += m_pBuddyProp->FormatProperty();
	}
}

BOOL CMyBCGPProp::IsList() const
{
	return m_dwFlags & PROP_HAS_LIST;
}

void CMyBCGPProp::GetSubShortOptions(CStringList& lstValue)
{
	for (POSITION pos = m_lstSubItems.GetHeadPosition(); pos != NULL;)
	{
		CBCGPProp* pProp = m_lstSubItems.GetNext(pos);
		ASSERT_VALID(pProp);

		CMyBCGPProp* pMyProp = DYNAMIC_DOWNCAST(CMyBCGPProp, pProp);
		if (pMyProp == NULL)
		{
			continue;
		}

		pMyProp->GetShortOptions(lstValue);
		pMyProp->GetSubShortOptions(lstValue);
	}
}

void CMyBCGPProp::GetShortOptions(CStringList& lstValue)
{
	lstValue.AddTail(&m_lstShortOptions);
}


