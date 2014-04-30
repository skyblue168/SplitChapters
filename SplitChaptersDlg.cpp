// SplitChaptersDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SplitChapters.h"
#include "SplitChaptersDlg.h"
#include "DlgRegxEdit.h"

#include <Strsafe.h>
#include <atlrx.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CStringW ConvertUTF8ToUTF16( __in const CHAR * pszTextUTF8 );

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitChaptersDlg dialog

CSplitChaptersDlg::CSplitChaptersDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSplitChaptersDlg::IDD, pParent)
	, m_ChapLen(20)
	, m_TitleLen(100)
	, m_bFullChpName(TRUE)
	, m_edPgNums(1)
	, m_IsUTF8(FALSE)
	, m_IsUnicode(FALSE)
	, m_IsGB(FALSE)
	, m_IsFixLength(FALSE)
	, FIXPAGELENGTH(10240)
	, m_ChapBegin(_T("第"))
	, m_ChapEnd(_T("章"))
	, m_IsSameChap(TRUE)
	, m_IsNumChap(FALSE)
	, m_CurChapNum(0)
	, m_IsFirstKey(TRUE)
	, m_IsAddNo(FALSE)
	, m_RegxStr(_T(""))
{
	//{{AFX_DATA_INIT(CSplitChaptersDlg)
	m_FilePath = _T("");
	m_srcfp = NULL;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_curPageLen = 0;
}

void CSplitChaptersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplitChaptersDlg)
	DDX_Text(pDX, IDC_EDFILEPATH, m_FilePath);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDCHAPLEN, m_ChapLen);
	DDX_Text(pDX, IDC_EDTITLELEN, m_TitleLen);
	DDV_MinMaxInt(pDX, m_TitleLen, 2, 1000);
	DDX_Check(pDX, IDC_CHKCPNAME, m_bFullChpName);
	DDX_Text(pDX, IDC_EDPGNO, m_edPgNums);
	DDX_Check(pDX, IDC_CHKUTF8, m_IsUTF8);
	DDX_Check(pDX, IDC_CHKUNICODE, m_IsUnicode);
	DDX_Check(pDX, IDC_CHKGB, m_IsGB);
	DDX_Check(pDX, IDC_CHKFIXLENGTH, m_IsFixLength);
	DDX_Text(pDX, IDC_EDBEGIN, m_ChapBegin);
	DDV_MaxChars(pDX, m_ChapBegin, 1);
	DDX_Text(pDX, IDC_EDEND, m_ChapEnd);
	DDV_MaxChars(pDX, m_ChapEnd, 1);
	DDX_Check(pDX, IDC_CHKSAMECHAP, m_IsSameChap);
	DDX_Check(pDX, IDC_CK_CPNUM, m_IsNumChap);
	DDX_Check(pDX, IDC_CK_FSTKEY, m_IsFirstKey);
	DDX_Check(pDX, IDC_CK_AddNo, m_IsAddNo);
	DDX_Text(pDX, IDC_EDREGX, m_RegxStr);
}

BEGIN_MESSAGE_MAP(CSplitChaptersDlg, CDialog)
	//{{AFX_MSG_MAP(CSplitChaptersDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNBROWSE, OnBtnbrowse)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BNREGX, &CSplitChaptersDlg::OnBnClickedBnregx)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitChaptersDlg message handlers

BOOL CSplitChaptersDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSplitChaptersDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSplitChaptersDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSplitChaptersDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



CAtlRegExp<CAtlRECharTraitsW> reRule;

BOOL RegExpChapterLine(CString &strInput, CString &strRegex)
{
	BOOL rc = FALSE;

	CAtlREMatchContext<CAtlRECharTraitsW> mcRule;
	wchar_t *wt = (wchar_t *)(LPCTSTR)strInput;
	
	if( reRule.Match((const ATL::CAtlRegExp<CAtlRECharTraitsW>::RECHAR *)wt,&mcRule))
	{
		rc = TRUE;
	}

	return rc;
}

