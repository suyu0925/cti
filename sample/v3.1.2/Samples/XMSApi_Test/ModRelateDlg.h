#if !defined(AFX_MODRELATEDLG_H__A040AE32_AD44_4A14_9E32_DAAB56610D6F__INCLUDED_)
#define AFX_MODRELATEDLG_H__A040AE32_AD44_4A14_9E32_DAAB56610D6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModRelateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ModRelateDlg dialog

class ModRelateDlg : public CDialog
{
// Construction
public:
	ModRelateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ModRelateDlg)
	enum { IDD = IDD_DIALOG_GET_RELATE_MOD_DLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ModRelateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ModRelateDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODRELATEDLG_H__A040AE32_AD44_4A14_9E32_DAAB56610D6F__INCLUDED_)
