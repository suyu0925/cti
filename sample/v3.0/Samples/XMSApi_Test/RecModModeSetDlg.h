#if !defined(AFX_RECMODMODESETDLG_H__672A996F_AB3B_4D61_9A79_A43CEC34925E__INCLUDED_)
#define AFX_RECMODMODESETDLG_H__672A996F_AB3B_4D61_9A79_A43CEC34925E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RecModModeSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRecModModeSetDlg dialog

class CRecModModeSetDlg : public CDialog
{
// Construction
public:
	CRecModModeSetDlg(CWnd* pParent = NULL);   // standard constructor
	void ShowDefWindow( bool bVal );
	void GetConfig( );
	void SetConfig( );

// Dialog Data
	//{{AFX_DATA(CRecModModeSetDlg)
	enum { IDD = IDD_DIALOG_REC_MOD_MODE_SET };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecModModeSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRecModModeSetDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRadioRdmsEnable();
	afx_msg void OnRADIORDMSDisable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECMODMODESETDLG_H__672A996F_AB3B_4D61_9A79_A43CEC34925E__INCLUDED_)
