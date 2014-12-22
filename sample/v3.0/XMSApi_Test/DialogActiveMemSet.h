#if !defined(AFX_DIALOGACTIVEMEMSET_H__6E4412B8_3584_4A82_A7A2_04F9A8A16F35__INCLUDED_)
#define AFX_DIALOGACTIVEMEMSET_H__6E4412B8_3584_4A82_A7A2_04F9A8A16F35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogActiveMemSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogActiveMemSet dialog

class CDialogActiveMemSet : public CDialog
{
// Construction
public:
	CDialogActiveMemSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogActiveMemSet)
	enum { IDD = IDD_DIALOG_ACTIVE_MEM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogActiveMemSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogActiveMemSet)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGACTIVEMEMSET_H__6E4412B8_3584_4A82_A7A2_04F9A8A16F35__INCLUDED_)
