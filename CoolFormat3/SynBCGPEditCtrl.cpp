// SynBCGPEditCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SynBCGPEditCtrl.h"
#include "GlobalUtils.h"

#include "FormatterHelp.h"
#include "ChildFrm.h"

static UINT g_uHtmlPos = 0;

static const TCHAR g_chEOL = _T ('\n');

//////////////////////////////////////////////////////////////////////////
// CSynBCGPEditCtrl

IMPLEMENT_DYNAMIC(CSynBCGPEditCtrl, CBCGPEditCtrl)

CSynBCGPEditCtrl::CSynBCGPEditCtrl()
{
	m_nUndoBufferSize = 30;
	m_nLeftMarginWidth = 0;
	m_ptCaret = (CPoint (0, 0));
	m_bEnableLineNumbersMargin = TRUE;
	m_nLineNumbersMarginWidth = 25;
	m_bEnableOutlineMargin = TRUE;
	m_nOutlineMarginWidth = 12;
	if (m_bEnableLineNumbersMargin)
	{
		m_ptCaret.x += m_nLineNumbersMarginWidth;
	}
	if (m_bEnableOutlineMargin)
	{
		m_ptCaret.x += m_nOutlineMarginWidth;
	}
	m_nColorBlockStrLenMax = 4 + 2;
	m_bNumberColor = FALSE;
	m_bCheckColorTags = FALSE;
	m_bFirstShow = TRUE;
}

CSynBCGPEditCtrl::~CSynBCGPEditCtrl()
{
}

