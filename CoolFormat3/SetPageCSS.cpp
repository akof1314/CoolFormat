// SetPageCSS.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageCSS.h"


// CSetPageCSS 对话框

IMPLEMENT_DYNCREATE(CSetPageCSS, CBCGPPropertyPage)

CSetPageCSS::CSetPageCSS()
	: CBCGPPropertyPage(CSetPageCSS::IDD)
{

}

CSetPageCSS::~CSetPageCSS()
{
}

void CSetPageCSS::DoDataExchange(CDataExchange* pDX)
{
	CBCGPPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetPageCSS, CBCGPPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO_CSS_COMPRESSION, &CSetPageCSS::OnCbnSelchangeComboCssCompression)
	ON_EN_SETFOCUS(IDC_EDIT_CSS_TEMPLATE, &CSetPageCSS::OnEnSetfocusEditCssTemplate)
	ON_BN_CLICKED(IDC_CHECK_CSS_PRESERVE, &CSetPageCSS::OnBnClickedCheckCssPreserve)
	ON_BN_CLICKED(IDC_CHECK_CSS_SELECTORS, &CSetPageCSS::OnBnClickedCheckCssSelectors)
	ON_BN_CLICKED(IDC_CHECK_CSS_PROPERTIES, &CSetPageCSS::OnBnClickedCheckCssProperties)
	ON_BN_CLICKED(IDC_CHECK_CSS_REMOVELAST, &CSetPageCSS::OnBnClickedCheckCssRemovelast)
	ON_BN_CLICKED(IDC_CHECK_CSS_REMOVESLASH, &CSetPageCSS::OnBnClickedCheckCssRemoveslash)
	ON_BN_CLICKED(IDC_CHECK_CSS_DISCARD, &CSetPageCSS::OnBnClickedCheckCssDiscard)
	ON_BN_CLICKED(IDC_CHECK_CSS_SILENT, &CSetPageCSS::OnBnClickedCheckCssSilent)
	ON_BN_CLICKED(IDC_CHECK_CSS_COLORS, &CSetPageCSS::OnBnClickedCheckCssColors)
	ON_BN_CLICKED(IDC_CHECK_CSS_FONTWEIGHT, &CSetPageCSS::OnBnClickedCheckCssFontweight)
	ON_BN_CLICKED(IDC_CHECK_CSS_LOWERCASE, &CSetPageCSS::OnBnClickedCheckCssLowercase)
	ON_BN_CLICKED(IDC_CHECK_CSS_TIMESTAMP, &CSetPageCSS::OnBnClickedCheckCssTimestamp)
	ON_CBN_SELCHANGE(IDC_COMBO_CSS_CASE, &CSetPageCSS::OnCbnSelchangeComboCssCase)
	ON_CBN_SELCHANGE(IDC_COMBO_CSS_OPTIMISE, &CSetPageCSS::OnCbnSelchangeComboCssOptimise)
	ON_CBN_SELCHANGE(IDC_COMBO_CSS_REGROUP, &CSetPageCSS::OnCbnSelchangeComboCssRegroup)
END_MESSAGE_MAP()


// CSetPageCSS 消息处理程序

BOOL CSetPageCSS::OnInitDialog()
{
	CBCGPPropertyPage::OnInitDialog();
	CString strTemp;
	BOOL bNameVaild = strTemp.LoadString(IDS_STR_VIEWFORMATTER);
	ASSERT(bNameVaild);
	SetDlgItemText(IDC_STATIC_VIEWFORMATTER, strTemp);
	GetDlgItem(IDC_EDIT_VIEWFORMATTER)->SetFont(&g_GlobalUtils.m_fontWidth);

	InitLimit();
	SetTidyConfig(g_GlobalTidy.m_TidyCss);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSetPageCSS::InitLimit()
{
	((CComboBox *)GetDlgItem(IDC_COMBO_CSS_COMPRESSION))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_COMBO_CSS_DISCARD))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_COMBO_CSS_CASE))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_COMBO_CSS_OPTIMISE))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_COMBO_CSS_REGROUP))->SetCurSel(0);
}

