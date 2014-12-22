package DJKeygoe;

import javax.swing.JOptionPane;

public class Global {
	public static final int 		MAX_DSP_MODULE_NUMBER_OF_XMS = 256;
	public static final int 		MAX_VOC_RES_NUM_EACH_DSP 	= 128; 
	public static final int 		MAX_PCM_RES_NUM_EACH_DSP 	= 4; 
	public static final int 		MAX_TRUNK_RES_NUM_EACH_DSP 	= 128; 
	public static final int 		MAX_USER_RES_NUM_EACH_DSP	= 128;
	
	public String			cfg_CallingNum   = "83636988";
	public String			cfg_SimCalledNum = "12345";
	
	public ServerID_t 		cfg_ServerID 	 = new ServerID_t();

	public int				cfg_iCalledLen 	 = 5;
	public int				cfg_iPartWork	 = 1;
	public int				cfg_iPartWorkModuleID = 0;
	public int				cfg_iCallOutRule = 0;
	public int				cfg_s32DebugOn   = 1;
	public int				cfg_iDispChnl 	 = 32;		// always disp 32 channel
	public int				cfg_iVoiceRule 	 = 0;		// search voice in Fix Relationship
	
	public int				g_acsHandle 	 = -1;
	
	// var in XMS_Dail_Event.CPP
	public TYPE_XMS_DSP_DEVICE_RES_DEMO	AllDeviceRes[] = new TYPE_XMS_DSP_DEVICE_RES_DEMO[MAX_DSP_MODULE_NUMBER_OF_XMS];

	public int						g_iTotalPcm;
	public int						g_iTotalPcmOpened;
	public TYPE_CHANNEL_MAP_TABLE	MapTable_Pcm[] = new TYPE_CHANNEL_MAP_TABLE[64];

	public int						g_iTotalTrunk;
	public int						g_iTotalTrunkOpened;
	public TYPE_CHANNEL_MAP_TABLE	MapTable_Trunk[] = new TYPE_CHANNEL_MAP_TABLE[2048];

	public int						g_iTotalUser;
	public int						g_iTotalUserOpened;
	public TYPE_CHANNEL_MAP_TABLE	MapTable_User[] = new TYPE_CHANNEL_MAP_TABLE[2048];

	public int						g_iTotalVoice;
	public int						g_iTotalVoiceOpened;
	public int						g_iTotalVoiceFree;
	public TYPE_CHANNEL_MAP_TABLE	MapTable_Voice[] = new TYPE_CHANNEL_MAP_TABLE[2048];

	public int						g_iTotalModule;
	public byte						MapTable_Module[] = new byte[MAX_DSP_MODULE_NUMBER_OF_XMS];
	
	public TYPE_ANALOG_GTD_PARAM 	g_Param_Analog = new TYPE_ANALOG_GTD_PARAM();

	public int 						g_iLoopStart = 0;
	
	public CmdParamData_GtdFreq_t		g_TmpGtdFreq  = new CmdParamData_GtdFreq_t();
	public CmdParamData_GtdProtoType_t	g_TmpGtdProto = new CmdParamData_GtdProtoType_t();
	public CmdParamData_AnalogTrunk_t   g_AnalogTrk   = new CmdParamData_AnalogTrunk_t();
	public CmdParamData_Voice_t 		g_cmdVoc	  = new CmdParamData_Voice_t();
	public CmdParamData_CAS_t 			g_Param_CAS   = new CmdParamData_CAS_t();
	public CmdParamData_AnalogUser_t    g_AnalogUser  = new CmdParamData_AnalogUser_t();
	
	public void InitCmdParamData_CASData(){
		for (int i = 0; i < 16; i++){
			g_Param_CAS.m_CalledTable[i] = new CAS_CalledTableDesc_t();
		}
	}
	void InitObjectArr(){ 
		for (int i = 0; i < MAX_DSP_MODULE_NUMBER_OF_XMS; i++){
    		AllDeviceRes[i] = new TYPE_XMS_DSP_DEVICE_RES_DEMO();
    		
    		for (int j = 0; j < MAX_VOC_RES_NUM_EACH_DSP; j++){
    			AllDeviceRes[i].pVoice[j] = new VOICE_STRUCT();
    		}
    		
    		for (int j = 0; j < MAX_PCM_RES_NUM_EACH_DSP; j++){
    			AllDeviceRes[i].pPcm[j] = new PCM_STRUCT();
    		}
    		
    		for (int j = 0; j < MAX_TRUNK_RES_NUM_EACH_DSP; j++){
    			AllDeviceRes[i].pTrunk[j] = new TRUNK_STRUCT();
    		}
    	}
    	
    	for (int i = 0; i < 64; i++){
    		MapTable_Pcm[i] = new TYPE_CHANNEL_MAP_TABLE();
    	}
    	
    	for (int i = 0; i < 2048; i++){
    		MapTable_Trunk[i] = new TYPE_CHANNEL_MAP_TABLE();
    		MapTable_Voice[i] = new TYPE_CHANNEL_MAP_TABLE();
    		MapTable_User[i]  = new TYPE_CHANNEL_MAP_TABLE();
    	}
	}
	
	public static void CharsToByte(byte[] DestArr, char []SourArr, int nLen){
		for (int i = 0; i < nLen; i++){
			DestArr[i] = (byte)SourArr[i]; 
		}
	}
	
	public static int GetByteArrLen(byte s8Arr[]){ 
    	int i = 0;
    	
    	while (s8Arr[i] != 0){
    		i++;
    	}
   
    	return i;
    }
	
	public void ReadFromConfig(){
		String strIniFilePath = new String("XMS_Dial.INI");
		try{
			String strIp = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "IpAddr", "192.168.10.74");
			CharsToByte(cfg_ServerID.m_s8ServerIp, strIp.toCharArray(), strIp.length());

			String strPort = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "Port", "9000");
			cfg_ServerID.m_u32ServerPort = Integer.parseInt(strPort);
			
			String strUserName = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "UserName", "");
			CharsToByte(cfg_ServerID.m_s8UserName, strUserName.toCharArray(), strUserName.length());
			
			String strPwd = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "PassWord", "");
			CharsToByte(cfg_ServerID.m_s8UserPwd, strPwd.toCharArray(), strPwd.length());
			
			String strCalledLen = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "CalledLen", "5");
			cfg_iCalledLen = Integer.parseInt(strCalledLen);
			if(cfg_iCalledLen > 20){
				cfg_iCalledLen = 20;
			}
			
			cfg_CallingNum = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "CallingNum", "83636988");
			
			String strCallOutRule = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "CallOutRule", "0");
			cfg_iCallOutRule = Integer.parseInt(strCallOutRule);
			
			cfg_SimCalledNum = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "SimCalledRNum", "12345");
			
			
			String strPartWork = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "PartWork", "0");
			cfg_iPartWork = Integer.parseInt(strPartWork);
			
			String strPartWorkModuleID = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "PartWorkModuleID", "0");
			cfg_iPartWorkModuleID = Integer.parseInt(strPartWorkModuleID);
			
			String strDebugOn = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "DebugOn", "0");
			cfg_s32DebugOn = Integer.parseInt(strDebugOn);
		}
		catch(Exception ee){
			ee.printStackTrace();
		}
	}
	
	public void WriteToConfig(){
		String strIniFilePath = new String("XMS_Dial.INI");
		try{
			String strIp = new String(cfg_ServerID.m_s8ServerIp, "UTF-8");
			JIniFile.setProfileString(strIniFilePath, "ConfigInfo", "IpAddr", strIp);

			String strPort = Integer.toString(cfg_ServerID.m_u32ServerPort);
			JIniFile.setProfileString(strIniFilePath, "ConfigInfo", "Port", strPort);
			
			String strCalledLen = Integer.toString(cfg_iCalledLen);
			JIniFile.setProfileString(strIniFilePath, "ConfigInfo", "CalledLen", strCalledLen);
			
			JIniFile.setProfileString(strIniFilePath, "ConfigInfo", "CallingNum", cfg_CallingNum);
			
			String strCallOutRule = Integer.toString(cfg_iCallOutRule);
			JIniFile.setProfileString(strIniFilePath, "ConfigInfo", "CallOutRule", strCallOutRule);
			
			JIniFile.setProfileString(strIniFilePath, "ConfigInfo", "SimCalledRNum", cfg_SimCalledNum);
			
			String strPartWork = Integer.toString(cfg_iPartWork);
			JIniFile.setProfileString(strIniFilePath, "ConfigInfo", "PartWork", strPartWork);
			
			String strPartWorkModuleID = Integer.toString(cfg_iPartWorkModuleID);
			JIniFile.setProfileString(strIniFilePath, "ConfigInfo", "PartWorkModuleID", strPartWorkModuleID);
			
			String strDebugOn = Integer.toString(cfg_s32DebugOn);
			JIniFile.setProfileString(strIniFilePath, "ConfigInfo", "DebugOn", strDebugOn);
		}
		catch(Exception ee){
			ee.printStackTrace();
		}
	}
	
