//this file is part of notepad++
//Copyright (C)2003 Don HO <donho@altern.org>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include <stdio.h>
#include <string>
#include <sstream>

#include "PluginDefinition.h"
#include "menuCmdID.h"
#include "SynLanguage.h"

//
// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;

HINSTANCE hInstCF = NULL;

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE hModule)
{
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
	if (hInstCF)
	{
		FreeLibrary(hInstCF);
		hInstCF = NULL;
	}
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{

    //--------------------------------------------//
    //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
    //--------------------------------------------//
    // with function :
    // setCommand(int index,                      // zero based number to indicate the order of command
    //            TCHAR *commandName,             // the command name that you want to see in plugin menu
    //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
    //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
    //            bool check0nInit                // optional. Make this menu item be checked visually
    //            );

	ShortcutKey *pShKey;
	pShKey = new ShortcutKey;
	pShKey->_isAlt = true;
	pShKey->_isCtrl = true;
	pShKey->_isShift = true;
	pShKey->_key = 'M';
	setCommand(0, TEXT("Quick Format"), quickFormat, pShKey, false);

	pShKey = new ShortcutKey;
	pShKey->_isAlt = true;
	pShKey->_isCtrl = true;
	pShKey->_isShift = true;
	pShKey->_key = 'J';
	setCommand(1, TEXT("Selected Format"), selectedFormat, pShKey, false);
	setCommand(2, TEXT("-SEPARATOR-"), NULL, NULL, false);
	setCommand(3, TEXT("Formatter Settings"), formatterSettings, NULL, false);
}

//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut here
}


