#include "jsformatString.h"

JSFormatString::JSFormatString(const char *input, 
								string *output,
								RealJSFormatter::FormatterOption option):
				RealJSFormatter(option), 
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
