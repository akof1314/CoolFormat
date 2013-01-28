// SetPageHtmlTwo.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolFormat3.h"
#include "SetPageHtmlTwo.h"


// CSetPageHtmlTwo 对话框

IMPLEMENT_DYNAMIC(CSetPageHtmlTwo, CBCGPDialog)

CSetPageHtmlTwo::CSetPageHtmlTwo(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CSetPageHtmlTwo::IDD, pParent)
{
	m_onlyHtmlXml = SYN_HTML;
}

CSetPageHtmlTwo::~CSetPageHtmlTwo()
{
}

void CSetPageHtmlTwo::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetPageHtmlTwo, CBCGPDialog)
	ON_BN_CLICKED(IDC_CHECK_HTML_BREAK_BEFORE_BR, &CSetPageHtmlTwo::OnBnClickedCheckHtmlBreakBeforeBr)
	ON_BN_CLICKED(IDC_CHECK_HTML_INDENT_ATTRIBUTES, &CSetPageHtmlTwo::OnBnClickedCheckHtmlIndentAttributes)
	ON_BN_CLICKED(IDC_CHECK_HTML_INDENT_SPACES, &CSetPageHtmlTwo::OnBnClickedCheckHtmlIndentSpaces)
	ON_BN_CLICKED(IDC_CHECK_HTML_MARKUP, &CSetPageHtmlTwo::OnBnClickedCheckHtmlMarkup)
	ON_BN_CLICKED(IDC_CHECK_HTML_PUNCTUATION_WRAP, &CSetPageHtmlTwo::OnBnClickedCheckHtmlPunctuationWrap)
	ON_BN_CLICKED(IDC_CHECK_HTML_VERTICAL_SPACE, &CSetPageHtmlTwo::OnBnClickedCheckHtmlVerticalSpace)
	ON_BN_CLICKED(IDC_CHECK_HTML_WRAP_ASP, &CSetPageHtmlTwo::OnBnClickedCheckHtmlWrapAsp)
	ON_BN_CLICKED(IDC_CHECK_HTML_WRAP_ATTRIBUTES, &CSetPageHtmlTwo::OnBnClickedCheckHtmlWrapAttributes)
	ON_BN_CLICKED(IDC_CHECK_HTML_WRAP_JSTE, &CSetPageHtmlTwo::OnBnClickedCheckHtmlWrapJste)
	ON_BN_CLICKED(IDC_CHECK_HTML_WRAP_PHP, &CSetPageHtmlTwo::OnBnClickedCheckHtmlWrapPhp)
	ON_BN_CLICKED(IDC_CHECK_HTML_WRAP_SCRIPT_LITERALS, &CSetPageHtmlTwo::OnBnClickedCheckHtmlWrapScriptLiterals)
	ON_BN_CLICKED(IDC_CHECK_HTML_WRAP_SECTIONS, &CSetPageHtmlTwo::OnBnClickedCheckHtmlWrapSections)
	ON_BN_CLICKED(IDC_CHECK_HTML_ASCII_CHARS, &CSetPageHtmlTwo::OnBnClickedCheckHtmlAsciiChars)
	ON_BN_CLICKED(IDC_CHECK_HTML_SHOW_WARNINGS, &CSetPageHtmlTwo::OnBnClickedCheckHtmlShowWarnings)
	ON_EN_SETFOCUS(IDC_EDIT_HTML_ALT_TEXT, &CSetPageHtmlTwo::OnEnSetfocusEditHtmlAltText)
	ON_EN_SETFOCUS(IDC_EDIT_HTML_CSS_PREFIX, &CSetPageHtmlTwo::OnEnSetfocusEditHtmlCssPrefix)	
	ON_EN_SETFOCUS(IDC_EDIT_HTML_NEW_BLOCKLEVEL_TAGS, &CSetPageHtmlTwo::OnEnSetfocusEditHtmlNewBlocklevelTags)
	ON_EN_SETFOCUS(IDC_EDIT_HTML_NEW_EMPTY_TAGS, &CSetPageHtmlTwo::OnEnSetfocusEditHtmlNewEmptyTags)
	ON_EN_SETFOCUS(IDC_EDIT_HTML_NEW_INLINE_TAGS, &CSetPageHtmlTwo::OnEnSetfocusEditHtmlNewInlineTags)
	ON_EN_SETFOCUS(IDC_EDIT_HTML_NEW_PRE_TAGS, &CSetPageHtmlTwo::OnEnSetfocusEditHtmlNewPreTags)
	ON_EN_SETFOCUS(IDC_EDIT_HTML_SHOW_ERRORS, &CSetPageHtmlTwo::OnEnSetfocusEditHtmlShowErrors)
	ON_EN_SETFOCUS(IDC_EDIT_HTML_INDENT_SPACES, &CSetPageHtmlTwo::OnEnSetfocusEditHtmlIndentSpaces)
	ON_EN_SETFOCUS(IDC_EDIT_HTML_TAB_SIZE, &CSetPageHtmlTwo::OnEnSetfocusEditHtmlTabSize)
	ON_EN_SETFOCUS(IDC_EDIT_HTML_WRAP, &CSetPageHtmlTwo::OnEnSetfocusEditHtmlWrap)
	ON_CBN_SETFOCUS(IDC_COMBO_HTML_INDENT, &CSetPageHtmlTwo::OnCbnSetfocusComboHtmlIndent)
	ON_CBN_SETFOCUS(IDC_COMBO_HTML_MERGE_DIVS, &CSetPageHtmlTwo::OnCbnSetfocusComboHtmlMergeDivs)
	ON_CBN_SETFOCUS(IDC_COMBO_HTML_MERGE_SPANS, &CSetPageHtmlTwo::OnCbnSetfocusComboHtmlMergeSpans)
	ON_CBN_SETFOCUS(IDC_COMBO_HTML_SHOW_BODY_ONLY, &CSetPageHtmlTwo::OnCbnSetfocusComboHtmlShowBodyOnly)
	ON_CBN_SETFOCUS(IDC_COMBO_HTML_DOCTYPE, &CSetPageHtmlTwo::OnCbnSetfocusComboHtmlDoctype)
	ON_CBN_SETFOCUS(IDC_COMBO_HTML_REPEATED_ATTRIBUTES, &CSetPageHtmlTwo::OnCbnSetfocusComboHtmlRepeatedAttributes)
	ON_CBN_SETFOCUS(IDC_COMBO_HTML_SORT_ATTRIBUTES, &CSetPageHtmlTwo::OnCbnSetfocusComboHtmlSortAttributes)
	ON_CBN_SETFOCUS(IDC_COMBO_HTML_CHAR_ENCODING, &CSetPageHtmlTwo::OnCbnSetfocusComboHtmlCharEncoding)
	ON_CBN_SETFOCUS(IDC_COMBO_HTML_INPUT_ENCODING, &CSetPageHtmlTwo::OnCbnSetfocusComboHtmlInputEncoding)
	ON_CBN_SETFOCUS(IDC_COMBO_HTML_OUTPUT_ENCODING, &CSetPageHtmlTwo::OnCbnSetfocusComboHtmlOutputEncoding)
	ON_BN_CLICKED(IDC_CHECK_HTML_FORCE_OUTPUT, &CSetPageHtmlTwo::OnBnClickedCheckHtmlForceOutput)
