using System;
using System.Text;
using System.Runtime.InteropServices;


 namespace Dial
{
    public unsafe class DJDataDefClass
    {
        public const int MAX_DSP_MODULE_NUMBER_OF_XMS = 256;
        public const int MAX_PCM_NUM_IN_THIS_DEMO = 64;
        public const int MAX_TRUNK_NUM_IN_THIS_DEMO = 32*MAX_PCM_NUM_IN_THIS_DEMO;
        public const int MAX_SEND_IODATA_DTMF_LEN = 16;
        public const int MAX_FILE_NAME_LEN = 256;

        public const int ACSPOSITIVE_ACK = 1;
        public const int ACS_MAX_CALL_NUM = 32;

        public enum TRUNK_STATE
        {
	        TRK_WAITOPEN,
	        TRK_FREE,
            TRK_NOTHANDLE,
            TRK_CALLOUT,
	        TRK_SIM_CALLOUT,
	        TRK_LINK,
	        TRK_PLAYDTMF,
            TRK_HANGUP,
	        TRK_FAIL,
	        TRK_WAIT_REMOVE
        };

        public enum USER_STATE
        {
            USER_WAITOPEN,
            USER_FREE,
            USER_OFFHOOK,
            USER_CALLOUT,
            USER_LINK,
            USER_WAITHANGUP,
            USER_WAIT_REMOVE
        };

        public enum VOICE_STATE
        {
            VOC_WAITOPEN,
            VOC_FREE,
            VOC_USED,
            VOC_WAIT_REMOVE
        };

        public enum REMOVE_STATE
        {
            DSP_REMOVE_STATE_NONE,
            DSP_REMOVE_STATE_START,
            DSP_REMOVE_STATE_READY
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

        public struct CallID_t
        {
            public int      m_s32FlowType;    /*CallType*/
            public int      m_s32FlowChannel; /*Call Channel*/
        };

        public struct DeviceID_t
        {   
	        public short    m_s16DeviceMain;  /*device main type*/
            public short    m_s16DeviceSub;   /*device sub type*/
            public byte     m_s8ModuleID;     /*device module ID*/
	        public byte     m_s8MachineID;    /*device machine ID*/
            public short    m_s16ChannelID;   /*device channel ID*/
            public short    m_s16DeviceGroup; /*device group ID*/
	        public fixed byte   m_Rfu2[2];    /*Reserved*/
	        public CallID_t        m_CallID;         /*Serveice ID*/
        };

        public struct TRUNK_STRUCT
        {
	        public DeviceID_t	deviceID;
	        public int			iSeqID;
	        public int			iModSeqID;
	        public int			iLineState;

	        public DeviceID_t	VocDevID;

	        public DeviceID_t	LinkDevID;

	        public TRUNK_STATE	State;

	        public USER_STATE	UserState;
	        public int			iUserSeqID;

	        public int		    DtmfCount;
	        public fixed char   DtmfBuf[32];   

	        public fixed char   CallerCode[20]; 
            public fixed char   CalleeCode[20]; 
        };

        public struct VOICE_STRUCT
        {
	        public DeviceID_t	deviceID;
	        public int			iSeqID;

	        public DeviceID_t	UsedDevID;

	        public VOICE_STATE	State;
        };

        public struct PCM_STRUCT
        {
	        public DeviceID_t	deviceID;
	        public int			iSeqID;
	        public bool	    	bOpenFlag;		// OpenDevice成功的标志

	        public byte	        u8E1Type;
	        public int		    s32AlarmVal;
        };

        public struct TYPE_CHANNEL_MAP_TABLE
        {
            public byte      m_s8ModuleID;    /*device module type*/
            public short     m_s16ChannelID;  /*device chan id*/
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

        public struct ServerID_t
        {
            public fixed byte m_s8ServerIp[32]; /*XMS server ip*/
	        public int   m_u32ServerPort;  /*XMS server port*/
            public fixed byte m_s8UserName[32]; /**/
            public fixed byte m_s8UserPwd[32];  /**/
        };

        /*Acs_Evt_t*/
        public struct Acs_Evt_t
        {
            public int m_s32AcsHandle;       /*acs handle*/
            public DeviceID_t m_DeviceID;           /*Device ID*/
            public int m_s32EvtSize;         /*Evt size*/
            public int m_s32EventType;       /*event type code*/
            public int m_s32AcsConfirmation; /*acs confirmation code*/
        };

