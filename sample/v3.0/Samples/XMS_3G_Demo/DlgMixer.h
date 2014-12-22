#if !defined(AFX_DLGMIXER_H__9958C50A_0AAB_4C0A_9C01_51403DE3613E__INCLUDED_)
#define AFX_DLGMIXER_H__9958C50A_0AAB_4C0A_9C01_51403DE3613E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMixer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMixer dialog

class CDlgMixer : public CDialog
{
// Construction
public:
	int m_iSrcCtrl;
	int m_iSrc2Ctrl;
	CDlgMixer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMixer)
	enum { IDD = IDD_DLG_MIXER };
	CComboBox	m_CobSrc2Ctrl;
	CComboBox	m_CobSrcCtrl;
	BOOL	m_bAudio;
	BOOL	m_bVideo;
	UINT	m_uiSrcId;
	UINT	m_uiSrc2Id;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMixer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMixer)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMIXER_H__9958C50A_0AAB_4C0A_9C01_51403DE3613E__INCLUDED_)
