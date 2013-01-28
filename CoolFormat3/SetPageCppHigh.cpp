// SetPageCppHigh.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageCppHigh.h"


// CSetPageCppHigh 对话框

IMPLEMENT_DYNAMIC(CSetPageCppHigh, CBCGPDialog)

CSetPageCppHigh::CSetPageCppHigh(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetPageCppHigh::IDD, pParent)
	, m_pEditWnd(NULL)
{

}

CSetPageCppHigh::~CSetPageCppHigh()
{
}

void CSetPageCppHigh::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetPageCppHigh, CBCGPDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_CPP_INDENT_TAB, &CSetPageCppHigh::OnCbnSelchangeComboCppIndentTab)
	ON_BN_CLICKED(IDC_CHECK_CPP_INDENT_CLASS, &CSetPageCppHigh::OnBnClickedCheckCppIndentClass)
	ON_BN_CLICKED(IDC_CHECK_CPP_INDENT_SWITCH, &CSetPageCppHigh::OnBnClickedCheckCppIndentSwitch)
	ON_BN_CLICKED(IDC_CHECK_CPP_INDENT_CASE, &CSetPageCppHigh::OnBnClickedCheckCppIndentCase)
	ON_BN_CLICKED(IDC_CHECK_CPP_INDENT_NAMESPACES, &CSetPageCppHigh::OnBnClickedCheckCppIndentNamespaces)
	ON_BN_CLICKED(IDC_CHECK_CPP_INDENT_LABEL, &CSetPageCppHigh::OnBnClickedCheckCppIndentLabel)
	ON_BN_CLICKED(IDC_CHECK_CPP_INDENT_PREPRO, &CSetPageCppHigh::OnBnClickedCheckCppIndentPrepro)
	ON_BN_CLICKED(IDC_CHECK_CPP_INDENT_COL1COMMENT, &CSetPageCppHigh::OnBnClickedCheckCppIndentCol1comment)
	ON_BN_CLICKED(IDC_CHECK_CPP_BREAK_BLOCKS, &CSetPageCppHigh::OnBnClickedCheckCppBreakBlocks)
	ON_BN_CLICKED(IDC_CHECK_CPP_BREAK_ALLBLOCKS, &CSetPageCppHigh::OnBnClickedCheckCppBreakAllblocks)
	ON_BN_CLICKED(IDC_CHECK_CPP_PAD_OPER, &CSetPageCppHigh::OnBnClickedCheckCppPadOper)
	ON_BN_CLICKED(IDC_CHECK_CPP_PAD_PARENS, &CSetPageCppHigh::OnBnClickedCheckCppPadParens)
	ON_BN_CLICKED(IDC_CHECK_CPP_PAD_PARENSOUT, &CSetPageCppHigh::OnBnClickedCheckCppPadParensout)
	ON_BN_CLICKED(IDC_CHECK_CPP_PAD_PARENSIN, &CSetPageCppHigh::OnBnClickedCheckCppPadParensin)
	ON_BN_CLICKED(IDC_CHECK_CPP_PAD_HEADER, &CSetPageCppHigh::OnBnClickedCheckCppPadHeader)
	ON_BN_CLICKED(IDC_CHECK_CPP_UNPAD_PARENS, &CSetPageCppHigh::OnBnClickedCheckCppUnpadParens)
	ON_BN_CLICKED(IDC_CHECK_CPP_DEL_EMPTYLINES, &CSetPageCppHigh::OnBnClickedCheckCppDelEmptylines)
	ON_BN_CLICKED(IDC_CHECK_CPP_FILL_EMPTYLINES, &CSetPageCppHigh::OnBnClickedCheckCppFillEmptylines)
	ON_BN_CLICKED(IDC_CHECK_CPP_BREAK_CLOSINGBRACKETS, &CSetPageCppHigh::OnBnClickedCheckCppBreakClosingbrackets)
	ON_BN_CLICKED(IDC_CHECK_CPP_BREAK_ELSEIFS, &CSetPageCppHigh::OnBnClickedCheckCppBreakElseifs)
	ON_BN_CLICKED(IDC_CHECK_CPP_ADD_BRACKETS, &CSetPageCppHigh::OnBnClickedCheckCppAddBrackets)
	ON_BN_CLICKED(IDC_CHECK_CPP_ADD_ONELINEBRACKETS, &CSetPageCppHigh::OnBnClickedCheckCppAddOnelinebrackets)
	ON_BN_CLICKED(IDC_CHECK_CPP_KEEP_ONELINEBLOCKS, &CSetPageCppHigh::OnBnClickedCheckCppKeepOnelineblocks)
	ON_BN_CLICKED(IDC_CHECK_CPP_KEEP_ONELINESTATE, &CSetPageCppHigh::OnBnClickedCheckCppKeepOnelinestate)
	ON_BN_CLICKED(IDC_CHECK_CPP_CONVERT_TABS, &CSetPageCppHigh::OnBnClickedCheckCppConvertTabs)
	ON_CBN_SELCHANGE(IDC_COMBO_CPP_MIN_CONDITIONAL, &CSetPageCppHigh::OnCbnSelchangeComboCppMinConditional)
	ON_CBN_SELCHANGE(IDC_COMBO_CPP_MAX_INSTATEMENT, &CSetPageCppHigh::OnCbnSelchangeComboCppMaxInstatement)
	ON_CBN_SELCHANGE(IDC_COMBO_CPP_ALIGN_POINTER, &CSetPageCppHigh::OnCbnSelchangeComboCppAlignPointer)
	ON_CBN_SELCHANGE(IDC_COMBO_CPP_ALIGN_REFERENCE, &CSetPageCppHigh::OnCbnSelchangeComboCppAlignReference)
