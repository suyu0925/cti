// XMSVoIPProxyDlg.h : header file
//

#if !defined(AFX_XMSVOIPPROXYDLG_H__C645D684_7CEC_4D24_B7DE_7A5F43882603__INCLUDED_)
#define AFX_XMSSVOIPPROXYDLG_H__C645D684_7CEC_4D24_B7DE_7A5F43882603__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DJAcsDataDef.h"
#include <list>

/////////////////////////////////////////////////////////////////////////////
// CXMSVoIPProxyDlg dialog

struct tagRouteItem
{
	CString strAddr;
	unsigned int uPort;
	CString strUserName;
	CString strPassword;
	CString strCalleeHead;
};

class CXMSVoIPProxyDlg : public CDialog
{
// Construction
public:
	void refreshListReg(int iRegID);
	void initIPList();
	void refreshListIP(int iDevice);
	void enableDevice(const DeviceID_t *pDeviceID, BOOL bEnable=TRUE);
	CXMSVoIPProxyDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXMSVoIPProxyDlg)
	enum { IDD = IDD_XMSVOIPPROXY_DIALOG };
	CButton	m_btnUseDspRtp;
	CListCtrl	m_lstRoute;
	CListCtrl	m_lstReg;
	CListCtrl	m_lstIP;
	UINT	m_uiServerPort;
	CString	m_strServerIP;
	CString	m_strUsername;
	CString	m_strPassword;
	int		m_iDSP;
	BOOL	m_bInteractive;
	CString	m_strRouteIP;
	UINT	m_uRoutePort;
	CString	m_strRouteUserName;
	CString	m_strRoutePassword;
	CString	m_strRouteCalleeHead;
	BOOL	m_bAutoRtp;
	BOOL	m_bUseDspRtp;
	CString	m_strDspIp;
	BOOL	m_bDspBehindNat;
	CString	m_strRegisterTelNO;
	CString	m_strRegServerIP;
	CString	m_strRegPassword;
	UINT	m_uRegPort;
	CString	m_strRegUserName;
	CString	m_UserID;
	CString	m_strOptionIP;
	CString	m_strOptionID;
	UINT	m_strOptionPort;
	CString	m_strOptionTelNO;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMSVoIPProxyDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strIniFile;
	void loadConfig();
	void saveConfig();

	void initUI();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXMSVoIPProxyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonInit();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnDeleteAll();
	afx_msg void OnCheckAutoRtp();
	afx_msg void OnCheckUseDspRtp();
	afx_msg void OnCheckDspNat();
	afx_msg void OnKillfocusEditDspIp();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMSVOIPPROXYDLG_H__C645D684_7CEC_4D24_B7DE_7A5F43882603__INCLUDED_)
