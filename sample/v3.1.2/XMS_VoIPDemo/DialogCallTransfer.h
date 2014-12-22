#if !defined(AFX_DIALOGCALLTRANSFER_H__B2FAFA88_916D_468E_A015_59C3511BB34D__INCLUDED_)
#define AFX_DIALOGCALLTRANSFER_H__B2FAFA88_916D_468E_A015_59C3511BB34D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogCallTransfer.h : header file
//

#include "XMSData.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogCallTransfer dialog

class CDialogCallTransfer : public CDialog
{
// Construction
public:
	CDialogCallTransfer(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogCallTransfer)
	enum { IDD = IDD_DIALOG_TRANSFER };
	CString	m_szCalleeTelNo;
	int	m_nDestSlot;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogCallTransfer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogCallTransfer)
	afx_msg void OnBtnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGCALLTRANSFER_H__B2FAFA88_916D_468E_A015_59C3511BB34D__INCLUDED_)
