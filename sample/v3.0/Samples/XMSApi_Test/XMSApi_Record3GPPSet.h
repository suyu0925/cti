#if !defined(AFX_XMSAPI_RECORD3GPPSET_H__C7783415_8235_4D39_B697_AE05DBC0DD62__INCLUDED_)
#define AFX_XMSAPI_RECORD3GPPSET_H__C7783415_8235_4D39_B697_AE05DBC0DD62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XMSApi_Record3GPPSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXMSApi_Record3GPPSet dialog

class CXMSApi_Record3GPPSet : public CDialog
{
// Construction
public:
	void HandleEnableDisable();
	CXMSApi_Record3GPPSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXMSApi_Record3GPPSet)
	enum { IDD = IDD_DIALOG_Record_3GPP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMSApi_Record3GPPSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXMSApi_Record3GPPSet)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnRADIONormalStop();
	afx_msg void OnRADIOSingleCode();
	afx_msg void OnRADIOAnyCode();
	afx_msg void OnCHECKs8MixEnable();
	afx_msg void OnCHECKViedeos8MixEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMSAPI_RECORD3GPPSET_H__C7783415_8235_4D39_B697_AE05DBC0DD62__INCLUDED_)
