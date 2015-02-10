#include "stdafx.h"
#include <string>

#ifndef _WIN32
#include <dlfcn.h>
#endif

extern std::string g_strDllFilePath;

#ifdef _WIN32
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID /*lpReserved*/
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		char szBuff[MAX_PATH];
		GetModuleFileNameA(hModule, szBuff, sizeof(szBuff));
		g_strDllFilePath = szBuff;
	}
							 
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#else
__attribute__((constructor))
void on_load(void) {
	Dl_info dl_info;
    dladdr((void *)on_load, &dl_info);
	g_strDllFilePath = dl_info.dli_fname;
}
#endif
