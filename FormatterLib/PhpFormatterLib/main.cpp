/*
 * Main
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

#include "common.h"

#include "exception.h"
#include "settings.h"
#include "formatter.h"
#include "scanner.h"
#include "parser.h"

/* globals */
CSettings  *settings  = NULL;
CFormatter *formatter = NULL;
CScanner   *scanner   = NULL;
CParser    *parser    = NULL;

/* main function */
int main(int argc, char **argv) {
    try {
        /* create settings class */
        settings = new CSettings();
        if (settings == NULL) {
            throw new CException(E_MEMORY);
        }
        
        /* create formatter class */
        formatter = new CFormatter();
        if (formatter == NULL) {
            throw new CException(E_MEMORY);
        }
        
        /* create scanner class */
        scanner = new CScanner();
        if (scanner == NULL) {
            throw new CException(E_MEMORY);
        }
        
        /* create parser class */
        parser = new CParser();
        if (parser == NULL) {
            throw new CException(E_MEMORY);
        }
        
        /* init settings */
        settings->InitFromArguments(argc, argv);

        //show input
        cout << "Input: " << settings->input << "\n";
        
        /* init formatter */
        formatter->Init();
        
        /* init scanner */
        scanner->Init();
        
        /* init parser */
        scanner->Init();
        
        /* start formatting */
        formatter->Run();
    }
    
    /* catch exceptions */
    catch (CException *exception) {
        /* show version and copyright */
        if ((settings == NULL) || !settings->quiet) {
            cout << "PHPFormatter version 4.0 BETA\nCopyright, Gerben (www.gerbenvv.nl)\n\n";
        }
        
        /* show message */
        cout << exception->message << "\n";
        
        /* delete classes */
        if (settings != NULL) {
            delete settings;
        }
        
        if (formatter != NULL) {
            delete formatter;
        }
        
        if (scanner != NULL) {
            delete scanner;
        }
        
        if (parser != NULL) {
            delete parser;
        }

        return 1;
    }
    
    /* show version and copyright */
    if (!settings->quiet) {
        cout << "PHPFormatter version 3.0 BETA\nCopyright, Gerben (www.gerbenvv.nl)\n\n";
    }
    
    /* delete classes */
    delete settings;
    delete formatter;
    delete scanner;
    delete parser;
    
    return 0;
}
