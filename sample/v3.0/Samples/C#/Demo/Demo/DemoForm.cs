using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using DJKeygoe;
using System.Runtime.InteropServices;
using System.Threading;

namespace Demo
{
    public partial class DemoForm : Form
    {
        public DemoForm()
        {
            InitializeComponent();
        }

        public DJDemoGlobals globals = new DJDemoGlobals();
        public DJKeygoeIncludes.EsrFunc g_ESRFuncPtr;
        private unsafe void buttonInitSystem_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < DJDemoGlobals.MAX_DSP_MODULE_NUMBER_OF_XMS; ++i)
            {
                globals.AllDeviceRes[i].lFlag = 0;
            }
            globals.ReadFromConfig();
            fixed (DJKeygoeIncludes.CmdParamData_CAS_t* pCas = &globals.g_Param_CAS)
            {
                globals.CAS_Common_Cfg_ReadCfg(pCas);
            }

            int iResult = 0;
            fixed (DJKeygoeIncludes.ServerID_t* pStruct = &globals.iniConfigParam.cfg_ServerID)
            {
                fixed (int* pAcsHandle = &globals.g_acsHandle)
                {
                    iResult = axDJAcsAPI.AcsOpenStreamEx((int)pAcsHandle, (int)pStruct, 12, 64, 64, globals.iniConfigParam.cfg_s32DebugOn, 0);
                    if (iResult == DJKeygoeIncludes.ACSPOSITIVE_ACK)
                    {
                        listBox_OptAndEvtInfo.Items.Add("AcsOpenStreamEx Success");
                    }
                    else
                    {
                        listBox_OptAndEvtInfo.Items.Add("AcsOpenStreamEx Fail");
                    }
                }
            }

            g_ESRFuncPtr = new DJKeygoeIncludes.EsrFunc(EvtHandler);
            iResult = axDJAcsAPI.AcsSetESREx(globals.g_acsHandle,
                System.Runtime.InteropServices.Marshal.GetFunctionPointerForDelegate(g_ESRFuncPtr).ToInt32(), 0, 1);

            if (iResult == DJKeygoeIncludes.ACSPOSITIVE_ACK)
            {
                listBox_OptAndEvtInfo.Items.Add("AcsSetESREx Success");
            }
            else
            {
                listBox_OptAndEvtInfo.Items.Add("AcsSetESREx Fail");
            }

            iResult = axDJAcsAPI.AcsGetDeviceListEx(globals.g_acsHandle, 0);
            if (iResult == DJKeygoeIncludes.ACSPOSITIVE_ACK)
            {
                listBox_OptAndEvtInfo.Items.Add("AcsGetDeviceListEx Success");
            }
            else
            {
                listBox_OptAndEvtInfo.Items.Add("AcsGetDeviceListEx Fail");
            }

