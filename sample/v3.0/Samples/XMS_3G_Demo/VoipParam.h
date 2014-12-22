#if !defined(AFX_VOIPPARAM_H__72063C94_648D_4304_8054_C9B9443FB6CC__INCLUDED_)
#define AFX_VOIPPARAM_H__72063C94_648D_4304_8054_C9B9443FB6CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VoipParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// VoipParam dialog

class VoipParam : public CDialog
{
// Construction
public:
	VoipParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(VoipParam)
	enum { IDD = IDD_DLG_VOIP_PARAM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(VoipParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(VoipParam)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOIPPARAM_H__72063C94_648D_4304_8054_C9B9443FB6CC__INCLUDED_)
