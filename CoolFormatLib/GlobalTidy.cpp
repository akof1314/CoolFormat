#include "stdafx.h"
#include <fstream>
#include "GlobalTidy.h"
#include "StrUseful.h"

TidyDeafult GlobalTidy::m_TidyNames[MAX_SYN_LANG] = {
    {"ActionScript",				("*.as;*.mx;"),																			SYN_ACTIONSCRIPT},
    {"Ada",							("*.ada;*.ads;*.adb;"),																	SYN_ADA},
    {"ASM",							("*.asm;"),																				SYN_ASM},
    {"ASP",							("*.asp;"),																				SYN_ASP},
    {"AutoHotkey",                  ("*.ahk;*.ia;*.scriptlet;*.hkml;"),														SYN_AUTOHOTKEY},
    {"AutoIt",                      ("*.au3;"),																				SYN_AUTOIT},
    {"Batch",						("*.bat;*.cmd;*.nt;"),																	SYN_BATCH},
    {"COBOL",						("*.cbl;*.cbd;*.cdb;*.cdc;*.cob;"),														SYN_COBOL},
    {"C++",							("-A1-p-N-Y-k3"),																			SYN_CPP},
    {"C#",                          ("-A1-p-N-Y-k3"),																			SYN_CS},
    {"CSS",							("-c2-rub-cl0-os1-cc-cf-cfp0-rs2"),														SYN_CSS},
    {"D",							("*.d;"),																					SYN_D},
    {"Fortran",						("*.f;*.for;*.f90;*.f95;*.f2k;"),															SYN_FORTRAN},
    {"Haskell",						("*.hs;*.lhs;*.las;"),																	SYN_HASKELL},
    {"HTML",							("-aan-dep-fb-fbc-fu-js-ll-n-ox-pe-qa-qn-m-wa-wj-wp-ws-sw-fo-i0-d1-ce0-ie0-oe0-w0-sbo0"),	SYN_HTML},
    {"INI",							("*.ini;*.inf;*.reg;*.url;"),																SYN_INI},
    {"Java",						("-A1-p-N-Y-k3"),																			SYN_JAVA},
    {"JavaScript",                  ("-nb-cn4"),																				SYN_JAVASCRIPT},
    {"JSON",						("-cn3"),																					SYN_JSON},
    {"JSP",							("*.jsp;"),																				SYN_JSP},
    {"LISP",						("*.lsp;*.lisp;"),																		SYN_LISP},
    {"LUA",							("*.lua;"),																				SYN_LUA},
    {"NormalText",                  ("*.txt;"),																				SYN_NORMALTEXT},
    {"Objective-C",					("-A1-p-N-Y-k3"),																			SYN_OBJECTIVEC},
    {"Pascal",						("*.dpr;*.dpk;*.pas;*.dfm;*.inc;*.pp;"),													SYN_PASCAL},
    {"Perl",							("*.pl;*.pm;*.plx;"),																		SYN_PERL},
    {"PHP",							("-sas-icd-samt-salo-saeo-saro-sabo-saao-samp-aas-rsl-iel-rpc-rst-st"),					    SYN_PHP},
    {"Python",                      ("*.py;*.pyw;"),																			SYN_PYTHON},
    {"Ruby",						("*.rb;*.rbw;"),																			SYN_RUBY},
    {"SQL",							("-cn2-el-ml0"),																			SYN_SQL},
    {"VB",                          ("*.vb;*.bas;*.frm;*.cls;*.ctl;*.pag;*.dsr;*.dob;*.vbs;*.dsm;*.vbp;*.vbg;*.mak;*.vbw;"),	SYN_VB},
    {"Verilog",						("-A1"),																		            SYN_VERILOG},
    {"VHDL",							("*.vhd;*.vhdl;*.vho;"),																	SYN_VHDL},
    {"XML",							("-aan-dep-fb-fbc-js-ll-n-ix-qa-qn-m-wa-wj-wp-ws-sw-fo-i1-ce0-ie0-oe0-w0"),				    SYN_XML}
};

