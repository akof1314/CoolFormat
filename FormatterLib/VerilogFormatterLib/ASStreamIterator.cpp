// $Id: ASStreamIterator.cpp,v 1.2 2004/02/06 08:15:39 devsolar Exp $
// --------------------------------------------------------------------------
//
// Copyright (c) 1998,1999,2000,2001,2002 Tal Davidson. All rights reserved.
//
// ASStreamIterator.h
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

#include "astyle.h"

#include <istream>
//~ #include <strstream>


#include <sstream>

#ifdef USES_NAMESPACE
using namespace std;

namespace istyle
{
#endif

// --------------------------------------------------------------------------
// ASStreamIterator
// --------------------------------------------------------------------------

ASStreamIterator::ASStreamIterator(istream *in)
{
    inStream = in;
    linecount = 0;
}

ASStreamIterator::~ASStreamIterator()
{
    //delete inStream;
}


bool ASStreamIterator::hasMoreLines() const
{
    if (*inStream)
        return !inStream->eof();
    else
        return false;
}


string ASStreamIterator::nextLine()
{
    string buffer;
    getline(*inStream, buffer);
    if (inStream->fail() && !inStream->eof())
    {
        string str;
        str = "Could not read line " ;
        //error(str.c_str(), "(too long?)");
    }
    if (buffer.size() > 0 && (buffer[buffer.size() - 1] == '\r'))
    {
        buffer.erase(buffer.size() - 1);
    }
    ++linecount;
    return buffer;
}

#ifdef USES_NAMESPACE
}
#endif
