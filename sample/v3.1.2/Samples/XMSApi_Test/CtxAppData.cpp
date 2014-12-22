// CtxAppData.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "CtxAppData.h"

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"
#include "XMSApi_Test_Event.h"
#include "XMSApi_Test_String.h"
#include "XMSApi_Test_Sub.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern ACSHandle_t		        g_acsHandle;
extern ACSHandle_t		        g_acsHandle;
extern TYPE_MY_DEVICE_STRUCT	DevOpened[MAX_DEVICE_ALLOW_OPEN];
extern int			            iOpenedIndex1;
extern int			            iOpenedIndex2;
extern DJ_U8			        g_u8UnitID;
extern char                     g_s8OwnAppName[];
extern char                     g_s8OthersAppName[];

App_Data_Struct                 g_stAppData;
DJ_U8                           g_u8IsUsed = 0;
DJ_U8                           g_u8IsSendAppDataFlag = 0;
UserData4CTX                    g_stUserDataCTX;

extern ACSHandle_t		        g_acsHandle;

/////////////////////////////////////////////////////////////////////////////
// CCtxAppData dialog


CCtxAppData::CCtxAppData(CWnd* pParent /*=NULL*/)
	: CDialog(CCtxAppData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCtxAppData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCtxAppData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCtxAppData)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCtxAppData, CDialog)
	//{{AFX_MSG_MAP(CCtxAppData)
	ON_BN_CLICKED(IDC_BUTTON_SendData, OnBUTTONSendData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCtxAppData message handlers

void CCtxAppData::OnOK() 
{
	CDialog::OnOK();
}

void CCtxAppData::OnBUTTONSendData() 
{
	char temp[100] = {0}, MsgStr[100] = {0};
	int  iTemp = 0;
	RetCode_t r = 0;
	DeviceID_t stTempDevID = g_stAppData.OthersCTXDevID;

	memset( &g_stAppData, 0, sizeof(g_stAppData) );

	g_stAppData.OthersCTXDevID = stTempDevID;

	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_SRC_APP_REG_NAME)->GetWindowText( g_stAppData.s8SrcAppRegName, 20 );
	
	GetDlgItem(IDC_EDIT_SRC_APP_UNITID)->GetWindowText( temp, 20 );
	sscanf( temp, "%d", &iTemp);
    g_stAppData.u8SrcUnitID = iTemp;

	GetDlgItem(IDC_EDIT_DEST_APP_REG_NAME)->GetWindowText( g_stAppData.s8DestAppRegName, 20 );

	GetDlgItem(IDC_EDIT_DEST_APP_UNITID)->GetWindowText( temp, 20 );
	sscanf( temp, "%d", &iTemp);
    g_stAppData.u8DestUnitID = iTemp;

	GetDlgItem(IDC_EDIT_DEST_APP_REQ_TYPE)->GetWindowText( temp, 20 );
	sscanf( temp, "%d", &iTemp);
    g_stAppData.u8AppRegType = iTemp;

	GetDlgItem(IDC_EDIT_TEST_NUMBER_1)->GetWindowText( temp, 20 );
	sscanf( temp, "%d", &iTemp);
    g_stAppData.s32TestNum1 = iTemp;

	GetDlgItem(IDC_EDIT_TEST_NUMBER_2)->GetWindowText( temp, 20 );
	sscanf( temp, "%d", &iTemp);
    g_stAppData.s32TestNum2 = iTemp;

	GetDlgItem(IDC_EDIT_TEST_STRING)->GetWindowText( g_stAppData.s8TestString, 100 );

	g_stUserDataCTX.s32TestNum1 = g_stAppData.s32TestNum1;
	g_stUserDataCTX.s32TestNum2 = g_stAppData.s32TestNum2;
	strcpy( g_stUserDataCTX.s8TestString, g_stAppData.s8TestString );

	g_u8IsUsed = 1;
	
	if ( XMS_DEVMAIN_CTX != DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain )
	{
		sprintf ( MsgStr, "The iOpenedIndex1 device must be CTX DEV.");
		AfxMessageBox ( MsgStr );

		return;
	}

    g_stUserDataCTX.CTXDevID = DevOpened[iOpenedIndex1].DevID;

	r = XMS_ctxSendAppData( g_acsHandle, 
		                    g_stAppData.s8SrcAppRegName, 
							g_stAppData.s8DestAppRegName, 
							g_stAppData.u8AppRegType, 
							(DJ_Void*)&g_stUserDataCTX,
							sizeof(g_stUserDataCTX),
							g_stAppData.u8SrcUnitID, 
							g_stAppData.u8DestUnitID, 
							&DevOpened[iOpenedIndex1].DevID,
							NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctxSendAppData() FAIL! (%d %d)", 
			r, g_stAppData.u8SrcUnitID,g_stAppData.u8DestUnitID  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr);
	}
	else
	{
		sprintf ( MsgStr, "X(%d) XMS_ctxSendAppData() success! (%d %d)", 
			r, g_stAppData.u8SrcUnitID,g_stAppData.u8DestUnitID  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr);

	}

	g_u8IsSendAppDataFlag = 1;

}

BOOL CCtxAppData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	char temp[100] = {0};
	DeviceID_t stTempDevID = g_stAppData.OthersCTXDevID;


	// TODO: Add extra initialization here
	if ( 1 != g_u8IsUsed )
	{
		memset( &g_stAppData, 0, sizeof(g_stAppData) );
	}

  	g_stAppData.OthersCTXDevID = stTempDevID;
 
	g_stAppData.u8SrcUnitID = g_u8UnitID;

	strcpy( g_stAppData.s8SrcAppRegName, g_s8OwnAppName);

	GetDlgItem(IDC_EDIT_SRC_APP_REG_NAME)->SetWindowText( g_stAppData.s8SrcAppRegName);

	
	sprintf(temp, "%d", g_stAppData.u8SrcUnitID );
	GetDlgItem(IDC_EDIT_SRC_APP_UNITID)->SetWindowText(temp );

	GetDlgItem(IDC_EDIT_SRC_CTX_DEVID)->SetWindowText( GetString_DeviceAll(&DevOpened[iOpenedIndex1].DevID) );

	GetDlgItem(IDC_EDIT_DEST_APP_REG_NAME)->SetWindowText( g_stAppData.s8DestAppRegName);

    sprintf(temp, "%d", g_stAppData.u8DestUnitID );
	GetDlgItem(IDC_EDIT_DEST_APP_UNITID)->SetWindowText( temp );

    sprintf(temp, "%d", g_stAppData.u8AppRegType );
	GetDlgItem(IDC_EDIT_DEST_APP_REQ_TYPE)->SetWindowText( temp );

    sprintf(temp, "%d", g_stAppData.s32TestNum1 );
	GetDlgItem(IDC_EDIT_TEST_NUMBER_1)->SetWindowText( temp );

    sprintf(temp, "%d", g_stAppData.s32TestNum2 );
	GetDlgItem(IDC_EDIT_TEST_NUMBER_2)->SetWindowText( temp );

	GetDlgItem(IDC_EDIT_TEST_STRING)->SetWindowText( g_stAppData.s8TestString );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
