#if !defined(AFX_DIALOGATRUNKEM_H__74E233DD_56AF_4CBD_8F18_04781318861F__INCLUDED_)
#define AFX_DIALOGATRUNKEM_H__74E233DD_56AF_4CBD_8F18_04781318861F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogAtrunkEM.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DialogAtrunkEM dialog

class DialogAtrunkEM : public CDialog
{
// Construction
public:
	DialogAtrunkEM(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DialogAtrunkEM)
	enum { IDD = IDD_DIALOG_PARAM_ATRUNKEM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DialogAtrunkEM)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DialogAtrunkEM)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGATRUNKEM_H__74E233DD_56AF_4CBD_8F18_04781318861F__INCLUDED_)
