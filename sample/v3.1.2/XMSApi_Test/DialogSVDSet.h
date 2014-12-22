#if !defined(AFX_DIALOGSVDSET_H__54AAC42E_FC1A_48B5_A835_ECDF98495627__INCLUDED_)
#define AFX_DIALOGSVDSET_H__54AAC42E_FC1A_48B5_A835_ECDF98495627__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogSVDSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogSVDSet dialog

class CDialogSVDSet : public CDialog
{
// Construction
public:
	CDialogSVDSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogSVDSet)
	enum { IDD = IDD_DIALOG_VSD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogSVDSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogSVDSet)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSVDSET_H__54AAC42E_FC1A_48B5_A835_ECDF98495627__INCLUDED_)