void CSetPageCSS::SetViewEdit( LPCTSTR lpszText )
{
	SetDlgItemText(IDC_EDIT_VIEWFORMATTER, lpszText);
}

void CSetPageCSS::OnCbnSelchangeComboCssCompression()
{
	CString strText;
	switch (((CComboBox *)GetDlgItem(IDC_COMBO_CSS_COMPRESSION))->GetCurSel())
	{
	case 0:strText = _T("h1{color:red;}h2{color:black;}");
		break;
	case 1:strText = _T("h1{color:red;}")
			   _T("\r\nh2{color:black;}");
		break;
	case 2:strText = _T("h1 {")
			   _T("\r\ncolor:red;")
			   _T("\r\n}")
			   _T("\r\n")
			   _T("\r\nh2 {")
			   _T("\r\ncolor:black;")
			   _T("\r\n}");
		break;
	case 3:strText = _T("h1")
			   _T("\r\n{")
			   _T("\r\n	color:red;")
			   _T("\r\n}")
			   _T("\r\n")
			   _T("\r\nh2")
			   _T("\r\n{")
			   _T("\r\n	color:black;")
			   _T("\r\n}");
		break;
	case 4:strText = _T("Use custom template");
		break;
	}
	SetViewEdit(strText);
}

void CSetPageCSS::OnEnSetfocusEditCssTemplate()
{
	CString strText;
	/*strText = _T("Example:\r\n\r\n<span class=\"at\">|</span> <span class=\"format\">{</span>")
		_T("\r\n|<span class=\"selector\">|</span> <span class=\"format\">{</span>")
		_T("\r\n|<span class=\"property\">|</span><span class=\"value\">|</span><span class=\"format\">;</span>")
		_T("\r\n|<span class=\"format\">}</span>|")
		_T("\r\n")
		_T("\r\n|")
		_T("\r\n<span class=\"format\">}</span>")
		_T("\r\n")
		_T("\r\n||</span> <span class=\"format\">{</span>")
		_T("\r\n|\r\n");*/
	strText = _T("Example:\r\n\r\n<span class=\"at\">|</span> <span class=\"format\">{</span>\r\n|<span class=\"selector\">|</span> <span class=\"format\">{</span>\r\n|<span class=\"property\">|</span><span class=\"value\">|</span><span class=\"format\">;</span>\r\n|<span class=\"format\">}</span>|\r\n\r\n|\r\n<span class=\"format\">}</span>\r\n\r\n||<span class=\"comment\">|</span>\r\n|\r\n|");
	SetViewEdit(strText);
}

void CSetPageCSS::OnBnClickedCheckCssPreserve()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_PRESERVE))->GetCheck())
	{
		strText = _T("/* color */")
			_T("\r\nh1 {")
			_T("\r\ncolor:red;")
			_T("\r\n}");
	} 
	else
	{
		strText = _T("h1 {")
			_T("\r\ncolor:red;")
			_T("\r\n}");
	}
	SetViewEdit(strText);
}

void CSetPageCSS::OnBnClickedCheckCssSelectors()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_SELECTORS))->GetCheck())
	{
		strText = _T("h2{color:black;}")
			_T("\r\nh1{color:red;}")
			_T("\r\n==>")
			_T("\r\nh1{color:red;}")
			_T("\r\nh2{color:black;}");
	} 
	else
	{
		strText = _T("h2{color:black;}")
			_T("\r\nh1{color:red;}")
			_T("\r\n==>")
			_T("\r\nh2{color:black;}")
			_T("\r\nh1{color:red;}");
	}
	SetViewEdit(strText);
}

void CSetPageCSS::OnBnClickedCheckCssProperties()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_PROPERTIES))->GetCheck())
	{
		strText = _T("h1{font-size:14px;color:red;}")
			_T("\r\n==>")
			_T("\r\nh1{color:red;font-size:14px;}");
	} 
	else
	{
		strText = _T("h1{font-size:14px;color:red;}")
			_T("\r\n==>")
			_T("\r\nh1{font-size:14px;color:red;}");
	}
	SetViewEdit(strText);
}