END_MESSAGE_MAP()

void CSetPageCppHigh::SetViewEdit( LPCTSTR lpszText )
{
	if (m_pEditWnd)
	{
		m_pEditWnd->SetWindowText(lpszText);
	}
}
BOOL CSetPageCppHigh::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	InitLimit();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSetPageCppHigh::InitLimit()
{
	((CComboBox *)GetDlgItem(IDC_COMBO_CPP_INDENT_TAB))->SetCurSel(0);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_CPP_INDENT_SPACES))->SetRange(2, 20);
	GetDlgItem(IDC_EDIT_CPP_INDENT_SPACES)->SetWindowText(_T("4"));
	((CComboBox *)GetDlgItem(IDC_COMBO_CPP_MIN_CONDITIONAL))->SetCurSel(2);
	((CComboBox *)GetDlgItem(IDC_COMBO_CPP_MAX_INSTATEMENT))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_COMBO_CPP_ALIGN_POINTER))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_COMBO_CPP_ALIGN_REFERENCE))->SetCurSel(0);
}

void CSetPageCppHigh::OnCbnSelchangeComboCppIndentTab()
{
	CString strText;
	switch (((CComboBox *)GetDlgItem(IDC_COMBO_CPP_INDENT_TAB))->GetCurSel())
	{
	case 0:strText = _T("int*Foo(bool*isBar)")
			   _T("\r\n")_T("{")
			   _T("\r\n")_T("****if*(isBar)*{")
			   _T("\r\n")_T("********bar();")
			   _T("\r\n")_T("****}")
			   _T("\r\n")_T("****else*{")
			   _T("\r\n")_T("********bar(arg1,")
			   _T("\r\n")_T("************arg2,")
			   _T("\r\n")_T("************arg3);")
			   _T("\r\n")_T("****}")
			   _T("\r\n")_T("}");
		break;
	case 1:strText = _T("int*Foo(bool*isBar)")
			   _T("\r\n")_T("{")
			   _T("\r\n")_T("--->if*(isBar)*{")
			   _T("\r\n")_T("--->--->bar();")
			   _T("\r\n")_T("--->}")
			   _T("\r\n")_T("--->else*{")
			   _T("\r\n")_T("--->--->bar(arg1,")
			   _T("\r\n")_T("--->--->****arg2,")
			   _T("\r\n")_T("--->--->****arg3);")
			   _T("\r\n")_T("--->}")
			   _T("\r\n")_T("}");
		break;
	case 2:strText = _T("int*Foo(bool*isBar)")
			   _T("\r\n")_T("{")
			   _T("\r\n")_T("--->if*(isBar)*{")
			   _T("\r\n")_T("--->--->bar();")
			   _T("\r\n")_T("--->}")
			   _T("\r\n")_T("--->else*{")
			   _T("\r\n")_T("--->--->bar(arg1,")
			   _T("\r\n")_T("--->--->--->arg2,")
			   _T("\r\n")_T("--->--->--->arg3);")
			   _T("\r\n")_T("--->}")
			   _T("\r\n")_T("}");
		break;
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppIndentClass()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_CLASS))->GetCheck())
	{
		strText = _T("class Foo")
			_T("\r\n{")
			_T("\r\n    public:")
			_T("\r\n        Foo();")
			_T("\r\n        virtual ~Foo();")
			_T("\r\n};");		
	} 
	else
	{
		strText = _T("class Foo")
			_T("\r\n{")
			_T("\r\npublic:")
			_T("\r\n    Foo();")
			_T("\r\n    virtual ~Foo();")
			_T("\r\n};");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppIndentSwitch()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_SWITCH))->GetCheck())
	{
		strText = _T("switch (foo)")
			_T("\r\n{")
			_T("\r\n    case 1:")
			_T("\r\n        a += 1;")
			_T("\r\n        break;")
			_T("\r\n")
			_T("\r\n    case 2:")
			_T("\r\n    {")
			_T("\r\n        a += 2;")
			_T("\r\n        break;")
			_T("\r\n    }")
			_T("\r\n}");
	} 
	else
	{
		strText = _T("switch (foo)")
			_T("\r\n{")
			_T("\r\ncase 1:")
			_T("\r\n    a += 1;")
			_T("\r\n    break;")
			_T("\r\n")
			_T("\r\ncase 2:")
			_T("\r\n{")
			_T("\r\n    a += 2;")
			_T("\r\n    break;")
			_T("\r\n}")
			_T("\r\n}");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppIndentCase()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_CASE))->GetCheck())
	{
		strText = _T("switch (foo)")
			_T("\r\n{")
			_T("\r\n    case 1:")
			_T("\r\n        a += 1;")
			_T("\r\n        break;")
			_T("\r\n")
			_T("\r\n    case 2:")
			_T("\r\n        {")
			_T("\r\n            a += 2;")
			_T("\r\n            break;")
			_T("\r\n        }")
			_T("\r\n}");
	} 
	else
	{
		strText = _T("switch (foo)")
			_T("\r\n{")
			_T("\r\n    case 1:")
			_T("\r\n        a += 1;")
			_T("\r\n        break;")
			_T("\r\n")
			_T("\r\n    case 2:")
			_T("\r\n    {")
			_T("\r\n        a += 2;")
			_T("\r\n        break;")
			_T("\r\n    }")
			_T("\r\n}");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppIndentNamespaces()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_NAMESPACES))->GetCheck())
	{
		strText = _T("namespace foospace")
			_T("\r\n{")
			_T("\r\n    class Foo")
			_T("\r\n    {")
			_T("\r\n        public:")
			_T("\r\n            Foo();")
			_T("\r\n            virtual ~Foo();")
			_T("\r\n    };")
			_T("\r\n}");
	} 
	else
	{
		strText = _T("namespace foospace")
			_T("\r\n{")
			_T("\r\nclass Foo")
			_T("\r\n{")
			_T("\r\n    public:")
			_T("\r\n        Foo();")
			_T("\r\n        virtual ~Foo();")
			_T("\r\n};")
			_T("\r\n}");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppIndentLabel()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_LABEL))->GetCheck())
	{
		strText = _T("void Foo() {")
			_T("\r\n    while (isFoo) {")
			_T("\r\n        if (isFoo)")
			_T("\r\n            goto error;")
			_T("\r\n        ... ")
			_T("\r\n    error:")
			_T("\r\n        ...")
			_T("\r\n    }        ")
			_T("\r\n}");
	} 
	else
	{
		strText = _T("void Foo() {")
			_T("\r\n    while (isFoo) {")
			_T("\r\n        if (isFoo)")
			_T("\r\n            goto error;")
			_T("\r\n        ...")
			_T("\r\nerror:")
			_T("\r\n        ...")
			_T("\r\n    }")
			_T("\r\n}");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppIndentPrepro()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_PREPRO))->GetCheck())
	{
		strText = _T("#define Is_Bar(arg,a,b) \\")
			_T("\r\n    (Is_Foo((arg), (a)) \\")
			_T("\r\n     || Is_Foo((arg), (b)))");
	} 
	else
	{
		strText = _T("#define Is_Bar(arg,a,b) \\")
			_T("\r\n(Is_Foo((arg), (a)) \\")
			_T("\r\n|| Is_Foo((arg), (b)))");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppIndentCol1comment()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_COL1COMMENT))->GetCheck())
	{
		strText = _T("void Foo()")
			_T("\r\n{")
			_T("\r\n    // comment")
			_T("\r\n    if (isFoo)")
			_T("\r\n        bar();")
			_T("\r\n}");
	} 
	else
	{
		strText = _T("void Foo()")
			_T("\r\n{")
			_T("\r\n// comment")
			_T("\r\n    if (isFoo)")
			_T("\r\n        bar();")
			_T("\r\n}");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppBreakBlocks()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_BREAK_BLOCKS))->GetCheck())
	{
		strText = _T("isFoo = true;")
			_T("\r\n")
			_T("\r\nif (isFoo) {")
			_T("\r\n    bar();")
			_T("\r\n} else {")
			_T("\r\n    anotherBar();")
			_T("\r\n}")
			_T("\r\n")
			_T("\r\nisBar = false;");
	} 
	else
	{
		strText = _T("isFoo = true;")
			_T("\r\nif (isFoo) {")
			_T("\r\n    bar();")
			_T("\r\n} else {")
			_T("\r\n    anotherBar();")
			_T("\r\n}")
			_T("\r\nisBar = false;");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppBreakAllblocks()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_BREAK_ALLBLOCKS))->GetCheck())
	{
		strText = _T("isFoo = true;")
			_T("\r\n")
			_T("\r\nif (isFoo) {")
			_T("\r\n    bar();")
			_T("\r\n    ")
			_T("\r\n} else {")
			_T("\r\n    anotherBar();")
			_T("\r\n}")
			_T("\r\n")
			_T("\r\nisBar = false;");
	} 
	else
	{
		strText = _T("isFoo = true;")
			_T("\r\nif (isFoo) {")
			_T("\r\n    bar();")
			_T("\r\n} else {")
			_T("\r\n    anotherBar();")
			_T("\r\n}")
			_T("\r\nisBar = false;");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppPadOper()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_PAD_OPER))->GetCheck())
	{
		strText = _T("if (foo == 2)")
			_T("\r\n     a = bar((b - c) * a, d--);");
	} 
	else
	{
		strText = _T("if (foo==2)")
			_T("\r\n    a=bar((b-c)*a,d--);");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppPadParens()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_PAD_PARENS))->GetCheck())
	{
		strText = _T("if ( isFoo ( a, b ) )")
			_T("\r\n    bar ( a, b );");
	} 
	else
	{
		strText = _T("if (isFoo(a, b))")
			_T("\r\n    bar(a, b);");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppPadParensout()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_PAD_PARENSOUT))->GetCheck())
	{
		strText = _T("if (isFoo (a, b) )")
			_T("\r\n    bar (a, b);");
	} 
	else
	{
		strText = _T("if (isFoo(a, b))")
			_T("\r\n    bar(a, b);");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppPadParensin()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_PAD_PARENSIN))->GetCheck())
	{
		strText = _T("if ( isFoo( a, b ) )")
			_T("\r\n    bar( a, b );");
	} 
	else
	{
		strText = _T("if (isFoo(a, b))")
			_T("\r\n    bar(a, b);");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppPadHeader()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_PAD_HEADER))->GetCheck())
	{
		strText = _T("if (isFoo(a, b))")
			_T("\r\n    bar(a, b);");
	} 
	else
	{
		strText = _T("if(isFoo(a, b))")
			_T("\r\n    bar(a, b);");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppUnpadParens()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_UNPAD_PARENS))->GetCheck())
	{
		strText = _T("if(isFoo(a, b))")
			_T("\r\n    bar(a, b);");
	} 
	else
	{
		strText = _T("if ( isFoo( a, b ) )")
			_T("\r\n    bar ( a, b );");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppDelEmptylines()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_DEL_EMPTYLINES))->GetCheck())
	{
		strText = _T("void Foo()")
			_T("\r\n{")
			_T("\r\n    foo1 = 1;")
			_T("\r\n    foo2 = 2;")
			_T("\r\n}");
	} 
	else
	{
		strText = _T("void Foo()")
			_T("\r\n{")
			_T("\r\n	")
			_T("\r\n    foo1 = 1;")
			_T("\r\n	")
			_T("\r\n    foo2 = 2;")
			_T("\r\n	")
			_T("\r\n}");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppFillEmptylines()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_FILL_EMPTYLINES))->GetCheck())
	{
		strText = _T("void Foo(bool isFoo) {")
			_T("\r\n****if (isFoo) {")
			_T("\r\n********bar();")
			_T("\r\n****}")
			_T("\r\n****")
			_T("\r\n****else {")
			_T("\r\n********anotherBar();")
			_T("\r\n****}")
			_T("\r\n}");
	} 
	else
	{
		strText = _T("void Foo(bool isFoo) {")
			_T("\r\n****if (isFoo) {")
			_T("\r\n********bar();")
			_T("\r\n****}")
			_T("\r\n")
			_T("\r\n****else {")
			_T("\r\n********anotherBar();")
			_T("\r\n****}")
			_T("\r\n}");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppBreakClosingbrackets()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_BREAK_CLOSINGBRACKETS))->GetCheck())
	{
		strText = _T("void Foo(bool isFoo) {")
			_T("\r\n    if (isFoo) {")
			_T("\r\n        bar();")
			_T("\r\n    }")
			_T("\r\n    else {")
			_T("\r\n        anotherBar();")
			_T("\r\n    }")
			_T("\r\n}");
	} 
	else
	{
		strText = _T("void Foo(bool isFoo) {")
			_T("\r\n    if (isFoo) {")
			_T("\r\n        bar();")
			_T("\r\n    } else {")
			_T("\r\n        anotherBar();")
			_T("\r\n    }")
			_T("\r\n}");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppBreakElseifs()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_BREAK_ELSEIFS))->GetCheck())
	{
		strText = _T("if (isFoo) {")
			_T("\r\n    bar();")
			_T("\r\n}")
			_T("\r\nelse")
			_T("\r\n    if (isFoo1()) {")
			_T("\r\n        bar1();")
			_T("\r\n    }")
			_T("\r\n  else")
			_T("\r\n        if (isFoo2()) {")
			_T("\r\n            bar2();")
			_T("\r\n        }");
	} 
	else
	{
		strText = _T("if (isFoo) {")
			_T("\r\n    bar();")
			_T("\r\n}")
			_T("\r\nelse if (isFoo1()) {")
			_T("\r\n    bar1();")
			_T("\r\n}")
			_T("\r\nelse if (isFoo2()) }")
			_T("\r\n    bar2;")
			_T("\r\n}");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppAddBrackets()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_ADD_BRACKETS))->GetCheck())
	{
		strText = _T("if (isFoo) {")
			_T("\r\n    isFoo = false;")
			_T("\r\n}");
	} 
	else
	{
		strText = _T("if (isFoo)")
			_T("\r\n    isFoo = false;");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppAddOnelinebrackets()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_ADD_ONELINEBRACKETS))->GetCheck())
	{
		strText = _T("if (isFoo)")
			_T("\r\n    { isFoo = false; }");
	} 
	else
	{
		strText = _T("if (isFoo)")
			_T("\r\n    isFoo = false;");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppKeepOnelineblocks()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_KEEP_ONELINEBLOCKS))->GetCheck())
	{
		strText = _T("if (isFoo)")
			_T("\r\n{ isFoo = false; cout << isFoo << endl; }\r\n\r\n//remains unchanged.");
	} 
	else
	{
		strText = _T("if (isFoo)")
			_T("\r\n{ isFoo = false; cout << isFoo << endl; }");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppKeepOnelinestate()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_KEEP_ONELINESTATE))->GetCheck())
	{
		strText = _T("if (isFoo)")
			_T("\r\n{")
			_T("\r\n    isFoo = false; cout << isFoo << endl;")
			_T("\r\n}\r\n\r\n//remains unchanged.");
	} 
	else
	{
		strText = _T("if (isFoo)")
			_T("\r\n{")
			_T("\r\n    isFoo = false; cout << isFoo << endl;")
			_T("\r\n}");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnBnClickedCheckCppConvertTabs()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_CONVERT_TABS))->GetCheck())
	{
		strText = _T("int Foo(bool isBar)********//Foo")
			_T("\r\n{")
			_T("\r\n    int a****= b;")
			_T("\r\n}");
	} 
	else
	{
		strText = _T("int Foo(bool isBar)--->--->//Foo")
			_T("\r\n{")
			_T("\r\n    int a--->= b;")
			_T("\r\n}");
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnCbnSelchangeComboCppMinConditional()
{
	CString strText;
	strText = _T("// default 2 indents")
		_T("\r\nif (a < b")
		_T("\r\n        || c > d)")
		_T("\r\n    foo++;")
		_T("\r\n")
		_T("\r\nif (a < b")
		_T("\r\n        || c > d)")
		_T("\r\n{")
		_T("\r\n    foo++;")
		_T("\r\n}")
		_T("\r\n")
		_T("\r\nbecomes")
		_T("\r\n")
		_T("\r\n// 0 indent")
		_T("\r\nif (a < b")
		_T("\r\n    || c > d)")
		_T("\r\n    foo++;")
		_T("\r\n")
		_T("\r\nif (a < b")
		_T("\r\n    || c > d)")
		_T("\r\n{")
		_T("\r\n    foo++;")
		_T("\r\n}");
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnCbnSelchangeComboCppMaxInstatement()
{
	CString strText;
	strText = _T("fooArray[] = { red,")
		_T("\r\n         green,")
		_T("\r\n         blue };")
		_T("\r\n")
		_T("\r\nfooFunction(barArg1,")
		_T("\r\n         barArg2,")
		_T("\r\n         barArg3);")
		_T("\r\n")
		_T("\r\nbecomes (with larger value)")
		_T("\r\n")
		_T("\r\nfooArray[] = { red,")
		_T("\r\n               green,")
		_T("\r\n               blue };")
		_T("\r\n")
		_T("\r\nfooFunction(barArg1,")
		_T("\r\n            barArg2,")
		_T("\r\n            barArg3);");
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnCbnSelchangeComboCppAlignPointer()
{
	CString strText;
	switch (((CComboBox *)GetDlgItem(IDC_COMBO_CPP_ALIGN_POINTER))->GetCurSel())
	{
	case 0:strText = _T("char *foo1;")
			   _T("\r\nchar& foo2;")
			   _T("\r\n")
			   _T("\r\n//remains unchanged.");
		break;
	case 1:strText = _T("char* foo1;")
			   _T("\r\nchar& foo2;");
		break;
	case 2:strText = _T("char * foo1;")
			   _T("\r\nchar & foo2;");
		break;
	case 3:strText = _T("char *foo1;")
			   _T("\r\nchar &foo2;");
		break;
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::OnCbnSelchangeComboCppAlignReference()
{
	CString strText;
	switch (((CComboBox *)GetDlgItem(IDC_COMBO_CPP_ALIGN_REFERENCE))->GetCurSel())
	{
	case 0:
		strText = _T("char &foo1;")
			_T("\r\n")
			_T("\r\n//same as pointer.");
		break;
	case 1:strText = _T("char &foo1;")
			   _T("\r\n")
			   _T("\r\n//remains unchanged.");
		break;
	case 2:strText = _T("char& foo1;");
		break;
	case 3:strText = _T("char & foo1;");
		break;
	case 4:strText = _T("char &foo1;");
		break;
	}
	SetViewEdit(strText);
}

void CSetPageCppHigh::SetTidyConfig( LPCTSTR lpszTidy )
{
	int lenTidy = _tcsclen(lpszTidy);
	int nOption = 0;
	if (lenTidy > 0 && lpszTidy[0] == '-')
	{
		for (int i = 1; i < lenTidy; ++i)
		{
			if (i > 1 && _istalpha(lpszTidy[i]) && 'x' != lpszTidy[i - 1])
			{
				SetTidyControl(lpszTidy, nOption, i - nOption);
				nOption = 0;
			}
			if (0 == nOption)
			{
				nOption = i;
			}
		}
		SetTidyControl(lpszTidy, nOption, lenTidy - nOption);
	}
}

void CSetPageCppHigh::SetTidyControl( LPCTSTR lpszTidy, int nPos, int nSize )
{
	switch (lpszTidy[nPos])
	{
	case 'A':
		break;
	case 's':
		{
			CString strParam(lpszTidy + nPos + 1, nSize - 1);
			if (strParam.IsEmpty())
			{
				strParam = _T("4");
			}
			if (2 > _ttoi(strParam))
			{
				strParam = _T("2");
			}
			else if (20 < _ttoi(strParam))
			{
				strParam = _T("20");
			}
			((CComboBox *)GetDlgItem(IDC_COMBO_CPP_INDENT_TAB))->SetCurSel(0);
			GetDlgItem(IDC_EDIT_CPP_INDENT_SPACES)->SetWindowText(strParam);
		}
		break;
	case 't':
		{
			CString strParam(lpszTidy + nPos + 1, nSize - 1);
			if (strParam.IsEmpty())
			{
				strParam = _T("4");
			}
			if (2 > _ttoi(strParam))
			{
				strParam = _T("2");
			}
			else if (20 < _ttoi(strParam))
			{
				strParam = _T("20");
			}
			((CComboBox *)GetDlgItem(IDC_COMBO_CPP_INDENT_TAB))->SetCurSel(1);
			GetDlgItem(IDC_EDIT_CPP_INDENT_SPACES)->SetWindowText(strParam);
		}
		break;
	case 'T':
		{
			CString strParam(lpszTidy + nPos + 1, nSize - 1);
			if (strParam.IsEmpty())
			{
				strParam = _T("4");
			}
			if (2 > _ttoi(strParam))
			{
				strParam = _T("2");
			}
			else if (20 < _ttoi(strParam))
			{
				strParam = _T("20");
			}
			((CComboBox *)GetDlgItem(IDC_COMBO_CPP_INDENT_TAB))->SetCurSel(2);
			GetDlgItem(IDC_EDIT_CPP_INDENT_SPACES)->SetWindowText(strParam);
		}
		break;
	case 'C':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_CLASS))->SetCheck(1);
		}
		break;
	case 'S':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_SWITCH))->SetCheck(1);
		}
		break;
	case 'K':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_CASE))->SetCheck(1);
		}
		break;
	case 'N':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_NAMESPACES))->SetCheck(1);
		}
		break;
	case 'L':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_LABEL))->SetCheck(1);
		}
		break;
	case 'w':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_PREPRO))->SetCheck(1);
		}
		break;
	case 'Y':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_COL1COMMENT))->SetCheck(1);
		}
		break;
	case 'm':
		{
			if (2 >= nSize)
			{
				if ('0' == lpszTidy[nPos + 1])
				{
					((CComboBox *)GetDlgItem(IDC_COMBO_CPP_MIN_CONDITIONAL))->SetCurSel(0);
				}
				else if ('1' == lpszTidy[nPos + 1])
				{
					((CComboBox *)GetDlgItem(IDC_COMBO_CPP_MIN_CONDITIONAL))->SetCurSel(1);
				}
				else if ('2' == lpszTidy[nPos + 1])
				{
					((CComboBox *)GetDlgItem(IDC_COMBO_CPP_MIN_CONDITIONAL))->SetCurSel(2);
				}
				else if ('3' == lpszTidy[nPos + 1])
				{
					((CComboBox *)GetDlgItem(IDC_COMBO_CPP_MIN_CONDITIONAL))->SetCurSel(3);
				}
			}
		}
		break;
	case 'M':
		{
			CString strParam(lpszTidy + nPos + 1, nSize - 1);
			if (strParam.IsEmpty())
			{
				strParam = _T("40");
			}
			if (40 > _ttoi(strParam))
			{
				strParam = _T("40");
			}
			else if (120 < _ttoi(strParam))
			{
				strParam = _T("120");
			}
			int nParam = _ttoi(strParam);
			nParam = nParam / 10 - 4;
			((CComboBox *)GetDlgItem(IDC_COMBO_CPP_MAX_INSTATEMENT))->SetCurSel(nParam);
		}
		break;
	case 'f':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_BREAK_BLOCKS))->SetCheck(1);
		}
		break;
	case 'F':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_BREAK_ALLBLOCKS))->SetCheck(1);
		}
		break;
	case 'p':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_PAD_OPER))->SetCheck(1);
		}
		break;
	case 'P':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_PAD_PARENS))->SetCheck(1);
		}
		break;
	case 'd':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_PAD_PARENSOUT))->SetCheck(1);
		}
		break;
	case 'D':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_PAD_PARENSIN))->SetCheck(1);
		}
		break;
	case 'H':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_PAD_HEADER))->SetCheck(1);
		}
		break;
	case 'U':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_UNPAD_PARENS))->SetCheck(1);
		}
		break;
	case 'x':
		{
			if (2 >= nSize && 'd' == lpszTidy[nPos + 1])
			{
				((CButton *)GetDlgItem(IDC_CHECK_CPP_DEL_EMPTYLINES))->SetCheck(1);
			}
		}
		break;
	case 'E':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_FILL_EMPTYLINES))->SetCheck(1);
		}
		break;
	case 'y':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_BREAK_CLOSINGBRACKETS))->SetCheck(1);
		}
		break;
	case 'e':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_BREAK_ELSEIFS))->SetCheck(1);
		}
		break;
	case 'j':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_ADD_BRACKETS))->SetCheck(1);
		}
		break;
	case 'J':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_ADD_ONELINEBRACKETS))->SetCheck(1);
		}
		break;
	case 'O':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_KEEP_ONELINEBLOCKS))->SetCheck(1);
		}
		break;
	case 'o':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_KEEP_ONELINESTATE))->SetCheck(1);
		}
		break;
	case 'c':
		{
			((CButton *)GetDlgItem(IDC_CHECK_CPP_CONVERT_TABS))->SetCheck(1);
		}
		break;
	case 'k':
		{
			if (2 >= nSize)
			{
				if ('1' == lpszTidy[nPos + 1])
				{
					((CComboBox *)GetDlgItem(IDC_COMBO_CPP_ALIGN_POINTER))->SetCurSel(1);
				}
				else if ('2' == lpszTidy[nPos + 1])
				{
					((CComboBox *)GetDlgItem(IDC_COMBO_CPP_ALIGN_POINTER))->SetCurSel(2);
				}
				else if ('3' == lpszTidy[nPos + 1])
				{
					((CComboBox *)GetDlgItem(IDC_COMBO_CPP_ALIGN_POINTER))->SetCurSel(3);
				}				
			}
		}
		break;
	case 'W':
		{
			if (2 >= nSize)
			{
				if ('0' == lpszTidy[nPos + 1])
				{
					((CComboBox *)GetDlgItem(IDC_COMBO_CPP_ALIGN_REFERENCE))->SetCurSel(1);
				}
				else if ('1' == lpszTidy[nPos + 1])
				{
					((CComboBox *)GetDlgItem(IDC_COMBO_CPP_ALIGN_REFERENCE))->SetCurSel(2);
				}
				else if ('2' == lpszTidy[nPos + 1])
				{
					((CComboBox *)GetDlgItem(IDC_COMBO_CPP_ALIGN_REFERENCE))->SetCurSel(3);
				}
				else if ('3' == lpszTidy[nPos + 1])
				{
					((CComboBox *)GetDlgItem(IDC_COMBO_CPP_ALIGN_REFERENCE))->SetCurSel(4);
				}				
			}
		}
		break;
	}
}

