
#ifndef ASTYLE_INTERFACE_H
#define ASTYLE_INTERFACE_H

#ifdef _DEBUG
	#pragma comment(lib, "AStyleLibd.lib")
#else
	#pragma comment(lib, "AStyleLib.lib")
#endif // _DEBUG


// allow for different calling conventions in Linux and Windows
#ifdef _WIN32
#define STDCALL __stdcall
#else
#define STDCALL
#endif

// external functions calls in Artistic Style shared or static library
extern "C"
{   char* STDCALL  AStyleGetVersion();
    char* STDCALL  AStyleMain(const char* textIn,
                              const char* options,
                              void(STDCALL* errorHandler)(int, const char*),
                              char*(STDCALL* memoryAlloc)(unsigned long));
}

/**
 * The AStyleInterface class contains the variables and methods to call the
 * Artistic Style shared library to format a source file.
 */

class AStyleInterface
{
public:
    AStyleInterface();
    char* formatSource(const char* textIn, const char* options);

private:
    static void  displayErrorMessage(LPCTSTR errorMessage);
    // callback functions for Artistic Style
    static void  STDCALL errorHandler(int errorNumber, const char* errorMessage);
    static char* STDCALL memoryAlloc(unsigned long memoryNeeded);

};  // class AStyleInterface

#endif      // closes ASTYLE_INTERFACE_H
