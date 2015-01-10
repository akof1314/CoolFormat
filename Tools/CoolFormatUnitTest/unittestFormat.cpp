#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\..\CoolFormat3\stdafx.h"
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
		Assert::AreEqual(strTextNeedOut.Compare(strTextOut), 0);
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
		Assert::AreEqual(strTextNeedOut.Compare(strTextOut), 0);
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
		Assert::AreEqual(strTextNeedOut.Compare(strTextOut), 0);
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
