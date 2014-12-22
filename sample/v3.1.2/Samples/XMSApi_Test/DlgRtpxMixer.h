#if !defined(AFX_DLGRTPXMIXER_H__DB24B32B_AF70_45E3_842C_829A603A7AEE__INCLUDED_)
#define AFX_DLGRTPXMIXER_H__DB24B32B_AF70_45E3_842C_829A603A7AEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRtpxMixer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRtpxMixer dialog

class CDlgRtpxMixer : public CDialog
{
// Construction
public:
	UINT m_uiSrcCtrl;
	CDlgRtpxMixer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRtpxMixer)
	enum { IDD = IDD_DLG_RTPXMIXER };
	CComboBox	m_cmbRtpxMixer;
	UINT	m_uiSrcId;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRtpxMixer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRtpxMixer)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRTPXMIXER_H__DB24B32B_AF70_45E3_842C_829A603A7AEE__INCLUDED_)
