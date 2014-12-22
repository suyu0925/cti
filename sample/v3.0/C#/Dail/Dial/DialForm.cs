using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Dial
{
    public partial class DialForm : Form
    {
        public DJDailGlobals g_DJDialGlobals = new DJDailGlobals();

        public DialForm()
        {
            InitializeComponent();
        }

        /* Event class define*/
        public enum XMS_EVT_CLASS
        {
            XMS_EVT_CLASS_GENERAL = 0x0001,
            XMS_EVT_CLASS_CALLCONTROL = 0x0002,
            XMS_EVT_CLASS_CONFPROC = 0x0003,
            XMS_EVT_CLASS_VOIPPROC = 0x0004,
            XMS_EVT_CLASS_MEDIAPROC = 0x0005,
            XMS_EVT_CLASS_FAXPROC = 0x0006,
            XMS_EVT_CLASS_IOPROC = 0x0007,
            XMS_EVT_CLASS_SYSMONITOR = 0x0008,
            XMS_EVT_CLASS_UNIFAILURE = 0x0009,
        };

        /*Event type define */
        public enum XMS_EVT_TYPE
        {
            XMS_EVT_OPEN_STREAM = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x01),
            XMS_EVT_QUERY_DEVICE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x02),
            XMS_EVT_QUERY_DEVICE_END = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x03),
            XMS_EVT_OPEN_DEVICE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x04),
            XMS_EVT_CLOSE_DEVICE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x05),
            XMS_EVT_RESET_DEVICE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x06),
            XMS_EVT_DEVICESTATE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x07),
            XMS_EVT_SETDEV_GROUP = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x08),
            XMS_EVT_SETPARAM = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x09),
            XMS_EVT_GETPARAM = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x0A),
            XMS_EVT_QUERY_ONE_DSP_START = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x0B),
            XMS_EVT_QUERY_ONE_DSP_END = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x0C),
            XMS_EVT_QUERY_REMOVE_ONE_DSP_START = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x0D),
            XMS_EVT_QUERY_REMOVE_ONE_DSP_END = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x0E),
            XMS_EVT_OPEN_STREAM_EXT = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x0F),
            XMS_EVT_ACS_TIMER = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0xFF),

            XMS_EVT_CALLOUT = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x01),
            XMS_EVT_CALLIN = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x02),
            XMS_EVT_ALERTCALL = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x03),
            XMS_EVT_ANSWERCALL = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x04),
            XMS_EVT_LINKDEVICE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x05),
            XMS_EVT_UNLINKDEVICE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x06),
            XMS_EVT_CLEARCALL = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x07),
            XMS_EVT_ANALOG_INTERFACE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x08),
            XMS_EVT_CAS_MFC_START = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x09),
            XMS_EVT_CAS_MFC_END = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x0A),
            XMS_EVT_SENDSIGMSG = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x0B),
            XMS_EVT_SIGMON = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x0C),
            XMS_EVT_324Data = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x0D),

            XMS_EVT_JOINTOCONF = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CONFPROC << 16) + 0x01),
            XMS_EVT_LEAVEFROMCONF = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CONFPROC << 16) + 0x02),
            XMS_EVT_CLEARCONF = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CONFPROC << 16) + 0x03),

            XMS_EVT_PLAY = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x01),
            XMS_EVT_INITINDEX = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x02),
            XMS_EVT_BUILDINDEX = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x03),
            XMS_EVT_CONTROLPLAY = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x04),
            XMS_EVT_RECORD = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x05),
            XMS_EVT_CONTROLRECORD = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x06),
            XMS_EVT_RECORDCSP = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x07),
            XMS_EVT_CONTROLRECORDCSP = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x08),
            XMS_EVT_3GPP_PLAY = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x09),
            XMS_EVT_3GPP_CONTROLPLAY = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x0A),
            XMS_EVT_3GPP_RECORD = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x0B),
            XMS_EVT_3GPP_CONTROLRECORD = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x0C),
            XMS_EVT_PLAYCSPREQ = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x0D),

            XMS_EVT_SENDFAX = ((XMS_EVT_CLASS.XMS_EVT_CLASS_FAXPROC << 16) + 0x01),
            XMS_EVT_RECVFAX = ((XMS_EVT_CLASS.XMS_EVT_CLASS_FAXPROC << 16) + 0x02),

            XMS_EVT_SENDIODATA = ((XMS_EVT_CLASS.XMS_EVT_CLASS_IOPROC << 16) + 0x01),
            XMS_EVT_RECVIODATA = ((XMS_EVT_CLASS.XMS_EVT_CLASS_IOPROC << 16) + 0x02),

            XMS_EVT_CHGMONITORFILTER = ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR << 16) + 0x01),
            XMS_EVT_DEV_TIMER = ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR << 16) + 0x02),

            XMS_EVT_UNIFAILURE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_UNIFAILURE << 16) + 0x01),
        };

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

                case XMS_EVT_TYPE.XMS_EVT_CHGMONITORFILTER: return "CHGMONITORFILTER";

                case XMS_EVT_TYPE.XMS_EVT_UNIFAILURE: return "UNIFAILURE";
            }

            return "UNKNOWN";
        }

        public enum XMS_DEVMAIN_TYPE
        {
            XMS_DEVMAIN_VOICE = 0x02, /*Voice device*/
            XMS_DEVMAIN_FAX = 0x03, /*Fax device*/
            XMS_DEVMAIN_DIGITAL_PORT = 0x04, /*Digital Port device*/
            XMS_DEVMAIN_INTERFACE_CH = 0x05, /*Interface Ch device*/
            XMS_DEVMAIN_DSS1_LINK = 0x06, /*DSS1 Link device*/
            XMS_DEVMAIN_SS7_LINK = 0x07, /*SS7 Link device*/
            XMS_DEVMAIN_BOARD = 0x08, /*DSP Board device*/
            XMS_DEVMAIN_CTBUS_TS = 0x09, /*CTBus ts device*/
            XMS_DEVMAIN_VOIP = 0x0A, /*VoIP device*/
            XMS_DEVMAIN_CONFERENCE = 0x0C, /*Conference Group Device*/
            XMS_DEVMAIN_VIDEO = 0x0D, /*Video device*/
        };

        public enum XMS_INTERFACE_DEVSUB_TYPE
        {
            XMS_DEVSUB_BASE = 0x0,  /*Base*/
            XMS_DEVSUB_ANALOG_TRUNK = 0x01, /*Analog Trunk*/
            XMS_DEVSUB_ANALOG_USER = 0x02, /*Analog User*/
            XMS_DEVSUB_ANALOG_HIZ = 0x03, /*Analog Hiz*/
            XMS_DEVSUB_ANALOG_EMPTY = 0x04, /*Analog Empty*/
            XMS_DEVSUB_E1_PCM = 0x05, /*E1 PCM*/
            XMS_DEVSUB_E1_CAS = 0x06, /*E1 CAS*/
            XMS_DEVSUB_E1_DSS1 = 0x07, /*E1 DSS1*/
            XMS_DEVSUB_E1_SS7_TUP = 0x08, /*E1 SS7 TUP*/
            XMS_DEVSUB_E1_SS7_ISUP = 0x09, /*E1 SS7 ISUP*/
            XMS_DEVSUB_ANALOG_VOC2W = 0x0A, /*Voice only 2 wire*/
            XMS_DEVSUB_ANALOG_VOC4W = 0x0B, /*Voice only 4 wire*/
            XMS_DEVSUB_ANALOG_EM = 0x0C, /*EM control module*/
            XMS_DEVSUB_ANALOG_MAG = 0x0D, /*magnetic module*/
            XMS_DEVSUB_E1_DCH = 0x0E, /*E1 6D25B's Dchannel*/
            XMS_DEVSUB_E1_BCH = 0x0F, /*E1 6D25B's Bchannel*/
            XMS_DEVSUB_UNUSABLE = 0x10, /*unusable timeslot, such as ts0 of E1*/
            XMS_DEVSUB_HIZ_CAS = 0x11, /*Hiz Cas*/
            XMS_DEVSUB_HIZ_PRI = 0x12, /*Hiz Pri*/
            XMS_DEVSUB_HIZ_SS7 = 0x13, /*Hiz ss7*/
            XMS_DEVSUB_HIZ_PRI_LINK = 0x14, /*Hiz pri link*/
            XMS_DEVSUB_HIZ_SS7_64K_LINK = 0x15, /*Hiz ss7 64k link*/
            XMS_DEVSUB_HIZ_SS7_2M_LINK = 0x16, /*Hiz ss7 2M link*/
            XMS_DEVSUB_SS7_LINK = 0x17, /*ss7 link*/
        };

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
                g_DJDialGlobals.AllDeviceRes[iModID].pTrunk[iChID].iSeqID = listItem.Index;
                listItem.Name = iIDSum.ToString();
                listItem.SubItems.Add(iModID.ToString());
                listItem.SubItems.Add(iChID.ToString());
                switch ((XMS_INTERFACE_DEVSUB_TYPE)g_DJDialGlobals.AllDeviceRes[iModID].pTrunk[iChID].deviceID.m_s16DeviceSub)
                {
                    case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER:
                        listItem.SubItems.Add("USER");
                        break;

                    case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK:
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

                int iItem = g_DJDialGlobals.AllDeviceRes[iDspModID].pTrunk[iChID].iSeqID;

                // 4
                switch ((XMS_INTERFACE_DEVSUB_TYPE)g_DJDialGlobals.AllDeviceRes[iDspModID].pTrunk[iChID].deviceID.m_s16DeviceSub)
                {
                    case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER:
                        switch ((DJDataDefClass.USER_STATE)g_DJDialGlobals.AllDeviceRes[iDspModID].pTrunk[iChID].State)
                        {
                            case DJDataDefClass.USER_STATE.USER_CALLOUT:
                                listView_InterfInfo.Items[iItem].SubItems[4].Text = "USER_CALLOUT";
                                break;

                            case DJDataDefClass.USER_STATE.USER_FREE:
                                listView_InterfInfo.Items[iItem].SubItems[4].Text = "USER_FREE";
                                break;

                            case DJDataDefClass.USER_STATE.USER_LINK:
                                listView_InterfInfo.Items[iItem].SubItems[4].Text = "USER_LINK";
                                break;

                            case DJDataDefClass.USER_STATE.USER_OFFHOOK:
                                listView_InterfInfo.Items[iItem].SubItems[4].Text = "USER_OFFHOOK";
                                break;

                            case DJDataDefClass.USER_STATE.USER_WAIT_REMOVE:
                                listView_InterfInfo.Items[iItem].SubItems[4].Text = "USER_WAIT_REMOVE";
                                break;

                            case DJDataDefClass.USER_STATE.USER_WAITHANGUP:
                                listView_InterfInfo.Items[iItem].SubItems[4].Text = "USER_WAITHANGUP";
                                break;

                            case DJDataDefClass.USER_STATE.USER_WAITOPEN:
                                listView_InterfInfo.Items[iItem].SubItems[4].Text = "USER_WAITOPEN";
                                break;

                            default:
                                listView_InterfInfo.Items[iItem].SubItems[4].Text = "UNKNOWN";
                                break;
                        }
                        break;

                    default:
                        {
                            switch ((DJDataDefClass.TRUNK_STATE)g_DJDialGlobals.AllDeviceRes[iDspModID].pTrunk[iChID].State)
                            {
                                case DJDataDefClass.TRUNK_STATE.TRK_CALLOUT:
                                    listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_CALLOUT";
                                    break;

                                case DJDataDefClass.TRUNK_STATE.TRK_FAIL:
                                    listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_FAIL";
                                    break;

                                case DJDataDefClass.TRUNK_STATE.TRK_FREE:
                                    listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_FREE";
                                    break;

                                case DJDataDefClass.TRUNK_STATE.TRK_HANGUP:
                                    listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_HANGUP";
                                    break;

                                case DJDataDefClass.TRUNK_STATE.TRK_LINK:
                                    listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_LINK";
                                    break;

                                case DJDataDefClass.TRUNK_STATE.TRK_NOTHANDLE:
                                    listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_NOTHANDLE";
                                    break;

                                case DJDataDefClass.TRUNK_STATE.TRK_PLAYDTMF:
                                    listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_PLAYDTMF";
                                    break;

                                case DJDataDefClass.TRUNK_STATE.TRK_SIM_CALLOUT:
                                    listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_SIM_CALLOUT";
                                    break;

                                case DJDataDefClass.TRUNK_STATE.TRK_WAIT_REMOVE:
                                    listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_WAIT_REMOVE";
                                    break;

                                case DJDataDefClass.TRUNK_STATE.TRK_WAITOPEN:
                                    listView_InterfInfo.Items[iItem].SubItems[4].Text = "TRK_WAITOPEN";
                                    break;

                                default:
                                    listView_InterfInfo.Items[iItem].SubItems[4].Text = "UNKNOWN";
                                    break;
                            }
                        }
                        break;
                }

                // 5
                switch ((DJDataDefClass.DEVICE_CALL_STATE)g_DJDialGlobals.AllDeviceRes[iDspModID].pTrunk[iChID].iLineState)
                {
                    case DJDataDefClass.DEVICE_CALL_STATE.DCS_ALERTING:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_ALERTING";
                        break;

                    case DJDataDefClass.DEVICE_CALL_STATE.DCS_BLOCK:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_BLOCK";
                        break;

                    case DJDataDefClass.DEVICE_CALL_STATE.DCS_CALLIN:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_CALLIN";
                        break;

                    case DJDataDefClass.DEVICE_CALL_STATE.DCS_CALLOUT:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_CALLOUT";
                        break;

                    case DJDataDefClass.DEVICE_CALL_STATE.DCS_CONNECT:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_CONNECT";
                        break;

                    case DJDataDefClass.DEVICE_CALL_STATE.DCS_DISCONNECT:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_DISCONNECT";
                        break;

                    case DJDataDefClass.DEVICE_CALL_STATE.DCS_FREE:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_FREE";
                        break;

                    case DJDataDefClass.DEVICE_CALL_STATE.DCS_LOCAL_BLOCK:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_LOCAL_BLOCK";
                        break;

                    case DJDataDefClass.DEVICE_CALL_STATE.DCS_REMOTE_BLOCK:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_REMOTE_BLOCK";
                        break;

                    case DJDataDefClass.DEVICE_CALL_STATE.DCS_UNAVAILABLE:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_UNAVAILABLE";
                        break;

                    case DJDataDefClass.DEVICE_CALL_STATE.DCS_WAIT_FREE:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DCS_WAIT_FREE";
                        break;

                    case DJDataDefClass.DEVICE_CALL_STATE.DEVICE_COMMON_STATE_START:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "DEVICE_COMMON_STATE_START";
                        break;

                    default:
                        listView_InterfInfo.Items[iItem].SubItems[5].Text = "UNKNOWN";
                        break;
                }

                // 6 7 8
                fixed (char* pStr1 = g_DJDialGlobals.AllDeviceRes[iDspModID].pTrunk[iChID].CallerCode)
                {
                    string strCaller = new string(pStr1);
                    listView_InterfInfo.Items[iItem].SubItems[6].Text = strCaller;
                }
                fixed (char* pStr2 = g_DJDialGlobals.AllDeviceRes[iDspModID].pTrunk[iChID].CalleeCode)
                {
                    string strCallee = new string(pStr2);
                    listView_InterfInfo.Items[iItem].SubItems[7].Text = strCallee;
                }
                fixed (char* pStr3 = g_DJDialGlobals.AllDeviceRes[iDspModID].pTrunk[iChID].DtmfBuf)
                {
                    pStr3[g_DJDialGlobals.AllDeviceRes[iDspModID].pTrunk[iChID].DtmfCount] = '\0';
                    string strDtmf = new string(pStr3);
                    listView_InterfInfo.Items[iItem].SubItems[8].Text = strDtmf;
                }

                // 9
                if (g_DJDialGlobals.AllDeviceRes[iDspModID].pTrunk[iChID].LinkDevID.m_s8ModuleID > 0)
                {
                    string strLinkDevInfo = g_DJDialGlobals.AllDeviceRes[iDspModID].pTrunk[iChID].LinkDevID.m_s8ModuleID.ToString() + "." +
                        g_DJDialGlobals.AllDeviceRes[iDspModID].pTrunk[iChID].LinkDevID.m_s16ChannelID.ToString();
                    listView_InterfInfo.Items[iItem].SubItems[9].Text = strLinkDevInfo;
                }
                else
                {
                    listView_InterfInfo.Items[iItem].SubItems[9].Text = "";
                }

                // 10
                if (g_DJDialGlobals.AllDeviceRes[iDspModID].pTrunk[iChID].VocDevID.m_s8ModuleID > 0)
                {
                    string strVocDevInfo = g_DJDialGlobals.AllDeviceRes[iDspModID].pTrunk[iChID].VocDevID.m_s8ModuleID.ToString() + "." +
                        g_DJDialGlobals.AllDeviceRes[iDspModID].pTrunk[iChID].VocDevID.m_s16ChannelID.ToString();
                    listView_InterfInfo.Items[iItem].SubItems[10].Text = strVocDevInfo;
                }
                else
                {
                    listView_InterfInfo.Items[iItem].SubItems[10].Text = "";
                }
            }
        }

        public unsafe void EvtHandler(int esrParam)
        {
            //return;
            try
            {
                fixed (int* pAcsHandle = &g_DJDialGlobals.g_acsHandle)
                {
                    DJDataDefClass.Acs_Evt_t* pAcsEvt = (DJDataDefClass.Acs_Evt_t*)esrParam;

                    //EvtInfo
                    {
                        string strEvtInfo = "EVT(" + pAcsEvt->m_s32EvtSize.ToString() + ") : " + GetEventTypeString(pAcsEvt->m_s32EventType);
                        this.ShowEvtInfo(strEvtInfo);
                    }

                    //EvtProc
                    {
                        switch ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType)
                        {
                            case XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_START: break;

                            #region XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE
                            case XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE:
                                if ((g_DJDialGlobals.cfg_iPartWork == 0) || (pAcsEvt->m_DeviceID.m_s8ModuleID == g_DJDialGlobals.cfg_iPartWorkModuleID))
                                {
                                    DJDataDefClass.Acs_Dev_List_Head_t* pAcsDevList = (DJDataDefClass.Acs_Dev_List_Head_t*)((uint)pAcsEvt + sizeof(DJDataDefClass.Acs_Evt_t));

                                    //收到设备变化的事件，增加/删除 该设备资源
                                    {
                                        int s32Type = pAcsDevList->m_s32DeviceMain;
                                        int s32Num = pAcsDevList->m_s32DeviceNum;
                                        int s8DspModID = pAcsDevList->m_s32ModuleID;

                                        if ((s8DspModID > 0) && (s8DspModID < DJDataDefClass.MAX_DSP_MODULE_NUMBER_OF_XMS))
                                        {
                                            switch ((XMS_DEVMAIN_TYPE)s32Type)
                                            {
                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE:
                                                    {
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].pVoice = new DJDataDefClass.VOICE_STRUCT[s32Num];
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lVocNum = s32Num;
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lVocOpened = 0;
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lVocFreeNum = 0;
                                                        DJDataDefClass.DeviceID_t* pDev = (DJDataDefClass.DeviceID_t*)((byte*)pAcsDevList + sizeof(DJDataDefClass.Acs_Dev_List_Head_t));
                                                        for (int i = 0; i < s32Num; i++)
                                                        {
                                                            g_DJDialGlobals.AllDeviceRes[s8DspModID].pVoice[i].deviceID = pDev[i];
                                                            g_DJDialGlobals.AllDeviceRes[s8DspModID].pVoice[i].State = DJDataDefClass.VOICE_STATE.VOC_WAITOPEN;
                                                        }
                                                        pDev = null;
                                                    }
                                                    break;

                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT:
                                                    {
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].pPcm = new DJDataDefClass.PCM_STRUCT[s32Num];
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lPcmNum = s32Num;
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lPcmOpened = 0;
                                                        DJDataDefClass.DeviceID_t* pDev = (DJDataDefClass.DeviceID_t*)((byte*)pAcsDevList + sizeof(DJDataDefClass.Acs_Dev_List_Head_t));
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
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk = new DJDataDefClass.TRUNK_STRUCT[s32Num];
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lTrunkNum = s32Num;
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lTrunkOpened = 0;
                                                        DJDataDefClass.DeviceID_t* pDev = (DJDataDefClass.DeviceID_t*)((byte*)pAcsDevList + sizeof(DJDataDefClass.Acs_Dev_List_Head_t));
                                                        for (int i = 0; i < s32Num; i++)
                                                        {
                                                            g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk[i].deviceID = pDev[i];
                                                            g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk[i].State = DJDataDefClass.TRUNK_STATE.TRK_WAITOPEN;
                                                        }
                                                        pDev = null;
                                                    }
                                                    break;

                                                case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD:
                                                    {
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].lFlag = 1;
                                                        DJDataDefClass.DeviceID_t* pDev = (DJDataDefClass.DeviceID_t*)((byte*)pAcsDevList + sizeof(DJDataDefClass.Acs_Dev_List_Head_t));
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].deviceID = pDev[0];
                                                        pDev = null;
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].bOpenFlag = false;
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].bErrFlag = false;
                                                        g_DJDialGlobals.AllDeviceRes[s8DspModID].RemoveState = DJDataDefClass.REMOVE_STATE.DSP_REMOVE_STATE_NONE;
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
                            case XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_END:
                            case XMS_EVT_TYPE.XMS_EVT_QUERY_REMOVE_ONE_DSP_END:
                                if (pAcsEvt->m_s32EventType == (int)XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_END)
                                {
                                    g_DJDialGlobals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].lFlag = 1;		// 该DSP可以用了
                                    int s8DspModID = pAcsEvt->m_DeviceID.m_s8ModuleID;

                                    if (g_DJDialGlobals.cfg_iPartWork != 0 && s8DspModID != g_DJDialGlobals.cfg_iPartWorkModuleID)
                                    {
                                        return;
                                    }

                                    // Open Board
                                    int iResult = 0;

                                    //if (g_DJDialGlobals.cfg_iPartWorkModuleID == s8DspModID)
                                    {
                                        for (int i = 0; i < g_DJDialGlobals.AllDeviceRes[s8DspModID].lTrunkNum; ++i)
                                        {
                                            this.AddTrunkListItems(s8DspModID * 1000 + i);
                                        }
                                    }

                                    if (g_DJDialGlobals.AllDeviceRes[s8DspModID].bOpenFlag == false)	// 还没有Open
                                    {
                                        fixed (DJDataDefClass.DeviceID_t* pDev = &g_DJDialGlobals.AllDeviceRes[s8DspModID].deviceID)
                                        {
                                            int pDevValue = (int)pDev;
                                            iResult = axDJAcsAPI.CtsOpenDeviceEx(g_DJDialGlobals.g_acsHandle, pDevValue, 0);
                                            if (iResult == DJDataDefClass.ACSPOSITIVE_ACK)
                                            {
                                                this.ShowEvtInfo("CtsOpenDeviceEx (Board) Success");
                                            }
                                            else
                                            {
                                                this.ShowEvtInfo("CtsOpenDeviceEx (Board) Fail");
                                            }
                                        }

                                        // Open Voice
                                        for (int i = 0; i < g_DJDialGlobals.AllDeviceRes[s8DspModID].lVocNum; ++i)
                                        {
                                            fixed (DJDataDefClass.DeviceID_t* pDev = &g_DJDialGlobals.AllDeviceRes[s8DspModID].pVoice[i].deviceID)
                                            {
                                                int pDevValue = (int)pDev;
                                                iResult = axDJAcsAPI.CtsOpenDeviceEx(g_DJDialGlobals.g_acsHandle, pDevValue, 0);
                                                if (iResult == DJDataDefClass.ACSPOSITIVE_ACK)
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
                                        for (int i = 0; i < g_DJDialGlobals.AllDeviceRes[s8DspModID].lPcmNum; ++i)
                                        {
                                            fixed (DJDataDefClass.DeviceID_t* pDev = &g_DJDialGlobals.AllDeviceRes[s8DspModID].pPcm[i].deviceID)
                                            {
                                                int pDevValue = (int)pDev;
                                                iResult = axDJAcsAPI.CtsOpenDeviceEx(g_DJDialGlobals.g_acsHandle, pDevValue, 0);
                                                if (iResult == DJDataDefClass.ACSPOSITIVE_ACK)
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
                                        for (int i = 0; i < g_DJDialGlobals.AllDeviceRes[s8DspModID].lTrunkNum; ++i)
                                        {
                                            fixed (DJDataDefClass.DeviceID_t* pDev = &g_DJDialGlobals.AllDeviceRes[s8DspModID].pTrunk[i].deviceID)
                                            {
                                                int pDevValue = (int)pDev;
                                                iResult = axDJAcsAPI.CtsOpenDeviceEx(g_DJDialGlobals.g_acsHandle, pDevValue, 0);
                                                if (iResult == DJDataDefClass.ACSPOSITIVE_ACK)
                                                {
                                                    this.ShowEvtInfo("CtsOpenDeviceEx (Interface) Success");
                                                }
                                                else
                                                {
                                                    this.ShowEvtInfo("CtsOpenDeviceEx (Interface) Fail");
                                                }
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    g_DJDialGlobals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].lFlag = 0;		// 该DSP已经Remove完毕
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
                                            }
                                            break;

                                        #region XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH
                                        case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH:
                                            {
                                                fixed (DJDataDefClass.TRUNK_STRUCT* pOneTrunk = &g_DJDialGlobals.AllDeviceRes[iDspModuleID].pTrunk[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                                {
                                                    pOneTrunk->deviceID.m_CallID = pAcsEvt->m_DeviceID.m_CallID;		// this line is very important, must before all operation

                                                    if (pOneTrunk->deviceID.m_s16DeviceSub == (int)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER
                                                        /*|| pOneTrunk->deviceID.m_s16DeviceSub == (int)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK*/)
                                                    {
                                                        pOneTrunk->State = DJDataDefClass.TRUNK_STATE.TRK_FREE;
                                                        pOneTrunk->UserState = DJDataDefClass.USER_STATE.USER_FREE;
                                                        pOneTrunk->VocDevID.m_s8ModuleID = 0;
                                                        pOneTrunk->LinkDevID.m_s8ModuleID = 0;
                                                        pOneTrunk->DtmfCount = 0;
                                                        pOneTrunk->DtmfBuf[0] = '\0';
                                                        pOneTrunk->CallerCode[0] = '\0';
                                                        pOneTrunk->CalleeCode[0] = '\0';

                                                        DJDataDefClass.DeviceID_t* pDev = &pAcsEvt->m_DeviceID;
                                                        int pDevValue = (int)pDev;
                                                        axDJAcsAPI.CtsResetDeviceEx(g_DJDialGlobals.g_acsHandle, pDevValue, 0);
                                                        axDJAcsAPI.CtsGetDevStateEx(g_DJDialGlobals.g_acsHandle, pDevValue, 0);
                                                        pDev = null;
                                                        pOneTrunk->State = DJDataDefClass.TRUNK_STATE.TRK_NOTHANDLE;// 中继通道不处理该user通道
                                                    }
                                                    else
                                                    {
                                                        pOneTrunk->State = DJDataDefClass.TRUNK_STATE.TRK_FREE;
                                                        pOneTrunk->VocDevID.m_s8ModuleID = 0;
                                                        pOneTrunk->LinkDevID.m_s8ModuleID = 0;
                                                        pOneTrunk->DtmfCount = 0;
                                                        pOneTrunk->DtmfBuf[0] = '\0';
                                                        pOneTrunk->CallerCode[0] = '\0';
                                                        pOneTrunk->CalleeCode[0] = '\0';

                                                        DJDataDefClass.DeviceID_t* pDev = &pAcsEvt->m_DeviceID;
                                                        int pDevValue = (int)pDev;
                                                        axDJAcsAPI.CtsResetDeviceEx(g_DJDialGlobals.g_acsHandle, pDevValue, 0);
                                                        axDJAcsAPI.CtsGetDevStateEx(g_DJDialGlobals.g_acsHandle, pDevValue, 0);
                                                        pDev = null;
                                                    }

                                                    ++g_DJDialGlobals.AllDeviceRes[iDspModuleID].lTrunkOpened;

                                                    if (pOneTrunk->deviceID.m_s16DeviceSub == (int)XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
                                                    {
                                                        DJDataDefClass.DeviceID_t FreeVocDeviceID = new DJDataDefClass.DeviceID_t();
                                                        DJDataDefClass.CmdParamData_AnalogTrunk_t cmdAnalogTrunk = new DJDataDefClass.CmdParamData_AnalogTrunk_t();
                                                        short u16ParamType = 0;//ANALOGTRUNK_PARAM_UNIPARAM
                                                        short u16ParamSize = (short)sizeof(DJDataDefClass.CmdParamData_AnalogTrunk_t);

                                                        cmdAnalogTrunk.m_u8CallerIdOption = 1;//XMS_ANALOG_TRUNK_CALLERID_FSK
                                                        cmdAnalogTrunk.m_u8CallInRingCount = 3;
                                                        cmdAnalogTrunk.m_u16Rfu1 = 0;
                                                        cmdAnalogTrunk.m_u8DialtoneDetect = 1;//XMS_ANALOG_TRUNK_DIALTONE_DETECT
                                                        cmdAnalogTrunk.m_u8CallOutMethod = 1;//XMS_ANALOG_TRUNK_CALLOUT_NORMAL_PROGRESS //XMS_ANALOG_TRUNK_CALLOUT_POLARITY_REVERSE;
                                                        cmdAnalogTrunk.m_u16Rfu2 = 0;

                                                        fixed (int* pacsHandle = &g_DJDialGlobals.g_acsHandle)
                                                        {
                                                            DJDataDefClass.CmdParamData_AnalogTrunk_t* p = &cmdAnalogTrunk;
                                                            int pValue = (int)p;
                                                            int iChID = SearchOneFreeVoice(pOneTrunk->deviceID.m_s8ModuleID);
                                                            if (iChID >= 0)
                                                            {
                                                                FreeVocDeviceID = g_DJDialGlobals.AllDeviceRes[pOneTrunk->deviceID.m_s8ModuleID].pVoice[iChID].deviceID;
                                                                cmdAnalogTrunk.m_VocDevID = FreeVocDeviceID;

                                                                //指定绑定关系
                                                                pOneTrunk->VocDevID = FreeVocDeviceID;
                                                                g_DJDialGlobals.AllDeviceRes[pOneTrunk->deviceID.m_s8ModuleID].pVoice[iChID].UsedDevID = pOneTrunk->deviceID;

                                                                //DrawMain_VocInfo ( pOneTrunk );
                                                                DJDataDefClass.DeviceID_t* pDev = &pOneTrunk->deviceID;
                                                                int pDevValue = (int)pDev;
                                                                int r = axDJAcsAPI.CtsSetParamEx(g_DJDialGlobals.g_acsHandle, pDevValue, u16ParamType, u16ParamSize, pValue);
                                                                string strMsg = "Set AnalogTrunk  ret = " + r.ToString();
                                                                ShowEvtInfo(strMsg);
                                                            }
                                                        }
                                                    }

                                                    //ShowInfo
                                                    int iIDSum = iDspModuleID * 1000 + pAcsEvt->m_DeviceID.m_s16ChannelID;
                                                    ShowTrunkListItems(iIDSum);
                                                }
                                            }
                                            break;
                                        #endregion

                                        case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE:
                                            {
                                                g_DJDialGlobals.AllDeviceRes[iDspModuleID].pVoice[pAcsEvt->m_DeviceID.m_s16ChannelID].deviceID.m_CallID = pAcsEvt->m_DeviceID.m_CallID;
                                                ++g_DJDialGlobals.AllDeviceRes[iDspModuleID].lVocOpened;
                                                ++g_DJDialGlobals.AllDeviceRes[iDspModuleID].lVocFreeNum;
                                                g_DJDialGlobals.AllDeviceRes[iDspModuleID].pVoice[pAcsEvt->m_DeviceID.m_s16ChannelID].State = DJDataDefClass.VOICE_STATE.VOC_FREE;
                                            }
                                            break;

                                        #region XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT
                                        case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT:
                                            {
                                                g_DJDialGlobals.AllDeviceRes[iDspModuleID].pPcm[pAcsEvt->m_DeviceID.m_s16ChannelID].deviceID.m_CallID = pAcsEvt->m_DeviceID.m_CallID;
                                                DJDataDefClass.DeviceID_t* pDev = &pAcsEvt->m_DeviceID;
                                                int pDevValue = (int)pDev;
                                                axDJAcsAPI.CtsResetDeviceEx(g_DJDialGlobals.g_acsHandle, pDevValue, 0);
                                                axDJAcsAPI.CtsGetDevStateEx(g_DJDialGlobals.g_acsHandle, pDevValue, 0);
                                                pDev = null;
                                                ++g_DJDialGlobals.AllDeviceRes[iDspModuleID].lPcmOpened;
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
                                break;

                            #region XMS_EVT_TYPE.XMS_EVT_DEVICESTATE
                            case XMS_EVT_TYPE.XMS_EVT_DEVICESTATE:
                                {
                                    DJDataDefClass.Acs_GeneralProc_Data* pGeneralData =
                                        (DJDataDefClass.Acs_GeneralProc_Data*)((int)pAcsEvt + sizeof(DJDataDefClass.Acs_Evt_t));
                                    if (pAcsEvt->m_DeviceID.m_s16DeviceMain == (short)XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH)
                                    {
                                        fixed (DJDataDefClass.TRUNK_STRUCT* pOneTrunk =
                                            &g_DJDialGlobals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pTrunk[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                        {
                                            pOneTrunk->iLineState = pGeneralData->m_s32DeviceState;

                                            //ShowInfo
                                            int iIDSum = pOneTrunk->deviceID.m_s8ModuleID * 1000 + pOneTrunk->deviceID.m_s16ChannelID;
                                            ShowTrunkListItems(iIDSum);
                                        }
                                    }
                                    /*
                                    if (pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_DIGITAL_PORT)
                                    {
                                        pOnePcm = &M_OnePcm(pAcsEvt->m_DeviceID);

                                        pOnePcm->u8E1Type = (pGeneralData->m_s32DeviceState >> 16) & 0xFF;
                                        pOnePcm->s32AlarmVal = (pGeneralData->m_s32DeviceState & 0xFFFF);

                                        DrawPcm_TypeAndAlarm(pOnePcm);
                                    }
                                    */
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
                                    fixed (DJDataDefClass.TRUNK_STRUCT* pOneTrunk = &g_DJDialGlobals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pTrunk[pAcsEvt->m_DeviceID.m_s16ChannelID])
                                    {
                                        ChannelWork(pOneTrunk, pAcsEvt);
                                    }
                                }
                                else if ((XMS_DEVMAIN_TYPE)pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE)
                                {
                                    fixed (DJDataDefClass.DeviceID_t* pDevID = &g_DJDialGlobals.AllDeviceRes[pAcsEvt->m_DeviceID.m_s8ModuleID].pVoice[pAcsEvt->m_DeviceID.m_s16ChannelID].UsedDevID)
                                    {
                                        if (pDevID->m_s8ModuleID == 0)
                                        {
                                            break;
                                        }

                                        if ((XMS_DEVMAIN_TYPE)pDevID->m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH)
                                        {
                                            fixed (DJDataDefClass.TRUNK_STRUCT* pOneTrunk = &g_DJDialGlobals.AllDeviceRes[pDevID->m_s8ModuleID].pTrunk[pDevID->m_s16ChannelID])
                                            {
                                                ChannelWork(pOneTrunk, pAcsEvt);
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
            catch(Exception)
                {}
            return;
        }

        public unsafe void UserWork(DJDataDefClass.TRUNK_STRUCT* pOneUser, DJDataDefClass.Acs_Evt_t* pAcsEvt)
        {
            if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CLEARCALL)	/*拆线事件*/
            {
                if ((pOneUser->UserState != DJDataDefClass.USER_STATE.USER_FREE) && (pOneUser->UserState != DJDataDefClass.USER_STATE.USER_WAIT_REMOVE))
                {
                    ResetUser(pOneUser, pAcsEvt);

                    //ShowInfo
                    int iIDSum = pOneUser->deviceID.m_s8ModuleID * 1000 + pOneUser->deviceID.m_s16ChannelID;
                    ShowTrunkListItems(iIDSum);
                    return;
                }
            }

            switch (pOneUser->UserState)
            {
                case DJDataDefClass.USER_STATE.USER_FREE:
                    if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CALLIN)	/*用户通道摘机事件*/
                    {
                        int iChID = SearchOneFreeVoice(pOneUser->deviceID.m_s8ModuleID);
                        if (iChID >= 0)
                        {
                            pOneUser->VocDevID = g_DJDialGlobals.AllDeviceRes[pOneUser->deviceID.m_s8ModuleID].pVoice[iChID].deviceID;
                            g_DJDialGlobals.AllDeviceRes[pOneUser->deviceID.m_s8ModuleID].pVoice[iChID].UsedDevID = pOneUser->deviceID;

                            DJDataDefClass.DeviceID_t* pDev1 = &pOneUser->deviceID;
                            DJDataDefClass.DeviceID_t* pDev2 = &pOneUser->VocDevID;
                            int pDev1Value = (int)pDev1;
                            int pDev2Value = (int)pDev2;
                            axDJAcsAPI.CtsLinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev1Value, pDev2Value, 0);
                            axDJAcsAPI.CtsLinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev2Value, pDev1Value, 0);

                            PlayTone(&pOneUser->VocDevID, 0);		// dial tone

                            pOneUser->UserState = DJDataDefClass.USER_STATE.USER_OFFHOOK;

                            //ShowInfo
                            int iIDSum = pOneUser->deviceID.m_s8ModuleID * 1000 + pOneUser->deviceID.m_s16ChannelID;
                            ShowTrunkListItems(iIDSum);
                        }
                    }
                    break;

                case DJDataDefClass.USER_STATE.USER_OFFHOOK:
                    char TmpDtmf = My_GetDtmfCode(pAcsEvt);
                    if (TmpDtmf != '\0')								//DTMF按键
                    {
                        pOneUser->DtmfBuf[pOneUser->DtmfCount++] = TmpDtmf;
                        if (pOneUser->DtmfCount >= 32)
                        {
                            pOneUser->DtmfCount = 31;
                        }
                        pOneUser->DtmfBuf[pOneUser->DtmfCount] = '\0';

                        PlayTone(&pOneUser->VocDevID, -1);

                        if (pOneUser->DtmfCount >= g_DJDialGlobals.cfg_iCalledLen)
                        {
                            int iChID = SearchOneFreeTrunk(pOneUser->deviceID.m_s8ModuleID);
                            if (iChID >= 0)
                            {
                                fixed (DJDataDefClass.DeviceID_t* pDev = &g_DJDialGlobals.AllDeviceRes[pOneUser->deviceID.m_s8ModuleID].pTrunk[iChID].deviceID)
                                {
                                    int iDevValue = (int)pDev;
                                    fixed (char* pCalling = g_DJDialGlobals.cfg_CallingNum)
                                    {
                                        string Calling = new string(pCalling);
                                        fixed (byte* byCalling = g_DJDialGlobals.g_CallNumBuf.g_byCalling)
                                        {
                                            int j = 0;
                                            for (j = 0; j < Calling.Length; ++j)
                                            {
                                                byCalling[j] = (byte)Calling[j];
                                                pOneUser->CallerCode[j] = Calling[j];
                                            }
                                            byCalling[j] = 0;
                                            pOneUser->CallerCode[j] = '\0';
                                            char* pCallee = pOneUser->DtmfBuf;
                                            string Callee = new string(pCallee);
                                            fixed (byte* byCallee = g_DJDialGlobals.g_CallNumBuf.g_byCallee)
                                            {
                                                for (j = 0; j < Callee.Length; ++j)
                                                {
                                                    byCallee[j] = (byte)Callee[j];
                                                    pOneUser->CalleeCode[j] = Callee[j];
                                                }
                                                byCallee[j] = 0;
                                                pOneUser->CalleeCode[j] = '\0';
                                                int iCalling = (int)byCalling;
                                                int iCallee = (int)byCallee;
                                                int r = axDJAcsAPI.CtsMakeCallOutEx(g_DJDialGlobals.g_acsHandle, iDevValue, iCalling, iCallee, 0);
                                                if (r > 0)
                                                {
                                                    // call out 成功
                                                    fixed (DJDataDefClass.TRUNK_STRUCT* pLinkTrunk =
                                                        &g_DJDialGlobals.AllDeviceRes[pDev->m_s8ModuleID].pTrunk[pDev->m_s16ChannelID])
                                                    {
                                                        pOneUser->LinkDevID = pLinkTrunk->deviceID;
                                                        pLinkTrunk->LinkDevID = pOneUser->deviceID;

                                                        for (j = 0; j < g_DJDialGlobals.cfg_CallingNum.Length && j < 20; ++j)
                                                        {
                                                            pLinkTrunk->CallerCode[j] = g_DJDialGlobals.cfg_CallingNum[j];
                                                        }
                                                        if (j >= 20)
                                                        {
                                                            pLinkTrunk->CallerCode[19] = '\0';
                                                        }
                                                        else
                                                        {
                                                            pLinkTrunk->CallerCode[j] = '\0';
                                                        }
                                                        for (j = 0; j < pOneUser->DtmfCount && j < 20; ++j)
                                                        {
                                                            pLinkTrunk->CalleeCode[j] = pOneUser->DtmfBuf[j];
                                                        }
                                                        if (j >= 20)
                                                        {
                                                            pLinkTrunk->CalleeCode[19] = '\0';
                                                        }
                                                        else
                                                        {
                                                            pLinkTrunk->CalleeCode[j] = '\0';
                                                        }

                                                        pOneUser->UserState = DJDataDefClass.USER_STATE.USER_CALLOUT;
                                                        pLinkTrunk->State = DJDataDefClass.TRUNK_STATE.TRK_CALLOUT;

                                                        //ShowInfo
                                                        int iIDSum = pOneUser->deviceID.m_s8ModuleID * 1000 + pOneUser->deviceID.m_s16ChannelID;
                                                        ShowTrunkListItems(iIDSum);
                                                        iIDSum = pLinkTrunk->deviceID.m_s8ModuleID * 1000 + pLinkTrunk->deviceID.m_s16ChannelID;
                                                        ShowTrunkListItems(iIDSum);
                                                    }
                                                    break;
                                                }
                                                else
                                                {
                                                    string strMsgInfo = "XMS_ctsMakeCallOut() FAIL! ret = " + r.ToString();
                                                    ShowEvtInfo(strMsgInfo);
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            PlayTone(&pOneUser->VocDevID, 2);		// busy tone
                            pOneUser->UserState = DJDataDefClass.USER_STATE.USER_WAITHANGUP;

                            //ShowInfo
                            int iIDSum1 = pOneUser->deviceID.m_s8ModuleID * 1000 + pOneUser->deviceID.m_s16ChannelID;
                            ShowTrunkListItems(iIDSum1);
                        }
                    }
                    break;

                case DJDataDefClass.USER_STATE.USER_WAITHANGUP:
                    {
                        PlayTone(&pOneUser->VocDevID, -1);
                        pOneUser->UserState = DJDataDefClass.USER_STATE.USER_FREE;

                        //ShowInfo
                        int iIDSum = pOneUser->deviceID.m_s8ModuleID * 1000 + pOneUser->deviceID.m_s16ChannelID;
                        ShowTrunkListItems(iIDSum);
                    }
                    break;

                default:
                    break;
            }
        }

        public bool IsTrunk(short s16DevSub)
        {

            if ((s16DevSub == (short)DJDataDefClass.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_PCM)
                || (s16DevSub == (short)DJDataDefClass.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_CAS)
                || (s16DevSub == (short)DJDataDefClass.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_DSS1)
                || (s16DevSub == (short)DJDataDefClass.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_TUP)
                || (s16DevSub == (short)DJDataDefClass.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_ISUP)
                || (s16DevSub == (short)DJDataDefClass.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK)
                )
            {
                return true;
            }

            return false;
        }

        public int iBase = 0;

        public unsafe int SearchOneFreeTrunk(int iModID)
        {
            for (int i = iBase + 1; i < g_DJDialGlobals.AllDeviceRes[iModID].lTrunkNum; ++i)
            {
                if ((DJDataDefClass.DEVICE_CALL_STATE)g_DJDialGlobals.AllDeviceRes[iModID].pTrunk[i].iLineState == DJDataDefClass.DEVICE_CALL_STATE.DCS_FREE
                    && (DJDataDefClass.TRUNK_STATE)g_DJDialGlobals.AllDeviceRes[iModID].pTrunk[i].State == DJDataDefClass.TRUNK_STATE.TRK_FREE
                    && IsTrunk(g_DJDialGlobals.AllDeviceRes[iModID].pTrunk[i].deviceID.m_s16DeviceSub))
                {
                    iBase = i;
                    return iBase;
                }
            }

            for (int i = 0; i <= iBase && i < g_DJDialGlobals.AllDeviceRes[iModID].lTrunkNum; ++i)
            {
                if ((DJDataDefClass.DEVICE_CALL_STATE)g_DJDialGlobals.AllDeviceRes[iModID].pTrunk[i].iLineState == DJDataDefClass.DEVICE_CALL_STATE.DCS_FREE
                    && (DJDataDefClass.TRUNK_STATE)g_DJDialGlobals.AllDeviceRes[iModID].pTrunk[i].State == DJDataDefClass.TRUNK_STATE.TRK_FREE
                    && IsTrunk(g_DJDialGlobals.AllDeviceRes[iModID].pTrunk[i].deviceID.m_s16DeviceSub))
                {
                    iBase = i;
                    return iBase;
                }
            }

            return -1;
        }

        public unsafe int SearchOneFreeTrunk(/*int iModID*/)
        {
            for (int i = iBase + 1; i < listView_InterfInfo.Items.Count/*g_DJDialGlobals.AllDeviceRes[iModID].lTrunkNum*/; ++i)
            {
                int iIDSum = int.Parse(listView_InterfInfo.Items[i].Name);
                int iModID = iIDSum / 1000;
                int iChID = iIDSum % 1000;
                if ((DJDataDefClass.DEVICE_CALL_STATE)g_DJDialGlobals.AllDeviceRes[iModID].pTrunk[iChID].iLineState == DJDataDefClass.DEVICE_CALL_STATE.DCS_FREE
                    && (DJDataDefClass.TRUNK_STATE)g_DJDialGlobals.AllDeviceRes[iModID].pTrunk[iChID].State == DJDataDefClass.TRUNK_STATE.TRK_FREE
                    && IsTrunk(g_DJDialGlobals.AllDeviceRes[iModID].pTrunk[iChID].deviceID.m_s16DeviceSub))
                {
                    iBase = i;
                    return iBase;
                }
            }

            for (int i = 0; i <= iBase && i < listView_InterfInfo.Items.Count/*g_DJDialGlobals.AllDeviceRes[iModID].lTrunkNum*/; ++i)
            {
                int iIDSum = int.Parse(listView_InterfInfo.Items[i].Name);
                int iModID = iIDSum / 1000;
                int iChID = iIDSum % 1000;
                if ((DJDataDefClass.DEVICE_CALL_STATE)g_DJDialGlobals.AllDeviceRes[iModID].pTrunk[iChID].iLineState == DJDataDefClass.DEVICE_CALL_STATE.DCS_FREE
                    && (DJDataDefClass.TRUNK_STATE)g_DJDialGlobals.AllDeviceRes[iModID].pTrunk[iChID].State == DJDataDefClass.TRUNK_STATE.TRK_FREE
                    && IsTrunk(g_DJDialGlobals.AllDeviceRes[iModID].pTrunk[iChID].deviceID.m_s16DeviceSub))
                {
                    iBase = i;
                    return iBase;
                }
            }

            return -1;
        }

        public unsafe char My_GetDtmfCode(DJDataDefClass.Acs_Evt_t* pAcsEvt)
        {
            if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_RECVIODATA)	/*IO Data事件*/
            {
                DJDataDefClass.Acs_IO_Data* pIOData = (DJDataDefClass.Acs_IO_Data*)((int)pAcsEvt + sizeof(DJDataDefClass.Acs_Evt_t));

                if (((DJDataDefClass.XMS_MEDIA_IO_TYPE)pIOData->m_u16IoType == DJDataDefClass.XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF)
                    && (pIOData->m_u16IoDataLen > 0))
                {
                    byte* p = (byte*)((int)pAcsEvt + sizeof(DJDataDefClass.Acs_Evt_t) + sizeof(DJDataDefClass.Acs_IO_Data));
                    byte pValue = *p;
                    char pChar = (char)pValue;

                    return pChar;
                }
            }

            return '\0';	// not a good DTMF
        }

        public unsafe void ResetUser(DJDataDefClass.TRUNK_STRUCT* pOneUser, DJDataDefClass.Acs_Evt_t* pAcsEvt)
        {
            if (pOneUser->VocDevID.m_s8ModuleID > 0)
            {
                DJDataDefClass.DeviceID_t* pDev1 = &pOneUser->deviceID;
                DJDataDefClass.DeviceID_t* pDev2 = &pOneUser->VocDevID;
                int pDev1Value = (int)pDev1;
                int pDev2Value = (int)pDev2;
                axDJAcsAPI.CtsUnlinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev1Value, pDev2Value, 0);
                axDJAcsAPI.CtsUnlinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev2Value, pDev1Value, 0);

                FreeOneFreeVoice(pOneUser->VocDevID.m_s8ModuleID, pOneUser->VocDevID.m_s16ChannelID);

                pOneUser->VocDevID.m_s8ModuleID = 0;
            }

            if (pOneUser->LinkDevID.m_s8ModuleID > 0)
            {
                DJDataDefClass.DeviceID_t* pDev1 = &pOneUser->deviceID;
                DJDataDefClass.DeviceID_t* pDev2 = &pOneUser->LinkDevID;
                int pDev1Value = (int)pDev1;
                int pDev2Value = (int)pDev2;
                axDJAcsAPI.CtsUnlinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev1Value, pDev2Value, 0);
                axDJAcsAPI.CtsUnlinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev2Value, pDev1Value, 0);

                fixed (DJDataDefClass.TRUNK_STRUCT* pLinkTrunk =
                                    &g_DJDialGlobals.AllDeviceRes[pOneUser->LinkDevID.m_s8ModuleID].pTrunk[pOneUser->LinkDevID.m_s16ChannelID])
                {
                    axDJAcsAPI.CtsClearCallEx(g_DJDialGlobals.g_acsHandle, pDev2Value, 0, 0);
                    pLinkTrunk->LinkDevID.m_s8ModuleID = 0; // 0表示还没有分配LinkDevID
                }
            }

            pOneUser->DtmfCount = 0;
            pOneUser->UserState = DJDataDefClass.USER_STATE.USER_FREE;
        }

        public unsafe void ResetTrunk(DJDataDefClass.TRUNK_STRUCT* pOneTrunk, DJDataDefClass.Acs_Evt_t* pAcsEvt)
        {
            if (pOneTrunk->LinkDevID.m_s8ModuleID > 0)
            {
                DJDataDefClass.DeviceID_t* pDev1 = &pOneTrunk->deviceID;
                DJDataDefClass.DeviceID_t* pDev2 = &pOneTrunk->LinkDevID;
                int pDev1Value = (int)pDev1;
                int pDev2Value = (int)pDev2;
                axDJAcsAPI.CtsUnlinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev1Value, pDev2Value, 0);
                axDJAcsAPI.CtsUnlinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev2Value, pDev1Value, 0);

                fixed (DJDataDefClass.TRUNK_STRUCT* pLinkUser =
                                    &g_DJDialGlobals.AllDeviceRes[pOneTrunk->LinkDevID.m_s8ModuleID].pTrunk[pOneTrunk->LinkDevID.m_s16ChannelID])
                {
                    DJDataDefClass.DeviceID_t* pDev3 = &pLinkUser->VocDevID;
                    DJDataDefClass.DeviceID_t* pDev4 = &pLinkUser->deviceID;
                    int pDev3Value = (int)pDev3;
                    int pDev4Value = (int)pDev4;
                    axDJAcsAPI.CtsLinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev3Value, pDev4Value, 0);
                    axDJAcsAPI.CtsLinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev4Value, pDev3Value, 0);

                    PlayTone(&pLinkUser->VocDevID, 2);		// busy tone
                }

                pOneTrunk->LinkDevID.m_s8ModuleID = 0;  // 没有LinkID
            }

            if (pOneTrunk->VocDevID.m_s8ModuleID > 0)
            {
                DJDataDefClass.DeviceID_t* pDev1 = &pOneTrunk->deviceID;
                DJDataDefClass.DeviceID_t* pDev2 = &pOneTrunk->VocDevID;
                int pDev1Value = (int)pDev1;
                int pDev2Value = (int)pDev2;
                axDJAcsAPI.CtsUnlinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev1Value, pDev2Value, 0);
                axDJAcsAPI.CtsUnlinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev2Value, pDev1Value, 0);

                FreeOneFreeVoice(pOneTrunk->VocDevID.m_s8ModuleID, pOneTrunk->VocDevID.m_s16ChannelID);

                g_DJDialGlobals.AllDeviceRes[pOneTrunk->VocDevID.m_s8ModuleID].pVoice[pOneTrunk->VocDevID.m_s16ChannelID].UsedDevID.m_s8ModuleID = 0;
                pOneTrunk->VocDevID.m_s8ModuleID = 0;
            }

            pOneTrunk->State = DJDataDefClass.TRUNK_STATE.TRK_FREE;
            pOneTrunk->DtmfCount = 0;
        }

        public unsafe int SearchOneFreeVoice(int iDSPModID)
        {
            for (int i = 0; i < g_DJDialGlobals.AllDeviceRes[iDSPModID].lVocNum; ++i)
            {
                fixed (DJDataDefClass.VOICE_STRUCT* pOneVoice = &g_DJDialGlobals.AllDeviceRes[iDSPModID].pVoice[i])
                {
                    if (pOneVoice->State == DJDataDefClass.VOICE_STATE.VOC_FREE)
                    {
                        pOneVoice->State = DJDataDefClass.VOICE_STATE.VOC_USED;

                        --g_DJDialGlobals.AllDeviceRes[iDSPModID].lVocFreeNum;

                        return i;
                    }
                }
            }

            return -1;
        }

        public unsafe void FreeOneFreeVoice(int iModID, int iChID)
        {
            g_DJDialGlobals.AllDeviceRes[iModID].pVoice[iChID].State = DJDataDefClass.VOICE_STATE.VOC_FREE;
            ++g_DJDialGlobals.AllDeviceRes[iModID].lVocFreeNum;
        }

        public unsafe void SpecialForCas(DJDataDefClass.TRUNK_STRUCT* pOneTrunk, DJDataDefClass.Acs_Evt_t* pAcsEvt)
        {
            if ((DJDataDefClass.XMS_INTERFACE_DEVSUB_TYPE)pOneTrunk->deviceID.m_s16DeviceSub != DJDataDefClass.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_CAS)
            {
                return;
            }

            if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CAS_MFC_START)	/* 开始接收MFC，需要一个Voc设备*/
            {
                int iFreeVoc = SearchOneFreeVoice(pOneTrunk->deviceID.m_s8ModuleID);
                if (iFreeVoc >= 0)
                {
                    pOneTrunk->VocDevID = g_DJDialGlobals.AllDeviceRes[pOneTrunk->deviceID.m_s8ModuleID].pVoice[iFreeVoc].deviceID;
                    g_DJDialGlobals.AllDeviceRes[pOneTrunk->deviceID.m_s8ModuleID].pVoice[iFreeVoc].UsedDevID = pOneTrunk->deviceID;

                    g_DJDialGlobals.g_Param_CAS.m_VocDevID = pOneTrunk->VocDevID;
                    fixed (int* p = &g_DJDialGlobals.g_acsHandle)
                    {
                        DJDataDefClass.DeviceID_t* pDev = &pOneTrunk->deviceID;
                        int pDevValue = (int)pDev;
                        fixed (DJDataDefClass.CmdParamData_CAS_t* pParam = &g_DJDialGlobals.g_Param_CAS)
                        {
                            int pParamValue = (int)pParam;
                            int iLen = sizeof(DJDataDefClass.CmdParamData_CAS_t);
                            axDJAcsAPI.CtsSetParamEx(g_DJDialGlobals.g_acsHandle, pDevValue, 0,
                                (short)iLen, pParamValue); // CAS_PARAM_UNIPARAM = 0
                        }
                    }
                }
            }

            if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CAS_MFC_END)	// 接收MFC完毕，释放Voc设备
            {
                FreeOneFreeVoice(pOneTrunk->VocDevID.m_s8ModuleID, pOneTrunk->VocDevID.m_s16ChannelID);

                // 0表示还没有分配 Device
                g_DJDialGlobals.AllDeviceRes[pOneTrunk->VocDevID.m_s8ModuleID].pVoice[pOneTrunk->VocDevID.m_s16ChannelID].UsedDevID.m_s8ModuleID = 0;
                pOneTrunk->VocDevID.m_s8ModuleID = 0;
            }
        }

        public unsafe int PlayTone(DJDataDefClass.DeviceID_t* pVocDevID, int iPlayType)
        {
            short u16IoLen = 0;
            short u16IoType = 0;
            int r = 0;
            byte[] IoDataBuf = new byte[16];

            if (iPlayType == -1)	// Stop Play Tone
            {
                u16IoLen = 0;
                u16IoType = (short)DJDataDefClass.XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_GTG;
            }
            else
            {
                u16IoType = (short)DJDataDefClass.XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_GTG;
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
            int ipVocDevIDValue = (int)pVocDevID;
            fixed (byte* p = IoDataBuf)
            {
                int iIoDataBuf = (int)p;
                r = axDJAcsAPI.CtsSendIODataEx(g_DJDialGlobals.g_acsHandle, ipVocDevIDValue, u16IoType, u16IoLen, iIoDataBuf);
            }

            return r;
        }

        public unsafe void TrunkWork(DJDataDefClass.TRUNK_STRUCT* pOneTrunk, DJDataDefClass.Acs_Evt_t* pAcsEvt)
        {
            {
                if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CLEARCALL)	/*拆线事件*/
                {
                    if ((pOneTrunk->State != DJDataDefClass.TRUNK_STATE.TRK_FREE) && (pOneTrunk->State != DJDataDefClass.TRUNK_STATE.TRK_WAIT_REMOVE))
                    {
                        ResetTrunk(pOneTrunk, pAcsEvt);

                        //ShowInfo
                        int iIDSum = pOneTrunk->deviceID.m_s8ModuleID * 1000 + pOneTrunk->deviceID.m_s16ChannelID;
                        ShowTrunkListItems(iIDSum);
                        return;
                    }
                }

                if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_RECVIODATA)	/*忙音事件*/
                {
                    int pAcsValue = (int)pAcsEvt;
                    DJDataDefClass.Acs_IO_Data* pIOData = (DJDataDefClass.Acs_IO_Data*)(pAcsValue + sizeof(DJDataDefClass.Acs_Evt_t));

                    if (((DJDataDefClass.XMS_MEDIA_IO_TYPE)pIOData->m_u16IoType == DJDataDefClass.XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_GTG) //
                        && (pIOData->m_u16IoDataLen > 0))
                    {
                        byte* p = (byte*)(pAcsValue + sizeof(DJDataDefClass.Acs_IO_Data));

                        if (*p == (byte)'I' || *p == (byte)'J' || *p == (byte)'K')//忙音
                        {
                            DJDataDefClass.DeviceID_t* pDev1 = &pOneTrunk->deviceID;
                            int pDev1Value = (int)pDev1;
                            axDJAcsAPI.CtsResetDeviceEx(g_DJDialGlobals.g_acsHandle, pDev1Value, 0);
                            axDJAcsAPI.CtsClearCallEx(g_DJDialGlobals.g_acsHandle, pDev1Value, 0, 0);

                            ResetTrunk(pOneTrunk, pAcsEvt);

                            //ShowInfo
                            int iIDSum = pOneTrunk->deviceID.m_s8ModuleID * 1000 + pOneTrunk->deviceID.m_s16ChannelID;
                            ShowTrunkListItems(iIDSum);
                            return;
                        }
                    }
                }

                switch (pOneTrunk->State)
                {
                    case DJDataDefClass.TRUNK_STATE.TRK_FREE:
                        SpecialForCas(pOneTrunk, pAcsEvt);// Special code for CAS(SS1)
                        break;

                    case DJDataDefClass.TRUNK_STATE.TRK_CALLOUT:
                        SpecialForCas(pOneTrunk, pAcsEvt);// Special code for CAS(SS1)
                        if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CALLOUT)
                        {
                            DJDataDefClass.Acs_CallControl_Data* pCallControl = (DJDataDefClass.Acs_CallControl_Data*)((int)pAcsEvt + sizeof(DJDataDefClass.Acs_Evt_t));

                            if (pCallControl->m_s32AcsEvtState == 1)	// 呼出成功，对方摘机
                            {
                                fixed (DJDataDefClass.TRUNK_STRUCT* pLinkUser =
                                    &g_DJDialGlobals.AllDeviceRes[pOneTrunk->LinkDevID.m_s8ModuleID].pTrunk[pOneTrunk->LinkDevID.m_s16ChannelID])
                                {
                                    // unlink voc
                                    // next line will trigger a BUG
                                    //My_DualUnink (  pUserDevID, &pTrunk[pUserDevID->m_s16ChannelID].VocDevID );
                                    //

                                    // Link trunk and user
                                    if (pOneTrunk->deviceID.m_s8MachineID == pLinkUser->deviceID.m_s8MachineID)
                                    {
                                        DJDataDefClass.DeviceID_t* pDev1 = &pOneTrunk->deviceID;
                                        DJDataDefClass.DeviceID_t* pDev2 = &pOneTrunk->LinkDevID;
                                        int pDev1Value = (int)pDev1;
                                        int pDev2Value = (int)pDev2;
                                        axDJAcsAPI.CtsLinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev1Value, pDev2Value, 0);
                                        axDJAcsAPI.CtsLinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev2Value, pDev1Value, 0);
                                    }

                                    pOneTrunk->State = DJDataDefClass.TRUNK_STATE.TRK_LINK;
                                    pLinkUser->UserState = DJDataDefClass.USER_STATE.USER_LINK;

                                    //ShowInfo
                                    int iIDSum = pOneTrunk->deviceID.m_s8ModuleID * 1000 + pOneTrunk->deviceID.m_s16ChannelID;
                                    ShowTrunkListItems(iIDSum);
                                    iIDSum = pLinkUser->deviceID.m_s8ModuleID * 1000 + pLinkUser->deviceID.m_s16ChannelID;
                                    ShowTrunkListItems(iIDSum);
                                }
                            }
                            else		// 呼出失败
                            {
                                //DrawMain_Reason(pOneTrunk, pCallControl->m_s32AcsEvtErrCode, pCallControl->m_s32CallClearCause);
                                pOneTrunk->State = DJDataDefClass.TRUNK_STATE.TRK_FREE;

                                fixed (DJDataDefClass.TRUNK_STRUCT* pLinkUser =
                                    &g_DJDialGlobals.AllDeviceRes[pOneTrunk->LinkDevID.m_s8ModuleID].pTrunk[pOneTrunk->LinkDevID.m_s16ChannelID])
                                {

                                    PlayTone(&pLinkUser->VocDevID, 2);		// busy tone

                                    pLinkUser->LinkDevID.m_s8ModuleID = 0;// 0表示还没有分配LinkDevID
                                    pLinkUser->UserState = DJDataDefClass.USER_STATE.USER_WAITHANGUP;

                                    //ShowInfo
                                    int iIDSum = pOneTrunk->deviceID.m_s8ModuleID * 1000 + pOneTrunk->deviceID.m_s16ChannelID;
                                    ShowTrunkListItems(iIDSum);
                                    iIDSum = pLinkUser->deviceID.m_s8ModuleID * 1000 + pLinkUser->deviceID.m_s16ChannelID;
                                    ShowTrunkListItems(iIDSum);
                                }
                            }
                        }
                        break;

                    case DJDataDefClass.TRUNK_STATE.TRK_SIM_CALLOUT:
                        SpecialForCas(pOneTrunk, pAcsEvt);// Special code for CAS(SS1)
                        if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CALLOUT)
                        {
                            DJDataDefClass.Acs_CallControl_Data* pCallControl = (DJDataDefClass.Acs_CallControl_Data*)((int)pAcsEvt + sizeof(DJDataDefClass.Acs_Evt_t));

                            if (pCallControl->m_s32AcsEvtState == 1)	// 呼出成功，对方摘机
                            {
                                int iChID = SearchOneFreeVoice(pOneTrunk->deviceID.m_s8ModuleID);
                                if (iChID >= 0)
                                {
                                    pOneTrunk->VocDevID = g_DJDialGlobals.AllDeviceRes[pOneTrunk->deviceID.m_s8ModuleID].pVoice[iChID].deviceID;
                                    g_DJDialGlobals.AllDeviceRes[pOneTrunk->deviceID.m_s8ModuleID].pVoice[iChID].UsedDevID = pOneTrunk->deviceID;

                                    DJDataDefClass.DeviceID_t* pDev1 = &pOneTrunk->deviceID;
                                    DJDataDefClass.DeviceID_t* pDev2 = &pOneTrunk->VocDevID;
                                    int pDev1Value = (int)pDev1;
                                    int pDev2Value = (int)pDev2;
                                    axDJAcsAPI.CtsLinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev1Value, pDev2Value, 0);
                                    axDJAcsAPI.CtsLinkDeviceEx(g_DJDialGlobals.g_acsHandle, pDev2Value, pDev1Value, 0);

                                    PlayDTMF(&pOneTrunk->VocDevID, "12345");		// play dtmf
                                }

                                pOneTrunk->State = DJDataDefClass.TRUNK_STATE.TRK_PLAYDTMF;
                            }
                            else		// 呼出失败
                            {
                                //DrawMain_Reason(pOneTrunk, pCallControl->m_s32AcsEvtErrCode, pCallControl->m_s32CallClearCause);
                                pOneTrunk->State = DJDataDefClass.TRUNK_STATE.TRK_FREE;
                            }

                            //ShowInfo
                            int iIDSum = pOneTrunk->deviceID.m_s8ModuleID * 1000 + pOneTrunk->deviceID.m_s16ChannelID;
                            ShowTrunkListItems(iIDSum);
                        }
                        break;

                    case DJDataDefClass.TRUNK_STATE.TRK_PLAYDTMF:
                        if (CheckPlayGTGEnd(pOneTrunk, pAcsEvt))	/*play完成事件*/
                        {
                            // 主动挂机
                            DJDataDefClass.DeviceID_t* pDev1 = &pOneTrunk->deviceID;
                            int pDev1Value = (int)pDev1;
                            axDJAcsAPI.CtsClearCallEx(g_DJDialGlobals.g_acsHandle, pDev1Value, 0, 0);

                            pOneTrunk->State = DJDataDefClass.TRUNK_STATE.TRK_HANGUP;

                            //ShowInfo
                            int iIDSum = pOneTrunk->deviceID.m_s8ModuleID * 1000 + pOneTrunk->deviceID.m_s16ChannelID;
                            ShowTrunkListItems(iIDSum);
                        }
                        break;

                    default:
                        break;
                }
            }
        }

        public unsafe bool CheckPlayGTGEnd(DJDataDefClass.TRUNK_STRUCT* pOneTrunk, DJDataDefClass.Acs_Evt_t* pAcsEvt)
        {
            if ((XMS_EVT_TYPE)pAcsEvt->m_s32EventType == XMS_EVT_TYPE.XMS_EVT_SENDIODATA)
            {
                return true;
            }

            return false;
        }

        public unsafe int PlayDTMF(DJDataDefClass.DeviceID_t* pVocDevID, string DtmfStr)
        {
            int len = 0;
            short u16IoType = 0;
            short u16IoLen = 0;
            byte[] IoDataBuf = new byte[16];
            int r = 0;

            if (DtmfStr == "")	// Stop Play Dtmf
            {
                u16IoLen = 0;
            }
            else
            {
                u16IoType = (short)DJDataDefClass.XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF;

                len = DtmfStr.Length;
                if (len > 16)
                {
                    len = 16;
                }
                u16IoLen = (short)len;

                for (int i = 0; i < len; ++i)
                {
                    IoDataBuf[i] = (byte)DtmfStr[i];
                }
            }

            int iDevValue = (int)pVocDevID;
            fixed (byte* p = IoDataBuf)
            {
                int pValue = (int)p;
                r = axDJAcsAPI.CtsSendIODataEx(g_DJDialGlobals.g_acsHandle, iDevValue, u16IoType, u16IoLen, pValue);
            }

            return r;

        }

        public unsafe void ChannelWork(DJDataDefClass.TRUNK_STRUCT* pOneTrunk, DJDataDefClass.Acs_Evt_t* pAcsEvt)
        {
            if ((DJDataDefClass.XMS_INTERFACE_DEVSUB_TYPE)pOneTrunk->deviceID.m_s16DeviceSub == DJDataDefClass.XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER)
            {
                UserWork(pOneTrunk, pAcsEvt);
            }
            else
            {
                TrunkWork(pOneTrunk, pAcsEvt);
            }
        }

        /*************************************************************************************
        return 
	        0:	OK.
	        -1:	Fail, m_u8CalledTableCount Invalid
	        -2: Fail, m_u8CalledLen Invalid
	        -3: Fail, m_u8CalledTimeOut Invalid
	        -4: Fail, m_u8AreaCodeLen Invalid
	        -5: Fail, m_CalledTable[x].m_u8NumLen Invalid
        *************************************************************************************/
        public unsafe int CAS_Common_Cfg_ReadCfg(DJDataDefClass.CmdParamData_CAS_t* pParam_CAS)
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
            fixed (byte* p = g_DJDialGlobals.g_Param_CAS.m_byteCalledTable)
            {
                DJDataDefClass.CAS_CalledTableDesc_t* pCalledTable = (DJDataDefClass.CAS_CalledTableDesc_t*)p;
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

        public unsafe void SimulateCallOut()
        {
            int iItemID = SearchOneFreeTrunk();
            if (iItemID >= 0)
            {
                int iIDSum = int.Parse(listView_InterfInfo.Items[iItemID].Name);
                int iModID = iIDSum / 1000;
                int iChID = iIDSum % 1000;
                fixed (DJDataDefClass.DeviceID_t* pDev = &g_DJDialGlobals.AllDeviceRes[iModID].pTrunk[iChID].deviceID)
                {
                    int iDevValue = (int)pDev;
                    fixed (char* pCalling = g_DJDialGlobals.cfg_CallingNum)
                    {
                        string Calling = new string(pCalling);
                        fixed (byte* byCalling = g_DJDialGlobals.g_CallNumBuf.g_byCalling)
                        {
                            int j = 0;
                            for (j = 0; j < Calling.Length; ++j)
                            {
                                byCalling[j] = (byte)Calling[j];
                            }
                            byCalling[j] = 0;
                            //char* pCallee = pOneUser->DtmfBuf;
                            //string Callee = new string(pCallee);
                            string Callee = textBox_Callee.Text;
                            fixed (byte* byCallee = g_DJDialGlobals.g_CallNumBuf.g_byCallee)
                            {
                                for (j = 0; j < Callee.Length; ++j)
                                {
                                    byCallee[j] = (byte)Callee[j];
                                }
                                byCallee[j] = 0;
                                int iCalling = (int)byCalling;
                                int iCallee = (int)byCallee;
                                int r = axDJAcsAPI.CtsMakeCallOutEx(g_DJDialGlobals.g_acsHandle, iDevValue, iCalling, iCallee, 0); if (r > 0)
                                {
                                    fixed (DJDataDefClass.TRUNK_STRUCT* pLinkTrunk =
                                                        &g_DJDialGlobals.AllDeviceRes[pDev->m_s8ModuleID].pTrunk[pDev->m_s16ChannelID])
                                    {
                                        for (j = 0; j < g_DJDialGlobals.cfg_CallingNum.Length && j < 20; ++j)
                                        {
                                            pLinkTrunk->CallerCode[j] = g_DJDialGlobals.cfg_CallingNum[j];
                                        }
                                        if (j >= 20)
                                        {
                                            pLinkTrunk->CallerCode[19] = '\0';
                                        }
                                        else
                                        {
                                            pLinkTrunk->CallerCode[j] = '\0';
                                        }
                                        for (j = 0; j < Callee.Length && j < 20; ++j)
                                        {
                                            pLinkTrunk->CalleeCode[j] = Callee[j];
                                        }
                                        if (j >= 20)
                                        {
                                            pLinkTrunk->CalleeCode[19] = '\0';
                                        }
                                        else
                                        {
                                            pLinkTrunk->CalleeCode[j] = '\0';
                                        }

                                        pLinkTrunk->State = DJDataDefClass.TRUNK_STATE.TRK_SIM_CALLOUT;

                                        //ShowInfo
                                        iIDSum = pLinkTrunk->deviceID.m_s8ModuleID * 1000 + pLinkTrunk->deviceID.m_s16ChannelID;
                                        ShowTrunkListItems(iIDSum);
                                    }
                                }
                                else
                                {
                                    string MsgStr = "XMS_ctsMakeCallOut() FAIL! ret = " + r.ToString();
                                    ShowEvtInfo(MsgStr);
                                }
                            }
                        }
                    }
                }
            }
        }

        public MYAPI.EvtHandlerPtr g_ESRFuncPtr;
        private unsafe void button_initsystem_Click(object sender, EventArgs e)
        {
            g_DJDialGlobals.ReadFromConfig();

            fixed (DJDataDefClass.ServerID_t* pStruct = &g_DJDialGlobals.cfg_ServerID)
            {
                int pStructValue = (int)pStruct;
                fixed (int* pAcsHandle = &g_DJDialGlobals.g_acsHandle)
                {
                    int pAcsHandleValue = (int)pAcsHandle;
                    int iResult = axDJAcsAPI.AcsOpenStreamEx(pAcsHandleValue, pStructValue, 13, 64, 64, g_DJDialGlobals.cfg_s32DebugOn, 0);
                    //DJDataDefClass.PrivateData_t privatedata = new DJDataDefClass.PrivateData_t();
                    //int iResult = MYAPI.XMS_acsOpenStream(ref g_DJDialGlobals.g_acsHandle, ref g_DJDialGlobals.cfg_ServerID, 12, 64, 64, g_DJDialGlobals.cfg_s32DebugOn, ref privatedata);
                    if (iResult == DJDataDefClass.ACSPOSITIVE_ACK)
                    {
                        listBox_OptAndEvtInfo.Items.Add("AcsOpenStreamEx Success");
                    }
                    else
                    {
                        listBox_OptAndEvtInfo.Items.Add("AcsOpenStreamEx Fail");
                    }

                    g_ESRFuncPtr = new MYAPI.EvtHandlerPtr(EvtHandler);
                    /*iResult = MYAPI.XMS_acsSetESR(g_DJDialGlobals.g_acsHandle, g_ESRFuncPtr, 0, true);*/
                    /*int hModule = MYAPI.LoadLibrary("DJAcsAPI_WE.dll");
                    if (hModule != 0)
                    {
                        MYAPI.XMS_acsSetESRPtr hFunc = (MYAPI.XMS_acsSetESRPtr)MYAPI.GetAddress(hModule, "XMS_acsSetESR", typeof(MYAPI.XMS_acsSetESRPtr));
                        if (hFunc != null)
                        {
                            iResult = hFunc(g_DJDialGlobals.g_acsHandle, g_ESRFuncPtr, 0, true);
                        }
                    }
                    //MYAPI.FreeLibrary(hModule);*/
                    iResult = axDJAcsAPI.AcsSetESREx(g_DJDialGlobals.g_acsHandle, 
                        System.Runtime.InteropServices.Marshal.GetFunctionPointerForDelegate(g_ESRFuncPtr).ToInt32(), 0, 1);

                    if (iResult == DJDataDefClass.ACSPOSITIVE_ACK)
                    {
                        listBox_OptAndEvtInfo.Items.Add("XMS_acsSetESR Success");
                    }
                    else
                    {
                        listBox_OptAndEvtInfo.Items.Add("XMS_acsSetESR Fail");
                    }

                    iResult = axDJAcsAPI.AcsGetDeviceListEx(g_DJDialGlobals.g_acsHandle, 0);
                    //iResult = MYAPI.XMS_acsGetDeviceList(g_DJDialGlobals.g_acsHandle, ref privatedata);
                    if (iResult == DJDataDefClass.ACSPOSITIVE_ACK)
                    {
                        listBox_OptAndEvtInfo.Items.Add("AcsGetDeviceListEx Success");
                    }
                    else
                    {
                        listBox_OptAndEvtInfo.Items.Add("AcsGetDeviceListEx Fail");
                    }
                }
            }
            
            button_initsystem.Enabled = false;
        }

        private void button_exitsystem_Click(object sender, EventArgs e)
        {
            //try
            {
                int iResult = 0;
                iResult = axDJAcsAPI.AcsCloseStream(g_DJDialGlobals.g_acsHandle, ref iResult);
                //DJDataDefClass.PrivateData_t pdata = new DJDataDefClass.PrivateData_t();
                //iResult = MYAPI.XMS_acsCloseStream(g_DJDialGlobals.g_acsHandle, ref pdata);
                if (iResult == DJDataDefClass.ACSPOSITIVE_ACK)
                {
                    listBox_OptAndEvtInfo.Items.Add("AcsCloseStreamEx Success");
                }
                else
                {
                    listBox_OptAndEvtInfo.Items.Add("AcsCloseStreamEx Fail");
                }
            }
            //catch (Exception)
            {
            }
            //finally
            {
            //    this.Close();
            }
        }

        private void DialForm_Load(object sender, EventArgs e)
        {
        }

        public bool bTimer = false;

        private void button_simulate_Click(object sender, EventArgs e)
        {
            if (checkBox_IsLoop.Checked)
            {
                if (!bTimer)
                {
                    timer_loopCallOut.Start();
                    bTimer = true;
                    button_simulate.Text = "Stop Simulate Callout";
                }
                else
                {
                    timer_loopCallOut.Stop();
                    bTimer = false;
                    button_simulate.Text = "Start Simulate Callout";
                }
            }
            else
            {
                SimulateCallOut();
            }
        }

        private void timer_loopCallOut_Tick(object sender, EventArgs e)
        {
            SimulateCallOut();
        }
    }
}