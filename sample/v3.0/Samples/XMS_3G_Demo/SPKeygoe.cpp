#include "stdafx.h"
#include "SP.h"
#include "SPDlg.h"
#include "DlgMixer.h"
#include "DlgParamType.h"
#include "DlgIODataUII.h"
#include "DlgRtpxParam.h"
#include "DlgLinkDev.h"
#include "DlgAddr.h"
#include "DlgSipCallParam.h"
#include "DlgPlay.h"
#include "DlgRecord.h"

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"
#include "DJAcsDevState.h"
#include "DJAcsISUPDef.h"

#include "SPKeygoe.h"

extern CSPApp theApp;

/************************************************************************/
/* Video Conf Operators Parm                                            */
/* strat                                                                */
/************************************************************************/
Acs_3GVConf_LayoutList g_layoutList;
Acs_3GVConf_VisibleList g_visibleList;
/************************************************************************/
/* end                                                                  */
/************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//global variable 

CSPDlg	*g_pDlg;
Global_Keygoe_Var g_KeygoeVar;
Dev_Type_Info g_DevType[MAX_DEV_TYPE];
Dev_Info g_DevInfo[MAX_UNIT][MAX_DEV_TYPE][MAX_DEV];
int g_LastUsedUnit[MAX_DEV_TYPE];
int g_LastUsedChann[MAX_UNIT][MAX_DEV_TYPE];
int g_CurDisplayDevType = 0;
int g_CurConfId = -1;
ConfList g_ConfList = NULL;
char msg[256];

DJ_Void EvtHandler(DJ_U32 esrParam);
void ServConfExit();

void AddMsg (char *str)
{
	if(g_pDlg->m_ListMsg.GetCount() >= 9999)
	{
		g_pDlg->m_ListMsg.ResetContent();
	}

	static	int	iTotal_ListMsg = 0;
	char		TmpStr[256];
	
	sprintf ( TmpStr, "%3d: ", iTotal_ListMsg+1 );
	strcat ( TmpStr, str );
	g_pDlg->m_ListMsg.AddString ( TmpStr );
	
	g_pDlg->m_ListMsg.SetCurSel ( iTotal_ListMsg);
	
	iTotal_ListMsg ++;
}

void InitView()
{
	LV_COLUMN	lvc;
	
	DWORD dwExStyle = LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES | LVS_EX_TWOCLICKACTIVATE | /*LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES |*/
		LVS_EX_HEADERDRAGDROP;// | LVS_EX_TRACKSELECT;
	g_pDlg->m_ListDevType.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(dwExStyle));	
	g_pDlg->m_ListDevInfo.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(dwExStyle));	
	g_pDlg->m_ListHotConf.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(dwExStyle));	
	g_pDlg->m_ListMember.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(dwExStyle));	
	
	lvc.mask =  LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
	lvc.iSubItem = 0;
	lvc.pszText = "ID" ;
	lvc.cx = 60;
	g_pDlg->m_ListDevType.InsertColumn(0, &lvc);

	lvc.iSubItem = 1;
	lvc.pszText = "Name" ;
	lvc.cx = 80;
	g_pDlg->m_ListDevType.InsertColumn(1, &lvc);

	lvc.iSubItem = 2;
	lvc.pszText = "Total/Open" ;
	lvc.cx = 80;
	g_pDlg->m_ListDevType.InsertColumn(2, &lvc);
	
	lvc.iSubItem = 0;
	lvc.pszText = "ID" ;
	lvc.cx = 30;
	g_pDlg->m_ListDevInfo.InsertColumn(0, &lvc);
	
	lvc.iSubItem = 1;
	lvc.pszText = "Mod,ch" ;
	lvc.cx = 60;
	g_pDlg->m_ListDevInfo.InsertColumn(1, &lvc);
	
	lvc.iSubItem = 2;
	lvc.pszText = "SubType" ;
	lvc.cx = 70;
	g_pDlg->m_ListDevInfo.InsertColumn(2, &lvc);
	
	lvc.iSubItem = 3;
	lvc.pszText = "State" ;
	lvc.cx = 70;
	g_pDlg->m_ListDevInfo.InsertColumn(3, &lvc);

	lvc.iSubItem = 0;
	lvc.pszText = "ID" ;
	lvc.cx = 40;
	g_pDlg->m_ListHotConf.InsertColumn(0, &lvc);
	
	lvc.iSubItem = 1;
	lvc.pszText = "Name" ;
	lvc.cx = 100;
	g_pDlg->m_ListHotConf.InsertColumn(1, &lvc);

	lvc.iSubItem = 2;
	lvc.pszText = "Member cout" ;
	lvc.cx = 80;
	g_pDlg->m_ListHotConf.InsertColumn(2, &lvc);
	
	lvc.iSubItem = 0;
	lvc.pszText = "ID" ;
	lvc.cx = 40;
	g_pDlg->m_ListMember.InsertColumn(0, &lvc);
	
	lvc.iSubItem = 1;
	lvc.pszText = "Name" ;
	lvc.cx = 100;
	g_pDlg->m_ListMember.InsertColumn(1, &lvc);
	
	int	i = g_pDlg->m_ListMsg.GetHorizontalExtent ( );
	g_pDlg->m_ListMsg.SetHorizontalExtent ( i + 1000 );
}

char* GetEvtName(int evtType)
{
	switch (evtType)
	{
	case XMS_EVT_OPEN_STREAM                     :return "EVT_OPEN_STREAM";                                                          
	case XMS_EVT_QUERY_DEVICE                    :return "EVT_QUERY_DEVICE";                                                          
	case XMS_EVT_QUERY_DEVICE_END                :return "EVT_QUERY_DEVICE_END";                                                          
	case XMS_EVT_OPEN_DEVICE                     :return "EVT_OPEN_DEVICE";                                                          
	case XMS_EVT_CLOSE_DEVICE                    :return "EVT_CLOSE_DEVICE";                                                          
	case XMS_EVT_RESET_DEVICE                    :return "EVT_RESET_DEVICE";                                                          
	case XMS_EVT_DEVICESTATE                     :return "EVT_DEVICESTATE";                                                          
	case XMS_EVT_SETDEV_GROUP                    :return "EVT_SETDEV_GROUP";                                                          
	case XMS_EVT_SETPARAM                        :return "EVT_SETPARAM";                                                          
	case XMS_EVT_GETPARAM                        :return "EVT_GETPARAM";                                                          
	case XMS_EVT_QUERY_ONE_DSP_START             :return "EVT_QUERY_ONE_DSP_START";                                                          
	case XMS_EVT_QUERY_ONE_DSP_END               :return "EVT_QUERY_ONE_DSP_END";                                                          
	case XMS_EVT_QUERY_REMOVE_ONE_DSP_START      :return "EVT_QUERY_REMOVE_ONE_DSP_START";                                                          
	case XMS_EVT_QUERY_REMOVE_ONE_DSP_END        :return "EVT_QUERY_REMOVE_ONE_DSP_END";                                                          
	case XMS_EVT_OPEN_STREAM_EXT                 :return "EVT_OPEN_STREAM_EXT";                                                          
	case XMS_EVT_LICENSE_QUERY                   :return "EVT_LICENSE_QUERY";                                                          
	case XMS_EVT_ACS_TIMER                       :return "EVT_ACS_TIMER";                                                          
		
	case XMS_EVT_CALLOUT                         :return "EVT_CALLOUT";                                                                      
	case XMS_EVT_CALLIN							 :return "EVT_CALLIN";                                                                      
	case XMS_EVT_ALERTCALL		                 :return "EVT_ALERTCALL";                                                              
	case XMS_EVT_ANSWERCALL		                 :return "EVT_ANSWERCALL";    
	case XMS_EVT_LINKDEVICE				         :return "EVT_LINKDEVICE";                                                                
	case XMS_EVT_UNLINKDEVICE					 :return "EVT_UNLINKDEVICE";                                                                    
	case XMS_EVT_CLEARCALL						 :return "EVT_CLEARCALL";                                                                      
	case XMS_EVT_ANALOG_INTERFACE                :return "EVT_ANALOG_INTERFACE";                                                          
	case XMS_EVT_CAS_MFC_START					 :return "EVT_CAS_MFC_START";                                                                    
	case XMS_EVT_CAS_MFC_END					 :return "EVT_CAS_MFC_END";                                                                    
	case XMS_EVT_SENDSIGMSG						 :return "EVT_SENDSIGMSG";                                                                    
	case XMS_EVT_SIGMON       					 :return "EVT_SIGMON";                                                                    
	case XMS_EVT_3G324M       					 :return "EVT_3G324M";                                                                    
	case XMS_EVT_CTX_REG                         :return "EVT_CTX_REG";                                                          
	case XMS_EVT_CTX_LINK                        :return "EVT_CTX_LINK";                                                          
	case XMS_EVT_CTX_APPDATA                     :return "EVT_CTX_APPDATA";                                                          
		
	case XMS_EVT_JOINTOCONF					     :return "EVT_JOINTOCONF";                                                                  
	case XMS_EVT_LEAVEFROMCONF					 :return "EVT_LEAVEFROMCONF";                                                                    
	case XMS_EVT_CLEARCONF					     :return "EVT_CLEARCONF";                                                                    
		
	case XMS_EVT_PLAY			                 :return "EVT_PLAY";                                                                
	case XMS_EVT_INITINDEX				         :return "EVT_INITINDEX";                                                                  
	case XMS_EVT_BUILDINDEX						 :return "EVT_BUILDINDEX";                                                                    
	case XMS_EVT_CONTROLPLAY				     :return "EVT_CONTROLPLAY";                                                                
	case XMS_EVT_RECORD							 :return "EVT_RECORD";                                                                      
	case XMS_EVT_CONTROLRECORD				     :return "EVT_CONTROLRECORD";                                                                  
	case XMS_EVT_RECORDCSP   				     :return "EVT_RECORDCSP";                                                                  
	case XMS_EVT_CONTROLRECORDCSP    		     :return "EVT_CONTROLRECORDCSP";                                                              
    case XMS_EVT_3GPP_PLAY			             :return "EVT_3GPP_PLAY";                                                              
	case XMS_EVT_3GPP_CONTROLPLAY		         :return "EVT_3GPP_CONTROLPLAY";                                                              
	case XMS_EVT_3GPP_RECORD	    			 :return "EVT_3GPP_RECORD";                                                                  
	case XMS_EVT_3GPP_CONTROLRECORD    		     :return "EVT_3GPP_CONTROLRECORD";                                                            
	case XMS_EVT_PLAYCSPREQ 				     :return "EVT_PLAYCSPREQ";                                                                
	case XMS_EVT_3GPP_INIT_INDEX                 :return "EVT_3GPP_INIT_INDEX";                                                
	case XMS_EVT_3GPP_BUILD_INDEX                :return "EVT_3GPP_BUILD_INDEX";             
		
	case XMS_EVT_3GVCONF_JOIN					 :return "XMS_EVT_3GVCONF_JOIN";
	case XMS_EVT_3GVCONF_LEAVE					 :return "XMS_EVT_3GVCONF_LEAVE";
	case XMS_EVT_3GVCONF_CLEAR					 :return "XMS_EVT_3GVCONF_CLEAR";
	case XMS_EVT_3GVCONF_GETLAYOUT				 :return "XMS_EVT_3GVCONF_GETLAYOUT";
	case XMS_EVT_3GVCONF_SETLAYOUT				 :return "XMS_EVT_3GVCONF_SETLAYOUT";
	case XMS_EVT_3GVCONF_GETVISIBLELIST			 :return "XMS_EVT_3GVCONF_GETVISIBLELIST";
	case XMS_EVT_3GVCONF_SETVISIBLELIST			 :return "XMS_EVT_3GVCONF_SETVISIBLELIST";
	case XMS_EVT_3GVCONF_STOP					 :return "XMS_EVT_3GVCONF_STOP";
		
	case XMS_EVT_SENDFAX			             :return "EVT_SENDFAX";                                                              
	case XMS_EVT_RECVFAX					     :return "EVT_RECVFAX";                                                                  
		
	case XMS_EVT_SENDIODATA                      :return "EVT_SENDIODATA";                                                                    
	case XMS_EVT_RECVIODATA						 :return "EVT_RECVIODATA";                                                                    
		                                                               
	case XMS_EVT_DEV_TIMER						 :return "EVT_DEV_TIMER";                                                                      
		
	case XMS_EVT_UNIFAILURE				         :return "EVT_UNIFAILURE";   
	default:							return "";
	}
}

char* GetDevTypeName(int i)
{
	switch(i)
	{
	case XMS_DEVMAIN_VOICE:			return "VOICE";
	case XMS_DEVMAIN_FAX:			return "FAX";
	case XMS_DEVMAIN_DIGITAL_PORT:	return "E1";
	case XMS_DEVMAIN_INTERFACE_CH:	return "INTERFACE";
	case XMS_DEVMAIN_DSS1_LINK:		return "DSS1_LINK";
	case XMS_DEVMAIN_SS7_LINK:		return "SS7_LINK";
	case XMS_DEVMAIN_BOARD:			return "BOARD";
	case XMS_DEVMAIN_CTBUS_TS:		return "CTBUS_TS";
	case XMS_DEVMAIN_VOIP:			return "VOIP";
	case XMS_DEVMAIN_MEDIAEX:		return "MEDIAEX";
	case XMS_DEVMAIN_CONFERENCE:	return "CONFERENCE";
	case XMS_DEVMAIN_VIDEO:			return "VIDEO";
	case XMS_DEVMAIN_CTX:			return "CTX";
	case XMS_DEVMAIN_RTPX:			return "RTPX";	
	case XMS_DEVMAIN_VIDEOCONF:		return "VIDEOCONF";
    case XMS_DEVMAIN_RTP:           return "RTP";
	default:						return "NULL";
	}
}

char* GetDevSubTypeName(DeviceID_t *pDev)
{
	switch(pDev->m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOICE:
		switch(pDev->m_s16DeviceSub)
		{
		case XMS_DEVSUB_MEDIA_VOC:
			return "VOC";
		case XMS_DEVSUB_MEDIA_324:
			return "324";
		case XMS_DEVSUB_MEDIA_RAW:
			return "RAW";
		default:
			return "NULL";
		}
	case XMS_DEVMAIN_INTERFACE_CH:
		switch(pDev->m_s16DeviceSub)
		{
		case XMS_DEVSUB_BASE:				return "BASE";
		case XMS_DEVSUB_ANALOG_TRUNK:      	return "TRUNK";
		case XMS_DEVSUB_ANALOG_USER:       	return "A_USER";
		case XMS_DEVSUB_ANALOG_HIZ:        	return "A_HIZ";
		case XMS_DEVSUB_ANALOG_EMPTY:      	return "A_EMPTY";
		case XMS_DEVSUB_E1_PCM:            	return "PCM";
		case XMS_DEVSUB_E1_CAS:            	return "CAS";
		case XMS_DEVSUB_E1_DSS1:           	return "DSS1";
		case XMS_DEVSUB_E1_SS7_TUP:        	return "SS7_TUP";
		case XMS_DEVSUB_E1_SS7_ISUP:       	return "SS7_ISUP";
		case XMS_DEVSUB_ANALOG_VOC2W:		return "A-VOC2W";
		case XMS_DEVSUB_ANALOG_VOC4W:		return "A-VOC4W";
		case XMS_DEVSUB_ANALOG_EM:			return "A-EM";
		case XMS_DEVSUB_ANALOG_MAG:			return "A-MAG";
		case XMS_DEVSUB_E1_DCH:				return "DCH";
		case XMS_DEVSUB_E1_BCH:				return "BCH";
		case XMS_DEVSUB_UNUSABLE:			return "UNUSABLE";
		case XMS_DEVSUB_HIZ_CAS:			return "HIZ_CAS";
		case XMS_DEVSUB_HIZ_PRI:			return "HIZ_PRI";
		case XMS_DEVSUB_HIZ_SS7:			return "HIZ_SS7BASE";
		case XMS_DEVSUB_HIZ_PRI_LINK:		return "HIZ_PRI_LINK";
		case XMS_DEVSUB_HIZ_SS7_64K_LINK:  	return "HIZ_SS7_64K_LINK";
		case XMS_DEVSUB_HIZ_SS7_2M_LINK:  	return "HIZ_SS7_2M_LINK";
		case XMS_DEVSUB_SS7_LINK:			return "SS7_LINK";
		case XMS_DEVSUB_LINESIDE:		    return "LINESIDE";
		case XMS_DEVSUB_ANALOG_REC:	      	return "A_REC";
		case XMS_DEVSUB_DIGITAL_REC:	    return "D_RECBASE";
		case XMS_DEVSUB_HIZ_HDLC_N64K_LINK:	return "HIZ_HDLC_N64K_LINK";
		default:							return "NULL";

		}
	default:
		return GetDevTypeName(pDev->m_s16DeviceMain);
	}
}

char* GetDevState(DevState	Dev_State)
{
	switch(Dev_State) 
	{
	case DEV_STATE_NULL:		return "NULL";
	case DEV_STATE_WAITOPEN:	return "NOT OPEN";
	case DEV_STATE_FREE:		return "FREE";
	case DEV_STATE_USED:		return "USED";
	case DEV_STATE_WAITCONNECT:	return "WAITCONNECT";
	case DEV_STATE_CONNECT:		return "CONNECT";
	case DEV_STATE_WAITFREE:	return "NOT FREE";
	case DEV_STATE_PLAYING:	return "PLAYING";
	case DEV_STATE_INCONF:	return "IN CONF";
	case DEV_STATE_JOIN:	return "JOINING";
	case DEV_STATE_RECORDING:	return "RECING";
	case DEV_STATE_CREATEFAILED: return "CREATEFAILED";
	default:					return "UNKOWN";
	}
}

void DisplayDevType()
{
	int i;
	char Str[100];
	int iDispRow;
	
	g_pDlg->m_ListDevType.DeleteAllItems();
	iDispRow = 0;
	
	for(i = 0; i < MAX_DEV_TYPE; ++i)
	{
		if(g_DevType[i].Dev_Total != 0)
		{
			sprintf(Str, "%d", i);
			g_pDlg->m_ListDevType.InsertItem (iDispRow, Str);
			g_pDlg->m_ListDevType.SetItemText (iDispRow, 1, GetDevTypeName(i));
			sprintf(Str, "%d/%d", g_DevType[i].Dev_Total, g_DevType[i].Dev_Opened);
			g_pDlg->m_ListDevType.SetItemText (iDispRow, 2, Str);
			g_DevType[i].sn = iDispRow;

			iDispRow++;
		}
	}
}

void DisplayDevInfo(int DevType)
{
	int i, j, iTotal;
	char Str[100], sDevName[100];
	DeviceID_t *pDev;
	
	g_CurDisplayDevType = DevType;

	g_pDlg->m_ListDevInfo.DeleteAllItems();

	sprintf(sDevName, "%s", GetDevTypeName(DevType));
	
	sprintf(Str, "Device Info - [%s]", sDevName);
	g_pDlg->SetDlgItemText(IDC_STATIC_DEVINFO, Str);

	iTotal = 0;
	for(i = 0; i < MAX_UNIT; ++i)
	{
		for(j = 0; j < MAX_DEV; ++j)
		{
			if(g_DevInfo[i][DevType][j].Dev_State == DEV_STATE_NULL)
				continue;

			sprintf(Str, "%d", iTotal);
			g_pDlg->m_ListDevInfo.InsertItem (iTotal, Str);

			pDev = &g_DevInfo[i][DevType][j].Dev;
			sprintf(Str, "%d, %d", pDev->m_s8ModuleID, pDev->m_s16ChannelID);
			g_pDlg->m_ListDevInfo.SetItemText (iTotal, 1, Str);
			g_pDlg->m_ListDevInfo.SetItemText (iTotal, 2, GetDevSubTypeName(pDev));
			g_pDlg->m_ListDevInfo.SetItemText (iTotal, 3, GetDevState(g_DevInfo[i][DevType][j].Dev_State));
			g_DevInfo[i][DevType][j].sn = iTotal;
			
			if(++iTotal >= (int)g_DevType[DevType].Dev_Total)
				return;
		}
	}
}

void RefreshDevType(Dev_Type_Info *pDevType)
{
	char Str[256];
	if(pDevType->sn == -1)
		return;

	sprintf(Str, "%d/%d", pDevType->Dev_Total, pDevType->Dev_Opened);
	g_pDlg->m_ListDevType.SetItemText (pDevType->sn, 2, Str);
	g_pDlg->m_ListDevType.EnsureVisible(pDevType->sn, FALSE);
}

void RefreshDevInfo(Dev_Info *pDevInfo)
{
	if(pDevInfo->sn == -1)
		return;

	g_pDlg->m_ListDevInfo.SetItemText(pDevInfo->sn, 3, GetDevState(pDevInfo->Dev_State));
	//g_pDlg->m_ListDevInfo.EnsureVisible(pDevInfo->sn, FALSE);
}

void RefreshConfMemberInfo()
{
	int sn = 0;
	Conf_Node *pNode = g_ConfList;
	char str[256];
	
	while(pNode != NULL)
	{
		if(pNode->conf.id == g_CurConfId)
			break;
		pNode = pNode->next;
	}

	g_pDlg->m_ListMember.DeleteAllItems();

	if(pNode != NULL)
	{
		User_Node *pMember = pNode->conf.MemberList;
		while(pMember != NULL)
		{
			sprintf(str, "%d", sn+1);
			g_pDlg->m_ListMember.InsertItem(sn, str);
			g_pDlg->m_ListMember.SetItemText(sn, 1, pMember->user.name);
			++sn;
			pMember = pMember->next;
		}
	}	
	else
		g_CurConfId = -1;

	char Str[256];
	sprintf(Str, "Conference Member - [%d]", g_CurConfId);
	g_pDlg->SetDlgItemText(IDC_STATIC_MEMBER, Str);
}

void RefreshConfInfo()
{
	int sn = 0;
	Conf_Node *pNode = g_ConfList;
	char str[256];

	g_pDlg->m_ListHotConf.DeleteAllItems();
	
	while(pNode != NULL)
	{
		sprintf(str, "%d", pNode->conf.id);
		g_pDlg->m_ListHotConf.InsertItem(sn, str);
		g_pDlg->m_ListHotConf.SetItemText(sn, 1, pNode->conf.name);
		User_Node *pMember = pNode->conf.MemberList;
		int count = 0;
		while(pMember != NULL)
		{
			++count;
			pMember = pMember->next;
		}
		sprintf(str, "%d", count);
		g_pDlg->m_ListHotConf.SetItemText(sn, 2, str);
		
		++sn;
		pNode = pNode->next;
	}

	RefreshConfMemberInfo();
}

void DisplayConfInfo(int ConfId)
{
	g_CurConfId = ConfId;
	RefreshConfMemberInfo();
}

void SetOverlayFile(DeviceID_t *pDev)
{
	Dev_Info *pDevInfo;
	if(pDev == NULL)
		return;
	pDevInfo = M_DEVINFO(pDev);
	if(pDevInfo->szFileName[4] == NULL)
		pDevInfo->szFileName[4] = (char*)malloc(256);
	if(pDevInfo->szFileName[4] != NULL)
	{
		if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE)
			sprintf(pDevInfo->szFileName[4], "%s\\overlay_324(%d-%d).bmp",g_KeygoeVar.cfg.VocPath, pDev->m_s8ModuleID, pDev->m_s16ChannelID);
		else if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOIP)
			sprintf(pDevInfo->szFileName[4], "%s\\overlay_IP(%d-%d).bmp",g_KeygoeVar.cfg.VocPath, pDev->m_s8ModuleID, pDev->m_s16ChannelID);
		else
			sprintf(pDevInfo->szFileName[4], "");
	}
}

//set overlay text
int SetOverlay(DeviceID_t *pDev, int flag)
{
	Dev_Info *pDevInfo;
	PutTextInPicture_Param paramItem[4];
	int sum = 0;
	
	if(pDev == NULL)
		return 0;

	pDevInfo = M_DEVINFO(pDev);
	
	memset(paramItem, 0, sizeof(PutTextInPicture_Param)*4);
	
	//backgrand
	paramItem[0].m_u8PutByType = PUT_TYPE_PICTURE;
	strcpy(paramItem[0].m_s8PutText, "");
	paramItem[0].structPoint.x = 176;
	paramItem[0].structPoint.y = 144;
	paramItem[0].structFontParam.strcutColor.m_u8R = 0;
	paramItem[0].structFontParam.strcutColor.m_u8G = 0;
	paramItem[0].structFontParam.strcutColor.m_u8B = 0;
	sum++;
	
	if(flag == 1 && strlen(pDevInfo->szText) > 0)
	{	
		paramItem[sum].m_u8PutByType = PUT_TYPE_TEXT;
		paramItem[sum].m_u16FontType = FONTTYPE_SIMSUN;
		strcpy(paramItem[sum].m_s8PutText, pDevInfo->szText);
		paramItem[sum].m_f32Diaphaneity = 1.0;
		paramItem[sum].structPoint.x = 80-(strlen(pDevInfo->szText)/2)*7;
		paramItem[sum].structPoint.y = 130;
		paramItem[sum].structFontParam.m_bUnderLine = false;
		paramItem[sum].structFontParam.m_f64DBSize = 15.0;
		paramItem[sum].structFontParam.m_f64DBBlank = 0.5;
		paramItem[sum].structFontParam.m_f64DBGap = 0.1;
		paramItem[sum].structFontParam.strcutColor.m_u8R = 255;
		sum++;		
	}
	if(flag == 2 && strlen(pDevInfo->szDTMF) > 0)
	{
		paramItem[sum].m_u8PutByType = PUT_TYPE_TEXT;
		paramItem[sum].m_u16FontType = FONTTYPE_MICROSS;
		strcpy(paramItem[sum].m_s8PutText, pDevInfo->szDTMF);
		paramItem[sum].m_f32Diaphaneity = 1.0;
		paramItem[sum].structPoint.x = 80-(strlen(pDevInfo->szDTMF)/2)*7;
		paramItem[sum].structPoint.y = 130;
		paramItem[sum].structFontParam.m_bUnderLine = false;
		paramItem[sum].structFontParam.m_f64DBSize = 20.0;
		paramItem[sum].structFontParam.m_f64DBBlank = 0.5;
		paramItem[sum].structFontParam.m_f64DBGap = 0.1;
		paramItem[sum].structFontParam.strcutColor.m_u8R = 255;
		sum++;
	}

	XMS_ctsPutTextInPicture(g_KeygoeVar.ACSHandle, pDevInfo->szFileName[4], paramItem, sum, NULL);	

	return 1;
}

