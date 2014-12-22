#if !defined(AFX_DLGMEDIAEXOUTPUT_H__A1721295_1983_4B15_B823_10014F53135E__INCLUDED_)
#define AFX_DLGMEDIAEXOUTPUT_H__A1721295_1983_4B15_B823_10014F53135E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMediaExOutput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMediaExOutput dialog

class CDlgMediaExOutput : public CDialog
{
// Construction
public:
	UINT m_uiMedia;
	CDlgMediaExOutput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMediaExOutput)
	enum { IDD = IDD_DLG_MEDIAEX_OUTPUT };
	CComboBox	m_cbMT;
	UINT	m_uiFPS;
	CString	m_sIP;
	UINT	m_uiKbps;
	UINT	m_uiPort;
	UINT	m_uiPT;
	UINT	m_uiX;
	UINT	m_uiY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMediaExOutput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMediaExOutput)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMEDIAEXOUTPUT_H__A1721295_1983_4B15_B823_10014F53135E__INCLUDED_)
