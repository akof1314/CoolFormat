#pragma once
#include <string>
using namespace std;

namespace JsonFormatter{
class JsonTidy
{
public:
	JsonTidy(void);
	~JsonTidy(void);
	bool JsonTidyMain(const char* pSourceIn, const char *pOptions, string &strOut, string &strErr);
};
}