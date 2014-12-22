#if !defined(AFX_XMSAPI_3GPP_BUILDINDEX_H__098E2C82_501E_4987_8A87_A65368D55761__INCLUDED_)
#define AFX_XMSAPI_3GPP_BUILDINDEX_H__098E2C82_501E_4987_8A87_A65368D55761__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XMSApi_3GPP_BuildIndex.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXMSApi_3GPP_BuildIndex dialog

class CXMSApi_3GPP_BuildIndex : public CDialog
{
// Construction
public:
	void GetNowSetVal();
	CXMSApi_3GPP_BuildIndex(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXMSApi_3GPP_BuildIndex)
	enum { IDD = IDD_DIALOG_3GPPBuildPlayIndex };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMSApi_3GPP_BuildIndex)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXMSApi_3GPP_BuildIndex)
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONSelectBuildIndex();
	afx_msg void OnBUTTONSelectBuildIndexVideo();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMSAPI_3GPP_BUILDINDEX_H__098E2C82_501E_4987_8A87_A65368D55761__INCLUDED_)
