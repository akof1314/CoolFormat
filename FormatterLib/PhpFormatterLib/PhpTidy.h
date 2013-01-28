#pragma once
#include <string>
using namespace std;

namespace PhpFormatter{
	class PhpTidy
	{
	public:
		PhpTidy(void);
		~PhpTidy(void);
		bool PhpTidyMain(const char* pSourceIn, const char *pOptions, string &strOut, string &strErr);
	};
}