BOOL CSplitChaptersDlg::IsChapterLine(CString &sLine, CString &sChapter)
{
	static CString sPreLine = _T("");
	BOOL rc = FALSE;
	int cp1 = -1, cp2 = -1;
	int len;

	if(!m_RegxStr.IsEmpty())
	{
		sLine.TrimLeft(_T("\t "));
		sLine.TrimRight(_T("\t "));

		if(sLine.GetLength() < m_TitleLen) 
		{
			if( RegExpChapterLine(sLine, m_RegxStr) )
			{
				//if( !m_IsSameChap )
				{
					len = sLine.GetLength();
					if(len > 30 ) len = 30;
					sPreLine = sLine;
					sChapter = sLine.Left(len);

					rc = TRUE;
				}
			}
		}
		return rc;
	}
	else if(m_IsFixLength == TRUE)
	{
		sLine.TrimLeft();
		sLine.TrimRight();
		len = sLine.GetLength();
		
		if(m_curPageLen == 0 && len != 0){
			if(len > 30 ) len = 30;
			sChapter = sLine.Left(len);
			rc = TRUE;
		}

		m_curPageLen += len;

		if(m_curPageLen >= FIXPAGELENGTH){
			m_curPageLen = 0;
		}

		return rc;
	}
	else if(m_IsNumChap)
	{
		int cp = _ttoi(sLine);

		//if(cp > m_CurChapNum) 
		if(cp > 0) 
		{
			sLine.TrimLeft(_T("\t "));
			sLine.TrimRight(_T("\t "));
			len = sLine.GetLength();
			if(len > m_TitleLen ) len = m_TitleLen;
			sChapter = sLine.Left(len);

			m_CurChapNum = cp;
			rc = TRUE;
		}

		return rc;
	}

	cp1 = sLine.Find(m_ChapBegin);
	if(cp1 >= 0)
		cp2 = sLine.Find(m_ChapEnd, cp1);
	if( cp1 >=0 && (cp2 > cp1) && (cp2-cp1 < m_ChapLen) )
	{
		sLine.TrimLeft(_T("\t "));
		sLine.TrimRight(_T("\t "));
		cp1 = sLine.Find(m_ChapBegin);
		cp2 = sLine.Find(m_ChapEnd, cp1);

		if((!m_IsFirstKey || cp1 == 0) && (sLine.GetLength() < m_TitleLen))
		//if(sLine.GetLength() < m_TitleLen) 
		{
			if( !m_IsSameChap || (sPreLine.GetLength() < cp2) || (sPreLine.Left(cp2) != sLine.Left(cp2)) )
			{
				len = sLine.GetLength();
				if(len > 30 ) len = 30;
				sPreLine = sLine;
				sChapter = sLine.Left(len);

				rc = TRUE;
			}
		}
	}

	return rc;
}

BOOL CSplitChaptersDlg::readFile2Buf(FILE* in)
{
	BOOL rc = FALSE;
	int ret;

	if(in == NULL) return rc;

	m_ib.bufgrow(READ_UNIT);
	while ((ret = fread(m_ib.data + m_ib.size, 1, m_ib.asize - m_ib.size, in)) > 0) {
		m_ib.size += ret;
		m_ib.bufgrow(m_ib.size + READ_UNIT);
	}
	if(m_ib.isUTF8Head())
		m_IsUTF8 = TRUE;
	if(m_ib.size > 0)
		rc = TRUE;

	return rc;
}

FILE* CSplitChaptersDlg::openChapFile(FILE* fptag, int nChap)
{
	CString sChapFName;

	if(fptag != NULL){
		fclose(fptag);
		fptag = NULL;
	}

	if(!m_bFullChpName)
		sChapFName.Format( _T("%s\\%d.txt"), m_DirPath, nChap );
	else
		sChapFName.Format( _T("%s\\%04d.txt"), m_DirPath, nChap );

	//return _tfopen(sChapFName, _T("wt, ccs=UNICODE")); 
	return _tfopen(sChapFName, _T("wt"));	// modify to output utf-8 file
}

BOOL CSplitChaptersDlg::writeUTF8File(FILE* fp, const CString& unicode)
{
	if(fp == NULL) return FALSE;

	char* outb = NULL;
	int nLen = unicode.GetLength();

	int len = WideCharToMultiByte(CP_UTF8, 0, unicode, nLen, NULL, 0, NULL, NULL);

	try
	{
	outb = (char*)malloc(len+6);
	memset(outb, 0, sizeof(outb));
	int ret = WideCharToMultiByte(CP_UTF8, 0, unicode, nLen, (LPSTR)outb, len, NULL, NULL);
	outb[ret] = 0;
	
	fprintf(fp, "%s", outb);

	free(outb);
	}
	catch(...) {
	}

	return TRUE;
}

