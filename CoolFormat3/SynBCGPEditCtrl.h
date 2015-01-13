#pragma once
#include "SynLanguage.h"
#include "XmlOutlineParser.h"
#include "KofFile.h"

static const DWORD g_dwUATComment		= 0x80000;
static const DWORD g_dwUATUncomment		= 0x100000;
static const DWORD g_dwUATFormatter		= 0x200000;

class CSynBCGPEditCtrl : public CBCGPEditCtrl
{
	DECLARE_DYNAMIC(CSynBCGPEditCtrl)
public:
	CSynBCGPEditCtrl();
	virtual ~CSynBCGPEditCtrl();

	void UseXmlParser (BOOL bXmlParser = TRUE)
	{
		((CXmlOutlineParser*)m_pOutlineParser)->EnableXmlParser (bXmlParser);
	}
	virtual CBCGPOutlineParser* CreateOutlineParser () const
	{
		return new CXmlOutlineParser;
	}

public:
	BOOL m_bCheckColorTags;	// TRUE if check for tags (<....>) in "OnGetCharColor"
	
	/**
	 * 选定语言
	 * @param UINT nLanguage 语言ID
	 * @return void 
	 */
	void SelectLanguage(UINT nLanguage);
	
	/**
	 * 根据后缀名选定语言
	 * @param CString strExt 后缀名
	 */
	void SelectLanguageByExt(CString strExt);
	
	/**
	 * 获取语言描述字符串
	 * @return LPCTSTR 
	 */
	LPCTSTR GetSelectLangString();

	/**
	* 设置代码页
	* @param UINT nCodepage 代码页
	*/
	void SelectEncoding(UINT nCodepage);

	/**
	* 获取代码页描述字符串
	* @return LPCTSTR
	*/
	LPCTSTR GetSelectEncodingString();

	COLORREF m_clrSyn;		//语法颜色
	COLORREF m_clrType;		//类型颜色
	COLORREF m_clrNumber;	//数字颜色
	COLORREF m_clrString;	//字符串颜色
	COLORREF m_clrChar;		//字符颜色
	COLORREF m_clrComment;	//注释颜色

	
	/**
	 * 加载编辑器颜色方案
	 * @param BOOL bRedraw 是否重绘
	 * @return void 
	 */
	void LoadColor(BOOL bRedraw = FALSE);
	
	/**
	 * 打开文件
	 * @param const CString & strFileName 文件名
	 * @return BOOL 是否成功
	 */
	BOOL OpenFileEx(const CString& strFileName);
	
	/**
	 * 保存文件
	 * @param const CString & strFileName 文件名
	 * @return BOOL 是否成功
	 */
	BOOL SaveFileEx(const CString& strFileName);
	
	/**
	 * 扩展导出到HTML
	 * @param CString & strBuffer HTML字符串缓冲区
	 * @return void 
	 */
	void ExportToMyHTML(CString& strBuffer);	
	
	/**
	 * 插入（取消）注释
	 * @param BOOL bForward 插入还是取消
	 * @return void 
	 */
	void InsertComment(BOOL bForward);
	
	/**
	 * 替换内容为格式化内容
	 * @param BOOL bAllText 是否全部文本格式化
	 * @return void 
	 */
	void ReplaceTextToFormatter(BOOL bAllText = TRUE);

protected:
	CSynLanguage m_SynLanguage;
	BOOL m_bNumberColor;
	BOOL m_bFirstShow;
	CKofFile m_File;
	void OnGetCharColor (TCHAR ch, int nOffset, COLORREF& clrText, COLORREF& clrBk);
	BOOL OnGetWordColor (const CString& strWord, COLORREF& clrText, COLORREF& clrBk, int nPos);	
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSysColorChange();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};