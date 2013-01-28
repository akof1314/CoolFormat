#include "stdafx.h"
#include "AStyleInterface.h"

/*
* The constructor sets the variable default values.
**/
AStyleInterface::AStyleInterface()
{  
}

/**
* Display error messages for the class.
* This method should be changed to display messages in a manner consistent
* with the rest of the user program (e.g. a message box).
*
* @param  errorMessage   The error message to be displayed.
*/
void AStyleInterface::displayErrorMessage(LPCTSTR errorMessage)
{  
	OutputDebugString(errorMessage);
	TRACE(_T("\r"));
}

// functions to call Artistic Style ---------------------------------------------------------------

/**
* Call the AStyleMain function in Artistic Style.
*
* @param   textIn  A pointer to the source code to be formatted.
* @return  A pointer to the formatted source from Artistic Style.
*/
char* AStyleInterface::formatSource(const char* textIn, const char* options)
{  
    char* textOut = AStyleMain(textIn,
                               options,
                               errorHandler,
                               memoryAlloc);
    return textOut;
}

/**
* Static method to handle error messages from messages from Artistic Style.
* This method is called only if there are errors when AStyleMain is called.
* This is for debugging and there should be no errors when the calling
* parameters are correct.
*
* @param  errorNumber   The error number from Artistic Style.
* @param  errorMessage  The error message from Artistic Style.
*/
void STDCALL AStyleInterface::errorHandler(int errorNumber, const char* errorMessage)
{ 
	CString strMsg;
	strMsg.Format(_T("astyle error %d\n%s"), errorNumber, errorMessage);
}

/**
* Allocate memory for the Artistic Style formatter.
* This method is called when Artistic Style needs to allocate memory.
* for the formatted file.
* The calling program is responsible for freeing the memory.
*
* @param  memoryNeeded  The amount of memory needed by Artistic Style.
*/
char* STDCALL AStyleInterface::memoryAlloc(unsigned long memoryNeeded)
{   // error condition should be checked by calling procedure
	char* buffer = new(std::nothrow) char [memoryNeeded];
    return buffer;
}
