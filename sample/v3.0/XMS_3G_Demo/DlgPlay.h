#if !defined(AFX_DLGPLAY_H__631D8460_50A6_43B4_926C_DBDD215EAC7E__INCLUDED_)
#define AFX_DLGPLAY_H__631D8460_50A6_43B4_926C_DBDD215EAC7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPlay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPlay dialog

class CDlgPlay : public CDialog
{
// Construction
public:
	int m_nPlayType;
	CDlgPlay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPlay)
	enum { IDD = IDD_DLG_PLAY };
	CComboBox	m_cmbType;
	UINT	m_uiTime;
	UINT	m_uiFps;
	UINT	m_uiBr;
	UINT	m_uiX;
	UINT	m_uiY;
	CString	m_sFile;
	CString	m_sFileOverlay;
	BOOL	m_bLoop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPlay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPlay)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButtonFile();
	afx_msg void OnButtonFileoverlay();
	afx_msg void OnSelchangeCmbType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPLAY_H__631D8460_50A6_43B4_926C_DBDD215EAC7E__INCLUDED_)
