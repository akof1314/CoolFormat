// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 COOLFORMATLIB_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// COOLFORMATLIB_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#include <string>

HMODULE hCFModule;

#ifdef COOLFORMATLIB_EXPORTS
#define COOLFORMATLIB_API __declspec(dllexport)
#else
#define COOLFORMATLIB_API __declspec(dllimport)
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