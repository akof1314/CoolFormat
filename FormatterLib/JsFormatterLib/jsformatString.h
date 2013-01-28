#ifndef _JSFORMATSTRING_H_
#define _JSFORMATSTRING_H_

#include <string>

#include "realjsformatter.h"

using namespace std;

class JSFormatString: public RealJSFormatter
{
public:
	JSFormatString(const char* input, 
				string* output,
				char chIndent,
				int nChPerInd,
				bool bPutCR,
				bool bNLBracket);

private:
	string in;
	string* out;

	size_t getPos;
	size_t putPos;

	virtual int GetChar();
	virtual void PutChar(int ch);
};

#endif
