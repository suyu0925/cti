// DlgCmdParamDataCAS.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgCmdParamDataCAS.h"
#include "DJAcsDataDef.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char cfg_Acs_m_u8CalledTableCount[20];
extern char cfg_Acs_m_u8CalledLen[20];
extern char cfg_Acs_m_u8CalledTimeOut[20];
extern char cfg_Acs_m_u8NeedCaller[20];
extern char cfg_Acs_m_u8AreaCodeLen[20];
extern char cfg_Acs_m_u8KA[20];
extern char cfg_Acs_m_u8KD[20];
extern char cfg_Acs_m_u8ControlMode[20];
extern char cfg_Acs_m_u8CountryCode[20];
extern CmdParamData_CAS_t g_CmdParamDataCAS;
/////////////////////////////////////////////////////////////////////////////
// CDlgCmdParamDataCAS dialog


CDlgCmdParamDataCAS::CDlgCmdParamDataCAS(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCmdParamDataCAS::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCmdParamDataCAS)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgCmdParamDataCAS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCmdParamDataCAS)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CDlgCmdParamDataCAS::OnInitDialog()
{
	CDialog::OnInitDialog();
	GetDlgItem ( IDC_m_u8CalledTableCount )->SetWindowText ( cfg_Acs_m_u8CalledTableCount );
	GetDlgItem ( IDC_m_CalledTable )->SetWindowText ( "0" );
	GetDlgItem ( IDC_m_u8CalledLen )->SetWindowText ( cfg_Acs_m_u8CalledLen);
	GetDlgItem ( IDC_m_u8AreaCodeLen )->SetWindowText ( cfg_Acs_m_u8AreaCodeLen);
	GetDlgItem ( IDC_m_u8CalledTimeOut )->SetWindowText ( cfg_Acs_m_u8CalledTimeOut);
	GetDlgItem ( IDC_m_u8KA )->SetWindowText ( cfg_Acs_m_u8KA );
	GetDlgItem ( IDC_m_u8KD )->SetWindowText ( cfg_Acs_m_u8KD );

	switch (atoi(cfg_Acs_m_u8CountryCode))
	{
	   case CHINA:
		   {
			   ((CButton *)GetDlgItem ( IDC_CHINA ))->SetCheck(1);
		   }
   	       break;
	   case KOREA:
		   {
			   ((CButton *)GetDlgItem ( IDC_KOREA ))->SetCheck(1);
		   }
   	       break;
	   case INDIA:
		   {
			   ((CButton *)GetDlgItem ( IDC_INDIA ))->SetCheck(1);
		   }
		   break;
	   case VIETNAM:
		   {
			   ((CButton *)GetDlgItem ( IDC_VIETNAM ))->SetCheck(1);
		   }
   	       break;
	   case COUNTRY_END:
		   {
			   ((CButton *)GetDlgItem ( IDC_COUNTRY_END ))->SetCheck(1);
		   }
		   break;
	   default:
		   break;
   }
	
	return TRUE;
}
BEGIN_MESSAGE_MAP(CDlgCmdParamDataCAS, CDialog)
	//{{AFX_MSG_MAP(CDlgCmdParamDataCAS)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCmdParamDataCAS message handlers

