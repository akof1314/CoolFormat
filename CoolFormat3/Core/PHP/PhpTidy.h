#pragma once
#include <string>
using namespace std;
#ifdef _DEBUG
#pragma comment(lib, "PhpFormatterLibd.lib")
#else
#pragma comment(lib, "PhpFormatterLib.lib")
#endif // _DEBUG

namespace PhpFormatter{
	class PhpTidy
	{
	public:
		PhpTidy(void);
		~PhpTidy(void);
		bool PhpTidyMain(const char* pSourceIn, const char *pOptions, string &strOut, string &strErr);
	};
}