using System;
using System.IO;
using System.Windows;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Runtime.InteropServices;

using DJKeygoe;

namespace Dial
{
    public partial class DialForm : Form
    {
        public struct SystemTime
        {
            public ushort wYear;
            public ushort wMonth;
            public ushort wDayOfWeek;
            public ushort wDay;
            public ushort wHour;
            public ushort wMinute;
            public ushort wSecond;
        }

        [DllImport("kernel32")]
        public static unsafe extern void GetLocalTime(SystemTime* st);

        public DialForm()
        {
            InitializeComponent();
            pDial = this;
            InitSystem();
            iLoopTrunkStart = 0;
            fs = new FileStream("Exception Lof File .Log", FileMode.Create, FileAccess.Write); //创建异常文件记录
            sw = new StreamWriter(fs);
        }

        public static DJDialGlobals g_DJDialGlobals = new DJDialGlobals();
        public static DJAcsApiDef.EsrFunc g_ESRFuncPtr;
        public static DialForm pDial;
        public static FileStream fs;
        public static StreamWriter sw;
        public static int iLoopTrunkStart;

        public string GetEventTypeString(int iEvtType)
        {
            switch ((XMS_EVT_TYPE)iEvtType)
            {
                case XMS_EVT_TYPE.XMS_EVT_OPEN_STREAM: return "OPEN_STREAM";
                case XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE: return "QUERY_DEVICE";
                case XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE_END: return "QUERY_DEVICE_END";
                case XMS_EVT_TYPE.XMS_EVT_OPEN_DEVICE: return "OPEN_DEVICE";
                case XMS_EVT_TYPE.XMS_EVT_CLOSE_DEVICE: return "CLOSE_DEVICE";
                case XMS_EVT_TYPE.XMS_EVT_RESET_DEVICE: return "RESET_DEVICE";
                case XMS_EVT_TYPE.XMS_EVT_DEVICESTATE: return "DEVICESTATE";
                case XMS_EVT_TYPE.XMS_EVT_SETDEV_GROUP: return "SETDEV_GROUP";
                case XMS_EVT_TYPE.XMS_EVT_SETPARAM: return "SETPARAM";
                case XMS_EVT_TYPE.XMS_EVT_GETPARAM: return "GETPARAM";
                case XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_START: return "QUERY_ONE_DSP_START";
                case XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_END: return "QUERY_ONE_DSP_END";
                case XMS_EVT_TYPE.XMS_EVT_QUERY_REMOVE_ONE_DSP_START: return "QUERY_REMOVE_ONE_DSP_START";
                case XMS_EVT_TYPE.XMS_EVT_QUERY_REMOVE_ONE_DSP_END: return "QUERY_REMOVE_ONE_DSP_END";

                case XMS_EVT_TYPE.XMS_EVT_CALLOUT: return "CALLOUT";
                case XMS_EVT_TYPE.XMS_EVT_CALLIN: return "CALLIN";
                case XMS_EVT_TYPE.XMS_EVT_ALERTCALL: return "ALERTCALL";
                case XMS_EVT_TYPE.XMS_EVT_ANSWERCALL: return "ANSWERCALL";
                case XMS_EVT_TYPE.XMS_EVT_LINKDEVICE: return "LINKDEVICE";
                case XMS_EVT_TYPE.XMS_EVT_UNLINKDEVICE: return "UNLINKDEVICE";
                case XMS_EVT_TYPE.XMS_EVT_CLEARCALL: return "CLEARCALL";
                case XMS_EVT_TYPE.XMS_EVT_ANALOG_INTERFACE: return "ANALOG_INTERFACE";
                case XMS_EVT_TYPE.XMS_EVT_CAS_MFC_START: return "CAS_MFC_START";
                case XMS_EVT_TYPE.XMS_EVT_CAS_MFC_END: return "CAS_MFC_END";

                case XMS_EVT_TYPE.XMS_EVT_JOINTOCONF: return "JOINTOCONF";
                case XMS_EVT_TYPE.XMS_EVT_LEAVEFROMCONF: return "LEAVEFROMCONF";
                case XMS_EVT_TYPE.XMS_EVT_CLEARCONF: return "CLEARCONF";


                case XMS_EVT_TYPE.XMS_EVT_PLAY: return "PLAY";
                case XMS_EVT_TYPE.XMS_EVT_INITINDEX: return "INITINDEX";
                case XMS_EVT_TYPE.XMS_EVT_BUILDINDEX: return "BUILDINDEX";
                case XMS_EVT_TYPE.XMS_EVT_CONTROLPLAY: return "CONTROLPLAY";
                case XMS_EVT_TYPE.XMS_EVT_RECORD: return "RECORD";
                case XMS_EVT_TYPE.XMS_EVT_CONTROLRECORD: return "CONTROLRECORD";

                case XMS_EVT_TYPE.XMS_EVT_SENDFAX: return "SENDFAX";
                case XMS_EVT_TYPE.XMS_EVT_RECVFAX: return "RECVFAX";

                case XMS_EVT_TYPE.XMS_EVT_SENDIODATA: return "SENDIODATA";
                case XMS_EVT_TYPE.XMS_EVT_RECVIODATA: return "RECVIODATA";

                case XMS_EVT_TYPE.XMS_EVT_MODMONITOR: return "MODMONITOR";

                case XMS_EVT_TYPE.XMS_EVT_UNIFAILURE: return "UNIFAILURE";
            }

            return "UNKNOWN";
        }

        public string GetString_PcmType(int iPcmType)
        {
            switch((XMS_E1_TYPE)iPcmType)
            {
                case XMS_E1_TYPE.XMS_E1_TYPE_NULL: return  "Disable";
                case XMS_E1_TYPE.XMS_E1_TYPE_Analog30: return "T_Analog30";
                case XMS_E1_TYPE.XMS_E1_TYPE_PCM31: return "T_PCM31";
                case XMS_E1_TYPE.XMS_E1_TYPE_PCM30: return "T_PCM30";
                case XMS_E1_TYPE.XMS_E1_TYPE_CAS: return "T_CAS";
                case XMS_E1_TYPE.XMS_E1_TYPE_PRI: return "T_PRI";
                case XMS_E1_TYPE.XMS_E1_TYPE_SS7_TUP_0_Link: return "T_TUP_0_LK";
                case XMS_E1_TYPE.XMS_E1_TYPE_SS7_TUP_1_Link: return "T_TUP_1_LK";
                case XMS_E1_TYPE.XMS_E1_TYPE_SS7_TUP_2_Link: return "T_TUP_2_LK";
                case XMS_E1_TYPE.XMS_T1_TYPE_D4: return "T_D4";
                case XMS_E1_TYPE.XMS_T1_TYPE_ESF: return "T_ESF";
                case XMS_E1_TYPE.XMS_J1_TYPE_D4: return "J_D4";
                case XMS_E1_TYPE.XMS_J1_TYPE_ESF: return "J_ESF"; 
                case XMS_E1_TYPE.XMS_SLC_TYPE_96: return "SLC_TYPE_96";
                case XMS_E1_TYPE.XMS_E1_TYPE_SS7_ISUP_0_Link: return "T_ISUP_0_LK";
                case XMS_E1_TYPE.XMS_E1_TYPE_SS7_ISUP_1_Link: return "T_ISUP_1_LK";
                case XMS_E1_TYPE.XMS_E1_TYPE_SS7_ISUP_2_Link: return "T_ISUP_2_LK";
                case XMS_E1_TYPE.XMS_E1_TYPE_6D25B: return "T_6D25B";
            }
            return "UNKNOWN";
        }

        public string GetString_LineState(int iLineState)
        {
            switch ((DEVICE_CALL_STATE)iLineState)
            {
                case DEVICE_CALL_STATE.DEVICE_COMMON_STATE_START: return  "S_START";
                case DEVICE_CALL_STATE.DCS_FREE: return "S_FREE";
                case DEVICE_CALL_STATE.DCS_LOCAL_BLOCK: return "S_LOCAL_BLOCK";
                case DEVICE_CALL_STATE.DCS_REMOTE_BLOCK: return "S_REMOTE_BLOCK";
                case DEVICE_CALL_STATE.DCS_BLOCK: return "S_BLOCK";
                case DEVICE_CALL_STATE.DCS_UNAVAILABLE: return "S_UNAVAILABLE";

                case DEVICE_CALL_STATE.DCS_CALLOUT: return "S_CALLOUT";
                case DEVICE_CALL_STATE.DCS_CALLIN: return "S_CALLIN";
                case DEVICE_CALL_STATE.DCS_ALERTING: return "S_ALERTING";

                case DEVICE_CALL_STATE.DCS_CONNECT: return "S_CONNECT";
                case DEVICE_CALL_STATE.DCS_DISCONNECT: return "S_DISCONNECT";
                case DEVICE_CALL_STATE.DCS_WAIT_FREE: return "S_WAIT_FREE";
            }
            return "UNKNOWN";
        }

        public string GetString_State(int iState)
        {
            switch ((DJDialGlobals.TRUNK_STATE)iState)
            {
                case DJDialGlobals.TRUNK_STATE.TRK_WAITOPEN: return "Wait Open";
                case DJDialGlobals.TRUNK_STATE.TRK_FREE: return "Free";
                case DJDialGlobals.TRUNK_STATE.TRK_NOTHANDLE: return "NotHandle";
                case DJDialGlobals.TRUNK_STATE.TRK_CALLOUT: return "CallOut";
                case DJDialGlobals.TRUNK_STATE.TRK_SIM_CALLOUT: return "SimCallOut";
                case DJDialGlobals.TRUNK_STATE.TRK_SIM_LINK: return "SimLinkOk";
                case DJDialGlobals.TRUNK_STATE.TRK_SIM_ANALOG_OFFHOOK: return "OffHook";
                case DJDialGlobals.TRUNK_STATE.TRK_SIM_ANALOG_DIALING: return "Dialing";
                case DJDialGlobals.TRUNK_STATE.TRK_LINK: return "Link";
                case DJDialGlobals.TRUNK_STATE.TRK_PLAYDTMF: return "PlayDtmf";
                case DJDialGlobals.TRUNK_STATE.TRK_HANGUP: return "HangUp";
                case DJDialGlobals.TRUNK_STATE.TRK_FAIL: return "FAIL";
                case DJDialGlobals.TRUNK_STATE.TRK_WAIT_REMOVE: return "Remove DSP";
                default: return "UNKNOWN";
            }
        }

        public string GetDevTypeString(int iDevType)
        {
            switch ((XMS_DEVMAIN_TYPE)iDevType)
            {
                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE: return "VOC";
                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_FAX: return "FAX";
                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT: return "DIGIT";
                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH: return "INTCH";
                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DSS1_LINK: return "DSS1";
                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_SS7_LINK: return "SS7";
                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD: return "BRD";
                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_CTBUS_TS: return "CTBUS";
                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOIP: return "VOIP";
                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_CONFERENCE: return "CONF";
                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VIDEO: return "VIDEO";
                default: return "UNKNOWN";
            }
        }

        public string GetSubDevTypeString(int iSubDevType)
        {
            switch((XMS_INTERFACE_DEVSUB_TYPE)iSubDevType)
            {
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_BASE: return "BASE   ";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK: return "A_TRUNK";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER: return "A_USER ";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_HIZ: return "A_HIZ  ";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_EMPTY: return "A_EMPTY";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_PCM: return "E1_PCM ";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_CAS: return "E1_CAS ";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_DSS1: return "E1_DSS1";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_TUP: return "E1_TUP ";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_ISUP: return "E1_ISUP";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_VOC2W: return "A_VOC2W";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_VOC4W: return "A_VOC4W";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_EM: return "A_EM   ";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_DCH: return "E1_DCH ";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_BCH: return "E1_BCH ";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_UNUSABLE: return "UNUSE  ";

	            // new add next types from V2.2.0
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_HIZ_CAS: return "HIZ_CAS";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_HIZ_PRI: return "HIZ_PRI";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_HIZ_SS7: return "HIZ_SS7";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_HIZ_PRI_LINK: return "HIZ_PRI_LINK";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_HIZ_SS7_64K_LINK: return "HIZ_SS7_64K_LINK";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_HIZ_SS7_2M_LINK: return "HIZ_SS7_2M_LINK";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_SS7_LINK: return "SS7_LINK";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_LINESIDE: return "LINESIDE";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_REC: return "A_REC";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_DIGITAL_REC: return "D_REC";
                case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_HIZ_HDLC_N64K_LINK: return "HDLC_N64_LINK";
	        }

	        return "UNKNOWN";
        }

        delegate void ListBox_AddItemCallback(string text); //界面由主线程创建 跨线程访问需要委托
        public void ListBox_AddItem(string strInfo)
        {
            if (this.listBox_OptAndEvtInfo.InvokeRequired)
            {
                ListBox_AddItemCallback d = new ListBox_AddItemCallback(ListBox_AddItem);
                this.Invoke(d, new object[] { strInfo });
            }
            else
            {
                string strMsg;

                if (g_DJDialGlobals.nNumOfListBoxItem % 10000 == 0)
                {
                    listBox_OptAndEvtInfo.Items.Clear();
                }

                g_DJDialGlobals.nNumOfListBoxItem++;
                strMsg = String.Format("{0,4} {1}", g_DJDialGlobals.nNumOfListBoxItem, strInfo);
                listBox_OptAndEvtInfo.Items.Add(strMsg);

                strMsg = null;
            }

            strInfo = null;
        }

        public unsafe void ShowEvtInfo(Acs_Evt_t* pAcsEvt)
        {
            string TmpStr;
            string TmpS;

            TmpStr = GetEventTypeString(pAcsEvt->m_s32EventType);

            switch (pAcsEvt->m_s32EventType)
            {
                case (int)XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE:
                    {
                        Acs_Dev_List_Head_t* pAcsDevList = (Acs_Dev_List_Head_t*)((byte*)pAcsEvt + sizeof(Acs_Evt_t));

                        TmpS = String.Format(" Dev=({0},{1:2},{2:3})", GetDevTypeString(pAcsDevList->m_s32DeviceMain), pAcsDevList->m_s32ModuleID, pAcsDevList->m_s32DeviceNum);
                        TmpStr += TmpS;
                    }
                    break;

                case (int)XMS_EVT_TYPE.XMS_EVT_RECVIODATA:
                    {
                        Acs_IO_Data* pIoData = (Acs_IO_Data*)((byte*)pAcsEvt + sizeof(Acs_Evt_t));

                        TmpS = String.Format(" Dev=({0}, {1}, {2}), DataType={3}, DataLen={4}", GetDevTypeString(pAcsEvt->m_DeviceID.m_s16DeviceMain),
                            pAcsEvt->m_DeviceID.m_s8ModuleID, pAcsEvt->m_DeviceID.m_s16ChannelID, pIoData->m_u16IoType, pIoData->m_u16IoDataLen);

                        TmpStr += TmpS;
                    }
                    break;

                default:
                    {
                        TmpS = String.Format(" Dev=({0}, {1}, {2})",
                            GetDevTypeString(pAcsEvt->m_DeviceID.m_s16DeviceMain), pAcsEvt->m_DeviceID.m_s8ModuleID, pAcsEvt->m_DeviceID.m_s16ChannelID);
                        TmpStr += TmpS;
                    }
                    break;
            }
            ListBox_AddItem(TmpStr);

            TmpStr = null;
            TmpS = null;
        }

        delegate void DrawCountCallBack(int nRow,int nColumn,string strMsg);
        public void DrawCount(int nRow,int nColumn,string strMsg) //到listview_count的nRow行nColumn列写字符串
        {
            if (this.listView_count.InvokeRequired)
            {
                DrawCountCallBack d = new DrawCountCallBack(DrawCount);
                this.Invoke(d, new object[]{nRow,nColumn,strMsg});
            }
            else
            {
                listView_count.Items[nRow].SubItems[nColumn].Text = strMsg;
            }

            strMsg = null;
        }

        delegate void DrawMainCallBack(int nRow,int nColumn,string strMsg);
        public void DrawMain(int nRow,int nColumn,string strMsg) 
        {
            if (this.listView_Main.InvokeRequired)
            {
                DrawMainCallBack d = new DrawMainCallBack(DrawMain);
                this.Invoke(d, new object[]{nRow,nColumn,strMsg});
            }
            else
            {
                listView_Main.Items[nRow].SubItems[nColumn].Text = strMsg;
            }

            strMsg = null;
        }

        delegate void DrawUserCallBack(int nRow,int nColumn,string strMsg);
        public void DrawUser(int nRow,int nColumn,string strMsg) 
        {
            if (this.listView_user.InvokeRequired)
            {
                DrawUserCallBack d = new DrawUserCallBack(DrawUser);
                this.Invoke(d, new object[]{nRow,nColumn,strMsg});
            }
            else
            {
                listView_user.Items[nRow].SubItems[nColumn].Text = strMsg;
            }

            strMsg = null;
        }

        delegate void DrawPcmCallBack(int nRow,int nColumn,string strMsg);
        public void DrawPcm(int nRow,int nColumn,string strMsg) 
        {
            if (this.listView_pcm.InvokeRequired)
            {
                DrawPcmCallBack d = new DrawPcmCallBack(DrawPcm);
                this.Invoke(d, new object[]{nRow,nColumn,strMsg});
            }
            else
            {
                listView_pcm.Items[nRow].SubItems[nColumn].Text = strMsg;
            }

            strMsg = null;
        }