void CSetPageCSS::OnBnClickedCheckCssRemovelast()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_REMOVELAST))->GetCheck())
	{
		strText = _T("h1{color:red}");
	} 
	else
	{
		strText = _T("h1{color:red;}");
	}
	SetViewEdit(strText);
}

void CSetPageCSS::OnBnClickedCheckCssRemoveslash()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_REMOVESLASH))->GetCheck())
	{
		strText = _T("h1{color:blue;}");
	} 
	else
	{
		strText = _T("h1{color:red;c\\olor:blue;}");
	}
	SetViewEdit(strText);
}

void CSetPageCSS::OnBnClickedCheckCssDiscard()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_DISCARD))->GetCheck())
	{
		strText = _T("h1{color:red;}");
	} 
	else
	{
		strText = _T("h1{color:red;font-size-adjust:.58;}");
	}
	SetViewEdit(strText);
}

void CSetPageCSS::OnBnClickedCheckCssSilent()
{
	CString strText;
	strText = _T("No errors are shown");
	SetViewEdit(strText);
}

void CSetPageCSS::OnBnClickedCheckCssColors()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_COLORS))->GetCheck())
	{
		strText = _T("h1{color:red;}");
	} 
	else
	{
		strText = _T("h1{color:#ff0000;}");
	}
	SetViewEdit(strText);
}

void CSetPageCSS::OnBnClickedCheckCssFontweight()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_FONTWEIGHT))->GetCheck())
	{
		strText = _T("h1{font-weight:700;}");
	} 
	else
	{
		strText = _T("h1{font-weight:bold;}");
	}
	SetViewEdit(strText);
}

void CSetPageCSS::OnBnClickedCheckCssLowercase()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_LOWERCASE))->GetCheck())
	{
		strText = _T("h1{color:red;}");
	} 
	else
	{
		strText = _T("H1{color:red;}");
	}
	SetViewEdit(strText);
}

void CSetPageCSS::OnBnClickedCheckCssTimestamp()
{
	CString strText;
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_TIMESTAMP))->GetCheck())
	{
		strText = _T("/* CSSTidy 1.3: Sun Sep 02 17:16:30 2012 */\r\nh1{color:red;}");
	} 
	else
	{
		strText = _T("h1{color:red;}");
	}
	SetViewEdit(strText);
}

void CSetPageCSS::OnCbnSelchangeComboCssCase()
{
	CString strText;
	switch (((CComboBox *)GetDlgItem(IDC_COMBO_CSS_CASE))->GetCurSel())
	{
	case 0:strText = _T("h1{color:red;}");
		break;
	case 1:strText = _T("h1{COLOR:red;}");
		break;
	}
	SetViewEdit(strText);
}

void CSetPageCSS::OnCbnSelchangeComboCssOptimise()
{
	CString strText;
	switch (((CComboBox *)GetDlgItem(IDC_COMBO_CSS_OPTIMISE))->GetCurSel())
	{
	case 0:strText = _T("h1{margin-top:10px;margin-right:20px;margin-bottom:10px;margin-left:20px;}");
		break;
	case 1:strText = _T("h1{margin:10px 20px;}");
		break;
	case 2:strText = _T("h1{margin:10px 20px;}");
		break;
	}
	SetViewEdit(strText);
}

void CSetPageCSS::OnCbnSelchangeComboCssRegroup()
{
	CString strText;
	switch (((CComboBox *)GetDlgItem(IDC_COMBO_CSS_REGROUP))->GetCurSel())
	{
	case 0:
		strText = _T("h1{color:red;}")
			_T("\r\nh2{color:red;}")
			_T("\r\n==>")
			_T("\r\nh1{color:red;}")
			_T("\r\nh2{color:red;}");
		break;
	case 1:strText = _T("h1,h2{color:red;}")
			   _T("\r\n==>")
			   _T("\r\nh1{color:red;}")
			   _T("\r\nh2{color:red;}");
		break;
	case 2:strText = _T("h1{color:red;}")
			   _T("\r\nh2{color:red;}")
			   _T("\r\n==>")
			   _T("\r\nh1,h2{color:red;}");
		break;
	}
	SetViewEdit(strText);
}

