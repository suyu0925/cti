#if !defined(AFX_DIALOGUSERREADXMSBOARDINFO_H__73A49B97_8D28_47BD_9EE7_5CACB3655353__INCLUDED_)
#define AFX_DIALOGUSERREADXMSBOARDINFO_H__73A49B97_8D28_47BD_9EE7_5CACB3655353__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogUserReadXmsBoardInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogUserReadXmsBoardInfo dialog

class CDialogUserReadXmsBoardInfo : public CDialog
{
// Construction
public:
	CDialogUserReadXmsBoardInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogUserReadXmsBoardInfo)
	enum { IDD = IDD_DIALOG_SENDIODATA };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogUserReadXmsBoardInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogUserReadXmsBoardInfo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGUSERREADXMSBOARDINFO_H__73A49B97_8D28_47BD_9EE7_5CACB3655353__INCLUDED_)
