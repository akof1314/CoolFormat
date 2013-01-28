// SynHtmlView.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SynHtmlView.h"


// CSynHtmlView

IMPLEMENT_DYNCREATE(CSynHtmlView, CHtmlView)

CSynHtmlView::CSynHtmlView()
:m_strHtmlSrc(_T(""))
,m_strHtmlCode(_T(""))
{
	glpDisp = NULL;
}

CSynHtmlView::~CSynHtmlView()
{
}

void CSynHtmlView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSynHtmlView, CHtmlView)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CSynHtmlView::OnEditSelectAll)
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_SAVE, &CSynHtmlView::OnFileSave)
	ON_COMMAND(ID_COPY_HTMLSRC, &CSynHtmlView::OnCopyHtmlsrc)
	ON_COMMAND(ID_FILE_SAVE_AS, &CSynHtmlView::OnFileSaveAs)
	ON_COMMAND(ID_EDIT_COPY, &CSynHtmlView::OnEditCopy)
END_MESSAGE_MAP()

// CSynHtmlView 诊断

#ifdef _DEBUG
void CSynHtmlView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CSynHtmlView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG


// CSynHtmlView 消息处理程序

void CSynHtmlView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
}

BOOL CSynHtmlView::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_RBUTTONDOWN)
	{
		CPoint point(pMsg->pt);
		theApp.ShowPopupMenu (IDR_HTML_CONTEXT_MENU, point, this);
		return TRUE;
	}
	else if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == 65)			//全选
		{
			if ((GetKeyState(VK_CONTROL) & 0x8000))
			{
				ExecWB(OLECMDID_SELECTALL, OLECMDEXECOPT_DONTPROMPTUSER, NULL, NULL);
				return TRUE;
			} 
		}
	}

	return CHtmlView::PreTranslateMessage(pMsg);
}

void CSynHtmlView::OnEditSelectAll()
{
	ExecWB(OLECMDID_SELECTALL, OLECMDEXECOPT_DONTPROMPTUSER, NULL, NULL);
}

