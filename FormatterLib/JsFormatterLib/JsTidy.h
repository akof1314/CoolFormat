#pragma once
#include <string>
using namespace std;

namespace JsFormatter{
	class JsTidy
	{
	public:
		JsTidy(void);
		~JsTidy(void);
		bool JsTidyMain(const char* pSourceIn, const char *pOptions, string &strOut/*, string &strErr*/);
	};
}