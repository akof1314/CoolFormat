#include "StdAfx.h"
#include "GlobalTidy.h"

TidyDeafult GlobalTidy::m_TidyNames[MAX_SYN_LANG] = {
	{_T("ActionScript"),		_T("*.as;*.mx;"),																			SYN_ACTIONSCRIPT},
	{_T("Ada"),					_T("*.ada;*.ads;*.adb;"),																	SYN_ADA},
	{_T("ASM"),					_T("*.asm;"),																				SYN_ASM},
	{_T("ASP"),					_T("*.asp;"),																				SYN_ASP},
	{_T("AutoHotkey"),			_T("*.ahk;*.ia;*.scriptlet;*.hkml;"),														SYN_AUTOHOTKEY},
	{_T("AutoIt"),				_T("*.au3;"),																				SYN_AUTOIT},
	{_T("Batch"),				_T("*.bat;*.cmd;*.nt;"),																	SYN_BATCH},
	{_T("COBOL"),				_T("*.cbl;*.cbd;*.cdb;*.cdc;*.cob;"),														SYN_COBOL},
	{_T("C++"),					_T("-A1-p-N-Y-k3"),																			SYN_CPP},
	{_T("C#"),					_T("-A1-p-N-Y-k3"),																			SYN_CS},
	{_T("CSS"),					_T("-c2-rub-cl0-os1-cc-cf-cfp0-rs2"),														SYN_CSS},
	{_T("D"),					_T("*.d;"),																					SYN_D},
	{_T("Fortran"),				_T("*.f;*.for;*.f90;*.f95;*.f2k;"),															SYN_FORTRAN},
	{_T("Haskell"),				_T("*.hs;*.lhs;*.las;"),																	SYN_HASKELL},
	{_T("HTML"),				_T("-aan-dep-fb-fbc-fu-js-ll-n-ox-pe-qa-qn-m-wa-wj-wp-ws-sw-fo-i0-d1-ce0-ie0-oe0-w0-sbo0"),		SYN_HTML},
	{_T("INI"),					_T("*.ini;*.inf;*.reg;*.url;"),																SYN_INI},
	{_T("Java"),				_T("-A1-p-N-Y-k3"),																			SYN_JAVA},
	{_T("JavaScript"),			_T("-nb-cn4"),																				SYN_JAVASCRIPT},
	{_T("JSON"),				_T("-cn3"),																					SYN_JSON},
	{_T("JSP"),					_T("*.jsp;"),																				SYN_JSP},
	{_T("LISP"),				_T("*.lsp;*.lisp;"),																		SYN_LISP},
	{_T("LUA"),					_T("*.lua;"),																				SYN_LUA},
	{_T("NormalText"),			_T("*.txt;"),																				SYN_NORMALTEXT},
	{_T("Objective-C"),			_T("*.h;*.m;*.mm;"),																		SYN_OBJECTIVEC},
	{_T("Pascal"),				_T("*.dpr;*.dpk;*.pas;*.dfm;*.inc;*.pp;"),													SYN_PASCAL},
	{_T("Perl"),				_T("*.pl;*.pm;*.plx;"),																		SYN_PERL},
	{_T("PHP"),					_T("-sas-icd-samt-salo-saeo-saro-sabo-saao-samp-aas-rsl-iel-rpc-rst-st"),					SYN_PHP},
	{_T("Python"),				_T("*.py;*.pyw;"),																			SYN_PYTHON},
	{_T("Ruby"),				_T("*.rb;*.rbw;"),																			SYN_RUBY},
	{_T("SQL"),					_T("-cn2-el-ml0"),																			SYN_SQL},
	{_T("VB"),					_T("*.vb;*.bas;*.frm;*.cls;*.ctl;*.pag;*.dsr;*.dob;*.vbs;*.dsm;*.vbp;*.vbg;*.mak;*.vbw;"),	SYN_VB},
	{_T("Verilog"),				_T("*.v;*.vl;*.vmd;"),																		SYN_VERILOG},
	{_T("VHDL"),				_T("*.vhd;*.vhdl;*.vho;"),																	SYN_VHDL},
	{_T("XML"),					_T("-aan-dep-fb-fbc-js-ll-n-ix-qa-qn-m-wa-wj-wp-ws-sw-fo-i1-ce0-ie0-oe0-w0"),				SYN_XML}
};

GlobalTidy g_GlobalTidy;

GlobalTidy::GlobalTidy(void)
{
}

GlobalTidy::~GlobalTidy(void)
{
}

