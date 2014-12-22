#if !defined(AFX_XMSAPI_3GPPCONTROLRECORD_H__80D987CD_63EF_48B4_BEBC_7CB6BF810C79__INCLUDED_)
#define AFX_XMSAPI_3GPPCONTROLRECORD_H__80D987CD_63EF_48B4_BEBC_7CB6BF810C79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XMSApi_3GPPControlRecord.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXMSApi_3GPPControlRecord dialog

class CXMSApi_3GPPControlRecord : public CDialog
{
// Construction
public:
	void Get_u32StepSize();
	CXMSApi_3GPPControlRecord(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXMSApi_3GPPControlRecord)
	enum { IDD = IDD_DIALOG_CONTROL3GPPRECORD };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMSApi_3GPPControlRecord)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXMSApi_3GPPControlRecord)
	afx_msg void OnBUTTON3GPPStop();
	afx_msg void OnBUTTON3GPPPause();
	afx_msg void OnBUTTON3GPPResume();
	afx_msg void OnBUTTON3GPPStepBack();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMSAPI_3GPPCONTROLRECORD_H__80D987CD_63EF_48B4_BEBC_7CB6BF810C79__INCLUDED_)
