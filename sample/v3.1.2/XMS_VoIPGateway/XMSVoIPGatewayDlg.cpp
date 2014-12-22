// XMSVoIPGatewayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSVoIPGateway.h"
#include "XMSVoIPGatewayDlg.h"

#include "winsock2.h"

#include "DJAcsAPIDef.h"
#include "DJAcsDevState.h"

#include "XMSData.h"
#include "XMSEventHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// init XMS device structs
void initXMS();

/////////////////////////////////////////////////////////////////////////////
// CXMSVoIPGatewayDlg dialog

CXMSVoIPGatewayDlg::CXMSVoIPGatewayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXMSVoIPGatewayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXMSVoIPGatewayDlg)
	m_uiServerPort = 9001;
	m_strServerIP = _T("");
	m_strUsername = _T("");
	m_strPassword = _T("");
	m_iProtocol = 0;
	m_iDSP = 1;
	m_strDialPlan = _T("Dial Plan:\r\n    IP User:\tRegister (or Set Gateway) to Keygoe and Dial Trunk's Assigned Number Directly (e.g. 001)\r\n    Analog User:\tDial IP User's Registered Number Followed by \"#\" (e.g. 123#) or\r\n\t\tDial Direct IP Address Seperated by \"*\" Followed by \"#\" (e.g. 192*168*0*1#)");
	m_bEC = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	GetModuleFileName(NULL, m_strIniFile.GetBuffer(_MAX_PATH), _MAX_PATH);
	m_strIniFile.ReleaseBuffer();
	m_strIniFile.Replace(_T(".exe"), _T(".ini"));

	loadConfig();
}

void CXMSVoIPGatewayDlg::loadConfig()
{
	GetPrivateProfileString(_T("Server"), _T("IP"), _T(""), m_strServerIP.GetBuffer(100), 100, m_strIniFile);
	m_strServerIP.ReleaseBuffer();

	if (m_strServerIP.IsEmpty())
	{
		// get local host ip
		char hostname[256] = {0};
		if (gethostname(hostname, sizeof(hostname)) == 0)
		{
			HOSTENT *he	= gethostbyname(hostname);

			if (he != NULL)
			{
				m_strServerIP = inet_ntoa(*((struct in_addr *)he->h_addr_list[0]));
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

	m_bEC = GetPrivateProfileInt(_T("Server"), _T("EC"), TRUE, m_strIniFile);

	for (int iDeviceTrk = 0; iDeviceTrk < MAX_DEVICE_INTERFACE; ++iDeviceTrk)
	{
		CString strbuf;
		strbuf.Format(_T("%d"), iDeviceTrk);
		GetPrivateProfileString(_T("Trunk"), strbuf, _T(""), g_deviceTrunk[iDeviceTrk].szTelNo,
			sizeof(g_deviceTrunk[iDeviceTrk].szTelNo), m_strIniFile);
	}
}

void CXMSVoIPGatewayDlg::saveConfig()
{
	UpdateData();

	WritePrivateProfileString(_T("Server"), _T("IP"), m_strServerIP, m_strIniFile);
	CString strbuf;
	strbuf.Format(_T("%d"), m_uiServerPort);
	WritePrivateProfileString(_T("Server"), _T("Port"), strbuf, m_strIniFile);
	WritePrivateProfileString(_T("Server"), _T("Username"), m_strUsername, m_strIniFile);
	WritePrivateProfileString(_T("Server"), _T("Password"), m_strPassword, m_strIniFile);
	strbuf.Format(_T("%d"), m_iDSP);
	WritePrivateProfileString(_T("Server"), _T("DSP"), strbuf, m_strIniFile);

	strbuf.Format(_T("%d"), m_iProtocol);
	WritePrivateProfileString(_T("Callee"), _T("Protocol"), strbuf, m_strIniFile);

	strbuf.Format(_T("%d"), m_bEC);
	WritePrivateProfileString(_T("Server"), _T("EC"), strbuf, m_strIniFile);

	for (int iDeviceTrk = 0; iDeviceTrk < g_iTrunkDevNum; ++iDeviceTrk)
	{
		strbuf.Format(_T("%d"), iDeviceTrk);
		WritePrivateProfileString(_T("Trunk"), strbuf, g_deviceTrunk[iDeviceTrk].szTelNo, m_strIniFile);
	}
}

void CXMSVoIPGatewayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXMSVoIPGatewayDlg)
	DDX_Control(pDX, IDC_LIST_TRUNK, m_lstTrunk);
	DDX_Control(pDX, IDC_LIST_IP, m_lstIP);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_uiServerPort);
	DDX_Text(pDX, IDC_EDIT_SERVER_IP, m_strServerIP);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUsername);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Radio(pDX, IDC_RADIO_H323, m_iProtocol);
	DDX_Text(pDX, IDC_EDIT_DSP, m_iDSP);
	DDX_Text(pDX, IDC_EDIT_DIALPLAN, m_strDialPlan);
	DDX_Check(pDX, IDC_CHECK_EC, m_bEC);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXMSVoIPGatewayDlg, CDialog)
	//{{AFX_MSG_MAP(CXMSVoIPGatewayDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonInit)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LIST_TRUNK, OnBeginlabeleditListTrunk)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_TRUNK, OnEndlabeleditListTrunk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TRUNK, OnDblclkListTrunk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMSVoIPGatewayDlg message handlers

