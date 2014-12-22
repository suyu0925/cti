// DialogCallTransfer.cpp : implementation file
//

#include "stdafx.h"
#include "xmsvoipdemo.h"
#include "DialogCallTransfer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogCallTransfer dialog


CDialogCallTransfer::CDialogCallTransfer(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogCallTransfer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogCallTransfer)
	m_szCalleeTelNo = _T("");
	m_nDestSlot = -1;
	//}}AFX_DATA_INIT
}


void CDialogCallTransfer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogCallTransfer)
	DDX_Text(pDX, IDC_EDIT_CALLEE_TELNO, m_szCalleeTelNo);
	DDX_Text(pDX, IDC_EDIT_DEST_SLOT, m_nDestSlot);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogCallTransfer, CDialog)
	//{{AFX_MSG_MAP(CDialogCallTransfer)
	ON_BN_CLICKED(ID_BTN_OK, OnBtnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogCallTransfer message handlers

void CDialogCallTransfer::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	OnOK();
}
