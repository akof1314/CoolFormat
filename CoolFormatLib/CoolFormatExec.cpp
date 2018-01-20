#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <assert.h>
#include <algorithm>

#include "StrUseful.h"
#include "GlobalTidy.h"
#include "FormatterHelp.h"

using namespace std;
const string _version = "1.0";

//////////////////////////////////////////////////////////////////////////

struct LanguageExt {
    const char *langName;	//ÓïÑÔÃû³Æ
    const char *extName;	//Ä¬ÈÏºó×ºÃû
    unsigned int langID;	//ÓïÑÔÃ¶¾Ù
};

LanguageExt _LangExts[MAX_SYN_LANG] = {
	{"ActionScript",		"*.as;*.mx;",																			SYN_ACTIONSCRIPT},
	{"Ada",					"*.ada;*.ads;*.adb;",																	SYN_ADA},
	{"ASM",					"*.asm;",																				SYN_ASM},
	{"ASP",					"*.asp;",																				SYN_ASP},
	{"AutoHotkey",			"*.ahk;*.ia;*.scriptlet;*.hkml;",														SYN_AUTOHOTKEY},
	{"AutoIt",				"*.au3;",																				SYN_AUTOIT},
	{"Batch",				"*.bat;*.cmd;*.nt;",																	SYN_BATCH},
	{"COBOL",				"*.cbl;*.cbd;*.cdb;*.cdc;*.cob;",														SYN_COBOL},
	{"C",					"*.h;*.hpp;*.hxx;*.cpp;*.cxx;*.cc;*.c;",												SYN_CPP},
	{"CS",					"*.cs;",																				SYN_CS},
	{"CSS",					"*.css;",																				SYN_CSS},
	{"D",					"*.d;",																					SYN_D},
	{"Fortran",				"*.f;*.for;*.f90;*.f95;*.f2k;",															SYN_FORTRAN},
	{"Haskell",				"*.hs;*.lhs;*.las;",																	SYN_HASKELL},
	{"HTML",				"*.html;*.htm;*.shtml;*.shtm;*.xhtml;",													SYN_HTML},
	{"INI",					"*.ini;*.inf;*.reg;*.url;",																SYN_INI},
	{"Java",				"*.java;",																				SYN_JAVA},
	{"JavaScript",			"*.js;",																				SYN_JAVASCRIPT},
	{"JSON",				"*.json;",																				SYN_JSON},
	{"JSP",					"*.jsp;",																				SYN_JSP},
	{"LISP",				"*.lsp;*.lisp;",																		SYN_LISP},
	{"LUA",					"*.lua;",																				SYN_LUA},
	{"NormalText",			"*.txt;",																				SYN_NORMALTEXT},
	{"Objective-C",			"*.h;*.m;*.mm;",																		SYN_OBJECTIVEC},
	{"Pascal",				"*.dpr;*.dpk;*.pas;*.dfm;*.inc;*.pp;",													SYN_PASCAL},
	{"Perl",				"*.pl;*.pm;*.plx;",																		SYN_PERL},
	{"PHP",					"*.php;*.php3;*.php4;*.php5;*.phtml;",													SYN_PHP},
	{"Python",				"*.py;*.pyw;",																			SYN_PYTHON},
	{"Ruby",				"*.rb;*.rbw;",																			SYN_RUBY},
	{"SQL",					"*.sql;",																				SYN_SQL},
	{"VB",					"*.vb;*.bas;*.frm;*.cls;*.ctl;*.pag;*.dsr;*.dob;*.vbs;*.dsm;*.vbp;*.vbg;*.mak;*.vbw;",	SYN_VB},
	{"Verilog",				"*.v;*.vl;*.vmd;",																		SYN_VERILOG},
	{"VHDL",				"*.vhd;*.vhdl;*.vho;",																	SYN_VHDL},
	{"XML",					"*.xml;*.xsl;*.svg;*.xul;*.xsd;*.dtd;*.xslt;*.axl;*.xrc;*.rdf;",						SYN_XML}
};

unsigned int GetLanguageByExt(const string& ext)
{
    string strFind = ext + ";";
    string strExt;
    for (unsigned int i = 0; i < MAX_SYN_LANG; i++)
    {
        strExt = _LangExts[i].extName;
        if (strExt.find(strFind) != string::npos)
        {
            return i;
        }
    }

    return SYN_NORMALTEXT;
}

