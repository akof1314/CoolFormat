#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\..\CoolFormat\stdafx.h"
#include "FormatterHelp.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(UnitTestCpp)
{
public:
	void DoFormatterAssert(const char *pOptions, const CString &strTextIn, const CString &strTextNeedOut)
	{
		CFormatterHelp formatterSP;
		CString strTextOut, strMsgOut;
		g_GlobalTidy.m_TidyCpp = pOptions;
		formatterSP.DoFormatter(SYN_CPP, strTextIn, strTextOut, strMsgOut, _AtlGetConversionACP());
		Assert::AreEqual(strTextNeedOut.GetString(), strTextOut.GetString());
	}

	TEST_METHOD(StyleDefaultCpp)
	{
		CString strTextIn(
			"\nnamespace FooName\n"
			"{\n"
			"\n"
			"class FooClass\n"
			"{\n"
			"private:\n"
			"    bool var1;\n"
			"    void func1();\n"
			"protected:\n"
			"    bool var2;\n"
			"    void func2();\n"
			"};\n"
			"\n"
			"void FooClass::Foo(bool isFoo)\n"
			"{\n"
			"    if (isFoo)\n"
			"    {\n"
			"        bar();\n"
			"    }\n"
			"    else\n"
			"        anotherBar();\n"
			"}\n"
			"\n"
			"}   // end FooName\n");
		DoFormatterAssert("", strTextIn, strTextIn);
	}

	TEST_METHOD(Tab)
	{
		CString strTextIn(
			"\nvoid Foo(bool isFoo)\n"
			"{\n"
			"    if (isFoo\n"
			"            && isBar)\n"
			"    {\n"
			"        bar();\n"
			"    }\n"
			"    else\n"
			"        anotherBar();\n"
			"}\n");
		CString strTextOut(
			"\nvoid Foo(bool isFoo)\n"
			"{\n"
			"	if (isFoo\n"
			"	        && isBar)\n"
			"	{\n"
			"		bar();\n"
			"	}\n"
			"	else\n"
			"		anotherBar();\n"
			"}\n");
		DoFormatterAssert("-t", strTextIn, strTextOut);
	}

	TEST_METHOD(IndentClasses)
	{
		CString strTextIn(
			"\nnamespace FooName\n"
			"{\n"
			"\n"
			"class FooClass\n"
			"{\n"
			"    private:\n"
			"        bool var1;\n"
			"        void func1();\n"
			"    protected:\n"
			"        bool var2;\n"
			"        void func2();\n"
			"};\n"
			"\n"
			"void FooClass::Foo(bool isFoo)\n"
			"{\n"
			"    if (isFoo)\n"
			"    {\n"
			"        bar();\n"
			"    }\n"
			"    else\n"
			"    {\n"
			"        anotherBar();\n"
			"    }\n"
			"}\n"
			"\n"
			"}   // end FooName\n");
		DoFormatterAssert("-C", strTextIn, strTextIn);
	}

	TEST_METHOD(PadOperator)
	{
		CString strTextIn(
			"\nstruct Bar\n"
			"{\n"
			"    int foo = 2;\n"
			"    int bar = 4;\n"
			"    int baz = foo*bar;\n"
			"};");
		CString strTextOut(
			"\nstruct Bar\n"
			"{\n"
			"    int foo = 2;\n"
			"    int bar = 4;\n"
			"    int baz = foo * bar;\n"
			"};");
		DoFormatterAssert("-p-k1", strTextIn, strTextOut);
	}
};

TEST_CLASS(UnitTestJS)
{
public:
	void DoFormatterAssert(const char *pOptions, const CString &strTextIn, const CString &strTextNeedOut)
	{
		CFormatterHelp formatterSP;
		CString strTextOut, strMsgOut;
		g_GlobalTidy.m_TidyJs = pOptions;
		formatterSP.DoFormatter(SYN_JAVASCRIPT, strTextIn, strTextOut, strMsgOut, _AtlGetConversionACP());
		Assert::AreEqual(strTextNeedOut.GetString(), strTextOut.GetString());
	}

	TEST_METHOD(Indent)
	{
		CString strTextIn(
			"if ('this_is' == /an_example/) {\n"
			"    of_beautifer();\n"
			"} else {\n"
			"    var a = b ? (c % d) : e[f];\n"
			"}\n");
		CString strTextOut(
			"if ('this_is' == /an_example/) {\n"
			"     of_beautifer();\n"
			"} else {\n"
			"     var a = b ? (c % d) : e[f];\n"
			"}\n");
		DoFormatterAssert("-cn5", strTextIn, strTextOut);
	}

	TEST_METHOD(IndentStyle)
	{
		CString strTextIn(
			"if ('this_is' == /an_example/) {\n"
			"    of_beautifer();\n"
			"} else {\n"
			"    var a = b ? (c % d) : e[f];\n"
			"}\n");
		CString strTextOut(
			"if ('this_is' == /an_example/)\n"
			"{\n"
			"     of_beautifer();\n"
			"}\n"
			"else\n"
			"{\n"
			"     var a = b ? (c % d) : e[f];\n"
			"}\n");
		DoFormatterAssert("-cn5-nb", strTextIn, strTextOut);
	}
};

