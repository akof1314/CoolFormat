// SetPageCppFast.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageCppFast.h"


// CSetPageCppFast 对话框

IMPLEMENT_DYNAMIC(CSetPageCppFast, CBCGPDialog)

CSetPageCppFast::CSetPageCppFast(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetPageCppFast::IDD, pParent)
	, m_pEditWnd(NULL)
{
}

CSetPageCppFast::~CSetPageCppFast()
{
}

void CSetPageCppFast::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetPageCppFast, CBCGPDialog)
	ON_BN_CLICKED(IDC_RADIO1, &CSetPageCppFast::OnBnClickedStyleRadio)
	ON_BN_CLICKED(IDC_RADIO2, &CSetPageCppFast::OnBnClickedStyleRadio)
	ON_BN_CLICKED(IDC_RADIO3, &CSetPageCppFast::OnBnClickedStyleRadio)
	ON_BN_CLICKED(IDC_RADIO4, &CSetPageCppFast::OnBnClickedStyleRadio)
	ON_BN_CLICKED(IDC_RADIO5, &CSetPageCppFast::OnBnClickedStyleRadio)
	ON_BN_CLICKED(IDC_RADIO6, &CSetPageCppFast::OnBnClickedStyleRadio)
	ON_BN_CLICKED(IDC_RADIO7, &CSetPageCppFast::OnBnClickedStyleRadio)
	ON_BN_CLICKED(IDC_RADIO8, &CSetPageCppFast::OnBnClickedStyleRadio)
	ON_BN_CLICKED(IDC_RADIO9, &CSetPageCppFast::OnBnClickedStyleRadio)
	ON_BN_CLICKED(IDC_RADIO10, &CSetPageCppFast::OnBnClickedStyleRadio)
	ON_BN_CLICKED(IDC_RADIO11, &CSetPageCppFast::OnBnClickedStyleRadio)
	ON_BN_CLICKED(IDC_RADIO12, &CSetPageCppFast::OnBnClickedStyleRadio)
	ON_BN_CLICKED(IDC_RADIO13, &CSetPageCppFast::OnBnClickedStyleRadio)
END_MESSAGE_MAP()