void CSplitChaptersDlg::OnOK() 
{
	// TODO: Add extra validation here
	//FILE *fp = NULL;
	FILE *fptag = NULL;
	FILE *fpMenu = NULL;
	CString sChapFName;
	CString stmp, sUnicode;
	CString sChapter;
	int nChap = 1;
	int nNowChap = 0;
	DWORD ptk, ntk;

	UpdateData();
	ptk = GetTickCount();

	if( !m_RegxStr.IsEmpty() )
	{
		wchar_t *wt = (wchar_t *)(LPCTSTR)m_RegxStr;
	    
		REParseError status = reRule.Parse((const ATL::CAtlRegExp<CAtlRECharTraitsW>::RECHAR *)wt);
	 
		if (REPARSE_ERROR_OK != status)
		{
			AfxMessageBox(_T("正則表達式語法錯誤!"));
			return;
		}
	}


	::CreateDirectory(m_DirPath, NULL);
	m_srcfp = _tfopen(m_FilePath, _T("rt"));

	if(m_srcfp == NULL) {
		AfxMessageBox(_T("開啟書檔失敗!"));
		return;
	}

	sChapFName.Format( _T("%s\\0.txt"), m_DirPath );
	//fpMenu = _tfopen(sChapFName, _T("wt, ccs=UNICODE"));
	fpMenu = _tfopen(sChapFName, _T("wt"));
	if(fpMenu == NULL) {
		AfxMessageBox(_T("開啟目錄檔失敗!"));
	}

	BeginWaitCursor();

	int pgcnt = 1;

	if( readFile2Buf(m_srcfp) ) {
	//	fptag = openChapFile(fptag, nChap);
	//	if(fptag != NULL){
	//		_ftprintf(fpMenu, _T("%04d %s\n"), nChap, stmp);
	//		nChap++;		// 目前章數加一
	//	}
	}
	else {
		AfxMessageBox(_T("Read File 失敗!"));
		return;
	}

	//while ( fgets(buf, sizeof(buf), m_srcfp) != NULL )
	while ( readUnicodeLine(stmp) == TRUE )
	{
		sUnicode.Empty();

		if(IsChapterLine(stmp, sChapter) == TRUE) 
		{
			if( pgcnt >= m_edPgNums )	//控制每幾個章節寫一個檔，預防產生太多檔案
			{
				pgcnt = 1;		
				fptag = openChapFile(fptag, nChap);
				if(fptag != NULL){
					sUnicode.Format(_T("%04d %s\n"), nChap, sChapter);
					//_ftprintf(fpMenu, _T("%04d %s\n"), nChap, sChapter);
					writeUTF8File(fpMenu, sUnicode);
					nNowChap = nChap++;		// 保留目前章數並將章數加一
				}
			}
			else
				pgcnt++;
		}

		if(fptag == NULL) {
			fptag = openChapFile(fptag, nChap);
			if(fptag != NULL){
				sUnicode.Format(_T("%04d %s\n"), nChap, stmp);
				//_ftprintf(fpMenu, _T("%04d %s\n"), nChap, stmp);
				writeUTF8File(fpMenu, sUnicode);
				nNowChap = nChap++;		// 保留目前章數並將章數加一
			}
		}

		if(fptag != NULL){
			if(nNowChap > 0 && m_IsAddNo) {
				sUnicode.Format(_T("%04d %s\n"), nNowChap, stmp);
				//_ftprintf(fptag, _T("%04d %s\n"), nNowChap, stmp);
			}
			else {
				sUnicode.Format(_T("%s\n"), stmp);
				//_ftprintf(fptag, _T("%s\n"), stmp);
			}

			writeUTF8File(fptag, sUnicode);
		}

		nNowChap = 0;
	}
	EndWaitCursor();

	if(fptag != NULL){
		fclose(fptag);
		fptag = NULL;

		ntk = GetTickCount();

		stmp.Format(_T("共分為 %d 章!!!\n %d sec"), nChap-1, (ntk-ptk)/1000);
		AfxMessageBox(stmp);
	}
	else
		AfxMessageBox( _T("分章失敗!"));

	if(fpMenu != NULL)
		fclose(fpMenu);

	fclose(m_srcfp);
	CDialog::OnOK();
}

