#if !defined(AFX_LEDDLG_H__CF010F37_5E00_48B9_AAA0_1D8B1513A8F1__INCLUDED_)
#define AFX_LEDDLG_H__CF010F37_5E00_48B9_AAA0_1D8B1513A8F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LedDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLedDlg dialog

class CLedDlg : public CDialog
{
// Construction
public:
	CLedDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLedDlg)
	enum { IDD = IDD_DIALOG_LED_CTRL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLedDlg)
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEDDLG_H__CF010F37_5E00_48B9_AAA0_1D8B1513A8F1__INCLUDED_)
