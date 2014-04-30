#pragma once
#include "afxcmn.h"


// CDlgRegxEdit dialog

class CDlgRegxEdit : public CDialog
{
	DECLARE_DYNAMIC(CDlgRegxEdit)

public:
	CDlgRegxEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRegxEdit();

// Dialog Data
	enum { IDD = IDD_DLGREGX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

	CFont m_Font;
	CString m_strRegEx;
	CListCtrl m_RegxList;
	virtual BOOL OnInitDialog();
};
