// XMS_VoIPServer.h : main header file for the XMS_VOIPSERVER application
//

#if !defined(AFX_XMS_VOIPSERVER_H__4288D1E5_B86B_4B84_B48F_4B2EBE7F8D97__INCLUDED_)
#define AFX_XMS_VOIPSERVER_H__4288D1E5_B86B_4B84_B48F_4B2EBE7F8D97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXMS_VoIPServerApp:
// See XMS_VoIPServer.cpp for the implementation of this class
//

class CXMS_VoIPServerApp : public CWinApp
{
public:
	CXMS_VoIPServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMS_VoIPServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXMS_VoIPServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMS_VOIPSERVER_H__4288D1E5_B86B_4B84_B48F_4B2EBE7F8D97__INCLUDED_)
