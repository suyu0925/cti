#if !defined(AFX_XMSAPI_CONTROL3GPPPLAY_H__954EC41E_CA64_4D06_BB61_926707CACC4F__INCLUDED_)
#define AFX_XMSAPI_CONTROL3GPPPLAY_H__954EC41E_CA64_4D06_BB61_926707CACC4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XMSApi_Control3GPPPlay.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXMSApi_Control3GPPPlay dialog

class CXMSApi_Control3GPPPlay : public CDialog
{
// Construction
public:
	CXMSApi_Control3GPPPlay(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXMSApi_Control3GPPPlay)
	enum { IDD = IDD_DIALOG_CONTROL3GPPPLAY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMSApi_Control3GPPPlay)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXMSApi_Control3GPPPlay)
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONStop();
	afx_msg void OnBUTTONPause();
	afx_msg void OnBUTTONResume();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMSAPI_CONTROL3GPPPLAY_H__954EC41E_CA64_4D06_BB61_926707CACC4F__INCLUDED_)
