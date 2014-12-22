// XMSVoIPDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSVoIPDemo.h"
#include "XMSVoIPDemoDlg.h"

#include <winsock2.h>

#include "DJAcsAPIDef.h"
#include "DJAcsDevState.h"

#include "XMSData.h"
#include "XMSEventHandler.h"

#include "DialogCallTransfer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// init XMS device structs
void initXMS();

/////////////////////////////////////////////////////////////////////////////
// CXMSVoIPDemoDlg dialog

CXMSVoIPDemoDlg::CXMSVoIPDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXMSVoIPDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXMSVoIPDemoDlg)
	m_strCalleeAddr = _T("");
	m_strCalleeTelNo = _T("");
	m_strCalleeUserID = _T("");
	m_iProtocol = 0;
	m_strServerAddr = _T("");
	m_uiServerPort = 9001;
	m_strPlayFile = _T("");
	m_iSampleRate = 0;
	m_iCodec = 0;
	m_strRecordFile = _T("");
	m_iDtmf = 0;
	m_strCalleePort = _T("1720");
	m_strUsername = _T("");
	m_strPassword = _T("");
	m_iDSP = 1;
	m_strCalleePassword = _T("");
	m_strCallerTelNo = _T("");
	m_strRegAddr = _T("");
	m_strRegPort = _T("");
	m_strRegUsername = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	GetModuleFileName(NULL, m_strIniFile.GetBuffer(_MAX_PATH), _MAX_PATH);
	m_strIniFile.ReleaseBuffer();
	m_strIniFile.Replace(_T(".exe"), _T(".ini"));

	loadConfig();
}

void CXMSVoIPDemoDlg::loadConfig()
{
	GetPrivateProfileString(_T("Server"), _T("IP"), _T(""), m_strServerAddr.GetBuffer(100), 100, m_strIniFile);
	m_strServerAddr.ReleaseBuffer();

	if (m_strServerAddr.IsEmpty())
	{
		// get local host ip
		char hostname[256] = {0};
		if (gethostname(hostname, sizeof(hostname)) == 0)
		{
			HOSTENT *he	= gethostbyname(hostname);

			if (he != NULL)
			{
				m_strServerAddr = inet_ntoa(*((struct in_addr *)he->h_addr_list[0]));
			}
		}
	}

	m_uiServerPort = GetPrivateProfileInt(_T("Server"), _T("Port"), 9000, m_strIniFile);
	GetPrivateProfileString(_T("Server"), _T("Username"), _T(""), m_strUsername.GetBuffer(100), 100, m_strIniFile);
	m_strUsername.ReleaseBuffer();
	GetPrivateProfileString(_T("Server"), _T("Password"), _T(""), m_strPassword.GetBuffer(100), 100, m_strIniFile);
	m_strPassword.ReleaseBuffer();
	m_iDSP = GetPrivateProfileInt(_T("Server"), _T("DSP"), 1, m_strIniFile);

	m_iProtocol = GetPrivateProfileInt(_T("Callee"), _T("Protocol"), 0, m_strIniFile);

	GetPrivateProfileString(_T("Callee"), _T("IP"), _T(""), m_strCalleeAddr.GetBuffer(100), 100, m_strIniFile);
	m_strCalleeAddr.ReleaseBuffer();
//	if (m_strCalleeAddr.IsEmpty())
//		m_strCalleeAddr = m_strServerAddr;
	GetPrivateProfileString(_T("Callee"), _T("Port"), _T(""), m_strCalleePort.GetBuffer(100), 100, m_strIniFile);
	m_strCalleePort.ReleaseBuffer();
	GetPrivateProfileString(_T("Callee"), _T("UserID"), _T(""), m_strCalleeUserID.GetBuffer(100), 100, m_strIniFile);
	m_strCalleeUserID.ReleaseBuffer();
	GetPrivateProfileString(_T("Callee"), _T("TelNo"), _T(""), m_strCalleeTelNo.GetBuffer(100), 100, m_strIniFile);
	m_strCalleeTelNo.ReleaseBuffer();

	GetPrivateProfileString(_T("Caller"), _T("TelNo"), _T(""), m_strCallerTelNo.GetBuffer(100), 100, m_strIniFile);
	m_strCallerTelNo.ReleaseBuffer();

	GetPrivateProfileString(_T("Voc"), _T("PlayFile"), _T(""), m_strPlayFile.GetBuffer(100), 100, m_strIniFile);
	m_strPlayFile.ReleaseBuffer();

	GetPrivateProfileString(_T("Voc"), _T("RecordFile"), _T(""), m_strRecordFile.GetBuffer(100), 100, m_strIniFile);
	m_strRecordFile.ReleaseBuffer();

	GetPrivateProfileString(_T("Reg"), _T("Password"), _T(""), m_strCalleePassword.GetBuffer(100), 100, m_strIniFile);
	m_strCalleePassword.ReleaseBuffer();
}

void CXMSVoIPDemoDlg::saveConfig()
{
	UpdateData();

	WritePrivateProfileString(_T("Server"), _T("IP"), m_strServerAddr, m_strIniFile);
	CString strbuf;
	strbuf.Format(_T("%d"), m_uiServerPort);
	WritePrivateProfileString(_T("Server"), _T("Port"), strbuf, m_strIniFile);
	WritePrivateProfileString(_T("Server"), _T("Username"), m_strUsername, m_strIniFile);
	WritePrivateProfileString(_T("Server"), _T("Password"), m_strPassword, m_strIniFile);
	strbuf.Format(_T("%d"), m_iDSP);
	WritePrivateProfileString(_T("Server"), _T("DSP"), strbuf, m_strIniFile);

	strbuf.Format(_T("%d"), m_iProtocol);
	WritePrivateProfileString(_T("Callee"), _T("Protocol"), strbuf, m_strIniFile);
	WritePrivateProfileString(_T("Callee"), _T("IP"), m_strCalleeAddr, m_strIniFile);
	WritePrivateProfileString(_T("Callee"), _T("Port"), m_strCalleePort, m_strIniFile);
	WritePrivateProfileString(_T("Callee"), _T("UserID"), m_strCalleeUserID, m_strIniFile);
	WritePrivateProfileString(_T("Callee"), _T("TelNo"), m_strCalleeTelNo, m_strIniFile);

	WritePrivateProfileString(_T("Caller"), _T("TelNo"), m_strCallerTelNo, m_strIniFile);

	WritePrivateProfileString(_T("Reg"), _T("Password"), m_strCallerTelNo, m_strCalleePassword);

	WritePrivateProfileString(_T("Voc"), _T("PlayFile"), m_strPlayFile, m_strIniFile);
	WritePrivateProfileString(_T("Voc"), _T("RecordFile"), m_strRecordFile, m_strIniFile);
}

void CXMSVoIPDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXMSVoIPDemoDlg)
	DDX_Control(pDX, IDC_TREE_CONF, m_treeConf);
	DDX_Control(pDX, IDC_LIST_VOICE, m_lstVoc);
	DDX_Control(pDX, IDC_LIST_IP, m_lstIP);
	DDX_Text(pDX, IDC_EDIT_CALLEE_ADDR, m_strCalleeAddr);
	DDX_Text(pDX, IDC_EDIT_CALLEE_TELNO, m_strCalleeTelNo);
	DDX_Text(pDX, IDC_EDIT_CALLEE_USERID, m_strCalleeUserID);
	DDX_Radio(pDX, IDC_RADIO_H323, m_iProtocol);
	DDX_Text(pDX, IDC_EDIT_SERVER_ADDR, m_strServerAddr);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_uiServerPort);
	DDX_Text(pDX, IDC_EDIT_PLAYFILE, m_strPlayFile);
	DDX_Radio(pDX, IDC_RADIO_8K, m_iSampleRate);
	DDX_Radio(pDX, IDC_RADIO_ALAW, m_iCodec);
	DDX_Text(pDX, IDC_EDIT_RECORDFILE, m_strRecordFile);
	DDX_Radio(pDX, IDC_RADIO_H245UII, m_iDtmf);
	DDX_Text(pDX, IDC_EDIT_CALLEE_PORT, m_strCalleePort);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUsername);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_DSPID, m_iDSP);
	DDX_Text(pDX, IDC_EDIT_CALLEE_PSW, m_strCalleePassword);
	DDX_Text(pDX, IDC_EDIT_CALLER_TELNO, m_strCallerTelNo);
	DDX_Text(pDX, IDC_EDIT_CALLEE_ADDR2, m_strRegAddr);
	DDX_Text(pDX, IDC_EDIT_CALLEE_PORT2, m_strRegPort);
	DDX_Text(pDX, IDC_EDIT_CALLEE_USERID2, m_strRegUsername);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXMSVoIPDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CXMSVoIPDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MAKECALL, OnButtonMakeCall)
	ON_BN_CLICKED(IDC_BUTTON_ANSWERCALL, OnButtonAnswerCall)
	ON_BN_CLICKED(IDC_BUTTON_DROPCALL, OnButtonDropCall)
	ON_BN_CLICKED(IDC_BUTTON_BIND, OnButtonBindVoice)
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonInitSystem)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_IP, OnButtonOpenDeviceIP)
	ON_BN_CLICKED(IDC_BUTTON_OPENALL_IP, OnButtonOpenAllIP)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_IP, OnItemchangedListIP)
	ON_BN_CLICKED(IDC_RADIO_H323, OnRadioH323)
	ON_BN_CLICKED(IDC_RADIO_SIP, OnRadioSip)
	ON_BN_CLICKED(IDC_BUTTON_BROWSEPLAYFILE, OnButtonBrowsePlayFile)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_VOICE, OnItemchangedListVoice)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_IP, OnButtonCloseDeviceIP)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEALL_IP, OnButtonCloseAllIP)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_VOC, OnButtonOpenDeviceVoc)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_VOC, OnButtonCloseDeviceVoc)
	ON_BN_CLICKED(IDC_BUTTON_OPENALL_VOC, OnButtonOpenAllVoc)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEALL_VOC, OnButtonCloseAllVoc)
	ON_BN_CLICKED(IDC_BUTTON_UNBIND, OnButtonUnbindVoice)
	ON_EN_SETFOCUS(IDC_EDIT_SERVER_ADDR, OnSetfocusEditServerAddr)
	ON_EN_SETFOCUS(IDC_EDIT_SERVER_PORT, OnSetfocusEditServerPort)
	ON_EN_SETFOCUS(IDC_EDIT_CALLEE_ADDR, OnSetfocusEditCalleeAddr)
	ON_EN_SETFOCUS(IDC_EDIT_CALLEE_PORT, OnSetfocusEditCalleePort)
	ON_EN_SETFOCUS(IDC_EDIT_CALLEE_USERID, OnSetfocusEditCalleeUserid)
	ON_EN_SETFOCUS(IDC_EDIT_CALLEE_TELNO, OnSetfocusEditCalleeTelno)
	ON_EN_SETFOCUS(IDC_EDIT_PLAYFILE, OnSetfocusEditPlayfile)
	ON_BN_CLICKED(IDC_BUTTON_BROWSERECORDFILE, OnButtonBrowseRecordFile)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnButtonRecord)
	ON_BN_CLICKED(IDC_BUTTON_3PCONF, OnButton3pconf)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_CONF, OnButtonOpenConf)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_CONF, OnButtonCloseConf)
	ON_BN_CLICKED(IDC_BUTTON_JOIN_CONF, OnButtonJoinConf)
	ON_BN_CLICKED(IDC_BUTTON_LEAVE_CONF, OnButtonLeaveConf)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_CONF, OnButtonClearConf)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_CONF, OnSelchangedTreeConf)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_IP, OnDblclkListIp)
	ON_BN_CLICKED(IDC_BUTTON_CHAIRMAN, OnButtonChairman)
	ON_BN_CLICKED(IDC_BUTTON_REG, OnButtonReg)
	ON_BN_CLICKED(IDC_BUTTON_UNREG, OnButtonUnreg)
	ON_BN_CLICKED(IDC_BUTTON_TRANSFERCALL, OnButtonTransfercall)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_DTMF1, IDC_BUTTON_DTMFP, OnButtonDtmf)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMSVoIPDemoDlg message handlers

