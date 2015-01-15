#ifndef _JSMINCHARARRAY_H_
#define _JSMINCHARARRAY_H_

#include <iostream>

#include "jsmin.h"

class JSMinCharArray: public JSMin
{
public:
	JSMinCharArray(const unsigned char *input, unsigned char *output, bool bPutCR, bool bKeepTopComt);

private:
	const unsigned char *in;
	unsigned char *out;

	bool bPutCR;

	size_t getPos;
	size_t putPos;

	virtual int getChar();
	virtual void put(int _Ch);
};

#endif
