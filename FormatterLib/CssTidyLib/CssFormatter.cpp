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
	int nOptionsLen = strlen(pOptions);
	if (nOptionsLen < 21)
	{
		return true;
	}
	int i = 0;
	for(map<string,int>::iterator j = csst.settings.begin(); j != csst.settings.end(); ++j )
	{
		csst.settings[j->first] = pOptions[i] - 48;		
		i++;
	}
	string css_Options = trim(pOptions);
	csst.css_level = strtoupper(css_Options.substr(15, 6));
	string template_value = css_Options.substr(21);
	if(template_value == "high" || template_value == "highest" || template_value == "low")
	{
		csst.csstemplate = predefined_templates[template_value];
	}
	else if(template_value != "default")
	{
		vector<string> tpl_arr = explode("|",template_value,true);
		csst.csstemplate = tpl_arr;		
	}

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