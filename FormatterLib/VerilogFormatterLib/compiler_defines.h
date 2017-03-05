// $Id: compiler_defines.h,v 1.2 2004/02/04 07:35:10 devsolar Exp $
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

// comment out the line below if your compiler does NOT understand NAMESPACES
#define USES_NAMESPACE

// gcc 2.x has a non-standard implementation of string.compare; the COMPARE()
// macro fixes this.
#if defined(__GNUC__) && (__GNUC__ < 3)
// gcc 2.x
#define COMPARE(place, length, str)       compare((str), (place), (length))
#else
// all others
#define COMPARE(place, length, str)       compare((place), (length), (str))
#endif

// Get rid of annoying MSVC warnings on debug builds about lengths of
// identifiers in template instantiations. (Contributed by John A. McNamara)
#ifdef _MSC_VER
#pragma warning( disable:4786 )
#endif