public void DispEventInfo(Acs_Evt_t acsEvtData, Object obj, int nEvtType){
		
		String strDisplay = GetString.GetString_EvtType(nEvtType);
		
		switch(nEvtType){
		case XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE: {
			DJEvtQueryDeviceData queryDeviceData = (DJEvtQueryDeviceData)obj;
			strDisplay = strDisplay + "(" + GetString.GetString_DeviceMain(queryDeviceData.acsDevListHead.m_s32DeviceMain) +
					"," + queryDeviceData.acsDevListHead.m_s32ModuleID + "," +  
					queryDeviceData.acsDevListHead.m_s32DeviceNum + ")";
			break;
		}
		
		case XMS_EVT_TYPE.XMS_EVT_UNIFAILURE: {
			
			DJEvtUnifailureData unifailureData = (DJEvtUnifailureData)obj;
			
			strDisplay = strDisplay + " " + GetString.GetString_ErrorCode(unifailureData.unifailureData.m_s32AcsEvtErrCode) + 
						  "(" + unifailureData.unifailureData.m_s32AcsEvtErrCode + ")" + " Dev=(" + 
						  GetString.GetString_DeviceMain(acsEvtData.m_DeviceID.m_s16DeviceMain) + "," +
						  acsEvtData.m_DeviceID.m_s8ModuleID + "," + acsEvtData.m_DeviceID.m_s16ChannelID +")";
			break;
		}
		
		/*case XMS_EVT_TYPE.XMS_EVT_RECVIODATA: {
			strDisplay = strDisplay + " Dev=(" + GetString.GetString_DeviceMain(NewJDialog.g_DJApi.Evt.m_DeviceID.m_s16DeviceMain) + 
			  "," + NewJDialog.g_DJApi.Evt.m_DeviceID.m_s8ModuleID + "," + NewJDialog.g_DJApi.Evt.m_DeviceID.m_s16ChannelID + ")";
			
			strDisplay += " RecvDataType:" + GetString.GetString_IODataType(NewJDialog.g_DJApi.IOData.m_u16IoType) + 
				" RecvDataLen:" + Integer.toString(NewJDialog.g_DJApi.IOData.m_u16IoDataLen);
			
			String str = new String(NewJDialog.g_DJApi.g_RecvData);
			strDisplay += "  " + str;
			
			break;
		}*/
		default: {
			strDisplay = strDisplay + " Dev=(" + GetString.GetString_DeviceMain(acsEvtData.m_DeviceID.m_s16DeviceMain) + 
			  "," + acsEvtData.m_DeviceID.m_s8ModuleID + "," + acsEvtData.m_DeviceID.m_s16ChannelID + ")";
		}
		
		}
		
		NewJDialog.Dialog.ListBox_AddMsg(strDisplay);
		
		strDisplay = null;
	}

	public void My_DualUnlink (DeviceID_t Dev1, DeviceID_t Dev2){
		PrivateData_t privateData = new PrivateData_t();
		
		privateData.m_u32DataSize = 0;
		
		NewJDialog.g_DJApi.XMS_ctsUnlinkDevice ( g_acsHandle, Dev1, Dev2, privateData ); 
		NewJDialog.g_DJApi.XMS_ctsUnlinkDevice ( g_acsHandle, Dev2, Dev1, privateData ); 
	}
	
	public void My_DualLink (DeviceID_t Dev1, DeviceID_t Dev2){
		PrivateData_t privateData = new PrivateData_t();
		
		privateData.m_u32DataSize = 0;
		
		NewJDialog.g_DJApi.XMS_ctsLinkDevice ( g_acsHandle, Dev1, Dev2, privateData ); 
		NewJDialog.g_DJApi.XMS_ctsLinkDevice ( g_acsHandle, Dev2, Dev1, privateData ); 
	}

	public boolean AddDeviceRes_Voice(DJEvtQueryDeviceData queryData){
		int nDevNum = queryData.acsDevListHead.m_s32DeviceNum; //
		byte bDspModID = (byte) queryData.acsDevListHead.m_s32ModuleID;
		
		if (bDspModID < 0 || bDspModID > 255) {
			System.out.println("Invalid DSP ID,Add Voice Resource Fail!");
			return false;
		}
		
		AllDeviceRes[bDspModID].lVocNum = nDevNum;
		AllDeviceRes[bDspModID].lVocOpened = 0;
		AllDeviceRes[bDspModID].lVocFreeNum = 0;
		
		for (int i = 0; i < nDevNum; i++){
			AllDeviceRes[bDspModID].pVoice[i].deviceID.CopyDeviceID_tObj(queryData.device[i]);
			AllDeviceRes[bDspModID].pVoice[i].State = VOICE_STATE.VOC_WAITOPEN;
		}
		return true;
	}
	
	public boolean AddDeviceRes_Pcm(DJEvtQueryDeviceData queryData){
		int nDevNum = queryData.acsDevListHead.m_s32DeviceNum; //
		byte bDspModID = (byte) queryData.acsDevListHead.m_s32ModuleID;
		
		if (bDspModID < 0 || bDspModID > 255) {
			System.out.println("Invalid DSP ID,Add Pcm Resource Fail!");
			return false;
		}
		
		AllDeviceRes[bDspModID].lPcmNum = nDevNum;
		AllDeviceRes[bDspModID].lPcmOpened = 0;
		
		for (int i = 0; i < nDevNum; i++){		
			AllDeviceRes[bDspModID].pPcm[i].deviceID.CopyDeviceID_tObj(queryData.device[i]);
			AllDeviceRes[bDspModID].pPcm[i].bOpenFlag = false;
		}
		return true;
	}
	
	public boolean AddDeviceRes_Board(DJEvtQueryDeviceData queryData){
		int nDevNum = queryData.acsDevListHead.m_s32DeviceNum; //
		byte bDspModID = (byte) queryData.acsDevListHead.m_s32ModuleID;
		
		if (bDspModID < 0 || bDspModID > 255) {
			System.out.println("Invalid DSP ID,Add Board Fail!");
			return false;
		}
		
		if (AllDeviceRes[bDspModID].lFlag == 0 && nDevNum > 0){
			AllDeviceRes[bDspModID].deviceID.CopyDeviceID_tObj(queryData.device[0]);
			AllDeviceRes[bDspModID].bOpenFlag = false;
			AllDeviceRes[bDspModID].bErrFlag = false;
			AllDeviceRes[bDspModID].RemoveState = REMOVE_STATE.DSP_REMOVE_STATE_NONE;
		}
		
		return true;
	}
	
	public boolean AddDeviceRes_Trunk(DJEvtQueryDeviceData queryData){
		int nDevNum = queryData.acsDevListHead.m_s32DeviceNum; //
		byte bDspModID = (byte) queryData.acsDevListHead.m_s32ModuleID;
		
		if (bDspModID < 0 || bDspModID > 255) {
			System.out.println("Invalid DSP ID,Add Board Fail!");
			return false;
		}
		
		AllDeviceRes[bDspModID].lTrunkNum = nDevNum;
		AllDeviceRes[bDspModID].lTrunkOpened = 0;
		
		for (int i = 0; i < nDevNum; i++){
			AllDeviceRes[bDspModID].pTrunk[i].deviceID.CopyDeviceID_tObj(queryData.device[i]);
			AllDeviceRes[bDspModID].pTrunk[i].State = TRUNK_STATE.TRK_WAITOPEN;
		}
		
		return true;
	}
	
	public void OpenAllDevice_Dsp(byte bDspModID){
		
		AllDeviceRes[bDspModID].bErrFlag = false;
		
		AllDeviceRes[bDspModID].RemoveState = REMOVE_STATE.DSP_REMOVE_STATE_NONE;
		
		PrivateData_t privateData = new PrivateData_t();
		privateData.m_u32DataSize = 0;
		
		NewJDialog.g_DJApi.XMS_ctsOpenDevice(g_acsHandle, AllDeviceRes[bDspModID].deviceID, privateData); //Open Board
		
		for (int i = 0; i < AllDeviceRes[bDspModID].lVocNum; i++){
			if (AllDeviceRes[bDspModID].pVoice[i].State == VOICE_STATE.VOC_WAITOPEN) { //Open Voc	
				NewJDialog.g_DJApi.XMS_ctsOpenDevice(g_acsHandle, AllDeviceRes[bDspModID].pVoice[i].deviceID, privateData);
			}
		}
		
		for (int i = 0; i < AllDeviceRes[bDspModID].lPcmNum; i++){
			if (AllDeviceRes[bDspModID].pPcm[i].bOpenFlag == false){
				NewJDialog.g_DJApi.XMS_ctsOpenDevice(g_acsHandle, AllDeviceRes[bDspModID].pPcm[i].deviceID, privateData);
			}
		}
		
		for (int i = 0; i < AllDeviceRes[bDspModID].lTrunkNum; i++){
			if (AllDeviceRes[bDspModID].pTrunk[i].State == TRUNK_STATE.TRK_WAITOPEN){
				NewJDialog.g_DJApi.XMS_ctsOpenDevice(g_acsHandle, AllDeviceRes[bDspModID].pTrunk[i].deviceID, privateData);
			}
		}
	}
	
	public PCM_STRUCT GetPcmStructByDevice(byte s8ModuleID, short s16ChannelID){
		return AllDeviceRes[s8ModuleID].pPcm[s16ChannelID];
	}
	
	public VOICE_STRUCT GetVoiceStructByDevice(byte s8ModuleID, short s16ChannelID){
		return AllDeviceRes[s8ModuleID].pVoice[s16ChannelID];
	}
	
	public TRUNK_STRUCT GetTrunkStructByDevice(byte s8ModuleID, short s16ChannelID){
		return AllDeviceRes[s8ModuleID].pTrunk[s16ChannelID];
	}
	
	void RefreshMapTable(){
		int iModuleCount = 0, iVocCount = 0, iTrkCount = 0, iPcmCount = 0, iModSeqID = 0, iUserCount = 0;
		
		for (int i = 0; i < MAX_DSP_MODULE_NUMBER_OF_XMS; i++){
			if (AllDeviceRes[i].lFlag != 0){
				AllDeviceRes[i].iSeqID = iModuleCount; 
				MapTable_Module[iModuleCount] = (byte)i;
				iModuleCount++;
				
				for (int j = 0; j < AllDeviceRes[i].lVocNum; j++){
					AllDeviceRes[i].pVoice[j].iSeqID = iVocCount;
					MapTable_Voice[iVocCount].m_s8ModuleID = AllDeviceRes[i].pVoice[j].deviceID.m_s8ModuleID;      
					MapTable_Voice[iVocCount].m_s16ChannelID = AllDeviceRes[i].pVoice[j].deviceID.m_s16ChannelID;
					iVocCount++;
				}
				
				iModSeqID = 0;
				for (int j = 0; j < AllDeviceRes[i].lTrunkNum; j++){
					AllDeviceRes[i].pTrunk[j].iSeqID = iTrkCount;
					MapTable_Trunk[iTrkCount].m_s8ModuleID = AllDeviceRes[i].pTrunk[j].deviceID.m_s8ModuleID;
					MapTable_Trunk[iTrkCount].m_s16ChannelID = AllDeviceRes[i].pTrunk[j].deviceID.m_s16ChannelID;
					iTrkCount++;
					
					if (AllDeviceRes[i].pTrunk[j].deviceID.m_s16DeviceSub != XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_UNUSABLE){
						AllDeviceRes[i].pTrunk[j].iModSeqID = iModSeqID;
						iModSeqID++;
					}
					
					if (AllDeviceRes[i].pTrunk[j].deviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER){
						AllDeviceRes[i].pTrunk[j].iUserSeqID = iUserCount;
						MapTable_User[iUserCount].m_s8ModuleID = AllDeviceRes[i].pTrunk[j].deviceID.m_s8ModuleID;
						MapTable_User[iUserCount].m_s16ChannelID = AllDeviceRes[i].pTrunk[j].deviceID.m_s16ChannelID;
						iUserCount ++;
					}
				}
				
				for (int j = 0; j < AllDeviceRes[i].lPcmNum; j++){
					AllDeviceRes[i].pPcm[j].iSeqID = iPcmCount;
					MapTable_Pcm[iPcmCount].m_s8ModuleID = AllDeviceRes[i].pPcm[j].deviceID.m_s8ModuleID;
					MapTable_Pcm[iPcmCount].m_s16ChannelID = AllDeviceRes[i].pPcm[j].deviceID.m_s16ChannelID;
					iPcmCount++;
				}
			}
		}
		
		g_iTotalModule = iModuleCount;
		g_iTotalTrunk  = iTrkCount;
		g_iTotalVoice  = iVocCount;
		g_iTotalPcm    = iPcmCount;
		g_iTotalUser   = iUserCount;
	}
	
	public void ReDrawAll(){	
		NewJDialog.Dialog.AddRowToCount(g_iTotalModule);
		NewJDialog.Dialog.AddRowToMain(g_iTotalTrunk);
		NewJDialog.Dialog.AddRowToPcm(g_iTotalPcm);
		NewJDialog.Dialog.AddRowToUser(g_iTotalUser);
		
		for (int i = 0; i < g_iTotalTrunk; i++){
			NewJDialog.Dialog.DrawMain(i, 1, Integer.toString(MapTable_Trunk[i].m_s8ModuleID) + 
					", " + Integer.toString(MapTable_Trunk[i].m_s16ChannelID));
			
			TRUNK_STRUCT OneTrk = GetTrunkStructByDevice(MapTable_Trunk[i].m_s8ModuleID, MapTable_Trunk[i].m_s16ChannelID);
			NewJDialog.Dialog.DrawMain(i, 2, GetString.GetString_DeviceSub(OneTrk.deviceID.m_s16DeviceSub));
			
			DrawMain_LineState ( OneTrk );
			DrawMain_State ( OneTrk );
			DrawMain_CallInfo ( OneTrk );
		}
		
		for (int i = 0; i < g_iTotalPcm; i++){
			DrawPcm_TypeAndAlarm(GetPcmStructByDevice(MapTable_Pcm[i].m_s8ModuleID, MapTable_Pcm[i].m_s16ChannelID));
		}
		
		for (int i = 0; i < g_iTotalUser; i ++){
			NewJDialog.Dialog.DrawUser( i, 1, Integer.toString(MapTable_User[i].m_s8ModuleID)
					+ "," + Integer.toString(MapTable_User[i].m_s16ChannelID));

			TRUNK_STRUCT OneTrunk = GetTrunkStructByDevice(MapTable_User[i].m_s8ModuleID, MapTable_User[i].m_s16ChannelID);
			NewJDialog.Dialog.DrawUser ( i, 2, GetString.GetString_DeviceSub( OneTrunk.deviceID.m_s16DeviceSub) );

			DrawUser_LineState ( OneTrunk );
			DrawUser_State ( OneTrunk );
		}
		
		for (int i = 0; i < g_iTotalModule; i++){
			NewJDialog.Dialog.DrawCount(i+1, 1, Integer.toString(MapTable_Module[i]));
			
			DrawCount_Pcm(MapTable_Module[i]);
			DrawCount_Trunk(MapTable_Module[i]);
			DrawCount_Voc(MapTable_Module[i]);
			DrawCount_ErrFlag(MapTable_Module[i]);
			DrawCount_RemoveState(MapTable_Module[i]);
		}
		
		for (int i = 0; i < g_iTotalUser; i ++ ){
			NewJDialog.Dialog.DrawUser(i, 1, Integer.toString(MapTable_User[i].m_s8ModuleID) + 
					", " + Integer.toString(MapTable_User[i].m_s16ChannelID));

			TRUNK_STRUCT OneTrk = GetTrunkStructByDevice(MapTable_User[i].m_s8ModuleID, MapTable_User[i].m_s16ChannelID);
			NewJDialog.Dialog.DrawUser(i, 2, GetString.GetString_DeviceSub(OneTrk.deviceID.m_s16DeviceSub));
			
			DrawUser_LineState ( OneTrk );
			DrawUser_State ( OneTrk );
		}
	}
	
	
	public void DrawUser_State(TRUNK_STRUCT OneTrk){
		NewJDialog.Dialog.DrawUser(OneTrk.iUserSeqID, 4, GetString.GetString_UserState(OneTrk.UserState));
	}
	
	public void DrawMain_LineState(TRUNK_STRUCT OneTrk){
		NewJDialog.Dialog.DrawMain(OneTrk.iSeqID, 3, GetString.GetString_LineState(OneTrk.iLineState)); 
	}
	
	public void DrawMain_State(TRUNK_STRUCT OneTrk){
		NewJDialog.Dialog.DrawMain(OneTrk.iSeqID, 4, GetString.GetString_State(OneTrk.State)); 
	}

	public void DrawMain_CallInfo(TRUNK_STRUCT OneTrk){
		String strCallee = new String(OneTrk.CalleeCode);
		NewJDialog.Dialog.DrawMain(OneTrk.iSeqID, 5, strCallee.substring(0, Global.GetByteArrLen(OneTrk.CalleeCode)));
		
		String strCaller = new String(OneTrk.CallerCode);
		NewJDialog.Dialog.DrawMain(OneTrk.iSeqID, 6, strCaller.substring(0, Global.GetByteArrLen(OneTrk.CallerCode)));
		
		strCallee = null;
		strCaller = null;
	}
	
	public void DrawMain_LinkDev(TRUNK_STRUCT OneTrk){
		String str;
		
		if (OneTrk.LinkDevID != null){
			if ( OneTrk.LinkDevID.m_s16DeviceMain != 0 ){
				str = Integer.toString(OneTrk.deviceID.m_s8ModuleID) + "," + Integer.toString(OneTrk.deviceID.m_s16ChannelID);
			} else {
				str = "";
			}
			
			NewJDialog.Dialog.DrawMain(OneTrk.iSeqID, 7, str);
		}
		
		str = null;
	}

	public void DrawMain_Reason ( TRUNK_STRUCT OneTrk, int s32ErrCode, int s32ClearCause ){
		String str;
		
		str = "Err=" + Integer.toString(s32ErrCode) + ",Cause=" + Integer.toString(s32ClearCause);
		
		NewJDialog.Dialog.DrawMain(OneTrk.iSeqID, 8, str);
		
		str = null;
	}

	public void DrawMain_Analog_Reason ( TRUNK_STRUCT OneTrk, String ErrStr )
	{
		NewJDialog.Dialog.DrawMain(OneTrk.iSeqID, 8, ErrStr);
	}
	
	public void DrawPcm_TypeAndAlarm(PCM_STRUCT OnePcm){
		int	 AlarmVal;

		AlarmVal = OnePcm.s32AlarmVal;

		// E1 Type
		NewJDialog.Dialog.DrawPcm(OnePcm.iSeqID, 1, GetString.GetString_PcmType(OnePcm.u8E1Type)); 

		// Alarm
		NewJDialog.Dialog.DrawPcm(OnePcm.iSeqID, 2, "0x" + Integer.toHexString(AlarmVal)); 

		if ( (AlarmVal & XMS_E1PORT_MASK_STATE.XMS_E1PORT_MASK_LOST_SIGNAL) != 0 )
			NewJDialog.Dialog.DrawPcm(OnePcm.iSeqID, 3, " X"); 
		else
			NewJDialog.Dialog.DrawPcm(OnePcm.iSeqID, 3, "O" ); 

		if ( (AlarmVal & XMS_E1PORT_MASK_STATE.XMS_E1PORT_MASK_FAS_ALARM) !=0 )
			NewJDialog.Dialog.DrawPcm(OnePcm.iSeqID, 4, " X"); 
		else
			NewJDialog.Dialog.DrawPcm(OnePcm.iSeqID, 4, "O"); 

		if ( (AlarmVal & XMS_E1PORT_MASK_STATE.XMS_E1PORT_MASK_REMOTE_ALARM) != 0 )
			NewJDialog.Dialog.DrawPcm(OnePcm.iSeqID, 5, " X"); 
		else
			NewJDialog.Dialog.DrawPcm(OnePcm.iSeqID, 5, "O"); 
	}
	
	public void DrawCount_Pcm(byte s8ModuleID){
		NewJDialog.Dialog.DrawCount(0, 2, Integer.toString(g_iTotalPcm)+"/ " + Integer.toString(g_iTotalPcmOpened));
		
		NewJDialog.Dialog.DrawCount(AllDeviceRes[s8ModuleID].iSeqID + 1, 2, Integer.toString((int)AllDeviceRes[s8ModuleID].lPcmNum) + 
				"/ " + Integer.toString((int)AllDeviceRes[s8ModuleID].lPcmOpened));
	}
	
	public void DrawCount_Trunk(byte s8ModuleID){
		NewJDialog.Dialog.DrawCount(0, 3, Integer.toString(g_iTotalTrunk)+"/ " + Integer.toString(g_iTotalTrunkOpened));
		
		NewJDialog.Dialog.DrawCount(AllDeviceRes[s8ModuleID].iSeqID + 1, 3, Integer.toString((int)AllDeviceRes[s8ModuleID].lTrunkNum) + 
				"/ " + Integer.toString((int)AllDeviceRes[s8ModuleID].lTrunkOpened));
	}
	
	public void DrawCount_Voc(byte s8ModuleID){
		NewJDialog.Dialog.DrawCount(0, 4, Integer.toString(g_iTotalVoice)+"/ " + Integer.toString(g_iTotalVoiceOpened));
		NewJDialog.Dialog.DrawCount(0, 5, Integer.toString(g_iTotalVoiceFree));
		
		NewJDialog.Dialog.DrawCount(AllDeviceRes[s8ModuleID].iSeqID+1, 4, Integer.toString((int)AllDeviceRes[s8ModuleID].lVocNum) + 
				"/ " + Integer.toString((int)AllDeviceRes[s8ModuleID].lVocOpened));
		NewJDialog.Dialog.DrawCount(AllDeviceRes[s8ModuleID].iSeqID+1, 5, Integer.toString(AllDeviceRes[s8ModuleID].lVocFreeNum));
	}
	
	public void	DrawCount_ErrFlag(byte s8ModuleID){
		if(AllDeviceRes[s8ModuleID].bErrFlag == true){
			NewJDialog.Dialog.DrawCount(AllDeviceRes[s8ModuleID].iSeqID + 1, 7, "T");
		}
		else{
			NewJDialog.Dialog.DrawCount(AllDeviceRes[s8ModuleID].iSeqID + 1, 7, "");
		}
	}

	public void	DrawCount_RemoveState(byte s8ModuleID){
		String str = new String();
		
		switch(AllDeviceRes[s8ModuleID].RemoveState){
		case REMOVE_STATE.DSP_REMOVE_STATE_NONE: {
			str = new String("");
			break;
		}
		case REMOVE_STATE.DSP_REMOVE_STATE_READY: {
			str = new String("Ready");
			break;
		}
		case REMOVE_STATE.DSP_REMOVE_STATE_START: {
			str = new String("Start");
		}
		}
		
		NewJDialog.Dialog.DrawCount(AllDeviceRes[s8ModuleID].iSeqID+1, 7, str);
	}
	
	public void Change_State(TRUNK_STRUCT OneTrk, int iTrkState){
		OneTrk.State = iTrkState;
		
		DrawMain_State ( OneTrk );
		
		if ( (AllDeviceRes[OneTrk.deviceID.m_s8ModuleID].RemoveState == REMOVE_STATE.DSP_REMOVE_STATE_START)
			&& (iTrkState == TRUNK_STATE.TRK_FREE) ){
			OneTrk.State = TRUNK_STATE.TRK_WAIT_REMOVE;

			DrawMain_State ( OneTrk );

			CheckRemoveReady ( OneTrk.deviceID.m_s8ModuleID );
		}
	}
	
	public void	CheckRemoveReady ( byte s8DspModID ){
		int			i;

		// check device : INTERFACE_CH
		for ( i = 0; i < AllDeviceRes[s8DspModID].lTrunkNum; i ++ )
		{
			if ( (AllDeviceRes[s8DspModID].pTrunk[i].State != TRUNK_STATE.TRK_WAITOPEN)
				&& (AllDeviceRes[s8DspModID].pTrunk[i].State != TRUNK_STATE.TRK_WAIT_REMOVE)
				&& (AllDeviceRes[s8DspModID].pTrunk[i].State != TRUNK_STATE.TRK_NOTHANDLE) )
			{
				return;
			}
			
			if ( AllDeviceRes[s8DspModID].pTrunk[i].deviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER )
			{
				if ( (AllDeviceRes[s8DspModID].pTrunk[i].UserState != USER_STATE.USER_WAITOPEN)
					&& (AllDeviceRes[s8DspModID].pTrunk[i].UserState != USER_STATE.USER_WAIT_REMOVE) )
				{
					return;
				}
			}

		}

		// check device : VOICE
		for ( i = 0; i < AllDeviceRes[s8DspModID].lVocNum; i ++ )
		{
			if ( (AllDeviceRes[s8DspModID].pVoice[i].State != VOICE_STATE.VOC_WAITOPEN)
				&& (AllDeviceRes[s8DspModID].pVoice[i].State != VOICE_STATE.VOC_WAIT_REMOVE) )
			{
				return;
			}
		}

		// all device in this DSP is ready for remove 
		AllDeviceRes[s8DspModID].RemoveState = REMOVE_STATE.DSP_REMOVE_STATE_READY;
		DrawCount_RemoveState ( s8DspModID );
	}
	
	public void	Change_UserState ( TRUNK_STRUCT OneTrk, int NewState ){
		OneTrk.UserState = NewState;

		DrawUser_State ( OneTrk );
		// Check if ready to remove DSP hardware
		if ( (AllDeviceRes[OneTrk.deviceID.m_s8ModuleID].RemoveState == REMOVE_STATE.DSP_REMOVE_STATE_START)
			&& (NewState == USER_STATE.USER_FREE) ){
			OneTrk.UserState = USER_STATE.USER_WAIT_REMOVE;

			DrawUser_State ( OneTrk );

			CheckRemoveReady ( OneTrk.deviceID.m_s8ModuleID );
		}
	}
	
	public void Change_Voc_State(VOICE_STRUCT OneVoc, int NewState){
		OneVoc.State = NewState;
		
		if ( (AllDeviceRes[OneVoc.deviceID.m_s8ModuleID].RemoveState == REMOVE_STATE.DSP_REMOVE_STATE_START)
				&& (NewState == VOICE_STATE.VOC_FREE) ){
				
				OneVoc.State = VOICE_STATE.VOC_WAIT_REMOVE;

				CheckRemoveReady ( OneVoc.deviceID.m_s8ModuleID );
			}
	}
	
	public void	DrawCount_User (byte s8ModID){
		NewJDialog.Dialog.DrawCount(0, 6, Integer.toString(g_iTotalUser)+"/"+Integer.toString(g_iTotalUserOpened));
	}
	
	public void CloseDeviceOK(Acs_Evt_t acsEvt){
		DeviceID_t dev = acsEvt.m_DeviceID;
		
		AllDeviceRes[dev.m_s8ModuleID].bErrFlag = true;
		DrawCount_ErrFlag (dev.m_s8ModuleID);

		if(dev.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD){
			AllDeviceRes[dev.m_s8ModuleID].bOpenFlag = false;
		}

		if(dev.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH){
			TRUNK_STRUCT OneTrunk = GetTrunkStructByDevice(dev.m_s8ModuleID, dev.m_s16ChannelID);

			Change_State(OneTrunk, TRUNK_STATE.TRK_WAITOPEN);
			
			if (OneTrunk.deviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER){
				Change_UserState ( OneTrunk, USER_STATE.USER_WAITOPEN );

				// modify the count
				g_iTotalUserOpened --;
				DrawCount_User ( OneTrunk.deviceID.m_s8ModuleID );
			}

			// modify the count
			g_iTotalTrunkOpened --;
			AllDeviceRes[dev.m_s8ModuleID].lTrunkOpened --;

			DrawCount_Trunk(dev.m_s8ModuleID);
		}

		if ( dev.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE )
		{
			VOICE_STRUCT OneVoc = GetVoiceStructByDevice(dev.m_s8ModuleID, dev.m_s16ChannelID);
			// init this Device: Voice
			Change_Voc_State(OneVoc, VOICE_STATE.VOC_WAITOPEN);

			// modify the count
			g_iTotalVoiceOpened --;
			g_iTotalVoiceFree --;
			AllDeviceRes[dev.m_s8ModuleID].lVocOpened --;
			AllDeviceRes[dev.m_s8ModuleID].lVocFreeNum --;

			DrawCount_Voc(dev.m_s8ModuleID);
		}

		if ( dev.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT )
		{
			PCM_STRUCT OnePcm = GetPcmStructByDevice(dev.m_s8ModuleID, dev.m_s16ChannelID);
			OnePcm.bOpenFlag = false;

			// moidfy the count
			g_iTotalPcmOpened --;
			AllDeviceRes[dev.m_s8ModuleID].lPcmOpened --;

			DrawCount_Pcm(dev.m_s8ModuleID);
		}
	}
	
	public void SetGTD_ToneParam(DeviceID_t BrdDevice){
		
		short u16ParamType = -1;
		
		/***Set Freq***/
		u16ParamType = XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDFREQ;
		
		g_TmpGtdFreq.m_u16Freq_Index = 0;
		g_TmpGtdFreq.m_u16Freq_Coef = g_Param_Analog.m_u16Freq0;
		NewJDialog.g_DJApi.XMS_ctsSetParam(g_acsHandle, BrdDevice, u16ParamType, (short)0, g_TmpGtdFreq);
		
		g_TmpGtdFreq.m_u16Freq_Index = 1;
		g_TmpGtdFreq.m_u16Freq_Coef = g_Param_Analog.m_u16Freq1;
		NewJDialog.g_DJApi.XMS_ctsSetParam(g_acsHandle, BrdDevice, u16ParamType, (short)0, g_TmpGtdFreq);
		
		/***Set DialTone***/
		u16ParamType = XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDTONE;
		g_TmpGtdProto.InitGtdProtoTypeWithZero();
		g_TmpGtdProto.m_u16GtdID = 48;		// DialTone, we use GTD's ID 48
		g_TmpGtdProto.m_u16Freq_Mask = g_Param_Analog.m_u16DialTone_FreqIndexMask;
		g_TmpGtdProto.m_u16Envelope_Mode = 0;
		g_TmpGtdProto.m_u16Repeat_Count = 1;
		g_TmpGtdProto.m_u16Min_On_Time1 = (short) (g_Param_Analog.m_u16DialTone_On_Time/15);		// the unit is 15 ms
		NewJDialog.g_DJApi.XMS_ctsSetParam(g_acsHandle, BrdDevice, u16ParamType, (short)0, g_TmpGtdProto);
		
		/***Set Ring Back Tone***/
		u16ParamType = XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDTONE;
		g_TmpGtdProto.InitGtdProtoTypeWithZero();
		g_TmpGtdProto.m_u16GtdID = 49;		// DialTone, we use GTD's ID 48
		g_TmpGtdProto.m_u16Freq_Mask = g_Param_Analog.m_u16RingBackTone_FreqIndexMask;
		g_TmpGtdProto.m_u16Envelope_Mode = 1;
		g_TmpGtdProto.m_u16Repeat_Count = 1;
		g_TmpGtdProto.m_u16Min_On_Time1 = (short) ((g_Param_Analog.m_u16RingBackTone_On_Time * 
				(100 - g_Param_Analog.m_u16RingBackTone_TimeDeviation)/100 ) / 15);		// the unit is 15 ms
		g_TmpGtdProto.m_u16Max_On_Time1 = (short) ((g_Param_Analog.m_u16RingBackTone_On_Time * 
				(100 + g_Param_Analog.m_u16RingBackTone_TimeDeviation))/100  / 15);		// the unit is 15 ms
		g_TmpGtdProto.m_u16Min_Off_Time1 = (short) ((g_Param_Analog.m_u16RingBackTone_Off_Time * 
				(100 - g_Param_Analog.m_u16RingBackTone_TimeDeviation))/100  / 15);		// the unit is 15 ms
		g_TmpGtdProto.m_u16Max_Off_Time1 = (short) ((g_Param_Analog.m_u16RingBackTone_Off_Time * 
				(100 + g_Param_Analog.m_u16RingBackTone_TimeDeviation))/100  / 15);		// the unit is 15 ms
		NewJDialog.g_DJApi.XMS_ctsSetParam(g_acsHandle, BrdDevice, u16ParamType, (short)0, g_TmpGtdProto);
		
		/***Set Busy Tone0***/
		u16ParamType = XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDTONE;
		g_TmpGtdProto.InitGtdProtoTypeWithZero();
		g_TmpGtdProto.m_u16GtdID = 50;		// DialTone, we use GTD's ID 48
		g_TmpGtdProto.m_u16Freq_Mask = g_Param_Analog.m_u16BusyTone0_FreqIndexMask;
		g_TmpGtdProto.m_u16Envelope_Mode = 1;
		g_TmpGtdProto.m_u16Repeat_Count = 1;
		g_TmpGtdProto.m_u16Min_On_Time1 = (short) ((g_Param_Analog.m_u16BusyTone0_On_Time * 
				(100 - g_Param_Analog.m_u16BusyTone0_TimeDeviation)/100 ) / 15);		// the unit is 15 ms
		g_TmpGtdProto.m_u16Max_On_Time1 = (short) ((g_Param_Analog.m_u16BusyTone0_On_Time * 
				(100 + g_Param_Analog.m_u16BusyTone0_TimeDeviation))/100  / 15);		// the unit is 15 ms
		g_TmpGtdProto.m_u16Min_Off_Time1 = (short) ((g_Param_Analog.m_u16BusyTone0_Off_Time * 
				(100 - g_Param_Analog.m_u16BusyTone0_TimeDeviation))/100  / 15);		// the unit is 15 ms
		g_TmpGtdProto.m_u16Max_Off_Time1 = (short) ((g_Param_Analog.m_u16BusyTone0_Off_Time * 
				(100 + g_Param_Analog.m_u16BusyTone0_TimeDeviation))/100  / 15);		// the unit is 15 ms
		NewJDialog.g_DJApi.XMS_ctsSetParam(g_acsHandle, BrdDevice, u16ParamType, (short)0, g_TmpGtdProto);
		
		/***Set Busy Tone1***/
		u16ParamType = XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDTONE;
		g_TmpGtdProto.InitGtdProtoTypeWithZero();
		g_TmpGtdProto.m_u16GtdID = 51;		// DialTone, we use GTD's ID 48
		g_TmpGtdProto.m_u16Freq_Mask = g_Param_Analog.m_u16BusyTone1_FreqIndexMask;
		g_TmpGtdProto.m_u16Envelope_Mode = 1;
		g_TmpGtdProto.m_u16Repeat_Count = 1;
		g_TmpGtdProto.m_u16Min_On_Time1 = (short) ((g_Param_Analog.m_u16BusyTone1_On_Time * 
				(100 - g_Param_Analog.m_u16BusyTone1_TimeDeviation)/100 ) / 15);		// the unit is 15 ms
		g_TmpGtdProto.m_u16Max_On_Time1 = (short) ((g_Param_Analog.m_u16BusyTone1_On_Time * 
				(100 + g_Param_Analog.m_u16BusyTone1_TimeDeviation))/100  / 15);		// the unit is 15 ms
		g_TmpGtdProto.m_u16Min_Off_Time1 = (short) ((g_Param_Analog.m_u16BusyTone1_Off_Time * 
				(100 - g_Param_Analog.m_u16BusyTone1_TimeDeviation))/100  / 15);		// the unit is 15 ms
		g_TmpGtdProto.m_u16Max_Off_Time1 = (short) ((g_Param_Analog.m_u16BusyTone1_Off_Time * 
				(100 + g_Param_Analog.m_u16BusyTone1_TimeDeviation))/100  / 15);		// the unit is 15 ms
		NewJDialog.g_DJApi.XMS_ctsSetParam(g_acsHandle, BrdDevice, u16ParamType, (short)0, g_TmpGtdProto);
		
		/***Set Busy Tone2***/
		u16ParamType = XMS_BOARD_PARAM_TYPE.BOARD_PARAM_SETGTDTONE;
		g_TmpGtdProto.InitGtdProtoTypeWithZero();
		g_TmpGtdProto.m_u16GtdID = 52;		// DialTone, we use GTD's ID 48
		g_TmpGtdProto.m_u16Freq_Mask = g_Param_Analog.m_u16BusyTone2_FreqIndexMask;
		g_TmpGtdProto.m_u16Envelope_Mode = 1;
		g_TmpGtdProto.m_u16Repeat_Count = 1;
		g_TmpGtdProto.m_u16Min_On_Time1 = (short) ((g_Param_Analog.m_u16BusyTone2_On_Time * 
				(100 - g_Param_Analog.m_u16BusyTone2_TimeDeviation)/100 ) / 15);		// the unit is 15 ms
		g_TmpGtdProto.m_u16Max_On_Time1 = (short) ((g_Param_Analog.m_u16BusyTone2_On_Time * 
				(100 + g_Param_Analog.m_u16BusyTone2_TimeDeviation))/100  / 15);		// the unit is 15 ms
		g_TmpGtdProto.m_u16Min_Off_Time1 = (short) ((g_Param_Analog.m_u16BusyTone2_Off_Time * 
				(100 - g_Param_Analog.m_u16BusyTone2_TimeDeviation))/100  / 15);		// the unit is 15 ms
		g_TmpGtdProto.m_u16Max_Off_Time1 = (short) ((g_Param_Analog.m_u16BusyTone2_Off_Time * 
				(100 + g_Param_Analog.m_u16BusyTone2_TimeDeviation))/100  / 15);		// the unit is 15 ms
		NewJDialog.g_DJApi.XMS_ctsSetParam(g_acsHandle, BrdDevice, u16ParamType, (short)0, g_TmpGtdProto);
	}
	
	public void	InitUserChannel (TRUNK_STRUCT OneUser){
		Change_UserState ( OneUser, USER_STATE.USER_FREE );

		OneUser.DtmfCount = 0;
		OneUser.DtmfBuf[0] = 0; 

		OneUser.VocDevID = null;
		OneUser.LinkDevID = null;
	}
	
	public void InitTrunkChannel(TRUNK_STRUCT OneTrk){
		Change_State ( OneTrk, TRUNK_STATE.TRK_FREE );

		OneTrk.VocDevID = null;
		OneTrk.LinkDevID = null;
	}
	
	void ChannelWork(DeviceID_t dev, Acs_Evt_t acsEvtData, Object obj){
		if (dev.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER){
			UserWork(dev, acsEvtData, obj);
		} else{
			TrunkWork(dev, acsEvtData, obj);
		}
	}
	
	public DeviceID_t SearchOneFreeVoice(TRUNK_STRUCT OneTrk){
		int iMostVocFreeNum = -1;
		byte iModuleID = -1;  
		DeviceID_t FreeOneVoc = null;
		
		byte s8DspID = OneTrk.deviceID.m_s8ModuleID;
		
		if (cfg_iVoiceRule == 0){ // Fix relationship between Trunk & Voice
			if (OneTrk.iModSeqID < AllDeviceRes[s8DspID].lVocNum){
				int i = OneTrk.iModSeqID;
				
				if (AllDeviceRes[s8DspID].pVoice[i].State != VOICE_STATE.VOC_WAITOPEN){
					FreeOneVoc = AllDeviceRes[s8DspID].pVoice[i].deviceID;
					Change_Voc_State(AllDeviceRes[s8DspID].pVoice[i], VOICE_STATE.VOC_USED);
					
					g_iTotalVoiceFree--;
					AllDeviceRes[s8DspID].lVocFreeNum--;
					
					DrawCount_Voc ( s8DspID );
					
					return FreeOneVoc;
				}
			}
		}else if (cfg_iVoiceRule == 1){ // Search in Same Module
			iModuleID = s8DspID;
		}else if (cfg_iVoiceRule == 2){ // Search in Most free resource module
			for (int i = 0; i < g_iTotalModule; i++){
				if (AllDeviceRes[MapTable_Module[i]].lVocFreeNum > iMostVocFreeNum){
					iMostVocFreeNum = AllDeviceRes[i].lVocFreeNum;
					iModuleID = MapTable_Module[i];
				}
			}
		}
		
		for (int i = 0; i < AllDeviceRes[iModuleID].lVocNum; i++){
			if (AllDeviceRes[iModuleID].pVoice[i].State == VOICE_STATE.VOC_FREE){
				FreeOneVoc = AllDeviceRes[iModuleID].pVoice[i].deviceID;
				//System.out.println(FreeOneVoc.m_s16DeviceMain);
				Change_Voc_State(AllDeviceRes[iModuleID].pVoice[i], VOICE_STATE.VOC_USED);
				
				g_iTotalVoiceFree--;
				AllDeviceRes[iModuleID].lVocFreeNum--;
				
				DrawCount_Voc ( iModuleID );
				
				return FreeOneVoc;
			}
		}

		return null;
	}
	
	// Special code for CAS(SS1)
	public void	SpecialForCas(TRUNK_STRUCT OneTrunk, int nEvtType)
	{
		DeviceID_t FreeVocDeviceID = null;

		if ( OneTrunk.deviceID.m_s16DeviceSub != XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_CAS )
			return;

		if (nEvtType == XMS_EVT_TYPE.XMS_EVT_CAS_MFC_START ){	/* start receive MFC, need a Voice Device */
			
			if (OneTrunk.VocDevID == null){
				FreeVocDeviceID = SearchOneFreeVoice(OneTrunk);
				if (FreeVocDeviceID != null )
				{
					// add next line from V2.2.0, link by Application Program
					My_DualLink (FreeVocDeviceID, OneTrunk.deviceID );

					OneTrunk.VocDevID = FreeVocDeviceID;
					GetVoiceStructByDevice(FreeVocDeviceID.m_s8ModuleID, FreeVocDeviceID.m_s16ChannelID).UsedDevID = OneTrunk.deviceID; 
					//DrawMain_VocInfo ( OneTrunk );

					g_Param_CAS.m_VocDevID = FreeVocDeviceID;
					NewJDialog.g_DJApi.XMS_ctsSetParam ( g_acsHandle, OneTrunk.deviceID, (short)XMS_CAS_PARAM_TYPE.CAS_PARAM_UNIPARAM, (short)0, g_Param_CAS);
				}
			}
		}
			
		if (nEvtType == XMS_EVT_TYPE.XMS_EVT_CALLOUT){
		//if ( NewJDialog.g_DJApi.Evt.m_s32EventType == XMS_EVT_TYPE.XMS_EVT_CAS_MFC_END ){	/* receive MFC end, release Voice Device */
			// add next line from V2.2.0, unlink by Application Program
			if (OneTrunk.VocDevID != null){
				My_DualUnlink(OneTrunk.VocDevID,OneTrunk.deviceID );		
		
				FreeOneFreeVoice (OneTrunk.VocDevID);
		
				GetVoiceStructByDevice(OneTrunk.VocDevID.m_s8ModuleID, OneTrunk.VocDevID.m_s16ChannelID).UsedDevID = null;
		
				OneTrunk.VocDevID = null;
			}
			//DrawMain_VocInfo (OneTrunk);
		}
	}
	// end of code for CAS(SS1)
	
	public void DrawUser_VocInfo( TRUNK_STRUCT OneUser ){
		if (OneUser.VocDevID != null){
			
			String Str;
			
			if (OneUser.VocDevID.m_s16DeviceMain != 0){
				DeviceID_t dev = OneUser.VocDevID;
				
				Str = Integer.toString(dev.m_s8ModuleID) + "," + Integer.toString(dev.m_s16ChannelID);
			} else {
				Str = "";
			}
			
			NewJDialog.Dialog.DrawUser(OneUser.iUserSeqID, 6, Str);
		}
	}
	
	public void DrawUser_DTMF( TRUNK_STRUCT OneUser ){
		String Str = new String(OneUser.DtmfBuf);
		
		NewJDialog.Dialog.DrawUser( OneUser.iUserSeqID, 5, Str.substring(0, OneUser.DtmfCount)); 
	}
	
	public void DrawUser_LinkDev( TRUNK_STRUCT OneUser ){
		
		if (OneUser.LinkDevID != null){
			String Str;
			if (OneUser.LinkDevID.m_s16DeviceMain != 0){
				Str = Integer.toString(OneUser.LinkDevID.m_s8ModuleID) + "," + Integer.toString(OneUser.LinkDevID.m_s16ChannelID);
			} else {
				Str = "";
			}
			
			NewJDialog.Dialog.DrawUser(OneUser.iUserSeqID, 7, Str);
		}
	}
	
	void DrawUser_LineState( TRUNK_STRUCT OneUser ){
		NewJDialog.Dialog.DrawUser( OneUser.iUserSeqID, 3, GetString.GetString_LineState (OneUser.iLineState )); 
	}
	
	public void ResetUser(TRUNK_STRUCT OneUser){
		if (OneUser.VocDevID != null){
			if (OneUser.VocDevID.m_s16DeviceMain != 0){
				My_DualUnlink(OneUser.VocDevID, OneUser.deviceID);
				
				FreeOneFreeVoice (OneUser.VocDevID);
				
				OneUser.VocDevID = null;
			}
		}
		
		if (OneUser.LinkDevID != null){
			if (OneUser.LinkDevID.m_s16DeviceMain != 0){
				My_DualUnlink(OneUser.LinkDevID, OneUser.deviceID);
				
				TRUNK_STRUCT LinkTrk = GetTrunkStructByDevice(OneUser.LinkDevID.m_s8ModuleID, OneUser.LinkDevID.m_s16ChannelID);
				
				if (LinkTrk.LinkDevID != null){
					LinkTrk.LinkDevID = null;
				}
				
				NewJDialog.g_DJApi.XMS_ctsClearCall(g_acsHandle, LinkTrk.deviceID, 0, null);
			}
		}
		
		InitUserChannel (OneUser);
	}
	
	public boolean GetDtmf(Acs_Evt_t acsEvtData, Object obj){
		
		if (acsEvtData.m_s32EventType == XMS_EVT_TYPE.XMS_EVT_RECVIODATA){
			DJEvtRecvIOData recvData = (DJEvtRecvIOData)obj;
			
			if (recvData.acsIOData.m_u16IoType == XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF){
				String strDtmf = new String(recvData.recvIOData);
				NewJDialog.Dialog.ListBox_AddMsg(strDtmf);
				return true;
			}
		}
		
		return false;
	}
	
	public DeviceID_t GetOutUserID (  byte pDtmf[]){
		if (cfg_iCallOutRule == 2){
			String strDtmf = new String(pDtmf);
			int iTmp = Integer.parseInt(strDtmf.substring(0, FilterStr(strDtmf)));

			iTmp %= 1000;

			byte s8ModID = MapTable_Trunk[iTmp].m_s8ModuleID;
			short s16ChID = MapTable_Trunk[iTmp].m_s16ChannelID;

			if ( iTmp >= g_iTotalTrunk )
				return null;
			
			if (AllDeviceRes[s8ModID].pTrunk[s16ChID].iLineState == DEVICE_CALL_STATE.DCS_FREE &&
					AllDeviceRes[s8ModID].pTrunk[s16ChID].deviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER){
				return AllDeviceRes[s8ModID].pTrunk[s16ChID].deviceID;
			}
		}
		return null;
	}
	
	public void strcpy(byte s8Dest[], byte s8Sour[], int nLen){
		for (int i = 0; i < nLen; i++){
			s8Dest[i] = s8Sour[i];
		}
	}
	
	public int	PlayFSKCallerID (DeviceID_t VocDevID, String CallerIDStr){

		short           u16IoType = 0;
		short           u16IoLen = 0;

		byte IoDataBuf[] = new byte[128];
		
		if ( CallerIDStr == null )	// Stop Play FSK Caller ID
		{
			u16IoLen = 0;
		}
		else
		{
			byte s8Caller[] = new byte[CallerIDStr.length() + 1];
			
			Global.CharsToByte(s8Caller, CallerIDStr.toCharArray(), CallerIDStr.length());
			u16IoType = XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_FSK;
			u16IoLen = (short)Analog_Common_Code.ConvertRawFskToCallerID ( s8Caller, IoDataBuf, 128 );
		}

		int nRet = NewJDialog.g_DJApi.XMS_ctsSendIOData ( g_acsHandle, VocDevID, u16IoType, u16IoLen, IoDataBuf);

		return	nRet;

	}
	
	public void UserWork(DeviceID_t dev, Acs_Evt_t acsEvtData, Object obj){
		
		int nEvtType = acsEvtData.m_s32EventType;
		
		TRUNK_STRUCT OneUser = GetTrunkStructByDevice(dev.m_s8ModuleID, dev.m_s16ChannelID);
		
		if (nEvtType == XMS_EVT_TYPE.XMS_EVT_CLEARCALL){
			if (OneUser.UserState != USER_STATE.USER_FREE && OneUser.UserState != USER_STATE.USER_WAIT_REMOVE){
				ResetUser(OneUser);
				return ;
			}
		}
		
		switch(OneUser.UserState){
		case USER_STATE.USER_FREE : {
			
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_CALLIN){
				DeviceID_t FreeVocDeviceID = SearchOneFreeVoice(OneUser);
				
				if (FreeVocDeviceID != null){
					OneUser.VocDevID = FreeVocDeviceID;
					DrawUser_VocInfo ( OneUser );
					
					My_DualLink(OneUser.VocDevID, OneUser.deviceID);
					
					VOICE_STRUCT OneVoc = GetVoiceStructByDevice(FreeVocDeviceID.m_s8ModuleID, FreeVocDeviceID.m_s16ChannelID);
					OneVoc.UsedDevID = OneUser.deviceID;
					
					PlayTone(FreeVocDeviceID, 0);
					
					Change_UserState ( OneUser, USER_STATE.USER_OFFHOOK );
				}
			}
			break;
		}
		
		case USER_STATE.USER_OFFHOOK : {
			//GetDtmf(acsEvtData, obj);
			
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_RECVIODATA){ //Recv DTMF
				DJEvtRecvIOData acsRecvData = (DJEvtRecvIOData)obj;
				
				if (acsRecvData.acsIOData.m_u16IoType == XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF
						&& acsRecvData.acsIOData.m_u16IoDataLen > 0){
					if (OneUser.DtmfCount<31){
						OneUser.DtmfBuf[OneUser.DtmfCount] = acsRecvData.recvIOData[0];
						OneUser.DtmfCount++;
						OneUser.DtmfBuf[OneUser.DtmfCount] = 0;
					}
					
					DrawUser_DTMF ( OneUser );
					
					PlayTone(OneUser.VocDevID, -1);
					
					if (OneUser.DtmfCount >= cfg_iCalledLen){
						if (cfg_iCallOutRule == 2){
							DeviceID_t UserDev = GetOutUserID(OneUser.DtmfBuf);
							
							if (UserDev != null){
								byte s8Calling[] = new byte[cfg_CallingNum.length()+1];
								CharsToByte(s8Calling, cfg_CallingNum.toCharArray(), cfg_CallingNum.length());
								
								int nRet = NewJDialog.g_DJApi.XMS_ctsMakeCallOut(g_acsHandle, UserDev, s8Calling, OneUser.DtmfBuf, null);
								
								if (nRet > 0) { //Callout OK
									PlayTone ( OneUser.VocDevID, 1 );		// RingBack tone
									
									TRUNK_STRUCT LinkUser = GetTrunkStructByDevice(UserDev.m_s8ModuleID, UserDev.m_s16ChannelID);
									
									OneUser.LinkDevID = UserDev;
									LinkUser.LinkDevID = OneUser.deviceID; 
									DrawUser_LinkDev ( OneUser );
									DrawUser_LinkDev ( LinkUser );

									Change_UserState ( OneUser, USER_STATE.USER_CALLOUT );
									Change_UserState ( LinkUser, USER_STATE.USER_RING );

									NewJDialog.g_DJApi.XMS_ctsSetDevTimer ( g_acsHandle, UserDev, g_Param_Analog.m_u16SendFSKCallerIDTime );	// start a timer: 1.5 Seconds
									break;
								} else {
									NewJDialog.Dialog.ListBox_AddMsg("XMS_ctsMakeCallOut Fail! ret ="+Integer.toString(nRet));
								}
							}
						}
						
						DeviceID_t FreeTrkDeviceID = SearchOneFreeTrunk(OneUser.DtmfBuf);
						
						if (FreeTrkDeviceID != null){
							byte s8Calling[] = new byte[cfg_CallingNum.length()+1];
							CharsToByte(s8Calling, cfg_CallingNum.toCharArray(), cfg_CallingNum.length());
							
							int nRet = NewJDialog.g_DJApi.XMS_ctsMakeCallOut(g_acsHandle, FreeTrkDeviceID, s8Calling, OneUser.DtmfBuf, null);
							
							if (nRet > 0){
								TRUNK_STRUCT LinkTrk = GetTrunkStructByDevice(FreeTrkDeviceID.m_s8ModuleID, FreeTrkDeviceID.m_s16ChannelID);
								
								OneUser.LinkDevID = FreeTrkDeviceID;
								LinkTrk.LinkDevID = OneUser.deviceID;
								
								DrawUser_LinkDev ( OneUser );
								DrawMain_LinkDev ( LinkTrk );
								
								strcpy ( LinkTrk.CallerCode, s8Calling, cfg_CallingNum.length());
								strcpy ( LinkTrk.CalleeCode, OneUser.DtmfBuf, OneUser.DtmfCount);
								DrawMain_CallInfo ( LinkTrk );

								Change_UserState ( OneUser, USER_STATE.USER_CALLOUT );
								Change_State ( LinkTrk, TRUNK_STATE.TRK_CALLOUT );
								break;
							} else {
								NewJDialog.Dialog.ListBox_AddMsg("XMS_ctsMakeCallOut Fail! ret ="+Integer.toString(nRet));
							}
						}
						
						PlayTone ( OneUser.VocDevID, 2 );		// busy tone

						Change_UserState ( OneUser, USER_STATE.USER_WAITHANGUP );
					}
				}
				}
				
				
			break;
		}
		
		case USER_STATE.USER_CALLOUT:
			break;

		case USER_STATE.USER_LINK:
			break;

		case USER_STATE.USER_WAITHANGUP:
			break;
			
		case USER_STATE.USER_RING: {
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_DEV_TIMER){
				DeviceID_t FreeVocDeviceID = SearchOneFreeVoice(OneUser);
				if (FreeVocDeviceID != null){
					OneUser.VocDevID = FreeVocDeviceID;

					VOICE_STRUCT OneVoc = GetVoiceStructByDevice(FreeVocDeviceID.m_s8ModuleID, FreeVocDeviceID.m_s16ChannelID);
					OneVoc.UsedDevID = OneUser.deviceID; 

					DrawUser_VocInfo ( OneUser );

					My_DualLink (FreeVocDeviceID, OneUser.deviceID);
					
					PlayFSKCallerID ( OneUser.VocDevID, cfg_CallingNum );
				}
				//
			}

			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_SENDIODATA){
				PlayFSKCallerID ( OneUser.VocDevID, null );
				
				if (OneUser.VocDevID.m_s16DeviceMain != 0){
					My_DualUnlink ( OneUser.VocDevID, OneUser.deviceID );

					FreeOneFreeVoice ( OneUser.VocDevID );

					OneUser.VocDevID = null;		// 0: Didn't alloc Voc Device

					DrawUser_VocInfo ( OneUser );
				}
			}

			// end of handle FSK Caller ID

			if ( nEvtType == XMS_EVT_TYPE.XMS_EVT_CALLIN ){	
				TRUNK_STRUCT LinkUser = GetTrunkStructByDevice(OneUser.LinkDevID.m_s8ModuleID, OneUser.LinkDevID.m_s16ChannelID);
				
				if (LinkUser.VocDevID != null){
					PlayTone ( LinkUser.VocDevID, -1 );
					
					if ( LinkUser.VocDevID.m_s16DeviceMain != 0 )
					{
						My_DualUnlink ( LinkUser.VocDevID, LinkUser.deviceID );

						FreeOneFreeVoice ( LinkUser.VocDevID );

						LinkUser.VocDevID = null;

						DrawUser_VocInfo ( LinkUser );
					}

					My_DualLink ( OneUser.deviceID, LinkUser.deviceID );

					Change_UserState ( LinkUser, USER_STATE.USER_LINK );
					Change_UserState ( OneUser, USER_STATE.USER_LINK );
				}
			}
			
			break;
		}
		}
	}
	public void TrunkWork(DeviceID_t dev, Acs_Evt_t acsEvtData, Object obj){
		int nEvtType = acsEvtData.m_s32EventType;
		
		TRUNK_STRUCT OneTrk = GetTrunkStructByDevice(dev.m_s8ModuleID, dev.m_s16ChannelID);
		if (nEvtType == XMS_EVT_TYPE.XMS_EVT_CLEARCALL){
			if ( (OneTrk.State != TRUNK_STATE.TRK_FREE) && (OneTrk.State != TRUNK_STATE.TRK_WAIT_REMOVE) ){
				ResetTrunk ( OneTrk );
				return;
			}
		}
		
		switch(OneTrk.State){
		case TRUNK_STATE.TRK_FREE : {
			SpecialForCas(OneTrk, nEvtType);
			break;
		}
		
		case TRUNK_STATE.TRK_CALLOUT: {
			SpecialForCas(OneTrk, nEvtType);
			
			if ( nEvtType == XMS_EVT_TYPE.XMS_EVT_CALLOUT ){

				DJEvtCallOutData callOutData = (DJEvtCallOutData)obj;
				
				if ( callOutData.acsCallOutData.m_s32AcsEvtState == 1 )	// Call Out OK
				{
					if (OneTrk.LinkDevID != null){
						TRUNK_STRUCT LinkUser = GetTrunkStructByDevice(OneTrk.LinkDevID.m_s8ModuleID, OneTrk.LinkDevID.m_s16ChannelID);
						
						if(OneTrk.deviceID.m_s8ModuleID == LinkUser.deviceID.m_s8ModuleID)
						{
							My_DualLink (OneTrk.deviceID, OneTrk.LinkDevID);
						}

						Change_State ( OneTrk, TRUNK_STATE.TRK_LINK );
						Change_UserState ( LinkUser, USER_STATE.USER_LINK );
					}
				} else {		// Call Out Fail
					DrawMain_Reason ( OneTrk, callOutData.acsCallOutData.m_s32AcsEvtErrCode, callOutData.acsCallOutData.m_s32CallClearCause );
					Change_State ( OneTrk, TRUNK_STATE.TRK_FREE );

					TRUNK_STRUCT LinkUser = GetTrunkStructByDevice(OneTrk.LinkDevID.m_s8ModuleID, OneTrk.LinkDevID.m_s16ChannelID);
		
					if (LinkUser.VocDevID != null){
						PlayTone ( LinkUser.VocDevID, 2 );		// busy tone	
					}

					LinkUser.LinkDevID = null;

					Change_UserState ( LinkUser, USER_STATE.USER_WAITHANGUP );
				}
			}
			
			break;
		}
		
		case TRUNK_STATE.TRK_SIM_CALLOUT: {
			SpecialForCas(OneTrk, nEvtType);
			
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_CALLOUT){

				DJEvtCallOutData callOutData = (DJEvtCallOutData)obj;
				
				if (acsEvtData.m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH
						&& acsEvtData.m_DeviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK){
					DrawMain_Analog_Reason ( OneTrk, "" ); 
	
					NewJDialog.g_DJApi.XMS_ctsSetDevTimer(g_acsHandle, OneTrk.deviceID, g_Param_Analog.m_u16NoDialToneAfterOffHook); /// start a timer: 5 Seconds
	
					Change_State(OneTrk,TRUNK_STATE.TRK_SIM_ANALOG_OFFHOOK);

					return;
				}
			
				if (callOutData.acsCallOutData.m_s32AcsEvtState == 1) {
					
					DeviceID_t FreeVocDeviceID = SearchOneFreeVoice(OneTrk);
					
					if (FreeVocDeviceID != null){
						OneTrk.VocDevID = FreeVocDeviceID;
						
						My_DualLink(OneTrk.VocDevID, OneTrk.deviceID);
						
						VOICE_STRUCT OneVoc = GetVoiceStructByDevice(FreeVocDeviceID.m_s8ModuleID, FreeVocDeviceID.m_s16ChannelID);
						
						OneVoc.UsedDevID = OneTrk.deviceID;
						
						Change_State ( OneTrk, TRUNK_STATE.TRK_SIM_LINK );
					} else {
						DrawMain_Reason ( OneTrk, callOutData.acsCallOutData.m_s32AcsEvtErrCode, callOutData.acsCallOutData.m_s32CallClearCause );
						Change_State ( OneTrk, TRUNK_STATE.TRK_FREE );
					}
				}
			}
			break;
		}
		
		case TRUNK_STATE.TRK_SIM_LINK : {
			
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_LINKDEVICE){
				PlayDtmf(OneTrk.VocDevID, "12345"); // play dtmf
				
				Change_State ( OneTrk, TRUNK_STATE.TRK_PLAYDTMF );
			}
			break;
		}
		
		case TRUNK_STATE.TRK_PLAYDTMF : {
			
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_SENDIODATA){
				
				System.out.println("XMS_EVT_SENDIODATA DTMF");
				
				NewJDialog.g_DJApi.XMS_ctsClearCall(g_acsHandle, OneTrk.deviceID, 0, null);
				
				Change_State(OneTrk, TRUNK_STATE.TRK_HANGUP);
			}
			break;
		}
		
		case TRUNK_STATE.TRK_SIM_ANALOG_OFFHOOK : {
			if ( nEvtType == XMS_EVT_TYPE.XMS_EVT_DEV_TIMER ){
				// time out
				DrawMain_Analog_Reason ( OneTrk, "Wait Dial Tone TimeOut" ); 

				System.out.println("TRK_SIM_ANALOG_OFFHOOK Wait Dial Tone TimeOut");
				
				NewJDialog.g_DJApi.XMS_ctsClearCall ( g_acsHandle, OneTrk.deviceID, 0, null );			

				Change_State ( OneTrk, TRUNK_STATE.TRK_HANGUP );
			}

			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_RECVIODATA){

				DJEvtRecvIOData recvIOData = (DJEvtRecvIOData)obj;
				
				if (recvIOData.acsIOData.m_u16IoType == XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_GTG 
						|| recvIOData.acsIOData.m_u16IoType == XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_PVD){
					
					if (recvIOData.recvIOData[0] == (byte)'I'
							|| recvIOData.recvIOData[0] == (byte)'J'
							|| recvIOData.recvIOData[0] == (byte)'K'){//Recv Busy Tone 
						
						DrawMain_Analog_Reason (OneTrk, "Busy Tone:" + recvIOData.recvIOData[0]);
						
						NewJDialog.g_DJApi.XMS_ctsClearCall(g_acsHandle, OneTrk.deviceID, 0, null);
						
						Change_State(OneTrk, TRUNK_STATE.TRK_HANGUP);
					} else if (recvIOData.recvIOData[0] == (byte)'G'){ //Dial Tone

						int nRet = PlayDtmf(acsEvtData.m_DeviceID, cfg_SimCalledNum);
						
						if (nRet > 0){
							NewJDialog.g_DJApi.XMS_ctsSetDevTimer(g_acsHandle, OneTrk.deviceID, g_Param_Analog.m_u16Ringback_NoAnswerTime);
							Change_State(OneTrk,TRUNK_STATE.TRK_SIM_ANALOG_DIALING);
						} else {
							ResetTrunk(OneTrk);
						}
					}
				}
			}
			break;
		}
		
		case TRUNK_STATE.TRK_SIM_ANALOG_DIALING : {
			
			if ( nEvtType == XMS_EVT_TYPE.XMS_EVT_DEV_TIMER ){
				// time out
				DrawMain_Analog_Reason ( OneTrk, "Wait Callee Offhook TimeOut" ); 

				NewJDialog.g_DJApi.XMS_ctsClearCall ( g_acsHandle, OneTrk.deviceID, 0, null );			

				Change_State ( OneTrk, TRUNK_STATE.TRK_HANGUP );
			}

			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_RECVIODATA){
				
				DJEvtRecvIOData recvIOData = (DJEvtRecvIOData)obj;
				
				if (recvIOData.acsIOData.m_u16IoType == XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_GTG 
						|| recvIOData.acsIOData.m_u16IoType == XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_PVD){
					if (recvIOData.recvIOData[0] == (byte)'I'
							|| recvIOData.recvIOData[0] == (byte)'J'
							|| recvIOData.recvIOData[0] == (byte)'K'){//Recv Busy Tone 
						
						DrawMain_Analog_Reason (OneTrk, "Callee Busy Tone " + recvIOData.recvIOData[0]);
						
						NewJDialog.g_DJApi.XMS_ctsClearCall(g_acsHandle, OneTrk.deviceID, 0, null);
						
						Change_State(OneTrk, TRUNK_STATE.TRK_HANGUP);
					} else if (recvIOData.recvIOData[0] == (byte)'h' 
							|| recvIOData.recvIOData[0] == (byte)'b'){ //Dial Tone
						DrawMain_Analog_Reason (OneTrk, "Callee Answer:" + (char)recvIOData.recvIOData[0]);
						
						PlayDtmf ( OneTrk.VocDevID, "12345" );		// play dtmf

						Change_State ( OneTrk, TRUNK_STATE.TRK_PLAYDTMF );
					}
				}
			}
			break;
		}
		}
	}
	
	public int PlayDtmf(DeviceID_t VocDevice, String dtmfStr){
		short s16IODataType = 0, s16IODataLen = 0;
		
		s16IODataLen = (short)dtmfStr.length();
		if (s16IODataLen != 0){
			s16IODataType = XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF;
		}
		
		if (s16IODataLen > 16){
			s16IODataLen = 16;
		}
		
		byte SendIOData[] = dtmfStr.getBytes();
		
		return NewJDialog.g_DJApi.XMS_ctsSendIOData(g_acsHandle, VocDevice, s16IODataType, s16IODataLen, SendIOData);
	}
	
	public int PlayTone(DeviceID_t VocDev, int nPlayType){
		short s16IODataLen = 0, s16IODataType = 0;
		byte  IoDataBuf[]  = new byte[16];
		
		if (nPlayType == -1){ //Stop Play TYpe
			s16IODataLen = 0;
			s16IODataType = XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_GTG;
		} else {
			s16IODataType = XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_GTG;
			s16IODataLen = 1;
			
			if (nPlayType == 0){ 
				IoDataBuf[0] = (byte)'G'; //Dial Tone
			} else if (nPlayType == 1){
				IoDataBuf[0] = (byte)'H'; //Ring Back Tone
			} else if (nPlayType == 2){
				IoDataBuf[0] = (byte)'I'; //Busy Tone
			}
		}
		
		return NewJDialog.g_DJApi.XMS_ctsSendIOData(g_acsHandle, VocDev, s16IODataType, s16IODataLen, IoDataBuf);
	}
	
	public int	FreeOneFreeVoice (DeviceID_t VocDeviceID)
	{
		byte	s8ModID;

		s8ModID = VocDeviceID.m_s8ModuleID;
		if ( AllDeviceRes[s8ModID].lFlag == 1 )
		{
			VOICE_STRUCT OneVoc = GetVoiceStructByDevice(VocDeviceID.m_s8ModuleID, VocDeviceID.m_s16ChannelID);
			Change_Voc_State (OneVoc, VOICE_STATE.VOC_FREE);

			AllDeviceRes[s8ModID].lVocFreeNum++;
			g_iTotalVoiceFree ++;
			DrawCount_Voc ( s8ModID );
			return	0;		// OK
		}

		return -1;			// invalid VocDeviceID
	}
	
	public void ResetTrunk(TRUNK_STRUCT OneTrk){
		if (OneTrk.LinkDevID != null){
			if (OneTrk.LinkDevID.m_s16DeviceMain != 0){
				My_DualUnlink(OneTrk.deviceID, OneTrk.LinkDevID);	
				
				TRUNK_STRUCT LinkUser = GetTrunkStructByDevice(OneTrk.LinkDevID.m_s8ModuleID, OneTrk.LinkDevID.m_s16ChannelID);
			
				if (LinkUser.VocDevID != null){
					My_DualLink(LinkUser.VocDevID, LinkUser.deviceID);
					PlayTone ( LinkUser.VocDevID, 2 );		// busy tone
					My_DualUnlink(LinkUser.VocDevID, LinkUser.deviceID);
					
					LinkUser.VocDevID = null;
					OneTrk.LinkDevID = null;
				}
			}
		}
		
		if (OneTrk.VocDevID != null){
			My_DualUnlink(OneTrk.deviceID, OneTrk.VocDevID);
			
			FreeOneFreeVoice (OneTrk.VocDevID);
			VOICE_STRUCT OneVoc = GetVoiceStructByDevice(OneTrk.VocDevID.m_s8ModuleID, OneTrk.VocDevID.m_s16ChannelID);
			
			OneVoc.UsedDevID = null;
			OneTrk.VocDevID = null;
		}
		
		InitTrunkChannel(OneTrk);
	}
	
	public int FilterStr(String str){ 
		int nLen = str.length();
		for (int i = 0; i < nLen; i++){
			char ch = str.charAt(i);
			
			if (ch > '9' || ch < '0'){
				return i;
			}
		}
		return nLen;
	}
	
	public boolean	IsTrunk ( short s16DevSub ){
		if ( (s16DevSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_PCM)
			|| (s16DevSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_CAS)
			|| (s16DevSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_DSS1)
			|| (s16DevSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_TUP)
			|| (s16DevSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_ISUP) 
			|| (s16DevSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK) 
			)
		{
			return true;
		}

		return false;
	}
	
	public DeviceID_t SearchOneFreeTrunk (byte pDtmf[]) {
		byte	s8ModID;
		short	s16ChID;

		if ( cfg_iCallOutRule == 2 )		// Select a Fix Channel by DTMF's tail 3
		{
			String strDtmf = new String(pDtmf);
			int iTmp = Integer.parseInt(strDtmf.substring(0, FilterStr(strDtmf)));

			iTmp %= 1000;

			s8ModID = MapTable_Trunk[iTmp].m_s8ModuleID;
			s16ChID = MapTable_Trunk[iTmp].m_s16ChannelID;

			if ( iTmp >= g_iTotalTrunk )
				return null;

			if ( ( AllDeviceRes[s8ModID].pTrunk[s16ChID].iLineState == DEVICE_CALL_STATE.DCS_FREE )
				//&& IsDigitTrunk(AllDeviceRes[s8ModID].pTrunk[s16ChID].deviceID.m_s16DeviceSub) )
				&& IsTrunk(AllDeviceRes[s8ModID].pTrunk[s16ChID].deviceID.m_s16DeviceSub) ){
				return AllDeviceRes[s8ModID].pTrunk[s16ChID].deviceID;

			}
			return null;
		}

		// Sequence Mode or Loop Mode
		if ( cfg_iCallOutRule == 0 )		// Sequence Mode
		{
			g_iLoopStart = 0;
		}

		//if ( cfg_iCallOutRule == 1 )		// Loop Mode
		for (int i = 0; i < g_iTotalTrunk; i++)
		{
			s8ModID = MapTable_Trunk[g_iLoopStart].m_s8ModuleID;
			s16ChID = MapTable_Trunk[g_iLoopStart].m_s16ChannelID;

			if ( ( AllDeviceRes[s8ModID].pTrunk[s16ChID].iLineState == DEVICE_CALL_STATE.DCS_FREE )
				//&& IsDigitTrunk(AllDeviceRes[s8ModID].pTrunk[s16ChID].deviceID.m_s16DeviceSub) )
				&& IsTrunk(AllDeviceRes[s8ModID].pTrunk[s16ChID].deviceID.m_s16DeviceSub) )
			{
				g_iLoopStart = (g_iLoopStart + 1 ) % g_iTotalTrunk;
				return AllDeviceRes[s8ModID].pTrunk[s16ChID].deviceID;
			}
			g_iLoopStart = (g_iLoopStart + 1 ) % g_iTotalTrunk;
		}

		return null;
	}
	
	void Remove_OneDsp(){
		
		int nSelectedRow = NewJDialog.Dialog.GetSelectedRow();
		if (nSelectedRow <= 0){
			JOptionPane.showConfirmDialog( null , "Please select a valid DSP module in the upper list!" , "Warning", JOptionPane.YES_NO_OPTION ) ;
			return ;
		} else {
			byte s8DspModID = MapTable_Module[nSelectedRow-1];		// because the first Row is Total, so minus 1
			AllDeviceRes[s8DspModID].RemoveState = REMOVE_STATE.DSP_REMOVE_STATE_START;
			DrawCount_RemoveState ( s8DspModID );
			
			for ( int i = 0; i < AllDeviceRes[s8DspModID].lTrunkNum; i ++ )
			{
				if ( AllDeviceRes[s8DspModID].pTrunk[i].State == TRUNK_STATE.TRK_FREE )
					Change_State ( AllDeviceRes[s8DspModID].pTrunk[i], TRUNK_STATE.TRK_WAIT_REMOVE );

				if ( AllDeviceRes[s8DspModID].pTrunk[i].deviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER )
				{
					if ( AllDeviceRes[s8DspModID].pTrunk[i].UserState == USER_STATE.USER_FREE )
						Change_UserState ( AllDeviceRes[s8DspModID].pTrunk[i], USER_STATE.USER_WAIT_REMOVE );
				}
			}

			// handle device : VOICE
			for ( int i = 0; i < AllDeviceRes[s8DspModID].lVocNum; i ++ )
			{
				if ( AllDeviceRes[s8DspModID].pVoice[i].State == VOICE_STATE.VOC_FREE )
				{
					Change_Voc_State ( AllDeviceRes[s8DspModID].pVoice[i], VOICE_STATE.VOC_WAIT_REMOVE);
				}
			}

			// check if all device is WAIT_OPEN or WAIT_REMOVE
			CheckRemoveReady ( s8DspModID );
		}
	}
	
	public void	ReOpen_AllDevice (){
		for (int i = 0; i < g_iTotalModule; i ++ ){
			OpenAllDevice_Dsp ( MapTable_Module[i] );
			DrawCount_ErrFlag (MapTable_Module[i]);
			DrawCount_RemoveState (MapTable_Module[i]);
		}
	}
}
 
