// txLinkCtxDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "txLinkCtxDlg.h"

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
extern App_Data_Struct          g_stAppData;

/////////////////////////////////////////////////////////////////////////////
// CtxLinkCtxDlg dialog


CtxLinkCtxDlg::CtxLinkCtxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtxLinkCtxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CtxLinkCtxDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CtxLinkCtxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CtxLinkCtxDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CtxLinkCtxDlg, CDialog)
	//{{AFX_MSG_MAP(CtxLinkCtxDlg)
	ON_BN_CLICKED(ID_CTX_LINK_2_CTX, OnCtxLink2Ctx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CtxLinkCtxDlg message handlers

BOOL CtxLinkCtxDlg::OnInitDialog() 
{	
	CDialog::OnInitDialog();
	
	GetDlgItem ( IDC_EDIT_SRCDEV )->SetWindowText ( GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
	GetDlgItem ( IDC_EDIT_DESTDEV )->SetWindowText ( GetString_DeviceAll (&g_stAppData.OthersCTXDevID) );
	
	CComboBox * pCB;
	pCB = (CComboBox *)this->GetDlgItem(IDC_COMBO_Link_Option);
    if (NULL == pCB)
	{
		ASSERT(0);
		return FALSE;
	}
    
	pCB->InsertString(0, "Link Opt Reset");
	pCB->InsertString(1, "Link Opt Link");
	pCB->InsertString(2, "Link Opt Unlink");
	pCB->InsertString(3, "Link Opt DualLink");
	pCB->InsertString(4, "Link Opt DualUnlink");

	pCB->SetItemData( 0, CTX_LINK_OPTION_RESET );
	pCB->SetItemData( 1, CTX_LINK_OPTION_LINK);
	pCB->SetItemData( 2, CTX_LINK_OPTION_UNLINK);
	pCB->SetItemData( 3, CTX_LINK_OPTION_DUALLINK);
	pCB->SetItemData( 4, CTX_LINK_OPTION_DUALUNLINK);

	pCB->SetTopIndex(3);
	pCB->SetCurSel(3);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CtxLinkCtxDlg::OnCtxLink2Ctx() 
{
	char szBuf[100] = {0};
	char MsgStr[100]={0};
	int nLinkOpt, index;
	int r = 0;
	DeviceID_t destDev;

	memcpy(&destDev,&DevOpened[iOpenedIndex1].DevID,sizeof(DeviceID_t));	

    destDev = g_stAppData.OthersCTXDevID;

	CComboBox *pCB;
	pCB = (CComboBox *)this->GetDlgItem(IDC_COMBO_Link_Option);
	if (NULL == pCB)
	{
		ASSERT(0);
		return;
	}

	index = pCB->GetCurSel();
	nLinkOpt = pCB->GetItemData(index);
		
	r = XMS_ctxLink(g_acsHandle,&DevOpened[iOpenedIndex1].DevID,&destDev,nLinkOpt,NULL);
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctxLink() FAIL! (%s %d)", 
			r, szBuf,nLinkOpt  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr);
	}
	else
	{
		sprintf ( MsgStr, "X(%d) XMS_ctxLink() success! (%s %d)", 
			r, szBuf,nLinkOpt  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr);
	}	
}
