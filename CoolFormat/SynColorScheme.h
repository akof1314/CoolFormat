/** 
 * @file SynColorScheme.h
 * @brief 编辑器配色方案
 * @author 无幻 
 * @date 2012-5-26
 * @details 
 */ 
#pragma once

class CSynColorScheme
{
public:
	CSynColorScheme(void);
	~CSynColorScheme(void);
	
	/**
	 * 初始化配色方案
	 * @param void 
	 * @return void 
	 */
	void InitColorScheme(void);

	COLORREF m_clrBack;	//背景色
	COLORREF m_clrText; //正常色

	COLORREF m_clrBackSelActive;	//选定的背景色
	COLORREF m_clrBackSelInActive;	//非活动的选定背景色
	COLORREF m_clrTextSelActive;	//选定的文本色
	COLORREF m_clrTextSelInActive;	//非活动的选定文本色

	COLORREF m_clrBackOutline;	//折叠块背景色
	COLORREF m_clrLineOutline;	//折叠块线色

	COLORREF m_clrBackLineNumber;	//行号背景色
	COLORREF m_clrTextLineNumber;	//行号色
	COLORREF m_clrBackSidebar;		//分隔线色
	COLORREF m_clrHyperlink;		//超链接色

	COLORREF m_clrSyn;		//语法颜色
	COLORREF m_clrType;		//类型颜色
	COLORREF m_clrNumber;	//数字颜色
	COLORREF m_clrString;	//字符串颜色
	COLORREF m_clrChar;		//字符颜色
	COLORREF m_clrComment;	//注释颜色

	COLORREF m_DefclrBackSelActive;		//默认选定的背景色
	COLORREF m_DefclrBackSelInActive;	//默认非活动的选定背景色
	COLORREF m_DefclrTextSelActive;		//默认选定的文本色
	COLORREF m_DefclrTextSelInActive;	//默认非活动的选定文本色
};
