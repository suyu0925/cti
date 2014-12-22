#if !defined(AFX_CTXAPPDATA_H__17BB0AB5_EAAF_4185_9B85_9F7ADD0222F7__INCLUDED_)
#define AFX_CTXAPPDATA_H__17BB0AB5_EAAF_4185_9B85_9F7ADD0222F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CtxAppData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCtxAppData dialog

class CCtxAppData : public CDialog
{
// Construction
public:
	CCtxAppData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCtxAppData)
	enum { IDD = IDD_DIALOG_CtxAppData };
	CEdit	m_RegName;
	CComboBox	m_RegType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCtxAppData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCtxAppData)
	virtual void OnOK();
	afx_msg void OnBUTTONSendData();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_CTXAPPDATA_H__17BB0AB5_EAAF_4185_9B85_9F7ADD0222F7__INCLUDED_)
