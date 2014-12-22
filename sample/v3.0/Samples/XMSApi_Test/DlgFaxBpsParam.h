#if !defined(AFX_DLGFAXBPSPARAM_H__7F35EC69_C4B6_44D1_BC24_2AE8B5D657BA__INCLUDED_)
#define AFX_DLGFAXBPSPARAM_H__7F35EC69_C4B6_44D1_BC24_2AE8B5D657BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFaxBpsParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFaxBpsParam dialog

class CDlgFaxBpsParam : public CDialog
{
// Construction
public:
	CDlgFaxBpsParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFaxBpsParam)
	enum { IDD = IDD_DIALOG_FAX_BPS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFaxBpsParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFaxBpsParam)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFAXBPSPARAM_H__7F35EC69_C4B6_44D1_BC24_2AE8B5D657BA__INCLUDED_)
