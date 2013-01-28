#include "StdAfx.h"
#include "CoolFormat3.h"
#include "KofFile.h"

const UCHAR CKofFile::m_EncodeBoms[][3] = {
	{0x00, 0x00, 0x00},  /**< Unknown */
	{0xEF, 0xBB, 0xBF},  /**< UTF8 */
	{0x00, 0x00, 0x00},  /**< Unknown */
	{0xFE, 0xFF, 0x00},  /**< Big endian */
	{0xFF, 0xFE, 0x00},  /**< Little endian */
};

const int CR = 0x0D;
const int LF = 0x0A;
const TCHAR WIN_EOL[] = _T("\r\n");
const TCHAR UNIX_EOL[] = _T("\n");
const TCHAR MAC_EOL[] = _T("\r");

CKofFile::CKofFile(void)
{
	m_FormatType = WIN_FORMAT;
	m_EncodeType = ANSI_ENCODE;
	m_nSkip = 0;
	ZeroMemory(m_szErrorMsg, MAX_ERROR_MSG);
}

CKofFile::~CKofFile(void)
{
}

BOOL CKofFile::OpenFile( LPCTSTR lpszFileName, CString &strFileText )
{
	if (0 == _tcsclen(lpszFileName))
	{
		CString strTemp;
		BOOL bNameVaild = strTemp.LoadString(IDS_STRING_NEEDFILE);
		ASSERT(bNameVaild);
		SetLastErrorMsg(strTemp);
		return FALSE;
	}

	CWaitCursor wait;
	CFile file;
	CFileException fileException;
	if (!file.Open(lpszFileName, CFile::modeRead, &fileException))
	{
		fileException.GetErrorMessage(m_szErrorMsg, MAX_ERROR_MSG, NULL);
		return FALSE;
	}
	try
	{
		const DWORD dwFileSize = (const DWORD)file.GetLength();
		if (dwFileSize == 0)
		{
			strFileText = _T("");
			return TRUE;
		}

		LPSTR pszFileBuffer = new char[dwFileSize + 2];
		ZeroMemory(pszFileBuffer, dwFileSize + 2);
		
#if _MSC_VER >= 1300
		file.Read(pszFileBuffer, dwFileSize);
#else
		file.ReadHuge(pszFileBuffer, dwFileSize);
#endif
		file.Close();

		DetermineEncodeType(pszFileBuffer, dwFileSize);
		LPSTR pszNewFileBuffer = pszFileBuffer + m_nSkip;
		DWORD dwNewFileSize = dwFileSize - m_nSkip;
		DetermineFormatType(pszNewFileBuffer, dwNewFileSize);
		ConvertEncodeToTChar(pszNewFileBuffer, dwNewFileSize, strFileText);
		ConvertFormatToTChar(strFileText);
		delete[] pszFileBuffer;
	}
	catch (CException* e)
	{
		e->GetErrorMessage(m_szErrorMsg, MAX_ERROR_MSG, NULL);
		e->Delete();
		return FALSE;
	}
	SetLastErrorMsg(_T(""));
	return TRUE;
}

