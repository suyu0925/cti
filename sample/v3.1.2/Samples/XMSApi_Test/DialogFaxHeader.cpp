// DialogFaxHeader.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DialogFaxHeader.h"

#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern Acs_TransAddHeader g_FaxHeader;
/////////////////////////////////////////////////////////////////////////////
// CDialogFaxHeader dialog


CDialogFaxHeader::CDialogFaxHeader(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogFaxHeader::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogFaxHeader)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogFaxHeader::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogFaxHeader)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogFaxHeader, CDialog)
	//{{AFX_MSG_MAP(CDialogFaxHeader)
	ON_BN_CLICKED(IDC_RADIO_PAGE_HEADER_TYPE_CLEAR, OnRadioPageHeaderTypeClear)
	ON_BN_CLICKED(IDC_RADIO_PAGE_HEADER_TYPE_SET, OnRadioPageHeaderTypeSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogFaxHeader message handlers

void CDialogFaxHeader::OnOK() 
{
	// TODO: Add extra validation here
	int iTmpVal=0;
	char Temp[256];
	
	if ( 1 == ((CButton*)GetDlgItem(IDC_RADIO_PAGE_HEADER_TYPE_CLEAR))->GetCheck() )
		g_FaxHeader.m_u32Op = XMS_FAX_PAGE_HEADER_TYPE_CLEAR;
	else
		g_FaxHeader.m_u32Op = XMS_FAX_PAGE_HEADER_TYPE_SET;

	/*
	memset(Temp, 0, sizeof(Temp));
	GetDlgItem ( IDC_EDIT_OP )->GetWindowText ( Temp, 20 );
	sscanf ( Temp, "%d", &iTmpVal );
	g_FaxHeader.m_u32Op	= iTmpVal;
	*/

	memset(Temp, 0, sizeof(Temp));
	GetDlgItem ( IDC_EDIT_XPOS )->GetWindowText (Temp, 20 );
	sscanf ( Temp, "%d", &iTmpVal );
	g_FaxHeader.m_u16XPos	= iTmpVal;
	memset(Temp, 0, sizeof(Temp));
	GetDlgItem ( IDC_EDIT_YPOS )->GetWindowText (Temp, 20 );
	sscanf ( Temp, "%d", &iTmpVal );
	g_FaxHeader.m_u16YPos	= iTmpVal;
	memset(g_FaxHeader.m_u8Data, 0, sizeof(g_FaxHeader.m_u8Data));
	GetDlgItem ( IDC_EDIT_DATA )->GetWindowText (g_FaxHeader.m_u8Data, 73 );

	CDialog::OnOK();
}

BOOL CDialogFaxHeader::OnInitDialog() 
{
	bool bFlag = false;

	CDialog::OnInitDialog();
	
	CString	str;
	/*
	str.Format("%d", g_FaxHeader.m_u32Op);
	SetDlgItemText(IDC_EDIT_OP,str);
    */

	if ( g_FaxHeader.m_u32Op == XMS_FAX_PAGE_HEADER_TYPE_CLEAR )
		((CButton*)GetDlgItem(IDC_RADIO_PAGE_HEADER_TYPE_CLEAR))->SetCheck(true);
	else
		((CButton*)GetDlgItem(IDC_RADIO_PAGE_HEADER_TYPE_SET))->SetCheck(true);

	str.Format("%d", g_FaxHeader.m_u16XPos);
	SetDlgItemText(IDC_EDIT_XPOS,str);
	str.Format("%d", g_FaxHeader.m_u16YPos);
	SetDlgItemText(IDC_EDIT_YPOS,str);
	SetDlgItemText(IDC_EDIT_DATA,g_FaxHeader.m_u8Data);

	if ( 1 == ((CButton*)GetDlgItem(IDC_RADIO_PAGE_HEADER_TYPE_CLEAR))->GetCheck() )
		bFlag = false;
	else
		bFlag = true;

	GetDlgItem(IDC_EDIT_XPOS)->EnableWindow(bFlag);
	GetDlgItem(IDC_EDIT_YPOS)->EnableWindow(bFlag);
	GetDlgItem(IDC_EDIT_DATA)->EnableWindow(bFlag);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogFaxHeader::OnRadioPageHeaderTypeClear() 
{
	bool bFlag = false;

	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_XPOS)->EnableWindow(bFlag);
	GetDlgItem(IDC_EDIT_YPOS)->EnableWindow(bFlag);
	GetDlgItem(IDC_EDIT_DATA)->EnableWindow(bFlag);
}

void CDialogFaxHeader::OnRadioPageHeaderTypeSet() 
{
	bool bFlag = true;

	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_XPOS)->EnableWindow(bFlag);
	GetDlgItem(IDC_EDIT_YPOS)->EnableWindow(bFlag);
	GetDlgItem(IDC_EDIT_DATA)->EnableWindow(bFlag);
}
