// XMSVoIPDemo.h : main header file for the XMSVOIPDEMO application
//

#if !defined(AFX_XMSVOIPDEMO_H__287C8140_D140_4672_A4B4_7B41C9E17323__INCLUDED_)
#define AFX_XMSVOIPDEMO_H__287C8140_D140_4672_A4B4_7B41C9E17323__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXMSVoIPDemoApp:
// See XMSVoIPDemo.cpp for the implementation of this class
//

class CXMSVoIPDemoApp : public CWinApp
{
public:
	CXMSVoIPDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMSVoIPDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXMSVoIPDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMSVOIPDEMO_H__287C8140_D140_4672_A4B4_7B41C9E17323__INCLUDED_)