HFONT g_hFont = NULL;

BOOL CALLBACK replaceFont(HWND hwndChild, LPARAM lParam)
{
	TCHAR tszClassName[256] = {0};
	if (GetClassName(hwndChild, tszClassName, sizeof(tszClassName)) > 0 &&
		_tcscmp(tszClassName, _T("Button")) == 0)
	{
		LONG lStyle = GetWindowLong(hwndChild, GWL_STYLE);
		if ((lStyle & BS_GROUPBOX) != BS_GROUPBOX)
			SendMessage(hwndChild, WM_SETFONT, (WPARAM)g_hFont, 0);
	}

	return TRUE;
}

BOOL CXMSVoIPDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	LOGFONT lf = {0};
	GetFont()->GetLogFont(&lf);
	lf.lfWeight = FW_BOLD;
	g_hFont = ::CreateFontIndirect(&lf);

	EnumChildWindows(GetSafeHwnd(), replaceFont, NULL);

	// init user interface
	initUI();

	// init XMS device structs
	initXMS();

	m_pdlgRtp = new CXMSVoIPDemoRTPDlg;
	m_pdlgRtp->Create(IDD_RTPSESSION_DIALOG, this);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXMSVoIPDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXMSVoIPDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////
// init list control
void CXMSVoIPDemoDlg::initUI()
{
	// IP Devices list
	m_lstIP.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_lstIP.InsertColumn(0, _T("Header"), LVCFMT_LEFT, 0);
	m_lstIP.InsertColumn(1, _T("#"), LVCFMT_CENTER, 30);
	m_lstIP.InsertColumn(2, _T("Protocol"), LVCFMT_CENTER, 60);
	m_lstIP.InsertColumn(3, _T("State"), LVCFMT_CENTER, 60);
	m_lstIP.InsertColumn(4, _T("Caller Address"), LVCFMT_CENTER, 120);
	m_lstIP.InsertColumn(5, _T("Caller UserID"), LVCFMT_CENTER, 80);
	m_lstIP.InsertColumn(6, _T("Caller TelNo"), LVCFMT_CENTER, 80);
	m_lstIP.InsertColumn(7, _T("Callee Address"), LVCFMT_CENTER, 120);
	m_lstIP.InsertColumn(8, _T("Callee UserID"), LVCFMT_CENTER, 80);
	m_lstIP.InsertColumn(9, _T("Callee TelNo"), LVCFMT_CENTER, 80);
	m_lstIP.InsertColumn(10, _T("DTMF"), LVCFMT_CENTER, 50);
	m_lstIP.InsertColumn(11, _T("Voice"), LVCFMT_CENTER, 40);

	// Voice Devices list
	m_lstVoc.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_lstVoc.InsertColumn(0, _T("Header"), LVCFMT_LEFT, 0);
	m_lstVoc.InsertColumn(1, _T("#"), LVCFMT_CENTER, 30);
	m_lstVoc.InsertColumn(2, _T("Play File"), LVCFMT_CENTER, 200);
	m_lstVoc.InsertColumn(3, _T("Sample Rate"), LVCFMT_CENTER, 80);
	m_lstVoc.InsertColumn(4, _T("Codec"), LVCFMT_CENTER, 50);
	m_lstVoc.InsertColumn(5, _T("Record File"), LVCFMT_CENTER, 200);
	m_lstVoc.InsertColumn(6, _T("IP"), LVCFMT_CENTER, 30);
}

//////////////////////////////////////////////////////////////////////////
// init XMS Device structs
void initXMS()
{
	for (int iDevice = 0; iDevice < MAX_DEVICE_VOIP; ++iDevice)
	{
		g_deviceVoIP[iDevice].bOpened = FALSE;
		memset(&g_deviceVoIP[iDevice].device, -1, sizeof(DeviceID_t));
		resetDeviceVoIP(iDevice);
	}

	for (iDevice = 0; iDevice < MAX_DEVICE_VOICE; ++iDevice)
	{
		g_deviceVoc[iDevice].bOpened = FALSE;
		memset(&g_deviceVoc[iDevice].device, -1, sizeof(DeviceID_t));
		resetDeviceVoc(iDevice);
	}

	for (iDevice = 0; iDevice < MAX_DEVICE_CONF; ++iDevice)
	{
		g_deviceConf[iDevice].bOpened = FALSE;
		memset(&g_deviceConf[iDevice].device, -1, sizeof(DeviceID_t));
		resetDeviceConf(iDevice);
	}
}

//////////////////////////////////////////////////////////////////////////
// init IP Devices list
void CXMSVoIPDemoDlg::initIPList()
{
	m_lstIP.DeleteAllItems();

	if (g_iVoIPDevNum <= 0)
	{
		MessageBox(_T("No IP Devices found!"), _T("Error"), MB_OK|MB_ICONERROR);
		return;
	}

	// fill list
	for (int i = 0; i < g_iVoIPDevNum; ++i)
	{
		CString str;

		m_lstIP.InsertItem(i, _T(""));
		str.Format(_T("%02d"), i);
		m_lstIP.SetItemText(i, 1, str);
		for (int j = 2; j < 12; ++j)
			m_lstIP.SetItemText(i, j, _T("N/A"));
	}

	// highlight the first device item
	m_lstIP.SetItemState(0, LVIS_FOCUSED|LVIS_SELECTED, -1);
}

//////////////////////////////////////////////////////////////////////////
// init Voice Devices list
void CXMSVoIPDemoDlg::initVocList()
{
	m_lstVoc.DeleteAllItems();

	if (g_iVocDevNum <= 0)
	{
		MessageBox(_T("No Voice Devices found!"), _T("Error"), MB_OK|MB_ICONERROR);
		return;
	}

	// fill list
	for (int i = 0; i < g_iVocDevNum; ++i)
	{
		CString str;

		m_lstVoc.InsertItem(i, _T(""));
		str.Format(_T("%03d"), i);
		m_lstVoc.SetItemText(i, 1, str);
		for (int j = 2; j < 7; ++j)
			m_lstVoc.SetItemText(i, j, _T("N/A"));
	}

	// highlight the first device item
	m_lstVoc.SetItemState(0, LVIS_FOCUSED|LVIS_SELECTED, -1);
}

//////////////////////////////////////////////////////////////////////////
// init Conference Device tree
void CXMSVoIPDemoDlg::initConfTree()
{
	m_treeConf.DeleteAllItems();

	if (g_iConfDevNum <= 0)
	{
		MessageBox(_T("No Conference Devices found!"), _T("Error"), MB_OK|MB_ICONERROR);
		return;
	}

	for (int i = 0; i < g_iConfDevNum; ++i)
	{
		CString str;
		str.Format(_T("Conference #%02d"), i);

		HTREEITEM hItem = m_treeConf.InsertItem(str);

		m_treeConf.SetItemData(hItem, i);
	}

	// highlight the first device item
	m_treeConf.SelectItem(m_treeConf.GetNextItem(TVI_ROOT, TVGN_ROOT));
}