        delegate void AddMainItemCallBack();
        public void AddMainItem()
        {
            if (this.listView_Main.InvokeRequired)
            {
                AddMainItemCallBack d = new AddMainItemCallBack(AddMainItem);
                this.Invoke(d, new object[] { });
            }
            else
            {
                for (int i =listView_Main.Items.Count; i < g_DJDialGlobals.g_iTotalTrunk; i++)
                {
                    ListViewItem listItem = new ListViewItem(i.ToString());
                    for (int j = 0; j < 8; j++)
                    {
                        listItem.SubItems.Add("");
                    }
                    listView_Main.Items.Add(listItem);
                }
            }
        }
             
        bool g_bAddOfTotal = true;

        delegate void AddCountItemCallBack();
        public void AddCountItem()
        {
            if (this.listView_count.InvokeRequired)
            {
                AddCountItemCallBack d = new AddCountItemCallBack(AddCountItem);
                this.Invoke(d, new object[] { });
            }
            else
            {
                if (g_bAddOfTotal)
                {
                    ListViewItem ItemTotal = new ListViewItem("Total");
                    for (int j = 0; j < 8; j++)
                    {
                        ItemTotal.SubItems.Add("");
                    }
                    listView_count.Items.Add(ItemTotal);

                    for (int i = 0; i < g_DJDialGlobals.g_iTotalModule; i++)
                    {
                        ListViewItem listItem = new ListViewItem(i.ToString());
                        for (int j = 0; j < 8; j++)
                        {
                            listItem.SubItems.Add("");
                        }
                        listView_count.Items.Add(listItem);
                    }
                    g_bAddOfTotal = false;
                }
                else
                {
                    for (int i = listView_count.Items.Count; i < g_DJDialGlobals.g_iTotalModule+1; i++)
                    {
                        ListViewItem listItem = new ListViewItem((i-1).ToString());
                        for (int j = 0; j < 8; j++)
                        {
                            listItem.SubItems.Add("");
                        }
                        listView_count.Items.Add(listItem);
                    }
                }
            }
        }

        delegate void AddUserItemCallBack();
        public void AddUserItem()
        {
            if (this.listView_user.InvokeRequired)
            {
                AddUserItemCallBack d = new AddUserItemCallBack(AddUserItem);
                this.Invoke(d, new object[] { });
            }
            else
            {
                for (int i = 0; i < g_DJDialGlobals.g_iTotalUser; i++)
                {
                    ListViewItem listItem = new ListViewItem(i.ToString());
                    for (int j = 0; j < 7; j++)
                    {
                        listItem.SubItems.Add("");
                    }
                    listView_user.Items.Add(listItem);
                }
            }
        }

        delegate void AddPcmItemCallBack();
        public void AddPcmItem()
        {
            if (this.listView_pcm.InvokeRequired)
            {
                AddPcmItemCallBack d = new AddPcmItemCallBack(AddPcmItem);
                this.Invoke(d, new object[] { });
            }
            else
            {
                for (int i = listView_pcm.Items.Count; i < g_DJDialGlobals.g_iTotalPcm; i++)
                {
                    ListViewItem listItem = new ListViewItem(i.ToString());
                    for (int j = 0; j < 6; j++)
                    {
                        listItem.SubItems.Add("");
                    }
                    listView_pcm.Items.Add(listItem);
                }
            }
        }

        public unsafe void DrawUser_DTMF(DJDialGlobals.TRUNK_STRUCT* pOneUser)
        {
            char[] szDtmf = new char[2 * (pOneUser->DtmfCount + 1)];

            szDtmf.Initialize();
            SBytesToChars((byte*)pOneUser->DtmfBuf, szDtmf, pOneUser->DtmfCount + 1);

            string strDtmf = new string(szDtmf);
            DrawUser(pOneUser->iUserSeqID, 5, strDtmf);

            strDtmf = null;
            szDtmf = null;
        }

        public void DrawMain_LineState(int iSeqID,int iLineState)
        {
            string strMsg;
            strMsg = GetString_LineState(iLineState);
            DrawMain(iSeqID, 3, strMsg);

            strMsg = null;
        }

        public void DrawMain_State(int iSeqID, int iState)
        {
            string strMsg;
            strMsg = GetString_State(iState);
            DrawMain(iSeqID, 4, strMsg);

            strMsg = null;
        }

        public void DrawUser_State(int iSeqID, int iUserState)
        {
            string strMsg;

            strMsg = GetString_UserState(iUserState);
            DrawUser(iSeqID, 4, strMsg);

            strMsg = null;
        }

        public void DrawCount_RemoveState(sbyte s8ModID)
        {
            string strMsg;

            strMsg = "";
            switch ((DJDialGlobals.REMOVE_STATE)g_DJDialGlobals.AllDeviceRes[s8ModID].RemoveState)
            {
                case DJDialGlobals.REMOVE_STATE.DSP_REMOVE_STATE_NONE: strMsg = ""; break;
                case DJDialGlobals.REMOVE_STATE.DSP_REMOVE_STATE_START: strMsg = "Start"; break;
                case DJDialGlobals.REMOVE_STATE.DSP_REMOVE_STATE_READY: strMsg = "Ready"; break;
            }
            DrawCount(g_DJDialGlobals.AllDeviceRes[s8ModID].iSeqID + 1, 8, strMsg);

            strMsg = null;
        }

        public unsafe void DrawMain_Analog_Reason(DJDialGlobals.TRUNK_STRUCT* pOneTrunk, string ErrStr)
        {
            DrawMain(pOneTrunk->iSeqID, 8, ErrStr);

            ErrStr = null;
        }

        public unsafe void DrawMain_Reason(DJDialGlobals.TRUNK_STRUCT* pOneTrunk, int s32ErrCode, int s32ClearCause)
        {
            string strMsg;

            strMsg = String.Format("Err={0},Cause={1}", s32ErrCode, s32ClearCause);
            DrawMain(pOneTrunk->iSeqID,8, strMsg);

            strMsg = null;
        }

        public  void CheckRemoveReady(sbyte s8DspModID)
        {
            // check device : INTERFACE_CH
            for (int i = 0; i < g_DJDialGlobals.AllDeviceRes[s8DspModID].lTrunkNum; i++)
            {
                if ((g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk[i].State != DJDialGlobals.TRUNK_STATE.TRK_WAITOPEN)
                    && (g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk[i].State != DJDialGlobals.TRUNK_STATE.TRK_WAIT_REMOVE)
                    && (g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk[i].State != DJDialGlobals.TRUNK_STATE.TRK_NOTHANDLE))
                {
                    return;
                }

                if (g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk[i].deviceID.m_s16DeviceSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER)
                {
                    if ((g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk[i].UserState != DJDialGlobals.USER_STATE.USER_WAITOPEN)
                        && (g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk[i].UserState != DJDialGlobals.USER_STATE.USER_WAIT_REMOVE))
                    {
                        return;
                    }
                }

            }

            // check device : VOICE
            for (int i = 0; i < g_DJDialGlobals.AllDeviceRes[s8DspModID].lVocNum; i++)
            {
                if ((g_DJDialGlobals.AllDeviceRes[s8DspModID].pVoice[i].State != DJDialGlobals.VOICE_STATE.VOC_WAITOPEN)
                    && (g_DJDialGlobals.AllDeviceRes[s8DspModID].pVoice[i].State != DJDialGlobals.VOICE_STATE.VOC_WAIT_REMOVE))
                {
                    return;
                }
            }

            // all device in this DSP is ready for remove 
            g_DJDialGlobals.AllDeviceRes[s8DspModID].RemoveState = DJDialGlobals.REMOVE_STATE.DSP_REMOVE_STATE_READY;
            DrawCount_RemoveState(s8DspModID);
        }

        public unsafe void Change_Voc_State(DJDialGlobals.VOICE_STRUCT* pOneVoice, DJDialGlobals.VOICE_STATE NewState)
        {
            pOneVoice->State = NewState;

            // Check if ready to remove DSP hardware
            if ((g_DJDialGlobals.AllDeviceRes[pOneVoice->deviceID.m_s8ModuleID].RemoveState == DJDialGlobals.REMOVE_STATE.DSP_REMOVE_STATE_START)
                && (NewState == DJDialGlobals.VOICE_STATE.VOC_FREE))
            {
                pOneVoice->State = DJDialGlobals.VOICE_STATE.VOC_WAIT_REMOVE;

                CheckRemoveReady(pOneVoice->deviceID.m_s8ModuleID);
            }
        }

        public unsafe void Change_UserState(DJDialGlobals.TRUNK_STRUCT* pOneTrunk, DJDialGlobals.USER_STATE NewState)
        {
            pOneTrunk->UserState = NewState;
            DrawUser_State(pOneTrunk->iUserSeqID, (int)pOneTrunk->UserState);

            if ((g_DJDialGlobals.AllDeviceRes[pOneTrunk->deviceID.m_s8ModuleID].RemoveState == DJDialGlobals.REMOVE_STATE.DSP_REMOVE_STATE_START)
                && (NewState == DJDialGlobals.USER_STATE.USER_FREE))
            {
                pOneTrunk->UserState = DJDialGlobals.USER_STATE.USER_WAIT_REMOVE;

                DrawUser_State(pOneTrunk->iUserSeqID, (int)pOneTrunk->UserState);

                CheckRemoveReady(pOneTrunk->deviceID.m_s8ModuleID);
            }
        }

        public unsafe void DrawUser_VocInfo(DJDialGlobals.TRUNK_STRUCT* pOneUser)
        {
            string strMsg;

            if (pOneUser->VocDevID.m_s16DeviceMain != -1)
            {
                strMsg = String.Format("{0},{1}",pOneUser->VocDevID.m_s8ModuleID,pOneUser->VocDevID.m_s16ChannelID);
            }
            else
            {
                strMsg = "";
            }
            DrawUser(pOneUser->iUserSeqID, 6, strMsg);

            strMsg = null;
        }

        public unsafe void DrawUser_LinkDev(DJDialGlobals.TRUNK_STRUCT* pOneUser)
        {
            string strMsg;

            if (pOneUser->VocDevID.m_s16DeviceMain != -1)
            {
                strMsg = String.Format("{0},{1}",pOneUser->LinkDevID.m_s8ModuleID, pOneUser->LinkDevID.m_s16ChannelID);
            }
            else
            {
                strMsg = "";
            }
            DrawUser(pOneUser->iUserSeqID, 7, strMsg);

            strMsg = null;
        }

        public unsafe void DrawMain_LinkDev(DJDialGlobals.TRUNK_STRUCT* pOneTrunk)
        {
            string strMsg;

            if (pOneTrunk->LinkDevID.m_s16DeviceMain != 0)
                strMsg = String.Format("{0},{1}", pOneTrunk->LinkDevID.m_s8ModuleID, pOneTrunk->LinkDevID.m_s16ChannelID);
            else
                strMsg = "";

            DrawMain(pOneTrunk->iSeqID, 7, strMsg);
            
            strMsg = null;
        }

        public unsafe void InitUserChannel(DJDialGlobals.TRUNK_STRUCT* pOneUser)
        {
            Change_UserState(pOneUser, DJDialGlobals.USER_STATE.USER_FREE);
            pOneUser->DtmfCount = 0;
            pOneUser->DtmfBuf[0] = 0;

            memset((byte*)&pOneUser->VocDevID, 0, sizeof(DeviceID_t));		// 0: didn't alloc Voc Device
            memset((byte*)&pOneUser->LinkDevID, 0, sizeof(DeviceID_t));		// 0: didn't alloc Link Device

            DrawUser_VocInfo(pOneUser);
            DrawUser_LinkDev(pOneUser);
        }

        public unsafe void InitTrunkChannel(DJDialGlobals.TRUNK_STRUCT* pOneTrunk)
        {
            Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_FREE);

            memset((byte*)&pOneTrunk->VocDevID, 0, sizeof(DeviceID_t));		// 0: didn't alloc Voc Device
            memset((byte*)&pOneTrunk->LinkDevID, 0, sizeof(DeviceID_t));	// 0: didn't alloc Link Device

            DrawMain_LinkDev(pOneTrunk);
        }

        public unsafe void DrawMain_CallInfo(DJDialGlobals.TRUNK_STRUCT* pOneTrunk)
        {
            string strCallee = new string(pOneTrunk->CalleeCode);
            string strCalled = new string(pOneTrunk->CallerCode);

            //SBytesToChars()
            DrawMain(pOneTrunk->iSeqID, 5, strCallee);
            DrawMain(pOneTrunk->iSeqID, 6, strCalled);

            strCallee = null;
            strCalled = null;
        }

        public unsafe void DrawPcm_TypeAndAlarm(DJDialGlobals.PCM_STRUCT* pOnePcm)
        {
            string strMsg;

            strMsg = GetString_PcmType(pOnePcm->u8E1Type);
            DrawPcm(pOnePcm->iSeqID, 1, strMsg);

            strMsg = null;

            strMsg = String.Format("0x{0:x}", pOnePcm->s32AlarmVal);
            DrawPcm(pOnePcm->iSeqID, 2, strMsg);

            if ((pOnePcm->s32AlarmVal & (int)XMS_E1PORT_MASK_STATE.XMS_E1PORT_MASK_LOST_SIGNAL) != 0)
            {
                DrawPcm(pOnePcm->iSeqID, 3, "X");
            }
            else
            {
                DrawPcm(pOnePcm->iSeqID, 3, "O");
            }

            if ((pOnePcm->s32AlarmVal & (int)XMS_E1PORT_MASK_STATE.XMS_E1PORT_MASK_FAS_ALARM) != 0)
            {
                DrawPcm(pOnePcm->iSeqID, 4, "X");
            }
            else
            {
                DrawPcm(pOnePcm->iSeqID, 4, "O");
            }

            if ((pOnePcm->s32AlarmVal & (int)XMS_E1PORT_MASK_STATE.XMS_E1PORT_MASK_REMOTE_ALARM) != 0)
            {
                DrawPcm(pOnePcm->iSeqID, 5, "X");
            }
            else
            {
                DrawPcm(pOnePcm->iSeqID, 5, "O");
            }

            strMsg = null;
        }

        public string GetString_UserState(int iUserState)
        {
            switch ((DJDialGlobals.USER_STATE)iUserState)
            {
                case DJDialGlobals.USER_STATE.USER_WAITOPEN: return "Wait Open";
                case DJDialGlobals.USER_STATE.USER_FREE: return "Free";
                case DJDialGlobals.USER_STATE.USER_OFFHOOK: return "OffHook";
                case DJDialGlobals.USER_STATE.USER_CALLOUT: return "CallOut";
                case DJDialGlobals.USER_STATE.USER_WAITHANGUP: return "WaitHangUp";
                case DJDialGlobals.USER_STATE.USER_LINK: return "Link";
                case DJDialGlobals.USER_STATE.USER_WAIT_REMOVE: return "Remove DSP";
                case DJDialGlobals.USER_STATE.USER_RING: return "Ring";
                default: return "UNKNOWN";
            }
        }

        public void DrawUser_LineState(int iSeqID, int iLineState)
        {
            string strMsg;

            strMsg = GetString_LineState(iLineState);
            DrawUser(iSeqID, 3, strMsg);

            strMsg = null;
        }

        public void DrawCount_Pcm (sbyte s8ModID)
        {
            string strMsg;
            
            strMsg = String.Format("{0,3}/{1,3}", g_DJDialGlobals.AllDeviceRes[s8ModID].lPcmNum, g_DJDialGlobals.AllDeviceRes[s8ModID].lPcmOpened);
            DrawCount(g_DJDialGlobals.AllDeviceRes[s8ModID].iSeqID + 1, 2,strMsg);

            strMsg = String.Format("{0,3}/{1,3}", g_DJDialGlobals.g_iTotalPcm, g_DJDialGlobals.g_iTotalPcmOpened);
            DrawCount(0, 2, strMsg);

            strMsg = null;
        }

        public void	DrawCount_Trunk (sbyte s8ModID)
        {
            string strMsg;

            strMsg = String.Format("{0,3}/{1,3}", g_DJDialGlobals.AllDeviceRes[s8ModID].lTrunkNum, g_DJDialGlobals.AllDeviceRes[s8ModID].lTrunkOpened);
            DrawCount(g_DJDialGlobals.AllDeviceRes[s8ModID].iSeqID + 1, 3,strMsg);

            strMsg = String.Format("{0,3}/{1,3}", g_DJDialGlobals.g_iTotalTrunk, g_DJDialGlobals.g_iTotalTrunkOpened);
            DrawCount(0, 3, strMsg);

            strMsg = null;
        }

        public void DrawCount_Voc(sbyte s8ModID)
        {
            string strMsg;

            strMsg = String.Format("{0,3}/{1,3}", g_DJDialGlobals.AllDeviceRes[s8ModID].lVocNum, g_DJDialGlobals.AllDeviceRes[s8ModID].lVocOpened);
            DrawCount(g_DJDialGlobals.AllDeviceRes[s8ModID].iSeqID + 1, 4, strMsg);

            strMsg = null;

            strMsg = String.Format("{0,3}", g_DJDialGlobals.AllDeviceRes[s8ModID].lVocFreeNum);
            DrawCount(g_DJDialGlobals.AllDeviceRes[s8ModID].iSeqID + 1, 5, strMsg);

            strMsg = null;

            strMsg = String.Format("{0,3}/{1,3}", g_DJDialGlobals.g_iTotalVoice, g_DJDialGlobals.g_iTotalVoiceOpened);
            DrawCount(0, 4, strMsg);

            strMsg = null;

            strMsg = String.Format("{0,3}", g_DJDialGlobals.g_iTotalVoiceFree);
            DrawCount(0, 5, strMsg);

            strMsg = null;
        }

