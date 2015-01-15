#include "jsminCharArray.h"

JSMinCharArray::JSMinCharArray(const unsigned char *input, unsigned char *output, bool bPutCR, bool bKeepTopComt)
		:JSMin(bKeepTopComt), in(input), out(output), getPos(0), putPos(0), bPutCR(bPutCR)
{}

int JSMinCharArray::getChar()
{
	if(getPos <= strlen(reinterpret_cast<const char*>(in)))
		return in[getPos++];
	else
		return EOF;
}

void JSMinCharArray::put(int _Ch)
{
	if(_Ch == '\n' && bPutCR)
		out[putPos++] = '\r';
	out[putPos++] = _Ch;
}
