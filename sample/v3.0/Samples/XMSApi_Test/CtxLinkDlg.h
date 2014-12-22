#if !defined(AFX_CTXLINKDLG_H__F2D0E225_1140_4B89_8A3B_0FB43AA721BD__INCLUDED_)
#define AFX_CTXLINKDLG_H__F2D0E225_1140_4B89_8A3B_0FB43AA721BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CtxLinkDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCtxLinkDlg dialog

class CCtxLinkDlg : public CDialog
{
// Construction
public:
	CCtxLinkDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCtxLinkDlg)
	enum { IDD = IDD_DIALOG_CTXLinkDlg };
	CComboBox	m_ComboLinkOpt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCtxLinkDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCtxLinkDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnCtxLink2Ctx();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonCtxLink();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTXLINKDLG_H__F2D0E225_1140_4B89_8A3B_0FB43AA721BD__INCLUDED_)