//////////////////////////////////////////////////////////////////////////
// open XMS system
void CXMSVoIPDemoDlg::OnButtonInitSystem()
{
	UpdateData();

	if (g_acsHandle == NULL)
	{
		GetDlgItem(IDC_BUTTON_INIT)->EnableWindow(FALSE);

		ServerID_t serverID;
		strcpy(serverID.m_s8ServerIp, m_strServerAddr);
		serverID.m_u32ServerPort = m_uiServerPort;;
		strcpy(serverID.m_s8UserName, m_strUsername);
		strcpy(serverID.m_s8UserPwd, m_strPassword);

		// connect to XMS service
		RetCode_t ret = XMS_acsOpenStream(&g_acsHandle, &serverID, XMS_APP_ID, 128, 32, FALSE, NULL);
		if (ret < 0 || g_acsHandle == NULL)
		{
			MessageBox(_T("XMS OpenStream failed!"), _T("Error"), MB_OK|MB_ICONERROR);
			GetDlgItem(IDC_BUTTON_INIT)->EnableWindow(TRUE);
			return;
		}

		// set XMS event handler
		ret = XMS_acsSetESR(g_acsHandle, XMSEventHandler, NULL, TRUE);

		// get device list
		ret = XMS_acsGetDeviceList(g_acsHandle, NULL);
	}
	else
	{
		RetCode_t ret = XMS_acsCloseStream(g_acsHandle, NULL);
		g_acsHandle = NULL;
	}
}

///////////////////////////////////////////////////////////////////////////
// open IP Device
void CXMSVoIPDemoDlg::OnButtonOpenDeviceIP() 
{
	if (m_lstIP.GetSelectedCount() == 0)
	{
		MessageBox(_T("Please select one item in the IP Devices list first."), _T("OpenDevice"), MB_OK|MB_ICONASTERISK);
		return;
	}

	RetCode_t ret;

	POSITION pos = m_lstIP.GetFirstSelectedItemPosition();
	while (pos)
	{
		int iDevice = m_lstIP.GetNextSelectedItem(pos);

		// opened already?
		if (g_deviceVoIP[iDevice].bOpened)
			continue;

		// send open device command
		ret = XMS_ctsOpenDevice(g_acsHandle, &g_deviceVoIP[iDevice].device, NULL);
	}
}

//////////////////////////////////////////////////////////////////////////
// close IP Device
void CXMSVoIPDemoDlg::OnButtonCloseDeviceIP() 
{
	POSITION pos = m_lstIP.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("Select one device first"), _T("CloseDevice"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDevice = m_lstIP.GetNextSelectedItem(pos);

	if (g_deviceVoIP[iDevice].bOpened)
	{
		// send close device command
		RetCode_t ret = XMS_ctsCloseDevice(g_acsHandle, &g_deviceVoIP[iDevice].device, NULL);
	}
}

//////////////////////////////////////////////////////////////////////////
// open all IP Devices
void CXMSVoIPDemoDlg::OnButtonOpenAllIP() 
{
	RetCode_t ret;

	for (int iDevice = 0; iDevice < g_iVoIPDevNum; ++iDevice)
	{
		// opened already?
		if (g_deviceVoIP[iDevice].bOpened)
			continue;

		// send open device command
		ret = XMS_ctsOpenDevice(g_acsHandle, &g_deviceVoIP[iDevice].device, NULL);
	}
}

//////////////////////////////////////////////////////////////////////////
// close all IP Devices
void CXMSVoIPDemoDlg::OnButtonCloseAllIP() 
{
	RetCode_t ret;

	for (int iDevice = 0; iDevice < g_iVoIPDevNum; ++iDevice)
	{
		// opened already?
		if (!g_deviceVoIP[iDevice].bOpened)
			continue;

		// send close device command
		ret = XMS_ctsCloseDevice(g_acsHandle, &g_deviceVoIP[iDevice].device, NULL);
	}
}

//////////////////////////////////////////////////////////////////////////
// make IP call
void CXMSVoIPDemoDlg::OnButtonMakeCall() 
{
	POSITION pos = m_lstIP.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("No IP device selected"), _T("MakeCall"), MB_OK|MB_ICONERROR);
		return;
	}

	int iDevice = m_lstIP.GetNextSelectedItem(pos);

	if (g_deviceVoIP[iDevice].bOpened && g_deviceVoIP[iDevice].iState == DCS_FREE)
	{
		UpdateData();

		// fill call parameters
		VoIPCallPrivate_t paramVoIPCall = {0};
		paramVoIPCall.m_PrivateData.m_u32DataSize = sizeof(VoIPCallPrivate_t);
		paramVoIPCall.m_s32Protocol = m_iProtocol == 0 ? XMS_VOIP_PROTOCOL_H323 : XMS_VOIP_PROTOCOL_SIP;

		strcpy(paramVoIPCall.m_s8CalleeAddress, m_strCalleeAddr);
		if (!m_strCalleeAddr.IsEmpty())
			paramVoIPCall.m_s32CalleePort = atol(m_strCalleePort);
		strcpy(paramVoIPCall.m_s8CalleeUserID, m_strCalleeUserID);

		// use code below to set media caps (supported in v2.1.2)
		paramVoIPCall.m_u8MediaCapNum = 0;
		paramVoIPCall.m_u8MediaCapList[0] = VOIP_MEDIA_AUDIO_G723;
		paramVoIPCall.m_u8MediaCapList[1] = VOIP_MEDIA_AUDIO_PCMA;
		paramVoIPCall.m_u8MediaCapList[2] = VOIP_MEDIA_AUDIO_G729;

		// send make call command
		RetCode_t ret = XMS_ctsMakeCallOut(g_acsHandle, &g_deviceVoIP[iDevice].device,
			(char *)(LPCTSTR)m_strCallerTelNo, (char *)(LPCTSTR)m_strCalleeTelNo, (PrivateData_t *)&paramVoIPCall);

		// update call info
		g_deviceVoIP[iDevice].iProtocol = paramVoIPCall.m_s32Protocol;
		strcpy(g_deviceVoIP[iDevice].addrCallee.tszAddr, m_strCalleeAddr);
		g_deviceVoIP[iDevice].addrCallee.port = (USHORT)paramVoIPCall.m_s32CalleePort;
		strcpy(g_deviceVoIP[iDevice].addrCallee.tszUserID, m_strCalleeUserID);
		strcpy(g_deviceVoIP[iDevice].addrCallee.tszTelNo, m_strCalleeTelNo);
		strcpy(g_deviceVoIP[iDevice].addrCaller.tszTelNo, m_strCallerTelNo);

		refreshListIP(iDevice);
	}
}

//////////////////////////////////////////////////////////////////////////
// answer IP call
void CXMSVoIPDemoDlg::OnButtonAnswerCall() 
{
	POSITION pos = m_lstIP.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("Please select one IP Device with incoming call first"), _T("AnswerCall"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDevice = m_lstIP.GetNextSelectedItem(pos);

	// send answer call command
	RetCode_t ret = XMS_ctsAnswerCallIn(g_acsHandle, &g_deviceVoIP[iDevice].device, NULL);
}

//////////////////////////////////////////////////////////////////////////
// drop IP call
void CXMSVoIPDemoDlg::OnButtonDropCall() 
{
	POSITION pos = m_lstIP.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("Please select one IP Device with connected call first"), _T("DropCall"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDevice = m_lstIP.GetNextSelectedItem(pos);

	// unbind voice device first
	if (g_deviceVoIP[iDevice].iVoiceDevice != -1)
		OnButtonUnbindVoice();

	// send clear call command
	RetCode_t ret = XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[iDevice].device, 0, NULL);
}

//////////////////////////////////////////////////////////////////////////
// bind Voice Device to IP Device
void CXMSVoIPDemoDlg::OnButtonBindVoice() 
{
	POSITION pos = m_lstIP.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("Select one IP Device first"), _T("BindVoice"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDeviceIP = m_lstIP.GetNextSelectedItem(pos);

	pos = m_lstVoc.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("Select one Voice Device first"), _T("BindVoice"), MB_OK|MB_ICONASTERISK);
		return;
	}

	if (g_deviceVoIP[iDeviceIP].iState != DCS_CONNECT)
	{
		MessageBox(_T("IP device not connected"), _T("BindVoice"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDeviceVoc = m_lstVoc.GetNextSelectedItem(pos);

	MixerControlParam_t paramMixer = {0};
	paramMixer.m_u8SRC1_Ctrl = XMS_MIXER_FROM_PLAY;
	paramMixer.m_u16SRC_ChID1 = g_deviceVoc[iDeviceVoc].device.m_s16ChannelID;

	// send SetParam command
	RetCode_t ret = XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceIP].device,
		VOIP_PARAM_RTPMIXER, sizeof(paramMixer), &paramMixer);

/*	for echo cancelling, voice activity detection and gain control settings, use code below:
	CmdParamData_Voice_t paramVoice = {0};
	paramVoice.m_u8InputCtrlValid = TRUE;
	paramVoice.m_u8OutputCtrlValid = TRUE;
	paramVoice.m_VocInputControl.m_u16FixGain = 0xffff;
	paramVoice.m_VocInputControl.m_u8EcEnable = TRUE;
	paramVoice.m_VocInputControl.m_u8VadEnable = TRUE;
	paramVoice.m_VocOutputControl.m_u16FixGain = 0xffff;
	paramVoice.m_VocOutputControl.m_u8OutputType = XMS_VOC_OUTPUT_FROM_MIXER;
	paramVoice.m_VocOutputControl.m_MixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_PLAY;
	paramVoice.m_VocOutputControl.m_MixerControl.m_u16SRC_ChID1 = g_deviceVoc[iDeviceVoc].device.m_s16ChannelID;

	// send SetParam command
	RetCode_t ret = XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceIP].device,
		VOIP_PARAM_VOICE, sizeof(paramVoice), &paramVoice);*/

	g_deviceVoIP[iDeviceIP].iVoiceDevice = iDeviceVoc;
	g_deviceVoc[iDeviceVoc].iVoIPDevice = iDeviceIP;

	refreshCtrlIP();
	refreshListIP(iDeviceIP);
	refreshListVoc(iDeviceVoc);
}

//////////////////////////////////////////////////////////////////////////
// unbind Voice Device to IP Device
void CXMSVoIPDemoDlg::OnButtonUnbindVoice() 
{
	POSITION pos = m_lstIP.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("Select one IP Device first"), _T("UnbindVoice"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDeviceIP = m_lstIP.GetNextSelectedItem(pos);

	pos = m_lstVoc.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("Select one Voice Device first"), _T("UnbindVoice"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDeviceVoc = m_lstVoc.GetNextSelectedItem(pos);

	MixerControlParam_t paramMixer = {0};

	// send SetParam command
	RetCode_t ret = XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceIP].device,
		VOIP_PARAM_RTPMIXER, sizeof(paramMixer), &paramMixer);

	g_deviceVoIP[iDeviceIP].iVoiceDevice = -1;
	g_deviceVoc[iDeviceVoc].iVoIPDevice = -1;

	refreshCtrlIP();
	refreshListIP(iDeviceIP);
	refreshListVoc(iDeviceVoc);
}

//////////////////////////////////////////////////////////////////////////
// 3-Party IP Conference without using Conference Device
// using 2-way IP voice mixer instead
void CXMSVoIPDemoDlg::OnButton3pconf() 
{
	if (m_lstIP.GetSelectedCount() < 3)
	{
		MessageBox(_T("Please select 3 IP devices first!"), _T("3P Conference"), MB_OK|MB_ICONASTERISK);
		return;
	}

	POSITION pos = m_lstIP.GetFirstSelectedItemPosition();

	int iDevice1 = m_lstIP.GetNextSelectedItem(pos);
	int iDevice2 = m_lstIP.GetNextSelectedItem(pos);
	int iDevice3 = m_lstIP.GetNextSelectedItem(pos);

	if (g_deviceVoIP[iDevice1].iState != DCS_CONNECT ||
		g_deviceVoIP[iDevice2].iState != DCS_CONNECT ||
		g_deviceVoIP[iDevice3].iState != DCS_CONNECT)
	{
		MessageBox(_T("Please connect all 3 IP devices first!"), _T("3P Conference"), MB_ICONASTERISK);
		return;
	}

	// VoIP Device parameter
	MixerControlParam_t paramMixer = {0};
	paramMixer.m_u8SRC1_Ctrl = XMS_MIXER_FROM_IP;
	paramMixer.m_u8SRC2_Ctrl = XMS_MIXER_FROM_IP;

	// set p1 device mixer from p2 & p3
	paramMixer.m_u16SRC_ChID1 = g_deviceVoIP[iDevice2].device.m_s16ChannelID;
	paramMixer.m_u16SRC_ChID2 = g_deviceVoIP[iDevice3].device.m_s16ChannelID;
	RetCode_t ret = XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDevice1].device,
		VOIP_PARAM_RTPMIXER, sizeof(paramMixer), &paramMixer);

	// set p2 device mixer from p1 & p3
	paramMixer.m_u16SRC_ChID1 = g_deviceVoIP[iDevice1].device.m_s16ChannelID;
	paramMixer.m_u16SRC_ChID2 = g_deviceVoIP[iDevice3].device.m_s16ChannelID;
	ret = XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDevice2].device,
		VOIP_PARAM_RTPMIXER, sizeof(paramMixer), &paramMixer);

	// set p3 device mixer from p1 & p2
	paramMixer.m_u16SRC_ChID1 = g_deviceVoIP[iDevice1].device.m_s16ChannelID;
	paramMixer.m_u16SRC_ChID2 = g_deviceVoIP[iDevice2].device.m_s16ChannelID;
	ret = XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDevice3].device,
		VOIP_PARAM_RTPMIXER, sizeof(paramMixer), &paramMixer);
}

