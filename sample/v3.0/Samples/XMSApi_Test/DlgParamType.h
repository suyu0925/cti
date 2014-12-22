#if !defined(AFX_DLGPARAMTYPE_H__FC7AEE81_A9B4_4CBB_95F6_51848BCA1C63__INCLUDED_)
#define AFX_DLGPARAMTYPE_H__FC7AEE81_A9B4_4CBB_95F6_51848BCA1C63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgParamType.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgParamType dialog

class CDlgParamType : public CDialog
{
// Construction
public:
	int m_iParamType;
	CDlgParamType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgParamType)
	enum { IDD = IDD_DLG_PARAMTYPE };
	CComboBox	m_cmbParamType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgParamType)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgParamType)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPARAMTYPE_H__FC7AEE81_A9B4_4CBB_95F6_51848BCA1C63__INCLUDED_)
