#if !defined(AFX_DLGMEDIAEXPARAM_H__3DCC6E81_A486_4870_A943_31D897CC0D05__INCLUDED_)
#define AFX_DLGMEDIAEXPARAM_H__3DCC6E81_A486_4870_A943_31D897CC0D05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMediaExParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMediaExParam dialog

class CDlgMediaExParam : public CDialog
{
// Construction
public:
	int m_iParamType;
	CDlgMediaExParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMediaExParam)
	enum { IDD = IDD_DLG_MEDIAEX_PARAM };
	CComboBox	m_cmbParamType;
	UINT	m_uiChNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMediaExParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMediaExParam)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMEDIAEXPARAM_H__3DCC6E81_A486_4870_A943_31D897CC0D05__INCLUDED_)
