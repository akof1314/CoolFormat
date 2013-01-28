/*
 * Copyright 2005, 2006, 2007 Florian Schmitz
 *
 * This file is part of CSSTidy.
 *
 *  CSSTidy is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   CSSTidy is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 * 
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
 
#include "csspp_globals.hpp"
using namespace std;

const string trim(const string istring)
{
	std::string::size_type first = istring.find_first_not_of(" \n\t\r\0xb");
	if (first == std::string::npos) {
		return std::string();
	}
	else {
		std::string::size_type last = istring.find_last_not_of(" \n\t\r\0xb");
		return istring.substr( first, last - first + 1);
	}
}

const string ltrim(const string istring)
{
	std::string::size_type first = istring.find_first_not_of(" \n\t\r\0xb");
	if (first == std::string::npos) {
		return std::string();
	}
	else {
		return istring.substr( first );
	}
}


const string rtrim(const string istring)
{
	std::string::size_type last = istring.find_last_not_of(" \n\t\r\0xb"); /// must succeed
	return istring.substr( 0, last + 1);
}

const string rtrim(const string istring, const string chars)
{
	std::string::size_type last = istring.find_last_not_of(chars); /// must succeed
	return istring.substr( 0, last + 1);
}

string strip_tags(string istring)
{
	bool intag = false;
	string new_string;
		
	for(int i = 0; i < istring.length(); i++)
	{
		if(istring[i] != '<' && !intag)
		{
			new_string += istring[i];
		}
		if(istring[i] == '<' && !intag)
		{
			intag = true;
		}
		if(istring[i] == '>' && intag)
		{
			intag = false;
		}			
	}
	return new_string;
}