void CSynHtmlView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (::IsWindow(m_wndBrowser.m_hWnd))
	{
		// need to push non-client borders out of the client area
		CRect rect;
		GetClientRect(rect);
		::AdjustWindowRectEx(rect,
			GetStyle(), FALSE, WS_EX_CLIENTEDGE);
		m_wndBrowser.SetWindowPos(NULL, rect.left, rect.top,
			rect.Width(), rect.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}
}
//////////////////////////////////////////////////////////////////////////
void CSynHtmlView::OnFileSave()
{
	TCHAR szPath[MAX_PATH];
	LPCTSTR pszFilter=_T("Html Files(*.html)|*.html|All Files(*.*)|*.*||");
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_EXTENSIONDIFFERENT;

	CString strDefault = GetDocument()->GetTitle();
	strDefault.Remove('*');
	strDefault = strDefault.Trim();
	CFileDialog dlg(FALSE, NULL, strDefault + _T(".html"), dwFlags, pszFilter, NULL);		
	if( dlg.DoModal() == IDOK )
	{
		CString strTemp = dlg.GetPathName();			
		switch (dlg.m_ofn.nFilterIndex)
		{		
		case 1:	
			{
				if (!dlg.GetFileExt().CompareNoCase(_T("html"))){}
				else
					strTemp += _T(".html");
			}
			break;		
		default: break;
		}										
		lstrcpy(szPath, strTemp.GetBuffer(0));
		CString lpszPathName = szPath;

		CFile mFile2(lpszPathName, CFile::modeWrite|CFile::modeCreate);
		CT2A strHtml(m_strHtmlSrc, GetACP());
		mFile2.Write(strHtml, strlen(strHtml));
		mFile2.Flush();
		mFile2.Close();
	}
	else
		return ;
}
//////////////////////////////////////////////////////////////////////////
void CSynHtmlView::OnCopyHtmlsrc()
{
	ExecWB(OLECMDID_SELECTALL, OLECMDEXECOPT_DONTPROMPTUSER, NULL, NULL);
	CopyHtmlSrcToClip(m_strHtmlSrc);
}
//////////////////////////////////////////////////////////////////////////
void CSynHtmlView::OnFileSaveAs()
{
	OnFileSave();
}
//////////////////////////////////////////////////////////////////////////
BOOL CSynHtmlView::ShowCodeToHtml( const CString &strHtml, const CString &strCode, const CString &strLang, int iLineCount, BOOL bAlreadyShow /*= FALSE*/ )
{
	m_strHtmlCode = strCode;
	m_strHtmlCode.Replace(_T("\n"), _T("\r\n"));
	MakeCodeToHtml(strHtml, strLang, iLineCount);
	Navigate(_T("about:blank"), NULL, NULL, NULL, NULL);
	if (g_GlobalUtils.m_sStyleScheme.m_bHtmlAutoCopy)
	{
		if (g_GlobalUtils.m_sStyleScheme.m_bHtmlCopyCode)
		{
			CopyHtmlSrcToClip(m_strHtmlSrc);
		}
		else
		{
			CopyHtmlToClip(m_strHtmlSrc, m_strHtmlCode);
		}
	}
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
void CSynHtmlView::MakeCodeToHtml( const CString& strCode, const CString &strLang, int iLineCount )
{
	m_strHtmlSrc = _T("<!-- CoolFormat Source Formatter http://blog.csdn.net/akof1314 -->");

	// 1)添加边框
	if (g_GlobalUtils.m_sStyleScheme.m_bHtmlShowBorder)
	{
		m_strHtmlSrc.AppendFormat(_T("<div style=\"width:100%%;border:%dpx #%0.2x%0.2x%0.2x "), 
			g_GlobalUtils.m_sStyleScheme.m_iHtmlBorderWidth, 
			GetRValue(g_GlobalUtils.m_sStyleScheme.m_clrHtmlBorderColor), GetGValue(g_GlobalUtils.m_sStyleScheme.m_clrHtmlBorderColor), GetBValue(g_GlobalUtils.m_sStyleScheme.m_clrHtmlBorderColor));
		switch (g_GlobalUtils.m_sStyleScheme.m_iHtmlBorderStyle)
		{
		case 0: m_strHtmlSrc.Append(_T("none"));break;
		case 1: m_strHtmlSrc.Append(_T("solid"));break;
		case 2: m_strHtmlSrc.Append(_T("dashed"));break;
		case 3: m_strHtmlSrc.Append(_T("dotted"));break;
		case 4: m_strHtmlSrc.Append(_T("double"));break;
		case 5: m_strHtmlSrc.Append(_T("groove"));break;
		case 6: m_strHtmlSrc.Append(_T("ridge"));break;
		case 7: m_strHtmlSrc.Append(_T("inset"));break;
		case 8: m_strHtmlSrc.Append(_T("outset"));break;
		}
		m_strHtmlSrc.Append(_T(";\">"));
	}

	// 2)添加语言标题或附加标题
	if (g_GlobalUtils.m_sStyleScheme.m_bHtmlShowLangTitle || g_GlobalUtils.m_sStyleScheme.m_bHtmlShowAddTitle)
	{
		CString strTitle = _T("");
		if (g_GlobalUtils.m_sStyleScheme.m_bHtmlShowLangTitle)
		{
			strTitle.AppendFormat(_T("%s Code&nbsp;"), strLang);
		}
		if (g_GlobalUtils.m_sStyleScheme.m_bHtmlShowAddTitle)
		{
			strTitle.Append(g_GlobalUtils.m_sStyleScheme.m_strHtmlAddTitle);
		}
		m_strHtmlSrc.AppendFormat(_T("<div style=\"width:100%%;font-family:'%s', 'Courier New';font-size:%dpx;border-bottom:1px solid #%0.2x%0.2x%0.2x;margin-top:5px;color:#%0.2x%0.2x%0.2x;\">&nbsp;%s</div>"), 
			g_GlobalUtils.m_sStyleScheme.m_strHtmlFontName, g_GlobalUtils.m_sStyleScheme.m_uHtmlFontSize,
			GetRValue(g_GlobalUtils.m_sStyleScheme.m_clrHtmlBorderColor), GetGValue(g_GlobalUtils.m_sStyleScheme.m_clrHtmlBorderColor), GetBValue(g_GlobalUtils.m_sStyleScheme.m_clrHtmlBorderColor),
			GetRValue(g_GlobalUtils.m_sColorScheme.m_clrText), GetGValue(g_GlobalUtils.m_sColorScheme.m_clrText), GetBValue(g_GlobalUtils.m_sColorScheme.m_clrText),
			strTitle);
	}

	// 3)添加表格布局
	m_strHtmlSrc.AppendFormat(_T("<table style=\"width:100%%;font-family:'%s', 'Courier New';font-size:%dpx;vertical-align:text-top;line-height:%dpx;\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\"><tr>"),
		g_GlobalUtils.m_sStyleScheme.m_strHtmlFontName, g_GlobalUtils.m_sStyleScheme.m_uHtmlFontSize, g_GlobalUtils.m_sStyleScheme.m_iHtmlLineHeight, g_GlobalUtils.m_sStyleScheme.m_clrHtmlBackgroundColor);
	
	// 4)添加行号
	if (g_GlobalUtils.m_sStyleScheme.m_bHtmlShowLineNumber)
	{
		m_strHtmlSrc.AppendFormat(_T("<td style=\"color:#%0.2x%0.2x%0.2x;background-color:#%0.2x%0.2x%0.2x;vertical-align:text-top;\"><div style=\"margin:7px;text-align:right;white-space:nowrap;\"><nobr>"), 
			GetRValue(g_GlobalUtils.m_sColorScheme.m_clrTextLineNumber), GetGValue(g_GlobalUtils.m_sColorScheme.m_clrTextLineNumber), GetBValue(g_GlobalUtils.m_sColorScheme.m_clrTextLineNumber), 
			GetRValue(g_GlobalUtils.m_sColorScheme.m_clrBackLineNumber), GetGValue(g_GlobalUtils.m_sColorScheme.m_clrBackLineNumber), GetBValue(g_GlobalUtils.m_sColorScheme.m_clrBackLineNumber));
		for (int i = 1; i <= iLineCount; ++i)
		{
			m_strHtmlSrc.AppendFormat(_T("%d<br>"), i);
		}
		m_strHtmlSrc.Append(_T("</nobr></div></td>"));
	}

	// 5)添加分割线
	if (g_GlobalUtils.m_sStyleScheme.m_bHtmlShowSidebar)
	{
		m_strHtmlSrc.AppendFormat(_T("<td style=\"background-color:#%0.2x%0.2x%0.2x;padding:1px;\"><div style=\"border:1px #%0.2x%0.2x%0.2x solid;\"></div></td>"),
			GetRValue(g_GlobalUtils.m_sColorScheme.m_clrBackSidebar), GetGValue(g_GlobalUtils.m_sColorScheme.m_clrBackSidebar), GetBValue(g_GlobalUtils.m_sColorScheme.m_clrBackSidebar),
			GetRValue(g_GlobalUtils.m_sColorScheme.m_clrBackSidebar), GetGValue(g_GlobalUtils.m_sColorScheme.m_clrBackSidebar), GetBValue(g_GlobalUtils.m_sColorScheme.m_clrBackSidebar)
			);
	}

	// 6)添加代码行
	m_strHtmlSrc.AppendFormat(_T("<td style=\"background-color:#%0.2x%0.2x%0.2x;width:100%%;vertical-align:text-top;color:#%0.2x%0.2x%0.2x;\"><div style=\"margin:7px;\">"),
		GetRValue(g_GlobalUtils.m_sStyleScheme.m_clrHtmlBackgroundColor), GetGValue(g_GlobalUtils.m_sStyleScheme.m_clrHtmlBackgroundColor), GetBValue(g_GlobalUtils.m_sStyleScheme.m_clrHtmlBackgroundColor),
		GetRValue(g_GlobalUtils.m_sColorScheme.m_clrText), GetGValue(g_GlobalUtils.m_sColorScheme.m_clrText), GetBValue(g_GlobalUtils.m_sColorScheme.m_clrText));
	m_strHtmlSrc.Append(strCode);
	m_strHtmlSrc.Append(_T("</div></td></tr></table>"));
	if (g_GlobalUtils.m_sStyleScheme.m_bHtmlShowBorder)
	{
		m_strHtmlSrc.Append(_T("</div>"));
	}
}
//////////////////////////////////////////////////////////////////////////
BOOL CSynHtmlView::CopyHtmlToClip( const CString &strHtml, const CString &strCode )
{
	// 1)转换成UTF-8
	CW2A pszU8(CT2W(strHtml), CP_UTF8);
	int nHtmlSrcLen = strlen(pszU8);

	// 2)组成剪贴板片段
	CStringA strHtmlClip;
	strHtmlClip.Format("Version:0.9\r\n"
		"StartHTML:%08u\r\n"
		"EndHTML:%08u\r\n"
		"StartFragment:%08u\r\n"
		"EndFragment:%08u\r\n"
		"<html><body>\r\n"
		"<!--StartFragment -->\r\n"
		"%s\r\n"
		"<!--EndFragment-->\r\n"
		"</body></html>",
		97, 172 + nHtmlSrcLen, 111, 136 + nHtmlSrcLen, pszU8);

	// 3)剪贴板操作
	static int cfid = 0;
	if(!cfid)
	{
		cfid = RegisterClipboardFormat(_T("HTML Format"));
	}

	if (!OpenClipboard())
	{
		return FALSE;
	}

	if (!EmptyClipboard())
	{
		CloseClipboard();
		return FALSE;
	}

	HGLOBAL hClipBuffer = GlobalAlloc(GMEM_DDESHARE, strHtmlClip.GetLength() + 1);
	if (hClipBuffer == NULL)
	{
		CloseClipboard();
		return FALSE;
	}

	char *lpExpBuffer = (char *)GlobalLock(hClipBuffer);
	if (lpExpBuffer == NULL)
	{
		GlobalFree(hClipBuffer);
		CloseClipboard();
		return FALSE;
	}

	memcpy(lpExpBuffer, strHtmlClip, strHtmlClip.GetLength());
	lpExpBuffer[strHtmlClip.GetLength()] = '\0';

	GlobalUnlock(hClipBuffer);
	SetClipboardData(cfid, hClipBuffer);

	HGLOBAL hClipBufferCode = GlobalAlloc(GMEM_DDESHARE, (strCode.GetLength() + 1) * sizeof(TCHAR));
	if (hClipBufferCode == NULL)
	{
		CloseClipboard();
		return FALSE;
	}

	TCHAR *lpExpBufferCode = (TCHAR *)GlobalLock(hClipBufferCode);
	if (lpExpBufferCode == NULL)
	{
		GlobalFree(hClipBufferCode);
		CloseClipboard();
		return FALSE;
	}

	memcpy(lpExpBufferCode, strCode, strCode.GetLength() * sizeof(TCHAR));
	lpExpBufferCode[strCode.GetLength()] = _T('\0');

	GlobalUnlock(hClipBufferCode);
	SetClipboardData(CF_UNICODETEXT, hClipBufferCode);
	CloseClipboard();    

	return TRUE;
}

void CSynHtmlView::OnEditCopy()
{
	ExecWB(OLECMDID_SELECTALL, OLECMDEXECOPT_DONTPROMPTUSER, NULL, NULL);
	CopyHtmlToClip(m_strHtmlSrc, m_strHtmlCode);
}

void CSynHtmlView::NavigateComplete2( LPDISPATCH pDisp, VARIANT* URL )
{
	ASSERT(V_VT(URL) == VT_BSTR);

	if (!glpDisp)
		glpDisp = pDisp;

	CString str(V_BSTR(URL));
	OnNavigateComplete2(str);
}

void CSynHtmlView::DocumentComplete( LPDISPATCH pDisp, VARIANT* URL )
{
	ASSERT(V_VT(URL) == VT_BSTR);

	if (glpDisp && glpDisp == pDisp)
	{
		// if the LPDISPATCH are same, that means
		// it is the final DocumentComplete. Reset glpDisp
		glpDisp = NULL;

		IHTMLDocument2 *document = NULL;
		GetHtmlDocument()->QueryInterface(IID_IHTMLDocument2, (void**)&document);    // Declared earlier in the code
		HRESULT hresult = S_OK;
		VARIANT *param;
		SAFEARRAY *sfArray;	
		do 
		{			
			BSTR bstr = m_strHtmlSrc.AllocSysString();
			// Creates a new one-dimensional array
			sfArray = SafeArrayCreateVector(VT_VARIANT, 0, 1);

			if (sfArray == NULL || document == NULL) {
				break;
			}

			hresult = SafeArrayAccessData(sfArray, (LPVOID*)&param);
			param->vt = VT_BSTR;
			param->bstrVal = bstr;
			hresult = SafeArrayUnaccessData(sfArray);
			hresult = document->write(sfArray);
		} while (0);

		//	SysFreeString(bstr);   //去掉这一句
		if (sfArray != NULL) {
			SafeArrayDestroy(sfArray);
		}
	}

	CString str(V_BSTR(URL));
	OnDocumentComplete(str);
}
//////////////////////////////////////////////////////////////////////////
BOOL CSynHtmlView::CopyHtmlSrcToClip( const CString &strHtml )
{
	//----------------------------------剪贴板操作-----------------------------------    
	if (!OpenClipboard ())
	{
		TRACE0("Can't open clipboard\n");
		return FALSE;
	}

	if (!::EmptyClipboard ())
	{
		TRACE0("Can't empty clipboard\n");
		::CloseClipboard ();
		return FALSE;
	}

	HGLOBAL hClipbuffer = ::GlobalAlloc (GMEM_DDESHARE, (strHtml.GetLength() + 1) * sizeof(TCHAR));
	if (hClipbuffer == NULL)
	{
		TRACE0("GlobalAlloc: out of memory\n");
		::CloseClipboard ();
		return FALSE;
	}

	LPTSTR lpExpBuffer = (LPTSTR) GlobalLock (hClipbuffer);
	if (lpExpBuffer == NULL)
	{
		TRACE0("GlobalLock: out of memory\n");
		GlobalFree (hClipbuffer);
		::CloseClipboard ();
		return FALSE;
	}

	memcpy (lpExpBuffer, strHtml, strHtml.GetLength() * sizeof(TCHAR));
	lpExpBuffer [strHtml.GetLength()] = _T ('\0');

	GlobalUnlock (hClipbuffer);
	SetClipboardData (CF_UNICODETEXT, hClipbuffer);

	::CloseClipboard ();
	return TRUE;
}