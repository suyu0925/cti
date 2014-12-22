// XMS_VoIPServerDlg.h : header file
//

#if !defined(AFX_XMS_VOIPSERVERDLG_H__2AC2F976_4C47_4BFF_BC50_91D81983E672__INCLUDED_)
#define AFX_XMS_VOIPSERVERDLG_H__2AC2F976_4C47_4BFF_BC50_91D81983E672__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXMS_VoIPServerDlg dialog

class CXMS_VoIPServerDlg : public CDialog
{
// Construction
public:
	CXMS_VoIPServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXMS_VoIPServerDlg)
	enum { IDD = IDD_XMS_VOIPSERVER_DIALOG };
	CListCtrl	m_tListEvent;
	CListCtrl	m_tListUser;
	CListCtrl	m_tListDevice;
	CListCtrl	m_tListCall;
	CString	m_strAddress;
	UINT	m_nAppID;
	UINT	m_nPort;
	CString	m_strUserName;
	CString	m_strPassword;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMS_VoIPServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strIniFile;
	void loadConfig();
	void saveConfig();

	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CXMS_VoIPServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnBtnInit();
	afx_msg void OnBtnClearLog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void InitUI();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMS_VOIPSERVERDLG_H__2AC2F976_4C47_4BFF_BC50_91D81983E672__INCLUDED_)