BOOL CKofFile::SaveFile( LPCTSTR lpszFileName, LPCTSTR lpszFileText )
{
	if (0 == _tcsclen(lpszFileName))
	{
		CString strTemp;
		BOOL bNameVaild = strTemp.LoadString(IDS_STRING_NEEDFILE);
		ASSERT(bNameVaild);
		SetLastErrorMsg(strTemp);
		return FALSE;
	}

	CWaitCursor wait;
	CFile file;
	CFileException fileException;
	if (!file.Open(lpszFileName, CFile::modeWrite | CFile::modeCreate, &fileException))
	{
		fileException.GetErrorMessage(m_szErrorMsg, MAX_ERROR_MSG, NULL);
		return FALSE;
	}
	try
	{
		switch (m_EncodeType)
		{
		case ANSI_ENCODE:
			{
				CT2A lpszNewFileText(lpszFileText);
				SaveFileText(file, lpszNewFileText, strlen(lpszNewFileText));
			}
			break;
		case UTF8_ENCODE:
			file.Write(m_EncodeBoms[UTF8_ENCODE], 3);
		case UTF8NB_ENCODE:
			{
				CW2A lpszNewFileText(CT2W(lpszFileText), CP_UTF8);
				SaveFileText(file, lpszNewFileText, strlen(lpszNewFileText));
			}
			break;
		case UTF16BE_ENCODE:
			{
				file.Write(m_EncodeBoms[UTF16BE_ENCODE], 2);
				CT2W lpszNewFileTextW(lpszFileText);
				LPSTR lpszNewFileText = (LPSTR)(LPWSTR)lpszNewFileTextW;
				DWORD dwFileSize = wcslen(lpszNewFileTextW) * 2;
				BigEndianSwapLittleEndian(lpszNewFileText, dwFileSize);
				SaveFileText(file, lpszNewFileText, dwFileSize);
			}
			break;
		case UTF16LE_ENCODE:
			{
				file.Write(m_EncodeBoms[UTF16LE_ENCODE], 2);
				CT2W lpszNewFileTextW(lpszFileText);
				LPSTR lpszNewFileText = (LPSTR)(LPWSTR)lpszNewFileTextW;
				SaveFileText(file, lpszNewFileText, wcslen(lpszNewFileTextW) * 2);
			}
			break;
		}
	}
	catch (CException* e)
	{
		e->GetErrorMessage(m_szErrorMsg, MAX_ERROR_MSG, NULL);
		e->Delete();
		return FALSE;
	}
	SetLastErrorMsg(_T(""));
	return TRUE;
}

void CKofFile::DetermineEncodeType( LPSTR lpszFileBuf, DWORD dwFileSize )
{
	UCHAR *pBuf = (UCHAR *)lpszFileBuf;
	if (dwFileSize > 1 && pBuf[0] == m_EncodeBoms[UTF16BE_ENCODE][0] && pBuf[1] == m_EncodeBoms[UTF16BE_ENCODE][1])
	{
		m_EncodeType = UTF16BE_ENCODE;
		m_nSkip = 2;
	}
	else if (dwFileSize > 1 && pBuf[0] == m_EncodeBoms[UTF16LE_ENCODE][0] && pBuf[1] == m_EncodeBoms[UTF16LE_ENCODE][1] )
	{
		m_EncodeType = UTF16LE_ENCODE;
		m_nSkip = 2;
	}
	else if (dwFileSize > 2 && pBuf[0] == m_EncodeBoms[UTF8_ENCODE][0] && pBuf[1] == m_EncodeBoms[UTF8_ENCODE][1] && pBuf[2] == m_EncodeBoms[UTF8_ENCODE][2] )
	{
		m_EncodeType = UTF8_ENCODE;
		m_nSkip = 3;
	}
	else 
	{
		if (IsTextUtf8(lpszFileBuf, dwFileSize))
		{
			m_EncodeType = UTF8NB_ENCODE;
		}
		else
		{
			m_EncodeType = ANSI_ENCODE;
		}
		m_nSkip = 0;
	}
}

BOOL CKofFile::IsTextUtf8( LPCSTR lpszFileBuf, DWORD dwFileSize )
{
/*
 * UTF-8 编码规则
 * 0xxxxxxx
 * 110xxxxx 10xxxxxx
 * 1110xxxx 10xxxxxx 10xxxxxx
 * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 */
	DWORD i;
	DWORD cOctets;  // 可以容纳UTF-8编码字符的字节大小
	UCHAR chr;
	BOOL bAllAscii = TRUE;	//如果全部为ASCII，说明不是UTF-8

	cOctets = 0;
	for( i = 0; i < dwFileSize; i++ )
	{
		chr = *(lpszFileBuf + i);
		if( (chr & 0x80) != 0 ) bAllAscii = FALSE;	//ASCII用7位储存，最高位为0，如果这里相与非0，就不是ASCII

		if( cOctets == 0 )
		{
			// 7 bit ascii after 7 bit ascii is just fine.  Handle start of encoding case.开始进行编码处理
			if( chr >= 0x80 )
			{
				// count of the leading 1 bits is the number of characters encoded
				do
				{
					chr <<= 1;
					cOctets++;
				}
				while( (chr & 0x80) != 0 );

				cOctets--;                        // count includes this character
				if( cOctets == 0 ) return FALSE;  // must start with 11xxxxxx
			}
		}
		else
		{
			// non-leading bytes must start as 10xxxxxx
			if( (chr & 0xC0) != 0x80 )
			{
				return FALSE;
			}
			cOctets--;                           // processed another octet in encoding
		}
	}

	// 文本末尾，检查一致性
	if( cOctets > 0 )     // 在最后还有遗留的话是错误的
	{
		return FALSE;
	}
	if( bAllAscii )       // Not utf-8 if all ascii.  调用者强制使用代码页转换
	{
		return FALSE;
	}
	return TRUE;
}

