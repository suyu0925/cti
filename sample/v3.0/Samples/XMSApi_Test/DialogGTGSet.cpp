// DialogGTGSet.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DialogGTGSet.h"
#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define MAX_PARAMETER_TYPE 3
int GTGiComboEnvelopParam = 0;

char GTGParamEnvelopStr[MAX_PARAMETER_TYPE][32]=
{
	"Mode_Any",
	"Mode_One",
	"Mode_Two"
};

extern CmdParamData_GtgFreq_t     g_GtgFreq[4];
extern CmdParamData_GtgProtoType_t g_GtgProto;

//------GTG set_freq-------
extern char gtg_cfg_freq_index1[20];
extern char gtg_cfg_freq_coef1[20];
extern char gtg_cfg_freq_index2[20];
extern char gtg_cfg_freq_coef2[20];
extern char gtg_cfg_freq_index3[20];
extern char gtg_cfg_freq_coef3[20];
extern char gtg_cfg_freq_index4[20];
extern char gtg_cfg_freq_coef4[20];

//------GTG Set Tone-------
extern char cfg_gtgid1[20];
extern char cfg_gtgfreqindex11[20];
extern char cfg_gtgfreqindex21[20];
extern char cfg_gtgthreshold11[20];
extern char cfg_gtgthreshold21[20];
extern char cfg_gtgenvelop1[20];
extern char cfg_gtgrepeatcount1[20];
extern char cfg_gtgontime11[20];
extern char cfg_gtgofftime11[20];
extern char cfg_gtgontime21[20];
extern char cfg_gtgofftime21[20];


extern char cfg_gtgid2[20];
extern char cfg_gtgfreqindex12[20];
extern char cfg_gtgfreqindex22[20];
extern char cfg_gtgthreshold12[20];
extern char cfg_gtgthreshold22[20];
extern char cfg_gtgenvelop2[20];
extern char cfg_gtgrepeatcount2[20];
extern char cfg_gtgontime12[20];
extern char cfg_gtgofftime12[20];
extern char cfg_gtgontime22[20];
extern char cfg_gtgofftime22[20];

extern char cfg_gtgid3[20];
extern char cfg_gtgfreqindex13[20];
extern char cfg_gtgfreqindex23[20];
extern char cfg_gtgthreshold13[20];
extern char cfg_gtgthreshold23[20];
extern char cfg_gtgenvelop3[20];
extern char cfg_gtgrepeatcount3[20];
extern char cfg_gtgontime13[20];
extern char cfg_gtgofftime13[20];
extern char cfg_gtgontime23[20];
extern char cfg_gtgofftime23[20];

extern char cfg_gtgid4[20];
extern char cfg_gtgfreqindex14[20];
extern char cfg_gtgfreqindex24[20];
extern char cfg_gtgthreshold14[20];
extern char cfg_gtgthreshold24[20];
extern char cfg_gtgenvelop4[20];
extern char cfg_gtgrepeatcount4[20];
extern char cfg_gtgontime14[20];
extern char cfg_gtgofftime14[20];
extern char cfg_gtgontime24[20];
extern char cfg_gtgofftime24[20];

extern char cfg_gtgid5[20];
extern char cfg_gtgfreqindex15[20];
extern char cfg_gtgfreqindex25[20];
extern char cfg_gtgthreshold15[20];
extern char cfg_gtgthreshold25[20];
extern char cfg_gtgenvelop5[20];
extern char cfg_gtgrepeatcount5[20];
extern char cfg_gtgontime15[20];
extern char cfg_gtgofftime15[20];
extern char cfg_gtgontime25[20];
extern char cfg_gtgofftime25[20];

extern char cfg_gtgid6[20];
extern char cfg_gtgfreqindex16[20];
extern char cfg_gtgfreqindex26[20];
extern char cfg_gtgthreshold16[20];
extern char cfg_gtgthreshold26[20];
extern char cfg_gtgenvelop6[20];
extern char cfg_gtgrepeatcount6[20];
extern char cfg_gtgontime16[20];
extern char cfg_gtgofftime16[20];
extern char cfg_gtgontime26[20];
extern char cfg_gtgofftime26[20];

/////////////////////////////////////////////////////////////////////////////
// CDialogGTGSet dialog

