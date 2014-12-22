//*****************************************************************************
//author       :  chenz
//DateTime    :  2010-7-26-3:57 
//Description  :  增加Acs_ParamData_UserReadXmsBoardInfo功能参数对话框
//position     :  XMSApi_Test.cpp                                                     
//*****************************************************************************

// DlgUserReadXmsBoardInfo.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgUserReadXmsBoardInfo.h"
#include "DJAcsDataDef.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUserReadXmsBoardInfo dialog
// UserReadXmsBoardInfo author:chenz
extern char cfg_Acs_m_u8MacAddr[20];
extern char cfg_Acs_m_u8ChassisType[20];
extern char cfg_Acs_m_u8ChassisIndex[20];
extern char cfg_Acs_m_u8ChassisSlot[20];
extern char cfg_Acs_m_u8SubBoardIndex[20];
extern char cfg_Acs_m_u8BoardType[20];
extern char cfg_Acs_rfu1[20];
extern char cfg_Acs_m_s8SystemName[32];
extern char cfg_Acs_m_s8PlatformType[20];
extern char cfg_Acs_m_s8UserCode[20];
extern char cfg_Acs_m_s32SysId[20];
extern char cfg_Acs_rfu2[20];
extern char cfg_Acs_m_s8FirmwareName[20];
extern char cfg_Acs_m_s8FirmwareVersion[20];
extern char cfg_Acs_m_s8RevisionDate[20];
extern Acs_ParamData_UserReadXmsBoardInfo g_UserReadXmsBoardInfo;

