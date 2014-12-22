#if !defined(AFX_TXLINKCTXDLG_H__ED5EEAF5_1F1F_4DF5_8A76_EF2A6CCBC6A3__INCLUDED_)
#define AFX_TXLINKCTXDLG_H__ED5EEAF5_1F1F_4DF5_8A76_EF2A6CCBC6A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// txLinkCtxDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CtxLinkCtxDlg dialog

class CtxLinkCtxDlg : public CDialog
{
// Construction
public:
	CtxLinkCtxDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CtxLinkCtxDlg)
	enum { IDD = IDD_DIALOG_CTXLinkCTX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CtxLinkCtxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CtxLinkCtxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCtxLink2Ctx();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TXLINKCTXDLG_H__ED5EEAF5_1F1F_4DF5_8A76_EF2A6CCBC6A3__INCLUDED_)
