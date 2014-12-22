// XMS_FaxDemoDlg.h : header file
//

#if !defined(AFX_XMS_FAXDEMODLG_H__3F4D20FF_1F08_4DFA_B2DC_BA625B25D0EF__INCLUDED_)
#define AFX_XMS_FAXDEMODLG_H__3F4D20FF_1F08_4DFA_B2DC_BA625B25D0EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXMS_FaxDemoDlg dialog

class CXMS_FaxDemoDlg : public CDialog
{
// Construction
public:
	CXMS_FaxDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXMS_FaxDemoDlg)
	enum { IDD = IDD_XMS_FAXDEMO_DIALOG };
	CListCtrl	m_ListCount;
	CListCtrl	m_ListFax;
	CListBox	m_ListMsg;
	CListCtrl	m_ListPcm;
	CListCtrl	m_ListMain;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMS_FaxDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXMS_FaxDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnBUTTONReOpen();
	afx_msg void OnBUTTONRemove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMS_FAXDEMODLG_H__3F4D20FF_1F08_4DFA_B2DC_BA625B25D0EF__INCLUDED_)
