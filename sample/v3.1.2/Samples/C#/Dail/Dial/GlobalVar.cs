using System;
using System.Text;

using DJKeygoe;

namespace Dial
{
    public class DJDialGlobals
    {
        public enum	REMOVE_STATE
        {
	        DSP_REMOVE_STATE_NONE	    =	0,		// Do not remove the DSP hardware
	        DSP_REMOVE_STATE_START	=	1,		// Ready to remove DSP hardware, wait all the Devices' Resource release
	        DSP_REMOVE_STATE_READY	=	2,		// All the Devices' Resource have released, start delete DSP hardware
        }

        public enum VOICE_STATE 
        {
	        VOC_WAITOPEN,
	        VOC_FREE,
	        VOC_USED,
	        VOC_WAIT_REMOVE,
        } 

        public enum TRUNK_STATE 
        {
	        TRK_WAITOPEN,
	        TRK_FREE,			
	        TRK_NOTHANDLE,
	        TRK_CALLOUT,
	        TRK_SIM_CALLOUT,
	        TRK_SIM_LINK,
	        TRK_SIM_ANALOG_OFFHOOK,
	        TRK_SIM_ANALOG_DIALING,
	        TRK_LINK,
	        TRK_PLAYDTMF,
	        TRK_HANGUP,
	        TRK_FAIL,

	        TRK_WAIT_REMOVE,
        }

        public enum USER_STATE 
        {
	        USER_WAITOPEN,
	        USER_FREE,
	        USER_OFFHOOK,
	        USER_CALLOUT,
	        USER_LINK,
	        USER_WAITHANGUP,
	        USER_WAIT_REMOVE,
	        USER_RING,
        }

        public struct VOICE_STRUCT
        {
	        public DeviceID_t	deviceID;
	        public int			iSeqID;
	        public DeviceID_t	UsedDevID;
	        public VOICE_STATE	State;
        } ;

        public struct PCM_STRUCT
        {
	        public DeviceID_t	deviceID;
	        public int			    iSeqID;
	        public bool		    bOpenFlag;		// flag of OpenDevice OK
	        public byte		    u8E1Type;
	        public int		        s32AlarmVal;
        } ;

        public unsafe struct TRUNK_STRUCT
        {
	        // ----------------
	        public DeviceID_t	deviceID;
	        public int			iSeqID;
	        public int			iModSeqID;
	        public int			iLineState;

	        public DeviceID_t	VocDevID;

	        public DeviceID_t	LinkDevID;

	        // -----------------
	        public TRUNK_STATE	State;

	        // -----------------
	        public USER_STATE	UserState;
	        public int			iUserSeqID;

	        public int		DtmfCount;
	        public fixed sbyte	    DtmfBuf[32];

            public fixed sbyte CallerCode[20];
            public fixed sbyte CalleeCode[20];

        } ;

        public struct TYPE_XMS_DSP_DEVICE_RES_DEMO
        {
            public int lFlag;				// 本DSP是否存在, 0：不存在，1：存在

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

        public struct TYPE_CHANNEL_MAP_TABLE
        {
            public sbyte      m_s8ModuleID;    /*device module type*/
            public short     m_s16ChannelID;  /*device chan id*/
        } ;

