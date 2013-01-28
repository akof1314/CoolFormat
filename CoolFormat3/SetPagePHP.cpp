// SetPagePHP.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPagePHP.h"


// CSetPagePHP 对话框

IMPLEMENT_DYNAMIC(CSetPagePHP, CBCGPPropertyPage)

CSetPagePHP::CSetPagePHP()
	: CBCGPPropertyPage(CSetPagePHP::IDD)
{

}

CSetPagePHP::~CSetPagePHP()
{
}

void CSetPagePHP::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSetPagePHP, CBCGPPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO_PHP_INDENT_TAB, &CSetPagePHP::OnCbnSelchangeComboPhpIndentTab)
	ON_CBN_SELCHANGE(IDC_COMBO_PHP_INDENT_STYLE, &CSetPagePHP::OnCbnSelchangeComboPhpIndentStyle)
	ON_EN_SETFOCUS(IDC_EDIT_PHP_INDENT_NUMBER, &CSetPagePHP::OnEnSetfocusEditPhpIndentNumber)
	ON_EN_SETFOCUS(IDC_EDIT_PHP_FIRST_NUMBER, &CSetPagePHP::OnEnSetfocusEditPhpFirstNumber)
	ON_BN_CLICKED(IDC_CHECK_PHP_SPACE_STRUCTURES, &CSetPagePHP::OnBnClickedCheckPhpSpaceStructures)
	ON_BN_CLICKED(IDC_CHECK_PHP_INDENT_CASE, &CSetPagePHP::OnBnClickedCheckPhpIndentCase)
	ON_BN_CLICKED(IDC_CHECK_PHP_BRACKETS, &CSetPagePHP::OnBnClickedCheckPhpBrackets)
	ON_BN_CLICKED(IDC_CHECK_PHP_EMPTY_BRACKETS, &CSetPagePHP::OnBnClickedCheckPhpEmptyBrackets)
	ON_BN_CLICKED(IDC_CHECK_PHP_BLOCK_BRACKETS, &CSetPagePHP::OnBnClickedCheckPhpBlockBrackets)
	ON_BN_CLICKED(IDC_CHECK_PHP_EMPTY_BLOCK, &CSetPagePHP::OnBnClickedCheckPhpEmptyBlock)
	ON_BN_CLICKED(IDC_CHECK_PHP_MATH_OPERATORS, &CSetPagePHP::OnBnClickedCheckPhpMathOperators)
	ON_BN_CLICKED(IDC_CHECK_PHP_LOGICAL_OPERATORS, &CSetPagePHP::OnBnClickedCheckPhpLogicalOperators)
	ON_BN_CLICKED(IDC_CHECK_PHP_EQUALITY_OPERATORS, &CSetPagePHP::OnBnClickedCheckPhpEqualityOperators)
	ON_BN_CLICKED(IDC_CHECK_PHP_RELATIONAL_OPER, &CSetPagePHP::OnBnClickedCheckPhpRelationalOper)
	ON_BN_CLICKED(IDC_CHECK_PHP_BITWISE_OPER, &CSetPagePHP::OnBnClickedCheckPhpBitwiseOper)
	ON_BN_CLICKED(IDC_CHECK_PHP_ASSIGNMENT_OPER, &CSetPagePHP::OnBnClickedCheckPhpAssignmentOper)
	ON_BN_CLICKED(IDC_CHECK_PHP_MAP_OPER, &CSetPagePHP::OnBnClickedCheckPhpMapOper)
	ON_BN_CLICKED(IDC_CHECK_PHP_REMOVE_COMMENTS, &CSetPagePHP::OnBnClickedCheckPhpRemoveComments)
	ON_BN_CLICKED(IDC_CHECK_PHP_COMMENT_STRUCTURES, &CSetPagePHP::OnBnClickedCheckPhpCommentStructures)
	ON_BN_CLICKED(IDC_CHECK_PHP_ALIGN_ASSIGNMENTS, &CSetPagePHP::OnBnClickedCheckPhpAlignAssignments)
	ON_BN_CLICKED(IDC_CHECK_PHP_REMOVE_EMPTYLINES, &CSetPagePHP::OnBnClickedCheckPhpRemoveEmptylines)
	ON_BN_CLICKED(IDC_CHECK_PHP_REMOVE_SEMICOLON, &CSetPagePHP::OnBnClickedCheckPhpRemoveSemicolon)
	ON_BN_CLICKED(IDC_CHECK_PHP_INDENT_EMPTYLINES, &CSetPagePHP::OnBnClickedCheckPhpIndentEmptylines)
	ON_BN_CLICKED(IDC_CHECK_PHP_REWRITE_PERL_COMM, &CSetPagePHP::OnBnClickedCheckPhpRewritePerlComm)
	ON_BN_CLICKED(IDC_CHECK_PHP_REWRITE_SHORT_TAG, &CSetPagePHP::OnBnClickedCheckPhpRewriteShortTag)
	ON_BN_CLICKED(IDC_CHECK_PHP_ASP_TAGS, &CSetPagePHP::OnBnClickedCheckPhpAspTags)
	ON_BN_CLICKED(IDC_CHECK_PHP_SHORT_TAGS, &CSetPagePHP::OnBnClickedCheckPhpShortTags)
	ON_BN_CLICKED(IDC_CHECK_PHP_QUIET, &CSetPagePHP::OnBnClickedCheckPhpQuiet)
