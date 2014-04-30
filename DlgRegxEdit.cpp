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
	_T("���N�r��"),
	_T("�r���� [abc] = a, b, and c"),
	_T("�b�r���άO�歺,[^abc] = a|b|c �}�Y�A�Y�b���h���}�Y�h���歺"),
	_T("��ܫe�����r��/�r���եX�{ �@����0��"),
	_T("��ܫe�����r��/�r���ե����X�{ �@���Φh��"),
	_T("��ܫe�����r��/�r���եX�{ 0���Φh��"),
	_T("��?,+,* ���O�M��̤֪��ŦX���ءA�Ҧp�u��Ĥ@�ӲŦX������"),
	_T("�N�h�ӫ��O�����@�Ӹs��:�p (\\d+,)*\\d+ = 1 or 1,23,456"),
	_T("�ŦX�A�����W�h����r�|�Q��J CAtlREMatchContext ����"),
	_T("����Ÿ��A�p[0-9]\\+ ��ܼƦr���ۤ@��+,�Y\\���ۼƦrn�A��ܭn��n���ŦX��"),
	_T("��b���h�����̫�A��ܦ���n�ŦX. [0-9]$ = ��������Ʀr"),
	_T("or ���O�A��b2�ӳW�h�����A�ŦX�@�ӧY�i. T|the = The or the"),
	_T("not ���O�A��ܤ���ŦX���W�h. a!b = a �᭱������ b"),
	_T("����^�Ʀr: [a-zA-Z0-9]"),
	_T("White space (blank): [ \\\\t]"),
	_T("Any alphabetic character: [a-zA-Z]"),
	_T("����Ʀr: [0-9]"),
	_T("����16�i��Ʀr: [0-9a-fA-F]"),
	_T("����Ÿ� (\\r|(\\r?\\n))"),
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

	m_RegxList.InsertColumn(0, _T("���O"), LVCFMT_LEFT, 66);
	m_RegxList.InsertColumn(1, _T("����"), LVCFMT_LEFT, rect.Width()-66);

	int size = sizeof(strItem)/sizeof(LPTSTR);

	for(int i=0; i < size; i++ )
	{
		m_RegxList.InsertItem( i, strItem[i]);
		m_RegxList.SetItemText(i, 1, strContent[i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