BEGIN_MESSAGE_MAP(CSynBCGPEditCtrl, CBCGPEditCtrl)
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CSynBCGPEditCtrl::SelectLanguage( UINT nLanguage )
{
	RemoveXMLSettings();
	theApp.m_nSynLanguage = nLanguage;

	// 1)设置语言
	m_SynLanguage.SetCurLanguage(nLanguage);

	// 2)设置分隔符
	m_strWordDelimeters = m_SynLanguage.GetWordDelimeters();
	m_strSpecialDelimiters = m_SynLanguage.GetSpecialDelimiters();
	m_strIntelliSenseChars = m_SynLanguage.GetIntelliSenseChars();
	CString strEscapeSequence, strEscapeSequences;
	int nPos, nPosPrior = 0;

	strEscapeSequences = m_SynLanguage.GetEscapeSequences();
	nPos = strEscapeSequences.Find(_T(","), nPosPrior);
	while (nPos != -1)
	{
		strEscapeSequence = strEscapeSequences.Mid(nPosPrior, nPos - nPosPrior);
		AddEscapeSequence (strEscapeSequence);

		nPosPrior = nPos + 1;
		nPos = strEscapeSequences.Find(_T(","), nPosPrior);
	}
	
	// 3)设置关键字
	BOOL bCaseSensitive;
	CString strWords;
	CString strWord;
	nPosPrior = 0;

	m_SynLanguage.GetWords(strWords, bCaseSensitive);
	nPos = strWords.Find(_T(","), nPosPrior);
	while (nPos != -1)
	{
		strWord = strWords.Mid(nPosPrior, nPos - nPosPrior);
		SetWordColor(strWord, m_clrSyn, -1, bCaseSensitive);

		nPosPrior = nPos + 1;
		nPos = strWords.Find(_T(","), nPosPrior);
	}

	nPosPrior = 0;
	m_SynLanguage.GetTypeWords(strWords, bCaseSensitive);
	nPos = strWords.Find(_T(","), nPosPrior);
	while (nPos != -1)
	{
		strWord = strWords.Mid(nPosPrior, nPos - nPosPrior);
		SetWordColor(strWord, m_clrType, -1, bCaseSensitive);

		nPosPrior = nPos + 1;
		nPos = strWords.Find(_T(","), nPosPrior);
	}
	m_SynLanguage.GetIsNumberColor(m_bNumberColor);

	// 4)设置注释
	CString strBlockOpen, strBlockClose;

	m_SynLanguage.GetMultilineComment(strBlockOpen, strBlockClose, bCaseSensitive);
	if (_T("") != strBlockOpen.Trim())
	{
		SetBlockColor(strBlockOpen, strBlockClose, TRUE, m_clrComment, -1, bCaseSensitive);
	}

	CString strBlockOpens;
	m_SynLanguage.GetLineComment(strBlockOpens, bCaseSensitive);
	nPosPrior = 0;
	nPos = strBlockOpens.Find(_T(","), nPosPrior);
	while (nPos != -1)
	{
		strBlockOpen = strBlockOpens.Mid(nPosPrior, nPos - nPosPrior);
		SetBlockColor(strBlockOpen, _T(""), FALSE, m_clrComment, -1, bCaseSensitive);

		nPosPrior = nPos + 1;
		nPos = strBlockOpens.Find(_T(","), nPosPrior);
	}

	// 5)设置字符串
	m_SynLanguage.GetString(strBlockOpen, strBlockClose, bCaseSensitive);
	if (_T("") != strBlockOpen.Trim())
	{
		SetBlockColor(strBlockOpen, strBlockClose, FALSE, m_clrString, -1, bCaseSensitive);
	}
	m_SynLanguage.GetChar(strBlockOpen, strBlockClose, bCaseSensitive);
	if (_T("") != strBlockOpen.Trim())
	{
		SetBlockColor(strBlockOpen, strBlockClose, FALSE, m_clrChar, -1, bCaseSensitive);
	}

	// 6)设置折叠
	if (m_pOutlineParser != NULL)
	{
		m_OutlineNodes.DeleteAllBlocks ();
		m_pOutlineParser->RemoveAllBlockTypes ();		

		// 7)大纲设置
		m_pOutlineParser->m_strDelimiters = m_strWordDelimeters;
		m_pOutlineParser->m_bCaseSensitive = m_SynLanguage.GetOutlineCaseSensitive();
		m_pOutlineParser->m_bWholeWords = m_SynLanguage.GetOutlineWholeWords();

		// 8)转义字符
		m_SynLanguage.GetOutlineEscapeSequences(strEscapeSequences);
		nPosPrior = 0;
		nPos = strEscapeSequences.Find(_T(","), nPosPrior);
		while (nPos != -1)
		{
			strEscapeSequence = strEscapeSequences.Mid(nPosPrior, nPos - nPosPrior);
			m_pOutlineParser->AddEscapeSequence (strEscapeSequence);

			nPosPrior = nPos + 1;
			nPos = strEscapeSequences.Find(_T(","), nPosPrior);
		}

		// 9)折叠块
		CString strBlock, strBlocks;
		CString strReplace, strNested, strIgnore;
		CStringList lstKeywordsList;
		int nBlockPos, nBlockPosPrior = 0;
		m_SynLanguage.GetOutlineBlockType(strBlocks);
		nPosPrior = 0;
		nPos = strBlocks.Find(_T("|"), nPosPrior);
		while (nPos != -1)
		{
			strBlock = strBlocks.Mid(nPosPrior, nPos - nPosPrior);

			nBlockPosPrior = 0;
			nBlockPos = strBlock.Find(_T(","), nBlockPosPrior);
			if (nBlockPos != -1)
			{
				strBlockOpen = strBlock.Mid(nBlockPosPrior, nBlockPos - nBlockPosPrior);

				nBlockPosPrior = nBlockPos + 1;
				nBlockPos = strBlock.Find(_T(","), nBlockPosPrior);
				if (nBlockPos != -1)
				{
					strBlockClose = strBlock.Mid(nBlockPosPrior, nBlockPos - nBlockPosPrior);

					nBlockPosPrior = nBlockPos + 1;
					nBlockPos = strBlock.Find(_T(","), nBlockPosPrior);
					if (nBlockPos != -1)
					{
						strReplace =  strBlock.Mid(nBlockPosPrior, nBlockPos - nBlockPosPrior);

						nBlockPosPrior = nBlockPos + 1;
						nBlockPos = strBlock.Find(_T(","), nBlockPosPrior);
						if (nBlockPos != -1)
						{
							strNested =  strBlock.Mid(nBlockPosPrior, nBlockPos - nBlockPosPrior);

							nBlockPosPrior = nBlockPos + 1;
							nBlockPos = strBlock.Find(_T(","), nBlockPosPrior);
							if (nBlockPos != -1)
							{
								strIgnore =  strBlock.Mid(nBlockPosPrior, nBlockPos - nBlockPosPrior);

								nBlockPosPrior = nBlockPos + 1;
								nBlockPos = strBlock.Find(_T(","), nBlockPosPrior);
								lstKeywordsList.RemoveAll();
								while (nBlockPos != -1)
								{
									lstKeywordsList.AddTail(strBlock.Mid(nBlockPosPrior, nBlockPos - nBlockPosPrior));

									nBlockPosPrior = nBlockPos + 1;
									nBlockPos = strBlock.Find(_T(","), nBlockPosPrior);
								}
								m_pOutlineParser->AddBlockType(strBlockOpen, strBlockClose, strReplace, _ttoi(strNested), _ttoi(strIgnore), &lstKeywordsList);
							}
						}
					}
				}
			}

			nPosPrior = nPos + 1;
			nPos = strBlocks.Find(_T("|"), nPosPrior);
		}
		EnableAutoOutlining(!strBlocks.IsEmpty());  //禁止掉无大纲的语言，这样可以有“隐藏选定区域”功能
	}

	// 10)设置超链接
	m_lstURLPrefixes.RemoveAll ();
	m_arrHyperlinks.RemoveAll ();
	m_nCurrHyperlink = -1;
	m_nCurrHyperlinkHot = -1;	

	m_lstURLPrefixes.AddTail (_T("http://"));
	m_lstURLPrefixes.AddTail (_T("ftp://"));
	m_lstURLPrefixes.AddTail (_T("mailto:"));
	m_lstURLPrefixes.AddTail (_T("news://"));
	m_lstURLPrefixes.AddTail (_T("file://"));
	m_lstURLPrefixes.AddTail (_T("telnet://"));
	m_lstURLPrefixes.AddTail (_T("gopher://"));
	m_lstURLPrefixes.AddTail (_T("prospero://"));
	m_lstURLPrefixes.AddTail (_T("wais://"));
	m_lstURLPrefixes.AddTail (_T("nntp://"));

	m_bCheckColorTags = FALSE;
	UseXmlParser (FALSE);
	switch (nLanguage)
	{
	case SYN_ASP:
	case SYN_HTML:
	case SYN_XML:
		m_bCheckColorTags = TRUE;
		EnableAutoOutlining(TRUE);
		UseXmlParser(TRUE);
		break;
	case SYN_PASCAL:
		SetBlockColor(_T("(*"), _T("*)"), FALSE, m_clrComment, -1, FALSE);
		break;
	case SYN_AUTOIT:
		//SetBlockColor(_T("#comments-start"), _T("#comments-end"), FALSE, m_clrComment, -1, FALSE);
		break;
	case SYN_D:
		SetBlockColor(_T("/+"), _T("+/"), FALSE, m_clrComment, -1, FALSE);
		SetBlockColor(_T("`"), _T("`"), FALSE, m_clrChar, -1, FALSE);
		break;
	}
	RedrawWindow();
	UpdateAutoOutlining();
}

