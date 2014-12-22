
//*****************************************************************************
//author       :  chenz
//DateTime    :  2010-7-26-10:57
//Description  :   增加CmdParamData_SS7RawFrame_t功能参数对话框
//position     :   XMSAip_Test                                                      
//*****************************************************************************

// DlgSS7SS7RawFrame.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgSS7SS7RawFrame.h"
#include "DJAcsDataDef.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSS7SS7RawFrame dialog
extern char cfg_ss7_m_u8UserType[20];
extern char cfg_ss7_m_u8LinkType[20];
extern char cfg_ss7_m_u8MsgType[20];
extern char cfg_ss7_m_u8InfoLen[20];
extern char cfg_ss7_m_u8UnitId[20];
extern char cfg_ss7_m_u8E1Port[20];
extern char cfg_ss7_m_u8Ts[20];
extern char cfg_ss7_m_u8Reserved1[20];
extern char cfg_ss7_m_u8Info[255];
extern char cfg_ss7_Reserved2[20];
extern CmdParamData_SS7RawFrame_t        g_SS7RawFrameParam ;

CDlgSS7SS7RawFrame::CDlgSS7SS7RawFrame(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSS7SS7RawFrame::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSS7SS7RawFrame)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSS7SS7RawFrame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSS7SS7RawFrame)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}
 
BOOL CDlgSS7SS7RawFrame::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	/*
	 * 从配置文件的取值中设置IDD_DIALOG_SS7RawFrame界面的初始化参数
	*/
	GetDlgItem ( IDC_INFOLEN )->SetWindowText ( cfg_ss7_m_u8InfoLen );

	GetDlgItem ( IDC_UNITID )->SetWindowText ( cfg_ss7_m_u8UnitId );

	GetDlgItem ( IDC_E1PORT )->SetWindowText ( cfg_ss7_m_u8E1Port );

	GetDlgItem ( IDC_U8TS )->SetWindowText ( cfg_ss7_m_u8Ts );

	GetDlgItem ( IDC_RESERVED1 )->SetWindowText ( cfg_ss7_m_u8Reserved1 );

	GetDlgItem ( IDC_U8INFO )->SetWindowText ( cfg_ss7_m_u8Info );

	GetDlgItem ( IDC_RESERVED2 )->SetWindowText ( cfg_ss7_Reserved2 );


	switch (atoi(cfg_ss7_m_u8UserType))
	{
	   case XMS_SS7_USER_TYPE_SCCP:
		   {
			   ((CButton *)GetDlgItem ( IDC_XMS_SS7_USER_TYPE_SCCP ))->SetCheck(1);
		   }
   	       break;
	   case XMS_SS7_USER_TYPE_TUP:
		   {
			   ((CButton *)GetDlgItem ( IDC_XMS_SS7_USER_TYPE_TUP ))->SetCheck(1);
		   }
   	       break;
	   case XMS_SS7_USER_TYPE_ISUP:
		   {
			   ((CButton *)GetDlgItem ( IDC_XMS_SS7_USER_TYPE_ISUP ))->SetCheck(1);
		   }
		   break;
	   default:
		   break;
   }

	switch (atoi(cfg_ss7_m_u8LinkType))
	{
	   case XMS_SS7_LINK_TYPE_ITU:
		   {
			  ((CButton *)GetDlgItem ( IDC_XMS_SS7_LINK_TYPE_ITU ))->SetCheck(1);
		   }
   	       break;
	   case XMS_SS7_LINK_TYPE_CHINA:
		   {
			   ((CButton *)GetDlgItem ( IDC_XMS_SS7_LINK_TYPE_CHINA ))->SetCheck(1);
		   }
   	       break;
	   default:
		   break;
   }

   switch (atoi(cfg_ss7_m_u8MsgType))
   {
	   case XMS_SS7_MSG_DATA:
		   {
			   ((CButton *)GetDlgItem ( IDC_XMS_SS7_MSG_DATA ))->SetCheck(1);
		   }
   	       break;
	   case XMS_SS7_MSG_CMD:
		   {
			   ((CButton *)GetDlgItem ( IDC_XMS_SS7_MSG_CMD ))->SetCheck(1);
		   }
   	       break;
	   case XMS_SS7_MSG_STATUS:
		   {
			   ((CButton *)GetDlgItem ( IDC_XMS_SS7_MSG_STATUS ))->SetCheck(1);
		   }
   	   break;
	   default:
	       break;
   }
	

	return TRUE;
}
BEGIN_MESSAGE_MAP(CDlgSS7SS7RawFrame, CDialog)
	//{{AFX_MSG_MAP(CDlgSS7SS7RawFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSS7SS7RawFrame message handlers