void CSetPageCppHigh::GetTidyConfig(CString &strTidyValue)
{
	CString strTidy, strValue;
	strTidy.Empty();

	switch (((CComboBox *)GetDlgItem(IDC_COMBO_CPP_INDENT_TAB))->GetCurSel())
	{
	case 0:strTidy.Append(_T("s"));
		break;
	case 1:strTidy.Append(_T("t"));
		break;
	case 2:strTidy.Append(_T("T"));
		break;
	}

	GetDlgItemText(IDC_EDIT_CPP_INDENT_SPACES, strValue);
	int nValue = _ttoi(strValue);
	if (2 > nValue)
	{
		nValue = 2;
	}
	else if (20 < nValue)
	{
		nValue = 20;
	}
	strTidy.AppendFormat(_T("%d"), nValue);

	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_CLASS))->GetCheck())
	{
		strTidy.Append(_T("C"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_SWITCH))->GetCheck())
	{
		strTidy.Append(_T("S"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_CASE))->GetCheck())
	{
		strTidy.Append(_T("K"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_NAMESPACES))->GetCheck())
	{
		strTidy.Append(_T("N"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_LABEL))->GetCheck())
	{
		strTidy.Append(_T("L"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_PREPRO))->GetCheck())
	{
		strTidy.Append(_T("w"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_INDENT_COL1COMMENT))->GetCheck())
	{
		strTidy.Append(_T("Y"));
	}
	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_CPP_MIN_CONDITIONAL))->GetCurSel())
	{
		strTidy.AppendFormat(_T("m%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_CPP_MIN_CONDITIONAL))->GetCurSel());
	}
	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_CPP_MAX_INSTATEMENT))->GetCurSel())
	{
		strTidy.AppendFormat(_T("M%d0"), ((CComboBox *)GetDlgItem(IDC_COMBO_CPP_MAX_INSTATEMENT))->GetCurSel() + 4);
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_BREAK_BLOCKS))->GetCheck())
	{
		strTidy.Append(_T("f"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_BREAK_ALLBLOCKS))->GetCheck())
	{
		strTidy.Append(_T("F"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_PAD_OPER))->GetCheck())
	{
		strTidy.Append(_T("p"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_PAD_PARENS))->GetCheck())
	{
		strTidy.Append(_T("P"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_PAD_PARENSOUT))->GetCheck())
	{
		strTidy.Append(_T("d"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_PAD_PARENSIN))->GetCheck())
	{
		strTidy.Append(_T("D"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_PAD_HEADER))->GetCheck())
	{
		strTidy.Append(_T("H"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_UNPAD_PARENS))->GetCheck())
	{
		strTidy.Append(_T("U"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_DEL_EMPTYLINES))->GetCheck())
	{
		strTidy.Append(_T("xd"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_FILL_EMPTYLINES))->GetCheck())
	{
		strTidy.Append(_T("E"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_BREAK_CLOSINGBRACKETS))->GetCheck())
	{
		strTidy.Append(_T("y"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_BREAK_ELSEIFS))->GetCheck())
	{
		strTidy.Append(_T("e"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_ADD_BRACKETS))->GetCheck())
	{
		strTidy.Append(_T("j"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_ADD_ONELINEBRACKETS))->GetCheck())
	{
		strTidy.Append(_T("J"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_KEEP_ONELINEBLOCKS))->GetCheck())
	{
		strTidy.Append(_T("O"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_KEEP_ONELINESTATE))->GetCheck())
	{
		strTidy.Append(_T("o"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CPP_CONVERT_TABS))->GetCheck())
	{
		strTidy.Append(_T("c"));
	}
	if (0 < ((CComboBox *)GetDlgItem(IDC_COMBO_CPP_ALIGN_POINTER))->GetCurSel())
	{
		strTidy.AppendFormat(_T("k%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_CPP_ALIGN_POINTER))->GetCurSel());
	}
	if (0 < ((CComboBox *)GetDlgItem(IDC_COMBO_CPP_ALIGN_REFERENCE))->GetCurSel())
	{
		strTidy.AppendFormat(_T("W%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_CPP_ALIGN_REFERENCE))->GetCurSel() - 1);
	}
	strTidyValue.Append(strTidy);
}