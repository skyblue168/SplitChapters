// SplitChaptersDlg.h : header file
//

#if !defined(AFX_SPLITCHAPTERSDLG_H__FEC5F8A0_5BFA_444E_8575_973AB8488F1A__INCLUDED_)
#define AFX_SPLITCHAPTERSDLG_H__FEC5F8A0_5BFA_444E_8575_973AB8488F1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Utfbuf.h"

/////////////////////////////////////////////////////////////////////////////
// CSplitChaptersDlg dialog

class CSplitChaptersDlg : public CDialog
{
public:
	const int FIXPAGELENGTH;
	int m_curPageLen;
	CString m_DirPath;
	FILE *	m_srcfp;

	CUtfbuf m_ib;


public:
	BOOL readFile2Buf(FILE* in);
	FILE* openChapFile(FILE* fptag, int nChap);
	BOOL writeUTF8File(FILE* fp, const CString& sLine);


// Construction
public:
	CSplitChaptersDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSplitChaptersDlg)
	enum { IDD = IDD_SPLITCHAPTERS_DIALOG };
	CString	m_FilePath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitChaptersDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSplitChaptersDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBtnbrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int m_ChapLen;		// 章節前後關鍵字間的允許長度，避免誤判
	int m_TitleLen;		// 章節含標題名稱的允許長度，避免誤判

	BOOL IsChapterLine(CString &sLine, CString &sChapter);
	BOOL readUnicodeLine(CString &str);
	
	
	BOOL m_bFullChpName;	// 判斷每個章節的檔案名稱是否要補滿4位數的檔名

	
	int m_edPgNums;		// 設定多少章合成一個檔
	BOOL m_IsUTF8;
	BOOL m_IsUnicode;
	BOOL m_IsGB;

	// 無法分出章節時，以固定長度分章節
	BOOL m_IsFixLength;
	CString m_ChapBegin;
	CString m_ChapEnd;
	BOOL m_IsSameChap;

	BOOL m_IsNumChap;		// 是否為數字章節
	UINT m_CurChapNum;		// 記錄目前的章節數
	BOOL m_IsFirstKey;		// 是否限定首字為章節關鍵字
	BOOL m_IsAddNo;
	CString m_RegxStr;
	afx_msg void OnBnClickedBnregx();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITCHAPTERSDLG_H__FEC5F8A0_5BFA_444E_8575_973AB8488F1A__INCLUDED_)
