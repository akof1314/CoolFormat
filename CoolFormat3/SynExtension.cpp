#include "StdAfx.h"
#include "CoolFormat3.h"
#include "SynExtension.h"

LanguageName CSynExtension::m_LangNames[MAX_SYN_LANG] = {
	{_T("ActionScript"),		_T("*.as;*.mx;"),																			SYN_ACTIONSCRIPT},
	{_T("Ada"),					_T("*.ada;*.ads;*.adb;"),																	SYN_ADA},
	{_T("ASM"),					_T("*.asm;"),																				SYN_ASM},
	{_T("ASP"),					_T("*.asp;"),																				SYN_ASP},
	{_T("AutoHotkey"),			_T("*.ahk;*.ia;*.scriptlet;*.hkml;"),														SYN_AUTOHOTKEY},
	{_T("AutoIt"),				_T("*.au3;"),																				SYN_AUTOIT},
	{_T("Batch"),				_T("*.bat;*.cmd;*.nt;"),																	SYN_BATCH},
	{_T("COBOL"),				_T("*.cbl;*.cbd;*.cdb;*.cdc;*.cob;"),														SYN_COBOL},
	{_T("C++"),					_T("*.h;*.hpp;*.hxx;*.cpp;*.cxx;*.cc;*.c;"),												SYN_CPP},
	{_T("C#"),					_T("*.cs;"),																				SYN_CS},
	{_T("CSS"),					_T("*.css;"),																				SYN_CSS},
	{_T("D"),					_T("*.d;"),																					SYN_D},
	{_T("Fortran"),				_T("*.f;*.for;*.f90;*.f95;*.f2k;"),															SYN_FORTRAN},
	{_T("Haskell"),				_T("*.hs;*.lhs;*.las;"),																	SYN_HASKELL},
	{_T("HTML"),				_T("*.html;*.htm;*.shtml;*.shtm;*.xhtml;"),													SYN_HTML},
	{_T("INI"),					_T("*.ini;*.inf;*.reg;*.url;"),																SYN_INI},
	{_T("Java"),				_T("*.java;"),																				SYN_JAVA},
	{_T("JavaScript"),			_T("*.js;"),																				SYN_JAVASCRIPT},
	{_T("JSON"),				_T("*.json;"),																				SYN_JSON},
	{_T("JSP"),					_T("*.jsp;"),																				SYN_JSP},
	{_T("LISP"),				_T("*.lsp;*.lisp;"),																		SYN_LISP},
	{_T("LUA"),					_T("*.lua;"),																				SYN_LUA},
	{_T("NormalText"),			_T("*.txt;"),																				SYN_NORMALTEXT},
	{_T("Objective-C"),			_T("*.h;*.m;*.mm;"),																		SYN_OBJECTIVEC},
	{_T("Pascal"),				_T("*.dpr;*.dpk;*.pas;*.dfm;*.inc;*.pp;"),													SYN_PASCAL},
	{_T("Perl"),				_T("*.pl;*.pm;*.plx;"),																		SYN_PERL},
	{_T("PHP"),					_T("*.php;*.php3;*.php4;*.php5;*.phtml;"),													SYN_PHP},
	{_T("Python"),				_T("*.py;*.pyw;"),																			SYN_PYTHON},
	{_T("Ruby"),				_T("*.rb;*.rbw;"),																			SYN_RUBY},
	{_T("SQL"),					_T("*.sql;"),																				SYN_SQL},
	{_T("VB"),					_T("*.vb;*.bas;*.frm;*.cls;*.ctl;*.pag;*.dsr;*.dob;*.vbs;*.dsm;*.vbp;*.vbg;*.mak;*.vbw;"),	SYN_VB},
	{_T("Verilog"),				_T("*.v;*.vl;*.vmd;"),																		SYN_VERILOG},
	{_T("VHDL"),				_T("*.vhd;*.vhdl;*.vho;"),																	SYN_VHDL},
	{_T("XML"),					_T("*.xml;*.xsl;*.svg;*.xul;*.xsd;*.dtd;*.xslt;*.axl;*.xrc;*.rdf;"),						SYN_XML}
};

CSynExtension::CSynExtension(void)
{
}