END_MESSAGE_MAP()

BOOL CSetPagePHP::OnInitDialog()
{
	CBCGPPropertyPage::OnInitDialog();
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STR_VIEWFORMATTER);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_VIEWFORMATTER, strTemp);
	GetDlgItem(IDC_EDIT_VIEWFORMATTER)->SetFont(&g_GlobalUtils.m_fontWidth);

	InitLimit();
	SetTidyConfig(g_GlobalTidy.m_TidyPhp);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSetPagePHP::InitLimit()
{
	((CComboBox *)GetDlgItem(IDC_COMBO_PHP_INDENT_TAB))->SetCurSel(0);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_PHP_INDENT_NUMBER))->SetRange(0, 100);
	GetDlgItem(IDC_EDIT_PHP_INDENT_NUMBER)->SetWindowText(_T("4"));
	((CComboBox *)GetDlgItem(IDC_COMBO_PHP_INDENT_STYLE))->SetCurSel(4);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_PHP_FIRST_NUMBER))->SetRange(0, 100);
	GetDlgItem(IDC_EDIT_PHP_FIRST_NUMBER)->SetWindowText(_T("0"));
}

void CSetPagePHP::SetViewEdit( LPCTSTR lpszText )
{
	SetDlgItemText(IDC_EDIT_VIEWFORMATTER, lpszText);
}

