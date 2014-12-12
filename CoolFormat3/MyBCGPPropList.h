/**
* @file MyBCGPPropList.h
* @brief 扩展CBCGPPropList实现选项改变事件
* @author 无幻
* @date 2014-12-11
* @details
*/
#pragma once

//////////////////////////////////////////////////////////////////////////
// CMyBCGPPropList

class CMyBCGPPropList : public CBCGPPropList
{
	DECLARE_DYNAMIC(CMyBCGPPropList)

public:
	virtual ~CMyBCGPPropList();

	/**
	 * 设置预览文本控件指针
	 * @param CWnd * pWnd
	 * @return void 
	 */
	void SetPreviewWnd(CWnd* pWnd);

	/**
	 * 查找指定的缩写词
	 * @param LPCTSTR lpszShort
	 * @param BOOL bSearchSubItems
	 * @return CBCGPProp* 
	 */
	CBCGPProp* FindItemByShort(LPCTSTR lpszShort, BOOL bSearchSubItems = TRUE) const;

	/**
	 * 得到最终的缩写词组成
	 * @param CString & strValue
	 * @return void 
	 */
	void GetResultShorts(CString& strValue);

	/**
	 * 验证是否存在相同缩写词
	 * @return BOOL 不通过的话，返回FALSE
	 */
	BOOL ValidateShort();

protected:
	DECLARE_MESSAGE_MAP()

	void Init();
	void OnChangeSelection(CBCGPProp* /*pNewSel*/, CBCGPProp* /*pOldSel*/);
	void OnPropertyChanged(CBCGPProp* pProp) const;

	void PreviewSelProperty(CBCGPProp* pProp, BOOL bCheck = FALSE) const;

protected:
	CWnd* m_pWndPreview;
};