int IsSameDev(DeviceID_t *pDev1, DeviceID_t *pDev2)
{
	if(pDev1 == NULL || pDev2 == NULL)
		return 0;

	if(pDev1->m_s8ModuleID == pDev2->m_s8ModuleID &&
		pDev1->m_s16ChannelID == pDev2->m_s16ChannelID &&
		pDev1->m_s16DeviceMain == pDev2->m_s16DeviceMain &&
		pDev1->m_s16DeviceSub == pDev2->m_s16DeviceSub)
		return 1;
	else
		return 0;
}

void ChangeDevState(Dev_Info *pDevInfo, DevState state)
{
	pDevInfo->Dev_State = state;
	if(pDevInfo->Dev.m_s16DeviceMain == g_CurDisplayDevType)
		RefreshDevInfo(pDevInfo);
}

DeviceID_t* GetSelectDev()
{
	unsigned int iModuleId, iChnnlId, splitpos;
	DeviceID_t *pDev = NULL;
	CString itemText;
	
	POSITION pos = g_pDlg->m_ListDevInfo.GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
		int nItem = g_pDlg->m_ListDevInfo.GetNextSelectedItem(pos);
		itemText = g_pDlg->m_ListDevInfo.GetItemText(nItem, 1);
		splitpos = itemText.Find(',', 0);
		iModuleId = atoi(itemText.Left(splitpos));
		iChnnlId = atoi(itemText.Right(itemText.GetLength()-splitpos-1));
		
		if(g_DevInfo[iModuleId][g_CurDisplayDevType][iChnnlId].Dev_State != DEV_STATE_WAITOPEN)
			pDev = &g_DevInfo[iModuleId][g_CurDisplayDevType][iChnnlId].Dev;
	}
	
	if(pDev == NULL)
	{
		AfxMessageBox("Please select an opened device!");
	}

	return pDev;
}

void ResetDev(DeviceID_t *pDev)
{
	Dev_Info *pDevInfo;
	
	if(pDev == NULL)
		return;

	XMS_ctsResetDevice(g_KeygoeVar.ACSHandle, pDev, NULL);	//reset device

	pDevInfo = M_DEVINFO(pDev);
	
	pDevInfo->pLinkDev = NULL;
	pDevInfo->pPlayRecDev = NULL;
	pDevInfo->pVoiceLinkDev1 = NULL;
	pDevInfo->pVoiceLinkDev2 = NULL;
	pDevInfo->audio.RxCodec = 0xff;
	pDevInfo->audio.RxPayloadType = 0xff;
	pDevInfo->audio.TxCodec = 0xff;
	pDevInfo->audio.TxPayloadType = 0xff;
	pDevInfo->video.RxCodec = 0xff;
	pDevInfo->video.RxPayloadType = 0xff;
	pDevInfo->video.TxCodec = 0xff;
	pDevInfo->video.TxPayloadType = 0xff;
	sprintf(pDevInfo->szDTMF, "");
	sprintf(pDevInfo->szText, "");
	if(pDevInfo->szFileName[0] != NULL)
		sprintf(pDevInfo->szFileName[0], "");
	if(pDevInfo->szFileName[1] != NULL)
		sprintf(pDevInfo->szFileName[1], "");
	if(pDevInfo->szFileName[2] != NULL)
		sprintf(pDevInfo->szFileName[2], "");
	if(pDevInfo->szFileName[3] != NULL)
		sprintf(pDevInfo->szFileName[3], "");
	if(pDevInfo->szFileName[4] != NULL)
		sprintf(pDevInfo->szFileName[4], "");
    pDevInfo->decoderConfigLength = 0;
}

void ReleaseDev(DeviceID_t *pDev)
{
	Dev_Info *pDevInfo;

	if(pDev == NULL)
		return;

	pDevInfo = M_DEVINFO(pDev);
	
	if(pDevInfo->pPlayRecDev != NULL)
	{
		ChangeDevState(M_DEVINFO(pDevInfo->pPlayRecDev), DEV_STATE_FREE);
		pDevInfo->pPlayRecDev = NULL;
	}
	if(pDevInfo->pVoiceLinkDev1 != NULL)
	{
		ChangeDevState(M_DEVINFO(pDevInfo->pVoiceLinkDev1), DEV_STATE_FREE);
		pDevInfo->pVoiceLinkDev1 = NULL;
	}
	if(pDevInfo->pVoiceLinkDev2 != NULL)
	{
		if(!IsSameDev(pDevInfo->pVoiceLinkDev2, pDev))
			ChangeDevState(M_DEVINFO(pDevInfo->pVoiceLinkDev2), DEV_STATE_FREE);
		pDevInfo->pVoiceLinkDev2 = NULL;
	}

	if((pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE && pDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_324) ||
		pDev->m_s16DeviceMain == XMS_DEVMAIN_VOIP || pDev->m_s16DeviceMain == XMS_DEVMAIN_VIDEOCONF)
	{
		Control3gppPlay_t control3gpPlay;
		memset(&control3gpPlay, 0, sizeof(Control3gppPlay_t));
		control3gpPlay.m_u16ControlType = XMS_STOP_PLAY;
		control3gpPlay.m_u8MediaType = MEDIA_TYPE_MEDIAEX_ANV;
		XMS_ctsControl3gppPlay(g_KeygoeVar.ACSHandle, pDev, &control3gpPlay, NULL);
	}
				
	ResetDev(pDev);
	ChangeDevState(pDevInfo, DEV_STATE_FREE);
}

int    SplitStr2Int(DJ_S8 *str, DJ_S8 *sep, int buf[])
{
	DJ_U32   i = 0;
	DJ_S8    *p = NULL;
	DJ_S8    *pBuf = NULL;
	
	if ( (str==NULL)||(strlen(str)==0)||(sep==NULL)||(strlen(sep)==0) )
	{
		return -1;
	}
	
	pBuf = str;
	p = strtok(pBuf, sep);
	
	while ( p != NULL )
	{
		buf[i++] = atoi(p);
		p = strtok(NULL, sep);
	}
	
	return i;
}

void ReadFromConfig(void)
{
//	int i;
	char cfg_IniName[256];
//	char str[256];
	
	GetCurrentDirectory (256-32, cfg_IniName );
	strcat (cfg_IniName, "\\XMS_3G_Demo.ini");
	
	GetPrivateProfileString ( "ConfigInfo", "IpAddr", "192.168.0.8", g_KeygoeVar.cfg.ServerId.m_s8ServerIp, sizeof(g_KeygoeVar.cfg.ServerId.m_s8ServerIp), cfg_IniName);
	
	g_KeygoeVar.cfg.ServerId.m_u32ServerPort = GetPrivateProfileInt ( "ConfigInfo", "Port", 9001, cfg_IniName);
	
	GetPrivateProfileString("ConfigInfo","UserName","",g_KeygoeVar.cfg.ServerId.m_s8UserName,sizeof(g_KeygoeVar.cfg.ServerId.m_s8UserName),cfg_IniName);
	GetPrivateProfileString("ConfigInfo","PassWord","",g_KeygoeVar.cfg.ServerId.m_s8UserPwd,sizeof(g_KeygoeVar.cfg.ServerId.m_s8UserPwd),cfg_IniName);
	g_KeygoeVar.cfg.DebugOn = GetPrivateProfileInt("ConfigInfo", "DebugOn", 0, cfg_IniName);
	char str[256];
	GetPrivateProfileString("ConfigInfo", "DspId", "", str, sizeof(str), cfg_IniName);
	SplitStr2Int(str, ",", g_KeygoeVar.cfg.DspId);
	g_KeygoeVar.cfg.UnitId = GetPrivateProfileInt("ConfigInfo", "UnitId", 10, cfg_IniName);

	GetPrivateProfileString("ConfigInfo","VocPath","",g_KeygoeVar.cfg.VocPath,sizeof(g_KeygoeVar.cfg.VocPath),cfg_IniName);
	GetPrivateProfileString("ConfigInfo","Callee","",g_KeygoeVar.cfg.callee,sizeof(g_KeygoeVar.cfg.callee),cfg_IniName);
	TRACE("%s",g_KeygoeVar.cfg.callee);
}

void InitDev(Dev_Info *pDevInfo)
{
	if(pDevInfo == NULL)
		return;

	ResetDev(&(pDevInfo->Dev));
	pDevInfo->Dev_State = DEV_STATE_NULL;
	pDevInfo->sn = -1;
}

void Init()
{
	int i, j, k;

	g_KeygoeVar.ACSHandle = -1;

	for(i = 0; i < MAX_DEV_TYPE; ++i)
	{
		g_DevType[i].Dev_Total = 0;
		g_DevType[i].Dev_Opened = 0;
		g_DevType[i].Dev_Free = 0;
		g_DevType[i].sn = -1;
		g_LastUsedUnit[i] = 1;
	}

	for(i = 0; i < MAX_UNIT; ++i)
	{
		for(j = 0; j < MAX_DEV_TYPE; ++j)
		{
			for(k = 0; k < MAX_DEV; ++k)
			{
				g_DevInfo[i][j][k].szFileName[0] = NULL;
				g_DevInfo[i][j][k].szFileName[1] = NULL;
				g_DevInfo[i][j][k].szFileName[2] = NULL;
				g_DevInfo[i][j][k].szFileName[3] = NULL;
				g_DevInfo[i][j][k].szFileName[4] = NULL;
				InitDev(&g_DevInfo[i][j][k]);	
			}
			g_LastUsedChann[i][j] = 0;
		}

		g_KeygoeVar.cfg.DspId[i] = 0;
	}

	g_CurDisplayDevType = 0;
	g_CurConfId = -1;
	
	ConfList pConfList;
	while(g_ConfList)
	{
		pConfList = g_ConfList;
		g_ConfList = g_ConfList->next;
		delete pConfList;
	}
}

bool InitSystem()
{
	RetCode_t	r;
	char		MsgStr[160];
	
	g_pDlg = (CSPDlg *)theApp.m_pMainWnd;
	
	AddMsg("Program starting ...\n");

	Init();

	InitView();
	
	// Read From INI
	ReadFromConfig();
	AddMsg("Get configuration!\n");

	/*Call acsOpenStream construct connection to ACS server*/
	r = XMS_acsOpenStream (&g_KeygoeVar.ACSHandle, 
							&g_KeygoeVar.cfg.ServerId,
							g_KeygoeVar.cfg.UnitId,		// App Unit ID 
							256,				// sendQSize, in K Bytes
							256,				// recvQSize, in K Bytes
							g_KeygoeVar.cfg.DebugOn,	// Debug On/Off
							NULL);

	if ( r < 0 )
	{
		sprintf ( MsgStr, "XMS_acsOpenStream(IP Addr : %s, port : %d) FAIL. ret = %d", 
			g_KeygoeVar.cfg.ServerId.m_s8ServerIp, g_KeygoeVar.cfg.ServerId.m_u32ServerPort, r );
		
		//MessageBox(NULL, MsgStr, "Init System", MB_OK ) ;
		AddMsg ( MsgStr );
		return false;
	}
	else
	{
		sprintf ( MsgStr, "XMS_acsOpenStream(%s,%d) OK!", g_KeygoeVar.cfg.ServerId.m_s8ServerIp, g_KeygoeVar.cfg.ServerId.m_u32ServerPort );
		AddMsg ( MsgStr );
	}
	
	r = XMS_acsSetESR (g_KeygoeVar.ACSHandle, (EsrFunc)EvtHandler, 0, 1 );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "XMS_acsSetESR() FAIL! ret = %d", r );
		AddMsg ( MsgStr );
		return false;
	}
	else
	{
		AddMsg ("XMS_acsSetESR() OK!");
	}
	
	//InitAllDeviceRes ();
//return r;	
	XMS_acsGetDeviceList(g_KeygoeVar.ACSHandle, NULL);
	
	return true;
}

void Release()
{
	int i, j, k;
	
	for(i = 0; i < MAX_UNIT; ++i)
	{
		for(j = 0; j < MAX_DEV_TYPE; ++j)
		{
			for(k = 0; k < MAX_DEV; ++k)
			{
				if(g_DevInfo[i][j][k].szFileName[0] != NULL)
					free(g_DevInfo[i][j][k].szFileName[0]);
				if(g_DevInfo[i][j][k].szFileName[1] != NULL)
					free(g_DevInfo[i][j][k].szFileName[1]);
				if(g_DevInfo[i][j][k].szFileName[2] != NULL)
					free(g_DevInfo[i][j][k].szFileName[2]);
				if(g_DevInfo[i][j][k].szFileName[3] != NULL)
					free(g_DevInfo[i][j][k].szFileName[3]);
				if(g_DevInfo[i][j][k].szFileName[4] != NULL)
					free(g_DevInfo[i][j][k].szFileName[4]);
				g_DevInfo[i][j][k].szFileName[0] = NULL;
				g_DevInfo[i][j][k].szFileName[1] = NULL;
				g_DevInfo[i][j][k].szFileName[2] = NULL;
				g_DevInfo[i][j][k].szFileName[3] = NULL;	
				g_DevInfo[i][j][k].szFileName[4] = NULL;	
			}
		}
	}
}

void ExitSystem() 
{
	RetCode_t	r;

	ServConfExit();

	r = XMS_acsCloseStream(g_KeygoeVar.ACSHandle, NULL);

	Release();
}

DeviceID_t* GetOneDev(int unit, int dev_main, int dev_sub, DevState dev_state)
{
	int i, j, iCount = 0, iCountUnit = 0, iBase = 0;
	DeviceID_t *pDev = NULL;

	if(unit >= MAX_UNIT)
		return NULL;

	if(unit == 0)
	{
		i = g_LastUsedUnit[dev_main];
		
	}
	else
	{
		i = unit;
	}

	while(i < MAX_UNIT)
	{
		j = g_LastUsedChann[i][dev_main];
		iCount = 0;
		while(j < MAX_DEV)
		{
			if(g_DevInfo[i][dev_main][j].Dev.m_s16DeviceSub == dev_sub && 
				g_DevInfo[i][dev_main][j].Dev_State == dev_state)
			{
				ChangeDevState(&g_DevInfo[i][dev_main][j], DEV_STATE_USED);
				pDev = &(g_DevInfo[i][dev_main][j].Dev);
				break;
			}

			if(++j >= MAX_DEV)
				j = 0;
			
			if(++iCount >= MAX_DEV)
				break;
		}
		
		if(unit != 0 || pDev)
			break;

		if(++i >= MAX_UNIT)
			i = 1;

		if(++iCountUnit >= MAX_UNIT)
			break;
	}
	
	if(pDev)
	{
		g_LastUsedUnit[dev_main] = pDev->m_s8ModuleID + 1;
		if(g_LastUsedUnit[dev_main] >= MAX_UNIT)
			g_LastUsedUnit[dev_main] = 1;
		g_LastUsedChann[pDev->m_s8ModuleID][dev_main] = pDev->m_s16ChannelID + 1;
		if(g_LastUsedChann[pDev->m_s8ModuleID][dev_main] >= MAX_DEV)
			g_LastUsedChann[pDev->m_s8ModuleID][dev_main] = 0;
	}

	return pDev;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//API wrapper

int SetDevTimer(DeviceID_t *pDev, int time)
{
	if(XMS_ctsSetDevTimer(g_KeygoeVar.ACSHandle, pDev,time) < 0)
	{
		AddMsg("XMS_ctsSetDevTimer failed");
		return 0;
	}
	return 1;
}

void GetDevList()
{
	XMS_acsGetDeviceList(g_KeygoeVar.ACSHandle, NULL);
}

void DualLinkDev(DeviceID_t *pDev1, DeviceID_t *pDev2)
{
	if(pDev1 == NULL || pDev2 == NULL)
		return;
	
	XMS_ctsLinkDevice(g_KeygoeVar.ACSHandle, pDev1, pDev2, NULL); 
	XMS_ctsLinkDevice(g_KeygoeVar.ACSHandle, pDev2, pDev1, NULL); 
}

void DualUnlinkDev(DeviceID_t *pDev1, DeviceID_t *pDev2)
{
	if(pDev1 == NULL || pDev2 == NULL)
		return;
	
	XMS_ctsUnlinkDevice(g_KeygoeVar.ACSHandle, pDev1, pDev2, NULL); 
	XMS_ctsUnlinkDevice(g_KeygoeVar.ACSHandle, pDev2, pDev1, NULL); 
}

/////// 3G-324M operation

//start 324 session
int H324StartSession(DeviceID_t *pVoc, int mode)
{
	RetCode_t	r;
	char str[128];
	
	r = XMS_ctsSendSignalMsg(g_KeygoeVar.ACSHandle, pVoc, mode);
	if ( r < 0 )
	{
		sprintf(str, "Start h324 cmd failed(mode=%d)", mode);
		AddMsg (str);
		return 0;
	}
	return 1;
}

//stop 324 session
int H324StopSession(DeviceID_t *pVoc)
{
	RetCode_t	r;
	
	r = XMS_ctsSendSignalMsg(g_KeygoeVar.ACSHandle, pVoc, XMS_324_CMD_TYPE_STOP);
	if ( r < 0 )
	{
		AddMsg ("Stop h324 cmd failed");
		return 0;
	}
	return 1;
}

//reset 324 session
int H324ResetSession(DeviceID_t *pVoc)
{
	RetCode_t	r;
	
	r = XMS_ctsSendSignalMsg(g_KeygoeVar.ACSHandle, pVoc, XMS_324_CMD_TYPE_RESET);
	if ( r < 0 )
	{
		AddMsg ("Stop h324 cmd failed");
		return 0;
	}
	return 1;
}

//Get media parameter from 3gp file
DJ_S32 H324GetMediaFilePara(DeviceID_t *pVocDev, char *sFileName)
{
	RetCode_t	r;
	Get3gppCfg_t para;
	
	if(!pVocDev || !sFileName)
		return 0;
	
	memset(&para, 0, sizeof(Get3gppCfg_t));
	para.m_u8MediaType = MEDIA_TYPE_ANV;   /*media type: XMS_MEDIA_TYPE*/
	para.m_u8AudioFileType = MD_CFG_TYPE_NON_INDEX;	
	strcpy(para.m_s8AudioFileName, sFileName);/*audio file path and name*/
	para.m_u8VideoFileType = MD_CFG_TYPE_NON_INDEX;            
	strcpy(para.m_s8VideoFileName, sFileName);/*video file path and name*/
	
	r = XMS_ctsGetParam(g_KeygoeVar.ACSHandle, 
		pVocDev, 
		H324_PARAM_MEDIA,
		sizeof(Get3gppCfg_t),
		&para);
	if ( r < 0 )
	{
		AddMsg ( "Get media file parameter failed!" );
		return 0;
	}
	
	return 1;
}

//Set 324 session media parameter
DJ_S32 H324SetMediaPara(DeviceID_t *pVocDev, ITP_3GPP_PARAM_CFG *pMediaPara)
{
	RetCode_t	r;
	
	if(!pVocDev || !pMediaPara)
		return 0;
	
	r = XMS_ctsSetParam(g_KeygoeVar.ACSHandle, 
		pVocDev, 
		H324_PARAM_MEDIA, 
		sizeof(ITP_3GPP_PARAM_CFG), 
		pMediaPara);
	if ( r < 0 )
	{
		AddMsg ( "Set media parameter failed!" );
		return 0;
	}
	
	return 1;
}

//set 324 channel configure
DJ_S32 H324SetChCfg(DeviceID_t *pVoc, CmdParamData_324CH_t *pChCfg)
{
	RetCode_t	r;
	
	if(!pVoc)
		return 0;
	
	r = XMS_ctsSetParam(g_KeygoeVar.ACSHandle, 
		pVoc, 
		H324_PARAM_CH, 
		sizeof(CmdParamData_324CH_t), 
		pChCfg);
	if ( r < 0 )
	{
		AddMsg ( "Set media parameter failed!" );
		return 0;
	}
	
	return 1;
}

int SetParam(DeviceID_t *pDev, int ParamType, int ParamLen, void *Param);

DJ_S32 H324SetTCS(DeviceID_t *pDev)
{
	Acs_3G324M_TCS tcs;

	if(!pDev)
		return 0;

	memset(&tcs, 0, sizeof(Acs_3G324M_TCS));

	//set h233 capability
	tcs.h223Capability.videoWithAL1 = 0;
	tcs.h223Capability.videoWithAL2 = 1;
	tcs.h223Capability.videoWithAL3 = 0;
	tcs.h223Capability.audioWithAL1 = 0;
	tcs.h223Capability.audioWithAL2 = 1;
	tcs.h223Capability.audioWithAL3 = 0;
	tcs.h223Capability.maximumAl2SDUSize = 4096;
	tcs.h223Capability.maximumAl3SDUSize = 4096;
	tcs.h223Capability.maximumDelayJitter = 200;
	tcs.h223Capability.maxMUXPDUSizeCapability = 0;
	tcs.h223Capability.nsrpSupport = 1;
	tcs.h223Capability.modeChangeCapability = 0;
	tcs.h223Capability.h223AnnexA = 1;
	tcs.h223Capability.h223AnnexADoubleFlag = 1;
	tcs.h223Capability.h223AnnexB = 1;
	tcs.h223Capability.h223AnnexBwithHeader = 1;

	//set media capability
	tcs.capabilityTable.capabilityNum = 4;
	
	int i;

	//AMR
	i = 0;
	tcs.capabilityTable.CapabilityTableEntry[i].entryNumber = i;
	tcs.capabilityTable.CapabilityTableEntry[i].capType = VOIP_MEDIA_AUDIO_AMR;
	tcs.capabilityTable.CapabilityTableEntry[i].direction = XMS_CAP_DIR_RXTX;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.AmrAudioCapability.maxBitRate = 122;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.AmrAudioCapability.maxFramesPerSdu = 3;

	//G7231
	i = 1;
	tcs.capabilityTable.CapabilityTableEntry[i].entryNumber = i;
	tcs.capabilityTable.CapabilityTableEntry[i].capType = VOIP_MEDIA_AUDIO_G723;
	tcs.capabilityTable.CapabilityTableEntry[i].direction = XMS_CAP_DIR_RXTX;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.G7231AudioCapability.maxFramesPerSdu = 3;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.G7231AudioCapability.silenceSuppression = 0;

	//H.263
    if(g_DevInfo[pDev->m_s8ModuleID][XMS_DEVMAIN_VOICE][10].Dev_State == DEV_STATE_WAITOPEN)
	    i = 2;
    else
        i = 3;
	tcs.capabilityTable.CapabilityTableEntry[i].entryNumber = i;
	tcs.capabilityTable.CapabilityTableEntry[i].capType = VOIP_MEDIA_VIDEO_H263;
	tcs.capabilityTable.CapabilityTableEntry[i].direction = XMS_CAP_DIR_RXTX;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.H263VideoCapability.sqcifMPI = 1;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.H263VideoCapability.qcifMPI = 2;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.H263VideoCapability.cifMPI = 2;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.H263VideoCapability.cif4MPI = 32;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.H263VideoCapability.cif16MPI = 32;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.H263VideoCapability.maxBitRate = 460;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.H263VideoCapability.unrestrictedVector = 0;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.H263VideoCapability.arithmeticCoding = 0;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.H263VideoCapability.advancedPrediction = 0;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.H263VideoCapability.pbFrames = 0;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.H263VideoCapability.temporalSpatialTradeOffCapability = 1;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.H263VideoCapability.errorCompensation = 0;

	//MPEG4
	if(g_DevInfo[pDev->m_s8ModuleID][XMS_DEVMAIN_VOICE][10].Dev_State == DEV_STATE_WAITOPEN)
	    i = 3;
    else
        i = 2;
	tcs.capabilityTable.CapabilityTableEntry[i].entryNumber = i;
	tcs.capabilityTable.CapabilityTableEntry[i].capType = VOIP_MEDIA_VIDEO_MPEG4;
	tcs.capabilityTable.CapabilityTableEntry[i].direction = XMS_CAP_DIR_RXTX;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.Mpeg4VideoCapability.maxBitRate = 600;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.Mpeg4VideoCapability.profileAndLevel = 2;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.Mpeg4VideoCapability.object = 0;
	tcs.capabilityTable.CapabilityTableEntry[i].capability.Mpeg4VideoCapability.decoderConfigLength = 28;

	//DJ_U8 info[28] = {0x00, 0x00, 0x01, 0xb0, 0x02, 0x00, 0x00, 0x01, 0xb5, 0x09, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01, 0x20, 0x00, 0x84, 0x5d, 0x4c, 0x28, 0x2c, 0x20, 0x90, 0xa2, 0xcf};
	//DJ_U8 info[39] = {0x00, 0x00, 0x01, 0xb0, 0x08, 0x00, 0x00, 0x01, 0xb5, 0x0e, 0xcf, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x20, 0x00, 0x8a, 0xe0, 0x00, 0x20, 0x1e, 0x20, 0x00, 0x2c, 0x00, 0x40, 0xf3, 0xcb, 0xa9, 0x85, 0x05, 0x84, 0x12, 0x14, 0x51};
	DJ_U8 info[32] = {	0x00, 0x00, 0x01, 0xb0, 0x08, 
						0x00, 0x00, 0x01, 0xb5, 0x0e, 0xe0, 0x40, 0xc0, 0xcf, 
						0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x20, 0x00, 0x84, 0x40, 0xfa, 0x28, 0x2c, 0x20, 0x90, 0xa3, 0x1f};
	tcs.capabilityTable.CapabilityTableEntry[i].capability.Mpeg4VideoCapability.decoderConfigLength = 32;
	memcpy(tcs.capabilityTable.CapabilityTableEntry[i].capability.Mpeg4VideoCapability.decoderConfigInfo, info, 32);

	SetParam(pDev, H324_PARAM_TCS, sizeof(tcs), &tcs);

	return 1;
}

int PlayVoc(DeviceID_t *pVoc, char *sFileName, unsigned int time, PrivateData_t * privateData)
{
	RetCode_t	r;
	PlayProperty_t  playProperty;

	memset(&playProperty,0,sizeof(playProperty));		
	
	playProperty.m_u16PlayType = XMS_PLAY_TYPE_FILE;	
	strcpy ( playProperty.m_s8PlayContent, sFileName );
	playProperty.m_u32MaxTime = time;

	r = XMS_ctsPlay(g_KeygoeVar.ACSHandle, pVoc, &playProperty, privateData);
	if ( r < 0 )
	{
		AddMsg ( "Play file failed!" );
		return 0;
	}
	
	return 1;
}

int RecordVoc(DeviceID_t *pVoc, char *sFileName, MixerControlParam_t *pAudioMixer, unsigned int u32RecSize, bool bIsAppend)
{	
	RecordProperty_t	recordProperty;
	RetCode_t			r;

	memset(&recordProperty,0,sizeof(RecordProperty_t));		
	
	recordProperty.m_u32MaxSize = u32RecSize;

	if ( bIsAppend )
		recordProperty.m_s8IsAppend = 1;
	else
		recordProperty.m_s8IsAppend = 0;

	strcpy ( recordProperty.m_s8FileName, sFileName );

	if(pAudioMixer != NULL)
	{
		recordProperty.m_s8IsMixEnable = 1;
		recordProperty.m_MixerControl.m_u8SRC1_Ctrl = pAudioMixer->m_u8SRC1_Ctrl;
		recordProperty.m_MixerControl.m_u16SRC_ChID1 = pAudioMixer->m_u16SRC_ChID1;
		recordProperty.m_MixerControl.m_u8SRC2_Ctrl = pAudioMixer->m_u8SRC2_Ctrl;
		recordProperty.m_MixerControl.m_u16SRC_ChID2 = pAudioMixer->m_u16SRC_ChID2;
	}
	
	r = XMS_ctsRecord(g_KeygoeVar.ACSHandle, pVoc, &recordProperty, NULL);
	if ( r < 0 )
	{
		AddMsg ( "Record file failed!" );
		return 0;
	}
	
	return 1;
}

int Play3GP(DeviceID_t *pDev, Play3gppProperty_t *pPlayProperty, PrivateData_t * privateData)
{
	RetCode_t	r = -1;
	
	r = XMS_cts3gppPlay (g_KeygoeVar.ACSHandle, pDev, pPlayProperty, privateData);
	if ( r < 0 )
	{
		AddMsg ( "Play 3gp file failed!" );
		return 0;
	}
	
	return 1;
}

int Record3GP(DeviceID_t *pDev, Record3gppProperty_t *pRecProperty, PrivateData_t * privateData)
{
	RetCode_t			r;

	r = XMS_cts3gppRecord (g_KeygoeVar.ACSHandle, pDev, pRecProperty, privateData);
	if ( r < 0 )
	{
		AddMsg ( "Record 3gp file failed!" );
		return 0;
	}

	return 1;
}

int StopPlay(DeviceID_t *pDev)
{
	RetCode_t			r;
	Control3gppPlay_t	control3gpPlay;
	Dev_Info *pDevInfo;
	
	if(!pDev)
		return 0;

	//video conferenc stop play
	if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VIDEOCONF)
	{
		Control3gppPlay_t paramPlay;
		memset(&paramPlay, 0, sizeof(Control3gppPlay_t));
		if(XMS_ctsControl3gppPlay(g_KeygoeVar.ACSHandle, pDev, &paramPlay, NULL) < 0)
			return 0;
		else
			return 1;
	}
	
	//stop mediaex play
	memset(&control3gpPlay, 0, sizeof(Control3gppPlay_t));
	control3gpPlay.m_u16ControlType = XMS_STOP_PLAY;
	control3gpPlay.m_u8MediaType = MEDIA_TYPE_MEDIAEX_ANV;
	r = XMS_ctsControl3gppPlay(g_KeygoeVar.ACSHandle, pDev, &control3gpPlay, NULL);
	if ( r < 0 )
	{
		AddMsg ( "Stop MediaEx play failed!" );
	}
	
	pDevInfo = M_DEVINFO(pDev);
	if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE && pDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_VOC)
	{
		//stop voice play
		ControlPlay_t	controlPlay;
		controlPlay.m_u16ControlType = XMS_STOP_PLAY;
		XMS_ctsControlPlay(g_KeygoeVar.ACSHandle, pDev, &controlPlay, NULL);
	}
	else if(pDevInfo->pPlayRecDev != NULL)
	{
		//stop 3GP play		
		control3gpPlay.m_u16ControlType = XMS_STOP_PLAY;
		control3gpPlay.m_u8MediaType = MEDIA_TYPE_ANV;
		r = XMS_ctsControl3gppPlay(g_KeygoeVar.ACSHandle, pDevInfo->pPlayRecDev, &control3gpPlay, NULL);
		if ( r < 0 )
		{
			AddMsg ( "Stop play 3gp file failed!" );
		}
	}
	
	return 1;
}