void CDlgCmdParamDataCAS::OnOK() 
{
	// TODO: Add extra validation here
	int iTmpVal;
	GetDlgItem ( IDC_m_u8CalledTableCount )->GetWindowText ( cfg_Acs_m_u8CalledTableCount, 20 );
	sscanf ( cfg_Acs_m_u8CalledTableCount, "%d", &iTmpVal );
	g_CmdParamDataCAS.m_u8CalledTableCount = iTmpVal;
	
	GetDlgItem ( IDC_m_u8CalledLen )->GetWindowText ( cfg_Acs_m_u8CalledLen, 20 );
	sscanf ( cfg_Acs_m_u8CalledLen, "%d", &iTmpVal );
    g_CmdParamDataCAS.m_u8CalledLen = iTmpVal;
	
	GetDlgItem ( IDC_m_u8AreaCodeLen )->GetWindowText ( cfg_Acs_m_u8AreaCodeLen, 20 );
	sscanf ( cfg_Acs_m_u8AreaCodeLen, "%d", &iTmpVal );
	g_CmdParamDataCAS.m_u8AreaCodeLen = iTmpVal;

	GetDlgItem ( IDC_m_u8CalledTimeOut )->GetWindowText ( cfg_Acs_m_u8CalledTimeOut, 20 );
	sscanf ( cfg_Acs_m_u8CalledTimeOut, "%d", &iTmpVal );
	g_CmdParamDataCAS.m_u8CalledTimeOut = iTmpVal;

	GetDlgItem ( IDC_m_u8AreaCodeLen )->GetWindowText ( cfg_Acs_m_u8AreaCodeLen, 20 );
	sscanf ( cfg_Acs_m_u8AreaCodeLen, "%d", &iTmpVal );
	g_CmdParamDataCAS.m_u8AreaCodeLen = iTmpVal;

	GetDlgItem ( IDC_m_u8KA )->GetWindowText ( cfg_Acs_m_u8KA, 20 );
	sscanf ( cfg_Acs_m_u8KA, "%d", &iTmpVal );
	g_CmdParamDataCAS.m_u8KA = iTmpVal;

	GetDlgItem ( IDC_m_u8KD )->GetWindowText ( cfg_Acs_m_u8KD, 20 );
	sscanf ( cfg_Acs_m_u8KD, "%d", &iTmpVal );
	g_CmdParamDataCAS.m_u8KD = iTmpVal;

	if ( ((CButton *)GetDlgItem ( IDC_Yes ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_u8NeedCaller,"1");
		g_CmdParamDataCAS.m_u8NeedCaller = 1;
	}
	
	if ( ((CButton *)GetDlgItem ( IDC_No ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_u8NeedCaller,"2");
		g_CmdParamDataCAS.m_u8NeedCaller = 0;
	}
	
	if ( ((CButton *)GetDlgItem ( IDC_None ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_u8ControlMode,"0");
		g_CmdParamDataCAS.m_u8ControlMode = 0;
	}

	if ( ((CButton *)GetDlgItem ( IDC_Caller_Control ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_u8ControlMode,"1");
		g_CmdParamDataCAS.m_u8ControlMode = 1;
	}

	if ( ((CButton *)GetDlgItem ( IDC_Called_Control ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_u8ControlMode,"2");
		g_CmdParamDataCAS.m_u8ControlMode = 2;
	}

	if ( ((CButton *)GetDlgItem ( IDC_CHINA ))->GetCheck() )
	{
		strcpy(cfg_Acs_m_u8CountryCode,"1");
		g_CmdParamDataCAS.m_u8CountryCode = CHINA;
	}
	
	if ( ((CButton *)GetDlgItem ( IDC_KOREA ))->GetCheck() )
	{
		//strcpy(cfg_Acs_m_u8CountryCode,"2");
		g_CmdParamDataCAS.m_u8CountryCode = KOREA;
	}
	
	if ( ((CButton *)GetDlgItem ( IDC_INDIA ))->GetCheck() )
	{
		//strcpy(cfg_Acs_m_u8CountryCode,"3");
		g_CmdParamDataCAS.m_u8CountryCode = INDIA;
	}

	if ( ((CButton *)GetDlgItem ( IDC_VIETNAM ))->GetCheck() )
	{
		//strcpy(cfg_Acs_m_u8CountryCode,"4");
		g_CmdParamDataCAS.m_u8CountryCode = VIETNAM;
	}

	if ( ((CButton *)GetDlgItem ( IDC_COUNTRY_END ))->GetCheck() )
	{
		//strcpy(cfg_Acs_m_u8CountryCode,"5");
		g_CmdParamDataCAS.m_u8CountryCode = COUNTRY_END;
	}

	sprintf(cfg_Acs_m_u8CountryCode, "%X", g_CmdParamDataCAS.m_u8CountryCode);

	CDialog::OnOK();
}
