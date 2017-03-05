// $Id: astyle_main.cpp,v 1.9 2004/02/06 09:37:36 devsolar Exp $
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

#include "compiler_defines.h"
#include "astyle_main.h"
#include "astyle.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iterator>
#include <sstream>
#include <stdlib.h>


#ifdef WIN32
#include <Windows.h>
#endif

#define IS_PARAM_OPTION(arg,op)    ((arg).length() < strlen(op) ? 0 : (arg).COMPARE(0, strlen(op), string(op))==0)
#define IS_PARAM_OPTIONS(arg,a,b)  (IS_PARAM_OPTION((arg),(a)) || IS_PARAM_OPTION((arg),(b)))

#define GET_PARAM(arg,op)          ((arg).substr(strlen(op)))
#define GET_PARAMS(arg,a,b)        (IS_PARAM_OPTION((arg),(a)) ? GET_PARAM((arg),(a)) : GET_PARAM((arg),(b)))


#ifdef USES_NAMESPACE
using namespace std;
using namespace istyle;
#endif

#ifndef ASTYLE_LIB

// default options:
ostream *_err = &cerr;
string _suffix = ".orig";

const string _version = "1.21";
bool shouldBackupFile = true;

// --------------------------------------------------------------------------
// Helper Functions
// --------------------------------------------------------------------------
void SetColor(unsigned short ForeColor=3,unsigned short BackGroundColor=0)
{
    #ifdef WIN32
        HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hCon,ForeColor|(BackGroundColor*16));
    #endif
}
void error(const char *why, const char* what)
{
    SetColor(12,0);
    (*_err) << why << ' ' << what <<'\n';
    SetColor(7,0);
    exit(1);
}
#endif	// ASTYLE_LIB


