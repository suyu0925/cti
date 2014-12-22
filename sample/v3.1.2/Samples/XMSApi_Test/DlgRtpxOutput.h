#if !defined(AFX_DLGRTPXOUTPUT_H__4630B759_1CC2_4026_B268_39AB977A5974__INCLUDED_)
#define AFX_DLGRTPXOUTPUT_H__4630B759_1CC2_4026_B268_39AB977A5974__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRtpxOutput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRtpxOutput dialog

class CDlgRtpxOutput : public CDialog
{
// Construction
public:
	UINT m_uiIP;
	UINT m_uiSrcCtrl;
	UINT m_uiMediaType;
	CDlgRtpxOutput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRtpxOutput)
	enum { IDD = IDD_DLG_RTPXOUTPUT };
	CIPAddressCtrl	m_IP;
	CComboBox	m_cmbSrcCtrl;
	CComboBox	m_cmbMediaType;
	BOOL	m_bEnable;
	UINT	m_uiPayload;
	UINT	m_uiPort;
	UINT	m_uiSrcId;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRtpxOutput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRtpxOutput)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRTPXOUTPUT_H__4630B759_1CC2_4026_B268_39AB977A5974__INCLUDED_)
