#if !defined(AFX_DIALOGGTD_H__0DF1F518_DEFE_46F9_884C_DF328C268269__INCLUDED_)
#define AFX_DIALOGGTD_H__0DF1F518_DEFE_46F9_884C_DF328C268269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogGTD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogGTD dialog

class CDialogGTD : public CDialog
{
// Construction
public:
	CDialogGTD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogGTD)
	enum { IDD = IDD_DIALOG_GTD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogGTD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogGTD)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGGTD_H__0DF1F518_DEFE_46F9_884C_DF328C268269__INCLUDED_)
