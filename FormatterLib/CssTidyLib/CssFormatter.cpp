#include "CssFormatter.h"
#include "csspp_globals.hpp"
#include "prepare.hpp"

CssFormatterTidy::CssFormatter::CssFormatter( void )
{

}

CssFormatterTidy::CssFormatter::~CssFormatter( void )
{

}

map< string, vector<string> > predefined_templates;
bool bFirstTidy = true;

bool CssFormatterTidy::CssFormatter::CssTidyMain( const char* pSourceIn, const char *pOptions, string &strOut, string &strErr )
{
	if (bFirstTidy)
	{
		prepare();
		predefined_templates["high"].push_back("<span class=\"at\">");
		predefined_templates["high"].push_back("</span> <span class=\"format\">{</span>\n");
		predefined_templates["high"].push_back("<span class=\"selector\">");
		predefined_templates["high"].push_back("</span><span class=\"format\">{</span>");
		predefined_templates["high"].push_back("<span class=\"property\">");
		predefined_templates["high"].push_back("</span><span class=\"value\">");
		predefined_templates["high"].push_back("</span><span class=\"format\">;</span>");
		predefined_templates["high"].push_back("<span class=\"format\">}</span>");
		predefined_templates["high"].push_back("\n");
		predefined_templates["high"].push_back("\n<span class=\"format\">}\n</span>");
		predefined_templates["high"].push_back("");
		predefined_templates["high"].push_back("<span class=\"comment\">"); // before comment
		predefined_templates["high"].push_back("</span>"); //after comment
		predefined_templates["high"].push_back("\n"); // after last line @-rule

		predefined_templates["highest"].push_back("<span class=\"at\">");
		predefined_templates["highest"].push_back("</span><span class=\"format\">{</span>");
		predefined_templates["highest"].push_back("<span class=\"selector\">");
		predefined_templates["highest"].push_back("</span><span class=\"format\">{</span>");
		predefined_templates["highest"].push_back("<span class=\"property\">");
		predefined_templates["highest"].push_back("</span><span class=\"value\">");
		predefined_templates["highest"].push_back("</span><span class=\"format\">;</span>");
		predefined_templates["highest"].push_back("<span class=\"format\">}</span>");
		predefined_templates["highest"].push_back("");
		predefined_templates["highest"].push_back("<span class=\"format\">}</span>");
		predefined_templates["highest"].push_back("");
		predefined_templates["highest"].push_back("<span class=\"comment\">"); // before comment
		predefined_templates["highest"].push_back("</span>"); //after comment
		predefined_templates["highest"].push_back(""); // after last line @-rule

		predefined_templates["low"].push_back("<span class=\"at\">");
		predefined_templates["low"].push_back("</span> <span class=\"format\">{</span>\n");
		predefined_templates["low"].push_back("<span class=\"selector\">");
		predefined_templates["low"].push_back("</span>\n<span class=\"format\">{</span>\n");
		predefined_templates["low"].push_back("\t<span class=\"property\">");
		predefined_templates["low"].push_back("</span><span class=\"value\">");
		predefined_templates["low"].push_back("</span><span class=\"format\">;</span>\n");
		predefined_templates["low"].push_back("<span class=\"format\">}</span>");
		predefined_templates["low"].push_back("\n\n");
		predefined_templates["low"].push_back("\n<span class=\"format\">}</span>\n\n");
		predefined_templates["low"].push_back("\t");
		predefined_templates["low"].push_back("<span class=\"comment\">"); // before comment
		predefined_templates["low"].push_back("</span>\n"); //after comment
		predefined_templates["low"].push_back("\n"); // after last line @-rule
		bFirstTidy = false;
	}

	string css_file;
	css_file = pSourceIn;
	if (css_file.empty())
	{
		return true;
	}

	csstidy csst;
	for (map<string, int>::iterator j = csst.settings.begin(); j != csst.settings.end(); ++j)
	{
		csst.settings[j->first] = 0;
	}
	InitFromOptions(pOptions, &csst);

	if (csst.csstemplate.size() < 14)
	{
		strErr = "Options Error";
		return false;
	}
	try
	{
		csst.parse_css(css_file);
		csst.print_css(strOut);
	}	
	catch (...)
	{
		strErr = "Parse Error";
		return false;
	}

	strErr = "";
	ostringstream oss;
	if(csst.logs.size() > 0 && !csst.settings["silent"])
	{
		for(map<int, vector<message> >::iterator j = csst.logs.begin(); j != csst.logs.end(); j++ )
		{
			for(unsigned int i = 0; i < j->second.size(); ++i)
			{
				oss << "line " << j->first << " - ";
				switch (j->second[i].t)
				{
				case Information:oss << "Information";
					break;
				case Warning:oss << "Warning";
					break;
				case Error:oss << "Error";
					break;
				}
				oss << ":" << j->second[i].m << "\r\n";
			}
		}
	}
	strErr = oss.str();	
	return true;
}