void CSetPagePHP::OnCbnSelchangeComboPhpIndentTab()
{
	CString strText;
	switch (((CComboBox *)GetDlgItem(IDC_COMBO_PHP_INDENT_TAB))->GetCurSel())
	{
	case 0:strText = _T("<?php")
			   _T("\r\nfunction foo()")
			   _T("\r\n{")
			   _T("\r\n****echo \"a is bigger than b\";")
			   _T("\r\n}")
			   _T("\r\n?>");
		break;
	case 1:strText = _T("<?php")
			   _T("\r\nfunction foo()")
			   _T("\r\n{")
			   _T("\r\n--->echo \"a is bigger than b\";")
			   _T("\r\n}")
			   _T("\r\n?>");
		break;
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnCbnSelchangeComboPhpIndentStyle()
{
	CString strText;
	switch (((CComboBox *)GetDlgItem(IDC_COMBO_PHP_INDENT_STYLE))->GetCurSel())
	{
	case 0:strText = _T("<?php")
			   _T("\r\nfunction foo() {")
			   _T("\r\n    echo \"a is bigger than b\";")
			   _T("\r\n}")
			   _T("\r\n?>");
		break;
	case 1:strText = _T("<?php")
			   _T("\r\nfunction foo()")
			   _T("\r\n{")
			   _T("\r\n    echo \"a is bigger than b\";")
			   _T("\r\n}")
			   _T("\r\n?>");
		break;
	case 2:strText = _T("<?php")
			   _T("\r\nfunction foo()")
			   _T("\r\n    {")
			   _T("\r\n    echo \"a is bigger than b\";")
			   _T("\r\n    }")
			   _T("\r\n?>");
		break;
	case 3:strText = _T("<?php")
			   _T("\r\nfunction foo()")
			   _T("\r\n  {")
			   _T("\r\n    echo \"a is bigger than b\";")
			   _T("\r\n  }")
			   _T("\r\n?>");
		break;
	case 4:strText = _T("<?php")
			   _T("\r\nfunction foo()")
			   _T("\r\n{")
			   _T("\r\n    echo \"a is bigger than b\";")
			   _T("\r\n}")
			   _T("\r\n?>");
		break;
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnEnSetfocusEditPhpIndentNumber()
{
	CString strText;
	strText = _T("//indent_number4")
		_T("\r\n<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n****echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>")
		_T("\r\n")
		_T("\r\n//indent_number5")
		_T("\r\n<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n*****echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>");
	SetViewEdit(strText);
}

void CSetPagePHP::OnEnSetfocusEditPhpFirstNumber()
{
	CString strText;
	strText = _T("//first_indent_number0")
		_T("\r\n<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>")
		_T("\r\n")
		_T("\r\n//first_indent_number2")
		_T("\r\n<?php")
		_T("\r\n  function foo()")
		_T("\r\n  {")
		_T("\r\n      echo \"a is bigger than b\";")
		_T("\r\n  }")
		_T("\r\n?>");
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpSpaceStructures()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_SPACE_STRUCTURES))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\nif ($a>$b)")
			_T("\r\n    echo \"a is bigger than b\";")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\nif($a>$b)")
			_T("\r\n    echo \"a is bigger than b\";")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpIndentCase()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_INDENT_CASE))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\nswitch($i) {")
			_T("\r\n    case 0:")
			_T("\r\n        echo \"i equals 0\";")
			_T("\r\n        break;")
			_T("\r\n    case 1:")
			_T("\r\n        echo \"i equals 1\";")
			_T("\r\n        break;")
			_T("\r\n    case 2:")
			_T("\r\n        echo \"i equals 2\";")
			_T("\r\n        break;")
			_T("\r\n    default:")
			_T("\r\n        echo \"i is not equal to 0, 1 or 2\";")
			_T("\r\n}")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\nswitch($i) {")
			_T("\r\ncase 0:")
			_T("\r\n    echo \"i equals 0\";")
			_T("\r\n    break;")
			_T("\r\ncase 1:")
			_T("\r\n    echo \"i equals 1\";")
			_T("\r\n    break;")
			_T("\r\ncase 2:")
			_T("\r\n    echo \"i equals 2\";")
			_T("\r\n    break;")
			_T("\r\ndefault:")
			_T("\r\n    echo \"i is not equal to 0, 1 or 2\";")
			_T("\r\n}")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpBrackets()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_BRACKETS))->GetCheck())
	{		
		strText = _T("<?php")
			_T("\r\nif( $a>$b )")
			_T("\r\n    echo \"a is bigger than b\";")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\nif($a>$b)")
			_T("\r\n    echo \"a is bigger than b\";")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpEmptyBrackets()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_EMPTY_BRACKETS))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\nfunction foo( )")
			_T("\r\n{")
			_T("\r\n    echo \"a is bigger than b\";")
			_T("\r\n}")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\nfunction foo()")
			_T("\r\n{")
			_T("\r\n    echo \"a is bigger than b\";")
			_T("\r\n}")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpBlockBrackets()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_BLOCK_BRACKETS))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\n$arr[ '1' ]=56;")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\n$arr['1']=56;")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpEmptyBlock()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_EMPTY_BLOCK))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\n$arr[ ]=56;")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\n$arr[]=56;")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpMathOperators()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_MATH_OPERATORS))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\n$a=3 * 3 % 5;")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\n$a=3*3%5;")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpLogicalOperators()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_LOGICAL_OPERATORS))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\n$g=true && false;")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\n$g=true&&false;")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpEqualityOperators()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_EQUALITY_OPERATORS))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\nvar_dump(0 == \"a\");")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\nvar_dump(0==\"a\");")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpRelationalOper()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_RELATIONAL_OPER))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\nvar_dump(0 >= \"a\");")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\nvar_dump(0>=\"a\");")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpBitwiseOper()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_BITWISE_OPER))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\necho 12 ^ 9;")
			_T("\r\n$res=4 >> 1;")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\necho 12^9;")
			_T("\r\n$res=4>>1;")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpAssignmentOper()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_ASSIGNMENT_OPER))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\n$a = 3;")
			_T("\r\n$a += 5;")
			_T("\r\n$b = \"Hello \";")
			_T("\r\n$b .= \"There!\";")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\n$a=3;")
			_T("\r\n$a+=5;")
			_T("\r\n$b=\"Hello \";")
			_T("\r\n$b.=\"There!\";")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpMapOper()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_MAP_OPER))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\n$array=array(")
			_T("\r\n    \"foo\" => \"bar\",")
			_T("\r\n    \"bar\" => \"foo\"")
			_T("\r\n);")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\n$array=array(")
			_T("\r\n    \"foo\"=>\"bar\",")
			_T("\r\n    \"bar\"=>\"foo\"")
			_T("\r\n);")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpRemoveComments()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_REMOVE_COMMENTS))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\nfunction foo()")
			_T("\r\n{")
			_T("\r\n    echo \"a is bigger than b\";")
			_T("\r\n}")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\nfunction foo()")
			_T("\r\n{")
			_T("\r\n    echo \"a is bigger than b\";")
			_T("\r\n    //a is bigger than b")
			_T("\r\n}")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpCommentStructures()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_COMMENT_STRUCTURES))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\nif($a>$b) {")
			_T("\r\n    echo \"a is bigger than b\";")
			_T("\r\n} //$a>$b")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\nif($a>$b) {")
			_T("\r\n    echo \"a is bigger than b\";")
			_T("\r\n}")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpAlignAssignments()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_ALIGN_ASSIGNMENTS))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\n$a   =3;")
			_T("\r\n$aa  =5;")
			_T("\r\n$aaaa=\"Hello \";")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\n$a=3;")
			_T("\r\n$aa=5;")
			_T("\r\n$aaaa=\"Hello \";")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpRemoveEmptylines()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_REMOVE_EMPTYLINES))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\nfunction foo()")
			_T("\r\n{")
			_T("\r\n    echo \"a is bigger than b\";")
			_T("\r\n}")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\nfunction foo()")
			_T("\r\n{")
			_T("\r\n    echo \"a is bigger than b\";")
			_T("\r\n")
			_T("\r\n}")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpRemoveSemicolon()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_REMOVE_SEMICOLON))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\nfunction foo()")
			_T("\r\n{")
			_T("\r\n    echo \"a is bigger than b\";")
			_T("\r\n}")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\nfunction foo()")
			_T("\r\n{")
			_T("\r\n    echo \"a is bigger than b\";")
			_T("\r\n    ;")
			_T("\r\n}")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpIndentEmptylines()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_INDENT_EMPTYLINES))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\nfunction foo()")
			_T("\r\n{")
			_T("\r\n****echo \"a is bigger than b\";")
			_T("\r\n****")
			_T("\r\n****echo \"a is bigger than b\";")
			_T("\r\n}")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\nfunction foo()")
			_T("\r\n{")
			_T("\r\n****echo \"a is bigger than b\";")
			_T("\r\n")
			_T("\r\n****echo \"a is bigger than b\";")
			_T("\r\n}")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpRewritePerlComm()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_REWRITE_PERL_COMM))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\necho 'One Final Test';")
			_T("\r\n// This is a one-line shell-style comment")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?php")
			_T("\r\necho 'One Final Test';")
			_T("\r\n# This is a one-line shell-style comment")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpRewriteShortTag()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_REWRITE_SHORT_TAG))->GetCheck())
	{
		strText = _T("<?php")
			_T("\r\necho 'Test';")
			_T("\r\n?>");
	} 
	else
	{
		strText = _T("<?")
			_T("\r\necho 'Test';")
			_T("\r\n?>");
	}
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpAspTags()
{
	CString strText;
	strText = _T("<%")
		_T("\r\necho 'Test';")
		_T("\r\n%>");
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpShortTags()
{
	CString strText;
	strText = _T("<?")
		_T("\r\necho 'Test';")
		_T("\r\n?>");
	SetViewEdit(strText);
}

void CSetPagePHP::OnBnClickedCheckPhpQuiet()
{
	CString strText;
	strText = _T("No errors are shown");
	SetViewEdit(strText);
}

void CSetPagePHP::SetTidyConfig( LPCTSTR lpszTidy )
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

void CSetPagePHP::SetTidyControl( LPCTSTR lpszTidy, int nPos, int nSize )
{
	if (lpszTidy[nPos] != '-' || nSize < 2)
	{
		return;
	}

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
		nNumValue = 0;
	}
	CString strNumValue;
	strNumValue.Format(_T("%d"), nNumValue);

	if (_T("sas") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_SPACE_STRUCTURES))->SetCheck(1);
	} 
	else if (_T("icd") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_INDENT_CASE))->SetCheck(1);
	}
	else if (_T("sibr") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_BRACKETS))->SetCheck(1);
	}
	else if (_T("siebr") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_EMPTY_BRACKETS))->SetCheck(1);
	}
	else if (_T("sibb") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_BLOCK_BRACKETS))->SetCheck(1);
	}
	else if (_T("siebb") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_EMPTY_BLOCK))->SetCheck(1);
	}
	else if (_T("samt") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_MATH_OPERATORS))->SetCheck(1);
	}
	else if (_T("salo") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_LOGICAL_OPERATORS))->SetCheck(1);
	}
	else if (_T("saeo") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_EQUALITY_OPERATORS))->SetCheck(1);
	}
	else if (_T("saro") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_RELATIONAL_OPER))->SetCheck(1);
	}
	else if (_T("sabo") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_BITWISE_OPER))->SetCheck(1);
	}
	else if (_T("saao") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_ASSIGNMENT_OPER))->SetCheck(1);
	}
	else if (_T("samp") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_MAP_OPER))->SetCheck(1);
	}
	else if (_T("rc") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_REMOVE_COMMENTS))->SetCheck(1);
	}
	else if (_T("cas") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_COMMENT_STRUCTURES))->SetCheck(1);
	}
	else if (_T("aas") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_ALIGN_ASSIGNMENTS))->SetCheck(1);
	}
	else if (_T("rel") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_REMOVE_EMPTYLINES))->SetCheck(1);
	}
	else if (_T("rsl") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_REMOVE_SEMICOLON))->SetCheck(1);
	}
	else if (_T("iel") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_INDENT_EMPTYLINES))->SetCheck(1);
	}
	else if (_T("rpc") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_REWRITE_PERL_COMM))->SetCheck(1);
	}
	else if (_T("rst") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_REWRITE_SHORT_TAG))->SetCheck(1);
	}
	else if (_T("at") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_ASP_TAGS))->SetCheck(1);
	}
	else if (_T("st") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_SHORT_TAGS))->SetCheck(1);
	}
	else if (_T("q") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_PHP_QUIET))->SetCheck(1);
	}
	else if (_T("ich") == strParam)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_PHP_INDENT_TAB))->SetCurSel(nNumValue);
	}
	else if (_T("in") == strParam)
	{
		GetDlgItem(IDC_EDIT_PHP_INDENT_NUMBER)->SetWindowText(strNumValue);
	}
	else if (_T("fin") == strParam)
	{
		GetDlgItem(IDC_EDIT_PHP_FIRST_NUMBER)->SetWindowText(strNumValue);
	}
	else if (_T("is") == strParam)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_PHP_INDENT_STYLE))->SetCurSel(nNumValue);
	}
}

