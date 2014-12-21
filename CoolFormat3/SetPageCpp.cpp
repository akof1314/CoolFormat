// SetPageCpp.cpp : 实现文件

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageCpp.h"

//////////////////////////////////////////////////////////////////////////
// CSetPageCpp 对话框

CSetPageCpp::CSetPageCpp(LPCTSTR lpszTitle, CString& strTidy)
	: CSetPageBase(lpszTitle, _T(""), strTidy)
{
}

CSetPageCpp::~CSetPageCpp()
{
}

void CSetPageCpp::InitPropList()
{
	CMyBCGPProp* pGrouBracket = new CMyBCGPProp(_T("Bracket"));
	CMyBCGPProp* pPropBracket = new CMyBCGPProp(_T("Bracket style"), _T("None"));
	pPropBracket->AddComboOption(_T("allman/ansi/bsd/break"), _T("A1"),
		_T("int Foo(bool isBar)")
		_T("\r\n")_T("{")
		_T("\r\n")_T("     if (isBar)")
		_T("\r\n")_T("     { ")
		_T("\r\n")_T("          bar();")
		_T("\r\n")_T("          return 1;")
		_T("\r\n")_T("     }")
		_T("\r\n")_T("     else")
		_T("\r\n")_T("          return 0;")
		_T("\r\n")_T("}"));
	pPropBracket->AddComboOption(_T("java/attach"), _T("A2"),
		_T("int Foo(bool isBar) {")
		_T("\r\n")_T("    if (isBar) {")
		_T("\r\n")_T("        bar();")
		_T("\r\n")_T("        return 1;")
		_T("\r\n")_T("    } else")
		_T("\r\n")_T("        return 0;")
		_T("\r\n")_T("}"));
	pPropBracket->AddComboOption(_T("kr"), _T("A3"),
		_T("int Foo(bool isBar)")
		_T("\r\n")_T("{")
		_T("\r\n")_T("    if (isBar) {")
		_T("\r\n")_T("        bar();")
		_T("\r\n")_T("        return 1;")
		_T("\r\n")_T("    } else")
		_T("\r\n")_T("        return 0;")
		_T("\r\n")_T("}"));
	pPropBracket->AddComboOption(_T("stroustrup"), _T("A4"),
		_T("int Foo(bool isBar)")
		_T("\r\n")_T("{")
		_T("\r\n")_T("     if (isBar) {")
		_T("\r\n")_T("          bar();")
		_T("\r\n")_T("          return 1;")
		_T("\r\n")_T("     } else")
		_T("\r\n")_T("          return 0;")
		_T("\r\n")_T("}"));
	pPropBracket->AddComboOption(_T("whitesmith"), _T("A5"),
		_T("int Foo(bool isBar)")
		_T("\r\n")_T("    {")
		_T("\r\n")_T("    if (isBar)")
		_T("\r\n")_T("        {")
		_T("\r\n")_T("        bar();")
		_T("\r\n")_T("        return 1;")
		_T("\r\n")_T("        }")
		_T("\r\n")_T("    else")
		_T("\r\n")_T("        return 0;")
		_T("\r\n")_T("    }"));
	pPropBracket->AddComboOption(_T("banner"), _T("A6"),
		_T("int Foo(bool isBar) {")
		_T("\r\n")_T("    if (isBar) {")
		_T("\r\n")_T("        bar();")
		_T("\r\n")_T("        return 1;")
		_T("\r\n")_T("        }")
		_T("\r\n")_T("    else")
		_T("\r\n")_T("        return 0;")
		_T("\r\n")_T("    }"));
	pPropBracket->AddComboOption(_T("gnu"), _T("A7"),
		_T("int Foo(bool isBar)")
		_T("\r\n")_T("{")
		_T("\r\n")_T("  if (isBar)")
		_T("\r\n")_T("    {")
		_T("\r\n")_T("      bar();")
		_T("\r\n")_T("      return 1;")
		_T("\r\n")_T("    }")
		_T("\r\n")_T("  else")
		_T("\r\n")_T("    return 0;")
		_T("\r\n")_T("}"));
	pPropBracket->AddComboOption(_T("linux"), _T("A8"),
		_T("int Foo(bool isBar)")
		_T("\r\n")_T("{")
		_T("\r\n")_T("        if (isBar) {")
		_T("\r\n")_T("                bar();")
		_T("\r\n")_T("                return 1;")
		_T("\r\n")_T("        } else")
		_T("\r\n")_T("                return 0;")
		_T("\r\n")_T("}"));
	pPropBracket->AddComboOption(_T("horstmann"), _T("A9"),
		_T("int Foo(bool isBar)")
		_T("\r\n")_T("{  if (isBar)")
		_T("\r\n")_T("   {  bar();")
		_T("\r\n")_T("      return 1;")
		_T("\r\n")_T("   }")
		_T("\r\n")_T("   else")
		_T("\r\n")_T("      return 0;")
		_T("\r\n")_T("}"));
	pPropBracket->AddComboOption(_T("1tbs/otbs"), _T("A10"),
		_T("int Foo(bool isBar)")
		_T("\r\n")_T("{")
		_T("\r\n")_T("    if (isBar) {")
		_T("\r\n")_T("        bar();")
		_T("\r\n")_T("        return 1;")
		_T("\r\n")_T("    } else {")
		_T("\r\n")_T("        return 0;")
		_T("\r\n")_T("    }")
		_T("\r\n")_T("}"));
	pPropBracket->AddComboOption(_T("pico"), _T("A11"),
		_T("int Foo(bool isBar)")
		_T("\r\n")_T("{  if (isBar)")
		_T("\r\n")_T("   {  bar();")
		_T("\r\n")_T("      return 1; }")
		_T("\r\n")_T("        return 1;")
		_T("\r\n")_T("    else")
		_T("\r\n")_T("      return 0; }"));
	pPropBracket->AddComboOption(_T("lisp/python"), _T("A12"),
		_T("int Foo(bool isBar) {")
		_T("\r\n")_T("    if (isBar) {")
		_T("\r\n")_T("        bar()")
		_T("\r\n")_T("        return 1; }")
		_T("\r\n")_T("    else")
		_T("\r\n")_T("        return 0; }"));
	pPropBracket->AddComboOption(_T("None"), _T(""),
		_T(""));
	pGrouBracket->AddSubItem(pPropBracket);
	m_wndPropList.AddProperty(pGrouBracket);

	CMyBCGPProp* pGrouIndentation = new CMyBCGPProp(_T("Indentation"));
	CMyBCGPProp* pPropIndent = new CMyBCGPProp(_T("Indent using"), _T("Spaces"));
	pPropIndent->AddComboOption(_T("Spaces"), _T("s"),
		_T("int*Foo(bool*isBar)")
		_T("\r\n")_T("{")
		_T("\r\n")_T("****if*(isBar)*{")
		_T("\r\n")_T("********bar();")
		_T("\r\n")_T("****}")
		_T("\r\n")_T("****else*{")
		_T("\r\n")_T("********bar(arg1,")
		_T("\r\n")_T("************arg2,")
		_T("\r\n")_T("************arg3);")
		_T("\r\n")_T("****}")
		_T("\r\n")_T("}"));
	pPropIndent->AddComboOption(_T("Tab"), _T("t"),
		_T("int*Foo(bool*isBar)")
		_T("\r\n")_T("{")
		_T("\r\n")_T("--->if*(isBar)*{")
		_T("\r\n")_T("--->--->bar();")
		_T("\r\n")_T("--->}")
		_T("\r\n")_T("--->else*{")
		_T("\r\n")_T("--->--->bar(arg1,")
		_T("\r\n")_T("--->--->****arg2,")
		_T("\r\n")_T("--->--->****arg3);")
		_T("\r\n")_T("--->}")
		_T("\r\n")_T("}"));
	pPropIndent->AddComboOption(_T("Force tab"), _T("T"),
		_T("int*Foo(bool*isBar)")
		_T("\r\n")_T("{")
		_T("\r\n")_T("--->if*(isBar)*{")
		_T("\r\n")_T("--->--->bar();")
		_T("\r\n")_T("--->}")
		_T("\r\n")_T("--->else*{")
		_T("\r\n")_T("--->--->bar(arg1,")
		_T("\r\n")_T("--->--->--->arg2,")
		_T("\r\n")_T("--->--->--->arg3);")
		_T("\r\n")_T("--->}")
		_T("\r\n")_T("}"));
	pGrouIndentation->AddSubItem(pPropIndent);

	CMyBCGPProp*pPropIndentBuddy = new CMyBCGPProp(_T("Indent number"), (_variant_t)4);
	pPropIndentBuddy->SetNumberSpin(0, 20, _T(""),
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
		_T("\r\n?>"), pPropIndent);
	pGrouIndentation->AddSubItem(pPropIndentBuddy);

	pPropIndent = new CMyBCGPProp(_T("Indent classes"), _T("No"));
	pPropIndent->AddComboOption(_T("Yes"), _T("C"),
		_T("class Foo")
		_T("\r\n{")
		_T("\r\n    public:")
		_T("\r\n        Foo();")
		_T("\r\n        virtual ~Foo();")
		_T("\r\n};"));
	pPropIndent->AddComboOption(_T("No"), _T(""),
		_T("class Foo")
		_T("\r\n{")
		_T("\r\npublic:")
		_T("\r\n    Foo();")
		_T("\r\n    virtual ~Foo();")
		_T("\r\n};"));
	pGrouIndentation->AddSubItem(pPropIndent);

	pPropIndent = new CMyBCGPProp(_T("Indent switches"), _T("No"));
	pPropIndent->AddComboOption(_T("Yes"), _T("S"),
		_T("switch (foo)")
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
		_T("\r\n}"));
	pPropIndent->AddComboOption(_T("No"), _T(""),
		_T("switch (foo)")
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
		_T("\r\n}"));
	pGrouIndentation->AddSubItem(pPropIndent);

	pPropIndent = new CMyBCGPProp(_T("Indent cases"), _T("No"));
	pPropIndent->AddComboOption(_T("Yes"), _T("K"),
		_T("switch (foo)")
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
		_T("\r\n}"));
	pPropIndent->AddComboOption(_T("No"), _T(""),
		_T("switch (foo)")
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
		_T("\r\n}"));
	pGrouIndentation->AddSubItem(pPropIndent);

	pPropIndent = new CMyBCGPProp(_T("Indent namespaces"), _T("No"));
	pPropIndent->AddComboOption(_T("Yes"), _T("N"),
		_T("namespace foospace")
		_T("\r\n{")
		_T("\r\n    class Foo")
		_T("\r\n    {")
		_T("\r\n        public:")
		_T("\r\n            Foo();")
		_T("\r\n            virtual ~Foo();")
		_T("\r\n    };")
		_T("\r\n}"));
	pPropIndent->AddComboOption(_T("No"), _T(""),
		_T("namespace foospace")
		_T("\r\n{")
		_T("\r\nclass Foo")
		_T("\r\n{")
		_T("\r\n    public:")
		_T("\r\n        Foo();")
		_T("\r\n        virtual ~Foo();")
		_T("\r\n};")
		_T("\r\n}"));
	pGrouIndentation->AddSubItem(pPropIndent);

	pPropIndent = new CMyBCGPProp(_T("Indent labels"), _T("No"));
	pPropIndent->AddComboOption(_T("Yes"), _T("L"),
		_T("void Foo() {")
		_T("\r\n    while (isFoo) {")
		_T("\r\n        if (isFoo)")
		_T("\r\n            goto error;")
		_T("\r\n        ... ")
		_T("\r\n    error:")
		_T("\r\n        ...")
		_T("\r\n    }        ")
		_T("\r\n}"));
	pPropIndent->AddComboOption(_T("No"), _T(""),
		_T("void Foo() {")
		_T("\r\n    while (isFoo) {")
		_T("\r\n        if (isFoo)")
		_T("\r\n            goto error;")
		_T("\r\n        ...")
		_T("\r\nerror:")
		_T("\r\n        ...")
		_T("\r\n    }")
		_T("\r\n}"));
	pGrouIndentation->AddSubItem(pPropIndent);

	pPropIndent = new CMyBCGPProp(_T("Indent preprocessor"), _T("No"));
	pPropIndent->AddComboOption(_T("Yes"), _T("w"),
		_T("#define Is_Bar(arg,a,b) \\")
		_T("\r\n    (Is_Foo((arg), (a)) \\")
		_T("\r\n     || Is_Foo((arg), (b)))"));
	pPropIndent->AddComboOption(_T("No"), _T(""),
		_T("#define Is_Bar(arg,a,b) \\")
		_T("\r\n(Is_Foo((arg), (a)) \\")
		_T("\r\n|| Is_Foo((arg), (b)))"));
	pGrouIndentation->AddSubItem(pPropIndent);

	pPropIndent = new CMyBCGPProp(_T("Indent col1 comments"), _T("No"));
	pPropIndent->AddComboOption(_T("Yes"), _T("Y"),
		_T("void Foo()")
		_T("\r\n{")
		_T("\r\n    // comment")
		_T("\r\n    if (isFoo)")
		_T("\r\n        bar();")
		_T("\r\n}"));
	pPropIndent->AddComboOption(_T("No"), _T(""),
		_T("void Foo()")
		_T("\r\n{")
		_T("\r\n// comment")
		_T("\r\n    if (isFoo)")
		_T("\r\n        bar();")
		_T("\r\n}"));
	pGrouIndentation->AddSubItem(pPropIndent);
	m_wndPropList.AddProperty(pGrouIndentation);

	CMyBCGPProp* pGrouPadding = new CMyBCGPProp(_T("Padding"));
	CMyBCGPProp* pPropPadding = new CMyBCGPProp(_T("Break blocks"), _T("No"));
	pPropPadding->AddComboOption(_T("Yes"), _T("f"),
		_T("isFoo = true;")
		_T("\r\n")
		_T("\r\nif (isFoo) {")
		_T("\r\n    bar();")
		_T("\r\n} else {")
		_T("\r\n    anotherBar();")
		_T("\r\n}")
		_T("\r\n")
		_T("\r\nisBar = false;"));
	pPropPadding->AddComboOption(_T("No"), _T(""),
		_T("isFoo = true;")
		_T("\r\nif (isFoo) {")
		_T("\r\n    bar();")
		_T("\r\n} else {")
		_T("\r\n    anotherBar();")
		_T("\r\n}")
		_T("\r\nisBar = false;"));
	pGrouPadding->AddSubItem(pPropPadding);

	m_wndPropList.AddProperty(pGrouPadding);
	
}
