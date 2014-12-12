// SetPagePHP.cpp : 实现文件

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPagePHP.h"

//////////////////////////////////////////////////////////////////////////
// CSetPagePHP 对话框

CSetPagePHP::CSetPagePHP(LPCTSTR lpszTitle, CString& strTidy)
	: CSetPageBase(lpszTitle, strTidy)
{
}

CSetPagePHP::~CSetPagePHP()
{
}

void CSetPagePHP::InitPropList()
{
	CMyBCGPProp* pGrouBracket = new CMyBCGPProp(_T("Bracket"));
	CMyBCGPProp* pPropBracket = new CMyBCGPProp(_T("Bracket style"), _T("PEAR"));
	pPropBracket->AddComboOption(_T("K&R"), _T("is0"),
		_T("<?php")
		_T("\r\nfunction foo() {")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>"));
	pPropBracket->AddComboOption(_T("Allman"), _T("is1"),
		_T("<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>"));
	pPropBracket->AddComboOption(_T("Whitesmiths"), _T("is2"),
		_T("<?php")
		_T("\r\nfunction foo()")
		_T("\r\n    {")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n    }")
		_T("\r\n?>"));
	pPropBracket->AddComboOption(_T("GNU"), _T("is3"),
		_T("<?php")
		_T("\r\nfunction foo()")
		_T("\r\n  {")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n  }")
		_T("\r\n?>"));
	pPropBracket->AddComboOption(_T("PEAR"), _T("is4"),
		_T("<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>"));
	pGrouBracket->AddSubItem(pPropBracket);
	m_wndPropList.AddProperty(pGrouBracket);

	CMyBCGPProp* pGrouIndentation = new CMyBCGPProp(_T("Indentation"));
	CMyBCGPProp* pPropIndent = new CMyBCGPProp(_T("Indent using"), _T("Spaces"));
	pPropIndent->AddComboOption(_T("Spaces"), _T("ich0"),
		_T("<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n****echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>"));
	pPropIndent->AddComboOption(_T("Tab"), _T("ich1"),
		_T("<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n--->echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>"));
	pGrouIndentation->AddSubItem(pPropIndent);

	pPropIndent = new CMyBCGPProp(_T("Indent number"), (_variant_t)4);
	pPropIndent->SetNumberSpin(0, 100, _T("in"),
		_T("//indent_number4")
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
		_T("\r\n?>"));
	pGrouIndentation->AddSubItem(pPropIndent);

	pPropIndent = new CMyBCGPProp(_T("First indent number"), (_variant_t)0);
	pPropIndent->SetNumberSpin(0, 100, _T("fin"),
		_T("//first_indent_number0")
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
		_T("\r\n?>"));
	pGrouIndentation->AddSubItem(pPropIndent);

	pPropIndent = new CMyBCGPProp(_T("Indent case default"), _T("No"));
	pPropIndent->AddComboOption(_T("Yes"), _T("icd"),
		_T("<?php")
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
		_T("\r\n?>"));
	pPropIndent->AddComboOption(_T("No"), _T(""),
		_T("<?php")
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
		_T("\r\n?>"));
	pGrouIndentation->AddSubItem(pPropIndent);
	m_wndPropList.AddProperty(pGrouIndentation);

	CMyBCGPProp* pGrouPadding = new CMyBCGPProp(_T("Padding"));
	CMyBCGPProp* pPropPadding = new CMyBCGPProp(_T("Structures"), _T("No"));
	pPropPadding->AddComboOption(_T("Yes"), _T("sas"),
		_T("<?php")
		_T("\r\nif ($a>$b)")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n?>"));
	pPropPadding->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\nif($a>$b)")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n?>"));
	pGrouPadding->AddSubItem(pPropPadding);

	pPropPadding = new CMyBCGPProp(_T("Brackets"), _T("No"));
	pPropPadding->AddComboOption(_T("Yes"), _T("sibr"),
		_T("<?php")
		_T("\r\nif( $a>$b )")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n?>"));
	pPropPadding->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\nif($a>$b)")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n?>"));
	pGrouPadding->AddSubItem(pPropPadding);

	pPropPadding = new CMyBCGPProp(_T("Empty brackets"), _T("No"));
	pPropPadding->AddComboOption(_T("Yes"), _T("siebr"),
		_T("<?php")
		_T("\r\nfunction foo( )")
		_T("\r\n{")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>"));
	pPropPadding->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>"));
	pGrouPadding->AddSubItem(pPropPadding);

	pPropPadding = new CMyBCGPProp(_T("Block brackets"), _T("No"));
	pPropPadding->AddComboOption(_T("Yes"), _T("sibb"),
		_T("<?php")
		_T("\r\n$arr[ '1' ]=56;")
		_T("\r\n?>"));
	pPropPadding->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\n$arr['1']=56;")
		_T("\r\n?>"));
	pGrouPadding->AddSubItem(pPropPadding);

	pPropPadding = new CMyBCGPProp(_T("Empty block brackets"), _T("No"));
	pPropPadding->AddComboOption(_T("Yes"), _T("siebb"),
		_T("<?php")
		_T("\r\n$arr[ ]=56;")
		_T("\r\n?>"));
	pPropPadding->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\n$arr[]=56;")
		_T("\r\n?>"));
	pGrouPadding->AddSubItem(pPropPadding);

	pPropPadding = new CMyBCGPProp(_T("Math operators"), _T("No"));
	pPropPadding->AddComboOption(_T("Yes"), _T("samt"),
		_T("<?php")
		_T("\r\n$a=3 * 3 % 5;")
		_T("\r\n?>"));
	pPropPadding->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\n$a=3*3%5;")
		_T("\r\n?>"));
	pGrouPadding->AddSubItem(pPropPadding);

	pPropPadding = new CMyBCGPProp(_T("Logical operators"), _T("No"));
	pPropPadding->AddComboOption(_T("Yes"), _T("salo"),
		_T("<?php")
		_T("\r\n$g=true && false;")
		_T("\r\n?>"));
	pPropPadding->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\n$g=true&&false;")
		_T("\r\n?>"));
	pGrouPadding->AddSubItem(pPropPadding);

	pPropPadding = new CMyBCGPProp(_T("Equality operators"), _T("No"));
	pPropPadding->AddComboOption(_T("Yes"), _T("saeo"),
		_T("<?php")
		_T("\r\nvar_dump(0 == \"a\");")
		_T("\r\n?>"));
	pPropPadding->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\nvar_dump(0==\"a\");")
		_T("\r\n?>"));
	pGrouPadding->AddSubItem(pPropPadding);

	pPropPadding = new CMyBCGPProp(_T("Relational operators"), _T("No"));
	pPropPadding->AddComboOption(_T("Yes"), _T("saro"),
		_T("<?php")
		_T("\r\nvar_dump(0 >= \"a\");")
		_T("\r\n?>"));
	pPropPadding->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\nvar_dump(0>=\"a\");")
		_T("\r\n?>"));
	pGrouPadding->AddSubItem(pPropPadding);

	pPropPadding = new CMyBCGPProp(_T("Bitwise operators"), _T("No"));
	pPropPadding->AddComboOption(_T("Yes"), _T("sabo"),
		_T("<?php")
		_T("\r\necho 12 ^ 9;")
		_T("\r\n$res=4 >> 1;")
		_T("\r\n?>"));
	pPropPadding->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\necho 12^9;")
		_T("\r\n$res=4>>1;")
		_T("\r\n?>"));
	pGrouPadding->AddSubItem(pPropPadding);

	pPropPadding = new CMyBCGPProp(_T("Assignment operators"), _T("No"));
	pPropPadding->AddComboOption(_T("Yes"), _T("saao"),
		_T("<?php")
		_T("\r\n$a = 3;")
		_T("\r\n$a += 5;")
		_T("\r\n$b = \"Hello \";")
		_T("\r\n$b .= \"There!\";")
		_T("\r\n?>"));
	pPropPadding->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\n$a=3;")
		_T("\r\n$a+=5;")
		_T("\r\n$b=\"Hello \";")
		_T("\r\n$b.=\"There!\";")
		_T("\r\n?>"));
	pGrouPadding->AddSubItem(pPropPadding);

	pPropPadding = new CMyBCGPProp(_T("Map operators"), _T("No"));
	pPropPadding->AddComboOption(_T("Yes"), _T("samp"),
		_T("<?php")
		_T("\r\n$array=array(")
		_T("\r\n    \"foo\" => \"bar\",")
		_T("\r\n    \"bar\" => \"foo\"")
		_T("\r\n);")
		_T("\r\n?>"));
	pPropPadding->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\n$array=array(")
		_T("\r\n    \"foo\"=>\"bar\",")
		_T("\r\n    \"bar\"=>\"foo\"")
		_T("\r\n);")
		_T("\r\n?>"));
	pGrouPadding->AddSubItem(pPropPadding);
	m_wndPropList.AddProperty(pGrouPadding);

	CMyBCGPProp* pGrouFormatting = new CMyBCGPProp(_T("Formatting"));
	CMyBCGPProp* pPropFormatting = new CMyBCGPProp(_T("Remove all comments"), _T("No"));
	pPropFormatting->AddComboOption(_T("Yes"), _T("rc"),
		_T("<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>"));
	pPropFormatting->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n    //a is bigger than b")
		_T("\r\n}")
		_T("\r\n?>"));
	pGrouFormatting->AddSubItem(pPropFormatting);

	pPropFormatting = new CMyBCGPProp(_T("Remove empty lines"), _T("No"));
	pPropFormatting->AddComboOption(_T("Yes"), _T("rel"),
		_T("<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>"));
	pPropFormatting->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n")
		_T("\r\n}")
		_T("\r\n?>"));
	pGrouFormatting->AddSubItem(pPropFormatting);

	pPropFormatting = new CMyBCGPProp(_T("Align assignments"), _T("No"));
	pPropFormatting->AddComboOption(_T("Yes"), _T("aas"),
		_T("<?php")
		_T("\r\n$a   =3;")
		_T("\r\n$aa  =5;")
		_T("\r\n$aaaa=\"Hello \";")
		_T("\r\n?>"));
	pPropFormatting->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\n$a=3;")
		_T("\r\n$aa=5;")
		_T("\r\n$aaaa=\"Hello \";")
		_T("\r\n?>"));
	pGrouFormatting->AddSubItem(pPropFormatting);

	pPropFormatting = new CMyBCGPProp(_T("Comment structures"), _T("No"));
	pPropFormatting->AddComboOption(_T("Yes"), _T("cas"),
		_T("<?php")
		_T("\r\nif($a>$b) {")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n} //$a>$b")
		_T("\r\n?>"));
	pPropFormatting->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\nif($a>$b) {")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>"));
	pGrouFormatting->AddSubItem(pPropFormatting);

	pPropFormatting = new CMyBCGPProp(_T("Remove semicolon lines"), _T("No"));
	pPropFormatting->AddComboOption(_T("Yes"), _T("rsl"),
		_T("<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>"));
	pPropFormatting->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n    echo \"a is bigger than b\";")
		_T("\r\n    ;")
		_T("\r\n}")
		_T("\r\n?>"));
	pGrouFormatting->AddSubItem(pPropFormatting);

	pPropFormatting = new CMyBCGPProp(_T("Indent empty lines"), _T("No"));
	pPropFormatting->AddComboOption(_T("Yes"), _T("iel"),
		_T("<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n****echo \"a is bigger than b\";")
		_T("\r\n****")
		_T("\r\n****echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>"));
	pPropFormatting->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\nfunction foo()")
		_T("\r\n{")
		_T("\r\n****echo \"a is bigger than b\";")
		_T("\r\n")
		_T("\r\n****echo \"a is bigger than b\";")
		_T("\r\n}")
		_T("\r\n?>"));
	pGrouFormatting->AddSubItem(pPropFormatting);

	pPropFormatting = new CMyBCGPProp(_T("Rewrite perl comments"), _T("No"));
	pPropFormatting->AddComboOption(_T("Yes"), _T("rpc"),
		_T("<?php")
		_T("\r\necho 'One Final Test';")
		_T("\r\n// This is a one-line shell-style comment")
		_T("\r\n?>"));
	pPropFormatting->AddComboOption(_T("No"), _T(""),
		_T("<?php")
		_T("\r\necho 'One Final Test';")
		_T("\r\n# This is a one-line shell-style comment")
		_T("\r\n?>"));
	pGrouFormatting->AddSubItem(pPropFormatting);

	pPropFormatting = new CMyBCGPProp(_T("Rewrite short tag"), _T("No"));
	pPropFormatting->AddComboOption(_T("Yes"), _T("rst"),
		_T("<?php")
		_T("\r\necho 'Test';")
		_T("\r\n?>"));
	pPropFormatting->AddComboOption(_T("No"), _T(""),
		_T("<?")
		_T("\r\necho 'Test';")
		_T("\r\n?>"));
	pGrouFormatting->AddSubItem(pPropFormatting);

	pPropFormatting = new CMyBCGPProp(_T("Asp tags"), _T("No"));
	pPropFormatting->AddComboOption(_T("Yes"), _T("at"),
		_T("<%")
		_T("\r\necho 'Test';")
		_T("\r\n%>"));
	pPropFormatting->AddComboOption(_T("No"), _T(""),
		_T(""));
	pGrouFormatting->AddSubItem(pPropFormatting);

	pPropFormatting = new CMyBCGPProp(_T("Short tags"), _T("No"));
	pPropFormatting->AddComboOption(_T("Yes"), _T("st"),
		_T("<?")
		_T("\r\necho 'Test';")
		_T("\r\n?>"));
	pPropFormatting->AddComboOption(_T("No"), _T(""),
		_T(""));
	pGrouFormatting->AddSubItem(pPropFormatting);

	pPropFormatting = new CMyBCGPProp(_T("Quiet"), _T("No"));
	pPropFormatting->AddComboOption(_T("Yes"), _T("q"),
		_T("No errors are shown"));
	pPropFormatting->AddComboOption(_T("No"), _T(""),
		_T("Errors are shown"));
	pGrouFormatting->AddSubItem(pPropFormatting);
	m_wndPropList.AddProperty(pGrouFormatting);
}
