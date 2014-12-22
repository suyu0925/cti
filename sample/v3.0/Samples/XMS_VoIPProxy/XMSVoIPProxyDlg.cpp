// XMSVoIPProxyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSVoIPProxy.h"
#include "XMSVoIPProxyDlg.h"

#include "winsock2.h"
//#pragma comment(lib,"stun.lib")
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
extern std::list<tagRouteItem*> g_lsRoute;

/////////////////////////////////////////////////////////////////////////////
// CXMSVoIPProxyDlg dialog

CXMSVoIPProxyDlg::CXMSVoIPProxyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXMSVoIPProxyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXMSVoIPProxyDlg)
	m_uiServerPort = 9001;
	m_strServerIP = _T("");
	m_strUsername = _T("");
	m_strPassword = _T("");
	m_iDSP = 0;
	m_bInteractive = FALSE;
	m_strRouteIP = _T("");
	m_uRoutePort = 0;
	m_strRouteUserName = _T("");
	m_strRoutePassword = _T("");
	m_strRouteCalleeHead = _T("");
	m_bAutoRtp = FALSE;
	m_bUseDspRtp = FALSE;
	m_strDspIp = _T("");
	m_bDspBehindNat = FALSE;
	m_strRegisterTelNO = _T("");
	m_strRegServerIP = _T("");
	m_strRegPassword = _T("");
	m_uRegPort = 0;
	m_strRegUserName = _T("");
	m_UserID = _T("");
	m_strOptionIP = _T("");
	m_strOptionID = _T("");
	m_strOptionPort = 0;
	m_strOptionTelNO = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	GetModuleFileName(NULL, m_strIniFile.GetBuffer(_MAX_PATH), _MAX_PATH);
	m_strIniFile.ReleaseBuffer();
	m_strIniFile.Replace(_T(".exe"), _T(".ini"));

	loadConfig();
}

void CXMSVoIPProxyDlg::loadConfig()
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
	m_bInteractive = GetPrivateProfileInt(_T("Proxy"), _T("Interactive"), FALSE, m_strIniFile);
	m_bAutoRtp = GetPrivateProfileInt(_T("Server"), _T("AutoRTP"), TRUE, m_strIniFile);
	m_bUseDspRtp = GetPrivateProfileInt(_T("Server"), _T("UseDspRtp"), FALSE, m_strIniFile);
	m_bDspBehindNat = GetPrivateProfileInt(_T("Server"), _T("DspNat"), FALSE, m_strIniFile);
	GetPrivateProfileString(_T("Server"), _T("DspIP"), _T(""), m_strDspIp.GetBuffer(100), 100, m_strIniFile);
	m_strDspIp.ReleaseBuffer();

	GetPrivateProfileString(_T("Route"), _T("calleehead"), _T(""), m_strRouteCalleeHead.GetBuffer(100), 100, m_strIniFile);
	m_strRouteCalleeHead.ReleaseBuffer();
	GetPrivateProfileString(_T("Route"), _T("ip"), _T(""), m_strRouteIP.GetBuffer(100), 100, m_strIniFile);
	m_strRouteIP.ReleaseBuffer();
	m_uRoutePort = GetPrivateProfileInt(_T("Route"), _T("port"), 5060, m_strIniFile);
	GetPrivateProfileString(_T("Route"), _T("username"), _T(""), m_strRouteUserName.GetBuffer(100), 100, m_strIniFile);
	m_strRouteUserName.ReleaseBuffer();
	GetPrivateProfileString(_T("Route"), _T("password"), _T(""), m_strRoutePassword.GetBuffer(100), 100, m_strIniFile);
	m_strRoutePassword.ReleaseBuffer();

	int ircount = GetPrivateProfileInt(_T("Route"), _T("count"), 0, m_strIniFile);
	for(int i=0; i<ircount; ++i)
	{
		char buf[100] = "";
		CString str;
		str.Format("Route%d", i);
		struct tagRouteItem* route = new tagRouteItem;
		GetPrivateProfileString(str, _T("calleehead"), _T(""), buf, 100, m_strIniFile);
		route->strCalleeHead = buf;
		GetPrivateProfileString(str, _T("ip"), _T(""), buf, 100, m_strIniFile);
		route->strAddr=buf;
		route->uPort = GetPrivateProfileInt(str, _T("port"), 5060, m_strIniFile);
		GetPrivateProfileString(str, _T("username"), _T(""), buf, 100, m_strIniFile);
		route->strUserName = buf;
		GetPrivateProfileString(str, _T("password"), _T(""), buf, 100, m_strIniFile);
		route->strPassword = buf;
		g_lsRoute.push_back(route);
	}
}

