#if !defined(AFX_XMSAPI_3GPPPLAYSET_H__E6DBDA93_CF94_4E7C_AB3D_C46FA0731D32__INCLUDED_)
#define AFX_XMSAPI_3GPPPLAYSET_H__E6DBDA93_CF94_4E7C_AB3D_C46FA0731D32__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XMSApi_3GPPPlaySet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXMSApi_3GPPPlaySet dialog

class CXMSApi_3GPPPlaySet : public CDialog
{
// Construction
public:
	void Select3GPPPlayFile(DWORD u32EditID);
	void Enable_File(bool IsEnable);
	void HandleEnableDisable();
	CXMSApi_3GPPPlaySet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXMSApi_3GPPPlaySet)
	enum { IDD = IDD_DIALOG_PLAY_3GPP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMSApi_3GPPPlaySet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXMSApi_3GPPPlaySet)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRADIONormalStop();
	afx_msg void OnRADIOSingleCode();
	afx_msg void OnRADIOAnyCode();
	afx_msg void OnRadioPlayTypeFile();
	afx_msg void OnRadioPlayTypeIndex();
	afx_msg void OnRadioPlayTypeFileQueue();
	afx_msg void OnRadioPlayTypeIndexQueue();
	afx_msg void OnRadioPlyCodeStrm();
	afx_msg void OnButtonGetAfileName();
	afx_msg void OnButtonGetVfileName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XMSAPI_3GPPPLAYSET_H__E6DBDA93_CF94_4E7C_AB3D_C46FA0731D32__INCLUDED_)
