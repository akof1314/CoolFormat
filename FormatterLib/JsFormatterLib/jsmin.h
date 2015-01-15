#ifndef _JSMIN_H_
#define _JSMIN_H_

class JSMin
{
public:
	JSMin(bool keepFirstComt = false):
	  theLookahead(EOF), keepFirstComt(keepFirstComt)
	{}
	void go();

private:
	int theA;
	int theB;
	int theLookahead;
	bool keepFirstComt;
	
	int isAlphanum(int c);
	int isBlank(int c);

	int get();
	virtual int getChar() = 0;
	virtual void put(int _Ch) = 0;
	int peek();
	int next();
	void action(int d);
};

#endif