int StopRecord(DeviceID_t *pDev)
{
	RetCode_t			r;
	Control3gppRecord_t	control3gpRecord;
	Dev_Info *pDevInfo;

	if(pDev == NULL)
		return 0;

	if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VIDEOCONF)
	{
		Control3gppRecord_t paramRecord;
		memset(&paramRecord, 0, sizeof(Control3gppRecord_t));
		if(XMS_ctsControl3gppRecord(g_KeygoeVar.ACSHandle, pDev, &paramRecord, NULL) < 0)
			return 0;
		else
			return 1;
	}

	//stop mediaex record
	memset(&control3gpRecord, 0, sizeof(Control3gppRecord_t));
	control3gpRecord.m_u32ControlType = XMS_STOP_RECORD;
	control3gpRecord.m_u8MediaType = MEDIA_TYPE_MEDIAEX_ANV;
	r = XMS_ctsControl3gppRecord(g_KeygoeVar.ACSHandle, pDev, &control3gpRecord, NULL);
	if ( r < 0 )
	{
		AddMsg ( "Stop record 3gp file failed!" );
	}

	pDevInfo = M_DEVINFO(pDev);
	if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE && pDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_VOC)
	{
		//stop voice record
		ControlRecord_t	controlRecord;
		controlRecord.m_u32ControlType = XMS_STOP_RECORD;
		XMS_ctsControlRecord(g_KeygoeVar.ACSHandle, pDev, &controlRecord, NULL);
	}
	else if(pDevInfo->pPlayRecDev != NULL)
	{		
		//stop 3GP record
		control3gpRecord.m_u32ControlType = XMS_STOP_RECORD;
		control3gpRecord.m_u8MediaType = MEDIA_TYPE_ANV;
		r = XMS_ctsControl3gppRecord(g_KeygoeVar.ACSHandle, pDevInfo->pPlayRecDev, &control3gpRecord, NULL);
		if ( r < 0 )
		{
			AddMsg ( "Stop record 3gp file failed!" );
		}	
	}

	return 1;
}
	
int StopMedia(DeviceID_t *pDev)
{
	StopPlay(pDev);
	StopRecord(pDev);

	return 1;
}

int GetParam(DeviceID_t *pDev, int ParamType, int ParamLen, void *Param)
{
	if(XMS_ctsGetParam(g_KeygoeVar.ACSHandle, pDev, ParamType, ParamLen, Param) < 0)
		return 0;

	return 1;
}

int SetParam(DeviceID_t *pDev, int ParamType, int ParamLen, void *Param)
{
	if(XMS_ctsSetParam(g_KeygoeVar.ACSHandle, pDev, ParamType, ParamLen, Param) < 0)
		return 0;

	return 1;
}

void SetParamVoiceMixer(DeviceID_t *pDev, DeviceID_t *pSrc1, DeviceID_t *pSrc2)
{
	CmdParamData_Voice_t paramVoc;
	MixerControlParam_t paramMixer, *pMixer;
	int ParamType, paramLen;
	DJ_U8 *pData;

	memset(&paramMixer, 0, sizeof(paramMixer));
	paramMixer.m_u8Video = 0;

	pData = (DJ_U8*)(&paramMixer);
	paramLen = sizeof(paramMixer);
	pMixer = &paramMixer;
	
	if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE)
	{
		if(pDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_VOC)
		{
			memset(&paramVoc, 0, sizeof(paramVoc));
			paramVoc.m_u8OutputCtrlValid = 1;
			paramVoc.m_VocOutputControl.m_u8OutputType = XMS_VOC_OUTPUT_FROM_MIXER;
			paramVoc.m_VocOutputControl.m_u16FixGain = 1024;
			ParamType = VOC_PARAM_UNIPARAM;
			pData = (DJ_U8*)(&paramVoc);
			paramLen = sizeof(paramVoc);
			pMixer = &paramVoc.m_VocOutputControl.m_MixerControl;
		}
		else if(pDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_324)
			ParamType = H324_PARAM_MIXER;
		else
			return;
	}
	else if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOIP)
	{
		ParamType = VOIP_PARAM_RTPMIXER;
	}
	else
		return;
	
	if(pSrc1 != NULL)
	{
		if(pSrc1->m_s16DeviceMain == XMS_DEVMAIN_VOICE)
		{
			if(pSrc1->m_s16DeviceSub == XMS_DEVSUB_MEDIA_VOC)
				pMixer->m_u8SRC1_Ctrl = XMS_MIXER_FROM_INPUT;
			else if(pSrc1->m_s16DeviceSub == XMS_DEVSUB_MEDIA_324)
				pMixer->m_u8SRC1_Ctrl = XMS_MIXER_FROM_324;
		}
		else if(pSrc1->m_s16DeviceMain == XMS_DEVMAIN_VOIP)
		{
			pMixer->m_u8SRC1_Ctrl = XMS_MIXER_FROM_IP;
		}
		else
			return;
		
		pMixer->m_u16SRC_ChID1 = pSrc1->m_s16ChannelID;
	}

	if(pSrc2 != NULL)
	{
		if(pSrc2->m_s16DeviceMain == XMS_DEVMAIN_VOICE)
		{
			if(pSrc2->m_s16DeviceSub == XMS_DEVSUB_MEDIA_VOC)
				pMixer->m_u8SRC2_Ctrl = XMS_MIXER_FROM_INPUT;
			else if(pSrc2->m_s16DeviceSub == XMS_DEVSUB_MEDIA_324)
				pMixer->m_u8SRC2_Ctrl = XMS_MIXER_FROM_324;
		}
		else if(pSrc2->m_s16DeviceMain == XMS_DEVMAIN_VOIP)
		{
			pMixer->m_u8SRC2_Ctrl = XMS_MIXER_FROM_IP;
		}
		else
			return;
		
		pMixer->m_u16SRC_ChID2 = pSrc2->m_s16ChannelID;
	}

	SetParam(pDev, ParamType, paramLen, pData);
}

void SetParamVideoMixer(DeviceID_t *pDev, DeviceID_t *pVideoSrc)
{
	MixerControlParam_t paramMixer;
	int ParamType;

	memset(&paramMixer, 0, sizeof(paramMixer));
	paramMixer.m_u8Video = 1;

	if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE && pDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_324)
	{
		ParamType = H324_PARAM_MIXER;
	}
	else if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOIP)
	{
		ParamType = VOIP_PARAM_RTPMIXER;
	}
	else if(pDev->m_s16DeviceMain == XMS_DEVMAIN_RTPX)
	{
		ParamType = XMS_RTPX_PARAM_MIXER;
	}
	else
		return;
	
	if(pVideoSrc != NULL)
	{
		if(pVideoSrc->m_s16DeviceMain == XMS_DEVMAIN_VOICE && pVideoSrc->m_s16DeviceSub == XMS_DEVSUB_MEDIA_324)
		{
			paramMixer.m_u8SRC1_Ctrl = XMS_MIXER_FROM_324;
		}
		else if(pVideoSrc->m_s16DeviceMain == XMS_DEVMAIN_VOIP)
		{
			paramMixer.m_u8SRC1_Ctrl = XMS_MIXER_FROM_IP;
		}
		else if(pVideoSrc->m_s16DeviceMain == XMS_DEVMAIN_RTPX)
		{
			paramMixer.m_u8SRC1_Ctrl = XMS_MIXER_FROM_RTPX;
		}
		else
			return;
		
		paramMixer.m_u16SRC_ChID1 = pVideoSrc->m_s16ChannelID;
	}

	SetParam(pDev, ParamType, sizeof(paramMixer), &paramMixer);
}

int SendIOData(DeviceID_t *pDev, int IODataType, int IODataLen, void *IOData)
{
	if(XMS_ctsSendIOData(g_KeygoeVar.ACSHandle, pDev, IODataType, IODataLen, IOData) < 0)
		return 0;

	return 1;
}

int SendFastUpdate(DeviceID_t *pDev)
{
	if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOIP)
	{
		Acs_VoIP_SIPINFO sipInfo = {0};
		strcpy(sipInfo.m_s8ContentType, "application/media_control+xml");
		strcpy(sipInfo.m_s8Body, "<?xml version=\"1.0\" encoding=\"utf-8\" ?>"
			"<media_control><vc_primitive><to_encoder>"
			"<picture_fast_update></picture_fast_update>"
			"</to_encoder></vc_primitive></media_control>");
		AddMsg("Send fast update");
		return SendIOData(pDev, XMS_IO_TYPE_VOIP_SIPINFO, sizeof(sipInfo), &sipInfo);
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//user interface operation

void OnOpenDevice()
{
	RetCode_t	r;
	CString itemText;
	unsigned int iModuleId, iChnnlId, splitpos;
	
	POSITION pos = g_pDlg->m_ListDevInfo.GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
		int nItem = g_pDlg->m_ListDevInfo.GetNextSelectedItem(pos);
		itemText = g_pDlg->m_ListDevInfo.GetItemText(nItem, 1);
		splitpos = itemText.Find(',', 0);
		iModuleId = atoi(itemText.Left(splitpos));
		iChnnlId = atoi(itemText.Right(itemText.GetLength()-splitpos-1));
		
		if(g_DevInfo[iModuleId][g_CurDisplayDevType][iChnnlId].Dev_State == DEV_STATE_WAITOPEN)
		{
			r = XMS_ctsOpenDevice(g_KeygoeVar.ACSHandle, &g_DevInfo[iModuleId][g_CurDisplayDevType][iChnnlId].Dev, NULL);
			if ( r < 0 )
			{
				AddMsg("XMS_ctsOpenDevice Fail!");
			}
		}
		else
		{
			r = XMS_ctsCloseDevice(g_KeygoeVar.ACSHandle, &g_DevInfo[iModuleId][g_CurDisplayDevType][iChnnlId].Dev, NULL);
			if ( r < 0 )
			{
				AddMsg("XMS_ctsCloseDevice Fail!");
			}
		}
	}
}

void OnOpenCurTypeDevice()
{
	int i, j;
	
	if(g_KeygoeVar.cfg.DspId[0] == 0)
		for(i = 0; i < MAX_UNIT; ++i)
		{
			for(j = 0; j < MAX_DEV; ++j)
			{
				if(g_DevInfo[i][g_CurDisplayDevType][j].Dev_State != DEV_STATE_WAITOPEN)
					continue;
				
				XMS_ctsOpenDevice(g_KeygoeVar.ACSHandle, &g_DevInfo[i][g_CurDisplayDevType][j].Dev, NULL);
			}
		}
	else
		for(i = 0; i < MAX_UNIT; ++i)
		{
			if(g_KeygoeVar.cfg.DspId[i] == 0)
				continue;

			for(j = 0; j < MAX_DEV; ++j)
			{
				if(g_DevInfo[g_KeygoeVar.cfg.DspId[i]][g_CurDisplayDevType][j].Dev_State != DEV_STATE_WAITOPEN)
					continue;
				
				XMS_ctsOpenDevice(g_KeygoeVar.ACSHandle, &g_DevInfo[g_KeygoeVar.cfg.DspId[i]][g_CurDisplayDevType][j].Dev, NULL);
			}
		}
}

void OnCloseCurTypeDevice()
{
	int i, j;
	
	if(g_KeygoeVar.cfg.DspId[0] == 0)
		for(i = 0; i < MAX_UNIT; ++i)
		{
			for(j = 0; j < MAX_DEV; ++j)
			{
				if(g_DevInfo[i][g_CurDisplayDevType][j].Dev_State == DEV_STATE_WAITOPEN)
					continue;
				
				XMS_ctsCloseDevice(g_KeygoeVar.ACSHandle, &g_DevInfo[i][g_CurDisplayDevType][j].Dev, NULL);
			}
		}
	else
		for(i = 0; i < MAX_UNIT; ++i)
		{
			if(g_KeygoeVar.cfg.DspId[i] == 0)
				continue;

			for(j = 0; j < MAX_DEV; ++j)
			{
				if(g_DevInfo[g_KeygoeVar.cfg.DspId[i]][g_CurDisplayDevType][j].Dev_State == DEV_STATE_WAITOPEN)
					continue;
				
				XMS_ctsCloseDevice(g_KeygoeVar.ACSHandle, &g_DevInfo[g_KeygoeVar.cfg.DspId[i]][g_CurDisplayDevType][j].Dev, NULL);
			}
		}
}

void OnOpenAllDevice()
{
	int i, j, k;

	if(g_KeygoeVar.cfg.DspId[0] == 0)
		for(i = 0; i < MAX_UNIT; ++i)
		{
			for(j = 0; j < MAX_DEV_TYPE; ++j)
			{
				if(j == XMS_DEVMAIN_RTPX || j == XMS_DEVMAIN_MEDIAEX)
					continue;
			
				for(k = 0; k < MAX_DEV; ++k)
				{
					if(g_DevInfo[i][j][k].Dev_State != DEV_STATE_WAITOPEN)
						continue;

					XMS_ctsOpenDevice(g_KeygoeVar.ACSHandle, &g_DevInfo[i][j][k].Dev, NULL);
				}
			}
		}
	else
		for(i = 0; i < MAX_UNIT; ++i)
		{
			if(g_KeygoeVar.cfg.DspId[i] == 0)
				continue;
			
			for(j = 0; j < MAX_DEV_TYPE; ++j)
			{
				if(j == XMS_DEVMAIN_RTPX || j == XMS_DEVMAIN_MEDIAEX)
					continue;
			
				for(k = 0; k < MAX_DEV; ++k)
				{
					if(g_DevInfo[g_KeygoeVar.cfg.DspId[i]][j][k].Dev_State != DEV_STATE_WAITOPEN)
						continue;
					
					XMS_ctsOpenDevice(g_KeygoeVar.ACSHandle, &g_DevInfo[g_KeygoeVar.cfg.DspId[i]][j][k].Dev, NULL);
				}
			}
		}
}

void OnCloseAllDevice()
{
	int i, j, k;
	
	if(g_KeygoeVar.cfg.DspId[0] == 0)
		for(i = 0; i < MAX_UNIT; ++i)
		{
			for(j = 0; j < MAX_DEV_TYPE; ++j)
			{
				for(k = 0; k < MAX_DEV; ++k)
				{
				if(g_DevInfo[i][j][k].Dev_State == DEV_STATE_WAITOPEN)
					continue;
				
					XMS_ctsCloseDevice(g_KeygoeVar.ACSHandle, &g_DevInfo[i][j][k].Dev, NULL);
				}
			}
		}
	else
		for(i = 0; i < MAX_UNIT; ++i)
		{
			if(g_KeygoeVar.cfg.DspId[i] == 0)
				continue;

			for(j = 0; j < MAX_DEV_TYPE; ++j)
			{
				for(k = 0; k < MAX_DEV; ++k)
				{
					XMS_ctsCloseDevice(g_KeygoeVar.ACSHandle, &g_DevInfo[g_KeygoeVar.cfg.DspId[i]][j][k].Dev, NULL);
				}
			}
		}
}

void OnSetVoipParam(DeviceID_t *pDev, XMS_VOIP_PARAM_TYPE ParamType)
{
	CDlgMixer MixerDlg;
	
	switch(ParamType)
	{
	case VOIP_PARAM_RTPMIXER:	
		if(MixerDlg.DoModal() == IDOK)
		{
			MixerControlParam_t paramMixer;
			memset(&paramMixer, 0, sizeof(paramMixer));
			paramMixer.m_u8SRC1_Ctrl = MixerDlg.m_iSrcCtrl;
			paramMixer.m_u8SRC2_Ctrl = MixerDlg.m_iSrc2Ctrl;
			paramMixer.m_u16SRC_ChID1 = MixerDlg.m_uiSrcId;
			paramMixer.m_u16SRC_ChID2 = MixerDlg.m_uiSrc2Id;
			
			if(MixerDlg.m_bAudio)
			{
				paramMixer.m_u8Video = 0;
				SetParam(pDev, ParamType, sizeof(paramMixer), &paramMixer);
			}
			if(MixerDlg.m_bVideo)
			{
				paramMixer.m_u8Video = 1;
				SetParam(pDev, ParamType, sizeof(paramMixer), &paramMixer);
			}
		}
		break;
	default:
		break;
	}
}

void OnSet324Param(DeviceID_t *pDev, XMS_324_PARAM_TYPE ParamType)
{
	CDlgMixer MixerDlg;
	
	switch(ParamType)
	{
	case H324_PARAM_MIXER:	
		if(MixerDlg.DoModal() == IDOK)
		{
			MixerControlParam_t paramMixer;
			memset(&paramMixer, 0, sizeof(paramMixer));
			paramMixer.m_u8SRC1_Ctrl = MixerDlg.m_iSrcCtrl;
			paramMixer.m_u8SRC2_Ctrl = MixerDlg.m_iSrc2Ctrl;
			paramMixer.m_u16SRC_ChID1 = MixerDlg.m_uiSrcId;
			paramMixer.m_u16SRC_ChID2 = MixerDlg.m_uiSrc2Id;
			
			if(MixerDlg.m_bAudio)
			{
				paramMixer.m_u8Video = 0;
				SetParam(pDev, ParamType, sizeof(paramMixer), &paramMixer);
			}
			if(MixerDlg.m_bVideo)
			{
				paramMixer.m_u8Video = 1;
				SetParam(pDev, ParamType, sizeof(paramMixer), &paramMixer);
			}
		}
		break;
	case H324_PARAM_TCS:
		H324SetTCS(pDev);				
		break;
	default:
		break;
	}
}