bool parseOption(ASFormatter &formatter, const string &arg, const string &/*errorInfo*/)
{
#ifndef ASTYLE_LIB
    if ( ( arg == "n" ) || ( arg == "suffix=none" ) )
    {
        shouldBackupFile = false;
    }
    else if ( IS_PARAM_OPTION(arg, "suffix=") )
    {
        string suffixParam = GET_PARAM(arg, "suffix=");
        if (suffixParam.length() > 0)
            _suffix = suffixParam;
    }
    else 
#endif	// ASTYLE_LIB

    if ( arg == "style=ansi" )
    {
        formatter.setBracketIndent(false);
        formatter.setSpaceIndentation(4);
        formatter.setBracketFormatMode(BREAK_MODE);
        formatter.setSwitchIndent(false);
    }
    else if ( arg == "style=gnu" )
    {
        formatter.setBlockIndent(true);
        formatter.setSpaceIndentation(2);
        formatter.setBracketFormatMode(BREAK_MODE);
        formatter.setSwitchIndent(false);
    }
    else if ( arg == "style=kr" )
    {
        formatter.setBracketIndent(false);
        formatter.setSpaceIndentation(4);
        formatter.setBracketFormatMode(ATTACH_MODE);
        formatter.setSwitchIndent(false);
    }
    else if ( IS_PARAM_OPTIONS(arg, "t", "indent=tab=") )
    {
        int spaceNum = 4;
        string spaceNumParam = GET_PARAMS(arg, "t", "indent=tab=");
        if (spaceNumParam.length() > 0)
        {
            spaceNum = atoi(spaceNumParam.c_str());
            if(spaceNum==0)
            {
                //(*_err) << errorInfo << arg << endl;
                return false; // unknown option
            }
        }
        formatter.setTabIndentation(spaceNum, false);
    }
    else if ( IS_PARAM_OPTIONS(arg, "T", "force-indent=tab=") )
    {
        int spaceNum = 4;
        string spaceNumParam = GET_PARAMS(arg, "T", "force-indent=tab=");
        if (spaceNumParam.length() > 0)
        {
            spaceNum = atoi(spaceNumParam.c_str());
            if(spaceNum==0)
            {
                //(*_err) << errorInfo << arg << endl;
                return false; // unknown option
            }
        }
        formatter.setTabIndentation(spaceNum, true);
    }
    else if ( IS_PARAM_OPTION(arg, "indent=tab") )
    {
        formatter.setTabIndentation(4);
    }
    else if ( IS_PARAM_OPTIONS(arg, "s", "indent=spaces=") )
    {
        int spaceNum = 4;
        string spaceNumParam = GET_PARAMS(arg, "s", "indent=spaces=");
        if (spaceNumParam.length() > 0)
        {
            spaceNum = atoi(spaceNumParam.c_str());
            if(spaceNum==0)
            {
                //(*_err) << errorInfo << arg << endl;
                return false; // unknown option
            }
        }
        formatter.setSpaceIndentation(spaceNum);
    }
    else if ( IS_PARAM_OPTION(arg, "indent=spaces") )
    {
        formatter.setSpaceIndentation(4);
    }
    else if ( IS_PARAM_OPTIONS(arg, "M", "max-instatement-indent=") )
    {
        int maxIndent = 40;
        string maxIndentParam = GET_PARAMS(arg, "M", "max-instatement-indent=");
        if (maxIndentParam.length() > 0)
            maxIndent = atoi(maxIndentParam.c_str());
        if(maxIndent==0)
        {
            //(*_err) << errorInfo << arg << endl;
            return false; // unknown option
        }

        formatter.setMaxInStatementIndentLength(maxIndent);
    }
    else if ( IS_PARAM_OPTIONS(arg, "m", "min-conditional-indent=") )
    {
        int minIndent = 0;
        string minIndentParam = GET_PARAMS(arg, "m", "min-conditional-indent=");
        if (minIndentParam.length() > 0)
        {
            minIndent = atoi(minIndentParam.c_str());
            if(minIndent==0)
            {
                //(*_err) << errorInfo << arg << endl;
                return false; // unknown option
            }
        }
        formatter.setMinConditionalIndentLength(minIndent);
    }
    else if ( (arg == "B") || (arg == "indent-brackets") )
    {
        formatter.setBracketIndent(true);
    }
    else if ( (arg == "G") || (arg == "indent-blocks") )
    {
        formatter.setBlockIndent(true);
    }
    else if ( (arg == "b") || (arg == "brackets=break") )
    {
        formatter.setBracketFormatMode(BREAK_MODE);
    }
    else if ( (arg == "a") || (arg == "brackets=attach") )
    {
        formatter.setBracketFormatMode(ATTACH_MODE);
    }
    else if ( (arg == "O") || (arg == "one-line=keep-blocks") )
    {
        formatter.setBreakOneLineBlocksMode(false);
    }
    else if ( (arg == "o") || (arg == "one-line=keep-statements") )
    {
        formatter.setSingleStatementsMode(false);
    }
    else if ( arg == "pad=paren" )
    {
        formatter.setParenthesisPaddingMode(true);
    }
    else if ((arg == "l") || ( arg == "pad=block" ))
    {
        formatter.setBlockPaddingMode(true);
    }
    else if ( (arg == "P") || (arg == "pad=all") )
    {
        formatter.setOperatorPaddingMode(true);
        formatter.setParenthesisPaddingMode(true);
        formatter.setBlockPaddingMode(true);
    }
    else if ( (arg == "p") || (arg == "pad=oper") )
    {
        formatter.setOperatorPaddingMode(true);
    }
    else if ( (arg == "E") || (arg == "fill-empty-lines") )
    {
        formatter.setEmptyLineFill(true);
    }
    else if (arg == "indent-preprocessor")
    {
        formatter.setPreprocessorIndent(true);
    }
    else if (arg == "convert-tabs")
    {
        formatter.setTabSpaceConversionMode(true);
    }
    else if (arg == "break-blocks=all")
    {
        formatter.setBreakBlocksMode(true);
        formatter.setBreakClosingHeaderBlocksMode(true);
    }
    else if (arg == "break-blocks")
    {
        formatter.setBreakBlocksMode(true);
    }
    else if (arg == "break-elseifs")
    {
        formatter.setBreakElseIfsMode(true);
    }
    else if ( (arg == "X") || (arg == "errors-to-standard-output") )
    {
        //_err = &cout;
    }
    else if ( (arg == "v") || (arg == "version") )
    {
        //(*_err) << "iStyle " << _version << endl;
    }
    else
    {
        //(*_err) << errorInfo << arg << endl;
        return false; // unknown option
    }
    return true; //o.k.
}

