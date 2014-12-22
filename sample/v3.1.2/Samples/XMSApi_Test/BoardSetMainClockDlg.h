#if !defined(AFX_BOARDSETMAINCLOCKDLG_H__FBC6756A_4A5A_43D9_8CFE_63F505274EB1__INCLUDED_)
#define AFX_BOARDSETMAINCLOCKDLG_H__FBC6756A_4A5A_43D9_8CFE_63F505274EB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BoardSetMainClockDlg.h : header file
//
#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"


extern Acs_BoardPrivateExt_Data      g_stBoardPrivateExt_Data;

/////////////////////////////////////////////////////////////////////////////
// CBoardSetMainClockDlg dialog

class CBoardSetMainClockDlg : public CDialog
{
// Construction
public:
	void EnableControlFlag(void);
	CBoardSetMainClockDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBoardSetMainClockDlg)
	enum { IDD = IDD_DIALOG_BOARD_SET_MAIN_CLOCK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoardSetMainClockDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBoardSetMainClockDlg)
	virtual void OnOK();
	afx_msg void OnRadioXmsBoardExtTypeNull();
	afx_msg void OnRadioXmsBoardExtTypeClock();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOARDSETMAINCLOCKDLG_H__FBC6756A_4A5A_43D9_8CFE_63F505274EB1__INCLUDED_)