BOOL CSynBCGPEditCtrl::OnGetWordColor( const CString& strWord, COLORREF& clrText, COLORREF& clrBk, int nPos )
{
	BCGP_EDIT_SYNTAX_COLOR clrWord;

	if (strWord.IsEmpty ())
	{
		return FALSE;
	}

	if (!m_mapWordColors.Lookup (strWord, clrWord))
	{
		CString strUpper = strWord; 
		strUpper.MakeUpper ();
		if (!m_mapWordColors.Lookup (strUpper, clrWord))
		{
			if (m_bNumberColor)
			{
				int nLength = strWord.GetLength();
				for (int i = 0; i < nLength; i++)
				{
					if (!_istdigit(strWord[i]))
					{
						return FALSE;
					}
				}
				clrText = m_clrNumber;
				return TRUE;
			} 
			else
			{
				return FALSE;
			}			
		}

		if (!clrWord.m_bCaseSensitive)
		{
			clrText = clrWord.m_clrForeground;
			clrBk = clrWord.m_clrBackground;

			if (clrText == (COLORREF) -1)
			{
				clrText = GetDefaultTextColor ();
			}

			if (clrBk == (COLORREF) -1)
			{	
				clrBk = GetDefaultBackColor ();
			}

			return TRUE;
		}

		return FALSE;
	}

	if (m_mapWordColors.Lookup (strWord, clrWord))
	{
		clrText = clrWord.m_clrForeground;
		clrBk = clrWord.m_clrBackground;

		if (clrText == (COLORREF) -1)
		{
			clrText = GetDefaultTextColor ();
		}

		if (clrBk == (COLORREF) -1)
		{	
			clrBk = GetDefaultBackColor ();
		}

		return TRUE;
	}

	return FALSE;
}

void CSynBCGPEditCtrl::SelectLanguageByExt( CString strExt )
{
	SelectLanguage(g_GlobalUtils.m_sLanguageExt.GetLanguageByExt(strExt));
}

