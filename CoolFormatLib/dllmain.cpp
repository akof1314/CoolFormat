// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#ifdef _WIN32
#else
#include <dlfcn.h>
#endif

#ifdef _WIN32
extern HMODULE hCFModule;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID /*lpReserved*/
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		hCFModule = hModule;
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
    //fprintf(stderr, "module %s loaded\n", dl_info.dli_fname);
}
#endif
