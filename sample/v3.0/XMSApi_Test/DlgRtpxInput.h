#if !defined(AFX_DLGRTPXINPUT_H__655B01CA_0358_4AA4_A28C_09B41C481493__INCLUDED_)
#define AFX_DLGRTPXINPUT_H__655B01CA_0358_4AA4_A28C_09B41C481493__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRtpxInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRtpxInput dialog

class CDlgRtpxInput : public CDialog
{
// Construction
public:
	UINT m_uiMediaType;
	CDlgRtpxInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRtpxInput)
	enum { IDD = IDD_DLG_RTPXINPUT };
	CComboBox	m_cmbMediaType;
	BOOL	m_bEnable;
	UINT	m_uiPayload;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRtpxInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRtpxInput)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRTPXINPUT_H__655B01CA_0358_4AA4_A28C_09B41C481493__INCLUDED_)
