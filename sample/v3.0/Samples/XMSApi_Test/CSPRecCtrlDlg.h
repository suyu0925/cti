#if !defined(AFX_CSPRECCTRLDLG_H__6B260447_5490_41C2_8A9B_838CFF7A53DB__INCLUDED_)
#define AFX_CSPRECCTRLDLG_H__6B260447_5490_41C2_8A9B_838CFF7A53DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CSPRecCtrlDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCSPRecCtrlDlg dialog

class CCSPRecCtrlDlg : public CDialog
{
// Construction
public:
	CCSPRecCtrlDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCSPRecCtrlDlg)
	enum { IDD = IDD_DIALOG_CSPREC_CTRL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSPRecCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCSPRecCtrlDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSPRECCTRLDLG_H__6B260447_5490_41C2_8A9B_838CFF7A53DB__INCLUDED_)
