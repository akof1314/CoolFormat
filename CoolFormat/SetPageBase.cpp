// SetPageBase.cpp : 实现文件

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageBase.h"
#include "BCGPTagManager.h"

#define STR_SHORT_TEXT_FALG _T("#")

//////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////
// CSetPageBase 对话框

IMPLEMENT_DYNAMIC(CSetPageBase, CBCGPPropertyPage)

CSetPageBase::CSetPageBase(LPCTSTR lpszTitle, LPCTSTR lpszConfigName, CString& strTidy)
	: CBCGPPropertyPage(CSetPageBase::IDD)
{
	m_psp.dwFlags |= PSP_USETITLE;
	m_psp.pszTitle = lpszTitle;
	m_strConfigName = lpszConfigName;
	m_strTidy = &strTidy;
}

CSetPageBase::~CSetPageBase()
{
}

void CSetPageBase::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSetPageBase, CBCGPPropertyPage)
END_MESSAGE_MAP()

// CSetPageBase 消息处理程序

BOOL CSetPageBase::OnInitDialog()
{
	CBCGPPropertyPage::OnInitDialog();

	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STR_VIEWFORMATTER);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_VIEWFORMATTER, strTemp);
	bNameVaild = strTemp.LoadString(IDS_STR_OPTIONFORMATTER);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_OPTIONFORMATTER, strTemp);
	GetDlgItem(IDC_EDIT_VIEWFORMATTER)->SetFont(&g_GlobalUtils.m_fontWidth);

	CRect rectPropList;
	GetDlgItem(IDC_PROPLIST_LOCATION)->GetClientRect(&rectPropList);
	GetDlgItem(IDC_PROPLIST_LOCATION)->MapWindowPoints(this, &rectPropList);
	GetDlgItem(IDC_PROPLIST_LOCATION)->ShowWindow(SW_HIDE);

	m_wndPropList.Create(WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectPropList, this, (UINT)-1);
	m_wndPropList.SetPreviewWnd(GetDlgItem(IDC_EDIT_VIEWFORMATTER));

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDesciptionArea(FALSE);
	m_wndPropList.SetVSDotNetLook(TRUE);
	m_wndPropList.MarkModifiedProperties(TRUE);
	m_wndPropList.SetNameAlign(DT_LEFT);
	m_wndPropList.SetAlphabeticMode(FALSE);
	m_wndPropList.SetShowDragContext(FALSE);
	m_wndPropList.EnableToolBar(TRUE);
	m_wndPropList.EnableSearchBox(TRUE);

	InitPropList();
	InitTidyConfig();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CSetPageBase::InitPropList()
{
	CBCGPTagManager tm;
	CString strRes(_T("IDR_SETCONFIG_XML_") + m_strConfigName.MakeUpper());
	if (!tm.LoadFromResource(strRes, _T("XML")))
	{
		return;
	}

	CString strStyle;
	if (!tm.ExcludeTag(_T("SETCONFIG"), strStyle))
	{
		return;
	}
	tm.SetBuffer(strStyle);

	int nVersion;
	tm.ReadInt(_T("VERSION"), nVersion);
	if (nVersion != 1)
	{
		return;
	}

	CString strPropertys;
	if (tm.ExcludeTag(_T("PROPERTYS"), strPropertys))
	{
		CBCGPTagManager tmPropertys(strPropertys);

		CMyBCGPProp* pPropGroup = NULL;
		CString strProperty;
		while (tmPropertys.ExcludeTag(_T("PROPERTY"), strProperty))
		{
			CBCGPTagManager tmProperty(strProperty);
			CString strName = _T("NO NAME");
			tmProperty.ReadString(_T("NAME"), strName);

			BOOL bGroup = FALSE;
			if (tmProperty.ReadBool(_T("GROUP"), bGroup) && bGroup)
			{
				if (pPropGroup)
				{
					m_wndPropList.AddProperty(pPropGroup, FALSE, FALSE);
					pPropGroup = NULL;
				}

				pPropGroup = new CMyBCGPProp(strName);
			} 
			else if (pPropGroup)
			{
				CString strType = _T("Combo");
				tmProperty.ReadString(_T("TYPE"), strType);

				if (strType.CompareNoCase(_T("Combo")) == 0)
				{
					CString strValue;
					tmProperty.ReadString(_T("VALUE"), strValue);

					CMyBCGPProp* pProp = new CMyBCGPProp(strName, (_variant_t)strValue);
					
					CString strItem;
					while (tmProperty.ExcludeTag(_T("ITEM"), strItem))
					{
						CBCGPTagManager tmItem(strItem);
						tmItem.ReadString(_T("VALUE"), strValue);

						CString strShort, strPreview;
						tmItem.ReadString(_T("SHORT"), strShort);
						tmItem.ReadString(_T("PREVIEW"), strPreview);
						Entity_Backward(strPreview, s_EntityText);
						EntityToSymbol(strPreview);

						pProp->AddComboOption(strValue, strShort, strPreview);
					}

					pPropGroup->AddSubItem(pProp);
				} 
				else if (strType.CompareNoCase(_T("Number")) == 0)
				{
					int nValue;
					tmProperty.ReadInt(_T("VALUE"), nValue);

					CMyBCGPProp* pProp = new CMyBCGPProp(strName, (_variant_t)nValue);

					CSize range;
					tmProperty.ReadSize(_T("RANGE"), range);

					BOOL bBuddy = FALSE;
					tmProperty.ReadBool(_T("BUDDY"), bBuddy);
					CMyBCGPProp* pPropBuddy = NULL;
					if (bBuddy)
					{
						pPropBuddy = DYNAMIC_DOWNCAST(CMyBCGPProp, pPropGroup->GetSubItem(pPropGroup->GetSubItemsCount() - 1));
					}

					CString strShort, strPreview;
					tmProperty.ReadString(_T("SHORT"), strShort);
					tmProperty.ReadString(_T("PREVIEW"), strPreview);
					Entity_Backward(strPreview, s_EntityText);
					EntityToSymbol(strPreview);

					pProp->SetNumberSpin(range.cx, range.cy, strShort, strPreview, pPropBuddy);
					pPropGroup->AddSubItem(pProp);
				}
				else if (strType.CompareNoCase(_T("Text")) == 0)
				{
					CString strValue;
					tmProperty.ReadString(_T("VALUE"), strValue);

					CMyBCGPProp* pProp = new CMyBCGPProp(strName, (_variant_t)strValue);

					CString strShort, strPreview;
					tmProperty.ReadString(_T("SHORT"), strShort);
					tmProperty.ReadString(_T("PREVIEW"), strPreview);
					Entity_Backward(strPreview, s_EntityText);
					EntityToSymbol(strPreview);

					pProp->SetEditText(strShort, strPreview);
					pPropGroup->AddSubItem(pProp);
				}
			}
		}

		if (pPropGroup)
		{
			m_wndPropList.AddProperty(pPropGroup, FALSE, FALSE);
			pPropGroup = NULL;
		}
	}
}