unsigned int GetLanguageByName(const string& name)
{
    string strName;
    for (unsigned int i = 0; i < MAX_SYN_LANG; i++)
    {
        strName = _LangExts[i].langName;
        transform(strName.begin(), strName.end(), strName.begin(), ::tolower);
        if (strName.compare(name) == 0)
        {
            return i;
        }
    }

    return SYN_NORMALTEXT;
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

enum FileEncoding
{
    ENCODING_8BIT,
    UTF_16BE,
    UTF_16LE,     // Windows default
    UTF_32BE,
    UTF_32LE
};

enum LineEndFormat
{
    LINEEND_DEFAULT,	// Use line break that matches most of the file
    LINEEND_WINDOWS,
    LINEEND_LINUX,
    LINEEND_MACOLD,
    LINEEND_CRLF = LINEEND_WINDOWS,
    LINEEND_LF = LINEEND_LINUX,
    LINEEND_CR = LINEEND_MACOLD
};

void error(const char* why, const char* what)
{
    cout << why << ' ' << what << endl;
}

// check files for 16 or 32 bit encoding
// the file must have a Byte Order Mark (BOM)
// NOTE: some string functions don't work with NULLs (e.g. length())
FileEncoding detectEncoding(const char* data, size_t dataSize)
{
    FileEncoding encoding = ENCODING_8BIT;

    if (dataSize >= 4 && memcmp(data, "\x00\x00\xFE\xFF", 4) == 0)
        encoding = UTF_32BE;
    else if (dataSize >= 4 && memcmp(data, "\xFF\xFE\x00\x00", 4) == 0)
        encoding = UTF_32LE;
    else if (dataSize >= 2 && memcmp(data, "\xFE\xFF", 2) == 0)
        encoding = UTF_16BE;
    else if (dataSize >= 2 && memcmp(data, "\xFF\xFE", 2) == 0)
        encoding = UTF_16LE;

    return encoding;
}

// Swap the two low order bytes of a 16 bit integer value.
int swap16bit(int value)
{
    return (((value & 0xff) << 8) | ((value & 0xff00) >> 8));
}

size_t utf8LengthFromUtf16(const char* utf16In, size_t inLen, bool isBigEndian)
{
    size_t len = 0;
    size_t wcharLen = inLen / 2;
    const short* uptr = reinterpret_cast<const short*>(utf16In);
    for (size_t i = 0; i < wcharLen && uptr[i];)
    {
        size_t uch = isBigEndian ? swap16bit(uptr[i]) : uptr[i];
        if (uch < 0x80)
            len++;
        else if (uch < 0x800)
            len += 2;
        else if ((uch >= 0xD800) && (uch <= 0xDFFF))
        {
            len += 4;
            i++;
        }
        else
            len += 3;
        i++;
    }
    return len;
}

// Adapted from SciTE Utf8_16.cxx.
// Copyright (C) 2002 Scott Kirkwood.
// Modified for Artistic Style by Jim Pattee.
// Convert a utf-8 file to utf-16.
size_t utf8ToUtf16(char* utf8In, size_t inLen, bool isBigEndian, char* utf16Out)
{
    typedef unsigned short utf16; // 16 bits
    typedef unsigned char utf8;   // 8 bits
    typedef unsigned char ubyte;  // 8 bits
    enum eState { eStart, eSecondOf4Bytes, ePenultimate, eFinal };

    int nCur = 0;
    ubyte* pRead = reinterpret_cast<ubyte*>(utf8In);
    utf16* pCur = reinterpret_cast<utf16*>(utf16Out);
    const ubyte* pEnd = pRead + inLen;
    const utf16* pCurStart = pCur;
    eState state = eStart;

    // the BOM will automatically be converted to utf-16
    while (pRead < pEnd)
    {
        switch (state)
        {
        case eStart:
            if ((0xF0 & *pRead) == 0xF0)
            {
                nCur = (0x7 & *pRead) << 18;
                state = eSecondOf4Bytes;
            }
            else if ((0xE0 & *pRead) == 0xE0)
            {
                nCur = (~0xE0 & *pRead) << 12;
                state = ePenultimate;
            }
            else if ((0xC0 & *pRead) == 0xC0)
            {
                nCur = (~0xC0 & *pRead) << 6;
                state = eFinal;
            }
            else
            {
                nCur = *pRead;
                state = eStart;
            }
            break;
        case eSecondOf4Bytes:
            nCur |= (0x3F & *pRead) << 12;
            state = ePenultimate;
            break;
        case ePenultimate:
            nCur |= (0x3F & *pRead) << 6;
            state = eFinal;
            break;
        case eFinal:
            nCur |= (0x3F & *pRead);
            state = eStart;
            break;
            // no default case is needed
        }
        ++pRead;

        if (state == eStart)
        {
            int codePoint = nCur;
            if (codePoint >= 0x10000)
            {
                codePoint -= 0x10000;
                int lead = (codePoint >> 10) + 0xD800;
                *pCur++ = static_cast<utf16>(isBigEndian ? swap16bit(lead) : lead);
                int trail = (codePoint & 0x3ff) + 0xDC00;
                *pCur++ = static_cast<utf16>(isBigEndian ? swap16bit(trail) : trail);
            }
            else
                *pCur++ = static_cast<utf16>(isBigEndian ? swap16bit(codePoint) : codePoint);
        }
    }
    // return value is the output length in BYTES (not wchar_t)
    return (pCur - pCurStart) * 2;
}

// Adapted from SciTE UniConversion.cxx.
// Copyright 1998-2001 by Neil Hodgson <neilh@scintilla.org>
// Modified for Artistic Style by Jim Pattee.
// Compute the length of an output utf-16 file given a utf-8 file.
// Return value is the size in BYTES (not wchar_t).
size_t utf16LengthFromUtf8(const char* utf8In, size_t len)
{
    size_t ulen = 0;
    size_t charLen;
    for (size_t i = 0; i < len;)
    {
        unsigned char ch = static_cast<unsigned char>(utf8In[i]);
        if (ch < 0x80)
            charLen = 1;
        else if (ch < 0x80 + 0x40 + 0x20)
            charLen = 2;
        else if (ch < 0x80 + 0x40 + 0x20 + 0x10)
            charLen = 3;
        else
        {
            charLen = 4;
            ulen++;
        }
        i += charLen;
        ulen++;
    }
    // return value is the length in bytes (not wchar_t)
    return ulen * 2;
}

// Adapted from SciTE Utf8_16.cxx.
// Copyright (C) 2002 Scott Kirkwood.
// Modified for Artistic Style by Jim Pattee.
// Convert a utf-16 file to utf-8.
size_t utf16ToUtf8(char* utf16In, size_t inLen, bool isBigEndian,
    bool firstBlock, char* utf8Out)
{
    typedef unsigned short utf16; // 16 bits
    typedef unsigned char utf8;   // 8 bits
    typedef unsigned char ubyte;  // 8 bits
    enum eState { eStart, eSecondOf4Bytes, ePenultimate, eFinal };

    int nCur16 = 0;
    int nCur = 0;
    ubyte* pRead = reinterpret_cast<ubyte*>(utf16In);
    ubyte* pCur = reinterpret_cast<ubyte*>(utf8Out);
    const ubyte* pEnd = pRead + inLen;
    const ubyte* pCurStart = pCur;
    static eState state = eStart;	// state is retained for subsequent blocks
    if (firstBlock)
        state = eStart;

    // the BOM will automatically be converted to utf-8
    while (pRead < pEnd)
    {
        switch (state)
        {
        case eStart:
            if (pRead >= pEnd)
            {
                ++pRead;
                break;
            }
            if (isBigEndian)
            {
                nCur16 = static_cast<utf16>(*pRead++ << 8);
                nCur16 |= static_cast<utf16>(*pRead);
            }
            else
            {
                nCur16 = *pRead++;
                nCur16 |= static_cast<utf16>(*pRead << 8);
            }
            if (nCur16 >= 0xD800 && nCur16 <= 0xDBFF)
            {
                ++pRead;
                int trail;
                if (isBigEndian)
                {
                    trail = static_cast<utf16>(*pRead++ << 8);
                    trail |= static_cast<utf16>(*pRead);
                }
                else
                {
                    trail = *pRead++;
                    trail |= static_cast<utf16>(*pRead << 8);
                }
                nCur16 = (((nCur16 & 0x3ff) << 10) | (trail & 0x3ff)) + 0x10000;
            }
            ++pRead;

            if (nCur16 < 0x80)
            {
                nCur = static_cast<ubyte>(nCur16 & 0xFF);
                state = eStart;
            }
            else if (nCur16 < 0x800)
            {
                nCur = static_cast<ubyte>(0xC0 | (nCur16 >> 6));
                state = eFinal;
            }
            else if (nCur16 < 0x10000)
            {
                nCur = static_cast<ubyte>(0xE0 | (nCur16 >> 12));
                state = ePenultimate;
            }
            else
            {
                nCur = static_cast<ubyte>(0xF0 | (nCur16 >> 18));
                state = eSecondOf4Bytes;
            }
            break;
        case eSecondOf4Bytes:
            nCur = static_cast<ubyte>(0x80 | ((nCur16 >> 12) & 0x3F));
            state = ePenultimate;
            break;
        case ePenultimate:
            nCur = static_cast<ubyte>(0x80 | ((nCur16 >> 6) & 0x3F));
            state = eFinal;
            break;
        case eFinal:
            nCur = static_cast<ubyte>(0x80 | (nCur16 & 0x3F));
            state = eStart;
            break;
            // no default case is needed
        }
        *pCur++ = static_cast<ubyte>(nCur);
    }
    return pCur - pCurStart;
}

FileEncoding readFile(const string& fileName_, stringstream& in)
{
    const int blockSize = 65536;	// 64 KB
    ifstream fin(fileName_.c_str(), ios::binary);
    if (!fin)
        error("Cannot open input file", fileName_.c_str());
    char* data = new (nothrow) char[blockSize];
    if (data == nullptr)
        error("Cannot allocate memory for input file", fileName_.c_str());
    fin.read(data, blockSize);
    if (fin.bad())
        error("Cannot read input file", fileName_.c_str());
    size_t dataSize = static_cast<size_t>(fin.gcount());
    FileEncoding encoding = detectEncoding(data, dataSize);
    if (encoding == UTF_32BE || encoding == UTF_32LE)
        error(("Cannot process UTF-32 encoding"), fileName_.c_str());
    bool firstBlock = true;
    bool isBigEndian = (encoding == UTF_16BE);
    while (dataSize != 0)
    {
        if (encoding == UTF_16LE || encoding == UTF_16BE)
        {
            // convert utf-16 to utf-8
            size_t utf8Size = utf8LengthFromUtf16(data, dataSize, isBigEndian);
            char* utf8Out = new (nothrow) char[utf8Size];
            if (utf8Out == nullptr)
                error("Cannot allocate memory for utf-8 conversion", fileName_.c_str());
            size_t utf8Len = utf16ToUtf8(data, dataSize, isBigEndian, firstBlock, utf8Out);
            assert(utf8Len == utf8Size);
            in << string(utf8Out, utf8Len);
            delete[] utf8Out;
        }
        else
            in << string(data, dataSize);
        fin.read(data, blockSize);
        if (fin.bad())
            error("Cannot read input file", fileName_.c_str());
        dataSize = static_cast<size_t>(fin.gcount());
        firstBlock = false;
    }
    fin.close();
    delete[] data;
    return encoding;
}

void writeFile(const string& fileName_, FileEncoding encoding, ostringstream& out)
{
    // write the output file
    ofstream fout(fileName_.c_str(), ios::binary | ios::trunc);
    if (!fout)
        error("Cannot open output file", fileName_.c_str());
    if (encoding == UTF_16LE || encoding == UTF_16BE)
    {
        // convert utf-8 to utf-16
        bool isBigEndian = (encoding == UTF_16BE);
        size_t utf16Size = utf16LengthFromUtf8(out.str().c_str(), out.str().length());
        char* utf16Out = new char[utf16Size];
        size_t utf16Len = utf8ToUtf16(const_cast<char*>(out.str().c_str()),
            out.str().length(), isBigEndian, utf16Out);
        assert(utf16Len == utf16Size);
        fout << string(utf16Out, utf16Len);
        delete[] utf16Out;
    }
    else
        fout << out.str();

    fout.close();
}

/**
* Open input file, format it, and close the output.
*
* @param fileName_     The path and name of the file to be processed.
*/
void formatFile(const string& fileName_, unsigned int mode)
{
    if (mode == -1)
    {
        string::size_type pos = fileName_.rfind('.');
        if (pos == string::npos)
        {
            return;
        }

        mode = GetLanguageByExt(fileName_.substr(pos));
    }
    if (mode == SYN_NORMALTEXT)
    {
        return;
    }

    stringstream in;
    ostringstream out;
    FileEncoding encoding = readFile(fileName_, in);

    string strTextOut, strMsgOut;
    CFormatterHelp formatter;

    bool doFormatted = formatter.DoFormatter(mode, in.str(), strTextOut, strMsgOut);;
    if (doFormatted)
    {
        out << strTextOut;
        writeFile(fileName_, encoding, out);
    }
}


void formatCinToCout(unsigned int mode, LineEndFormat lineEndFormat)
{
    if (mode == -1)
    {
        return;
    }

    // Using cin.tellg() causes problems with both Windows and Linux.
    // The Windows problem occurs when the input is not Windows line-ends.
    // The tellg() will be out of sequence with the get() statements.
    // The Linux cin.tellg() will return -1 (invalid).
    // Copying the input sequentially to a stringstream before
    // formatting solves the problem for both.
    istream* inStream = &cin;
    stringstream outStream;
    char ch;
    inStream->get(ch);
    while (!inStream->eof() && !inStream->fail())
    {
        outStream.put(ch);
        inStream->get(ch);
    }

    string strTextOut, strMsgOut;
    CFormatterHelp formatter;

    bool doFormatted = formatter.DoFormatter(mode, outStream.str(), strTextOut, strMsgOut);;
    if (doFormatted)
    {
        cout << strTextOut;
    }
    cout.flush();
}

//////////////////////////////////////////////////////////////////////////

void printHelp()
{
    cout << endl;
    cout << "                     CoolFormat " << _version << endl;
    cout << "                     https://github.com/akof1314/CoolFormat\n";
    cout << endl;
    cout << "Usage:\n";
    cout << "------\n";
    cout << "            coolformatexec [OPTIONS] File1 File2 File3 [...]\n";
    cout << endl;
    cout << "            coolformatexec [OPTIONS] < Original > Beautified\n";
    cout << endl;
    cout << "Options:\n";
    cout << "------------------\n";
    cout << "    --options=####\n";
    cout << "    Specify an options file #### to read and use.\n";
    cout << endl;
    cout << "    --lineend=windows  \n";
    cout << "    --lineend=linux    \n";
    cout << "    --lineend=macold   \n";
    cout << "    Force use of the specified line end style. Valid options\n";
    cout << "    are windows (CRLF), linux (LF), and macold (CR).\n";
    cout << endl;
    cout << "    --mode=c\n";
    cout << "    Indent a C or C++ source file.\n";
    cout << endl;
    cout << "    --mode=java\n";
    cout << "    Indent a Java source file.\n";
    cout << endl;
    cout << "    --mode=cs\n";
    cout << "    Indent a C# source file.\n";
    cout << endl;
}

bool isOption(const string& arg, const char* op)
{
    return arg.compare(op) == 0;
}

bool isParamOption(const string& arg, const char* option)
{
    bool retVal = arg.compare(0, strlen(option), option) == 0;
    // if comparing for short option, 2nd char of arg must be numeric
    if (retVal && strlen(option) == 1 && arg.length() > 1)
        if (!isdigit((unsigned char)arg[1]))
            retVal = false;
    return retVal;
}

int processOptionMode(const string& arg)
{
    string::size_type pos = arg.find("--mode=");
    if (pos != string::npos)
    {
        string lanName = arg.substr(7);
        unsigned int mode = GetLanguageByName(lanName);
        if (mode == SYN_NORMALTEXT)
        {
            return -1;
        }
        return mode;
    }

    return -1;
}

void processOptions(const vector<string>& argvOptions)
{
    string arg;
    string optionsFileName = "CoolFormatConfig.cfconfig";
    int mode = -1;
    LineEndFormat lineEndFormat = LINEEND_DEFAULT;
    vector<string> fileNameVector;

    for (size_t i = 0; i < argvOptions.size(); i++)
    {
        arg = argvOptions[i];

        if (isParamOption(arg, "--options="))
        {
            optionsFileName = arg.substr(strlen("--options="));
        }
        else if (isOption(arg, "-h")
            || isOption(arg, "--help")
            || isOption(arg, "-?"))
        {
            printHelp();
            exit(EXIT_SUCCESS);
        }        
        else if (isOption(arg, "-V")
            || isOption(arg, "--version"))
        {
            cout << "CoolFormat Version " << _version << endl;
            exit(EXIT_SUCCESS);
        }
        else if (isParamOption(arg, "--mode="))
        {
            mode = processOptionMode(arg);
        }
        else if (isOption(arg, "--lineend=windows"))
        {
            lineEndFormat = LINEEND_WINDOWS;
        }
        else if (isOption(arg, "--lineend=linux"))
        {
            lineEndFormat = LINEEND_LINUX;
        }
        else if (isOption(arg, "--lineend=macold"))
        {
            lineEndFormat = LINEEND_MACOLD;
        }
        else // file-name
        {
            fileNameVector.emplace_back(arg);
        }
    }

    g_GlobalTidy.InitGlobalTidy("", optionsFileName);

    if (!fileNameVector.empty())
    {
        for (size_t i = 0; i < fileNameVector.size(); i++)
        {
            formatFile(fileNameVector[i], mode);
        }
    }
    else
    {
        if (mode == -1)
        {
            printHelp();
            return;
        }
        formatCinToCout(mode, lineEndFormat);
    }
}

int main(int argc, char** argv)
{
    vector<string> optionsVector;
    for (int i = 1; i < argc; i++)
    {
        optionsVector.emplace_back(string(argv[i]));
    }
    processOptions(optionsVector);

	return 0;
}

