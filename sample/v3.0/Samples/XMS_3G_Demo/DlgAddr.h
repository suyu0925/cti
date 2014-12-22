#if !defined(AFX_DLGADDR_H__8E5F4ABA_3B0E_4071_AB7C_D99D705C563B__INCLUDED_)
#define AFX_DLGADDR_H__8E5F4ABA_3B0E_4071_AB7C_D99D705C563B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAddr dialog

class CDlgAddr : public CDialog
{
// Construction
public:
	DWORD m_uiIP;
	CDlgAddr(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAddr)
	enum { IDD = IDD_DLG_ADDR };
	CIPAddressCtrl	m_IP;
	UINT	m_Port;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAddr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAddr)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDR_H__8E5F4ABA_3B0E_4071_AB7C_D99D705C563B__INCLUDED_)