// --------------------------------------------------------------------------------
// define the structure: Single DSP's available Device Resource
class	TYPE_XMS_DSP_DEVICE_RES_DEMO
{
	public static final int 		MAX_VOC_RES_NUM_EACH_DSP 	= 128; 
	public static final int 		MAX_PCM_RES_NUM_EACH_DSP 	= 4;   
	public static final int 		MAX_TRUNK_RES_NUM_EACH_DSP 	= 128;
	public static final int 		MAX_USER_RES_NUM_EACH_DSP	= 128;
	
	public int 	lFlag;				// If this DSP exist, 0: not exist, 1: exist

	public DeviceID_t	deviceID 		= new DeviceID_t();		// this DSP's deviceID
	public int			iSeqID;			// this DSP's Sequence ID
	public boolean		bOpenFlag;		// flag of OpenDevice OK
	public boolean		bErrFlag;		// flag of CloseDevice Event
	public int			RemoveState;	// the state of stop DSP hardware

	public int			lVocNum;			// the XMS_DEVMAIN_VOICE number in this DSP
	public int			lVocOpened;			// the VOICE number opened by OpenDevice()
	public int			lVocFreeNum;		// the free voice number in this DSP
	public VOICE_STRUCT	pVoice[] 		= new VOICE_STRUCT[MAX_VOC_RES_NUM_EACH_DSP];	// the structer of voice, alloc as need

