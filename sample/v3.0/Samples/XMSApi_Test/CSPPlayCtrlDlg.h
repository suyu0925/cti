#if !defined(AFX_CSPPLAYCTRLDLG_H__BFE1E457_5D51_4A8B_89F6_931BABA4D364__INCLUDED_)
#define AFX_CSPPLAYCTRLDLG_H__BFE1E457_5D51_4A8B_89F6_931BABA4D364__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSPPlayCtrlDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCSPPlayCtrlDlg dialog

class CCSPPlayCtrlDlg : public CDialog
{
// Construction
public:
	CCSPPlayCtrlDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCSPPlayCtrlDlg)
	enum { IDD = IDD_DIALOG_CSPPLAY_CTRL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSPPlayCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCSPPlayCtrlDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSPPLAYCTRLDLG_H__BFE1E457_5D51_4A8B_89F6_931BABA4D364__INCLUDED_)
