/*
 * Exception class
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

#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include "common.h"

/* errors enumeration */
enum EError {
    E_INTERNAL,
    E_SETTINGS,
    E_MEMORY,
    E_SOURCE
};

class CException {
    public:
        CException(EError, string);
        CException(EError);
        
        string message;
};

#endif