void CSetPageCppFast::OnBnClickedStyleRadio()
{
	CString strExample = _T("");
	UINT selectStyle = 0;
	for (int i = IDC_RADIO1; i <= IDC_RADIO12 ; i++)
	{
		if (((CButton*)GetDlgItem(i))->GetCheck())
			selectStyle = i - IDC_RADIO1 + 1;
	}	
	switch (selectStyle)
	{
	case 1: strExample = _T("int Foo(bool isBar)")
				_T("\r\n")_T("{")
				_T("\r\n")_T("     if (isBar)")
				_T("\r\n")_T("     { ")
				_T("\r\n")_T("          bar();")
				_T("\r\n")_T("          return 1;")
				_T("\r\n")_T("     }")
				_T("\r\n")_T("     else")
				_T("\r\n")_T("          return 0;")
				_T("\r\n")_T("}");
		break;
	case 2: strExample = _T("int Foo(bool isBar) {")
				_T("\r\n")_T("    if (isBar) {")
				_T("\r\n")_T("        bar();")
				_T("\r\n")_T("        return 1;")
				_T("\r\n")_T("    } else")
				_T("\r\n")_T("        return 0;")
				_T("\r\n")_T("}");
		break;
	case 3: strExample = _T("int Foo(bool isBar)")
				_T("\r\n")_T("{")
				_T("\r\n")_T("    if (isBar) {")
				_T("\r\n")_T("        bar();")
				_T("\r\n")_T("        return 1;")
				_T("\r\n")_T("    } else")
				_T("\r\n")_T("        return 0;")
				_T("\r\n")_T("}");
		break;
	case 4: strExample = _T("int Foo(bool isBar)")
				_T("\r\n")_T("{")
				_T("\r\n")_T("     if (isBar) {")
				_T("\r\n")_T("          bar();")
				_T("\r\n")_T("          return 1;")
				_T("\r\n")_T("     } else")
				_T("\r\n")_T("          return 0;")
				_T("\r\n")_T("}");
		break;
	case 5: strExample = _T("int Foo(bool isBar)")
				_T("\r\n")_T("    {")
				_T("\r\n")_T("    if (isBar)")
				_T("\r\n")_T("        {")
				_T("\r\n")_T("        bar();")
				_T("\r\n")_T("        return 1;")
				_T("\r\n")_T("        }")
				_T("\r\n")_T("    else")
				_T("\r\n")_T("        return 0;")
				_T("\r\n")_T("    }");
		break;
	case 6: strExample = _T("int Foo(bool isBar) {")
				_T("\r\n")_T("    if (isBar) {")
				_T("\r\n")_T("        bar();")
				_T("\r\n")_T("        return 1;")
				_T("\r\n")_T("        }")
				_T("\r\n")_T("    else")
				_T("\r\n")_T("        return 0;")
				_T("\r\n")_T("    }");
		break;
	case 7: strExample = _T("int Foo(bool isBar)")
				_T("\r\n")_T("{")
				_T("\r\n")_T("  if (isBar)")
				_T("\r\n")_T("    {")
				_T("\r\n")_T("      bar();")
				_T("\r\n")_T("      return 1;")
				_T("\r\n")_T("    }")
				_T("\r\n")_T("  else")
				_T("\r\n")_T("    return 0;")
				_T("\r\n")_T("}");
		break;
	case 8: strExample = _T("int Foo(bool isBar)")
				_T("\r\n")_T("{")
				_T("\r\n")_T("        if (isBar) {")
				_T("\r\n")_T("                bar();")
				_T("\r\n")_T("                return 1;")
				_T("\r\n")_T("        } else")
				_T("\r\n")_T("                return 0;")
				_T("\r\n")_T("}");
		break;
	case 9: strExample = _T("int Foo(bool isBar)")
				_T("\r\n")_T("{  if (isBar)")
				_T("\r\n")_T("   {  bar();")
				_T("\r\n")_T("      return 1;")
				_T("\r\n")_T("   }")
				_T("\r\n")_T("   else")
				_T("\r\n")_T("      return 0;")
				_T("\r\n")_T("}");
		break;
	case 10: strExample = _T("int Foo(bool isBar)")
				 _T("\r\n")_T("{")
				 _T("\r\n")_T("    if (isBar) {")
				 _T("\r\n")_T("        bar();")
				 _T("\r\n")_T("        return 1;")
				 _T("\r\n")_T("    } else {")
				 _T("\r\n")_T("        return 0;")
				 _T("\r\n")_T("    }")
				 _T("\r\n")_T("}");
		break;
	case 11: strExample = _T("int Foo(bool isBar)")
				 _T("\r\n")_T("{  if (isBar)")
				 _T("\r\n")_T("   {  bar();")
				 _T("\r\n")_T("      return 1; }")
				 _T("\r\n")_T("        return 1;")
				 _T("\r\n")_T("    else")
				 _T("\r\n")_T("      return 0; }");
		break;
	case 12: strExample = _T("int Foo(bool isBar) {")
				 _T("\r\n")_T("    if (isBar) {")
				 _T("\r\n")_T("        bar()")
				 _T("\r\n")_T("        return 1; }")
				 _T("\r\n")_T("    else")
				 _T("\r\n")_T("        return 0; }");
		break;
	}
	if (m_pEditWnd)
	{
		m_pEditWnd->SetWindowText(strExample);
	}
}

BOOL CSetPageCppFast::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSetPageCppFast::SetTidyConfig( LPCTSTR lpszTidy )
{
	bool bStyle = false;
	int lenTidy = _tcsclen(lpszTidy);
	for (int i = 0; i < lenTidy; ++i)
	{
		if ('A' == lpszTidy[i])
		{
			if (i + 1 != lenTidy && _istdigit(lpszTidy[i + 1]))
			{
				int nStyle;
				if (i + 2 < lenTidy && _istdigit(lpszTidy[i + 2]))
				{
					CString strStyle(lpszTidy + i + 1, 2);
					nStyle = _ttoi(strStyle);
				}
				else
				{
					CString strStyle(lpszTidy + i + 1, 1);
					nStyle = _ttoi(strStyle);
				}
				
				if (nStyle > 0 && nStyle < 13)
				{
					((CButton*)GetDlgItem(IDC_RADIO1 + nStyle - 1))->SetCheck(1);
					bStyle = true;
					break;
				}
			}
		}
	}
	if (!bStyle)
	{
		((CButton*)GetDlgItem(IDC_RADIO13))->SetCheck(1);
	}
}

void CSetPageCppFast::GetTidyConfig(CString &strTidyValue)
{
	CString strTidy = _T("A");
	for (int i = IDC_RADIO1; i <= IDC_RADIO12 ; i++)
	{
		if (((CButton*)GetDlgItem(i))->GetCheck())
		{
			strTidy.AppendFormat(_T("%d"), i - IDC_RADIO1 + 1);
			strTidyValue.Append(strTidy);
			return ;
		}
	}	
}