BOOL CSplitChaptersDlg::readUnicodeLine(CString& str)
{
	BOOL rc = FALSE;
	char buf[4096];
	wchar_t wbuf[4096];

	if( m_ib.getLine((unsigned char*)buf, sizeof(buf)) != NULL)
	{
		if(m_IsUTF8 == TRUE) {
			str = ConvertUTF8ToUTF16(buf);
		}
		else if(m_IsUnicode == TRUE){
			str.Empty();
		}
		else {
			int elen = strlen(buf);
			if(elen > 1 && buf[elen-1] == 0x0a) buf[elen-1] = 0x00;

			ZeroMemory(wbuf, sizeof(wbuf));
			if(m_IsGB == TRUE){
				MultiByteToWideChar(936, 0, buf, -1, wbuf, sizeof(wbuf));
			}
			else {
				MultiByteToWideChar(950, 0, buf, -1, wbuf, sizeof(wbuf));
			}
			str = wbuf;
		}
		if(str.IsEmpty() == FALSE)
			rc = TRUE;
	}

	return rc;
}

void CSplitChaptersDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CSplitChaptersDlg::OnBtnbrowse() 
{
	// TODO: Add your control notification handler code here
	static TCHAR BASED_CODE szFilter[] = _T("TXT Files (*.txt)|*.txt|All Files(*.*)|*.*||");
	CFileDialog fdlg(TRUE, _T("txt"), _T("*.txt"), OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST, szFilter);	

	if(fdlg.DoModal() != IDOK)
		return;
	m_FilePath = fdlg.GetPathName();
	UpdateData(FALSE);

	int i = m_FilePath.ReverseFind(_T('\\'));
	m_DirPath = m_FilePath.Left(i);
	
	m_DirPath += _T("\\txtsrc");
}


//----------------------------------------------------------------------------
// FUNCTION: ConvertUTF8ToUTF16
// DESC: Converts Unicode UTF-8 text to Unicode UTF-16 (Windows default).
//----------------------------------------------------------------------------
CStringW ConvertUTF8ToUTF16( __in const CHAR * pszTextUTF8 )
{
    //
    // Special case of NULL or empty input string
    //
    if ( (pszTextUTF8 == NULL) || (*pszTextUTF8 == '\0') )
    {
        // Return empty string
        return L"";
    }
 
 
    //
    // Consider CHAR's count corresponding to total input string length,
    // including end-of-string (\0) character
    //
    const size_t cchUTF8Max = INT_MAX - 1;
    size_t cchUTF8;
    HRESULT hr = ::StringCchLengthA( pszTextUTF8, cchUTF8Max, &cchUTF8 );
    if ( FAILED( hr ) )
    {
        AtlThrow( hr );
    }
   
    // Consider also terminating \0
    ++cchUTF8;
 
    // Convert to 'int' for use with MultiByteToWideChar API
    int cbUTF8 = static_cast<int>( cchUTF8 );
 
 
    //
    // Get size of destination UTF-16 buffer, in WCHAR's
    //
    int cchUTF16 = ::MultiByteToWideChar(
        CP_UTF8,                // convert from UTF-8
        MB_ERR_INVALID_CHARS,   // error on invalid chars
        pszTextUTF8,            // source UTF-8 string
        cbUTF8,                 // total length of source UTF-8 string,
                                // in CHAR's (= bytes), including end-of-string \0
        NULL,                   // unused - no conversion done in this step
        0                       // request size of destination buffer, in WCHAR's
        );
    //ATLASSERT( cchUTF16 != 0 );
    if ( cchUTF16 == 0 )
    {
        AtlThrowLastWin32();
    }
 
 
    //
    // Allocate destination buffer to store UTF-16 string
    //
    CStringW strUTF16;
    WCHAR * pszUTF16 = strUTF16.GetBuffer( cchUTF16 );
 
    //
    // Do the conversion from UTF-8 to UTF-16
    //
    int result = ::MultiByteToWideChar(
        CP_UTF8,                // convert from UTF-8
        MB_ERR_INVALID_CHARS,   // error on invalid chars
        pszTextUTF8,            // source UTF-8 string
        cbUTF8,                 // total length of source UTF-8 string,
                                // in CHAR's (= bytes), including end-of-string \0
        pszUTF16,               // destination buffer
        cchUTF16                // size of destination buffer, in WCHAR's
        );
    //ATLASSERT( result != 0 );
    if ( result == 0 )
    {
        AtlThrowLastWin32();
    }
 
    // Release internal CString buffer
    strUTF16.ReleaseBuffer();
 
    // Return resulting UTF16 string
    return strUTF16;
}

void CSplitChaptersDlg::OnBnClickedBnregx()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CDlgRegxEdit dlg;

	dlg.m_strRegEx = m_RegxStr;

	if( dlg.DoModal() == IDOK ) {
		m_RegxStr = dlg.m_strRegEx;
		UpdateData(FALSE);
	}
	
}