	public int			lPcmNum;			// the XMS_DEVMAIN_DIGITAL_PORT number in this DPS
	public int			lPcmOpened;			// the PCM number opened by OpenDevice()
	public PCM_STRUCT	pPcm[] 			= new PCM_STRUCT[MAX_PCM_RES_NUM_EACH_DSP];		// the structer of PCM, alloc as need

	public int			lTrunkNum;			// the XMS_DEVMAIN_INTERFACE_CH number in this DSP
	public int			lTrunkOpened;		// the Trunk number opened by OpenDevice()
	public TRUNK_STRUCT	pTrunk[] 		= new TRUNK_STRUCT[MAX_TRUNK_RES_NUM_EACH_DSP];			// the structer of Trunk, alloc as need

}

class TYPE_CHANNEL_MAP_TABLE
{
	public byte      	m_s8ModuleID;    /*device module type*/
    public short     	m_s16ChannelID;  /*device chan id*/
} 

class TRUNK_STRUCT
{
	public DeviceID_t	deviceID 	= new DeviceID_t();
	public int			iSeqID;
	public int			iModSeqID;
	public int			iLineState;

	public DeviceID_t	VocDevID 	= new DeviceID_t();
	public DeviceID_t	LinkDevID 	= new DeviceID_t();

	public int			State;