void OnSetRtpxParam(DeviceID_t *pDev, int ParamType)
{
	CDlgRtpxParam RtpxDlg;
	CDlgMixer MixerDlg;
	CDlgAddr AddrDlg;
	
	switch(ParamType)
	{
	case XMS_RTPX_PARAM_INPUT:	
		if(RtpxDlg.DoModal() == IDOK)
		{
			CmdParamData_RTPXInput_t paramIn;
			memset(&paramIn, 0, sizeof(paramIn));
			paramIn.m_u8ChanEnable = RtpxDlg.m_bEnable;
			paramIn.m_u8MediaType = RtpxDlg.m_iDataType;
			paramIn.m_u8PayloadType = RtpxDlg.m_pt;
			
			SetParam(pDev, ParamType, sizeof(paramIn), &paramIn);
		}
		break;
	case XMS_RTPX_PARAM_OUTPUT:
		if(RtpxDlg.DoModal() == IDOK)
		{
			CmdParamData_RTPXOutput_t paramOut;
			memset(&paramOut, 0, sizeof(paramOut));
			paramOut.m_u8ChanEnable = RtpxDlg.m_bEnable;
			if(paramOut.m_u8ChanEnable != 0)
			{
				paramOut.m_u8MediaType = RtpxDlg.m_iDataType;
				paramOut.m_u8PayloadType = RtpxDlg.m_pt;

				if(MixerDlg.DoModal() == IDOK)
				{
					paramOut.m_u8SRC_Ctrl1 = MixerDlg.m_iSrcCtrl;
					paramOut.m_u16SRC_Id1 = MixerDlg.m_uiSrcId;
				}

				if(AddrDlg.DoModal() == IDOK)
				{
					 paramOut.m_u32RemoteIP = AddrDlg.m_uiIP;
					 paramOut.m_u16RemotePort = AddrDlg.m_Port;
				}
			}
			
			SetParam(pDev, ParamType, sizeof(paramOut), &paramOut);
		}
		break;
	case XMS_RTPX_PARAM_MIXER:
		if(MixerDlg.DoModal() == IDOK)
		{
			MixerControlParam_t paramMixer;
			memset(&paramMixer, 0, sizeof(paramMixer));
			paramMixer.m_u8SRC1_Ctrl = MixerDlg.m_iSrcCtrl;
			paramMixer.m_u16SRC_ChID1 = MixerDlg.m_uiSrcId;
			
			SetParam(pDev, ParamType, sizeof(paramMixer), &paramMixer);
		}
		break;
	case XMS_RTPX_PARAM_ADDR:
		if(AddrDlg.DoModal() == IDOK)
		{
			CmdParamData_RTPXAddr_t paramAddr;
			memset(&paramAddr, 0, sizeof(paramAddr));
			paramAddr.m_u32RemoteIP = AddrDlg.m_uiIP;
			paramAddr.m_u16RemotePort = AddrDlg.m_Port;
			
			SetParam(pDev, ParamType, sizeof(paramAddr), &paramAddr);
		}
		break;
	case XMS_RTPX_PARAM_INPUT_A:	
		if(RtpxDlg.DoModal() == IDOK)
		{
			CmdParamData_RTPXInput_A_t paramIn;
			memset(&paramIn, 0, sizeof(paramIn));
			paramIn.m_u8ChanEnable = RtpxDlg.m_bEnable;
			paramIn.m_u8MediaType = RtpxDlg.m_iDataType;
			paramIn.m_u8PayloadType = RtpxDlg.m_pt;
			paramIn.m_u8Decode = RtpxDlg.m_bTranscode;
			
			SetParam(pDev, ParamType, sizeof(paramIn), &paramIn);
		}
		break;
	case XMS_RTPX_PARAM_OUTPUT_A:
		if(RtpxDlg.DoModal() == IDOK)
		{
			CmdParamData_RTPXOutput_A_t paramOut;
			memset(&paramOut, 0, sizeof(paramOut));
			paramOut.m_u8ChanEnable = RtpxDlg.m_bEnable;
			if(paramOut.m_u8ChanEnable != 0)
			{
				paramOut.m_u8MediaType = RtpxDlg.m_iDataType;
				paramOut.m_u8PayloadType = RtpxDlg.m_pt;
				paramOut.m_u8Encode = RtpxDlg.m_bTranscode;
				
				if(MixerDlg.DoModal() == IDOK)
				{
					paramOut.m_u8SRC_Ctrl1 = MixerDlg.m_iSrcCtrl;
					paramOut.m_u16SRC_Id1 = MixerDlg.m_uiSrcId;
					paramOut.m_u8SRC_Ctrl2 = MixerDlg.m_iSrc2Ctrl;
					paramOut.m_u16SRC_Id2 = MixerDlg.m_uiSrc2Id;
				}
				
				if(AddrDlg.DoModal() == IDOK)
				{
					paramOut.m_u32RemoteIP = AddrDlg.m_uiIP;
					paramOut.m_u16RemotePort = AddrDlg.m_Port;
				}
			}
			
			SetParam(pDev, ParamType, sizeof(paramOut), &paramOut);
		}
		break;
	case XMS_RTPX_PARAM_MIXER_A:
		if(MixerDlg.DoModal() == IDOK)
		{
			MixerControlParam_t paramMixer;
			memset(&paramMixer, 0, sizeof(paramMixer));
			paramMixer.m_u8SRC1_Ctrl = MixerDlg.m_iSrcCtrl;
			paramMixer.m_u16SRC_ChID1 = MixerDlg.m_uiSrcId;
			
			SetParam(pDev, ParamType, sizeof(paramMixer), &paramMixer);
		}
		break;
	case XMS_RTPX_PARAM_ADDR_A:
		if(AddrDlg.DoModal() == IDOK)
		{
			CmdParamData_RTPXAddr_t paramAddr;
			memset(&paramAddr, 0, sizeof(paramAddr));
			paramAddr.m_u32RemoteIP = AddrDlg.m_uiIP;
			paramAddr.m_u16RemotePort = AddrDlg.m_Port;
			
			SetParam(pDev, ParamType, sizeof(paramAddr), &paramAddr);
		}
		break;
	default:
		break;
	}
}

int OnSetParam(DeviceID_t *pDev)
{
	if(pDev  == NULL)
		return 0;

	CDlgParamType dlg;
	dlg.m_iDevType = g_CurDisplayDevType;

	switch(pDev->m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
		if(dlg.DoModal() != IDOK)
			return 0;
		OnSetVoipParam(pDev, (XMS_VOIP_PARAM_TYPE)(dlg.m_iParamType));
		break;
	case XMS_DEVMAIN_VOICE:
		if(dlg.DoModal() != IDOK)
			return 0;
		if(pDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_324)
			OnSet324Param(pDev, (XMS_324_PARAM_TYPE)dlg.m_iParamType);
		break;
	case XMS_DEVMAIN_RTPX:
		if(dlg.DoModal() != IDOK)
			return 0;
		OnSetRtpxParam(pDev, dlg.m_iParamType);
		break;
	default:
		AfxMessageBox("Device not support set parameter\n");
		return 0;
	}

	return 1;
}

int OnSendIOData(DeviceID_t *pDev)
{
	CDlgIODataUII uiiDlg;
	H245_UII h245UII;	
	Acs_VoIP_RTPDTMF rtpDtmf = {0};
	int ret = 0;
	
	if(pDev == NULL)
		return 0;

	switch(pDev->m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOICE:
		if(pDev->m_s16DeviceSub != XMS_DEVSUB_MEDIA_324)
			break;
		
		if(uiiDlg.DoModal() != IDOK)
			break;
		memset(&h245UII, 0, sizeof(h245UII));
		h245UII.m_u8Type = uiiDlg.m_nUIIType + 1;
		h245UII.m_s8Signal = uiiDlg.m_sSignal.GetAt(0);
		sprintf(h245UII.str, uiiDlg.m_sAlphanumeric);
		ret = SendIOData(pDev, XMS_324_CMD_TYPE_UII, sizeof(h245UII), &h245UII);
		break;
	case XMS_DEVMAIN_VOIP:
		if(uiiDlg.DoModal() != IDOK)
			break;
		rtpDtmf.m_s8EventChar	= uiiDlg.m_sSignal.GetAt(0);				// rtp dtmf event char
		rtpDtmf.m_s8Volume		= -32;			// volume (in dbm0 from -63 to 0)
		rtpDtmf.m_u16Duration	= 1600;				// duration (in timestamp units)

		// send dtmf command
		ret = SendIOData(pDev, XMS_IO_TYPE_VOIP_RTPDTMF, sizeof(rtpDtmf), &rtpDtmf);

		break;
	default:
		AfxMessageBox("Device not support set parameter\n");
		break;
	}

	return 1;
}

int OnCall(DeviceID_t *pDev)
{
	Dev_Info *pDevInfo;
	CDlgSipCallParam SipCallDlg;
	int ret = 0;
	
	if(pDev == NULL)
		return 0;

	pDevInfo = M_DEVINFO(pDev);
	if(pDevInfo->Dev_State != DEV_STATE_FREE)
		return 0;
	
	switch(pDev->m_s16DeviceMain)
	{
	case XMS_DEVMAIN_INTERFACE_CH:
		if(pDev->m_s16DeviceSub == XMS_DEVSUB_E1_SS7_ISUP)
		{
			//set isup video call
			ISUP_spTransmissionMediumRequirement  SP_tmr;
			DJ_U16 Len = sizeof(SP_tmr);
			memset(&SP_tmr, 0, Len);	
			SP_tmr.m_u8TransmissionMediumRequirement = 2; 
			ret = SetParam(pDev,
				ISUP_SP_TransmissionMediumRequirement,
				Len,
				&SP_tmr
				);
			
			ISUP_spUserServiceInformation          SP_ui;
			Len = sizeof(SP_ui);
			memset(&SP_ui, 0, Len);
			SP_ui.m_u8USILen = 3;
			SP_ui.m_u8USInformation[0] = 0x88;
			SP_ui.m_u8USInformation[1] = 0x90;
			SP_ui.m_u8USInformation[2] = 0xA6;
			SetParam(pDev,
				ISUP_SP_UserServiceInformation,
				Len,
				&SP_ui
				);

			ISUP_spUserToUserInformation uui;
			Len = sizeof(uui);
			memset(&uui, 0, sizeof(uui));
			uui.m_u8UifLen = 25;
			SetParam(pDev,
				ISUP_SP_UserToUserInformation,
				Len,
				&uui
				);
		}
		if(XMS_ctsMakeCallOut(g_KeygoeVar.ACSHandle, pDev, "12345", g_KeygoeVar.cfg.callee, NULL) >= 0)
		{
			ChangeDevState(pDevInfo, DEV_STATE_WAITCONNECT);
			pDevInfo->User_Type = USER_3G;
			ret = 1;
		}
		break;
	case XMS_DEVMAIN_VOIP:
		if(SipCallDlg.DoModal() == IDOK)
		{
			VoIPCallPrivate_t paramVoIPCall = {0};
			paramVoIPCall.m_PrivateData.m_u32DataSize = sizeof(paramVoIPCall);
			paramVoIPCall.m_s32Protocol = XMS_VOIP_PROTOCOL_SIP;
			strcpy(paramVoIPCall.m_s8CallerAddress, SipCallDlg.m_sCallerAddr);
			paramVoIPCall.m_s32CallerPort = SipCallDlg.m_uiCallerPort;
			strcpy(paramVoIPCall.m_s8CallerUserID, SipCallDlg.m_sCallerName);
			strcpy(paramVoIPCall.m_s8CalleeAddress, SipCallDlg.m_sCalleeAddr);
			paramVoIPCall.m_s32CalleePort =SipCallDlg.m_uiCalleePort;
			strcpy(paramVoIPCall.m_s8CalleeUserID, SipCallDlg.m_sCalleeName);
			if(XMS_ctsMakeCallOut(g_KeygoeVar.ACSHandle,pDev, (char*)(LPCTSTR)(SipCallDlg.m_sCallerID), (char*)(LPCTSTR)SipCallDlg.m_sCalleeID, (PrivateData_t *)&paramVoIPCall) >= 0)
			{
				ChangeDevState(pDevInfo, DEV_STATE_WAITCONNECT);
				ret = 1;
			}
		}
		break;
	default:
		AfxMessageBox("Device not support set parameter\n");
		break;
	}

	return ret;
}

void ResetServConf(DeviceID_t *pDev);

int ClearCall(DeviceID_t *pDev)
{
	int ret = 0;
	
	if(pDev == NULL)
		return ret;
	
	switch(pDev->m_s16DeviceMain)
	{
	case XMS_DEVMAIN_INTERFACE_CH:
		if(XMS_ctsClearCall(g_KeygoeVar.ACSHandle, pDev, 0, NULL) >= 0)
			ret = 1;
		break;
	case XMS_DEVMAIN_VOIP:
		ResetServConf(pDev);	
		RefreshConfInfo();
		if(XMS_ctsClearCall(g_KeygoeVar.ACSHandle, pDev, 0, NULL) >= 0)
			ret = 1;
		break;
	case XMS_DEVMAIN_VOICE:
		if(pDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_324)
			ret = H324StopSession(pDev);
		break;
	default:
		AfxMessageBox("Device not support set parameter\n");
		break;
	}

	return ret;
}

int OnClearCall(DeviceID_t *pDev)
{
	return ClearCall(pDev);
}

int PlayToDev(DeviceID_t *pDev, char *sFileName, XMS_MEDIA_TYPE MediaType, unsigned int time, PrivateData_t * privateData, char *sOverlayImage = NULL)
{
	int ret = 0;
	Dev_Info *pDevInfo;
	Play3gppProperty_t playProperty;
	
	if(!pDev || !sFileName)
		return ret;

	pDevInfo = M_DEVINFO(pDev);
	memset(&playProperty, 0, sizeof(Play3gppProperty_t));
	playProperty.m_u8MediaType = MediaType;
	if(MediaType == MEDIA_TYPE_MEDIAEX_AUDIO ||
		MediaType == MEDIA_TYPE_MEDIAEX_VIDEO ||
		MediaType == MEDIA_TYPE_MEDIAEX_ANV)
	{
		if(privateData == NULL)
		{
			Acs_MediaEx_Play play;
			
			memset(&play, 0, sizeof(play));
			play.m_PrivateData.m_u32DataSize = sizeof(play);
			strcpy(play.m_s8SrcName, sFileName);
			play.m_u32Start = 0;
			if(time == 0)
				play.m_u8Loop = 0;
			else 
				play.m_u8Loop = 1;
			play.audio.m_u8Codec = VOIP_MEDIA_AUDIO_PCMU;
			play.video.m_u8Codec = pDevInfo->video.TxCodec;
			play.video.m_u16ResX = 176;
			play.video.m_u16ResY = 144;
			if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOIP)
			{
				play.video.m_u8Fps = 15;
				play.video.m_u16Kbps = 128;
			}
			else
			{
				play.video.m_u8Fps = 10;
				play.video.m_u16Kbps = 40;
			}
			if(sOverlayImage)
				strcpy(play.s8OverlayImage, sOverlayImage);

			return Play3GP(pDev, &playProperty, (PrivateData_t*)&play);
		}
		else
			return Play3GP(pDev, &playProperty, privateData);
	}
	else
	{
		if(pDevInfo->pPlayRecDev)
		{
			//set play property
			strcpy(playProperty.m_s8PlayContent, sFileName);
			strcpy(playProperty.m_s8VideoPlayContent, sFileName);
			playProperty.m_u8TaskID = (DJ_S8)GetTickCount();
			playProperty.m_u8VideoTaskID = playProperty.m_u8TaskID;   
			playProperty.m_u32MaxTime = time;
			playProperty.m_u32VideoMaxTime = time;
			
			if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE)
			{
				if(pDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_VOC)
				{
					//set voice output source
					CmdParamData_Voice_t VoiceParam = {0};
					VoiceParam.m_u8OutputCtrlValid = 1;
					VoiceParam.m_VocOutputControl.m_u16FixGain = 1024;
					VoiceParam.m_VocOutputControl.m_u8OutputType = XMS_VOC_OUTPUT_FROM_PLAY;
					SetParam(pDev, VOC_PARAM_UNIPARAM, sizeof(CmdParamData_Voice_t), &VoiceParam);
					
					ret = PlayVoc(pDev, sFileName, time, privateData);
				}
				else if(pDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_324)
				{
					MixerControlParam_t paramMixer;
					memset(&paramMixer, 0, sizeof(paramMixer));
					paramMixer.m_u8SRC1_Ctrl = XMS_MIXER_FROM_PLAY;
					paramMixer.m_u16SRC_ChID1 = pDevInfo->pPlayRecDev->m_s16ChannelID;
					paramMixer.m_u8Video = 0;
					SetParam(pDev, H324_PARAM_MIXER, sizeof(paramMixer), &paramMixer);
					paramMixer.m_u8Video = 1;
					SetParam(pDev, H324_PARAM_MIXER, sizeof(paramMixer), &paramMixer);
					
					ret = Play3GP(pDevInfo->pPlayRecDev, &playProperty, privateData);
				}
			}
			else if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOIP)
			{
				MixerControlParam_t paramMixer;
				memset(&paramMixer, 0, sizeof(paramMixer));
				paramMixer.m_u8SRC1_Ctrl = XMS_MIXER_FROM_PLAY;
				paramMixer.m_u8SRC2_Ctrl = XMS_MIXER_FROM_NULL;
				paramMixer.m_u16SRC_ChID1 = pDevInfo->pPlayRecDev->m_s16ChannelID;
				paramMixer.m_u16SRC_ChID2 = pDevInfo->pPlayRecDev->m_s16ChannelID;
				paramMixer.m_u8Video = 0;
				SetParam(pDev, VOIP_PARAM_RTPMIXER, sizeof(paramMixer), &paramMixer);
				paramMixer.m_u8Video = 1;
				SetParam(pDev, VOIP_PARAM_RTPMIXER, sizeof(paramMixer), &paramMixer);

				ret = Play3GP(pDevInfo->pPlayRecDev, &playProperty, privateData);
			}
		}
	}
	
	return ret;
}

int RecFromDev(DeviceID_t *pDev, DJ_S8 *sFileName, XMS_MEDIA_TYPE MediaType, PrivateData_t * privateData)
{
	int ret = 0;
	Record3gppProperty_t recordProperty;
	
	if(!pDev)
		return ret;

	memset(&recordProperty, 0, sizeof(Record3gppProperty_t));
	recordProperty.m_u8MediaType = MediaType;

	if(MediaType == MEDIA_TYPE_MEDIAEX_AUDIO ||
		MediaType == MEDIA_TYPE_MEDIAEX_VIDEO ||
		MediaType == MEDIA_TYPE_MEDIAEX_ANV)
	{
		return Record3GP(pDev, &recordProperty, privateData);
	}
	else
	{
		 if(!sFileName)
			 return ret;

		Dev_Info *pDevInfo;
		
		pDevInfo = M_DEVINFO(pDev);

		recordProperty.m_u8AudioSRCMode    = XMS_SRC_3GVIDEO;
		recordProperty.m_u8AudioTracks     = XMS_AUDIO_TRACKS_STEREO;
		recordProperty.m_s8AudioIsMixEnable = 1;
		recordProperty.m_u8AudioEncodeType = XMS_Amr_type;
		recordProperty.m_AudioMixerControl.m_u16SRC_ChID1 = pDev->m_s16ChannelID;
		if(pDevInfo->video.RxCodec == VOIP_MEDIA_VIDEO_H263)
			recordProperty.m_u8VideoEncodeType = XMS_VIDEO_CODE_TYPE_H263;
		else if(pDevInfo->video.RxCodec == VOIP_MEDIA_VIDEO_MPEG4)
			recordProperty.m_u8VideoEncodeType = XMS_VIDEO_CODE_TYPE_MP4V;
		else if(pDevInfo->video.RxCodec == VOIP_MEDIA_VIDEO_H264)
			recordProperty.m_u8VideoEncodeType = XMS_VIDEO_CODE_TYPE_H264;
		else
			return ret;
		recordProperty.m_s8VideoIsMixEnable = 1;
		recordProperty.m_VideoMixerControl.m_u16SRC_ChID1 = pDev->m_s16ChannelID;
		if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE)
		{
			recordProperty.m_AudioMixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_324;
			recordProperty.m_VideoMixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_324;
		}
		else if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOIP)
		{
			recordProperty.m_AudioMixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_IP;
			recordProperty.m_VideoMixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_IP;
		}
		strcpy(recordProperty.m_s8FileName, sFileName);
		return Record3GP(pDevInfo->pPlayRecDev, &recordProperty, NULL);
	}
}

int OnPlay(DeviceID_t *pDev)
{
	Dev_Info *pDevInfo;
	DJ_S8 sFileName[256];

	if(pDev == NULL)
		return 0;
	pDevInfo = M_DEVINFO(pDev);

	CDlgPlay playDlg;
	if(playDlg.DoModal() != IDOK)
		return 0;

	strcpy(sFileName, playDlg.m_sFile);

	if(pDevInfo->Dev.m_s16DeviceMain == XMS_DEVMAIN_VIDEOCONF)
	{
		Conf_Instance *pConfIns = NULL;
		if(pDevInfo->Dev_State == DEV_STATE_USED)
		{
			pConfIns = FindConf(pDev);
		}
		else
		{
			return 0;
		}
		
		if(pConfIns != NULL)
		{
			DeviceID_t *pDstDev;
			pDstDev = pConfIns->pVocConf;

			Acs_3GVConf_Play play;
			memset(&play, 0, sizeof(Acs_3GVConf_Play));
			play.m_PrivateData.m_u32DataSize = sizeof(Acs_3GVConf_Play);
			if(AfxMessageBox("Yes: enable audio, No: disable audio", MB_YESNO) == IDYES)
			{
				memcpy(&play.m_device, pDstDev, sizeof(DeviceID_t));
			}
			play.m_play.m_u32Start = 1;
			play.m_play.m_u8Loop = playDlg.m_bLoop;
			strcpy(play.m_play.m_s8SrcName, sFileName);

			Play3gppProperty_t paramPlay;
			memset(&paramPlay, 0, sizeof(Play3gppProperty_t));
			int iResult;
			if((iResult = XMS_cts3gppPlay(g_KeygoeVar.ACSHandle, pDev, &paramPlay, (PrivateData_t*)&play)) < 0)
				return 0;
			else
				return 1;
		}
	}

	if(playDlg.m_nPlayType == MEDIA_TYPE_MEDIAEX_AUDIO ||
		playDlg.m_nPlayType == MEDIA_TYPE_MEDIAEX_VIDEO ||
		playDlg.m_nPlayType == MEDIA_TYPE_MEDIAEX_ANV)
	{
		Acs_MediaEx_Play play;
			
		memset(&play, 0, sizeof(play));
		play.m_PrivateData.m_u32DataSize = sizeof(play);
		strcpy(play.m_s8SrcName, sFileName);
		play.m_u32Start = 0;
		play.m_u8Loop = playDlg.m_bLoop;
		play.audio.m_u8Codec = VOIP_MEDIA_AUDIO_PCMU;
		play.video.m_u8Codec = pDevInfo->video.TxCodec;
		play.video.m_u16ResX = playDlg.m_uiX;
		play.video.m_u16ResY = playDlg.m_uiY;
		play.video.m_u8Fps = playDlg.m_uiFps;
		play.video.m_u16Kbps = playDlg.m_uiBr;
		strcpy(play.s8OverlayImage, playDlg.m_sFileOverlay);
		PlayToDev(pDev, sFileName, (XMS_MEDIA_TYPE)playDlg.m_nPlayType, playDlg.m_bLoop, (PrivateData_t *)&play);
	}
	else
	{
		if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE)
		{
			if(pDev->m_s16DeviceSub ==XMS_DEVSUB_MEDIA_VOC)
			{
				MixerControlParam_t AudioMixer;
				memset(&AudioMixer, 0, sizeof(MixerControlParam_t));
				AudioMixer.m_u8SRC1_Ctrl = XMS_MIXER_FROM_INPUT;
				AudioMixer.m_u16SRC_ChID1 = pDev->m_s16ChannelID;
				return PlayVoc(pDev, sFileName, playDlg.m_uiTime, NULL);
			}
			else if(pDev->m_s16DeviceSub ==XMS_DEVSUB_MEDIA_324)
			{
				if(pDevInfo->pPlayRecDev == NULL)
					pDevInfo->pPlayRecDev = pDev;
				return PlayToDev(pDev, sFileName, (XMS_MEDIA_TYPE)playDlg.m_nPlayType, playDlg.m_uiTime, NULL);

			}
		}
		else if(pDev->m_s16DeviceMain ==  XMS_DEVMAIN_VOIP)
		{
			if(pDevInfo->pPlayRecDev == NULL)
			{
				//Get a free 324 device
				pDevInfo->pPlayRecDev = GetOneDev(pDev->m_s8ModuleID, XMS_DEVMAIN_VOICE, 
												XMS_DEVSUB_MEDIA_324, DEV_STATE_FREE);
			}
		
			if(pDevInfo->pPlayRecDev != NULL)
				return PlayToDev(pDev, sFileName, (XMS_MEDIA_TYPE)playDlg.m_nPlayType, playDlg.m_uiTime, NULL);
		}
	}

	return 0;
}