END_MESSAGE_MAP()

void CSetPageHtmlTwo::SetViewEdit( LPCTSTR lpszText )
{
	if (m_pEditWnd)
	{
		m_pEditWnd->SetWindowText(lpszText);
	}
}

BOOL CSetPageHtmlTwo::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	InitLimit();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSetPageHtmlTwo::OnBnClickedCheckHtmlBreakBeforeBr()
{
	CString strText;
	strText = _T("This option specifies if Tidy should output a line break before each <BR> element.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否输出时在每一个<BR>元素前,加一个空行."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnBnClickedCheckHtmlIndentAttributes()
{
	CString strText;
	strText = _T("This option specifies if Tidy should begin each attribute on a new line.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否每个属性占一行."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnBnClickedCheckHtmlIndentSpaces()
{
	CString strText;
	strText = _T("");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T(""));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnBnClickedCheckHtmlMarkup()
{
	CString strText;
	strText = _T("This option specifies if Tidy should generate a pretty printed version of the markup. Note that Tidy won't generate a pretty printed version if it finds significant errors (see force-output).");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否生成美化版本的标记.注意:如果有严重错误时不生成美化版. (见 force-output)."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnBnClickedCheckHtmlPunctuationWrap()
{
	CString strText;
	strText = _T("This option specifies if Tidy should line wrap after some Unicode or Chinese punctuation characters.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否在一些Unicode或中文发音字符后绕行."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnBnClickedCheckHtmlVerticalSpace()
{
	CString strText;
	strText = _T("This option specifies if Tidy should add some empty lines for readability.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否为可读性加入一些空行."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnBnClickedCheckHtmlWrapAsp()
{
	CString strText;
	strText = _T("This option specifies if Tidy should line wrap text contained within ASP pseudo elements, which look like: <% ... %>.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否在对ASP伪元素内的文本内容换行, 形如: <% ... %>."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnBnClickedCheckHtmlWrapAttributes()
{
	CString strText;
	strText = _T("This option specifies if Tidy should line wrap attribute values, for easier editing. This option can be set independently of wrap-script-literals.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否为方便编辑而对属性值绕行. 该选项可独立于wrap-script-literals选项设置."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnBnClickedCheckHtmlWrapJste()
{
	CString strText;
	strText = _T("This option specifies if Tidy should line wrap text contained within JSTE pseudo elements, which look like: <# ... #>.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否对JSTE伪元素内的文本内容进行绕行, 形如: <# ... #>."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnBnClickedCheckHtmlWrapPhp()
{
	CString strText;
	strText = _T("This option specifies if Tidy should line wrap text contained within PHP pseudo elements, which look like: <?php ... ?>.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否对php伪元素内的文本内容进行绕行, 形如: <?php ... ?>."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnBnClickedCheckHtmlWrapScriptLiterals()
{
	CString strText;
	strText = _T("This option specifies if Tidy should line wrap string literals that appear in script attributes. Tidy wraps long script string literals by inserting a backslash character before the line break.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否对出现在脚本属性(script attributes)中的字符串字面量进行绕行. Tidy通过在换行前插入反斜杠对长字符串字面量进行绕行."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnBnClickedCheckHtmlWrapSections()
{
	CString strText;
	strText = _T("This option specifies if Tidy should line wrap text contained within <![ ... ]> section tags.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否对<![ ... ]>段标签内的文本内容进行绕行."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnBnClickedCheckHtmlAsciiChars()
{
	CString strText;
	strText = _T("Can be used to modify behavior of -c (--clean yes) option. If set to \"yes\" when using -c, &emdash;, &rdquo;, and other named character entities are downgraded to their closest ascii equivalents.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("可以用于调整选项-c (--clean yes)的行为. 当用-c选项时,置为\"yes\",则 &emdash;, &rdquo;, 以及其他命名字符实体将被降级为最相近的ascii."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnBnClickedCheckHtmlShowWarnings()
{
	CString strText;
	strText = _T("This option specifies if Tidy should suppress warnings. This can be useful when a few errors are hidden in a flurry of warnings.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否抑制警告信息,当有大量警告信息使得错误信息难于发现时可用."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnBnClickedCheckHtmlForceOutput()
{
	CString strText;
	strText = _T("This option specifies if Tidy should produce output even if errors are encountered. Use this option with care - if Tidy reports an error, this means Tidy was not able to, or is not sure how to, fix the error, so the resulting output may not reflect your intention.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否产生输出, 即使有严重错误存在.如果Tidy报告严重错误的话,该选项慎用, 这意味着Tidy不能或不确定如何修复错误,从而使输出不能表现你的意图."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnEnSetfocusEditHtmlAltText()
{
	CString strText;
	strText = _T("This option specifies the default \"alt=\" text Tidy uses for <IMG> attributes. This feature is dangerous as it suppresses further accessibility warnings. You are responsible for making your documents accessible to people who can not see the images!");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此配置项规定标签<IMG>的\"alt=\"属性的默认文本.这个功能是危险的, 因为它会抑制接下来的可访问性警告.你有责任帮助那些不能看到图片的人识别你的文档!"));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnEnSetfocusEditHtmlCssPrefix()
{
	CString strText;
	strText = _T("This option specifies the prefix that Tidy uses for styles rules. By default, \"c\" will be used.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定用在风格规则的前缀.默认为\"c\"."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnEnSetfocusEditHtmlNewBlocklevelTags()
{
	CString strText;
	strText = _T("This option specifies new block-level tags. This option takes a space or comma separated list of tag names. Unless you declare new tags, Tidy will refuse to generate a tidied file if the input includes previously unknown tags. Note you can't change the content model for elements such as <TABLE>, <UL>, <OL> and <DL>. This option is ignored in XML mode.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定新的块级标签. 此选项用空格或逗号分隔标签列表.除非你声明了新表签, 如果输入文件包含先前未知的标签,Tidy将不会生成处理文件. 你不能改变元素内容的模式,比如: <TABLE>, <UL>, <OL> and <DL>. 这个选项在XML模式中被忽略."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnEnSetfocusEditHtmlNewEmptyTags()
{
	CString strText;
	strText = _T("This option specifies new empty inline tags. This option takes a space or comma separated list of tag names. Unless you declare new tags, Tidy will refuse to generate a tidied file if the input includes previously unknown tags. Remember to also declare empty tags as either inline or blocklevel. This option is ignored in XML mode.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("该选项指定新的空inline标签.该选项规定新的空inline标签. 此选项用空格或逗号分隔标签列表.除非你声明了新表签, 如果输入文件包含先前未知的标签,Tidy将不会生成处理文件.记住,声明的空标签也作为inline或blocklevel标签. 这个选项在XML模式中被忽略."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnEnSetfocusEditHtmlNewInlineTags()
{
	CString strText;
	strText = _T("This option specifies new non-empty inline tags. This option takes a space or comma separated list of tag names. Unless you declare new tags, Tidy will refuse to generate a tidied file if the input includes previously unknown tags. This option is ignored in XML mode.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定新的非空inline标签.此选项用空格或逗号分隔标签列表. 除非你声明了新表签,如果输入文件包含先前未知的标签,Tidy将不会生成处理文件. 这个选项在XML模式中被忽略."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnEnSetfocusEditHtmlNewPreTags()
{
	CString strText;
	strText = _T("This option specifies new tags that are to be processed in exactly the same way as HTML's <PRE> element. This option takes a space or comma separated list of tag names. Unless you declare new tags, Tidy will refuse to generate a tidied file if the input includes previously unknown tags. Note you can not as yet add new CDATA elements (similar to <SCRIPT>). This option is ignored in XML mode.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定以HTML的<PRE>元素做同样处理的新标签. 此选项用空格或逗号分隔标签列表.除非你声明了新表签,如果输入文件包含先前未知的标签, Tidy将不会生成处理文件. 注意:你也不能加新的CDATA 元素 (类似 <SCRIPT>). 这个选项在XML模式中被忽略."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnEnSetfocusEditHtmlShowErrors()
{
	CString strText;
	strText = _T("This option specifies the number Tidy uses to determine if further errors should be shown. If set to 0, then no errors are shown.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定Tidy确定显示错误信息的数字. 如果置为 0, 则不显示错误."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnEnSetfocusEditHtmlIndentSpaces()
{
	CString strText;
	strText = _T("This option specifies the number of spaces Tidy uses to indent content, when indentation is enabled.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定缩进选型开启时,缩进的空格数."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnEnSetfocusEditHtmlTabSize()
{
	CString strText;
	strText = _T("This option specifies the number of columns that Tidy uses between successive tab stops. It is used to map tabs to spaces when reading the input. Tidy never outputs tabs.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定连续tab符号所占的列数. 用于从tab到空格的映射.Tidy不输出tab."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnEnSetfocusEditHtmlWrap()
{
	CString strText;
	strText = _T("This option specifies the right margin Tidy uses for line wrapping. Tidy tries to wrap lines so that they do not exceed this length. Set wrap to zero if you want to disable line wrapping.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定绕行的右边距. Tidy在不超过此长度内换行. 置为0,意味着关闭绕行功能."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnCbnSetfocusComboHtmlIndent()
{
	CString strText;
	strText = _T("This option specifies if Tidy should indent block-level tags. If set to \"auto\", this option causes Tidy to decide whether or not to indent the content of tags such as TITLE, H1-H6, LI, TD, TD, or P depending on whether or not the content includes a block-level element. You are advised to avoid setting indent to yes as this can expose layout bugs in some browsers.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否缩进块级标签. 若置为\"auto\", 则此选项会根据标签,如:TITLE, H1-H6, LI, TD, TD, 或 P是否包括块级元素内容, 决定是否缩进标签内容. 建议避免使用yes, 因为会使一些浏览器出现层(layout)bugs."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnCbnSetfocusComboHtmlMergeDivs()
{
	CString strText;
	strText = _T("Can be used to modify behavior of -c (--clean yes) option. This option specifies if Tidy should merge nested <div> such as \"<div><div>...</div></div>\". If set to \"auto\", the attributes of the inner <div> are moved to the outer one. As well, nested <div> with ID attributes are not merged. If set to \"yes\", the attributes of the inner <div> are discarded with the exception of \"class\" and \"style\".");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("用于改变-c (--clean yes)选项的行为.该选项规定是否合并嵌套的<div>像\"<div><div>...</div></div>\". 如果设为\"auto\", 内部<div>的属性值被移到外部. 带ID属性的<div>不进行合并. 如果设为\"yes\", 内部<div>的属性值若有不合法的\"class\"和\"style\"将被丢弃."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnCbnSetfocusComboHtmlMergeSpans()
{
	CString strText;
	strText = _T("Can be used to modify behavior of -c (--clean yes) option. This option specifies if Tidy should merge nested <span> such as \"<span><span>...</span></span>\". The algorithm is identical to the one used by --merge-divs.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("用于改变-c (--clean yes)选项的行为. 该选项规定是否合并嵌套的<span>像\"<span><span>...</span></span>\". 算法与选项--merge-divs一致."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnCbnSetfocusComboHtmlShowBodyOnly()
{
	CString strText;
	strText = _T("This option specifies if Tidy should print only the contents of the body tag as an HTML fragment. If set to \"auto\", this is performed only if the body tag has been inferred. Useful for incorporating existing whole pages as a portion of another page. This option has no effect if XML output is requested.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否只打印html的body标签的内容.如果置为\"auto\",仅在推断存在有body标签时执行."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnCbnSetfocusComboHtmlDoctype()
{
	CString strText;
	strText = _T("This option specifies the DOCTYPE declaration generated by Tidy. If set to \"omit\" the output won't contain a DOCTYPE declaration. If set to \"auto\" (the default) Tidy will use an educated guess based upon the contents of the document. If set to \"strict\", Tidy will set the DOCTYPE to the strict DTD. If set to \"loose\", the DOCTYPE is set to the loose (transitional) DTD. Alternatively, you can supply a string for the formal public identifier (FPI).");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定Tidy生成的DOCTYPE 声明. 设为\"omit\" 输出不包含 DOCTYPE 声明. 设为\"auto\"(默认) 则依据内容作经验判断. 设为\"strict\", Tidy 设置 DOCTYPE 为严格(strict) DTD. 设为\"loose\", DOCTYPE 设为 loose (transitional) DTD. 作为选择, 你可以给一个字符串作为FPI(the formal public identifier)."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnCbnSetfocusComboHtmlRepeatedAttributes()
{
	CString strText;
	strText = _T("This option specifies if Tidy should keep the first or last attribute, if an attribute is repeated, e.g. has two align attributes.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否保持重复属性的第一个或最后一个不变.比如:两个对齐align属性."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnCbnSetfocusComboHtmlSortAttributes()
{
	CString strText;
	strText = _T("This option specifies that tidy should sort attributes within an element using the specified sort algorithm. If set to \"alpha\", the algorithm is an ascending alphabetic sort.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定是否按一些特定的排序算法对元素中的属性进行排序. 如果置为\"alpha\", 则按字母序排序."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnCbnSetfocusComboHtmlCharEncoding()
{
	CString strText;
	strText = _T("This option specifies the character encoding Tidy uses for both the input and output. For ascii, Tidy will accept Latin-1 (ISO-8859-1) character values, but will use entities for all characters whose value > 127. For raw, Tidy will output values above 127 without translating them into entities. For latin1, characters above 255 will be written as entities. For utf8, Tidy assumes that both input and output is encoded as UTF-8. You can use iso2022 for files encoded using the ISO-2022 family of encodings e.g. ISO-2022-JP. For mac and win1252, Tidy will accept vendor specific character values, but will use entities for all characters whose value > 127. For unsupported encodings, use an external utility to convert to and from UTF-8.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定用于输入和输出的字符集编码. 对于ascii,Tidy将接受Latin-1 (ISO-8859-1)字符值, 但将对所有其值>127字符用实体. 对于raw, Tidy将不用实体输出其值>127字符. 对于latin1, 字符在255以上的输出为其实体. 对于utf8, Tidy假设输入和输出文件都是用utf-8编码. 你可以用ISO-2022家族编码,例如ISO-2022-JP. 对于mac和win1252, Tidy将接受其厂商的特殊字符值, 但对于所有字符值>127的将用其实体. 对于不支持的编码, 要用外部工具从UTF-8转化, 或转化到UTF-8."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnCbnSetfocusComboHtmlInputEncoding()
{
	CString strText;
	strText = _T("This option specifies the character encoding Tidy uses for the input. See char-encoding for more info.");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定输入文件的字符集编码. 更多请见char-encoding."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::OnCbnSetfocusComboHtmlOutputEncoding()
{
	CString strText;
	strText = _T("This option specifies the character encoding Tidy uses for the output. See char-encoding for more info. May only be different from input-encoding for Latin encodings (ascii, latin0, latin1, mac, win1252, ibm858).");
	if (1 == theApp.m_nAppLanguageID)
	{
		strText.Append(_T("\r\n"));
		strText.Append(_T("此选项规定Tidy用于输出的字符集编码. 更多请见char-encoding. 仅对于Latin编码(ascii, latin0, latin1, mac, win1252, ibm858),可能与输入编码不同."));
	}
	SetViewEdit(strText);
}

void CSetPageHtmlTwo::InitLimit()
{
	((CComboBox *)GetDlgItem(IDC_COMBO_HTML_INDENT))->SetCurSel(2);
	((CComboBox *)GetDlgItem(IDC_COMBO_HTML_MERGE_DIVS))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_COMBO_HTML_MERGE_SPANS))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_COMBO_HTML_SHOW_BODY_ONLY))->SetCurSel(2);
	((CComboBox *)GetDlgItem(IDC_COMBO_HTML_DOCTYPE))->SetCurSel(1);
	((CComboBox *)GetDlgItem(IDC_COMBO_HTML_REPEATED_ATTRIBUTES))->SetCurSel(1);
	((CComboBox *)GetDlgItem(IDC_COMBO_HTML_SORT_ATTRIBUTES))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_COMBO_HTML_CHAR_ENCODING))->SetCurSel(1);
	((CComboBox *)GetDlgItem(IDC_COMBO_HTML_INPUT_ENCODING))->SetCurSel(3);
	((CComboBox *)GetDlgItem(IDC_COMBO_HTML_OUTPUT_ENCODING))->SetCurSel(1);
	((CEdit *)GetDlgItem(IDC_EDIT_HTML_SHOW_ERRORS))->SetWindowText(_T("6"));
	((CEdit *)GetDlgItem(IDC_EDIT_HTML_INDENT_SPACES))->SetWindowText(_T("2"));
	((CEdit *)GetDlgItem(IDC_EDIT_HTML_TAB_SIZE))->SetWindowText(_T("8"));
	((CEdit *)GetDlgItem(IDC_EDIT_HTML_WRAP))->SetWindowText(_T("68"));
}

void CSetPageHtmlTwo::SetTidyConfig( LPCTSTR lpszTidy, UINT uLangID )
{
	m_onlyHtmlXml = uLangID;
	int lenTidy = _tcsclen(lpszTidy);
	if (lenTidy <= 0 || lpszTidy[0] != '-')
	{
		return;
	}

	int nOption = -1;
	for (int i = 0; i < lenTidy; ++i)
	{
		if (lpszTidy[i] == '-')
		{
			if (-1 != nOption)
			{
				SetTidyControl(lpszTidy, nOption, i - nOption);
			}
			nOption = i;
		}
	}
	SetTidyControl(lpszTidy, nOption, lenTidy - nOption);
}

void CSetPageHtmlTwo::GetTidyConfig( CString &strTidyValue )
{
	CString strTidy, strValue;
	strTidy.Empty();

	if (((CButton *)GetDlgItem(IDC_CHECK_HTML_BREAK_BEFORE_BR))->GetCheck())
	{
		strTidy.Append(_T("-bbb"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_HTML_INDENT_ATTRIBUTES))->GetCheck())
	{
		strTidy.Append(_T("-ia"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_HTML_MARKUP))->GetCheck())
	{
		strTidy.Append(_T("-m"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_HTML_PUNCTUATION_WRAP))->GetCheck())
	{
		strTidy.Append(_T("-pw"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_HTML_VERTICAL_SPACE))->GetCheck())
	{
		strTidy.Append(_T("-vs"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_HTML_WRAP_ASP))->GetCheck())
	{
		strTidy.Append(_T("-wa"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_HTML_WRAP_ATTRIBUTES))->GetCheck())
	{
		strTidy.Append(_T("-wat"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_HTML_WRAP_JSTE))->GetCheck())
	{
		strTidy.Append(_T("-wj"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_HTML_WRAP_PHP))->GetCheck())
	{
		strTidy.Append(_T("-wp"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_HTML_WRAP_SCRIPT_LITERALS))->GetCheck())
	{
		strTidy.Append(_T("-wsl"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_HTML_WRAP_SECTIONS))->GetCheck())
	{
		strTidy.Append(_T("-ws"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_HTML_ASCII_CHARS))->GetCheck())
	{
		strTidy.Append(_T("-ac"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_HTML_SHOW_WARNINGS))->GetCheck())
	{
		strTidy.Append(_T("-sw"));
	}
	if (((CButton *)GetDlgItem(IDC_CHECK_HTML_FORCE_OUTPUT))->GetCheck())
	{
		strTidy.Append(_T("-fo"));
	}
	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_INDENT))->GetCurSel())
	{
		strTidy.AppendFormat(_T("-i%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_INDENT))->GetCurSel());
	}
	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_MERGE_DIVS))->GetCurSel())
	{
		strTidy.AppendFormat(_T("-md%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_MERGE_DIVS))->GetCurSel());
	}
	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_MERGE_SPANS))->GetCurSel())
	{
		strTidy.AppendFormat(_T("-ms%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_MERGE_SPANS))->GetCurSel());
	}
	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_SHOW_BODY_ONLY))->GetCurSel())
	{
		strTidy.AppendFormat(_T("-sbo%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_SHOW_BODY_ONLY))->GetCurSel());
	}
	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_DOCTYPE))->GetCurSel())
	{
		strTidy.AppendFormat(_T("-d%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_DOCTYPE))->GetCurSel());
	}
	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_REPEATED_ATTRIBUTES))->GetCurSel())
	{
		strTidy.AppendFormat(_T("-ra%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_REPEATED_ATTRIBUTES))->GetCurSel());
	}
	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_SORT_ATTRIBUTES))->GetCurSel())
	{
		strTidy.AppendFormat(_T("-sa%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_SORT_ATTRIBUTES))->GetCurSel());
	}
	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_CHAR_ENCODING))->GetCurSel())
	{
		strTidy.AppendFormat(_T("-ce%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_CHAR_ENCODING))->GetCurSel());
	}
	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_INPUT_ENCODING))->GetCurSel())
	{
		strTidy.AppendFormat(_T("-ie%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_INPUT_ENCODING))->GetCurSel());
	}
	if (CB_ERR != ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_OUTPUT_ENCODING))->GetCurSel())
	{
		strTidy.AppendFormat(_T("-oe%d"), ((CComboBox *)GetDlgItem(IDC_COMBO_HTML_OUTPUT_ENCODING))->GetCurSel());
	}

	CString strNothing;
	GetDlgItemText(IDC_EDIT_HTML_SHOW_ERRORS, strValue);
	strTidy.Append(_T("-se"));
	strTidy.Append(strValue);

	GetDlgItemText(IDC_EDIT_HTML_INDENT_SPACES, strValue);
	strTidy.Append(_T("-is"));
	strTidy.Append(strValue);

	GetDlgItemText(IDC_EDIT_HTML_TAB_SIZE, strValue);
	strTidy.Append(_T("-ts"));
	strTidy.Append(strValue);

	GetDlgItemText(IDC_EDIT_HTML_WRAP, strValue);
	strTidy.Append(_T("-w"));
	strTidy.Append(strValue);

	GetDlgItemText(IDC_EDIT_HTML_ALT_TEXT, strValue);
	{
		strTidy.Append(_T("-at"));
		m_onlyHtmlXml == SYN_HTML? g_GlobalTidy.m_TidyHtml_at = strValue:strNothing = strValue;
	}

	GetDlgItemText(IDC_EDIT_HTML_CSS_PREFIX, strValue);
	{
		strTidy.Append(_T("-cp"));
		m_onlyHtmlXml == SYN_HTML? g_GlobalTidy.m_TidyHtml_cp = strValue:strNothing = strValue;
	}

	GetDlgItemText(IDC_EDIT_HTML_NEW_BLOCKLEVEL_TAGS, strValue);
	{
		strTidy.Append(_T("-nbt"));
		m_onlyHtmlXml == SYN_HTML? g_GlobalTidy.m_TidyHtml_nbt = strValue:strNothing = strValue;
	}

	GetDlgItemText(IDC_EDIT_HTML_NEW_EMPTY_TAGS, strValue);
	{
		strTidy.Append(_T("-net"));
		m_onlyHtmlXml == SYN_HTML? g_GlobalTidy.m_TidyHtml_net = strValue:strNothing = strValue;
	}

	GetDlgItemText(IDC_EDIT_HTML_NEW_INLINE_TAGS, strValue);
	{
		strTidy.Append(_T("-nit"));
		m_onlyHtmlXml == SYN_HTML? g_GlobalTidy.m_TidyHtml_nit = strValue:strNothing = strValue;
	}

	GetDlgItemText(IDC_EDIT_HTML_NEW_PRE_TAGS, strValue);
	{
		strTidy.Append(_T("-npt"));
		m_onlyHtmlXml == SYN_HTML? g_GlobalTidy.m_TidyHtml_npt = strValue:strNothing = strValue;
	}

	strTidyValue.Append(strTidy);
}

void CSetPageHtmlTwo::SetTidyControl( LPCTSTR lpszTidy, int nPos, int nSize )
{
	if (lpszTidy[nPos] != '-' || nSize < 2)
	{
		return;
	}

	int nNumValue = nSize;
	for (int i = nPos + 1; i < nPos + nSize; ++i)
	{
		if (!_istalpha(lpszTidy[i]))
		{
			nNumValue = i - nPos;
			break;
		}
	}
	CString strParam(lpszTidy + nPos + 1, nNumValue - 1);
	if (nNumValue != nSize)
	{
		CString strNum(lpszTidy + nPos + nNumValue, nSize - nNumValue);
		nNumValue = _ttoi(strNum);
	}
	else
	{
		nNumValue = 0;
	}
	CString strNumValue;
	strNumValue.Format(_T("%d"), nNumValue);

	CString strNothing;
	strNothing.Empty();
	if (_T("bbb") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_HTML_BREAK_BEFORE_BR))->SetCheck(1);
	} 
	else if (_T("ia") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_HTML_INDENT_ATTRIBUTES))->SetCheck(1);
	}
	else if (_T("m") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_HTML_MARKUP))->SetCheck(1);
	}
	else if (_T("pw") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_HTML_PUNCTUATION_WRAP))->SetCheck(1);
	}
	else if (_T("vs") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_HTML_VERTICAL_SPACE))->SetCheck(1);
	}
	else if (_T("wa") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_HTML_WRAP_ASP))->SetCheck(1);
	}
	else if (_T("wat") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_HTML_WRAP_ATTRIBUTES))->SetCheck(1);
	}
	else if (_T("wj") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_HTML_WRAP_JSTE))->SetCheck(1);
	}
	else if (_T("wp") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_HTML_WRAP_PHP))->SetCheck(1);
	}
	else if (_T("wsl") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_HTML_WRAP_SCRIPT_LITERALS))->SetCheck(1);
	}
	else if (_T("ws") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_HTML_WRAP_SECTIONS))->SetCheck(1);
	}
	else if (_T("ac") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_HTML_ASCII_CHARS))->SetCheck(1);
	}
	else if (_T("sw") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_HTML_SHOW_WARNINGS))->SetCheck(1);
	}
	else if (_T("fo") == strParam)
	{
		((CButton *)GetDlgItem(IDC_CHECK_HTML_FORCE_OUTPUT))->SetCheck(1);
	}
	else if (_T("i") == strParam)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_HTML_INDENT))->SetCurSel(nNumValue);
	}
	else if (_T("md") == strParam)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_HTML_MERGE_DIVS))->SetCurSel(nNumValue);
	}
	else if (_T("ms") == strParam)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_HTML_MERGE_SPANS))->SetCurSel(nNumValue);
	}
	else if (_T("sbo") == strParam)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_HTML_SHOW_BODY_ONLY))->SetCurSel(nNumValue);
	}
	else if (_T("d") == strParam)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_HTML_DOCTYPE))->SetCurSel(nNumValue);
	}
	else if (_T("ra") == strParam)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_HTML_REPEATED_ATTRIBUTES))->SetCurSel(nNumValue);
	}
	else if (_T("sa") == strParam)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_HTML_SORT_ATTRIBUTES))->SetCurSel(nNumValue);
	}
	else if (_T("ce") == strParam)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_HTML_CHAR_ENCODING))->SetCurSel(nNumValue);
	}
	else if (_T("ie") == strParam)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_HTML_INPUT_ENCODING))->SetCurSel(nNumValue);
	}
	else if (_T("oe") == strParam)
	{
		((CComboBox *)GetDlgItem(IDC_COMBO_HTML_OUTPUT_ENCODING))->SetCurSel(nNumValue);
	}
	else if (_T("se") == strParam)
	{
		GetDlgItem(IDC_EDIT_HTML_SHOW_ERRORS)->SetWindowText(strNumValue);
	}
	else if (_T("is") == strParam)
	{
		GetDlgItem(IDC_EDIT_HTML_INDENT_SPACES)->SetWindowText(strNumValue);
	}
	else if (_T("ts") == strParam)
	{
		GetDlgItem(IDC_EDIT_HTML_TAB_SIZE)->SetWindowText(strNumValue);
	}
	else if (_T("w") == strParam)
	{
		GetDlgItem(IDC_EDIT_HTML_WRAP)->SetWindowText(strNumValue);
	}
	else if (_T("at") == strParam)
	{
		m_onlyHtmlXml == SYN_HTML? GetDlgItem(IDC_EDIT_HTML_ALT_TEXT)->SetWindowText(g_GlobalTidy.m_TidyHtml_at):GetDlgItem(IDC_EDIT_HTML_ALT_TEXT)->SetWindowText(strNothing);
	}
	else if (_T("cp") == strParam)
	{
		m_onlyHtmlXml == SYN_HTML? GetDlgItem(IDC_EDIT_HTML_ALT_TEXT)->SetWindowText(g_GlobalTidy.m_TidyHtml_cp):GetDlgItem(IDC_EDIT_HTML_ALT_TEXT)->SetWindowText(strNothing);
	}
	else if (_T("nbt") == strParam)
	{
		m_onlyHtmlXml == SYN_HTML? GetDlgItem(IDC_EDIT_HTML_ALT_TEXT)->SetWindowText(g_GlobalTidy.m_TidyHtml_nbt):GetDlgItem(IDC_EDIT_HTML_ALT_TEXT)->SetWindowText(strNothing);
	}
	else if (_T("net") == strParam)
	{
		m_onlyHtmlXml == SYN_HTML? GetDlgItem(IDC_EDIT_HTML_ALT_TEXT)->SetWindowText(g_GlobalTidy.m_TidyHtml_net):GetDlgItem(IDC_EDIT_HTML_ALT_TEXT)->SetWindowText(strNothing);
	}
	else if (_T("nit") == strParam)
	{
		m_onlyHtmlXml == SYN_HTML? GetDlgItem(IDC_EDIT_HTML_ALT_TEXT)->SetWindowText(g_GlobalTidy.m_TidyHtml_nit):GetDlgItem(IDC_EDIT_HTML_ALT_TEXT)->SetWindowText(strNothing);
	}
	else if (_T("npt") == strParam)
	{
		m_onlyHtmlXml == SYN_HTML? GetDlgItem(IDC_EDIT_HTML_ALT_TEXT)->SetWindowText(g_GlobalTidy.m_TidyHtml_npt):GetDlgItem(IDC_EDIT_HTML_ALT_TEXT)->SetWindowText(strNothing);
	}
}