	public int			UserState;
	public int			iUserSeqID;

	public int			DtmfCount;
	public byte 		DtmfBuf[] 	= new byte[32];

	public byte 		CallerCode[] = new byte[20];
	public byte		 	CalleeCode[] = new byte[20];

}

class VOICE_STRUCT
{
	public DeviceID_t	deviceID = new DeviceID_t();
	public int			iSeqID;
	public DeviceID_t	UsedDevID;
	public int			State;
}

class PCM_STRUCT
{
	public DeviceID_t	deviceID = new DeviceID_t();
	public int			iSeqID;
	public boolean		bOpenFlag;		// flag of OpenDevice OK
	public byte			u8E1Type;
	public int			s32AlarmVal;
} 

class	REMOVE_STATE
{
	public static final int DSP_REMOVE_STATE_NONE			= 0;		// Do not remove the DSP hardware
	public static final int DSP_REMOVE_STATE_START			= 1;		// Ready to remove DSP hardware, wait all the Devices' Resource release
	public static final int DSP_REMOVE_STATE_READY			= 2;		// All the Devices' Resource have released, start delete DSP hardware
}

class VOICE_STATE {
	public static final int 		VOC_WAITOPEN			= 0;
	public static final int 		VOC_FREE				= 1;
	public static final int 		VOC_USED				= 2;
	public static final int 		VOC_WAIT_REMOVE			= 3;
}