HFONT g_hFont = NULL;

BOOL CALLBACK replaceFont(HWND hwndChild, LPARAM lParam)
{
	TCHAR tszClassName[256] = {0};
	if (GetClassName(hwndChild, tszClassName, sizeof(tszClassName)) > 0 &&
		(_tcscmp(tszClassName, _T("Button")) == 0 ||
		GetDlgCtrlID(hwndChild) == IDC_EDIT_DIALPLAN))
	{
		LONG lStyle = GetWindowLong(hwndChild, GWL_STYLE);
		if ((lStyle & BS_GROUPBOX) != BS_GROUPBOX)
			SendMessage(hwndChild, WM_SETFONT, (WPARAM)g_hFont, 0);
	}

	return TRUE;
}

BOOL CXMSVoIPGatewayDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXMSVoIPGatewayDlg::OnPaint() 
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
HCURSOR CXMSVoIPGatewayDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////
// init list control
void CXMSVoIPGatewayDlg::initUI()
{
	// IP Device list
	m_lstIP.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_lstIP.InsertColumn(0, _T("Header"), LVCFMT_LEFT, 0);
	m_lstIP.InsertColumn(1, _T("#"), LVCFMT_CENTER, 35);
	m_lstIP.InsertColumn(2, _T("Protocol"), LVCFMT_CENTER, 60);
	m_lstIP.InsertColumn(3, _T("State"), LVCFMT_CENTER, 60);
	m_lstIP.InsertColumn(4, _T("Caller Address"), LVCFMT_CENTER, 120);
	m_lstIP.InsertColumn(5, _T("Caller UserID"), LVCFMT_CENTER, 80);
	m_lstIP.InsertColumn(6, _T("Caller TelNo"), LVCFMT_CENTER, 75);
	m_lstIP.InsertColumn(7, _T("Callee Address"), LVCFMT_CENTER, 120);
	m_lstIP.InsertColumn(8, _T("Callee UserID"), LVCFMT_CENTER, 80);
	m_lstIP.InsertColumn(9, _T("Callee TelNo"), LVCFMT_CENTER, 75);
	m_lstIP.InsertColumn(10, _T("RegTel"), LVCFMT_CENTER, 60);
	m_lstIP.InsertColumn(11, _T("Trunk"), LVCFMT_CENTER, 40);

	// Interface Device list
	m_lstTrunk.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_lstTrunk.InsertColumn(0, _T("Header"), LVCFMT_LEFT, 0);
	m_lstTrunk.InsertColumn(1, _T("#"), LVCFMT_CENTER, 35);
	m_lstTrunk.InsertColumn(2, _T("SubType"), LVCFMT_CENTER, 100);
	m_lstTrunk.InsertColumn(3, _T("State"), LVCFMT_CENTER, 60);
	m_lstTrunk.InsertColumn(4, _T("Caller Num"), LVCFMT_CENTER, 80);
	m_lstTrunk.InsertColumn(5, _T("Callee Num"), LVCFMT_CENTER, 80);
	m_lstTrunk.InsertColumn(6, _T("DTMF"), LVCFMT_CENTER, 100);
	m_lstTrunk.InsertColumn(7, _T("Voc"), LVCFMT_CENTER, 40);
	m_lstTrunk.InsertColumn(8, _T("IP"), LVCFMT_CENTER, 40);
	m_lstTrunk.InsertColumn(9, _T("TelNo"), LVCFMT_CENTER, 80);
}