void CXMSVoIPProxyDlg::saveConfig()
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

	strbuf.Format(_T("%d"), m_bInteractive);
	WritePrivateProfileString(_T("Proxy"), _T("Interactive"), strbuf, m_strIniFile);
	WritePrivateProfileString(_T("Server"), _T("AutoRTP"), m_bAutoRtp?"1":"0", m_strIniFile);
	WritePrivateProfileString(_T("Server"), _T("UseDspRtp"), m_bUseDspRtp?"1":"0", m_strIniFile);
	WritePrivateProfileString(_T("Server"), _T("DspIP"), m_strDspIp, m_strIniFile);
	WritePrivateProfileString(_T("Server"), _T("DspNat"), m_bDspBehindNat?"1":"0", m_strIniFile);

	WritePrivateProfileString(_T("Route"), _T("calleehead"), m_strRouteCalleeHead, m_strIniFile);
	WritePrivateProfileString(_T("Route"), _T("ip"), m_strRouteIP, m_strIniFile);
	strbuf.Format(_T("%d"), m_uRoutePort);
	WritePrivateProfileString(_T("Route"), _T("port"), strbuf, m_strIniFile);
	WritePrivateProfileString(_T("Route"), _T("username"), m_strRouteUserName, m_strIniFile);
	WritePrivateProfileString(_T("Route"), _T("password"), m_strRoutePassword, m_strIniFile);
	
	GetPrivateProfileInt(_T("Route"), _T("count"), 0, m_strIniFile);
	std::list<tagRouteItem*>::iterator iter = g_lsRoute.begin();
	for(int i=0; iter!=g_lsRoute.end(); ++i, ++iter)
	{
		char buf[100] = "";
		CString str;
		str.Format("Route%d", i);
		struct tagRouteItem* route = *iter;
		WritePrivateProfileString(str, _T("calleehead"), route->strCalleeHead, m_strIniFile);
		WritePrivateProfileString(str, _T("ip"), route->strAddr, m_strIniFile);
		strbuf.Format(_T("%d"), route->uPort);
		WritePrivateProfileString(str, _T("port"), strbuf, m_strIniFile);
		WritePrivateProfileString(str, _T("username"), route->strUserName, m_strIniFile);
		WritePrivateProfileString(str, _T("password"), route->strPassword, m_strIniFile);
	}
	strbuf.Format(_T("%d"), i);
	WritePrivateProfileString(_T("Route"), _T("count"), strbuf, m_strIniFile);
}

void CXMSVoIPProxyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXMSVoIPProxyDlg)
	DDX_Control(pDX, IDC_CHECK_USE_DSP_RTP, m_btnUseDspRtp);
	DDX_Control(pDX, IDC_LIST_ROUTE, m_lstRoute);
	DDX_Control(pDX, IDC_LIST_REG, m_lstReg);
	DDX_Control(pDX, IDC_LIST_IP, m_lstIP);
	DDX_Text(pDX, IDC_EDIT_SERVER_PORT, m_uiServerPort);
	DDX_Text(pDX, IDC_EDIT_SERVER_IP, m_strServerIP);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUsername);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
	DDX_Text(pDX, IDC_EDIT_DSPID, m_iDSP);
	DDX_Check(pDX, IDC_CHECK_INTERACTIVE, m_bInteractive);
	DDX_Text(pDX, IDC_EDIT_ROUTE_IP, m_strRouteIP);
	DDX_Text(pDX, IDC_EDIT_ROUTE_PORT, m_uRoutePort);
	DDX_Text(pDX, IDC_EDIT_ROUTE_USERNAME, m_strRouteUserName);
	DDX_Text(pDX, IDC_EDIT_ROUTE_PASSWORD, m_strRoutePassword);
	DDX_Text(pDX, IDC_EDIT_ROUTE_CALLEE_HEAD, m_strRouteCalleeHead);
	DDX_Check(pDX, IDC_CHECK_AUTO_RTP, m_bAutoRtp);
	DDX_Check(pDX, IDC_CHECK_USE_DSP_RTP, m_bUseDspRtp);
	DDX_Text(pDX, IDC_EDIT_DSP_IP, m_strDspIp);
	DDX_Check(pDX, IDC_CHECK_DSP_NAT, m_bDspBehindNat);
	DDX_Text(pDX, IDC_EDIT_ROUTE_CALLEE_HEAD2, m_strRegisterTelNO);
	DDX_Text(pDX, IDC_EDIT_ROUTE_IP2, m_strRegServerIP);
	DDX_Text(pDX, IDC_EDIT_ROUTE_PASSWORD2, m_strRegPassword);
	DDX_Text(pDX, IDC_EDIT_ROUTE_PORT2, m_uRegPort);
	DDX_Text(pDX, IDC_EDIT_ROUTE_USERNAME2, m_strRegUserName);
	DDX_Text(pDX, IDC_EDIT_ROUTE_PASSWORD3, m_UserID);
	DDX_Text(pDX, IDC_EDIT_ROUTE_IP3, m_strOptionIP);
	DDX_Text(pDX, IDC_EDIT_ROUTE_PASSWORD5, m_strOptionID);
	DDX_Text(pDX, IDC_EDIT_ROUTE_PORT3, m_strOptionPort);
	DDX_Text(pDX, IDC_EDIT_ROUTE_CALLEE_HEAD3, m_strOptionTelNO);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXMSVoIPProxyDlg, CDialog)
	//{{AFX_MSG_MAP(CXMSVoIPProxyDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonInit)
	ON_BN_CLICKED(ID_ADD, OnAdd)
	ON_BN_CLICKED(ID_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_CHECK_AUTO_RTP, OnCheckAutoRtp)
	ON_BN_CLICKED(IDC_CHECK_USE_DSP_RTP, OnCheckUseDspRtp)
	ON_BN_CLICKED(IDC_CHECK_DSP_NAT, OnCheckDspNat)
	ON_EN_KILLFOCUS(IDC_EDIT_DSP_IP, OnKillfocusEditDspIp)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMSVoIPProxyDlg message handlers

HFONT g_hFont = NULL;

BOOL CALLBACK replaceFont(HWND hwndChild, LPARAM lParam)
{
	TCHAR tszClassName[256] = {0};
	if (GetClassName(hwndChild, tszClassName, sizeof(tszClassName)) > 0 &&
		(_tcscmp(tszClassName, _T("Button")) == 0 ||
		(_tcscmp(tszClassName, _T("Static")) == 0 && GetDlgCtrlID(hwndChild) == IDC_STATIC_DIALPLAN)))
	{
		LONG lStyle = GetWindowLong(hwndChild, GWL_STYLE);
		if ((lStyle & BS_GROUPBOX) != BS_GROUPBOX)
			SendMessage(hwndChild, WM_SETFONT, (WPARAM)g_hFont, 0);
	}

	return TRUE;
}

BOOL CXMSVoIPProxyDlg::OnInitDialog()
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