TEST_CLASS(UnitTestJson)
{
public:
	void DoFormatterAssert(const char *pOptions, const CString &strTextIn, const CString &strTextNeedOut)
	{
		CFormatterHelp formatterSP;
		CString strTextOut, strMsgOut;
		g_GlobalTidy.m_TidyJson = pOptions;
		formatterSP.DoFormatter(SYN_JSON, strTextIn, strTextOut, strMsgOut, _AtlGetConversionACP());
		Assert::AreEqual(strTextNeedOut.GetString(), strTextOut.GetString());
	}

	TEST_METHOD(Indent)
	{
		CString strTextIn(
			"{\n"
			"   \"test\" : 123\n"
			"}");
		CString strTextOut(
			"{\n"
			"    \"test\" : 123\n"
			"}");
		DoFormatterAssert("-cn4", strTextIn, strTextOut);
	}
};

TEST_CLASS(UnitTestHTML)
{
public:
	void DoFormatterAssert(const char *pOptions, const CString &strTextIn, const CString &strTextNeedOut)
	{
		CFormatterHelp formatterSP;
		CString strTextOut, strMsgOut;
		g_GlobalTidy.m_TidyHtml = pOptions;
		formatterSP.DoFormatter(SYN_HTML, strTextIn, strTextOut, strMsgOut, _AtlGetConversionACP());
		Assert::AreEqual(strTextNeedOut.GetString(), strTextOut.GetString());
	}

	TEST_METHOD(Indent)
	{
		CString strTextIn(
			"<ol>\n"
			"<li>Coffee</li>\n"
			"</ol>\n");
		CString strTextOut(
			"<ol>\n"
			"  <li>Coffee</li>\n"
			"</ol>\n");
		DoFormatterAssert("-m-ox-sbo0-i0", strTextIn, strTextOut);
	}
};

TEST_CLASS(UnitTestXML)
{
public:
	void DoFormatterAssert(const char *pOptions, const CString &strTextIn, const CString &strTextNeedOut)
	{
		CFormatterHelp formatterSP;
		CString strTextOut, strMsgOut;
		g_GlobalTidy.m_TidyXml = pOptions;
		formatterSP.DoFormatter(SYN_XML, strTextIn, strTextOut, strMsgOut, _AtlGetConversionACP());
		Assert::AreEqual(strTextNeedOut.GetString(), strTextOut.GetString());
	}

	TEST_METHOD(Indent)
	{
		CString strTextIn(
			"<note>\n"
			"<to>George</to>\n"
			"<from>John</from>\n"
			"</note>\n");
		CString strTextOut(
			"<note>\n"
			"  <to>George</to>\n"
			"  <from>John</from>\n"
			"</note>\n");
		DoFormatterAssert("-m-ix-sbo0-i0", strTextIn, strTextOut);
	}
};

TEST_CLASS(UnitTestSQL)
{
public:
	void DoFormatterAssert(const char *pOptions, const CString &strTextIn, const CString &strTextNeedOut)
	{
		CFormatterHelp formatterSP;
		CString strTextOut, strMsgOut;
		g_GlobalTidy.m_TidySql = pOptions;
		formatterSP.DoFormatter(SYN_SQL, strTextIn, strTextOut, strMsgOut, _AtlGetConversionACP());
		Assert::AreEqual(strTextNeedOut.GetString(), strTextOut.GetString());
	}

	TEST_METHOD(Indent)
	{
		CString strTextIn(
			"select\n"
			"  id\n"
			"from\n"
			"  a\n"
			"where\n"
			"  a.id = 1");
		CString strTextOut(
			"select\n"
			"    id\n"
			"from\n"
			"    a\n"
			"where\n"
			"    a.id = 1");
		DoFormatterAssert("-cn4", strTextIn, strTextOut);
	}

	TEST_METHOD(IndentTab)
	{
		CString strTextIn(
			"select\n"
			"  id\n"
			"from\n"
			"  a\n"
			"where\n"
			"  a.id = 1");
		CString strTextOut(
			"select\n"
			"		id\n"
			"from\n"
			"		a\n"
			"where\n"
			"		a.id = 1");
		DoFormatterAssert("-ci1-cn2", strTextIn, strTextOut);
	}
};