int OnRecord(DeviceID_t *pDev)
{
	Dev_Info *pDevInfo;
	char sFileName[256];
	
	if(pDev == NULL)
		return 0;
		
	CDlgRecord dlg;
	if(dlg.DoModal() != IDOK)
		return 0;

	strcpy(sFileName, dlg.m_sFile);
	
	pDevInfo = M_DEVINFO(pDev);

	if(pDevInfo->Dev.m_s16DeviceMain == XMS_DEVMAIN_VIDEOCONF)
	{
		Conf_Instance *pConfIns = NULL;
		if(pDevInfo->Dev_State == DEV_STATE_USED)
		{
			pConfIns = FindConf(pDev);
		}
		else
		{
			return 0;
		}

		if(pConfIns != NULL)
		{
			DeviceID_t *pDstDev;
			pDstDev = pConfIns->pVocConf;

			Acs_3GVConf_Record record;
			memset(&record, 0, sizeof(Acs_3GVConf_Record));
			record.m_PrivateData.m_u32DataSize = sizeof(Acs_3GVConf_Record);
			if(AfxMessageBox("Yes: enable audio, No: disable audio", MB_YESNO) == IDYES)
			{
				memcpy(&record.m_device, pDstDev, sizeof(DeviceID_t));
			}
			strcpy(record.m_record.m_s8DstName, sFileName);
			record.m_record.video.m_u8Codec = VOIP_MEDIA_VIDEO_H263;

			Record3gppProperty_t paramRecord;
			memset(&paramRecord, 0, sizeof(Record3gppProperty_t));
			if(XMS_cts3gppRecord(g_KeygoeVar.ACSHandle, pDev, &paramRecord, (PrivateData_t*)&record) < 0)
				return 0;
			else
				return 1;
		}

		return 0;
	}

	if(dlg.m_nRecType == MEDIA_TYPE_MEDIAEX_AUDIO ||
		dlg.m_nRecType == MEDIA_TYPE_MEDIAEX_VIDEO ||
		dlg.m_nRecType == MEDIA_TYPE_MEDIAEX_ANV)
	{
		Acs_MediaEx_Record rec;
			
		memset(&rec, 0, sizeof(rec));
		rec.m_PrivateData.m_u32DataSize = sizeof(rec);
		strcpy(rec.m_s8DstName, sFileName);
		rec.audio.m_u8Codec = VOIP_MEDIA_AUDIO_PCMU;
		rec.video.m_u8Codec = pDevInfo->video.RxCodec;
		rec.video.m_u16ResX = dlg.m_uiX;
		rec.video.m_u16ResY = dlg.m_uiY;
		rec.video.m_u8Fps = dlg.m_uiFps;
		rec.video.m_u16Kbps = dlg.m_uiBR;
		return	RecFromDev(pDev, sFileName, (XMS_MEDIA_TYPE)dlg.m_nRecType, (PrivateData_t *)&rec);
	}
	else
	{
		if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE)
		{
			if(pDev->m_s16DeviceSub ==XMS_DEVSUB_MEDIA_VOC)
			{
				MixerControlParam_t AudioMixer;
				memset(&AudioMixer, 0, sizeof(MixerControlParam_t));
				AudioMixer.m_u8SRC1_Ctrl = XMS_MIXER_FROM_INPUT;
				AudioMixer.m_u16SRC_ChID1 = pDev->m_s16ChannelID;
				return RecordVoc(pDev, sFileName, &AudioMixer, 0, false);
			}
			else if(pDev->m_s16DeviceSub ==XMS_DEVSUB_MEDIA_324)
			{
				if(pDevInfo->pPlayRecDev != NULL)
					return RecFromDev(pDev, sFileName, (XMS_MEDIA_TYPE)dlg.m_nRecType, NULL);
				else
				{
					pDevInfo->pPlayRecDev = pDev;
					return RecFromDev(pDev, sFileName, (XMS_MEDIA_TYPE)dlg.m_nRecType, NULL);
				}
			}
		}
		else if(pDev->m_s16DeviceMain ==  XMS_DEVMAIN_VOIP)
		{
			if(pDevInfo->pPlayRecDev == NULL)
			{
				//Get a free 324 device
				pDevInfo->pPlayRecDev = GetOneDev(pDev->m_s8ModuleID, XMS_DEVMAIN_VOICE, 
												XMS_DEVSUB_MEDIA_324, DEV_STATE_FREE);
			}
		
			if(pDevInfo->pPlayRecDev != NULL)
				return RecFromDev(pDev, sFileName, (XMS_MEDIA_TYPE)dlg.m_nRecType, NULL);
		}
	}
	
	return 0;
}

int OnStopPlay(DeviceID_t *pDev)
{
	int ret = -0;
//	Dev_Info *pDevInfo;

	if(pDev == NULL)
		return ret;

	ret = StopPlay(pDev);

	return ret;
}

int OnStopRecord(DeviceID_t *pDev)
{
	int ret = -0;
//	Dev_Info *pDevInfo;
	
	if(pDev == NULL)
		return ret;


	ret = StopRecord(pDev);
	
	return ret;
}

int OnGetFileInfo(DeviceID_t *pDev)
{
    CFileDialog filedlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,     
		"All files(*.*)|*.*||", NULL); 
	
	if(filedlg.DoModal() == IDOK)
	{      
        char sFileName[256];

        strcpy(sFileName, filedlg.GetPathName());
        return H324GetMediaFilePara(pDev, sFileName);
	}
    
}

int JoinVocConf(DeviceID_t *pConfDevID, DeviceID_t *pVocDevID, int iMode);
int LeaveVocConf(DeviceID_t *pConfDevID, DeviceID_t *pVocDevID, int iMode);

int OnLinkDev(DeviceID_t *pDev)
{
	CDlgLinkDev dlg;
	DeviceID_t *pDstDev;
	Acs_Video_Link_Param LinkParam;

	if(!pDev)
		return 0;

	if(dlg.DoModal() != IDOK)
		return 0;
	
	pDstDev = &g_DevInfo[dlg.m_uiUnit][dlg.m_iDestType][dlg.m_uiDestID].Dev;

	memset(&LinkParam, 0, sizeof(LinkParam));
	LinkParam.m_PrivateData.m_u32DataSize = sizeof(LinkParam);
	if(((pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE && pDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_324) || pDev->m_s16DeviceMain == XMS_DEVMAIN_VOIP) &&
		((pDstDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE && pDstDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_324) || pDstDev->m_s16DeviceMain == XMS_DEVMAIN_VOIP))
	{
		Dev_Info *pDevInfo;
		pDevInfo = M_DEVINFO(pDev);
		LinkParam.m_u8SrcCodec = pDevInfo->video.RxCodec;
        if(pDevInfo->decoderConfigLength > 0)
        {
            char str[256];
            
            sprintf(str, "link len = %d", pDevInfo->decoderConfigLength);
            AddMsg(str);
            LinkParam.decoderConfigLength = pDevInfo->decoderConfigLength;
            memcpy(LinkParam.decoderConfigInfo, pDevInfo->decoderConfigInfo, pDevInfo->decoderConfigLength);
        }
		pDevInfo = M_DEVINFO(pDstDev);
		LinkParam.m_u8DstCodec = pDevInfo->video.TxCodec;
		strcpy(LinkParam.s8OverlayImage, dlg.m_sOverlayFile);

		if(pDstDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE &&
			(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOIP ||
			LinkParam.m_u8SrcCodec != LinkParam.m_u8DstCodec ||
			strlen(LinkParam.s8OverlayImage) > 0))
		{
			//limit the bitrate for 3G-324M user
			LinkParam.m_u8Fps = 10;
			LinkParam.m_u16Kbps = 40;
		}        
	}

	if(XMS_ctsLinkDevice(g_KeygoeVar.ACSHandle, pDev, pDstDev, (PrivateData_t*)&LinkParam) < 0)
	{
		AddMsg("Link failed!");
		return 0;
	}

	return 1;
}

int OnUnlinkDev(DeviceID_t *pDev)
{
	CDlgLinkDev dlg;
	DeviceID_t *pDstDev;
	
	if(!pDev)
		return 0;
	
	dlg.m_iType = 1;
	if(dlg.DoModal() != IDOK)
		return 0;
	
	pDstDev = &g_DevInfo[dlg.m_uiUnit][dlg.m_iDestType][dlg.m_uiDestID].Dev;

	if(XMS_ctsUnlinkDevice(g_KeygoeVar.ACSHandle, pDev, pDstDev, NULL) < 0)
	{
		AddMsg("UnLink failed!");
		return 0;
	}
	return 1;
}

int OnResetDev(DeviceID_t *pDev)
{
	if(pDev == NULL)
		return 0;

	if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE &&
		pDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_324)
	{
		Dev_Info *pDevInfo = M_DEVINFO(pDev);
		if(pDevInfo->Dev_State == DEV_STATE_CONNECT)
		{
			H324ResetSession(pDev);
			return 1;
		}
	}
	
	ResetDev(pDev);
	
	return 1;
}

/************************************************************************/
/* Video Conf Operators                                                 */
/* start                                                                */
/************************************************************************/
int OnJoinConf(DeviceID_t *pDev)
{
	CDlgLinkDev dlg;
	DeviceID_t *pDstDev;

	if(!pDev)
		return 0;

	if(dlg.DoModal() != IDOK)
		return 0;

	Dev_Info *pDevInfo = M_DEVINFO(pDev);

	DJ_U8 iVisible = 0;
	if(AfxMessageBox("Yes: Visible No: Invisible", MB_YESNO) == IDYES)
	{
		iVisible = 1;
	}

	int iSum = atoi(dlg.m_sOverlayFile);
	if(iSum <= 0)
	{
		iSum = 1;
	}

	for(int iIndex = 0; iIndex <iSum; ++iIndex)
	{
		UINT uiDestID = dlg.m_uiDestID + iIndex;
		if(uiDestID >= MAX_DEV)
		{
			break;
		}

		pDstDev = &g_DevInfo[dlg.m_uiUnit][dlg.m_iDestType][uiDestID].Dev;

		Conf_Instance *pConfIns = NULL;
		if(pDevInfo->Dev_State == DEV_STATE_FREE)
		{
			pConfIns = CreateConf(-1, GetOneDev(0, XMS_DEVMAIN_CONFERENCE, 0, DEV_STATE_FREE), pDev);
		}
		else
		{
			pConfIns = FindConf(pDev);
		}
		if(pConfIns != NULL)
		{
			JoinConf(pConfIns, pDstDev, iVisible);
			ChangeDevState(pDevInfo, DEV_STATE_USED);
		}
	}

	RefreshConfInfo();

	return 1;
}

int OnLeaveConf(DeviceID_t *pDev)
{
	CDlgLinkDev dlg;
	DeviceID_t *pDstDev;

	if(!pDev)
		return 0;
	
	if(dlg.DoModal() != IDOK)
		return 0;

	int iSum = atoi(dlg.m_sOverlayFile);
	if(iSum <= 0)
	{
		iSum = 1;
	}
	
	Conf_Instance *pConfIns = FindConf(pDev);

	for(int iIndex = 0; iIndex <iSum; ++iIndex)
	{
		UINT uiDestID = dlg.m_uiDestID + iIndex;
		if(uiDestID >= MAX_DEV)
		{
			break;
		}

		pDstDev = &g_DevInfo[dlg.m_uiUnit][dlg.m_iDestType][uiDestID].Dev;

		if(pConfIns != NULL)
		{
			LeaveConf(pConfIns, pDstDev, 0, 0);
		}
	}

	RefreshConfInfo();
	
	return 1;
}

int OnClearConf(DeviceID_t *pDev)
{
	if(!pDev)
		return 0;

	Conf_Instance *pConfIns = FindConf(pDev);
	if(pConfIns != NULL)
	{
		DestroyConf(pConfIns->id, NULL);
	}

	RefreshConfInfo();

	return 1;
}

int OnRestartConf(DeviceID_t *pDev)
{
	if(!pDev)
		return 0;
	
	if(XMS_ctsRestart3GVConf(g_KeygoeVar.ACSHandle, pDev, NULL) < 0)
	{
		return 0;
	}

	return 1;
}

int OnPlayConf(DeviceID_t *pDev)
{
	return OnPlay(pDev);
}

int OnRecordConf(DeviceID_t *pDev)
{
	return OnRecord(pDev);
}

int OnGetLayout(DeviceID_t *pDev)
{
	if(!pDev)
		return 0;
	
	if(XMS_ctsGetLayout(g_KeygoeVar.ACSHandle, pDev, NULL) < 0)
	{
		return 0;
	}

	return 1;
}

int OnSetLayout(DeviceID_t *pDev)
{
	if(!pDev)
		return 0;
	
	DeviceID_t curDev;
	for(int j = 0; j < 16; ++j)
	{
		if(g_layoutList.m_device[j].m_s16DeviceMain == 0)
		{
			break;
		}
	}
	for(int i = 0; i < j/2 && j >= 2; ++i)
	{
		curDev = g_layoutList.m_device[i];
		g_layoutList.m_device[i] = g_layoutList.m_device[j-1-i];
		g_layoutList.m_device[j-1-i] = curDev;
	}

	if(XMS_ctsSetLayout(g_KeygoeVar.ACSHandle, pDev, &g_layoutList, NULL) < 0)
	{
		//return 0;
	}

	return 1;
}

int OnGetVisibleList(DeviceID_t *pDev)
{
	if(!pDev)
		return 0;
	
	if(XMS_ctsGetVisibleList(g_KeygoeVar.ACSHandle, pDev, NULL) < 0)
	{
		return 0;
	}

	return 1;
}

int OnSetVisibleList(DeviceID_t *pDev)
{
	CDlgLinkDev dlg;
	DeviceID_t *pDstDev;

	if(dlg.DoModal() != IDOK)
		return 0;
	
	pDstDev = &g_DevInfo[dlg.m_uiUnit][dlg.m_iDestType][dlg.m_uiDestID].Dev;

	memcpy(&g_visibleList.m_device[0], pDstDev, sizeof(DeviceID_t));

	if(XMS_ctsSetVisibleList(g_KeygoeVar.ACSHandle, pDev, &g_visibleList, NULL) < 0)
	{
		//return 0;
	}

	return 1;
}

