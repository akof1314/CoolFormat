//this file is part of notepad++
//Copyright (C)2003 Don HO ( donho@altern.org )
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

#include <string>
#include "StrUseful.h"
#include "GoToLineDlg.h"
#include "PluginDefinition.h"

extern NppData nppData;

BOOL CALLBACK OutputDlg::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case WM_SIZE:
		{
			int iDlgWidth, iDlgHeight;
			iDlgWidth = LOWORD(lParam);
			iDlgHeight = HIWORD(lParam);

			SetWindowPos(GetDlgItem(_hSelf, ID_GOLINE_EDIT),
				HWND_TOP, 0, 0, iDlgWidth, iDlgHeight,
				SWP_SHOWWINDOW);
			return FALSE;
		}
		case WM_CTLCOLOREDIT:
		{
			HDC hDC = (HDC)wParam;
			SetTextColor(hDC, _clrTextFg);
			SetBkMode(hDC, TRANSPARENT);
			return (LRESULT)_hBrush;
		}
		case WM_INITDIALOG:
		{
			return FALSE;
		}
		case WM_DESTROY:
		{
			DeleteObject(_hBrush);
			DeleteObject(_fontText);
			return FALSE;
		}
		default :
			return DockingDlgInterface::run_dlgProc(message, wParam, lParam);
	}
}

void OutputDlg::setOutput(const char *pszOutput)
{
	std::string strOutput(pszOutput);
	strOutput.erase(strOutput.find_last_not_of(" \n\r\t") + 1);
	strOutput = ReplaceAll(strOutput, "\n", "\r\n");

	if (strOutput.size() == 0)
	{
		if (isCreated())
		{
			display(false);
		}
	}
	else
	{
		if (!isCreated())
		{
			tTbData	data = { 0 };
			create(&data);

			// define the default docking behaviour
			data.uMask = DWS_DF_CONT_BOTTOM;

			data.pszModuleName = getPluginFileName();
			data.pszName = TEXT("CoolFormat");

			// the dlgDlg should be the index of funcItem where the current function pointer is
			data.dlgID = 0;
			resetStyle();
			::SendMessage(nppData._nppHandle, NPPM_DMMREGASDCKDLG, 0, (LPARAM)&data);
		}

		display(true);
		::SetDlgItemTextA(_hSelf, ID_GOLINE_EDIT, strOutput.c_str());
	}
}

void OutputDlg::resetStyle()
{
	if (!isCreated())
	{
		return;
	}

	int which = -1;
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
	if (which == -1)
		return;
	HWND hCurrScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

	COLORREF clrBg = ::SendMessage(hCurrScintilla, SCI_STYLEGETBACK, STYLE_DEFAULT, 0);
	_clrTextFg = ::SendMessage(hCurrScintilla, SCI_STYLEGETFORE, STYLE_DEFAULT, 0);
	char szFontName[255];
	::SendMessage(hCurrScintilla, SCI_STYLEGETFONT, STYLE_DEFAULT, *szFontName);
	int fontSize = ::SendMessage(hCurrScintilla, SCI_STYLEGETSIZE, STYLE_DEFAULT, 0);
	if (_hBrush)
	{
		DeleteObject(_hBrush); 
	}
	_hBrush = CreateSolidBrush(clrBg);
	if (_fontText)
	{
		DeleteObject(_fontText);
	}
	_fontText = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, s2ws(szFontName).c_str());
	::SendMessage(GetDlgItem(_hSelf, ID_GOLINE_EDIT), WM_SETFONT, WPARAM(_fontText), TRUE);

	RedrawWindow(_hSelf, NULL, NULL, RDW_INVALIDATE);
}

