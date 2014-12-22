#if !defined(AFX_DLGIODATAUII_H__ACBF2B78_4C5F_4BC9_A27F_A9085C3E62FA__INCLUDED_)
#define AFX_DLGIODATAUII_H__ACBF2B78_4C5F_4BC9_A27F_A9085C3E62FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIODataUII.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIODataUII dialog

class CDlgIODataUII : public CDialog
{
// Construction
public:
	CDlgIODataUII(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIODataUII)
	enum { IDD = IDD_DLG_IODATA_UII };
	CString	m_sAlphanumeric;
	CString	m_sSignal;
	int		m_nUIIType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIODataUII)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIODataUII)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIODATAUII_H__ACBF2B78_4C5F_4BC9_A27F_A9085C3E62FA__INCLUDED_)
