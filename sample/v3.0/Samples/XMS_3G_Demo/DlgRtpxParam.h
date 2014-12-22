#if !defined(AFX_DLGRTPXPARAM_H__3FBC031D_6125_40F9_812C_18A4C76C9649__INCLUDED_)
#define AFX_DLGRTPXPARAM_H__3FBC031D_6125_40F9_812C_18A4C76C9649__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRtpxParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRtpxParam dialog

class CDlgRtpxParam : public CDialog
{
// Construction
public:
	int m_iDataType;
	CDlgRtpxParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRtpxParam)
	enum { IDD = IDD_DIALOG_RTPX };
	CComboBox	m_cmbDataType;
	BOOL	m_bEnable;
	UINT	m_pt;
	BOOL	m_bTranscode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRtpxParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRtpxParam)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRTPXPARAM_H__3FBC031D_6125_40F9_812C_18A4C76C9649__INCLUDED_)
