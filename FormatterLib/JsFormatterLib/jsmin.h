#ifndef _JSMIN_H_
#define _JSMIN_H_

#include <stdlib.h>
#include <stdio.h>

class JSMin
{
public:
	JSMin(bool keepFirstComt = false):
	  theLookahead(EOF), theX(EOF), theY(EOF),
	  keepFirstComt(keepFirstComt)
	{}
	void go();

private:
	int theA;
	int theB;
	int theLookahead;
	int theX;
	int theY;
	bool keepFirstComt;

	void error(char* s);
	int isAlphanum(int c);
	int isBlank(int c);

	int peek();
	int next();
	void action(int d);

	int get();
	virtual int getChar() = 0;
	virtual void put(int _Ch) = 0;

};

#endif


