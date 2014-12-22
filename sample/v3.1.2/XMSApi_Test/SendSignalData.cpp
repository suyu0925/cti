// SendSignalData.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "SendSignalData.h"

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"
#include "XMSApi_Test_Event.h"
#include "XMSApi_Test_String.h"
#include "XMSApi_Test_Sub.h"
#include "XMSApi_Test_Func.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendSignalData dialog


CSendSignalData::CSendSignalData(CWnd* pParent /*=NULL*/)
	: CDialog(CSendSignalData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendSignalData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSendSignalData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendSignalData)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendSignalData, CDialog)
	//{{AFX_MSG_MAP(CSendSignalData)
	ON_BN_CLICKED(IDC_BUTTON_RUN, OnButtonRun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendSignalData message handlers

void CSendSignalData::OnButtonRun() 
{
	// TODO: Add your control notification handler code here
		// TODO: Add your control notification handler code here
	DJ_U16      u16SignalMsgType = 0;
	
	//= XMS_324_CMD_TYPE_NORMAL_START; //1 == XMS_324_CMD_TYPE_NORMAL_START;
	// TODO: Add your control notification handler code here
    if ( ((CButton *)GetDlgItem ( IDC_RADIO_XMS_324_CMD_TYPE_NORMAL_START ))->GetCheck() )
		u16SignalMsgType = XMS_324_CMD_TYPE_NORMAL_START;
	else if ( ((CButton *)GetDlgItem ( IDC_RADIO_XMS_324_CMD_TYPE_MONITOR_START ))->GetCheck() )
		u16SignalMsgType = XMS_324_CMD_TYPE_MONITOR_START;
	else if ( ((CButton *)GetDlgItem ( IDC_RADIO_XMS_324_CMD_TYPE_STOP ))->GetCheck() )
		u16SignalMsgType = XMS_324_CMD_TYPE_STOP;
	else if ( ((CButton *)GetDlgItem ( IDC_RADIO_XMS_324_CMD_TYPE_RESET ))->GetCheck() )
		u16SignalMsgType = XMS_324_CMD_TYPE_RESET;
	else 
		return;

	DoFunc_SendSignalMsg(u16SignalMsgType);
}

BOOL CSendSignalData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CButton *)GetDlgItem ( IDC_RADIO_XMS_324_CMD_TYPE_NORMAL_START ))->SetCheck(true);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
