// DlgRegxEdit.cpp : implementation file
//

#include "stdafx.h"
#include "SplitChapters.h"
#include "DlgRegxEdit.h"


// CDlgRegxEdit dialog

IMPLEMENT_DYNAMIC(CDlgRegxEdit, CDialog)

CDlgRegxEdit::CDlgRegxEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRegxEdit::IDD, pParent)
	, m_strRegEx(_T(""))
{

}

CDlgRegxEdit::~CDlgRegxEdit()
{
}

void CDlgRegxEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strRegEx);
	DDX_Control(pDX, IDC_LISTREGX, m_RegxList);
}


BEGIN_MESSAGE_MAP(CDlgRegxEdit, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgRegxEdit::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgRegxEdit::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgRegxEdit message handlers

void CDlgRegxEdit::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CDlgRegxEdit::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

LPTSTR strItem[] = {
	_T("."), 
	_T("[ ]"), 
	_T("^"),
	_T("?"),
	_T("+"),
	_T("*"),
	_T("??,+?,*?"),
	_T("( )"),
	_T("{ }"),
	_T("\\"),
	_T("$"),
	_T("|"),
	_T("!"),
	_T("\\a"),
	_T("\\b"),
	_T("\\c"),
	_T("\\d"),
	_T("\\h"),
	_T("\\n"),
	_T("\\q"),
	_T("\\w"),
	_T("\\z"),
};

LPTSTR strContent[] = {
	_T("任意字元"),
	_T("字元組 [abc] = a, b, and c"),
	_T("在字首或是行首,[^abc] = a|b|c 開頭，若在正則式開頭則為行首"),
	_T("表示前面的字元/字元組出現 一次或0次"),
	_T("表示前面的字元/字元組必須出現 一次或多次"),
	_T("表示前面的字元/字元組出現 0次或多次"),
	_T("對?,+,* 指令尋找最少的符合項目，例如只找第一個符合的項目"),
	_T("將多個指令視為一個群組:如 (\\d+,)*\\d+ = 1 or 1,23,456"),
	_T("符合括號內規則的文字會被放入 CAtlREMatchContext 物件中"),
	_T("跳脫符號，如[0-9]\\+ 表示數字後跟著一個+,若\\後跟著數字n，表示要第n次符合的"),
	_T("放在正則式的最後，表示行尾要符合. [0-9]$ = 行尾須為數字"),
	_T("or 指令，放在2個規則中間，符合一個即可. T|the = The or the"),
	_T("not 指令，表示不能符合此規則. a!b = a 後面不能跟著 b"),
	_T("任何英數字: [a-zA-Z0-9]"),
	_T("White space (blank): [ \\\\t]"),
	_T("Any alphabetic character: [a-zA-Z]"),
	_T("任何數字: [0-9]"),
	_T("任何16進位數字: [0-9a-fA-F]"),
	_T("換行符號 (\\r|(\\r?\\n))"),
	_T("A quoted string: (\\\"[^\\\"]*\\\")|(\\'[^\\']*\\')"),
	_T("A simple word: [a-zA-Z]+"),
	_T("An integer: [0-9]+"),

};

BOOL CDlgRegxEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	LONG lStyle;
	lStyle = GetWindowLong(m_RegxList.m_hWnd, GWL_STYLE); 
	lStyle &= ~LVS_TYPEMASK; 
	lStyle |= LVS_REPORT; 
	SetWindowLong(m_RegxList.m_hWnd, GWL_STYLE, lStyle); 

    DWORD dwStyle = m_RegxList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
    dwStyle |= LVS_EX_GRIDLINES;
    m_RegxList.SetExtendedStyle(dwStyle);

	VERIFY(m_Font.CreateFont(
		16,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial"))               // lpszFacename
	);

	m_RegxList.SetFont(&m_Font);


	CRect rect;
	m_RegxList.GetClientRect(rect);

	m_RegxList.InsertColumn(0, _T("指令"), LVCFMT_LEFT, 66);
	m_RegxList.InsertColumn(1, _T("說明"), LVCFMT_LEFT, rect.Width()-66);

	int size = sizeof(strItem)/sizeof(LPTSTR);

	for(int i=0; i < size; i++ )
	{
		m_RegxList.InsertItem( i, strItem[i]);
		m_RegxList.SetItemText(i, 1, strContent[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