void CSetPageCSS::SetTidyControl( LPCTSTR lpszTidy, int nPos, int nSize )
{
	CString strTidy(lpszTidy);
	CString strOne(_T("1"));
	CString strTwo(_T("2"));
	if (strTwo == strTidy.Mid(1, 1))
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_CSS_CASE))->SetCurSel(1);
	}
	else
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_CSS_CASE))->SetCurSel(0);
	}
	if (strOne == strTidy.Mid(2, 1))
	{
		((CButton *)GetDlgItem(IDC_CHECK_CSS_COLORS))->SetCheck(1);
	}
	if (strOne == strTidy.Mid(3, 1))
	{
		((CButton *)GetDlgItem(IDC_CHECK_CSS_FONTWEIGHT))->SetCheck(1);
	}
	if (strOne == strTidy.Mid(4, 1))
	{
		((CButton *)GetDlgItem(IDC_CHECK_CSS_DISCARD))->SetCheck(1);
	}
	if (strOne == strTidy.Mid(5, 1))
	{
		((CButton *)GetDlgItem(IDC_CHECK_CSS_LOWERCASE))->SetCheck(1);
	}
	if (strOne == strTidy.Mid(6, 1))
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_CSS_REGROUP))->SetCurSel(1);
	}
	else if (strTwo == strTidy.Mid(6, 1))
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_CSS_REGROUP))->SetCurSel(2);
	}
	else
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_CSS_REGROUP))->SetCurSel(0);
	}
	if (strOne == strTidy.Mid(7, 1))
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_CSS_OPTIMISE))->SetCurSel(1);
	}
	else if (strTwo == strTidy.Mid(7, 1))
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_CSS_OPTIMISE))->SetCurSel(2);
	}
	else
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_CSS_OPTIMISE))->SetCurSel(0);
	}
	if (strOne == strTidy.Mid(8, 1))
	{
		((CButton *)GetDlgItem(IDC_CHECK_CSS_PRESERVE))->SetCheck(1);
	}
	if (strOne == strTidy.Mid(9, 1))
	{
		((CButton *)GetDlgItem(IDC_CHECK_CSS_REMOVESLASH))->SetCheck(1);
	}
	if (strOne == strTidy.Mid(10, 1))
	{
		((CButton *)GetDlgItem(IDC_CHECK_CSS_REMOVELAST))->SetCheck(1);
	}
	if (strOne == strTidy.Mid(11, 1))
	{
		((CButton *)GetDlgItem(IDC_CHECK_CSS_SILENT))->SetCheck(1);
	}
	if (strOne == strTidy.Mid(12, 1))
	{
		((CButton *)GetDlgItem(IDC_CHECK_CSS_PROPERTIES))->SetCheck(1);
	}
	if (strOne == strTidy.Mid(13, 1))
	{
		((CButton *)GetDlgItem(IDC_CHECK_CSS_SELECTORS))->SetCheck(1);
	}
	if (strOne == strTidy.Mid(14, 1))
	{
		((CButton *)GetDlgItem(IDC_CHECK_CSS_TIMESTAMP))->SetCheck(1);
	}
	CString strLevel = strTidy.Mid(15, 6);
	if (CB_ERR == ((CComboBox *)GetDlgItem(IDC_COMBO_CSS_DISCARD))->SelectString(-1, strLevel))
	{		
	}
	CString strTemp = strTidy.Mid(21);
	if (_T("highest") == strTemp)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_CSS_COMPRESSION))->SetCurSel(0);
	}
	else if (_T("high") == strTemp)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_CSS_COMPRESSION))->SetCurSel(1);
	}
	else if (_T("default") == strTemp)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_CSS_COMPRESSION))->SetCurSel(2);
	}
	else if (_T("low") == strTemp)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_CSS_COMPRESSION))->SetCurSel(3);
	}
	else
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_CSS_COMPRESSION))->SetCurSel(4);
		SetDlgItemText(IDC_EDIT_CSS_TEMPLATE, strTemp);
	}
}

void CSetPageCSS::SetTidyConfig( LPCTSTR lpszTidy )
{
	SetTidyControl(lpszTidy, 0, 0);
}