void importOptions(istream &in, vector<string> &optionsVector)
{
    char ch;
    string currentToken;

    while (in)
    {
        currentToken = "";
        do
        {
            in.get(ch);
            if (in.eof())
                break;
            // treat '#' as line comments
            if (ch == '#')
                while (in)
                {
                    in.get(ch);
                    if (ch == '\n' || ch == '\r')
                        break;
                }

            // break options on spaces, tabs or new-lines
            if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
                break;
            else
                currentToken.append(1, ch);

        }
        while (in);

        if (currentToken.length() != 0)
            optionsVector.push_back(currentToken);
    }
}

template<class ITER>
bool parseOptions(ASFormatter &formatter,
                  const ITER &optionsBegin,
                  const ITER &optionsEnd,
                  const string &errorInfo)
{
    ITER option;
    bool ok = true;
    string arg, subArg;

    for (option = optionsBegin; option != optionsEnd; ++option)
    {
        arg = *option; //string(*option);

        if (arg.COMPARE(0, 2, string("--")) == 0)
            ok &= parseOption(formatter, arg.substr(2), errorInfo);
        else if (arg[0] == '-')
        {
            int i;

            for (i=1; i < (int)arg.length(); ++i)
            {
                if (isalpha(arg[i]) && i > 1)
                {
                    ok &= parseOption(formatter, subArg, errorInfo);
                    subArg = "";
                }
                subArg.append(1, arg[i]);
            }
            ok &= parseOption(formatter, subArg, errorInfo);
            subArg = "";
        }
        else
        {
            ok &= parseOption(formatter, arg, errorInfo);
            subArg = "";
        }
    }

    return ok;
}

#ifndef ASTYLE_LIB
void printHelpTitle()
{
    cout << endl;

    SetColor(10,0);
    cout << "iStyle " << _version;

    SetColor(2,0);
    cout <<  " (Fast and Free Automatic Formatter for Verilog Source Code)\n";
    cout << "               (Created by haimag, Report Bugs: haimag@gmail.com)\n";
    cout << "               (Thanks to Tal Davidson & Astyle)\n";
    cout << endl;
    SetColor(7,0);
    //~ cout << endl;
}
void printHelpSimple(int isGetchar=0)
{

    SetColor(14,0);
    cout << endl;
    cout << "Usage  :  iStyle [options] Foo.v  B*r.v  [...]\n";
    cout << endl;
    SetColor(7,0);
    cout << "For help on options, type 'iStyle -h'" ;

    if(isGetchar ==1 )
    {
        cout << ", Press ENTER to exit." << endl;
        getchar();
    }
    else
    {
        cout<<"."<<endl;
    }
    //~ cout << endl;
}

