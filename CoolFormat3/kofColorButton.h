/** 
 * @file kofColorButton.h
 * @brief 实现颜色按钮
 * @author 无幻 
 * @date 2012-5-26
 * @details 
 */ 
#pragma once

//////////////////////////////////////////////////////////////////////////
// CkofColorButton

class CkofColorButton : public CButton
{
	DECLARE_DYNAMIC(CkofColorButton)
public:
	CkofColorButton(COLORREF color = RGB(0, 0, 0));
	virtual ~CkofColorButton();

	COLORREF GetColor () const
	{
		return m_Color;
	}
	void SetColor (COLORREF color);

protected:
	COLORREF m_Color;
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


