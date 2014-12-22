#if !defined(AFX_3GPPCONFGDLG_H__FA46E51B_D4AA_4694_A72E_21BF451C030B__INCLUDED_)
#define AFX_3GPPCONFGDLG_H__FA46E51B_D4AA_4694_A72E_21BF451C030B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 3gppConfgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C3gppConfgDlg dialog

class C3gppConfgDlg : public CDialog
{
// Construction
public:
	C3gppConfgDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(C3gppConfgDlg)
	enum { IDD = IDD_DIALOG_GET_3GP_CFG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3gppConfgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C3gppConfgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAudioGetPath();
	afx_msg void OnButtonVideoGetPath();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3GPPCONFGDLG_H__FA46E51B_D4AA_4694_A72E_21BF451C030B__INCLUDED_)