int OnTimerFor3GVConf()
{
	int iRandomType = (rand()%100)/20;
	TRACE("iRandomType %d\n", iRandomType);

	switch(iRandomType)
	{
	case 0:	// leave -> join
		{
			if(g_ConfList != NULL)
			{
				Conf_Node *confNode = g_ConfList;
				do
				{
					User_Node *userNode = confNode->conf.MemberList;
//					do
//					{
						DeviceID_t *pDev = userNode->user.pDev;
						LeaveConf(&confNode->conf, pDev, 0, 0);
						Sleep(1000);
						JoinConf(&confNode->conf, pDev);
						Sleep(1000);
//					}
//					while((userNode = userNode->next) != NULL);
				}
				while((confNode = confNode->next) != NULL);
			}
		}
		break;

	case 1:	// restart
		{
			if(g_ConfList != NULL)
			{
				Conf_Node *confNode = g_ConfList;
				do
				{
					OnRestartConf(confNode->conf.pVideoConf);
					Sleep(1000);
				}
				while((confNode = confNode->next) != NULL);
			}
		}
		break;

	case 2:	// getlayout -> setlayout
		{
			if(g_ConfList != NULL)
			{
				Conf_Node *confNode = g_ConfList;
				do
				{
					OnGetLayout(confNode->conf.pVideoConf);
					Sleep(1000);
					OnSetLayout(confNode->conf.pVideoConf);
					Sleep(1000);
				}
				while((confNode = confNode->next) != NULL);
			}
		}
		break;

	case 3:	// play
		{
			if(g_ConfList != NULL)
			{
				Conf_Node *confNode = g_ConfList;
				do
				{
					DeviceID_t *pDev = confNode->conf.pVideoConf;
					
					// stop play
					StopPlay(pDev);
					Sleep(1000);
					
					// strat play
					DeviceID_t *pDstDev = confNode->conf.pVocConf;

					Acs_3GVConf_Play play;
					memset(&play, 0, sizeof(Acs_3GVConf_Play));
					play.m_PrivateData.m_u32DataSize = sizeof(Acs_3GVConf_Play);
					memcpy(&play.m_device, pDstDev, sizeof(DeviceID_t));
					play.m_play.m_u32Start = 1;
					play.m_play.m_u8Loop = 1;
					strcpy(play.m_play.m_s8SrcName, "C:\\DJKeygoe\\Samples\\Voc\\advertisement(QCIF-200K-MPEG4-12K-AMR).3gp");

					Play3gppProperty_t paramPlay;
					memset(&paramPlay, 0, sizeof(Play3gppProperty_t));
					int iResult = XMS_cts3gppPlay(g_KeygoeVar.ACSHandle, pDev, &paramPlay, (PrivateData_t*)&play);
					Sleep(1000);
				}
				while((confNode = confNode->next) != NULL);
			}
		}
		break;

	case 4:	// record
		{
			if(g_ConfList != NULL)
			{
				Conf_Node *confNode = g_ConfList;
				int iIndex = 1;
				do
				{
					DeviceID_t *pDev = confNode->conf.pVideoConf;
					
					// stop record
					StopRecord(pDev);
					Sleep(1000);

					// strat record
					DeviceID_t *pDstDev = confNode->conf.pVocConf;

					Acs_3GVConf_Record record;
					memset(&record, 0, sizeof(Acs_3GVConf_Record));
					record.m_PrivateData.m_u32DataSize = sizeof(Acs_3GVConf_Record);
					memcpy(&record.m_device, pDstDev, sizeof(DeviceID_t));

					sprintf(record.m_record.m_s8DstName, "C:\\DJKeygoe\\Samples\\Voc\\%d.avi", iIndex++);
					record.m_record.video.m_u8Codec = VOIP_MEDIA_VIDEO_MPEG4;

					Record3gppProperty_t paramRecord;
					memset(&paramRecord, 0, sizeof(Record3gppProperty_t));
					int iResult = XMS_cts3gppRecord(g_KeygoeVar.ACSHandle, pDev, &paramRecord, (PrivateData_t*)&record);
					Sleep(1000);
				}
				while((confNode = confNode->next) != NULL);
			}
		}
		break;

	default:
		break;
	}

	return 1;
}
/************************************************************************/
/* end                                                                  */
/************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////////
//conference service

int DestroyConf(int ConfID, DeviceID_t *pDev);

int JoinVocConf(DeviceID_t *pConfDevID, DeviceID_t *pVocDevID, int iMode)
{
	CmdParamData_Conf_t		confParam;

	if(pConfDevID == NULL || pVocDevID == NULL)
		return 0;
	
	switch ( iMode )
	{
	case CONF_MODE_ADD:			// add
		confParam.m_u8InputOpt = XMS_CONF_INPUT_OPT_NORMAL;
		confParam.m_u8OutputOpt = XMS_CONF_OUTPUT_OPT_NORMAL;
		break;
		
	case CONF_MODE_LISTEN:		// listen
		confParam.m_u8InputOpt = XMS_CONF_INPUT_OPT_SILENCE;
		confParam.m_u8OutputOpt = XMS_CONF_OUTPUT_OPT_SUM;
		break;
		
	case CONF_MODE_SPEAKONLY:	// Speak Only
		confParam.m_u8InputOpt = XMS_CONF_INPUT_OPT_NORMAL;
		confParam.m_u8OutputOpt = XMS_CONF_OUTPUT_OPT_SILENCE;
		break;
		
	case CONF_MODE_PLAY:		// Play
		confParam.m_u8InputOpt = XMS_CONF_INPUT_OPT_PLAY;
		confParam.m_u8OutputOpt = XMS_CONF_OUTPUT_OPT_SILENCE;
		break;
	default:
		return 0;
	}
	
	if(XMS_ctsJoinToConf(g_KeygoeVar.ACSHandle, pConfDevID, pVocDevID, &confParam, NULL) < 0)
		return 0;

	char msg[256];
	sprintf(msg, "%s (%d-%d) join voice conf (%d-%d)", GetDevTypeName(pVocDevID->m_s16DeviceMain), 
		pVocDevID->m_s8ModuleID, pVocDevID->m_s16ChannelID, 
		pConfDevID->m_s8ModuleID, pConfDevID->m_s16ChannelID);
	AddMsg(msg);
	
	return	1;
}

int LeaveVocConf(DeviceID_t *pConfDevID, DeviceID_t *pVocDevID, int iMode)
{
	CmdParamData_Conf_t		confParam;

	if(pConfDevID == NULL || pVocDevID == NULL)
		return 0;

	if ( iMode != CONF_MODE_PLAY )
		confParam.m_u8InputOpt = XMS_CONF_INPUT_OPT_NORMAL;
	else
		confParam.m_u8InputOpt = XMS_CONF_INPUT_OPT_PLAY;
	
	// confParam.m_u8OutputOpt // don't care
	
	if(XMS_ctsLeaveFromConf(g_KeygoeVar.ACSHandle, pConfDevID, pVocDevID, &confParam, NULL) < 0)
		return 0;

	char msg[256];
	sprintf(msg, "%s (%d-%d) leave voice conf (%d-%d)", GetDevTypeName(pVocDevID->m_s16DeviceMain), 
		pVocDevID->m_s8ModuleID, pVocDevID->m_s16ChannelID, 
		pConfDevID->m_s8ModuleID, pConfDevID->m_s16ChannelID);
	AddMsg(msg);
	
	return	1;
} 

int JoinVideoConf(DeviceID_t *pConfDevID, DeviceID_t *pDev, int isVisible)
{
	Acs_MediaEx_Input_V input;
	Acs_MediaEx_Output_V output;
	
	memset(&input, 0, sizeof(input));
	input.m_u8Codec = M_DEVINFO(pDev)->video.RxCodec;
    if(M_DEVINFO(pDev)->decoderConfigLength > 0 &&
        M_DEVINFO(pDev)->decoderConfigLength <= MAX_DECODER_CFG_INFO)
    {
        input.decoderConfigLength = M_DEVINFO(pDev)->decoderConfigLength;
        memcpy(input.decoderConfigInfo, M_DEVINFO(pDev)->decoderConfigInfo, 
                M_DEVINFO(pDev)->decoderConfigLength);
    }

	memset(&output, 0, sizeof(output));
	output.m_u8Codec = M_DEVINFO(pDev)->video.TxCodec;

	if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE)
	{
		output.m_u8Fps = 10;
		output.m_u16Kbps = 40;
	}
	else if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOIP)
	{
		output.m_u8Fps = 15;
		output.m_u16Kbps = 128;
	}
	
	if(XMS_ctsJoinTo3GVConf(g_KeygoeVar.ACSHandle,  pConfDevID, 
		pDev, &input, &output, isVisible, NULL) < 0)
	{
		char msg[256];
		sprintf(msg, "%s (%d-%d) join video conf (%d-%d) failed!", GetDevTypeName(pDev->m_s16DeviceMain), 
			pDev->m_s8ModuleID, pDev->m_s16ChannelID, 
			pConfDevID->m_s8ModuleID, pConfDevID->m_s16ChannelID);
		AddMsg(msg);
	}
	else
	{
		char msg[256];
		sprintf(msg, "%s (%d-%d) join video conf (%d-%d)", GetDevTypeName(pDev->m_s16DeviceMain), 
			pDev->m_s8ModuleID, pDev->m_s16ChannelID, 
			pConfDevID->m_s8ModuleID, pConfDevID->m_s16ChannelID);
		AddMsg(msg);
	}
	
	return	1;
}

int LeaveVideoConf(DeviceID_t *pConfDevID, DeviceID_t *pDev)
{	
	if(XMS_ctsLeaveFrom3GVConf(g_KeygoeVar.ACSHandle,  pConfDevID, 
		pDev, NULL) < 0)
	{
		char msg[256];
		sprintf(msg, "%s (%d-%d) leave video conf (%d-%d) failed!", GetDevTypeName(pDev->m_s16DeviceMain), 
			pDev->m_s8ModuleID, pDev->m_s16ChannelID, 
			pConfDevID->m_s8ModuleID, pConfDevID->m_s16ChannelID);
		AddMsg(msg);
	}
	else
	{
		char msg[256];
		sprintf(msg, "%s (%d-%d) leave video conf (%d-%d)", GetDevTypeName(pDev->m_s16DeviceMain), 
			pDev->m_s8ModuleID, pDev->m_s16ChannelID, 
			pConfDevID->m_s8ModuleID, pConfDevID->m_s16ChannelID);
		AddMsg(msg);
	}
	
	return	1;
}

Conf_Instance* CreateConf(int id, DeviceID_t *pVocConf, DeviceID_t *pVideoConf)
{
	Conf_Node *pNode1, *pNode2;
	
	if(pVocConf == NULL || pVideoConf == NULL)
		return NULL;

	if(id != -1)
	{
		pNode1 = g_ConfList;
		while(pNode1)
		{
			if(pNode1->conf.id == id)
				break;
			pNode1 = pNode1->next;
		}

		if(pNode1) //conference id is in using
			return NULL;
	}	
	else
		id = (pVideoConf->m_s8ModuleID-1)*30 + pVideoConf->m_s16ChannelID;

	//alloc memery
	if((pNode1 = (Conf_Node*)malloc(sizeof(Conf_Node))) == NULL)
	{
		Dev_Info *pDevInfo = M_DEVINFO(pVocConf);
		ChangeDevState(pDevInfo, DEV_STATE_FREE);
		pDevInfo = M_DEVINFO(pVideoConf);
		ChangeDevState(pDevInfo, DEV_STATE_FREE);
		return NULL;
	}
	
	pNode1->conf.id = id;
	sprintf(pNode1->conf.name, "(%d-%d, %d-%d)", pVocConf->m_s8ModuleID, pVocConf->m_s16ChannelID, pVideoConf->m_s8ModuleID, pVideoConf->m_s16ChannelID);
	pNode1->conf.MemberList = NULL;
	pNode1->conf.pVocConf = pVocConf;
	pNode1->conf.pVideoConf = pVideoConf;
	pNode1->next = NULL;
	
	if(g_ConfList == NULL)
	{
		g_ConfList = pNode1;
	}
	else
	{
		pNode2 = g_ConfList;
		while(pNode2->next != NULL)
			pNode2 = pNode2->next;
		pNode2->next = pNode1;
	}

	return &pNode1->conf;
}

Conf_Instance* FindConf(DeviceID_t *pDev)
{
	Conf_Node *pNode;

	//search the conferece
	pNode = g_ConfList;
	while(pNode != NULL)
	{
		if(IsSameDev(pNode->conf.pVideoConf, pDev))
			break;
		pNode = pNode->next;
	}

	if(pNode == NULL)
		return NULL;			//conference is not exist

	return &pNode->conf;
}

int JoinConf(Conf_Instance *pConf, DeviceID_t *pDev, DJ_U8 visible)
{
	int ret = 0;
	User_Node *pMember, *pNode;
	Dev_Info *pDevInfo;
	
	if(pConf == NULL || pDev == NULL)
		return 0;

	if(pDev->m_s16DeviceMain != XMS_DEVMAIN_VOICE &&
		pDev->m_s16DeviceMain != XMS_DEVMAIN_VOIP)
		return 0;

	pDevInfo = M_DEVINFO(pDev);
	
	if(pConf->pVocConf->m_s8ModuleID == pDev->m_s8ModuleID)
	{
		if(pDevInfo->pVoiceLinkDev1 != NULL)
		{
			ReleaseDev(pDevInfo->pVoiceLinkDev1);
			pDevInfo->pVoiceLinkDev1 = NULL;
		}
		if(pDevInfo->pVoiceLinkDev2 != NULL)
		{
			if(!IsSameDev(pDevInfo->pVoiceLinkDev2, pDev))
				ChangeDevState(M_DEVINFO(pDevInfo->pVoiceLinkDev2), DEV_STATE_FREE);
			pDevInfo->pVoiceLinkDev2 = NULL;
		}
		pDevInfo->pVoiceLinkDev2 = pDev;
	}
	else
	{
		if(pDevInfo->pVoiceLinkDev1 == NULL)
			if((pDevInfo->pVoiceLinkDev1 = GetOneDev(pDev->m_s8ModuleID, XMS_DEVMAIN_VOICE, XMS_DEVSUB_MEDIA_VOC, DEV_STATE_FREE)) == NULL)
				return 0;
		if(pDevInfo->pVoiceLinkDev2 == NULL || IsSameDev(pDevInfo->pVoiceLinkDev2, pDev))
			if((pDevInfo->pVoiceLinkDev2 = GetOneDev(pConf->pVocConf->m_s8ModuleID, XMS_DEVMAIN_VOICE, XMS_DEVSUB_MEDIA_VOC, DEV_STATE_FREE)) == NULL)
				return 0;
	}
	
	if((pMember = (User_Node*)malloc(sizeof(User_Node))) == NULL)
	{
		return 0;
	}

	pMember->user.pDev = pDev;
	pMember->next = NULL;

	if(pConf->MemberList == NULL)
		pConf->MemberList = pMember;
	else
	{
		pNode = pConf->MemberList;
		while(pNode->next != NULL)
			pNode = pNode->next;
		pNode->next = pMember;
	}

	//name
	if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE)
	{
		if(pDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_VOC)
		{
			sprintf(pMember->user.name, "VOC(%d, %d)", pDev->m_s8ModuleID, pDev->m_s16ChannelID);
		}
		else if(pDev->m_s16DeviceSub = XMS_DEVSUB_MEDIA_324)
		{
			sprintf(pMember->user.name, "3G(%d, %d)", pDev->m_s8ModuleID, pDev->m_s16ChannelID);
		}
	}
	else if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOIP)
	{
		sprintf(pMember->user.name, "IP(%d, %d)", pDev->m_s8ModuleID, pDev->m_s16ChannelID);
	}

	//voice link
	if(!IsSameDev(pDevInfo->pVoiceLinkDev2, pDev)) 
	{
		SetParamVoiceMixer(pDev, pDevInfo->pVoiceLinkDev1, NULL);
		SetParamVoiceMixer(pDevInfo->pVoiceLinkDev1, pDev, NULL);
		DualLinkDev(pDevInfo->pVoiceLinkDev1, pDevInfo->pVoiceLinkDev2);
	}
	
	//voice join conference
	JoinVocConf(pConf->pVocConf, pDevInfo->pVoiceLinkDev2, CONF_MODE_ADD);
	
	//join video conference
	JoinVideoConf(pConf->pVideoConf, pDev, visible);
		
	pDevInfo->pConf = pConf;
	
	return 1;
}

int JoinConf(int ConfID, DeviceID_t *pDev)
{
	Conf_Node *pNode;

	//search the conferece
	pNode = g_ConfList;
	while(pNode != NULL)
	{
		if(pNode->conf.id == ConfID)
			break;
		pNode = pNode->next;
	}

	if(pNode == NULL)
		return 0;			//conference is not exist

	return JoinConf(&pNode->conf, pDev);
}

int LeaveConf(Conf_Instance *pConf, DeviceID_t *pDev, int destroyFlag, int restartFlag)
{
	Conf_Node *pConfNode;
	User_Node *pMemberNode, *pTmpNode;
	Dev_Info *pDevInfo;
	int creator = 0, ConfId;

	if(pConf == NULL)
	{
		//search conference
		pConfNode = g_ConfList;
		while(pConf==NULL && pConfNode != NULL)
		{
			pMemberNode = pConfNode->conf.MemberList;	
			while(pMemberNode != NULL)
			{
				if(IsSameDev(pMemberNode->user.pDev, pDev))
				{
					pConf = &pConfNode->conf;	//find the conference
					break;
				}
				pMemberNode = pMemberNode->next;
			}
			if(pMemberNode != NULL)
				break;
			pConfNode = pConfNode->next;
		}
	}

	if(pConf == NULL)
		return 0;

	pDevInfo = M_DEVINFO(pDev);
	ConfId = pConf->id;
	
	if(destroyFlag && pConf->MemberList != NULL && IsSameDev(pConf->MemberList->user.pDev, pDev))//the creator leave, destroy the conference
	{
		DestroyConf(pConf->id, pDev);
		char str[32];
		sprintf(str, "Conference %d destroyed!", ConfId);
		AddMsg(str);
	}
	else
	{
		pMemberNode = pConf->MemberList;
		pTmpNode = NULL;
		while(pMemberNode != NULL)
		{		
			if(IsSameDev(pMemberNode->user.pDev, pDev))
			{
				if(pTmpNode != NULL)
					pTmpNode->next = pMemberNode->next;
				else
					pConf->MemberList = pMemberNode->next;
			}
			pTmpNode = pMemberNode;
			pMemberNode = pTmpNode->next;
		}
		
		LeaveVocConf(pConf->pVocConf, pDevInfo->pVoiceLinkDev2, CONF_MODE_ADD);
		LeaveVideoConf(pConf->pVideoConf, pDev);
		
		DualUnlinkDev(pDevInfo->pVoiceLinkDev1, pDevInfo->pVoiceLinkDev2);
		if(pDevInfo->pVoiceLinkDev1 != NULL)
		{
			ChangeDevState(M_DEVINFO(pDevInfo->pVoiceLinkDev1), DEV_STATE_FREE);
			pDevInfo->pVoiceLinkDev1 = NULL;
		}
		if(pDevInfo->pVoiceLinkDev2 != NULL)
		{
			if(!IsSameDev(pDevInfo->pVoiceLinkDev2, pDev))
				ChangeDevState(M_DEVINFO(pDevInfo->pVoiceLinkDev2), DEV_STATE_FREE);
			pDevInfo->pVoiceLinkDev2 = NULL;
		}

		pDevInfo->pConf = NULL;
		ChangeDevState(pDevInfo, DEV_STATE_CONNECT);
	}
	
	return ConfId;
}

int ClearConf(Conf_Instance *pConf)
{	
	if(pConf == NULL)
		return 0;
		
	//all member leave
	while(pConf->MemberList != NULL)
	{
		LeaveConf(pConf, pConf->MemberList->user.pDev, 0, 0);
	}
	
	return 1;
}

int DestroyConf(int ConfID, DeviceID_t *pDev)
{
	Conf_Node *pNode1, *pNode2;

	//search the conferece
	pNode1 = g_ConfList;
	pNode2 = NULL;
	while(pNode1 != NULL)
	{
		if(pNode1->conf.id == ConfID)
			break;
		pNode2 = pNode1;
		pNode1 = pNode1->next;
	}

	if(pNode1 == NULL)
		return 0;			//conference is not exist
			
	if(ClearConf(&pNode1->conf) > 0)
	{
		//release device
		XMS_ctsClearConf(g_KeygoeVar.ACSHandle, pNode1->conf.pVocConf, NULL);
		ChangeDevState(M_DEVINFO(pNode1->conf.pVocConf,), DEV_STATE_FREE);

		XMS_ctsClear3GVConf(g_KeygoeVar.ACSHandle, pNode1->conf.pVideoConf, NULL);
		ChangeDevState(M_DEVINFO(pNode1->conf.pVideoConf), DEV_STATE_FREE);

		//delete the node 
		if(pNode2 != NULL)
			pNode2->next = pNode1->next;
		else
			g_ConfList = pNode1->next;
		free(pNode1);
		return 1;
	}
	else
		return 0;
}

void ResetServConf(DeviceID_t *pDev)
{
	Dev_Info *pDevInfo = M_DEVINFO(pDev);
	
	StopMedia(pDev);
	StopMedia(pDevInfo->pPlayRecDev);
	if(pDevInfo->pConf)
	{
		LeaveConf(pDevInfo->pConf, pDev, 1, 1);
	}
	SetDevTimer(pDev, 0);	//clear timer
}

int GetRecFile(DeviceID_t *pDev, char *sFileName)
{
	if(!pDev || !sFileName)
		return 0;

	SYSTEMTIME st; 
	GetLocalTime(&st);

	if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE)
	{
		sprintf(sFileName, "%s\\rec_trk(%d-%d)-%d-%d-%d-%d-%d.3gp", 
			g_KeygoeVar.cfg.VocPath, pDev->m_s8ModuleID, pDev->m_s16ChannelID, 
			st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);	
		return 1;
	}
	else if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOIP)
	{
		sprintf(sFileName, "%s\\rec_ip(%d-%d)-%d-%d-%d-%d-%d.3gp", 
			g_KeygoeVar.cfg.VocPath, pDev->m_s8ModuleID, pDev->m_s16ChannelID, 
			st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		return 1;
	}
	else if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VIDEOCONF)
	{
		sprintf(sFileName, "%s\\rec_conf(%d-%d)-%d-%d-%d-%d-%d.3gp", 
			g_KeygoeVar.cfg.VocPath, pDev->m_s8ModuleID, pDev->m_s16ChannelID, 
			st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		return 1;
	}

	return 0;
}

int RecFromConf(Conf_Instance *pConfIns)
{
	if(pConfIns == NULL)
		return 0;

	char sFileName[256];
	
	if(GetRecFile(pConfIns->pVideoConf, sFileName) == 0)
		return 0;
	
	Record3gppProperty_t paramRecord;
	memset(&paramRecord, 0, sizeof(Record3gppProperty_t));

	Acs_3GVConf_Record record;
	memset(&record, 0, sizeof(Acs_3GVConf_Record));
	record.m_PrivateData.m_u32DataSize = sizeof(Acs_3GVConf_Record);
	memcpy(&record.m_device, pConfIns->pVocConf, sizeof(DeviceID_t));

	strcpy(record.m_record.m_s8DstName, sFileName);
	record.m_record.video.m_u8Codec = VOIP_MEDIA_VIDEO_H263;
	
	return Record3GP(pConfIns->pVideoConf, &paramRecord, (PrivateData_t*)&record);
}

int ServConfFlow(DeviceID_t *pDev)
{
	Dev_Info *pDevInfo;
	Conf_Instance *pConf = NULL;
	int ConfId;
	static int flag = 1;
	
	if(pDev == NULL)
		return 0;

	pDevInfo = M_DEVINFO(pDev);
	if(strlen(pDevInfo->szDTMF) == 0)
		return 0;
	
	switch(pDevInfo->Dev_State)
	{
	case DEV_STATE_CONNECT:
		switch(pDevInfo->szDTMF[0])	
		{
		case '1':			//create conference
			{
				DeviceID_t *pVocConf, *pVideoConf;
				int ret = 0;
				
				pVocConf = GetOneDev(pDev->m_s8ModuleID, XMS_DEVMAIN_CONFERENCE, 0, DEV_STATE_FREE);
				if(pVocConf == NULL)
					break;
				
				pVideoConf = GetOneDev(0, XMS_DEVMAIN_VIDEOCONF, 0, DEV_STATE_FREE);
				if(pVideoConf == NULL)
				{
					ChangeDevState(M_DEVINFO(pVocConf), DEV_STATE_FREE);
					break;
				}
				
				pConf = CreateConf(-1, pVocConf, pVideoConf);
				if(pConf)
				{
					if(JoinConf(pConf, pDev) > 0)
					{
						ChangeDevState(pDevInfo, DEV_STATE_INCONF);
						strcpy(pDevInfo->szDTMF, "");
						StopMedia(pDevInfo->pPlayRecDev);
						RefreshConfInfo();
						
						ret = 1;
						
						sprintf(msg, "Create conference succeed! id = %d", pConf->id);
						AddMsg(msg);
					}
					else
						DestroyConf(pConf->id, NULL);
				}

				if(!ret)
				{
					PlayToDev(pDev, pDevInfo->szFileName[1], MEDIA_TYPE_ANV, 1000000, NULL);
					ChangeDevState(pDevInfo, DEV_STATE_CREATEFAILED);
					
					sprintf(msg, "Create conference failed!");
					AddMsg(msg);
				}
			}
			break;
		case '2':			//join conference
			{
				strcpy(pDevInfo->szDTMF, "");
				strcpy(pDevInfo->szText, "请输入三位会议号");
				SetOverlay(pDev, 1);
				SetDevTimer(pDev, 500);
				
				PlayToDev(pDev, pDevInfo->szFileName[2], MEDIA_TYPE_MEDIAEX_ANV, 1000000, NULL, pDevInfo->szFileName[4]);

				ChangeDevState(pDevInfo, DEV_STATE_JOIN);
			}
			break;
		default:
			strcpy(pDevInfo->szDTMF, "");
			break;
		}
		break;
	case DEV_STATE_JOIN:
		SetDevTimer(pDev, 0);
		SetOverlay(pDev, 2);
		
		if(strlen(pDevInfo->szDTMF) >= 3)
		{
			StopPlay(pDev);
			ConfId = (pDevInfo->szDTMF[0]-'0')*100 + (pDevInfo->szDTMF[1]-'0')*10 + (pDevInfo->szDTMF[2]-'0');
			if(JoinConf(ConfId, &pDevInfo->Dev) > 0)
			{
				ChangeDevState(pDevInfo, DEV_STATE_INCONF);
				strcpy(pDevInfo->szDTMF, "");
				RefreshConfInfo();
				
				sprintf(msg, "Join conference %d succeed!", ConfId);
				AddMsg(msg);
			}
			else
			{
				strcpy(pDevInfo->szDTMF, "");
				strcpy(pDevInfo->szText, "请输入三位会议号");
				SetOverlay(pDev, 1);
				SetDevTimer(pDev, 500);

				PlayToDev(pDev, pDevInfo->szFileName[3], MEDIA_TYPE_MEDIAEX_ANV, 1000000, NULL, pDevInfo->szFileName[4]);
				
				ChangeDevState(pDevInfo, DEV_STATE_JOIN);
				
				sprintf(msg, "Join conference %d failed!", ConfId);
				AddMsg(msg);
			}
		}
		else 
		{
			if(pDevInfo->szDTMF[0] == '#' || pDevInfo->szDTMF[1] == '#')
			{
				PlayToDev(pDev, pDevInfo->szFileName[0], MEDIA_TYPE_ANV, 1000000, NULL);
				ChangeDevState(pDevInfo, DEV_STATE_CONNECT);
				strcpy(pDevInfo->szDTMF, "");
			}
		}
		break;
	case DEV_STATE_CREATEFAILED:
	case DEV_STATE_PLAYING:
		switch(pDevInfo->szDTMF[0])	
		{
		case '#':
			PlayToDev(pDev, pDevInfo->szFileName[0], MEDIA_TYPE_ANV, 1000000, NULL);
			ChangeDevState(pDevInfo, DEV_STATE_CONNECT);
			strcpy(pDevInfo->szDTMF, "");
			break;
		default:
			strcpy(pDevInfo->szDTMF, "");
			break;
		}
		break;
	case DEV_STATE_INCONF:
		switch(pDevInfo->szDTMF[0])	
		{
		case '1':		//record
			if(RecFromConf(pDevInfo->pConf))
				ChangeDevState(pDevInfo, DEV_STATE_RECORDING);
			break;
		case '#':
			ConfId = LeaveConf(NULL, pDev, 1, 1);
			
			PlayToDev(pDev, pDevInfo->szFileName[0], MEDIA_TYPE_ANV, 1000000, NULL);
			ChangeDevState(pDevInfo, DEV_STATE_CONNECT);
			strcpy(pDevInfo->szDTMF, "");

			RefreshConfInfo();
			
			sprintf(msg, "Leave conference %d", ConfId);
			AddMsg(msg);
			break;
		default:
			strcpy(pDevInfo->szDTMF, "");
			break;
		}
	case DEV_STATE_RECORDING:
		switch(pDevInfo->szDTMF[0])	
		{
		case '#':
			if(pDevInfo->pConf)
			{
				if(pConf->pVideoConf)
					StopRecord(pConf->pVideoConf);
			}
			break;
		default:
			strcpy(pDevInfo->szDTMF, "");
			break;
		}
		break;
	default:
		break;
	}

	return 1;
}

void ServConfExit()
{
	Conf_Node *pConfNode;
	User_Node *pMemberNode;
	
	while(g_ConfList)
	{
		while(g_ConfList->conf.MemberList)
		{
			pMemberNode = g_ConfList->conf.MemberList->next;
			free(g_ConfList->conf.MemberList);
			g_ConfList->conf.MemberList = pMemberNode;
		}
			
		pConfNode = g_ConfList->next;
		free(g_ConfList);
		g_ConfList = pConfNode;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//kegoe event process routine

int Get3G324MUII(Acs_Evt_t *pAcsEvt, char *pStr)
{
	if(pAcsEvt->m_s32EventType == XMS_EVT_3G324M)	
	{
		Acs_3G324_Data *p324EvtData = (Acs_3G324_Data*)FetchEventData(pAcsEvt);
		if(p324EvtData->m_u8DataType == XMS_324_EVT_TYPE_UII)
		{
			H245_UII *pUII = (H245_UII*)(p324EvtData + 1);
			if(pUII->m_u8Type == 1)
			{
				*pStr = pUII->m_s8Signal;
				return 1;
			}
			else if(pUII->m_u8Type == 2)
			{
				sprintf(pStr, "%s", pUII->str);
				return 2;
			}
		}				
	}

	return 0;
}

int GetRtpDtmf(Acs_Evt_t *pAcsEvt, char *pChar)
{
	if(pAcsEvt->m_s32EventType == XMS_EVT_RECVIODATA)	
	{
		Acs_IO_Data *pIOEvt = (Acs_IO_Data *)FetchEventData(pAcsEvt);
		if(pIOEvt->m_u16IoType == XMS_IO_TYPE_VOIP_RTPDTMF)
		{
			if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_RTPDTMF))
			{
				Acs_VoIP_RTPDTMF *rtpDtmf = (Acs_VoIP_RTPDTMF *)FetchIOData(pAcsEvt);
				*pChar = rtpDtmf->m_s8EventChar;
				return 1;
			}
		}				
	}

	return 0;
}

void OnEvtQueryDev(Acs_Evt_t *pAcsEvt)
{
	Acs_Dev_List_Head_t *pAcsDevList = (Acs_Dev_List_Head_t *)FetchEventData(pAcsEvt);
	char TmpStr[256];
	
	sprintf(TmpStr, "<%s>(%d, %d, %d, %d)", GetEvtName(pAcsEvt->m_s32EventType),
		pAcsDevList->m_s32ModuleID, pAcsEvt->m_DeviceID.m_s16ChannelID,
		pAcsDevList->m_s32DeviceMain, pAcsDevList->m_s32DeviceNum);
	AddMsg(TmpStr);

	if (g_KeygoeVar.cfg.DspId[0] != 0)
	{
		for(int i = 0; i < MAX_UNIT; ++i)
		{
			if(g_KeygoeVar.cfg.DspId[i] == pAcsDevList->m_s32ModuleID)
				break;
		}
		
		if(i == MAX_UNIT)
			return;
	}
	
	if(pAcsDevList->m_s32ModuleID >= MAX_UNIT || pAcsDevList->m_s32DeviceMain > MAX_DEV_TYPE)
		return;

	if(pAcsDevList->m_s32DeviceMain == XMS_DEVMAIN_VIDEO ||
		pAcsDevList->m_s32DeviceMain == XMS_DEVMAIN_SS7_LINK)
		return;
	
	DeviceID_t *pDevSrc = (DeviceID_t *)(pAcsDevList+1);
	Dev_Info *pDevInfo;
	int iDevMain = pAcsDevList->m_s32DeviceMain;
	int iUnit = pAcsDevList->m_s32ModuleID;

	for(int i = 0; i < MAX_DEV; ++i)
	{
		if(g_DevInfo[iUnit][iDevMain][i].Dev_State != DEV_STATE_NULL)
		{
			if(g_DevInfo[iUnit][iDevMain][i].Dev_State != DEV_STATE_WAITOPEN)
			{
				if(g_DevType[iDevMain].Dev_Opened > 0)
					g_DevType[iDevMain].Dev_Opened--;
			}
			if(g_DevType[iDevMain].Dev_Total > 0) 
				g_DevType[iDevMain].Dev_Total--;
		}

		InitDev(&g_DevInfo[iUnit][iDevMain][i]);
	}
	
	for (i = 0; i < pAcsDevList->m_s32DeviceNum; ++i)
	{
		pDevInfo = M_DEVINFO(pDevSrc);
		memcpy(&pDevInfo->Dev, pDevSrc, sizeof(DeviceID_t));
		pDevInfo->Dev_State = DEV_STATE_WAITOPEN;
		pDevSrc++;
	}
	g_DevType[iDevMain].Dev_Total += pAcsDevList->m_s32DeviceNum;
}

void OnEvtQueryDevEnd(Acs_Evt_t *pAcsEvt)
{
	DisplayDevType();
	for(int i = 0; i < MAX_DEV_TYPE; ++i)
	{
		if(g_DevType[i].Dev_Total != 0)
		{
			DisplayDevInfo(i);
			break;
		}
	}
	OnOpenAllDevice();
}

void OnEvtOpenDev(Acs_Evt_t *pAcsEvt)
{
	DeviceID_t *pDev;
	Dev_Info *pDevInfo;

	pDev = &pAcsEvt->m_DeviceID;
	pDevInfo = M_DEVINFO(pDev);

	g_DevType[pDev->m_s16DeviceMain].Dev_Opened++;
	memcpy(&(pDevInfo->Dev), pDev, sizeof(DeviceID_t));
	pDevInfo->Dev_State = DEV_STATE_FREE;

	if(pDev->m_s16DeviceMain == XMS_DEVMAIN_INTERFACE_CH)
	{
		pDevInfo->Dev_State = DEV_STATE_WAITFREE;
		XMS_ctsResetDevice(g_KeygoeVar.ACSHandle, pDev, NULL);
		XMS_ctsGetDevState(g_KeygoeVar.ACSHandle, pDev, NULL);
	}
	else if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE)
	{
		if(pDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_VOC)
		{
			// disable gtd
			CmdParamData_Voice_t ParamVoice = {0};
			ParamVoice.m_u8GtdCtrlValid = 1;
			ParamVoice.m_VocGtdControl.m_u8ChannelEnable = 0;
			SetParam(pDev, VOC_PARAM_UNIPARAM, sizeof(CmdParamData_Voice_t), &ParamVoice);
		}
	}
	
	RefreshDevType(&g_DevType[pDev->m_s16DeviceMain]);
	if(pDevInfo->Dev.m_s16DeviceMain == g_CurDisplayDevType)
		RefreshDevInfo(pDevInfo);

	TRACE("Open device %s <%d, %d>\n", GetDevTypeName(pDev->m_s16DeviceMain), pDev->m_s8ModuleID, pDev->m_s16ChannelID);
}

void OnEvtCloseDev(Acs_Evt_t *pAcsEvt)
{
	DeviceID_t *pDev;
	Dev_Info *pDevInfo;
	
	pDev = &pAcsEvt->m_DeviceID;
	pDevInfo = M_DEVINFO(pDev);

	if(g_DevType[pDev->m_s16DeviceMain].Dev_Opened > 0)
		g_DevType[pDev->m_s16DeviceMain].Dev_Opened--;
	pDevInfo->Dev_State = DEV_STATE_WAITOPEN;
	
	RefreshDevType(&g_DevType[pDev->m_s16DeviceMain]);
	if(pDevInfo->Dev.m_s16DeviceMain == g_CurDisplayDevType)
		RefreshDevInfo(pDevInfo);
	
	TRACE("Close device %s <%d, %d>\n", GetDevTypeName(pDev->m_s16DeviceMain), pDev->m_s8ModuleID, pDev->m_s16ChannelID);

	if(pDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE && pDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_324)
	{
		char str[256];
		Acs_GeneralProc_Data *pData;
		pData = (Acs_GeneralProc_Data*)FetchEventData(pAcsEvt);
		sprintf(str, "<%d-%d>324 Closed(%d, %d)", pDev->m_s8ModuleID, pDev->m_s16ChannelID, pData->m_s32AcsEvtState, pData->m_s32AcsEvtErrCode);
		AddMsg(str);
	}
}

void OnEvtDevState(Acs_Evt_t *pAcsEvt)
{
	Acs_GeneralProc_Data *pGeneralData = (Acs_GeneralProc_Data *)FetchEventData(pAcsEvt);
	if(pGeneralData != NULL)
	{
		DeviceID_t *pDev = &pAcsEvt->m_DeviceID;
		Dev_Info *pDevInfo = M_DEVINFO(pDev);
		
		if(pGeneralData->m_s32DeviceState == DCS_FREE)	/* FREE */
		{
			if(pDevInfo->Dev_State != DEV_STATE_WAITOPEN && pDevInfo->Dev_State != DEV_STATE_NULL)
				ChangeDevState(pDevInfo, DEV_STATE_FREE);
		}
	}
}

