#include "stdafx.h"
#include "MakeSetConfig.h"
#include "MainFrm.h"
#include "MainLogic.h"
#include "afxtagmanager.h"
#include "MyTagManager.h"

#define STR_XML_NAME_BEGIN _T("IDR_SETCONFIG_XML_")
#define STR_RC_BEGIN_FIND_XML _T("// XML\r\n//\r\n\r\n")
#define STR_RES_CONFIG_PATH _T("res\\\\SetConfig\\\\")

CMainLogic::CMainLogic()
{
}

CMainLogic::~CMainLogic()
{
}

void CMainLogic::LoadRCFile(LPCTSTR lpszFileName)
{
	CString strText;
	if (OpenFile(lpszFileName, strText))
	{
		ParseRCText(lpszFileName, strText);
	}
}

BOOL CMainLogic::ParseRCText(LPCTSTR lpszFileName, const CString& strText)
{
	int nPosXml = strText.Find(STR_RC_BEGIN_FIND_XML);
	if (nPosXml == -1)
	{
		AfxMessageBox(_T("Could not find the xml"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	m_strRCFileName = lpszFileName;
	m_strConfigPath.Empty();
	m_lstConfigs.RemoveAll();
	AfxGetApp()->AddToRecentFileList(m_strRCFileName);

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

void CMainLogic::OpenConfigFile(CTreeCtrl* pTreeCtrl)
{
	HTREEITEM hTreeItem = pTreeCtrl->GetSelectedItem();
	if (hTreeItem == NULL)
	{
		return;
	}

	CString strFileName = pTreeCtrl->GetItemText(hTreeItem);
	if (m_lstConfigs.Find(strFileName) == NULL)
	{
		return;
	}

	strFileName = m_strFullConfigPath + strFileName;
	CTagManager tm;
	if (!tm.LoadFromFile(strFileName))
	{
		return;
	}

	CString strText;
	OpenFile(strFileName, strText);
	((CMainFrame*)AfxGetMainWnd())->SetConfigText(strText);

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
			CMyTagManager tmProperty(strProperty);
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

						CMyTagManager tmItem(strItem);
						tmItem.ExcludeTag(_T("VALUE"), strValue);
						CMFCPropertyGridProperty* pPropChild = new CMFCPropertyGridProperty(_T("VALUE"), (COleVariant)strValue);
						pPropItem->AddSubItem(pPropChild);

						CString strShort, strPreview;
						tmItem.ExcludeTag(_T("SHORT"), strShort);
						pPropChild = new CMFCPropertyGridProperty(_T("SHORT"), (COleVariant)strShort);
						pPropItem->AddSubItem(pPropChild);

						tmItem.ReadEntityString(_T("PREVIEW"), strPreview);
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

					tmProperty.ReadEntityString(_T("PREVIEW"), strPreview);
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

					tmProperty.ReadEntityString(_T("PREVIEW"), strPreview);
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

CString CMainLogic::SymbolToEntity(const CString& value)
{
	CString strValue(value);
	strValue.Replace(_T("\t"), _T("\\t"));
	strValue.Replace(_T("\n"), _T("\\n"));
	strValue.Replace(_T("\r"), _T("\\r"));
	return strValue;
}

BOOL CMainLogic::OpenFile(LPCTSTR lpszFileName, CString& value)
{
	CFile listFile;
	CFileException fileException;
	if (!listFile.Open(lpszFileName, CFile::modeRead, &fileException))
	{
		TCHAR szErrorMsg[1024];
		fileException.GetErrorMessage(szErrorMsg, 1024, NULL);
		AfxMessageBox(szErrorMsg, MB_OK | MB_ICONERROR);
		return FALSE;
	}
	try
	{
		CWaitCursor wait;
		const DWORD dwFileSize = (const DWORD)listFile.GetLength();
		if (dwFileSize == 0)
		{
			return FALSE;
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

		value = strText;
		return TRUE;
	}
	catch (CException* e)
	{
		TCHAR szErrorMsg[1024];
		e->GetErrorMessage(szErrorMsg, 1024, NULL);
		e->Delete();
		AfxMessageBox(szErrorMsg, MB_OK | MB_ICONERROR);
	}
	return FALSE;
}

BOOL CMainLogic::SaveConfigFile(CTreeCtrl* pTreeCtrl)
{
	HTREEITEM hTreeItem = pTreeCtrl->GetSelectedItem();
	if (hTreeItem == NULL)
	{
		return FALSE;
	}

	CString strFileName = pTreeCtrl->GetItemText(hTreeItem);
	if (strFileName.GetAt(strFileName.GetLength() - 1) == '*')
	{
		strFileName.Delete(strFileName.GetLength() - 1);
	}

	if (m_lstConfigs.Find(strFileName) == NULL)
	{
		ModifyRCFile(strFileName, NULL);
	}

	strFileName = m_strFullConfigPath + strFileName;

	CString strData;
	CMyTagManager::WriteTag(strData, CMyTagManager::WriteInt(_T("VERSION"), 1, 0));

	CString strPropertys;
	HTREEITEM hChildItem = pTreeCtrl->GetChildItem(hTreeItem);
	while (hChildItem)
	{
		DWORD_PTR dwChildData = pTreeCtrl->GetItemData(hChildItem);
		if (dwChildData)
		{
			CString strProperty;
			CMyTagManager::WriteTag(strProperty, CMyTagManager::WriteString(_T("NAME"), pTreeCtrl->GetItemText(hChildItem)));
			CMyTagManager::WriteTag(strProperty, CMyTagManager::WriteBool(_T("GROUP"), TRUE, FALSE));
			CMyTagManager::WriteItem(strPropertys, _T("PROPERTY"), strProperty);

			HTREEITEM hPropItem = pTreeCtrl->GetChildItem(hChildItem);
			while (hPropItem)
			{
				DWORD_PTR dwPropData = pTreeCtrl->GetItemData(hPropItem);
				if (dwPropData)
				{
					CMFCPropertyGridProperty* pGroupProp = (CMFCPropertyGridProperty*)dwPropData;
					if (pGroupProp)
					{
						strProperty.Empty();
						CMyTagManager::WriteTag(strProperty, CMyTagManager::WriteString(_T("NAME"), pGroupProp->GetSubItem(0)->GetValue()));
						CMyTagManager::WriteTag(strProperty, CMyTagManager::WriteString(_T("TYPE"), pGroupProp->GetSubItem(1)->GetValue()));
						CMyTagManager::WriteTag(strProperty, CMyTagManager::WriteString(_T("VALUE"), pGroupProp->GetSubItem(2)->GetValue()));
						
						CString strType(pGroupProp->GetSubItem(1)->GetValue());
						if (strType.CompareNoCase(_T("Combo")) == 0)
						{
							CMFCPropertyGridProperty* pItemsProp = pGroupProp->GetSubItem(3);
							for (int i = 0; i < pItemsProp->GetSubItemsCount(); i++)
							{
								CMFCPropertyGridProperty* pItemProp = pItemsProp->GetSubItem(i);

								CString strItem;
								CMyTagManager::WriteTag(strItem, CMyTagManager::WriteString(_T("VALUE"), pItemProp->GetSubItem(0)->GetValue()));
								CMyTagManager::WriteTag(strItem, CMyTagManager::WriteString(_T("SHORT"), pItemProp->GetSubItem(1)->GetValue()));
								CMyTagManager::WriteTag(strItem, CMyTagManager::WriteEntityString(_T("PREVIEW"), SymbolToEntity(pItemProp->GetSubItem(2)->GetValue())));
								
								CMyTagManager::WriteItem(strProperty, _T("ITEM"), strItem);
							}
						}
						else if (strType.CompareNoCase(_T("Number")) == 0)
						{
							CMyTagManager::WriteTag(strProperty, CMyTagManager::WriteSize(_T("RANGE"), 
								CSize(pGroupProp->GetSubItem(3)->GetValue().intVal, pGroupProp->GetSubItem(4)->GetValue().intVal), CSize(-999, 9999)));
							CMyTagManager::WriteTag(strProperty, CMyTagManager::WriteBool(_T("BUDDY"), pGroupProp->GetSubItem(5)->GetValue().boolVal, FALSE));
							CMyTagManager::WriteTag(strProperty, CMyTagManager::WriteString(_T("SHORT"), pGroupProp->GetSubItem(6)->GetValue()));
							CMyTagManager::WriteTag(strProperty, CMyTagManager::WriteEntityString(_T("PREVIEW"), SymbolToEntity(pGroupProp->GetSubItem(7)->GetValue())));
						}
						else if (strType.CompareNoCase(_T("Text")) == 0)
						{
							CMyTagManager::WriteTag(strProperty, CMyTagManager::WriteString(_T("SHORT"), pGroupProp->GetSubItem(3)->GetValue()));
							CMyTagManager::WriteTag(strProperty, CMyTagManager::WriteEntityString(_T("PREVIEW"), SymbolToEntity(pGroupProp->GetSubItem(4)->GetValue())));
						}
						CMyTagManager::WriteItem(strPropertys, _T("PROPERTY"), strProperty);
					}
				}
				hPropItem = pTreeCtrl->GetNextItem(hPropItem, TVGN_NEXT);
			}
		}
		hChildItem = pTreeCtrl->GetNextItem(hChildItem, TVGN_NEXT);
	}
	CMyTagManager::WriteItem(strData, _T("PROPERTYS"), strPropertys);

	CString strTag;
	CMyTagManager::WriteItem(strTag, _T("SETCONFIG"), strData);

	CFile listFile;
	CFileException fileException;
	if (!listFile.Open(strFileName, CFile::modeWrite | CFile::modeCreate, &fileException))
	{
		TCHAR szErrorMsg[1024];
		fileException.GetErrorMessage(szErrorMsg, 1024, NULL);
		AfxMessageBox(szErrorMsg, MB_OK | MB_ICONERROR);
		return FALSE;
	}
	CStringA strListA(strTag);
	listFile.Write(strListA, strListA.GetLength());
	listFile.Close();
	return TRUE;
}

void CMainLogic::ModifyRCFile(LPCTSTR lpszAddConfig, LPCTSTR lpszDelConfig)
{
	CString strText;
	if (!OpenFile(m_strRCFileName, strText))
	{
		AfxMessageBox(_T("Could not open RC file"), MB_OK | MB_ICONERROR);
		return;
	}
	int nPosXml = strText.Find(STR_RC_BEGIN_FIND_XML);
	if (nPosXml == -1)
	{
		AfxMessageBox(_T("Could not find the xml"), MB_OK | MB_ICONERROR);
		return;
	}	

	if (lpszAddConfig)
	{
		int nPosLineBegin = strText.Find(_T("\r\n\r\n"), nPosXml + CString(STR_RC_BEGIN_FIND_XML).GetLength());
		if (nPosLineBegin != -1)
		{
			CString strName(lpszAddConfig);
			CString strUpper(strName.Left(strName.GetLength() - 4).MakeUpper());
			CString strLine = STR_XML_NAME_BEGIN + strUpper +
				_T("  XML") + CString(' ', max(0, 25 - strUpper.GetLength())) + _T("\"") + STR_RES_CONFIG_PATH + lpszAddConfig + _T("\"\r\n");
			strText.Insert(nPosLineBegin + 2, strLine);
		}
		m_lstConfigs.AddTail(lpszAddConfig);
	}
	if (lpszDelConfig)
	{
		CFileFind find;
		if (find.FindFile(m_strFullConfigPath + lpszDelConfig))
		{
			CFile::Remove(m_strFullConfigPath + lpszDelConfig);
		}
		find.Close();

		POSITION pos = m_lstConfigs.Find(lpszDelConfig);
		if (pos == NULL)
		{
			return;
		}

		CString strName(lpszDelConfig);
		int nPosLineBegin = strText.Find(STR_XML_NAME_BEGIN + strName.Left(strName.GetLength() - 4).MakeUpper(), nPosXml);
		if (nPosLineBegin != -1)
		{
			int nPosLineEnd = strText.Find(_T('\n'), nPosLineBegin);
			if (nPosLineEnd != -1)
			{
				strText.Delete(nPosLineBegin, nPosLineEnd - nPosLineBegin + 1);
			}
		}
		m_lstConfigs.RemoveAt(pos);
	}

	CFile listFile;
	CFileException fileException;
	if (!listFile.Open(m_strRCFileName, CFile::modeWrite | CFile::modeCreate, &fileException))
	{
		TCHAR szErrorMsg[1024];
		fileException.GetErrorMessage(szErrorMsg, 1024, NULL);
		AfxMessageBox(szErrorMsg, MB_OK | MB_ICONERROR);
		return;
	}
	CStringA strListA(strText);
	listFile.Write(strListA, strListA.GetLength());
	listFile.Close();
}
