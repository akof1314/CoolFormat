/** 
 * @file KofFile.h
 * @brief 打开及保存文件
 * @author 无幻 
 * @date 2012-4-3
 * @details 打开及保存ANSI、UTF-8、UTF-8NoBom、UTF-16BE、UTF-16LE和Windows、UNIX、Mac不同换行符下的文本文件
 */ 
#pragma once

/** 文档格式类型 */
enum FileFormatType{
	WIN_FORMAT,		/**< Windows格式文档 */
	UNIX_FORMAT,
	MAC_FORMAT
};

/** 文档编码类型 */
enum FileEncodeType{
	ANSI_ENCODE = 0,	/**< ANSI编码 */
	UTF8_ENCODE,
	UTF8NB_ENCODE,
	UTF16BE_ENCODE,
	UTF16LE_ENCODE,
	END_ENCODE
};

/** 最大错误信息长度 */
const UINT MAX_ERROR_MSG = 1024;

class CKofFile
{
public:
	CKofFile(void);
	~CKofFile(void);

	/**
	 * 打开指定文件名文件，保存内容到字符串变量
	 * @param LPCTSTR lpszFileName 文件名
	 * @param CString & strFileText 字符串变量
	 * @return BOOL 是否打开成功
	 */
	BOOL OpenFile(LPCTSTR lpszFileName, CString &strFileText);

	/**
	 * 保存指定内容到指定的文件名文件
	 * @param LPCTSTR lpszFileName 文件名 
	 * @param LPCTSTR lpszFileText 字符串内容
	 * @return BOOL 是否保存成功
	 */
	BOOL SaveFile(LPCTSTR lpszFileName, LPCTSTR lpszFileText);
	
	/**
	 * 获取最后的错误信息
	 * @return LPCTSTR 返回错误信息指针
	 */
	LPCTSTR GetLastErrorMsg(){return m_szErrorMsg;} 

	
	/**
	 * 获取当前打开的文件文档格式类型
	 * @return FileFormatType 返回文件文档格式类型
	 */
	FileFormatType GetFileFormatType(){return m_FormatType;}
	
	/**
	 * 获取当前打开的文件文档编码类型
	 * @return FileEncodeType 返回文件文档编码类型
	 */
	FileEncodeType GetFileEncodeType(){return m_EncodeType;}

protected:
	void DetermineEncodeType(LPSTR lpszFileBuf, DWORD dwFileSize);
	void DetermineFormatType(LPSTR lpszFileBuf, DWORD dwFileSize);
	void ConvertEncodeToTChar(LPSTR lpszFileBuf, DWORD dwFileSize, CString &strFileText);
	void ConvertFormatToTChar(CString &strFileText);
	void ProcessTCharFormat(LPSTR lpszFileText, DWORD &dwFileSize);
	void SaveFileText(CFile &file, LPSTR lpszFileBuf, DWORD dwFileSize);
	void BigEndianSwapLittleEndian(LPSTR lpszFileBuf, DWORD dwFileSize);
	BOOL IsTextUtf8(LPCSTR lpszFileBuf, DWORD dwFileSize);
	void SetLastErrorMsg(LPCTSTR lpszErrorMsg){lstrcpy(m_szErrorMsg, lpszErrorMsg);}

private:
	FileFormatType m_FormatType;
	FileEncodeType m_EncodeType;
	TCHAR m_szErrorMsg[MAX_ERROR_MSG];
	UINT m_nSkip;
	static const UCHAR m_EncodeBoms[END_ENCODE][3];
};