GlobalTidy g_GlobalTidy;

GlobalTidy::GlobalTidy(void)
{
}

GlobalTidy::~GlobalTidy(void)
{
}

void GlobalTidy::InitGlobalTidy(const std::string &strDllPath)
{
	for(int i = 0; i <= SYN_XML; ++i)
	{
        m_bTidySyn[i] = false;
	}
    m_bTidySyn[SYN_CPP] = true;
    m_bTidySyn[SYN_CS] = true;
    m_bTidySyn[SYN_JAVA] = true;
    m_bTidySyn[SYN_OBJECTIVEC] = true;
    m_bTidySyn[SYN_HTML] = true;
    m_bTidySyn[SYN_XML] = true;
    m_bTidySyn[SYN_PHP] = true;
    m_bTidySyn[SYN_JAVASCRIPT] = true;
    m_bTidySyn[SYN_CSS] = true;
    m_bTidySyn[SYN_JSON] = true;
    m_bTidySyn[SYN_SQL] = true;
    m_bTidySyn[SYN_VERILOG] = true;

	m_TidyCpp = m_TidyNames[SYN_CPP].tidyName;
	m_TidyJava = m_TidyNames[SYN_JAVA].tidyName;
	m_TidyCSharp = m_TidyNames[SYN_CS].tidyName;
	m_TidyObjectiveC = m_TidyNames[SYN_OBJECTIVEC].tidyName;
	m_TidyHtml = m_TidyNames[SYN_HTML].tidyName;
	m_TidyXml = m_TidyNames[SYN_XML].tidyName;
	m_TidyPhp = m_TidyNames[SYN_PHP].tidyName;
	m_TidyJs = m_TidyNames[SYN_JAVASCRIPT].tidyName;
	m_TidyCss = m_TidyNames[SYN_CSS].tidyName;
	m_TidyJson = m_TidyNames[SYN_JSON].tidyName;
    m_TidySql = m_TidyNames[SYN_SQL].tidyName;
    m_TidyVerilog = m_TidyNames[SYN_VERILOG].tidyName;
	LoadGlobalTidy(strDllPath);
}

bool GlobalTidy::LoadGlobalTidy(const std::string &strDllPath)
{
#ifdef USE_LOCAL_CONFIG_FILE
	return LoadFromFile(strDllPath);
#else
	return LoadFromReg();
#endif
}

