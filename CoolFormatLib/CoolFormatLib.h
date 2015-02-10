#include <string>

#ifdef _WIN32
	#ifdef COOLFORMATLIB_EXPORTS
		#define COOLFORMATLIB_API __declspec(dllexport)
	#else
		#define COOLFORMATLIB_API __declspec(dllimport)
	#endif
#else
	#define COOLFORMATLIB_API
#endif

#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif

COOLFORMATLIB_API bool DoFormatter(unsigned int nLanguage,
	const char *pszTextIn,
	char *pszTextOut,
	int &nTextOut,
	char *pszMsgOut,
	int &nMsgOut,
	unsigned int uCodepage = 0,
	const char *pszEol = NULL,
	const char *pszInitIndent = NULL);

COOLFORMATLIB_API void ShowSettings();

#ifdef __cplusplus
}
#endif