void CXMSVoIPProxyDlg::OnPaint() 
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
HCURSOR CXMSVoIPProxyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//////////////////////////////////////////////////////////////////////////
// init list control
void CXMSVoIPProxyDlg::initUI()
{
	// IP Device list
	m_lstIP.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_lstIP.InsertColumn(0, _T("Header"), LVCFMT_LEFT, 0);
	m_lstIP.InsertColumn(1, _T("#"), LVCFMT_CENTER, 30);
	m_lstIP.InsertColumn(2, _T("State"), LVCFMT_CENTER, 60);
	m_lstIP.InsertColumn(3, _T("Protocol"), LVCFMT_CENTER, 60);
	m_lstIP.InsertColumn(4, _T("Peer TelNo"), LVCFMT_CENTER, 80);
	m_lstIP.InsertColumn(5, _T("Peer Device"), LVCFMT_CENTER, 70);

	m_lstReg.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_lstReg.InsertColumn(0, _T("Header"), LVCFMT_LEFT, 0);
	m_lstReg.InsertColumn(1, _T("#"), LVCFMT_CENTER, 30);
	m_lstReg.InsertColumn(2, _T("Protocol"), LVCFMT_CENTER, 60);
	m_lstReg.InsertColumn(3, _T("TelNo"), LVCFMT_CENTER, 80);
	m_lstReg.InsertColumn(4, _T("Address"), LVCFMT_CENTER, 120);
	m_lstReg.InsertColumn(5, _T("UserID"), LVCFMT_CENTER, 80);

	m_lstRoute.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_lstRoute.InsertColumn(0, _T("#"), LVCFMT_CENTER, 30);
	m_lstRoute.InsertColumn(1, _T("callee"), LVCFMT_CENTER, 100);
	m_lstRoute.InsertColumn(2, _T("Addr"), LVCFMT_CENTER, 140);
	m_lstRoute.InsertColumn(3, _T("UserName"), LVCFMT_CENTER, 80);
	m_lstRoute.InsertColumn(4, _T("Password"), LVCFMT_CENTER, 80);
	int i=0;
	for(std::list<tagRouteItem*>::iterator iter=g_lsRoute.begin(); iter!=g_lsRoute.end(); ++iter, ++i)
	{
		struct tagRouteItem* route = *iter;
		CString str;
		str.Format("%d", i+1);
		i = m_lstRoute.InsertItem(i, "");
		m_lstRoute.SetItemText(i, 0, str);
		m_lstRoute.SetItemText(i, 1, route->strCalleeHead);
		str.Format("%s:%d", route->strAddr, route->uPort);
		m_lstRoute.SetItemText(i, 2, str);
		m_lstRoute.SetItemText(i, 3, route->strUserName);
		m_lstRoute.SetItemText(i, 4, route->strPassword);
		m_lstRoute.SetItemData(i, (unsigned long)route);
	}

	if(m_bAutoRtp)
	{
		m_btnUseDspRtp.EnableWindow(FALSE);
	}
}

//////////////////////////////////////////////////////////////////////////
// init XMS Device structs
void initXMS()
{
	for (int iDevice = 0; iDevice < MAX_DEVICE_BOARD; ++iDevice)
	{
		memset(&g_deviceBoard[iDevice], -1, sizeof(DeviceID_t));
	}

	for (iDevice = 0; iDevice < MAX_DEVICE_VOIP; ++iDevice)
	{
		g_deviceVoIP[iDevice].bOpened = FALSE;
		memset(&g_deviceVoIP[iDevice].device, -1, sizeof(DeviceID_t));
		resetDeviceVoIP(iDevice);
	}

	for (iDevice = 0; iDevice < MAX_DEVICE_VOIP; ++iDevice)
	{
		g_deviceRTP[iDevice].bOpened = FALSE;
		memset(&g_deviceRTP[iDevice].device, -1, sizeof(DeviceID_t));
		resetDeviceRTP(iDevice);
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
void CXMSVoIPProxyDlg::initIPList()
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
		str.Format(_T("%02d"), g_deviceVoIP[i].device.m_s16ChannelID);
		m_lstIP.SetItemText(i, 1, str);
		for (int j = 2; j < 9; ++j)
			m_lstIP.SetItemText(i, j, _T("N/A"));
	}

	// high-light the first device item
	m_lstIP.SetItemState(0, LVIS_FOCUSED|LVIS_SELECTED, -1);

	for (int iReg = 0; iReg < MAX_VOIP_REG; ++iReg)
	{
		CString strBuf;
		m_lstReg.InsertItem(iReg, NULL);
		strBuf.Format(_T("%02d"), iReg);
		m_lstReg.SetItemText(iReg, 1, strBuf);
	}
}

