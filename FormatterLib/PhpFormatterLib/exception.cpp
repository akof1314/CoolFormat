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

#include "exception.h"

/* constructor */
CException::CException(EError type, string msg) {
    /* show type */
    switch (type) {
        case E_MEMORY:
            message = "Memory allocation failure: ";
            break;
            
        case E_SOURCE:
            message = "Source error: ";
            break;
            
        case E_SETTINGS:
            message = "Settings error: ";
            break;
            
        default:
            message = "Internal error: ";
            break;
    }
    
    /* show message */
    message += msg;
}

/* constructor */
CException::CException(EError type) {
    /* show type */
    switch (type) {
        case E_MEMORY:
            message = "Memory allocation failure!";
            break;
            
        case E_SOURCE:
            message = "Source error!";
            break;
            
        case E_SETTINGS:
            message = "Settings error!";
            break;
            
        default:
            message = "Internal error!";
            break;
    }
}
