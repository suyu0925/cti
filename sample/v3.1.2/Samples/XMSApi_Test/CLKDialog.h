#if !defined(AFX_CLKDIALOG_H__A246253E_C7DC_4AE8_9252_03A6DA4242E7__INCLUDED_)
#define AFX_CLKDIALOG_H__A246253E_C7DC_4AE8_9252_03A6DA4242E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CLKDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCLKDialog dialog

class CCLKDialog : public CDialog
{
// Construction
public:
	CCLKDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCLKDialog)
	enum { IDD = IDD_CLKDIALOG };
	CComboBox	m_NetComBo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCLKDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCLKDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLKDIALOG_H__A246253E_C7DC_4AE8_9252_03A6DA4242E7__INCLUDED_)
