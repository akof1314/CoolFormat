// $Id: ASBeautifier.cpp,v 1.4 2004/02/06 08:37:56 devsolar Exp $
// --------------------------------------------------------------------------
//
// Copyright (c) 1998,1999,2000,2001,2002 Tal Davidson. All rights reserved.
//
// compiler_defines.h
// by Tal Davidson (davidsont@bigfoot.com)
//
// This file is a part of "Artistic Style" - an indentater and reformatter
// of C, C++, C# and Java source files.
//
// --------------------------------------------------------------------------
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// --------------------------------------------------------------------------
//
// Patches:
// 18 March 1999 - Brian Rampel -
//       Fixed inverse insertion of spaces vs. tabs when in -t mode.

#include "compiler_defines.h"
#include "astyle.h"

#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <iostream>

#define INIT_CONTAINER(container, value)     {if ( (container) != NULL ) delete (container); (container) = (value); }
#define DELETE_CONTAINER(container)          {if ( (container) != NULL ) delete (container) ; }

#ifdef USES_NAMESPACE
using namespace std;
#endif

#ifdef USES_NAMESPACE
namespace istyle
{
#endif

bool ASBeautifier::calledInitStatic = false;

vector<const string*> ASBeautifier::headers;
vector<const string*> ASBeautifier::nonParenHeaders;

vector<const string*> ASBeautifier::verilogBlockBegin;
vector<const string*> ASBeautifier::verilogBlockEnd;
vector<const string*> ASBeautifier::preprocessorHeaders;

/*
* initialize the static vars
*/
void ASBeautifier::initStatic()
{
    if (calledInitStatic)
        return;

    calledInitStatic = true;

    headers.push_back(&AS_IF);
    headers.push_back(&AS_ELSE);
    headers.push_back(&AS_FOR);
    headers.push_back(&AS_WHILE);
    headers.push_back(&AS_INITIAL);
    headers.push_back(&AS_FOREVER);
    headers.push_back(&AS_ALWAYS);
    headers.push_back(&AS_REPEAT);

    nonParenHeaders.push_back(&AS_ELSE);
    nonParenHeaders.push_back(&AS_INITIAL);
    nonParenHeaders.push_back(&AS_FOREVER);
    nonParenHeaders.push_back(&AS_ALWAYS);
    nonParenHeaders.push_back(&AS_REPEAT);

    verilogBlockBegin.push_back(&AS_CASE      );
    verilogBlockBegin.push_back(&AS_CASEX     );
    verilogBlockBegin.push_back(&AS_CASEZ     );
	verilogBlockBegin.push_back(&AS_GENERATE  );
    verilogBlockBegin.push_back(&AS_FUNCTION  );
    verilogBlockBegin.push_back(&AS_FORK      );
    verilogBlockBegin.push_back(&AS_TABLE     );
    verilogBlockBegin.push_back(&AS_TASK      );
    verilogBlockBegin.push_back(&AS_SPECIFY   );
    verilogBlockBegin.push_back(&AS_PRIMITIVE );
    //verilogBlockBegin.push_back(&AS_MODULE    );
    verilogBlockBegin.push_back(&AS_BEGIN     );

    verilogBlockEnd.push_back(&AS_ENDCASE      );
	verilogBlockEnd.push_back(&AS_ENDGENERATE  );
    verilogBlockEnd.push_back(&AS_ENDFUNCTION  );
    verilogBlockEnd.push_back(&AS_JOIN         );
    verilogBlockEnd.push_back(&AS_ENDTASK      );
    verilogBlockEnd.push_back(&AS_ENDTABLE     );
    verilogBlockEnd.push_back(&AS_ENDSPECIFY   );
    verilogBlockEnd.push_back(&AS_ENDPRIMITIVE );
    //verilogBlockEnd.push_back(&AS_ENDMODULE    );
    verilogBlockEnd.push_back(&AS_END          );

    preprocessorHeaders.push_back(&PRO_CELLDEFINE           );
    preprocessorHeaders.push_back(&PRO_DEFAULT_NETTYPE      );
    preprocessorHeaders.push_back(&PRO_DEFINE               );
    preprocessorHeaders.push_back(&PRO_ELSE);
    preprocessorHeaders.push_back(&PRO_ENDCELLDEFINE        );
    preprocessorHeaders.push_back(&PRO_ENDIF                );
    preprocessorHeaders.push_back(&PRO_IFDEF                );
    preprocessorHeaders.push_back(&PRO_INCLUDE              );
    preprocessorHeaders.push_back(&PRO_NOUNCONNECTED_DRIVE  );
    preprocessorHeaders.push_back(&PRO_RESETALL             );
    preprocessorHeaders.push_back(&PRO_TIMESCALE            );
    preprocessorHeaders.push_back(&PRO_UNCONNECTED_DRIVE    );
    preprocessorHeaders.push_back(&PRO_UNDEF                );
}

/**
* ASBeautifier's constructor
*/
ASBeautifier::ASBeautifier()
{
    initStatic();

    waitingBeautifierStack = NULL;
    activeBeautifierStack = NULL;
    waitingBeautifierStackLengthStack = NULL;
    activeBeautifierStackLengthStack = NULL;

    headerStack  = NULL;
    tempStacks = NULL;
    blockParenDepthStack = NULL;

    inStatementIndentStack = NULL;
    inStatementIndentStackSizeStack = NULL;
    parenIndentStack = NULL;
    sourceIterator = NULL;

    isMinimalConditinalIndentSet = false;
    shouldForceTabIndentation = false;

    setSpaceIndentation(4);
    setMaxInStatementIndentLength(40);

    setSwitchIndent(false);

    setBlockIndent(false);
    setBracketIndent(false);

    setLabelIndent(false);
    setEmptyLineFill(false);
    //setCStyle();
    setPreprocessorIndent(false);
}

ASBeautifier::ASBeautifier(const ASBeautifier &other)
{
    waitingBeautifierStack = NULL;
    activeBeautifierStack = NULL;
    waitingBeautifierStackLengthStack = NULL;
    activeBeautifierStackLengthStack = NULL;

    headerStack  = new vector<const string*>;
    *headerStack = *other.headerStack;

    tempStacks = new vector< vector<const string*>* >;
    vector< vector<const string*>* >::iterator iter;
    for (iter = other.tempStacks->begin();
            iter != other.tempStacks->end();
            ++iter)
    {
        vector<const string*> *newVec = new vector<const string*>;
        *newVec = **iter;
        tempStacks->push_back(newVec);
    }
    blockParenDepthStack = new vector<int>;
    *blockParenDepthStack = *other.blockParenDepthStack;

    inStatementIndentStack = new vector<int>;
    *inStatementIndentStack = *other.inStatementIndentStack;

    inStatementIndentStackSizeStack = new vector<int>;
    *inStatementIndentStackSizeStack = *other.inStatementIndentStackSizeStack;

    parenIndentStack = new vector<int>;
    *parenIndentStack = *other.parenIndentStack;

    sourceIterator = other.sourceIterator;

    indentString = other.indentString;
    currentHeader = other.currentHeader;
    previousLastLineHeader = other.previousLastLineHeader;

    isInQuote = other.isInQuote;
    isInComment = other.isInComment;
    isInCase = other.isInCase;
    isInQuestion = other.isInQuestion;
    isInStatement =other. isInStatement;
    isInHeader = other.isInHeader;

    bracketIndent = other.bracketIndent;
    blockIndent = other.blockIndent;
    labelIndent = other.labelIndent;
    preprocessorIndent = other.preprocessorIndent;
    parenDepth = other.parenDepth;
    indentLength = other.indentLength;

    leadingWhiteSpaces = other.leadingWhiteSpaces;
    maxInStatementIndent = other.maxInStatementIndent;
    quoteChar = other.quoteChar;
    prevNonSpaceCh = other.prevNonSpaceCh;
    currentNonSpaceCh = other.currentNonSpaceCh;
    currentNonLegalCh = other.currentNonLegalCh;
    prevNonLegalCh = other.prevNonLegalCh;
    isInConditional = other.isInConditional;
    minConditionalIndent = other.minConditionalIndent;
    prevFinalLineSpaceTabCount = other.prevFinalLineSpaceTabCount;
    prevFinalLineTabCount = other.prevFinalLineTabCount;
    emptyLineFill = other.emptyLineFill;

    isInDefine = other.isInDefine;
    isInDefineDefinition = other.isInDefineDefinition;
    backslashEndsPrevLine = other.backslashEndsPrevLine;
    defineTabCount = other.defineTabCount;
}

/**
* ASBeautifier's destructor
*/
ASBeautifier::~ASBeautifier()
{
    deleteBeautifierContainer(waitingBeautifierStack);
    deleteBeautifierContainer(activeBeautifierStack);
    DELETE_CONTAINER(waitingBeautifierStackLengthStack);
    DELETE_CONTAINER(activeBeautifierStackLengthStack);
    DELETE_CONTAINER( headerStack );
    deleteTempStacksContainer(tempStacks);
    DELETE_CONTAINER( blockParenDepthStack );

    DELETE_CONTAINER( inStatementIndentStack );
    DELETE_CONTAINER( inStatementIndentStackSizeStack );
    DELETE_CONTAINER( parenIndentStack );
}

/**
* initialize the ASBeautifier.
*
* init() should be called every time a ABeautifier object is to start
* beautifying a NEW source file.
* init() recieves a pointer to a DYNAMICALLY CREATED ASStreamIterator object
* that will be used to iterate through the source code. This object will be
* deleted during the ASBeautifier's destruction, and thus should not be
* deleted elsewhere.
*
* @param iter     a pointer to the DYNAMICALLY CREATED ASStreamIterator object.
*/
void ASBeautifier::init(ASStreamIterator *iter)
{
    sourceIterator = iter;
    init();
}

/**
* initialize the ASBeautifier.
*/
void ASBeautifier::init()
{
    INIT_CONTAINER( waitingBeautifierStack,  new vector<ASBeautifier*> );
    INIT_CONTAINER( activeBeautifierStack,  new vector<ASBeautifier*> );

    INIT_CONTAINER( waitingBeautifierStackLengthStack, new vector<int> );
    INIT_CONTAINER( activeBeautifierStackLengthStack, new vector<int> );

    INIT_CONTAINER( headerStack,  new vector<const string*> );
    INIT_CONTAINER( tempStacks, new vector< vector<const string*>* > );
    tempStacks->push_back(new vector<const string*>);

    INIT_CONTAINER( blockParenDepthStack, new vector<int> );

    INIT_CONTAINER( inStatementIndentStack, new vector<int> );
    INIT_CONTAINER( inStatementIndentStackSizeStack, new vector<int> );
    inStatementIndentStackSizeStack->push_back(0);
    INIT_CONTAINER( parenIndentStack, new vector<int> );

    previousLastLineHeader = NULL;

    isInQuote = false;
    isInComment = false;
    isInStatement = false;
    isInCase = 0;
    isInQuestion = false;
    isInHeader = false;

    isInConditional = false;
    parenDepth=0;

    leadingWhiteSpaces = 0;
    prevNonSpaceCh = '{';
    currentNonSpaceCh = '{';
    prevNonLegalCh = '{';
    currentNonLegalCh = '{';
    prevFinalLineSpaceTabCount = 0;
    prevFinalLineTabCount = 0;

    backslashEndsPrevLine = false;
    isInDefine = false;
    isInDefineDefinition = false;
    defineTabCount = 0;

}

/**
* indent using one tab per indentation
*/
void ASBeautifier::setTabIndentation(int length, bool forceTabs)
{
    indentString = "\t";
    indentLength = length;
    shouldForceTabIndentation = forceTabs;

    if (!isMinimalConditinalIndentSet)
        minConditionalIndent = indentLength * 2;
}

/**
* indent using a number of spaces per indentation.
*
* @param   length     number of spaces per indent.
*/
void ASBeautifier::setSpaceIndentation(int length)
{
    indentString=string(length, ' ');
    indentLength = length;

    if (!isMinimalConditinalIndentSet)
        minConditionalIndent = indentLength * 2;
}

/**
* set the maximum indentation between two lines in a multi-line statement.
*
* @param   max     maximum indentation length.
*/
void ASBeautifier::setMaxInStatementIndentLength(int max)
{
    maxInStatementIndent = max;
}

/**
* set the minimum indentation between two lines in a multi-line condition.
*
* @param   min     minimal indentation length.
*/
void ASBeautifier::setMinConditionalIndentLength(int min)
{
    minConditionalIndent = min;
    isMinimalConditinalIndentSet = true;
}

/**
* set the state of the bracket indentation option. If true, brackets will
* be indented one additional indent.
*
* @param   state             state of option.
*/
void ASBeautifier::setBracketIndent(bool state)
{
    bracketIndent = state;
}

/**
* set the state of the block indentation option. If true, entire blocks
* will be indented one additional indent, similar to the GNU indent style.
*
* @param   state             state of option.
*/
void ASBeautifier::setBlockIndent(bool state)
{
    if (state)
        setBracketIndent(false); // so that we don't have both bracket and block indent
    blockIndent = state;
}

/**
* set the state of the class indentation option. If true, C++ class
* definitions will be indented one additional indent.
*
* @param   state             state of option.
*/
//  void ASBeautifier::setClassIndent(bool state)
//  {
//      classIndent = state;
//  }

/**
* set the state of the switch indentation option. If true, blocks of 'switch'
* statements will be indented one additional indent.
*
* @param   state             state of option.
*/
void ASBeautifier::setSwitchIndent(bool state)
{
    ;// switchIndent = state;
}

/**
* set the state of the case indentation option. If true, lines of 'case'
* statements will be indented one additional indent.
*
* @param   state             state of option.
*/
void ASBeautifier::setCaseIndent(bool state)
{
    ;//caseIndent = state;
}

/**
* set the state of the label indentation option.
* If true, labels will be indented one indent LESS than the
* current indentation level.
* If false, labels will be flushed to the left with NO
* indent at all.
*
* @param   state             state of option.
*/
void ASBeautifier::setLabelIndent(bool state)
{
    labelIndent = state;
}

/**
* set the state of the preprocessor indentation option.
* If true, multiline #define statements will be indented.
*
* @param   state             state of option.
*/
void ASBeautifier::setPreprocessorIndent(bool state)
{
    preprocessorIndent = state;
}

/**
* set the state of the empty line fill option.
* If true, empty lines will be filled with the whitespace.
* of their previous lines.
* If false, these lines will remain empty.
*
* @param   state             state of option.
*/
void ASBeautifier::setEmptyLineFill(bool state)
{
    emptyLineFill = state;
}

/**
* check if there are any indented lines ready to be read by nextLine()
*
* @return    are there any indented lines ready?
*/
bool ASBeautifier::hasMoreLines() const
{
    return sourceIterator->hasMoreLines();
}

/**
* get the next indented line.
*
* @return    indented line.
*/
string ASBeautifier::nextLine()
{
    return beautify(sourceIterator->nextLine());
}

/**
* beautify a line of source code.
* every line of source code in a source code file should be sent
* one after the other to the beautify method.
*
* @return      the indented line.
* @param originalLine       the original unindented line.
*/
string ASBeautifier::beautify(const string &originalLine)
{
    string line;
    bool isInLineComment = false;
    bool lineStartsInComment = false;
    bool isSpecialChar = false;
    char ch = ' ';
    char prevCh;
    string outBuffer; // the newly idented line is bufferd here
    int tabCount = 0;
    const string *lastLineHeader = NULL;
    bool closingBracketReached = false;
    int spaceTabCount = 0;
    char tempCh;
    int headerStackSize = headerStack->size();

    bool shouldIndentBrackettedLine = true;
    int lineOpeningBlocksNum = 0;
    int lineClosingBlocksNum = 0;
    int i;

    currentHeader = NULL;

    lineStartsInComment = isInComment;

    //+ renqh
    const string *vBlockBegin;
    const string *vBlockEnd;

    vBlockBegin = NULL;
    vBlockEnd   = NULL;

    // handle and remove white spaces around the line:
    // If not in comment, first find out size of white space before line,
    // so that possible comments starting in the line continue in
    // relation to the preliminary white-space.
    if (!isInComment)
    {
        leadingWhiteSpaces = 0;
        while (leadingWhiteSpaces<originalLine.length() && originalLine[leadingWhiteSpaces] <= 0x20)
            leadingWhiteSpaces++;

        line = trim(originalLine);
    }
    else
    {
        int trimSize;
        for (trimSize=0;
                trimSize < originalLine.length() && trimSize<leadingWhiteSpaces && originalLine[trimSize] <= 0x20 ;
                trimSize++)
            ;
        line = originalLine.substr(trimSize);
    }

    if (line.length() == 0)
    {
        if (emptyLineFill)
            return preLineWS(prevFinalLineSpaceTabCount, prevFinalLineTabCount);
        else
            return line;
    }

    // handle preprocessor commands
    bool isPreprocesor = false;
    if(line[0] == PREPROCESSOR_CHAR)  isPreprocesor= (findHeader(line, 0, preprocessorHeaders)!=NULL);
    if ( !isInComment && (isPreprocesor || backslashEndsPrevLine))
    {
        if (line[0] == PREPROCESSOR_CHAR)
        {
            string preproc = trim(string(line.c_str() + 1));

            // When finding a multi-lined #define statement, the original beautifier
            // 1. sets its isInDefineDefinition flag
            // 2. clones a new beautifier that will be used for the actual indentation
            //    of the #define. This clone is put into the activeBeautifierStack in order
            //    to be called for the actual indentation.
            // The original beautifier will have isInDefineDefinition = true, isInDefine = false
            // The cloned beautifier will have   isInDefineDefinition = true, isInDefine = true
            if (preprocessorIndent && preproc.COMPARE(0, 6, string("define")) == 0 &&  line[line.length() - 1] == '\\')
            {
                if (!isInDefineDefinition)
                {
                    ASBeautifier *defineBeautifier;

                    // this is the original beautifier
                    isInDefineDefinition = true;

                    // push a new beautifier into the active stack
                    // this breautifier will be used for the indentation of this define
                    defineBeautifier = new ASBeautifier(*this);
                    //defineBeautifier->init();
                    //defineBeautifier->isInDefineDefinition = true;
                    //defineBeautifier->beautify("");
                    activeBeautifierStack->push_back(defineBeautifier);
                }
                else
                {
                    // the is the cloned beautifier that is in charge of indenting the #define.
                    isInDefine = true;
                }
            }
            else if (preproc.COMPARE(0, 2, string("if")) == 0)
            {
                // push a new beautifier into the stack
                waitingBeautifierStackLengthStack->push_back(waitingBeautifierStack->size());
                activeBeautifierStackLengthStack->push_back(activeBeautifierStack->size());
                waitingBeautifierStack->push_back(new ASBeautifier(*this));
            }
            else if (preproc.COMPARE(0, 4/*2*/, string("else")) == 0)
            {
                if (!waitingBeautifierStack->empty())
                {
                    // MOVE current waiting beautifier to active stack.
                    activeBeautifierStack->push_back(waitingBeautifierStack->back());
                    waitingBeautifierStack->pop_back();
                }
            }

            else if (preproc.COMPARE(0, 5, string("endif")) == 0)
            {
                int stackLength;
                ASBeautifier *beautifier;

                if (!waitingBeautifierStackLengthStack->empty())
                {
                    stackLength = waitingBeautifierStackLengthStack->back();
                    waitingBeautifierStackLengthStack->pop_back();
                    while (waitingBeautifierStack->size() > stackLength)
                    {
                        beautifier = waitingBeautifierStack->back();
                        waitingBeautifierStack->pop_back();
                        delete beautifier;
                    }
                }

                if (!activeBeautifierStackLengthStack->empty())
                {
                    stackLength = activeBeautifierStackLengthStack->back();
                    activeBeautifierStackLengthStack->pop_back();
                    while (activeBeautifierStack->size() > stackLength)
                    {
                        beautifier = activeBeautifierStack->back();
                        activeBeautifierStack->pop_back();
                        delete beautifier;
                    }
                }
            }
        }

        // check if the last char is a backslash
        if(line.length() > 0)
            backslashEndsPrevLine = (line[line.length() - 1] == '\\');
        else
            backslashEndsPrevLine = false;

        // check if this line ends a multi-line #define
        // if so, use the #define's cloned beautifier for the line's indentation
        // and then remove it from the active beautifier stack and delete it.
        if (!backslashEndsPrevLine && isInDefineDefinition && !isInDefine)
        {
            string beautifiedLine;
            ASBeautifier *defineBeautifier;

            isInDefineDefinition = false;
            defineBeautifier = activeBeautifierStack->back();
            activeBeautifierStack->pop_back();

            beautifiedLine = defineBeautifier->beautify(line);
            delete defineBeautifier;
            return beautifiedLine;
        }

        // unless this is a multi-line #define, return this precompiler line as is.

        if (!isInDefine && !isInDefineDefinition )
            return originalLine;
    }

    // if there exists any worker beautifier in the activeBeautifierStack,
    // then use it instead of me to indent the current line.
    if (!isInDefine && activeBeautifierStack != NULL && !activeBeautifierStack->empty())
    {
        return activeBeautifierStack->back()->beautify(line);
    }

    // calculate preliminary indentation based on data from past lines
    if (!inStatementIndentStack->empty())
        spaceTabCount = inStatementIndentStack->back();

    for (i=0; i<headerStackSize; i++)
    {
        if (blockIndent || (!(i>0 && (*headerStack)[i-1] != &AS_OPEN_BRACKET
                              && (*headerStack)[i] == &AS_OPEN_BRACKET)))
            ++tabCount;
    }

    if (isInConditional)
    {
        --tabCount;
    }

    // parse characters in the current line.
    bool isFirstLoop = true ;
    int  iLength = line.length();
    for (i=0; i<iLength; (i=i+1,isFirstLoop=false))
    {
        tempCh = line[i];

        prevCh = ch;
        ch = tempCh;

        outBuffer.append(1, ch);

        if (isWhiteSpace(ch))
            continue;

        // handle special characters (i.e. backslash+character such as \n, \t, ...)
        if (isSpecialChar)
        {
            isSpecialChar = false;
            continue;
        }
        if (!(isInComment || isInLineComment) && line.COMPARE(i, 2, string("\\\\")) == 0)
        {
            outBuffer.append(1, '\\');
            i++;
            continue;
        }
        if (!(isInComment || isInLineComment) && ch=='\\')
        {
            isSpecialChar = true;
            continue;
        }

        // handle quotes (such as 'x' and "Hello Dolly")
        if (!(isInComment || isInLineComment) && (ch=='"' ))
        {
            if (!isInQuote)
            {
                quoteChar = ch;
                isInQuote = true;
            }
            else if (quoteChar == ch)
            {
                isInQuote = false;
                continue;
            }
        }
        if (isInQuote)
            continue;

        // handle comments

        if ( !(isInComment || isInLineComment) && line.COMPARE(i, 2, AS_OPEN_LINE_COMMENT) == 0 )
        {
            isInLineComment = true;
            outBuffer.append(1, '/');
            i++;
            continue;
        }
        else if ( !(isInComment || isInLineComment) && line.COMPARE(i, 2, AS_OPEN_COMMENT) == 0 )
        {
            isInComment = true;
            outBuffer.append(1, '*');
            i++;
            continue;
        }
        else if ( (isInComment || isInLineComment) && line.COMPARE(i, 2, AS_CLOSE_COMMENT) == 0 )
        {
            isInComment = false;
            outBuffer.append(1, '/');
            i++;
            continue;
        }

        if (isInComment||isInLineComment)
            continue;

        //renqh+ find the statements grouped  keywords begin and end.
        vBlockBegin = NULL;
        vBlockEnd   = NULL;

        // join end endtable endspecify
        if(ch == '{')        ch = '[';
        else if(ch == '}')   ch = ']';
        else {
              vBlockEnd   = findHeader(line, i, verilogBlockEnd);
              vBlockBegin = findHeader(line, i, verilogBlockBegin);
		}

        if(vBlockEnd != NULL)
        {
            outBuffer.append(vBlockEnd->substr(1));
            i = i+ vBlockEnd->length()-1;
            ch = '}';
            if(vBlockEnd==&AS_ENDCASE)
                isInCase--;
        }
        else if(vBlockBegin   != NULL)
        {
            outBuffer.append(vBlockBegin->substr(1));
            i = i+ vBlockBegin->length()-1;
            ch = '{';
            if(vBlockBegin==&AS_CASE || vBlockBegin==&AS_CASEZ ||vBlockBegin==&AS_CASEX )
                isInCase++;
        }

        //renqh

        prevNonSpaceCh = currentNonSpaceCh;
        currentNonSpaceCh = ch;
        if (!isLegalNameChar(ch) && ch != ',' && ch != ';' )
        {
            prevNonLegalCh = currentNonLegalCh;
            currentNonLegalCh = ch;
        }
        if (isInHeader)
        {
            isInHeader = false;
            currentHeader = headerStack->back();
        }
        else
            currentHeader = NULL;

        // handle parenthesies
        if (ch == '(' || ch == '[' || ch == ')' || ch == ']')
        {
            if (ch == '(' || ch == '[')
            {
                parenDepth++;

                inStatementIndentStackSizeStack->push_back(inStatementIndentStack->size());

                if (currentHeader != NULL)
                    registerInStatementIndent(line, i, spaceTabCount, minConditionalIndent/*indentLength*2*/, true);
                else
                    registerInStatementIndent(line, i, spaceTabCount, 0, true);
            }
            else if (ch == ')' || ch == ']')
            {
                parenDepth--;
                if (parenDepth == 0)
                {

                    ch = ' ';
                    isInConditional = false;
                }

                if (!inStatementIndentStackSizeStack->empty())
                {
                    int previousIndentStackSize = inStatementIndentStackSizeStack->back();
                    inStatementIndentStackSizeStack->pop_back();
                    while (previousIndentStackSize < inStatementIndentStack->size())
                        inStatementIndentStack->pop_back();

                    if (!parenIndentStack->empty())
                    {
                        int poppedIndent = parenIndentStack->back();
                        parenIndentStack->pop_back();

                        if (i == 0||isFirstLoop)
                            spaceTabCount = poppedIndent;
                    }
                }
            }
            continue;
        }

        if (ch == '{')
        {
            // this bracket is a block opener...
            ++lineOpeningBlocksNum;

            blockParenDepthStack->push_back(parenDepth);
            inStatementIndentStackSizeStack->push_back(inStatementIndentStack->size());

            parenDepth = 0;
            isInStatement = false;

            tempStacks->push_back(new vector<const string*>);
            headerStack->push_back(&AS_OPEN_BRACKET);
            lastLineHeader = &AS_OPEN_BRACKET; // <------
            continue;
        }

        //check if a header has been reached
        if (prevCh == ' ')
        {
            const string *newHeader = findHeader(line, i, headers);
            if (newHeader != NULL)
            {
                // if we reached here, then this is a header...
                isInHeader = true;

                vector<const string*> *lastTempStack;
                if (tempStacks->empty())
                    lastTempStack = NULL;
                else
                    lastTempStack = tempStacks->back();

                // take care of the special case: 'else if (...)'
                if (newHeader == &AS_IF && lastLineHeader == &AS_ELSE)
                {
                    headerStack->pop_back();
                }
                // take care of 'else'
                else if (newHeader == &AS_ELSE)
                {
                    if (lastTempStack != NULL)
                    {
                        int indexOfIf = indexOf(*lastTempStack, &AS_IF); // <---
                        if (indexOfIf != -1)
                        {
                            // recreate the header list in headerStack up to the previous 'if'
                            // from the temporary snapshot stored in lastTempStack.
                            int restackSize = lastTempStack->size() - indexOfIf - 1;
                            for (int r=0; r<restackSize; r++)
                            {
                                headerStack->push_back(lastTempStack->back());
                                lastTempStack->pop_back();
                            }
                            if (!closingBracketReached)
                                tabCount += restackSize;
                        }
                    }
                }

                headerStack->push_back(newHeader);
                if (indexOf(nonParenHeaders, newHeader) == -1)
                {
                    isInConditional = true;
                }
                lastLineHeader = newHeader;

                outBuffer.append(newHeader->substr(1));
                i += newHeader->length() - 1;
                continue;
            }
        }

        if (ch == '?')
            isInQuestion = true;

        // special handling of 'case' statements
        if (ch == ':')
        {
            // found a '[10:0] [`para:0] #(1:2:3)
            if (parenDepth!=0  || prevNonSpaceCh== '}'|| prevNonSpaceCh == '{')
            {}
            else
            {
                currentNonSpaceCh = ';'; // so that brackets after the ':' will appear as block-openers
                if (isInCase>0 )
                {
                    //ch = ';' ;
                    isInHeader = true;
                    headerStack->push_back(&AS_CASE);
                    lastLineHeader = &AS_CASE;
                }
                else if (isInQuestion)
                {
                    isInQuestion = false;
                }
                else //if(!isInStatement) // is in a label (e.g. 'label1:')
                {
                    if (labelIndent)
                        --tabCount; // unindent label by one indent
                    else
                        tabCount = 0; // completely flush indent to left
                }
            }
        }

        if ((ch == ';'  || (parenDepth>0 && ch == ','))  && !inStatementIndentStackSizeStack->empty())
            while (inStatementIndentStackSizeStack->back() + (parenDepth>0 ? 1 : 0)  < inStatementIndentStack->size())
                inStatementIndentStack->pop_back();

        // handle ends of statements
        if ( (ch == ';' && parenDepth == 0) || ch == '}'/* || (ch == ',' && parenDepth == 0)*/)
        {
            isInQuestion = false;
            if (ch == '}')
            {
                // this bracket is block closer...
                ++lineClosingBlocksNum;

                if(!inStatementIndentStackSizeStack->empty())
                    inStatementIndentStackSizeStack->pop_back();

                if (!blockParenDepthStack->empty())
                {
                    parenDepth = blockParenDepthStack->back();
                    blockParenDepthStack->pop_back();

                }

                closingBracketReached = true;
                int headerPlace = indexOf(*headerStack, &AS_OPEN_BRACKET); // <---
                if (headerPlace != -1)
                {
                    const string *popped = headerStack->back();
                    while (popped != &AS_OPEN_BRACKET)
                    {
                        headerStack->pop_back();
                        popped = headerStack->back();
                    }
                    headerStack->pop_back();

                    if (!tempStacks->empty())
                    {
                        vector<const string*> *temp =  tempStacks->back();
                        tempStacks->pop_back();
                        delete temp;
                    }
                }

                ch = ' '; // needed due to cases such as '}else{', so that headers ('else' tn tih case) will be identified...
            }

            /*
            * Create a temporary snapshot of the current block's header-list in the
            * uppermost inner stack in tempStacks, and clear the headerStack up to
            * the begining of the block.
            * Thus, the next future statement will think it comes one indent past
            * the block's '{' unless it specifically checks for a companion-header
            * (such as a previous 'if' for an 'else' header) within the tempStacks,
            * and recreates the temporary snapshot by manipulating the tempStacks.
            */
            if (!tempStacks->back()->empty())
                while (!tempStacks->back()->empty())
                    tempStacks->back()->pop_back();
            while (!headerStack->empty() && headerStack->back() != &AS_OPEN_BRACKET)
            {
                tempStacks->back()->push_back(headerStack->back());
                headerStack->pop_back();
            }

            if (ch == ';')
                isInStatement=false;
            continue;
        }
        // Handle mult line assign
        if (!isInStatement && i==0 && parenDepth == 0 && isInCase==0)
        {
            int pos =0;
            while (pos < iLength)
            {
                if( !isLegalNameChar(line[pos]) )
                    break;
                ++pos;
            }
            if (pos >= iLength)
                pos--;
            while (pos < iLength)
            {
                if( !isWhiteSpace(line[pos]) )
                    break;
                ++pos;
            }
            if (pos >= iLength)
                pos--;

            registerInStatementIndent(string(line.c_str()+pos), 0, spaceTabCount, pos, false);
            isInStatement = true;
        }
    }

    // indent #define lines with one less tab
    //if (isInDefine)
    //    tabCount -= defineTabCount-1;

    vBlockBegin = findHeader(outBuffer, 0, verilogBlockBegin);
    vBlockEnd   = findHeader(outBuffer, 0, verilogBlockEnd);

    if (!lineStartsInComment
            && !blockIndent
            && outBuffer.length()>0
            && ( vBlockBegin!=NULL)
            && !(lineOpeningBlocksNum > 0 && lineOpeningBlocksNum == lineClosingBlocksNum)
            && !(headerStack->size() > 1 && (*headerStack)[headerStack->size()-2] == &AS_OPEN_BRACKET)
            && shouldIndentBrackettedLine)
        --tabCount;

    else if (!lineStartsInComment
             && outBuffer.length()>0
             && ( vBlockEnd!=NULL)
             && shouldIndentBrackettedLine )
        --tabCount;

    // correctly indent one-line-blocks...
    else if (!lineStartsInComment
             && outBuffer.length()>0
             && lineOpeningBlocksNum > 0
             && lineOpeningBlocksNum == lineClosingBlocksNum
             && previousLastLineHeader != NULL
             && previousLastLineHeader != &AS_OPEN_BRACKET)
        tabCount -= 1; //lineOpeningBlocksNum - (blockIndent ? 1 : 0);

    if (tabCount < 0)
        tabCount = 0;

    // take care of extra bracket indentatation option...
    if (bracketIndent && outBuffer.length()>0 && shouldIndentBrackettedLine)
        if (vBlockEnd!=NULL||vBlockBegin!=NULL)
            tabCount++;

    if (isInDefine)
    {
        if (outBuffer[0] == PREPROCESSOR_CHAR)
        {
            string preproc = trim(string(outBuffer.c_str() + 1));
            if (preproc.COMPARE(0, 6, string("define")) == 0)
            {
                if (!inStatementIndentStack->empty()
                        && inStatementIndentStack->back() > 0)
                {
                    defineTabCount = tabCount;
                }
                else
                {
                    defineTabCount = tabCount - 1;
                    tabCount--;
                }
            }
        }

        tabCount -= defineTabCount;
    }

    if (tabCount < 0)
        tabCount = 0;

    // finally, insert indentations into begining of line

    prevFinalLineSpaceTabCount = spaceTabCount;
    prevFinalLineTabCount = tabCount;

    if (shouldForceTabIndentation)
    {
        tabCount += spaceTabCount / indentLength;
        spaceTabCount = spaceTabCount % indentLength;
    }

    outBuffer = preLineWS(spaceTabCount,tabCount) + outBuffer;

    if (lastLineHeader != NULL)
        previousLastLineHeader = lastLineHeader;

    return outBuffer;
}

string ASBeautifier::preLineWS(int spaceTabCount, int tabCount)
{
    string ws;

    for (int i=0; i<tabCount; i++)
        ws += indentString;

    while ((spaceTabCount--) > 0)
        ws += string(" ");

    return ws;
}

/**
* Delete the ASBeautifier vector object.
* This is a vector of pointers to ASBeautifier objects allocated with the 'new' operator.
* Therefore the ASBeautifier objects have to be deleted in addition to the
* ASBeautifier pointer entries.
*/
void ASBeautifier::deleteBeautifierContainer(vector<ASBeautifier*>* &container)
{
    if (container != NULL)
    {
        vector<ASBeautifier*>::iterator iter = container->begin();
        while (iter < container->end())
        {
            delete *iter;
            ++iter;
        }
        container->clear();
        delete (container);
        container = NULL;
    }
}

/**
* Delete the tempStacks vector object.
* The tempStacks is a vector of pointers to strings allocated with the 'new' operator.
* Therefore the strings have to be deleted in addition to the tempStacks entries.
*/
void ASBeautifier::deleteTempStacksContainer(vector<vector<const string*>*>* &container)
{
    if (container != NULL)
    {
        vector<vector<const string*>*>::iterator iter = container->begin();
        while (iter < container->end())
        {
            delete *iter;
            ++iter;
        }
        container->clear();
        delete (container);
        container = NULL;
    }
}

/**
* register an in-statement indent.
*/
void ASBeautifier::registerInStatementIndent(const string &line, int i, int spaceTabCount,
        int minIndent, bool updateParenStack)
{
    int inStatementIndent;
    int remainingCharNum = line.length() - i;
    int nextNonWSChar = 1;

    nextNonWSChar = getNextProgramCharDistance(line, i);

    // if indent is around the last char in the line, indent instead 2 spaces from the previous indent
    if (nextNonWSChar == remainingCharNum)
    {
        int previousIndent = spaceTabCount;
        if (!inStatementIndentStack->empty())
            previousIndent = inStatementIndentStack->back();

        inStatementIndentStack->push_back(/*2*/ indentLength + previousIndent );
        if (updateParenStack)
            parenIndentStack->push_back( previousIndent );
        return;
    }

    if (updateParenStack)
        parenIndentStack->push_back(i+spaceTabCount);

    inStatementIndent = i + nextNonWSChar + spaceTabCount;

    if (i + nextNonWSChar < minIndent)
        inStatementIndent = minIndent + spaceTabCount;

    if (i + nextNonWSChar > maxInStatementIndent)
        inStatementIndent =  indentLength*2 + spaceTabCount;

    if (!inStatementIndentStack->empty() &&
            inStatementIndent < inStatementIndentStack->back())
        inStatementIndent = inStatementIndentStack->back();

    inStatementIndentStack->push_back(inStatementIndent);
}

/**
* get distance to the next non-white sspace, non-comment character in the line.
* if no such character exists, return the length remaining to the end of the line.
*/
int ASBeautifier::getNextProgramCharDistance(const string &line, int i)
{
    bool inComment = false;
    int remainingCharNum = line.length() - i;
    int charDistance = 1;
    int ch;

    for (charDistance = 1; charDistance < remainingCharNum; charDistance++)
    {
        ch = line[i + charDistance];
        if (inComment)
        {
            if (line.COMPARE(i + charDistance, 2, AS_CLOSE_COMMENT) == 0)
            {
                charDistance++;
                inComment = false;
            }
            continue;
        }
        else if (isWhiteSpace(ch))
            continue;
        else if (ch == '/')
        {
            if (line.COMPARE(i + charDistance, 2, AS_OPEN_LINE_COMMENT) == 0)
                return remainingCharNum;
            else if (line.COMPARE(i + charDistance, 2, AS_OPEN_COMMENT) == 0)
            {
                charDistance++;
                inComment = true;
            }
        }
        else
            return charDistance;
    }

    return charDistance;
}

/**
* check if a specific character can be used in a legal variable/method/class name
*
* @return          legality of the char.
* @param ch        the character to be checked.
*/
bool ASBeautifier::isLegalNameChar(char ch) const
{
    return (isalnum(ch) //(ch>='a' && ch<='z') || (ch>='A' && ch<='Z') || (ch>='0' && ch<='9') ||
            || ch=='.' || ch=='_' || ( ch=='$') || (ch=='`'));
}
/**
* check the char '?' is  a verilog number
*
* @return          is a number
* @param i         '?' in the position in string line
*/

bool ASBeautifier::isInVerilogNum(const string &line,int i) const
{
    bool isNum = false;
    char ch = line[i];
    int  pos =i;
    while(pos>=0 && !isWhiteSpace(ch))
    {
        if(ch== '0' || ch=='1'||ch =='x' ||ch =='X'||
                ch =='z' ||ch =='Z'||ch =='_'||ch =='?' )
        {
            pos--;
            ch= line[pos];
            continue;
        }
        if( (ch=='b' ||ch =='B') && (pos >0 &&line[pos-1]=='\''))
            isNum = true;
        break;
    }
    return isNum;
}

/**
* check if a specific line position contains a header, out of several possible headers.
*
* @return    a pointer to the found header. if no header was found then return NULL.
*/
const string *ASBeautifier::findHeader(const string &line, int i, const vector<const string*> &possibleHeaders, bool checkBoundry)
{
    int maxHeaders = possibleHeaders.size();
    const string *header = NULL;
    int p;

    for (p=0; p < maxHeaders; p++)
    {
        header = possibleHeaders[p];

        if (line.COMPARE(i, header->length(), *header) == 0)
        {
            // check that this is a header and not a part of a longer word
            // (e.g. not at its begining, not at its middle...)

            int lineLength = line.length();
            int headerEnd = i + header->length();
            char startCh = (*header)[0];   // first char of header
            char endCh = 0;                // char just after header
            char prevCh = 0;               // char just before header

            if (headerEnd < lineLength)
            {
                endCh = line[headerEnd];
            }
            if (i > 0)
            {
                prevCh = line[i-1];
            }

            if (!checkBoundry)
            {
                return header;
            }
            else if (prevCh != 0
                     && isLegalNameChar(startCh)
                     && isLegalNameChar(prevCh))
            {
                continue;
            }
            else if (headerEnd >= lineLength
                     || !isLegalNameChar(startCh)
                     || !isLegalNameChar(endCh))
            {
                return header;
            }
            else
            {
                continue;
            }
        }
    }

    return NULL;
}

/**
* check if a specific character can be used in a legal variable/method/class name
*
* @return          legality of the char.
* @param ch        the character to be checked.
*/
bool ASBeautifier::isWhiteSpace(char ch) const
{
    return (ch == ' ' || ch == '\t');
}

/**
* find the index number of a string element in a container of strings
*
* @return              the index number of element in the ocntainer. -1 if element not found.
* @param container     a vector of strings.
* @param element       the element to find .
*/
int ASBeautifier::indexOf(vector<const string*> &container, const string *element)
{
    vector<const string*>::const_iterator where;

    where= find(container.begin(), container.end(), element);
    if (where == container.end())
        return -1;
    else
        return where - container.begin();
}

/**
* trim removes the white space surrounding a line.
*
* @return          the trimmed line.
* @param str       the line to trim.
*/
string ASBeautifier::trim(const string &str)
{

    int start = 0;
    int end = str.length() - 1;

    while (start < end && isWhiteSpace(str[start]))
        start++;

    while (start <= end && isWhiteSpace(str[end]))
        end--;

    string returnStr(str, start, end+1-start);
    return returnStr;
}

#ifdef USES_NAMESPACE
}
#endif

