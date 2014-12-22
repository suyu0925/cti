#if !defined(AFX_DLGLINKDEV_H__F9B16EE5_7695_41B3_B4A5_6C9B98A8643C__INCLUDED_)
#define AFX_DLGLINKDEV_H__F9B16EE5_7695_41B3_B4A5_6C9B98A8643C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLinkDev.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLinkDev dialog

class CDlgLinkDev : public CDialog
{
// Construction
public:
	int m_iType;
	int m_iDestType;
	CDlgLinkDev(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLinkDev)
	enum { IDD = IDD_DLG_LINKDEV };
	CComboBox	m_cmbDestType;
	UINT	m_uiDestID;
	UINT	m_uiUnit;
	CString	m_sOverlayFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLinkDev)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLinkDev)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonOpenfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLINKDEV_H__F9B16EE5_7695_41B3_B4A5_6C9B98A8643C__INCLUDED_)
