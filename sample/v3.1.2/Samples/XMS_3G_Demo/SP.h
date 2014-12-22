// SP.h : main header file for the SP application
//

#if !defined(AFX_SP_H__E7BC7BD0_AB0D_43EF_81DC_35705E00C8C4__INCLUDED_)
#define AFX_SP_H__E7BC7BD0_AB0D_43EF_81DC_35705E00C8C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSPApp:
// See SP.cpp for the implementation of this class
//

class CSPApp : public CWinApp
{
public:
	CSPApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSPApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSPApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CSPApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SP_H__E7BC7BD0_AB0D_43EF_81DC_35705E00C8C4__INCLUDED_)
