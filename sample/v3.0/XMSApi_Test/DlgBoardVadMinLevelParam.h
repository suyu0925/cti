#if !defined(AFX_DLGBOARDVADMINLEVELPARAM_H__0A716AB6_6852_49EE_B8E8_60D87C942018__INCLUDED_)
#define AFX_DLGBOARDVADMINLEVELPARAM_H__0A716AB6_6852_49EE_B8E8_60D87C942018__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBoardVadMinLevelParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBoardVadMinLevelParam dialog

class CDlgBoardVadMinLevelParam : public CDialog
{
// Construction
public:
	CDlgBoardVadMinLevelParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBoardVadMinLevelParam)
	enum { IDD = IDD_DIALOG_BRD_VAD_MIN_LEVEL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBoardVadMinLevelParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBoardVadMinLevelParam)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBOARDVADMINLEVELPARAM_H__0A716AB6_6852_49EE_B8E8_60D87C942018__INCLUDED_)
