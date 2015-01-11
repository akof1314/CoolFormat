// MyBCGPProp.cpp : 实现文件

#include "stdafx.h"
#include "MyBCGPProp.h"
#include "CoolFormat3.h"
#include "MulTextEditDlg.h"

//////////////////////////////////////////////////////////////////////////
// CMyBCGPProp

#define PROP_HAS_LIST	0x0001
#define PROP_HAS_BUTTON	0x0002
#define PROP_HAS_SPIN	0x0004

#define STR_SHORT_PREFIX _T("-")
#define STR_SHORT_TEXT_FALG _T("#")

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
	m_dwFlags |= PROP_HAS_BUTTON;
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
	if (bRet)
	{
		if ((m_dwFlags & PROP_HAS_SPIN) && m_varValue.vt == VT_INT)
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
		else if (IsText())
		{
			if (strText.Find('-') != -1)
			{
				CString strNewText(strText);
				strNewText.Replace('-', '_');

				m_varValue = (LPCTSTR)strNewText;
			}
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
		CString strFormatProperty = FormatProperty();
		if (IsText())
		{
			if (!strFormatProperty.IsEmpty())
			{
				strValue += STR_SHORT_PREFIX + strShort + STR_SHORT_TEXT_FALG + strFormatProperty;
			}
		} 
		else
		{
			strValue += STR_SHORT_PREFIX + strShort
				+ (IsList() ? _T("") : FormatProperty());
		}
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

BOOL CMyBCGPProp::IsText() const
{
	return (m_varValue.vt == VT_BSTR) && !IsList();
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

void CMyBCGPProp::OnClickButton(CPoint point)
{
	CBCGPProp::OnClickButton(point);
	if (IsText())
	{
		ASSERT_VALID(this);
		ASSERT_VALID(m_pWndList);
		ASSERT_VALID(m_pWndInPlace);
		ASSERT(::IsWindow(m_pWndInPlace->GetSafeHwnd()));

		m_bButtonIsDown = TRUE;
		m_bButtonIsHighlighted = FALSE;
		Redraw();

		CString strPath = (LPCTSTR)(_bstr_t)m_varValue;
		BOOL bUpdate = FALSE;

		CMulTextEditDlg dlg;
		dlg.SetText(strPath);
		if (dlg.DoModal() == IDOK)
		{
			bUpdate = TRUE;
			strPath = dlg.GetText();
		}

		if (bUpdate)
		{
			if (strPath.Find('-') != -1)
			{
				strPath.Replace('-', '_');
			}

			if (m_pWndInPlace != NULL)
			{
				m_pWndInPlace->SetWindowText(strPath);
			}

			m_varValue = (LPCTSTR)strPath;
		}

		m_bButtonIsDown = FALSE;
		Redraw();

		if (m_pWndInPlace != NULL)
		{
			m_pWndInPlace->SetFocus();
		}
		else
		{
			m_pWndList->SetFocus();
		}
	}
}
