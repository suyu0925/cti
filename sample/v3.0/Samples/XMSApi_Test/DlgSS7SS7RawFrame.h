#if !defined(AFX_DLGSS7SS7RAWFRAME_H__C938B579_ABCE_45D5_846D_9956629334D4__INCLUDED_)
#define AFX_DLGSS7SS7RAWFRAME_H__C938B579_ABCE_45D5_846D_9956629334D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSS7SS7RawFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSS7SS7RawFrame dialog

class CDlgSS7SS7RawFrame : public CDialog
{
// Construction
public:
	CDlgSS7SS7RawFrame(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSS7SS7RawFrame)
	enum { IDD = IDD_DIALOG_SS7RAWFRAME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSS7SS7RawFrame)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSS7SS7RawFrame)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSS7SS7RAWFRAME_H__C938B579_ABCE_45D5_846D_9956629334D4__INCLUDED_)