//////////////////////////////////////////////////////////////////////////
// init XMS Device structs
void initXMS()
{
	int iDevice;

	for ( iDevice = 0; iDevice < MAX_DEVICE_BOARD; ++iDevice)
	{
		memset(&g_deviceBoard[iDevice], -1, sizeof(DeviceID_t));
	}

	for (iDevice = 0; iDevice < MAX_DEVICE_VOIP; ++iDevice)
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

	for (iDevice = 0; iDevice < MAX_DEVICE_INTERFACE; ++iDevice)
	{
		g_deviceTrunk[iDevice].bOpened = FALSE;
		memset(&g_deviceTrunk[iDevice].device, -1, sizeof(DeviceID_t));
		resetDeviceTrunk(iDevice);
	}
}

//////////////////////////////////////////////////////////////////////////
// init VoIP Device list
void CXMSVoIPGatewayDlg::initIPList()
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
//		str.Format(_T("%d/%02d"), g_deviceVoIP[i].device.m_s8ModuleID, g_deviceVoIP[i].device.m_s16ChannelID);
		str.Format(_T("%02d"), g_deviceVoIP[i].device.m_s16ChannelID);
		m_lstIP.SetItemText(i, 1, str);
		for (int j = 2; j < 12; ++j)
			m_lstIP.SetItemText(i, j, _T("N/A"));
	}

	// highlight the first device item
	m_lstIP.SetItemState(0, LVIS_FOCUSED|LVIS_SELECTED, -1);
}

//////////////////////////////////////////////////////////////////////////
// init Interface Device list
void CXMSVoIPGatewayDlg::initTrunkList()
{
	m_lstTrunk.DeleteAllItems();

	if (g_iTrunkDevNum <= 0)
	{
		MessageBox(_T("No Interface Devices found!"), _T("Error"), MB_OK|MB_ICONERROR);
		return;
	}

	// fill list
	for (int i = 0; i < g_iTrunkDevNum; ++i)
	{
		CString str;

		m_lstTrunk.InsertItem(i, _T(""));

//		str.Format(_T("%d/%03d"), g_deviceTrunk[i].device.m_s8ModuleID, g_deviceTrunk[i].device.m_s16ChannelID);
		str.Format(_T("%03d"), g_deviceTrunk[i].device.m_s16ChannelID);
		m_lstTrunk.SetItemText(i, 1, str);
		for (int j = 2; j < 9; ++j)
			m_lstTrunk.SetItemText(i, j, _T("N/A"));

		m_lstTrunk.SetItemText(i, 9, g_deviceTrunk[i].szTelNo);
	}

	// highlight the first device item
	m_lstTrunk.SetItemState(0, LVIS_FOCUSED|LVIS_SELECTED, -1);
}

void CXMSVoIPGatewayDlg::OnButtonInit() 
{
	int iDevice;

	UpdateData();

	if (g_acsHandle == NULL)
	{
		// init XMS service
		GetDlgItem(IDC_BUTTON_INIT)->EnableWindow(FALSE);

		ServerID_t serverID;
		strcpy(serverID.m_s8ServerIp, m_strServerIP);
		serverID.m_u32ServerPort = m_uiServerPort;
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
		ret = XMS_acsSetESR(g_acsHandle, (EsrFunc)XMSEventHandler, NULL, TRUE);

		// get device list
		ret = XMS_acsGetDeviceList(g_acsHandle, NULL);
	}
	else
	{
		// close XMS service
		RetCode_t ret;

		for ( iDevice = 0; iDevice < g_iVoIPDevNum; ++iDevice)
		{
			// opened already?
			if (!g_deviceVoIP[iDevice].bOpened)
				continue;

			// send close device command
			ret = XMS_ctsCloseDevice(g_acsHandle, &g_deviceVoIP[iDevice].device, NULL);

			memset(&g_deviceVoIP[iDevice].device, -1, sizeof(DeviceID_t));
		}

		for (iDevice = 0; iDevice < g_iTrunkDevNum; ++iDevice)
		{
			// opened already?
			if (!g_deviceTrunk[iDevice].bOpened)
				continue;

			// send close device command
			ret = XMS_ctsCloseDevice(g_acsHandle, &g_deviceTrunk[iDevice].device, NULL);

			memset(&g_deviceTrunk[iDevice].device, -1, sizeof(DeviceID_t));
		}

		ret = XMS_acsCloseStream(g_acsHandle, NULL);

		g_acsHandle = NULL;

		GetDlgItem(IDC_BUTTON_INIT)->SetWindowText(_T("Init System"));
	}
}