void CKofFile::ConvertEncodeToTChar( LPSTR lpszFileBuf, DWORD dwFileSize, CString &strFileText )
{
	switch (m_EncodeType)
	{
	case ANSI_ENCODE:
		strFileText = CA2T(lpszFileBuf);
		break;
	case UTF8_ENCODE:
	case UTF8NB_ENCODE:
		strFileText = CW2T(CA2W(lpszFileBuf, CP_UTF8));
		break;
	case UTF16BE_ENCODE:
		BigEndianSwapLittleEndian(lpszFileBuf, dwFileSize);
	case UTF16LE_ENCODE:
		strFileText = (CW2T((LPWSTR)lpszFileBuf));
		break;
	}
}

void CKofFile::BigEndianSwapLittleEndian( LPSTR lpszFileBuf, DWORD dwFileSize )
{
	USHORT *pBuf = (USHORT*)lpszFileBuf;
	for (DWORD i = 0; i < dwFileSize; i += 2, pBuf += 1)
	{
		*pBuf = (*pBuf >> 8) | (*pBuf << 8);
	}
}

void CKofFile::DetermineFormatType( LPSTR lpszFileBuf, DWORD dwFileSize )
{
	m_FormatType = WIN_FORMAT;
	DWORD dwSkip = (m_EncodeType == UTF16BE_ENCODE) || (m_EncodeType == UTF16LE_ENCODE)?2:1;
	for (DWORD i = 0 ; i < dwFileSize ; i++)
	{
		if (lpszFileBuf[i] == CR)
		{
			if (i + dwSkip < dwFileSize &&  lpszFileBuf[i + dwSkip] == LF)
			{
				m_FormatType = WIN_FORMAT;
			}
			else
			{
				m_FormatType = MAC_FORMAT;
			}
			break;
		}
		if (lpszFileBuf[i] == LF)
		{
			m_FormatType = UNIX_FORMAT;
			break;
		}
	}
}

void CKofFile::ConvertFormatToTChar( CString &strFileText )
{
	switch (m_FormatType)
	{
	case WIN_FORMAT://不做任何转换
		break;
	case UNIX_FORMAT:
		strFileText.Replace(UNIX_EOL, WIN_EOL);
		break;
	case MAC_FORMAT:
		strFileText.Replace(MAC_EOL, WIN_EOL);
		break;
	}
}

void CKofFile::ProcessTCharFormat( LPSTR lpszFileText, DWORD &dwFileSize )
{
	int nEol = 0;
	DWORD dwSkip = (m_EncodeType == UTF16BE_ENCODE) || (m_EncodeType == UTF16LE_ENCODE)?2:1;
	switch (m_FormatType)
	{
	case WIN_FORMAT:
		return;
	case UNIX_FORMAT:
		nEol = LF;
		break;
	case MAC_FORMAT:
		nEol = CR;
		break;
	default:
		return;
	}

	LPSTR lpszText = lpszFileText;
	DWORD dwNewFileSize = dwFileSize;
	for (DWORD i = 0; i < dwFileSize; lpszFileText++, i++ )
	{
		if (*lpszFileText == CR)
		{
			if (i + dwSkip < dwFileSize && *(lpszFileText + dwSkip) == LF )
			{
				*lpszText = (UCHAR)nEol;
				i += dwSkip;
				lpszFileText += dwSkip;
				dwNewFileSize -= dwSkip;
			}
			else
			{
				*lpszText = *lpszFileText;
			}
		}
		else
		{
			*lpszText = *lpszFileText;
		}
		lpszText++;
	}
	*lpszText = '\0';
	dwFileSize = dwNewFileSize;
}

void CKofFile::SaveFileText( CFile &file, LPSTR lpszFileBuf, DWORD dwFileSize )
{
	DWORD dwNewFileSize = dwFileSize;
	ProcessTCharFormat(lpszFileBuf, dwNewFileSize);
	file.Write(lpszFileBuf, dwNewFileSize);
	file.Flush();
	file.Close();
}