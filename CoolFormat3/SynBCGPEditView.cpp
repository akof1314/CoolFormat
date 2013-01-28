// SynBCGPEditView.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "MainFrm.h"

#include "SynBCGPEditView.h"
#include "CoolFormat3Doc.h"
#include "CoolFormat3View.h"
#include "GotoLineDlg.h"
#include "BCGEX\MyBCGPRibbonLabel.h"
#include "SynHtmlView.h"



//////////////////////////////////////////////////////////////////////////
// CSynBCGPEditView

IMPLEMENT_DYNCREATE(CSynBCGPEditView, CBCGPEditView)

CSynBCGPEditView::CSynBCGPEditView()
{
}

CSynBCGPEditView::~CSynBCGPEditView()
{

}

BEGIN_MESSAGE_MAP(CSynBCGPEditView, CBCGPEditView)
	ON_COMMAND(ID_EDIT_GOTO_LINE, &CSynBCGPEditView::OnEditGotoLine)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_STATUSBAR_PANE3, OnUpdateCursorPos)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_FASTFORMAT, &CSynBCGPEditView::OnFastformat)
	ON_COMMAND(ID_EDIT_HIDESELECTION, &CSynBCGPEditView::OnEditHideselection)
	ON_UPDATE_COMMAND_UI(ID_EDIT_HIDESELECTION, &CSynBCGPEditView::OnUpdateEditHideselection)
	ON_COMMAND(ID_EDIT_STOPHIDINGCURRENT, &CSynBCGPEditView::OnEditStophidingcurrent)
	ON_UPDATE_COMMAND_UI(ID_EDIT_STOPHIDINGCURRENT, &CSynBCGPEditView::OnUpdateEditStophidingcurrent)
	ON_COMMAND(ID_EDIT_TOGGLEOUTLINING, &CSynBCGPEditView::OnEditToggleoutlining)
	ON_UPDATE_COMMAND_UI(ID_EDIT_TOGGLEOUTLINING, &CSynBCGPEditView::OnUpdateEditToggleoutlining)
	ON_COMMAND(ID_EDIT_TOGGLEALLOUTLINING, &CSynBCGPEditView::OnEditTogglealloutlining)
	ON_UPDATE_COMMAND_UI(ID_EDIT_TOGGLEALLOUTLINING, &CSynBCGPEditView::OnUpdateEditTogglealloutlining)
	ON_COMMAND(ID_EDIT_COLLAPSETODEFINITIONS, &CSynBCGPEditView::OnEditCollapsetodefinitions)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COLLAPSETODEFINITIONS, &CSynBCGPEditView::OnUpdateEditCollapsetodefinitions)
	ON_COMMAND(ID_EDIT_STOPOUTLINING, &CSynBCGPEditView::OnEditStopoutlining)
	ON_UPDATE_COMMAND_UI(ID_EDIT_STOPOUTLINING, &CSynBCGPEditView::OnUpdateEditStopoutlining)
	ON_COMMAND(ID_LANG, &CSynBCGPEditView::OnLang)
	ON_COMMAND(ID_A_ACTIONSCRIPT, &CSynBCGPEditView::OnAActionscript)
	ON_COMMAND(ID_A_ADA, &CSynBCGPEditView::OnAAda)
	ON_COMMAND(ID_A_ASM, &CSynBCGPEditView::OnAAsm)
	ON_COMMAND(ID_A_ASP, &CSynBCGPEditView::OnAAsp)
	ON_COMMAND(ID_BATCH, &CSynBCGPEditView::OnBatch)
	ON_COMMAND(ID_C_COBOL, &CSynBCGPEditView::OnCCobol)
	ON_COMMAND(ID_C_C, &CSynBCGPEditView::OnCC)
	ON_COMMAND(ID_C_C32893, &CSynBCGPEditView::OnCC32893)
	ON_COMMAND(ID_C_CSS, &CSynBCGPEditView::OnCCss)
	ON_COMMAND(ID_D, &CSynBCGPEditView::OnD)
	ON_COMMAND(ID_FORTRAN, &CSynBCGPEditView::OnFortran)
	ON_COMMAND(ID_H_HASKELL, &CSynBCGPEditView::OnHHaskell)
	ON_COMMAND(ID_H_HTML, &CSynBCGPEditView::OnHHtml)
	ON_COMMAND(ID_INI, &CSynBCGPEditView::OnIni)
	ON_COMMAND(ID_J_JAVA, &CSynBCGPEditView::OnJJava)
	ON_COMMAND(ID_J_JAVASCRIPT, &CSynBCGPEditView::OnJJavascript)
	ON_COMMAND(ID_J_JSON, &CSynBCGPEditView::OnJJson)
	ON_COMMAND(ID_J_JSP, &CSynBCGPEditView::OnJJsp)
	ON_COMMAND(ID_L_LISP, &CSynBCGPEditView::OnLLisp)
	ON_COMMAND(ID_L_LUA, &CSynBCGPEditView::OnLLua)
	ON_COMMAND(ID_NORMALTEXT, &CSynBCGPEditView::OnNormaltext)
	ON_COMMAND(ID_OBJECTIVE, &CSynBCGPEditView::OnObjective)
	ON_COMMAND(ID_P_PASCAL, &CSynBCGPEditView::OnPPascal)
	ON_COMMAND(ID_P_PERL, &CSynBCGPEditView::OnPPerl)
	ON_COMMAND(ID_P_PHP, &CSynBCGPEditView::OnPPhp)
	ON_COMMAND(ID_P_PYTHON, &CSynBCGPEditView::OnPPython)
	ON_COMMAND(ID_RUBY, &CSynBCGPEditView::OnRuby)
	ON_COMMAND(ID_SQL, &CSynBCGPEditView::OnSql)
	ON_COMMAND(ID_V_VB, &CSynBCGPEditView::OnVVb)
	ON_COMMAND(ID_V_VERILOG, &CSynBCGPEditView::OnVVerilog)
	ON_COMMAND(ID_V_VHDL, &CSynBCGPEditView::OnVVhdl)
	ON_COMMAND(ID_XML, &CSynBCGPEditView::OnXml)
	ON_COMMAND(ID_A_AUTOHOTKEY, &CSynBCGPEditView::OnAAutohotkey)
	ON_COMMAND(ID_A_AUTOIT, &CSynBCGPEditView::OnAAutoit)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSynBCGPEditView::OnFilePrintPreview)
	ON_COMMAND(ID_HTMLTOBLOG, &CSynBCGPEditView::OnHtmltoblog)
	ON_COMMAND(ID_INDENT_ADD, &CSynBCGPEditView::OnIndentAdd)
	ON_COMMAND(ID_INDENT_MIN, &CSynBCGPEditView::OnIndentMin)
	ON_COMMAND(ID_COMMENT_DO, &CSynBCGPEditView::OnCommentDo)
	ON_COMMAND(ID_COMMENT_NOT, &CSynBCGPEditView::OnCommentNot)
	ON_COMMAND(ID_SELFORMAT, &CSynBCGPEditView::OnSelformat)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CSynBCGPEditView 绘图

