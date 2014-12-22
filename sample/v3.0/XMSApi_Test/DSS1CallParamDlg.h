#if !defined(AFX_DSS1CALLPARAMDLG_H__A6EB0E47_B087_47C1_AAFC_45A80DD37241__INCLUDED_)
#define AFX_DSS1CALLPARAMDLG_H__A6EB0E47_B087_47C1_AAFC_45A80DD37241__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DSS1CallParamDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDSS1CallParamDlg dialog

class CDSS1CallParamDlg : public CDialog
{
// Construction
public:
	CDSS1CallParamDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDSS1CallParamDlg)
	enum { IDD = IDD_DIALOG_DSS1_CALL_PARAM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDSS1CallParamDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDSS1CallParamDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSS1CALLPARAMDLG_H__A6EB0E47_B087_47C1_AAFC_45A80DD37241__INCLUDED_)
