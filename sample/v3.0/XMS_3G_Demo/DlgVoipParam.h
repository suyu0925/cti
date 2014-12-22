#if !defined(AFX_DLGVOIPPARAM_H__DC84E8E5_A2AE_4D59_856D_43999BEA20A9__INCLUDED_)
#define AFX_DLGVOIPPARAM_H__DC84E8E5_A2AE_4D59_856D_43999BEA20A9__INCLUDED_

#include "DlgMixer.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVoipParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVoipParam dialog

class CDlgVoipParam : public CDialog
{
// Construction
public:
	CDlgMixer m_DlgMixer;
	CDlgVoipParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVoipParam)
	enum { IDD = IDD_DLG_VOIPPARAM };
	CTabCtrl	m_TabCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVoipParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVoipParam)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVOIPPARAM_H__DC84E8E5_A2AE_4D59_856D_43999BEA20A9__INCLUDED_)