//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit) 
{
    if (index >= nbFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}

//----------------------------------------------//
//-- STEP 4. DEFINE YOUR ASSOCIATED FUNCTIONS --//
//----------------------------------------------//
void quickFormat()
{
    //// Open a new document
    //::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FILE_NEW);

    //// Get the current scintilla
    //int which = -1;
    //::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    //if (which == -1)
    //    return;
    //HWND curScintilla = (which == 0)?nppData._scintillaMainHandle:nppData._scintillaSecondHandle;

    //// Say hello now :
    //// Scintilla control has no Unicode mode, so we use (char *) here
    //::SendMessage(curScintilla, SCI_SETTEXT, 0, (LPARAM)"Hello, Notepad++!");
	doFormat(false);
}

void selectedFormat()
{
	doFormat(true);
}

void formatterSettings()
{
	::MessageBox(NULL, TEXT("Hello, Notepad++!"), TEXT("Notepad++ Plugin Template"), MB_OK);
}

struct LangSynType {
	LangType langType;
	unsigned int uLanguage;
};

LangSynType langSynType[] = {
	{ L_TXT, SYN_NORMALTEXT },
	{ L_PHP, SYN_PHP },
	{ L_C, SYN_CPP },
	{ L_CPP, SYN_CPP },
	{ L_CS, SYN_CS },
	{ L_OBJC, SYN_OBJECTIVEC },
	{ L_JAVA, SYN_JAVA },
	{ L_RC, SYN_NORMALTEXT },
	{ L_HTML, SYN_HTML },
	{ L_XML, SYN_XML },
	{ L_MAKEFILE, SYN_NORMALTEXT },
	{ L_PASCAL, SYN_PASCAL },
	{ L_BATCH, SYN_BATCH },
	{ L_INI, SYN_INI },
	{ L_NFO, SYN_NORMALTEXT },
	{ L_USER, SYN_NORMALTEXT },
	{ L_ASP, SYN_ASP },
	{ L_SQL, SYN_SQL },
	{ L_VB, SYN_VB },
	{ L_JS, SYN_JAVASCRIPT },
	{ L_CSS, SYN_CSS },
	{ L_PERL, SYN_PERL },
	{ L_PYTHON, SYN_PYTHON },
	{ L_LUA, SYN_LUA },
	{ L_TEX, SYN_NORMALTEXT },
	{ L_FORTRAN, SYN_FORTRAN },
	{ L_BASH, SYN_NORMALTEXT },
	{ L_FLASH, SYN_ACTIONSCRIPT },
	{ L_NSIS, SYN_NORMALTEXT },
	{ L_TCL, SYN_NORMALTEXT },
	{ L_LISP, SYN_LISP },
	{ L_SCHEME, SYN_NORMALTEXT },
	{ L_ASM, SYN_ASM },
	{ L_DIFF, SYN_NORMALTEXT },
	{ L_PROPS, SYN_NORMALTEXT },
	{ L_PS, SYN_NORMALTEXT },
	{ L_RUBY, SYN_RUBY },
	{ L_SMALLTALK, SYN_NORMALTEXT },
	{ L_VHDL, SYN_VHDL },
	{ L_KIX, SYN_NORMALTEXT },
	{ L_AU3, SYN_ACTIONSCRIPT },
	{ L_CAML, SYN_NORMALTEXT },
	{ L_ADA, SYN_ADA },
	{ L_VERILOG, SYN_VERILOG },
	{ L_MATLAB, SYN_NORMALTEXT },
	{ L_HASKELL, SYN_HASKELL },
	{ L_INNO, SYN_NORMALTEXT },
	{ L_SEARCHRESULT, SYN_NORMALTEXT },
	{ L_CMAKE, SYN_NORMALTEXT },
	{ L_YAML, SYN_NORMALTEXT },
	{ L_EXTERNAL, SYN_NORMALTEXT }
};

typedef bool( * DoFormatterProc)(unsigned int uLanguage,
	const std::string &strTextIn,
	std::string &strTextOut,
	std::string &strMsgOut,
	unsigned int uCodepage);

typedef void( * ShowSettingsProc)();

DoFormatterProc DoFormatter;
ShowSettingsProc ShowSettings;

void loadCFDll()
{
	if (hInstCF == NULL)
	{
		hInstCF = LoadLibrary(TEXT("plugins\\CoolFormat\\CoolFormatLib.dll"));
		if (hInstCF)
		{
			DoFormatter = (DoFormatterProc)GetProcAddress(hInstCF, "DoFormatter");
			ShowSettings = (ShowSettingsProc)GetProcAddress(hInstCF, "ShowSettings");
			if (DoFormatter == NULL || ShowSettings == NULL)
			{
#ifdef _DEBUG
				std::wstringstream ss;
				ss << GetLastError();
				::MessageBox(NULL, ss.str().c_str(), NPP_PLUGIN_NAME, MB_OK);
#endif
			}
		}
		else
		{
			::MessageBox(NULL, TEXT("Cannot load CoolFormatLib.dll!"), NPP_PLUGIN_NAME, MB_OK);
		}
	}
}

void doFormat(bool bSelected)
{
	loadCFDll();

	int which = -1;
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
	if (which == -1)
		return;
	HWND hCurrScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

	size_t nTextLen = ::SendMessage(hCurrScintilla, SCI_GETTEXTLENGTH, 0, 0);
	if (nTextLen == 0)
		return;

	char *pText = NULL;
	std::string initIndent("");
	if (bSelected)
	{
		pText = new char[nTextLen + 1];
		::SendMessage(hCurrScintilla, SCI_GETTEXT, nTextLen + 1, (LPARAM)pText);
	} 
	else
	{
		size_t selStart = ::SendMessage(hCurrScintilla, SCI_GETSELECTIONSTART, 0, 0);
		size_t selEnd = ::SendMessage(hCurrScintilla, SCI_GETSELECTIONEND, 0, 0);

		// 格式化选中部分
		char testChar;
		// 找行头
		while (selStart > 0)
		{
			testChar = (char)::SendMessage(hCurrScintilla, SCI_GETCHARAT, selStart - 1, 0);
			if (testChar == '\r' || testChar == '\n')
				break;

			--selStart;
		}
		// 找行尾
		while (selEnd < nTextLen)
		{
			testChar = (char)::SendMessage(hCurrScintilla, SCI_GETCHARAT, selEnd, 0);
			if (testChar == '\r' || testChar == '\n')
				break;

			++selEnd;
		}

		// 重新选择整行
		::SendMessage(hCurrScintilla, SCI_SETSELECTIONSTART, selStart, 0);
		::SendMessage(hCurrScintilla, SCI_SETSELECTIONEND, selEnd, 0);

		// 获得 Sel
		size_t nTextLenSel = ::SendMessage(hCurrScintilla, SCI_GETSELTEXT, 0, 0);
		pText = new char[nTextLenSel];
		::SendMessage(hCurrScintilla, SCI_GETSELTEXT, nTextLenSel, (LPARAM)pText);

		// 得到 Initial Indent
		for (size_t i = 0; i < nTextLenSel; ++i)
		{
			testChar = pText[i];
			if (testChar != ' ' && testChar != '\t')
				break;
			initIndent += testChar;
		}
	}

	std::string strTextOut;
	std::string strMsgOut;
	if (DoFormatter)
	{
		LangType langType = L_TXT;
		::SendMessage(nppData._nppHandle, NPPM_GETCURRENTLANGTYPE, 0, (LPARAM)&langType);
		unsigned int uLanguage = langSynType[langType].uLanguage;
		unsigned int uCodepage = get;

		if (DoFormatter(uLanguage, pText, strTextOut, strMsgOut, uCodepage))
		{
			::SendMessage(hCurrScintilla, SCI_SETTEXT, 0, (LPARAM)strTextOut.c_str());
		}
		::MessageBoxA(NULL, strTextOut.c_str(), "s", MB_OK);
		::MessageBoxA(NULL, strMsgOut.c_str(), "s2", MB_OK);
	}
	delete[] pText;
}

void showSettings()
{
	loadCFDll();

	if (ShowSettings)
	{
		ShowSettings();
	}
}