bool GlobalTidy::LoadFromReg()
{
#ifdef _WIN32
	std::string strTidy;
	HKEY hKEY;
    const char *lpszSection = "Software\\CoolFormat\\CoolFormat3\\Settings\\SynTidy";

	if (RegOpenKeyExA(HKEY_CURRENT_USER, lpszSection, 0, KEY_READ, &hKEY) == ERROR_SUCCESS)
	{
		auto readKey = [&hKEY](const char * pszKey, std::string &sVal){
			UINT  nBytes = 0;
			DWORD dwType = 0;
			DWORD dwCount = 0;

			LONG lResult = ::RegQueryValueExA(hKEY, pszKey, NULL, &dwType,
				NULL, &dwCount);

			if (lResult == ERROR_SUCCESS && dwCount > 0)
			{
				nBytes = dwCount;

				BYTE* pData = new BYTE[nBytes + 1];

				lResult = ::RegQueryValueExA(hKEY, pszKey, NULL, &dwType,
					pData, &dwCount);

				if (lResult == ERROR_SUCCESS &&  dwCount > 0)
				{
					sVal = (char*)pData;
				}
				else
				{
					sVal.clear();
				}

				delete[] pData;
				pData = NULL;
			}
			else
			{
				sVal.clear();
			}

			return lResult == ERROR_SUCCESS;
		};

		if (readKey(m_TidyNames[SYN_CPP].langName, strTidy))
		{
			m_TidyCpp = strTidy;
		}

		if (readKey(m_TidyNames[SYN_JAVA].langName, strTidy))
		{
			m_TidyJava = strTidy;
		}

		if (readKey(m_TidyNames[SYN_CS].langName, strTidy))
		{
			m_TidyCSharp = strTidy;
		}

		if (readKey(m_TidyNames[SYN_OBJECTIVEC].langName, strTidy))
		{
			m_TidyObjectiveC = strTidy;
		}

		if (readKey(m_TidyNames[SYN_HTML].langName, strTidy))
		{
			m_TidyHtml = strTidy;
		}

		if (readKey(m_TidyNames[SYN_XML].langName, strTidy))
		{
			m_TidyXml = strTidy;
		}

		if (readKey(m_TidyNames[SYN_PHP].langName, strTidy))
		{
			m_TidyPhp = strTidy;
		}

		if (readKey(m_TidyNames[SYN_JAVASCRIPT].langName, strTidy))
		{
			m_TidyJs = strTidy;
		}

		if (readKey(m_TidyNames[SYN_CSS].langName, strTidy))
		{
			m_TidyCss = strTidy;
		}

		if (readKey(m_TidyNames[SYN_JSON].langName, strTidy))
		{
			m_TidyJson = strTidy;
		}

		if (readKey(m_TidyNames[SYN_SQL].langName, strTidy))
		{
			m_TidySql = strTidy;
		}

        if (readKey(m_TidyNames[SYN_VERILOG].langName, strTidy))
        {
            m_TidyVerilog = strTidy;
        }

		RegCloseKey(hKEY);
		return true;
	}
#endif
	return false;
}

bool GlobalTidy::LoadFromFile(const std::string &strDllPath)
{
    std::string strFileName(strDllPath);
    std::string::size_type pos = strFileName.rfind('/');
	if (pos == std::string::npos)
	{
		return false;
	}
	strFileName.erase(pos);
    strFileName.append("/CoolFormatConfig.cfconfig");

	std::ifstream configFile(strFileName);
	if (configFile.is_open())
	{
		std::string strLine;
		bool bSynTidy = false;
		while (configFile.good())
		{
			std::getline(configFile, strLine);

			if (strLine.size() == 0)
			{
				continue;
			}
			else if (strLine.compare("[SynTidy]") == 0)
			{
				bSynTidy = true;
			}
			else if (strLine[0] == '[')
			{
				bSynTidy = false;
			}
			else if (bSynTidy)
			{
				std::string::size_type posSplit = strLine.find('=');
				if (posSplit != std::string::npos)
				{
					std::string strLang = strLine.substr(0, posSplit);
					std::string strTidy = strLine.substr(posSplit + 3);
					strTidy = strTidy.erase(strTidy.size() - 2);

					if (strLang == "C++")
					{
						m_TidyCpp = strTidy;
					}
					else if (strLang == "C#")
					{
						m_TidyCSharp = strTidy;
					}
					else if (strLang == "CSS")
					{
						m_TidyCss = strTidy;
					}
					else if (strLang == "HTM")
					{
						m_TidyHtml = strTidy;
					}
					else if (strLang == "Java")
					{
						m_TidyJava = strTidy;
					}
					else if (strLang == "JavaScript")
					{
						m_TidyJs = strTidy;
					}
					else if (strLang == "JSON")
					{
						m_TidyJson = strTidy;
					}
					else if (strLang == "Objective-C")
					{
						m_TidyObjectiveC = strTidy;
					}
					else if (strLang == "PHP")
					{
						m_TidyPhp = strTidy;
					}
					else if (strLang == "SQ")
					{
						m_TidySql = strTidy;
					}
					else if (strLang == "XM")
					{
						m_TidyXml = strTidy;
					}
                    else if (strLang == "Verilog")
                    {
                        m_TidyVerilog = strTidy;
                    }
				}
			}
		}
		configFile.close();
		return true;
	}
	return false;
}
