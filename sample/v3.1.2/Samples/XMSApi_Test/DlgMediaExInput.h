#if !defined(AFX_DLGMEDIAEXINPUT_H__33B64534_DD32_419B_A431_72AD555AC1D6__INCLUDED_)
#define AFX_DLGMEDIAEXINPUT_H__33B64534_DD32_419B_A431_72AD555AC1D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMediaExInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMediaExInput dialog

class CDlgMediaExInput : public CDialog
{
// Construction
public:
	UINT m_uiMedia;
	CDlgMediaExInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMediaExInput)
	enum { IDD = IDD_DLG_MEDIAEX_INPUT };
	CComboBox	m_cbMT;
	UINT	m_uiLevel;
	UINT	m_uiPort;
	UINT	m_uiPT;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMediaExInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMediaExInput)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMEDIAEXINPUT_H__33B64534_DD32_419B_A431_72AD555AC1D6__INCLUDED_)
