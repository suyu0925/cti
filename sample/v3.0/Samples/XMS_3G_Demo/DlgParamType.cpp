// DlgParamType.cpp : implementation file
//

#include "stdafx.h"
#include "SP.h"
#include "DlgParamType.h"
#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgParamType dialog


CDlgParamType::CDlgParamType(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParamType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgParamType)
	//}}AFX_DATA_INIT
	m_iDevType = -1;
}


void CDlgParamType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgParamType)
	DDX_Control(pDX, IDC_COB_PARAMTYPE, m_CobParamType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgParamType, CDialog)
	//{{AFX_MSG_MAP(CDlgParamType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgParamType message handlers

void CDlgParamType::OnOK() 
{
	// TODO: Add extra validation here
	m_iParamType = m_CobParamType.GetCurSel();

	CDialog::OnOK();
}

BOOL CDlgParamType::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	switch(m_iDevType)
	{
	case XMS_DEVMAIN_VOIP:
		m_CobParamType.InsertString(0, "ACCESS");
		m_CobParamType.InsertString(1, "VOICE");
		m_CobParamType.InsertString(2, "SESSION");
		m_CobParamType.InsertString(3, "RTPADDR");
		m_CobParamType.InsertString(4, "RTCPADDR");
		m_CobParamType.InsertString(5, "CODEC");
		m_CobParamType.InsertString(6, "MIXER");
		m_CobParamType.SetCurSel(6);
		break;
	case XMS_DEVMAIN_VOICE:
		m_CobParamType.InsertString(0, "UNIPARAM");
		m_CobParamType.InsertString(1, "MEDIA PAMRA");
		m_CobParamType.InsertString(2, "CN PAMRA");
		m_CobParamType.InsertString(3, "MIXER");
		m_CobParamType.InsertString(4, "3G324M_TCS");
		m_CobParamType.SetCurSel(4);
		break;
	case XMS_DEVMAIN_RTPX:
		m_CobParamType.InsertString(0, "INPUT");
		m_CobParamType.InsertString(1, "OUTPUT");
		m_CobParamType.InsertString(2, "MIXER");
		m_CobParamType.InsertString(3, "ADDR");
		m_CobParamType.InsertString(4, "AUDIO INPUT");
		m_CobParamType.InsertString(5, "AUDIO OUTPUT");
		m_CobParamType.InsertString(6, "AUDIO MIXER");
		m_CobParamType.InsertString(7, "AUDIO ADDR");
		m_CobParamType.SetCurSel(0);
		break;
	default:
		break;		
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
