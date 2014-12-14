/**
* @file MyBCGPProp.h
* @brief 扩展CMyBCGPProp实现存储更多信息
* @author 无幻
* @date 2014-12-11
* @details
*/
#pragma once

//////////////////////////////////////////////////////////////////////////
// CMyBCGPProp

class CMyBCGPProp : public CBCGPProp
{
	DECLARE_DYNAMIC(CMyBCGPProp)

	friend class CMyBCGPPropList;

public:
	// Group constructor
	CMyBCGPProp(const CString& strGroupName, DWORD_PTR dwData = 0,
		BOOL bIsValueList = FALSE);

	CMyBCGPProp(const CString& strName, const _variant_t& varValue,
		LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL,
		LPCTSTR lpszValidChars = NULL);
	virtual ~CMyBCGPProp();

	/**
	 * 增加下拉项
	 * @param LPCTSTR lpszOption 下拉项
	 * @param LPCTSTR lpszShort 缩写词
	 * @param LPCTSTR lpszPreview 预览文本
	 * @param BOOL bInsertUnique 是否唯一
	 * @return BOOL 
	 */
	BOOL AddComboOption(LPCTSTR lpszOption, LPCTSTR lpszShort, LPCTSTR lpszPreview, BOOL bInsertUnique = TRUE);

	/**
	 * 增加数字项
	 * @param int nMin 最小值
	 * @param int nMax 最大值
	 * @param LPCTSTR lpszShort 缩写词
	 * @param LPCTSTR lpszPreview 预览文本
	 * @param CMyBCGPProp* pBuddyToProp 绑定到关联的属性
	 * @return BOOL 
	 */
	BOOL SetNumberSpin(int nMin, int nMax, LPCTSTR lpszShort, LPCTSTR lpszPreview, CMyBCGPProp* pBuddyToProp = NULL);

	/**
	 * 增加编辑文本项
	 * @param LPCTSTR lpszShort 缩写词
	 * @param LPCTSTR lpszPreview 预览文本
	 * @return BOOL 
	 */
	BOOL SetEditText(LPCTSTR lpszShort, LPCTSTR lpszPreview);

	/**
	 * 获得选中项的预览文本
	 * @return LPCTSTR 
	 */
	LPCTSTR GetSelectedPreviewOption() const;

	/**
	 * 根据缩写词来查找项
	 * @param LPCTSTR lpszShort 缩写词
	 * @return CBCGPProp* 项指针
	 */
	CBCGPProp* FindSubItemByShort(LPCTSTR lpszShort) const;

	/**
	 * 是否存在缩写词
	 * @param LPCTSTR lpszShort 缩写词
	 * @return BOOL 
	 */
	BOOL IsExistShort(LPCTSTR lpszShort);

	/**
	 * 设置值
	 * @param LPCTSTR lpszShort 缩写词
	 * @param const _variant_t & varValue
	 * @return void 
	 */
	void SetValueByShort(LPCTSTR lpszShort, const _variant_t& varValue);

	/**
	 * 获取子项的所有缩写词结果
	 * @param CString & strValue 
	 * @return void 
	 */
	void GetSubResultShorts(CString& strValue);

	/**
	 * 获取缩写词结果
	 * @param CString & strValue
	 * @return void 
	 */
	void GetResultShort(CString& strValue);

	/**
	 * 是否是列表
	 * @return BOOL 
	 */
	BOOL IsList() const;

	/**
	* 是否是文本
	* @return BOOL
	*/
	BOOL IsText() const;

	void GetSubShortOptions(CStringList& lstValue);

	void GetShortOptions(CStringList& lstValue);

protected:
	CStringList	m_lstShortOptions;	// 缩写文本
	CStringList	m_lstPreviewOptions;	// 预览文本
	CMyBCGPProp* m_pBuddyProp;	// 绑定的属性，一般用作编辑框绑定

	/**
	 * 重载以实现数字限定范围
	 * @param const CString & strText 文本内容
	 * @return BOOL 
	 */
	virtual BOOL TextToVar(const CString& strText);
};


