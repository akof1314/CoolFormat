#include "stdafx.h"
// core API
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
using namespace std;


// custom
#include "SQLFormatter2.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                  P U B L I C  M E T H O D S                                             //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////





/**
 * Formats given sql string
 * Behold : no validation will be done : crap in => crap out 注意：未确认可能导致：废话进来-》废话出去
 */

void SQLFormatter2::formatSql(char *sqlString, char *dest) {
  _formatSql(&sqlString[0], &sqlString[strlen(sqlString)-1], dest, _indent, false);
}

/**
 * Checks if given strings have same length (not counting endline, spaces and tabs)
 */

bool SQLFormatter2::sameLength(char *str1, char *str2) {

  int strlen1 = 0;
  int strlen2 = 0;

  for (;*str1; str1++) {
    if (*str1 != '\n' && *str1 != '\t' && *str1 != ' ' && *str1 != '\r') {
      strlen1++;
    }
  }

  for (;*str2; str2++) {
    if (*str2 != '\n' && *str2 != '\t' && *str2 != ' ' && *str2 != '\r') {
      strlen2++;
    }
  }

  return (strlen1 == strlen2);
}

/**
 * Flattens out given sql string
 */

void SQLFormatter2::flattenSql(char *sqlString, char *dest) {
  
  char *q = dest;
  char *p = sqlString;

  _moveWhileSpaces(p);

  for (; *p;) {

    if (*p == '\n' || *p == '\r' || *p == '\t') {
      *q++ = ' ';
      p++;
    }
    else if (*p == ' ') {      
      if (*(q-1) != ' ') {
	*q++ = *p;
      }

      for (; *(p) == ' '; *p++) {}
    }
    else {
      *q++ = *p++;
    }

  }

  // end the result appropriately !
  *q = '\0';
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                  P R I V A T E  M E T H O D S                                           //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Formats given sql string.
 */

void SQLFormatter2::_formatSql(char *start, char *end, char *dest, int indent, bool lastWasToken) {
 
  //cerr << "\n\n----> formatting : "; _output(start, end, false); //cerr << " (indent : " << indent << ")\n";

  char *p1 = start;
  char *p2 = start;
  char *res = dest;

  for (int lookahead=0; *p2 && p2 < (end+1); *p2++) {

    // Make sure to flush the buffer zone at the end !确认最后清除缓冲区

    if (!*p2) {
      break;
    }

    if (lookahead == _maxLookahead) {
      _handleMaxLookaheadReached(p1, p2, res, indent, lastWasToken, lookahead);
    }
    else if (*p2 == ' ' || *p2 == '\n' || *p2 == '\t') {         
      _handleIncreaseLookahead(p1, p2, res, indent, lastWasToken, lookahead);      
    }
    else if (*p2 == '(') {
      _handleSubQuery(p1, p2, res, indent, lastWasToken, lookahead);
    }
    else if (*p2 == ',' || _isSqlToken(p1, p2)) {
      _handleTokenOrEndline(p1, p2, res, indent, lastWasToken, lookahead, (p1 == start) );
    }

  }

  if (end - p1 > 0) {

    //cerr << "Still got something in the buffer zone...\n";

    if (lastWasToken) {
      //cerr << "last was token !\n";
      //cerr << "indent : " << indent << "\n";
      *res++ = '\n';
      _addIndentation(res, indent);
	  lastWasToken = false;	//增加了这一句
    }
    else {
      *res++ = ' ';
    }

    //cerr << "Moving 1 word...\n";

    _moveOneWord(p1, end, res);

    if (res - p1 > 0) {
      //cerr << "Still got some more in the buffer zone...\n";
      _formatSql(p1, end, res, indent, lastWasToken);
    }
  }

  // flush buffer zone...
  _moveWhileSpaces(p1);
  //cerr << "flushing buffer zone (length:" << end - p1 << ") : "; _output(p1, end, true);

  if (end - p1 > 0) {
    if (lastWasToken) {
      //cerr << "last was token !\n";
      //cerr << "indent : " << indent << "\n";
      *res++ = '\n';
      _addIndentation(res, indent);
    }
    else {
      *res++ = ' ';
    }

    _moveWhileSpaces(p1);
    _moveUntil(p1, end, res);
  }


  *res = '\0'; // end the resulting string properly !

  //cerr << "RESULT : " << dest << "\n";
}

/**
 * Adds indentation characters to given input (using _indentation char)
 */

void SQLFormatter2::_addIndentation(char *&p, int indent) {
  _addIndentation(p, indent, _indentationChar);
}

/**
 * Adds indentation characters to given input
 */

void SQLFormatter2::_addIndentation(char *&p, int indent, char indentationChar) {
  //cerr << "adding indentation : " << indent << " using '" << indentationChar << "' character !\n";
  for (int i=0; indent > 0 && i < indent; i++, *p++=indentationChar) {}
}

/**当搜索到空格之类移到指针
 * Moves ahead while spaces are found
 */

void SQLFormatter2::_moveWhileSpaces(char *&p) {
  for (; *p == ' ' || *p == '\n' || *p == '\r' || *p == '\t'; *p++) {}
}

/**把P1指针移到P2，同时复制结果值到res里面  
 * Moves given pointer p1 until given pointer p2, while copying the results into res
 */

void SQLFormatter2::_moveUntil(char *&p1, char *p2, char *&res) {
  for (; p1 != (p2+1); *res++=*p1++) {}   //添加了转换到大写字母
}

/**
 * Moves given pointer p1 1 word (until space character found), results are copied into res
 */

void SQLFormatter2::_moveOneWord(char *&p1, char *&end, char *&res) {

  //cerr << "*** Moving 1 word...\n";
  
  //cerr << "from p1 : " << p1 << "\n";

  //cerr << "word : ";

  for(; *p1 && p1 <= (end) && *p1 != ' ';*p1++) {
    if (*p1 == '\n' || *p1 == '\r' || *p1 == '\t') {
      //cerr << "(invalid token)";
    }
    else {
      //cerr << *p1;
      *res++=*p1;
    }
  }

  //cerr << "\n";
}

/**最大先行达到时触发
 * Handles the case when the max lookahead is reached !
 */

void SQLFormatter2::_handleMaxLookaheadReached(char *&p1, char *&p2, char *&res, int indent, bool &lastWasToken, int &lookahead) {

  //cerr << "*** Max lookahead reached : " << *(p1+1) << "\n";

  //cerr << "in buffer : "; _output(p1, p2, true);

  if (lastWasToken) {		//换行缩进
    *res++ = '\n';
    _addIndentation(res, indent);
  }
  else {
    *res++ = ' ';
  }

  _moveOneWord(p1, p2, res);
  _moveWhileSpaces(p1);

  lookahead = 0;
  p2=p1-1;
  lastWasToken = false;

  //cerr << "left : "; _output(p1, p2, true);
}

/**
 * Handles the case when a token or endline char was found ! 当SQL标志或者换行字符被搜索到触发的事件
 */

void SQLFormatter2::_handleTokenOrEndline(char *&p1, char *&p2, char *&res, int &indent, bool &lastWasToken, int &lookahead, bool isFirstWord) {

  //cerr << "*** Token or endline param...\n";

  //cerr << "====> IS FIRST WORD ? " << ((isFirstWord) ? "YES" : "NO") << "\n";

  if (isFirstWord && indent != _indent) {
    indent+=_indent;
  }

  //cerr << "indent : " << indent << "\n";

  *res++ = '\n';
  
  if (*p2 == ',') {
    _addIndentation(res, indent);
  }
  else {
    for (int i=0; indent > 0 && i < indent-_indent; i++, *res++=' ') {} // add indentation chars...
  }

  //cerr << "printing : "; _output(p1, p2, true);
  
  _moveUntil(p1, p2, res);
  _moveWhileSpaces(p1);
  
  lookahead = 0;
  p2=p1-1;
  lastWasToken = true;
}

/**开始子查询
 * Handles the case when a subquery was detected !
 */

void SQLFormatter2::_handleSubQuery(char *&p1, char *&p2, char *&res, int indent, bool &lastWasToken, int &lookahead) {

  //cerr << "--------------------------------\n";
  //cerr << "-          SUBQUERY !          -\n";
  //cerr << "--------------------------------\n";

  if (p2-1-p1 > 0 && lastWasToken) { // if there is something in the buffer before '(', and lastWasToken flag is set, then
    *res++ = '\n';
    _addIndentation(res, indent);
  }
  else {
    *res++ = ' ';
  }

  _moveUntil(p1, p2-1, res); //移到结果值到括号前面
  _moveWhileSpaces(p1);
  lastWasToken = true;
  lookahead = 0;
  
  p2=p1+1;

  // move p2 until corresponding ending ')'

  for(int o=1, c=0; o != c && *p2; *p2++) {
    if (*p2 == '(') {
      o++;
    }
    else if (*p2 == ')') {
      c++;
    }
  }
   
  p2--; // push back ')'

  //cerr << "min subq length : " << _minSubqueryLength << "\n";
  //cerr << "query length    : " << p2-p1 << "\n";
  
  if (p2-p1 > _minSubqueryLength) {

    if (_endLineOnSubQuery) {
      *res++ = '\n';
      _addIndentation(res, indent);	
    }
 
    *res++ = *p1++;
    _moveWhileSpaces(p1);

    //cerr << "******* FORMATTING SUBQUERY ********* \n";
    _formatSql(p1, p2-1, res, indent+_indent, true);
    //cerr << "******* SUBQUERY FORMATTED ********* \n";

    //cerr << "indent : " << indent << "\n";
    
    //cerr << "result from formatted subquery : ";

    for(;*res; *res++) { //cerr << *res; 
	}

    //cerr << "\n";
    
    if (_endLineOnSubQuery) {
      //cerr << "adding endline character...\n";
      *res++ = '\n';
      _addIndentation(res, indent);
    }

    //cerr << "adding : " << *p2 << "\n"; 
    *res++ = *p2++;  
    p1=p2;
  }
  else {
    _moveUntil(p1, p2, res);
    *p2++;
  }

  //cerr << "after subquery format : "; _output(p1, p2, true);
   
  p1 = p2;
  _moveWhileSpaces(p1);
  p2 = p1-1;  

  //cerr << "--------------------------------\n";
  //cerr << "-        END SUBQUERY !        -\n";
  //cerr << "--------------------------------\n";
}

/**碰到空格，TAB，换行则先行增加
 * Handles the case when the lookahead should be increased !
 */

void SQLFormatter2::_handleIncreaseLookahead(char *&p1, char *&p2, char *&res, int indent, bool &lastWasToken, int &lookahead) {
	lastWasToken;indent;res;
  //cerr << "increasing lookahead...\n";
  //cerr << "in buffer : "; _output(p1, p2, true);
  lookahead++;
  _moveWhileSpaces(p2);
  //cerr << "left : "; _output(p1, p2, true);
}

/** 检查是否SQL标志
 * Checks if given string, starting from the pointer value which start referers to until the value which end refers to.
 */

bool SQLFormatter2::_isSqlToken(const char *start, const char *end) {

  char *sql_tokens[10] = {"SELECT", "INSERT INTO", "FROM", "WHERE", "AND", "OR", "ORDER BY", "GROUP BY", "COALESCE", 0};
  char **tab = sql_tokens;  
  
  const char *s = &start[0];
  const char *e = &end[0];    

  ////cerr << "checking for token in '"; _output(start, end, false); //cerr << "' ... ";

  for (; *tab; tab++) {

    const char *s = start;
    const char *e = end;

    char *t = *tab;

    for(; *t && (toupper(*s)) == *t && s != (e+1); *s++, *t++) {
      ////cerr << "checking token char '" << *s << "' with '" << *t << "' ... ";      
    }

    if (!*t && (!*s || *s == ' ')) {     // did we reach the end ?
      //cerr << "YES !\n";
      return true;                       // we've got a winner ;-)
    }
  }

  //cerr << "\n";
  return false;
}

/**
 * Outputs contents between start and end 输出在Start和end之间的内容
 */

void SQLFormatter2::_output(const char *start, const char *end, bool endLine) {
	start;end;endLine;
/*
  const char *s = start;
  const char *e = end+1;

  for(;s != e; *s++) {
    //cerr << *s;
  }

  if (endLine) {
    //cerr << "\n";
  }
*/
}

SQLFormatter2::SQLFormatter2( int n_maxLookahead /*= 2*/, int n_indent /*= 2*/, bool n_endLineOnSubQuery /*= true*/, int n_minSubqueryLength /*= 100*/, char n_indentationChar /*= ' '*/ )
{
	_maxLookahead = n_maxLookahead;
	_indent = n_indent;
	_endLineOnSubQuery = n_endLineOnSubQuery;
	_minSubqueryLength = n_minSubqueryLength;
	_indentationChar = n_indentationChar;
}