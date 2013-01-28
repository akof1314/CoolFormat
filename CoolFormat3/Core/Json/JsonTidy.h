#pragma once
#include <string>
using namespace std;
#ifdef _DEBUG
#pragma comment(lib, "JsonCppLibd.lib")
#else
#pragma comment(lib, "JsonCppLib.lib")
#endif // _DEBUG

namespace JsonFormatter{
class JsonTidy
{
public:
	JsonTidy(void);
	~JsonTidy(void);
	bool JsonTidyMain(const char* pSourceIn, const char *pOptions, string &strOut, string &strErr);
};
}