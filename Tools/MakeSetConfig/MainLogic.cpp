#include "stdafx.h"
#include "MakeSetConfig.h"
#include "MainFrm.h"
#include "MainLogic.h"
#include "afxtagmanager.h"

#define STR_XML_NAME_BEGIN _T("IDR_SETCONFIG_XML_")

CMainLogic::CMainLogic()
{
}


CMainLogic::~CMainLogic()
{
}

void CMainLogic::LoadRCFile(LPCTSTR lpszFileName)
{
	CFile listFile;
	CFileException fileException;
	if (!listFile.Open(lpszFileName, CFile::modeRead, &fileException))
	{
		TCHAR szErrorMsg[1024];
		fileException.GetErrorMessage(szErrorMsg, 1024, NULL);
		AfxMessageBox(szErrorMsg, MB_OK | MB_ICONERROR);
		return;
	}
	try
	{
		CWaitCursor wait;
		const DWORD dwFileSize = (const DWORD)listFile.GetLength();
		if (dwFileSize == 0)
		{
			return;
		}

		LPSTR pszFileBuffer = new char[dwFileSize + 2];
		ZeroMemory(pszFileBuffer, dwFileSize + 2);

#if _MSC_VER >= 1300
		listFile.Read(pszFileBuffer, dwFileSize);
#else
		listFile.ReadHuge(pszFileBuffer, dwFileSize);
#endif
		listFile.Close();

		CString strText(pszFileBuffer);
		delete[] pszFileBuffer;

		ParseRCText(lpszFileName, strText);
	}
	catch (CException* e)
	{
		TCHAR szErrorMsg[1024];
		e->GetErrorMessage(szErrorMsg, 1024, NULL);
		e->Delete();
		AfxMessageBox(szErrorMsg, MB_OK | MB_ICONERROR);
	}
}

