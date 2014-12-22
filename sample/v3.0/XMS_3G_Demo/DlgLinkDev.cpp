// DlgLinkDev.cpp : implementation file
//

#include "stdafx.h"
#include "SP.h"
#include "DlgLinkDev.h"
#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLinkDev dialog


CDlgLinkDev::CDlgLinkDev(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLinkDev::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLinkDev)
	m_uiDestID = 0;
	m_uiUnit = 1;
	m_iType = 0;
	m_sOverlayFile = _T("");
	//}}AFX_DATA_INIT
}


void CDlgLinkDev::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLinkDev)
	DDX_Control(pDX, IDC_CMB_DESTTYPE, m_cmbDestType);
	DDX_Text(pDX, IDC_EDIT_DESTID, m_uiDestID);
	DDV_MinMaxUInt(pDX, m_uiDestID, 0, 128);
	DDX_Text(pDX, IDC_EDIT_UNIT, m_uiUnit);
	DDV_MinMaxUInt(pDX, m_uiUnit, 1, 128);
	DDX_Text(pDX, IDC_EDIT_OVERLAYFILE, m_sOverlayFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLinkDev, CDialog)
	//{{AFX_MSG_MAP(CDlgLinkDev)
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE, OnButtonOpenfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLinkDev message handlers

void CDlgLinkDev::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	m_iDestType = m_cmbDestType.GetCurSel();
	
	switch(m_iDestType)
	{
	case 0:
		m_iDestType = XMS_DEVMAIN_VOICE;
		break;
	case 1:
		m_iDestType = XMS_DEVMAIN_INTERFACE_CH;
		break;
	case 2:
		m_iDestType = XMS_DEVMAIN_VOIP;
		break;
	default:
		m_iDestType = 0;
		break;
	}
	
	CDialog::OnOK();
}

BOOL CDlgLinkDev::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbDestType.InsertString(0, "VOC");
	m_cmbDestType.InsertString(1, "Interface");
	m_cmbDestType.InsertString(2, "VOIP");
	m_cmbDestType.SetCurSel(0);
	if(m_iType == 1)
		SetWindowText("Unlink Device");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLinkDev::OnButtonOpenfile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog filedlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,     
		"All files(*.*)|*.*||", NULL); 
	
	if(filedlg.DoModal() == IDOK)
	{
		UpdateData(TRUE);
		m_sOverlayFile.Format("%s", filedlg.GetPathName());
		UpdateData(FALSE);
	}
}