//////////////////////////////////////////////////////////////////////////
// send IP dtmf using H.245 UserInputIndication / SIP INFO / RFC 2833
void CXMSVoIPDemoDlg::OnButtonDtmf(int idBtn) 
{
	int idBtnDtmf[] = {
		IDC_BUTTON_DTMF0, IDC_BUTTON_DTMF1, IDC_BUTTON_DTMF2, IDC_BUTTON_DTMF3,
		IDC_BUTTON_DTMF4, IDC_BUTTON_DTMF5, IDC_BUTTON_DTMF6, IDC_BUTTON_DTMF7,
		IDC_BUTTON_DTMF8, IDC_BUTTON_DTMF9, IDC_BUTTON_DTMFA, IDC_BUTTON_DTMFP
	};

	for (int iDtmf = 0; iDtmf < sizeof(idBtnDtmf)/sizeof(int); ++iDtmf)
	{
		if (idBtn == idBtnDtmf[iDtmf])
			break;
	}
	if (iDtmf == sizeof(idBtnDtmf)/sizeof(int))
		return;

	POSITION pos = m_lstIP.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("Select one IP device first"), _T("SendDtmf"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDevice = m_lstIP.GetNextSelectedItem(pos);

	UpdateData();

	if (g_deviceVoIP[iDevice].iState == DCS_CONNECT)
	{
		const char szDtmf[] = "0123456789*#";

		switch (m_iDtmf)
		{
		case 0: // send dtmf using H.245 UserInputIndication
			{
				Acs_VoIP_H245UII h245Uii = {0};
				h245Uii.m_s8Signal = szDtmf[iDtmf]; // dtmf char in "0123456789#*ABCD!"
				h245Uii.m_u32Duration = 200; // milliseconds

				// send dtmf command
				RetCode_t ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDevice].device,
					XMS_IO_TYPE_VOIP_H245UII, sizeof(h245Uii), &h245Uii);
			}
			break;
		case 1: // send dtmf using SIP INFO
			{
				Acs_VoIP_SIPINFO sipInfo = {0};
				strcpy(sipInfo.m_s8ContentType, "application/dtmf");
				sprintf(sipInfo.m_s8Body, "dtmf=%c\nduration=%d", szDtmf[iDtmf], 200);

				// send dtmf command
				RetCode_t ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDevice].device,
					XMS_IO_TYPE_VOIP_SIPINFO, sizeof(sipInfo), &sipInfo);
			}
			break;
		case 2: // send dtmf using RTP (RFC 2833/4733)
			{
				Acs_VoIP_RTPDTMF rtpDtmf = {0};
				rtpDtmf.m_s8EventChar	= szDtmf[iDtmf];	// rtp dtmf event char
				rtpDtmf.m_s8Volume		= -32;				// volume (in dbm0 from -63 to 0)
				rtpDtmf.m_u16Duration	= 1600;				// duration (in timestamp units)

				// send dtmf command
				RetCode_t ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDevice].device,
					XMS_IO_TYPE_VOIP_RTPDTMF, sizeof(rtpDtmf), &rtpDtmf);

/* to send rtp tone, use code below:
				Acs_VoIP_RTPTONE rtpTone = {0};
				rtpTone.m_u16Modulation		= 100;	// tone modulation
				rtpTone.m_s8Volume			= -32;	// volume (in dbm0 from -63 to 0)
				rtpTone.m_u16Duration		= 200;	// duration (in timestamp units)
				rtpTone.m_u8FrequencyNum	= 2;	// frequency number
				rtpTone.m_u16Frequency[0]	= 100;	// frequency 1
				rtpTone.m_u16Frequency[1]	= 800;	// frequency 2

				// send dtmf command
				RetCode_t ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDevice].device,
					XMS_IO_TYPE_VOIP_RTPTONE, sizeof(rtpTone), &rtpTone);*/
			}
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// open Voice Device
void CXMSVoIPDemoDlg::OnButtonOpenDeviceVoc() 
{
	RetCode_t ret;

	POSITION pos = m_lstVoc.GetFirstSelectedItemPosition();
	while (pos)
	{
		int iDevice = m_lstVoc.GetNextSelectedItem(pos);

		// opened already?
		if (g_deviceVoc[iDevice].bOpened)
			continue;

		// send open device command
		ret = XMS_ctsOpenDevice(g_acsHandle, &g_deviceVoc[iDevice].device, NULL);
	}
}

