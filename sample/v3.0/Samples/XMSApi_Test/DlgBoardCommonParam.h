#if !defined(AFX_DLGBOARDBOARDCOMMONPARAM_H__48FF27C6_FD40_4F70_A861_6788DC7D87E0__INCLUDED_)
#define AFX_DLGBOARDBOARDCOMMONPARAM_H__48FF27C6_FD40_4F70_A861_6788DC7D87E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBoardCommonParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBoardCommonParam dialog

class CDlgBoardCommonParam : public CDialog
{
// Construction
public:
	void DisplayControlX( void );
	CDlgBoardCommonParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBoardCommonParam)
	enum { IDD = IDD_DIALOG_BoardComParam };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBoardCommonParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBoardCommonParam)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioCngEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBOARDBOARDCOMMONPARAM_H__48FF27C6_FD40_4F70_A861_6788DC7D87E0__INCLUDED_)
