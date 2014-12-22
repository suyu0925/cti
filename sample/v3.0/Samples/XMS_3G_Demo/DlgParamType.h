#if !defined(AFX_DLGPARAMTYPE_H__8617F3DA_D8D4_4ADA_9651_400B185E736B__INCLUDED_)
#define AFX_DLGPARAMTYPE_H__8617F3DA_D8D4_4ADA_9651_400B185E736B__INCLUDED_

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
	int m_iDevType;
	CDlgParamType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgParamType)
	enum { IDD = IDD_DLG_PARAMTYPE };
	CComboBox	m_CobParamType;
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
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPARAMTYPE_H__8617F3DA_D8D4_4ADA_9651_400B185E736B__INCLUDED_)