//////////////////////////////////////////////////////////////////////////
// close Voice Device
void CXMSVoIPDemoDlg::OnButtonCloseDeviceVoc() 
{
	POSITION pos = m_lstVoc.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("Select one device first"), _T("CloseDevice"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDevice = m_lstVoc.GetNextSelectedItem(pos);

	if (g_deviceVoc[iDevice].bOpened)
	{
		// send close device command
		RetCode_t ret = XMS_ctsCloseDevice(g_acsHandle, &g_deviceVoc[iDevice].device, NULL);
	}
}

//////////////////////////////////////////////////////////////////////////
// open all Voice Devices
void CXMSVoIPDemoDlg::OnButtonOpenAllVoc() 
{
	RetCode_t ret;

	for (int iDevice = 0; iDevice < g_iVocDevNum; ++iDevice)
	{
		// opened already?
		if (g_deviceVoc[iDevice].bOpened)
			continue;

		// send open device comannd
		ret = XMS_ctsOpenDevice(g_acsHandle, &g_deviceVoc[iDevice].device, NULL);
	}
}

//////////////////////////////////////////////////////////////////////////
// close all Voice Devices
void CXMSVoIPDemoDlg::OnButtonCloseAllVoc() 
{
	RetCode_t ret;

	for (int iDevice = 0; iDevice < g_iVocDevNum; ++iDevice)
	{
		// opened already?
		if (!g_deviceVoc[iDevice].bOpened)
			continue;

		// send close device command
		ret = XMS_ctsCloseDevice(g_acsHandle, &g_deviceVoc[iDevice].device, NULL);
	}
}

//////////////////////////////////////////////////////////////////////////
void CXMSVoIPDemoDlg::OnRadioH323() 
{
	UpdateData();
	m_strCalleePort = _T("1720");
	UpdateData(FALSE);
}

//////////////////////////////////////////////////////////////////////////
void CXMSVoIPDemoDlg::OnRadioSip() 
{
	UpdateData();
	m_strCalleePort = _T("5060");
	UpdateData(FALSE);
}

//////////////////////////////////////////////////////////////////////////
void CXMSVoIPDemoDlg::OnButtonBrowsePlayFile() 
{
	OPENFILENAME ofn = {0};
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetSafeHwnd();
	ofn.lpstrFile = m_strPlayFile.GetBuffer(_MAX_PATH);
	ofn.nMaxFile = _MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST|OFN_READONLY;
	ofn.lpstrTitle = _T("Select Play File...");

	BOOL bRet = GetOpenFileName(&ofn);

	m_strPlayFile.ReleaseBuffer();

	if (bRet)
		UpdateData(FALSE);
}

void CXMSVoIPDemoDlg::OnButtonBrowseRecordFile() 
{
	OPENFILENAME ofn = {0};
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetSafeHwnd();
	ofn.lpstrFile = m_strRecordFile.GetBuffer(_MAX_PATH);
	ofn.nMaxFile = _MAX_PATH;
	ofn.Flags = OFN_CREATEPROMPT|OFN_OVERWRITEPROMPT;
	ofn.lpstrTitle = _T("Select Record File...");

	BOOL bRet = GetSaveFileName(&ofn);

	m_strRecordFile.ReleaseBuffer();

	if (bRet)
		UpdateData(FALSE);
}

//////////////////////////////////////////////////////////////////////////
// play/stop file
void CXMSVoIPDemoDlg::OnButtonPlay() 
{
	POSITION pos = m_lstVoc.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("Select one voice device first"), _T("Play"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDevice = m_lstVoc.GetNextSelectedItem(pos);

	// playing ?
	if (_tcslen(g_deviceVoc[iDevice].tszPlayFile) > 0)
	{
		// stop playing
		ControlPlay_t cp = {0};
		cp.m_u16ControlType = XMS_STOP_PLAY;

		// send control play command
		RetCode_t ret = XMS_ctsControlPlay(g_acsHandle, &g_deviceVoc[iDevice].device, &cp, NULL);

		memset(g_deviceVoc[iDevice].tszPlayFile, 0, sizeof(g_deviceVoc[iDevice].tszPlayFile));
	}
	else
	{
		// start playing
		UpdateData();

		if (m_strPlayFile.IsEmpty())
		{
			MessageBox(_T("Select play file first"), _T("Play"), MB_OK|MB_ICONASTERISK);
			return;
		}

		// fill play property
		PlayProperty_t pp = {0};
		pp.m_u8DecodeType = m_iCodec == 0 ? XMS_Alaw_type : XMS_Ulaw_type;
		pp.m_u16PlayType = XMS_PLAY_TYPE_FILE;
		pp.m_u8SrcMode = m_iSampleRate == 0 ? XMS_SRC_8K : XMS_SRC_6K;

		strcpy(pp.m_s8PlayContent, m_strPlayFile);

		// send play command
		RetCode_t ret = XMS_ctsPlay(g_acsHandle, &g_deviceVoc[iDevice].device, &pp, NULL);

		g_deviceVoc[iDevice].iSampleRate = pp.m_u8SrcMode;
		g_deviceVoc[iDevice].iCodec = pp.m_u8DecodeType;
		strcpy(g_deviceVoc[iDevice].tszPlayFile, m_strPlayFile);
	}

	refreshListVoc(iDevice);

	refreshCtrlVoc();
}

//////////////////////////////////////////////////////////////////////////
// record/stop file
void CXMSVoIPDemoDlg::OnButtonRecord() 
{
	POSITION pos = m_lstVoc.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("Select one voice device first"), _T("Record"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDevice = m_lstVoc.GetNextSelectedItem(pos);

	// recording ?
	if (_tcslen(g_deviceVoc[iDevice].tszRecordFile) > 0)
	{
		// stop recording
		ControlRecord_t cr = {0};
		cr.m_u32ControlType = XMS_STOP_RECORD;

		// send control record command
		RetCode_t ret = XMS_ctsControlRecord(g_acsHandle, &g_deviceVoc[iDevice].device, &cr, NULL);

		memset(g_deviceVoc[iDevice].tszRecordFile, 0, sizeof(g_deviceVoc[iDevice].tszRecordFile));
	}
	else
	{
		int iDeviceIP = g_deviceVoc[iDevice].iVoIPDevice;
		if (iDeviceIP == -1)
		{
			MessageBox(_T("No IP device bind this voice device."), _T("Record"), MB_OK|MB_ICONERROR);
			return;
		}

		// start recording
		UpdateData();

		if (m_strRecordFile.IsEmpty())
		{
			MessageBox(_T("Select record file first"), _T("Record"), MB_OK|MB_ICONASTERISK);
			return;
		}

		// fill record property
		RecordProperty_t pr = {0};
		pr.m_u8EncodeType = m_iCodec == 0 ? XMS_Alaw_type : XMS_Ulaw_type;
		pr.m_u8SRCMode = m_iSampleRate == 0 ? XMS_SRC_8K : XMS_SRC_6K;
		pr.m_s8IsMixEnable = 1;
		pr.m_MixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_IP;
		pr.m_MixerControl.m_u16SRC_ChID1 = iDeviceIP;

		strcpy(pr.m_s8FileName, m_strRecordFile);

		// send record command
		RetCode_t ret = XMS_ctsRecord(g_acsHandle, &g_deviceVoc[iDevice].device,
			&pr, NULL);

		strcpy(g_deviceVoc[iDevice].tszRecordFile, m_strRecordFile);
	}

	refreshListVoc(iDevice);

	refreshCtrlVoc();
}

//////////////////////////////////////////////////////////////////////////
void CXMSVoIPDemoDlg::OnItemchangedListIP(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if (pNMListView->uNewState & LVIS_SELECTED)
	{
		// select the voice device binded if exists
		int iDeviceIP = pNMListView->iItem;
		int iDeviceVoc = g_deviceVoIP[iDeviceIP].iVoiceDevice;
		if (iDeviceVoc != -1)
		{
			// de-select all
/*			for (int iItem = 0; iItem < m_lstVoc.GetItemCount(); ++iItem)
			{
				if (m_lstVoc.GetItemState(iItem, LVIS_FOCUSED) == LVIS_FOCUSED)
					m_lstVoc.SetItemState(iItem, 0, LVIS_FOCUSED);
			}*/

			m_lstVoc.SetItemState(iDeviceVoc, LVIS_FOCUSED|LVIS_SELECTED, -1);
			m_lstVoc.EnsureVisible(iDeviceVoc, FALSE);
		}
	}

	refreshCtrlIP();

	refreshCtrlConf();

	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////
void CXMSVoIPDemoDlg::OnItemchangedListVoice(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if (pNMListView->uNewState & LVIS_SELECTED)
	{
		// select the IP device binded if exists
		int iDeviceVoc = pNMListView->iItem;
		int iDeviceIP = g_deviceVoc[iDeviceVoc].iVoIPDevice;
		if (iDeviceIP != -1)
		{
			// de-select all
			for (int iItem = 0; iItem < m_lstIP.GetItemCount(); ++iItem)
			{
				if (m_lstIP.GetItemState(iItem, LVIS_FOCUSED|LVIS_SELECTED) == (LVIS_FOCUSED|LVIS_SELECTED))
					m_lstIP.SetItemState(iItem, 0, LVIS_FOCUSED|LVIS_SELECTED);
			}

			m_lstIP.SetItemState(iDeviceIP, LVIS_FOCUSED|LVIS_SELECTED, -1);
			m_lstIP.EnsureVisible(iDeviceIP, FALSE);
		}

	}

	refreshCtrlVoc();

	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////
void CXMSVoIPDemoDlg::OnSelchangedTreeConf(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	refreshCtrlConf();

	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////
void CXMSVoIPDemoDlg::OnSetfocusEditServerAddr() 
{
	SetDefID(IDC_BUTTON_INIT);
}

void CXMSVoIPDemoDlg::OnSetfocusEditServerPort() 
{
	SetDefID(IDC_BUTTON_INIT);
}

void CXMSVoIPDemoDlg::OnSetfocusEditCalleeAddr() 
{
	SetDefID(IDC_BUTTON_MAKECALL);
}

void CXMSVoIPDemoDlg::OnSetfocusEditCalleePort() 
{
	SetDefID(IDC_BUTTON_MAKECALL);
}

void CXMSVoIPDemoDlg::OnSetfocusEditCalleeUserid() 
{
	SetDefID(IDC_BUTTON_MAKECALL);
}

void CXMSVoIPDemoDlg::OnSetfocusEditCalleeTelno() 
{
	SetDefID(IDC_BUTTON_MAKECALL);
}

void CXMSVoIPDemoDlg::OnSetfocusEditPlayfile() 
{
	SetDefID(IDC_BUTTON_PLAY);
}

//////////////////////////////////////////////////////////////////////////
void CXMSVoIPDemoDlg::enableDevice(const DeviceID_t *pDeviceID, BOOL bEnable)
{
	int iDevice;

	switch (pDeviceID->m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
		iDevice = pDeviceID->m_s16ChannelID;

		if (bEnable)
			g_deviceVoIP[iDevice].device = *pDeviceID;
		else
			resetDeviceVoIP(iDevice);

		g_deviceVoIP[iDevice].bOpened = bEnable;

		refreshListIP(iDevice);
		refreshCtrlIP();
		break;

	case XMS_DEVMAIN_VOICE:
		iDevice = pDeviceID->m_s16ChannelID;

		if (bEnable)
			g_deviceVoc[iDevice].device = *pDeviceID;
		else
			resetDeviceVoc(iDevice);

		g_deviceVoc[iDevice].bOpened = bEnable;

		refreshListVoc(iDevice);
		refreshCtrlVoc();
		break;

	case XMS_DEVMAIN_CONFERENCE:
		iDevice = pDeviceID->m_s16ChannelID;

		if (bEnable)
			g_deviceConf[iDevice].device = *pDeviceID;
		else
			resetDeviceConf(iDevice);

		g_deviceConf[iDevice].bOpened = bEnable;

		refreshTreeConf(iDevice);
		refreshCtrlConf();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// refresh item in IP Device list
void CXMSVoIPDemoDlg::refreshListIP(int iDevice)
{
	if (!g_deviceVoIP[iDevice].bOpened)
	{
		for (int i = 2; i < 12; ++i)
			m_lstIP.SetItemText(iDevice, i, _T("N/A"));
		return;
	}

	switch (g_deviceVoIP[iDevice].iProtocol)
	{
	case XMS_VOIP_PROTOCOL_H323:
		m_lstIP.SetItemText(iDevice, 2, _T("H.323"));
		break;
	case XMS_VOIP_PROTOCOL_SIP:
		m_lstIP.SetItemText(iDevice, 2, _T("SIP"));
		break;
	default:
		m_lstIP.SetItemText(iDevice, 2, _T("N/A"));
		break;
	}

	CString strBuf;

	// call state
	switch (g_deviceVoIP[iDevice].iState)
	{
	case DCS_FREE:
		strBuf = _T("FREE");
		break;
	case DCS_CALLOUT:
		strBuf = _T("CALLOUT");
		break;
	case DCS_CALLIN:
		strBuf = _T("CALLIN");
		{
			// highlight the device item
			POSITION pos = m_lstIP.GetFirstSelectedItemPosition();
			while (pos != NULL)
			{
				int iItem = m_lstIP.GetNextSelectedItem(pos);
				m_lstIP.SetItemState(iItem, 0, -1);
			}

			m_lstIP.SetItemState(iDevice, LVIS_FOCUSED|LVIS_SELECTED, -1);
		}

		m_lstIP.EnsureVisible(iDevice, FALSE);
		break;
	case DCS_ALERTING:
		strBuf = _T("ALERTING");
		break;
	case DCS_CONNECT:
		strBuf = _T("CONNECT");
		break;
	case DCS_DISCONNECT:
		strBuf = _T("DISCONNECT");
		break;
	default:
		// protocol special states
		strBuf = _T("OTHER");
		break;
	}

	m_lstIP.SetItemText(iDevice, 3, strBuf);

	// caller info
	if (g_deviceVoIP[iDevice].addrCaller.port > 0)
		strBuf.Format(_T("%s:%d"),
			g_deviceVoIP[iDevice].addrCaller.tszAddr,
			g_deviceVoIP[iDevice].addrCaller.port);
	else
		strBuf = g_deviceVoIP[iDevice].addrCaller.tszAddr;
	m_lstIP.SetItemText(iDevice, 4, strBuf);

	m_lstIP.SetItemText(iDevice, 5, g_deviceVoIP[iDevice].addrCaller.tszUserID);
	m_lstIP.SetItemText(iDevice, 6, g_deviceVoIP[iDevice].addrCaller.tszTelNo);

	// callee info
	if (g_deviceVoIP[iDevice].addrCallee.port > 0)
		strBuf.Format(_T("%s:%d"),
			g_deviceVoIP[iDevice].addrCallee.tszAddr,
			g_deviceVoIP[iDevice].addrCallee.port);
	else
		strBuf = g_deviceVoIP[iDevice].addrCallee.tszAddr;
	m_lstIP.SetItemText(iDevice, 7, strBuf);

	m_lstIP.SetItemText(iDevice, 8, g_deviceVoIP[iDevice].addrCallee.tszUserID);
	m_lstIP.SetItemText(iDevice, 9, g_deviceVoIP[iDevice].addrCallee.tszTelNo);

	// dtmf
	m_lstIP.SetItemText(iDevice, 10, g_deviceVoIP[iDevice].szDtmf);

	// Voice Device binded
	if (g_deviceVoIP[iDevice].iVoiceDevice != -1)
	{
		strBuf.Format(_T("%d"), g_deviceVoIP[iDevice].iVoiceDevice);
		m_lstIP.SetItemText(iDevice, 11, strBuf);
	}
	else
		m_lstIP.SetItemText(iDevice, 11, _T("N/A"));

	m_lstIP.EnsureVisible(iDevice, FALSE);
}

//////////////////////////////////////////////////////////////////////////
// refresh ui control states in IP Device panel
void CXMSVoIPDemoDlg::refreshCtrlIP()
{
	POSITION pos = m_lstIP.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;

	int iDevice = m_lstIP.GetNextSelectedItem(pos);

	GetDlgItem(IDC_BUTTON_OPEN_IP)->EnableWindow(!g_deviceVoIP[iDevice].bOpened);
	GetDlgItem(IDC_BUTTON_CLOSE_IP)->EnableWindow(g_deviceVoIP[iDevice].bOpened);

	GetDlgItem(IDC_BUTTON_OPENALL_IP)->EnableWindow();
	GetDlgItem(IDC_BUTTON_CLOSEALL_IP)->EnableWindow();
	GetDlgItem(IDC_BUTTON_REG)->EnableWindow();
	GetDlgItem(IDC_BUTTON_UNREG)->EnableWindow();

	if (!g_deviceVoIP[iDevice].bOpened)
	{
		GetDlgItem(IDC_BUTTON_MAKECALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ANSWERCALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_DROPCALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_BIND)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_UNBIND)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_TRANSFERCALL)->EnableWindow(FALSE);
		return;
	}

	switch (g_deviceVoIP[iDevice].iState)
	{
	case DCS_FREE:
		GetDlgItem(IDC_BUTTON_MAKECALL)->EnableWindow();
		GetDlgItem(IDC_BUTTON_ANSWERCALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_DROPCALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_BIND)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_UNBIND)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_TRANSFERCALL)->EnableWindow(FALSE);
		break;
	case DCS_CALLOUT:
		GetDlgItem(IDC_BUTTON_MAKECALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ANSWERCALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_DROPCALL)->EnableWindow();
		GetDlgItem(IDC_BUTTON_BIND)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_UNBIND)->EnableWindow(FALSE);
		break;
	case DCS_CALLIN:
		GetDlgItem(IDC_BUTTON_MAKECALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ANSWERCALL)->EnableWindow();
		GetDlgItem(IDC_BUTTON_DROPCALL)->EnableWindow();
		GetDlgItem(IDC_BUTTON_BIND)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_UNBIND)->EnableWindow(FALSE);
		break;
	case DCS_ALERTING:
		GetDlgItem(IDC_BUTTON_MAKECALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ANSWERCALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_DROPCALL)->EnableWindow();
		GetDlgItem(IDC_BUTTON_BIND)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_UNBIND)->EnableWindow(FALSE);
		break;
	case DCS_CONNECT:
		GetDlgItem(IDC_BUTTON_MAKECALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ANSWERCALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_DROPCALL)->EnableWindow();
		GetDlgItem(IDC_BUTTON_TRANSFERCALL)->EnableWindow();

		{
/*			POSITION pos = m_lstVoc.GetFirstSelectedItemPosition();
			int iDeviceVoc = -1;
			if (pos != NULL)
				iDeviceVoc = m_lstVoc.GetNextSelectedItem(pos);*/
			int iDeviceVoc = m_lstVoc.GetNextItem(-1, LVIS_FOCUSED);
			GetDlgItem(IDC_BUTTON_BIND)->EnableWindow(g_deviceVoIP[iDevice].iVoiceDevice == -1 &&
				 iDeviceVoc != -1 && g_deviceVoc[iDeviceVoc].bOpened &&
				 g_deviceVoc[iDeviceVoc].iVoIPDevice == -1);
		}

		GetDlgItem(IDC_BUTTON_UNBIND)->EnableWindow(g_deviceVoIP[iDevice].iVoiceDevice != -1);
		break;
	case DCS_DISCONNECT:
		GetDlgItem(IDC_BUTTON_MAKECALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ANSWERCALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_DROPCALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_BIND)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_UNBIND)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_TRANSFERCALL)->EnableWindow(FALSE);
		break;
	default:
		break;
	}

	int idBtnDtmf[] = {
		IDC_BUTTON_DTMF0, IDC_BUTTON_DTMF1, IDC_BUTTON_DTMF2, IDC_BUTTON_DTMF3,
		IDC_BUTTON_DTMF4, IDC_BUTTON_DTMF5, IDC_BUTTON_DTMF6, IDC_BUTTON_DTMF7,
		IDC_BUTTON_DTMF8, IDC_BUTTON_DTMF9, IDC_BUTTON_DTMFA, IDC_BUTTON_DTMFP
	};
	for (int i = 0; i < sizeof(idBtnDtmf)/sizeof(int); ++i)
	{
		GetDlgItem(idBtnDtmf[i])->EnableWindow(g_deviceVoIP[iDevice].iState == DCS_CONNECT);
	}

	GetDlgItem(IDC_BUTTON_3PCONF)->EnableWindow(m_lstIP.GetSelectedCount() >= 3);
}