        public void	DrawCount_User (sbyte s8ModID)
        {
            string strMsg;

            strMsg = String.Format("{0,3}/{1,3}", g_DJDialGlobals.g_iTotalUser, g_DJDialGlobals.g_iTotalUserOpened);
            DrawCount(0, 6, strMsg);

            strMsg = null;
        }

        public void DrawCount_ErrFlag(sbyte s8ModID)
        {
            string strMsg;

            if (g_DJDialGlobals.AllDeviceRes[s8ModID].bErrFlag)
            {
                strMsg = "T";
            }
            else
            {
                strMsg = "";
            }
            DrawCount(g_DJDialGlobals.AllDeviceRes[s8ModID].iSeqID + 1, 7, strMsg);

            strMsg = null;
        }

        public unsafe void ReDraw()
        {
            AddMainItem();
            AddPcmItem();
            AddCountItem();
            AddUserItem();

            for (int i = 0; i < g_DJDialGlobals.g_iTotalTrunk; i++)
            {
                string strMsg = String.Format("{0},{1}", g_DJDialGlobals.MapTable_Trunk[i].m_s8ModuleID, g_DJDialGlobals.MapTable_Trunk[i].m_s16ChannelID);
                DrawMain(i, 1, strMsg);
                fixed (DJDialGlobals.TRUNK_STRUCT* pOneTrunk = &g_DJDialGlobals.AllDeviceRes[g_DJDialGlobals.MapTable_Trunk[i].m_s8ModuleID].pTrunk[g_DJDialGlobals.MapTable_Trunk[i].m_s16ChannelID])
                {
                    strMsg = null;
                    strMsg = String.Format("{0}", GetSubDevTypeString(pOneTrunk->deviceID.m_s16DeviceSub));
                    DrawMain(i, 2, strMsg);
                    DrawMain_LineState(pOneTrunk->iSeqID, pOneTrunk->iLineState);
                    DrawMain_State(pOneTrunk->iSeqID, (int)pOneTrunk->State);
                    DrawMain_CallInfo(pOneTrunk);
                }
                strMsg = null;
            }

            for (int i = 0; i < g_DJDialGlobals.g_iTotalPcm; i++)
            {
                fixed (DJDialGlobals.PCM_STRUCT* pOnePcm = &g_DJDialGlobals.AllDeviceRes[g_DJDialGlobals.MapTable_Pcm[i].m_s8ModuleID].pPcm[g_DJDialGlobals.MapTable_Pcm[i].m_s16ChannelID])
                {
                    DrawPcm_TypeAndAlarm(pOnePcm);
                }
            }

            for (int i = 0; i < g_DJDialGlobals.g_iTotalUser; i++)
            {
                fixed (DJDialGlobals.TRUNK_STRUCT* pOneTrunk = &g_DJDialGlobals.AllDeviceRes[g_DJDialGlobals.MapTable_User[i].m_s8ModuleID].pTrunk[g_DJDialGlobals.MapTable_User[i].m_s16ChannelID])
                {
                    string strMsg;
                    strMsg = String.Format("{0},{1}", pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID);
                    DrawUser(i, 1, strMsg);

                    strMsg = null;

                    strMsg = GetSubDevTypeString(pOneTrunk->deviceID.m_s16DeviceSub);
                    DrawUser(i, 2, strMsg);

                    DrawUser_LineState(pOneTrunk->iUserSeqID, pOneTrunk->iLineState);
                    DrawUser_State(pOneTrunk->iUserSeqID, (int)pOneTrunk->UserState);

                    strMsg = null;
                }
            }

            for (int i = 0; i < g_DJDialGlobals.g_iTotalModule; i++)
            {
                string strMsg;

                strMsg = String.Format("{0}", g_DJDialGlobals.MapTable_Module[i]);
                DrawCount(i + 1, 1, strMsg);
                DrawCount_Pcm(g_DJDialGlobals.MapTable_Module[i]);
                DrawCount_Trunk(g_DJDialGlobals.MapTable_Module[i]);
                DrawCount_Voc(g_DJDialGlobals.MapTable_Module[i]);
                DrawCount_ErrFlag(g_DJDialGlobals.MapTable_Module[i]);
                DrawCount_RemoveState(g_DJDialGlobals.MapTable_Module[i]);

                strMsg = null;
            }
        }

        public void RefreshMapTable ()
        {
	        int		i, j;
	        int		TrkCount, VocCount, PcmCount, ModuleCount, UserCount;
	        int		iModSeqID;

	        // Remember the AllDeviceRes's Interface,Voice,PCM channel
	        ModuleCount = TrkCount = VocCount = PcmCount = UserCount = 0;
            for (i = 0; i < DJDialGlobals.MAX_DSP_MODULE_NUMBER_OF_XMS; i++)
	        {
                if (g_DJDialGlobals.AllDeviceRes[i].lFlag == 1) //如果DSP可用
		        {
			        // DSP Module
                    g_DJDialGlobals.AllDeviceRes[i].iSeqID = ModuleCount;
                    g_DJDialGlobals.MapTable_Module[ModuleCount] = (sbyte)i;
                    ModuleCount++;

			        // Voice Channel
                    for (j = 0; j < g_DJDialGlobals.AllDeviceRes[i].lVocNum; j++)
			        {
                        g_DJDialGlobals.AllDeviceRes[i].pVoice[j].iSeqID = VocCount;
                        g_DJDialGlobals.MapTable_Voice[VocCount].m_s8ModuleID = g_DJDialGlobals.AllDeviceRes[i].pVoice[j].deviceID.m_s8ModuleID;
                        g_DJDialGlobals.MapTable_Voice[VocCount].m_s16ChannelID = g_DJDialGlobals.AllDeviceRes[i].pVoice[j].deviceID.m_s16ChannelID;
				        VocCount ++;
			        }

			     // PCM Channel
                    for (j = 0; j < g_DJDialGlobals.AllDeviceRes[i].lPcmNum; j++)
			        {
                        g_DJDialGlobals.AllDeviceRes[i].pPcm[j].iSeqID = PcmCount;
                        g_DJDialGlobals.MapTable_Pcm[PcmCount].m_s8ModuleID = g_DJDialGlobals.AllDeviceRes[i].pPcm[j].deviceID.m_s8ModuleID;
                        g_DJDialGlobals.MapTable_Pcm[PcmCount].m_s16ChannelID = g_DJDialGlobals.AllDeviceRes[i].pPcm[j].deviceID.m_s16ChannelID;
				        PcmCount ++;
			        }

			        // Interface Channel
			        iModSeqID = 0;
                    for (j = 0; j < g_DJDialGlobals.AllDeviceRes[i].lTrunkNum; j++)
			        {
                        g_DJDialGlobals.AllDeviceRes[i].pTrunk[j].iSeqID = TrkCount;
                        g_DJDialGlobals.MapTable_Trunk[TrkCount].m_s8ModuleID = g_DJDialGlobals.AllDeviceRes[i].pTrunk[j].deviceID.m_s8ModuleID;
                        g_DJDialGlobals.MapTable_Trunk[TrkCount].m_s16ChannelID = g_DJDialGlobals.AllDeviceRes[i].pTrunk[j].deviceID.m_s16ChannelID;
				        TrkCount ++;

                        if (g_DJDialGlobals.AllDeviceRes[i].pTrunk[j].deviceID.m_s16DeviceSub != (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_UNUSABLE)
				        {
					        // Available Channel
                            g_DJDialGlobals.AllDeviceRes[i].pTrunk[j].iModSeqID = iModSeqID;
					        iModSeqID ++;
				        }

                        if (g_DJDialGlobals.AllDeviceRes[i].pTrunk[j].deviceID.m_s16DeviceSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER) 
				        {
                            g_DJDialGlobals.AllDeviceRes[i].pTrunk[j].iUserSeqID = UserCount;
                            g_DJDialGlobals.MapTable_User[UserCount].m_s8ModuleID = g_DJDialGlobals.AllDeviceRes[i].pTrunk[j].deviceID.m_s8ModuleID;
                            g_DJDialGlobals.MapTable_User[UserCount].m_s16ChannelID = g_DJDialGlobals.AllDeviceRes[i].pTrunk[j].deviceID.m_s16ChannelID;
					        UserCount ++;
				        }
			        }
		        }
	        }

            g_DJDialGlobals.g_iTotalModule = ModuleCount;
            g_DJDialGlobals.g_iTotalTrunk = TrkCount;
            g_DJDialGlobals.g_iTotalUser = UserCount;
            g_DJDialGlobals.g_iTotalVoice = VocCount;
            g_DJDialGlobals.g_iTotalPcm = PcmCount;

        }

        public unsafe void CharsToSBytes(char[] chSrc, byte* byDst, int size)
        {
            int i = 0;
            for (i = 0; i < size && chSrc[i] != '\0'; ++i)
            {
                byDst[i] = (byte)chSrc[i];
            }
            byDst[i] = (byte)'\0';
        }

        public unsafe void CharsToChars(char[] Src, char* Dest, int nLen)
        {
            for (int i = 0; i < nLen && Src[i] != '\0'; i++)
            {
                Dest[i] = Src[i];
            }
        }

        public unsafe void CharsToChar(char* Src, char* Dest, int nLen)
        {
            for (int i = 0; i < nLen && Src[i] != '\0'; i++)
            {
                Dest[i] = Src[i];
            }
        }

        public unsafe void SBytesToSBytes(sbyte* Dest, sbyte* Src, int nLen)
        {
            for (int i = 0; Src[i] != (sbyte)'\0' && i < nLen; i++)
            {
                Dest[i] = Src[i];
            }
        }

        public unsafe void SBytesToChars(byte* bySrc, char[] chDst, int nLen)
        {
            int i = 0;
            for (i = 0; bySrc[i] != (byte)'\0' && i < nLen; ++i)
            {
                chDst[i] = (char)bySrc[i];
            }
            chDst[i] = '\0';
        }

        public unsafe void InitTextBox()
        {
            string strTemp = new string('\0', 0);
            fixed(sbyte* p = g_DJDialGlobals.cfg_ServerID.m_s8ServerIp)
            {
                strTemp = new string(p);
            }
            textBox_ServerIP.Text = strTemp;

            textBox_Port.Text = g_DJDialGlobals.cfg_ServerID.m_u32ServerPort.ToString();
            textBox_CalledLen.Text = g_DJDialGlobals.cfg_iCalledLen.ToString();
            textBox_CallingNum.Text = g_DJDialGlobals.cfg_CallingNum;
            textBox_CalledNum.Text = g_DJDialGlobals.cfg_SimCalledNum;
            textBox_ModID.Text = g_DJDialGlobals.cfg_iPartWorkModuleID.ToString();

            if (g_DJDialGlobals.cfg_s32DebugOn == 0) //CheckBox未选中
            {
                checkBox_Debug.Checked = false;
            }
            else
            {
                checkBox_Debug.Checked = true;
            }

            if (g_DJDialGlobals.cfg_iPartWork == 0)
            {
                checkBox_ModID.Checked = false;
            }
            else
            {
                checkBox_ModID.Checked = true;
            }

            if (g_DJDialGlobals.cfg_iCallOutRule == 0)
            {
                radioButton_Seq.Checked = true;
            }
            else if (g_DJDialGlobals.cfg_iCallOutRule == 1)
            {
                radioButton_Loop.Checked = true;
            }
            else
            {
                radioButton_Dtmf.Checked = true;
            }

            strTemp = null;
        }

        public unsafe void SaveTextBox()
        {
            string strServerIp = textBox_ServerIP.Text;
            char[] chTemp = strServerIp.ToCharArray();
            fixed (sbyte* p = g_DJDialGlobals.cfg_ServerID.m_s8ServerIp)
            {
                CharsToSBytes(chTemp, (byte *)p, strServerIp.Length);
            }

            g_DJDialGlobals.cfg_ServerID.m_u32ServerPort = uint.Parse(textBox_Port.Text);
            g_DJDialGlobals.cfg_iCalledLen = int.Parse(textBox_CalledLen.Text);
            g_DJDialGlobals.cfg_CallingNum = textBox_CallingNum.Text;
            g_DJDialGlobals.cfg_SimCalledNum = textBox_CalledNum.Text;
            g_DJDialGlobals.cfg_iPartWorkModuleID = int.Parse(textBox_ModID.Text);

            if (checkBox_Debug.Checked == false)
            {
                g_DJDialGlobals.cfg_s32DebugOn = 0;
            }
            else
            {
                g_DJDialGlobals.cfg_s32DebugOn = 1;
            }

            if (checkBox_ModID.Checked == false)
            {
                g_DJDialGlobals.cfg_iPartWork = 0;
            }
            else
            {
                g_DJDialGlobals.cfg_iPartWork = 1;
            }

            if (radioButton_Seq.Checked == true)
            {
                g_DJDialGlobals.cfg_iCallOutRule = 0;
            }
            if (radioButton_Loop.Checked == true)
            {
                g_DJDialGlobals.cfg_iCallOutRule = 1;
            }
            if (radioButton_Dtmf.Checked == true)
            {
                g_DJDialGlobals.cfg_iCallOutRule = 2;
            }

            strServerIp = null;
        }

        public unsafe byte My_GetGtdOrPVDCode ( Acs_Evt_t *pAcsEvt )
        {
	        if ( pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_RECVIODATA )	/*IO Data Event*/
	        {
                Acs_IO_Data* pIOData = (Acs_IO_Data*)((byte *)pAcsEvt + sizeof(Acs_Evt_t));
                {
                    if ( ( ( pIOData->m_u16IoType==(ushort)XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_GTG ) || ( pIOData->m_u16IoType==(ushort)XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_PVD ) )
			                && ( pIOData->m_u16IoDataLen > 0 ) )
		            {
                        byte* p = (byte*)pIOData + sizeof(Acs_IO_Data);
                        {
                            char[] szMsg = new char[2 * (pIOData->m_u16IoDataLen + 1)];
                            szMsg.Initialize();

                            SBytesToChars(p, szMsg, pIOData->m_u16IoDataLen);
                            string strMsg = new string(szMsg);
                            ListBox_AddItem(strMsg);

                            szMsg = null;

                            return p[0];
                        }
                    }
                }
		    }
            return 0;
        }

        public unsafe void SetGtd_AnalogTrunk(DeviceID_t* pDevId)
        {
	    //========Set GTG Begin========
				
	        CmdParamData_Voice_t cmdVoc;

            memset((byte*)&cmdVoc, 0, sizeof(CmdParamData_Voice_t));

	        cmdVoc.m_u8GtdCtrlValid = 1 ; //Enable GTD
	        cmdVoc.m_VocGtdControl.m_u8ChannelEnable = 1;//Enable Gtd channel
	        cmdVoc.m_VocGtdControl.m_u8DTMFEnable = 1;
	        cmdVoc.m_VocGtdControl.m_u8MR2FEnable = 1;
	        cmdVoc.m_VocGtdControl.m_u8MR2BEnable = 1;
	        cmdVoc.m_VocGtdControl.m_u8GTDEnable = 1;
	        cmdVoc.m_VocGtdControl.m_u8FSKEnable = 1;
	
	        cmdVoc.m_VocGtdControl.m_u8EXTEnable = 0x2;		// Enable PVD Detect

            cmdVoc.m_VocGtdControl.m_u8GTDID[0] = (byte)'G';
            cmdVoc.m_VocGtdControl.m_u8GTDID[1] = (byte)'H';
            cmdVoc.m_VocGtdControl.m_u8GTDID[2] = (byte)'I';
            cmdVoc.m_VocGtdControl.m_u8GTDID[3] = (byte)'J';
            cmdVoc.m_VocGtdControl.m_u8GTDID[4] = (byte)'K';

	        ushort u16ParamType = 0;
            ushort u16ParamSize = (ushort)sizeof(CmdParamData_Voice_t);

            int r = DJAcsApiDef.XMS_ctsSetParam(g_DJDialGlobals.g_acsHandle, pDevId, u16ParamType, u16ParamSize, (void*)&cmdVoc);
            string strMsg;

            strMsg = String.Format("Set GTD ret = {0}", r);
            ListBox_AddItem(strMsg);

            strMsg = null;
	    //========Set GTG End  ========
        }

        public unsafe void memset(byte* dest, int c, int count) //把一块内存内存初始化为c
        {
            if (dest == null) return;
            for (int i = 0; i < count; i++)
            {
                dest[i] = (byte)c;
            }
        }

        public unsafe void Change_State(DJDialGlobals.TRUNK_STRUCT* pOneTrunk, DJDialGlobals.TRUNK_STATE NewState)
        {
            pOneTrunk->State = NewState;

            DrawMain_State(pOneTrunk->iSeqID, (int)pOneTrunk->State);

            // Check if ready to remove DSP hardware
            if ((g_DJDialGlobals.AllDeviceRes[pOneTrunk->deviceID.m_s8ModuleID].RemoveState == DJDialGlobals.REMOVE_STATE.DSP_REMOVE_STATE_START)
                && (NewState == DJDialGlobals.TRUNK_STATE.TRK_FREE))
            {
                pOneTrunk->State = DJDialGlobals.TRUNK_STATE.TRK_WAIT_REMOVE;

                DrawMain_State(pOneTrunk->iSeqID, (int)pOneTrunk->State);

                CheckRemoveReady(pOneTrunk->deviceID.m_s8ModuleID);
            }
        }

        public unsafe int GetOutUserID (  string pDtmf, DeviceID_t *pUserDeviceID )
        {
            if (g_DJDialGlobals.cfg_iCallOutRule == 2)
            {
                int iTmp = 0;

                iTmp = Convert.ToInt32(pDtmf);
                iTmp %= 1000;

                sbyte s8ModID = g_DJDialGlobals.MapTable_Trunk[iTmp].m_s8ModuleID;
		        short s16ChID = g_DJDialGlobals.MapTable_Trunk[iTmp].m_s16ChannelID;

                if (iTmp >= g_DJDialGlobals.g_iTotalTrunk)
			        return -1;

                if ((g_DJDialGlobals.AllDeviceRes[s8ModID].pTrunk[s16ChID].iLineState == (int)DEVICE_CALL_STATE.DCS_FREE)
                    && (g_DJDialGlobals.AllDeviceRes[s8ModID].pTrunk[s16ChID].deviceID.m_s16DeviceSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER))
		        {
			        *pUserDeviceID = g_DJDialGlobals.AllDeviceRes[s8ModID].pTrunk[s16ChID].deviceID;
			        return iTmp;
		        }
		        return -1;
            }
            return -1;
        }

        public unsafe void SetGTD_ToneParam(DeviceID_t* pDevice)
        {
            int r;
            ushort u16ParamType, u16ParamSize;

            CmdParamData_GtdFreq_t TmpGtdFreq;
            CmdParamData_GtdProtoType_t TmpGtdProto;

            // ---------- set Freq ----------
            u16ParamType = (ushort)XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDFREQ;
            u16ParamSize = (ushort)sizeof(CmdParamData_GtdFreq_t);

            // freq0
            TmpGtdFreq.m_u16Freq_Index = 0;
            TmpGtdFreq.m_u16Freq_Coef = g_DJDialGlobals.g_Param_Analog.m_u16Freq0;

            r = DJAcsApiDef.XMS_ctsSetParam(g_DJDialGlobals.g_acsHandle, pDevice, u16ParamType, u16ParamSize, (byte*)&TmpGtdFreq);
            // freq1
            TmpGtdFreq.m_u16Freq_Index = 1;
            TmpGtdFreq.m_u16Freq_Coef = g_DJDialGlobals.g_Param_Analog.m_u16Freq1;
            r = DJAcsApiDef.XMS_ctsSetParam(g_DJDialGlobals.g_acsHandle, pDevice, u16ParamType, u16ParamSize, (byte*)&TmpGtdFreq);

            // ---------- set DialTone ----------
            u16ParamType = (ushort)XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDTONE;
            u16ParamSize = (ushort)sizeof(CmdParamData_GtdProtoType_t);

            memset((byte*)&TmpGtdProto, 0, sizeof(CmdParamData_GtdProtoType_t));
            TmpGtdProto.m_u16GtdID = 48;		// DialTone, we use GTD's ID 48
            TmpGtdProto.m_u16Freq_Mask = g_DJDialGlobals.g_Param_Analog.m_u16DialTone_FreqIndexMask;
            TmpGtdProto.m_u16Envelope_Mode = 0;
            TmpGtdProto.m_u16Repeat_Count = 1;
            TmpGtdProto.m_u16Min_On_Time1 = (ushort)(g_DJDialGlobals.g_Param_Analog.m_u16DialTone_On_Time/15);		// the unit is 15 ms

            r = DJAcsApiDef.XMS_ctsSetParam(g_DJDialGlobals.g_acsHandle, pDevice, u16ParamType, u16ParamSize, (byte*)&TmpGtdProto);

            // ---------- set RingBack Tone ----------
            u16ParamType = (ushort)XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDTONE;
            u16ParamSize = (ushort)sizeof(CmdParamData_GtdProtoType_t);

            memset((byte*)&TmpGtdProto, 0, sizeof(CmdParamData_GtdProtoType_t));
            TmpGtdProto.m_u16GtdID = 49;		// DialTone, we use GTD's ID 49
            TmpGtdProto.m_u16Freq_Mask = g_DJDialGlobals.g_Param_Analog.m_u16RingBackTone_FreqIndexMask;
            TmpGtdProto.m_u16Envelope_Mode = 1;
            TmpGtdProto.m_u16Repeat_Count = 1;
            TmpGtdProto.m_u16Min_On_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16RingBackTone_On_Time *
                (100 - g_DJDialGlobals.g_Param_Analog.m_u16RingBackTone_TimeDeviation) / 100) / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_On_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16RingBackTone_On_Time *
                (100 + g_DJDialGlobals.g_Param_Analog.m_u16RingBackTone_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Min_Off_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16RingBackTone_Off_Time *
                (100 - g_DJDialGlobals.g_Param_Analog.m_u16RingBackTone_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_Off_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16RingBackTone_Off_Time *
                (100 + g_DJDialGlobals.g_Param_Analog.m_u16RingBackTone_TimeDeviation)) / 100 / 15);		// the unit is 15 ms

            r = DJAcsApiDef.XMS_ctsSetParam(g_DJDialGlobals.g_acsHandle, pDevice, u16ParamType, u16ParamSize, (byte*)&TmpGtdProto);

            // ---------- set Busy Tone0 ----------
            u16ParamType = (ushort)XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDTONE;
            u16ParamSize = (ushort)sizeof(CmdParamData_GtdProtoType_t);

            memset((byte*)&TmpGtdProto, 0, sizeof(CmdParamData_GtdProtoType_t));
            TmpGtdProto.m_u16GtdID = 50;		// BusyTone0, we use GTD's ID 50
            TmpGtdProto.m_u16Freq_Mask = g_DJDialGlobals.g_Param_Analog.m_u16BusyTone0_FreqIndexMask;
            TmpGtdProto.m_u16Envelope_Mode = 1;
            TmpGtdProto.m_u16Repeat_Count = 1;
            TmpGtdProto.m_u16Min_On_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16BusyTone0_On_Time *
                (100 - g_DJDialGlobals.g_Param_Analog.m_u16BusyTone0_TimeDeviation) / 100) / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_On_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16BusyTone0_On_Time *
                (100 + g_DJDialGlobals.g_Param_Analog.m_u16BusyTone0_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Min_Off_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16BusyTone0_Off_Time *
                (100 - g_DJDialGlobals.g_Param_Analog.m_u16BusyTone0_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_Off_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16BusyTone0_Off_Time *
                (100 + g_DJDialGlobals.g_Param_Analog.m_u16BusyTone0_TimeDeviation)) / 100 / 15);		// the unit is 15 ms