void CXMSVoIPProxyDlg::OnButtonInit()
{
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
		ret = XMS_acsSetESR(g_acsHandle, XMSEventHandler, NULL, TRUE);

		// get device list
		ret = XMS_acsGetDeviceList(g_acsHandle, NULL);
	}
	else
	{
		// close XMS service
		RetCode_t ret;

		for (int iDevice = 0; iDevice < g_iVoIPDevNum; ++iDevice)
		{
			// opened already?
			if (!g_deviceVoIP[iDevice].bOpened)
				continue;

			// send close device command
			ret = XMS_ctsCloseDevice(g_acsHandle, &g_deviceVoIP[iDevice].device, NULL);

			memset(&g_deviceVoIP[iDevice].device, -1, sizeof(DeviceID_t));
		}

		Sleep(50);

		ret = XMS_acsCloseStream(g_acsHandle, NULL);

		g_acsHandle = NULL;

		GetDlgItem(IDC_BUTTON_INIT)->SetWindowText(_T("Init XMS System"));
	}
}

//////////////////////////////////////////////////////////////////////////
void CXMSVoIPProxyDlg::enableDevice(const DeviceID_t *pDeviceID, BOOL bEnable)
{
	int iDevice;

	switch (pDeviceID->m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
		iDevice = mapDeviceItem(pDeviceID);

		if (bEnable)
			g_deviceVoIP[iDevice].device = *pDeviceID;
		else
			resetDeviceVoIP(iDevice);

		g_deviceVoIP[iDevice].bOpened = bEnable;

		refreshListIP(iDevice);
//		refreshCtrlIP();
		break;

	case XMS_DEVMAIN_RTP:
		iDevice = mapDeviceItem(pDeviceID);
		
		if (bEnable)
			g_deviceRTP[iDevice].device = *pDeviceID;
		else
			resetDeviceRTP(iDevice);
		
		g_deviceRTP[iDevice].bOpened = bEnable;
		
		//refreshListIP(iDevice);
		//		refreshCtrlIP();
		break;

	case XMS_DEVMAIN_VOICE:
		iDevice = mapDeviceItem(pDeviceID);

		if (bEnable)
			g_deviceVoc[iDevice].device = *pDeviceID;
		else
			resetDeviceVoc(iDevice);

		g_deviceVoc[iDevice].bOpened = bEnable;

//		refreshListVoc(iDevice);
//		refreshCtrlVoc();
		break;

	case XMS_DEVMAIN_INTERFACE_CH:
		iDevice = mapDeviceItem(pDeviceID);

		if (bEnable)
			g_deviceTrunk[iDevice].device = *pDeviceID;
		else
			resetDeviceTrunk(iDevice);

		g_deviceTrunk[iDevice].bOpened = bEnable;

		break;
	}
		Acs_VoIP_REGSTATE regstate={0};
	XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[0].device, XMS_IO_TYPE_VOIP_REGSTATE,
				sizeof(regstate), &regstate);
}

