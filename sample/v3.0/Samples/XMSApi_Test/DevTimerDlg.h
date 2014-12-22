#if !defined(AFX_DEVTIMERDLG_H__4BB8C697_5565_4072_A86A_C015F3823F3C__INCLUDED_)
#define AFX_DEVTIMERDLG_H__4BB8C697_5565_4072_A86A_C015F3823F3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DevTimerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDevTimerDlg dialog

class CDevTimerDlg : public CDialog
{
// Construction
public:
	CDevTimerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDevTimerDlg)
	enum { IDD = IDD_DIALOG_DEV_TIMER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDevTimerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDevTimerDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEVTIMERDLG_H__4BB8C697_5565_4072_A86A_C015F3823F3C__INCLUDED_)
