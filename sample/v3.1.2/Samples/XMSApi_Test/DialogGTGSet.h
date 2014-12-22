#if !defined(AFX_DIALOGGTGSET_H__532D147B_B7FD_48E2_90DF_A4BB570186DE__INCLUDED_)
#define AFX_DIALOGGTGSET_H__532D147B_B7FD_48E2_90DF_A4BB570186DE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogGTGSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogGTGSet dialog

class CDialogGTGSet : public CDialog
{
// Construction
public:
	CDialogGTGSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogGTGSet)
	enum { IDD = IDD_DIALOG_GTGSET };
	CComboBox	m_GTGComboEnvelop;
	CTabCtrl	m_tab_gtg_tone;
	CTabCtrl	m_tab_gtg_freq;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogGTGSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogGTGSet)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickTabGtGFreq(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnClickTabGtGTone(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboEnvelop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGGTGSET_H__532D147B_B7FD_48E2_90DF_A4BB570186DE__INCLUDED_)