        public struct Acs_Dev_List_Head_t
        {
            public int m_s32DeviceMain;   /*device Main*/
            public int m_s32ModuleID;     /*Device Module ID*/
            public int m_s32DeviceNum;    /*device num*/
        };

        public struct PrivateData_t
        {
	        public uint  m_u32DataSize; /*private data size*/
        };

        public enum XMS_MEDIA_IO_TYPE
        {
            XMS_IO_TYPE_DTMF = 1,
            XMS_IO_TYPE_MR2F = 2,
            XMS_IO_TYPE_MR2B = 3,
            XMS_IO_TYPE_GTG = 4,
            XMS_IO_TYPE_FSK = 5,
        };

        public struct Acs_IO_Data
        {
            public int m_s32AcsEvtState;   /*acs event state*/
            public int m_s32AcsEvtErrCode; /*acs event errcode*/
            public ushort m_u16IoType;     /*io proc type*/
            public ushort m_u16IoDataLen;  /*io data len*/
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

        public struct CAS_CalledTableDesc_t
        {
	        public byte						m_u8NumHeadLen;			/* Compared Called Number Head Length */
	        public fixed byte				m_u8NumHead[14];		/* Compared Called Number Head Content */
	        public byte						m_u8NumLen;				/* Total Called Number Length */
        };

        public struct CmdParamData_CAS_t
        {
	        public DeviceID_t					m_VocDevID;				/* Voice Device ID which is used for MFC, alloced by Application */

	        /* Call In Parameter */
	        public byte						m_u8CalledTableCount;	/* Called Table Count ( 0-16:Table Count) */
	        public fixed byte                       m_Rfu1[3];              /* Reserved*/
	        //public fixed CAS_CalledTableDesc_t		m_CalledTable[16];		/* Max 16 items */
            public fixed byte               m_byteCalledTable[256];
	        public byte						m_u8CalledLen;			/* Called Number Length (0:Variable, Other:Length) */

	        public byte						m_u8CalledTimeOut;		/* Time Out Seconds when Receive MFC */

	        public byte						m_u8NeedCaller;			/* Is Need Caller Number ( 1:Yes, 0:No ) */
	        public byte						m_u8AreaCodeLen;		/* Area Code Length when receive Called Number, Used for Receive Caller Number */

	        /* Call Out Parameter */
	        public byte						m_u8KA;					/* KA ( Default KA = 1 ) */
	        public byte						m_u8KD;					/* KD ( Default KD = 3 ) */

	        /* Other */
	        public byte						m_u8ControlMode;		/* Release Control Mode ( 0:None, 1:Caller Control, 2:Called Control ) */
	        public fixed byte						m_u8Rfu[9];				/* Reserved for Future Use */
        };

        public struct Acs_CallControl_Data
        {
	        public int         m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
	        public int       m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	        public int                  m_s32CallClearCause; /*Call clear cause code*/
	        public byte                   m_u8CallingCategory;/*Calling Category*/
	        public byte                   m_u8CallingAddressIndicator;/*Address Indicator*/
	        public byte                   m_u8CalledAddressIndicator;/*Address Indicator*/
	        public fixed byte                   m_s8Rfu1[1];
	        public fixed byte               m_s8CallingNum[ACS_MAX_CALL_NUM]; /*calling num*/
	        public fixed byte               m_s8CalledNum[ACS_MAX_CALL_NUM];  /*called num*/
	        public fixed byte                   m_s8Rfu2[32];
	        public PrivateData_t           m_PrivData;/*private data*/
        };

        public struct CmdParamData_AnalogTrunk_t
        {
            public DeviceID_t m_VocDevID; /* Voice Device ID which is used for MFC, alloced by Application */

            /* Call In Parameter */
            public byte m_u8CallerIdOption;  /*0:disabled; 1:Fsk CallerId; 2:DTMF CallerId; 3: FSK/DTMF CallerId,reference XMS_ANALOG_TRUNK_CALLERID_OPT*/
            public byte m_u8CallInRingCount; /*ring count before CallIn event*/
            public ushort m_u16Rfu1;

