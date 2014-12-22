using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.Runtime.InteropServices;
using System.Threading;

using DJKeygoe;

namespace Demo
{
    public partial class DemoForm : Form
    {
        public DemoForm()
        {
            InitializeComponent();
            pDemo = this;
            InitSystem();

            fs = new FileStream("Exception Lof File .Log", FileMode.Create, FileAccess.Write); //创建异常文件记录
            sw = new StreamWriter(fs);
        }

        public static DJDemoGlobals globals = new DJDemoGlobals();
        public static DJAcsApiDef.EsrFunc g_ESRFuncPtr;
        public static DemoForm pDemo;
        public static FileStream fs;
        public static StreamWriter sw;

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
                
                if (globals.nNumOfListBoxItem % 10000 == 0)
                {
                    listBox_OptAndEvtInfo.Items.Clear();
                }

                globals.nNumOfListBoxItem++;
                strMsg = String.Format("{0,4} {1}", globals.nNumOfListBoxItem, strInfo);
                listBox_OptAndEvtInfo.Items.Add(strMsg);
            }
        }

        public unsafe void ShowEvtInfo(Acs_Evt_t* pAcsEvt)
        {
            string TmpStr;
            string TmpS;

            TmpStr = globals.GetEventTypeString(pAcsEvt->m_s32EventType);

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
                            pAcsEvt->m_DeviceID.m_s8ModuleID, pAcsEvt->m_DeviceID.m_s16ChannelID, GetString_IoDataType(pIoData->m_u16IoType), pIoData->m_u16IoDataLen);

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

        public unsafe void SBytesToSBytes(sbyte* Src, sbyte* Dest)
        {
            for (int i = 0; Dest[i] != '\0'; i++)
            {
                Src[i] = Dest[i];
            }
        }

        public unsafe void SBytesToChars(sbyte* bySrc, char[] chDst, int nLen)
        {
            int i = 0;
            for (i = 0; bySrc[i] != (sbyte)'\0' && i < nLen; ++i)
            {
                chDst[i] = (char)bySrc[i];
            }
            chDst[i] = '\0';
        }

        delegate void DrawCountCallBack(int nRow, int nColumn, string strMsg);
        public void DrawCount(int nRow, int nColumn, string strMsg) //到listview_count的nRow行nColumn列写字符串
        {
            if (this.listView_Count.InvokeRequired)
            {
                DrawCountCallBack d = new DrawCountCallBack(DrawCount);
                this.Invoke(d, new object[] { nRow, nColumn, strMsg });
            }
            else
            {
                listView_Count.Items[nRow].SubItems[nColumn].Text = strMsg;
            }

            strMsg = null;
        }

        delegate void DrawMainCallBack(int nRow, int nColumn, string strMsg);
        public void DrawMain(int nRow, int nColumn, string strMsg)
        {
            if (this.listView_Main.InvokeRequired)
            {
                DrawMainCallBack d = new DrawMainCallBack(DrawMain);
                this.Invoke(d, new object[] { nRow, nColumn, strMsg });
            }
            else
            {
                listView_Main.Items[nRow].SubItems[nColumn].Text = strMsg;
            }

            strMsg = null;
        }

        delegate void DrawPcmCallBack(int nRow, int nColumn, string strMsg);
        public void DrawPcm(int nRow, int nColumn, string strMsg)
        {
            if (this.listView_pcm.InvokeRequired)
            {
                DrawPcmCallBack d = new DrawPcmCallBack(DrawPcm);
                this.Invoke(d, new object[] { nRow, nColumn, strMsg });
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
                for (int i = listView_Main.Items.Count; i < globals.g_iTotalTrunk; i++)
                {
                    int iDispRow;

                    iDispRow = CalDispRow(i);
                    if (iDispRow < 0) continue;

                    ListViewItem listItem = new ListViewItem(iDispRow.ToString());
                    for (int j = 0; j < 8; j++)
                    {
                        listItem.SubItems.Add("");
                    }
                    listView_Main.Items.Add(listItem);
                }
            }
        }

        bool g_bTotalAdd = true;

        delegate void AddCountItemCallBack();
        public void AddCountItem()
        {
            if (this.listView_Count.InvokeRequired)
            {
                AddCountItemCallBack d = new AddCountItemCallBack(AddCountItem);
                this.Invoke(d, new object[] { });
            }
            else
            {
                if (g_bTotalAdd)
                {
                    ListViewItem ItemTotal = new ListViewItem("Total");
                    for (int j = 0; j < 7; j++)
                    {
                        ItemTotal.SubItems.Add("");
                    }
                    listView_Count.Items.Add(ItemTotal);

                    for (int i = 0; i < globals.g_iTotalModule; i++)
                    {
                        ListViewItem listItem = new ListViewItem(i.ToString());
                        for (int j = 0; j < 7; j++)
                        {
                            listItem.SubItems.Add("");
                        }
                        listView_Count.Items.Add(listItem);
                    }
                    g_bTotalAdd = false;
                }
                else
                {
                    for (int i = listView_Count.Items.Count-1; i < globals.g_iTotalModule; i++)
                    {
                        ListViewItem listItem = new ListViewItem(i.ToString());
                        for (int j = 0; j < 7; j++)
                        {
                            listItem.SubItems.Add("");
                        }
                        listView_Count.Items.Add(listItem);
                    }
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
                for (int i = listView_pcm.Items.Count; i < globals.g_iTotalPcm; i++)
                {
                    ListViewItem listItem = new ListViewItem(i.ToString());
                    for (int j = 0; j < 5; j++)
                    {
                        listItem.SubItems.Add("");
                    }
                    listView_pcm.Items.Add(listItem);
                }
            }
        }

        public unsafe void CharsToSBytes(char[] chSrc, sbyte* byDst, int size)
        {
            int i = 0;
            for (i = 0; i < size && chSrc[i] != '\0'; ++i)
            {
                byDst[i] = (sbyte)chSrc[i];
            }
            byDst[i] = (sbyte)'\0';
        }

        public int CalDispRow(int iSeqID)
        {
            int iRet;

            if (globals.cfg_iDispChnl == 30)
            {
                if ((iSeqID % 16) == 0)
                    return -1;

                iRet = (iSeqID / 32) * 30 + (iSeqID % 32);
                iRet--;
                if ((iSeqID % 32) > 16)
                    iRet--;
                return iRet;

            }

            if (globals.cfg_iDispChnl == 31)
            {
                if ((iSeqID % 32) == 0)
                    return -1;

                iRet = (iSeqID / 32) * 31 + (iSeqID % 32);
                iRet--;
                return iRet;
            }

            return iSeqID;
        }

        public void DrawCount_ErrFlag(sbyte s8ModID)
        {
            string strMsg;

            if (globals.AllDeviceRes[s8ModID].bErrFlag)
            {
                strMsg = "T";
            }
            else
            {
                strMsg = "";
            }
            DrawCount(globals.AllDeviceRes[s8ModID].iSeqID + 1, 6, strMsg);
        }

        public void DrawCount_RemoveState(sbyte s8ModID)
        {
            string strMsg;

            strMsg = "";
            switch ((DJDemoGlobals.REMOVE_STATE)globals.AllDeviceRes[s8ModID].RemoveState)
            {
                case DJDemoGlobals.REMOVE_STATE.DSP_REMOVE_STATE_NONE: strMsg = ""; break;
                case DJDemoGlobals.REMOVE_STATE.DSP_REMOVE_STATE_START: strMsg = "Start"; break;
                case DJDemoGlobals.REMOVE_STATE.DSP_REMOVE_STATE_READY: strMsg = "Ready"; break;
            }
            DrawCount(globals.AllDeviceRes[s8ModID].iSeqID + 1, 7, strMsg);
        }

        public void RefreshMapTable()
        {
            int i, j;
            int TrkCount, VocCount, PcmCount, ModuleCount;
            int iModSeqID;

            // Remember the AllDeviceRes's Interface,Voice,PCM channel
            ModuleCount = TrkCount = VocCount = PcmCount = 0;
            for (i = 0; i < DJDemoGlobals.MAX_DSP_MODULE_NUMBER_OF_XMS; i++)
            {
                if (globals.AllDeviceRes[i].lFlag == 1) //如果DSP可用
                {
                    // DSP Module
                    globals.AllDeviceRes[i].iSeqID = ModuleCount;
                    globals.MapTable_Module[ModuleCount] = (sbyte)i;
                    ModuleCount++;

                    // Voice Channel
                    for (j = 0; j < globals.AllDeviceRes[i].lVocNum; j++)
                    {
                        globals.AllDeviceRes[i].pVoice[j].iSeqID = VocCount;
                        globals.MapTable_Voice[VocCount].m_s8ModuleID = globals.AllDeviceRes[i].pVoice[j].deviceID.m_s8ModuleID;
                        globals.MapTable_Voice[VocCount].m_s16ChannelID = globals.AllDeviceRes[i].pVoice[j].deviceID.m_s16ChannelID;
                        VocCount++;
                    }

                    // PCM Channel
                    for (j = 0; j < globals.AllDeviceRes[i].lPcmNum; j++)
                    {
                        globals.AllDeviceRes[i].pPcm[j].iSeqID = PcmCount;
                        globals.MapTable_Pcm[PcmCount].m_s8ModuleID = globals.AllDeviceRes[i].pPcm[j].deviceID.m_s8ModuleID;
                        globals.MapTable_Pcm[PcmCount].m_s16ChannelID = globals.AllDeviceRes[i].pPcm[j].deviceID.m_s16ChannelID;
                        PcmCount++;
                    }

                    // Interface Channel
                    iModSeqID = 0;
                    for (j = 0; j < globals.AllDeviceRes[i].lTrunkNum; j++)
                    {
                        globals.AllDeviceRes[i].pTrunk[j].iSeqID = TrkCount;
                        globals.MapTable_Trunk[TrkCount].m_s8ModuleID = globals.AllDeviceRes[i].pTrunk[j].deviceID.m_s8ModuleID;
                        globals.MapTable_Trunk[TrkCount].m_s16ChannelID = globals.AllDeviceRes[i].pTrunk[j].deviceID.m_s16ChannelID;
                        TrkCount++;

                        if (globals.AllDeviceRes[i].pTrunk[j].deviceID.m_s16DeviceSub != (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_UNUSABLE)
                        {
                            // Available Channel
                            globals.AllDeviceRes[i].pTrunk[j].iModSeqID = iModSeqID;
                            iModSeqID++;
                        }
                    }
                }
            }

            globals.g_iTotalModule = ModuleCount;
            globals.g_iTotalTrunk = TrkCount;
            globals.g_iTotalVoice = VocCount;
            globals.g_iTotalPcm = PcmCount;

            AddMainItem();
            AddPcmItem();
            AddCountItem();

        }

        public string GetString_PcmType(int iPcmType)
        {
            switch ((XMS_E1_TYPE)iPcmType)
            {
                case XMS_E1_TYPE.XMS_E1_TYPE_NULL: return "Disable";
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
                case DEVICE_CALL_STATE.DEVICE_COMMON_STATE_START: return "S_START";
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
            switch ((DJDemoGlobals.TRUNK_STATE)iState)
            {
                case DJDemoGlobals.TRUNK_STATE.TRK_WAITOPEN: return "Wait Open";
                case DJDemoGlobals.TRUNK_STATE.TRK_FREE: return "Free";
                case DJDemoGlobals.TRUNK_STATE.TRK_WELCOME: return "Welcome to DonJin Keygo Bank Demo";
                case DJDemoGlobals.TRUNK_STATE.TRK_ACCOUNT: return "Please input your acount";
                case DJDemoGlobals.TRUNK_STATE.TRK_PASSWORD: return "Please input your password";
                case DJDemoGlobals.TRUNK_STATE.TRK_SELECT: return "Please select function";
                case DJDemoGlobals.TRUNK_STATE.TRK_RECORDFILE: return "Record";
                case DJDemoGlobals.TRUNK_STATE.TRK_PLAYRESULT: return "Play result";
                case DJDemoGlobals.TRUNK_STATE.TRK_PLAYRECORD: return "Play Back";
                case DJDemoGlobals.TRUNK_STATE.TRK_WAIT_ANSWERCALL: return "Wait offhook ok";
                case DJDemoGlobals.TRUNK_STATE.TRK_WAIT_LINKOK: return "Wait Link ok";
                case DJDemoGlobals.TRUNK_STATE.TRK_WAIT_REMOVE: return "DSP remove";
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
            switch ((XMS_INTERFACE_DEVSUB_TYPE)iSubDevType)
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

        public string GetString_IoDataType(int iDataType)
        {
            switch ((XMS_MEDIA_IO_TYPE)iDataType)
            {
                case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF: return "DTMF";
                case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_MR2F: return "MR2F";
                case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_GTD: return "GTG/GTD";
                case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_FSK: return "FSK";
                case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DPD: return "DPD";
                case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_PVD: return "PVD";
                case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_MSK: return "MSK";
                case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_VSD: return "VSD";
                case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_MSKREND: return "MSKREND";
                case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DRS: return "DRS";
            }

            return "UNKNOWN";
        }

        public unsafe void DrawMain_DTMF( DJDemoGlobals.TRUNK_STRUCT *pOneTrunk )
        {
            string strMsg;
            int iDispRow;

            iDispRow = CalDispRow(pOneTrunk->iSeqID);
            if (iDispRow < 0) return;

            strMsg = new string(pOneTrunk->DtmfBuf);
            DrawMain(iDispRow, 7, strMsg);

            strMsg = null;
        }

        public void DrawMain_LineState(int iSeqID, int iLineState)
        {
            string strMsg;
            int iDispRow;

            iDispRow = CalDispRow(iSeqID);
            if (iDispRow < 0) return;

            strMsg = GetString_LineState(iLineState);
            DrawMain(iDispRow, 3, strMsg);

            strMsg = null;
        }

        public void DrawMain_State(int iSeqID, int iState)
        {
            string strMsg;
            int iDispRow;

            iDispRow = CalDispRow(iSeqID);
            if (iDispRow < 0) return;

            strMsg = GetString_State(iState);
            DrawMain(iDispRow, 4, strMsg);

            strMsg = null;
        }

        public unsafe void DrawMain_CallInfo(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk)
        {
            string strCallee = new string(pOneTrunk->CalleeCode);
            string strCalled = new string(pOneTrunk->CallerCode);
            int iDispRow;

            iDispRow = CalDispRow(pOneTrunk->iSeqID);
            if (iDispRow < 0) return;

            DrawMain(iDispRow, 5, strCallee);
            DrawMain(iDispRow, 6, strCalled);

            strCallee = null;
            strCalled = null;
        }

        public void DrawCount_Pcm(sbyte s8ModID)
        {
            string strMsg;

            strMsg = String.Format("{0,3}/{1,3}", globals.AllDeviceRes[s8ModID].lPcmNum, globals.AllDeviceRes[s8ModID].lPcmOpened);
            DrawCount(globals.AllDeviceRes[s8ModID].iSeqID + 1, 2, strMsg);

            strMsg = String.Format("{0,3}/{1,3}", globals.g_iTotalPcm, globals.g_iTotalPcmOpened);
            DrawCount(0, 2, strMsg);

            strMsg = null;
        }

        public void DrawCount_Trunk(sbyte s8ModID)
        {
            string strMsg;

            strMsg = String.Format("{0,3}/{1,3}", globals.AllDeviceRes[s8ModID].lTrunkNum, globals.AllDeviceRes[s8ModID].lTrunkOpened);
            DrawCount(globals.AllDeviceRes[s8ModID].iSeqID + 1, 3, strMsg);

            strMsg = String.Format("{0,3}/{1,3}", globals.g_iTotalTrunk, globals.g_iTotalTrunkOpened);
            DrawCount(0, 3, strMsg);

            strMsg = null;
        }

        public void DrawCount_Voc(sbyte s8ModID)
        {
            string strMsg;

            strMsg = String.Format("{0,3}/{1,3}", globals.AllDeviceRes[s8ModID].lVocNum, globals.AllDeviceRes[s8ModID].lVocOpened);
            DrawCount(globals.AllDeviceRes[s8ModID].iSeqID + 1, 4, strMsg);

            strMsg = null;

            strMsg = String.Format("{0,3}", globals.AllDeviceRes[s8ModID].lVocFreeNum);
            DrawCount(globals.AllDeviceRes[s8ModID].iSeqID + 1, 5, strMsg);

            strMsg = null;

            strMsg = String.Format("{0,3}/{1,3}", globals.g_iTotalVoice, globals.g_iTotalVoiceOpened);
            DrawCount(0, 4, strMsg);

            strMsg = null;

            strMsg = String.Format("{0,3}", globals.g_iTotalVoiceFree);
            DrawCount(0, 5, strMsg);
        }

        public unsafe void DrawPcm_TypeAndAlarm(DJDemoGlobals.PCM_STRUCT* pOnePcm)
        {
            string strMsg;
            strMsg = GetString_PcmType(pOnePcm->u8E1Type);
            DrawPcm(pOnePcm->iSeqID, 1, strMsg);

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

        public unsafe void Change_Voc_State(DJDemoGlobals.VOICE_STRUCT* pOneVoice, DJDemoGlobals.VOICE_STATE NewState)
        {
            pOneVoice->State = NewState;

            // Check if ready to remove DSP hardware
            if ((globals.AllDeviceRes[pOneVoice->deviceID.m_s8ModuleID].RemoveState == DJDemoGlobals.REMOVE_STATE.DSP_REMOVE_STATE_START)
                && (NewState == DJDemoGlobals.VOICE_STATE.VOC_FREE))
            {
                pOneVoice->State =DJDemoGlobals.VOICE_STATE. VOC_WAIT_REMOVE;

                CheckRemoveReady(pOneVoice->deviceID.m_s8ModuleID);
            }
        }

        public unsafe void ReDrawAll()
        {
            int iDispRow;

            for (int i = 0; i < globals.g_iTotalTrunk; i++)
            {
                iDispRow = CalDispRow(i);
                if (iDispRow < 0) continue;

                string strMsg = String.Format("{0},{1}", globals.MapTable_Trunk[i].m_s8ModuleID, globals.MapTable_Trunk[i].m_s16ChannelID);
                DrawMain(iDispRow, 1, strMsg);
                fixed (DJDemoGlobals.TRUNK_STRUCT* pOneTrunk = &globals.AllDeviceRes[globals.MapTable_Trunk[i].m_s8ModuleID].pTrunk[globals.MapTable_Trunk[i].m_s16ChannelID])
                {
                    strMsg = null;

                    strMsg = String.Format("{0}", GetSubDevTypeString(pOneTrunk->deviceID.m_s16DeviceSub));
                    DrawMain(iDispRow, 2, strMsg);
                    DrawMain_LineState(pOneTrunk->iSeqID, pOneTrunk->iLineState);
                    DrawMain_State(pOneTrunk->iSeqID, (int)pOneTrunk->State);
                    DrawMain_CallInfo(pOneTrunk);
                    DrawMain_DTMF(pOneTrunk);
                }

                strMsg = null;
            }

            for (int i = 0; i < globals.g_iTotalPcm; i++)
            {
                fixed (DJDemoGlobals.PCM_STRUCT* pOnePcm = &globals.AllDeviceRes[globals.MapTable_Pcm[i].m_s8ModuleID].pPcm[globals.MapTable_Pcm[i].m_s16ChannelID])
                {
                    DrawPcm_TypeAndAlarm(pOnePcm);
                }
            }

            for (int i = 0; i < globals.g_iTotalModule; i++)
            {
                string strMsg;
                strMsg = String.Format("{0}", globals.MapTable_Module[i]);
                DrawCount(i + 1, 1, strMsg);
                DrawCount_Pcm(globals.MapTable_Module[i]);
                DrawCount_Trunk(globals.MapTable_Module[i]);
                DrawCount_Voc(globals.MapTable_Module[i]);
                DrawCount_ErrFlag(globals.MapTable_Module[i]);
                DrawCount_RemoveState(globals.MapTable_Module[i]);

                strMsg = null;
            }
        }


        private unsafe void InitSystem() //初始化
        {
            string strMsg;

            globals.ReadFromConfig();
            InitTextBox();


            if (0 != CAS_Common_Code.CAS_Common_Cfg_ReadCfg(ref globals.g_Param_CAS))
            {
                MessageBox.Show("CAS_Common_Cfg_ReadCfg \"C:\\DJKeygoe\\Samples\\CAS_Common_Code\\XMS_CAS_Cfg.INI\" Error!", "Init System");
            }

            if (0 != Analog_Common_Code.Analog_Common_Cfg_ReadCfg(ref globals.g_Param_Analog))
            {
                MessageBox.Show("Analog_Common_Cfg_ReadCfg \"C:\\DJKeygoe\\Samples\\Analog_Common_Code\\XMS_Analog_Cfg.INI\\ Error", "Init System");
            }

            int iResult = 0;

            fixed (UInt32* pAcsHandle = &globals.g_acsHandle)
            {
                fixed (ServerID_t* ServerID = &globals.cfg_ServerID)
                {
                    iResult = DJAcsApiDef.XMS_acsOpenStream(pAcsHandle, ServerID, 12, 64, 64, globals.cfg_s32DebugOn, null);

                    strMsg = String.Format("{0} ({1},{2})", "XMS_acsOpenStream", textBox_ServerIP.Text, textBox_Port.Text);

                    if (iResult == (int)ERROR_CODE.ACSPOSITIVE_ACK) //OpenStream Success
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
            iResult = DJAcsApiDef.XMS_acsSetESR(globals.g_acsHandle, g_ESRFuncPtr, 0, 1);

            if (iResult == (int)ERROR_CODE.ACSPOSITIVE_ACK)
            {
                strMsg += "XMS_acsSetESR() OK!";
            }
            else
            {
                strMsg += "XMS_acsSetESR() FAIL!";
            }
            ListBox_AddItem(strMsg);

            iResult = DJAcsApiDef.XMS_acsGetDeviceList(globals.g_acsHandle, null);

            strMsg = null;
            if (iResult == (int)ERROR_CODE.ACSPOSITIVE_ACK)
            {
                strMsg += "XMS_acsGetDeviceList() OK!";
            }
            else
            {
                strMsg += "XMS_acsGetDeviceList() FAIL!";
            }
            ListBox_AddItem(strMsg);

            strMsg = null;
        }

        public unsafe void* memset(void* mem, byte value, int size)
        {
            byte* pByteMem = (byte*)mem;
            for (int i = 0; i < size; ++i)
            {
                pByteMem[i] = value;
            }

            return mem;
        }

        #region Keygoe Work Codes
        public unsafe void My_DualLink(DeviceID_t* pDev1, DeviceID_t* pDev2)
        {
            DJAcsApiDef.XMS_ctsLinkDevice(globals.g_acsHandle, pDev1, pDev2, null);
            DJAcsApiDef.XMS_ctsLinkDevice(globals.g_acsHandle, pDev2, pDev1, null);
        }

        public unsafe void My_DualUnlink(DeviceID_t* pDev1, DeviceID_t* pDev2)
        {
            DJAcsApiDef.XMS_ctsUnlinkDevice(globals.g_acsHandle, pDev1, pDev2, null);
            DJAcsApiDef.XMS_ctsUnlinkDevice(globals.g_acsHandle, pDev2, pDev1, null);
        }

        public unsafe int FreeOneFreeVoice(DeviceID_t* pFreeVocDeviceID)
        {
            if (globals.AllDeviceRes[pFreeVocDeviceID->m_s8ModuleID].lFlag == 1)
            {
                fixed(DJDemoGlobals.VOICE_STRUCT* pOneVoc = &globals.AllDeviceRes[pFreeVocDeviceID->m_s8ModuleID].pVoice[pFreeVocDeviceID->m_s16ChannelID])
                {
                    Change_Voc_State ( pOneVoc, DJDemoGlobals.VOICE_STATE.VOC_FREE);
                    ++globals.AllDeviceRes[pFreeVocDeviceID->m_s8ModuleID].lVocFreeNum;
                    ++globals.g_iTotalVoiceFree;
                    DrawCount_Voc ( pFreeVocDeviceID->m_s8ModuleID );

                    return 0;		// OK
                }
            }

            return -1;			// invalid VocDeviceID
        }

        public unsafe int SearchOneFreeVoice(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk, DeviceID_t* pFreeVocDeviceID)
        {
            SByte			s8ModID = pOneTrunk->deviceID.m_s8ModuleID;

            if (globals.cfg_iVoiceRule == 0)			// Fix relationship between Trunk & Voice
            {
                Int16 s16ChID = (short)pOneTrunk->iModSeqID;
                if (s16ChID < globals.AllDeviceRes[s8ModID].lVocNum)
                {
                    fixed (DJDemoGlobals.VOICE_STRUCT* pOneVoice = &globals.AllDeviceRes[s8ModID].pVoice[s16ChID])
                    {
                        if (pOneVoice->State != DJDemoGlobals.VOICE_STATE.VOC_WAITOPEN)
                        {
                            *pFreeVocDeviceID = pOneVoice->deviceID;

                            // use this voice device 
                            Change_Voc_State(pOneVoice, DJDemoGlobals.VOICE_STATE.VOC_USED);
                            --globals.g_iTotalVoiceFree;
                            --globals.AllDeviceRes[s8ModID].lVocFreeNum;
                            DrawCount_Voc(s8ModID);

                            return s16ChID;
                        }
                    }
                }

                return -1;
            }

            SByte s8SearchModID;
            long lNowMostFreeNum;
            if (globals.cfg_iVoiceRule == 1)			// Search in Same Module
            {
                s8SearchModID = s8ModID;
            }
            else		// Search in Most free resource module
            {
                s8SearchModID = -1;
                lNowMostFreeNum = -1;
                for (int i = 0; i < globals.g_iTotalModule; ++i)
                {
                    if (globals.AllDeviceRes[globals.MapTable_Module[i]].lVocFreeNum > lNowMostFreeNum)
                    {
                        s8SearchModID = globals.MapTable_Module[i];
                        lNowMostFreeNum = globals.AllDeviceRes[globals.MapTable_Module[i]].lVocFreeNum;
                    }
                }
            }

            for (int i = 0; i < globals.AllDeviceRes[s8SearchModID].lVocNum; ++i)
            {
                fixed (DJDemoGlobals.VOICE_STRUCT* pOneVoice = &globals.AllDeviceRes[s8SearchModID].pVoice[i])
                {
                    if (pOneVoice->State == DJDemoGlobals.VOICE_STATE.VOC_FREE)
                    {
                        *pFreeVocDeviceID = pOneVoice->deviceID;

                        // user this voice device 
                        Change_Voc_State(pOneVoice, DJDemoGlobals.VOICE_STATE.VOC_USED);
                        --globals.AllDeviceRes[s8ModID].lVocFreeNum;
                        --globals.g_iTotalVoiceFree;
                        DrawCount_Voc(s8SearchModID);
                        return i;
                    }
                }
            }

            return -1;
        }

        public unsafe void SetGtD_AnalogTrunk(DeviceID_t* pDevId)
        {
	        //========Set GTG Begin========
	        CmdParamData_Voice_t cmdVoc;
            memset(&cmdVoc, 0, sizeof(CmdParamData_Voice_t));
	        cmdVoc.m_u8GtdCtrlValid = 1 ;						//Enable GTD
	        cmdVoc.m_VocGtdControl.m_u8ChannelEnable = 1;		//Enable Gtd channel
	        cmdVoc.m_VocGtdControl.m_u8DTMFEnable = 1;			// Detect DTMF
	        cmdVoc.m_VocGtdControl.m_u8GTDEnable = 1;			// Detect GTD 
	        cmdVoc.m_VocGtdControl.m_u8FSKEnable = 1;			// Detect FSK for receive CallerID

	        cmdVoc.m_VocGtdControl.m_u8EXTEnable = 0x2;		// Enable PVD Detect

            cmdVoc.m_VocGtdControl.m_u8GTDID[0] = (byte)'G';
            cmdVoc.m_VocGtdControl.m_u8GTDID[1] = (byte)'H';
            cmdVoc.m_VocGtdControl.m_u8GTDID[2] = (byte)'I';
            cmdVoc.m_VocGtdControl.m_u8GTDID[3] = (byte)'J';
            cmdVoc.m_VocGtdControl.m_u8GTDID[4] = (byte)'K';

	        ushort u16ParamType = (ushort)XMS_VOC_PARAM_TYPE.VOC_PARAM_UNIPARAM;
            ushort u16ParamSize = (ushort)sizeof(CmdParamData_Voice_t);
	        void* p = (void*) &cmdVoc;

            int nRet = DJAcsApiDef.XMS_ctsSetParam(globals.g_acsHandle, pDevId, u16ParamType, u16ParamSize, (void *)&cmdVoc);

            string strMsg;

            strMsg = String.Format("Set GTD ret = {0}", nRet);
            //listBox_OptAndEvtInfo.Items.Add(strMsg);
            ListBox_AddItem(strMsg);

            strMsg = null;
	        //========Set GTG End  ========
        }

        // Search Free Voice for get CallerID(FSK)
        public unsafe void PrepareForCallerID(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk)
        {
            if (pOneTrunk->deviceID.m_s16DeviceSub != (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
                return;

            DeviceID_t FreeVocDeviceID;

            if (SearchOneFreeVoice(pOneTrunk, &FreeVocDeviceID) >= 0)
            {
                pOneTrunk->VocDevID = FreeVocDeviceID;

                fixed (DJDemoGlobals.VOICE_STRUCT* pOneVoc = &globals.AllDeviceRes[FreeVocDeviceID.m_s8ModuleID].pVoice[FreeVocDeviceID.m_s16ChannelID])
                {
                    pOneVoc->UsedDevID = pOneTrunk->deviceID;
                }

                DrawMain_VocInfo(pOneTrunk);
                My_DualLink(&pOneTrunk->VocDevID, &pOneTrunk->deviceID);
                SetGtD_AnalogTrunk(&FreeVocDeviceID);
            }
        }

        public unsafe void ResetTrunk(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk, Acs_Evt_t* pAcsEvt)
        {
            StopPlayFile(&pOneTrunk->VocDevID);

            // free the used Voice Resource
            if (pOneTrunk->VocDevID.m_s16DeviceMain != 0)
            {
                My_DualUnlink(&pOneTrunk->VocDevID, &pOneTrunk->deviceID);

                FreeOneFreeVoice(&pOneTrunk->VocDevID);

                fixed(DeviceID_t *pUsedDev = 
                    &globals.AllDeviceRes[pOneTrunk->VocDevID.m_s8ModuleID].pVoice[pOneTrunk->VocDevID.m_s16ChannelID].UsedDevID)
                {
                    memset(pUsedDev, 0, sizeof(DeviceID_t));		// 0: didn't alloc Device
                }
                memset(&pOneTrunk->VocDevID, 0, sizeof(DeviceID_t));		// 0: didn't alloc Device
            }

            InitTrunkChannel(pOneTrunk);

            // Search Free Voice for get CallerID(FSK)
            // if you needn't CallerID, ignore next line
            PrepareForCallerID(pOneTrunk);
        }

        public unsafe sbyte *My_GetGtdCode(Acs_Evt_t* pAcsEvt)
        {
            Acs_IO_Data* pIOData = null;
            sbyte* p = null;

            if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_RECVIODATA)	/*IO Data Event*/
            {
                pIOData = (Acs_IO_Data*)((byte*)pAcsEvt + sizeof(Acs_Evt_t));

                if ((pIOData->m_u16IoType == (ushort)XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_GTG)
                    && (pIOData->m_u16IoDataLen > 0))
                {
                    char[] szMsg = new char[2 * (pIOData->m_u16IoDataLen + 1)];
                    szMsg.Initialize();

                    p = (sbyte*)((sbyte*)pIOData + sizeof(Acs_IO_Data));
                    SBytesToChars(p, szMsg, pIOData->m_u16IoDataLen);

                    string strMsg = new string(szMsg);
                    ListBox_AddItem(strMsg);

                    szMsg = null;
                    strMsg = null;

                    return p;
                }
            }

            return null;	// not a good GTD
        }

        public unsafe byte* My_GetFskCode(Acs_Evt_t* pAcsEvt)
        {
            Acs_IO_Data* pIOData = null;
            byte* p = null;

            //if (pAcsEvt->m_s32EventType == (int)DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_RECVIODATA)	/*IO Data Evemt*/
            if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_RECVIODATA)	//modify by lmy 20120321
            {
                pIOData = (Acs_IO_Data*)((byte*)pAcsEvt + sizeof(Acs_Evt_t));

                if ((pIOData->m_u16IoType == (ushort)XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_FSK)
                    && (pIOData->m_u16IoDataLen > 0))
                {
                    char[] szMsg = new char[2 * (pIOData->m_u16IoDataLen + 1)];
                    szMsg.Initialize();

                    p = (byte*)((byte*)pIOData + sizeof(Acs_IO_Data));
                    SBytesToChars((sbyte*)p, szMsg, pIOData->m_u16IoDataLen);

                    string strMsg = new string(szMsg);
                    ListBox_AddItem(strMsg);

                    
                    szMsg = null;
                    strMsg = null;

                    return p;
                }
            }

            return null;	// not a good FSK
        }

        public unsafe sbyte My_GetDtmfCode(Acs_Evt_t* pAcsEvt)
        {
            Acs_IO_Data* pIOData = null;
            sbyte* p = null;

            /*fixed (DJDemoGlobals.TRUNK_STRUCT* pOneTrunk = &globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pTrunk[pAcsEvt->m_DeviceID.m_s16ChannelID])
            {
          
            }*/
            if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_RECVIODATA)	/*IO Data Event*/
            {
                pIOData = (Acs_IO_Data*)((byte*)pAcsEvt + sizeof(Acs_Evt_t));
                
                if ((pIOData->m_u16IoType == (ushort)XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF)
                    && (pIOData->m_u16IoDataLen > 0))
                {
                    char[] DtmfArr = new char[2 * (pIOData->m_u16IoDataLen + 1)];
                    DtmfArr.Initialize();

                    p = (sbyte*)((byte*)pIOData + sizeof(Acs_IO_Data));
                    if (p[1] != 0)
                    {
                    }
                    SBytesToChars((sbyte *)p, DtmfArr, pIOData->m_u16IoDataLen);
                    /*
                     * DtmfArr[0] = (char)p[0]; //DTMF每次只能接受一个字节
                     */
                    string strMsg = new string(DtmfArr);
                    ListBox_AddItem(strMsg);

                    DtmfArr = null;
                    strMsg = null;

                    return p[0];
                }
            }

            return -1;	// not a good DTMF
        }

        public unsafe void My_InitDtmfBuf(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk)
        {
            pOneTrunk->DtmfCount = 0;
            pOneTrunk->DtmfBuf[0] = 0;
        }

        public unsafe void My_AddDtmfBuf(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk, sbyte TmpDtmf)
        {
            if (pOneTrunk->DtmfCount < (32 - 1))
            {
                pOneTrunk->DtmfBuf[pOneTrunk->DtmfCount] = TmpDtmf;
                pOneTrunk->DtmfBuf[pOneTrunk->DtmfCount + 1] = 0;
                ++pOneTrunk->DtmfCount;
            }
        }

        public unsafe int strlen(sbyte* psbyStr)
        {
            int iLen = 0;
            for (iLen = 0; psbyStr[iLen] != 0; ++iLen)
            {
            }

            return iLen;
        }

        public unsafe void sprintf(char* pDst, sbyte* pSrc)
        {
            int i = 0;
            for (i = 0; pSrc[i] != 0; ++i)
            {
                pDst[i] = (char)pSrc[i];
            }
            pDst[i] = '\0';
        }

        public unsafe void strcpy(sbyte* pDst, string strSrc)
        {
            for (int i = 0; i < strSrc.Length; ++i)
            {
                pDst[i] = (sbyte)strSrc[i];
            }
            pDst[strSrc.Length] = 0;
        }

        // multiple format
        public unsafe void HandleMultiple(sbyte* IDStr)
        {
            sbyte* p = IDStr;
            {
                sbyte[] TmpIDStr = new sbyte[80];
                TmpIDStr.Initialize();

                int i = 0, j = 0;

                while(p[j] != 0)
                {
                    if ( (p[j] == 1) || (p[j] == 2) || (p[j] == 4) || (p[j] == 7) || (p[j] == 8) )
                    {
                        j += 2;
                    }
                    else
                    {
                        TmpIDStr[i] = p[j];
                        i++;
                        j++;
                    }
                }

                int count;
                for (count = 0; count < i; count++)
                {
                    IDStr[count] = TmpIDStr[count];
                }
                IDStr[count] = 0;

                TmpIDStr = null;
            }
        }
        // end of multiple

        public unsafe int ConvertRawFskToCallerID(byte* RawFSKStr, int iFSKDataLen, sbyte* IDStr, int IDStrBufLen)
        {
            int count;
            int i, j;
            int pos, len;
            byte ChkSum;
        	
	        if ( null == RawFSKStr )
		        return -1;
        	
	        RawFSKStr[iFSKDataLen] = 0;
        	
	        count = iFSKDataLen;

            for (int k = 0; k < IDStrBufLen; k++)
            {
                IDStr[k] = 0;
            }
        	
	        if ( count == 0 )
	        {
		        return -1;  // not a good Caller ID
	        }
        	
	        // find the Format
	        for ( i = 0; i < count; i ++ ) 
	        {
		        if ( RawFSKStr[i] == 0x04 )  // single format
		        {
			        break;
		        }
        		
		        if ( RawFSKStr[i] == 0x80 ) {  // multiple format
			        break;
		        }
	        }
        	
	        if ( (i == count) || (i==count-1) )
	        {
		        return -1;  // not a good Caller ID
	        }
        	
	        // start fetch the Caller ID
	        pos = i;
	        len = RawFSKStr[pos+1];
        	
	        if ( len > IDStrBufLen )
		        len = IDStrBufLen;
        	
	        // "count-pos-2"    is the length of now received
	        for ( i = pos+2,j = 0; (i<(count-1)) && (j<len); i ++,j++ )
	        {
		        IDStr[j] = (sbyte)(RawFSKStr[i] & 0x7F);
		        if ( j == IDStrBufLen - 1 )    // it will be overflow
			        break;
	        }
	        IDStr[j] = 0;
        	
	        if ( (count-pos-3) < len  )
	        {
		        return -1;  // not a good Caller ID
	        }
        	
	        ChkSum = 0;
	        for ( i = pos; i < pos+len+3; i ++ )
		        ChkSum += RawFSKStr[i];
        	
	        // multiple format
	        if ( RawFSKStr[pos] == 0x80 ) 
	        {
		        HandleMultiple ( IDStr );
	        }
	        // end of multiple
        	
	        if ( ChkSum == 0 )
		        return 0;  // OK
	        else
		        return -1;  // Fail
        }

/*        public unsafe int ConvertRawFskToCallerID(byte* RawFSKStr, sbyte* IDStr, int IDStrBufLen)
        {
	        int			count;
	        int			i,j;
	        int			pos,len;
	        byte	        ChkSum;

            count = strlen((sbyte *)RawFSKStr);
            IDStr[0] = 0;

	        if ( count == 0 )
	        {
		        return -1;		// not a good Caller ID
	        }

	        // find the Format
            for (i = 0; i < count; ++i)
            {
                if (RawFSKStr[i] == 0x04)		// single format
                {
                    break;
                }

                if ((byte)RawFSKStr[i] == 0x80)
                {		// multiple format
                    break;
                }
            }

            if ((i == count) || (i == count - 1))
            {
                return -1;		// not a good Caller ID
            }

	        // start fetch the Caller ID
	        pos = i;
	        len = RawFSKStr[pos+1];

	        // "count-pos-2"    is the length of now received
            for (i = pos + 2, j = 0; (i < (count - 1)) && (j < len); i++, j++)
            {
                IDStr[j] = (sbyte)(RawFSKStr[i] & 0x7F);
                if (j == IDStrBufLen - 1)				// it will be overflow
                    break;
            }
	        IDStr[j] = 0;

            if ((count - pos - 3) < len)
            {
                return -1;		// not a good Caller ID
            }

	        ChkSum = 0;
            for (i = pos; i < pos + len + 3; i++)
            {
                ChkSum += RawFSKStr[i];
            }

        // multiple format
            if (RawFSKStr[pos] == 0x80)
            {
                HandleMultiple(IDStr);
            }
        // end of multiple

            if (ChkSum == 0)
            {
                return 0;		// OK
            }
            else
            {
                return -1;		// Fail
            }
        }*/

        public unsafe void SpecialForCas(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk, Acs_Evt_t* pAcsEvt)
        {
            if ((XMS_INTERFACE_DEVSUB_TYPE)pOneTrunk->deviceID.m_s16DeviceSub != XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_CAS)
            {
                return;
            }

            if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CAS_MFC_START)	/* 开始接收MFC，需要一个Voc设备*/
            {
                DeviceID_t FreeVocDeviceID;

                if (SearchOneFreeVoice(pOneTrunk, &FreeVocDeviceID) >= 0)
                {
                    My_DualLink(&FreeVocDeviceID, &pOneTrunk->deviceID);

                    pOneTrunk->VocDevID = FreeVocDeviceID;
                    globals.AllDeviceRes[FreeVocDeviceID.m_s8ModuleID].pVoice[FreeVocDeviceID.m_s16ChannelID].UsedDevID = pOneTrunk->deviceID;
                    DrawMain_VocInfo(pOneTrunk);

                    globals.g_Param_CAS.m_VocDevID = FreeVocDeviceID;

                    int iLen = sizeof(CmdParamData_CAS_t);
                    fixed (CmdParamData_CAS_t* pParamCasData = &globals.g_Param_CAS)
                    {
                        DJAcsApiDef.XMS_ctsSetParam(globals.g_acsHandle, &pOneTrunk->deviceID, (ushort)XMS_CAS_PARAM_TYPE.CAS_PARAM_UNIPARAM,
                                (ushort)iLen, pParamCasData); // CAS_PARAM_UNIPARAM = 0
                    }
                }
            }


            if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_CAS_MFC_END)	// 接收MFC完毕，释放Voc设备
            {
                My_DualUnlink(&pOneTrunk->VocDevID, &pOneTrunk->deviceID);

                FreeOneFreeVoice(&pOneTrunk->VocDevID);

                fixed(DeviceID_t *pDev = &globals.AllDeviceRes[pOneTrunk->VocDevID.m_s8ModuleID].pVoice[pOneTrunk->VocDevID.m_s16ChannelID].UsedDevID)
                {
                    memset(pDev, 0, sizeof(DeviceID_t));
                }
                memset(&pOneTrunk->VocDevID, 0, sizeof(DeviceID_t));
                DrawMain_VocInfo(pOneTrunk);
            }
        }

        public unsafe int PlayFile(DeviceID_t* pVocDevID, string FileName, byte u8PlayTag, bool bIsQueue)
        {
            PlayProperty_t playProperty;

            memset(&playProperty, 0, sizeof(PlayProperty_t));

            if (bIsQueue)
                playProperty.m_u16PlayType = (ushort)XMS_PLAY_TYPE.XMS_PLAY_TYPE_FILE_QUEUE;
            else
                playProperty.m_u16PlayType = (ushort)XMS_PLAY_TYPE.XMS_PLAY_TYPE_FILE;

            playProperty.m_u8TaskID = u8PlayTag;

            strcpy(playProperty.m_s8PlayContent, FileName);

            return DJAcsApiDef.XMS_ctsPlay(globals.g_acsHandle, pVocDevID, &playProperty, null);
        }

        public unsafe int PlayIndex(DeviceID_t* pVocDevID, ushort u16Index, byte u8PlayTag, bool bIsQueue)
        {
            PlayProperty_t playProperty;

            memset(&playProperty, 0, sizeof(PlayProperty_t));

            if (bIsQueue)
                playProperty.m_u16PlayType = (ushort)XMS_PLAY_TYPE.XMS_PLAY_TYPE_INDEX_QUEUE;
            else
                playProperty.m_u16PlayType = (ushort)XMS_PLAY_TYPE.XMS_PLAY_TYPE_INDEX;

            playProperty.m_u8TaskID = u8PlayTag;

            playProperty.m_u16PlayIndex = u16Index;

            return DJAcsApiDef.XMS_ctsPlay(globals.g_acsHandle, pVocDevID, &playProperty, null);
        }

        public unsafe int StopPlayFile(DeviceID_t* pVocDevID)
        {
            ControlPlay_t controlPlay;
            controlPlay.m_u16ControlType = (ushort)XMS_CTRL_PLAY_TYPE.XMS_STOP_PLAY;

            return DJAcsApiDef.XMS_ctsControlPlay(globals.g_acsHandle, pVocDevID, &controlPlay, null);
        }

        public unsafe bool CheckPlayEnd(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk, Acs_Evt_t* pAcsEvt)
        {
            Acs_MediaProc_Data* pMediaData = null;

            if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_PLAY)
            {
                pMediaData = (Acs_MediaProc_Data*)((byte*)pAcsEvt + sizeof(Acs_Evt_t));
                if (pMediaData->m_u8TaskID == pOneTrunk->u8PlayTag)
                    return true;
            }

            return false;
        }

        public unsafe void SetGTD_ToneParam(DeviceID_t* pDevice)
        {
            int r;
            ushort u16ParamType, u16ParamSize;
            CmdParamData_GtdFreq_t TmpGtdFreq;
            CmdParamData_GtdProtoType_t TmpGtdProto;

            int pDevValue = (int)pDevice; //把指针强转为整数
            int pFreq = (int)&TmpGtdFreq;
            int pProtoType = (int)&TmpGtdProto;

            // ---------- set Freq ----------
            u16ParamType = (ushort)XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDFREQ;
            u16ParamSize = (ushort)sizeof(CmdParamData_GtdFreq_t);

            // freq0
            TmpGtdFreq.m_u16Freq_Index = 0;
            TmpGtdFreq.m_u16Freq_Coef = globals.g_Param_Analog.m_u16Freq0;

            r = DJAcsApiDef.XMS_ctsSetParam(globals.g_acsHandle, pDevice, u16ParamType, u16ParamSize, &TmpGtdFreq);

            // freq1
            TmpGtdFreq.m_u16Freq_Index = 1;
            TmpGtdFreq.m_u16Freq_Coef = globals.g_Param_Analog.m_u16Freq1;
            r = DJAcsApiDef.XMS_ctsSetParam(globals.g_acsHandle, pDevice, u16ParamType, u16ParamSize, &TmpGtdFreq);

            // ---------- set DialTone ----------
            u16ParamType = (ushort)XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDTONE;
            u16ParamSize = (ushort)sizeof(CmdParamData_GtdProtoType_t);

            memset((byte*)&TmpGtdProto, 0, sizeof(CmdParamData_GtdProtoType_t));
            TmpGtdProto.m_u16GtdID = 48;		// DialTone, we use GTD's ID 48
            TmpGtdProto.m_u16Freq_Mask = globals.g_Param_Analog.m_u16DialTone_FreqIndexMask;
            TmpGtdProto.m_u16Envelope_Mode = 0;
            TmpGtdProto.m_u16Repeat_Count = 1;
            TmpGtdProto.m_u16Min_On_Time1 = (ushort)(globals.g_Param_Analog.m_u16DialTone_On_Time / 15);		// the unit is 15 ms

            r = DJAcsApiDef.XMS_ctsSetParam(globals.g_acsHandle, pDevice, u16ParamType, u16ParamSize, &TmpGtdProto);

            // ---------- set RingBack Tone ----------
            u16ParamType = (ushort)XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDTONE;
            u16ParamSize = (ushort)sizeof(CmdParamData_GtdProtoType_t);

            memset((byte*)&TmpGtdProto, 0, sizeof(CmdParamData_GtdProtoType_t));
            TmpGtdProto.m_u16GtdID = 49;		// DialTone, we use GTD's ID 49
            TmpGtdProto.m_u16Freq_Mask = globals.g_Param_Analog.m_u16RingBackTone_FreqIndexMask;
            TmpGtdProto.m_u16Envelope_Mode = 1;
            TmpGtdProto.m_u16Repeat_Count = 1;
            TmpGtdProto.m_u16Min_On_Time1 = (ushort)((globals.g_Param_Analog.m_u16RingBackTone_On_Time *
                (100 - globals.g_Param_Analog.m_u16RingBackTone_TimeDeviation) / 100) / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_On_Time1 = (ushort)((globals.g_Param_Analog.m_u16RingBackTone_On_Time *
                (100 + globals.g_Param_Analog.m_u16RingBackTone_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Min_Off_Time1 = (ushort)((globals.g_Param_Analog.m_u16RingBackTone_Off_Time *
                (100 - globals.g_Param_Analog.m_u16RingBackTone_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_Off_Time1 = (ushort)((globals.g_Param_Analog.m_u16RingBackTone_Off_Time *
                (100 + globals.g_Param_Analog.m_u16RingBackTone_TimeDeviation)) / 100 / 15);		// the unit is 15 ms

            r = DJAcsApiDef.XMS_ctsSetParam(globals.g_acsHandle, pDevice, u16ParamType, u16ParamSize, &TmpGtdProto);

            // ---------- set Busy Tone0 ----------
            u16ParamType = (ushort)XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDTONE;
            u16ParamSize = (ushort)sizeof(CmdParamData_GtdProtoType_t);

            memset((byte*)&TmpGtdProto, 0, sizeof(CmdParamData_GtdProtoType_t));
            TmpGtdProto.m_u16GtdID = 50;		// BusyTone0, we use GTD's ID 50
            TmpGtdProto.m_u16Freq_Mask = globals.g_Param_Analog.m_u16BusyTone0_FreqIndexMask;
            TmpGtdProto.m_u16Envelope_Mode = 1;
            TmpGtdProto.m_u16Repeat_Count = 1;
            TmpGtdProto.m_u16Min_On_Time1 = (ushort)((globals.g_Param_Analog.m_u16BusyTone0_On_Time *
                (100 - globals.g_Param_Analog.m_u16BusyTone0_TimeDeviation) / 100) / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_On_Time1 = (ushort)((globals.g_Param_Analog.m_u16BusyTone0_On_Time *
                (100 + globals.g_Param_Analog.m_u16BusyTone0_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Min_Off_Time1 = (ushort)((globals.g_Param_Analog.m_u16BusyTone0_Off_Time *
                (100 - globals.g_Param_Analog.m_u16BusyTone0_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_Off_Time1 = (ushort)((globals.g_Param_Analog.m_u16BusyTone0_Off_Time *
                (100 + globals.g_Param_Analog.m_u16BusyTone0_TimeDeviation)) / 100 / 15);		// the unit is 15 ms

            r = DJAcsApiDef.XMS_ctsSetParam(globals.g_acsHandle, pDevice, u16ParamType, u16ParamSize, &TmpGtdProto);

            // ---------- set Busy Tone1 ----------
            u16ParamType = (ushort)XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDTONE;
            u16ParamSize = (ushort)sizeof(CmdParamData_GtdProtoType_t);

            memset((byte*)&TmpGtdProto, 0, sizeof(CmdParamData_GtdProtoType_t));
            TmpGtdProto.m_u16GtdID = 51;		// BusyTone1, we use GTD's ID 51
            TmpGtdProto.m_u16Freq_Mask = globals.g_Param_Analog.m_u16BusyTone1_FreqIndexMask;
            TmpGtdProto.m_u16Envelope_Mode = 1;
            TmpGtdProto.m_u16Repeat_Count = 1;
            TmpGtdProto.m_u16Min_On_Time1 = (ushort)((globals.g_Param_Analog.m_u16BusyTone1_On_Time *
                (100 - globals.g_Param_Analog.m_u16BusyTone1_TimeDeviation) / 100) / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_On_Time1 = (ushort)((globals.g_Param_Analog.m_u16BusyTone1_On_Time *
                (100 + globals.g_Param_Analog.m_u16BusyTone1_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Min_Off_Time1 = (ushort)((globals.g_Param_Analog.m_u16BusyTone1_Off_Time *
                (100 - globals.g_Param_Analog.m_u16BusyTone1_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_Off_Time1 = (ushort)((globals.g_Param_Analog.m_u16BusyTone1_Off_Time *
                (100 + globals.g_Param_Analog.m_u16BusyTone1_TimeDeviation)) / 100 / 15);		// the unit is 15 ms

            r = DJAcsApiDef.XMS_ctsSetParam(globals.g_acsHandle, pDevice, u16ParamType, u16ParamSize, &TmpGtdProto);

            // ---------- set Busy Tone2 ----------
            u16ParamType = (ushort)XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDTONE;
            u16ParamSize = (ushort)sizeof(CmdParamData_GtdProtoType_t);

            memset((byte*)&TmpGtdProto, 0, sizeof(CmdParamData_GtdProtoType_t));
            TmpGtdProto.m_u16GtdID = 52;		// BusyTone2, we use GTD's ID 52
            TmpGtdProto.m_u16Freq_Mask = globals.g_Param_Analog.m_u16BusyTone2_FreqIndexMask;
            TmpGtdProto.m_u16Envelope_Mode = 1;
            TmpGtdProto.m_u16Repeat_Count = 1;
            TmpGtdProto.m_u16Min_On_Time1 = (ushort)((globals.g_Param_Analog.m_u16BusyTone2_On_Time *
                (100 - globals.g_Param_Analog.m_u16BusyTone2_TimeDeviation) / 100) / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_On_Time1 = (ushort)((globals.g_Param_Analog.m_u16BusyTone2_On_Time *
                (100 + globals.g_Param_Analog.m_u16BusyTone2_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Min_Off_Time1 = (ushort)((globals.g_Param_Analog.m_u16BusyTone2_Off_Time *
                (100 - globals.g_Param_Analog.m_u16BusyTone2_TimeDeviation)) / 100 / 15);		// the unit is 15 ms
            TmpGtdProto.m_u16Max_Off_Time1 = (ushort)((globals.g_Param_Analog.m_u16BusyTone2_Off_Time *
                (100 + globals.g_Param_Analog.m_u16BusyTone2_TimeDeviation)) / 100 / 15);		// the unit is 15 ms

            r = DJAcsApiDef.XMS_ctsSetParam(globals.g_acsHandle, pDevice, u16ParamType, u16ParamSize, &TmpGtdProto);
        }

        public void CheckRemoveReady(sbyte s8DspModID)
        {
            // check device : INTERFACE_CH
            for (int i = 0; i < globals.AllDeviceRes[s8DspModID].lTrunkNum; i++)
            {
                if ((globals.AllDeviceRes[s8DspModID].pTrunk[i].State != DJDemoGlobals.TRUNK_STATE.TRK_WAITOPEN)
                    && (globals.AllDeviceRes[s8DspModID].pTrunk[i].State != DJDemoGlobals.TRUNK_STATE.TRK_WAIT_REMOVE))
                {
                    return;
                }
            }

            // check device : VOICE
            for (int i = 0; i < globals.AllDeviceRes[s8DspModID].lVocNum; i++)
            {
                if ((globals.AllDeviceRes[s8DspModID].pVoice[i].State != DJDemoGlobals.VOICE_STATE.VOC_WAITOPEN)
                    && (globals.AllDeviceRes[s8DspModID].pVoice[i].State != DJDemoGlobals.VOICE_STATE.VOC_WAIT_REMOVE))
                {
                    return;
                }
            }

            // all device in this DSP is ready for remove 
            globals.AllDeviceRes[s8DspModID].RemoveState = DJDemoGlobals.REMOVE_STATE.DSP_REMOVE_STATE_READY;
            DrawCount_RemoveState(s8DspModID);
        }

        public unsafe void Change_State(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk, DJDemoGlobals.TRUNK_STATE NewState)
        {
            pOneTrunk->State = NewState;

            DrawMain_State(pOneTrunk->iSeqID, (int)pOneTrunk->State);

            // Check if ready to remove DSP hardware
            if ((globals.AllDeviceRes[pOneTrunk->deviceID.m_s8ModuleID].RemoveState == DJDemoGlobals.REMOVE_STATE.DSP_REMOVE_STATE_START)
                && (NewState == DJDemoGlobals.TRUNK_STATE.TRK_FREE))
            {
                pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_WAIT_REMOVE;

                DrawMain_State(pOneTrunk->iSeqID, (int)pOneTrunk->State);

                CheckRemoveReady(pOneTrunk->deviceID.m_s8ModuleID);
            }
        }

        public unsafe void DrawMain_VocInfo( DJDemoGlobals.TRUNK_STRUCT *pOneTrunk )
        {
            int iDispRow;

            iDispRow = CalDispRow(pOneTrunk->iSeqID);

            if (iDispRow < 0) return ;

            if (pOneTrunk->VocDevID.m_s16DeviceMain != 0)
            {
                string strMsg;

                strMsg = String.Format("{0},{1}", pOneTrunk->VocDevID.m_s8ModuleID, pOneTrunk->VocDevID.m_s16ChannelID);
                DrawMain(iDispRow, 8, strMsg);

                strMsg = null;
            }
        }

        public unsafe void InitTrunkChannel(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk)
        {
            Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_FREE);

            pOneTrunk->CallerCode[0] = 0;
            pOneTrunk->CalleeCode[0] = 0;

            pOneTrunk->DtmfCount = 0;
            pOneTrunk->DtmfBuf[0] = 0; 
            DrawMain_DTMF(pOneTrunk);

            memset((void*)&pOneTrunk->VocDevID, 0, sizeof(DeviceID_t));		// 0: didn't alloc Voc Device
            DrawMain_VocInfo(pOneTrunk);
        }

        public unsafe void	My_BuildIndex ( DeviceID_t* pVocDevID )
        {
            int nRet;
            string strFileName;

            nRet = DJAcsApiDef.XMS_ctsInitPlayIndex(globals.g_acsHandle, pVocDevID, null);
            if (nRet < 0)
            {
                string strMsg;

                strMsg = String.Format("XMS_ctsInitPlayIndex() FAIL. ret = {0}", nRet);
                ListBox_AddItem(strMsg);
                strMsg = null;
                //listBox_OptAndEvtInfo.Items.Add(strMsg);
                return ;
            }
            PlayProperty_t  playProperty;

            memset((void *)&playProperty, 0, sizeof(PlayProperty_t));

            for (int i = 0; i < 17; i++)
            {
                if (16 == i)
                {
                    playProperty.m_u16PlayType = (ushort)XMS_BUILD_INDEX_TYPE.XMS_BUILD_INDEX_FILE;
                    strFileName = globals.cfg_VocPath ;
                    //strFileName += "\\bank.008";
                    strFileName += "Bank.008";
                }
                else
                {
                    playProperty.m_u16PlayType = (ushort)XMS_BUILD_INDEX_TYPE.XMS_BUILD_INDEX_RAM;
                    //strFileName = String.Format("{0}\\D{1}", globals.cfg_VocPath, i);
                    strFileName = String.Format("{0}D{1}", globals.cfg_VocPath, i);
                }
                CharsToSBytes(strFileName.ToCharArray(), playProperty.m_s8PlayContent, strFileName.Length);

                nRet = DJAcsApiDef.XMS_ctsBuildPlayIndex(globals.g_acsHandle, pVocDevID, &playProperty, null);
                if (nRet < 0)
                {
                    string strMsg;

                    strMsg = String.Format("XMS_ctsBuildPlayIndex(%s) FAIL. ret = {0}", nRet);
                    //listBox_OptAndEvtInfo.Items.Add(strMsg);
                    ListBox_AddItem(strMsg);

                    strMsg = null;
                }
            }

            strFileName = null;
        }

        /* Stop Record */
        public unsafe int StopRecordFile(DeviceID_t* pVocDevID)
        {
            ControlRecord_t controlRecord;

            memset(&controlRecord, 0, sizeof(ControlRecord_t));
            controlRecord.m_u32ControlType = (uint)XMS_CTRL_RECORD_TYPE.XMS_STOP_RECORD;

            return DJAcsApiDef.XMS_ctsControlRecord(globals.g_acsHandle, pVocDevID, &controlRecord, null);
        }

        /* Handle Record */
        public unsafe int RecordFile(DeviceID_t* pVocDevID, string FileName, uint u32RecSize, bool bIsAppend)
        {
            RecordProperty_t recordProperty;

            memset(&recordProperty, 0, sizeof(RecordProperty_t));

            recordProperty.m_u32MaxSize = u32RecSize;

            if (bIsAppend)
                recordProperty.m_s8IsAppend = 1;
            else
                recordProperty.m_s8IsAppend = 0;

            strcpy(recordProperty.m_s8FileName, FileName);

            FileName = null;

            return DJAcsApiDef.XMS_ctsRecord(globals.g_acsHandle, pVocDevID, &recordProperty, null);
        }

        public unsafe bool CheckRecordEnd(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk, Acs_Evt_t* pAcsEvt)
        {

            if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_RECORD)
            {
                return true;
            }

            return false;
        }

        int dtmfIndex = 0;

        public unsafe void TrunkWork(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk, Acs_Evt_t* pAcsEvt)
        {
            #region
            if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_CLEARCALL)	//clear Event
            {
                if ((pOneTrunk->State != DJDemoGlobals.TRUNK_STATE.TRK_FREE) && (pOneTrunk->State != DJDemoGlobals.TRUNK_STATE.TRK_WAIT_REMOVE))
                {
                    ResetTrunk(pOneTrunk, pAcsEvt);
                    return;
                }
            }

            if (pOneTrunk->deviceID.m_s16DeviceSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
            {
                sbyte* psbTmpGtd = My_GetGtdCode(pAcsEvt);
                if (psbTmpGtd != null)
                {
                    sbyte TmpGtd = (sbyte)(*psbTmpGtd);
                    if (TmpGtd == (sbyte)'I' || TmpGtd == (sbyte)'J' || TmpGtd == (sbyte)'K')	// Busy Tone
                    {
                        DJAcsApiDef.XMS_ctsResetDevice(globals.g_acsHandle, &pOneTrunk->deviceID, null);
                        DJAcsApiDef.XMS_ctsClearCall(globals.g_acsHandle, &pOneTrunk->deviceID, 0, null);
                        ResetTrunk(pOneTrunk, pAcsEvt);
                    }
                }
            }
            #endregion

            switch(pOneTrunk->State)
            {
            case DJDemoGlobals.TRUNK_STATE.TRK_FREE:
                // Special code for CAS(SS1)
                SpecialForCas(pOneTrunk, pAcsEvt);

                if ( pOneTrunk->deviceID.m_s16DeviceSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK )
                {
                    byte	 *p = My_GetFskCode ( pAcsEvt );
                    if ( p != null )
                    {
                        Acs_IO_Data* pIOData = (Acs_IO_Data*)((byte*)pAcsEvt + sizeof(Acs_Evt_t));
                        int iFSKDataLen = pIOData->m_u16IoDataLen;
                        ConvertRawFskToCallerID(p, iFSKDataLen, pOneTrunk->CallerCode, 20);
                        //ConvertRawFskToCallerID(p, pOneTrunk->CallerCode, 20);
                    }

                    sbyte ch = My_GetDtmfCode(pAcsEvt);
                    if (-1 != ch)
                    {
                        if (ch >= (sbyte)'0' && ch <= (sbyte)'9')
                        {
                            pOneTrunk->CallerCode[dtmfIndex++] = ch;
                            DrawMain_CallInfo(pOneTrunk);
                        }
                        else if (ch == (sbyte)'d' || ch == (sbyte)'D')
                        {
                            dtmfIndex = 0;
                        }
                        else if (ch == (sbyte)'c' || ch == (sbyte)'C')
                        {
                            memset(pOneTrunk->CallerCode, 0, sizeof(char) * 20);
                        }
                    }

                }

                if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_CALLIN)	// Call In Event 
                {
                    // release the Voice for get FSK
                    if (pOneTrunk->deviceID.m_s16DeviceSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
                    {
                        My_DualUnlink(&pOneTrunk->VocDevID, &pOneTrunk->deviceID);

                        FreeOneFreeVoice(&pOneTrunk->VocDevID);

                        fixed (DeviceID_t* pUsedDev =
                            &globals.AllDeviceRes[pOneTrunk->VocDevID.m_s8ModuleID].pVoice[pOneTrunk->VocDevID.m_s16ChannelID].UsedDevID)
                        {
                            memset(pUsedDev, 0, sizeof(DeviceID_t));		// 0: didn't alloc Device
                        }
                        memset(&pOneTrunk->VocDevID, 0, sizeof(DeviceID_t));		// 0: didn't alloc Device
                        DrawMain_VocInfo(pOneTrunk);
                    }

                    Acs_CallControl_Data* pCallControl = (Acs_CallControl_Data*)((byte*)pAcsEvt + sizeof(Acs_Evt_t));
                    DJAcsApiDef.XMS_ctsAlertCall(globals.g_acsHandle, &pOneTrunk->deviceID, null);
                    DJAcsApiDef.XMS_ctsAnswerCallIn(globals.g_acsHandle, &pOneTrunk->deviceID, null);

                    if (pOneTrunk->deviceID.m_s16DeviceSub != (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
                    {
                        SBytesToSBytes(pOneTrunk->CalleeCode, pCallControl->m_s8CalledNum);
                        SBytesToSBytes(pOneTrunk->CallerCode, pCallControl->m_s8CallingNum);
                    }

                    DrawMain_CallInfo(pOneTrunk);
                    Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_WAIT_ANSWERCALL);
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_WAIT_ANSWERCALL:
                // Special code for CAS(SS1)
                SpecialForCas(pOneTrunk,pAcsEvt);

                if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_ANSWERCALL)	//Answer Call In End Event
                {
                    Acs_CallControl_Data* pCallControl = (Acs_CallControl_Data*)((byte*)pAcsEvt + sizeof(Acs_Evt_t));

                    DeviceID_t FreeVocDeviceID;
                    if (SearchOneFreeVoice(pOneTrunk, &FreeVocDeviceID) >= 0)
                    {
                        pOneTrunk->u8PlayTag = 16;

                        pOneTrunk->VocDevID = FreeVocDeviceID;

                        globals.AllDeviceRes[FreeVocDeviceID.m_s8ModuleID].pVoice[FreeVocDeviceID.m_s16ChannelID].UsedDevID = pOneTrunk->deviceID;

                        DrawMain_VocInfo(pOneTrunk);

                        My_DualLink(&FreeVocDeviceID, &pOneTrunk->deviceID);

                        if (pOneTrunk->deviceID.m_s16DeviceSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
                        {
                            SetGtD_AnalogTrunk(&FreeVocDeviceID);		// prepare for get Busy Tone
                        }

                        Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_WAIT_LINKOK);
                    }
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_WAIT_LINKOK:
                if ( pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_LINKDEVICE )	//LinkDevice End
                {
                    string FileName = globals.cfg_VocPath;
                    //FileName += "\\bank.001";
                    FileName += "Bank.001";
                    ++pOneTrunk->u8PlayTag;
                    PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, false);

                    Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_WELCOME);

                    FileName = null;
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_WELCOME:
                if ( CheckPlayEnd ( pOneTrunk, pAcsEvt) )	//play end Event
                {
                    string FileName = globals.cfg_VocPath;
                    //FileName += "\\bank.002";
                    FileName += "Bank.002";
                    ++pOneTrunk->u8PlayTag;
                    PlayFile ( &pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, false);

                    Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_ACCOUNT);

                    FileName = null;
                }

                sbyte sDtmf = My_GetDtmfCode ( pAcsEvt );
                if (sDtmf != -1)								//DTMF key
                {
                    My_AddDtmfBuf(pOneTrunk, sDtmf);

                    DrawMain_DTMF(pOneTrunk);

                    StopPlayFile ( &pOneTrunk->VocDevID );

                    Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_ACCOUNT);
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_ACCOUNT:
                {
                    // if play end
                    // do nothing

                    sbyte sTmpDtmf = My_GetDtmfCode(pAcsEvt);
                    if (sTmpDtmf != -1)								//DTMF Key
                    {
                        My_AddDtmfBuf(pOneTrunk, sTmpDtmf);

                        DrawMain_DTMF(pOneTrunk);

                        StopPlayFile(&pOneTrunk->VocDevID);

                        if (pOneTrunk->DtmfCount >= 8)
                        {
                            /*Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_PASSWORD);
                            My_InitDtmfBuf(pOneTrunk);*/

                            //string FileName = globals.cfg_VocPath + "\\bank.003";
                            string FileName = globals.cfg_VocPath + "Bank.003";

                            ++pOneTrunk->u8PlayTag;
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, false);

                            My_InitDtmfBuf(pOneTrunk);
                            Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_PASSWORD);

                            FileName = null;
                        }
                    }
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_PASSWORD:
                {
                    // if play end
                    // do nothing

                    sbyte sTmpDtmf = My_GetDtmfCode(pAcsEvt);
                    if (sTmpDtmf != -1)								//DTMF key
                    {
                        My_AddDtmfBuf(pOneTrunk, sTmpDtmf);

                        DrawMain_DTMF(pOneTrunk);

                        StopPlayFile(&pOneTrunk->VocDevID);

                        if (pOneTrunk->DtmfCount >= 6)
                        {
                            /*Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_SELECT);
                            My_InitDtmfBuf(pOneTrunk);*/

                            string FileName = globals.cfg_VocPath + "Bank.004";

                            ++pOneTrunk->u8PlayTag;
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, false);

                            My_InitDtmfBuf(pOneTrunk);
                            Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_SELECT);

                            FileName = null;
                            //pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_SELECT;
                        }
                    }
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_SELECT:
                {
                    // if play end
                    // do nothing

                    sbyte sTmpDtmf = My_GetDtmfCode(pAcsEvt);
                    if (sTmpDtmf == -1)								//DTMF Key
                        break;

                    My_AddDtmfBuf(pOneTrunk, sTmpDtmf);
                    DrawMain_DTMF(pOneTrunk);

                    ++pOneTrunk->u8PlayTag;
                    string FileName = globals.cfg_VocPath;
                    switch (sTmpDtmf)
                    {
                        case (sbyte)'1':
                            {
                                StopPlayFile(&pOneTrunk->VocDevID);

                                FileName += "Bank.005";
                                PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                                PlayIndex(&pOneTrunk->VocDevID, 5, pOneTrunk->u8PlayTag, true);
                                PlayIndex(&pOneTrunk->VocDevID, 12, pOneTrunk->u8PlayTag, true);
                                PlayIndex(&pOneTrunk->VocDevID, 8, pOneTrunk->u8PlayTag, true);
                                PlayIndex(&pOneTrunk->VocDevID, 11, pOneTrunk->u8PlayTag, true);
                                PlayIndex(&pOneTrunk->VocDevID, 9, pOneTrunk->u8PlayTag, true);
                                PlayIndex(&pOneTrunk->VocDevID, 10, pOneTrunk->u8PlayTag, true);
                                PlayIndex(&pOneTrunk->VocDevID, 15, pOneTrunk->u8PlayTag, true);
                                PlayIndex(&pOneTrunk->VocDevID, 8, pOneTrunk->u8PlayTag, true);

                                PlayIndex(&pOneTrunk->VocDevID, 16, pOneTrunk->u8PlayTag, true);		// bank.008
                                
                                Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_PLAYRESULT);
                                //pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_PLAYRESULT;
                            }
                            break;

                        case (sbyte)'2':
                            StopPlayFile(&pOneTrunk->VocDevID);

                            FileName += "Bank.006";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            PlayIndex(&pOneTrunk->VocDevID, 0, pOneTrunk->u8PlayTag, true);
                            PlayIndex(&pOneTrunk->VocDevID, 15, pOneTrunk->u8PlayTag, true);
                            PlayIndex(&pOneTrunk->VocDevID, 4, pOneTrunk->u8PlayTag, true);
                            PlayIndex(&pOneTrunk->VocDevID, 8, pOneTrunk->u8PlayTag, true);

                            FileName = globals.cfg_VocPath + "Bank.008";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_PLAYRESULT);
                            //pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_PLAYRESULT;
                            break;

                        case (sbyte)'3':
                            StopPlayFile(&pOneTrunk->VocDevID);

                            FileName = globals.cfg_VocPath + "Bank.007";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            FileName = globals.cfg_VocPath + "D3";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            FileName = globals.cfg_VocPath + "D13";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            FileName = globals.cfg_VocPath + "D7";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            FileName = globals.cfg_VocPath + "D12";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            FileName = globals.cfg_VocPath + "Bank.008";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_PLAYRESULT);
                            //pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_PLAYRESULT;
                            break;

                        case (sbyte)'4':
                            StopPlayFile(&pOneTrunk->VocDevID);

                            FileName = globals.cfg_VocPath + "DemoRec." + pOneTrunk->iSeqID.ToString("%03d");
                            RecordFile(&pOneTrunk->VocDevID, FileName, 8000 * 10, false);

                            Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_RECORDFILE);
                            //pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_RECORDFILE;
                            break;

                        default:
                            break;
                    }

                    FileName = null;
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_PLAYRESULT:
            case DJDemoGlobals.TRUNK_STATE.TRK_PLAYRECORD:
                if ( CheckPlayEnd ( pOneTrunk, pAcsEvt) )	// Play End Event 
                {
                    // Clear Call
                    DJAcsApiDef.XMS_ctsClearCall(globals.g_acsHandle, &pOneTrunk->deviceID, 0, null);

                    Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_HANGON);
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_RECORDFILE:
                {
                    sbyte sTmpDtmf = My_GetDtmfCode(pAcsEvt);
                    if (sTmpDtmf != -1)								//DTMF Key
                    {
                        My_AddDtmfBuf(pOneTrunk, sTmpDtmf);
                        DrawMain_DTMF(pOneTrunk);

                        StopRecordFile(&pOneTrunk->VocDevID);
                    }

                    if (CheckRecordEnd(pOneTrunk, pAcsEvt))	//record end
                    {
                        ++pOneTrunk->u8PlayTag;

                        string FileName = globals.cfg_VocPath + "DemoRec." + pOneTrunk->iSeqID.ToString("%03d");

                        PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, false);

                        Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_PLAYRECORD);

                        FileName = null;
                    }
                }
                break;

                default:
                    break;
            }
        }

        public static unsafe void EvtHandler(UInt32 esrParam)
        {   
            try
            {
                fixed (UInt32* pAcsHandle = &globals.g_acsHandle)
                {
                    Acs_Evt_t* pAcsEvt = (Acs_Evt_t*)esrParam;

                    //EvtInfo
                    {
                        pDemo.ShowEvtInfo(pAcsEvt);
                    }

                    //EvtProc
                    {
                        switch ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType)
                        {
                            case XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_START:
                                break;

                            #region XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE
                            case XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE:
                                if ((globals.cfg_iPartWork == 0) || (pAcsEvt->m_DeviceID.m_s8ModuleID == globals.cfg_iPartWorkModuleID))
                                {
                                    Acs_Dev_List_Head_t* pAcsDevList = (Acs_Dev_List_Head_t*)((byte*)pAcsEvt + sizeof(Acs_Evt_t));

                                    //收到设备变化的事件，增加/删除 该设备资源
                                    {
                                        int s32Type = pAcsDevList->m_s32DeviceMain;
                                        int s32Num = pAcsDevList->m_s32DeviceNum;
                                        int s8DspModID = pAcsDevList->m_s32ModuleID;

                                        if ((s8DspModID > 0) && (s8DspModID < DJDemoGlobals.MAX_DSP_MODULE_NUMBER_OF_XMS))
                                        {
                                            DeviceID_t* pDev = (DeviceID_t*)((byte*)pAcsDevList + sizeof(Acs_Dev_List_Head_t));
                                            switch ((XMS_DEVMAIN_TYPE)s32Type)
                                            {
                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE:
                                                    {
                                                        globals.AllDeviceRes[s8DspModID].pVoice = new DJDemoGlobals.VOICE_STRUCT[s32Num];
                                                        globals.AllDeviceRes[s8DspModID].pVoice.Initialize(); 
                                                        globals.AllDeviceRes[s8DspModID].lVocNum = s32Num;
                                                        globals.AllDeviceRes[s8DspModID].lVocOpened = 0;
                                                        globals.AllDeviceRes[s8DspModID].lVocFreeNum = 0;

                                                        for (int i = 0; i < s32Num; ++i)
                                                        {
                                                            globals.AllDeviceRes[s8DspModID].pVoice[i].deviceID = pDev[i];
                                                            globals.AllDeviceRes[s8DspModID].pVoice[i].State = DJDemoGlobals.VOICE_STATE.VOC_WAITOPEN;
                                                        }
                                                    }
                                                    break;

                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT:
                                                    {
                                                        globals.AllDeviceRes[s8DspModID].pPcm = new DJDemoGlobals.PCM_STRUCT[s32Num];
                                                        globals.AllDeviceRes[s8DspModID].pPcm.Initialize();
                                                        globals.AllDeviceRes[s8DspModID].lPcmNum = s32Num;
                                                        globals.AllDeviceRes[s8DspModID].lPcmOpened = 0;

                                                        for (int i = 0; i < s32Num; ++i)
                                                        {
                                                            globals.AllDeviceRes[s8DspModID].pPcm[i].deviceID = pDev[i];
                                                            globals.AllDeviceRes[s8DspModID].pPcm[i].bOpenFlag = false;
                                                        }
                                                    }
                                                    break;

                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH:
                                                    {
                                                        globals.AllDeviceRes[s8DspModID].pTrunk = new DJDemoGlobals.TRUNK_STRUCT[s32Num];
                                                        globals.AllDeviceRes[s8DspModID].pTrunk.Initialize();
                                                        globals.AllDeviceRes[s8DspModID].lTrunkNum = s32Num;
                                                        globals.AllDeviceRes[s8DspModID].lTrunkOpened = 0;

                                                        for (int i = 0; i < s32Num; i++)
                                                        {
                                                            globals.AllDeviceRes[s8DspModID].pTrunk[i].deviceID = pDev[i];
                                                            globals.AllDeviceRes[s8DspModID].pTrunk[i].State = DJDemoGlobals.TRUNK_STATE.TRK_WAITOPEN;
                                                        }
                                                    }
                                                    break;

                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD:
                                                    {
                                                        globals.AllDeviceRes[s8DspModID].deviceID = pDev[0];
                                                        globals.AllDeviceRes[s8DspModID].bOpenFlag = false;
                                                        globals.AllDeviceRes[s8DspModID].bErrFlag = false;
                                                        globals.AllDeviceRes[s8DspModID].RemoveState = DJDemoGlobals.REMOVE_STATE.DSP_REMOVE_STATE_NONE;
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

                                            pDev = null;
                                        }
                                    }

                                    pAcsDevList = null;
                                }
                                break;
                            #endregion

                            #region XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_END
                            case XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_END:
                            case XMS_EVT_TYPE.XMS_EVT_QUERY_REMOVE_ONE_DSP_END:

                                if (globals.cfg_iPartWork != 0 && pAcsEvt->m_DeviceID.m_s8ModuleID != globals.cfg_iPartWorkModuleID)
                                {
                                    return;
                                }

                                if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_END)
                                {
                                    globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].lFlag = 1;		// 该DSP可以用了
                                    sbyte s8DspModID = pAcsEvt->m_DeviceID.m_s8ModuleID;

                                    globals.AllDeviceRes[s8DspModID].bErrFlag = false;
                                    globals.AllDeviceRes[s8DspModID].RemoveState = DJDemoGlobals.REMOVE_STATE.DSP_REMOVE_STATE_NONE;

                                    // Open Board
                                    int iResult = 0;

                                    if (globals.AllDeviceRes[s8DspModID].bOpenFlag == false)	// 还没有Open
                                    {
                                        fixed (DeviceID_t* pDev = &globals.AllDeviceRes[s8DspModID].deviceID)
                                        {
                                            iResult = DJAcsApiDef.XMS_ctsOpenDevice(globals.g_acsHandle, pDev, null);
                                            if (iResult != (int)ERROR_CODE.ACSPOSITIVE_ACK)
                                            {
                                                string strMsg = "XMS_ctsOpenDevice (Board) Fail!";
                                                pDemo.ListBox_AddItem(strMsg);

                                                strMsg = null;
                                            }
                                        }
                                    }
                                        // Open Voice
                                        for (int i = 0; i < globals.AllDeviceRes[s8DspModID].lVocNum; ++i)
                                        {
                                            fixed (DeviceID_t* pDev = &globals.AllDeviceRes[s8DspModID].pVoice[i].deviceID)
                                            {
                                                iResult = DJAcsApiDef.XMS_ctsOpenDevice(globals.g_acsHandle, pDev, null);
                                                if (iResult != (int)ERROR_CODE.ACSPOSITIVE_ACK)
                                                {
                                                    string strMsg = "CtsOpenDeviceEx (Voice) Fail!";

                                                    pDemo.ListBox_AddItem(strMsg);

                                                    strMsg = null;
                                                }
                                            }
                                        }

                                        // Open Pcm
                                        for (int i = 0; i < globals.AllDeviceRes[s8DspModID].lPcmNum; ++i)
                                        {
                                            fixed (DeviceID_t* pDev = &globals.AllDeviceRes[s8DspModID].pPcm[i].deviceID)
                                            {
                                                iResult = DJAcsApiDef.XMS_ctsOpenDevice(globals.g_acsHandle, pDev, null);
                                                if (iResult != (int)ERROR_CODE.ACSPOSITIVE_ACK)
                                                {
                                                    string strMsg = "CtsOpenDeviceEx (Pcm) Fail!";

                                                    pDemo.ListBox_AddItem(strMsg);

                                                    strMsg = null;
                                                }
                                            }
                                        }

                                        // Open Trunk
                                        for (int i = 0; i < globals.AllDeviceRes[s8DspModID].lTrunkNum; ++i)
                                        {
                                            fixed (DeviceID_t* pDev = &globals.AllDeviceRes[s8DspModID].pTrunk[i].deviceID)
                                            {
                                                iResult = DJAcsApiDef.XMS_ctsOpenDevice(globals.g_acsHandle, pDev, null);
                                                if (iResult != (int)ERROR_CODE.ACSPOSITIVE_ACK)
                                                {
                                                    string strMsg = "CtsOpenDeviceEx (Trunk) Fail!";

                                                    pDemo.ListBox_AddItem(strMsg);

                                                    strMsg = null;
                                                }
                                            }
                                        }
                                }
                                
                                else
                                {
                                    globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].lFlag = 0;		// 该DSP已经Remove完毕
                                }

                                pDemo.RefreshMapTable();
                                pDemo.ReDrawAll();

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
                                                globals.AllDeviceRes[iDspModuleID].deviceID.m_CallID = pAcsEvt->m_DeviceID.m_CallID;
                                                globals.AllDeviceRes[iDspModuleID].bOpenFlag = true;

                                                pDemo.SetGTD_ToneParam(&pAcsEvt->m_DeviceID);
                                            }
                                            break;

                                        #region XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH
                                        case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH:
                                            {
                                                fixed (DJDemoGlobals.TRUNK_STRUCT* pOneTrunk = &globals.AllDeviceRes[iDspModuleID].pTrunk[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                                {
                                                    pOneTrunk->deviceID.m_CallID = pAcsEvt->m_DeviceID.m_CallID;		// this line is very important, must before all operation

                                                   /* if (pOneTrunk->deviceID.m_s16DeviceSub == (short)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_DSS1)
                                                    {
                                                        MessageBox.Show("XMS_INTERFACE_DEVSUB_TYPE");
                                                    } */

                                                    pDemo.InitTrunkChannel(pOneTrunk);

                                                    {
                                                        DJAcsApiDef.XMS_ctsResetDevice(globals.g_acsHandle, &pOneTrunk->deviceID, null);
                                                        DJAcsApiDef.XMS_ctsGetDevState(globals.g_acsHandle, &pOneTrunk->deviceID, null);
                                                    }

                                                    ++globals.AllDeviceRes[iDspModuleID].lTrunkOpened;
                                                    ++globals.g_iTotalTrunkOpened;

                                                    pDemo.DrawCount_Trunk(pAcsEvt->m_DeviceID.m_s8ModuleID);

                                                    if (pOneTrunk->deviceID.m_s16DeviceSub == (int)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
                                                    {
                                                        CmdParamData_AnalogTrunk_t cmdAnalogTrunk;
                                                        ushort u16ParamType = (ushort)XMS_ANALOGTRUNK_PARAM_TYPE.ANALOGTRUNK_PARAM_UNIPARAM; // 0
                                                        ushort u16ParamSize = (ushort)sizeof(CmdParamData_AnalogTrunk_t);

                                                        pDemo.memset((void*)&cmdAnalogTrunk, 0, sizeof(CmdParamData_AnalogTrunk_t));
                                                        cmdAnalogTrunk.m_u16CallInRingCount = 3;			// 3 times RingBack
                                                        cmdAnalogTrunk.m_u16CallInRingTimeOut = 6000;		// 60 seconds

                                                        {

                                                            int iResult = DJAcsApiDef.XMS_ctsSetParam(globals.g_acsHandle, &pOneTrunk->deviceID, u16ParamType, u16ParamSize, &cmdAnalogTrunk);

                                                            string strMsg;
                                                            strMsg = String.Format("Set AnalogTrunk  ret = {0}", iResult.ToString());
                                                            //listBox_OptAndEvtInfo.Items.Add(strMsg);
                                                            pDemo.ListBox_AddItem(strMsg);
                                                            pDemo.PrepareForCallerID(pOneTrunk);
                                                        }

                                                    }

                                                }
                                            }
                                            break;
                                        #endregion

                                        case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE:
                                            {
                                                fixed (DJDemoGlobals.VOICE_STRUCT* pOneVoc = &globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pVoice[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                                {
                                                    pOneVoc->deviceID.m_CallID = pAcsEvt->m_DeviceID.m_CallID;
                                                    pDemo.Change_Voc_State(pOneVoc, DJDemoGlobals.VOICE_STATE.VOC_FREE);

                                                    DJAcsApiDef.XMS_ctsResetDevice(globals.g_acsHandle, &pOneVoc->deviceID, null);
                                                    DJAcsApiDef.XMS_ctsGetDevState(globals.g_acsHandle, &pOneVoc->deviceID, null);

                                                    if (globals.g_iTotalVoiceOpened == 0)
                                                    {
                                                        pDemo.My_BuildIndex(&pOneVoc->deviceID);
                                                    }
                                                }

                                                ++globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].lVocOpened;
                                                ++globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].lVocFreeNum;
                                                ++globals.g_iTotalVoiceFree;
                                                ++globals.g_iTotalVoiceOpened;

                                                pDemo.DrawCount_Voc(pAcsEvt->m_DeviceID.m_s8ModuleID);
                                            }

                                            break;

                                        #region XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT
                                        case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT:
                                            {
                                                fixed(DJDemoGlobals.PCM_STRUCT* pOnePcm = &globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pPcm[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                                {
                                                    pOnePcm->deviceID.m_CallID = pAcsEvt->m_DeviceID.m_CallID;
                                                    pOnePcm->bOpenFlag = true;

                                                    DJAcsApiDef.XMS_ctsResetDevice(globals.g_acsHandle, &pOnePcm->deviceID, null);
                                                    DJAcsApiDef.XMS_ctsGetDevState(globals.g_acsHandle, &pOnePcm->deviceID, null);
                                                    pDemo.DrawPcm_TypeAndAlarm(pOnePcm);
                                                }
                                                ++globals.AllDeviceRes[iDspModuleID].lPcmOpened;
                                                ++globals.g_iTotalPcmOpened;

                                                pDemo.DrawCount_Pcm(pAcsEvt->m_DeviceID.m_s8ModuleID);
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
                                //CloseDeviceOK(&pAcsEvt->m_DeviceID);
                                {
                                    sbyte s8ModuleID = pAcsEvt->m_DeviceID.m_s8ModuleID;
                                    short s16ChannelID = pAcsEvt->m_DeviceID.m_s16ChannelID;

                                    globals.AllDeviceRes[s8ModuleID].bErrFlag = true;
                                    pDemo.DrawCount_ErrFlag(s8ModuleID);

                                    if (pAcsEvt->m_DeviceID.m_s16DeviceMain == (short)XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD)
                                    {
                                        globals.AllDeviceRes[s8ModuleID].bOpenFlag = false;
                                    }

                                    if (pAcsEvt->m_DeviceID.m_s16DeviceMain == (short)XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH)
                                    {
                                        fixed (DJDemoGlobals.TRUNK_STRUCT* pOneTrunk = &globals.AllDeviceRes[s8ModuleID].pTrunk[s16ChannelID])
                                        {
                                            pDemo.Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_WAITOPEN);

                                            globals.g_iTotalTrunkOpened--;
                                            globals.AllDeviceRes[s8ModuleID].lTrunkOpened--;

                                            pDemo.DrawCount_Trunk(s8ModuleID);
                                        }
                                    }

                                    if (pAcsEvt->m_DeviceID.m_s16DeviceMain == (short)XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE)
                                    {
                                        fixed (DJDemoGlobals.VOICE_STRUCT* pOneVoc = &globals.AllDeviceRes[s8ModuleID].pVoice[s16ChannelID])
                                        {
                                            pDemo.Change_Voc_State(pOneVoc, DJDemoGlobals.VOICE_STATE.VOC_WAITOPEN);

                                            globals.g_iTotalVoiceOpened--;
                                            globals.g_iTotalVoiceFree--;
                                            globals.AllDeviceRes[s8ModuleID].lVocOpened--;
                                            globals.AllDeviceRes[s8ModuleID].lVocFreeNum--;

                                            pDemo.DrawCount_Voc(s8ModuleID);
                                        }
                                    }

                                    if (pAcsEvt->m_DeviceID.m_s16DeviceMain == (short)XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT)
                                    {
                                        fixed (DJDemoGlobals.PCM_STRUCT* pOnePcm = &globals.AllDeviceRes[s8ModuleID].pPcm[s16ChannelID])
                                        {
                                            pOnePcm->bOpenFlag = false;
                                            globals.AllDeviceRes[s8ModuleID].lPcmOpened--;
                                            globals.g_iTotalPcm--;
                                            pDemo.DrawCount_Pcm(s8ModuleID);
                                        }
                                    }
                                }
                                break;

                            #region XMS_EVT_TYPE.XMS_EVT_DEVICESTATE
                            case XMS_EVT_TYPE.XMS_EVT_DEVICESTATE:
                                {
                                    Acs_GeneralProc_Data* pGeneralData =
                                        (Acs_GeneralProc_Data*)((byte*)pAcsEvt + sizeof(Acs_Evt_t));
                                    if (pAcsEvt->m_DeviceID.m_s16DeviceMain == (short)XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH)
                                    {
                                        fixed (DJDemoGlobals.TRUNK_STRUCT* pOneTrunk =
                                            &globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pTrunk[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                        {
                                            pOneTrunk->iLineState = pGeneralData->m_s32DeviceState;

                                            pDemo.DrawMain_LineState(pOneTrunk->iSeqID, pOneTrunk->iLineState);
                                        }
                                    }

                                    if (pAcsEvt->m_DeviceID.m_s16DeviceMain == (short)XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT)
                                    {
                                        fixed (DJDemoGlobals.PCM_STRUCT* pOnePcm = &globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pPcm[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                        {
                                            pOnePcm->u8E1Type = (byte)((pGeneralData->m_s32DeviceState >> 16) & 0xFF);
                                            pOnePcm->s32AlarmVal = (pGeneralData->m_s32DeviceState & 0xFFFF);
                                            pDemo.DrawPcm_TypeAndAlarm(pOnePcm);
                                        }
                                    }

                                    pGeneralData = null;
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
                                    fixed (DJDemoGlobals.TRUNK_STRUCT* pOneTrunk = &globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pTrunk[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                    {
                                        pDemo.TrunkWork(pOneTrunk, pAcsEvt);
                                    }
                                }
                                else if ((XMS_DEVMAIN_TYPE)pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE)
                                {
                                    fixed (DeviceID_t* pDevID = &globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pVoice[pAcsEvt->m_DeviceID.m_s16ChannelID].UsedDevID)
                                    {
                                        if ((XMS_DEVMAIN_TYPE)pDevID->m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH)
                                        {
                                            fixed (DJDemoGlobals.TRUNK_STRUCT* pOneTrunk = &globals.AllDeviceRes[pDevID->m_s8ModuleID].pTrunk[pDevID->m_s16ChannelID])
                                            {
                                                pDemo.TrunkWork(pOneTrunk, pAcsEvt);
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
            }
            catch (Exception ex)
            {
                sw.WriteLine(ex.Message);
                //MessageBox.Show(ex.Message);
            }
            
            return;
        }

        public unsafe void InitTextBox()
        {
            fixed (sbyte* p = globals.cfg_ServerID.m_s8ServerIp)
            {
                string strServerIp = new string(p);
                textBox_ServerIP.Text = strServerIp;

                textBox_Port.Text = globals.cfg_ServerID.m_u32ServerPort.ToString();
                textBox_VocPath.Text = globals.cfg_VocPath;

                if (globals.cfg_iDispChnl == 30)
                {
                    radioButton_Disp30.Checked = true;
                }
                else if (globals.cfg_iDispChnl == 31)
                {
                    radioButton_Disp31.Checked = true;
                }
                else if (globals.cfg_iDispChnl == 32)
                {
                    radioButton_Disp32.Checked = true;
                }

                if (globals.cfg_iVoiceRule == 0)
                {
                    radioButton_VocFix.Checked = true;
                }
                else if (globals.cfg_iVoiceRule == 1)
                {
                    radioButton_VocSameMode.Checked = true;
                }
                else
                {
                    radioButton_VocMost.Checked = true;
                }

                if (globals.cfg_iPartWork == 0)
                {
                    checkBox_ModID.Checked = false;
                }
                else
                {
                    checkBox_ModID.Checked = true;
                }

                if (globals.cfg_s32DebugOn == 0)
                {
                    checkBox_Debug.Checked = false;
                }
                else
                {
                    checkBox_Debug.Checked = true;
                }

                textBox_ModID.Text = globals.cfg_iPartWorkModuleID.ToString();

                strServerIp = null;
            }
        }

        public unsafe void SaveTextBox()
        {
            string strServerIp = textBox_ServerIP.Text;
            char[] chTemp = strServerIp.ToCharArray();
            fixed (sbyte* p = globals.cfg_ServerID.m_s8ServerIp)
            {
                CharsToSBytes(chTemp, p, strServerIp.Length);
            }

            globals.cfg_ServerID.m_u32ServerPort = uint.Parse(textBox_Port.Text);
            globals.cfg_VocPath = textBox_VocPath.Text;
            globals.cfg_iPartWorkModuleID = int.Parse(textBox_ModID.Text);

            if (checkBox_Debug.Checked == false)
            {
                globals.cfg_s32DebugOn = 0;
            }
            else
            {
                globals.cfg_s32DebugOn = 1;
            }

            if (checkBox_ModID.Checked == false)
            {
                globals.cfg_iPartWork = 0;
            }
            else
            {
                globals.cfg_iPartWork = 1;
            }

            if (radioButton_Disp30.Checked == true)
            {
                globals.cfg_iDispChnl = 30;
            }
            if (radioButton_Disp31.Checked == true)
            {
                globals.cfg_iDispChnl = 31;
            }
            if (radioButton_Disp32.Checked == true)
            {
                globals.cfg_iDispChnl = 32;
            }

            if (radioButton_VocFix.Checked == true)
            {
                globals.cfg_iVoiceRule = 0;
            }
            if (radioButton_VocSameMode.Checked == true)
            {
                globals.cfg_iVoiceRule = 1;
            }
            if (radioButton_VocMost.Checked == true)
            {
                globals.cfg_iVoiceRule = 2;
            }

            strServerIp = null;
        }

        protected unsafe override void OnFormClosing(FormClosingEventArgs e) //重载关闭按钮
        {
            sw.Close();
            fs.Close();

            SaveTextBox();
            globals.WriteToConfig();

            int iResult = 0;
            iResult = DJAcsApiDef.XMS_acsCloseStream(globals.g_acsHandle, null);
            if (iResult == (int)ERROR_CODE.ACSPOSITIVE_ACK)
            {
                listBox_OptAndEvtInfo.Items.Add("AcsCloseStreamEx Success");
            }
            else
            {
                listBox_OptAndEvtInfo.Items.Add("AcsCloseStreamEx Fail");
            }

            base.OnFormClosing(e);
        }

        #endregion

        private void Btn_Exit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        public unsafe void ReOpen_AllDevice()
        {
            for (int i = 0; i < globals.g_iTotalModule; i++)
            {
                sbyte s8DspModID = globals.MapTable_Module[i];

                globals.AllDeviceRes[s8DspModID].bErrFlag = false;
                DrawCount_ErrFlag(s8DspModID);
                globals.AllDeviceRes[s8DspModID].RemoveState = DJDemoGlobals.REMOVE_STATE.DSP_REMOVE_STATE_NONE;
                DrawCount_RemoveState(s8DspModID);
                
                // Open Board Device
                if (globals.AllDeviceRes[s8DspModID].bOpenFlag == false) //board not open
                {
                    fixed (DeviceID_t* pBoardDev = &globals.AllDeviceRes[s8DspModID].deviceID)
                    {
                        DJAcsApiDef.XMS_ctsOpenDevice(globals.g_acsHandle, pBoardDev, null);
                    }
                }

                //Open Voc Device
                for (int j = 0; j < globals.AllDeviceRes[s8DspModID].lVocFreeNum; j++)
                {
                    if (globals.AllDeviceRes[s8DspModID].pVoice[j].State == DJDemoGlobals.VOICE_STATE.VOC_WAITOPEN)
                    {
                        fixed (DeviceID_t* pVocDev = &globals.AllDeviceRes[s8DspModID].pVoice[j].deviceID)
                        {
                            DJAcsApiDef.XMS_ctsOpenDevice(globals.g_acsHandle, pVocDev, null);
                        }
                    }
                }

                // Open Trunk Device
                for (int j = 0; j < globals.AllDeviceRes[s8DspModID].lTrunkNum; j++)
                {
                    if (globals.AllDeviceRes[s8DspModID].pTrunk[j].State == DJDemoGlobals.TRUNK_STATE.TRK_WAITOPEN)
                    {
                        fixed (DeviceID_t* pTukDev = &globals.AllDeviceRes[s8DspModID].pTrunk[j].deviceID)
                        {
                            DJAcsApiDef.XMS_ctsOpenDevice(globals.g_acsHandle, pTukDev, null);
                        }
                    }
                }

                // Open Pcm Device
                for (int j = 0; j < globals.AllDeviceRes[s8DspModID].lPcmNum; j++)
                {
                    if (globals.AllDeviceRes[s8DspModID].pPcm[j].bOpenFlag == false)
                    {
                        fixed (DeviceID_t* pPcmDev = &globals.AllDeviceRes[s8DspModID].pPcm[j].deviceID)
                        {
                            DJAcsApiDef.XMS_ctsOpenDevice(globals.g_acsHandle, pPcmDev, null);
                        }
                    }
                }
            }
        }

        public unsafe void Remove_OneDsp()
        {
            if (listView_Count.SelectedItems.Count == 0)
            {
                MessageBox.Show("Please select a valid DSP module in the upper list!");
                return;
            }

            int nNumOfSelected = listView_Count.SelectedIndices[0];

            if (nNumOfSelected <= 0 || nNumOfSelected > globals.g_iTotalModule)
            {
                MessageBox.Show("Please select a valid DSP module in the upper list!");
                return;
            }

            sbyte s8ModuleID = globals.MapTable_Module[nNumOfSelected - 1]; // 0行是Total
            globals.AllDeviceRes[s8ModuleID].RemoveState = DJDemoGlobals.REMOVE_STATE.DSP_REMOVE_STATE_START;
            DrawCount_RemoveState(s8ModuleID);

            for (int i = 0; i < globals.AllDeviceRes[s8ModuleID].lTrunkNum; i++)
            {
                fixed (DJDemoGlobals.TRUNK_STRUCT* pOneTrunk = &globals.AllDeviceRes[s8ModuleID].pTrunk[i])
                {
                    if (pOneTrunk->State == DJDemoGlobals.TRUNK_STATE.TRK_FREE)
                    {
                        Change_State(pOneTrunk, DJDemoGlobals.TRUNK_STATE.TRK_WAIT_REMOVE);
                    }
                }
            }

            for (int i = 0; i < globals.AllDeviceRes[s8ModuleID].lVocNum; i++)
            {
                fixed (DJDemoGlobals.VOICE_STRUCT* pOneVoc = &globals.AllDeviceRes[s8ModuleID].pVoice[i])
                {
                    if (pOneVoc->State == DJDemoGlobals.VOICE_STATE.VOC_FREE)
                    {
                        Change_Voc_State(pOneVoc, DJDemoGlobals.VOICE_STATE.VOC_WAIT_REMOVE);
                    }
                }
            }
            CheckRemoveReady(s8ModuleID);
        }

        private void Btn_ReOpen_Click(object sender, EventArgs e)
        {
            ReOpen_AllDevice();
        }

        private void BtnForRemove_Click(object sender, EventArgs e)
        {
            Remove_OneDsp();
        }
    }

    public class DJDemoGlobals
    {
        #region Res Define
        public enum TRUNK_STATE
        {
            TRK_WAITOPEN,
            TRK_FREE,
            TRK_WELCOME,
            TRK_ACCOUNT,
            TRK_PASSWORD,
            TRK_SELECT,
            TRK_PLAYRESULT,
            TRK_RECORDFILE,
            TRK_PLAYRECORD,
            TRK_HANGON,

            // new add for XMS
            TRK_WAIT_ANSWERCALL,
            TRK_WAIT_LINKOK,

            TRK_WAIT_REMOVE,
        };

        public enum VOICE_STATE
        {
            VOC_WAITOPEN,
            VOC_FREE,
            VOC_USED,

            VOC_WAIT_REMOVE
        };

        public enum DEVICE_CALL_STATE
        {
            /////////////// 通用呼叫状态定义 //////////////////////////////////////////////////////////////////
            DEVICE_COMMON_STATE_START = 0x0000, // 通用状态开始识别号: TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR
            DCS_FREE = 0x0001, // 空闲状态(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
            DCS_LOCAL_BLOCK = 0x0002, // 本地阻塞(TUP,ISUP)
            DCS_REMOTE_BLOCK = 0x0003, // 远端阻塞(TUP,ISUP)
            DCS_BLOCK = 0x0004, // 本地和远端阻塞(ISUP)
            DCS_UNAVAILABLE = 0x0005, // 不可用(TUP,ISUP,PRI)

            DCS_CALLOUT = 0x0006, // 开始呼出(TUP,ISUP,PRI,VOIP,ANA_TRK)
            DCS_CALLIN = 0x0007, // 呼叫进入(TUP,ISUP,PRI,VOIP,ANA_TRK)
            DCS_ALERTING = 0x0008, // 地址收齐对用户振铃等(TUP,ISUP)

            DCS_CONNECT = 0x0009, // 连通(不分主被叫方式)(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)

            DCS_DISCONNECT = 0x000A, // 收到拆线(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
            DCS_WAIT_FREE = 0x000B, // 对拆线的响应(TUP,ISUP,PRI,VOIP)
        }

        public unsafe struct TRUNK_STRUCT
        {
            public DeviceID_t deviceID;
            public int iSeqID;
            public int iModSeqID;
            public int iLineState;

            public DeviceID_t VocDevID;
            public byte u8PlayTag;

            public TRUNK_STATE State;

            public int DtmfCount;
            public fixed sbyte DtmfBuf[32];

            public fixed sbyte CallerCode[20];
            public fixed sbyte CalleeCode[20];
        };

        public struct VOICE_STRUCT
        {
            public DeviceID_t deviceID;
            public int iSeqID;

            public DeviceID_t UsedDevID;

            public VOICE_STATE State;
        };

        public struct PCM_STRUCT
        {
            public DeviceID_t deviceID;
            public int iSeqID;
            public bool bOpenFlag;		// OpenDevice成功的标志

            public byte u8E1Type;
            public int s32AlarmVal;
        };

        public enum REMOVE_STATE
        {
            DSP_REMOVE_STATE_NONE,
            DSP_REMOVE_STATE_START,
            DSP_REMOVE_STATE_READY
        };

        public struct TYPE_XMS_DSP_DEVICE_RES_DEMO
        {
            public long lFlag;				// 本DSP是否存在, 0：不存在，1：存在

            public DeviceID_t deviceID;		// 本DSP模块的deviceID
            public int iSeqID;			    // 本DSP模块的顺序号
            public bool bOpenFlag;		    // OpenDevice成功的标志
            public bool bErrFlag;		    // 发生过CloseDevice事件的标志
            public REMOVE_STATE RemoveState;// 停止DSP硬件的标志

            public long lVocNum;			// 该DSP上的ACS_DEVMAIN_VOICE数量
            public long lVocOpened;			// 该DSP上OpenDevice成功的VOICE数量
            public long lVocFreeNum;		// 该DSP上可用的VOICE数量
            public VOICE_STRUCT[] pVoice;	// 根据需要，分配相应的结构

            public long lPcmNum;			// 该DSP上的ACS_DEVMAIN_DIGITAL_PORT数量
            public long lPcmOpened;			// 该DSP上OpenDevice成功的Pcm数量
            public PCM_STRUCT[] pPcm;		// 根据需要，分配相应的结构

            public long lTrunkNum;			// 该DSP上的ACS_DEVMAIN_INTERFACE_CH数量
            public long lTrunkOpened;		// 该DSP上OpenDevice成功的Trunk数量
            public TRUNK_STRUCT[] pTrunk;	// 根据需要，分配相应的结构
        };

        #endregion

        #region Config

        public unsafe void CharsToSBytes(char[] chSrc, sbyte* byDst, int size)
        {
            int i = 0;
            for (i = 0; i < size && chSrc[i] != '\0'; ++i)
            {
                byDst[i] = (sbyte)chSrc[i];
            }
            byDst[i] = (sbyte)'\0';
        }

        public unsafe void SBytesToChars(sbyte* bySrc, char[] chDst, int nLen)
        {
            int i = 0;
            for (i = 0; bySrc[i] != (sbyte)'\0' && i < nLen; ++i)
            {
                chDst[i] = (char)bySrc[i];
            }
            chDst[i] = '\0';
        }

        public struct TYPE_CHANNEL_MAP_TABLE
        {
            public sbyte     m_s8ModuleID;    /*device module type*/
            public short     m_s16ChannelID;  /*device chan id*/
        };
        public unsafe void ReadFromConfig()
        {
            ClsIniFile clsIniFile = new ClsIniFile(".\\XMS_Demo.INI");

            StringBuilder strBlderTemp = new StringBuilder(256);
            clsIniFile.GetFileString("ConfigInfo", "IpAddr", "192.168.10.75", strBlderTemp, 256);
            string strTemp = strBlderTemp.ToString();
            fixed (sbyte* p = cfg_ServerID.m_s8ServerIp)
            {
                CharsToSBytes(strTemp.ToCharArray(), p, strTemp.Length);
            }
            cfg_ServerID.m_u32ServerPort = (uint)clsIniFile.GetFileInt("ConfigInfo", "Port", 9000);
            clsIniFile.GetFileString("ConfigInfo", "UserName", "", strBlderTemp, 256);

            strTemp = null;

            strTemp = strBlderTemp.ToString();
            fixed (sbyte* p = cfg_ServerID.m_s8UserName)
            {
                CharsToSBytes(strTemp.ToCharArray(), p, strTemp.Length);
            }
            clsIniFile.GetFileString("ConfigInfo", "PassWord", "", strBlderTemp, 256);

            strTemp = null;

            strTemp = strBlderTemp.ToString();
            fixed (sbyte* p = cfg_ServerID.m_s8UserPwd)
            {
                CharsToSBytes(strTemp.ToCharArray(), p, strTemp.Length);
            }

            clsIniFile.GetFileString("ConfigInfo", "VocPath", "", strBlderTemp, 256);
            cfg_VocPath = strBlderTemp.ToString();
            cfg_iDispChnl = (int)clsIniFile.GetFileInt("ConfigInfo", "DispChnl", 32);
            cfg_iVoiceRule = (int)clsIniFile.GetFileInt("ConfigInfo", "VoiceRule", 1);

            cfg_iPartWork = clsIniFile.GetFileInt("ConfigInfo", "PartWork", 0);
            cfg_iPartWorkModuleID = clsIniFile.GetFileInt("ConfigInfo", "PartWorkModuleID", 0);
            cfg_s32DebugOn = clsIniFile.GetFileInt("ConfigInfo", "DebugOn", 0);

            strBlderTemp = null;
            strTemp = null;
        }

        public unsafe void WriteToConfig()
        {
            ClsIniFile clsIniFile = new ClsIniFile(".\\XMS_Demo.INI");

            string strTemp = new string('\0', 0);
            char[] chTemp = new char[66];
            
            chTemp.Initialize();
            fixed (sbyte* p = cfg_ServerID.m_s8ServerIp)
            {
                SBytesToChars(p, chTemp, 32);
            }
            strTemp = new string(chTemp);
            clsIniFile.WriteFileString("ConfigInfo", "IpAddr", strTemp);

            strTemp = null;

            strTemp = cfg_ServerID.m_u32ServerPort.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "Port", strTemp);

            clsIniFile.WriteFileString("ConfigInfo", "VocPath", cfg_VocPath);

            strTemp = null;

            strTemp = cfg_iDispChnl.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "DispChnl", strTemp);

            strTemp = null;

            strTemp = cfg_iVoiceRule.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "VoiceRule", strTemp);

            strTemp = null;

            strTemp = cfg_iPartWork.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "PartWork", strTemp);

            strTemp = null;

            strTemp = cfg_iPartWorkModuleID.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "PartWorkModuleID", strTemp);

            strTemp = null;

            strTemp = cfg_s32DebugOn.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "DebugOn", strTemp);

            strTemp = null;
            chTemp = null;
        }
        #endregion

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

                case XMS_EVT_TYPE.XMS_EVT_UNIFAILURE: return "UNIFAILURE";
            }

            return "UNKNOWN";
        }
        public const int MAX_DSP_MODULE_NUMBER_OF_XMS = 256;

        public TYPE_XMS_DSP_DEVICE_RES_DEMO[] AllDeviceRes = new TYPE_XMS_DSP_DEVICE_RES_DEMO[MAX_DSP_MODULE_NUMBER_OF_XMS];
        public int g_iTotalModule = 0;

        public sbyte[] MapTable_Module = new sbyte[MAX_DSP_MODULE_NUMBER_OF_XMS];

        public int g_iTotalPcm = 0;
        public int g_iTotalPcmOpened = 0;
        public TYPE_CHANNEL_MAP_TABLE[] MapTable_Pcm = new TYPE_CHANNEL_MAP_TABLE[64];

        public int g_iTotalTrunk = 0;
        public int g_iTotalTrunkOpened = 0;
        public TYPE_CHANNEL_MAP_TABLE[] MapTable_Trunk = new TYPE_CHANNEL_MAP_TABLE[2048];

        public int g_iTotalUser = 0;
        public int g_iTotalUserOpened = 0;
        public TYPE_CHANNEL_MAP_TABLE[] MapTable_User = new TYPE_CHANNEL_MAP_TABLE[2048];

        public int g_iTotalVoice = 0;
        public int g_iTotalVoiceOpened = 0;
        public int g_iTotalVoiceFree = 0;

        public string cfg_CallingNum;
        public string cfg_SimCalledNum;
        public string cfg_VocPath;
        public ServerID_t cfg_ServerID;
        public int cfg_iCalledLen;
        public int cfg_iPartWork;
        public int cfg_iPartWorkModuleID;
        public int cfg_s32DebugOn;
        public int cfg_iCallOutRule;
        public int cfg_iVoiceRule;		// search voice in Fix Relationship
        public int cfg_iDispChnl;

        public TYPE_CHANNEL_MAP_TABLE[] MapTable_Voice = new TYPE_CHANNEL_MAP_TABLE[2048];

        public UInt32 nNumOfListBoxItem = 0; //ListBox界面显示的消息数目

        public CmdParamData_CAS_t g_Param_CAS = new CmdParamData_CAS_t();
        public TYPE_ANALOG_GTD_PARAM g_Param_Analog;

        public uint g_acsHandle = 0;

        public DJDemoGlobals() //constructor
        {
            AllDeviceRes.Initialize();
            MapTable_Module.Initialize();
            MapTable_Pcm.Initialize();
            MapTable_Trunk.Initialize();
            MapTable_User.Initialize();
            MapTable_Voice.Initialize();
        }
    }
}