            buttonInitSystem.Enabled = false;
        }

        private void buttonExitSystem_Click(object sender, EventArgs e)
        {
            int iResult = 0;
            iResult = axDJAcsAPI.AcsCloseStream(globals.g_acsHandle, ref iResult);
            if (iResult == DJKeygoeIncludes.ACSPOSITIVE_ACK)
            {
                listBox_OptAndEvtInfo.Items.Add("AcsCloseStreamEx Success");
            }
            else
            {
                listBox_OptAndEvtInfo.Items.Add("AcsCloseStreamEx Fail");
            }

            buttonInitSystem.Enabled = true;
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

        #region Contrl Show Informations
        delegate void ShowEvtInfoCallback(string text);
        public void ShowEvtInfo(string strInfo)
        {
            if (this.listBox_OptAndEvtInfo.InvokeRequired)
            {
                ShowEvtInfoCallback d = new ShowEvtInfoCallback(ShowEvtInfo);
                this.Invoke(d, new object[] { strInfo });
            }
            else
            {
                this.listBox_OptAndEvtInfo.Items.Add(strInfo);
            }
        }

        delegate void AddTrunkListItemsCallback(int iIDSum);
        public void AddTrunkListItems(int iIDSum)
        {
            if (this.listView_InterfInfo.InvokeRequired)
            {
                AddTrunkListItemsCallback d = new AddTrunkListItemsCallback(AddTrunkListItems);
                this.Invoke(d, new object[] { iIDSum });
            }
            else
            {
                int iModID = iIDSum / 1000;
                int iChID = iIDSum % 1000;
                ListViewItem listItem = this.listView_InterfInfo.Items.Add(listView_InterfInfo.Items.Count.ToString());
                globals.AllDeviceRes[iModID].pTrunk[iChID].iSeqID = listItem.Index;
                listItem.Name = iIDSum.ToString();
                listItem.SubItems.Add(iModID.ToString());
                listItem.SubItems.Add(iChID.ToString());
                switch ((DJKeygoeIncludes.XMS_INTERFACE_DEVSUB_TYPE)globals.AllDeviceRes[iModID].pTrunk[iChID].deviceID.m_s16DeviceSub)
                {
                    case DJKeygoeIncludes.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER:
                        listItem.SubItems.Add("USER");
                        break;

                    case DJKeygoeIncludes.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK:
                        listItem.SubItems.Add("ATRUNK");
                        break;

                    default:
                        listItem.SubItems.Add("DTRUNK");
                        break;
                }
                listItem.SubItems.Add("WAIT OPEN");
                listItem.SubItems.Add("WAIT OPEN");
                listItem.SubItems.Add("");
                listItem.SubItems.Add("");
                listItem.SubItems.Add("");
                listItem.SubItems.Add("");
                listItem.SubItems.Add("");
            }
        }

        delegate void ShowTrunkListItemsCallback(int iIDSum);
        public unsafe void ShowTrunkListItems(int iIDSum)
        {
            if (this.listView_InterfInfo.InvokeRequired)
            {
                ShowTrunkListItemsCallback d = new ShowTrunkListItemsCallback(ShowTrunkListItems);
                this.Invoke(d, new object[] { iIDSum });
            }
            else
            {
                int iDspModID = iIDSum / 1000;
                int iChID = iIDSum % 1000;

                int iItem = globals.AllDeviceRes[iDspModID].pTrunk[iChID].iSeqID;

                // 4
                switch ((DJDemoGlobals.TRUNK_STATE)globals.AllDeviceRes[iDspModID].pTrunk[iChID].State)
                {
                    case DJDemoGlobals.TRUNK_STATE.TRK_ACCOUNT:
                        listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_ACCOUNT";
                        break;

                    case DJDemoGlobals.TRUNK_STATE.TRK_FREE:
                        listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_FREE";
                        break;

                    case DJDemoGlobals.TRUNK_STATE.TRK_HANGON:
                        listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_HANGON";
                        break;

                    case DJDemoGlobals.TRUNK_STATE.TRK_PASSWORD:
                        listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_PASSWORD";
                        break;

                    case DJDemoGlobals.TRUNK_STATE.TRK_PLAYRECORD:
                        listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_PLAYRECORD";
                        break;

                    case DJDemoGlobals.TRUNK_STATE.TRK_PLAYRESULT:
                        listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_PLAYRESULT";
                        break;

                    case DJDemoGlobals.TRUNK_STATE.TRK_RECORDFILE:
                        listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_RECORDFILE";
                        break;

                    case DJDemoGlobals.TRUNK_STATE.TRK_SELECT:
                        listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_SELECT";
                        break;

                    case DJDemoGlobals.TRUNK_STATE.TRK_WAIT_ANSWERCALL:
                        listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_WAIT_ANSWERCALL";
                        break;

                    case DJDemoGlobals.TRUNK_STATE.TRK_WAIT_LINKOK:
                        listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_WAIT_LINKOK";
                        break;

                    case DJDemoGlobals.TRUNK_STATE.TRK_WAIT_REMOVE:
                        listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_WAIT_REMOVE";
                        break;

                    case DJDemoGlobals.TRUNK_STATE.TRK_WAITOPEN:
                        listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_SIM_CALLOUT";
                        break;

                    case DJDemoGlobals.TRUNK_STATE.TRK_WELCOME:
                        listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_WAIT_REMOVE";
                        break;

                    default:
                        listView_InterfInfo.Items[iItem].SubItems[4].Text = "UNKNOWN";
                        break;
                }

                // 5
                switch ((DJDemoGlobals.DEVICE_CALL_STATE)globals.AllDeviceRes[iDspModID].pTrunk[iChID].iLineState)
                {
                    case DJDemoGlobals.DEVICE_CALL_STATE.DCS_ALERTING:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_ALERTING";
                        break;

                    case DJDemoGlobals.DEVICE_CALL_STATE.DCS_BLOCK:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_BLOCK";
                        break;

                    case DJDemoGlobals.DEVICE_CALL_STATE.DCS_CALLIN:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_CALLIN";
                        break;

                    case DJDemoGlobals.DEVICE_CALL_STATE.DCS_CALLOUT:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_CALLOUT";
                        break;

                    case DJDemoGlobals.DEVICE_CALL_STATE.DCS_CONNECT:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_CONNECT";
                        break;

                    case DJDemoGlobals.DEVICE_CALL_STATE.DCS_DISCONNECT:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_DISCONNECT";
                        break;

                    case DJDemoGlobals.DEVICE_CALL_STATE.DCS_FREE:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_FREE";
                        break;

                    case DJDemoGlobals.DEVICE_CALL_STATE.DCS_LOCAL_BLOCK:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_LOCAL_BLOCK";
                        break;

                    case DJDemoGlobals.DEVICE_CALL_STATE.DCS_REMOTE_BLOCK:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_REMOTE_BLOCK";
                        break;

                    case DJDemoGlobals.DEVICE_CALL_STATE.DCS_UNAVAILABLE:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_UNAVAILABLE";
                        break;

                    case DJDemoGlobals.DEVICE_CALL_STATE.DCS_WAIT_FREE:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_WAIT_FREE";
                        break;

                    case DJDemoGlobals.DEVICE_CALL_STATE.DEVICE_COMMON_STATE_START:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DEVICE_COMMON_STATE_START";
                        break;

                    default:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "UNKNOWN";
                        break;
                }

                // 6 7 8
                fixed (char* pStr1 = globals.AllDeviceRes[iDspModID].pTrunk[iChID].CallerCode)
                {
                    string strCaller = new string(pStr1);
                    listView_InterfInfo.Items[iItem].SubItems[6].Text = strCaller;
                }
                fixed (char* pStr2 = globals.AllDeviceRes[iDspModID].pTrunk[iChID].CalleeCode)
                {
                    string strCallee = new string(pStr2);
                    listView_InterfInfo.Items[iItem].SubItems[7].Text = strCallee;
                }
                fixed (char* pStr3 = globals.AllDeviceRes[iDspModID].pTrunk[iChID].DtmfBuf)
                {
                    pStr3[globals.AllDeviceRes[iDspModID].pTrunk[iChID].DtmfCount] = '\0';
                    string strDtmf = new string(pStr3);
                    listView_InterfInfo.Items[iItem].SubItems[8].Text = strDtmf;
                }

                // 9
                listView_InterfInfo.Items[iItem].SubItems[9].Text = "";

                // 10
                if (globals.AllDeviceRes[iDspModID].pTrunk[iChID].VocDevID.m_s8ModuleID > 0)
                {
                    string strVocDevInfo = globals.AllDeviceRes[iDspModID].pTrunk[iChID].VocDevID.m_s8ModuleID.ToString() + "." +
                        globals.AllDeviceRes[iDspModID].pTrunk[iChID].VocDevID.m_s16ChannelID.ToString();
                    listView_InterfInfo.Items[iItem].SubItems[10].Text = strVocDevInfo;
                }
                else
                {
                    listView_InterfInfo.Items[iItem].SubItems[10].Text = "";
                }
            }
        }
        #endregion

        #region Keygoe Work Codes
        public unsafe void My_DualLink(DJKeygoeIncludes.DeviceID_t* pDev1, DJKeygoeIncludes.DeviceID_t* pDev2)
        {
            axDJAcsAPI.CtsLinkDeviceEx(globals.g_acsHandle, (int)pDev1, (int)pDev2, 0);
            axDJAcsAPI.CtsLinkDeviceEx(globals.g_acsHandle, (int)pDev2, (int)pDev1, 0);
        }

        public unsafe void My_DualUnlink(DJKeygoeIncludes.DeviceID_t* pDev1, DJKeygoeIncludes.DeviceID_t* pDev2)
        {
            axDJAcsAPI.CtsUnlinkDeviceEx(globals.g_acsHandle, (int)pDev1, (int)pDev2, 0);
            axDJAcsAPI.CtsUnlinkDeviceEx(globals.g_acsHandle, (int)pDev2, (int)pDev1, 0);
        }

        public unsafe int FreeOneFreeVoice(DJKeygoeIncludes.DeviceID_t* pFreeVocDeviceID)
        {
            int iResult = -1;
            if (globals.AllDeviceRes[pFreeVocDeviceID->m_s8ModuleID].lFlag == 1)
            {
                globals.AllDeviceRes[pFreeVocDeviceID->m_s8ModuleID].pVoice[pFreeVocDeviceID->m_s16ChannelID].State = DJDemoGlobals.VOICE_STATE.VOC_FREE;
                ++globals.AllDeviceRes[pFreeVocDeviceID->m_s8ModuleID].lVocFreeNum;

                iResult = 0;		// OK
            }

            return iResult;			// invalid VocDeviceID
        }

        public unsafe int FreeOneFreeVoice(int iModID, int iChID)
        {
            int iResult = -1;
            if (globals.AllDeviceRes[iModID].lFlag == 1)
            {
                globals.AllDeviceRes[iModID].pVoice[iChID].State = DJDemoGlobals.VOICE_STATE.VOC_FREE;
                ++globals.AllDeviceRes[iModID].lVocFreeNum;

                iResult = 0;		// OK
            }

            return iResult;			// invalid VocDeviceID
        }

        public unsafe void InitTrunkChannel(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk)
        {
            pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_FREE;

            pOneTrunk->CallerCode[0] = (char)0;
            pOneTrunk->CalleeCode[0] = (char)0;

            pOneTrunk->DtmfBuf[0] = (char)0;
            pOneTrunk->DtmfCount = 0;

            memset(&pOneTrunk->VocDevID, 0, sizeof(DJKeygoeIncludes.DeviceID_t));		// 0: didn't alloc Voc Device
        }

        public unsafe DJKeygoeIncludes.DeviceID_t* SearchOneFreeVoice(DJDemoGlobals.TRUNK_STRUCT *pOneTrunk)
        {
            DJKeygoeIncludes.DeviceID_t *pFreeVocDeviceID = null;
            SByte			s8ModID = pOneTrunk->deviceID.m_s8ModuleID;

            if (globals.iniConfigParam.cfg_iVoiceRule == 0)			// Fix relationship between Trunk & Voice
            {
                Int16 s16ChID = pOneTrunk->deviceID.m_s16ChannelID;
                int i = s16ChID;// pOneTrunk->iModSeqID;
                if (i < globals.AllDeviceRes[s8ModID].lVocNum)
                {
                    fixed (DJDemoGlobals.VOICE_STRUCT* pOneVoice = &globals.AllDeviceRes[s8ModID].pVoice[i])
                    {
                        if (pOneVoice->State != DJDemoGlobals.VOICE_STATE.VOC_WAITOPEN)
                        {
                            pFreeVocDeviceID = &pOneVoice->deviceID;

                            // use this voice device 
                            globals.AllDeviceRes[pFreeVocDeviceID->m_s8ModuleID].pVoice[pFreeVocDeviceID->m_s16ChannelID].State = DJDemoGlobals.VOICE_STATE.VOC_USED;
                            --globals.AllDeviceRes[s8ModID].lVocFreeNum;
                        }
                    }
                }

                return pFreeVocDeviceID;
            }

            SByte s8SearchModID;
            long lNowMostFreeNum;
            if (globals.iniConfigParam.cfg_iVoiceRule == 1)			// Search in Same Module
            {
                s8SearchModID = s8ModID;
            }
            else		// Search in Most free resource module
            {
                s8SearchModID = -1;
                lNowMostFreeNum = -1;
                for (int i = 0; i < DJDemoGlobals.MAX_DSP_MODULE_NUMBER_OF_XMS; ++i)
                {
                    if (globals.AllDeviceRes[i].lFlag != 0 && globals.AllDeviceRes[i].lVocFreeNum > lNowMostFreeNum)
                    {
                        s8SearchModID = (SByte)i;
                        lNowMostFreeNum = globals.AllDeviceRes[i].lVocFreeNum;
                    }
                }
            }

            for (int i = 0; i < globals.AllDeviceRes[s8SearchModID].lVocNum; ++i)
            {
                fixed (DJDemoGlobals.VOICE_STRUCT* pOneVoice = &globals.AllDeviceRes[s8SearchModID].pVoice[i])
                {
                    if (pOneVoice->State == DJDemoGlobals.VOICE_STATE.VOC_FREE)
                    {
                        pFreeVocDeviceID = &pOneVoice->deviceID;

                        // user this voice device 
                        globals.AllDeviceRes[pFreeVocDeviceID->m_s8ModuleID].pVoice[pFreeVocDeviceID->m_s16ChannelID].State = DJDemoGlobals.VOICE_STATE.VOC_USED;
                        --globals.AllDeviceRes[s8ModID].lVocFreeNum;
                        break;
                    }
                }
            }

            return pFreeVocDeviceID;
        }

        public unsafe void SetGtD_AnalogTrunk(DJKeygoeIncludes.DeviceID_t* pDevId)
        {
	        /*//========Set GTG Begin========
	        CmdParamData_Voice_t cmdVoc;
	        memset(&cmdVoc,0,sizeof(cmdVoc));
	        cmdVoc.m_u8GtdCtrlValid = 1 ;						//Enable GTD
	        cmdVoc.m_VocGtdControl.m_u8ChannelEnable = 1;		//Enable Gtd channel
	        cmdVoc.m_VocGtdControl.m_u8DTMFEnable = 1;			// Detect DTMF
	        cmdVoc.m_VocGtdControl.m_u8GTDEnable = 1;			// Detect GTD 
	        cmdVoc.m_VocGtdControl.m_u8FSKEnable = 1;			// Detect FSK for receive CallerID

	        cmdVoc.m_VocGtdControl.m_u8EXTEnable = 0x2;		// Enable PVD Detect

	        strcpy((char*)&cmdVoc.m_VocGtdControl.m_u8GTDID[0],"GHIJK");	// Detect Busy Tone

	        DJ_U16 u16ParamType = VOC_PARAM_UNIPARAM;
	        DJ_U16 u16ParamSize = sizeof(cmdVoc);
	        void* p = (void*) &cmdVoc;

	        int r = XMS_ctsSetParam( g_acsHandle,pDevId,u16ParamType,u16ParamSize,(void*)p);
	        char szbuffer[1024];
	        memset(szbuffer,0,sizeof(szbuffer));
	        sprintf(szbuffer,"Set GTD ret = %d\n",r);
	        AddMsg ( szbuffer );

	        //========Set GTG End  ========*/
        }

        // Search Free Voice for get CallerID(FSK)
        public unsafe void PrepareForCallerID(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk)
        {
            if (pOneTrunk->deviceID.m_s16DeviceSub != (short)DJKeygoeIncludes.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
                return;

            DJKeygoeIncludes.DeviceID_t *pFreeVocDeviceID = SearchOneFreeVoice(pOneTrunk);
            if (pFreeVocDeviceID != null)
            {
                pOneTrunk->VocDevID = *pFreeVocDeviceID;

                globals.AllDeviceRes[pFreeVocDeviceID->m_s8ModuleID].pVoice[pFreeVocDeviceID->m_s16ChannelID].UsedDevID = pOneTrunk->deviceID;

                My_DualLink(pFreeVocDeviceID, &pOneTrunk->deviceID);
                SetGtD_AnalogTrunk(pFreeVocDeviceID);
            }
        }

        public unsafe void ResetTrunk(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk, DJKeygoeIncludes.Acs_Evt_t* pAcsEvt)
        {
            StopPlayFile(&pOneTrunk->VocDevID);

            // free the used Voice Resource
            if (pOneTrunk->VocDevID.m_s16DeviceMain != 0)
            {
                My_DualUnlink(&pOneTrunk->VocDevID, &pOneTrunk->deviceID);

                FreeOneFreeVoice(&pOneTrunk->VocDevID);

                fixed(DJKeygoeIncludes.DeviceID_t *pUsedDev = 
                    &globals.AllDeviceRes[pOneTrunk->VocDevID.m_s8ModuleID].pVoice[pOneTrunk->VocDevID.m_s16ChannelID].UsedDevID)
                {
                    memset(pUsedDev, 0, sizeof(DJKeygoeIncludes.DeviceID_t));		// 0: didn't alloc Device
                }
                memset(&pOneTrunk->VocDevID, 0, sizeof(DJKeygoeIncludes.DeviceID_t));		// 0: didn't alloc Device
            }

            InitTrunkChannel(pOneTrunk);

            // Search Free Voice for get CallerID(FSK)
            // if you needn't CallerID, ignore next line
            PrepareForCallerID(pOneTrunk);
        }

        public unsafe sbyte *My_GetGtdCode(DJKeygoeIncludes.Acs_Evt_t* pAcsEvt)
        {
            DJKeygoeIncludes.Acs_IO_Data* pIOData = null;
            sbyte* p = null;

            if (pAcsEvt->m_s32EventType == (int)DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_RECVIODATA)	/*IO Data Event*/
            {
                pIOData = (DJKeygoeIncludes.Acs_IO_Data*)((byte*)pAcsEvt + sizeof(DJKeygoeIncludes.Acs_Evt_t));

                if ((pIOData->m_u16IoType == (ushort)DJKeygoeIncludes.XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_GTG)
                    && (pIOData->m_u16IoDataLen > 0))
                {
                    p = (sbyte*)((byte*)pIOData + sizeof(DJKeygoeIncludes.Acs_IO_Data));

                    return p;
                }
            }

            return null;	// not a good GTD
        }

        public unsafe sbyte* My_GetFskCode(DJKeygoeIncludes.Acs_Evt_t* pAcsEvt)
        {
            DJKeygoeIncludes.Acs_IO_Data* pIOData = null;
            sbyte* p = null;

            //if (pAcsEvt->m_s32EventType == (int)DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_RECVIODATA)	/*IO Data Evemt*/
            if ((DJKeygoeIncludes.XMS_EVT_TYPE)pAcsEvt->m_s32EventType == DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_RECVIODATA)	//modify by lmy 20120321
            {
                pIOData = (DJKeygoeIncludes.Acs_IO_Data*)((byte*)pAcsEvt + sizeof(DJKeygoeIncludes.Acs_Evt_t));

                if ((pIOData->m_u16IoType == (ushort)DJKeygoeIncludes.XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_FSK)
                    && (pIOData->m_u16IoDataLen > 0))
                {
                    p = (sbyte*)((byte*)pIOData + sizeof(DJKeygoeIncludes.Acs_IO_Data));

                    return p;
                }
            }

            return null;	// not a good FSK
        }

        public unsafe sbyte* My_GetDtmfCode(DJKeygoeIncludes.Acs_Evt_t* pAcsEvt)
        {
            DJKeygoeIncludes.Acs_IO_Data* pIOData = null;
            sbyte* p = null;

            if (pAcsEvt->m_s32EventType == (int)DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_RECVIODATA)	/*IO Data Event*/
            {
                pIOData = (DJKeygoeIncludes.Acs_IO_Data*)((byte*)pAcsEvt + sizeof(DJKeygoeIncludes.Acs_Evt_t));

                if ((pIOData->m_u16IoType == (ushort)DJKeygoeIncludes.XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF)
                    && (pIOData->m_u16IoDataLen > 0))
                {
                    p = (sbyte*)((byte*)pIOData + sizeof(DJKeygoeIncludes.Acs_IO_Data));

                    return p;
                }
            }

            return null;	// not a good DTMF
        }

        public unsafe void My_InitDtmfBuf(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk)
        {
            pOneTrunk->DtmfCount = 0;
            pOneTrunk->DtmfBuf[0] = '\0';
        }

        public unsafe void My_AddDtmfBuf(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk, char TmpDtmf)
        {
            if (pOneTrunk->DtmfCount < (32 - 1))
            {
                pOneTrunk->DtmfBuf[pOneTrunk->DtmfCount] = TmpDtmf;
                pOneTrunk->DtmfBuf[pOneTrunk->DtmfCount + 1] = '\0';
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
        public unsafe void HandleMultiple(char* IDStr)
        {
            byte[] pSrc = new byte[80];
            int j;
            for (j = 0; IDStr[j] != '\0'; ++j)
            {
                pSrc[j] = (byte)IDStr[j];
            }
            pSrc[j] = 0;

	        int i = 0;
	        byte[] TmpIDStr = new byte[80];
	        byte c;

            fixed (byte* p = pSrc)
            {
                j = 0;
                while (p[j] != 0)
                {
                    c = p[j];
                    if ((c == 1) || (c == 2) || (c == 4) || (c == 7) || (c == 8))
                    {
                        j += 2;
                    }
                    else
                    {
                        TmpIDStr[i] = c;
                        ++i;
                        j += 1;
                    }
                }
                TmpIDStr[i] = 0;
            }

            for (j = 0; TmpIDStr[j] != 0; ++j)
            {
                IDStr[j] = (char)TmpIDStr[j];
            }
            IDStr[j] = '\0';
        }
        // end of multiple

        public unsafe int ConvertRawFskToCallerID(sbyte* RawFSKStr, char* IDStr, int IDStrBufLen)
        {
	        int			count;
	        int			i,j;
	        int			pos,len;
	        sbyte	ChkSum;

            count = strlen(RawFSKStr);
            IDStr[0] = '\0';

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
                IDStr[j] = (char)(RawFSKStr[i] & 0x7F);
                if (j == IDStrBufLen - 1)				// it will be overflow
                    break;
            }
	        IDStr[j] = '\0';

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
            if ((byte)RawFSKStr[pos] == 0x80)
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
        }

        public unsafe void SpecialForCas(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk, DJKeygoeIncludes.Acs_Evt_t* pAcsEvt)
        {
            if ((DJKeygoeIncludes.XMS_INTERFACE_DEVSUB_TYPE)pOneTrunk->deviceID.m_s16DeviceSub != DJKeygoeIncludes.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_CAS)
            {
                return;
            }

            if ((DJKeygoeIncludes.XMS_EVT_TYPE)pAcsEvt->m_s32EventType == DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_CAS_MFC_START)	/* 开始接收MFC，需要一个Voc设备*/
            {
                int iFreeVoc = SearchOneFreeVoice(pOneTrunk->deviceID.m_s8ModuleID);
                if (iFreeVoc >= 0)
                {
                    pOneTrunk->VocDevID = globals.AllDeviceRes[pOneTrunk->deviceID.m_s8ModuleID].pVoice[iFreeVoc].deviceID;
                    globals.AllDeviceRes[pOneTrunk->deviceID.m_s8ModuleID].pVoice[iFreeVoc].UsedDevID = pOneTrunk->deviceID;

                    globals.g_Param_CAS.m_VocDevID = pOneTrunk->VocDevID;
                    fixed (int* p = &globals.g_acsHandle)
                    {
                        DJKeygoeIncludes.DeviceID_t* pDev = &pOneTrunk->deviceID;
                        int pDevValue = (int)pDev;
                        fixed (DJKeygoeIncludes.CmdParamData_CAS_t* pParam = &globals.g_Param_CAS)
                        {
                            int pParamValue = (int)pParam;
                            int iLen = sizeof(DJKeygoeIncludes.CmdParamData_CAS_t);
                            axDJAcsAPI.CtsSetParamEx(globals.g_acsHandle, pDevValue, 0,
                                (short)iLen, pParamValue); // CAS_PARAM_UNIPARAM = 0
                        }
                    }
                }
            }

            if ((DJKeygoeIncludes.XMS_EVT_TYPE)pAcsEvt->m_s32EventType == DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_CAS_MFC_END)	// 接收MFC完毕，释放Voc设备
            {
                FreeOneFreeVoice(pOneTrunk->VocDevID.m_s8ModuleID, pOneTrunk->VocDevID.m_s16ChannelID);

                fixed(DJKeygoeIncludes.DeviceID_t *pDev = &globals.AllDeviceRes[pOneTrunk->VocDevID.m_s8ModuleID].pVoice[pOneTrunk->VocDevID.m_s16ChannelID].UsedDevID)
                {
                    memset(pDev, 0, sizeof(DJKeygoeIncludes.DeviceID_t));
                }
                memset(&pOneTrunk->VocDevID, 0, sizeof(DJKeygoeIncludes.DeviceID_t));
            }
        }

        public unsafe int PlayFile(DJKeygoeIncludes.DeviceID_t* pVocDevID, string FileName, byte u8PlayTag, bool bIsQueue)
        {
            DJKeygoeIncludes.PlayProperty_t playProperty = new DJKeygoeIncludes.PlayProperty_t();

            memset(&playProperty, 0, sizeof(DJKeygoeIncludes.PlayProperty_t));

            if (bIsQueue)
                playProperty.m_u16PlayType = (ushort)DJKeygoeIncludes.XMS_PLAY_TYPE.XMS_PLAY_TYPE_FILE_QUEUE;
            else
                playProperty.m_u16PlayType = (ushort)DJKeygoeIncludes.XMS_PLAY_TYPE.XMS_PLAY_TYPE_FILE;

            playProperty.m_u8TaskID = u8PlayTag;

            strcpy(playProperty.m_s8PlayContent, FileName);

            return axDJAcsAPI.CtsPlayEx(globals.g_acsHandle, (int)pVocDevID, (int)&playProperty, 0);
        }

        public unsafe int PlayIndex(DJKeygoeIncludes.DeviceID_t* pVocDevID, ushort u16Index, byte u8PlayTag, bool bIsQueue)
        {
            DJKeygoeIncludes.PlayProperty_t playProperty = new DJKeygoeIncludes.PlayProperty_t();

            memset(&playProperty, 0, sizeof(DJKeygoeIncludes.PlayProperty_t));

            if (bIsQueue)
                playProperty.m_u16PlayType = (ushort)DJKeygoeIncludes.XMS_PLAY_TYPE.XMS_PLAY_TYPE_INDEX_QUEUE;
            else
                playProperty.m_u16PlayType = (ushort)DJKeygoeIncludes.XMS_PLAY_TYPE.XMS_PLAY_TYPE_INDEX;

            playProperty.m_u8TaskID = u8PlayTag;

            playProperty.m_u16PlayIndex = u16Index;

            return axDJAcsAPI.CtsPlayEx(globals.g_acsHandle, (int)pVocDevID, (int)&playProperty, 0);
        }

        public unsafe int StopPlayFile(DJKeygoeIncludes.DeviceID_t* pVocDevID)
        {
            DJKeygoeIncludes.ControlPlay_t controlPlay;
            controlPlay.m_u16ControlType = (ushort)DJKeygoeIncludes.XMS_CTRL_PLAY_TYPE.XMS_STOP_PLAY;

            return axDJAcsAPI.CtsControlPlayEx(globals.g_acsHandle, (int)pVocDevID, (int)&controlPlay, 0);
        }

        public unsafe bool CheckPlayEnd(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk, DJKeygoeIncludes.Acs_Evt_t* pAcsEvt)
        {
            DJKeygoeIncludes.Acs_MediaProc_Data* pMediaData = null;

            if (pAcsEvt->m_s32EventType == (int)DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_PLAY)
            {
                pMediaData = (DJKeygoeIncludes.Acs_MediaProc_Data*)((byte*)pAcsEvt + sizeof(DJKeygoeIncludes.Acs_Evt_t));
                if (pMediaData->m_u8TaskID == pOneTrunk->u8PlayTag)
                    return true;
            }

            return false;
        }

        /* Stop Record */
        public unsafe int StopRecordFile(DJKeygoeIncludes.DeviceID_t* pVocDevID)
        {
            DJKeygoeIncludes.ControlRecord_t controlRecord = new DJKeygoeIncludes.ControlRecord_t();

            controlRecord.m_u32ControlType = (uint)DJKeygoeIncludes.XMS_CTRL_RECORD_TYPE.XMS_STOP_RECORD;

            return axDJAcsAPI.CtsControlRecordEx(globals.g_acsHandle, (int)pVocDevID, (int)&controlRecord, 0);
        }

        /* Handle Record */
        public unsafe int RecordFile(DJKeygoeIncludes.DeviceID_t* pVocDevID, string FileName, uint u32RecSize, bool bIsAppend)
        {
            DJKeygoeIncludes.RecordProperty_t recordProperty = new DJKeygoeIncludes.RecordProperty_t();

            memset(&recordProperty, 0, sizeof(DJKeygoeIncludes.RecordProperty_t));

            recordProperty.m_u32MaxSize = u32RecSize;

            if (bIsAppend)
                recordProperty.m_s8IsAppend = 1;
            else
                recordProperty.m_s8IsAppend = 0;

            strcpy(recordProperty.m_s8FileName, FileName);

            return axDJAcsAPI.CtsRecordEx(globals.g_acsHandle, (int)pVocDevID, (int)&recordProperty, 0);
        }

        public unsafe bool CheckRecordEnd(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk, DJKeygoeIncludes.Acs_Evt_t* pAcsEvt)
        {
            DJKeygoeIncludes.Acs_MediaProc_Data* pMediaData = null;

            if (pAcsEvt->m_s32EventType == (int)DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_RECORD)
            {
                return true;
            }

            return false;
        }

        public unsafe void TrunkWork(DJDemoGlobals.TRUNK_STRUCT* pOneTrunk, DJKeygoeIncludes.Acs_Evt_t* pAcsEvt)
        {
#region
            if (pAcsEvt->m_s32EventType == (int)DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_CLEARCALL)	//clear Event
            {
                if ((pOneTrunk->State != DJDemoGlobals.TRUNK_STATE.TRK_FREE) && (pOneTrunk->State != DJDemoGlobals.TRUNK_STATE.TRK_WAIT_REMOVE))
                {
                    ResetTrunk(pOneTrunk, pAcsEvt);
                    return;
                }
            }

            if (pOneTrunk->deviceID.m_s16DeviceSub == (short)DJKeygoeIncludes.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
            {
                sbyte* psbTmpGtd = My_GetGtdCode(pAcsEvt);
                if (psbTmpGtd != null)
                {
                    char TmpGtd = (char)(*psbTmpGtd);
                    if (TmpGtd == 'I' || TmpGtd == 'J' || TmpGtd == 'K')	// Busy Tone
                    {
                        axDJAcsAPI.CtsResetDeviceEx(globals.g_acsHandle, (int)&pOneTrunk->deviceID, 0);
                        axDJAcsAPI.CtsClearCallEx(globals.g_acsHandle, (int)&pOneTrunk->deviceID, 0, 0);
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

                if ( pOneTrunk->deviceID.m_s16DeviceSub == (short)DJKeygoeIncludes.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK )
                {
                    sbyte	 *p = My_GetFskCode ( pAcsEvt );
                    if ( p != null )
                    {
                        ConvertRawFskToCallerID(p, pOneTrunk->CallerCode, 20);
                    }	
                }

                if (pAcsEvt->m_s32EventType == (int)DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_CALLIN)	// Call In Event 
                {
                    // release the Voice for get FSK
                    if (pOneTrunk->deviceID.m_s16DeviceSub == (short)DJKeygoeIncludes.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
                    {
                        My_DualUnlink(&pOneTrunk->VocDevID, &pOneTrunk->deviceID);

                        FreeOneFreeVoice(&pOneTrunk->VocDevID);

                        fixed (DJKeygoeIncludes.DeviceID_t* pUsedDev =
                            &globals.AllDeviceRes[pOneTrunk->VocDevID.m_s8ModuleID].pVoice[pOneTrunk->VocDevID.m_s16ChannelID].UsedDevID)
                        {
                            memset(pUsedDev, 0, sizeof(DJKeygoeIncludes.DeviceID_t));		// 0: didn't alloc Device
                        }
                        memset(&pOneTrunk->VocDevID, 0, sizeof(DJKeygoeIncludes.DeviceID_t));		// 0: didn't alloc Device
                    }

                    DJKeygoeIncludes.Acs_CallControl_Data* pCallControl = (DJKeygoeIncludes.Acs_CallControl_Data*)((byte*)pAcsEvt + sizeof(DJKeygoeIncludes.Acs_Evt_t));
                    axDJAcsAPI.CtsAlertCallEx(globals.g_acsHandle, (int)&pOneTrunk->deviceID, 0);
                    axDJAcsAPI.CtsAnswerCallInEx(globals.g_acsHandle, (int)&pOneTrunk->deviceID, 0);

                    if (pOneTrunk->deviceID.m_s16DeviceSub != (short)DJKeygoeIncludes.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
                    {
                        sprintf(pOneTrunk->CalleeCode, pCallControl->m_s8CalledNum);
                        sprintf(pOneTrunk->CallerCode, pCallControl->m_s8CallingNum);
                    }

                    pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_WAIT_ANSWERCALL;
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_WAIT_ANSWERCALL:
                // Special code for CAS(SS1)
                SpecialForCas(pOneTrunk,pAcsEvt);

                if (pAcsEvt->m_s32EventType == (int)DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_ANSWERCALL)	//Answer Call In End Event
                {
                    DJKeygoeIncludes.Acs_CallControl_Data* pCallControl = (DJKeygoeIncludes.Acs_CallControl_Data*)((byte*)pAcsEvt + sizeof(DJKeygoeIncludes.Acs_Evt_t));

                    DJKeygoeIncludes.DeviceID_t* pFreeVocDeviceID = SearchOneFreeVoice(pOneTrunk);
                    if (pFreeVocDeviceID != null)
                    {
                        pOneTrunk->u8PlayTag = 16;

                        pOneTrunk->VocDevID = *pFreeVocDeviceID;

                        globals.AllDeviceRes[pFreeVocDeviceID->m_s8ModuleID].pVoice[pFreeVocDeviceID->m_s16ChannelID].UsedDevID = pOneTrunk->deviceID;

                        My_DualLink(pFreeVocDeviceID, &pOneTrunk->deviceID);

                        if (pOneTrunk->deviceID.m_s16DeviceSub == (short)DJKeygoeIncludes.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
                        {
                            SetGtD_AnalogTrunk(pFreeVocDeviceID);		// prepare for get Busy Tone
                        }

                        pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_WAIT_LINKOK;
                    }
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_WAIT_LINKOK:
                if ( pAcsEvt->m_s32EventType == (int)DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_LINKDEVICE )	//LinkDevice End
                {
                    string FileName = globals.iniConfigParam.cfg_VocPath;
                    FileName += "\\bank.001";
                    ++pOneTrunk->u8PlayTag;
                    PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, false);

                    pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_WELCOME;
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_WELCOME:
                if ( CheckPlayEnd ( pOneTrunk, pAcsEvt) )	//play end Event
                {
                    string FileName = globals.iniConfigParam.cfg_VocPath;
                    FileName += "\\bank.002";
                    ++pOneTrunk->u8PlayTag;
                    PlayFile ( &pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, false);

                    pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_ACCOUNT;
                }

                sbyte *pDtmf = My_GetDtmfCode ( pAcsEvt );
                if (pDtmf != null)								//DTMF key
                {
                    char TmpDtmf = (char)(*pDtmf);
                    My_AddDtmfBuf ( pOneTrunk, TmpDtmf );

                    StopPlayFile ( &pOneTrunk->VocDevID );
        				
                    pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_ACCOUNT;
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_ACCOUNT:
                {
                    // if play end
                    // do nothing

                    sbyte* pTmpDtmf = My_GetDtmfCode(pAcsEvt);
                    if (pTmpDtmf != null)								//DTMF Key
                    {
                        char TmpDtmf = (char)(*pTmpDtmf);
                        My_AddDtmfBuf(pOneTrunk, TmpDtmf);

                        StopPlayFile(&pOneTrunk->VocDevID);

                        if (pOneTrunk->DtmfCount >= 8)
                        {
                            string FileName = globals.iniConfigParam.cfg_VocPath + "\\bank.003";
                            ++pOneTrunk->u8PlayTag;
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, false);

                            My_InitDtmfBuf(pOneTrunk);
                            pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_PASSWORD;
                        }
                    }
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_PASSWORD:
                {
                    // if play end
                    // do nothing

                    sbyte* pTmpDtmf = My_GetDtmfCode(pAcsEvt);
                    if (pTmpDtmf != null)								//DTMF key
                    {
                        char TmpDtmf = (char)(*pTmpDtmf);
                        My_AddDtmfBuf(pOneTrunk, TmpDtmf);

                        StopPlayFile(&pOneTrunk->VocDevID);

                        if (pOneTrunk->DtmfCount >= 6)
                        {
                            string FileName = globals.iniConfigParam.cfg_VocPath + "\\bank.004";
                            ++pOneTrunk->u8PlayTag;
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, false);

                            My_InitDtmfBuf(pOneTrunk);
                            pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_SELECT;
                        }
                    }
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_SELECT:
                {
                    // if play end
                    // do nothing

                    sbyte* pTmpDtmf = My_GetDtmfCode(pAcsEvt);
                    if (pTmpDtmf == null)								//DTMF Key
                        break;

                    char TmpDtmf = (char)(*pTmpDtmf);
                    My_AddDtmfBuf(pOneTrunk, TmpDtmf);

                    ++pOneTrunk->u8PlayTag;
                    string FileName = globals.iniConfigParam.cfg_VocPath;
                    switch (TmpDtmf)
                    {
                        case '1':
                            {
                                StopPlayFile(&pOneTrunk->VocDevID);

                                FileName += "\\bank.005";
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

                                pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_PLAYRESULT;
                            }
                            break;

                        case '2':
                            StopPlayFile(&pOneTrunk->VocDevID);

                            FileName += "\\bank.006";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            PlayIndex(&pOneTrunk->VocDevID, 0, pOneTrunk->u8PlayTag, true);
                            PlayIndex(&pOneTrunk->VocDevID, 15, pOneTrunk->u8PlayTag, true);
                            PlayIndex(&pOneTrunk->VocDevID, 4, pOneTrunk->u8PlayTag, true);
                            PlayIndex(&pOneTrunk->VocDevID, 8, pOneTrunk->u8PlayTag, true);

                            FileName = globals.iniConfigParam.cfg_VocPath + "\\bank.008";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_PLAYRESULT;
                            break;

                        case '3':
                            StopPlayFile(&pOneTrunk->VocDevID);

                            FileName = globals.iniConfigParam.cfg_VocPath + "\\bank.007";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            FileName = globals.iniConfigParam.cfg_VocPath + "\\D3";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            FileName = globals.iniConfigParam.cfg_VocPath + "\\D13";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            FileName = globals.iniConfigParam.cfg_VocPath + "\\D7";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            FileName = globals.iniConfigParam.cfg_VocPath + "\\D12";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            FileName = globals.iniConfigParam.cfg_VocPath + "\\bank.008";
                            PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, true);

                            pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_PLAYRESULT;
                            break;

                        case '4':
                            StopPlayFile(&pOneTrunk->VocDevID);

                            FileName = globals.iniConfigParam.cfg_VocPath + "\\DemoRec." + pOneTrunk->iSeqID.ToString("%03d");
                            RecordFile(&pOneTrunk->VocDevID, FileName, 8000 * 10, false);

                            pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_RECORDFILE;
                            break;

                        default:
                            break;
                    }
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_PLAYRESULT:
            case DJDemoGlobals.TRUNK_STATE.TRK_PLAYRECORD:
                if ( CheckPlayEnd ( pOneTrunk, pAcsEvt) )	// Play End Event 
                {
                    // Clear Call
                    axDJAcsAPI.CtsClearCallEx(globals.g_acsHandle, (int)&pOneTrunk->deviceID, 0, 0);

                    pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_HANGON;
                }
                break;

            case DJDemoGlobals.TRUNK_STATE.TRK_RECORDFILE:
                {
                    sbyte* pTmpDtmf = My_GetDtmfCode(pAcsEvt);
                    if (pTmpDtmf != null)								//DTMF Key
                    {
                        char TmpDtmf = (char)(*pTmpDtmf);
                        My_AddDtmfBuf(pOneTrunk, TmpDtmf);

                        StopRecordFile(&pOneTrunk->VocDevID);
                    }

                    if (CheckRecordEnd(pOneTrunk, pAcsEvt))	//record end
                    {
                        ++pOneTrunk->u8PlayTag;

                        string FileName = globals.iniConfigParam.cfg_VocPath + "\\DemoRec." + pOneTrunk->iSeqID.ToString("%03d");
                        PlayFile(&pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag, false);

                        pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_PLAYRECORD;
                    }
                }
                break;

                default:
                    break;
            }
        }

        public unsafe int SearchOneFreeVoice(int iDSPModID)
        {
            int iResult = -1;
            for (int i = 0; i < globals.AllDeviceRes[iDSPModID].lVocNum; ++i)
            {
                fixed (DJDemoGlobals.VOICE_STRUCT* pOneVoice = &globals.AllDeviceRes[iDSPModID].pVoice[i])
                {
                    if (pOneVoice->State == DJDemoGlobals.VOICE_STATE.VOC_FREE)
                    {
                        pOneVoice->State = DJDemoGlobals.VOICE_STATE.VOC_USED;

                        --globals.AllDeviceRes[iDSPModID].lVocFreeNum;

                        iResult = i;
                    }
                }
                if (iResult != -1)
                {
                    break;
                }
            }

            return iResult;
        }

        public unsafe void EvtHandler(int esrParam)
        {
            try
            {
                fixed (int* pAcsHandle = &globals.g_acsHandle)
                {
                    DJKeygoeIncludes.Acs_Evt_t* pAcsEvt = (DJKeygoeIncludes.Acs_Evt_t*)esrParam;

                    //EvtInfo
                    {
                        string strEvtInfo = "EVT(" + pAcsEvt->m_s32EvtSize.ToString() + ") : " + globals.GetEventTypeString(pAcsEvt->m_s32EventType);
                        this.ShowEvtInfo(strEvtInfo);
                    }

                    //EvtProc
                    {
                        switch ((DJKeygoeIncludes.XMS_EVT_TYPE)pAcsEvt->m_s32EventType)
                        {
                            case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_START:
                                break;

                            #region XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE
                            case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE:
                                if ((globals.iniConfigParam.cfg_iPartWork == 0) || (pAcsEvt->m_DeviceID.m_s8ModuleID == globals.iniConfigParam.cfg_iPartWorkModuleID))
                                {
                                    DJKeygoeIncludes.Acs_Dev_List_Head_t* pAcsDevList = (DJKeygoeIncludes.Acs_Dev_List_Head_t*)((byte*)pAcsEvt + sizeof(DJKeygoeIncludes.Acs_Evt_t));

                                    //收到设备变化的事件，增加/删除 该设备资源
                                    {
                                        int s32Type = pAcsDevList->m_s32DeviceMain;
                                        int s32Num = pAcsDevList->m_s32DeviceNum;
                                        int s8DspModID = pAcsDevList->m_s32ModuleID;

                                        if ((s8DspModID > 0) && (s8DspModID < DJDemoGlobals.MAX_DSP_MODULE_NUMBER_OF_XMS))
                                        {
                                            DJKeygoeIncludes.DeviceID_t* pDev = (DJKeygoeIncludes.DeviceID_t*)((byte*)pAcsDevList + sizeof(DJKeygoeIncludes.Acs_Dev_List_Head_t));
                                            switch ((DJKeygoeIncludes.XMS_DEVMAIN_TYPE)s32Type)
                                            {
                                                case DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE:
                                                    {
                                                        globals.AllDeviceRes[s8DspModID].pVoice = new DJDemoGlobals.VOICE_STRUCT[s32Num];
                                                        globals.AllDeviceRes[s8DspModID].lVocNum = s32Num;
                                                        globals.AllDeviceRes[s8DspModID].lVocOpened = 0;
                                                        globals.AllDeviceRes[s8DspModID].lVocFreeNum = 0;

                                                        for (int i = 0; i < s32Num; ++i)
                                                        {
                                                            globals.AllDeviceRes[s8DspModID].pVoice[i].deviceID = pDev[i];
                                                            globals.AllDeviceRes[s8DspModID].pVoice[i].State = DJDemoGlobals.VOICE_STATE.VOC_WAITOPEN;
                                                        }

                                                        this.ShowEvtInfo("Add Voc Res " + s32Num.ToString() + " DSP" + s8DspModID.ToString());
                                                    }
                                                    break;

                                                case DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT:
                                                    {
                                                        globals.AllDeviceRes[s8DspModID].pPcm = new DJDemoGlobals.PCM_STRUCT[s32Num];
                                                        globals.AllDeviceRes[s8DspModID].lPcmNum = s32Num;
                                                        globals.AllDeviceRes[s8DspModID].lPcmOpened = 0;

                                                        for (int i = 0; i < s32Num; ++i)
                                                        {
                                                            globals.AllDeviceRes[s8DspModID].pPcm[i].deviceID = pDev[i];
                                                            globals.AllDeviceRes[s8DspModID].pPcm[i].bOpenFlag = false;
                                                        }

                                                        this.ShowEvtInfo("Add Pcm Res " + s32Num.ToString() + " DSP" + s8DspModID.ToString());
                                                    }
                                                    break;

                                                case DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH:
                                                    {
                                                        globals.AllDeviceRes[s8DspModID].pTrunk = new DJDemoGlobals.TRUNK_STRUCT[s32Num];
                                                        globals.AllDeviceRes[s8DspModID].lTrunkNum = s32Num;
                                                        globals.AllDeviceRes[s8DspModID].lTrunkOpened = 0;

                                                        for (int i = 0; i < s32Num; i++)
                                                        {
                                                            globals.AllDeviceRes[s8DspModID].pTrunk[i].deviceID = pDev[i];
                                                            globals.AllDeviceRes[s8DspModID].pTrunk[i].State = DJDemoGlobals.TRUNK_STATE.TRK_WAITOPEN;
                                                        }

                                                        this.ShowEvtInfo("Add Interface Res " + s32Num.ToString() + " DSP" + s8DspModID.ToString());
                                                    }
                                                    break;

                                                case DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD:
                                                    {
                                                        globals.AllDeviceRes[s8DspModID].lFlag = 1;

                                                        globals.AllDeviceRes[s8DspModID].deviceID = pDev[0];

                                                        globals.AllDeviceRes[s8DspModID].bOpenFlag = false;
                                                        globals.AllDeviceRes[s8DspModID].bErrFlag = false;
                                                        globals.AllDeviceRes[s8DspModID].RemoveState = DJDemoGlobals.REMOVE_STATE.DSP_REMOVE_STATE_NONE;

                                                        this.ShowEvtInfo("Add Board Res " + s32Num.ToString() + " DSP" + s8DspModID.ToString());
                                                    }
                                                    break;

                                                case DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_FAX: break;
                                                case DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DSS1_LINK: break;
                                                case DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_SS7_LINK: break;
                                                case DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_CTBUS_TS: break;
                                                case DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOIP: break;
                                                case DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_CONFERENCE: break;
                                                case DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VIDEO: break;
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
                            case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_END:
                            case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_QUERY_REMOVE_ONE_DSP_END:
                                if (pAcsEvt->m_s32EventType == (int)DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_END)
                                {
                                    globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].lFlag = 1;		// 该DSP可以用了
                                    int s8DspModID = pAcsEvt->m_DeviceID.m_s8ModuleID;

                                    if (globals.iniConfigParam.cfg_iPartWork != 0 && s8DspModID != globals.iniConfigParam.cfg_iPartWorkModuleID)
                                    {
                                        return;
                                    }

                                    // Open Board
                                    int iResult = 0;

                                    if (globals.AllDeviceRes[s8DspModID].bOpenFlag == false)	// 还没有Open
                                    {
                                        fixed (DJKeygoeIncludes.DeviceID_t* pDev = &globals.AllDeviceRes[s8DspModID].deviceID)
                                        {
                                            iResult = axDJAcsAPI.CtsOpenDeviceEx(globals.g_acsHandle, (int)pDev, 0);
                                            if (iResult == DJKeygoeIncludes.ACSPOSITIVE_ACK)
                                            {
                                                this.ShowEvtInfo("CtsOpenDeviceEx (Board) Success");
                                            }
                                            else
                                            {
                                                this.ShowEvtInfo("CtsOpenDeviceEx (Board) Fail");
                                            }
                                        }

                                        // Open Voice
                                        for (int i = 0; i < globals.AllDeviceRes[s8DspModID].lVocNum; ++i)
                                        {
                                            fixed (DJKeygoeIncludes.DeviceID_t* pDev = &globals.AllDeviceRes[s8DspModID].pVoice[i].deviceID)
                                            {
                                                iResult = axDJAcsAPI.CtsOpenDeviceEx(globals.g_acsHandle, (int)pDev, 0);
                                                if (iResult == DJKeygoeIncludes.ACSPOSITIVE_ACK)
                                                {
                                                    this.ShowEvtInfo("CtsOpenDeviceEx (Voice) Success");
                                                }
                                                else
                                                {
                                                    this.ShowEvtInfo("CtsOpenDeviceEx (Voice) Fail");
                                                }
                                            }
                                        }

                                        // Open Pcm
                                        for (int i = 0; i < globals.AllDeviceRes[s8DspModID].lPcmNum; ++i)
                                        {
                                            fixed (DJKeygoeIncludes.DeviceID_t* pDev = &globals.AllDeviceRes[s8DspModID].pPcm[i].deviceID)
                                            {
                                                iResult = axDJAcsAPI.CtsOpenDeviceEx(globals.g_acsHandle, (int)pDev, 0);
                                                if (iResult == DJKeygoeIncludes.ACSPOSITIVE_ACK)
                                                {
                                                    this.ShowEvtInfo("CtsOpenDeviceEx (Pcm) Success");
                                                }
                                                else
                                                {
                                                    this.ShowEvtInfo("CtsOpenDeviceEx (Pcm) Fail");
                                                }
                                            }
                                        }

                                        // Open Trunk
                                        for (int i = 0; i < globals.AllDeviceRes[s8DspModID].lTrunkNum; ++i)
                                        {
                                            fixed (DJKeygoeIncludes.DeviceID_t* pDev = &globals.AllDeviceRes[s8DspModID].pTrunk[i].deviceID)
                                            {
                                                iResult = axDJAcsAPI.CtsOpenDeviceEx(globals.g_acsHandle, (int)pDev, 0);
                                                if (iResult == DJKeygoeIncludes.ACSPOSITIVE_ACK)
                                                {
                                                    this.ShowEvtInfo("CtsOpenDeviceEx (Interface) Success");
                                                }
                                                else
                                                {
                                                    this.ShowEvtInfo("CtsOpenDeviceEx (Interface) Fail");
                                                }
                                            }
                                            iResult = s8DspModID * 1000 + i;
                                            this.AddTrunkListItems(iResult);//debugging
                                        }
                                    }
                                }
                                else
                                {
                                    globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].lFlag = 0;		// 该DSP已经Remove完毕
                                }
                                break;
                            #endregion

                            case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE_END:	// 获取设备列表结束
                                break;

                            #region XMS_EVT_TYPE.XMS_EVT_OPEN_DEVICE
                            case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_OPEN_DEVICE:
                                {
                                    int iDspModuleID = pAcsEvt->m_DeviceID.m_s8ModuleID;
                                    switch ((DJKeygoeIncludes.XMS_DEVMAIN_TYPE)pAcsEvt->m_DeviceID.m_s16DeviceMain)
                                    {
                                        case DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD:
                                            {
                                                globals.AllDeviceRes[iDspModuleID].deviceID.m_CallID = pAcsEvt->m_DeviceID.m_CallID;
                                            }
                                            break;

                                        #region XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH
                                        case DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH:
                                            {
                                                fixed (DJDemoGlobals.TRUNK_STRUCT* pOneTrunk = &globals.AllDeviceRes[iDspModuleID].pTrunk[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                                {
                                                    pOneTrunk->deviceID.m_CallID = pAcsEvt->m_DeviceID.m_CallID;		// this line is very important, must before all operation

                                                    pOneTrunk->State = DJDemoGlobals.TRUNK_STATE.TRK_FREE;
                                                    pOneTrunk->VocDevID.m_s8ModuleID = 0;
                                                    pOneTrunk->DtmfCount = 0;
                                                    pOneTrunk->DtmfBuf[0] = '\0';
                                                    pOneTrunk->CallerCode[0] = '\0';
                                                    pOneTrunk->CalleeCode[0] = '\0';

                                                    {
                                                        DJKeygoeIncludes.DeviceID_t* pDev = &pOneTrunk->deviceID;
                                                        axDJAcsAPI.CtsResetDeviceEx(globals.g_acsHandle, (int)pDev, 0);
                                                        axDJAcsAPI.CtsGetDevStateEx(globals.g_acsHandle, (int)pDev, 0);
                                                        pDev = null;
                                                    }

                                                    ++globals.AllDeviceRes[iDspModuleID].lTrunkOpened;

                                                    if (pOneTrunk->deviceID.m_s16DeviceSub == (int)DJKeygoeIncludes.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
                                                    {
                                                        DJKeygoeIncludes.CmdParamData_AnalogTrunk_t cmdAnalogTrunk = new DJKeygoeIncludes.CmdParamData_AnalogTrunk_t();
                                                        short u16ParamType = (short)DJKeygoeIncludes.XMS_ANALOGTRUNK_PARAM_TYPE.ANALOGTRUNK_PARAM_UNIPARAM; // 0
                                                        short u16ParamSize = (short)sizeof(DJKeygoeIncludes.CmdParamData_AnalogTrunk_t);
                                                        cmdAnalogTrunk.m_u16CallInRingCount = 3;			// 3 times RingBack
                                                        cmdAnalogTrunk.m_u16CallInRingTimeOut = 6000;		// 60 seconds

                                                        {
                                                            DJKeygoeIncludes.DeviceID_t* pDev = &pOneTrunk->deviceID;
                                                            DJKeygoeIncludes.CmdParamData_AnalogTrunk_t* pCmdAnalogTrunk = &cmdAnalogTrunk;
                                                            int iResult = axDJAcsAPI.CtsSetParamEx(globals.g_acsHandle, (int)pDev, u16ParamType, u16ParamSize, (int)pCmdAnalogTrunk);
                                                            pDev = null;
                                                            pCmdAnalogTrunk = null;
                                                            string strMsg = "Set AnalogTrunk  ret = " + iResult.ToString();
                                                            ShowEvtInfo(strMsg);
                                                        }

                                                        {
                                                            int iChID = SearchOneFreeVoice(pOneTrunk->deviceID.m_s8ModuleID);
                                                            if (iChID >= 0)
                                                            {
                                                                //指定绑定关系
                                                                pOneTrunk->VocDevID = globals.AllDeviceRes[pOneTrunk->deviceID.m_s8ModuleID].pVoice[iChID].deviceID;
                                                                globals.AllDeviceRes[pOneTrunk->deviceID.m_s8ModuleID].pVoice[iChID].UsedDevID = pOneTrunk->deviceID;

                                                                DJKeygoeIncludes.CmdParamData_Voice_t cmdVoc = new DJKeygoeIncludes.CmdParamData_Voice_t();
                                                                //memset(&cmdVoc, 0, sizeof(DJKeygoeIncludes.CmdParamData_Voice_t));//debugging
                                                                cmdVoc.m_u8GtdCtrlValid = 1;						//Enable GTD
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
                                                                cmdVoc.m_VocGtdControl.m_u8GTDID[5] = 0; // Detect Busy Tone

                                                                u16ParamType = (short)DJKeygoeIncludes.XMS_VOC_PARAM_TYPE.VOC_PARAM_UNIPARAM;
                                                                u16ParamSize = (short)sizeof(DJKeygoeIncludes.CmdParamData_Voice_t);

                                                                fixed (DJKeygoeIncludes.DeviceID_t* pFreeVocDeviceID = &globals.AllDeviceRes[pOneTrunk->deviceID.m_s8ModuleID].pVoice[iChID].deviceID)
                                                                {
                                                                    DJKeygoeIncludes.CmdParamData_Voice_t* pCmdVoc = &cmdVoc;
                                                                    int iResult = axDJAcsAPI.CtsSetParamEx(globals.g_acsHandle, (int)pFreeVocDeviceID, u16ParamType, u16ParamSize, (int)pCmdVoc);
                                                                    pCmdVoc = null;
                                                                
                                                                    string strMsg = "Set Voice  ret = " + iResult.ToString();
                                                                    ShowEvtInfo(strMsg);
                                                                }
                                                                My_DualLink(&pOneTrunk->VocDevID, &pOneTrunk->deviceID);//add by lmy 20120321
                                                            }
                                                        }
                                                    }

                                                    //ShowInfo
                                                    int iIDSum = iDspModuleID * 1000 + pAcsEvt->m_DeviceID.m_s16ChannelID;
                                                    this.ShowTrunkListItems(iIDSum);//debugging
                                                }
                                            }
                                            break;
                                        #endregion

                                        case DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE:
                                            {
                                                globals.AllDeviceRes[iDspModuleID].pVoice[pAcsEvt->m_DeviceID.m_s16ChannelID].deviceID.m_CallID = pAcsEvt->m_DeviceID.m_CallID;
                                                ++globals.AllDeviceRes[iDspModuleID].lVocOpened;
                                                ++globals.AllDeviceRes[iDspModuleID].lVocFreeNum;
                                                globals.AllDeviceRes[iDspModuleID].pVoice[pAcsEvt->m_DeviceID.m_s16ChannelID].State = DJDemoGlobals.VOICE_STATE.VOC_FREE;
                                            }
                                            break;

                                        #region XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT
                                        case DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT:
                                            {
                                                globals.AllDeviceRes[iDspModuleID].pPcm[pAcsEvt->m_DeviceID.m_s16ChannelID].deviceID.m_CallID = pAcsEvt->m_DeviceID.m_CallID;
                                                {
                                                    DJKeygoeIncludes.DeviceID_t* pDev = &pAcsEvt->m_DeviceID;
                                                    axDJAcsAPI.CtsResetDeviceEx(globals.g_acsHandle, (int)pDev, 0);
                                                    axDJAcsAPI.CtsGetDevStateEx(globals.g_acsHandle, (int)pDev, 0);
                                                    pDev = null;
                                                }
                                                ++globals.AllDeviceRes[iDspModuleID].lPcmOpened;
                                            }
                                            break;
                                        #endregion

                                        default:
                                            break;
                                    }
                                }
                                break;
                            #endregion

                            case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_CLOSE_DEVICE:		// 在删除设备之前，先发给应用程序CloseDevice事件；调用函数XMS_ctsCloseDevicey也会产生本事件
                                //CloseDeviceOK(&pAcsEvt->m_DeviceID);
                                break;

                            #region XMS_EVT_TYPE.XMS_EVT_DEVICESTATE
                            case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_DEVICESTATE:
                                {
                                    DJKeygoeIncludes.Acs_GeneralProc_Data* pGeneralData =
                                        (DJKeygoeIncludes.Acs_GeneralProc_Data*)((byte*)pAcsEvt + sizeof(DJKeygoeIncludes.Acs_Evt_t));
                                    if (pAcsEvt->m_DeviceID.m_s16DeviceMain == (short)DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH)
                                    {
                                        fixed (DJDemoGlobals.TRUNK_STRUCT* pOneTrunk =
                                            &globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pTrunk[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                        {
                                            pOneTrunk->iLineState = pGeneralData->m_s32DeviceState;

                                            //ShowInfo
                                            int iIDSum = pOneTrunk->deviceID.m_s8ModuleID * 1000 + pOneTrunk->deviceID.m_s16ChannelID;
                                            this.ShowTrunkListItems(iIDSum);//debugging
                                        }
                                    }

                                    pGeneralData = null;
                                }
                                break;
                            #endregion

                            case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_UNIFAILURE:
                                // must handle this event in your real System
                                break;

                            #region default
                            default:
                                if ((DJKeygoeIncludes.XMS_DEVMAIN_TYPE)pAcsEvt->m_DeviceID.m_s16DeviceMain == DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH)
                                {
                                    fixed (DJDemoGlobals.TRUNK_STRUCT* pOneTrunk = &globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pTrunk[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                    {
                                        TrunkWork(pOneTrunk, pAcsEvt);

                                        //ShowInfo
                                        int iIDSum = pAcsEvt->m_DeviceID.m_s8ModuleID * 1000 + pAcsEvt->m_DeviceID.m_s16ChannelID;
                                        this.ShowTrunkListItems(iIDSum);//debugging
                                    }
                                }
                                else if ((DJKeygoeIncludes.XMS_DEVMAIN_TYPE)pAcsEvt->m_DeviceID.m_s16DeviceMain == DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE)
                                {
                                    fixed (DJKeygoeIncludes.DeviceID_t* pDevID = &globals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pVoice[pAcsEvt->m_DeviceID.m_s16ChannelID].UsedDevID)
                                    {
                                        if (pDevID->m_s8ModuleID == 0)
                                        {
                                            break;
                                        }

                                        if ((DJKeygoeIncludes.XMS_DEVMAIN_TYPE)pDevID->m_s16DeviceMain == DJKeygoeIncludes.XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH)
                                        {
                                            fixed (DJDemoGlobals.TRUNK_STRUCT* pOneTrunk = &globals.AllDeviceRes[pDevID->m_s8ModuleID].pTrunk[pDevID->m_s16ChannelID])
                                            {
                                                TrunkWork(pOneTrunk, pAcsEvt);

                                                //ShowInfo
                                                int iIDSum = pDevID->m_s8ModuleID * 1000 + pDevID->m_s16ChannelID;
                                                this.ShowTrunkListItems(iIDSum);//debugging
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
            catch (Exception)
            {
            }

            return;
        }
        #endregion
    }

    public class ClsIniFile
    {
        [DllImport("kernel32")]
        private static extern int WritePrivateProfileString(string section,
            string key, string val, string filePath);

        [DllImport("kernel32")]
        private static extern int GetPrivateProfileString(string section,
            string key, string def, StringBuilder val, int size, string filePath);

        [DllImport("kernel32")]
        private static extern Int32 GetModuleFileName(
                                         Int32 hModule,    // handle to module
                                         StringBuilder lpFilename,  // path buffer
                                         Int32 nSize         // size of buffer
                                       );

        [DllImport("kernel32")]
        private static extern Int32 GetPrivateProfileInt(
                                         string section,  // section name
                                         string key,  // key name
                                         int iDefault,       // return value if key name not found
                                         string filePath  // initialization file name
                                       );


        protected string strIniPath;

        public ClsIniFile(string strFilePath)
        {
            strIniPath = strFilePath;
        }

        public void SetIniFileName(string strFilePath)
        {
            strIniPath = strFilePath;
        }

        public int WriteFileString(string section, string key, string val)
        {
            return WritePrivateProfileString(section, key, val, strIniPath);
        }

        public int GetFileString(string section, string key, string def, StringBuilder val, int size)
        {
            return GetPrivateProfileString(section, key, def, val, size, strIniPath);
        }

        public int GetFileInt(string section, string key, int iDeafult)
        {
            return GetPrivateProfileInt(section, key, iDeafult, strIniPath);
        }

        public int GetExeFilePath(StringBuilder lpFilePath, Int32 nSize)
        {
            return GetModuleFileName(0, lpFilePath, nSize);
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
            public DJKeygoeIncludes.DeviceID_t deviceID;
            public int iSeqID;
            public int iModSeqID;
            public int iLineState;

            public DJKeygoeIncludes.DeviceID_t VocDevID;
            public byte u8PlayTag;

            public TRUNK_STATE State;

            public int DtmfCount;
            public fixed char DtmfBuf[32];

            public fixed char CallerCode[20];
            public fixed char CalleeCode[20];
        };

        public struct VOICE_STRUCT
        {
            public DJKeygoeIncludes.DeviceID_t deviceID;
            public int iSeqID;

            public DJKeygoeIncludes.DeviceID_t UsedDevID;

            public VOICE_STATE State;
        };

        public struct PCM_STRUCT
        {
            public DJKeygoeIncludes.DeviceID_t deviceID;
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

            public DJKeygoeIncludes.DeviceID_t deviceID;		// 本DSP模块的deviceID
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

        public const int MAX_DSP_MODULE_NUMBER_OF_XMS = 256;
        public TYPE_XMS_DSP_DEVICE_RES_DEMO[] AllDeviceRes = new TYPE_XMS_DSP_DEVICE_RES_DEMO[MAX_DSP_MODULE_NUMBER_OF_XMS];
        #endregion

        #region Config
        public DJKeygoeIncludes.CmdParamData_CAS_t g_Param_CAS = new DJKeygoeIncludes.CmdParamData_CAS_t();
        /*************************************************************************************
        return 
	        0:	OK.
	        -1:	Fail, m_u8CalledTableCount Invalid
	        -2: Fail, m_u8CalledLen Invalid
	        -3: Fail, m_u8CalledTimeOut Invalid
	        -4: Fail, m_u8AreaCodeLen Invalid
	        -5: Fail, m_CalledTable[x].m_u8NumLen Invalid
        *************************************************************************************/
        public unsafe int CAS_Common_Cfg_ReadCfg(DJKeygoeIncludes.CmdParamData_CAS_t* pParam_CAS)
        {
            ClsIniFile clsIniFile = new ClsIniFile("C:\\DJKeygoe\\Samples\\CAS_Common_Code\\XMS_CAS_Cfg.INI");

            //int			i;
            //char		TmpStr[32], TmpName[32];

            // ------------------------ [Rule] ------------------------
            // m_u8CalledTableCount
            int iTmp = clsIniFile.GetFileInt("Rule", "CalledTableCount", 0);
            if ((iTmp < 0) || (iTmp > 16))
                return -1;							// m_u8CalledTableCount Invalid
            pParam_CAS->m_u8CalledTableCount = (byte)iTmp;

            // m_u8CalledLen
            iTmp = clsIniFile.GetFileInt("Rule", "CalledLen", 5);
            if ((iTmp <= 0) || (iTmp > 32))
                return -2;							// m_u8CalledLen Invalid
            pParam_CAS->m_u8CalledLen = (byte)iTmp;

            // m_u8CalledTimeOut
            iTmp = clsIniFile.GetFileInt("Rule", "CalledTimeOut", 0);
            if ((iTmp < 0) || (iTmp > 10))
                return -3;							// m_u8CalledTimeOut Invalid
            pParam_CAS->m_u8CalledTimeOut = (byte)iTmp;

            // m_u8NeedCaller
            iTmp = clsIniFile.GetFileInt("Rule", "NeedCaller", 0);
            if (iTmp != 0)
                iTmp = 1;
            pParam_CAS->m_u8NeedCaller = (byte)iTmp;

            // m_u8AreaCodeLen
            iTmp = clsIniFile.GetFileInt("Rule", "AreaCodeLen", 0);
            if (pParam_CAS->m_u8NeedCaller != 0)		// need caller
            {
                if ((iTmp < 0) || (iTmp > 10))
                    return -4;						// m_u8AreaCodeLen Invalid
            }
            pParam_CAS->m_u8AreaCodeLen = (byte)iTmp;

            // m_u8ControlMode
            iTmp = clsIniFile.GetFileInt("Rule", "ControlMode", 0);
            if ((iTmp != 0) && (iTmp != 1) && (iTmp != 2))
                iTmp = 0;
            pParam_CAS->m_u8ControlMode = (byte)iTmp;

            // ------------------------ [CalledTable] ------------------------
            //memset ( pParam_CAS->m_CalledTable, 0, sizeof(DJDataDefClass.CAS_CalledTableDesc_t) * 16 );
            fixed (byte* p = g_Param_CAS.m_CalledTable)
            {
                DJKeygoeIncludes.CAS_CalledTableDesc_t* pCalledTable = (DJKeygoeIncludes.CAS_CalledTableDesc_t*)p;
                for (int i = 0; i < pParam_CAS->m_u8CalledTableCount; ++i)
                {
                    // m_u8NumHeadLen & m_u8NumHead
                    string TmpName = "NumHead[" + i.ToString() + "]";

                    StringBuilder strBlderTemp = new StringBuilder(256);
                    clsIniFile.GetFileString("CalledTable", TmpName, "168", strBlderTemp, 256);
                    string strTemp = strBlderTemp.ToString();
                    int j = 0;
                    for (j = 0; j < strTemp.Length && j < 15; ++j)
                    {
                        pCalledTable[i].m_u8NumHead[j] = (byte)strTemp[j];
                    }
                    if (j >= 15)
                    {
                        j = 14;
                        pCalledTable[i].m_u8NumHead[j] = (byte)'\0';
                    }
                    else
                    {
                        pCalledTable[i].m_u8NumHead[j] = (byte)'\0';
                    }
                    pCalledTable[i].m_u8NumHeadLen = (byte)j;

                    // m_u8NumLen
                    string TmpNameEx = "NumLen[" + i.ToString() + "]";
                    iTmp = clsIniFile.GetFileInt("CalledTable", TmpNameEx, 5);
                    if ((iTmp < 0) || (iTmp > 16))
                        return -5;							// m_CalledTable[x].m_u8NumLen Invalid
                    pCalledTable[i].m_u8NumLen = (byte)iTmp;
                }
            }

            // ------------------------ Other ------------------------
            // Call Out Parameter, set to default value directly.
            pParam_CAS->m_u8KA = 1;
            pParam_CAS->m_u8KD = 3;

            return 0;		// OK
        }

        public class IniConfigParam
        {
            // var about Demo.INI
            public string cfg_IniName = "";
            public string cfg_IniShortName = "\\Demo.ini";

            public DJKeygoeIncludes.ServerID_t cfg_ServerID;

            public string cfg_VocPath;
            public int cfg_iDispChnl;		// always disp 32 channel
            public int cfg_iVoiceRule;		// search voice in Fix Relationship

            public int cfg_iPreIDNum;
            public string[] cfg_PreE1Out;

            public int cfg_iPartWork;
            public int cfg_iPartWorkModuleID;
            public int cfg_s32DebugOn;

            public IniConfigParam()
            {
                cfg_ServerID = new DJKeygoeIncludes.ServerID_t();
            }
        };
        public IniConfigParam iniConfigParam = new IniConfigParam();
        public unsafe void CharsToSBytes(char[] chSrc, sbyte* byDst, int size)
        {
            int i = 0;
            for (i = 0; i < size && chSrc[i] != '\0'; ++i)
            {
                byDst[i] = (sbyte)chSrc[i];
            }
            byDst[i] = (sbyte)'\0';
        }
        public unsafe void SBytesToChars(sbyte* bySrc, char[] chDst)
        {
            int i = 0;
            for (i = 0; bySrc[i] != (sbyte)'\0'; ++i)
            {
                chDst[i] = (char)bySrc[i];
            }
            chDst[i] = '\0';
        }
        public unsafe void ReadFromConfig()
        {
            ClsIniFile clsIniFile = new ClsIniFile("");
            StringBuilder strFileName = new StringBuilder(256);
            clsIniFile.GetExeFilePath(strFileName, 256);
            string strFilePath = strFileName.ToString();
            clsIniFile.SetIniFileName(strFilePath.Replace(".exe", ".ini"));

            StringBuilder strBlderTemp = new StringBuilder(256);
            clsIniFile.GetFileString("ConfigInfo", "IpAddr", "192.168.10.33", strBlderTemp, 256);
            string strTemp = strBlderTemp.ToString();
            fixed (sbyte* p = iniConfigParam.cfg_ServerID.m_s8ServerIp)
            {
                CharsToSBytes(strTemp.ToCharArray(), p, strTemp.Length);
            }
            iniConfigParam.cfg_ServerID.m_u32ServerPort = (uint)clsIniFile.GetFileInt("ConfigInfo", "Port", 9000);
            clsIniFile.GetFileString("ConfigInfo", "UserName", "", strBlderTemp, 256);
            strTemp = strBlderTemp.ToString();
            fixed (sbyte* p = iniConfigParam.cfg_ServerID.m_s8UserName)
            {
                CharsToSBytes(strTemp.ToCharArray(), p, strTemp.Length);
            }
            clsIniFile.GetFileString("ConfigInfo", "PassWord", "", strBlderTemp, 256);
            strTemp = strBlderTemp.ToString();
            fixed (sbyte* p = iniConfigParam.cfg_ServerID.m_s8UserPwd)
            {
                CharsToSBytes(strTemp.ToCharArray(), p, strTemp.Length);
            }

            clsIniFile.GetFileString("ConfigInfo", "VocPath", "", strBlderTemp, 256);
            iniConfigParam.cfg_VocPath = strBlderTemp.ToString();
            iniConfigParam.cfg_iDispChnl = (int)clsIniFile.GetFileInt("ConfigInfo", "DispChnl", 32);
            iniConfigParam.cfg_iVoiceRule = (int)clsIniFile.GetFileInt("ConfigInfo", "VoiceRule", 1);

            iniConfigParam.cfg_iPartWork = clsIniFile.GetFileInt("ConfigInfo", "PartWork", 0);
            iniConfigParam.cfg_iPartWorkModuleID = clsIniFile.GetFileInt("ConfigInfo", "PartWorkModuleID", 0);
            iniConfigParam.cfg_s32DebugOn = clsIniFile.GetFileInt("ConfigInfo", "DebugOn", 0);

            iniConfigParam.cfg_iPreIDNum = clsIniFile.GetFileInt("ConfigInfo", "PreIDNum", 0);
            if (iniConfigParam.cfg_iPreIDNum > 0)
            {
                iniConfigParam.cfg_PreE1Out = new string[iniConfigParam.cfg_iPreIDNum];
                int i = 0;
                for (i = 0; i < iniConfigParam.cfg_iPreIDNum; ++i)
                {
                    clsIniFile.GetFileString("ConfigInfo", "PreE1Out" + i.ToString(), "", strBlderTemp, 256);
                    iniConfigParam.cfg_PreE1Out[i] = strBlderTemp.ToString();
                }
            }
        }
        public unsafe void WriteToConfig()
        {
            ClsIniFile clsIniFile = new ClsIniFile("");
            StringBuilder strFileName = new StringBuilder(256);
            clsIniFile.GetExeFilePath(strFileName, 256);
            string strFilePath = strFileName.ToString();
            clsIniFile.SetIniFileName(strFilePath.Replace(".exe", ".ini"));

            string strTemp = new string('\0', 0);
            char[] chTemp = new char[32];
            fixed (sbyte* p = iniConfigParam.cfg_ServerID.m_s8ServerIp)
            {
                SBytesToChars(p, chTemp);
            }
            strTemp = new string(chTemp);
            clsIniFile.WriteFileString("ConfigInfo", "IpAddr", strTemp);
            strTemp = iniConfigParam.cfg_ServerID.m_u32ServerPort.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "Port", strTemp);
            fixed (sbyte* p = iniConfigParam.cfg_ServerID.m_s8UserName)
            {
                SBytesToChars(p, chTemp);
            }
            strTemp = new string(chTemp);
            clsIniFile.WriteFileString("ConfigInfo", "UserName", strTemp);
            fixed (sbyte* p = iniConfigParam.cfg_ServerID.m_s8UserPwd)
            {
                SBytesToChars(p, chTemp);
            }
            strTemp = new string(chTemp);
            clsIniFile.WriteFileString("ConfigInfo", "PassWord", strTemp);

            clsIniFile.WriteFileString("ConfigInfo", "VocPath", iniConfigParam.cfg_VocPath);
            strTemp = iniConfigParam.cfg_iDispChnl.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "DispChnl", strTemp);
            strTemp = iniConfigParam.cfg_iVoiceRule.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "VoiceRule", strTemp);

            strTemp = iniConfigParam.cfg_iPartWork.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "PartWork", strTemp);
            strTemp = iniConfigParam.cfg_iPartWorkModuleID.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "PartWorkModuleID", strTemp);
            strTemp = iniConfigParam.cfg_s32DebugOn.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "DebugOn", strTemp);

            strTemp = iniConfigParam.cfg_iPreIDNum.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "PreIDNum", strTemp);
            int i = 0;
            for (i = 0; i < iniConfigParam.cfg_iPreIDNum; ++i)
            {
                clsIniFile.WriteFileString("ConfigInfo", "PreE1Out" + i.ToString(), iniConfigParam.cfg_PreE1Out[i]);
            }
        }
        #endregion

        public int g_acsHandle = -1;

        public string GetEventTypeString(int iEvtType)
        {
            switch ((DJKeygoeIncludes.XMS_EVT_TYPE)iEvtType)
            {
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_OPEN_STREAM: return "OPEN_STREAM";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE: return "QUERY_DEVICE";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE_END: return "QUERY_DEVICE_END";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_OPEN_DEVICE: return "OPEN_DEVICE";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_CLOSE_DEVICE: return "CLOSE_DEVICE";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_RESET_DEVICE: return "RESET_DEVICE";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_DEVICESTATE: return "DEVICESTATE";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_SETDEV_GROUP: return "SETDEV_GROUP";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_SETPARAM: return "SETPARAM";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_GETPARAM: return "GETPARAM";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_START: return "QUERY_ONE_DSP_START";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_END: return "QUERY_ONE_DSP_END";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_QUERY_REMOVE_ONE_DSP_START: return "QUERY_REMOVE_ONE_DSP_START";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_QUERY_REMOVE_ONE_DSP_END: return "QUERY_REMOVE_ONE_DSP_END";

                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_CALLOUT: return "CALLOUT";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_CALLIN: return "CALLIN";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_ALERTCALL: return "ALERTCALL";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_ANSWERCALL: return "ANSWERCALL";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_LINKDEVICE: return "LINKDEVICE";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_UNLINKDEVICE: return "UNLINKDEVICE";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_CLEARCALL: return "CLEARCALL";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_ANALOG_INTERFACE: return "ANALOG_INTERFACE";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_CAS_MFC_START: return "CAS_MFC_START";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_CAS_MFC_END: return "CAS_MFC_END";

                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_JOINTOCONF: return "JOINTOCONF";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_LEAVEFROMCONF: return "LEAVEFROMCONF";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_CLEARCONF: return "CLEARCONF";


                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_PLAY: return "PLAY";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_INITINDEX: return "INITINDEX";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_BUILDINDEX: return "BUILDINDEX";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_CONTROLPLAY: return "CONTROLPLAY";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_RECORD: return "RECORD";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_CONTROLRECORD: return "CONTROLRECORD";

                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_SENDFAX: return "SENDFAX";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_RECVFAX: return "RECVFAX";

                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_SENDIODATA: return "SENDIODATA";
                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_RECVIODATA: return "RECVIODATA";

                case DJKeygoeIncludes.XMS_EVT_TYPE.XMS_EVT_UNIFAILURE: return "UNIFAILURE";
            }

            return "UNKNOWN";
        }
    }
}
