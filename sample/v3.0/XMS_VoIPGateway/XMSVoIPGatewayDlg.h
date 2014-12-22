// XMSVoIPGatewayDlg.h : header file
//

#if !defined(AFX_XMSVOIPGATEWAYDLG_H__C645D684_7CEC_4D24_B7DE_7A5F43882603__INCLUDED_)
#define AFX_XMSVOIPGATEWAYDLG_H__C645D684_7CEC_4D24_B7DE_7A5F43882603__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DJAcsDataDef.h"

/////////////////////////////////////////////////////////////////////////////
// CXMSVoIPGatewayDlg dialog

class CXMSVoIPGatewayDlg : public CDialog
{
// Construction
public:
	void initIPList();
	void refreshListIP(int iDevice);
	void initTrunkList();
	void refreshListTrunk(int iDevice);
	void enableDevice(const DeviceID_t *pDeviceID, BOOL bEnable=TRUE);
	CXMSVoIPGatewayDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXMSVoIPGatewayDlg)
	enum { IDD = IDD_XMSVOIPGATEWAY_DIALOG };
	CListCtrl	m_lstTrunk;
	CListCtrl	m_lstIP;
	UINT	m_uiServerPort;
	CString	m_strServerIP;
	CString	m_strUsername;
	CString	m_strPassword;
	int		m_iProtocol;
	int		m_iDSP;
	CString	m_strDialPlan;
	BOOL	m_bEC;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMSVoIPGatewayDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strIniFile;
	void loadConfig();
	void saveConfig();

	void initUI();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXMSVoIPGatewayDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonInit();
	afx_msg void OnBeginlabeleditListTrunk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditListTrunk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListTrunk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMSVOIPGATEWAYDLG_H__C645D684_7CEC_4D24_B7DE_7A5F43882603__INCLUDED_)