void printHelpFull()
{

    SetColor(14,0);
    cout << endl;
    cout << "Usage  :  iStyle [options] Foo.v  B*r.v  [...]\n";
    cout << endl;
    SetColor(7,0);
    cout << "When indenting a specific file, the resulting indented file RETAINS the\n";
    cout << "original file-name. The original pre-indented file is renamed, with a\n";
    cout << "suffix of \".orig\" added to the original filename. \n";
    cout << endl;
    cout << "By default, iStyle is set up to indent Verilog files, with 4 spaces per \n" ;
    cout << "indent, a maximal indentation of 40 spaces inside continuous statements,\n";
    cout << "and NO formatting.\n";
    cout << endl;
    SetColor(14,0);
    cout << "Option's Format:\n";
    SetColor(7,0);
    cout << "----------------\n";
    cout << "    Long options (starting with '--') must be written one at a time.\n";
    cout << "    Short options (starting with '-') may be appended together.\n";
    cout << "    Thus, -bps4 is the same as -b -p -s4.\n";
    cout << endl;
    SetColor(14,0);
    cout << "Predefined Styling options:\n";
    SetColor(7,0);
    cout << "---------------------------\n";
    cout << "    --style=ansi\n";
    cout << "    ANSI style formatting/indenting.\n";
    cout << endl;
    cout << "    --style=kr\n";
    cout << "    Kernighan&Ritchie style formatting/indenting.\n";
    cout << endl;
    cout << "    --style=gnu\n";
    cout << "    GNU style formatting/indenting.\n";
    cout << endl;
    SetColor(14,0);
    cout << "Indentation options:\n";
    cout << "--------------------\n";
    SetColor(7,0);
    cout << "    -s   OR   -s#   OR   --indent=spaces=#\n";
    cout << "    Indent using # spaces per indent. Not specifying #\n" ;
    cout << "    will result in a default of 4 spacec per indent.\n" ;
    cout << endl;
    cout << "    -t   OR   -t#   OR   --indent=tab=#\n";
    cout << "    Indent using tab characters, assuming that each\n";
    cout << "    tab is # spaces long. Not specifying # will result\n";
    cout << "    in a default assumption of 4 spaces per tab.\n" ;
    cout << endl;
    cout << "    -T#   OR   --force-indent=tab=#\n";
    cout << "    Indent using tab characters, assuming that each\n";
    cout << "    tab is # spaces long. Force tabs to be used in areas\n";
    cout << "    iStyle would prefer to use spaces.\n" ;
    cout << endl;
    cout << "    -B   OR   --indent-brackets\n";
    cout << "    Add extra indentation to 'begin' and 'end' block brackets.\n";
    cout << endl;
    cout << "    -G   OR   --indent-blocks\n";
    cout << "    Add extra indentation entire blocks (including brackets).\n";
    cout << endl;
    cout << "    -m#  OR  --min-conditional-indent=#\n";
    cout << "    Indent a minimal # spaces in a continuous conditional\n";
    cout << "    belonging to a conditional header.\n";
    cout << endl;
    cout << "    -M#  OR  --max-instatement-indent=#\n";
    cout << "    Indent a maximal # spaces in a continuous statement,\n";
    cout << "    relatively to the previous line.\n";
    cout << endl;
    cout << "    -E  OR  --fill-empty-lines\n";
    cout << "    Fill empty lines with the white space of their\n";
    cout << "    previous lines.\n";
    cout << endl;
    cout << "    --indent-preprocessor\n";
    cout << "    Indent multi-line #define statements\n";
    cout << endl;
    SetColor(14,0);
    cout << "Formatting options:\n";
    SetColor(7,0);
    cout << "-------------------\n";
    cout << "    -b  OR  --brackets=break\n";
    cout << "    Break brackets from pre-block code (i.e. ANSI C/C++ style).\n";
    cout << endl;
    cout << "    -a  OR  --brackets=attach\n";
    cout << "    Attach brackets to pre-block code (i.e. Java/K&R style).\n";
    cout << endl;
    cout << "    -o   OR  --one-line=keep-statements\n";
    cout << "    Don't break lines containing multiple statements into\n";
    cout << "    multiple single-statement lines.\n";
    cout << endl;
    cout << "    -O   OR  --one-line=keep-blocks\n";
    cout << "    Don't break blocks residing completely on one line\n";
    cout << endl;
    cout << "    -p   OR  --pad=oper\n";
    cout << "    Insert space paddings around operators only.\n";
    cout << endl;
    cout << "    --pad=paren\n";
    cout << "    Insert space paddings around parenthesies only.\n";
    cout << "    -l OR --pad=block\n";
    cout << "    Enclose one statement in a begin-end only for keyword if/else/while/for.\n";
    cout << endl;
    cout << "    -P   OR  --pad=all\n";
    cout << "    Insert space paddings around operators AND parenthesies.\n";
    cout << endl;
    cout << "    --convert-tabs\n";
    cout << "    Convert tabs to spaces.\n";
    cout << endl;
    cout << "    --break-blocks\n";
    cout << "    Insert empty lines around unrelated blocks, labels, ...\n";
    cout << endl;
    cout << "    --break-blocks=all\n";
    cout << "    Like --break-blocks, except also insert empty lines \n";
    cout << "    around closing headers (e.g. 'else', ...).\n";
    cout << endl;
    cout << "    --break-elseifs\n";
    cout << "    Break 'else if()' statements into two different lines.\n";
    cout << endl;
    SetColor(14,0);
    cout << "Other options:\n";
    SetColor(7,0);
    cout << "-------------\n";
    cout << "    --suffix=####\n";
    cout << "    Append the suffix #### instead of '.orig' to original filename.\n";
    cout << endl;
    cout << "    -n   OR  --suffix=none" << endl;
    cout << "    Tells Astyle not to keep backups of the original source files." << endl;
    cout << "    WARNING: Use this option with care, as Astyle comes with NO WARRANTY..." << endl;
    cout << endl;
    cout << "    -X   OR  --errors-to-standard-output\n";
    cout << "    Print errors and help information to standard-output rather than\n";
    cout << "    to standard-error.\n";
    cout << endl;
    cout << "    -v   OR   --version\n";
    cout << "    Print version number\n";
    cout << endl;
    cout << "    -h   OR   -?   OR   --help\n";
    cout << "    Print this help message\n";
    cout << endl;
    cout << "    --options=####  OR --options=none\n";
    cout << "    Parse used the specified options file: ####, options=none, none\n";
    cout << "    parse options file, and not looks for parse options files\n";
    cout << endl;
    SetColor(14,0);
    cout << "Default options file:\n";
    SetColor(7,0);
    cout << "---------------------\n";
    cout << "    iStyle looks for a default options file in the following order:\n";
    cout << "    1. The contents of the ISTYLE_OPTIONS environment\n";
    cout << "       variable if it exists.\n";
    cout << "    2. The file called .iStylerc in the directory pointed to by the\n";
    cout << "       HOME environment variable ( i.e. $HOME/.iStylerc ).\n";
    cout << "    3. The file called .iStylerc in the directory pointed to by the\n";
    cout << "       HOMEPATH environment variable ( i.e. %HOMEPATH%\\.iStylerc ).\n";
    cout << "    If a default options file is found, the options in this file\n";
    cout << "    will be parsed BEFORE the command-line options.\n";
    cout << "    Options within the default option file may be written without\n";
    cout << "    the preliminary '-' or '--'.\n";
    SetColor(7,0);
    cout << endl;
}
bool isWriteable( char const * const filename )
{
    std::ifstream in(filename);
    if (!in)
    {
        //(*_err) << "File '" << filename << "' does not exist." << endl;
        return false;
    }
    in.close();
    std::ofstream out(filename, std::ios_base::app);
    if (!out)
    {
        //(*_err) << "File '" << filename << "' is not writeable." << endl;
        return false;
    }
    out.close();
    return true;
}
#endif	// ASTYLE_LIB

