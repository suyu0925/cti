#if !defined(AFX_CONFPARASETDLG_H__58413247_4FF9_4571_A454_10AF5E0DEF63__INCLUDED_)
#define AFX_CONFPARASETDLG_H__58413247_4FF9_4571_A454_10AF5E0DEF63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfParaSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfParaSetDlg dialog

class CConfParaSetDlg : public CDialog
{
// Construction
public:
	CConfParaSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfParaSetDlg)
	enum { IDD = IDD_DIALOG_CONF_PARAM_SET };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfParaSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfParaSetDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFPARASETDLG_H__58413247_4FF9_4571_A454_10AF5E0DEF63__INCLUDED_)
