// $Id: ASFormatter.cpp,v 1.3 2004/02/06 08:12:00 devsolar Exp $
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
// Patches:
// 26 November 1998 - Richard Bullington -
//        A correction of line-breaking in headers following '}',
//        was created using a variation of a  patch by Richard Bullington.

#include "compiler_defines.h"
#include "astyle.h"

#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <iostream>

#define INIT_CONTAINER(container, value)     {if ( (container) != NULL ) delete (container); (container) = (value); }
#define DELETE_CONTAINER(container)          {if ( (container) != NULL ) delete (container) ; }
#define IS_A(a,b)                            ( ((a) & (b)) == (b))
#ifdef USES_NAMESPACE
using namespace std;

namespace istyle
{
#endif

bool ASFormatter::calledInitStatic = false;
vector<const string*> ASFormatter::headers;
vector<const string*> ASFormatter::nonParenHeaders;
vector<const string*> ASFormatter::preprocessorHeaders;
vector<const string*> ASFormatter::operators;
vector<const string*> ASFormatter::verilogBlockBegin;
vector<const string*> ASFormatter::verilogBlockEnd;

/**
 * Constructor of ASFormatter
 */
ASFormatter::ASFormatter()
{
    staticInit();

    preBracketHeaderStack = NULL;
    parenStack = NULL;

    sourceIterator = NULL;
    bracketFormatMode = NONE_MODE;
    shouldPadOperators = false;
    shouldPadParenthesies = false;
    shouldPadBlocks = false;
    shouldBreakOneLineBlocks = true;
    shouldBreakOneLineStatements = true;
    shouldConvertTabs = false;
    shouldBreakBlocks = false;
    shouldBreakClosingHeaderBlocks = false;
    shouldBreakElseIfs = false;
}

/**
 * Destructor of ASFormatter
 */
ASFormatter::~ASFormatter()
{
    DELETE_CONTAINER(preBracketHeaderStack);
    DELETE_CONTAINER(parenStack);
}

/**
 * initialization of static data of ASFormatter.
 */
void ASFormatter::staticInit()
{
    if (calledInitStatic)
        return;

    calledInitStatic = true;

    headers.push_back(&AS_IF);
    headers.push_back(&AS_ELSE);
    headers.push_back(&AS_WHILE);
    headers.push_back(&AS_FOR);
    headers.push_back(&AS_CASE);
    headers.push_back(&AS_CASEZ);
    headers.push_back(&AS_CASEX);

    headers.push_back(&AS_INITIAL);
    headers.push_back(&AS_FOREVER);

    headers.push_back(&AS_ENDCASE      );

    headers.push_back(&AS_ENDTASK      );
    headers.push_back(&AS_ENDPRIMITIVE );
    //headers.push_back(&AS_ENDMODULE    );
	headers.push_back(&AS_ENDGENERATE  );
    headers.push_back(&AS_ENDFUNCTION  );

    nonParenHeaders.push_back(&AS_INITIAL);
    nonParenHeaders.push_back(&AS_ELSE);
    nonParenHeaders.push_back(&AS_FOREVER);

    nonParenHeaders.push_back(&AS_ENDCASE      );
    nonParenHeaders.push_back(&AS_ENDTASK      );
    nonParenHeaders.push_back(&AS_ENDPRIMITIVE );
    //nonParenHeaders.push_back(&AS_ENDMODULE    );
	nonParenHeaders.push_back(&AS_ENDGENERATE  );
    nonParenHeaders.push_back(&AS_ENDFUNCTION  );

    //add by renqh
    preprocessorHeaders.push_back(&PRO_CELLDEFINE           );
    preprocessorHeaders.push_back(&PRO_DEFAULT_NETTYPE      );
    preprocessorHeaders.push_back(&PRO_DEFINE               );
    preprocessorHeaders.push_back(&AS_ELSE);
    preprocessorHeaders.push_back(&PRO_ENDCELLDEFINE        );
    preprocessorHeaders.push_back(&PRO_ENDIF                );
    preprocessorHeaders.push_back(&PRO_IFDEF                );
    preprocessorHeaders.push_back(&PRO_INCLUDE              );
    preprocessorHeaders.push_back(&PRO_NOUNCONNECTED_DRIVE  );
    preprocessorHeaders.push_back(&PRO_RESETALL             );
    preprocessorHeaders.push_back(&PRO_TIMESCALE            );
    preprocessorHeaders.push_back(&PRO_UNCONNECTED_DRIVE    );
    preprocessorHeaders.push_back(&PRO_UNDEF                );

    operators.push_back(&AS_EQUAL_EQUAL);
    operators.push_back(&AS_NOT_EQUAL_EQUAL);
    operators.push_back(&AS_BITNOT_AND  );
    operators.push_back(&AS_BITNOT_OR   );
    operators.push_back(&AS_BITNOT_XNOR );
    operators.push_back(&AS_NOT_XNOR    );

    operators.push_back(&AS_EQUAL);
    operators.push_back(&AS_NOT_EQUAL);
    operators.push_back(&AS_GR_EQUAL);

    operators.push_back(&AS_GR_GR);
    operators.push_back(&AS_LS_EQUAL);

    operators.push_back(&AS_LS_LS);

    operators.push_back(&AS_AND);
    operators.push_back(&AS_OR);

    operators.push_back(&AS_EXP);
    operators.push_back(&AS_PLUS);
    operators.push_back(&AS_MINUS);
    operators.push_back(&AS_MULT);
    operators.push_back(&AS_DIV);
    operators.push_back(&AS_MOD);
    operators.push_back(&AS_QUESTION);
    operators.push_back(&AS_COLON);
    operators.push_back(&AS_ASSIGN);
    operators.push_back(&AS_LS);
    operators.push_back(&AS_GR);
    operators.push_back(&AS_NOT);
    operators.push_back(&AS_BIT_OR);
    operators.push_back(&AS_BIT_AND);
    operators.push_back(&AS_BIT_NOT);
    operators.push_back(&AS_BIT_XOR);

    operators.push_back(&AS_COMMA);

    verilogBlockBegin.push_back(&AS_FORK      );
    verilogBlockBegin.push_back(&AS_TABLE     );
    verilogBlockBegin.push_back(&AS_SPECIFY   );
    verilogBlockBegin.push_back(&AS_BEGIN     );

    verilogBlockEnd.push_back(&AS_JOIN         );
    verilogBlockEnd.push_back(&AS_ENDTABLE     );
    verilogBlockEnd.push_back(&AS_ENDSPECIFY   );
    verilogBlockEnd.push_back(&AS_END          );
}

/**
 * initialize the ASFormatter.
 *
 * init() should be called every time a ASFormatter object is to start
 * formatting a NEW source file.
 * init() recieves a pointer to a DYNAMICALLY CREATED ASStreamIterator object
 * that will be used to iterate through the source code. This object will be
 * deleted during the ASFormatter's destruction, and thus should not be
 * deleted elsewhere.
 *
 * @param iter     a pointer to the DYNAMICALLY CREATED ASStreamIterator object.
 */
void ASFormatter::init(ASStreamIterator *si)
{
    ASBeautifier::init(si);
    sourceIterator = si;

    INIT_CONTAINER( preBracketHeaderStack, new vector<const string*> );
    INIT_CONTAINER( parenStack, new vector<int> );
    parenStack->push_back(0);

    currentHeader = NULL;
    currentLine = string("");
    formattedLine = "";
    currentChar = ' ';
    previousCommandChar = ' ';
    previousNonWSChar = ' ';
    quoteChar = '"';
    charNum = 0;
    previousOperator = NULL;

    isVirgin = true;
    isInLineComment = false;
    isInComment = false;
    isInPreprocessor = false;
    doesLineStartComment = false;
    isInQuote = false;
    isSpecialChar = false;
    isNonParenHeader = true;

    foundQuestionMark = false;
    isInLineBreak = false;
    endOfCodeReached = false;
    isLineReady = false;

    shouldReparseCurrentChar = false;
    passedSemicolon = false;
    passedColon = false;
    shouldBreakLineAfterComments = false;
    isImmediatelyPostComment = false;
    isImmediatelyPostLineComment = false;

    isPrependPostBlockEmptyLineRequested = false;
    isAppendPostBlockEmptyLineRequested = false;
    prependEmptyLine = false;

    previousReadyFormattedLineLength = 0;
    isImmediatelyPostHeader = false;
    isInHeader = false;
    isRealBraceCh = false;
    isInsert      = false;

    vBlockBegin  = NULL;
    vBlockEnd    = NULL;

}

/**
 * get the next formatted line.
 *
 * @return    formatted line.
 */

string ASFormatter::nextLine()
{
    const string *newHeader;
    bool isCharImmediatelyPostComment = false;
    bool isPreviousCharPostComment = false;
    bool isCharImmediatelyPostLineComment = false;
    bool isInVirginLine = isVirgin;
    bool isCharImmediatelyPostOpenBlock = false;
    bool isCharImmediatelyPostCloseBlock = false;
    bool isCharImmediatelyPostTemplate = false;

    if (!isFormattingEnabled())
        return ASBeautifier::nextLine();

    while (!isLineReady)
    {
        isRealBraceCh = false ;

        vBlockBegin = NULL;
        vBlockEnd   = NULL;

        if (shouldReparseCurrentChar)
        {
            shouldReparseCurrentChar = false;

        }
        else if (!getNextChar())
        {
            breakLine();
            return beautify(readyFormattedLine);
        }
        else // stuff to do when reading a new character...
        {
            // make sure that a virgin '{' at the begining ofthe file will be treated as a block...
            if (isInVirginLine && currentChar == '{')
                previousCommandChar = '{';
            isPreviousCharPostComment = isCharImmediatelyPostComment;
            isCharImmediatelyPostComment = false;
            isCharImmediatelyPostTemplate = false;
        }

        if (isInLineComment)
        {
            appendCurrentChar();

            // explicitely break a line when a line comment's end is found.
            if ( (charNum+1 ) == currentLine.length() )
            {
                isInLineBreak = true;
                isInLineComment = false;
                isImmediatelyPostLineComment = true;
                currentChar = 0;  //make sure it is a neutral char.
            }
            continue;
        }
        else if (isInComment)
        {
            if (isSequenceReached(AS_CLOSE_COMMENT))
            {
                isInComment = false;
                isImmediatelyPostComment = true;
                appendSequence(AS_CLOSE_COMMENT);
                goForward(1);
            }
            else
                appendCurrentChar();

            continue;
        }
        // not in line comment or comment
        else if (isInQuote)
        {
            if (isSpecialChar)
            {
                isSpecialChar = false;
                appendCurrentChar();
            }
            else if (currentChar == '\\')
            {
                isSpecialChar = true;
                appendCurrentChar();
            }
            else if (quoteChar == currentChar)
            {
                isInQuote = false;
                appendCurrentChar();
            }
            else
            {
                appendCurrentChar();
            }
            continue;
        }

        // handle white space - needed to simplify the rest.
        if (isWhiteSpace(currentChar) || isInPreprocessor)
        {
            ////// DEVEL: if (isLegalNameChar(previousChar) && isLegalNameChar(peekNextChar()))
            appendCurrentChar();
            continue;
        }

        /* not in MIDDLE of quote or comment or white-space of any type ... */
        if (isSequenceReached(AS_OPEN_LINE_COMMENT))
        {
            isInLineComment = true;
            if (shouldPadOperators)
                appendSpacePad();
            appendSequence(AS_OPEN_LINE_COMMENT);
            goForward(1);
            continue;
        }
        else if (isSequenceReached(AS_OPEN_COMMENT))
        {
            isInComment = true;
            if (shouldPadOperators)
                appendSpacePad();
            appendSequence(AS_OPEN_COMMENT);
            goForward(1);
            continue;
        }
        else if (currentChar == '"' )
        {
            isInQuote = true;
            quoteChar = currentChar;
            ////if (shouldPadOperators)  // BUGFIX: these two lines removed. seem to be unneeded, and interfere with L"
            ////appendSpacePad();    // BUFFIX: TODO make sure the removal of these lines doesn't reopen old bugs...
            appendCurrentChar();
            continue;
        }

        /* not in quote or comment or white-space of any type ... */

        // check if in preprocessor
        // ** isInPreprocessor will be automatically reset at the begining
        //    of a new line in getnextChar()
        if (currentChar == PREPROCESSOR_CHAR && ( findHeader(preprocessorHeaders)!=NULL))
            isInPreprocessor = true;

        if (isInPreprocessor)
        {
            appendCurrentChar();
            continue;
        }

        /* not in preprocessor ... */
        if (isImmediatelyPostComment)
        {
            isImmediatelyPostComment = false;
            isCharImmediatelyPostComment = true;
        }

        if (isImmediatelyPostLineComment)
        {
            isImmediatelyPostLineComment = false;
            isCharImmediatelyPostLineComment = true;
        }

        if (shouldBreakLineAfterComments)
        {
            shouldBreakLineAfterComments = false;
            shouldReparseCurrentChar = true;
            breakLine();
            continue;
        }

        // reset isImmediatelyPostHeader information
        if (isImmediatelyPostHeader)
        {
            isImmediatelyPostHeader = false;

            // Make sure headers are broken from their succeeding blocks
            // (e.g.
            //     if (isFoo) DoBar();
            //  should become
            //     if (isFoo)
            //         DoBar;
            // )
            // But treat else if() as a special case which should not be broken!
            if (shouldBreakOneLineStatements)
            {
                // if may break 'else if()'s, then simply break the line
                if (shouldBreakElseIfs)
                    isInLineBreak = true;
                else
                {
                    // make sure 'else if()'s are not broken.
                    bool isInElseIf = false;
                    const string *upcomingHeader;

                    upcomingHeader = findHeader(headers);
                    if (currentHeader == &AS_ELSE && upcomingHeader == &AS_IF)
                        isInElseIf = true;

                    if (!isInElseIf)
                        isInLineBreak = true;  ////BUGFIX: SHOULD NOT BE breakLine() !!!

                    // add by renqh, insert 'begin' , changed '   if(1) a; ' to ' if(1) begin a;
                    if(shouldPadBlocks && !isInElseIf )
                    {
                        vBlockBegin = findHeader(verilogBlockBegin);
                        if ( vBlockBegin == NULL &&
                             (currentHeader == &AS_IF || currentHeader == &AS_ELSE
                              || currentHeader == &AS_FOR || currentHeader == &AS_WHILE)
                         )
                        {
                            currentChar='b' ;
                            string str1 = "begin ";
                            currentLine.insert(charNum, str1);;

                            isInsert = true;
                        }
                        }
                   }
            }
        }

        if (passedSemicolon)
        {
            passedSemicolon = false;
            if (parenStack->back() == 0)
            {
                shouldReparseCurrentChar = true;
                isInLineBreak = true;
                continue;
            }
        }

        if (passedColon)
        {
            passedColon = false;
            if (parenStack->back() == 0)
            {
                shouldReparseCurrentChar = true;
                isInLineBreak = true;
                continue;
            }
        }

        //handle verilogBlock +

        if (currentChar == '{' )
        {
            isRealBraceCh = true ;
            currentChar = '[';
        }
        else if(currentChar == '}' )
        {
            isRealBraceCh = true ;
            currentChar = ']';
        }
        else if (bracketFormatMode != NONE_MODE)
        {
            if(currentChar=='e' || currentChar=='j' ) // join end endtable endspecify
            {
                vBlockEnd = findHeader(verilogBlockEnd);
                if (vBlockEnd )
                {
                    currentChar = '}';
                    charNum =charNum + (vBlockEnd->length() - 1);
                }
            }
            else if((currentChar=='f' || currentChar=='t' || currentChar=='s' ||currentChar=='b' ))// fork table specify begin
            {
                vBlockBegin = findHeader(verilogBlockBegin);
                if (vBlockBegin )
                {
                    currentChar = '{';
                    charNum =charNum + (vBlockBegin->length() - 1);
                }
            }
        }
        //handle verilogBlock -

        // handle parenthesies
        //
        if (currentChar == '(' || currentChar == '[' )
        {
            parenStack->back()++;
        }
        else if (currentChar == ')' || currentChar == ']' )
        {
            parenStack->back()--;

            // check if this parenthesis closes a header, e.g. if (...), while (...)
            if (isInHeader && parenStack->back() == 0)
            {
                isInHeader = false;
                isImmediatelyPostHeader = true;
            }
        }

        // handle brackets
        //
        if (currentChar == '{')
        {
            parenStack->push_back(0);
            preBracketHeaderStack->push_back(currentHeader);
            currentHeader = NULL;
        }
        else if (currentChar == '}')
        {
            if (!parenStack->empty())
            {
                parenStack->pop_back();
            }
            // if a request has been made to append a post block empty line,
            // but the block exists immediately before a closing bracket,
            // then there is not need for the post block empty line.
            //
            isAppendPostBlockEmptyLineRequested = false;

            if (!preBracketHeaderStack->empty())
            {
                currentHeader = preBracketHeaderStack->back();
                preBracketHeaderStack->pop_back();
            }
            else
                currentHeader = NULL;
        }

        //{
        if (bracketFormatMode != NONE_MODE)
        {
            if (currentChar == '{')
            {
                if (  bracketFormatMode == ATTACH_MODE
                        && !isCharImmediatelyPostLineComment )
                {
                    appendSpacePad();
                    if (!isCharImmediatelyPostComment // do not attach '{' to lines that end with /**/ comments.
                            && previousCommandChar != '{'
                            && previousCommandChar != '}'
                            && previousCommandChar != ';') // '}' , ';' chars added for proper handling of '{' immediately after a '}' or ';'
                        appendBlock(false);
                    else
                        appendBlock(true);
                    continue;
                }
                else if (bracketFormatMode == BREAK_MODE)
                {
                    if ( shouldBreakOneLineBlocks  )
                        breakLine();
                    appendBlock();
                    continue;
                }
                appendBlock(true);
                continue;
            }
            else if (currentChar == '}')
            {
                if(shouldBreakOneLineBlocks )
                {
                    breakLine();
                    appendBlock();
                }
                else
                {
                    if (!isCharImmediatelyPostComment)
                        isInLineBreak = false;
                    appendBlock();
                    if (shouldBreakOneLineBlocks )
                        shouldBreakLineAfterComments = true;
                }

                if (shouldBreakBlocks)
                {
                    isAppendPostBlockEmptyLineRequested =true;
                }

                continue;
            }
        }
        //}

        if ( ( (previousCommandChar == '{' )
                || (previousCommandChar == '}'
                    && !isPreviousCharPostComment    // <-- Fixes wrongly appended newlines after '}' immediately after comments... 10/9/1999
                    && peekNextChar() != ' '))
                &&  (shouldBreakOneLineBlocks  ) )
        {
            isCharImmediatelyPostOpenBlock = (previousCommandChar == '{');
            isCharImmediatelyPostCloseBlock = (previousCommandChar == '}');

            previousCommandChar = ' ';
            isInLineBreak = true;  //<----
        }

        //{
        if ( (newHeader = findHeader(headers)) != NULL)
        {
            const string *previousHeader;

            previousHeader = currentHeader;
            currentHeader = newHeader;

            // check if the found header is non-paren header
            isNonParenHeader = ( find(nonParenHeaders.begin(), nonParenHeaders.end(),
                                      newHeader) != nonParenHeaders.end() );
            appendSequence(*currentHeader);
            goForward(currentHeader->length() - 1);
            // if padding is on, and a paren-header is found
            // then add a space pad after it.
            if (shouldPadOperators && !isNonParenHeader)
                appendSpacePad();

            // Signal that a header has been reached
            // *** But treat a closing while() (as in do...while)
            //     as if it where NOT a header since a closing while()
            //     should never have a block after it!

            isInHeader = true;
            if (isNonParenHeader)
            {
                isImmediatelyPostHeader = true;
                isInHeader = false;
            }

            if (currentHeader == &AS_IF && previousHeader == &AS_ELSE)
                isInLineBreak = false;

            if (shouldBreakBlocks)
            {
                if (previousHeader == NULL
                        && !isCharImmediatelyPostOpenBlock
                    )
                {
                    isPrependPostBlockEmptyLineRequested = true;
                }

                if (currentHeader == &AS_ELSE
                    || isCharImmediatelyPostLineComment
                    || isCharImmediatelyPostComment
                    )
                {
                    isPrependPostBlockEmptyLineRequested = false;
                }

                if (shouldBreakClosingHeaderBlocks
                        &&  isCharImmediatelyPostCloseBlock)
                {
                    isPrependPostBlockEmptyLineRequested = true;
                }
            }

            continue;
        }

        //}

        if (previousNonWSChar == '}' || currentChar == ';')
        {
            if (shouldBreakOneLineStatements && currentChar == ';'
                    && (shouldBreakOneLineBlocks ))
            {
                passedSemicolon = true;

                if(isInsert)
                {
                    isInsert = false;
                    string str1 = " end ";
                    currentLine.insert(charNum+1, str1);
                }
            }

            if (currentChar != ';')
                currentHeader = NULL; //DEVEL: is this ok?

            foundQuestionMark = false;

        }

        if(currentChar == ':' )
        {
            if( previousNonWSChar == '}'|| previousNonWSChar == '{')
            {
                isInLineBreak = false;
                appendCurrentChar();
                if (shouldBreakOneLineBlocks )
                    shouldBreakLineAfterComments = true;
                isInLineComment  = true ;  // begin : lable
                continue;
            }
            else if (shouldBreakOneLineStatements
                     && previousNonWSChar != '}'
                     && previousNonWSChar != '{'
                     && !foundQuestionMark // not in a ... ? ... : ... sequence
                     && previousCommandChar != ')' // not immediately after closing paren of a method header, e.g. ASFormatter::ASFormatter(...) : ASBeautifier(...)
                    )
            {
                passedColon = true;
            }
        }

        if (currentChar == '?')
        {
            if(!isInVerilogNum(currentLine,charNum))
                foundQuestionMark = true;
        }

        if (shouldPadOperators)
        {
            if ((newHeader = findHeader(operators)) != NULL)
            {
                bool shouldPad = (   newHeader != &AS_PAREN_PAREN
                                     && newHeader != &AS_BLPAREN_BLPAREN
                                     && newHeader != &AS_NOT
                                     && newHeader != &AS_BIT_NOT
                                     && newHeader != &AS_BITNOT_AND
                                     && newHeader != &AS_BITNOT_OR
                                     && newHeader != &AS_NOT_XNOR
                                     && newHeader != &AS_BITNOT_XNOR
                                     && !(newHeader == &AS_MINUS && isInExponent())
                                     && !(newHeader == &AS_PLUS && isInExponent())
                                     && !( ( isCharImmediatelyPostTemplate)
                                           && (newHeader == &AS_LS || newHeader == &AS_GR))
                                 );

                // pad before operator
                if (shouldPad
                        && !(newHeader == &AS_COLON && !foundQuestionMark)
                        && newHeader != &AS_SEMICOLON
                        && newHeader != &AS_COMMA)
                    appendSpacePad();
                appendSequence(*newHeader);
                goForward(newHeader->length() - 1);

                // since this block handles '()' and '[]',
                // the parenStack must be updated here accordingly!
                if (newHeader == &AS_PAREN_PAREN
                        || newHeader == &AS_BLPAREN_BLPAREN)
                    parenStack->back()--;

                currentChar = (*newHeader)[newHeader->length() - 1];
                // pad after operator
                // but do not pad after a '-' that is a urinary-minus.
                if ( shouldPad && !(newHeader == &AS_MINUS && isUrinaryMinus()) )
                    appendSpacePad();

                previousOperator = newHeader;
                continue;
            }
        }
        if (shouldPadParenthesies)
        {
            if (currentChar == '(' || currentChar == '[' )
            {
                char peekedChar = peekNextChar();

                appendCurrentChar();
                if (!(currentChar == '(' && peekedChar == ')')
                        && !(currentChar == '[' && peekedChar == ']'))
                    appendSpacePad();
                continue;
            }
            else if (currentChar == ')' || currentChar == ']')
            {
                char peekedChar = peekNextChar();

                if (!(previousChar == '(' && currentChar == ')')
                        && !(previousChar == '[' && currentChar == ']'))
                    appendSpacePad();

                appendCurrentChar();

                if (peekedChar != ';' && peekedChar != ',' && peekedChar != '.'
                        && !(currentChar == ']' && peekedChar == '['))
                    appendSpacePad();
                continue;
            }
        }

        appendCurrentChar();
    }

    // return a beautified (i.e. correctly indented) line.

    string beautifiedLine;
    int readyFormattedLineLength = trim(readyFormattedLine).length();

    if (prependEmptyLine
            && readyFormattedLineLength > 0
            && previousReadyFormattedLineLength > 0)
    {
        isLineReady = true; // signal that a readyFormattedLine is still waiting
        beautifiedLine = beautify("");
    }
    else
    {
        isLineReady = false;
        beautifiedLine = beautify(readyFormattedLine);
    }

    prependEmptyLine = false;
    previousReadyFormattedLineLength = readyFormattedLineLength;

    return beautifiedLine;

}

/**
* check if there are any indented lines ready to be read by nextLine()
*
* @return    are there any indented lines ready?
*/
bool ASFormatter::hasMoreLines() const
{
    if (!isFormattingEnabled())
        return ASBeautifier::hasMoreLines();
    else
        return !endOfCodeReached;
}

/**
 * check if formatting options are enabled, in addition to indentation.
 *
 * @return     are formatting options enabled?
 */
bool ASFormatter::isFormattingEnabled() const
{
    return (bracketFormatMode != NONE_MODE
            || shouldPadOperators
            || shouldConvertTabs);
}

/**
* Return isLineReady for the final check at end of file.
*/
bool ASFormatter::getIsLineReady() const
{
    return isLineReady;
}

/**
 * set the bracket formatting mode.
 * options:
 *    astyle::NONE_MODE     no formatting of brackets.
 *    astyle::ATTACH_MODE   Java, K&R style bracket placement.
 *    astyle::BREAK_MODE    ANSI C/C++ style bracket placement.
 *
 * @param mode         the bracket formatting mode.
 */
void ASFormatter::setBracketFormatMode(BracketMode mode)
{
    bracketFormatMode = mode;
}

/**
 * set 'else if()' breaking mode
 * options:
 *    true     'else' headers will be broken from their succeeding 'if' headers.
 *    false    'else' headers will be attached to their succeeding 'if' headers.
 *
 * @param mode         the 'else if()' breaking mode.
 */
void ASFormatter::setBreakElseIfsMode(bool state)
{
    shouldBreakElseIfs = state;
}

/**
 * set operator padding mode.
 * options:
 *    true     statement operators will be padded with spaces around them.
 *    false    statement operators will not be padded.
 *
 * @param mode         the padding mode.
 */
void ASFormatter::setOperatorPaddingMode(bool state)
{
    shouldPadOperators = state;
}

/**
* set parentheies padding mode.
* options:
*    true     statement parenthesies will be padded with spaces around them.
*    false    statement parenthesies will not be padded.
*
* @param mode         the padding mode.
*/
void ASFormatter::setParenthesisPaddingMode(bool state)
{
    shouldPadParenthesies = state;
}
//Enclose one statement in a begin-end only for keyword if/else/while/for
void ASFormatter::setBlockPaddingMode(bool state)
{
    shouldPadBlocks = state;
}

/**
 * set option to break/not break one-line blocks
 *
 * @param state        true = break, false = don't break.
 */
void ASFormatter::setBreakOneLineBlocksMode(bool state)
{
    shouldBreakOneLineBlocks = state;
}

/**
 * set option to break/not break lines consisting of multiple statements.
 *
 * @param state        true = break, false = don't break.
 */
void ASFormatter::setSingleStatementsMode(bool state)
{
    shouldBreakOneLineStatements = state;
}

/**
 * set option to convert tabs to spaces.
 *
 * @param state        true = convert, false = don't convert.
 */
void ASFormatter::setTabSpaceConversionMode(bool state)
{
    shouldConvertTabs = state;
}

/**
 * set option to break unrelated blocks of code with empty lines.
 *
 * @param state        true = convert, false = don't convert.
 */
void ASFormatter::setBreakBlocksMode(bool state)
{
    shouldBreakBlocks = state;
}

/**
 * set option to break closing header blocks of code (such as 'else', 'catch', ...) with empty lines.
 *
 * @param state        true = convert, false = don't convert.
 */
void ASFormatter::setBreakClosingHeaderBlocksMode(bool state)
{
    shouldBreakClosingHeaderBlocks = state;
}

/**
 * check if a specific sequence exists in the current placement of the current line
 *
 * @return             whether sequence has been reached.
 * @param sequence     the sequence to be checked
 */
bool ASFormatter::isSequenceReached(const string &sequence) const
{
    return currentLine.COMPARE(charNum, sequence.length(), sequence) == 0;

}

/**
 * jump over several characters.
 *
 * @param i       the number of characters to jump over.
 */
void ASFormatter::goForward(int i)
{
    while (--i >= 0)
        getNextChar();
}

/**
* peek at the next unread character.
*
* @return     the next unread character.
*/
char ASFormatter::peekNextChar() const
{
    int peekNum = charNum + 1;
    int len = currentLine.length();
    char ch = ' ';

    while (peekNum < len)
    {
        ch = currentLine[peekNum++];
        if (!isWhiteSpace(ch))
            return ch;
    }

    if (shouldConvertTabs && ch == '\t')
        ch = ' ';

    return ch;
}

/**
* check if current placement is before a comment or line-comment
*
* @return     is before a comment or line-comment.
*/
bool ASFormatter::isBeforeComment() const
{
    int peekNum = charNum + 1;
    int len = currentLine.length();
    // char ch = ' ';
    bool foundComment = false;

    for (peekNum = charNum + 1;
            peekNum < len && isWhiteSpace(currentLine[peekNum]);
            ++peekNum)
        ;

    if (peekNum < len)
        foundComment = ( currentLine.COMPARE(peekNum, 2, AS_OPEN_COMMENT) == 0
                         || currentLine.COMPARE(peekNum, 2, AS_OPEN_LINE_COMMENT) == 0 );

    return foundComment;
}

/**
* get the next character, increasing the current placement in the process.
* the new character is inserted into the variable currentChar.
*
* @return   whether succeded to recieve the new character.
*/
bool ASFormatter::getNextChar()
{
    isInLineBreak = false;
    bool isAfterFormattedWhiteSpace = false;

    if (shouldPadOperators && !isInComment && !isInLineComment
            && !isInQuote && !doesLineStartComment && !isInPreprocessor
            && !isBeforeComment())
    {
        int len = formattedLine.length();
        if (len > 0 && isWhiteSpace(formattedLine[len-1]))
            isAfterFormattedWhiteSpace = true;
    }

    previousChar = currentChar;

    if (!isWhiteSpace(currentChar) )
    {
        previousNonWSChar = currentChar;
        if (!isInComment && !isInLineComment && !isInQuote
                && !isSequenceReached(AS_OPEN_COMMENT)
                && !isSequenceReached(AS_OPEN_LINE_COMMENT)
                )
            previousCommandChar = previousNonWSChar;
    }

    int currentLineLength = currentLine.length();

    if (charNum+1 < currentLineLength
            && (!isWhiteSpace(peekNextChar()) || isInComment || isInLineComment))
    {
        currentChar = currentLine[++charNum];
        if (isAfterFormattedWhiteSpace)
            while (isWhiteSpace(currentChar) && charNum+1 < currentLineLength)
                currentChar = currentLine[++charNum];

        if (shouldConvertTabs && currentChar == '\t')
            currentChar = ' ';

        return true;
    }
    else
    {
        if (sourceIterator->hasMoreLines())
        {
            currentLine = sourceIterator->nextLine();
            if (currentLine.length() == 0)
            {
                /*think*/ currentLine = string(" ");
            }

            // unless reading in the first line of the file,
            // break a new line.
            if (!isVirgin)
                isInLineBreak = true;
            else
                isVirgin = false;

            if (isInLineComment)
                isImmediatelyPostLineComment = true;
            isInLineComment = false;

            trimNewLine();
            currentChar = currentLine[charNum];

            // check if is in preprocessor right after the line break and line trimming
            if (previousNonWSChar != '\\' )
                isInPreprocessor = false;

            if (shouldConvertTabs && currentChar == '\t')
                currentChar = ' ';

            return true;
        }
        else
        {
            endOfCodeReached = true;
            return false;
        }
    }
}

/**
* jump over the leading white space in the current line,
* IF the line does not begin a comment or is in a preprocessor definition.
*/
void ASFormatter::trimNewLine()
{
    int len = currentLine.length();
    charNum = 0;

    if (isInComment || isInPreprocessor)
        return;

    while (isWhiteSpace(currentLine[charNum]) && charNum+1 < len)
        ++charNum;

    doesLineStartComment = false;
    if (isSequenceReached(string("/*")))
    {
        charNum = 0;
        doesLineStartComment = true;
    }
}

/**
 * append a character to the current formatted line.
 * Unless disabled (via canBreakLine == false), first check if a
 * line-break has been registered, and if so break the
 * formatted line, and only then append the character into
 * the next formatted line.
 *
 * @param ch               the character to append.
 * @param canBreakLine     if true, a registered line-break
 */
void ASFormatter::appendChar(char ch, bool canBreakLine)
{
    if (canBreakLine && isInLineBreak)
        breakLine();
    formattedLine.append(1, ch);
}

/**
 * append the CURRENT character (curentChar)to the current
 * formatted line. Unless disabled (via canBreakLine == false),
 * first check if a line-break has been registered, and if so
 * break the formatted line, and only then append the character
 * into the next formatted line.
 *
 * @param canBreakLine     if true, a registered line-break
 */
void ASFormatter::appendCurrentChar(bool canBreakLine)
{
    char tmpCh;
    tmpCh = currentChar;

    if(isRealBraceCh)
    {
        if(currentChar == '[')
            tmpCh = '{';
        else if (currentChar == ']')
            tmpCh = '}';
        isRealBraceCh  = false ;
    }

    appendChar(tmpCh, canBreakLine);
}

// append block begin end
void ASFormatter::appendBlock(bool canBreakLine)
{
    if (vBlockBegin!=NULL)
    {
        appendSequence(*vBlockBegin,canBreakLine);
        vBlockBegin =NULL;
    }
    else if (vBlockEnd!=NULL)
    {
        appendSpacePad();
        appendSequence(*vBlockEnd,canBreakLine);
        vBlockEnd = NULL;
    }
}

/**
 * append a string sequence to the current formatted line.
 * Unless disabled (via canBreakLine == false), first check if a
 * line-break has been registered, and if so break the
 * formatted line, and only then append the sequence into
 * the next formatted line.
 *
 * @param sequence         the sequence to append.
 * @param canBreakLine     if true, a registered line-break
 */
void ASFormatter::appendSequence(const string &sequence, bool canBreakLine)
{
    if (canBreakLine && isInLineBreak)
        breakLine();
    formattedLine.append(sequence);
}

/**
 * append a space to the current formattedline, UNLESS the
 * last character is already a white-space character.
 */
void ASFormatter::appendSpacePad()
{
    int len = formattedLine.length();
    if (len == 0 || !isWhiteSpace(formattedLine[len-1]))
        formattedLine.append(1, ' ');
}

/**
 * register a line break for the formatted line.
 */
void ASFormatter::breakLine()
{
    isLineReady = true;
    isInLineBreak = false;

    // queue an empty line prepend request if one exists
    prependEmptyLine = isPrependPostBlockEmptyLineRequested;

    readyFormattedLine =  formattedLine;
    if (isAppendPostBlockEmptyLineRequested)
    {
        isAppendPostBlockEmptyLineRequested = false;
        isPrependPostBlockEmptyLineRequested = true;
    }
    else
    {
        isPrependPostBlockEmptyLineRequested = false;
    }

    formattedLine = "";
}

/**
 * check if the currently reached open-bracket (i.e. '{')
 * opens a:
 * - a definition type block (such as a class or namespace),
 * - a command block (such as a method block)
 * - a static array
 * this method takes for granted that the current character
 * is an opening bracket.
 *
 * @return    the type of the opened block.
 */
BracketType ASFormatter::getBracketType() const
{
    return COMMAND_TYPE;
}

/**
 * check if the currently reached '-' character is
 * a urinary minus
 * this method takes for granted that the current character
 * is a '-'.
 *
 * @return        whether the current '-' is a urinary minus.
 */
bool ASFormatter::isUrinaryMinus() const
{
    return ( (!isalnum(previousCommandChar))
             && previousCommandChar != '.'
             && previousCommandChar != ')'
             && previousCommandChar != ']' );
}

/**
 * check if the currently reached '-' or '+' character is
 * part of an exponent, i.e. 0.2E-5.
 * this method takes for granted that the current character
 * is a '-' or '+'.
 *
 * @return        whether the current '-' is in an exponent.
 */
bool ASFormatter::isInExponent() const
{
    int formattedLineLength = formattedLine.length();
    if (formattedLineLength >= 2)
    {
        char prevPrevFormattedChar = formattedLine[formattedLineLength - 2];
        char prevFormattedChar = formattedLine[formattedLineLength - 1];

        return ( (prevFormattedChar == 'e' || prevFormattedChar == 'E')
                 && (prevPrevFormattedChar == '.' || isdigit(prevPrevFormattedChar)) );
    }
    else
        return false;
}

/**
 * check if a one-line bracket has been reached,
 * i.e. if the currently reached '{' character is closed
 * with a complimentry '}' elsewhere on the current line,
 *.
 * @return        has a one-line bracket been reached?
 */
bool ASFormatter::isOneLineBlockReached() const
{
    bool isInComment = false;
    bool isInQuote = false;
    int bracketCount = 1;
    int currentLineLength = currentLine.length();
    int i = 0;
    char ch = ' ';
    char quoteChar = ' ';

    for (i = charNum + 1; i < currentLineLength; ++i)
    {
        ch = currentLine[i];

        if (isInComment)
        {
            if (currentLine.COMPARE(i, 2, "*/") == 0)
            {
                isInComment = false;
                ++i;
            }
            continue;
        }

        if (ch == '\\')
        {
            ++i;
            continue;
        }

        if (isInQuote)
        {
            if (ch == quoteChar)
                isInQuote = false;
            continue;
        }

        if (ch == '"' )
        {
            isInQuote = true;
            quoteChar = ch;
            continue;
        }

        if (currentLine.COMPARE(i, 2, "//") == 0)
            break;

        if (currentLine.COMPARE(i, 2, "/*") == 0)
        {
            isInComment = true;
            ++i;
            continue;
        }

        if (ch == '{')
            ++bracketCount;
        else if (ch == '}')
            --bracketCount;

        if(bracketCount == 0)
            return true;
    }

    return false;
}

/**
 * check if one of a set of headers has been reached in the
 * current position of the current line.
 *
 * @return             a pointer to the found header. Or a NULL if no header has been reached.
 * @param headers      a vector of headers
 * @param checkBoundry
 */
const string *ASFormatter::findHeader(const vector<const string*> &headers, bool checkBoundry)
{
    return ASBeautifier::findHeader(currentLine, charNum, headers, checkBoundry);
}

#ifdef USES_NAMESPACE
}
#endif