TEST_CLASS(UnitTestPHP)
{
public:
	void DoFormatterAssert(const char *pOptions, const CString &strTextIn, const CString &strTextNeedOut)
	{
		CFormatterHelp formatterSP;
		CString strTextOut, strMsgOut;
		g_GlobalTidy.m_TidyPhp = pOptions;
		formatterSP.DoFormatter(SYN_PHP, strTextIn, strTextOut, strMsgOut, _AtlGetConversionACP());
		Assert::AreEqual(strTextNeedOut.GetString(), strTextOut.GetString());
	}

	TEST_METHOD(Indent)
	{
		CString strTextIn(
			"<?php\n"
			"function foo()\n"
			"{\n"
			"    echo \"a is bigger than b\";\n"
			"}\n"
			"?>");
		CString strTextOut(
			"<?php\n"
			"function foo()\n"
			"{\n"
			"     echo \"a is bigger than b\";\n"
			"}\n"
			"?>");
		DoFormatterAssert("-in5", strTextIn, strTextOut);
	}

	TEST_METHOD(IndentTab)
	{
		CString strTextIn(
			"<?php\n"
			"function foo()\n"
			"{\n"
			"    echo \"a is bigger than b\";\n"
			"}\n"
			"?>");
		CString strTextOut(
			"<?php\n"
			"function foo()\n"
			"{\n"
			"		echo \"a is bigger than b\";\n"
			"}\n"
			"?>");
		DoFormatterAssert("-in2-ich1", strTextIn, strTextOut);
	}
};

TEST_CLASS(UnitTestCSS)
{
public:
	void DoFormatterAssert(const char *pOptions, const CString &strTextIn, const CString &strTextNeedOut)
	{
		CFormatterHelp formatterSP;
		CString strTextOut, strMsgOut;
		g_GlobalTidy.m_TidyCss = pOptions;
		formatterSP.DoFormatter(SYN_CSS, strTextIn, strTextOut, strMsgOut, _AtlGetConversionACP());
		Assert::AreEqual(strTextNeedOut.GetString(), strTextOut.GetString());
	}

	TEST_METHOD(Indent)
	{
		CString strTextIn(
			"h1{color:red;}h2{color:black;}");
		CString strTextOut(
			"h1\n"
			"{\n"
			"	color:red;\n"
			"}\n"
			"\n"
			"h2\n"
			"{\n"
			"	color:black;\n"
			"}");
		DoFormatterAssert("-c3", strTextIn, strTextOut);
	}

	TEST_METHOD(IndentSort)
	{
		CString strTextIn(
			"h2{color:black;}\n"
			"h1{color:red;}");
		CString strTextOut(
			"h1\n"
			"{\n"
			"	color:red;\n"
			"}\n"
			"\n"
			"h2\n"
			"{\n"
			"	color:black;\n"
			"}");
		DoFormatterAssert("-c3-ss", strTextIn, strTextOut);
	}
};

TEST_CLASS(UnitTestObjC)
{
public:
	void DoFormatterAssert(const char *pOptions, const CString &strTextIn, const CString &strTextNeedOut)
	{
		CFormatterHelp formatterSP;
		CString strTextOut, strMsgOut;
		g_GlobalTidy.m_TidyObjectiveC = pOptions;
		formatterSP.DoFormatter(SYN_OBJECTIVEC, strTextIn, strTextOut, strMsgOut, _AtlGetConversionACP());
		Assert::AreEqual(strTextNeedOut.GetString(), strTextOut.GetString());
	}

	TEST_METHOD(ObjCUnPadMethodPrefix)
	{
		CString strTextIn(
			"\n"
			"-(void)Foo1;\n"
			"+ (void)Foo2;\n"
			"-    (void)Foo3;\n"
			"\n"
			"-(void)Foo4\n"
			"{ }");
		CString strTextOut(
			"\n"
			"-(void)Foo1;\n"
			"+(void)Foo2;\n"
			"-(void)Foo3;\n"
			"\n"
			"-(void)Foo4\n"
			"{ }");
		DoFormatterAssert("-xR", strTextIn, strTextOut);
	}
};
