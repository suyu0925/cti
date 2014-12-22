#if !defined(AFX_SENDSIGNALDATA_H__B57BF925_0EC9_40A0_9F63_32599F317FC4__INCLUDED_)
#define AFX_SENDSIGNALDATA_H__B57BF925_0EC9_40A0_9F63_32599F317FC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendSignalData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSendSignalData dialog

class CSendSignalData : public CDialog
{
// Construction
public:
	CSendSignalData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSendSignalData)
	enum { IDD = IDD_DIALOG_SEND_SIGNAL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendSignalData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSendSignalData)
	afx_msg void OnButtonRun();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDSIGNALDATA_H__B57BF925_0EC9_40A0_9F63_32599F317FC4__INCLUDED_)