//////////////////////////////////////////////////////////////////////////
// refresh item in Voice Device list
void CXMSVoIPDemoDlg::refreshListVoc(int iDevice)
{
	if (!g_deviceVoc[iDevice].bOpened)
	{
		for (int i = 2; i < 7; ++i)
			m_lstVoc.SetItemText(iDevice, i, _T("N/A"));
		return;
	}

	// play file
	m_lstVoc.SetItemText(iDevice, 2, g_deviceVoc[iDevice].tszPlayFile);

	// play file codec & sample rate
	if (_tcslen(g_deviceVoc[iDevice].tszPlayFile) > 0)
	{
		switch (g_deviceVoc[iDevice].iSampleRate)
		{
		case XMS_SRC_8K:
			m_lstVoc.SetItemText(iDevice, 3, _T("8K"));
			break;
		case XMS_SRC_6K:
			m_lstVoc.SetItemText(iDevice, 3, _T("6K"));
			break;
		}

		switch (g_deviceVoc[iDevice].iCodec)
		{
		case XMS_Alaw_type:
			m_lstVoc.SetItemText(iDevice, 4, _T("A Law"));
			break;
		case XMS_Ulaw_type:
			m_lstVoc.SetItemText(iDevice, 4, _T("u Law"));
			break;
		}
	}
	else
	{
		m_lstVoc.SetItemText(iDevice, 3, _T(""));
		m_lstVoc.SetItemText(iDevice, 4, _T(""));
	}

	// record file
	m_lstVoc.SetItemText(iDevice, 5, g_deviceVoc[iDevice].tszRecordFile);

	// IP Device binded
	if (g_deviceVoc[iDevice].iVoIPDevice != -1)
	{
		CString strBuf;
		strBuf.Format(_T("%d"), g_deviceVoc[iDevice].iVoIPDevice);
		m_lstVoc.SetItemText(iDevice, 6, strBuf);
	}
	else
		m_lstVoc.SetItemText(iDevice, 6, _T("N/A"));

	m_lstVoc.EnsureVisible(iDevice, FALSE);
}

