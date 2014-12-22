#if !defined(AFX_DLGUSERREADXMSBOARDINFO_H__BD90104B_F5EE_41EA_B2FE_0BB8A9F718AA__INCLUDED_)
#define AFX_DLGUSERREADXMSBOARDINFO_H__BD90104B_F5EE_41EA_B2FE_0BB8A9F718AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUserReadXmsBoardInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUserReadXmsBoardInfo dialog

class CDlgUserReadXmsBoardInfo : public CDialog
{
// Construction
public:
	CDlgUserReadXmsBoardInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgUserReadXmsBoardInfo)
	enum { IDD = IDD_USERREADXMSBOARD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUserReadXmsBoardInfo)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUserReadXmsBoardInfo)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUSERREADXMSBOARDINFO_H__BD90104B_F5EE_41EA_B2FE_0BB8A9F718AA__INCLUDED_)