            /*Call Out Parameter*/
            public byte m_u8DialtoneDetect;/*0:don't detect dialtone; 1: detect dialtone before dial dtmf,reference XMS_ANALOG_TRUNK_DIALTONE_DETECT_OPT*/
            public byte m_u8CallOutMethod;	/*0:Application full control; 1:Normal CallProgress Tone Detection,detect ring-back tone & busy tone;2:Polarity-Reverse Detection, detect polarity-reverse & busy tone,reference XMS_ANALOG_TRUNK_CALLOUT_METHOD_OPT*/
            public ushort m_u16Rfu2;
        };

        public struct Acs_GeneralProc_Data
        {
            public int m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
            public int m_s32AcsEvtErrCode;  /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
            public int m_s32DeviceState;    /*Device State*/
            public int m_s32Resrv;          /*reserved*/
            public PrivateData_t m_PrivData;          /*private data*/
        };
    }

     class ClsIniFile
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

     public unsafe class MYAPI
     {
         public delegate void EvtHandlerPtr(int esrParam);

         [DllImport("DJAcsAPI_WE")]
         public static extern int XMS_acsSetESR(int acsHandle, EvtHandlerPtr FuncPtr, uint esrParam, bool notifyAll);

         public delegate int XMS_acsSetESRPtr(int acsHandle, EvtHandlerPtr FuncPtr, uint esrParam, bool notifyAll);

         [DllImport("Kernel32.dll")]
         public static extern int LoadLibrary(string lpFileName);

         [DllImport("Kernel32.dll")]
         public static extern bool FreeLibrary(int hModule);

         [DllImport("Kernel32.dll")]
         public static extern IntPtr GetProcAddress(int hModule, string lpProcName);

         public static Delegate GetAddress(int dllHandle, string functionName, Type t)
         {
             IntPtr functionAddr = GetProcAddress(dllHandle, functionName);

             if (functionAddr == null)
                 return null;
             else
                 return Marshal.GetDelegateForFunctionPointer(functionAddr, t);
         }

         /*[DllImport("DJAcsAPI_WE")]
         public static extern int XMS_acsOpenStream(ref int acsHandle,ref DJDataDefClass.ServerID_t serverID, byte u8AppID,
                                        uint u32SendQSize, uint u32RecvQSize, int s32DebugOn,ref DJDataDefClass.PrivateData_t privateData);

         [DllImport("DJAcsAPI_WE")]
         public static extern int XMS_acsGetDeviceList(int acsHandle, ref DJDataDefClass.PrivateData_t privateData);

         [DllImport("DJAcsAPI_WE")]
         public static extern int XMS_acsCloseStream(int acsHandle, ref DJDataDefClass.PrivateData_t privateData);*/
     }

    public unsafe class DJDailGlobals
    {
        public struct tagCallNumBuf
        {
            public fixed byte g_byCalling[32];
            public fixed byte g_byCallee[32];
        };

        public tagCallNumBuf g_CallNumBuf = new tagCallNumBuf();

        public DJDataDefClass.TYPE_XMS_DSP_DEVICE_RES_DEMO[]    AllDeviceRes;   // DJDataDefClass.MAX_DSP_MODULE_NUMBER_OF_XMS
        public DJDataDefClass.CmdParamData_CAS_t g_Param_CAS = new DJDataDefClass.CmdParamData_CAS_t();

        public int	                                 			g_iTotalModule = 0;
        public byte[]				                            MapTable_Module;    //MAX_DSP_MODULE_NUMBER_OF_XMS

        public int		                        				g_iTotalPcm = 0;
        public int					                        	g_iTotalPcmOpened = 0;
        public DJDataDefClass.TYPE_CHANNEL_MAP_TABLE[]      	MapTable_Pcm;   //MAX_PCM_NUM_IN_THIS_DEMO

        public int				                        		g_iTotalTrunk = 0;
        public int			                        			g_iTotalTrunkOpened = 0;
        public DJDataDefClass.TYPE_CHANNEL_MAP_TABLE[]	        MapTable_Trunk; //MAX_TRUNK_NUM_IN_THIS_DEMO

        public int		                        				g_iTotalUser = 0;
        public int					                        	g_iTotalUserOpened = 0;
        public DJDataDefClass.TYPE_CHANNEL_MAP_TABLE[]      	MapTable_User;  //MAX_TRUNK_NUM_IN_THIS_DEMO

