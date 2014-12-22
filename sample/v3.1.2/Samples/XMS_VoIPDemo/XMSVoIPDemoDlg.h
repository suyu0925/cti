// XMSVoIPDemoDlg.h : header file
//

#if !defined(AFX_XMSVOIPDEMODLG_H__A657D642_0FD9_4C53_B29A_E862C484EA54__INCLUDED_)
#define AFX_XMSVOIPDEMODLG_H__A657D642_0FD9_4C53_B29A_E862C484EA54__INCLUDED_

#include "DJAcsDataDef.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XMSVoIPDemoRTPDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CXMSVoIPDemoDlg dialog

class CXMSVoIPDemoDlg : public CDialog
{
// Construction
public:
	CXMSVoIPDemoRTPDlg *m_pdlgRtp;
	void initIPList();
	void initVocList();
	void initConfTree();
	void refreshCtrlIP();
	void refreshCtrlVoc();
	void refreshCtrlConf();
	void refreshListIP(int iDevice);
	void refreshListVoc(int iDevice);
	void refreshTreeConf(int iDevice);
	void enableDevice(const DeviceID_t *pDeviceID, BOOL bEnable=TRUE);
	CXMSVoIPDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXMSVoIPDemoDlg)
	enum { IDD = IDD_XMSVOIPDEMO_DIALOG };
	CTreeCtrl	m_treeConf;
	CListCtrl	m_lstVoc;
	CListCtrl	m_lstIP;
	CString	m_strCalleeAddr;
	CString	m_strCalleeTelNo;
	CString	m_strCalleeUserID;
	int		m_iProtocol;
	CString	m_strServerAddr;
	UINT	m_uiServerPort;
	CString	m_strPlayFile;
	int		m_iSampleRate;
	int		m_iCodec;
	CString	m_strRecordFile;
	int		m_iDtmf;
	CString	m_strCalleePort;
	CString	m_strUsername;
	CString	m_strPassword;
	int		m_iDSP;
	CString	m_strCalleePassword;
	CString	m_strCallerTelNo;
	CString	m_strRegAddr;
	CString	m_strRegPort;
	CString	m_strRegUsername;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMSVoIPDemoDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strIniFile;
	CFont m_font;
	void loadConfig();
	void saveConfig();
	void initUI();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXMSVoIPDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonMakeCall();
	afx_msg void OnButtonAnswerCall();
	afx_msg void OnButtonDropCall();
	afx_msg void OnButtonBindVoice();
	afx_msg void OnButtonInitSystem();
	afx_msg void OnButtonOpenDeviceIP();
	afx_msg void OnButtonOpenAllIP();
	afx_msg void OnItemchangedListIP(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRadioH323();
	afx_msg void OnRadioSip();
	afx_msg void OnButtonBrowsePlayFile();
	afx_msg void OnButtonPlay();
	afx_msg void OnItemchangedListVoice(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonCloseDeviceIP();
	afx_msg void OnButtonCloseAllIP();
	afx_msg void OnButtonOpenDeviceVoc();
	afx_msg void OnButtonCloseDeviceVoc();
	afx_msg void OnButtonOpenAllVoc();
	afx_msg void OnButtonCloseAllVoc();
	afx_msg void OnButtonUnbindVoice();
	afx_msg void OnSetfocusEditServerAddr();
	afx_msg void OnSetfocusEditServerPort();
	afx_msg void OnSetfocusEditCalleeAddr();
	afx_msg void OnSetfocusEditCalleePort();
	afx_msg void OnSetfocusEditCalleeUserid();
	afx_msg void OnSetfocusEditCalleeTelno();
	afx_msg void OnSetfocusEditPlayfile();
	afx_msg void OnButtonBrowseRecordFile();
	afx_msg void OnButtonRecord();
	afx_msg void OnButtonDtmf(UINT idBtn);
	afx_msg void OnButton3pconf();
	afx_msg void OnButtonOpenConf();
	afx_msg void OnButtonCloseConf();
	afx_msg void OnButtonJoinConf();
	afx_msg void OnButtonLeaveConf();
	afx_msg void OnButtonClearConf();
	afx_msg void OnSelchangedTreeConf(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListIp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonChairman();
	afx_msg void OnButtonReg();
	afx_msg void OnButtonUnreg();
	afx_msg void OnButtonTransfercall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMSVOIPDEMODLG_H__A657D642_0FD9_4C53_B29A_E862C484EA54__INCLUDED_)