void CSetPagePHP::GetTidyConfig( CString &strTidyValue )
{
	CString strTidy, strValue;
	strTidy.Empty();

	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_SPACE_STRUCTURES))->GetCheck())
	{
		strTidy.Append(_T("-sas"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_INDENT_CASE))->GetCheck())
	{
		strTidy.Append(_T("-icd"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_BRACKETS))->GetCheck())
	{
		strTidy.Append(_T("-sibr"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_EMPTY_BRACKETS))->GetCheck())
	{
		strTidy.Append(_T("-siebr"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_BLOCK_BRACKETS))->GetCheck())
	{
		strTidy.Append(_T("-sibb"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_EMPTY_BLOCK))->GetCheck())
	{
		strTidy.Append(_T("-siebb"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_MATH_OPERATORS))->GetCheck())
	{
		strTidy.Append(_T("-samt"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_LOGICAL_OPERATORS))->GetCheck())
	{
		strTidy.Append(_T("-salo"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_EQUALITY_OPERATORS))->GetCheck())
	{
		strTidy.Append(_T("-saeo"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_RELATIONAL_OPER))->GetCheck())
	{
		strTidy.Append(_T("-saro"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_BITWISE_OPER))->GetCheck())
	{
		strTidy.Append(_T("-sabo"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_ASSIGNMENT_OPER))->GetCheck())
	{
		strTidy.Append(_T("-saao"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_MAP_OPER))->GetCheck())
	{
		strTidy.Append(_T("-samp"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_REMOVE_COMMENTS))->GetCheck())
	{
		strTidy.Append(_T("-rc"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_COMMENT_STRUCTURES))->GetCheck())
	{
		strTidy.Append(_T("-cas"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_ALIGN_ASSIGNMENTS))->GetCheck())
	{
		strTidy.Append(_T("-aas"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_REMOVE_EMPTYLINES))->GetCheck())
	{
		strTidy.Append(_T("-rel"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_REMOVE_SEMICOLON))->GetCheck())
	{
		strTidy.Append(_T("-rsl"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_INDENT_EMPTYLINES))->GetCheck())
	{
		strTidy.Append(_T("-iel"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_REWRITE_PERL_COMM))->GetCheck())
	{
		strTidy.Append(_T("-rpc"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_REWRITE_SHORT_TAG))->GetCheck())
	{
		strTidy.Append(_T("-rst"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_ASP_TAGS))->GetCheck())
	{
		strTidy.Append(_T("-at"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_SHORT_TAGS))->GetCheck())
	{
		strTidy.Append(_T("-st"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_PHP_QUIET))->GetCheck())
	{
		strTidy.Append(_T("-q"));
	}
	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_PHP_INDENT_TAB))->GetCurSel())
	{
		strTidy.AppendFormat(_T("-ich%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_PHP_INDENT_TAB))->GetCurSel());
	}
	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_PHP_INDENT_STYLE))->GetCurSel())
	{
		strTidy.AppendFormat(_T("-is%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_PHP_INDENT_STYLE))->GetCurSel());
	}
	GetDlgItemText(IDC_EDIT_PHP_INDENT_NUMBER, strValue);
	strTidy.Append(_T("-in"));
	strTidy.Append(strValue);

	GetDlgItemText(IDC_EDIT_PHP_FIRST_NUMBER, strValue);
	strTidy.Append(_T("-fin"));
	strTidy.Append(strValue);

	strTidyValue.Append(strTidy);
}

void CSetPagePHP::OnOK()
{
	CString strTidy;
	GetTidyConfig(strTidy);
	g_GlobalTidy.m_TidyPhp = strTidy;
	
	CBCGPPropertyPage::OnOK();
}