void GlobalTidy::InitGlobalTidy()
{
	for(int i = 0; i <= SYN_XML; ++i)
	{
		m_bTidySyn[i] = FALSE;
	}
	m_bTidySyn[SYN_CPP] = TRUE;
	m_bTidySyn[SYN_CS] = TRUE;
	m_bTidySyn[SYN_JAVA] = TRUE;
	m_bTidySyn[SYN_HTML] = TRUE;
	m_bTidySyn[SYN_XML] = TRUE;
	m_bTidySyn[SYN_PHP] = TRUE;
	m_bTidySyn[SYN_JAVASCRIPT] = TRUE;
	m_bTidySyn[SYN_CSS] = TRUE;
	m_bTidySyn[SYN_JSON] = TRUE;
	m_bTidySyn[SYN_SQL] = TRUE;

	CString strTidy;
	LPCTSTR lpszSubSection = _T("SynTidy");
	CString strSection = GetWorkspace()->GetRegSectionPath(lpszSubSection);

	CBCGPRegistrySP regSP;
	CBCGPRegistry& reg = regSP.Create (FALSE, TRUE);

	if (reg.Open (strSection))
	{
		if (!reg.Read(m_TidyNames[SYN_CPP].langName, strTidy))
		{
			strTidy = m_TidyNames[SYN_CPP].tidyName;
		}
		m_TidyCpp = strTidy;

		if (!reg.Read(m_TidyNames[SYN_JAVA].langName, strTidy))
		{
			strTidy = m_TidyNames[SYN_JAVA].tidyName;
		}
		m_TidyJava = strTidy;

		if (!reg.Read(m_TidyNames[SYN_CS].langName, strTidy))
		{
			strTidy = m_TidyNames[SYN_CS].tidyName;
		}
		m_TidyCSharp = strTidy;

		if (!reg.Read(m_TidyNames[SYN_HTML].langName, strTidy))
		{
			strTidy = m_TidyNames[SYN_HTML].tidyName;
		}
		m_TidyHtml = strTidy;

		if (!reg.Read(m_TidyNames[SYN_XML].langName, strTidy))
		{
			strTidy = m_TidyNames[SYN_XML].tidyName;
		}
		m_TidyXml = strTidy;

		if (!reg.Read(m_TidyNames[SYN_PHP].langName, strTidy))
		{
			strTidy = m_TidyNames[SYN_PHP].tidyName;
		}
		m_TidyPhp = strTidy;

		if (!reg.Read(m_TidyNames[SYN_JAVASCRIPT].langName, strTidy))
		{
			strTidy = m_TidyNames[SYN_JAVASCRIPT].tidyName;
		}
		m_TidyJs = strTidy;

		if (!reg.Read(m_TidyNames[SYN_CSS].langName, strTidy))
		{
			strTidy = m_TidyNames[SYN_CSS].tidyName;
		}
		m_TidyCss = strTidy;

		if (!reg.Read(m_TidyNames[SYN_JSON].langName, strTidy))
		{
			strTidy = m_TidyNames[SYN_JSON].tidyName;
		}
		m_TidyJson = strTidy;

		if (!reg.Read(m_TidyNames[SYN_SQL].langName, strTidy))
		{
			strTidy = m_TidyNames[SYN_SQL].tidyName;
		}
		m_TidySql = strTidy;

		if (!reg.Read(_T("HTMLat"), strTidy))
		{
			strTidy.Empty();
		}
		m_TidyHtml_at = strTidy;

		if (!reg.Read(_T("HTMLcp"), strTidy))
		{
			strTidy.Empty();
		}
		m_TidyHtml_cp = strTidy;

		if (!reg.Read(_T("HTMLnbt"), strTidy))
		{
			strTidy.Empty();
		}
		m_TidyHtml_nbt  = strTidy;

		if (!reg.Read(_T("HTMLnet"), strTidy))
		{
			strTidy.Empty();
		}
		m_TidyHtml_net = strTidy;

		if (!reg.Read(_T("HTMLnit"), strTidy))
		{
			strTidy.Empty();
		}
		m_TidyHtml_nit = strTidy;

		if (!reg.Read(_T("HTMLnpt"), strTidy))
		{
			strTidy.Empty();
		}
		m_TidyHtml_npt = strTidy;
	}
	else
	{
		m_TidyCpp = m_TidyNames[SYN_CPP].tidyName;
		m_TidyJava = m_TidyNames[SYN_JAVA].tidyName;
		m_TidyCSharp = m_TidyNames[SYN_CS].tidyName;
		m_TidyHtml = m_TidyNames[SYN_HTML].tidyName;
		m_TidyXml = m_TidyNames[SYN_XML].tidyName;
		m_TidyPhp = m_TidyNames[SYN_PHP].tidyName;
		m_TidyJs = m_TidyNames[SYN_JAVASCRIPT].tidyName;
		m_TidyCss = m_TidyNames[SYN_CSS].tidyName;
		m_TidyJson = m_TidyNames[SYN_JSON].tidyName;
		m_TidySql = m_TidyNames[SYN_SQL].tidyName;
	}
}