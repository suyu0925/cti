#if !defined(AFX_DLGFAXMULTIFILEPARAM_H__A56326A5_5DE4_4046_B251_7FE597F2388B__INCLUDED_)
#define AFX_DLGFAXMULTIFILEPARAM_H__A56326A5_5DE4_4046_B251_7FE597F2388B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFaxMultiFileParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFaxMultiFileParam dialog

class CDlgFaxMultiFileParam : public CDialog
{
// Construction
public:
	CDlgFaxMultiFileParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFaxMultiFileParam)
	enum { IDD = IDD_DIALOG_FAX_MULTI_FILE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFaxMultiFileParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFaxMultiFileParam)
	virtual void OnOK();
	afx_msg void OnButtonFindFilePath();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFAXMULTIFILEPARAM_H__A56326A5_5DE4_4046_B251_7FE597F2388B__INCLUDED_)