void CSynBCGPEditView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// CSynBCGPEditView 诊断

#ifdef _DEBUG
void CSynBCGPEditView::AssertValid() const
{
	CBCGPEditView::AssertValid();
}

#ifndef _WIN32_WCE
void CSynBCGPEditView::Dump(CDumpContext& dc) const
{
	CBCGPEditView::Dump(dc);
}
#endif
#endif //_DEBUG


void CSynBCGPEditView::OnInitialUpdate()
{
	CBCGPEditView::OnInitialUpdate();

	//m_pEdit->SelectLanguage(8);
	m_pEdit->UpdateAutoOutlining();
}

CBCGPEditCtrl* CSynBCGPEditView::CreateEdit()
{
	m_pEdit = new CSynBCGPEditCtrl;

	return m_pEdit;
}
//////////////////////////////////////////////////////////////////////////
BOOL CSynBCGPEditView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_RBUTTONDOWN)
	{
		CPoint point(pMsg->pt);
		theApp.ShowPopupMenu (IDR_EDIT_CONTEXT_MENU, point, this);
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == 65)			//全选
		{
			if ((GetKeyState(VK_CONTROL) & 0x8000))
			{
				this->GetEditCtrl()->SetSel(0, -1);
				return TRUE;
			} 
		}
		else if (pMsg->wParam == 70)	//查找
		{
			if ((GetKeyState(VK_CONTROL) & 0x8000))
			{
				if (!this->GetEditCtrl()->GetText().IsEmpty())
				{
					this->OnEditFind();				
				}
				return TRUE;
			}
		}
		else if (pMsg->wParam == 72)	//替换
		{
			if ((GetKeyState(VK_CONTROL) & 0x8000))
			{
				if (!this->GetEditCtrl()->GetText().IsEmpty())
				{
					this->OnEditReplace();
				}
				return TRUE;
			}
		}
		else if (pMsg->wParam == VK_F3)	//重复查找/替换
		{
			if ((GetKeyState(VK_SHIFT) & 0x8000))
			{
				m_dwFindMask &= ~FR_DOWN;
				if (m_pFindDlg != NULL && !m_pFindDlg->IsTerminating())
				{
					m_pFindDlg->m_fr.Flags &= ~FR_DOWN;
				}
			}
			else
			{
				m_dwFindMask |= FR_DOWN;
				if (m_pFindDlg != NULL && !m_pFindDlg->IsTerminating())
				{
					m_pFindDlg->m_fr.Flags |= FR_DOWN;
				}
			}
			OnFindReplace(0, 0);
			return TRUE;		
		}
	}

	return CBCGPEditView::PreTranslateMessage(pMsg);
}
//////////////////////////////////////////////////////////////////////////
BOOL CSynBCGPEditView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	((CCoolFormat3View *)GetParent()->GetParent())->GetDocument()->SetModifiedFlag(GetEditCtrl()->IsModified());
	((CCoolFormat3View *)GetParent()->GetParent())->GetDocument()->CheckTitle();

	return CBCGPEditView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditView::OnEditGotoLine()
{
	CGotoLineDlg goDlg(this, GetEditCtrl()->GetLineCount());
	if (goDlg.DoModal() != IDOK)
	{
		return;
	}

	GetEditCtrl()->GoToLine(goDlg.m_nLineNumber);
}
//////////////////////////////////////////////////////////////////////////
int CSynBCGPEditView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
// 	if (CBCGPEditView::OnCreate(lpCreateStruct) == -1)
// 		return -1;
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pWndEditCtrl = CreateEdit ();
	if (m_pWndEditCtrl == NULL)
	{
		TRACE0("CBCGPEditView::OnCreate: edit control is not created\n");
		return -1;
	}

	ASSERT_VALID (m_pWndEditCtrl);
	ASSERT (m_pWndEditCtrl->IsKindOf (RUNTIME_CLASS (CBCGPEditCtrl)));

	if (!m_pWndEditCtrl->Create (WS_CHILD, CRect (0, 0, 0, 0), this, 1))
	{
		TRACE0("CBCGPEditView::OnCreate: cannot create edit control\n");
		return -1;
	}

	ResetDefaultFont();
	m_pEdit->EnableOutlining(TRUE);
	m_pEdit->EnableAutoOutlining(TRUE);
	m_pEdit->EnableOutlineParser(TRUE);
	m_pEdit->EnableHyperlinkSupport(TRUE);
	m_pEdit->EnableToolTips(TRUE);

	m_pEdit->m_bEnableCurrentLineCopy = TRUE;

	//超链接颜色关闭
	m_pEdit->SetHyperlinkColor(FALSE);

	DisableMainframeForFindDlg(FALSE);

	return 0;
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditView::OnUpdateCursorPos( CCmdUI *pCmdUI )
{
	CBCGPRibbonStatusBar* pStatusBar = ((CMainFrame*) GetTopLevelFrame ())->GetRibbonStatusBar ();
	CBCGPRibbonStatusBarPane* pCursorPos = DYNAMIC_DOWNCAST (
		CBCGPRibbonStatusBarPane,
		pStatusBar->FindElement (ID_STATUSBAR_PANE3));
	ASSERT_VALID (pCursorPos);

	CString strCursorPos, strTemp;
	BOOL bNameValid = strTemp.LoadString(IDS_STATUS_ROWCOL);
	ASSERT(bNameValid);
	strCursorPos.Format (strTemp, m_pEdit->GetCurRow() + 1, m_pEdit->GetCurColumn() + 1);

	pCursorPos->SetText (strCursorPos);
	pCursorPos->Redraw ();
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditView::GetUndoActions( CStringList& lstActions ) const
{
	CDWordArray dwaUAT;
	m_pEdit->GetUndoActions(dwaUAT);

	lstActions.RemoveAll();

	int nIndex = (int)dwaUAT.GetSize();
	if ( nIndex != 0)
	{
		CString strAction;

		while (nIndex--)
		{
			strAction.Empty();

			switch (dwaUAT.GetAt(nIndex) & UAT_REASON) 
			{
			case g_dwUATUndefined:
				strAction.LoadString(IDS_STRING_UAT_UNDEF);
				break;

			case g_dwUATTyping:
				strAction.LoadString(IDS_STRING_UAT_TYPE);
				break;

			case g_dwUATCut:
				strAction.LoadString(IDS_STRING_UAT_CUT);
				break;

			case g_dwUATPaste:
				strAction.LoadString(IDS_STRING_UAT_PASTE);
				break;

			case g_dwUATDelete:
				strAction.LoadString(IDS_STRING_UAT_DEL);
				break;

			case g_dwUATBackspace:
				strAction.LoadString(IDS_STRING_UAT_BACK);
				break;

			case g_dwUATDragDrop:
				strAction.LoadString(IDS_STRING_UAT_DRAG);
				break;

			case g_dwUATEnter:
				strAction.LoadString(IDS_STRING_UAT_ENTER);
				break;

			case g_dwUATIndent:
				strAction.LoadString(IDS_STRING_UAT_INDENT);
				break;		

			case g_dwUATUnindent:
				strAction.LoadString(IDS_STRING_UAT_UNINDENT);
				break;

			case g_dwUATTab:
				strAction.LoadString(IDS_STRING_UAT_TAB);
				break;		

			case g_dwUATReplace:
				strAction.LoadString(IDS_STRING_UAT_REP);
				break;
			case g_dwUATComment:
				strAction.LoadString(IDS_STRING_UAT_COMM);
				break;
			case g_dwUATUncomment:
				strAction.LoadString(IDS_STRING_UAT_UNCOMM);
				break;
			case g_dwUATFormatter:
				strAction.LoadString(IDS_STRING_UAT_TIDY);
				break;
			default:
				strAction.LoadString(IDS_STRING_UAT_UNDEF);
			}			

			if (strAction.IsEmpty())
			{
				ASSERT(FALSE);
				strAction = _T("<?>");
			}

			lstActions.AddHead(strAction);
		}
	}
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditView::OnEditUndo()
{
	 CBCGPRibbonBar *pRibbon = ((CMainFrame*) GetTopLevelFrame())->GetRibbonBar();
	 ASSERT_VALID(pRibbon);

	 CBCGPRibbonUndoButton *pEditUndo = DYNAMIC_DOWNCAST(CBCGPRibbonUndoButton, pRibbon->FindByID(ID_EDIT_UNDO));
	 ASSERT_VALID(pEditUndo);

	 int nActionNumber = pEditUndo->GetActionNumber();

	 if (-1 == nActionNumber)
	 {
		 m_pEdit->OnUndo();
		 return;
	 }

	 for (int i = 0; i < nActionNumber; i++)
	 {
		 if (!m_pEdit->OnUndo())
		 {
			 break;
		 }
	 }
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditView::OnFastformat()
{
	m_pEdit->ReplaceTextToFormatter(TRUE);
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditView::ResetDefaultFont()
{
	HFONT hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
	CDC* pDC = GetDC();

	CFont* pFont = pDC->SelectObject(CFont::FromHandle(hFont));
	pDC->SelectObject(pFont);
	::DeleteObject(hFont);

	LOGFONT lf;
	pFont->GetLogFont (&lf);

	CString strFontName(g_GlobalUtils.m_sStyleScheme.m_strEdtFontName);
	CopyMemory(lf.lfFaceName,(LPCTSTR)strFontName,(strFontName.GetLength() + 1) * sizeof(TCHAR));
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = g_GlobalUtils.m_sStyleScheme.m_bEdtFontBold ? FW_BOLD : FW_NORMAL;
	lf.lfItalic = g_GlobalUtils.m_sStyleScheme.m_bEdtFontItalic ? 1 : 0;
	lf.lfUnderline = 0;
	lf.lfStrikeOut = 0;
	lf.lfHeight = -MulDiv(g_GlobalUtils.m_sStyleScheme.m_uEdtFontSize, GetDeviceCaps(pDC->GetSafeHdc(), LOGPIXELSY), 72);
	lf.lfOutPrecision =	3;
	lf.lfClipPrecision = 2;
	lf.lfQuality = 1;
	lf.lfPitchAndFamily = 49;
	lf.lfCharSet = 0;

	LOGFONT glf;
	globalData.fontRegular.GetLogFont (&glf);
	CString strFaceName(glf.lfFaceName);
	if (0 == strFaceName.CompareNoCase(_T("微软雅黑")))
	{
		lf.lfQuality = 5;
	}

	m_Font.CreateFontIndirect(&lf);
	m_pEdit->SetFont (&m_Font);
}

void CSynBCGPEditView::OnEditHideselection()
{
	m_pEdit->HideSelection();
}

void CSynBCGPEditView::OnUpdateEditHideselection(CCmdUI *pCmdUI)
{
	int nStart = 0;
	int nEnd = 0;
	m_pEdit->GetSel(nStart, nEnd);

	pCmdUI->Enable(
		nStart >= 0 && nEnd >= 0 && (nStart != nEnd) &&
		m_pEdit->IsOutliningEnabled() &&
		!m_pEdit->IsAutoOutliningEnabled());
}

void CSynBCGPEditView::OnEditStophidingcurrent()
{
	m_pEdit->StopHidingCurrent();
}

void CSynBCGPEditView::OnUpdateEditStophidingcurrent(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(
		m_pEdit->IsOutliningEnabled() &&
		!m_pEdit->IsAutoOutliningEnabled());
}

void CSynBCGPEditView::OnEditToggleoutlining()
{
	m_pEdit->ToggleOutlining();
}

void CSynBCGPEditView::OnUpdateEditToggleoutlining(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pEdit->IsOutliningEnabled());
}

void CSynBCGPEditView::OnEditTogglealloutlining()
{
	m_pEdit->ToggleAllOutlining();
}

void CSynBCGPEditView::OnUpdateEditTogglealloutlining(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pEdit->IsOutliningEnabled());
}

void CSynBCGPEditView::OnEditCollapsetodefinitions()
{
	m_pEdit->CollapseToDefinitions();
}

void CSynBCGPEditView::OnUpdateEditCollapsetodefinitions(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pEdit->IsOutliningEnabled());
}

void CSynBCGPEditView::OnEditStopoutlining()
{
		m_pEdit->StopOutlining();
}

void CSynBCGPEditView::OnUpdateEditStopoutlining(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(
		m_pEdit->IsOutliningEnabled() &&
		m_pEdit->IsAutoOutliningEnabled());
}

void CSynBCGPEditView::OnLang()
{
	// TODO: 在此添加命令处理程序代码
}

void CSynBCGPEditView::OnAActionscript()
{
	m_pEdit->SelectLanguage(SYN_ACTIONSCRIPT);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnAAda()
{
	m_pEdit->SelectLanguage(SYN_ADA);
	ReSetLangLabel(); 
}

void CSynBCGPEditView::OnAAsm()
{
	m_pEdit->SelectLanguage(SYN_ASM);
	ReSetLangLabel(); 
}

void CSynBCGPEditView::OnAAsp()
{
	m_pEdit->SelectLanguage(SYN_ASP);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnAAutohotkey()
{
	m_pEdit->SelectLanguage(SYN_AUTOHOTKEY);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnAAutoit()
{
	m_pEdit->SelectLanguage(SYN_AUTOIT);
	ReSetLangLabel();
}
void CSynBCGPEditView::OnBatch()
{
	m_pEdit->SelectLanguage(SYN_BATCH);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnCCobol()
{
	m_pEdit->SelectLanguage(SYN_COBOL);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnCC()
{
	m_pEdit->SelectLanguage(SYN_CPP);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnCC32893()
{
	m_pEdit->SelectLanguage(SYN_CS);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnCCss()
{
	m_pEdit->SelectLanguage(SYN_CSS);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnD()
{
	m_pEdit->SelectLanguage(SYN_D);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnFortran()
{
	m_pEdit->SelectLanguage(SYN_FORTRAN);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnHHaskell()
{
	m_pEdit->SelectLanguage(SYN_HASKELL);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnHHtml()
{
	m_pEdit->SelectLanguage(SYN_HTML);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnIni()
{
	m_pEdit->SelectLanguage(SYN_INI);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnJJava()
{
	m_pEdit->SelectLanguage(SYN_JAVA);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnJJavascript()
{
	m_pEdit->SelectLanguage(SYN_JAVASCRIPT);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnJJson()
{
	m_pEdit->SelectLanguage(SYN_JSON);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnJJsp()
{
	m_pEdit->SelectLanguage(SYN_JSP);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnLLisp()
{
	m_pEdit->SelectLanguage(SYN_LISP);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnLLua()
{
	m_pEdit->SelectLanguage(SYN_LUA);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnNormaltext()
{
	m_pEdit->SelectLanguage(SYN_NORMALTEXT);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnObjective()
{
	m_pEdit->SelectLanguage(SYN_OBJECTIVEC);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnPPascal()
{
	m_pEdit->SelectLanguage(SYN_PASCAL);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnPPerl()
{
	m_pEdit->SelectLanguage(SYN_PERL);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnPPhp()
{
	m_pEdit->SelectLanguage(SYN_PHP);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnPPython()
{
	m_pEdit->SelectLanguage(SYN_PYTHON);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnRuby()
{
	m_pEdit->SelectLanguage(SYN_RUBY);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnSql()
{
	m_pEdit->SelectLanguage(SYN_SQL);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnVVb()
{
	m_pEdit->SelectLanguage(SYN_VB);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnVVerilog()
{
	m_pEdit->SelectLanguage(SYN_VERILOG);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnVVhdl()
{
	m_pEdit->SelectLanguage(SYN_VHDL);
	ReSetLangLabel();
}

void CSynBCGPEditView::OnXml()
{
	m_pEdit->SelectLanguage(SYN_XML);
	ReSetLangLabel();
}

void CSynBCGPEditView::ReSetLangLabel()
{
	CBCGPRibbonBar *pRibbonBar = ((CMainFrame*)GetTopLevelFrame())->GetRibbonBar();
	ASSERT_VALID(pRibbonBar);

	CMyBCGPRibbonLabel *pRibbonLabel = DYNAMIC_DOWNCAST(CMyBCGPRibbonLabel, pRibbonBar->FindByID(ID_NOW_LANG));
	if (pRibbonLabel)
	{
		CString strLabelText;
		strLabelText.Format(_T("%16s"), m_pEdit->GetSelectLangString());
		pRibbonLabel->SetTextEx(strLabelText);
		pRibbonLabel->Redraw();
	}
}

void CSynBCGPEditView::OnFilePrintPreview()
{
	CWnd *pWnd = GetParent();
	if (pWnd)
	{
		CCoolFormat3View *pView = (CCoolFormat3View *)pWnd->GetParent();
		if (!pView)
		{
			return;
		}

		if (pView->GetTabControl().GetVisibleTabsNum() == 2)
		{
			pView->GetTabControl().ShowTab(1, FALSE);
		}
		BCGPPrintPreview (this);
		if (pView->GetTabControl().GetTabsNum() == 2)
		{
			pView->GetTabControl().ShowTab(1, TRUE);
		}
	}	
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditView::LoadFont( void )
{
	CDC* pDC = GetDC();
	LOGFONT lf;
	m_pEdit->GetFont()->GetLogFont(&lf);

	CString strFontName(g_GlobalUtils.m_sStyleScheme.m_strEdtFontName);
	CopyMemory(lf.lfFaceName,(LPCTSTR)strFontName,(strFontName.GetLength() + 1) * sizeof(TCHAR));	
	lf.lfWeight = g_GlobalUtils.m_sStyleScheme.m_bEdtFontBold ? FW_BOLD : FW_NORMAL;
	lf.lfItalic = g_GlobalUtils.m_sStyleScheme.m_bEdtFontItalic ? 1 : 0;	
	lf.lfHeight = -MulDiv(g_GlobalUtils.m_sStyleScheme.m_uEdtFontSize, GetDeviceCaps(pDC->GetSafeHdc(), LOGPIXELSY), 72);

	m_Font.DeleteObject();
	m_Font.CreateFontIndirect(&lf);
	m_pEdit->SetFont (&m_Font);
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditView::OnHtmltoblog()
{
	CWnd *pParentWnd = GetParent();
	if (pParentWnd == NULL)
	{
		return;
	}
	pParentWnd = pParentWnd->GetParent();
	if (pParentWnd == NULL)
	{
		return;
	}

	CWaitCursor wait;
	BOOL bAlreadyShow = TRUE;
	CBCGPTabView *pTabView = (CBCGPTabView *)pParentWnd;
	if (pTabView->GetTabControl().GetTabsNum() == 1)
	{
		CString strTemp;
		BOOL bNameVaild = strTemp.LoadString(ID_TAB_HTML);
		ASSERT(bNameVaild);
		pTabView->AddView(RUNTIME_CLASS(CSynHtmlView), strTemp, ID_TAB_HTML);
		bAlreadyShow = FALSE;
	}
	pTabView->SetActiveView(1);
	CSynHtmlView *pHtmlView = (CSynHtmlView *)pTabView->GetActiveView();
	CString strCode;
	m_pEdit->ExportToMyHTML(strCode);
	pHtmlView->ShowCodeToHtml(strCode, m_pEdit->GetText(), m_pEdit->GetSelectLangString(), m_pEdit->GetLineCount(), bAlreadyShow);
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditView::OnIndentAdd()
{
	m_pEdit->IndentSelection(TRUE);
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditView::OnIndentMin()
{
	m_pEdit->IndentSelection(FALSE);
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditView::OnCommentDo()
{
	m_pEdit->InsertComment(TRUE);
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditView::OnCommentNot()
{
	m_pEdit->InsertComment(FALSE);
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditView::OnSelformat()
{
	m_pEdit->ReplaceTextToFormatter(FALSE);
}
//////////////////////////////////////////////////////////////////////////
void CSynBCGPEditView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (m_pWndEditCtrl->GetSafeHwnd () != NULL)
	{
		m_pWndEditCtrl->SetWindowPos (NULL, -1, -1, cx, cy - 1,
			SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

		if (!m_pWndEditCtrl->IsWindowVisible())
		{
			int nParentNum = 1;
			CWnd *pWndParent = GetParent();
			while (pWndParent != NULL)
			{
				if (4 <= nParentNum)
				{
					break;
				}
				pWndParent = pWndParent->GetParent();
				++nParentNum;
			}

			if (4 <= nParentNum)
			{
				CRect rcParent;
				pWndParent->GetClientRect(&rcParent);

				if (rcParent.right - cx <= 10 || rcParent.bottom - cy <= 29)
				{
					m_pWndEditCtrl->ShowWindow(SW_SHOW);
				}
			}
		}
	}
}
