#if !defined(AFX_XMSVOIPDEMORTPDLG_H__CF17C85F_F4C6_424D_9B30_EC458D8F4D81__INCLUDED_)
#define AFX_XMSVOIPDEMORTPDLG_H__CF17C85F_F4C6_424D_9B30_EC458D8F4D81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XMSVoIPDemoRTPDlg.h : header file
//

#include "DJAcsAPIDef.h"

#define UM_UPDATEDATA	(WM_USER+100)

/////////////////////////////////////////////////////////////////////////////
// CXMSVoIPDemoRTPDlg dialog

class CXMSVoIPDemoRTPDlg : public CDialog
{
// Construction
public:
	Acs_VoIP_RTPCODEC m_paramCodec;
	Acs_VoIP_RTPADDR m_paramAddr;
	int m_iDeviceIP;
	CXMSVoIPDemoRTPDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXMSVoIPDemoRTPDlg)
	enum { IDD = IDD_RTPSESSION_DIALOG };
	int		m_iAudioTxCodec;
	int		m_iAudioRxCodec;
	int		m_iVideoRxCodec;
	int		m_iVideoTxCodec;
	CString	m_strAudioIP;
	UINT	m_uAudioPort;
	CString	m_strVideoIP;
	UINT	m_uVideoPort;
	int		m_iAudioDisable;
	int		m_iVideoDisable;
	BYTE	m_cAudioRxPt;
	BYTE	m_cAudioTxPt;
	BYTE	m_cVideoRxPt;
	BYTE	m_cVideoTxPt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMSVoIPDemoRTPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXMSVoIPDemoRTPDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void validCtrl();
	//}}AFX_MSG
	LRESULT OnUpdateData(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMSVOIPDEMORTPDLG_H__CF17C85F_F4C6_424D_9B30_EC458D8F4D81__INCLUDED_)
