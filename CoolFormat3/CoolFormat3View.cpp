// CoolFormat3View.cpp : implementation of the CCoolFormat3View class
//

#include "stdafx.h"
#include "CoolFormat3.h"

#include "CoolFormat3Doc.h"
#include "CoolFormat3View.h"

#include "ChildFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCoolFormat3View

IMPLEMENT_DYNCREATE(CCoolFormat3View, CBCGPTabView)

BEGIN_MESSAGE_MAP(CCoolFormat3View, CBCGPTabView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CBCGPTabView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CBCGPTabView::OnFilePrint)
	ON_WM_SETFOCUS()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CCoolFormat3View construction/destruction

CCoolFormat3View::CCoolFormat3View()
{
	m_DocIcon = NULL;
}

CCoolFormat3View::~CCoolFormat3View()
{
	if (m_DocIcon)
	{
		ASSERT(DestroyIcon(m_DocIcon));
	}
}

BOOL CCoolFormat3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGPTabView::PreCreateWindow(cs);
}

// CCoolFormat3View drawing

void CCoolFormat3View::OnDraw(CDC* /*pDC*/)
{
	CCoolFormat3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CCoolFormat3View printing

void CCoolFormat3View::OnFilePrintPreview()
{	
	BCGPPrintPreview (this);
}

BOOL CCoolFormat3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCoolFormat3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	//
}

void CCoolFormat3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	//
}


// CCoolFormat3View diagnostics

#ifdef _DEBUG
void CCoolFormat3View::AssertValid() const
{
	CBCGPTabView::AssertValid();
}

void CCoolFormat3View::Dump(CDumpContext& dc) const
{
	CBCGPTabView::Dump(dc);
}

CCoolFormat3Doc* CCoolFormat3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCoolFormat3Doc)));
	return (CCoolFormat3Doc*)m_pDocument;
}
#endif //_DEBUG


// CCoolFormat3View message handlers

void CCoolFormat3View::OnInitialUpdate()
{	
	CBCGPTabView::OnInitialUpdate();

	CSynBCGPEditView *pCodeView = (CSynBCGPEditView*)GetActiveView();
	if (!GetDocument()->GetPathName().IsEmpty())
	{
		// 1)加载文件内容
		CString strFileName = GetDocument()->GetPathName();
		CString strExt = strFileName.Right(strFileName.GetLength() - strFileName.ReverseFind('.') - 1);
		pCodeView->GetEditCtrl()->SelectLanguageByExt(strExt);
		pCodeView->GetEditCtrl()->OpenFileEx(strFileName);
		pCodeView->ReSetLangLabel();
		pCodeView->ReSetEncodingLabel();
		GetDocument()->SetModifiedFlag(FALSE);

		// 2)加载文件图标
		SHFILEINFO shFile;
	    SHGetFileInfo(strFileName, FILE_ATTRIBUTE_NORMAL, &shFile, sizeof(shFile), SHGFI_ATTRIBUTES |  SHGFI_ICON | SHGFI_SMALLICON);
		m_DocIcon = ::CopyIcon(shFile.hIcon);
		DestroyIcon(shFile.hIcon);
		GetParentFrame()->SetIcon(m_DocIcon, FALSE);
	}
	else
	{
		pCodeView->GetEditCtrl()->SelectLanguage(theApp.m_nSynLanguage);
		pCodeView->ReSetLangLabel();
		pCodeView->ReSetEncodingLabel();
	}
}

void CCoolFormat3View::SaveEditFile( CString lpszPathName )
{
	SetActiveView(0);
	CSynBCGPEditView *pEditView = (CSynBCGPEditView *)GetActiveView();
	pEditView->GetEditCtrl()->SaveFileEx(lpszPathName);
}

CSynBCGPEditView * CCoolFormat3View::GetSynView()
{
	//获取TAB数 返回动态绑定
	CSynBCGPEditView *pView = NULL;
	if (GetTabControl().GetTabsNum() > 0)
	{
		pView = DYNAMIC_DOWNCAST(CSynBCGPEditView, m_wndTabs.GetTabWnd(0));
	}
	return pView;
}

BOOL CCoolFormat3View::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (TranslateAccelerator(m_hWnd, m_hAccel, pMsg))
		{
			return true;
		}
	}
	return CBCGPTabView::PreTranslateMessage(pMsg);
}

void CCoolFormat3View::OnSetFocus(CWnd* pOldWnd)
{
	CBCGPTabView::OnSetFocus(pOldWnd);

	if (GetActiveView())
	{
		GetActiveView()->SetFocus();
	}
}

int CCoolFormat3View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	GetTabControl().EnableTabSwap(FALSE);
	GetTabControl().HideSingleTab(TRUE);
	GetTabControl().AutoDestroyWindow(TRUE);
	m_hAccel = LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCEL_EDIT));

	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(ID_TAB_CODE);
	ASSERT(bNameVaild);
	AddView(RUNTIME_CLASS(CSynBCGPEditView), strTemp, ID_TAB_CODE);

	return 0;
}