        public int          					            	g_iTotalVoice = 0;
        public int			                    			    g_iTotalVoiceOpened = 0;
        public int						                        g_iTotalVoiceFree = 0;
        public DJDataDefClass.TYPE_CHANNEL_MAP_TABLE[]          MapTable_Voice; //MAX_TRUNK_NUM_IN_THIS_DEMO

        // var about Dial.INI
        public string			cfg_IniName = "";
        public string			cfg_IniShortName = "\\Dail.ini";

        public DJDataDefClass.ServerID_t cfg_ServerID = new DJDataDefClass.ServerID_t();
        public int				cfg_iCalledLen = 5;
        public string			cfg_CallingNum = "83636988";

        public string			cfg_VocPath = "";	// no use in XMS_Dial
        public int				cfg_iDispChnl = 32;		// always disp 32 channel
        public int				cfg_iVoiceRule = 0;		// search voice in Fix Relationship

        public int				cfg_iPartWork = 0;
        public int				cfg_iPartWorkModuleID = 0;

        public int				cfg_iCallOutRule = 0;
        public string			cfg_SimCalledNum = "12345";

        public int				cfg_s32DebugOn = 0;

        // var about work
        public int		g_acsHandle = -1;
        public byte			g_u8UnitID = 1;

        

        public DJDailGlobals()
        {
            AllDeviceRes = new DJDataDefClass.TYPE_XMS_DSP_DEVICE_RES_DEMO[DJDataDefClass.MAX_DSP_MODULE_NUMBER_OF_XMS];
            for (int i = 0; i < DJDataDefClass.MAX_DSP_MODULE_NUMBER_OF_XMS; ++i)
            {
                AllDeviceRes[i] = new DJDataDefClass.TYPE_XMS_DSP_DEVICE_RES_DEMO();
                AllDeviceRes[i].lFlag = 0;
            }
            MapTable_Module = new byte[DJDataDefClass.MAX_DSP_MODULE_NUMBER_OF_XMS];
            MapTable_Pcm = new DJDataDefClass.TYPE_CHANNEL_MAP_TABLE[DJDataDefClass.MAX_PCM_NUM_IN_THIS_DEMO];
            MapTable_Trunk = new DJDataDefClass.TYPE_CHANNEL_MAP_TABLE[DJDataDefClass.MAX_TRUNK_NUM_IN_THIS_DEMO];
            MapTable_User = new DJDataDefClass.TYPE_CHANNEL_MAP_TABLE[DJDataDefClass.MAX_TRUNK_NUM_IN_THIS_DEMO];
            MapTable_Voice = new DJDataDefClass.TYPE_CHANNEL_MAP_TABLE[DJDataDefClass.MAX_TRUNK_NUM_IN_THIS_DEMO];
        }