CDialogGTGSet::CDialogGTGSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogGTGSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogGTDSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogGTGSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogGTGSet)
	DDX_Control(pDX, IDC_COMBO_ENVELOP, m_GTGComboEnvelop);
	DDX_Control(pDX, IDC_TAB_GTG_TONE, m_tab_gtg_tone);
	DDX_Control(pDX, IDC_TAB_GTG_FREQ, m_tab_gtg_freq);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogGTGSet, CDialog)
	//{{AFX_MSG_MAP(CDialogGTGSet)
	ON_NOTIFY(NM_CLICK, IDC_TAB_GTG_FREQ, OnClickTabGtGFreq)
	ON_NOTIFY(NM_CLICK, IDC_TAB_GTG_TONE, OnClickTabGtGTone)
	ON_CBN_SELCHANGE(IDC_COMBO_ENVELOP, OnSelchangeComboEnvelop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogGTDSet message handlers

BOOL CDialogGTGSet::OnInitDialog() 
{
	char	TmpStr[256];
	int		iTmpVal = 0;
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_tab_gtg_freq.InsertItem( 0, _T("Set Freq1") );
	m_tab_gtg_freq.InsertItem( 1, _T("Set Freq2") );
	m_tab_gtg_freq.InsertItem( 2, _T("Set Freq3") );
	m_tab_gtg_freq.InsertItem( 3, _T("Set Freq4") );

	//default Setup
	//SetDlgItemText(IDC_EDIT_FREQ_INDEX,"0");
	//SetDlgItemText(IDC_EDIT_FREQ_COEF,"450");

	SetDlgItemText(IDC_EDIT_FREQ_INDEX,"0");
	SetDlgItemText(IDC_EDIT_FREQ_COEF,"450");

	m_tab_gtg_tone.InsertItem( 0, _T("Set Tone1") );
	m_tab_gtg_tone.InsertItem( 1, _T("Set Tone2") );
	m_tab_gtg_tone.InsertItem( 2, _T("Set Tone3") );
	m_tab_gtg_tone.InsertItem( 3, _T("Set Tone4") );
	m_tab_gtg_tone.InsertItem( 4, _T("Set Tone5") );
	m_tab_gtg_tone.InsertItem( 5, _T("Set Tone6") );

	// init m_ComboParam
	for ( int i = 0; i < MAX_PARAMETER_TYPE ; i ++ )
	{
		sprintf ( TmpStr, "%2d - %s", i, GTGParamEnvelopStr[i] );
		m_GTGComboEnvelop.AddString ( TmpStr );
	}
	//iComboEnveopParam = cfg_iComboParam;
	GTGiComboEnvelopParam = 0;
	m_GTGComboEnvelop.SetCurSel ( GTGiComboEnvelopParam );


	//Init the SetTone Parameter
	SetDlgItemText(IDC_EDIT_GTGID,"48");
	SetDlgItemText(IDC_EDIT_FREQ_INDEX1,"0");
	SetDlgItemText(IDC_EDIT_FREQ_INDEX2,"0");
	SetDlgItemText(IDC_EDIT_THRESHOLD1,"10");
	SetDlgItemText(IDC_EDIT_THRESHOLD2,"10");
	SetDlgItemText(IDC_EDIT_REPEATCOUNT,"2");
	SetDlgItemText(IDC_EDIT_ONTIME1,"50");
	SetDlgItemText(IDC_EDIT_ONTIME2,"50");
	SetDlgItemText(IDC_EDIT_OFFTIME1,"50");
	SetDlgItemText(IDC_EDIT_OFFTIME2,"50");

	m_GTGComboEnvelop.SetCurSel ( 0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogGTGSet::OnClickTabGtGFreq(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	char TmpStr[20];
	int iTmpVal;

	int id = m_tab_gtg_freq.GetCurSel();
	//IDC_EDIT_FREQ_INDEX
	sprintf(TmpStr,"%d",id);

	SetDlgItemText(IDC_EDIT_FREQ_INDEX,TmpStr);
	switch(id)
	{
	case 0:
		SetDlgItemText(IDC_EDIT_FREQ_COEF,"450");
		break;
	case 1:
		SetDlgItemText(IDC_EDIT_FREQ_COEF,"500");
		break;
	case 2:
		SetDlgItemText(IDC_EDIT_FREQ_COEF,"1000");
		break;
	case 3:
		SetDlgItemText(IDC_EDIT_FREQ_COEF,"2100");
		break;

	}

	GetDlgItem ( IDC_EDIT_FREQ_INDEX )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );

	GetDlgItem ( IDC_EDIT_FREQ_COEF )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	//g_FskSet.rxFilterWindow = iTmpVal;

	*pResult = 0;
}

void CDialogGTGSet::OnOK() 
{
	// TODO: Add extra validation here

	char TmpStr[20];
	//int	 iTmpVal;

	//Get GTDFreq Parameters
	
	GetDlgItem ( IDC_EDIT_FREQ_INDEX )->GetWindowText ( gtg_cfg_freq_index1, 20 );
	GetDlgItem ( IDC_EDIT_FREQ_COEF )->GetWindowText ( gtg_cfg_freq_coef1, 20 );
	sscanf ( gtg_cfg_freq_index1, "%d", &g_GtgFreq[0].m_u16Freq_Index );
	sscanf ( gtg_cfg_freq_coef1, "%d",  &g_GtgFreq[0].m_u16Freq_Coef );

	GetDlgItem ( IDC_EDIT_FREQ_INDEX )->GetWindowText ( gtg_cfg_freq_index2, 20 );
	GetDlgItem ( IDC_EDIT_FREQ_COEF )->GetWindowText ( gtg_cfg_freq_coef2, 20 );
	sscanf ( gtg_cfg_freq_index2, "%d", &g_GtgFreq[1].m_u16Freq_Index );
	sscanf ( gtg_cfg_freq_coef2, "%d",  &g_GtgFreq[1].m_u16Freq_Coef );

	GetDlgItem ( IDC_EDIT_FREQ_INDEX )->GetWindowText ( gtg_cfg_freq_index3, 20 );
	GetDlgItem ( IDC_EDIT_FREQ_COEF )->GetWindowText ( gtg_cfg_freq_coef3, 20 );
	sscanf ( gtg_cfg_freq_index3, "%d", &g_GtgFreq[2].m_u16Freq_Index );
	sscanf ( gtg_cfg_freq_coef3, "%d",  &g_GtgFreq[2].m_u16Freq_Coef );

	GetDlgItem ( IDC_EDIT_FREQ_INDEX )->GetWindowText ( gtg_cfg_freq_index4, 20 );
	GetDlgItem ( IDC_EDIT_FREQ_COEF )->GetWindowText ( gtg_cfg_freq_coef4, 20 );
	sscanf ( gtg_cfg_freq_index4, "%d", &g_GtgFreq[3].m_u16Freq_Index );
	sscanf ( gtg_cfg_freq_coef4, "%d",  &g_GtgFreq[3].m_u16Freq_Coef );
	



	//Get GTD_Tone Parameters
	GetDlgItem ( IDC_EDIT_GTGID )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &g_GtgProto.m_u8GTG_id);

	GetDlgItem ( IDC_EDIT_FREQ_INDEX1 )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &g_GtgProto.m_u8Freq1_Index );

	GetDlgItem ( IDC_EDIT_FREQ_INDEX2 )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &g_GtgProto.m_u8Freq2_Index );

	g_GtgProto.m_u16Envelope_Mode = m_GTGComboEnvelop.GetCurSel();

	GetDlgItem ( IDC_EDIT_THRESHOLD1 )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &g_GtgProto.m_u16Freq1_Amp);

	GetDlgItem ( IDC_EDIT_THRESHOLD2 )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &g_GtgProto.m_u16Freq2_Amp );

	GetDlgItem ( IDC_EDIT_REPEATCOUNT )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &g_GtgProto.m_u16Repeat_Count);

	GetDlgItem ( IDC_EDIT_ONTIME1 )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &g_GtgProto.m_u16On_Time1 );

	GetDlgItem ( IDC_EDIT_OFFTIME1 )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &g_GtgProto.m_u16Off_Time1);
	
	GetDlgItem ( IDC_EDIT_ONTIME2 )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &g_GtgProto.m_u16On_Time2 );
	
	GetDlgItem ( IDC_EDIT_OFFTIME2 )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &g_GtgProto.m_u16Off_Time2 );

	int id = m_tab_gtg_tone.GetCurSel();

	switch(id)
	{
	case 0:
		sprintf(cfg_gtgid1,           "%d",g_GtgProto.m_u8GTG_id);
		sprintf(cfg_gtgfreqindex11,   "%d",g_GtgProto.m_u8Freq1_Index);
		sprintf(cfg_gtgfreqindex21,   "%d",g_GtgProto.m_u8Freq2_Index);
		sprintf(cfg_gtgthreshold11,   "%d",g_GtgProto.m_u16Freq1_Amp);
		sprintf(cfg_gtgthreshold21,   "%d",g_GtgProto.m_u16Freq2_Amp);
		sprintf(cfg_gtgenvelop1,      "%d",g_GtgProto.m_u16Envelope_Mode);
		sprintf(cfg_gtgrepeatcount1 , "%d",g_GtgProto.m_u16Repeat_Count);
		sprintf(cfg_gtgontime11,      "%d",g_GtgProto.m_u16On_Time1);
		sprintf(cfg_gtgofftime11,     "%d",g_GtgProto.m_u16Off_Time1);
		sprintf(cfg_gtgontime21,      "%d",g_GtgProto.m_u16On_Time2);
		sprintf(cfg_gtgofftime21,     "%d",g_GtgProto.m_u16Off_Time2);
		break;
	case 1:
		sprintf(cfg_gtgid2,           "%d",g_GtgProto.m_u8GTG_id);
		sprintf(cfg_gtgfreqindex12,   "%d",g_GtgProto.m_u8Freq1_Index);
		sprintf(cfg_gtgfreqindex22,   "%d",g_GtgProto.m_u8Freq2_Index);
		sprintf(cfg_gtgthreshold12,   "%d",g_GtgProto.m_u16Freq1_Amp);
		sprintf(cfg_gtgthreshold22,   "%d",g_GtgProto.m_u16Freq2_Amp);
		sprintf(cfg_gtgenvelop2,      "%d",g_GtgProto.m_u16Envelope_Mode);
		sprintf(cfg_gtgrepeatcount2 , "%d",g_GtgProto.m_u16Repeat_Count);
		sprintf(cfg_gtgontime12,      "%d",g_GtgProto.m_u16On_Time1);
		sprintf(cfg_gtgofftime12,     "%d",g_GtgProto.m_u16Off_Time1);
		sprintf(cfg_gtgontime22,      "%d",g_GtgProto.m_u16On_Time2);
		sprintf(cfg_gtgofftime22,     "%d",g_GtgProto.m_u16Off_Time2);
		break;
	case 2:
		sprintf(cfg_gtgid3,           "%d",g_GtgProto.m_u8GTG_id);
		sprintf(cfg_gtgfreqindex13,   "%d",g_GtgProto.m_u8Freq1_Index);
		sprintf(cfg_gtgfreqindex23,   "%d",g_GtgProto.m_u8Freq2_Index);
		sprintf(cfg_gtgthreshold13,   "%d",g_GtgProto.m_u16Freq1_Amp);
		sprintf(cfg_gtgthreshold23,   "%d",g_GtgProto.m_u16Freq2_Amp);
		sprintf(cfg_gtgenvelop3,      "%d",g_GtgProto.m_u16Envelope_Mode);
		sprintf(cfg_gtgrepeatcount3 , "%d",g_GtgProto.m_u16Repeat_Count);
		sprintf(cfg_gtgontime13,      "%d",g_GtgProto.m_u16On_Time1);
		sprintf(cfg_gtgofftime13,     "%d",g_GtgProto.m_u16Off_Time1);
		sprintf(cfg_gtgontime23,      "%d",g_GtgProto.m_u16On_Time2);
		sprintf(cfg_gtgofftime23,     "%d",g_GtgProto.m_u16Off_Time2);
		break;
	case 3:
		sprintf(cfg_gtgid4,           "%d",g_GtgProto.m_u8GTG_id);
		sprintf(cfg_gtgfreqindex14,   "%d",g_GtgProto.m_u8Freq1_Index);
		sprintf(cfg_gtgfreqindex24,   "%d",g_GtgProto.m_u8Freq2_Index);
		sprintf(cfg_gtgthreshold14,   "%d",g_GtgProto.m_u16Freq1_Amp);
		sprintf(cfg_gtgthreshold24,   "%d",g_GtgProto.m_u16Freq2_Amp);
		sprintf(cfg_gtgenvelop4,      "%d",g_GtgProto.m_u16Envelope_Mode);
		sprintf(cfg_gtgrepeatcount4 , "%d",g_GtgProto.m_u16Repeat_Count);
		sprintf(cfg_gtgontime14,      "%d",g_GtgProto.m_u16On_Time1);
		sprintf(cfg_gtgofftime14,     "%d",g_GtgProto.m_u16Off_Time1);
		sprintf(cfg_gtgontime24,      "%d",g_GtgProto.m_u16On_Time2);
		sprintf(cfg_gtgofftime24,     "%d",g_GtgProto.m_u16Off_Time2);
		break;
	case 4:
		sprintf(cfg_gtgid5,           "%d",g_GtgProto.m_u8GTG_id);
		sprintf(cfg_gtgfreqindex15,   "%d",g_GtgProto.m_u8Freq1_Index);
		sprintf(cfg_gtgfreqindex25,   "%d",g_GtgProto.m_u8Freq2_Index);
		sprintf(cfg_gtgthreshold15,   "%d",g_GtgProto.m_u16Freq1_Amp);
		sprintf(cfg_gtgthreshold25,   "%d",g_GtgProto.m_u16Freq2_Amp);
		sprintf(cfg_gtgenvelop5,      "%d",g_GtgProto.m_u16Envelope_Mode);
		sprintf(cfg_gtgrepeatcount5 , "%d",g_GtgProto.m_u16Repeat_Count);
		sprintf(cfg_gtgontime15,      "%d",g_GtgProto.m_u16On_Time1);
		sprintf(cfg_gtgofftime15,     "%d",g_GtgProto.m_u16Off_Time1);
		sprintf(cfg_gtgontime25,      "%d",g_GtgProto.m_u16On_Time2);
		sprintf(cfg_gtgofftime25,     "%d",g_GtgProto.m_u16Off_Time2);
		break;
	case 5:
		sprintf(cfg_gtgid6,           "%d",g_GtgProto.m_u8GTG_id);
		sprintf(cfg_gtgfreqindex16,   "%d",g_GtgProto.m_u8Freq1_Index);
		sprintf(cfg_gtgfreqindex26,   "%d",g_GtgProto.m_u8Freq2_Index);
		sprintf(cfg_gtgthreshold16,   "%d",g_GtgProto.m_u16Freq1_Amp);
		sprintf(cfg_gtgthreshold26,   "%d",g_GtgProto.m_u16Freq2_Amp);
		sprintf(cfg_gtgenvelop6,      "%d",g_GtgProto.m_u16Envelope_Mode);
		sprintf(cfg_gtgrepeatcount6 , "%d",g_GtgProto.m_u16Repeat_Count);
		sprintf(cfg_gtgontime16,      "%d",g_GtgProto.m_u16On_Time1);
		sprintf(cfg_gtgofftime16,     "%d",g_GtgProto.m_u16Off_Time1);
		sprintf(cfg_gtgontime26,      "%d",g_GtgProto.m_u16On_Time2);
		sprintf(cfg_gtgofftime26,     "%d",g_GtgProto.m_u16Off_Time2);
		break;
	
	}

	CDialog::OnOK();
}