void CSetPageCSS::GetTidyConfig( CString &strTidyValue )
{
	CString strTidy, strValue;
	strTidy.Empty();

	strTidy.Append(_T("0"));

	int nCurSel = ((CComboBox *)GetDlgItem(IDC_COMBO_CSS_CASE))->GetCurSel();
	nCurSel = nCurSel == -1 ? 0 : nCurSel;
	strTidy.AppendFormat(_T("%d"), nCurSel);
	
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_COLORS))->GetCheck())
	{
		strTidy.Append(_T("1"));
	}
	else
	{
		strTidy.Append(_T("0"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_FONTWEIGHT))->GetCheck())
	{
		strTidy.Append(_T("1"));
	}
	else
	{
		strTidy.Append(_T("0"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_DISCARD))->GetCheck())
	{
		strTidy.Append(_T("1"));
	}
	else
	{
		strTidy.Append(_T("0"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_LOWERCASE))->GetCheck())
	{
		strTidy.Append(_T("1"));
	}
	else
	{
		strTidy.Append(_T("0"));
	}
	nCurSel = ((CComboBox *)GetDlgItem(IDC_COMBO_CSS_REGROUP))->GetCurSel();
	nCurSel = nCurSel == -1 ? 0 : nCurSel;
	strTidy.AppendFormat(_T("%d"), nCurSel);
	
	nCurSel = ((CComboBox *)GetDlgItem(IDC_COMBO_CSS_OPTIMISE))->GetCurSel();
	nCurSel = nCurSel == -1 ? 0 : nCurSel;
	strTidy.AppendFormat(_T("%d"), nCurSel);
	
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_PRESERVE))->GetCheck())
	{
		strTidy.Append(_T("1"));
	}
	else
	{
		strTidy.Append(_T("0"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_REMOVESLASH))->GetCheck())
	{
		strTidy.Append(_T("1"));
	}
	else
	{
		strTidy.Append(_T("0"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_REMOVELAST))->GetCheck())
	{
		strTidy.Append(_T("1"));
	}
	else
	{
		strTidy.Append(_T("0"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_SILENT))->GetCheck())
	{
		strTidy.Append(_T("1"));
	}
	else
	{
		strTidy.Append(_T("0"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_PROPERTIES))->GetCheck())
	{
		strTidy.Append(_T("1"));
	}
	else
	{
		strTidy.Append(_T("0"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_SELECTORS))->GetCheck())
	{
		strTidy.Append(_T("1"));
	}
	else
	{
		strTidy.Append(_T("0"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_CSS_TIMESTAMP))->GetCheck())
	{
		strTidy.Append(_T("1"));
	}
	else
	{
		strTidy.Append(_T("0"));
	}
	nCurSel = ((CComboBox *)GetDlgItem(IDC_COMBO_CSS_DISCARD))->GetCurSel();
	nCurSel = nCurSel == -1 ? 0 : nCurSel;
	if (0 == nCurSel)
	{
		strTidy.Append(_T("CSS2.1"));
	} 
	else if (1 == nCurSel)
	{
		strTidy.Append(_T("CSS2.1"));
	}
	else
	{
		strTidy.Append(_T("CSS1.0"));
	}
	nCurSel = ((CComboBox *)GetDlgItem(IDC_COMBO_CSS_COMPRESSION))->GetCurSel();
	nCurSel = nCurSel == -1 ? 0 : nCurSel;
	switch (nCurSel)
	{
	case 0:strTidy.Append(_T("highest"));
		break;
	case 1:strTidy.Append(_T("high"));
		break;
	case 2:strTidy.Append(_T("default"));
		break;
	case 3:strTidy.Append(_T("low"));
		break;
	case 4:
		{
			GetDlgItemText(IDC_EDIT_CSS_TEMPLATE, strValue);
			if (strValue.IsEmpty())
			{
				strValue = _T("default");
			}
			strTidy.Append(strValue);
		}
		break;
	}

	strTidyValue.Append(strTidy);
}
void CSetPageCSS::OnOK()
{
	CString strTidy;
	GetTidyConfig(strTidy);
	TRACE(strTidy);
	TRACE(_T("\r"));
	g_GlobalTidy.m_TidyCss = strTidy;

	CBCGPPropertyPage::OnOK();
}
