#pragma once

enum{
	SYN_ACTIONSCRIPT = 0,
	SYN_ADA,	
	SYN_ASM,	
	SYN_ASP,
	SYN_AUTOHOTKEY,
	SYN_AUTOIT,
	SYN_BATCH,
	SYN_COBOL,
	SYN_CPP,
	SYN_CS,
	SYN_CSS,
	SYN_D,
	SYN_FORTRAN,
	SYN_HASKELL,
	SYN_HTML,
	SYN_INI,
	SYN_JAVA,
	SYN_JAVASCRIPT,
	SYN_JSON,
	SYN_JSP,
	SYN_LISP,
	SYN_LUA,
	SYN_NORMALTEXT,
	SYN_OBJECTIVEC,
	SYN_PASCAL,
	SYN_PERL,
	SYN_PHP,
	SYN_PYTHON,
	SYN_RUBY,
	SYN_SQL,
	SYN_VB,
	SYN_VERILOG,
	SYN_VHDL,
	SYN_XML,
};

const UINT MAX_SYN_LANG = SYN_XML + 1;

class CSynLanguage
{
public:
	CSynLanguage(void);
	~CSynLanguage(void);

	void SetCurLanguage(UINT nLanguage);
	UINT GetCurLanguage(){return m_nLanguage;}

	/************************************************************************/
	/* 介绍了适用于编辑控件的常用设置                              */
	/************************************************************************/
	CString GetWordDelimeters();
	CString GetSpecialDelimiters();
	CString GetIntelliSenseChars();
	CString GetEscapeSequences();

	/************************************************************************/
	/* 用于语法高亮定义                                            */
	/************************************************************************/
	void GetWords(CString &strWords, BOOL &bCaseSensitive);
	void GetTypeWords(CString &strWords, BOOL &bCaseSensitive);
	void GetMultilineComment(CString &strBlockOpen, CString &strBlockClose, BOOL &bCaseSensitive);
	void GetLineComment(CString &strBlocks, BOOL &bCaseSensitive);
	void GetString(CString &strBlockOpen, CString &strBlockClose, BOOL &bCaseSensitive);
	void GetChar(CString &strBlockOpen, CString &strBlockClose, BOOL &bCaseSensitive);
	void GetIsNumberColor(BOOL &bNumberColor);

	/************************************************************************/
	/* 定义大纲解析器设置                                          */
	/************************************************************************/
	BOOL GetOutlineCaseSensitive();
	BOOL GetOutlineWholeWords();
	void GetOutlineEscapeSequences(CString &strEscapeSequences);
	void GetOutlineBlockType(CString &strBlocks);

private:
	UINT m_nLanguage;
};