void OnEvt3G324M(Acs_Evt_t *pAcsEvt)
{
	char uiiStr[256];
	DeviceID_t *pDev, *pFreeDev, *pTrkDev;
	Dev_Info *pDevInfo;
	Acs_GeneralProc_Data *pGeneralData;
	Acs_3G324_Data* p324EvtData;
	Acs_3G324_Stop_Evt *pStopEvt;
	H245_UII *pUII;
	Acs_LinkDev_Data *pLink;
	Evt_H245_OLC *pOLC;
	int iFlag = 0;
	static int flag = 0;

	pDev = &pAcsEvt->m_DeviceID;
	pDevInfo = M_DEVINFO(pDev);

	switch(pAcsEvt->m_s32EventType)
	{
	case XMS_EVT_DEV_TIMER:
		if(pDevInfo->Dev_State == DEV_STATE_WAITCONNECT)
		{
			//3g324m failed
			H324StopSession(pDev);
			ChangeDevState(pDevInfo, DEV_STATE_FREE);
			break;
		}

		if(flag)
		{
			SetOverlay(pDev, 1);
			flag = 0;
		}
		else
		{
			SetOverlay(pDev, 0);
			flag = 1;
		}
		SetDevTimer(pDev, 500);
		break;
	case XMS_EVT_DEVICESTATE:	//event device state
		pGeneralData = (Acs_GeneralProc_Data *)FetchEventData(pAcsEvt);
		if(pGeneralData != NULL && pGeneralData->m_s32DeviceState == DCS_FREE)	/* FREE */
			ChangeDevState(pDevInfo, DEV_STATE_FREE);
		break;
	case XMS_EVT_PLAY:
		{
			Acs_MediaProc_Data *pData;
			pData = (Acs_MediaProc_Data*)FetchEventData(pAcsEvt);
			sprintf(msg, "Play evt %d(%d)", pData->m_s32AcsEvtState, pData->m_s32AcsEvtErrCode);
			AddMsg(msg);
		}
		break;
	case XMS_EVT_CONTROLPLAY:
		//AddMsg("Control play evt!");
		break;
	case XMS_EVT_3GPP_PLAY:
		{
			Acs_Media3GPPProc_Data *pData = (Acs_Media3GPPProc_Data *)FetchEventData(pAcsEvt);
			if(pData->m_u8MediaType == MEDIA_TYPE_MEDIAEX_ANV ||
				pData->m_u8MediaType == MEDIA_TYPE_MEDIAEX_AUDIO ||
				pData->m_u8MediaType == MEDIA_TYPE_MEDIAEX_VIDEO)
			{
				sprintf(msg, "<%d-%d>mediaex play evt %d %d(%d)", pDev->m_s8ModuleID, pDev->m_s16ChannelID, pData->m_u8MediaType, pData->m_s32AcsEvtState, pData->m_s32AcsEvtErrCode);
				AddMsg(msg);
			}
			else
			{
				sprintf(msg, "<%d-%d>3gp play evt %d(%d)", pDev->m_s8ModuleID, pDev->m_s16ChannelID, pData->m_s32AcsEvtState, pData->m_s32AcsEvtErrCode);
				AddMsg(msg);
			}
		}
		break;
	case XMS_EVT_3GPP_CONTROLPLAY:
		//AddMsg("3gp Control play evt!");
		break;
	case XMS_EVT_3GPP_CONTROLRECORD:
		//AddMsg("3gp control record evt!");
		break;
	case XMS_EVT_3GPP_RECORD:
		{
			Acs_Media3GPPProc_Data *pData = (Acs_Media3GPPProc_Data *)FetchEventData(pAcsEvt);
			if(pData->m_u8MediaType == MEDIA_TYPE_MEDIAEX_ANV ||
				pData->m_u8MediaType == MEDIA_TYPE_MEDIAEX_AUDIO ||
				pData->m_u8MediaType == MEDIA_TYPE_MEDIAEX_VIDEO)
			{
				sprintf(msg, "<%d-%d>mediaex rec evt %d %d(%d)", pDev->m_s8ModuleID, pDev->m_s16ChannelID, pData->m_u8MediaType, pData->m_s32AcsEvtState, pData->m_s32AcsEvtErrCode);
				AddMsg(msg);
			}
			else
			{
				sprintf(msg, "<%d-%d>3gp play evt %d(%d)", pDev->m_s8ModuleID, pDev->m_s16ChannelID, pData->m_s32AcsEvtState, pData->m_s32AcsEvtErrCode);
				//AddMsg(msg);
			}
		}
		break;
    case XMS_EVT_GETPARAM:
		{
			char msg[256];
			CmdParamData_3GPP_t * pData = NULL;
			Acs_ParamProc_Data * pEvt = (Acs_ParamProc_Data *)FetchEventData(pAcsEvt);
			if ( H324_PARAM_MEDIA == pEvt->m_u16ParamCmdType )
			{
				pData =  (CmdParamData_3GPP_t *)FetchParamData(pAcsEvt);
            
				sprintf(msg, "DecoderCfgInfo(%d): ", pData->m_u16VideoDecoderCfgLen);
				
                char *p = &msg[strlen(msg)];
                for(int i = 0; i < pData->m_u16VideoDecoderCfgLen; i++)
			    {
				    if((pData->m_u8VideoDecoderCfg[i]/16) >= 10)
					    *p++ = (pData->m_u8VideoDecoderCfg[i]/16) - 10 + 'A';
				    else
					    *p++ = (pData->m_u8VideoDecoderCfg[i]/16) + '0';
				    if((pData->m_u8VideoDecoderCfg[i]%16) >= 10)
					    *p++ = (pData->m_u8VideoDecoderCfg[i]%16) - 10 + 'A';
				    else
					    *p++ = (pData->m_u8VideoDecoderCfg[i]%16) + '0';
			    }
			    *p = '\0';
                AddMsg(msg);
			}
		}
		break;
	case XMS_EVT_LINKDEVICE:	//event link ok
		pLink = (Acs_LinkDev_Data*)FetchEventData(pAcsEvt);
		if(pLink->m_DestDevice.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH)
		{
			sprintf(msg, "<%d-%d>324 video link evt %d(%d)", pDev->m_s8ModuleID, pDev->m_s16ChannelID, pLink->m_s32AcsEvtState, pLink->m_s32AcsEvtErrCode);
			AddMsg(msg);
			break;
		}
		break;
	case XMS_EVT_UNLINKDEVICE:	//event link ok
		pLink = (Acs_LinkDev_Data*)FetchEventData(pAcsEvt);
		if(pLink->m_DestDevice.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH)
		{
			sprintf(msg, "<%d-%d>324 video unlink evt %d(%d)", pDev->m_s8ModuleID, pDev->m_s16ChannelID, pLink->m_s32AcsEvtState, pLink->m_s32AcsEvtErrCode);
			AddMsg(msg);
			break;
		}
		break;
	case XMS_EVT_3G324M:	//event 3G-324M
		p324EvtData = (Acs_3G324_Data*)FetchEventData(pAcsEvt);
		switch(p324EvtData->m_u8DataType)
		{
		case XMS_324_EVT_TYPE_OLC:
			sprintf(msg, "324<%d-%d> OLC", pDev->m_s8ModuleID, pDev->m_s16ChannelID);
			pOLC = (Evt_H245_OLC*)((DJ_U8*)p324EvtData+sizeof(Acs_3G324_Data));
	
			switch(pOLC->u8Codec)
			{
			case VOIP_MEDIA_AUDIO_AMR:
				if(pOLC->u8Direction == 0)
				{
					pDevInfo->audio.TxCodec = pOLC->u8Codec;
					sprintf(msg, "%s: TX-%d AMR", msg, pOLC->u8ChannelNumber);
				}
				else
				{
					pDevInfo->audio.RxCodec = pOLC->u8Codec;
					sprintf(msg, "%s: RX-%d AMR", msg, pOLC->u8ChannelNumber);
				}
				break;
			case VOIP_MEDIA_AUDIO_G723:
				if(pOLC->u8Direction == 0)
				{
					pDevInfo->audio.TxCodec = pOLC->u8Codec;
					sprintf(msg, "%s: TX-%d G723", msg, pOLC->u8ChannelNumber);
				}
				else
				{
					pDevInfo->audio.RxCodec = pOLC->u8Codec;
					sprintf(msg, "%s: RX-%d G723", msg, pOLC->u8ChannelNumber);
				}
				break;
			case VOIP_MEDIA_VIDEO_H263:
				if(pOLC->u8Direction == 0)
				{
					pDevInfo->video.TxCodec = pOLC->u8Codec;
					sprintf(msg, "%s: TX-%d H263", msg, pOLC->u8ChannelNumber);
				}
				else
				{
					pDevInfo->video.RxCodec = pOLC->u8Codec;
					sprintf(msg, "%s: RX-%d H263", msg, pOLC->u8ChannelNumber);
				}
				break;
			case VOIP_MEDIA_VIDEO_MPEG4:
				if(pOLC->u8Direction == 0)
				{
					pDevInfo->video.TxCodec = pOLC->u8Codec;
					sprintf(msg, "%s: TX-%d MPEG4(%d)", msg, pOLC->u8ChannelNumber, pOLC->u8DecoderConfigInfoLen);
				}
				else
				{
					pDevInfo->video.RxCodec = pOLC->u8Codec;
                    if(pOLC->u8DecoderConfigInfoLen > 0 && pOLC->u8DecoderConfigInfoLen <= MAX_DECODER_CFG_INFO)
                    {
                        pDevInfo->decoderConfigLength = pOLC->u8DecoderConfigInfoLen;
                        memcpy(pDevInfo->decoderConfigInfo, pOLC->s8DecoderConfigInfo, pOLC->u8DecoderConfigInfoLen);
                    }
					sprintf(msg, "%s: RX-%d MPEG4(%d)", msg, pOLC->u8ChannelNumber, pOLC->u8DecoderConfigInfoLen);
				}
				break;
			default:
				iFlag = 1;
				sprintf(msg, "%s Unkown(%d)", msg, pOLC->u8Codec);
				break;
			}
			
			AddMsg(msg);

			if(iFlag)
				break;

			if(pDevInfo->audio.TxCodec != 255 &&
				pDevInfo->audio.RxCodec != 255 &&
				pDevInfo->video.TxCodec != 255 &&
				pDevInfo->video.RxCodec != 255)
			{
				///set h324 channel configure parameter
				CmdParamData_324CH_t ChCfg;
				memset(&ChCfg, 0, sizeof(ChCfg));
				ChCfg.m_u8Channel_Enable = 1;	//enable
				ChCfg.m_u8AudioSRC1_Ctrl = XMS_MIXER_FROM_PLAY;	//audio source
				ChCfg.m_u16AudioSRC1_ID = pDev->m_s16ChannelID;
				ChCfg.m_u8VideoSRC1_Ctrl = XMS_MIXER_FROM_PLAY;	//video source
				ChCfg.m_u16VideoSRC1_ID = pDev->m_s16ChannelID;
				ChCfg.m_u8AudioInDecodeFlag = 1;	/* 1 - input decode, 0 - no decode */
				ChCfg.m_u8AudioOutEncodeFlag = 1; /* 1 - output encode, 0 - no encode */
				if(pDevInfo->audio.RxCodec == VOIP_MEDIA_AUDIO_G723)
					ChCfg.m_u8AudioInCodec = XMS_G723_type;		/* audio input codec */
				else
					ChCfg.m_u8AudioInCodec = XMS_Amr_type;
				if(pDevInfo->audio.TxCodec == VOIP_MEDIA_AUDIO_G723)
					ChCfg.m_u8AudioOutCodec = XMS_G723_type;		/* audio output codec */
				else
					ChCfg.m_u8AudioOutCodec = XMS_Amr_type;
				if(pDevInfo->video.RxCodec == VOIP_MEDIA_VIDEO_H263)
					ChCfg.m_u8VideoInCodec = XMS_VIDEO_CODE_TYPE_H263;		/* video input codec */
				else
					ChCfg.m_u8VideoInCodec = XMS_VIDEO_CODE_TYPE_MP4V;
				if(pDevInfo->video.TxCodec == VOIP_MEDIA_VIDEO_H263)
					ChCfg.m_u8VideoOutCodec = XMS_VIDEO_CODE_TYPE_H263;		/* video output codec */
				else
					ChCfg.m_u8VideoOutCodec = XMS_VIDEO_CODE_TYPE_MP4V;
				H324SetChCfg(pDev, &ChCfg);
				
				if(pDevInfo->szFileName[0] == NULL)
					pDevInfo->szFileName[0] = (char*)malloc(256);
				if(pDevInfo->szFileName[1] == NULL)
					pDevInfo->szFileName[1] = (char*)malloc(256);
				if(pDevInfo->szFileName[2] == NULL)
					pDevInfo->szFileName[2] = (char*)malloc(256);
				if(pDevInfo->szFileName[3] == NULL)
					pDevInfo->szFileName[3] = (char*)malloc(256);
				if(pDevInfo->video.TxCodec == VOIP_MEDIA_VIDEO_H263)
				{
					if(pDevInfo->szFileName[0] != NULL)
						sprintf(pDevInfo->szFileName[0], "%s\\servconf_basemenu-h263.3gp", g_KeygoeVar.cfg.VocPath);
					if(pDevInfo->szFileName[1] != NULL)
						sprintf(pDevInfo->szFileName[1], "%s\\servconf_create_failed-h263.3gp", g_KeygoeVar.cfg.VocPath);
					if(pDevInfo->szFileName[2] != NULL)
						sprintf(pDevInfo->szFileName[2], "%s\\servconf_join-h263.3gp", g_KeygoeVar.cfg.VocPath);
					if(pDevInfo->szFileName[3] != NULL)
						sprintf(pDevInfo->szFileName[3], "%s\\servconf_join_failed-h263.3gp",g_KeygoeVar.cfg.VocPath);
				}
				else
				{
					if(pDevInfo->szFileName[0] != NULL)
						sprintf(pDevInfo->szFileName[0], "%s\\servconf_basemenu-mpeg4.3gp", g_KeygoeVar.cfg.VocPath);
					if(pDevInfo->szFileName[1] != NULL)
						sprintf(pDevInfo->szFileName[1], "%s\\servconf_create_failed-mpeg4.3gp", g_KeygoeVar.cfg.VocPath);
					if(pDevInfo->szFileName[2] != NULL)
						sprintf(pDevInfo->szFileName[2], "%s\\servconf_join-mpeg4.3gp", g_KeygoeVar.cfg.VocPath);
					if(pDevInfo->szFileName[3] != NULL)
						sprintf(pDevInfo->szFileName[3], "%s\\servconf_join_failed-mpeg4.3gp",g_KeygoeVar.cfg.VocPath);
				}
				
				pDevInfo->pPlayRecDev = &pDevInfo->Dev;
				PlayToDev(pDev, pDevInfo->szFileName[0], MEDIA_TYPE_ANV, 1000000, NULL);
				SetOverlayFile(pDev);
				strcpy(pDevInfo->szDTMF, "");
				strcpy(pDevInfo->szText, "");
				SetOverlay(pDev, 0);
				//PlayToDev(pDev, pDevInfo->szFileName[0], MEDIA_TYPE_MEDIAEX_ANV, 1, NULL, pDevInfo->szFileName[4]);			
				ChangeDevState(pDevInfo, DEV_STATE_CONNECT);
			}
			break;
        case XMS_324_EVT_TYPE_CLC:
            {
                Evt_H245_CLC *pClC = (Evt_H245_CLC*)((DJ_U8*)p324EvtData+sizeof(Acs_3G324_Data));
                sprintf(msg, "<%d-%d>lc %d(%d) closed!", pDev->m_s8ModuleID, pDev->m_s16ChannelID, pClC->u8ChannelNumber, pClC->u8Direction);
				AddMsg(msg);
            }
            break;
		case XMS_324_EVT_TYPE_STOP:	//324 SESSION STOP	
			pStopEvt = (Acs_3G324_Stop_Evt *)((DJ_U8*)p324EvtData+sizeof(Acs_3G324_Data));
			if(pStopEvt->m_u8StopCode == XMS_324_STOP_CODE_LOWERSTOP)
			{
				sprintf(msg, "<%d-%d>session stoped!", pDev->m_s8ModuleID, pDev->m_s16ChannelID);
				AddMsg(msg);
				
				StopMedia(pDev);

				if(pDevInfo->pLinkDev != NULL)
				{
					//unlink
					DualUnlinkDev(pDev, pDevInfo->pLinkDev);

					//clear call
					ClearCall(pDevInfo->pLinkDev);

					//break relationship
					M_DEVINFO(pDevInfo->pLinkDev)->pLinkDev = NULL;
					pDevInfo->pLinkDev = NULL;
				}

				ResetServConf(pDev);
				ReleaseDev(pDev);	
				RefreshConfInfo();
			}

			break;
		case XMS_324_EVT_TYPE_RESET:
			AddMsg("	Reset Event!");

			pTrkDev = pDevInfo->pLinkDev;
			if(pTrkDev == NULL || pTrkDev->m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH)
			{
				pDevInfo->pLinkDev = NULL;
				ChangeDevState(pDevInfo, DEV_STATE_FREE);
				break;
			}

			if((pFreeDev = GetOneDev (pDev->m_s8ModuleID, XMS_DEVMAIN_VOICE, XMS_DEVSUB_MEDIA_324, DEV_STATE_FREE)))
			{
				AddMsg("	Reset on new 324!");
				DualUnlinkDev(pDev, pTrkDev);
				pDevInfo->pLinkDev = NULL;
				
				M_DEVINFO(pTrkDev)->pLinkDev = pFreeDev;
				M_DEVINFO(pFreeDev)->pLinkDev = pTrkDev;
				DualLinkDev(pTrkDev, pFreeDev);

				M_DEVINFO(pFreeDev)->audio.TxCodec = 255;
				M_DEVINFO(pFreeDev)->audio.RxCodec = 255;
				M_DEVINFO(pFreeDev)->video.TxCodec = 255;
				M_DEVINFO(pFreeDev)->video.RxCodec = 255;
				
				H324SetTCS(pFreeDev);	// optional
				H324StartSession(pFreeDev, XMS_324_CMD_TYPE_NORMAL_START);
				
				ChangeDevState(M_DEVINFO(pFreeDev), DEV_STATE_WAITCONNECT);
				SetDevTimer(pFreeDev, 30000);
			}
			else
			{
				AddMsg("	Reset on old 324!");
				H324StartSession(pDev, XMS_324_CMD_TYPE_NORMAL_START);

				ChangeDevState(pDevInfo, DEV_STATE_WAITCONNECT);
			}		

			break;
		case XMS_324_EVT_TYPE_UII:
			pUII = (H245_UII*)(p324EvtData + 1);
			if(pUII->m_u8Type == 1)
			{
				sprintf(msg, "(%d-%d)UII Signal: %c", pDev->m_s8ModuleID, pDev->m_s16ChannelID, pUII->m_s8Signal);
				if(strlen(pDevInfo->szDTMF)+1 < 32)
				{
					sprintf(pDevInfo->szDTMF, "%s%c", pDevInfo->szDTMF, pUII->m_s8Signal);
				}
			}
			else if(pUII->m_u8Type == 2)
			{
				sprintf(msg, "(%d-%d)UII text: %s", pDev->m_s8ModuleID, pDev->m_s16ChannelID, pUII->str);
				if(strlen(pDevInfo->szDTMF) + strlen(pUII->str) < 32)	
				{
					strcat(pDevInfo->szDTMF, pUII->str);
				}
			}
			AddMsg(msg);
			
			break;
		case XMS_324_EVT_TYPE_SIG_PDU: //h.245 signal data
			//perform h.245 signal data processing.
			unsigned char buf[1024];
			int datalen;
			AddMsg("H.245 signal data event");
			
			if(p324EvtData->m_u16DataLen > 0)
			{
				datalen = p324EvtData->m_u16DataLen > 1024? 1024 : p324EvtData->m_u16DataLen;
				memcpy(buf, (DJ_U8*)p324EvtData+sizeof(Acs_3G324_Data), datalen);
			}
			
			break;
		default:
			break;
		} 
		break;
	default:
		break;
	}

	ServConfFlow(pDev);
}

void OnEvtVoice(Acs_Evt_t *pAcsEvt)
{
	char *dtmf = NULL;
	DeviceID_t *pDev;
	Dev_Info *pDevInfo;
	Acs_IO_Data *pIOData = NULL;;
	
	pDev = &pAcsEvt->m_DeviceID;
	pDevInfo = M_DEVINFO(pDev);
	
	switch(pAcsEvt->m_s32EventType)
	{
	case XMS_EVT_LINKDEVICE:
		if(pDevInfo->szFileName[0] == NULL)
			pDevInfo->szFileName[0] = (char*)malloc(256);
		if(pDevInfo->szFileName[1] == NULL)
			pDevInfo->szFileName[1] = (char*)malloc(256);
		if(pDevInfo->szFileName[2] == NULL)
			pDevInfo->szFileName[2] = (char*)malloc(256);
		if(pDevInfo->szFileName[3] == NULL)
			pDevInfo->szFileName[3] = (char*)malloc(256);
		
		if(pDevInfo->szFileName[0] != NULL)
			sprintf(pDevInfo->szFileName[0], "%s\\ConfMusi.Pcm", g_KeygoeVar.cfg.VocPath);
		if(pDevInfo->szFileName[1] != NULL)
			sprintf(pDevInfo->szFileName[1], "%s\\ConfMusi.Pcm", g_KeygoeVar.cfg.VocPath);
		if(pDevInfo->szFileName[2] != NULL)
			sprintf(pDevInfo->szFileName[2], "%s\\ConfMusi.Pcm", g_KeygoeVar.cfg.VocPath);
		if(pDevInfo->szFileName[3] != NULL)
			sprintf(pDevInfo->szFileName[3], "%s\\ConfMusi.Pcm",g_KeygoeVar.cfg.VocPath);

		pDevInfo->pPlayRecDev = &pDevInfo->Dev;
		PlayVoc(pDevInfo->pPlayRecDev, pDevInfo->szFileName[0], 1000000, NULL);
		ChangeDevState(pDevInfo, DEV_STATE_CONNECT);

		{
		// enable dtmf
		CmdParamData_Voice_t ParamVoice = {0};
		ParamVoice.m_u8GtdCtrlValid = 1;
		ParamVoice.m_VocGtdControl.m_u8ChannelEnable = 1;
		ParamVoice.m_VocGtdControl.m_u8DTMFEnable = 1;
		SetParam(pDev, VOC_PARAM_UNIPARAM, sizeof(CmdParamData_Voice_t), &ParamVoice);
		}
		break;
	case XMS_EVT_UNLINKDEVICE:
		StopMedia(pDev);

		{
		// disable dtmf
		CmdParamData_Voice_t ParamVoice = {0};
		ParamVoice.m_u8GtdCtrlValid = 1;
		ParamVoice.m_VocGtdControl.m_u8ChannelEnable = 0;
		SetParam(pDev, VOC_PARAM_UNIPARAM, sizeof(CmdParamData_Voice_t), &ParamVoice);
		}

		ChangeDevState(M_DEVINFO(pDev), DEV_STATE_FREE);
		break;
	case XMS_EVT_RECVIODATA:
		pIOData = (Acs_IO_Data *)FetchEventData(pAcsEvt);
		if(pIOData->m_u16IoType == XMS_IO_TYPE_DTMF && pIOData->m_u16IoDataLen > 0)
		{
			dtmf = (char *)FetchIOData(pAcsEvt);
			if(strlen(pDevInfo->szDTMF)+1 < 32)
				sprintf(pDevInfo->szDTMF, "%s%c", pDevInfo->szDTMF, *dtmf);
			sprintf(msg, "<%d-%d>DTMF: %c", pDev->m_s8ModuleID, pDev->m_s16ChannelID, *dtmf);
			AddMsg(msg);
		}
		break;
	default:
		break;
	}

	ServConfFlow(pDev);
}

