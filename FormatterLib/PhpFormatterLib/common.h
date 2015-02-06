/*
 * Common types and functions
 *
 * Copyright 2009, Gerben van Veenendaal (http://www.gerbenvv.nl)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License in the COPYING file at the
 * root directory of this project for more details.
 */

#ifndef _COMMON_H
#define _COMMON_H

/* includes common headers */
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cstring> //NOTE: <cstring> needed?
#include <cstdarg>
#include <malloc.h>
#include <sstream>

/* linux includes */
#ifndef WIN32
//#  include <alloca.h> //NOTE: needed for parser; malloca
#  include <stdlib.h> //NOTE: what are the C++ variants for these two?
#  include <stdio.h>
#endif

/* use std namespace */
using namespace std;

/* scanner and parser buffer sizes */
#define SCANNER_BUFFER    1024  //1Mb scanner buffer
#define PARSER_INIT_STACK 200   //init 200 nodes
#define PARSER_MAX_STACK  10000 //max 10000 nodes

/* common types */
typedef unsigned int   uint;
typedef unsigned long  ulong;
typedef unsigned char  uchar;
typedef unsigned short ushort;

//turn off debugging
#undef DEBUG

//include string and debug functions
#include "str.h"
#include "debug.h"

#endif
