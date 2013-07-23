// SplitChapters.h : main header file for the SPLITCHAPTERS application
//

#if !defined(AFX_SPLITCHAPTERS_H__C3FFDAAC_503A_4407_A390_0B99CB961840__INCLUDED_)
#define AFX_SPLITCHAPTERS_H__C3FFDAAC_503A_4407_A390_0B99CB961840__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSplitChaptersApp:
// See SplitChapters.cpp for the implementation of this class
//

class CSplitChaptersApp : public CWinApp
{
public:
	CSplitChaptersApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitChaptersApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSplitChaptersApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITCHAPTERS_H__C3FFDAAC_503A_4407_A390_0B99CB961840__INCLUDED_)
