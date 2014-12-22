#if !defined(AFX_DLGRECORD_H__2A07143D_BCC6_4563_B792_14A310C88CF4__INCLUDED_)
#define AFX_DLGRECORD_H__2A07143D_BCC6_4563_B792_14A310C88CF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRecord.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRecord dialog

class CDlgRecord : public CDialog
{
// Construction
public:
	int m_nRecType;
	CDlgRecord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRecord)
	enum { IDD = IDD_DLG_RECORD };
	CComboBox	m_cmbType;
	UINT	m_uiBR;
	CString	m_sFile;
	UINT	m_uiFps;
	UINT	m_uiX;
	UINT	m_uiY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRecord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRecord)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonFile();
	virtual void OnOK();
	afx_msg void OnSelchangeCmbType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRECORD_H__2A07143D_BCC6_4563_B792_14A310C88CF4__INCLUDED_)