void CDialogGTGSet::OnClickTabGtGTone(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	//char TmpStr[20];
//	int iTmpVal;

	int id = m_tab_gtg_tone.GetCurSel();
	//IDC_EDIT_FREQ_INDEX
	//sprintf(TmpStr,"%d",id);

	//SetDlgItemText(IDC_EDIT_FREQ_TONE,TmpStr);
	switch(id)
	{
	case 0:
		SetDlgItemText(IDC_EDIT_GTGID,"48");
		m_GTGComboEnvelop.SetCurSel ( 0);

		break;
	case 1:
		SetDlgItemText(IDC_EDIT_GTGID,"49");
		m_GTGComboEnvelop.SetCurSel (0);
		break;
	case 2:
		SetDlgItemText(IDC_EDIT_GTGID,"50");
		m_GTGComboEnvelop.SetCurSel ( 0);

		break;
	case 3:
		SetDlgItemText(IDC_EDIT_GTGID,"51");
		m_GTGComboEnvelop.SetCurSel ( 0);
		break;
	case 4:
		SetDlgItemText(IDC_EDIT_GTGID,"52");
		m_GTGComboEnvelop.SetCurSel (0);

		break;
	case 5:
		SetDlgItemText(IDC_EDIT_GTGID,"53");
		m_GTGComboEnvelop.SetCurSel (0);
		break;

	}

	*pResult = 0;
}

void CDialogGTGSet::OnSelchangeComboEnvelop() 
{
	// TODO: Add your control notification handler code here
	GTGiComboEnvelopParam = m_GTGComboEnvelop.GetCurSel ( ); 
}