        public void CharsToSBytes(char[] chSrc, byte* byDst, int size)
        {
            int i = 0;
            for (i = 0; i < size && chSrc[i] != '\0'; ++i)
            {
                byDst[i] = (byte)chSrc[i];
            }
            byDst[i] = (byte)'\0';
        }
        public void SBytesToChars(byte* bySrc, char[] chDst)
        {
            int i = 0;
            for (i = 0; bySrc[i] != (byte)'\0'; ++i)
            {
                chDst[i] = (char)bySrc[i];
            }
            chDst[i] = '\0';
        }
        public void	ReadFromConfig()
        {
            ClsIniFile clsIniFile = new ClsIniFile("");
            StringBuilder strFileName = new StringBuilder(256);
            clsIniFile.GetExeFilePath(strFileName, 256);
            string strFilePath = strFileName.ToString();
            clsIniFile.SetIniFileName(strFilePath.Replace(".exe", ".ini"));

            StringBuilder strBlderTemp = new StringBuilder(256);
            clsIniFile.GetFileString("ConfigInfo", "IpAddr", "192.168.10.33", strBlderTemp, 256);
            string strTemp = strBlderTemp.ToString();
            fixed( byte* p = cfg_ServerID.m_s8ServerIp )
            {
                CharsToSBytes(strTemp.ToCharArray(), p, strTemp.Length);
                /*int i = 0;
                for(i = 0; i < strTemp.Length; ++i)
                {
                    p[i] = (byte)strTemp[i];
                }
                p[i] = (byte)'\0';*/
            }

            cfg_ServerID.m_u32ServerPort = clsIniFile.GetFileInt("ConfigInfo", "Port", 9000);

            clsIniFile.GetFileString("ConfigInfo", "UserName", "", strBlderTemp, 256);
            strTemp = strBlderTemp.ToString();
            fixed (byte* p = cfg_ServerID.m_s8UserName)
            {
                int i = 0;
                for (i = 0; i < strTemp.Length; ++i)
                {
                    p[i] = (byte)strTemp[i];
                }
                p[i] = (byte)'\0';
            }
            clsIniFile.GetFileString("ConfigInfo", "PassWord", "", strBlderTemp, 256);
            strTemp = strBlderTemp.ToString();
            fixed (byte* p = cfg_ServerID.m_s8UserPwd)
            {
                int i = 0;
                for (i = 0; i < strTemp.Length; ++i)
                {
                    p[i] = (byte)strTemp[i];
                }
                p[i] = (byte)'\0';
            }

            cfg_iCalledLen = clsIniFile.GetFileInt("ConfigInfo", "CalledLen", 5);
            if (cfg_iCalledLen > 20)
            {
                cfg_iCalledLen = 20;
            }

            clsIniFile.GetFileString("ConfigInfo", "CallingNum", "83636988", strBlderTemp, 256);
            cfg_CallingNum = strBlderTemp.ToString();

            cfg_iCallOutRule = clsIniFile.GetFileInt("ConfigInfo", "CallOutRule", 0);

            clsIniFile.GetFileString("ConfigInfo", "SimCalledRNum", "12345", strBlderTemp, 256);
            cfg_SimCalledNum = strBlderTemp.ToString();

            cfg_iPartWork = clsIniFile.GetFileInt("ConfigInfo", "PartWork", 0);

            cfg_iPartWorkModuleID = clsIniFile.GetFileInt("ConfigInfo", "PartWorkModuleID", 0);

            cfg_s32DebugOn = clsIniFile.GetFileInt("ConfigInfo", "DebugOn", 0);
        }

        public void WriteToConfig()
        {
            ClsIniFile clsIniFile = new ClsIniFile("");
            StringBuilder strFileName = new StringBuilder(256);
            clsIniFile.GetExeFilePath(strFileName, 256);
            string strFilePath = strFileName.ToString();
            clsIniFile.SetIniFileName(strFilePath.Replace(".exe", ".ini"));

            string strTemp = new string('\0', 0);
            char[] chTemp = new char[32];
            fixed (byte* p = cfg_ServerID.m_s8ServerIp)
            {
                SBytesToChars(p, chTemp);
            }
            strTemp = new string(chTemp);
            clsIniFile.WriteFileString("ConfigInfo", "IpAddr", strTemp);

            strTemp = cfg_ServerID.m_u32ServerPort.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "Port", strTemp);

            fixed (byte* p = cfg_ServerID.m_s8UserName)
            {
                int i = 0;
                for (i = 0; p[i] != '\0'; ++i)
                {
                    chTemp[i] = (char)p[i];
                }
                chTemp[i] = '\0';
            }
            strTemp = new string(chTemp);
            clsIniFile.WriteFileString("ConfigInfo", "UserName", strTemp);

            fixed (byte* p = cfg_ServerID.m_s8UserPwd)
            {
                int i = 0;
                for (i = 0; p[i] != '\0'; ++i)
                {
                    chTemp[i] = (char)p[i];
                }
                chTemp[i] = '\0';
            }
            strTemp = new string(chTemp);
            clsIniFile.WriteFileString("ConfigInfo", "PassWord", strTemp);

            strTemp = cfg_iCalledLen.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "CalledLen", strTemp);

            clsIniFile.WriteFileString("ConfigInfo", "CallingNum", cfg_CallingNum);

            strTemp = cfg_iCallOutRule.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "CallOutRule", strTemp);

            clsIniFile.WriteFileString("ConfigInfo", "SimCalledRNum", cfg_SimCalledNum);

            strTemp = cfg_iPartWork.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "PartWork", strTemp);

            strTemp = cfg_iPartWorkModuleID.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "PartWorkModuleID", strTemp);

            strTemp = cfg_s32DebugOn.ToString();
            clsIniFile.WriteFileString("ConfigInfo", "DebugOn", strTemp);
        }
    };
}