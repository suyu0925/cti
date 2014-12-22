#if !defined(AFX_DLGSETVOIPPARAMS_H__B728B0DC_89E5_419B_9B31_4117608B1F0C__INCLUDED_)
#define AFX_DLGSETVOIPPARAMS_H__B728B0DC_89E5_419B_9B31_4117608B1F0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetVoIPParams.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSetVoIPParams dialog

class CDlgSetVoIPParams : public CDialog
{
// Construction
public:
	CDlgSetVoIPParams(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetVoIPParams)
	enum { IDD = IDD_DIALOG_VOIP_SET_PARAM };
	BOOL	m_bV;
	BOOL	m_bA;
	UINT	m_nDtmf;
	UINT	m_nTone;
	CString	m_szIPV;
	UINT	m_nPortV;
	CString	m_szIPA;
	UINT	m_nPortA;
	CString	m_szCapsA;
	CString	m_szCapsV;
	BOOL	m_bRTPAddr;
	BOOL	m_bRTPCodec;
	BOOL	m_bRTPSession;
	BOOL	m_bVoIPMedia;
	BOOL	m_bOpenRTP;
	BOOL	m_bUseDsp;
	CString	m_szDSPIP;
	UINT	m_nDspPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetVoIPParams)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetVoIPParams)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETVOIPPARAMS_H__B728B0DC_89E5_419B_9B31_4117608B1F0C__INCLUDED_)