void CSetPageBase::InitTidyConfig()
{
	ASSERT(m_wndPropList.ValidateShort());

	SetTidyConfig(*m_strTidy);
	m_wndPropList.CommitModifiedValues(FALSE);
}

void CSetPageBase::EndTidyConfig()
{
	CString strTidy;
	GetTidyConfig(strTidy);
	*m_strTidy = strTidy;
}

void CSetPageBase::SetTidyConfig(LPCTSTR lpszTidy)
{
	int lenTidy = _tcsclen(lpszTidy);
	if (lenTidy <= 0 || lpszTidy[0] != '-')
	{
		return;
	}

	int nOption = -1;
	for (int i = 0; i < lenTidy; ++i)
	{
		if (lpszTidy[i] == '-')
		{
			if (-1 != nOption)
			{
				SetTidyControl(lpszTidy, nOption, i - nOption);
			}
			nOption = i;
		}
	}
	SetTidyControl(lpszTidy, nOption, lenTidy - nOption);
}

void CSetPageBase::SetTidyControl(LPCTSTR lpszTidy, int nPos, int nSize)
{
	if (lpszTidy[nPos] != '-' || nSize < 2)
	{
		return;
	}

	CString strTextParam(lpszTidy + nPos + 1, nSize - 1);
	int nPosFlag = strTextParam.Find(STR_SHORT_TEXT_FALG);
	if (nPosFlag > 0)
	{
		CString strBstrValue(strTextParam.Mid(nPosFlag + 1));
		strTextParam = strTextParam.Left(nPosFlag);
		SetTidyProp(strTextParam, (LPCTSTR)strBstrValue);
	}
	else
	{
		int nNumValue = nSize;
		for (int i = nPos + 1; i < nPos + nSize; ++i)
		{
			if (!_istalpha(lpszTidy[i]))
			{
				nNumValue = i - nPos;
				break;
			}
		}
		CString strParam(lpszTidy + nPos + 1, nNumValue - 1);
		if (nNumValue != nSize)
		{
			CString strNum(lpszTidy + nPos + nNumValue, nSize - nNumValue);
			nNumValue = _ttoi(strNum);
		}
		else
		{
			nNumValue = INT_MIN;
		}

		if (!SetTidyProp(strParam, nNumValue))
		{
			strParam.AppendFormat(_T("%d"), nNumValue);
			SetTidyProp(strParam, nNumValue);
		}
	}
}

BOOL CSetPageBase::SetTidyProp(LPCTSTR lpszParam, const _variant_t& varValue)
{
	CBCGPProp* pProp = m_wndPropList.FindItemByShort(lpszParam);
	if (pProp)
	{
		CMyBCGPProp* pMyProp = DYNAMIC_DOWNCAST(CMyBCGPProp, pProp);
		if (pMyProp)
		{
			pMyProp->SetValueByShort(lpszParam, varValue);
		}
	}
	return pProp != NULL;
}

void CSetPageBase::GetTidyConfig(CString &strTidyValue)
{
	m_wndPropList.GetResultShorts(strTidyValue);
}

void CSetPageBase::EntityToSymbol(CString& value)
{
	value.Replace(_T("\\t"), _T("\t"));
	value.Replace(_T("\\n"), _T("\n"));
	value.Replace(_T("\\r"), _T("\r"));
}

void CSetPageBase::OnOK()
{
	EndTidyConfig();
	CBCGPPropertyPage::OnOK();
}