LPCTSTR CSynBCGPEditCtrl::GetSelectLangString()
{
	return g_GlobalUtils.m_sLanguageExt.GetLanguageString(m_SynLanguage.GetCurLanguage());
}

void CSynBCGPEditCtrl::OnGetCharColor( TCHAR ch, int nOffset, COLORREF& clrText, COLORREF& clrBk )
{
	if (m_SynLanguage.GetCurLanguage() == SYN_INI)
	{
		if (ch == _T ('='))
		{
			clrText = m_clrSyn;
		}
	}
	if (m_bCheckColorTags)
	{

		TCHAR chOpen = _T ('<');
		TCHAR chClose = _T ('>');

		if (ch == chOpen || ch == chClose || ch == _T ('/'))
		{
			clrText = m_clrSyn;
		}
		else 
		{
			COLORREF clrDefaultBack = GetDefaultBackColor ();
			COLORREF clrDefaultTxt = GetDefaultTextColor ();
			int nBlockStart, nBlockEnd;
			if (!IsInBlock (nOffset, chOpen, chClose, nBlockStart, nBlockEnd))
			{
				clrText = clrDefaultTxt;
				clrBk = clrDefaultBack;
			}
			/*else if (GetCharAt (nBlockStart + 1) == _T ('%') && 
				GetCharAt (nBlockEnd - 1) == _T ('%'))
			{
				
			}*/
			else if (clrText == clrDefaultTxt && m_SynLanguage.GetCurLanguage() == SYN_XML)
			{
				if (ch == _T ('='))
				{
					//clrText = RGB (0, 0, 255);
				}
				else
				{
					clrText = m_clrSyn;
				}
			}
		}
	}
}


void CSynBCGPEditCtrl::OnKillFocus(CWnd* pNewWnd)
{
	CBCGPEditCtrl::OnKillFocus(pNewWnd);

	if (m_bFirstShow)
	{
		m_bFirstShow = FALSE;
		SetFocus();
	}
}

BOOL CSynBCGPEditCtrl::OpenFileEx( const CString& strFileName )
{
	CString strText;
	if (m_File.OpenFile(strFileName, strText))
	{
		if (!globalData.bIsWindowsVista) //XP的时候
		{
			if (theApp.m_bChangedLang)
			{
				strText = CA2T(CT2A(strText), GetACP());
			}
		}
		SetWindowText(strText);
		return TRUE;
	} 
	else
	{
		CFMessageBox(m_File.GetLastErrorMsg(), MB_OK | MB_ICONERROR);
		return FALSE;
	}
}

BOOL CSynBCGPEditCtrl::SaveFileEx( const CString& strFileName )
{
	CString strBuffer(m_strBuffer);
	strBuffer.Replace(_T("\n"), _T("\r\n"));
	if (m_File.SaveFile(strFileName, strBuffer))
	{
		m_bIsModified = FALSE;
		m_posDocSavedUndoPos = m_posUndoBuffer;
		m_bSavedUndo = !m_bBOL;

		// Update saved flag:
		for (POSITION pos = m_lstUndoActions.GetHeadPosition (); pos != NULL;)
		{
			POSITION posSave = pos;
			BCGP_EDIT_UNDO_ACTION* pUndoAction = m_lstUndoActions.GetNext (pos);
			ASSERT (pUndoAction != NULL);

			if (m_bEOL && posSave == m_lstUndoActions.GetTailPosition () ||
				!m_bEOL && posSave == m_posUndoBuffer)
			{
				// mark as saved
				pUndoAction->m_dwFlags |= g_dwUAFSaved;
			}
			else
			{
				// clear saved flag
				pUndoAction->m_dwFlags &= ~g_dwUAFSaved;
			}
		}
		return TRUE;
	} 
	else
	{
		CFMessageBox(m_File.GetLastErrorMsg(), MB_OK | MB_ICONERROR);
		return FALSE;
	}
}