//////////////////////////////////////////////////////////////////////////
// refresh ui control states in Voice Device panel
void CXMSVoIPDemoDlg::refreshCtrlVoc()
{
	POSITION pos = m_lstVoc.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;

	int iDeviceVoc = m_lstVoc.GetNextSelectedItem(pos);

/*	int iDeviceIP = -1;
	pos = m_lstIP.GetFirstSelectedItemPosition();
	if (pos != NULL)
		iDeviceIP = m_lstIP.GetNextSelectedItem(pos);*/
	int iDeviceIP = m_lstIP.GetNextItem(-1, LVIS_FOCUSED);

	GetDlgItem(IDC_BUTTON_OPEN_VOC)->EnableWindow(!g_deviceVoc[iDeviceVoc].bOpened);
	GetDlgItem(IDC_BUTTON_CLOSE_VOC)->EnableWindow(g_deviceVoc[iDeviceVoc].bOpened);

	GetDlgItem(IDC_BUTTON_OPENALL_VOC)->EnableWindow();
	GetDlgItem(IDC_BUTTON_CLOSEALL_VOC)->EnableWindow();

	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(g_deviceVoc[iDeviceVoc].bOpened);
	GetDlgItem(IDC_BUTTON_RECORD)->EnableWindow(g_deviceVoc[iDeviceVoc].bOpened);

	GetDlgItem(IDC_BUTTON_BIND)->EnableWindow(g_deviceVoc[iDeviceVoc].iVoIPDevice == -1 &&
		g_deviceVoIP[iDeviceIP].iState == DCS_CONNECT &&
		g_deviceVoIP[iDeviceIP].iVoiceDevice == -1);
	GetDlgItem(IDC_BUTTON_UNBIND)->EnableWindow(g_deviceVoc[iDeviceVoc].iVoIPDevice != -1 &&
		g_deviceVoIP[g_deviceVoc[iDeviceVoc].iVoIPDevice].iVoiceDevice == iDeviceVoc);

	if (_tcslen(g_deviceVoc[iDeviceVoc].tszPlayFile) > 0)
		GetDlgItem(IDC_BUTTON_PLAY)->SetWindowText(_T("Stop"));
	else
		GetDlgItem(IDC_BUTTON_PLAY)->SetWindowText(_T("Play"));

	if (_tcslen(g_deviceVoc[iDeviceVoc].tszRecordFile) > 0)
		GetDlgItem(IDC_BUTTON_RECORD)->SetWindowText(_T("Stop"));
	else
		GetDlgItem(IDC_BUTTON_RECORD)->SetWindowText(_T("Record"));
}

//////////////////////////////////////////////////////////////////////////
// refresh item in conference tree
void CXMSVoIPDemoDlg::refreshTreeConf(int iDevice)
{
	HTREEITEM hItemConf = m_treeConf.GetRootItem();

	for (int iDeviceConf = 0; iDeviceConf < iDevice; ++iDeviceConf)
		hItemConf = m_treeConf.GetNextItem(hItemConf, TVGN_NEXT);

	ASSERT(hItemConf != NULL);

	// clear all members in conference tree
	while (m_treeConf.ItemHasChildren(hItemConf))
	{
		m_treeConf.DeleteItem(m_treeConf.GetChildItem(hItemConf));
	}

	for (int iDeviceIP = 0; iDeviceIP < g_deviceConf[iDevice].iMemberCnt; ++iDeviceIP)
	{
		CString str;
		str.Format(_T("IP #%d"), iDeviceIP);

		HTREEITEM hItemIP = m_treeConf.InsertItem(str, hItemConf);
		m_treeConf.SetItemData(hItemIP, iDeviceIP);

		m_treeConf.Expand(hItemConf, TVE_EXPAND);
	}
}

//////////////////////////////////////////////////////////////////////////
// refresh ui control states in Conference Device panel
void CXMSVoIPDemoDlg::refreshCtrlConf()
{
	HTREEITEM hItemSel = m_treeConf.GetSelectedItem();

	if (hItemSel == NULL)
		return;

	HTREEITEM hItemConf = NULL;
	HTREEITEM hItemIP = NULL;

	if (m_treeConf.GetParentItem(hItemSel) == NULL)
	{
		hItemConf = hItemSel;
	}
	else
	{
		hItemConf = m_treeConf.GetParentItem(hItemSel);
		hItemIP = hItemSel;
	}

	int iDeviceConf = m_treeConf.GetItemData(hItemConf);

	GetDlgItem(IDC_BUTTON_OPEN_CONF)->EnableWindow(!g_deviceConf[iDeviceConf].bOpened);
	GetDlgItem(IDC_BUTTON_CLOSE_CONF)->EnableWindow(g_deviceConf[iDeviceConf].bOpened);

	int iDeviceIP = -1;
	POSITION pos = m_lstIP.GetFirstSelectedItemPosition();
	if (pos != NULL)
		iDeviceIP = m_lstIP.GetNextSelectedItem(pos);
	GetDlgItem(IDC_BUTTON_JOIN_CONF)->EnableWindow(g_deviceConf[iDeviceConf].bOpened &&
		iDeviceIP != -1 && g_deviceVoIP[iDeviceIP].iState == DCS_CONNECT);

	GetDlgItem(IDC_BUTTON_LEAVE_CONF)->EnableWindow(hItemIP != NULL);

	GetDlgItem(IDC_BUTTON_CLEAR_CONF)->EnableWindow(g_deviceConf[iDeviceConf].bOpened &&
		m_treeConf.ItemHasChildren(hItemConf));

	GetDlgItem(IDC_BUTTON_CHAIRMAN)->EnableWindow(hItemIP != NULL);
}

//////////////////////////////////////////////////////////////////////////
// open Conference Device
void CXMSVoIPDemoDlg::OnButtonOpenConf() 
{
	RetCode_t ret;

	HTREEITEM hItem = m_treeConf.GetSelectedItem();

	int iDevice = m_treeConf.GetItemData(hItem);

	// opened already?
	if (!g_deviceConf[iDevice].bOpened)
	{
		// send open device command
		ret = XMS_ctsOpenDevice(g_acsHandle, &g_deviceConf[iDevice].device, NULL);
	}
}

//////////////////////////////////////////////////////////////////////////
// close Conference Device
void CXMSVoIPDemoDlg::OnButtonCloseConf() 
{
	RetCode_t ret;

	HTREEITEM hItem = m_treeConf.GetSelectedItem();

	int iDevice = m_treeConf.GetItemData(hItem);

	// opened already?
	if (g_deviceConf[iDevice].bOpened)
	{
		// send close device command
		ret = XMS_ctsCloseDevice(g_acsHandle, &g_deviceConf[iDevice].device, NULL);
	}
}