CDlgUserReadXmsBoardInfo::CDlgUserReadXmsBoardInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUserReadXmsBoardInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUserReadXmsBoardInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgUserReadXmsBoardInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUserReadXmsBoardInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CDlgUserReadXmsBoardInfo::OnInitDialog()
{
	/*
	 * 从配置文件的取值中设置IDD_DIALOG_SS7RawFrame界面的初始化参数
	*/
	GetDlgItem ( IDC_u8MacAddr )->SetWindowText ( cfg_Acs_m_u8MacAddr );

	GetDlgItem ( IDC_u8ChassisIndex )->SetWindowText ( cfg_Acs_m_u8ChassisIndex );

	GetDlgItem ( IDC_u8ChassisSlot )->SetWindowText ( cfg_Acs_m_u8ChassisSlot );

	GetDlgItem ( IDC_u8SubBoardIndex )->SetWindowText ( cfg_Acs_m_u8SubBoardIndex );

	GetDlgItem ( IDC_rfu1 )->SetWindowText ( cfg_Acs_rfu1 );

	GetDlgItem ( IDC_s8SystemName )->SetWindowText ( cfg_Acs_m_s8SystemName );

	GetDlgItem ( IDC_s8UserCode )->SetWindowText ( cfg_Acs_m_s8UserCode );

	GetDlgItem ( IDC_s32SysId )->SetWindowText ( cfg_Acs_m_s32SysId );

	GetDlgItem ( IDC_rfu2 )->SetWindowText ( cfg_Acs_rfu2 );

	GetDlgItem ( IDC_s8FirmwareName )->SetWindowText ( cfg_Acs_m_s8FirmwareName );

	GetDlgItem ( IDC_s8FirmwareVersion )->SetWindowText ( cfg_Acs_m_s8FirmwareVersion );

	GetDlgItem ( IDC_s8RevisionDate )->SetWindowText ( cfg_Acs_m_s8RevisionDate );


	switch (atoi(cfg_Acs_m_u8BoardType))
	{
		case 0:
			((CButton *)GetDlgItem ( IDC_itp_1200 ))->SetCheck(1);
			break;	
		case 1:
			((CButton *)GetDlgItem ( IDC_itp_2400 ))->SetCheck(1);
			break;
		case 2:
			((CButton *)GetDlgItem ( IDC_itp_4800 ))->SetCheck(1);
			break;
		default:
			break;
	}
 
	switch (atoi(cfg_Acs_m_u8ChassisType))
	{
	case 0:
		((CButton *)GetDlgItem ( IDC_ITP1200 ))->SetCheck(1);
		break;	
	case 1:
		((CButton *)GetDlgItem ( IDC_3U_chassis ))->SetCheck(1);
		break;
	case 2:
		((CButton *)GetDlgItem ( IDC_5U_chassis ))->SetCheck(1);
		break;
	case 3:
		((CButton *)GetDlgItem ( IDC_11U_chassis ))->SetCheck(1);
		break;
	default:
		break;
	}
 
	switch (atoi(cfg_Acs_m_u8ChassisType))
	{
	case 1:
	    ((CButton *)GetDlgItem ( IDC_callback ))->SetCheck(1);
		break;	
	case 2:
		((CButton *)GetDlgItem ( IDC_keygoe_1000 ))->SetCheck(1);
		break;
	case 3:
		((CButton *)GetDlgItem ( IDC_keygoe_3000 ))->SetCheck(1);
		break;
	case 4:
		((CButton *)GetDlgItem ( IDC_keygoe_8000 ))->SetCheck(1);
		break;
	default:
		break;
	}

	return TRUE;
}
BEGIN_MESSAGE_MAP(CDlgUserReadXmsBoardInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgUserReadXmsBoardInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUserReadXmsBoardInfo message handlers

void CDlgUserReadXmsBoardInfo::OnOK() 
{
	// TODO: Add extra validation here
	// TODO: Add extra validation here
	int iTmpVal;
	
	GetDlgItem ( IDC_u8MacAddr )->GetWindowText ( cfg_Acs_m_u8MacAddr, 20 );
	strcpy((char *)g_UserReadXmsBoardInfo.m_u8MacAddr,cfg_Acs_m_u8MacAddr);
	
	//playpropetry . m_u8SrcMode
	if ( ((CButton *)GetDlgItem ( IDC_ITP1200 ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_u8ChassisType,"0");
		g_UserReadXmsBoardInfo.m_u8ChassisType = 0;
	}

	if ( ((CButton *)GetDlgItem ( IDC_3U_chassis ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_u8ChassisType,"1");
		g_UserReadXmsBoardInfo.m_u8ChassisType = 1;
	}

	if ( ((CButton *)GetDlgItem ( IDC_5U_chassis ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_u8ChassisType,"2");
		g_UserReadXmsBoardInfo.m_u8ChassisType = 2;
	}

	if ( ((CButton *)GetDlgItem ( IDC_11U_chassis ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_u8ChassisType,"3");
		g_UserReadXmsBoardInfo.m_u8ChassisType = 3;
	}
	
	GetDlgItem ( IDC_u8ChassisIndex )->GetWindowText ( cfg_Acs_m_u8ChassisIndex, 20 );
	sscanf ( cfg_Acs_m_u8ChassisIndex, "%d", &iTmpVal );
	g_UserReadXmsBoardInfo.m_u8ChassisIndex = iTmpVal;
	
	GetDlgItem ( IDC_u8ChassisSlot )->GetWindowText ( cfg_Acs_m_u8ChassisSlot, 20 );
	sscanf ( cfg_Acs_m_u8ChassisSlot, "%d", &iTmpVal );
	g_UserReadXmsBoardInfo.m_u8ChassisSlot = iTmpVal;
	
	GetDlgItem ( IDC_u8SubBoardIndex )->GetWindowText ( cfg_Acs_m_u8SubBoardIndex, 20 );
	sscanf ( cfg_Acs_m_u8SubBoardIndex, "%d", &iTmpVal );
	g_UserReadXmsBoardInfo.m_u8SubBoardIndex = iTmpVal;
	

	//playpropetry . m_u8SrcMode
	if ( ((CButton *)GetDlgItem ( IDC_itp_1200 ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_u8BoardType,"0");
		g_UserReadXmsBoardInfo.m_u8BoardType = 0;
	}
	
	if ( ((CButton *)GetDlgItem ( IDC_itp_2400 ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_u8BoardType,"1");
		g_UserReadXmsBoardInfo.m_u8BoardType = 1;
	}
	
	if ( ((CButton *)GetDlgItem ( IDC_itp_4800 ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_u8BoardType,"2");
		g_UserReadXmsBoardInfo.m_u8BoardType = 2;
	}
	
	GetDlgItem ( IDC_rfu1 )->GetWindowText ( cfg_Acs_rfu1, 20 );
	strcpy((char *)g_UserReadXmsBoardInfo.rfu1,cfg_Acs_rfu1);
	
	GetDlgItem ( IDC_s8SystemName )->GetWindowText ( cfg_Acs_m_s8SystemName, 32);
	strcpy((char *)g_UserReadXmsBoardInfo.m_s8SystemName,cfg_Acs_m_s8SystemName);

	if ( ((CButton *)GetDlgItem ( IDC_callback ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_s8PlatformType,"1");
		g_UserReadXmsBoardInfo.m_s8PlatformType = 1;
	}
	
	if ( ((CButton *)GetDlgItem ( IDC_keygoe_1000 ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_s8PlatformType,"2");
		g_UserReadXmsBoardInfo.m_s8PlatformType = 2;
	}
	
	if ( ((CButton *)GetDlgItem ( IDC_keygoe_3000 ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_s8PlatformType,"3");
		g_UserReadXmsBoardInfo.m_s8PlatformType = 3;
	}

	if ( ((CButton *)GetDlgItem ( IDC_keygoe_8000 ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_s8PlatformType,"4");
		g_UserReadXmsBoardInfo.m_s8PlatformType = 4;
	}
	
	GetDlgItem ( IDC_s8UserCode )->GetWindowText ( cfg_Acs_m_s8UserCode, 20 );
	strcpy((char *)g_UserReadXmsBoardInfo.m_s8UserCode,cfg_Acs_m_s8UserCode);

	GetDlgItem ( IDC_s32SysId )->GetWindowText ( cfg_Acs_m_s32SysId, 20 );
	sscanf ( cfg_Acs_m_s32SysId, "%d", &iTmpVal );
	g_UserReadXmsBoardInfo.m_s32SysId = iTmpVal;

	GetDlgItem ( IDC_rfu2 )->GetWindowText ( cfg_Acs_rfu2, 20 );
	strcpy((char *)g_UserReadXmsBoardInfo.rfu2,cfg_Acs_rfu2);

	GetDlgItem ( IDC_s8FirmwareName )->GetWindowText ( cfg_Acs_m_s8FirmwareName, 20 );
	strcpy((char *)g_UserReadXmsBoardInfo.m_s8FirmwareName,cfg_Acs_m_s8FirmwareName);

	GetDlgItem ( IDC_s8FirmwareVersion )->GetWindowText ( cfg_Acs_m_s8FirmwareVersion, 20 );
	strcpy((char *)g_UserReadXmsBoardInfo.m_s8FirmwareVersion,cfg_Acs_m_s8FirmwareVersion);

	GetDlgItem ( IDC_s8RevisionDate )->GetWindowText ( cfg_Acs_m_s8RevisionDate, 20 );
	strcpy((char *)g_UserReadXmsBoardInfo.m_s8RevisionDate,cfg_Acs_m_s8RevisionDate);

	CDialog::OnOK();
}
