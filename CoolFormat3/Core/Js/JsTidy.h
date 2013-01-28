#pragma once
#include <string>
using namespace std;
#ifdef _DEBUG
#pragma comment(lib, "JsFormatterLibd.lib")
#else
#pragma comment(lib, "JsFormatterLib.lib")
#endif // _DEBUG

namespace JsFormatter{
	class JsTidy
	{
	public:
		JsTidy(void);
		~JsTidy(void);
		bool JsTidyMain(const char* pSourceIn, const char *pOptions, string &strOut/*, string &strErr*/);
	};
}