//////////////////////////////////////////////////////////////////////////
void CXMSVoIPGatewayDlg::enableDevice(const DeviceID_t *pDeviceID, BOOL bEnable)
{
	int iDevice;

	switch (pDeviceID->m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
//		iDevice = mapDeviceItem(pDeviceID);
		iDevice = pDeviceID->m_s16ChannelID;

		if (bEnable)
			g_deviceVoIP[iDevice].device = *pDeviceID;
		else
			resetDeviceVoIP(iDevice);

		g_deviceVoIP[iDevice].bOpened = bEnable;

		refreshListIP(iDevice);
//		refreshCtrlIP();
		break;

	case XMS_DEVMAIN_VOICE:
//		iDevice = mapDeviceItem(pDeviceID);
		iDevice = pDeviceID->m_s16ChannelID;

		if (bEnable)
			g_deviceVoc[iDevice].device = *pDeviceID;
		else
			resetDeviceVoc(iDevice);

		g_deviceVoc[iDevice].bOpened = bEnable;

//		refreshListVoc(iDevice);
//		refreshCtrlVoc();
		break;

	case XMS_DEVMAIN_INTERFACE_CH:
//		iDevice = mapDeviceItem(pDeviceID);
		iDevice = pDeviceID->m_s16ChannelID;

		if (bEnable)
			g_deviceTrunk[iDevice].device = *pDeviceID;
		else
			resetDeviceTrunk(iDevice);

		g_deviceTrunk[iDevice].bOpened = bEnable;

		refreshListTrunk(iDevice);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// refresh item in IP Device list
void CXMSVoIPGatewayDlg::refreshListIP(int iDevice)
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

	// call state
	if (g_deviceVoIP[iDevice].iState < DEVICE_ESPECIAL_STATE_START)
		m_lstIP.SetItemText(iDevice, 3, g_pszDevStateName[g_deviceVoIP[iDevice].iState]);

	if (g_deviceVoIP[iDevice].iState == DCS_CALLIN)
	{
		// highlight the incoming call item
		// deselect all other call items
		POSITION pos = m_lstIP.GetFirstSelectedItemPosition();
		while (pos != NULL)
		{
			int iItem = m_lstIP.GetNextSelectedItem(pos);
			m_lstIP.SetItemState(iItem, 0, -1);
		}

		m_lstIP.SetItemState(iDevice, LVIS_FOCUSED|LVIS_SELECTED, -1);

		m_lstIP.EnsureVisible(iDevice, FALSE);
	}

	CString strBuf;

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
//	m_lstIP.SetItemText(iDevice, 10, g_deviceVoIP[iDevice].szDtmf);
	m_lstIP.SetItemText(iDevice, 10, g_deviceVoIP[iDevice].addrRegClient.tszTelNo);

	// Interface Device binded
	int iDeviceTrk = g_deviceVoIP[iDevice].iTrunkDevice;
	if (iDeviceTrk != -1)
	{
//		strBuf.Format(_T("%d/%03d"), g_deviceTrunk[iDeviceTrk].device.m_s8ModuleID, g_deviceTrunk[iDeviceTrk].device.m_s16ChannelID);
		strBuf.Format(_T("%03d"), g_deviceTrunk[iDeviceTrk].device.m_s16ChannelID);
		m_lstIP.SetItemText(iDevice, 11, strBuf);
	}
	else
		m_lstIP.SetItemText(iDevice, 11, _T("N/A"));

	m_lstIP.EnsureVisible(iDevice, FALSE);
}

void CXMSVoIPGatewayDlg::refreshListTrunk(int iDevice)
{
	m_lstTrunk.SetItemText(iDevice, 9, g_deviceTrunk[iDevice].szTelNo);

	if (!g_deviceTrunk[iDevice].bOpened)
	{
		for (int i = 2; i < 9; ++i)
			m_lstTrunk.SetItemText(iDevice, i, _T("N/A"));
		return;
	}

	CString strBuf(_T("N/A"));

	// device sub-type
	m_lstTrunk.SetItemText(iDevice, 2, g_pszDevSubName[g_deviceTrunk[iDevice].device.m_s16DeviceSub]);

	// device state
	m_lstTrunk.SetItemText(iDevice, 3, g_pszDevStateName[g_deviceTrunk[iDevice].iState]);

	// caller num
	m_lstTrunk.SetItemText(iDevice, 4, g_deviceTrunk[iDevice].szCallerNum);

	// callee num
	m_lstTrunk.SetItemText(iDevice, 5, g_deviceTrunk[iDevice].szCalleeNum);

	// DTMF
	m_lstTrunk.SetItemText(iDevice, 6, g_deviceTrunk[iDevice].szDtmf);

	// Voice Device linked with
	int iDeviceVoc = g_deviceTrunk[iDevice].iVocDevice;
	if (iDeviceVoc != -1)
	{
//		strBuf.Format(_T("%d/%03d"), g_deviceVoc[iDeviceVoc].device.m_s8ModuleID, g_deviceVoc[iDeviceVoc].device.m_s16ChannelID);
		strBuf.Format(_T("%03d"), g_deviceVoc[iDeviceVoc].device.m_s16ChannelID);
		m_lstTrunk.SetItemText(iDevice, 7, strBuf);
	}
	else
		m_lstTrunk.SetItemText(iDevice, 7, _T("N/A"));

	// VoIP Device linked with
	int iDeviceIP = g_deviceTrunk[iDevice].iVoIPDevice;
	if (iDeviceIP != -1)
	{
//		strBuf.Format(_T("%d/%02d"), g_deviceVoIP[iDeviceIP].device.m_s8ModuleID, g_deviceVoIP[iDeviceIP].device.m_s16ChannelID);
		strBuf.Format(_T("%02d"), g_deviceVoIP[iDeviceIP].device.m_s16ChannelID);
		m_lstTrunk.SetItemText(iDevice, 8, strBuf);
	}
	else
		m_lstTrunk.SetItemText(iDevice, 8, _T("N/A"));

	m_lstTrunk.EnsureVisible(iDevice, FALSE);
}

BOOL CXMSVoIPGatewayDlg::DestroyWindow() 
{
	int iDevice;

	// close XMS service
	for (iDevice = 0; iDevice < g_iVoIPDevNum; ++iDevice)
	{
		// opened already?
		if (!g_deviceVoIP[iDevice].bOpened)
			continue;

		// send close device command
		XMS_ctsCloseDevice(g_acsHandle, &g_deviceVoIP[iDevice].device, NULL);
	}

	for (iDevice = 0; iDevice < g_iTrunkDevNum; ++iDevice)
	{
		// opened already?
		if (!g_deviceTrunk[iDevice].bOpened)
			continue;

		// send close device command
		XMS_ctsCloseDevice(g_acsHandle, &g_deviceTrunk[iDevice].device, NULL);

		memset(&g_deviceTrunk[iDevice].device, -1, sizeof(DeviceID_t));
	}

	// wait for close device command to complete
	Sleep(50);

	saveConfig();

	return CDialog::DestroyWindow();
}

void CXMSVoIPGatewayDlg::OnBeginlabeleditListTrunk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO *pDispInfo = (LV_DISPINFO *)pNMHDR;

	CEdit *pEdit = m_lstTrunk.GetEditControl();
	pEdit->SetWindowText(g_deviceTrunk[pDispInfo->item.iItem].szTelNo);

	*pResult = 0;
}