void CSynBCGPEditCtrl::LoadColor( BOOL bRedraw /*= FALSE*/ )
{
	m_clrBack = g_GlobalUtils.m_sColorScheme.m_clrBack;	//背景色
	m_clrText = g_GlobalUtils.m_sColorScheme.m_clrText; //正常色

	m_clrBackSelActive = g_GlobalUtils.m_sColorScheme.m_clrBackSelActive;	//选定的背景色
	m_clrBackSelInActive = g_GlobalUtils.m_sColorScheme.m_clrBackSelInActive;	//非活动的选定背景色
	m_clrTextSelActive = g_GlobalUtils.m_sColorScheme.m_clrTextSelActive;	//选定的文本色
	m_clrTextSelInActive = g_GlobalUtils.m_sColorScheme.m_clrTextSelInActive;	//非活动的选定文本色

	m_clrBackOutline = g_GlobalUtils.m_sColorScheme.m_clrBackOutline;	//折叠块背景色
	m_clrLineOutline = g_GlobalUtils.m_sColorScheme.m_clrLineOutline;	//折叠块线色

	m_clrBackLineNumber = g_GlobalUtils.m_sColorScheme.m_clrBackLineNumber;	//行号背景色
	m_clrTextLineNumber = g_GlobalUtils.m_sColorScheme.m_clrTextLineNumber;	//行号色
	m_clrBackSidebar = g_GlobalUtils.m_sColorScheme.m_clrBackSidebar;		//分隔线色
	m_clrHyperlink = g_GlobalUtils.m_sColorScheme.m_clrHyperlink;		//超链接色

	m_clrSyn = g_GlobalUtils.m_sColorScheme.m_clrSyn;		//语法颜色
	m_clrType = g_GlobalUtils.m_sColorScheme.m_clrType;		//类型颜色
	m_clrNumber = g_GlobalUtils.m_sColorScheme.m_clrNumber;	//数字颜色
	m_clrString = g_GlobalUtils.m_sColorScheme.m_clrString;	//字符串颜色
	m_clrChar = g_GlobalUtils.m_sColorScheme.m_clrChar;		//字符颜色
	m_clrComment = g_GlobalUtils.m_sColorScheme.m_clrComment;	//注释颜色

	if (bRedraw)
	{
		SelectLanguage(m_SynLanguage.GetCurLanguage());
	}
}

int CSynBCGPEditCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPEditCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	LoadColor();

	return 0;
}

void CSynBCGPEditCtrl::OnSysColorChange()
{
	CWnd::OnSysColorChange();

	InitColors ();
	RedrawWindow ();
}

static CString ColorMyTag (COLORREF clr)
{
	BYTE bR = GetRValue (clr);
	BYTE bG = GetGValue (clr);
	BYTE bB = GetBValue (clr);

	CString strColorTag = _T("");
	//strColorTag.Format (_T("<font color=\"#%0.2x%0.2x%0.2x\">"), bR, bG, bB);
	if (g_uHtmlPos == 0)
	{		
		g_uHtmlPos = 1;
	}
	else
	{
		strColorTag.Append(_T("</span>"));
	}
	strColorTag.AppendFormat(_T("<span style=\"color:#%0.2x%0.2x%0.2x;\">"), bR, bG, bB);

	return strColorTag;
}