void OnEvtVoc(Acs_Evt_t *pAcsEvt)
{
	if(pAcsEvt->m_DeviceID.m_s16DeviceSub == XMS_DEVSUB_MEDIA_VOC)
	{
		OnEvtVoice(pAcsEvt);
	}
	else if(pAcsEvt->m_DeviceID.m_s16DeviceSub == XMS_DEVSUB_MEDIA_324)
	{
		OnEvt3G324M(pAcsEvt);
	}
}

void OnEvtTrk(Acs_Evt_t *pAcsEvt)
{
	DeviceID_t *pVocDev;
	DeviceID_t *pDev;
	Dev_Info *pDevInfo;
	Acs_GeneralProc_Data *pGeneralData;
	Acs_CallControl_Data *pCallControl;
//	char FileName[256];
	char Msg[256];
	int iAutoAnswer = 0;

	pDev = &pAcsEvt->m_DeviceID;
	pDevInfo = M_DEVINFO(pDev);

	switch(pAcsEvt->m_s32EventType)
	{
	case XMS_EVT_DEVICESTATE:	//event device state
		pGeneralData = (Acs_GeneralProc_Data *)FetchEventData(pAcsEvt);
		if(pGeneralData != NULL && pGeneralData->m_s32DeviceState == DCS_FREE)	/* FREE */ 
			ChangeDevState(pDevInfo, DEV_STATE_FREE);
 
		break;
	case XMS_EVT_CLEARCALL:		//event clear call 
		if (pDevInfo->Dev_State == DEV_STATE_FREE) 	
			break;

		//display clear code
		pCallControl = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);
		sprintf(Msg, "<Trunk %d-%d>disc(code:%d)", pDev->m_s8ModuleID, pDev->m_s16ChannelID,
						pCallControl->m_s32CallClearCause);
		AddMsg(Msg);
		
		if(pDevInfo->pLinkDev != NULL)
		{
			//unlink
			DualUnlinkDev(pDev, pDevInfo->pLinkDev);

			//break relationship
			M_DEVINFO(pDevInfo->pLinkDev)->pLinkDev = NULL;
			if(pDevInfo->pLinkDev->m_s16DeviceMain == XMS_DEVMAIN_VOICE && pDevInfo->pLinkDev->m_s16DeviceSub == XMS_DEVSUB_MEDIA_324)
			{
				H324StopSession(pDevInfo->pLinkDev);
				ChangeDevState(M_DEVINFO(pDevInfo->pLinkDev), DEV_STATE_FREE);
			}

			pDevInfo->pLinkDev = NULL;
		}

		//change state
		ChangeDevState(pDevInfo, DEV_STATE_FREE);
 
		break;
	case XMS_EVT_CALLIN:			//event call in
		pCallControl = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);
		
		//show msg
		sprintf (Msg, "<%d-%d>CALL IN(Callee:%s, Caller:%s)", 
			pDev->m_s8ModuleID, pDev->m_s16ChannelID, 
			pCallControl->m_s8CalledNum, pCallControl->m_s8CallingNum);
		AddMsg (Msg);

		if(pDevInfo->Dev_State != DEV_STATE_FREE)
			break;

		if(0)
			pDevInfo->User_Type = USER_2G;
		else
			pDevInfo->User_Type = USER_3G;
		
		XMS_ctsAlertCall(g_KeygoeVar.ACSHandle, &pDevInfo->Dev, NULL );
		XMS_ctsAnswerCallIn( g_KeygoeVar.ACSHandle, &pDevInfo->Dev, NULL );
		ChangeDevState(pDevInfo, DEV_STATE_WAITCONNECT);
		
		break;
	case XMS_EVT_CALLOUT:	
		pCallControl = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);
		if (pCallControl->m_s32AcsEvtState != 1)
		{
			sprintf(Msg, "<%d-%d>call failed(%d)", pDev->m_s8ModuleID, pDev->m_s16ChannelID, pCallControl->m_s32CallClearCause);
			AddMsg(Msg);
			break;
		}
	case XMS_EVT_ANSWERCALL:	//event answer call succeed
		pCallControl = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);
		
		if(pDevInfo->Dev_State != DEV_STATE_WAITCONNECT)
			break;

		if(pDevInfo->User_Type == USER_2G)
			pVocDev = GetOneDev (pDev->m_s8ModuleID, XMS_DEVMAIN_VOICE, XMS_DEVSUB_MEDIA_VOC, DEV_STATE_FREE);
		else
			pVocDev = GetOneDev (pDev->m_s8ModuleID, XMS_DEVMAIN_VOICE, XMS_DEVSUB_MEDIA_324, DEV_STATE_FREE);
		if (pVocDev != NULL)
		{
			//set relationship
			pDevInfo->pLinkDev = pVocDev;
			M_DEVINFO(pVocDev)->pLinkDev = &pDevInfo->Dev;

			sprintf(Msg, "Link<%d-%d, %d> <=> <%d-%d, %d>", 
					pDev->m_s8ModuleID, pDev->m_s16ChannelID, pDev->m_s16DeviceMain, 
					pVocDev->m_s8ModuleID, pVocDev->m_s16ChannelID, pVocDev->m_s16DeviceMain);
			AddMsg(Msg);
			DualLinkDev(pVocDev, pDev); 

			if(pDevInfo->User_Type == USER_3G)
			{
				M_DEVINFO(pVocDev)->audio.TxCodec = 255;
				M_DEVINFO(pVocDev)->audio.RxCodec = 255;
				M_DEVINFO(pVocDev)->video.TxCodec = 255;
				M_DEVINFO(pVocDev)->video.RxCodec = 255;
                M_DEVINFO(pVocDev)->decoderConfigLength = 0;
				
				H324SetTCS(pVocDev);	// optional
				H324StartSession(pVocDev, XMS_324_CMD_TYPE_NORMAL_START);

				ChangeDevState(M_DEVINFO(pVocDev), DEV_STATE_WAITCONNECT);
				SetDevTimer(pVocDev, 30000);
			}
		}
		else
		{
			ClearCall(pDev);
		}
		ChangeDevState(pDevInfo, DEV_STATE_CONNECT);
		
		break;
	case XMS_EVT_LINKDEVICE:	//event link ok
		break;
	default:
		break;
	}
}

void OnEvtIp(Acs_Evt_t *pAcsEvt)
{
	DeviceID_t *pDev/*, *p3GDev*/;
	Dev_Info *pDevInfo;
	MixerControlParam_t paramMixer;
	Acs_ParamProc_Data *pParam;
	Acs_IO_Data *pIOEvt;
	char rtpDtmf;
	Acs_CallControl_Data* pCallData;
	static int flag = 0;
	VoIPConnectPrivate_t* pConParam;
	
	pDev = &pAcsEvt->m_DeviceID;
	pDevInfo = M_DEVINFO(pDev);

	switch(pAcsEvt->m_s32EventType)
	{	
	case XMS_EVT_DEV_TIMER:
		if(flag)
		{
			SetOverlay(pDev, 1);
			flag = 0;
		}
		else
		{
			SetOverlay(pDev, 0);
			flag = 1;
		}
		SetDevTimer(pDev, 500);
		break;
	case XMS_EVT_CLEARCALL:
		ResetServConf(pDev);
		ReleaseDev(pDev);	
		RefreshConfInfo();

		sprintf(msg, "IP(%d-%d) call disconnected!", pDev->m_s8ModuleID, pDev->m_s16ChannelID);
		AddMsg(msg);
		break;
	case XMS_EVT_CALLIN:
		sprintf(msg, "IP(%d-%d) call in!", pDev->m_s8ModuleID, pDev->m_s16ChannelID);
		AddMsg(msg);
		XMS_ctsAnswerCallIn(g_KeygoeVar.ACSHandle, pDev, NULL);
		ChangeDevState(pDevInfo, DEV_STATE_WAITCONNECT);
		break;
	case XMS_EVT_CALLOUT:
	case XMS_EVT_ANSWERCALL:
		pCallData = (Acs_CallControl_Data*)FetchEventData(pAcsEvt);
		if(pCallData->m_s32AcsEvtState != 1)	//failed
		{
			ResetServConf(pDev);
			ReleaseDev(pDev);	
			RefreshConfInfo();

			sprintf(msg, "IP(%d-%d) call connect failed!!", pDev->m_s8ModuleID, pDev->m_s16ChannelID);
			AddMsg(msg);
			break;
		}
		
		pConParam = (VoIPConnectPrivate_t*)(&pCallData->m_PrivData);
		pDevInfo->audio.RxCodec = pConParam->audio.rx.u8CodecType;
		pDevInfo->audio.RxPayloadType = pConParam->audio.rx.u8PayloadType;
		pDevInfo->audio.TxCodec= pConParam->audio.tx.u8CodecType;
		pDevInfo->audio.TxPayloadType = pConParam->audio.tx.u8PayloadType;
		pDevInfo->video.RxCodec = pConParam->video.rx.u8CodecType;
		pDevInfo->video.RxPayloadType = pConParam->video.rx.u8PayloadType;
		pDevInfo->video.TxCodec= pConParam->video.tx.u8CodecType;
		pDevInfo->video.TxPayloadType = pConParam->video.tx.u8PayloadType;

		if(pDevInfo->szFileName[0] == NULL)
			pDevInfo->szFileName[0] = (char*)malloc(256);
		if(pDevInfo->szFileName[1] == NULL)
			pDevInfo->szFileName[1] = (char*)malloc(256);
		if(pDevInfo->szFileName[2] == NULL)
			pDevInfo->szFileName[2] = (char*)malloc(256);
		if(pDevInfo->szFileName[3] == NULL)
			pDevInfo->szFileName[3] = (char*)malloc(256);			
		if(pDevInfo->video.TxCodec == VOIP_MEDIA_VIDEO_H263 ||
			pDevInfo->video.TxCodec == VOIP_MEDIA_VIDEO_H263P)
		{
			if(pDevInfo->szFileName[0] != NULL)
				sprintf(pDevInfo->szFileName[0], "%s\\servconf_basemenu-h263.3gp", g_KeygoeVar.cfg.VocPath);
			if(pDevInfo->szFileName[1] != NULL)
				sprintf(pDevInfo->szFileName[1], "%s\\servconf_create_failed-h263.3gp", g_KeygoeVar.cfg.VocPath);
			if(pDevInfo->szFileName[2] != NULL)
				sprintf(pDevInfo->szFileName[2], "%s\\servconf_join-h263.3gp", g_KeygoeVar.cfg.VocPath);
			if(pDevInfo->szFileName[3] != NULL)
				sprintf(pDevInfo->szFileName[3], "%s\\servconf_join_failed-h263.3gp",g_KeygoeVar.cfg.VocPath);
		}
		else if(pDevInfo->video.TxCodec == VOIP_MEDIA_VIDEO_MPEG4)
		{
			if(pDevInfo->szFileName[0] != NULL)
				sprintf(pDevInfo->szFileName[0], "%s\\servconf_basemenu-mpeg4.3gp", g_KeygoeVar.cfg.VocPath);
			if(pDevInfo->szFileName[1] != NULL)
				sprintf(pDevInfo->szFileName[1], "%s\\servconf_create_failed-mpeg4.3gp", g_KeygoeVar.cfg.VocPath);
			if(pDevInfo->szFileName[2] != NULL)
				sprintf(pDevInfo->szFileName[2], "%s\\servconf_join-mpeg4.3gp", g_KeygoeVar.cfg.VocPath);
			if(pDevInfo->szFileName[3] != NULL)
				sprintf(pDevInfo->szFileName[3], "%s\\servconf_join_failed-mpeg4.3gp",g_KeygoeVar.cfg.VocPath);
		}
		else if(pDevInfo->video.TxCodec == VOIP_MEDIA_VIDEO_H264)
		{
			if(pDevInfo->szFileName[0] != NULL)
				sprintf(pDevInfo->szFileName[0], "%s\\servconf_basemenu-h264.3gp", g_KeygoeVar.cfg.VocPath);
			if(pDevInfo->szFileName[1] != NULL)
				sprintf(pDevInfo->szFileName[1], "%s\\servconf_create_failed-h264.3gp", g_KeygoeVar.cfg.VocPath);
			if(pDevInfo->szFileName[2] != NULL)
				sprintf(pDevInfo->szFileName[2], "%s\\servconf_join-h264.3gp", g_KeygoeVar.cfg.VocPath);
			if(pDevInfo->szFileName[3] != NULL)
				sprintf(pDevInfo->szFileName[3], "%s\\servconf_join_failed-h264.3gp", g_KeygoeVar.cfg.VocPath);
		}
		else
		{
			if(pDevInfo->szFileName[0] != NULL)
				strcpy(pDevInfo->szFileName[0], "");
			if(pDevInfo->szFileName[1] != NULL)
				strcpy(pDevInfo->szFileName[1], "");
			if(pDevInfo->szFileName[2] != NULL)
				strcpy(pDevInfo->szFileName[2], "");
			if(pDevInfo->szFileName[3] != NULL)
				strcpy(pDevInfo->szFileName[3], "");
		}
		
		if((pDevInfo->pPlayRecDev = GetOneDev(pDev->m_s8ModuleID, XMS_DEVMAIN_VOICE, XMS_DEVSUB_MEDIA_324, DEV_STATE_FREE)) != NULL)
		{
			memset(&paramMixer, 0, sizeof(paramMixer));
			paramMixer.m_u8SRC1_Ctrl = XMS_MIXER_FROM_PLAY;
			paramMixer.m_u16SRC_ChID1 = pDevInfo->pPlayRecDev->m_s16ChannelID;
			paramMixer.m_u8Video = 0;
			SetParam(pDev, VOIP_PARAM_RTPMIXER, sizeof(paramMixer), &paramMixer);
			paramMixer.m_u8Video = 1;
			SetParam(pDev, VOIP_PARAM_RTPMIXER, sizeof(paramMixer), &paramMixer);
		}
		
		SetOverlayFile(pDev);
		strcpy(pDevInfo->szDTMF, "");
		strcpy(pDevInfo->szText, "");
		SetOverlay(pDev, 0);
		
		PlayToDev(pDev, pDevInfo->szFileName[0], MEDIA_TYPE_ANV, 1000000, NULL);

		ChangeDevState(pDevInfo, DEV_STATE_CONNECT);
		sprintf(msg, "IP(%d-%d) call connected!", pDev->m_s8ModuleID, pDev->m_s16ChannelID);
		AddMsg(msg);
		
		break;
	case XMS_EVT_RECVIODATA:
		pIOEvt = (Acs_IO_Data *)FetchEventData(pAcsEvt);
		switch (pIOEvt->m_u16IoType)
		{
		case XMS_IO_TYPE_VOIP_REGREQUEST:
			if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_REGSTATE))
			{
				// check client's info
				Acs_VoIP_REGSTATE *pRegRequest = (Acs_VoIP_REGSTATE *)FetchIOData(pAcsEvt);
				sprintf(msg, "SIP reg(%d): \"%s\" %s@%s:%d\n", pRegRequest->m_u16SlotID, pRegRequest->m_s8UserID, 
						pRegRequest->m_s8TelNo, pRegRequest->m_s8Address, pRegRequest->m_u16Port);
				AddMsg(msg);
				
				// response to registration
				// set Acs_VoIP_REGRESP::m_u8Granted to 1/0 to grant/disgrant registration,
				// fill Acs_VoIP_REGRESP::m_s8Password for sip authentication if enabled
				Acs_VoIP_REGRESP regResponse = {0};
				regResponse.m_u16SlotID = pRegRequest->m_u16SlotID;
				regResponse.m_u8Granted = 1;
				//strcpy(regResponse.m_s8Password, "passwd");
				SendIOData(pDev, XMS_IO_TYPE_VOIP_REGRESPONSE,
					sizeof(regResponse), &regResponse);
			}
			break;
		case XMS_IO_TYPE_VOIP_REGSTATE:
			if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_REGSTATE))
			{
				Acs_VoIP_REGSTATE *pRegState = (Acs_VoIP_REGSTATE *)FetchIOData(pAcsEvt);
				sprintf(msg, "SIP reg(%d) state: %d", pRegState->m_u16SlotID, pRegState->m_u8State);
				AddMsg(msg);
			}
			break;
		case XMS_IO_TYPE_VOIP_H245UII:
			if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_H245UII))
			{
				Acs_VoIP_H245UII *h245Uii = (Acs_VoIP_H245UII *)FetchIOData(pAcsEvt);
				sprintf(msg, "<IP(%d-%d)> Rx h245UII: %s", pDev->m_s8ModuleID, pDev->m_s16ChannelID, h245Uii->m_s8Signal);
				AddMsg(msg);
			}
			break;
		case XMS_IO_TYPE_VOIP_SIPINFO:
			if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_SIPINFO))
			{
				Acs_VoIP_SIPINFO *sipInfo = (Acs_VoIP_SIPINFO *)FetchIOData(pAcsEvt);
				sprintf(msg, "<IP(%d-%d)> Rx SIPINFO: %s", pDev->m_s8ModuleID, pDev->m_s16ChannelID, 
						sipInfo->m_s8ContentType, sipInfo->m_s8Body);
				AddMsg(msg);
			}
			break;
		case XMS_IO_TYPE_VOIP_RTPDTMF:
			if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_RTPDTMF))
			{
				Acs_VoIP_RTPDTMF *rtpDtmf = (Acs_VoIP_RTPDTMF *)FetchIOData(pAcsEvt);
				if(strlen(pDevInfo->szDTMF)+1 < 32)
					sprintf(pDevInfo->szDTMF, "%s%c", pDevInfo->szDTMF, rtpDtmf->m_s8EventChar);
				sprintf(msg, "<IP(%d-%d)> Rx RTPDTMF: %c", pDev->m_s8ModuleID, pDev->m_s16ChannelID, rtpDtmf->m_s8EventChar);
				AddMsg(msg);
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	ServConfFlow(pDev);
}
	
DJ_Void EvtHandler(DJ_U32 esrParam)
{
	Acs_Evt_t *	pAcsEvt = NULL;
	Acs_Media3GPPProc_Data* pMedia = NULL;
	char		TmpStr[256];

	pAcsEvt = (Acs_Evt_t *) esrParam;

	sprintf(TmpStr, "<%s>(%d, %d, %d, %d)", GetEvtName(pAcsEvt->m_s32EventType),
			pAcsEvt->m_DeviceID.m_s8ModuleID, pAcsEvt->m_DeviceID.m_s16ChannelID,
			pAcsEvt->m_DeviceID.m_s16DeviceMain, pAcsEvt->m_DeviceID.m_s16DeviceSub);
	//AddMsg(TmpStr);
	
	switch (pAcsEvt->m_s32EventType)
	{
	case XMS_EVT_OPEN_STREAM:
		AddMsg(TmpStr);
		break;
	case XMS_EVT_QUERY_DEVICE:
		OnEvtQueryDev(pAcsEvt);
		break; 
	case XMS_EVT_QUERY_DEVICE_END:
		AddMsg(TmpStr);
		OnEvtQueryDevEnd(pAcsEvt);
		break;		
	case XMS_EVT_QUERY_ONE_DSP_START:
		AddMsg(TmpStr);
		break;	
	case XMS_EVT_QUERY_ONE_DSP_END:
		AddMsg(TmpStr);
		break;	
	case XMS_EVT_QUERY_REMOVE_ONE_DSP_START:
		AddMsg(TmpStr);
		break;	
	case XMS_EVT_QUERY_REMOVE_ONE_DSP_END:
		AddMsg(TmpStr);
		break;	
	case XMS_EVT_OPEN_DEVICE:
		OnEvtOpenDev(pAcsEvt);
		break;
	case XMS_EVT_CLOSE_DEVICE:	
		OnEvtCloseDev(pAcsEvt);
		break;
	case XMS_EVT_DEVICESTATE:
		OnEvtDevState(pAcsEvt);
		break;
	case XMS_EVT_UNIFAILURE:
		break;
	case XMS_EVT_3GPP_INIT_INDEX:
		AddMsg("EVT: Init 3gpp play index succeed!");
		break;
	case XMS_EVT_3GPP_BUILD_INDEX:
		pMedia=(Acs_Media3GPPProc_Data*)FetchEventData(pAcsEvt);
		if(pMedia->m_u8MediaType == MEDIA_TYPE_AUDIO)
			sprintf(TmpStr, "EVT: Build 3gpp index(A:%d)", pMedia->m_u32AudioCurFileIndex);
		else if(pMedia->m_u8MediaType == MEDIA_TYPE_VIDEO)
			sprintf(TmpStr, "EVT: Build 3gpp index(V:%d)", pMedia->m_u32VideoCurFileIndex);
		else if(pMedia->m_u8MediaType == MEDIA_TYPE_ANV)
			sprintf(TmpStr, "EVT: Build 3gpp index(A:%d, V:%d)", pMedia->m_u32AudioCurFileIndex, pMedia->m_u32VideoCurFileIndex);
		else
			sprintf(TmpStr, "EVT: Build 3gpp index, error type");
		AddMsg(TmpStr);
		break;
/************************************************************************/
/* Video Conf Evt                                                       */
/* start                                                                */
/************************************************************************/
		case XMS_EVT_3GVCONF_JOIN:
		{
			Acs_JoinTo3GVConf_Data *pEvtData = (Acs_JoinTo3GVConf_Data*)FetchEventData(pAcsEvt);
			sprintf(TmpStr, "3GVCONF_JOIN %d %d", pEvtData->m_s32AcsEvtState, pEvtData->m_s32AcsEvtErrCode);
			AddMsg(TmpStr);
		}
		break;
	case XMS_EVT_3GVCONF_LEAVE:
		{
			Acs_LeaveFrom3GVConf_Data *pEvtData = (Acs_LeaveFrom3GVConf_Data*)FetchEventData(pAcsEvt);
			sprintf(TmpStr, "3GVCONF_LEAVE %d %d", pEvtData->m_s32AcsEvtState, pEvtData->m_s32AcsEvtErrCode);
			AddMsg(TmpStr);
		}
		break;
	case XMS_EVT_3GVCONF_CLEAR:
		{
			Acs_Clear3GVConf_Data *pEvtData = (Acs_Clear3GVConf_Data*)FetchEventData(pAcsEvt);
			sprintf(TmpStr, "3GVCONF_CLEAR %d %d", pEvtData->m_s32AcsEvtState, pEvtData->m_s32AcsEvtErrCode);
			AddMsg(TmpStr);
		}
		break;
	case XMS_EVT_3GVCONF_GETLAYOUT:
		{
			Acs_GetLayout_Data *pEvtData = (Acs_GetLayout_Data*)FetchEventData(pAcsEvt);
			memcpy(&g_layoutList, &pEvtData->m_list, sizeof(Acs_3GVConf_LayoutList));
			sprintf(TmpStr, "3GVCONF_GETLAYOUT %d %d", pEvtData->m_s32AcsEvtState, pEvtData->m_s32AcsEvtErrCode);
			AddMsg(TmpStr);
		}
		break;
	case XMS_EVT_3GVCONF_SETLAYOUT:
		{
			Acs_SetLayout_Data *pEvtData = (Acs_SetLayout_Data*)FetchEventData(pAcsEvt);
			sprintf(TmpStr, "3GVCONF_SETLAYOUT %d %d", pEvtData->m_s32AcsEvtState, pEvtData->m_s32AcsEvtErrCode);
			AddMsg(TmpStr);
		}
		break;
	case XMS_EVT_3GVCONF_GETVISIBLELIST:
		{
			Acs_GetVisibleList_Data *pEvtData = (Acs_GetVisibleList_Data*)FetchEventData(pAcsEvt);
			memcpy(&g_visibleList, &pEvtData->m_list, sizeof(Acs_3GVConf_VisibleList));
			sprintf(TmpStr, "3GVCONF_GETVISIBLELIST %d %d", pEvtData->m_s32AcsEvtState, pEvtData->m_s32AcsEvtErrCode);
			AddMsg(TmpStr);
		}
		break;
	case XMS_EVT_3GVCONF_SETVISIBLELIST:
		{
			Acs_SetVisibleList_Data *pEvtData = (Acs_SetVisibleList_Data*)FetchEventData(pAcsEvt);
			sprintf(TmpStr, "3GVCONF_SETVISIBLELIST %d %d", pEvtData->m_s32AcsEvtState, pEvtData->m_s32AcsEvtErrCode);
			AddMsg(TmpStr);
		}
		break;
/************************************************************************/
/* end                                                                  */
/************************************************************************/
	default:
		switch(pAcsEvt->m_DeviceID.m_s16DeviceMain) 
		{
		case XMS_DEVMAIN_VOIP:
			OnEvtIp(pAcsEvt);
			break;
		case XMS_DEVMAIN_VOICE:
			OnEvtVoc(pAcsEvt);
			break;
		case XMS_DEVMAIN_INTERFACE_CH:
			OnEvtTrk(pAcsEvt);
			break;
		default:
			break;
		}
		break;
	}
}