#ifdef ASTYLE_LIB

bool VerilogTidyMain(const char* pSourceIn, const char* pOptions, std::string &strOut, std::string &strErr)
{
    if (pSourceIn == NULL)
    {
        strErr = "No pointer to source input.";
        return false;
    }
    if (pOptions == NULL)
    {
        strErr = "No pointer to AStyle options.";
        return false;
    }

    ASFormatter formatter;

    vector<string> optionsVector;
    istringstream opt(pOptions);

    importOptions(opt, optionsVector);

    bool ok = parseOptions(formatter,
        optionsVector.begin(),
        optionsVector.end(),
        string("Unknown command line option: "));
    if (!ok)
        strErr = "Unknown command line option: ";

    istringstream in(pSourceIn);
    ASStreamIterator streamIterator(&in);
    ostringstream out;
    formatter.init(&streamIterator);

    while (formatter.hasMoreLines())
    {
        out << formatter.nextLine();
        if (formatter.hasMoreLines())
        {
            out << "\n";
        }
        else
        {
            // this can happen if the file if missing a closing bracket and break-blocks is requested
            if (formatter.getIsLineReady())
            {
                out << "\n";
                out << formatter.nextLine();
            }
        }
    }
    strOut = out.str();
    return true;
}

#elif !defined(ASTYLECON_LIB)
int main(int argc, char *argv[])
{
    ASFormatter formatter;
    vector<string> fileNameVector;
    vector<string> optionsVector;
    string optionsFileName = "";
    string arg;
    bool ok = true;
    bool shouldPrintHelp = false;
    bool shouldParseOptionsFile = true;

    _err = &cerr;
    _suffix = ".orig";

    printHelpTitle();

    // manage flags
    for (int i=1; i<argc; i++)
    {
        arg = string(argv[i]);

        if ( IS_PARAM_OPTION(arg ,"--options=none") )
        {
            shouldParseOptionsFile = false;
        }
        else if ( IS_PARAM_OPTION(arg ,"--options=") )
        {
            optionsFileName = GET_PARAM(arg, "--options=");
        }
        else if ( (arg == "-h") || (arg == "--help") || (arg == "-?") )
        {
            shouldPrintHelp = true;
        }
        else if (arg[0] == '-')
        {
            optionsVector.push_back(arg);
        }
        else // file-name
        {
            fileNameVector.push_back(arg);
        }
    }

    // parse options file
    if (shouldParseOptionsFile)
    {
        if (optionsFileName.compare("") == 0)
        {
            char* env = getenv("ISTYLE_OPTIONS");
            if (env != NULL)
                optionsFileName = string(env);
        }
        if (optionsFileName.compare("") == 0)
        {
            char* env = getenv("HOME");
            if (env != NULL)
                optionsFileName = string(env) + string("/.iStylerc");
        }
        if (optionsFileName.compare("") == 0)
        {
            char* drive = getenv("HOMEDRIVE");
            char* path = getenv("HOMEPATH");
            if (path != NULL)
                optionsFileName = string(drive) + string(path) + string("/.iStylerc");
        }

        if (!optionsFileName.empty())
        {
            ifstream optionsIn(optionsFileName.c_str());

            if (optionsIn)
            {
                vector<string> fileOptionsVector;
                // reading (whitespace seperated) strings from file into string vector
                importOptions(optionsIn, fileOptionsVector);
                ok = parseOptions(formatter,
                                  fileOptionsVector.begin(),
                                  fileOptionsVector.end(),
                                  string("Unknown option in default options file: "));

            }

            optionsIn.close();

            if (!ok)
            {
                printHelpSimple();
            }
        }
    }

    // parse options from command line

    ok = parseOptions(formatter,
                      optionsVector.begin(),
                      optionsVector.end(),
                      string("Unknown command line option: "));
    if (!ok)
    {
        printHelpSimple();
        exit(1);
    }

    if (shouldPrintHelp)
    {
        printHelpFull();
        exit(1);

    }

    // if no files have been given, use cin for input and cout for output
    if (fileNameVector.empty() )
    {
        printHelpSimple(1);

    }
    else
    {
        // indent the given files
        for (int i=0; i<fileNameVector.size(); i++)
        {
            string originalFileName = fileNameVector[i];
            string inFileName = originalFileName + _suffix;

            if ( ! isWriteable(originalFileName.c_str()) )
            {
                error(string("Error: File '" + originalFileName ).c_str() ,
                      "' does not exist, or is read-only.");
                continue;
            }

            remove(inFileName.c_str());

            if ( rename(originalFileName.c_str(), inFileName.c_str()) < 0)
            {
                error(string("Error: Could not rename " + originalFileName).c_str() ,
                      string(" to " + inFileName).c_str());
                exit(1);
            }

            ifstream in(inFileName.c_str());
            if (!in)
            {
                error("Could not open input file", inFileName.c_str());
                exit(1);
            }

            ofstream out(originalFileName.c_str());
            if (!out)
            {
                error("Could not open output file", originalFileName.c_str());
                exit(1);
            }

            formatter.init( new ASStreamIterator(&in) );
            while (formatter.hasMoreLines() )
            {
                out << formatter.nextLine();
                if (formatter.hasMoreLines())
                    out << endl;
            }

            out.flush();
            out.close();
            in.close();

            if ( ! shouldBackupFile )
            {
                remove( inFileName.c_str() );
            }

            // print
            SetColor(3,0);
            cout <<"Indented file -- " <<originalFileName << "."<< endl;
            SetColor(7,0);
        }
    }
    SetColor(7,0);
    return 0;
}
#endif	// ASTYLE_LIB