class TRUNK_STATE {
	public static final int 		TRK_WAITOPEN 			= 0;
	public static final int 		TRK_FREE     			= 1;			
	public static final int 		TRK_NOTHANDLE			= 2;
	public static final int 		TRK_CALLOUT				= 3;
	public static final int 		TRK_SIM_CALLOUT			= 4;
	public static final int 		TRK_SIM_LINK			= 5;
	public static final int 		TRK_SIM_ANALOG_OFFHOOK	= 6;
	public static final int 		TRK_SIM_ANALOG_DIALING	= 7;

	public static final int 		TRK_LINK				= 8;
	public static final int 		TRK_PLAYDTMF			= 9;
	public static final int 		TRK_HANGUP				= 10;
	public static final int 		TRK_FAIL				= 11;

	public static final int 		TRK_WAIT_REMOVE			= 12;
}

class USER_STATE {
	public static final int 		USER_WAITOPEN			= 0;
	public static final int 		USER_FREE				= 1;	
	public static final int 		USER_OFFHOOK			= 2;
	public static final int 		USER_CALLOUT			= 3;
	public static final int 		USER_LINK				= 4;
	public static final int 		USER_WAITHANGUP			= 5;
	public static final int 		USER_WAIT_REMOVE		= 6;
	public static final int 		USER_RING				= 7;
}

