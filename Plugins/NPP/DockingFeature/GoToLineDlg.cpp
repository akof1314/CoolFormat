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
		default :
			return DockingDlgInterface::run_dlgProc(message, wParam, lParam);
	}
}

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to)
{
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

void OutputDlg::setOutput(const char *pszOutput)
{
	std::string strOutput(pszOutput);
	strOutput.erase(strOutput.find_last_not_of(" \n\r\t") + 1);
	strOutput = ReplaceAll(strOutput, "\n", "\r\n");

	if (strOutput.size() == 0)
	{
		display(false);
	}
	else
	{
		display(true);
		::SetDlgItemTextA(_hSelf, ID_GOLINE_EDIT, strOutput.c_str());
	}
}