void CSynBCGPEditCtrl::ExportToMyHTML( CString& strHTML )
{
	g_uHtmlPos = 0;
	int nStartOffset = 0; 
	int nEndOffset = m_strBuffer.GetLength () - 1;

	COLORREF clrDefaultText = GetDefaultTextColor ();
	COLORREF clrDefaultBack = GetDefaultBackColor ();

	COLORREF clrNextWordFore	= clrDefaultText;
	COLORREF clrNextWordBk		= clrDefaultBack;

	COLORREF clrOutText = clrDefaultText;
	COLORREF clrOutBack = clrDefaultBack;

	// ----------------------------------------------
	// Build color areas for visible part of a buffer (comments, strings and so on):
	// ----------------------------------------------
	BCGP_EDIT_COLOR_BLOCK	clrBlock; 
	BOOL bIsOpenBlock = FindOpenBlock (nStartOffset, &clrBlock);

	int nCloseBlockOffset = -1;
	if (bIsOpenBlock)
	{
		nCloseBlockOffset = FindCloseBlock (nStartOffset, &clrBlock);
	}

	COLORREF clrBlockFore = (clrBlock.m_clrForeground == -1) ? GetDefaultTextColor () : clrBlock.m_clrForeground;
	COLORREF clrBlockBack = (clrBlock.m_clrBackground == -1) ? GetDefaultBackColor () : clrBlock.m_clrBackground; 

	CList <BCGP_EDIT_COLOR_AREA, BCGP_EDIT_COLOR_AREA&> colorAreas;

	if (bIsOpenBlock) 
	{
		if (nCloseBlockOffset < nEndOffset)
		{
			BuildColorAreas (colorAreas, nCloseBlockOffset, nEndOffset, NULL, FALSE);
		}
	}
	else
	{
		BuildColorAreas (colorAreas, nStartOffset, nEndOffset, NULL, FALSE);
	}

	// ---------------------------------------------
	// Draw the text for the visible part of buffer:
	// ---------------------------------------------
	TCHAR* lpszOutBuffer = (TCHAR*) alloca (sizeof (TCHAR) * m_nMaxScrollWidth);
	memset (lpszOutBuffer, 0, sizeof (TCHAR) * m_nMaxScrollWidth);
	int iIdx = 0;

	int nNextDelimiter = -1;
	int nCurrRow = 0;
	int nCurrColumn = 0;

	for (int i = nStartOffset; i <= nEndOffset; i++)
	{
		COLORREF clrForeground = clrDefaultText;
		COLORREF clrBackground = clrDefaultBack;

		TCHAR chNext = m_strBuffer [i];

		// --------------
		// Define colors:
		// --------------
		BOOL bColorFound = FALSE;

		// 1) ignore selection
		// 2) ignore colored line markers

		// 3) check for color blocks:
		if (bIsOpenBlock && i < nCloseBlockOffset)
		{
			clrForeground = clrBlockFore;
			clrBackground = clrBlockBack;
			bColorFound = TRUE;
		}
		else
		{
			// check all color areas (comments, strings and so on)
			for (POSITION pos = colorAreas.GetHeadPosition (); pos != NULL;)
			{
				BCGP_EDIT_COLOR_AREA colorArea = colorAreas.GetNext (pos);
				if (i >= colorArea.m_nStart && i <= colorArea.m_nEnd)
				{
					clrForeground = colorArea.m_clrForeground; 
					clrBackground = colorArea.m_clrBackground;

					if (clrForeground == -1)
					{
						clrForeground = clrDefaultText;
					}

					if (clrBackground == -1)
					{
						clrBackground = clrDefaultBack;
					}

					bColorFound = TRUE;
					break;
				}
			}
		}

		// 4) User can define text color by own:
		if (OnGetTextColor (i, nNextDelimiter, clrForeground, clrBackground, bColorFound))
		{
			bColorFound = TRUE;
		}

		// 5) Check all color words (keywords and words):
		if (chNext != g_chEOL)
		{
			if (nNextDelimiter == -1) 
			{
				CString strNextWord;		

				for (int iIdx = i; iIdx <= nEndOffset; iIdx++)
				{
					TCHAR ch = m_strBuffer [iIdx];
					if (m_strWordDelimeters.Find (ch) != -1)
					{
						nNextDelimiter = iIdx;
						break;
					}
				}

				if (nNextDelimiter == -1)
				{
					nNextDelimiter = nEndOffset + 1;
				}

				if (nNextDelimiter != -1)
				{
					strNextWord = 
						m_strBuffer.Mid (i, nNextDelimiter - i);
				}

				if (!OnGetWordColor (strNextWord, clrNextWordFore, clrNextWordBk, i))
				{
					clrNextWordFore = clrDefaultText;
					clrNextWordBk = clrDefaultBack;
				}
			}

			if (i >= nNextDelimiter - 1)
			{
				nNextDelimiter = -1;
			}

			if (!bColorFound)
			{
				clrForeground = clrNextWordFore;
				clrBackground = clrNextWordBk;
			}
		}

		// 6) ignore hilited text

		// 7) User can define color of current char:
		if (!bColorFound)
		{
			OnGetCharColor (chNext, i, clrForeground, clrBackground);
		}

		// -----------------------------------
		// Proceed end of same color fragment:
		// -----------------------------------

		if (clrForeground != clrOutText || clrBackground != clrOutBack)
		{ 
			clrOutText = clrForeground;
			clrOutBack = clrBackground;

			if (iIdx != 0)
			{
				CString strLine (lpszOutBuffer);
				OnPrepareHTMLString (strLine);
				strHTML += strLine;

				iIdx = 0;
				memset (lpszOutBuffer, 0, sizeof (TCHAR) * m_nMaxScrollWidth);
			}

			strHTML += ColorMyTag (clrOutText);
		}

		// --------------------
		// Proceed end of line:
		// --------------------
		if (chNext == g_chEOL)
		{
			{
				CString strLine (lpszOutBuffer);
				OnPrepareHTMLString (strLine);
				strLine += _T("<BR>");
				strLine += g_chEOL;
				strHTML += strLine;

				iIdx = 0;
				memset (lpszOutBuffer, 0, sizeof (TCHAR) * m_nMaxScrollWidth);
			}

			nCurrRow++;
			nCurrColumn = 0;
			continue;
		}

		// -------------
		// Replace Tabs:
		// -------------
		if (chNext == _T('\t'))
		{
			int nRestOfTab = m_nTabSize - nCurrColumn % m_nTabSize;
			nCurrColumn += nRestOfTab;

			for (int k = 0; k < nRestOfTab; k++)
			{
				if (iIdx + k + 1 > m_nMaxScrollWidth - 1)
				{
					CString strLine (lpszOutBuffer);
					OnPrepareHTMLString (strLine);
					strHTML += strLine;

					iIdx = 0;
					memset (lpszOutBuffer, 0, sizeof (TCHAR) * m_nMaxScrollWidth);
				}

				lpszOutBuffer [iIdx] = _T(' ');
				lpszOutBuffer [iIdx + 1] = _T ('\0');
				iIdx ++;
			}
		}

		else
		{
			nCurrColumn++;

			if (iIdx + 1 > m_nMaxScrollWidth - 1)
			{
				CString strLine (lpszOutBuffer);
				OnPrepareHTMLString (strLine);
				strHTML += strLine;

				iIdx = 0;
				memset (lpszOutBuffer, 0, sizeof (TCHAR) * m_nMaxScrollWidth);
			}

			lpszOutBuffer [iIdx] = chNext;
			lpszOutBuffer [iIdx + 1] = _T ('\0');
			iIdx++;
		}
	}

	// --------------------------
	// Draw the last of the text:
	// --------------------------
	if (iIdx != 0)
	{
		CString strLine (lpszOutBuffer);
		OnPrepareHTMLString (strLine);
		strHTML += strLine;

		iIdx = 0;
		memset (lpszOutBuffer, 0, sizeof (TCHAR) * m_nMaxScrollWidth);
	}
	if (g_uHtmlPos != 0)
	{
		strHTML += _T("</span>");
	}	
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditCtrl::InsertComment(BOOL bForward)
{
	int iStartSel = min (m_iStartSel, m_iEndSel);
	int iEndSel = max (m_iStartSel, m_iEndSel);
	int nFirstSelRow, nLastSelRow;
	if (iStartSel == -1 || iEndSel == -1)
	{
		nFirstSelRow = GetCurrRowStart(FALSE);
		nLastSelRow = GetCurrRowEnd(FALSE);
	} 
	else
	{
		int nEndRowOffset = GetRowStartByOffset (iEndSel, TRUE);

		if (nEndRowOffset == iEndSel)
		{
			iEndSel--;
		}

		nFirstSelRow = GetRowStartByOffset	(iStartSel, TRUE);
		nLastSelRow  = max (iEndSel, GetRowEndByOffset (iEndSel, TRUE));
	}
	

	SetSel2(nFirstSelRow, nLastSelRow + 1, TRUE, FALSE);
	CString strSelText(GetSelText());
	if (strSelText.IsEmpty())
	{
		return;
	}

	CString strComment;
	BOOL bCaseSensitive;
	m_SynLanguage.GetLineComment(strComment, bCaseSensitive);
	int nPosPrior = 0;
	int nPos = strComment.Find(_T(","), nPosPrior);
	if(nPos != -1)
	{
		strComment = strComment.Mid(nPosPrior, nPos - nPosPrior);
	}
	if (strComment.IsEmpty())
	{
		return;
	}

	if (bForward)
	{
		int nCommentLen = strComment.GetLength();
		nPos = nCommentLen;
		strSelText.Insert(0, strComment);
		nPos = strSelText.Find(g_chEOL, nPos);
		while (nPos != -1)
		{
			if (nPos == strSelText.GetLength() - 1)
			{
				break;
			}
			strSelText.Insert(nPos + 1, strComment);
			nPos = strSelText.Find(g_chEOL, nPos + nCommentLen + 1);
		}

		SetLastUndoReason(g_dwUATComment);
		ReplaceSel(strSelText, TRUE);
	} 
	else
	{
		int nCommentLen = strComment.GetLength();
		BOOL bModify = FALSE;
		CString strMid, strLeft;
		int nPosComment;
		nPos = 0, nPosPrior = 0;
		nPos = strSelText.Find(g_chEOL, nPosPrior);
		// 当是最后一行时，也要处理
		if (-1 == nPos)
		{
			nPos = strSelText.GetLength();
		}
		while (nPos != -1)
		{
			strMid = strSelText.Mid(nPosPrior, nPos - nPosPrior);
			strLeft = strMid.TrimLeft();
			strLeft = strLeft.Left(nCommentLen);
			if (strLeft.Compare(strComment) == 0)
			{
				nPosComment = strSelText.Find(strComment, nPosPrior);
				if (nPosComment != -1)
				{
					strSelText.Delete(nPosComment, nCommentLen);
					nPos -= nCommentLen;
					bModify = TRUE;
				}
			}
			nPosPrior = nPos + 1;
			nPos = strSelText.Find(g_chEOL, nPosPrior);
			if (-1 == nPos)
			{
				if (nPosPrior < strSelText.GetLength())
				{
					nPos = strSelText.GetLength();
				}
			}
		}

		if (bModify)
		{
			SetLastUndoReason(g_dwUATUncomment);
			ReplaceSel(strSelText, TRUE);
		}
	}
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditCtrl::ReplaceTextToFormatter( BOOL bAllText /*= TRUE*/ )
{
	if (bAllText)
	{
		SetSel2(0, -1, TRUE, FALSE);
	}
	CString strSelText(GetSelText());
	if (strSelText.IsEmpty())
	{
		return;
	}


	CT2A strTextIn(strSelText, GetACP());	
	CString strTextOut, strMsgOut;
	CFormatterHelp formatterSP;
	if (formatterSP.DoFormatter(m_SynLanguage.GetCurLanguage(), strTextIn, strTextOut, strMsgOut))
	{
		SetLastUndoReason(g_dwUATFormatter);
		DeleteSelectedText (FALSE, FALSE, TRUE);
		if (!globalData.bIsWindowsVista) //XP的时候
		{
			if (theApp.m_bChangedLang)
			{
				strTextOut = CA2T(CT2A(strTextOut), GetACP());
			}
		}
		InsertText (strTextOut, m_nCurrOffset, FALSE);
		if (bAllText)
		{
			SetSel2(0, 0, FALSE);
		}
		else
		{
			RedrawWindow ();
		}
	}
	else
	{
		if (bAllText)
		{
			SetSel2(0, 0, FALSE);
		}
	}
	
	CChildFrame *pFrame = ((CChildFrame *)((CView *)GetParent())->GetParentFrame());
	if (pFrame != NULL)
	{
		pFrame->AddOutputMsg(strMsgOut);
	}
}
void CSynBCGPEditCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	const BOOL bShift = ::GetAsyncKeyState (VK_SHIFT) & 0x8000;
	const BOOL bCtrl = ::GetAsyncKeyState (VK_CONTROL) & 0x8000;
	const BOOL bAlt = ::GetAsyncKeyState (VK_MENU) & 0x8000;
	if (bShift && !bCtrl && !bAlt)
	{
		SetRedraw(FALSE);
	}
	
	int iStartSel = -1;
	int iEndSel = -1;

	iStartSel = min (m_iEndSel, m_iStartSel);
	iEndSel = max (m_iEndSel, m_iStartSel);
	if (-1 == iStartSel)
	{
		iStartSel = m_nCurrOffset;
		iEndSel = m_nCurrOffset;
	}
	BOOL bStartCart = iStartSel == m_nCurrOffset? TRUE:FALSE;

	CBCGPEditCtrl::OnLButtonDown(nFlags, point);
	
	if (bShift && !bCtrl && !bAlt)
	{
		int iStartSel2 = m_nCurrOffset;
		int iEndSel2 = m_nCurrOffset;
		int nStartSel = -1;
		int nEndSel = -1;
		if (iStartSel < iEndSel2)
		{
			nStartSel = bStartCart ? iEndSel : iStartSel;
			nEndSel = iEndSel2;
		} 
		else
		{
			nEndSel = iStartSel2;
			nStartSel = bStartCart ? iEndSel : iStartSel;
		}

		if (m_strBuffer.IsEmpty ())
		{
			return;
		}

		if (nStartSel == -1)
		{
			m_iStartSel = m_iEndSel = -1;			
		}

		if (nStartSel < 0)
		{
			nStartSel = 0;
		}

		if (nEndSel == -1)
		{
			nEndSel = m_strBuffer.GetLength ();
		}

		if (nEndSel > m_strBuffer.GetLength ())
		{
			nEndSel = m_strBuffer.GetLength ();
		}

		m_iStartSel = nStartSel;
		m_iEndSel = nEndSel;

		SetRedraw(TRUE);
		RedrawWindow ();
	}
}
