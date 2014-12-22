#if !defined(AFX_DLGCMDPARAMDATACAS_H__633A38A8_FC06_4688_8A24_01A49E483EAD__INCLUDED_)
#define AFX_DLGCMDPARAMDATACAS_H__633A38A8_FC06_4688_8A24_01A49E483EAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCmdParamDataCAS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCmdParamDataCAS dialog

class CDlgCmdParamDataCAS : public CDialog
{
// Construction
public:
	CDlgCmdParamDataCAS(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCmdParamDataCAS)
	enum { IDD = IDD_DIALOG_CMDPARAMDATA_CAS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCmdParamDataCAS)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCmdParamDataCAS)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCMDPARAMDATACAS_H__633A38A8_FC06_4688_8A24_01A49E483EAD__INCLUDED_)
