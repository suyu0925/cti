// SPDlg.h : header file
//

#if !defined(AFX_SPDLG_H__65802BB6_8E06_4D53_A045_38144745D639__INCLUDED_)
#define AFX_SPDLG_H__65802BB6_8E06_4D53_A045_38144745D639__INCLUDED_

#include "DlgIODataUII.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSPDlg dialog

class CSPDlg : public CDialog
{
// Construction
public:
	CSPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSPDlg)
	enum { IDD = IDD_SP_DIALOG };
	CListCtrl	m_ListMember;
	CListCtrl	m_ListHotConf;
	CListCtrl	m_ListDevInfo;
	CListCtrl	m_ListDevType;
	CListBox	m_ListMsg;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickListDevType(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListDevInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonOpenall();
	afx_msg void OnButtonCloseall();
	afx_msg void OnButtonSetparam();
	afx_msg void OnButtonClearcall();
	afx_msg void OnButtonIOData();
	afx_msg void OnButtonCall();
	afx_msg void OnButtonPlay();
	afx_msg void OnButtonRecord();
	afx_msg void OnButtonStop();
	afx_msg void OnButtonLink();
	afx_msg void OnButtonUnlink();
	afx_msg void OnButtonReset();
	afx_msg void OnButtonInit();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClickListHotconf(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonStoprec();
	afx_msg void OnRclickListDevInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuMainJoin();
	afx_msg void OnMenuMainLeave();
	afx_msg void OnMenuMainPlay();
	afx_msg void OnMenuMainRecord();
	afx_msg void OnMenuMainRestart();
	afx_msg void OnMenuMainSetlayout();
	afx_msg void OnMenuMainSetvisiblelist();
	afx_msg void OnMenuMainClear();
	afx_msg void OnMenuMainGetlayout();
	afx_msg void OnMenuMainGetvisiblelist();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMenuMainStarttimer();
	afx_msg void OnMenuMainStoptimer();
	afx_msg void OnButtonGetfileinfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CDlgIODataUII m_dlgUII;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPDLG_H__65802BB6_8E06_4D53_A045_38144745D639__INCLUDED_)
