#if !defined(AFX_ARECVOLTAGESETDLG_H__E61D1D84_02F5_4936_98AE_54685D5C20D8__INCLUDED_)
#define AFX_ARECVOLTAGESETDLG_H__E61D1D84_02F5_4936_98AE_54685D5C20D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ARecVoltageSetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CARecVoltageSetDlg dialog

class CARecVoltageSetDlg : public CDialog
{
// Construction
public:
	CARecVoltageSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CARecVoltageSetDlg)
	enum { IDD = IDD_DIALOG_AREC_VOLTAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CARecVoltageSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CARecVoltageSetDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARECVOLTAGESETDLG_H__E61D1D84_02F5_4936_98AE_54685D5C20D8__INCLUDED_)
