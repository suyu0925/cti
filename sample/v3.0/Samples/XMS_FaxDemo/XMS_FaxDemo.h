// XMS_FaxDemo.h : main header file for the XMS_FAXDEMO application
//

#if !defined(AFX_XMS_FAXDEMO_H__F31263EF_C354_4696_B6DA_BD93C7CB2B08__INCLUDED_)
#define AFX_XMS_FAXDEMO_H__F31263EF_C354_4696_B6DA_BD93C7CB2B08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXMS_FaxDemoApp:
// See XMS_FaxDemo.cpp for the implementation of this class
//

class CXMS_FaxDemoApp : public CWinApp
{
public:
	CXMS_FaxDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMS_FaxDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXMS_FaxDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMS_FAXDEMO_H__F31263EF_C354_4696_B6DA_BD93C7CB2B08__INCLUDED_)
