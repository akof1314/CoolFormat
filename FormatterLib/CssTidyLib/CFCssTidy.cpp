#include "CFCssTidy.h"
#include "csspp_globals.hpp"
#include "prepare.hpp"

CCFCssTidy::CCFCssTidy( void )
{

}

CCFCssTidy::~CCFCssTidy( void )
{

}

map< string, vector<string> > predefined_templates;
bool bFirstTidy = true;

bool CCFCssTidy::TidyMain(const char* pSourceIn, const char *pOptions, string &strOut, string &strErr)
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
	TidyOptionsSet(&csst, pOptions);

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

void CCFCssTidy::InitTidyDefault()
{
	csstidy* formatter = (csstidy*)tidy;
	for (map<string, int>::iterator j = formatter->settings.begin(); j != formatter->settings.end(); ++j)
	{
		formatter->settings[j->first] = 0;
	}
}

void CCFCssTidy::SetTidyProp(const string& strParam, int nNumValue, const string& /*strNumValue*/, const string& strTextValue)
{
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
