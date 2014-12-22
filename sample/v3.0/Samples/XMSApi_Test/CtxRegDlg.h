#if !defined(AFX_CTXREGDLG_H__1DBBBCB4_5515_4918_B146_7A916B8D97E4__INCLUDED_)
#define AFX_CTXREGDLG_H__1DBBBCB4_5515_4918_B146_7A916B8D97E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CtxRegDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCtxRegDlg dialog

class CCtxRegDlg : public CDialog
{
// Construction
public:
	CCtxRegDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCtxRegDlg)
	enum { IDD = IDD_DIALOG_CTX_Register };
	CEdit	m_RegName;
	CComboBox	m_RegType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCtxRegDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCtxRegDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnExcute();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTXREGDLG_H__1DBBBCB4_5515_4918_B146_7A916B8D97E4__INCLUDED_)
