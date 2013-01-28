/*
 * Scanner class
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

#ifndef _SCANNER_H
#define _SCANNER_H

#include "common.h"
#include "node.h"

/* state enumeration */
enum EScannerState {
    SS_HTML,
    SS_PHP,
    SS_OBJECT_PROPERTY,
    SS_HALT_COMPILER
    
    /*
    SS_BACK_QUOTE_STRING,
    SS_SINGLE_QUOTE_STRING,
    SS_DOUBLE_QUOTE_STRING,
    SS_SHORT_COMMENT,
    SS_LONG_COMMENT
    */
};

class CScanner {
    public:
        CScanner(void);
        ~CScanner(void);
        
        void Init(const char* pSourceIn);
        void ScanAhead(void);
        
        void FillBuffer(void);
        uint CountNewlines(string *);
        void AddNewlines(string *);
        void TokenNode(CNode *);
        int  Scan(CNode **);
        
        //FILE *file;
        
        uchar *bottom,
              *token,
              *limit,
              *eof,
              *top,
              *cursor,
              *marker;
        string strInput;
        EScannerState state;
        
        uint line;
        
        CNode *previous_node;
        
        bool in_short_tag;
        
        CNode *next_node;
        int    next_token;
};

#endif
