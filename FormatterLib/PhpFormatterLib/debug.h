/*
 * Debug functions
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

#ifndef _DEBUG_H
#define _DEBUG_H

#include "common.h"

#ifdef DEBUG

/* debug function */
inline
void debug(const char *format, ...) {
    FILE   *file;
    va_list args;

    /* get args */
    va_start(args, format);

    /* write error to file */
    file = fopen("debug.txt", "a+");
    vfprintf(file, format, args);
    fwrite("\n", 1, 1, file);
    fclose(file);

    /* end args */
    va_end(args);
}

#else

/* debug function */
inline
void debug(const char *, ...) { }

#endif

#endif