void CXMSVoIPGatewayDlg::OnEndlabeleditListTrunk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO *pDispInfo = (LV_DISPINFO *)pNMHDR;

	if (pDispInfo->item.pszText != NULL)
	{
		strcpy(g_deviceTrunk[pDispInfo->item.iItem].szTelNo, pDispInfo->item.pszText);
	}

	refreshListTrunk(pDispInfo->item.iItem);

	*pResult = 0;
}

void CXMSVoIPGatewayDlg::OnDblclkListTrunk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMITEMACTIVATE *pItem = (NMITEMACTIVATE *)pNMHDR;
	if (pItem->iItem >= 0)
	{
		m_lstTrunk.EditLabel(pItem->iItem);
	}

	*pResult = 0;
}

BOOL CXMSVoIPGatewayDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	CEdit *pEdit = m_lstTrunk.GetEditControl();
	if (pEdit != NULL && pEdit->GetSafeHwnd() == (HWND)lParam)
	{
		CRect rcSubItem;
		m_lstTrunk.GetSubItemRect(0, 9, LVIR_BOUNDS, rcSubItem);

		CRect rcEdit;
		pEdit->GetWindowRect(rcEdit);
		m_lstTrunk.ScreenToClient(rcEdit);
		rcEdit.left = rcSubItem.left;
		rcEdit.right = rcSubItem.right-1;

		pEdit->MoveWindow(rcEdit);
	}

	return CDialog::OnCommand(wParam, lParam);
}
