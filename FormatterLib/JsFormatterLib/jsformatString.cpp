#include "jsformatString.h"

JSFormatString::JSFormatString(const char* input, 
				string* output,
				char chIndent,
				int nChPerInd,
				bool bPutCR,
				bool bNLBracket)
		:RealJSFormatter(chIndent, nChPerInd, true, bPutCR, bNLBracket), 
		in(), out(output), getPos(0), putPos(0)
{
	in.append(input);
}

int JSFormatString::GetChar()
{
	if(getPos <= in.length())
		return in[getPos++];
	else
		return 0;
}

void JSFormatString::PutChar(int ch)
{ 
	out->append(1, ch);
}