        public unsafe void CharsToSBytes(char[] chSrc, byte* byDst, int size)
        {
            int i = 0;
            for (i = 0; i < size && chSrc[i] != '\0'; ++i)
            {
                byDst[i] = (byte)chSrc[i];
            }
            byDst[i] = (byte)'\0';
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

        public unsafe void ReadFromConfig()
        {
            ClsIniFile clsIniFile = new ClsIniFile(".\\XMS_Dial.INI");

            StringBuilder strBlderTemp = new StringBuilder(256);
            clsIniFile.GetFileString("ConfigInfo", "IpAddr", "192.168.10.75", strBlderTemp, 256);
            string strTemp = strBlderTemp.ToString();
            fixed (sbyte* p = cfg_ServerID.m_s8ServerIp)
            {
                CharsToSBytes(strTemp.ToCharArray(), (byte*)p, strTemp.Length);
            }
            cfg_ServerID.m_u32ServerPort = (uint)clsIniFile.GetFileInt("ConfigInfo", "Port", 9000);

            strTemp = null;

            clsIniFile.GetFileString("ConfigInfo", "UserName", "", strBlderTemp, 256);
            strTemp = strBlderTemp.ToString();
            fixed (sbyte* p = cfg_ServerID.m_s8UserName)
            {
                CharsToSBytes(strTemp.ToCharArray(), (byte*)p, strTemp.Length);
            }
            clsIniFile.GetFileString("ConfigInfo", "PassWord", "", strBlderTemp, 256);

            strTemp = null;

            strTemp = strBlderTemp.ToString();
            fixed (sbyte* p = cfg_ServerID.m_s8UserPwd)
            {
                CharsToSBytes(strTemp.ToCharArray(), (byte*)p, strTemp.Length);
            }
            cfg_iCalledLen = clsIniFile.GetFileInt("ConfigInfo", "CalledLen", 5);
            if (cfg_iCalledLen > 20) { cfg_iCalledLen = 20; }
            clsIniFile.GetFileString("ConfigInfo", "CallingNum", "83636988", strBlderTemp, 32);
            cfg_CallingNum = strBlderTemp.ToString();
            cfg_iCallOutRule = clsIniFile.GetFileInt("ConfigInfo", "CallOutRule", 0);
            clsIniFile.GetFileString("ConfigInfo", "SimCalledRNum", "12345", strBlderTemp, 32);
            cfg_SimCalledNum = strBlderTemp.ToString();
            cfg_iPartWork = clsIniFile.GetFileInt("ConfigInfo", "PartWork", 0);
            cfg_iPartWorkModuleID = clsIniFile.GetFileInt("ConfigInfo", "PartWorkModuleID", 0);
            cfg_s32DebugOn = clsIniFile.GetFileInt("ConfigInfo", "DebugOn", 0);

            strBlderTemp = null;
            strTemp = null;
        }

        public unsafe void WriteToConfig()
        {
            ClsIniFile clsIniFile = new ClsIniFile(".\\XMS_Dial.INI");
            
            string strTemp;
            char[] szIp = new char[66];
            szIp.Initialize();

            fixed (sbyte* p = cfg_ServerID.m_s8ServerIp)
            {
                SBytesToChars((byte*)p, szIp, 32);
                strTemp = new string(szIp);
                clsIniFile.WriteFileString("ConfigInfo", "IpAddr", strTemp);
            }

            strTemp = cfg_ServerID.m_u32ServerPort.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "Port", strTemp);

            clsIniFile.WriteFileString("ConfigInfo", "CalledLen", cfg_iCalledLen.ToString());

            clsIniFile.WriteFileString("ConfigInfo", "CallingNum", cfg_CallingNum);

            clsIniFile.WriteFileString("ConfigInfo", "CallOutRule", cfg_iCallOutRule.ToString());

            clsIniFile.WriteFileString("ConfigInfo", "SimCalledRNum", cfg_SimCalledNum);

            clsIniFile.WriteFileString("ConfigInfo", "PartWork", cfg_iPartWork.ToString());

            clsIniFile.WriteFileString("ConfigInfo", "PartWorkModuleID", cfg_iPartWorkModuleID.ToString());

            clsIniFile.WriteFileString("ConfigInfo", "DebugOn", cfg_s32DebugOn.ToString());

            strTemp = null;
            szIp = null;
        }

        public const int MAX_DSP_MODULE_NUMBER_OF_XMS = 256;

        public string cfg_CallingNum = "";
        public string cfg_SimCalledNum = "";
        public ServerID_t cfg_ServerID;
        public int cfg_iCalledLen = 0;
        public int cfg_iCallOutRule = 0;

        public int cfg_iPartWork = 0;
        public int cfg_iPartWorkModuleID = 0;
        public int g_iCallOutRule = 0;
        public int cfg_s32DebugOn = 0;
        public UInt32 g_acsHandle = 0;
        public byte g_u8UnitID = 0;
        public int cfg_iVoiceRule = 0;
        public TYPE_XMS_DSP_DEVICE_RES_DEMO []AllDeviceRes = new TYPE_XMS_DSP_DEVICE_RES_DEMO[256];
        public int g_iTotalModule = 0;

        public sbyte[] MapTable_Module = new sbyte[256];
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
        public TYPE_CHANNEL_MAP_TABLE[] MapTable_Voice = new TYPE_CHANNEL_MAP_TABLE[2048];

        public TYPE_ANALOG_GTD_PARAM g_Param_Analog;
        public CmdParamData_CAS_t g_Param_CAS;
        public int cfg_iDispChnl = 0;

        public UInt32 nNumOfListBoxItem = 0;

        public DJDialGlobals()
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