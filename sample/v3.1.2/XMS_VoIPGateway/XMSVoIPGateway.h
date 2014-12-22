// XMSVoIPGateway.h : main header file for the XMSIPGATEWAY application
//

#if !defined(AFX_XMSVOIPGATEWAY_H__F259822C_C9F3_4DE9_BAF0_813B452D2B10__INCLUDED_)
#define AFX_XMSVOIPGATEWAY_H__F259822C_C9F3_4DE9_BAF0_813B452D2B10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXMSVoIPGatewayApp:
// See XMSVoIPGateway.cpp for the implementation of this class
//

class CXMSVoIPGatewayApp : public CWinApp
{
public:
	CXMSVoIPGatewayApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMSVoIPGatewayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXMSVoIPGatewayApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMSVOIPGATEWAY_H__F259822C_C9F3_4DE9_BAF0_813B452D2B10__INCLUDED_)