            r = DJAcsApiDef.XMS_ctsSetParam(g_DJDialGlobals.g_acsHandle, pDevice, u16ParamType, u16ParamSize, (byte*)&TmpGtdProto);

            // ---------- set Busy Tone1 ----------
            u16ParamType = (ushort)XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDTONE;
            u16ParamSize = (ushort)sizeof(CmdParamData_GtdProtoType_t);

            memset((byte*)&TmpGtdProto, 0, sizeof(CmdParamData_GtdProtoType_t));
            TmpGtdProto.m_u16GtdID = 51;		// BusyTone1, we use GTD's ID 51
            TmpGtdProto.m_u16Freq_Mask = g_DJDialGlobals.g_Param_Analog.m_u16BusyTone1_FreqIndexMask;
            TmpGtdProto.m_u16Envelope_Mode = 1;
            TmpGtdProto.m_u16Repeat_Count = 1;
            TmpGtdProto.m_u16Min_On_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16BusyTone1_On_Time *
                (100 - g_DJDialGlobals.g_Param_Analog.m_u16BusyTone1_TimeDeviation) / 100) / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_On_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16BusyTone1_On_Time *
                (100 + g_DJDialGlobals.g_Param_Analog.m_u16BusyTone1_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Min_Off_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16BusyTone1_Off_Time *
                (100 - g_DJDialGlobals.g_Param_Analog.m_u16BusyTone1_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_Off_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16BusyTone1_Off_Time *
                (100 + g_DJDialGlobals.g_Param_Analog.m_u16BusyTone1_TimeDeviation)) / 100 / 15);		// the unit is 15 ms

            r = DJAcsApiDef.XMS_ctsSetParam(g_DJDialGlobals.g_acsHandle, pDevice, u16ParamType, u16ParamSize, (byte*)&TmpGtdProto);

            // ---------- set Busy Tone2 ----------
            u16ParamType = (ushort)XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDTONE;
            u16ParamSize = (ushort)sizeof(CmdParamData_GtdProtoType_t);

            memset((byte*)&TmpGtdProto, 0, sizeof(CmdParamData_GtdProtoType_t));
            TmpGtdProto.m_u16GtdID = 52;		// BusyTone2, we use GTD's ID 52
            TmpGtdProto.m_u16Freq_Mask = g_DJDialGlobals.g_Param_Analog.m_u16BusyTone2_FreqIndexMask;
            TmpGtdProto.m_u16Envelope_Mode = 1;
            TmpGtdProto.m_u16Repeat_Count = 1;
            TmpGtdProto.m_u16Min_On_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16BusyTone2_On_Time *
                (100 - g_DJDialGlobals.g_Param_Analog.m_u16BusyTone2_TimeDeviation) / 100) / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_On_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16BusyTone2_On_Time *
                (100 + g_DJDialGlobals.g_Param_Analog.m_u16BusyTone2_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Min_Off_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16BusyTone2_Off_Time *
                (100 - g_DJDialGlobals.g_Param_Analog.m_u16BusyTone2_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_Off_Time1 = (ushort)((g_DJDialGlobals.g_Param_Analog.m_u16BusyTone2_Off_Time *
                (100 + g_DJDialGlobals.g_Param_Analog.m_u16BusyTone2_TimeDeviation)) / 100 / 15);		// the unit is 15 ms

            r = DJAcsApiDef.XMS_ctsSetParam(g_DJDialGlobals.g_acsHandle, pDevice, u16ParamType, u16ParamSize, (byte*)&TmpGtdProto);
        }

        public unsafe void CloseDeviceOK(DeviceID_t* pDevice)
        {
            g_DJDialGlobals.AllDeviceRes[pDevice->m_s8ModuleID].bErrFlag = true;
            DrawCount_ErrFlag(pDevice->m_s8ModuleID);

            if (pDevice->m_s16DeviceMain == (short)XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD)
            {
                g_DJDialGlobals.AllDeviceRes[pDevice->m_s8ModuleID].bOpenFlag = false;
            }

            if (pDevice->m_s16DeviceMain == (short)XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH)
            {
                fixed (DJDialGlobals.TRUNK_STRUCT* pOneTrunk = &g_DJDialGlobals.AllDeviceRes[pDevice->m_s8ModuleID].pTrunk[pDevice->m_s16ChannelID])
                {

                    Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_WAITOPEN);

                    if (pOneTrunk->deviceID.m_s16DeviceSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER)
                    {
                        Change_UserState(pOneTrunk, DJDialGlobals.USER_STATE.USER_WAITOPEN);

                        // modify the count
                        g_DJDialGlobals.g_iTotalUserOpened--;
                        DrawCount_User(pDevice->m_s8ModuleID);
                    }
                    else
                    {

                    }

                    // modify the count
                    g_DJDialGlobals.g_iTotalTrunkOpened--;
                    g_DJDialGlobals.AllDeviceRes[pDevice->m_s8ModuleID].lTrunkOpened--;

                    DrawCount_Trunk(pDevice->m_s8ModuleID);
                }
            }

            if (pDevice->m_s16DeviceMain == (short)XMS_DEVMAIN_TYPE. XMS_DEVMAIN_VOICE)
            {
                fixed (DJDialGlobals.VOICE_STRUCT* pOneVoice = &g_DJDialGlobals.AllDeviceRes[pDevice->m_s8ModuleID].pVoice[pDevice->m_s16ChannelID])
                {

                    Change_Voc_State(pOneVoice, DJDialGlobals.VOICE_STATE.VOC_WAITOPEN);

                    g_DJDialGlobals.g_iTotalVoiceOpened--;
                    g_DJDialGlobals.g_iTotalVoiceFree--;
                    g_DJDialGlobals.AllDeviceRes[pDevice->m_s8ModuleID].lVocOpened--;
                    g_DJDialGlobals.AllDeviceRes[pDevice->m_s8ModuleID].lVocFreeNum--;

                    DrawCount_Voc(pDevice->m_s8ModuleID);
                }
            }

            if (pDevice->m_s16DeviceMain == (short)XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT)
            {
                fixed (DJDialGlobals.PCM_STRUCT* pOnePcm = &g_DJDialGlobals.AllDeviceRes[pDevice->m_s8ModuleID].pPcm[pDevice->m_s16ChannelID])
                {

                    pOnePcm->bOpenFlag = false;

                    // moidfy the count
                    g_DJDialGlobals.g_iTotalPcmOpened--;
                    g_DJDialGlobals.AllDeviceRes[pDevice->m_s8ModuleID].lPcmOpened--;

                    DrawCount_Pcm(pDevice->m_s8ModuleID);
                }
            }
        }

        public unsafe void InitSystem()
        {
            int iResult;
            string strMsg;

            g_DJDialGlobals.ReadFromConfig();
            InitTextBox();

            if (0 != CAS_Common_Code.CAS_Common_Cfg_ReadCfg(ref g_DJDialGlobals.g_Param_CAS))
            {
                MessageBox.Show("CAS_Common_Cfg_ReadCfg \"C:\\DJKeygoe\\Samples\\CAS_Common_Code\\XMS_CAS_Cfg.INI\" Error!", "Init System");
            }

            if (0 != Analog_Common_Code.Analog_Common_Cfg_ReadCfg(ref g_DJDialGlobals.g_Param_Analog))
            {
                MessageBox.Show("Analog_Common_Cfg_ReadCfg \"C:\\DJKeygoe\\Samples\\Analog_Common_Code\\XMS_Analog_Cfg.INI\\ Error", "Init System");
            }

            fixed (ServerID_t* pStruct = &g_DJDialGlobals.cfg_ServerID)
            {
                fixed (UInt32* pAcsHandle = &g_DJDialGlobals.g_acsHandle)
                {
                    iResult = DJAcsApiDef.XMS_acsOpenStream(pAcsHandle, pStruct, 13, 64, 64, g_DJDialGlobals.cfg_s32DebugOn, null);
                    
                    strMsg = String.Format("{0} ({1},{2})", "XMS_acsOpenStream", textBox_ServerIP.Text, textBox_Port.Text);
                    if (iResult == (int)ERROR_CODE.ACSPOSITIVE_ACK)
                    {
                        strMsg += " OK!";
                    }
                    else
                    {
                        strMsg += " FAIL!";
                    }
                    ListBox_AddItem(strMsg);
                }
            }

            strMsg = null;

            g_ESRFuncPtr = new DJAcsApiDef.EsrFunc(EvtHandler);
            iResult = DJAcsApiDef.XMS_acsSetESR(g_DJDialGlobals.g_acsHandle, g_ESRFuncPtr, 0, 1);

            if (iResult == (int)ERROR_CODE.ACSPOSITIVE_ACK)
            {
                strMsg += "XMS_acsSetESR() OK!";
            }
            else
            {
                strMsg += "XMS_acsSetESR() FAIL!";
            }
            ListBox_AddItem(strMsg);

            iResult = DJAcsApiDef.XMS_acsGetDeviceList(g_DJDialGlobals.g_acsHandle, null);

            strMsg = null;

            strMsg = String.Format("{0}", "AcsGetDeviceListEx()");
            if (iResult == (int)ERROR_CODE.ACSPOSITIVE_ACK)
            {
                strMsg += " OK!";
            }
            else
            {
                strMsg += " FAIL!";
            }
            ListBox_AddItem(strMsg);

            strMsg = null;
        }

        public static unsafe void EvtHandler(UInt32 esrParam)
        {
            //return;
            try
            {
                    Acs_Evt_t* pAcsEvt = (Acs_Evt_t*)esrParam;

                    pDial.ShowEvtInfo(pAcsEvt);

                    //EvtProc
                    {
                        switch ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType)
                        {
                            case XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_START: break;

                            #region XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE
                            case XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE:
                                if ((g_DJDialGlobals.cfg_iPartWork == 0) || (pAcsEvt->m_DeviceID.m_s8ModuleID == g_DJDialGlobals.cfg_iPartWorkModuleID))
                                {
                                    Acs_Dev_List_Head_t* pAcsDevList = (Acs_Dev_List_Head_t*)((byte *)pAcsEvt + sizeof(Acs_Evt_t));

                                    //收到设备变化的事件，增加/删除 该设备资源
                                    {
                                        int s32Type = pAcsDevList->m_s32DeviceMain;
                                        int s32Num = pAcsDevList->m_s32DeviceNum;
                                        int s8DspModID = pAcsDevList->m_s32ModuleID;

                                        if ((s8DspModID > 0) && (s8DspModID < DJDialGlobals.MAX_DSP_MODULE_NUMBER_OF_XMS))
                                        {
                                            switch ((XMS_DEVMAIN_TYPE)s32Type)
                                            {
                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE:
                                                    {
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].pVoice = new DJDialGlobals.VOICE_STRUCT[s32Num];
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lVocNum = s32Num;
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lVocOpened = 0;
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lVocFreeNum = 0;
                                                        DeviceID_t* pDev = (DeviceID_t*)((byte*)pAcsDevList + sizeof(Acs_Dev_List_Head_t));
                                                        for (int i = 0; i < s32Num; i++)
                                                        {
                                                            g_DJDialGlobals.AllDeviceRes[s8DspModID].pVoice[i].deviceID = pDev[i];
                                                            g_DJDialGlobals.AllDeviceRes[s8DspModID].pVoice[i].State = DJDialGlobals.VOICE_STATE.VOC_WAITOPEN;
                                                        }
                                                        pDev = null;
                                                    }
                                                    break;

                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT:
                                                    {
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].pPcm = new DJDialGlobals.PCM_STRUCT[s32Num];
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lPcmNum = s32Num;
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lPcmOpened = 0;
                                                        DeviceID_t* pDev = (DeviceID_t*)((byte*)pAcsDevList + sizeof(Acs_Dev_List_Head_t));
                                                        for (int i = 0; i < s32Num; ++i)
                                                        {
                                                            g_DJDialGlobals.AllDeviceRes[s8DspModID].pPcm[i].deviceID = pDev[i];
                                                            g_DJDialGlobals.AllDeviceRes[s8DspModID].pPcm[i].bOpenFlag = false;
                                                        }
                                                        pDev = null;
                                                    }
                                                    break;

                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH:
                                                    {
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk = new DJDialGlobals.TRUNK_STRUCT[s32Num];
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lTrunkNum = s32Num;
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lTrunkOpened = 0;
                                                        DeviceID_t* pDev = (DeviceID_t*)((byte*)pAcsDevList + sizeof(Acs_Dev_List_Head_t));
                                                        for (int i = 0; i < s32Num; i++)
                                                        {
                                                            g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk[i].deviceID = pDev[i];
                                                            g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk[i].State = DJDialGlobals.TRUNK_STATE.TRK_WAITOPEN;
                                                        }
                                                        pDev = null;
                                                    }
                                                    break;

                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD:
                                                    {
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lFlag = 1;
                                                        DeviceID_t* pDev = (DeviceID_t*)((byte*)pAcsDevList + sizeof(Acs_Dev_List_Head_t));
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].deviceID = pDev[0];
                                                        pDev = null;
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].bOpenFlag = false;
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].bErrFlag = false;
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].RemoveState = DJDialGlobals.REMOVE_STATE.DSP_REMOVE_STATE_NONE;
                                                    }
                                                    break;

                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_FAX: break;
                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DSS1_LINK: break;
                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_SS7_LINK: break;
                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_CTBUS_TS: break;
                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOIP: break;
                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_CONFERENCE: break;
                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VIDEO: break;
                                                default: break;
                                            }
                                        }
                                    }

                                    pAcsDevList = null;
                                }
                                break;
                            #endregion

                            #region XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_END
                            case XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_END: //
                            case XMS_EVT_TYPE.XMS_EVT_QUERY_REMOVE_ONE_DSP_END:
                                if ((g_DJDialGlobals.cfg_iPartWork == 0) || (pAcsEvt->m_DeviceID.m_s8ModuleID == g_DJDialGlobals.cfg_iPartWorkModuleID))
                                {
                                    if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_END)
                                    {
                                        g_DJDialGlobals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].lFlag = 1;		// 该DSP可以用了
                                        int s8DspModID = pAcsEvt->m_DeviceID.m_s8ModuleID;
                                        int iResult = 0;

                                        if (g_DJDialGlobals.AllDeviceRes[s8DspModID].bOpenFlag == false)	// 如果BOARD没有Open
                                        {
                                            fixed (DeviceID_t* pDev = &g_DJDialGlobals.AllDeviceRes[s8DspModID].deviceID)
                                            {
                                                iResult = DJAcsApiDef.XMS_ctsOpenDevice(g_DJDialGlobals.g_acsHandle, pDev, null);
                                                if (iResult != (int)ERROR_CODE.ACSPOSITIVE_ACK)
                                                {
                                                    string strMsg = "XMS_ctsOpenDevice (Board) Fail!";
                                                    pDial.ListBox_AddItem(strMsg);
                                                }
                                            }

                                            // Open Voice
                                            for (int i = 0; i < g_DJDialGlobals.AllDeviceRes[s8DspModID].lVocNum; ++i)
                                            {
                                                fixed (DeviceID_t* pDev = &g_DJDialGlobals.AllDeviceRes[s8DspModID].pVoice[i].deviceID)
                                                {
                                                    iResult = DJAcsApiDef.XMS_ctsOpenDevice(g_DJDialGlobals.g_acsHandle, pDev, null);
                                                    if (iResult != (int)ERROR_CODE.ACSPOSITIVE_ACK)
                                                    {
                                                        string strMsg;
                                                        strMsg = String.Format("{0} Dev({1},{2},{3}) {4}", "XMS_ctsOpenDevice", pDial.GetDevTypeString(pDev->m_s16DeviceMain), pDev->m_s8ModuleID, pDev->m_s16ChannelID, "FAIL!");
                                                        pDial.ListBox_AddItem(strMsg);
                                                    }
                                                }
                                            }

                                            // Open Pcm
                                            for (int i = 0; i < g_DJDialGlobals.AllDeviceRes[s8DspModID].lPcmNum; ++i)
                                            {
                                                fixed (DeviceID_t* pDev = &g_DJDialGlobals.AllDeviceRes[s8DspModID].pPcm[i].deviceID)
                                                {
                                                    iResult = DJAcsApiDef.XMS_ctsOpenDevice(g_DJDialGlobals.g_acsHandle, pDev, null);
                                                    if (iResult != (int)ERROR_CODE.ACSPOSITIVE_ACK)
                                                    {
                                                        string strMsg;
                                                        strMsg = String.Format("{0} Dev({1},{2},{3}) {4}", "XMS_ctsOpenDevice", pDial.GetDevTypeString(pDev->m_s16DeviceMain), pDev->m_s8ModuleID, pDev->m_s16ChannelID, "FAIL!");
                                                        pDial.ListBox_AddItem(strMsg);
                                                    }
                                                }
                                            }

                                            // Open Trunk
                                            for (int i = 0; i < g_DJDialGlobals.AllDeviceRes[s8DspModID].lTrunkNum; ++i)
                                            {
                                                fixed (DeviceID_t* pDev = &g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk[i].deviceID)
                                                {
                                                    iResult = DJAcsApiDef.XMS_ctsOpenDevice(g_DJDialGlobals.g_acsHandle, pDev, null);
                                                    if (iResult != (int)ERROR_CODE.ACSPOSITIVE_ACK)
                                                    {
                                                        string strMsg;
                                                        strMsg = String.Format("{0} Dev({1},{2},{3}) {4}", "XMS_ctsOpenDevice", pDial.GetDevTypeString(pDev->m_s16DeviceMain), pDev->m_s8ModuleID, pDev->m_s16ChannelID, "FAIL!");
                                                        pDial.ListBox_AddItem(strMsg);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        g_DJDialGlobals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].lFlag = 0;		// 该DSP已经Remove完毕
                                    }
                                    pDial.RefreshMapTable();
                                    pDial.ReDraw();
                                }
                                break;
                            #endregion

                            case XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE_END:	// 获取设备列表结束
                                break;

                            #region XMS_EVT_TYPE.XMS_EVT_OPEN_DEVICE
                            case XMS_EVT_TYPE.XMS_EVT_OPEN_DEVICE:
                                {
                                    int iDspModuleID = pAcsEvt->m_DeviceID.m_s8ModuleID;
                                    switch ((XMS_DEVMAIN_TYPE)pAcsEvt->m_DeviceID.m_s16DeviceMain)
                                    {
                                        case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD:
                                            {
                                                g_DJDialGlobals.AllDeviceRes[iDspModuleID].deviceID.m_CallID = pAcsEvt->m_DeviceID.m_CallID;
                                                fixed (DeviceID_t* pDevice = &g_DJDialGlobals.AllDeviceRes[iDspModuleID].deviceID)
                                                {
                                                    pDial.SetGTD_ToneParam(pDevice);
                                                }
                                            }
                                            break;  

                                        #region XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH
                                        case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH:
                                            {
                                                fixed (DJDialGlobals.TRUNK_STRUCT* pOneTrunk = &g_DJDialGlobals.AllDeviceRes[iDspModuleID].pTrunk[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                                {
                                                    pOneTrunk->deviceID.m_CallID = pAcsEvt->m_DeviceID.m_CallID;		// this line is very important, must before all operation

                                                    if (pOneTrunk->deviceID.m_s16DeviceSub == (int)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER
                                                        /*|| pOneTrunk->deviceID.m_s16DeviceSub == (int)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK*/)
                                                    {
                                                        pDial.InitUserChannel(pOneTrunk);

                                                        DeviceID_t* pDev = &pAcsEvt->m_DeviceID;
                                                        DJAcsApiDef.XMS_ctsResetDevice(g_DJDialGlobals.g_acsHandle, pDev, null);
                                                        DJAcsApiDef.XMS_ctsGetDevState(g_DJDialGlobals.g_acsHandle, pDev, null);
                                                        //pOneTrunk->State = DJDataDefClass.TRUNK_STATE.TRK_NOTHANDLE;// 中继通道不处理该user通道
                                                        pDial.Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_FREE);

                                                        g_DJDialGlobals.g_iTotalUserOpened++;
                                                        pDial.DrawCount_User(pAcsEvt->m_DeviceID.m_s8ModuleID);
                                                        pDev = null;
                                                    }
                                                    else
                                                    {
                                                        pDial.InitTrunkChannel(pOneTrunk);

                                                        DJAcsApiDef.XMS_ctsResetDevice(g_DJDialGlobals.g_acsHandle, &pAcsEvt->m_DeviceID, null);
                                                        DJAcsApiDef.XMS_ctsGetDevState(g_DJDialGlobals.g_acsHandle, &pAcsEvt->m_DeviceID, null);
                                                    }

                                                    ++g_DJDialGlobals.g_iTotalTrunkOpened;
                                                    ++g_DJDialGlobals.AllDeviceRes[iDspModuleID].lTrunkOpened;
                                                    pDial.DrawCount_Trunk(pAcsEvt->m_DeviceID.m_s8ModuleID);

                                                    if (pOneTrunk->deviceID.m_s16DeviceSub == (int)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
                                                    {
                                                        CmdParamData_AnalogTrunk_t cmdAnalogTrunk;
                                                        ushort u16ParamType = 0;//ANALOGTRUNK_PARAM_UNIPARAM
                                                        ushort u16ParamSize = (ushort)sizeof(CmdParamData_AnalogTrunk_t);

                                                        pDial.memset((byte*)&cmdAnalogTrunk, 0, sizeof(CmdParamData_AnalogTrunk_t));
                                                        cmdAnalogTrunk.m_u16CallInRingCount = 1;//XMS_ANALOG_TRUNK_CALLERID_FSK
                                                        cmdAnalogTrunk.m_u16CallInRingTimeOut = 6000;

                                                        int r = DJAcsApiDef.XMS_ctsSetParam(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, u16ParamType, u16ParamSize, (byte*)&cmdAnalogTrunk);
                                                        string strMsg;
                                                        strMsg = String.Format("Set AnalogTrunk  ret = {0}", r);
                                                        pDial.ListBox_AddItem(strMsg);
                                                    }
                                                    else if (pOneTrunk->deviceID.m_s16DeviceSub == (int)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER)
                                                    {
                                                        CmdParamData_AnalogUser_t g_AnalogUser;
                                                        ushort u16ParamType = 0;
                                                        ushort u16ParamSize = (ushort)sizeof(CmdParamData_AnalogUser_t);

                                                        pDial.memset((byte*)&g_AnalogUser, 0, sizeof(CmdParamData_AnalogUser_t));
                                                        g_AnalogUser.m_u8CallerIdOption = 1;
                                                        g_AnalogUser.m_u8RingCadenceType = 0;
                                                        g_AnalogUser.m_u8CallOutRingTimeOut = 30;

                                                        int r = DJAcsApiDef.XMS_ctsSetParam(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, u16ParamType, u16ParamSize, (void*)&g_AnalogUser);
                                                        string strMsg;
                                                        strMsg = String.Format("Set AnalogUser  ret ={0}", r);
                                                        pDial.ListBox_AddItem(strMsg);
                                                    }
                                                }
                                            }
                                            break;
                                        #endregion

                                        case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE:
                                            {
                                                fixed (DJDialGlobals.VOICE_STRUCT* pOneVoc = &g_DJDialGlobals.AllDeviceRes[iDspModuleID].pVoice[pAcsEvt->m_DeviceID.m_s16ChannelID]) 
                                                {
                                                    pOneVoc->deviceID.m_CallID = pAcsEvt->m_DeviceID.m_CallID;
                                                    g_DJDialGlobals.g_iTotalVoiceOpened++;
                                                    g_DJDialGlobals.g_iTotalVoiceFree++;
                                                    ++g_DJDialGlobals.AllDeviceRes[iDspModuleID].lVocOpened;
                                                    ++g_DJDialGlobals.AllDeviceRes[iDspModuleID].lVocFreeNum;
                                                    //g_DJDialGlobals.AllDeviceRes[iDspModuleID].pVoice[pAcsEvt->m_DeviceID.m_s16ChannelID].State = DJDataDefClass.VOICE_STATE.VOC_FREE;
                                                    pDial.Change_Voc_State(pOneVoc, DJDialGlobals.VOICE_STATE.VOC_FREE);
                                                    pDial.DrawCount_Voc(g_DJDialGlobals.AllDeviceRes[iDspModuleID].pVoice[pAcsEvt->m_DeviceID.m_s16ChannelID].deviceID.m_s8ModuleID);
                                                }
                                            }
                                            break;

                                        #region XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT
                                        case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT:
                                            {
                                                fixed (DJDialGlobals.PCM_STRUCT* pOnePcm = &g_DJDialGlobals.AllDeviceRes[iDspModuleID].pPcm[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                                {
                                                    pOnePcm->deviceID.m_CallID = pAcsEvt->m_DeviceID.m_CallID;
                                                    DeviceID_t* pDev = &pAcsEvt->m_DeviceID;
                                                    DJAcsApiDef.XMS_ctsResetDevice(g_DJDialGlobals.g_acsHandle, pDev, null);
                                                    DJAcsApiDef.XMS_ctsGetDevState(g_DJDialGlobals.g_acsHandle, pDev, null);
                                                    pDial.DrawPcm_TypeAndAlarm(pOnePcm);
                                                    pDev = null;
                                                    ++g_DJDialGlobals.g_iTotalPcmOpened;
                                                    ++g_DJDialGlobals.AllDeviceRes[iDspModuleID].lPcmOpened;
                                                    pDial.DrawCount_Pcm(pAcsEvt->m_DeviceID.m_s8ModuleID);
                                                }
                                            }
                                            break;
                                        #endregion

                                        default:
                                            break;
                                    }
                                }
                                break;
                            #endregion

                            case XMS_EVT_TYPE.XMS_EVT_CLOSE_DEVICE:		// 在删除设备之前，先发给应用程序CloseDevice事件；调用函数XMS_ctsCloseDevicey也会产生本事件
                                pDial.CloseDeviceOK(&pAcsEvt->m_DeviceID);
                                break;

                            #region XMS_EVT_TYPE.XMS_EVT_DEVICESTATE
                            case XMS_EVT_TYPE.XMS_EVT_DEVICESTATE:
                                {
                                    Acs_GeneralProc_Data* pGeneralData = (Acs_GeneralProc_Data*)((byte*)pAcsEvt + sizeof(Acs_Evt_t));
                                    if (pAcsEvt->m_DeviceID.m_s16DeviceMain == (short)XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH)
                                    {
                                        fixed (DJDialGlobals.TRUNK_STRUCT* pOneTrunk =
                                            &g_DJDialGlobals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pTrunk[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                        {
                                            pOneTrunk->iLineState = pGeneralData->m_s32DeviceState;
                                            pDial.DrawMain_LineState(pOneTrunk->iSeqID, pOneTrunk->iLineState);

                                            if (pAcsEvt->m_DeviceID.m_s16DeviceSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER)
                                            {
                                                pDial.DrawUser_LineState(pOneTrunk->iUserSeqID, pOneTrunk->iLineState);
                                            }
                                        }
                                    }

                                    if (pAcsEvt->m_DeviceID.m_s16DeviceMain == (short)XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT)
                                    {
                                        fixed (DJDialGlobals.PCM_STRUCT* pOnePcm = &g_DJDialGlobals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pPcm[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                        {
                                             pOnePcm->u8E1Type = (byte)((pGeneralData->m_s32DeviceState >> 16) & 0xFF);
                                             pOnePcm->s32AlarmVal = (pGeneralData->m_s32DeviceState & 0xFFFF);

                                             pDial.DrawPcm_TypeAndAlarm(pOnePcm);
                                        }
                                    }
                                    
                                }
                                break;
                            #endregion

                            case XMS_EVT_TYPE.XMS_EVT_UNIFAILURE:
                                // must handle this event in your real System
                                break;

                            #region default
                            default:
                                if ((XMS_DEVMAIN_TYPE)pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH)
                                {
                                    fixed (DJDialGlobals.TRUNK_STRUCT* pOneTrunk = &g_DJDialGlobals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pTrunk[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                    {
                                        pDial.ChannelWork(pOneTrunk, pAcsEvt);
                                    }
                                }
                                else if ((XMS_DEVMAIN_TYPE)pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE)
                                {
                                    fixed (DeviceID_t* pDevID = &g_DJDialGlobals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pVoice[pAcsEvt->m_DeviceID.m_s16ChannelID].UsedDevID)
                                    {
                                        if (pDevID->m_s8ModuleID == 0)
                                        {
                                            break;
                                        }

                                        if ((XMS_DEVMAIN_TYPE)pDevID->m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH)
                                        {
                                            fixed (DJDialGlobals.TRUNK_STRUCT* pOneTrunk = &g_DJDialGlobals.AllDeviceRes[pDevID->m_s8ModuleID].pTrunk[pDevID->m_s16ChannelID])
                                            {
                                                pDial.ChannelWork(pOneTrunk, pAcsEvt);
                                            }
                                        }
                                    }
                                }
                                break;
                            #endregion
                        }
                    }

                    pAcsEvt = null;
            }
            catch(Exception ex)
                {
                    //sw.WriteLine(ex.Message);
                    MessageBox.Show(ex.Message);
                }
            return;
        }

        public unsafe void UserWork(DJDialGlobals.TRUNK_STRUCT* pOneUser, Acs_Evt_t* pAcsEvt)
        {
            if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CLEARCALL)	/*拆线事件*/
            {
                if ((pOneUser->UserState != DJDialGlobals.USER_STATE.USER_FREE) && (pOneUser->UserState != DJDialGlobals.USER_STATE.USER_WAIT_REMOVE))
                {
                    ResetUser(pOneUser, pAcsEvt);
                    return;
                }
            }

            switch (pOneUser->UserState)
            {
                case DJDialGlobals.USER_STATE.USER_FREE:
                    if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CALLIN)	/*用户通道摘机事件*/
                    {
                        DeviceID_t FreeVocDeviceID;
                        int iRet = SearchOneFreeVoice(pOneUser, &FreeVocDeviceID);
                        if (iRet >= 0)
                        {
                            pOneUser->VocDevID = FreeVocDeviceID;
                            fixed (DJDialGlobals.VOICE_STRUCT* pOneVoc = &g_DJDialGlobals.AllDeviceRes[FreeVocDeviceID.m_s8ModuleID].pVoice[FreeVocDeviceID.m_s16ChannelID])
                            {
                                pOneVoc->UsedDevID = pOneUser->deviceID;

                                DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &pOneUser->deviceID, &pOneUser->VocDevID, null);
                                DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &pOneUser->VocDevID, &pOneUser->deviceID, null);

                                PlayTone(&pOneUser->VocDevID, 0);		// dial tone

                                Change_UserState(pOneUser, DJDialGlobals.USER_STATE.USER_OFFHOOK);
                                //pOneUser->UserState = DJDialGlobals.USER_STATE.USER_OFFHOOK;
                            }
                        }
                    }
                    break;

                case DJDialGlobals.USER_STATE.USER_OFFHOOK:
                    sbyte TmpDtmf = My_GetDtmfCode(pAcsEvt); 
                    if (TmpDtmf != -1)								//DTMF按键
                    {
                        if (pOneUser->DtmfCount < 31)
                        {
                            pOneUser->DtmfBuf[pOneUser->DtmfCount] = TmpDtmf;
                            pOneUser->DtmfBuf[pOneUser->DtmfCount+1] = 0;
                            pOneUser->DtmfCount++;
                        }
                        DrawUser_DTMF(pOneUser);

                        PlayTone(&pOneUser->VocDevID, -1);

                        if (pOneUser->DtmfCount >= g_DJDialGlobals.cfg_iCalledLen)
                        {
                            if (g_DJDialGlobals.cfg_iCallOutRule == 2)
                            {
                                DeviceID_t OutUserDeviceID;
                                string strDtmf = new string(pOneUser->DtmfBuf);
                                int i = GetOutUserID(strDtmf, &OutUserDeviceID);
                                if (i > 0)
                                {
                                    sbyte []sCallingNum = new sbyte[32];
                                    sCallingNum.Initialize();

                                    fixed (sbyte* p = &sCallingNum[0])
                                    {
                                        CharsToSBytes(g_DJDialGlobals.cfg_CallingNum.ToCharArray(), (byte*)p, g_DJDialGlobals.cfg_CallingNum.Length);

                                        int nRet = DJAcsApiDef.XMS_ctsMakeCallOut(g_DJDialGlobals.g_acsHandle, &OutUserDeviceID, p, &pOneUser->DtmfBuf[0], null);
                                        if (nRet > 0) //Dial success
                                        {
                                            PlayTone(&pOneUser->VocDevID, 1);		// RingBack tone

                                            // call out OK
                                            fixed (DJDialGlobals.TRUNK_STRUCT* pLinkUser = &g_DJDialGlobals.AllDeviceRes[OutUserDeviceID.m_s8ModuleID].pTrunk[OutUserDeviceID.m_s16ChannelID])
                                            {
                                                pOneUser->LinkDevID = OutUserDeviceID;
                                                pLinkUser->LinkDevID = pOneUser->deviceID;
                                                DrawUser_LinkDev(pOneUser);
                                                DrawUser_LinkDev(pLinkUser);

                                                Change_UserState(pOneUser, DJDialGlobals.USER_STATE.USER_CALLOUT);
                                                Change_UserState(pLinkUser, DJDialGlobals.USER_STATE.USER_RING);

                                                DJAcsApiDef.XMS_ctsSetDevTimer(g_DJDialGlobals.g_acsHandle, &OutUserDeviceID, g_DJDialGlobals.g_Param_Analog.m_u16SendFSKCallerIDTime);
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            string strMsg;

                                            strMsg = String.Format("XMS_ctsMakeCallOut() FAIL! ret = {0}", nRet);
                                            ListBox_AddItem(strMsg);

                                            strMsg = null;
                                        }
                                    }

                                    sCallingNum = null;
                                }
                                strDtmf = null;
                              }
                            
                            DeviceID_t FreeTrkDeviceID;
                            string strUserDtmf = new string(pOneUser->DtmfBuf);
                            int r = SearchOneFreeTrunk(strUserDtmf, &FreeTrkDeviceID);
                            if (r >= 0)
                            {
                                //fixed (char* p = g_DJDialGlobals.cfg_CallingNum.ToCharArray()) //注意Unicode和Asicc
                                //{
                                sbyte []sCallingNum = new sbyte[32];
                                sCallingNum.Initialize();

                                fixed (sbyte* p = &sCallingNum[0])
                                {
                                    CharsToSBytes(g_DJDialGlobals.cfg_CallingNum.ToCharArray(), (byte *)p, g_DJDialGlobals.cfg_CallingNum.Length);

                                    int nRet = DJAcsApiDef.XMS_ctsMakeCallOut(g_DJDialGlobals.g_acsHandle, &FreeTrkDeviceID, p, &pOneUser->DtmfBuf[0], null);

                                    if (nRet > 0)
                                    {
                                        fixed (DJDialGlobals.TRUNK_STRUCT* pLinkTrunk = &g_DJDialGlobals.AllDeviceRes[FreeTrkDeviceID.m_s8ModuleID].pTrunk[FreeTrkDeviceID.m_s16ChannelID])
                                        {
                                            pOneUser->LinkDevID = FreeTrkDeviceID;
                                            pLinkTrunk->LinkDevID = pOneUser->deviceID;
                                            DrawUser_LinkDev(pOneUser);
                                            DrawMain_LinkDev(pLinkTrunk);

                                            CharsToSBytes(g_DJDialGlobals.cfg_CallingNum.ToCharArray(), (byte*)&pLinkTrunk->CallerCode[0], g_DJDialGlobals.cfg_CallingNum.Length);
                                            SBytesToSBytes(&pLinkTrunk->CalleeCode[0], &pOneUser->DtmfBuf[0], pOneUser->DtmfCount - 1);
                                            //CharsToChar(pOneUser->DtmfBuf, pLinkTrunk->CalleeCode, pOneUser->DtmfCount - 1);
                                            DrawMain_CallInfo(pLinkTrunk);

                                            Change_UserState(pOneUser, DJDialGlobals.USER_STATE.USER_CALLOUT);
                                            Change_State(pLinkTrunk, DJDialGlobals.TRUNK_STATE.TRK_CALLOUT);
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        string strMsg;

                                        strMsg = String.Format("XMS_ctsMakeCallOut() FAIL! ret = {0}", nRet);
                                        ListBox_AddItem(strMsg);

                                        strMsg = null;
                                    }
                                }

                                sCallingNum = null;
                            }

                            strUserDtmf = null;
                            PlayTone(&pOneUser->VocDevID, 2);		// busy tone
                            Change_UserState(pOneUser, DJDialGlobals.USER_STATE.USER_WAITHANGUP);
                            //pOneUser->UserState = DJDialGlobals.USER_STATE.USER_WAITHANGUP;

                        }
                    }
                    break;

                case DJDialGlobals.USER_STATE.USER_CALLOUT:
                    {
                    }
                    break;

                case DJDialGlobals.USER_STATE.USER_LINK:
                    {
                    }
                    break;

                case DJDialGlobals.USER_STATE.USER_WAITHANGUP:
                    {
                    }
                    break;

                case DJDialGlobals.USER_STATE.USER_RING:
                    {
                        if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_DEV_TIMER)
                        {
                            DeviceID_t FreeVocDevice;
                            if (SearchOneFreeVoice(pOneUser, &FreeVocDevice) >= 0)
                            {
                                pOneUser->VocDevID = FreeVocDevice;
                                fixed (DJDialGlobals.VOICE_STRUCT* pOneVoc = &g_DJDialGlobals.AllDeviceRes[FreeVocDevice.m_s8ModuleID].pVoice[FreeVocDevice.m_s16ChannelID])
                                {
                                    pOneVoc->UsedDevID = pOneUser->deviceID;

                                    DrawUser_VocInfo(pOneUser);

                                    DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &pOneUser->deviceID, &pOneUser->VocDevID, null);
                                    DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &pOneUser->VocDevID, &pOneUser->deviceID, null);

                                    PlayFSKCallerID(&pOneUser->VocDevID, g_DJDialGlobals.cfg_CallingNum);
                                }
                            }
                        }

                        if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_SENDIODATA) //Send data over
                        {
                            PlayFSKCallerID(&pOneUser->VocDevID, ""); //Stop play fsk

                            if (pOneUser->VocDevID.m_s16DeviceMain != 0)
                            {
                                DJAcsApiDef.XMS_ctsUnlinkDevice(g_DJDialGlobals.g_acsHandle, &pOneUser->deviceID, &pOneUser->VocDevID, null);
                                DJAcsApiDef.XMS_ctsUnlinkDevice(g_DJDialGlobals.g_acsHandle, &pOneUser->VocDevID, &pOneUser->deviceID, null);

                                FreeOneFreeVoice(pOneUser->VocDevID.m_s8ModuleID, pOneUser->VocDevID.m_s16ChannelID);

                                memset((byte *)&pOneUser->VocDevID, 0, sizeof(DeviceID_t));		// 0: Didn't alloc Voc Device

                                DrawUser_VocInfo(pOneUser);
                            }
                        }

                        if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_CALLIN)	/*User Offhook Event*/
                        {
                            fixed (DJDialGlobals.TRUNK_STRUCT* pLinkUser = &g_DJDialGlobals.AllDeviceRes[pOneUser->LinkDevID.m_s8ModuleID].pTrunk[pOneUser->LinkDevID.m_s16ChannelID])
                            {
                                PlayTone(&pLinkUser->VocDevID, -1);

                                if (pLinkUser->VocDevID.m_s16DeviceMain != 0)
                                {
                                    DJAcsApiDef.XMS_ctsUnlinkDevice(g_DJDialGlobals.g_acsHandle, &pLinkUser->deviceID, &pLinkUser->VocDevID, null);
                                    DJAcsApiDef.XMS_ctsUnlinkDevice(g_DJDialGlobals.g_acsHandle, &pLinkUser->VocDevID, &pLinkUser->deviceID, null);

                                    FreeOneFreeVoice(pLinkUser->VocDevID.m_s8ModuleID, pLinkUser->VocDevID.m_s16ChannelID);

                                    memset((byte*)&pLinkUser->VocDevID, 0, sizeof(DeviceID_t));		// 0: Didn't alloc Voc Device

                                    DrawUser_VocInfo(pLinkUser);
                                }

                                DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &pLinkUser->deviceID, &pOneUser->deviceID, null);
                                DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &pOneUser->deviceID, &pLinkUser->deviceID, null);

                                Change_UserState(pLinkUser, DJDialGlobals.USER_STATE.USER_LINK);
                                Change_UserState(pOneUser, DJDialGlobals.USER_STATE.USER_LINK);
                            }
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        public unsafe int strlen(sbyte* pData)
        {
            int i = 0;

            while (pData[i] != (sbyte)'\0')
            {
                i++;
            }

            return i;
        }

        public unsafe ushort ConvertCallerIDToRawFsk(sbyte* IDStr, byte* RawFSKStr, int FSKStrBufLen)
        {
            SystemTime st;
            int nPos, nLen;
            string TmpDateTimeStr;

            GetLocalTime(&st);
            TmpDateTimeStr = String.Format("{0:2},{1:2},{2,2},{3:2}", st.wMonth, st.wDay, st.wHour, st.wMinute);

            nPos = 0;
            nLen = TmpDateTimeStr.Length + strlen((sbyte*)IDStr);

            RawFSKStr[nPos++] = 0x04;			// we use single format
            RawFSKStr[nPos++] = (byte)nLen;

            for (int i = 0; i < (int)TmpDateTimeStr.Length; i++)
            {
                char[] szDtatStr = TmpDateTimeStr.ToCharArray();
                {
                    RawFSKStr[nPos++] = (byte)szDtatStr[i];
                    if (nPos >= (FSKStrBufLen - 1))		// overflow
                        break;
                }
            }

            for (int i = 0; i < (int)strlen(IDStr); i++)
            {
                RawFSKStr[nPos++] = (byte)IDStr[i];
                if (nPos >= (FSKStrBufLen - 1))		// overflow
                    break;
            }

            byte ChkSum = 0;

            for (int i = 0; i < nPos; i++)
            {
                ChkSum += RawFSKStr[i];
            }

            ChkSum = (byte)(0 - ChkSum);

            RawFSKStr[nPos++] = ChkSum;

            TmpDateTimeStr = null;

            return (ushort)nPos;
        }

        public unsafe void PlayFSKCallerID(DeviceID_t* pDev, string strCallerID)
        {
            ushort u16DataLen;
            ushort u16DataType;
            byte []u8DataBuf = new byte[128];

            u8DataBuf.Initialize();
            u16DataType = 0;

            if (strCallerID.Length == 0) //strCallerID为空
            {
                u16DataLen = 0;
            }
            else
            {
                u16DataType = (ushort)XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_FSK;

                sbyte[] u8CallerID = new sbyte[strCallerID.Length + 1];
                u8CallerID.Initialize();

                fixed (sbyte* pCallerID = &u8CallerID[0])
                {
                    CharsToSBytes(strCallerID.ToCharArray(), (byte*)pCallerID, strCallerID.Length);

                    fixed (byte* pDataBuf = &u8DataBuf[0])
                    {
                        u16DataLen = ConvertCallerIDToRawFsk(pCallerID, pDataBuf, 128);
                    }
                }
            }

            fixed (byte* pData = &u8DataBuf[0])
            {
                DJAcsApiDef.XMS_ctsSendIOData(g_DJDialGlobals.g_acsHandle, pDev, u16DataType, u16DataLen, pData);
            }

            strCallerID = null;
            u8DataBuf = null;
        }

        public bool IsTrunk(short s16DevSub)
        {

            if ((s16DevSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_PCM)
                || (s16DevSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_CAS)
                || (s16DevSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_DSS1)
                || (s16DevSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_TUP)
                || (s16DevSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_ISUP)
                || (s16DevSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
                )
            {
                return true;
            }

            return false;
        }

        public int iBase = 0;

        public unsafe int SearchOneFreeTrunk(string strTemp, DeviceID_t* pFreeTrkDeviceID)
        {
            int iTmp;
            sbyte s8ModID;
            short s16ChID;

            if (g_DJDialGlobals.cfg_iCallOutRule == 2)
            {
                iTmp = Convert.ToInt32(strTemp);

                iTmp %= 1000;

                s16ChID = g_DJDialGlobals.MapTable_Trunk[iTmp].m_s16ChannelID;
                s8ModID = g_DJDialGlobals.MapTable_Trunk[iTmp].m_s8ModuleID;

                if (iTmp >= g_DJDialGlobals.g_iTotalTrunk) return -1;

                if ((g_DJDialGlobals.AllDeviceRes[s8ModID].pTrunk[s16ChID].iLineState == (int)DEVICE_CALL_STATE.DCS_FREE)
                    && (g_DJDialGlobals.AllDeviceRes[s8ModID].pTrunk[s16ChID].State == DJDialGlobals.TRUNK_STATE.TRK_FREE)
                    && IsTrunk(g_DJDialGlobals.AllDeviceRes[s8ModID].pTrunk[s16ChID].deviceID.m_s16DeviceSub))
                {
                    *pFreeTrkDeviceID = g_DJDialGlobals.AllDeviceRes[s8ModID].pTrunk[s16ChID].deviceID;
                    return iTmp;
                }
                return -1;
            }

            // Sequence Mode or Loop Mode
	        if ( g_DJDialGlobals.cfg_iCallOutRule == 0 )		// Sequence Mode
	        {
                iLoopTrunkStart = 0;
	        }
             
            for ( int i = 0; i < g_DJDialGlobals.g_iTotalTrunk; i ++ )
	        {
                s8ModID = g_DJDialGlobals.MapTable_Trunk[iLoopTrunkStart].m_s8ModuleID;
                s16ChID = g_DJDialGlobals.MapTable_Trunk[iLoopTrunkStart].m_s16ChannelID;

                if (s16ChID % 16 == 0)
                {
                }
		        if ( ( g_DJDialGlobals.AllDeviceRes[s8ModID].pTrunk[s16ChID].iLineState == (int)DEVICE_CALL_STATE.DCS_FREE )
                    && (g_DJDialGlobals.AllDeviceRes[s8ModID].pTrunk[s16ChID].State == DJDialGlobals.TRUNK_STATE.TRK_FREE)
			        //&& IsDigitTrunk(AllDeviceRes[s8ModID].pTrunk[s16ChID].deviceID.m_s16DeviceSub) )
			        && IsTrunk(g_DJDialGlobals.AllDeviceRes[s8ModID].pTrunk[s16ChID].deviceID.m_s16DeviceSub) )
		        {
			        *pFreeTrkDeviceID = g_DJDialGlobals.AllDeviceRes[s8ModID].pTrunk[s16ChID].deviceID;
                    iTmp = iLoopTrunkStart;
                    iLoopTrunkStart = (iLoopTrunkStart + 1) % g_DJDialGlobals.g_iTotalTrunk;
			        return iTmp;
		        }
                iLoopTrunkStart = (iLoopTrunkStart + 1) % g_DJDialGlobals.g_iTotalTrunk;
	        }

            return -1;
        }

        public unsafe sbyte My_GetDtmfCode(Acs_Evt_t* pAcsEvt)
        {
            if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_RECVIODATA)	/*IO Data事件*/
            {
                Acs_IO_Data* pIOData = (Acs_IO_Data*)((byte*)pAcsEvt + sizeof(Acs_Evt_t));

                if ((pIOData->m_u16IoType == (short)XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF)
                    && (pIOData->m_u16IoDataLen > 0))
                {
                    sbyte* p = (sbyte*)((sbyte*)pAcsEvt + sizeof(Acs_Evt_t) + sizeof(Acs_IO_Data));
                    sbyte pValue = *p;
                    return pValue;
                }
            }

            return -1;	// not a good DTMF
        }

        public unsafe void ResetUser(DJDialGlobals.TRUNK_STRUCT* pOneUser, Acs_Evt_t* pAcsEvt)
        {
            if (pOneUser->VocDevID.m_s16DeviceMain != 0) 
            {
                DJAcsApiDef.XMS_ctsUnlinkDevice(g_DJDialGlobals.g_acsHandle, &pOneUser->deviceID, &pOneUser->VocDevID, null);
                DJAcsApiDef.XMS_ctsUnlinkDevice(g_DJDialGlobals.g_acsHandle, &pOneUser->VocDevID, &pOneUser->deviceID, null);

                FreeOneFreeVoice(pOneUser->VocDevID.m_s8ModuleID, pOneUser->VocDevID.m_s16ChannelID);
            }

            if (pOneUser->LinkDevID.m_s16DeviceMain != 0)
            {
                DJAcsApiDef.XMS_ctsUnlinkDevice(g_DJDialGlobals.g_acsHandle, &pOneUser->deviceID, &pOneUser->LinkDevID, null);
                DJAcsApiDef.XMS_ctsUnlinkDevice(g_DJDialGlobals.g_acsHandle, &pOneUser->LinkDevID, &pOneUser->deviceID, null);

                fixed (DJDialGlobals.TRUNK_STRUCT* pLinkTrunk =
                                    &g_DJDialGlobals.AllDeviceRes[pOneUser->LinkDevID.m_s8ModuleID].pTrunk[pOneUser->LinkDevID.m_s16ChannelID])
                {
                    memset((byte*)&pLinkTrunk->LinkDevID, 0, sizeof(DeviceID_t));
                    DJAcsApiDef.XMS_ctsClearCall(g_DJDialGlobals.g_acsHandle, &pLinkTrunk->deviceID, 0, null);


                    if (pOneUser->LinkDevID.m_s16DeviceSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER)
                    {
                        //pLinkUser = pLinkTrunk;
                        if (pLinkTrunk->UserState == DJDialGlobals.USER_STATE.USER_RING)
                            InitUserChannel(pLinkTrunk);
                    }
                }
            }

            InitUserChannel(pOneUser);
        }

        public unsafe void ResetTrunk(DJDialGlobals.TRUNK_STRUCT* pOneTrunk, Acs_Evt_t* pAcsEvt)
        {
            if (pOneTrunk->LinkDevID.m_s16DeviceMain != 0)
            {
                DJAcsApiDef.XMS_ctsUnlinkDevice(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, &pOneTrunk->LinkDevID, null);
                DJAcsApiDef.XMS_ctsUnlinkDevice(g_DJDialGlobals.g_acsHandle, &pOneTrunk->LinkDevID, &pOneTrunk->deviceID, null);

                fixed (DJDialGlobals.TRUNK_STRUCT* pLinkUser =
                                    &g_DJDialGlobals.AllDeviceRes[pOneTrunk->LinkDevID.m_s8ModuleID].pTrunk[pOneTrunk->LinkDevID.m_s16ChannelID])
                {
                    DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &pLinkUser->VocDevID, &pLinkUser->deviceID, null);
                    DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &pLinkUser->deviceID, &pLinkUser->VocDevID, null);

                    PlayTone(&pLinkUser->VocDevID, 2);		// busy tone

                    memset((byte*)&pLinkUser->LinkDevID, 0, sizeof(DeviceID_t));
                }
            }

            if (pOneTrunk->VocDevID.m_s16DeviceMain != 0)
            {
                DJAcsApiDef.XMS_ctsUnlinkDevice(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, &pOneTrunk->VocDevID, null);
                DJAcsApiDef.XMS_ctsUnlinkDevice(g_DJDialGlobals.g_acsHandle, &pOneTrunk->VocDevID, &pOneTrunk->deviceID, null);

                FreeOneFreeVoice(pOneTrunk->VocDevID.m_s8ModuleID, pOneTrunk->VocDevID.m_s16ChannelID);
                fixed (DJDialGlobals.VOICE_STRUCT* pOneVoc = &g_DJDialGlobals.AllDeviceRes[pOneTrunk->VocDevID.m_s8ModuleID].pVoice[pOneTrunk->VocDevID.m_s16ChannelID])
                {
                    memset((byte *)&pOneVoc->UsedDevID, 0, sizeof(DeviceID_t));		// 0: didn't alloc Device
                }
                memset((byte *)&pOneTrunk->VocDevID, 0, sizeof(DeviceID_t));		// 0: didn't alloc Device
            }

            InitTrunkChannel(pOneTrunk);
        }

        public unsafe int SearchOneFreeVoice(DJDialGlobals.TRUNK_STRUCT* pOneTrunk, DeviceID_t* pFreeVocDeviceID)
        {
	        sbyte 		s8ModID;
	        short 		s16ChID;

	        s8ModID = pOneTrunk->deviceID.m_s8ModuleID;

            if (g_DJDialGlobals.cfg_iVoiceRule == 0)			// Fix relationship between Trunk & Voice
	        {
		        s16ChID = pOneTrunk->deviceID.m_s16ChannelID;
		
		        int i = pOneTrunk->iModSeqID;

                if (i < g_DJDialGlobals.AllDeviceRes[s8ModID].lVocNum)
		        {
                    fixed (DJDialGlobals.VOICE_STRUCT* pOneVoice = &g_DJDialGlobals.AllDeviceRes[s8ModID].pVoice[i])
                    {
                        //if (pOneVoice->State != DJDialGlobals.VOICE_STATE.VOC_WAITOPEN)
                        if (pOneVoice->State == DJDialGlobals.VOICE_STATE.VOC_FREE)
                        {
                            *pFreeVocDeviceID = pOneVoice->deviceID;

                            // use this voice device 
                            Change_Voc_State(pOneVoice, DJDialGlobals.VOICE_STATE.VOC_USED);
                            g_DJDialGlobals.AllDeviceRes[s8ModID].lVocFreeNum--;
                            g_DJDialGlobals.g_iTotalVoiceFree--;
                            DrawCount_Voc(s8ModID);
                            return i;
                        }
                    }
                }
		    }

		    return -1;
	    }

        public unsafe void FreeOneFreeVoice(int iModID, int iChID)
        {
            if (g_DJDialGlobals.AllDeviceRes[iModID].lFlag == 1)
            {
                fixed (DJDialGlobals.VOICE_STRUCT* pOneVoc = &g_DJDialGlobals.AllDeviceRes[iModID].pVoice[iChID])
                {
                    //pOneVoc->State = DJDialGlobals.VOICE_STATE.VOC_FREE; ;
                    Change_Voc_State(pOneVoc, DJDialGlobals.VOICE_STATE.VOC_FREE);
                    g_DJDialGlobals.AllDeviceRes[iModID].lVocFreeNum++;
                    g_DJDialGlobals.g_iTotalVoiceFree++;
                    DrawCount_Voc((sbyte)iModID);
                }
            }
        }

        public unsafe void SpecialForCas(DJDialGlobals.TRUNK_STRUCT* pOneTrunk, Acs_Evt_t* pAcsEvt)
        {
            if (pOneTrunk->deviceID.m_s16DeviceSub != (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_CAS)
            {
                return;
            }

            if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CAS_MFC_START)	// 开始接收MFC，需要一个Voc设备
            {
                DeviceID_t FreeVocDeviceID;

                int iFreeVoc = SearchOneFreeVoice(pOneTrunk, &FreeVocDeviceID);
                if (iFreeVoc >= 0)
                {
                    pOneTrunk->VocDevID = FreeVocDeviceID;
                    fixed (DJDialGlobals.VOICE_STRUCT* pOneVoc = &g_DJDialGlobals.AllDeviceRes[FreeVocDeviceID.m_s8ModuleID].pVoice[FreeVocDeviceID.m_s16ChannelID])
                    {
                        pOneVoc->UsedDevID = pOneTrunk->deviceID;
                        DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &FreeVocDeviceID, &pOneTrunk->deviceID, null);
                        DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, &FreeVocDeviceID, null);

                        g_DJDialGlobals.g_Param_CAS.m_VocDevID = FreeVocDeviceID;

                         /*DJAcsApiDef.XMS_ctsSetParam(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, 0,
                                (ushort)sizeof(CmdParamData_CAS_t), g_DJDialGlobals.g_Param_CAS); // CAS_PARAM_UNIPARAM = 0*/

                       fixed (CmdParamData_CAS_t* pParamCas = &g_DJDialGlobals.g_Param_CAS)
                        {
                            DJAcsApiDef.XMS_ctsSetParam(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, 0,
                                (ushort)sizeof(CmdParamData_CAS_t), pParamCas); // CAS_PARAM_UNIPARAM = 0
                        }
                    }
                }
            }

            if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CAS_MFC_END)	// 接收MFC完毕，释放Voc设备
            {
                DJAcsApiDef.XMS_ctsUnlinkDevice(g_DJDialGlobals.g_acsHandle, &pOneTrunk->VocDevID, &pOneTrunk->deviceID, null);
                DJAcsApiDef.XMS_ctsUnlinkDevice(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, &pOneTrunk->VocDevID, null);

                DeviceID_t* pVocDevID = &pOneTrunk->VocDevID;
                {
                    fixed (DJDialGlobals.VOICE_STRUCT* pOneVoc = &g_DJDialGlobals.AllDeviceRes[pVocDevID->m_s8ModuleID].pVoice[pVocDevID->m_s16ChannelID])
                    {
                        FreeOneFreeVoice(pOneVoc->deviceID.m_s8ModuleID, pOneVoc->deviceID.m_s16ChannelID);

                        memset((byte*)&pOneTrunk->VocDevID, 0, sizeof(DeviceID_t));
                        memset((byte *)&pOneVoc->UsedDevID, 0, sizeof(DeviceID_t));
                    }
                }
            }
        }

        public unsafe int PlayTone(DeviceID_t* pVocDevID, int iPlayType)
        {
            ushort u16IoLen = 0;
            ushort u16IoType = 0;
            int r = 0;
            byte[] IoDataBuf = new byte[16];

            IoDataBuf.Initialize();

            if (iPlayType == -1)	// Stop Play Tone
            {
                u16IoLen = 0;
                u16IoType = (ushort)XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_GTG;
            }
            else
            {
                u16IoType = (ushort)XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_GTG;
                u16IoLen = 1;

                switch (iPlayType)
                {
                    case 0:		// Dial Tone
                        IoDataBuf[0] = (byte)'G';
                        break;
                    case 1:		// Ring Back Tone
                        IoDataBuf[0] = (byte)'H';
                        break;
                    case 2:		// Busy Tone
                        IoDataBuf[0] = (byte)'I';
                        break;
                }
            }

            fixed (byte* p = &IoDataBuf[0])
            {
                r = DJAcsApiDef.XMS_ctsSendIOData(g_DJDialGlobals.g_acsHandle, pVocDevID, u16IoType, u16IoLen, p);
            }

            IoDataBuf = null;
            return r;
        }

        public unsafe void TrunkWork(DJDialGlobals.TRUNK_STRUCT* pOneTrunk, Acs_Evt_t* pAcsEvt)
        {
            byte TmpGtd;

            {
                if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CLEARCALL)	/*拆线事件*/
                {
                    if ((pOneTrunk->State != DJDialGlobals.TRUNK_STATE.TRK_FREE) && (pOneTrunk->State != DJDialGlobals.TRUNK_STATE.TRK_WAIT_REMOVE))
                    {
                        ResetTrunk(pOneTrunk, pAcsEvt);
                    }
   //                 SimulateCallOut();
                }

                switch (pOneTrunk->State)
                {
                    case DJDialGlobals.TRUNK_STATE.TRK_FREE:
                        SpecialForCas(pOneTrunk, pAcsEvt);// Special code for CAS(SS1)
                        break;

                    case DJDialGlobals.TRUNK_STATE.TRK_CALLOUT:
                        SpecialForCas(pOneTrunk, pAcsEvt);// Special code for CAS(SS1)
                        if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CALLOUT)
                        {
                            Acs_CallControl_Data* pCallControl = (Acs_CallControl_Data*)((byte*)pAcsEvt + sizeof(Acs_Evt_t));

                            if (pCallControl->m_s32AcsEvtState == 1)	// 呼出成功，对方摘机
                            {
                                fixed (DJDialGlobals.TRUNK_STRUCT* pLinkUser =
                                    &g_DJDialGlobals.AllDeviceRes[pOneTrunk->LinkDevID.m_s8ModuleID].pTrunk[pOneTrunk->LinkDevID.m_s16ChannelID])
                                {
                                    // unlink voc
                                    // next line will trigger a BUG
                                    //My_DualUnink (  pUserDevID, &pTrunk[pUserDevID->m_s16ChannelID].VocDevID );
                                    //

                                    // Link trunk and user
                                    if (pOneTrunk->deviceID.m_s8MachineID == pLinkUser->deviceID.m_s8MachineID)
                                    {
                                        DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, &pOneTrunk->LinkDevID, null);
                                        DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &pOneTrunk->LinkDevID, &pOneTrunk->deviceID, null);
                                    }

                                    Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_LINK);
                                    Change_UserState(pLinkUser, DJDialGlobals.USER_STATE.USER_LINK);
                                }
                            }
                            else		// 呼出失败
                            {
                                //DrawMain_Reason(pOneTrunk, pCallControl->m_s32AcsEvtErrCode, pCallControl->m_s32CallClearCause);
                                DrawMain_Reason(pOneTrunk, pCallControl->m_s32AcsEvtErrCode, pCallControl->m_s32CallClearCause);
                                Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_FREE);

                                fixed (DJDialGlobals.TRUNK_STRUCT* pLinkUser =
                                    &g_DJDialGlobals.AllDeviceRes[pOneTrunk->LinkDevID.m_s8ModuleID].pTrunk[pOneTrunk->LinkDevID.m_s16ChannelID])
                                {

                                    PlayTone(&pLinkUser->VocDevID, 2);		// busy tone

                                    memset((byte*)&pLinkUser->LinkDevID, 0, sizeof(DeviceID_t));		// 0: didn't alloc Link Device
                                    Change_UserState(pLinkUser, DJDialGlobals.USER_STATE.USER_WAITHANGUP);
                                }
                            }
                        }
                        break;

                    case DJDialGlobals.TRUNK_STATE.TRK_SIM_CALLOUT:
                        //SpecialForCas(pOneTrunk, pAcsEvt);// Special code for CAS(SS1)
                        if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CALLOUT)
                        {
                            Acs_CallControl_Data* pCallControl = (Acs_CallControl_Data*)((byte*)pAcsEvt + sizeof(Acs_Evt_t));

                            if (pOneTrunk->deviceID.m_s16DeviceMain == (short)XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH
                                && pOneTrunk->deviceID.m_s16DeviceSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
                            {
                                DrawMain_Analog_Reason(pOneTrunk, "");

                                DJAcsApiDef.XMS_ctsSetDevTimer(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, g_DJDialGlobals.g_Param_Analog.m_u16NoDialToneAfterOffHook);
                                Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_SIM_ANALOG_OFFHOOK);
                                return;
                            }

                            if (pCallControl->m_s32AcsEvtState == 1)	// 呼出成功，对方摘机
                            {
                                DeviceID_t FreeVocDeviceID;
                                int iChID = SearchOneFreeVoice(pOneTrunk, &FreeVocDeviceID);
                                if (iChID >= 0)
                                {
                                    pOneTrunk->VocDevID = FreeVocDeviceID;
                                    
                                    g_DJDialGlobals.AllDeviceRes[FreeVocDeviceID.m_s8ModuleID].pVoice[FreeVocDeviceID.m_s16ChannelID].UsedDevID = pOneTrunk->deviceID;

                                    DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, &pOneTrunk->VocDevID, null);
                                    DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &pOneTrunk->VocDevID, &pOneTrunk->deviceID, null);
                                }
                                Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_SIM_LINK);
                            }
                            else		// 呼出失败
                            {
                                DrawMain_Reason(pOneTrunk, pCallControl->m_s32AcsEvtErrCode, pCallControl->m_s32CallClearCause);
                                //pOneTrunk->State = DJDialGlobals.TRUNK_STATE.TRK_FREE;
                                Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_FREE);
                            }
                        }
                        break;

                    case DJDialGlobals.TRUNK_STATE.TRK_SIM_LINK:
                        {
                            if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_LINKDEVICE)
                            {
                                //PlayDTMF(&pOneTrunk->VocDevID, "12345678");		// play dtmf
                                PlayDTMF(&pOneTrunk->VocDevID, "12345");
                                Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_PLAYDTMF);
                            }
                        }
                        break;

                    case DJDialGlobals.TRUNK_STATE.TRK_SIM_ANALOG_OFFHOOK:
                        if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_DEV_TIMER) //
                        {
                            // time out
                            DrawMain_Analog_Reason(pOneTrunk, "Wait Dial Tone TimeOut");

                            DJAcsApiDef.XMS_ctsClearCall(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, 0, null);

                            Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_HANGUP);
                        }

                        TmpGtd = My_GetGtdOrPVDCode(pAcsEvt);
                        if (TmpGtd != 0)
                        {
                            if (TmpGtd == (byte)'I' || TmpGtd == (byte)'J' || TmpGtd == (byte)'K')		// Busy Tone
                            {
                                string strMsg;
                                strMsg = String.Format("Busy Tone : {0}", TmpGtd);
                                DrawMain_Analog_Reason(pOneTrunk, strMsg);

                                DJAcsApiDef.XMS_ctsClearCall(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, 0, null);
                                Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_HANGUP);
                            }
                            else if (TmpGtd == (byte)'G')		// Dial Tone
                            {
                                byte[] bCalledNum = new byte[g_DJDialGlobals.cfg_SimCalledNum.Length + 1];
                                bCalledNum.Initialize();

                                fixed (byte* pCalledNum = &bCalledNum[0])
                                {
                                    CharsToSBytes(g_DJDialGlobals.cfg_SimCalledNum.ToCharArray(), pCalledNum, g_DJDialGlobals.cfg_SimCalledNum.Length);
                                    // start semd DTMF

                                    //C#中char是UNICODE编码,占两个字节,所以发送号码时注意:把UNICODE转为ASICC
                                    int ret = DJAcsApiDef.XMS_ctsSendIOData(g_DJDialGlobals.g_acsHandle, &pAcsEvt->m_DeviceID,
                                        (ushort)XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF, (ushort)g_DJDialGlobals.cfg_SimCalledNum.Length, pCalledNum);

                                    if (ret > 0)
                                    {
                                        DJAcsApiDef.XMS_ctsSetDevTimer(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, g_DJDialGlobals.g_Param_Analog.m_u16Ringback_NoAnswerTime);
                                        Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_SIM_ANALOG_DIALING);
                                    }
                                    else
                                    {
                                        ResetTrunk(pOneTrunk, pAcsEvt);
                                    }

                                    bCalledNum = null; //释放new的内存
                                }
                            }
                        }
                        break;

                    case DJDialGlobals.TRUNK_STATE.TRK_SIM_ANALOG_DIALING:
                        {
                            if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_DEV_TIMER)
                            {
                                // time out
                                DrawMain_Analog_Reason(pOneTrunk, "Wait Dial Tone TimeOut");

                                DJAcsApiDef.XMS_ctsClearCall(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, 0, null);

                                Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_HANGUP);
                            }

                            TmpGtd = My_GetGtdOrPVDCode(pAcsEvt);

                            if (TmpGtd != 0)
                            {
                                if (TmpGtd == (byte)'I' || TmpGtd == (byte)'J' || TmpGtd == (byte)'K')		// Busy Tone
                                {
                                    string TmpStr;

                                    TmpStr= String.Format("Callee Busy Tone : {0}", (char)TmpGtd);
                                    DrawMain_Analog_Reason(pOneTrunk, TmpStr);

                                    DJAcsApiDef.XMS_ctsClearCall(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, 0, null);

                                    Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_HANGUP);
                                }
                                else if (TmpGtd == (byte)'h' || TmpGtd == (byte)'b')
                                {
                                    string TmpStr;

                                    TmpStr = String.Format("Callee Answer : {0}", (char)TmpGtd);
                                    DrawMain_Analog_Reason(pOneTrunk, TmpStr);

                                    PlayDTMF(&pOneTrunk->VocDevID, "12345");		// play dtmf

                                    Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_PLAYDTMF);
                                }
                            }
                            
                        }
                        break;

                    case DJDialGlobals.TRUNK_STATE.TRK_PLAYDTMF:
                        if (CheckPlayGTGEnd(pOneTrunk, pAcsEvt))	/*play完成事件*/
                        {
                            /*
                            Thread.Sleep(2000);
                            PlayDTMF(&pOneTrunk->VocDevID, "123456");
                            Thread.Sleep(2000);
                            PlayDTMF(&pOneTrunk->VocDevID, "1");
                            */
                            DJAcsApiDef.XMS_ctsClearCall(g_DJDialGlobals.g_acsHandle, &pOneTrunk->deviceID, 0, null);

                            Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_HANGUP);
                        }
                        break;

                    default:
                        break;
                }
            }
        }

        public unsafe bool CheckPlayGTGEnd(DJDialGlobals.TRUNK_STRUCT* pOneTrunk, Acs_Evt_t* pAcsEvt)
        {
            if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_SENDIODATA)
            {
                return true;
            }

            return false;
        }

        public unsafe int PlayDTMF(DeviceID_t* pVocDevID, string DtmfStr)
        {
            int len = 0;
            ushort u16IoType = 0;
            ushort u16IoLen = 0;
            byte[] IoDataBuf = new byte[16];
            int r = 0;

            IoDataBuf.Initialize();

            if (DtmfStr == "")	// Stop Play Dtmf
            {
                u16IoLen = 0;
            }
            else
            {
                u16IoType = (ushort)XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF;

                len = DtmfStr.Length;
                if (len > 16)
                {
                    len = 16;
                }
                u16IoLen = (ushort)len;

                for (int i = 0; i < len; ++i)
                {
                    IoDataBuf[i] = (byte)DtmfStr[i];
                }
            }

            fixed (byte* p = &IoDataBuf[0])
            {
                r = DJAcsApiDef.XMS_ctsSendIOData(g_DJDialGlobals.g_acsHandle, pVocDevID, u16IoType, u16IoLen, p);
            }

            DtmfStr = null;
            IoDataBuf = null;
            return r;

        }

        public unsafe void ChannelWork(DJDialGlobals.TRUNK_STRUCT* pOneTrunk, Acs_Evt_t* pAcsEvt)
        {
            if (pOneTrunk->deviceID.m_s16DeviceSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER)
            {
                UserWork(pOneTrunk, pAcsEvt);
            }
            else
            {
                TrunkWork(pOneTrunk, pAcsEvt);
            }
        }

        public unsafe void SimulateCallOut()
        {
            DeviceID_t FreeTrunkDeviceID;
            int iItemID = SearchOneFreeTrunk(g_DJDialGlobals.cfg_SimCalledNum, &FreeTrunkDeviceID);
            if (iItemID >= 0)
            {
                g_DJDialGlobals.cfg_SimCalledNum = textBox_CalledNum.Text;
                g_DJDialGlobals.cfg_CallingNum = textBox_CallingNum.Text;

                fixed (DJDialGlobals.TRUNK_STRUCT* pOneTrunk = &g_DJDialGlobals.AllDeviceRes[FreeTrunkDeviceID.m_s8ModuleID].pTrunk[FreeTrunkDeviceID.m_s16ChannelID])
                {
                    if (pOneTrunk->deviceID.m_s16DeviceMain == (short)XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH
                        && pOneTrunk->deviceID.m_s16DeviceSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)//如果是中继设备,CallOut前需要绑定语音设备
                    {
                        DeviceID_t FreeVocDeviceID;
                        if (SearchOneFreeVoice(pOneTrunk, &FreeVocDeviceID) >= 0) //找到空闲语音设备
                        {
                            pOneTrunk->VocDevID = FreeVocDeviceID;
                            fixed (DJDialGlobals.VOICE_STRUCT* pOneVoice = &g_DJDialGlobals.AllDeviceRes[FreeVocDeviceID.m_s8ModuleID].pVoice[FreeVocDeviceID.m_s16ChannelID])
                            {
                                pOneVoice->UsedDevID = pOneTrunk->deviceID;
                                DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &FreeTrunkDeviceID, &FreeVocDeviceID, null);
                                DJAcsApiDef.XMS_ctsLinkDevice(g_DJDialGlobals.g_acsHandle, &FreeVocDeviceID, &FreeTrunkDeviceID, null);
                                SetGtd_AnalogTrunk(&FreeVocDeviceID);
                            }
                        }
                        else
                        {
                            MessageBox.Show("No VoiceDevice is Free!, SearchOneFreeVoice Failed!");
                            return;
                        }
                    }

                    sbyte[] bCaller = new sbyte[g_DJDialGlobals.cfg_CallingNum.Length + 1];
                    sbyte[] bCalled = new sbyte[g_DJDialGlobals.cfg_SimCalledNum.Length + 1];

                    bCaller.Initialize();
                    bCalled.Initialize();

                    fixed (sbyte* pCaller = &bCaller[0])
                    {
                        fixed (sbyte* pCalled = &bCalled[0])
                        {
                            CharsToSBytes(g_DJDialGlobals.cfg_CallingNum.ToCharArray(), (byte*)pCaller, g_DJDialGlobals.cfg_CallingNum.Length);
                            CharsToSBytes(g_DJDialGlobals.cfg_SimCalledNum.ToCharArray(), (byte*)pCalled, g_DJDialGlobals.cfg_SimCalledNum.Length);

                            int r = DJAcsApiDef.XMS_ctsMakeCallOut(g_DJDialGlobals.g_acsHandle, &FreeTrunkDeviceID, pCaller, pCalled, null);
                            if (r > 0)
                            {
                                DrawMain_LinkDev(pOneTrunk);

                                CharsToSBytes(g_DJDialGlobals.cfg_CallingNum.ToCharArray(), (byte*)&pOneTrunk->CallerCode[0], g_DJDialGlobals.cfg_CallingNum.Length);
                                CharsToSBytes(g_DJDialGlobals.cfg_SimCalledNum.ToCharArray(), (byte*)&pOneTrunk->CalleeCode[0], g_DJDialGlobals.cfg_SimCalledNum.Length);

                                DrawMain_CallInfo(pOneTrunk);

                                Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_SIM_CALLOUT);
                            }
                            else
                            {
                                string strMsg;
                                strMsg = String.Format("XMS_ctsMakeCallOut() FAIL! ret = {0}", r);
                                ListBox_AddItem(strMsg);
                                strMsg = null;
                                return;
                            }
                        }  
                    }
                    bCalled = null;
                    bCaller = null;
                }
            }
        }

        /*private void DialForm_Load(object sender, EventArgs e)
        {
        }

        private void timer_loopCallOut_Tick(object sender, EventArgs e)
        {
            SimulateCallOut();
        }*/

        protected unsafe override void OnFormClosing(FormClosingEventArgs e) //重载关闭按钮
        {
            sw.Close();
            fs.Close();

            SaveTextBox();
            g_DJDialGlobals.WriteToConfig();

            int iResult = 0;
            iResult = DJAcsApiDef.XMS_acsCloseStream(g_DJDialGlobals.g_acsHandle, null);
            if (iResult == (int)ERROR_CODE.ACSPOSITIVE_ACK)
            {
                listBox_OptAndEvtInfo.Items.Add("XMS_acsCloseStream Success");
            }
            else
            {
                listBox_OptAndEvtInfo.Items.Add("XMS_acsCloseStream Fail");
            }

            base.OnFormClosing(e);
        }

        private void Btn_Exit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Btn_Simulate_Click(object sender, EventArgs e)
        {
           SimulateCallOut(); 

           /*System.Timers.Timer t = new System.Timers.Timer(200);  //实例化Timer类，设置间隔时间为10000毫秒；   
            t.Elapsed +=   new System.Timers.ElapsedEventHandler(theout);  //到达时间的时候执行事件；   
            t.AutoReset = true;  //设置是执行一次（false）还是一直执行(true)；   
            t.Enabled = true;  //是否执行System.Timers.Timer.Elapsed事件；*/
        }

        public void theout(object source, System.Timers.ElapsedEventArgs e)
        {
            SimulateCallOut();
        }

        public unsafe void ReOpen_AllDevice()
        {
            for (int i = 0; i < g_DJDialGlobals.g_iTotalModule; i++)
            {
                sbyte s8DspModID = g_DJDialGlobals.MapTable_Module[i];

                g_DJDialGlobals.AllDeviceRes[s8DspModID].bErrFlag = false;
                DrawCount_ErrFlag(s8DspModID);
                g_DJDialGlobals.AllDeviceRes[s8DspModID].RemoveState = DJDialGlobals.REMOVE_STATE.DSP_REMOVE_STATE_NONE;
                DrawCount_RemoveState(s8DspModID);

                // Open Board Device
                if (g_DJDialGlobals.AllDeviceRes[s8DspModID].bOpenFlag == false) //board not open
                {
                    fixed (DeviceID_t* pBoardDev = &g_DJDialGlobals.AllDeviceRes[s8DspModID].deviceID)
                    {
                        DJAcsApiDef.XMS_ctsOpenDevice(g_DJDialGlobals.g_acsHandle, pBoardDev, null);
                    }
                }

                //Open Voc Device
                for (int j = 0; j < g_DJDialGlobals.AllDeviceRes[s8DspModID].lVocFreeNum; j++)
                {
                    if (g_DJDialGlobals.AllDeviceRes[s8DspModID].pVoice[j].State == DJDialGlobals.VOICE_STATE.VOC_WAITOPEN)
                    {
                        fixed (DeviceID_t* pVocDev = &g_DJDialGlobals.AllDeviceRes[s8DspModID].pVoice[j].deviceID)
                        {
                            DJAcsApiDef.XMS_ctsOpenDevice(g_DJDialGlobals.g_acsHandle, pVocDev, null);
                        }
                    }
                }

                // Open Trunk Device
                for (int j = 0; j < g_DJDialGlobals.AllDeviceRes[s8DspModID].lTrunkNum; j++)
                {
                    if (g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk[j].State == DJDialGlobals.TRUNK_STATE.TRK_WAITOPEN)
                    {
                        fixed (DeviceID_t* pTukDev = &g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk[j].deviceID)
                        {
                            DJAcsApiDef.XMS_ctsOpenDevice(g_DJDialGlobals.g_acsHandle, pTukDev, null);
                        }
                    }
                }

                // Open Pcm Device
                for (int j = 0; j < g_DJDialGlobals.AllDeviceRes[s8DspModID].lPcmNum; j++)
                {
                    if (g_DJDialGlobals.AllDeviceRes[s8DspModID].pPcm[j].bOpenFlag == false)
                    {
                        fixed (DeviceID_t* pPcmDev = &g_DJDialGlobals.AllDeviceRes[s8DspModID].pPcm[j].deviceID)
                        {
                            DJAcsApiDef.XMS_ctsOpenDevice(g_DJDialGlobals.g_acsHandle, pPcmDev, null);
                        }
                    }
                }
            }
        }

        public unsafe void Remove_OneDsp()
        {
            if (listView_count.SelectedItems.Count == 0)
            {
                MessageBox.Show("Please select a valid DSP module in the upper list!");
                return;
            }
            int nNumOfSelected = listView_count.SelectedIndices[0];

            if (nNumOfSelected <= 0 || nNumOfSelected > g_DJDialGlobals.g_iTotalModule)
            {
                MessageBox.Show("Please select a valid DSP module in the upper list!");
                return;
            }

            sbyte s8ModuleID = g_DJDialGlobals.MapTable_Module[nNumOfSelected - 1]; // 0行是Total
            g_DJDialGlobals.AllDeviceRes[s8ModuleID].RemoveState = DJDialGlobals.REMOVE_STATE.DSP_REMOVE_STATE_START;
            DrawCount_RemoveState(s8ModuleID);

            for (int i = 0; i < g_DJDialGlobals.AllDeviceRes[s8ModuleID].lTrunkNum; i++)
            {
                fixed (DJDialGlobals.TRUNK_STRUCT* pOneTrunk = &g_DJDialGlobals.AllDeviceRes[s8ModuleID].pTrunk[i])
                {
                    if (pOneTrunk->State == DJDialGlobals.TRUNK_STATE.TRK_FREE)
                    {
                        Change_State(pOneTrunk, DJDialGlobals.TRUNK_STATE.TRK_WAIT_REMOVE);
                    }
                }
            }

            for (int i = 0; i < g_DJDialGlobals.AllDeviceRes[s8ModuleID].lVocNum; i++)
            {
                fixed (DJDialGlobals.VOICE_STRUCT* pOneVoc = &g_DJDialGlobals.AllDeviceRes[s8ModuleID].pVoice[i])
                {
                    if (pOneVoc->State == DJDialGlobals.VOICE_STATE.VOC_FREE)
                    {
                        Change_Voc_State(pOneVoc, DJDialGlobals.VOICE_STATE.VOC_WAIT_REMOVE);
                    }
                }
            }
            CheckRemoveReady(s8ModuleID);
        }

        private void listView_Main_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void Btn_PreForRemove_Click(object sender, EventArgs e)
        {
            Remove_OneDsp();
        }

        private void Btn_ReOpen_Click(object sender, EventArgs e)
        {
            ReOpen_AllDevice();
        }

    }
}