//////////////////////////////////////////////////////////////////////////
// join conference
void CXMSVoIPDemoDlg::OnButtonJoinConf() 
{
	HTREEITEM hItemConf = m_treeConf.GetSelectedItem();
	if (hItemConf == NULL)
	{
		MessageBox(_T("Please select one Conference Device first"), _T("JoinConf"), MB_OK|MB_ICONASTERISK);
		return;
	}

	HTREEITEM hItemRoot = m_treeConf.GetParentItem(hItemConf);
	if (hItemRoot != NULL)
		hItemConf = hItemRoot;

	int iDeviceConf = m_treeConf.GetItemData(hItemConf);

	if (g_deviceConf[iDeviceConf].iMemberCnt+1 >= MAX_CONF_MEMBER)
	{
		MessageBox(_T("Members full in this conference"), _T("JoinConf"), MB_OK|MB_ICONERROR);
		return;
	}

	POSITION pos = m_lstIP.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("Please select one IP Device first"), _T("JoinConf"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDeviceIP = m_lstIP.GetNextSelectedItem(pos);

	// check if has joined conference already
	for (int iDevice = 0; iDevice < g_deviceConf[iDeviceConf].iMemberCnt; ++iDevice)
	{
		if (iDeviceIP == g_deviceConf[iDeviceConf].iMember[iDevice])
		{
			MessageBox(_T("IP Device already exists in this conference!"), _T("JoinConf"), MB_OK|MB_ICONERROR);
			return;
		}
	}

	CmdParamData_Conf_t pdc = {0};
	pdc.m_u8InputOpt = XMS_CONF_INPUT_OPT_NORMAL;
	pdc.m_u8OutputOpt = XMS_CONF_OUTPUT_OPT_NORMAL;

	// send join conference command
	RetCode_t ret = XMS_ctsJoinToConf(g_acsHandle,
		&g_deviceConf[iDeviceConf].device,
		&g_deviceVoIP[iDeviceIP].device,
		&pdc, NULL);

	g_deviceConf[iDeviceConf].iMember[g_deviceConf[iDeviceConf].iMemberCnt] = iDeviceIP;
	++g_deviceConf[iDeviceConf].iMemberCnt;

	// add to conference tree
	CString str;
	str.Format(_T("IP #%d"), iDeviceIP);

	HTREEITEM hItemIP = m_treeConf.InsertItem(str, hItemConf);
	m_treeConf.SetItemData(hItemIP, iDeviceIP);

	m_treeConf.Expand(hItemConf, TVE_EXPAND);
}

//////////////////////////////////////////////////////////////////////////
// leave conference
void CXMSVoIPDemoDlg::OnButtonLeaveConf() 
{
	HTREEITEM hItemIP = m_treeConf.GetSelectedItem();
	if (hItemIP == NULL)
	{
		MessageBox(_T("Please select one Conference Device first"), _T("QuitConf"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDeviceIP = m_treeConf.GetItemData(hItemIP);

	// make sure the selected item is an IP Device node
	HTREEITEM hItemConf = m_treeConf.GetParentItem(hItemIP);
	if (hItemConf == NULL)
	{
		MessageBox(_T("Please select one IP Device first"), _T("QuitConf"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDeviceConf = m_treeConf.GetItemData(hItemConf);

	CmdParamData_Conf_t pdc = {0};

	// send leave conference command
	RetCode_t ret = XMS_ctsLeaveFromConf(g_acsHandle,
		&g_deviceConf[iDeviceConf].device,
		&g_deviceVoIP[iDeviceIP].device,
		&pdc, NULL);

	// find the conference member to remove
	for (int iDevice = 0; iDevice < g_deviceConf[iDeviceConf].iMemberCnt; ++iDevice)
	{
		if (g_deviceConf[iDeviceConf].iMember[iDevice] == iDeviceIP)
		{
			// got'cha
			for (int iDeviceMove = iDevice; iDeviceMove < g_deviceConf[iDeviceConf].iMemberCnt-1; ++iDeviceMove)
			{
				g_deviceConf[iDeviceConf].iMember[iDeviceMove] = g_deviceConf[iDeviceConf].iMember[iDeviceMove+1];
			}

			--g_deviceConf[iDeviceConf].iMemberCnt;
		}
	}

	// remove from conference tree
	m_treeConf.DeleteItem(hItemIP);
}

//////////////////////////////////////////////////////////////////////////
// clear conference
void CXMSVoIPDemoDlg::OnButtonClearConf() 
{
	HTREEITEM hItemConf = m_treeConf.GetSelectedItem();
	if (hItemConf == NULL)
	{
		MessageBox(_T("Please select one Conference Device first"), _T("JoinConf"), MB_OK|MB_ICONASTERISK);
		return;
	}

	HTREEITEM hItemRoot = m_treeConf.GetParentItem(hItemConf);
	if (hItemRoot != NULL)
		hItemConf = hItemRoot;

	int iDeviceConf = m_treeConf.GetItemData(hItemConf);

	// send clear conference command
	RetCode_t ret = XMS_ctsClearConf(g_acsHandle, &g_deviceConf[iDeviceConf].device, NULL);

	g_deviceConf[iDeviceConf].iMemberCnt = 0;

	// clear members in conference tree
	while (m_treeConf.ItemHasChildren(hItemConf))
	{
		m_treeConf.DeleteItem(m_treeConf.GetChildItem(hItemConf));
	}
}

//////////////////////////////////////////////////////////////////////////
// make party member chairman in video session
void CXMSVoIPDemoDlg::OnButtonChairman() 
{
	HTREEITEM hItemIP = m_treeConf.GetSelectedItem();
	if (hItemIP == NULL)
	{
		MessageBox(_T("Please select one party member in conference firest"), _T("Make Chairman"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDeviceIP = m_treeConf.GetItemData(hItemIP);

	// make sure the selected item is an IP Device node
	HTREEITEM hItemConf = m_treeConf.GetParentItem(hItemIP);
	if (hItemConf == NULL)
	{
		MessageBox(_T("Please select one party member in conference first"), _T("QuitConf"), MB_OK|MB_ICONASTERISK);
		return;
	}

	int iDeviceConf = m_treeConf.GetItemData(hItemConf);

	Acs_VoIP_Mixer paramMixer = {0};
	paramMixer.m_s8Video = TRUE;

	paramMixer.m_u8SRC1_Ctrl = XMS_MIXER_FROM_IP;
	paramMixer.m_u16SRC_ChID1 = g_deviceVoIP[iDeviceIP].device.m_s16ChannelID;

	for (int iMember = 0; iMember < g_deviceConf[iDeviceConf].iMemberCnt; ++iMember)
	{
		XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[g_deviceConf[iDeviceConf].iMember[iMember]].device,
			VOIP_PARAM_RTPMIXER, sizeof(paramMixer), &paramMixer);
	}
}

BOOL CXMSVoIPDemoDlg::DestroyWindow() 
{
	m_pdlgRtp->DestroyWindow();
	delete m_pdlgRtp;

	// close XMS service
	for (int iDevice = 0; iDevice < g_iVoIPDevNum; ++iDevice)
	{
		// opened already?
		if (!g_deviceVoIP[iDevice].bOpened)
			continue;

		// send close device command
		XMS_ctsCloseDevice(g_acsHandle, &g_deviceVoIP[iDevice].device, NULL);
	}

	// wait for close device command to complete
	Sleep(50);

	saveConfig();

	return CDialog::DestroyWindow();
}

void CXMSVoIPDemoDlg::OnDblclkListIp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE pnmItem = (LPNMITEMACTIVATE)pNMHDR;

	int iDeviceIP = pnmItem->iItem;

	if (iDeviceIP == -1 || !g_deviceVoIP[iDeviceIP].bOpened)
		return;

	// get rtp address
	Acs_VoIP_RTPADDR paramRtpAddr = {0};
	XMS_ctsGetParam(g_acsHandle, &g_deviceVoIP[iDeviceIP].device, VOIP_PARAM_RTPADDR, sizeof(paramRtpAddr), &paramRtpAddr);

	// get rtp codec
	Acs_VoIP_RTPCODEC paramRtpCodec = {0};
	XMS_ctsGetParam(g_acsHandle, &g_deviceVoIP[iDeviceIP].device, VOIP_PARAM_RTPCODEC, sizeof(paramRtpCodec), &paramRtpCodec);

	m_pdlgRtp->m_iDeviceIP = iDeviceIP;

	m_pdlgRtp->ShowWindow(SW_SHOW);

	*pResult = 0;
}

void CXMSVoIPDemoDlg::OnButtonReg() 
{
	// TODO: Add your control notification handler code here

	Acs_VoIP_SIPREGEX reg = {0};
	UpdateData();
	strcpy(reg.m_s8Password, m_strCalleePassword);
	strcpy(reg.m_s8TelNo, m_strCalleeTelNo);
	strcpy(reg.m_s8Username, m_strCalleeUserID);
	strcpy(reg.m_s8ProxyAddress, m_strRegAddr);
	strcpy(reg.m_s8UserID, m_strRegUsername);
	reg.m_u16ProxyPort = atoi(m_strCalleePort);
	// send dtmf command
	RetCode_t ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[0].device,
		XMS_IO_TYPE_VOIP_SIPREG, sizeof(reg), &reg);
}

void CXMSVoIPDemoDlg::OnButtonUnreg()
{
	// TODO: Add your control notification handler code here
	Acs_VoIP_SIPREGEX reg = {0};
	UpdateData();
	strcpy(reg.m_s8Password, m_strCalleePassword);
	strcpy(reg.m_s8TelNo, m_strCalleeTelNo);
	strcpy(reg.m_s8Username, m_strCalleeUserID);
	strcpy(reg.m_s8ProxyAddress, m_strRegAddr);
	strcpy(reg.m_s8UserID, m_strRegUsername);
	reg.m_u16ProxyPort = atoi(m_strCalleePort);
	// send dtmf command
	RetCode_t ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[0].device,
		XMS_IO_TYPE_VOIP_SIPUNREG, sizeof(reg), &reg);
}

void CXMSVoIPDemoDlg::OnButtonTransfercall() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_lstIP.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("Please select one IP Device with connected call first"), _T("Call Transfer"), MB_OK|MB_ICONASTERISK);
		return;
	}
	
	DJ_S8 iDestSlot = 0;
	char szCalleeTelNo[20] = "";

	CDialogCallTransfer dlg;
	if(dlg.DoModal()!=IDOK)
		return;

	int iDevice = m_lstIP.GetNextSelectedItem(pos);
	iDestSlot = dlg.m_nDestSlot;
	strcpy(szCalleeTelNo, dlg.m_szCalleeTelNo);
	
	VoIPCallModifyPrivate_t callModify = {0};
	callModify.m_PrivateData.m_u32DataSize = sizeof(VoIPCallModifyPrivate_t);
	callModify.m_u8MediaCapNum = 0;
	// set media mode to recvonly
	callModify.u8MediaMode = 2;

	// send clear call command
	RetCode_t ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDevice].device, XMS_IO_TYPE_VOIP_CALLMODIFY, sizeof(VoIPCallModifyPrivate_t), (void*)&callModify);

	Acs_VoIP_Transfer callTransfer = {0};
	callTransfer.m_u8SrcUnitId = m_iDSP;
	callTransfer.m_u8DstUnitId = m_iDSP;
	callTransfer.m_u16DstCallId = iDestSlot;
	strncpy(callTransfer.m_s8TelNo, szCalleeTelNo, sizeof(callTransfer.m_s8TelNo));
	
	// send clear call command
	ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDevice].device, XMS_IO_TYPE_VOIP_TRANSFER, sizeof(Acs_VoIP_Transfer), (void*)&callTransfer);
}