//////////////////////////////////////////////////////////////////////////
// refresh item in IP Device list
void CXMSVoIPProxyDlg::refreshListIP(int iDevice)
{
	if (!g_deviceVoIP[iDevice].bOpened)
	{
		for (int i = 2; i < 9; ++i)
			m_lstIP.SetItemText(iDevice, i, _T("N/A"));
		return;
	}

	// call state
	if (g_deviceVoIP[iDevice].iState < DEVICE_ESPECIAL_STATE_START)
		m_lstIP.SetItemText(iDevice, 2, g_pszDevStateName[g_deviceVoIP[iDevice].iState]);

	if (g_deviceVoIP[iDevice].iState == DCS_CALLIN)
	{
		// high-light the incoming call item
		// de-select all other call items
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

	// registered client info
	switch (g_deviceVoIP[iDevice].iProtocol)
	{
	case XMS_VOIP_PROTOCOL_H323:
		m_lstIP.SetItemText(iDevice, 3, "H.323");
		break;
	case XMS_VOIP_PROTOCOL_SIP:
		m_lstIP.SetItemText(iDevice, 3, "SIP");
		break;
	default:
		m_lstIP.SetItemText(iDevice, 3, "N/A");
		break;
	}

	// peer telephone number
	m_lstIP.SetItemText(iDevice, 4, g_deviceVoIP[iDevice].tszPeerTelNo);

	// peer device
	if (g_deviceVoIP[iDevice].iPeerDevice >= 0)
		strBuf.Format(_T("%02d"), g_deviceVoIP[iDevice].iPeerDevice);
	else
		strBuf.Empty();
	m_lstIP.SetItemText(iDevice, 5, strBuf);

	m_lstIP.EnsureVisible(iDevice, FALSE);
}

void CXMSVoIPProxyDlg::refreshListReg(int iRegID)
{
	switch (g_ipRegSlot[iRegID].iProtocol)
	{
	case XMS_VOIP_PROTOCOL_H323:
		m_lstReg.SetItemText(iRegID, 2, "H.323");
		break;
	case XMS_VOIP_PROTOCOL_SIP:
		m_lstReg.SetItemText(iRegID, 2, "SIP");
		break;
	default:
		m_lstReg.SetItemText(iRegID, 2, "");
		break;
	}

	m_lstReg.SetItemText(iRegID, 3, g_ipRegSlot[iRegID].addrRegClient.tszTelNo);

	CString strBuf;

	if (g_ipRegSlot[iRegID].addrRegClient.port > 0)
		strBuf.Format(_T("%s:%d"), g_ipRegSlot[iRegID].addrRegClient.tszAddr, g_ipRegSlot[iRegID].addrRegClient.port);
	else
		strBuf = g_ipRegSlot[iRegID].addrRegClient.tszAddr;

	m_lstReg.SetItemText(iRegID, 4, strBuf);

	m_lstReg.SetItemText(iRegID, 5, g_ipRegSlot[iRegID].addrRegClient.tszUserID);
}

BOOL CXMSVoIPProxyDlg::DestroyWindow() 
{
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

	for(std::list<tagRouteItem*>::iterator iter=g_lsRoute.begin(); iter!=g_lsRoute.end(); ++iter)
	{
		struct tagRouteItem* temproute = *iter;
		delete temproute;
	}
	g_lsRoute.clear();

	return CDialog::DestroyWindow();
}

void CXMSVoIPProxyDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	struct tagRouteItem* route = new tagRouteItem;
	route->strAddr = m_strRouteIP;
	route->uPort = m_uRoutePort;
	route->strUserName = m_strRouteUserName;
	route->strPassword = m_strRoutePassword;
	route->strCalleeHead = m_strRouteCalleeHead;
	int icount = m_lstRoute.GetItemCount();
	std::list<tagRouteItem*>::iterator iter = g_lsRoute.begin();
	for(int i=0; i<icount; ++i, ++iter)
	{
		char buf[100] = "";
		CString str;
		struct tagRouteItem* temproute = (struct tagRouteItem*)m_lstRoute.GetItemData(i);
		if(route->strCalleeHead.Compare(temproute->strCalleeHead)!=0)
			continue;
		break;
	}
	if(i<icount)
	{
		struct tagRouteItem* temproute = (struct tagRouteItem*)m_lstRoute.GetItemData(i);
		for(std::list<tagRouteItem*>::iterator iter=g_lsRoute.begin(); iter!=g_lsRoute.end(); )
		{
			if(*iter!=temproute)
			{
				++iter;
				continue;
			}
			iter = g_lsRoute.erase(iter);
		}
		delete temproute;
	}
	else
	{
		i = m_lstRoute.InsertItem(i, "");
	}

	CString str;
	str.Format("%d", i+1);
	m_lstRoute.SetItemText(i, 0, str);
	m_lstRoute.SetItemText(i, 1, route->strCalleeHead);
	str.Format("%s:%d", route->strAddr, route->uPort);
	m_lstRoute.SetItemText(i, 2, str);
	m_lstRoute.SetItemText(i, 3, route->strUserName);
	m_lstRoute.SetItemText(i, 4, route->strPassword);
	m_lstRoute.SetItemData(i, (unsigned long)route);
	g_lsRoute.push_back(route);
}

void CXMSVoIPProxyDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_lstRoute.GetFirstSelectedItemPosition();
	for(;;)
	{
		int i = m_lstRoute.GetNextSelectedItem(pos);
		if(i<0)
			break;
		struct tagRouteItem* temproute = (struct tagRouteItem*)m_lstRoute.GetItemData(i);
		for(std::list<tagRouteItem*>::iterator iter=g_lsRoute.begin(); iter!=g_lsRoute.end(); ++iter)
		{
			if(*iter!=temproute)
				continue;
			g_lsRoute.erase(iter);
			break;
		}
		delete temproute;
		m_lstRoute.DeleteItem(i);
	}

	int icount = m_lstRoute.GetItemCount();
	for(int i=0; i<icount; ++i)
	{
		CString str;
		str.Format("%d", i+1);
		m_lstRoute.SetItemText(i, 0, str);
	}
}

void CXMSVoIPProxyDlg::OnDeleteAll()
{
	// TODO: Add your control notification handler code here
	int icount = m_lstRoute.GetItemCount();
	for(int i=0; i<icount; ++i)
	{
		struct tagRouteItem* temproute = (struct tagRouteItem*)m_lstRoute.GetItemData(i);
		delete temproute;
	}
	m_lstRoute.DeleteAllItems();
	g_lsRoute.clear();
}

void CXMSVoIPProxyDlg::OnCheckAutoRtp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_btnUseDspRtp.EnableWindow(!m_bAutoRtp);
}

void CXMSVoIPProxyDlg::OnCheckUseDspRtp()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CXMSVoIPProxyDlg::OnCheckDspNat() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CXMSVoIPProxyDlg::OnKillfocusEditDspIp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
}

void CXMSVoIPProxyDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	Acs_VoIP_SIPREGEX regstate={0};
	strcpy(regstate.m_s8TelNo,m_strRegisterTelNO);
	strcpy(regstate.m_s8Username,m_strRegUserName);
	strcpy(regstate.m_s8ProxyAddress,m_strRegServerIP);
	strcpy(regstate.m_s8Password,m_strRegPassword);
	regstate.m_u16ProxyPort=m_uRegPort;
	strcpy(regstate.m_s8UserID,m_UserID);

/*	strcpy(regstate.m_s8TelNo,"55555");
	strcpy(regstate.m_s8Username,"donjin");
	strcpy(regstate.m_s8ProxyAddress,"10.10.10.106");
	regstate.m_u16ProxyPort=5065;*/
	XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[0].device, XMS_IO_TYPE_VOIP_SIPREG,
				sizeof(regstate), &regstate);
}

void CXMSVoIPProxyDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	VoIPCallOptionPrivate_t option={0};
	option.m_s32Protocol=XMS_VOIP_PROTOCOL_SIP;
	option.m_s8BeOption=1;
	option.m_PrivateData.m_u32DataSize= sizeof(VoIPCallOptionPrivate_t);
	option.m_s32CalleePort=m_strOptionPort;
	strcpy(option.m_s8CalleeTelNo,m_strOptionTelNO);
	strcpy(option.m_s8CalleeAddress,m_strOptionIP);
	strcpy(option.m_s8CalleeUserID,m_strOptionID);

	
	XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[2].device, XMS_IO_TYPE_VOIP_OPTION,
				sizeof(option), &option);
	
