#if !defined(AFX_DLGSIPCALLPARAM_H__19618725_E849_4042_A4D7_9842B7B6CECE__INCLUDED_)
#define AFX_DLGSIPCALLPARAM_H__19618725_E849_4042_A4D7_9842B7B6CECE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSipCallParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSipCallParam dialog

class CDlgSipCallParam : public CDialog
{
// Construction
public:
	CDlgSipCallParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSipCallParam)
	enum { IDD = IDD_DLG_SIP_CALLOUT };
	CString	m_sCalleeAddr;
	CString	m_sCalleeID;
	CString	m_sCalleeName;
	UINT	m_uiCalleePort;
	CString	m_sCallerAddr;
	CString	m_sCallerID;
	CString	m_sCallerName;
	UINT	m_uiCallerPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSipCallParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSipCallParam)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSIPCALLPARAM_H__19618725_E849_4042_A4D7_9842B7B6CECE__INCLUDED_)
