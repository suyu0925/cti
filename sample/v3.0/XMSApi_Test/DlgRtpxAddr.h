#if !defined(AFX_DLGRTPXADDR_H__D48F3FC6_0708_4A2F_9A59_0977F07E63FE__INCLUDED_)
#define AFX_DLGRTPXADDR_H__D48F3FC6_0708_4A2F_9A59_0977F07E63FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRtpxAddr.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRtpxAddr dialog

class CDlgRtpxAddr : public CDialog
{
// Construction
public:
	UINT m_uiIP;
	CDlgRtpxAddr(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRtpxAddr)
	enum { IDD = IDD_DLG_RTPXADDR };
	CIPAddressCtrl	m_IP;
	UINT	m_uiPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRtpxAddr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRtpxAddr)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRTPXADDR_H__D48F3FC6_0708_4A2F_9A59_0977F07E63FE__INCLUDED_)