/*	Acs_VoIP_SIPREG regstate={0};
	strcpy(regstate.m_s8TelNo,"1234");
	strcpy(regstate.m_s8Username,"donjin");

	XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[0].device, XMS_IO_TYPE_VOIP_SIPUNREG,
				sizeof(regstate), &regstate);*/
}

void CXMSVoIPProxyDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
		UpdateData();

	Acs_VoIP_SIPREGEX regstate={0};
	strcpy(regstate.m_s8TelNo,m_strRegisterTelNO);
	strcpy(regstate.m_s8Username,m_strRegUserName);
	strcpy(regstate.m_s8ProxyAddress,m_strRegServerIP);
	strcpy(regstate.m_s8Password,m_strRegPassword);
	regstate.m_u16ProxyPort=m_uRegPort;
	strcpy(regstate.m_s8UserID,m_UserID);
/*	Acs_VoIP_SIPREGEX regstate={0};
	strcpy(regstate.m_s8TelNo,"55555");
	strcpy(regstate.m_s8Username,"donjin");
	strcpy(regstate.m_s8ProxyAddress,"192.168.10.106");
	regstate.m_u16ProxyPort=5060;*/
	XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[0].device, XMS_IO_TYPE_VOIP_SIPUNREG,
				sizeof(regstate), &regstate);
}

void CXMSVoIPProxyDlg::OnButton5() 
{
	// TODO: Add your control notification handler code here
//	Acs_VoIP_RTPADDR paramRtpAddr = {0};
//	Acs_VoIP_WANADDR paramWanAddr = {0};
//	XMS_ctsGetParam(g_acsHandle, &g_deviceVoIP[0].device, VOIP_PARAM_VOIPADDR, sizeof(paramWanAddr), &paramWanAddr);

//	XMS_ctsGetParam(g_acsHandle, &g_deviceVoIP[iDeviceIP].device, VOIP_PARAM_RTPADDR, sizeof(paramRtpAddr), &paramRtpAddr);
//			Acs_VoIP_Call_Diversion_Info divInfo;
//			memset(&divInfo, 0, sizeof(Acs_VoIP_Call_Diversion_Info));
//	XMS_ctsGetParam(g_acsHandle, &g_deviceVoIP[0].device, VOIP_PARAM_CALL_DIVERSION_INFO, sizeof(Acs_VoIP_Call_Diversion_Info), &divInfo);
	UpdateData();
	VoIPCallOptionPrivate_t option={0};
	option.m_s32Protocol=XMS_VOIP_PROTOCOL_SIP;
	option.m_s8BeOption=0;
	option.m_PrivateData.m_u32DataSize= sizeof(VoIPCallOptionPrivate_t);
	option.m_s32CalleePort=m_strOptionPort;
	strcpy(option.m_s8CalleeTelNo,m_strOptionTelNO);
	strcpy(option.m_s8CalleeAddress,m_strOptionIP);
	strcpy(option.m_s8CalleeUserID,m_strOptionID);

	
	XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[2].device, XMS_IO_TYPE_VOIP_OPTION,
				sizeof(option), &option);
}

void CXMSVoIPProxyDlg::OnButton6() 
{
	// TODO: Add your control notification handler code here
	UpdateData();

	VoIPCallOptionPrivate_t option={0};
	option.m_s32Protocol=XMS_VOIP_PROTOCOL_SIP;
	option.m_s8BeOption=1;
	option.m_PrivateData.m_u32DataSize= sizeof(VoIPCallOptionPrivate_t);
	option.m_s32CalleePort=m_strOptionPort;
	strcpy(option.m_s8CalleeTelNo,m_strOptionTelNO);
	strcpy(option.m_s8CalleeAddress,m_strOptionIP);
	strcpy(option.m_s8CalleeUserID,m_strOptionID);

	
	XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[2].device, XMS_IO_TYPE_VOIP_OPTION,
				sizeof(option), &option);

}