void CDlgSS7SS7RawFrame::OnOK() 
{
	// TODO: Add extra validation here
	char TmpStr[255];
	int iTmpVal;

	GetDlgItem ( IDC_INFOLEN )->GetWindowText ( cfg_ss7_m_u8InfoLen, 20 );
	sscanf ( cfg_ss7_m_u8InfoLen, "%d", &iTmpVal );
	g_SS7RawFrameParam.m_u8InfoLen = iTmpVal;
	
	GetDlgItem ( IDC_UNITID )->GetWindowText ( cfg_ss7_m_u8UnitId, 20 );
	sscanf ( cfg_ss7_m_u8UnitId, "%d", &iTmpVal );
	g_SS7RawFrameParam.m_u8UnitId = iTmpVal;
	
	GetDlgItem ( IDC_E1PORT )->GetWindowText ( cfg_ss7_m_u8E1Port, 20 );
	sscanf ( cfg_ss7_m_u8E1Port, "%d", &iTmpVal );
	g_SS7RawFrameParam.m_u8E1Port = iTmpVal;
	
	GetDlgItem ( IDC_U8TS )->GetWindowText ( cfg_ss7_m_u8Ts, 20 );
	sscanf ( cfg_ss7_m_u8Ts, "%d", &iTmpVal );
	g_SS7RawFrameParam.m_u8Ts = iTmpVal;
	
	GetDlgItem ( IDC_RESERVED1 )->GetWindowText ( cfg_ss7_m_u8Reserved1, 20 );
	sscanf ( cfg_ss7_m_u8Reserved1, "%d", &iTmpVal );
	g_SS7RawFrameParam.m_u8Reserved1 = iTmpVal;
	
	GetDlgItem ( IDC_U8INFO )->GetWindowText ( cfg_ss7_m_u8Info, 255 );
	sscanf ( cfg_ss7_m_u8Info, "%s", &TmpStr );
	strcpy((char *)g_SS7RawFrameParam.m_u8Info,TmpStr);
	
	GetDlgItem ( IDC_RESERVED2 )->GetWindowText ( cfg_ss7_Reserved2, 20 );
	sscanf ( cfg_ss7_Reserved2, "%d", &iTmpVal );
	g_SS7RawFrameParam.Reserved2 = iTmpVal;

	// g_SS7RawFrameParam.m_u8UserType
	if ( ((CButton *)GetDlgItem ( IDC_XMS_SS7_USER_TYPE_SCCP ))->GetCheck() )
	{
		g_SS7RawFrameParam.m_u8UserType = XMS_SS7_USER_TYPE_SCCP;
	}

	if ( ((CButton *)GetDlgItem ( IDC_XMS_SS7_USER_TYPE_TUP ))->GetCheck() )
	{
		g_SS7RawFrameParam.m_u8UserType = XMS_SS7_USER_TYPE_TUP;
	}

	if ( ((CButton *)GetDlgItem ( IDC_XMS_SS7_USER_TYPE_ISUP ))->GetCheck() )
	{
		g_SS7RawFrameParam.m_u8UserType = XMS_SS7_USER_TYPE_ISUP;
	}

	sprintf(cfg_ss7_m_u8UserType, "%X", g_SS7RawFrameParam.m_u8UserType);

	// g_SS7RawFrameParam.m_u8LinkType
	if ( ((CButton *)GetDlgItem ( IDC_XMS_SS7_LINK_TYPE_ITU ))->GetCheck() )
	{
		g_SS7RawFrameParam.m_u8LinkType = XMS_SS7_LINK_TYPE_ITU;
	}
	
	if ( ((CButton *)GetDlgItem ( IDC_XMS_SS7_LINK_TYPE_CHINA))->GetCheck() )
	{
		g_SS7RawFrameParam.m_u8LinkType = XMS_SS7_LINK_TYPE_CHINA;
	}

	sprintf(cfg_ss7_m_u8LinkType, "%X", g_SS7RawFrameParam.m_u8LinkType);

	// g_SS7RawFrameParam.m_u8MsgType
	if ( ((CButton *)GetDlgItem ( IDC_XMS_SS7_MSG_DATA))->GetCheck() )
	{
		g_SS7RawFrameParam.m_u8MsgType = XMS_SS7_MSG_DATA;
	}
	
	if ( ((CButton *)GetDlgItem ( IDC_XMS_SS7_MSG_CMD ))->GetCheck() )
	{
		g_SS7RawFrameParam.m_u8MsgType = XMS_SS7_MSG_CMD;
	}

	if ( ((CButton *)GetDlgItem ( IDC_XMS_SS7_MSG_STATUS ))->GetCheck() )
	{
		g_SS7RawFrameParam.m_u8MsgType = XMS_SS7_MSG_STATUS;
	}

	sprintf(cfg_ss7_m_u8MsgType, "%X", g_SS7RawFrameParam.m_u8MsgType);

	CDialog::OnOK();
}
