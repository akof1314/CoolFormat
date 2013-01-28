#pragma once
#include <string>
using namespace std;
#ifdef _DEBUG
#pragma comment(lib, "CssTidyLibd.lib")
#else
#pragma comment(lib, "CssTidyLib.lib")
#endif // _DEBUG

namespace CssFormatterTidy{
	class CssFormatter
	{
	public:
		CssFormatter(void);
		~CssFormatter(void);
		
		/**
		 * ∏Ò ΩªØcss
		 * @param const char * pSourceIn 
		 * @param const char * pOptions 
		 * @param string & strOut 
		 * @param string & strErr 
		 * @return bool 
		 */
		bool CssTidyMain(const char* pSourceIn, const char *pOptions, string &strOut, string &strErr);
	};
}
/*
settings["allow_html_in_templates"] = 0;
settings["case_properties"] = 0;	
settings["compress_colors"] = 1;
settings["compress_font-weight"] = 1;
settings["discard_invalid_properties"] = 0;
settings["lowercase_s"] = 0;
settings["merge_selectors"] = 2;
settings["optimise_shorthands"] = 1;
settings["preserve_css"] = 0;	
settings["remove_bslash"] = 1;
settings["remove_last_;"] = 0;
settings["silent"] = 0;
settings["sort_properties"] = 0;
settings["sort_selectors"] = 0;	
settings["timestamp"] = 0;
css_level = "CSS2.1";
csstemplate 
*/