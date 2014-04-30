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
	int m_ChapLen;		// ���`�e������r�������\���סA�קK�~�P
	int m_TitleLen;		// ���`�t���D�W�٪����\���סA�קK�~�P

	BOOL IsChapterLine(CString &sLine, CString &sChapter);
	BOOL readUnicodeLine(CString &str);
	
	
	BOOL m_bFullChpName;	// �P�_�C�ӳ��`���ɮצW�٬O�_�n�ɺ�4��ƪ��ɦW

	
	int m_edPgNums;		// �]�w�h�ֳ��X���@����
	BOOL m_IsUTF8;
	BOOL m_IsUnicode;
	BOOL m_IsGB;

	// �L�k���X���`�ɡA�H�T�w���פ����`
	BOOL m_IsFixLength;
	CString m_ChapBegin;
	CString m_ChapEnd;
	BOOL m_IsSameChap;

	BOOL m_IsNumChap;		// �O�_���Ʀr���`
	UINT m_CurChapNum;		// �O���ثe�����`��
	BOOL m_IsFirstKey;		// �O�_���w���r�����`����r
	BOOL m_IsAddNo;
	CString m_RegxStr;
	afx_msg void OnBnClickedBnregx();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITCHAPTERSDLG_H__FEC5F8A0_5BFA_444E_8575_973AB8488F1A__INCLUDED_)