BOOL CMainLogic::ParseRCText(LPCTSTR lpszFileName, const CString& strText)
{
	int nPosXml = strText.Find(_T("// XML\r\n//\r\n\r\n"));
	if (nPosXml == -1)
	{
		AfxMessageBox(_T("Could not find the xml"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	m_strRCFileName = lpszFileName;
	m_strConfigPath.Empty();
	m_lstConfigs.RemoveAll();

	int nPosConfigBegin = strText.Find(STR_XML_NAME_BEGIN, nPosXml);
	while (nPosConfigBegin != -1)
	{
		int nPosNameBegin = strText.Find(_T("\""), nPosConfigBegin);
		if (nPosNameBegin != -1)
		{
			int nPosNameEnd = strText.Find(_T("\""), nPosNameBegin + 1);
			if (nPosNameEnd != -1)
			{
				CString strFullName = strText.Mid(nPosNameBegin + 1, nPosNameEnd - nPosNameBegin - 1);
				nPosNameBegin = strFullName.ReverseFind(_T('\\'));
				m_lstConfigs.AddTail(strFullName.Mid(nPosNameBegin + 1));

				if (m_strConfigPath.IsEmpty())
				{
					m_strConfigPath = strFullName.Left(nPosNameBegin);

					m_strFullConfigPath = m_strConfigPath;
					m_strFullConfigPath.Replace(_T("\\\\"), _T("\\"));

					nPosNameBegin = m_strRCFileName.ReverseFind(_T('\\'));
					m_strFullConfigPath.Insert(0, m_strRCFileName.Left(nPosNameBegin + 1));
				}

				nPosConfigBegin = strText.Find(STR_XML_NAME_BEGIN, nPosNameEnd);
				continue;
			}
		}

		break;
	}

	((CMainFrame*)AfxGetMainWnd())->RefreshConfigView();
	return TRUE;
}

void CMainLogic::OpenConfigFile(LPCTSTR lpszName, CTreeCtrl* pTreeCtrl)
{
	HTREEITEM hTreeItem = pTreeCtrl->GetSelectedItem();
	if (hTreeItem == NULL)
	{
		return;
	}

	if (m_lstConfigs.Find(lpszName) == NULL)
	{
		return;
	}

	CTagManager tm;
	if (!tm.LoadFromFile(m_strFullConfigPath + lpszName))
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
		CTagManager tmPropertys(strPropertys);

		HTREEITEM hGroupItem = NULL;
		CString strProperty;
		while (tmPropertys.ExcludeTag(_T("PROPERTY"), strProperty))
		{
			CTagManager tmProperty(strProperty);
			CString strName = _T("NO NAME");
			tmProperty.ExcludeTag(_T("NAME"), strName);
			CMFCPropertyGridProperty* pPropGroup = new CMFCPropertyGridProperty(_T("PROPERTY"));
			CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("NAME"), (COleVariant)strName);
			pPropGroup->AddSubItem(pProp);

			BOOL bGroup = FALSE;
			if (tmProperty.ReadBool(_T("GROUP"), bGroup) && bGroup)
			{
				pProp = new CMFCPropertyGridProperty(_T("GROUP"), (_variant_t)(bGroup == TRUE), _T(""));
				pPropGroup->AddSubItem(pProp);

				hGroupItem = pTreeCtrl->InsertItem(strName, 1, 1, hTreeItem);
				pTreeCtrl->SetItemData(hGroupItem, (DWORD_PTR)pPropGroup);
			}
			else if (hGroupItem)
			{
				CString strType = _T("Combo");
				tmProperty.ExcludeTag(_T("TYPE"), strType);
				pProp = new CMFCPropertyGridProperty(_T("TYPE"), (COleVariant)strType, _T(""), PROP_DATA_TYPE);
				pProp->AddOption(_T("Combo"));
				pProp->AddOption(_T("Number"));
				pProp->AddOption(_T("Text"));
				pProp->AllowEdit(FALSE);
				pPropGroup->AddSubItem(pProp);

				if (strType.CompareNoCase(_T("Combo")) == 0)
				{
					CString strValue;
					tmProperty.ExcludeTag(_T("VALUE"), strValue);

					pProp = new CMFCPropertyGridProperty(_T("VALUE"), (COleVariant)strValue);
					pPropGroup->AddSubItem(pProp);

					pProp = new CMFCPropertyGridProperty(_T("ITEMS"), PROP_DATA_ITEMS, TRUE);
					pPropGroup->AddSubItem(pProp);

					CString strItem;
					while (tmProperty.ExcludeTag(_T("ITEM"), strItem))
					{
						CMFCPropertyGridProperty* pPropItem = new CMFCPropertyGridProperty(_T("ITEM"), 0, TRUE);
						pProp->AddSubItem(pPropItem);
						pProp->Expand(TRUE);

						CTagManager tmItem(strItem);
						tmItem.ExcludeTag(_T("VALUE"), strValue);
						CMFCPropertyGridProperty* pPropChild = new CMFCPropertyGridProperty(_T("VALUE"), (COleVariant)strValue);
						pPropItem->AddSubItem(pPropChild);

						CString strShort, strPreview;
						tmItem.ExcludeTag(_T("SHORT"), strShort);
						pPropChild = new CMFCPropertyGridProperty(_T("SHORT"), (COleVariant)strShort);
						pPropItem->AddSubItem(pPropChild);

						tmItem.ExcludeTag(_T("PREVIEW"), strPreview);
						EntityToSymbol(strPreview);
						pPropChild = new CMFCPropertyGridProperty(_T("PREVIEW"), (COleVariant)strPreview);
						pPropItem->AddSubItem(pPropChild);
						pPropItem->Expand(TRUE);
					}

					HTREEITEM hItem = pTreeCtrl->InsertItem(strName, 2, 2, hGroupItem);
					pTreeCtrl->SetItemData(hItem, (DWORD_PTR)pPropGroup);
				}
				else if (strType.CompareNoCase(_T("Number")) == 0)
				{
					int nValue;
					tmProperty.ReadInt(_T("VALUE"), nValue);

					pProp = new CMFCPropertyGridProperty(_T("VALUE"), (_variant_t)nValue, _T(""));
					pPropGroup->AddSubItem(pProp);

					CSize range;
					tmProperty.ReadSize(_T("RANGE"), range);
					pProp = new CMFCPropertyGridProperty(_T("RANGE MIN"), (_variant_t)range.cx, _T(""));
					pProp->EnableSpinControl(TRUE, -9999, 9999);
					pPropGroup->AddSubItem(pProp);
					pProp = new CMFCPropertyGridProperty(_T("RANGE MAX"), (_variant_t)range.cy, _T(""));
					pProp->EnableSpinControl(TRUE, -9999, 9999);
					pPropGroup->AddSubItem(pProp);

					BOOL bBuddy = FALSE;
					tmProperty.ReadBool(_T("BUDDY"), bBuddy);
					pProp = new CMFCPropertyGridProperty(_T("BUDDY"), (_variant_t)(bBuddy == TRUE), _T(""));
					pPropGroup->AddSubItem(pProp);

					CString strShort, strPreview;
					tmProperty.ExcludeTag(_T("SHORT"), strShort);
					pProp = new CMFCPropertyGridProperty(_T("SHORT"), (_variant_t)strShort, _T(""));
					pPropGroup->AddSubItem(pProp);

					tmProperty.ExcludeTag(_T("PREVIEW"), strPreview);
					EntityToSymbol(strPreview);
					pProp = new CMFCPropertyGridProperty(_T("PREVIEW"), (_variant_t)strPreview, _T(""));
					pPropGroup->AddSubItem(pProp);

					HTREEITEM hItem = pTreeCtrl->InsertItem(strName, 2, 2, hGroupItem);
					pTreeCtrl->SetItemData(hItem, (DWORD_PTR)pPropGroup);
				}
				else if (strType.CompareNoCase(_T("Text")) == 0)
				{
					CString strValue;
					tmProperty.ExcludeTag(_T("VALUE"), strValue);

					pProp = new CMFCPropertyGridProperty(_T("VALUE"), (COleVariant)strValue);
					pPropGroup->AddSubItem(pProp);

					CString strShort, strPreview;
					tmProperty.ExcludeTag(_T("SHORT"), strShort);
					pProp = new CMFCPropertyGridProperty(_T("SHORT"), (COleVariant)strShort);
					pPropGroup->AddSubItem(pProp);

					tmProperty.ExcludeTag(_T("PREVIEW"), strPreview);
					EntityToSymbol(strPreview);
					pProp = new CMFCPropertyGridProperty(_T("PREVIEW"), (COleVariant)strPreview);
					pPropGroup->AddSubItem(pProp);

					HTREEITEM hItem = pTreeCtrl->InsertItem(strName, 2, 2, hGroupItem);
					pTreeCtrl->SetItemData(hItem, (DWORD_PTR)pPropGroup);
				}
			}
		}

		if (hGroupItem)
		{
			pTreeCtrl->Expand(hGroupItem, TVE_EXPAND);
		}
	}
}

void CMainLogic::EntityToSymbol(CString& value)
{
	value.Replace(_T("\\t"), _T("\t"));
	value.Replace(_T("\\n"), _T("\n"));
	value.Replace(_T("\\r"), _T("\r"));
}