CSynExtension::~CSynExtension(void)
{
}

void CSynExtension::InitLanguageExt()
{
	CString strExt;
	LPCTSTR lpszSubSection = _T("SynExt");
	CString strSection = theApp.GetRegSectionPath(lpszSubSection);

	CBCGPRegistrySP regSP;
	CBCGPRegistry& reg = regSP.Create (FALSE, TRUE);

	if (reg.Open (strSection))
	{
		for (UINT i = 0; i < MAX_SYN_LANG; i++)
		{
			if (!reg.Read(m_LangNames[i].langName, strExt))
			{
				strExt = m_LangNames[i].extName;
			}
			m_mapLangExt.SetAt(m_LangNames[i].langID, strExt);
		}		
	}
	else
	{
		for (UINT i = 0; i < MAX_SYN_LANG; i++)
		{			
			strExt = m_LangNames[i].extName;
			m_mapLangExt.SetAt(m_LangNames[i].langID, strExt);
		}		
	}
}

UINT CSynExtension::GetLanguageByExt( CString strExt )
{
	int nIndex;
	CString strLangExt;
	CString strExts;
	strLangExt.Format(_T("*.%s;"), strExt);
	strLangExt.MakeLower();
	POSITION pos = m_mapLangExt.GetStartPosition();
	while (pos)
	{
		m_mapLangExt.GetNextAssoc(pos, nIndex, strExts);
		if (strExts.Find(strLangExt) != -1)
		{
			return nIndex;
		}
	}
	return SYN_NORMALTEXT;
}

LPCTSTR CSynExtension::GetLanguageString( UINT nLanguage )
{
	if (nLanguage < MAX_SYN_LANG)
	{
		return m_LangNames[nLanguage].langName;
	}
	return _T("");
}

void CSynExtension::GetAllLanguageFilter(CString &strFilter)
{
	strFilter = _T("All Files(*.*)|*.*|");
	CString strExt;
	for (UINT i = 0; i < MAX_SYN_LANG; i++)
	{
		if (m_mapLangExt.Lookup(i, strExt))
		{
			strFilter.AppendFormat(_T("%s Files(%s)|%s|"), m_LangNames[i].langName, strExt, strExt);
		}
		else
		{
			strFilter.AppendFormat(_T("%s Files(%s)|%s|"), m_LangNames[i].langName, m_LangNames[i].extName, m_LangNames[i].extName);
		}
	}
	strFilter.Append(_T("|"));
}

void CSynExtension::GetLanguageOneFilter( UINT nLanguage, CString &strFilter )
{
	if (nLanguage < MAX_SYN_LANG)
	{
		if (m_mapLangExt.Lookup(nLanguage, strFilter))
		{
		}
		else
		{
			strFilter = m_LangNames[nLanguage].extName;
		}
		int nFirst = strFilter.Find(_T('.'));
		int nCount = strFilter.Find(_T(';')) - nFirst;
		strFilter = strFilter.Mid(nFirst, nCount);
	}
	else
		strFilter.Empty();
}

void CSynExtension::GetLanguageFilter( UINT nLanguage, CString &strFilter )
{
	if (nLanguage < MAX_SYN_LANG)
	{
		if (m_mapLangExt.Lookup(nLanguage, strFilter))
		{
		}
		else
		{
			strFilter = m_LangNames[nLanguage].extName;
		}		
	}
	else
		strFilter.Empty();
}

void CSynExtension::SetLanguageFilter( UINT nLanguage, CString &strFilter )
{
	if (nLanguage < MAX_SYN_LANG)
	{
		m_mapLangExt.SetAt(nLanguage, strFilter);			
	}
}

bool CSynExtension::IsDocSupport( LPCTSTR strExt )
{
	if (strExt == NULL)
	{
		return false;
	}
	if (0 == _tcscmp(strExt, _T(".exe"))
		|| 0 == _tcscmp(strExt, _T(".chm"))
		|| 0 == _tcscmp(strExt, _T(".pdf"))
		|| 0 == _tcscmp(strExt, _T(".doc"))
		|| 0 == _tcscmp(strExt, _T(".jpg")))
	{
		return false;
	}
	return true;
}