void CssFormatterTidy::CssFormatter::InitFromOptions(const char* pOptions, void* pTidy)
{
	if (NULL == pOptions)
	{
		return;
	}
	tidy = pTidy;

	int lenTidy = strlen(pOptions);
	if (lenTidy <= 0 || pOptions[0] != '-')
	{
		return;
	}

	int nOption = -1;
	for (int i = 0; i < lenTidy; ++i)
	{
		if (pOptions[i] == '-')
		{
			if (-1 != nOption)
			{
				SetTidyOption(pOptions, nOption, i - nOption);
			}
			nOption = i;
		}
	}
	SetTidyOption(pOptions, nOption, lenTidy - nOption);
}

void CssFormatterTidy::CssFormatter::SetTidyOption(const char *pOption, int nPos, int nSize)
{
	if (pOption[nPos] != '-' || nSize < 2)
	{
		return;
	}

	#define STR_SHORT_TEXT_FALG "#"

	string strParam;
	string strNumValue;
	string strBstrValue;

	string strTextParam(pOption + nPos + 1, nSize - 1);
	string::size_type nPosFlag = strTextParam.find(STR_SHORT_TEXT_FALG);
	if (nPosFlag != string::npos)
	{
		strBstrValue = strTextParam.substr(nPosFlag + 1);
		strParam = strTextParam.substr(0, nPosFlag);
	}
	else
	{
		auto it = std::find_if(strTextParam.begin(), strTextParam.end(), isdigit);
		if (it != strTextParam.end())
		{
			strParam.assign(strTextParam.begin(), it);
			strNumValue.assign(it, strTextParam.end());
		}
		else
		{
			strParam.assign(strTextParam);
		}
	}

	SetTidyProp(strParam, strNumValue, strBstrValue);
}

void CssFormatterTidy::CssFormatter::SetTidyProp(const string& strParam, const string& strNumValue, const string& strTextValue)
{
	int nNumValue = strNumValue.empty() ? 0 : std::stoi(strNumValue);

	csstidy* formatter = (csstidy*)tidy;
	if ("c" == strParam)
	{
		switch (nNumValue)
		{
		case 0:formatter->csstemplate = predefined_templates["highest"];	 break;
		case 1:formatter->csstemplate = predefined_templates["high"]; break;
		case 2:break;
		case 3:formatter->csstemplate = predefined_templates["low"];	 break;
		case 4:formatter->csstemplate.clear(); break;
		}
	}
	else if ("ct" == strParam)
	{
		if (formatter->csstemplate.size() == 0)
		{
			vector<string> tpl_arr = explode("|", strTextValue, true);
			formatter->csstemplate = tpl_arr;
		}
	}
	else if ("pc" == strParam)
	{
		formatter->settings["preserve_css"] = 1;
	}
	else if ("ss" == strParam)
	{
		formatter->settings["sort_selectors"] = 1;
	}
	else if ("sp" == strParam)
	{
		formatter->settings["sort_properties"] = 1;
	}
	else if ("rl" == strParam)
	{
		formatter->settings["remove_last_;"] = 1;
	}
	else if ("rub" == strParam)
	{
		formatter->settings["remove_bslash"] = 1;
	}
	else if ("dip" == strParam)
	{
		formatter->settings["discard_invalid_properties"] = 1;
	}
	else if ("cl" == strParam)
	{
		switch (nNumValue)
		{
		case 0:formatter->css_level = "CSS2.1"; break;
		case 1:formatter->css_level = "CSS2.0"; break;
		case 2:formatter->css_level = "CSS1.0"; break;
		}
	}
	else if ("s" == strParam)
	{
		formatter->settings["silent"] = 1;
	}
	else if ("os" == strParam)
	{
		formatter->settings["optimise_shorthands"] = nNumValue;
	}
	else if ("cc" == strParam)
	{
		formatter->settings["compress_colors"] = 1;
	}
	else if ("cf" == strParam)
	{
		formatter->settings["compress_font-weight"] = 1;
	}
	else if ("ls" == strParam)
	{
		formatter->settings["lowercase_s"] = 1;
	}
	else if ("at" == strParam)
	{
		formatter->settings["timestamp"] = 1;
	}
	else if ("cfp" == strParam)
	{
		formatter->settings["case_properties"] = nNumValue;
	}
	else if ("rs" == strParam)
	{
		formatter->settings["merge_selectors"] = nNumValue;
	}
}
