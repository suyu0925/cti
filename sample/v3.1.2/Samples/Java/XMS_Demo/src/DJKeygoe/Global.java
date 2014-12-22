package DJKeygoe;

import javax.swing.JOptionPane;

public class Global {
	public static final int 		MAX_DSP_MODULE_NUMBER_OF_XMS = 256;
	public static final int 		MAX_VOC_RES_NUM_EACH_DSP 	= 128;
	public static final int 		MAX_PCM_RES_NUM_EACH_DSP 	= 4;
	public static final int 		MAX_TRUNK_RES_NUM_EACH_DSP 	= 128;
	
	public TYPE_XMS_DSP_DEVICE_RES_DEMO[] AllDeviceRes = new TYPE_XMS_DSP_DEVICE_RES_DEMO[MAX_DSP_MODULE_NUMBER_OF_XMS];
	
	public int g_iTotalModule 		= 0;
	
	public byte MapTable_Module[] 	= new byte[MAX_DSP_MODULE_NUMBER_OF_XMS];
	
	public int g_iTotalPcm 			= 0;
    public int g_iTotalPcmOpened 	= 0;
    public TYPE_CHANNEL_MAP_TABLE[] MapTable_Pcm   = new TYPE_CHANNEL_MAP_TABLE[64];
	
    public int g_iTotalTrunk 		= 0;
    public int g_iTotalTrunkOpened 	= 0;
    public TYPE_CHANNEL_MAP_TABLE[] MapTable_Trunk = new TYPE_CHANNEL_MAP_TABLE[2048];
    
    public int g_iTotalVoice 		= 0;
    public int g_iTotalVoiceOpened  = 0;
    public int g_iTotalVoiceFree    = 0;
    public TYPE_CHANNEL_MAP_TABLE[] MapTable_Voice = new TYPE_CHANNEL_MAP_TABLE[2048];
    
    public String cfg_CallingNum     = new String();
    public String cfg_SimCalledNum   = new String();
    public String cfg_VocPath		 = new String();
    public ServerID_t cfg_ServerID 	 = new ServerID_t();
    public int cfg_iPartWork		 = 0;
    public int cfg_iPartWorkModuleID = 0;
    public int cfg_s32DebugOn		 = 0;
    public int cfg_iVoiceRule		 = 0;		// search voice in Fix Relationship
    public int cfg_iDispChnl		 = 0;
    
    public TYPE_ANALOG_GTD_PARAM 		g_Param_Analog = new TYPE_ANALOG_GTD_PARAM ();
    
    public CmdParamData_GtdFreq_t		g_TmpGtdFreq  = new CmdParamData_GtdFreq_t();
	public CmdParamData_GtdProtoType_t	g_TmpGtdProto = new CmdParamData_GtdProtoType_t();
	public CmdParamData_AnalogTrunk_t   g_AnalogTrk   = new CmdParamData_AnalogTrunk_t();
	public CmdParamData_Voice_t 		g_CmdVoc	  = new CmdParamData_Voice_t();
	public CmdParamData_CAS_t 			g_Param_CAS   = new CmdParamData_CAS_t();
	
	public byte	callerDtmf[] 		= new byte[20];
	
	public int dtmfIndex			= 0;
	
    public int g_acsHandle			= -1;
    
    public static int GetByteArrLen(byte s8Arr[]){ 
    	int i = 0;
    	
    	while (s8Arr[i] != 0){
    		i++;
    	}
   
    	return i;
    }
    
    public void InitCmdParamData_CASData(){
		for (int i = 0; i < 16; i++){
			g_Param_CAS.m_CalledTable[i] = new CAS_CalledTableDesc_t();
		}
	}
    
    public void InitGlobalObjectArr(){ 
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
    	}
    }
    
	public void CharsToByte(byte[] DestArr, char []SourArr, int nLen){ /**/
		for (int i = 0; i < nLen; i++){
			DestArr[i] = (byte)SourArr[i];
		}
	}
	
	public void ReadFromConfig(){
		String strIniFilePath = new String("XMS_Demo.ini");
		try{
			String strIp = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "IpAddr", "192.168.10.74");
			CharsToByte(cfg_ServerID.m_s8ServerIp, strIp.toCharArray(), strIp.length());

			String strPort = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "Port", "9000");
			cfg_ServerID.m_u32ServerPort = Integer.parseInt(strPort);
			
			String strUserName = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "UserName", "");
			CharsToByte(cfg_ServerID.m_s8UserName, strUserName.toCharArray(), strUserName.length());
			
			String strPwd = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "PassWord", "");
			CharsToByte(cfg_ServerID.m_s8UserPwd, strPwd.toCharArray(), strPwd.length());
			
			cfg_VocPath = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "VocPath", "..\\VOC\\");
			
			String strDispChannel = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "DispChnl", "30");
			cfg_iDispChnl = Integer.parseInt(strDispChannel);
			
			String strVocRule = JIniFile.getProfileString(strIniFilePath, "ConfigInfo", "VoiceRule", "0");
			cfg_iVoiceRule = Integer.parseInt(strVocRule);
			
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
		String strIniFilePath = new String("XMS_Demo.ini");
		try{
			String strIp = new String(cfg_ServerID.m_s8ServerIp, "UTF-8");
			JIniFile.setProfileString(strIniFilePath, "ConfigInfo", "IpAddr", strIp);

			String strPort = Integer.toString(cfg_ServerID.m_u32ServerPort);
			JIniFile.setProfileString(strIniFilePath, "ConfigInfo", "Port", strPort);
			
			JIniFile.setProfileString(strIniFilePath, "ConfigInfo", "VocPath", cfg_VocPath);
			
			String strDispChannel = Integer.toString(cfg_iDispChnl);
			JIniFile.setProfileString(strIniFilePath, "ConfigInfo", "DispChnl", strDispChannel);
			
			String strVocRule = Integer.toString(cfg_iVoiceRule);
			JIniFile.setProfileString(strIniFilePath, "ConfigInfo", "VoiceRule", strVocRule);
			
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
	
	public boolean AddDeviceRes_Voice(DJEvtQueryDeviceData acsQueryDevice){
		int nDevNum = acsQueryDevice.acsDevListHead.m_s32DeviceNum; 
		byte bDspModID = (byte)acsQueryDevice.acsDevListHead.m_s32ModuleID;
		
		if (bDspModID < 0 || bDspModID > 255) {
			System.out.println("Invalid DSP ID,Add Voice Resource Fail!");
			return false;
		}
		
		AllDeviceRes[bDspModID].lVocNum = nDevNum;
		AllDeviceRes[bDspModID].lVocOpened = 0;
		AllDeviceRes[bDspModID].lVocFreeNum = 0;
		
		for (int i = 0; i < nDevNum; i++){
			AllDeviceRes[bDspModID].pVoice[i].deviceID.CopyDeviceID_tObj(acsQueryDevice.device[i]);
			AllDeviceRes[bDspModID].pVoice[i].State = VOICE_STATE.VOC_WAITOPEN;
		}
		return true;
	}
	
	public boolean AddDeviceRes_Pcm(DJEvtQueryDeviceData acsQueryDevice){
		int nDevNum = acsQueryDevice.acsDevListHead.m_s32DeviceNum;
		byte bDspModID = (byte)acsQueryDevice.acsDevListHead.m_s32ModuleID;
		
		if (bDspModID < 0 || bDspModID > 255) {
			System.out.println("Invalid DSP ID,Add Pcm Resource Fail!");
			return false;
		}
		
		AllDeviceRes[bDspModID].lPcmNum = nDevNum;
		AllDeviceRes[bDspModID].lPcmOpened = 0;
		
		for (int i = 0; i < nDevNum; i++){		
			AllDeviceRes[bDspModID].pPcm[i].deviceID.CopyDeviceID_tObj(acsQueryDevice.device[i]);
			AllDeviceRes[bDspModID].pPcm[i].bOpenFlag = false;
		}
		return true;
	}
	
	public boolean AddDeviceRes_Board(DJEvtQueryDeviceData acsQueryDevice){
		int nDevNum = acsQueryDevice.acsDevListHead.m_s32DeviceNum; //
		byte bDspModID = (byte)acsQueryDevice.acsDevListHead.m_s32ModuleID;
		
		if (bDspModID < 0 || bDspModID > 255) {
			System.out.println("Invalid DSP ID,Add Board Fail!");
			return false;
		}
		
		if (AllDeviceRes[bDspModID].lFlag == 0 && nDevNum > 0){
			AllDeviceRes[bDspModID].deviceID.CopyDeviceID_tObj(acsQueryDevice.device[0]);
			AllDeviceRes[bDspModID].bOpenFlag = false;
			AllDeviceRes[bDspModID].bErrFlag = false;
			AllDeviceRes[bDspModID].RemoveState = REMOVE_STATE.DSP_REMOVE_STATE_NONE;
		}
		
		return true;
	}
	
	public boolean AddDeviceRes_Trunk(DJEvtQueryDeviceData acsQueryDevice){
		int nDevNum = acsQueryDevice.acsDevListHead.m_s32DeviceNum;
		byte bDspModID = (byte)acsQueryDevice.acsDevListHead.m_s32ModuleID;
		
		if (bDspModID < 0 || bDspModID > 255) {
			System.out.println("Invalid DSP ID,Add Board Fail!");
			return false;
		}
		
		AllDeviceRes[bDspModID].lTrunkNum = nDevNum;
		AllDeviceRes[bDspModID].lTrunkOpened = 0;
		
		for (int i = 0; i < nDevNum; i++){
			AllDeviceRes[bDspModID].pTrunk[i].deviceID.CopyDeviceID_tObj(acsQueryDevice.device[i]);
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
	
	public int StopPlayFile(DeviceID_t VocDevice){
		int nRet = -1;
		
		ControlPlay_t ctrlPlay = new ControlPlay_t();
		PrivateData_t privateData = new PrivateData_t();
		
		ctrlPlay.m_u16ControlType = XMS_CTRL_PLAY_TYPE.XMS_STOP_PLAY;
		privateData.m_u32DataSize = 0;
		
		nRet = NewJDialog.g_DJApi.XMS_ctsControlPlay(g_acsHandle, VocDevice, ctrlPlay, privateData);
		
		return nRet;
	}
	
	public int PlayFile(DeviceID_t VocDevice, String FileName, byte s8PlayTag, boolean bIsQueue){
		PlayProperty_t	PlayProty = new PlayProperty_t();
		byte s8FilePath[] = FileName.getBytes();
		
		if (bIsQueue){
			PlayProty.m_u16PlayType = XMS_PLAY_TYPE.XMS_PLAY_TYPE_FILE_QUEUE;
		}
		else {
			PlayProty.m_u16PlayType = XMS_PLAY_TYPE.XMS_PLAY_TYPE_FILE;
		}
		
		PlayProty.m_u8TaskID = s8PlayTag;
		
		for (int i = 0; i < FileName.length() && i < 128; i++){ //128 
			PlayProty.m_s8PlayContent[i] = s8FilePath[i];
		}
		
		PrivateData_t privateData = new PrivateData_t();
		
		privateData.m_u32DataSize = 0;
		int nRet = NewJDialog.g_DJApi.XMS_ctsPlay(g_acsHandle, VocDevice, PlayProty, privateData);
		
		return nRet;
	}
	
	public int RecordFile ( DeviceID_t VocDevID, String RecordFilePath, int u32RecSize, boolean bIsAppend )
	{	
		RecordProperty_t	recordProperty = new RecordProperty_t();
		
		recordProperty.m_u32MaxSize = u32RecSize;

		if ( bIsAppend )
			recordProperty.m_s8IsAppend = 1;
		else
			recordProperty.m_s8IsAppend = 0;

		byte s8FileName[] = RecordFilePath.getBytes();
		for(int i = 0; i < RecordFilePath.length() && i < 259; i++){ //259=260-1 260 m_s8FileName����
			recordProperty.m_s8FileName[i] = s8FileName[i];
		}

		PrivateData_t privateData = new PrivateData_t();
		
		privateData.m_u32DataSize = 0;
		int nRet = NewJDialog.g_DJApi.XMS_ctsRecord ( g_acsHandle, VocDevID, recordProperty, privateData );

		return nRet;
	}
	
	public int StopRecordFile(DeviceID_t VocDeviceID){
		ControlRecord_t	controlRecord = new ControlRecord_t();
		
		controlRecord.m_u32ControlType = XMS_CTRL_RECORD_TYPE.XMS_STOP_RECORD;
		
		PrivateData_t privateData = new PrivateData_t();
		
		privateData.m_u32DataSize = 0;
		
		return NewJDialog.g_DJApi.XMS_ctsControlRecord ( g_acsHandle, VocDeviceID, controlRecord, privateData );
	}
	
	public void My_DualUnlink (DeviceID_t Dev1, DeviceID_t Dev2)
	{
		PrivateData_t privateData = new PrivateData_t();
		
		privateData.m_u32DataSize = 0;
		
		NewJDialog.g_DJApi.XMS_ctsUnlinkDevice ( g_acsHandle, Dev1, Dev2, privateData ); 
		NewJDialog.g_DJApi.XMS_ctsUnlinkDevice ( g_acsHandle, Dev2, Dev1, privateData ); 
	}
	
	public void My_DualLink (DeviceID_t Dev1, DeviceID_t Dev2)
	{
		PrivateData_t privateData = new PrivateData_t();
		
		privateData.m_u32DataSize = 0;
		
		NewJDialog.g_DJApi.XMS_ctsLinkDevice ( g_acsHandle, Dev1, Dev2, privateData ); 
		NewJDialog.g_DJApi.XMS_ctsLinkDevice ( g_acsHandle, Dev2, Dev1, privateData ); 
	}
	
	public void FreeOneFreeVoice(DeviceID_t VocDevice){
		byte s8ModuleID = VocDevice.m_s8ModuleID;
		
		if (AllDeviceRes[s8ModuleID].lFlag == 1){
			VOICE_STRUCT OneVoc = GetVoiceStructByDevice(VocDevice.m_s8ModuleID, VocDevice.m_s16ChannelID);
			
			Change_Voc_State(OneVoc, VOICE_STATE.VOC_FREE);
			
			AllDeviceRes[s8ModuleID].lVocFreeNum++;
			g_iTotalVoiceFree++;
			
			DrawCount_Voc ( s8ModuleID );
		}
	}
	
	public void	CheckRemoveReady ( byte s8DspModID ){
		int			i;

		// check device : INTERFACE_CH
		for ( i = 0; i < AllDeviceRes[s8DspModID].lTrunkNum; i ++ )
		{
			if ( (AllDeviceRes[s8DspModID].pTrunk[i].State != TRUNK_STATE.TRK_WAITOPEN)
				&& (AllDeviceRes[s8DspModID].pTrunk[i].State != TRUNK_STATE.TRK_WAIT_REMOVE) )
			{
				return;
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
	
	public void DrawMain_VocInfo(TRUNK_STRUCT OneTrk){
		if (OneTrk.VocDevID.m_s16DeviceMain != 0){
			int iDispRow = CalDispRow(OneTrk.iSeqID);
			
			if (iDispRow < 0) return;
			
			NewJDialog.inst.DrawMain(iDispRow, 8, Integer.toString(OneTrk.VocDevID.m_s8ModuleID) + "," + Integer.toString(OneTrk.deviceID.m_s16ChannelID));
		}
	}
	public void InitTrunkChannel(TRUNK_STRUCT pOneTrk){
		Change_State ( pOneTrk, TRUNK_STATE.TRK_FREE );

		pOneTrk.InitCallCode();
		pOneTrk.InitDtmfBuf();

		DrawMain_DTMF ( pOneTrk );

		
		pOneTrk.VocDevID = null;
		
		//DrawMain_VocInfo ( pOneTrk );
	}
	
	public void ResetTrunk(TRUNK_STRUCT pOneTrk){
		if (pOneTrk.VocDevID != null){
			StopPlayFile(pOneTrk.VocDevID);
			
			if (pOneTrk.VocDevID.m_s16DeviceMain != 0){
				My_DualUnlink(pOneTrk.deviceID, pOneTrk.VocDevID);
				
				FreeOneFreeVoice(pOneTrk.VocDevID);
				
				GetVoiceStructByDevice(pOneTrk.VocDevID.m_s8ModuleID, pOneTrk.VocDevID.m_s16ChannelID).UsedDevID = null;
				
				pOneTrk.VocDevID = null; 
				//DrawMain_VocInfo ( pOneTrk );
			}
		}
		InitTrunkChannel ( pOneTrk );
		
		// Search Free Voice for get CallerID(FSK)
		// if you needn't CallerID, ignore next line
		PrepareForCallerID ( pOneTrk );
	}
	
	public void TrunkWork(DeviceID_t dev, Acs_Evt_t acsEvtData, Object obj){
		
		int nEvtType = acsEvtData.m_s32EventType;
		
		TRUNK_STRUCT OneTrk = GetTrunkStructByDevice(dev.m_s8ModuleID, dev.m_s16ChannelID);
		PrivateData_t privateData = new PrivateData_t();
		
		privateData.m_u32DataSize = 0;

		if (nEvtType == XMS_EVT_TYPE.XMS_EVT_CLEARCALL){
			if ((OneTrk.State != TRUNK_STATE.TRK_FREE) && (OneTrk.State != TRUNK_STATE.TRK_WAIT_REMOVE)){
				ResetTrunk(OneTrk);
				return ;
			}
		}
		
		if (OneTrk.deviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH &&
				OneTrk.deviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK){
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_RECVIODATA){ //
				
				DJEvtRecvIOData acsRecvData = (DJEvtRecvIOData)obj;
				
				if(acsRecvData.acsIOData.m_u16IoType == XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_GTG){
					String str = new String(acsRecvData.recvIOData);
					NewJDialog.inst.ListBox_AddMsg(str);
					if (acsRecvData.recvIOData[0] == (byte)'I' ||
							acsRecvData.recvIOData[0] == (byte)'J' ||
							acsRecvData.recvIOData[0] == (byte)'K'){ //Recv Busy Tone
						
						NewJDialog.g_DJApi.XMS_ctsResetDevice(g_acsHandle, OneTrk.deviceID, privateData);
						NewJDialog.g_DJApi.XMS_ctsClearCall(g_acsHandle, OneTrk.deviceID, 0, privateData);
						
						ResetTrunk(OneTrk);
					}
			
				}
			}
		}
		
		switch(OneTrk.State){
		case TRUNK_STATE.TRK_FREE:{
			SpecialForCas(OneTrk, nEvtType);
			
			if (OneTrk.deviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH
					&& OneTrk.deviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK){
				if (nEvtType == XMS_EVT_TYPE.XMS_EVT_RECVIODATA){ //
					
					DJEvtRecvIOData acsRecvData = (DJEvtRecvIOData)obj;
					if (acsRecvData.acsIOData.m_u16IoType == XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_FSK){
						
						Analog_Common_Code.ConvertRawFskToCallerID(acsRecvData.recvIOData, acsRecvData.acsIOData.m_u16IoDataLen, OneTrk.CallerCode, 20);
					}
					
					if (acsRecvData.acsIOData.m_u16IoType == XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF){
						if (acsRecvData.recvIOData[0] == (byte)'D' || acsRecvData.recvIOData[0] == (byte)'d'){
							dtmfIndex = 0;
						}
						else if (acsRecvData.recvIOData[0] == (byte)'C' || acsRecvData.recvIOData[0] == (byte)'c'){
							for (int i = 0; i < 20; i++){
								OneTrk.CallerCode[i] = (byte)0;
							}
						}
						else if (acsRecvData.recvIOData[0] >= (byte)'0' && acsRecvData.recvIOData[0] <= (byte)'9'){
							OneTrk.CallerCode[dtmfIndex++] = acsRecvData.recvIOData[0];
						
							DrawMain_CallInfo( OneTrk );
						}
					}
				}
			}
			
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_CALLIN){ //
				
				DJEvtCallInData acsCallIn = (DJEvtCallInData)obj;
				
				if (OneTrk.deviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH
						&& OneTrk.deviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK){
					My_DualUnlink(OneTrk.deviceID, OneTrk.VocDevID);
					
					FreeOneFreeVoice (OneTrk.VocDevID);
					
					VOICE_STRUCT OneVoc = GetVoiceStructByDevice(OneTrk.VocDevID.m_s8ModuleID, OneTrk.deviceID.m_s16ChannelID);
					
					OneVoc.UsedDevID = null;
					OneTrk.VocDevID = null;
					
					//DrawMain_VocInfo (OneTrk);
				}
				
				NewJDialog.g_DJApi.XMS_ctsAlertCall(g_acsHandle, OneTrk.deviceID, null);
				NewJDialog.g_DJApi.XMS_ctsAnswerCallIn(g_acsHandle, OneTrk.deviceID, null);
				
				if ( OneTrk.deviceID.m_s16DeviceSub != XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK ){
					for (int i = 0; i < 20; i++){
						OneTrk.CalleeCode[i] = acsCallIn.acsCallInData.m_s8CalledNum[i];
						OneTrk.CallerCode[i] = acsCallIn.acsCallInData.m_s8CallingNum[i];
					}
				}
	
				DrawMain_CallInfo( OneTrk );
				Change_State ( OneTrk, TRUNK_STATE.TRK_WAIT_ANSWERCALL );
			
				break;
			}
		}
		
		case TRUNK_STATE.TRK_WAIT_ANSWERCALL: {
			SpecialForCas(OneTrk, nEvtType);
			
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_ANSWERCALL){

				DeviceID_t FreeVocDeviceID = SearchOneFreeVoice(OneTrk);
				
				if (FreeVocDeviceID != null){
					OneTrk.u8PlayTag = 16;
					
					OneTrk.VocDevID = FreeVocDeviceID;
					
					GetVoiceStructByDevice(FreeVocDeviceID.m_s8ModuleID, FreeVocDeviceID.m_s16ChannelID).UsedDevID = OneTrk.deviceID;
					
					DrawMain_VocInfo(OneTrk);
					
					My_DualLink(OneTrk.deviceID, OneTrk.VocDevID);
		
					if ( OneTrk.deviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH
							&& OneTrk.deviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK ){
						SetGtD_AnalogTrunk(FreeVocDeviceID);		// prepare for get Busy Tone
					}
					
					Change_State ( OneTrk, TRUNK_STATE.TRK_WAIT_LINKOK );
				}
			}
			break;
		}
		
		case TRUNK_STATE.TRK_WAIT_LINKOK: {

			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_LINKDEVICE){
				OneTrk.u8PlayTag++;
				
				String PlayFile1 = cfg_VocPath;
				PlayFile1 += "\\bank.001";
				
				PlayFile(OneTrk.VocDevID, PlayFile1, OneTrk.u8PlayTag, false);
				Change_State(OneTrk, TRUNK_STATE.TRK_WELCOME);
			}
			break;
		}
		
		case TRUNK_STATE.TRK_WELCOME: {

			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_PLAY){
				
				DJEvtPlayData acsEvtPlay = (DJEvtPlayData)obj;
				
				if (acsEvtPlay.acsMediaProcData.m_u8TaskID == OneTrk.u8PlayTag){
					
					OneTrk.u8PlayTag++;
					
					String PlayFile2 = cfg_VocPath;
					PlayFile2 += "\\bank.002";
					
					PlayFile(OneTrk.VocDevID, PlayFile2, OneTrk.u8PlayTag, false);
					Change_State(OneTrk, TRUNK_STATE.TRK_ACCOUNT);
				}
			}
				
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_RECVIODATA){
				DJEvtRecvIOData acsRecvData = (DJEvtRecvIOData)obj;
				
				if (acsRecvData.acsIOData.m_u16IoType == XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF
						&& acsRecvData.acsIOData.m_u16IoDataLen > 0){ //Recv DTMF
					My_AddDtmfBuf(OneTrk, acsRecvData.recvIOData[0]);
					
					DrawMain_DTMF(OneTrk);
					
					StopPlayFile ( OneTrk.VocDevID );
					
					Change_State ( OneTrk, TRUNK_STATE.TRK_ACCOUNT );
				}	
			}
			break;
		}
		
		case TRUNK_STATE.TRK_ACCOUNT: {
			
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_RECVIODATA){
				
				DJEvtRecvIOData acsRecvData = (DJEvtRecvIOData)obj;
				
				if (acsRecvData.acsIOData.m_u16IoType == XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF
						&& acsRecvData.acsIOData.m_u16IoDataLen > 0){ //Recv DTMF
					My_AddDtmfBuf(OneTrk, acsRecvData.recvIOData[0]);
					
					DrawMain_DTMF(OneTrk);
					
					StopPlayFile ( OneTrk.VocDevID );
					
					if (OneTrk.DtmfCount >= 8){
						String PlayFile3 = cfg_VocPath;
						PlayFile3 += "\\bank.003";
						
						OneTrk.u8PlayTag++;
						
						PlayFile(OneTrk.VocDevID, PlayFile3, OneTrk.u8PlayTag, false);
						
						OneTrk.DtmfBuf[0] = 0;
						OneTrk.DtmfCount = 0;
						
						Change_State (OneTrk, TRUNK_STATE.TRK_PASSWORD );
					}
					
				}
			}
			
			break;
			}
		
		case TRUNK_STATE.TRK_PASSWORD: {
			
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_RECVIODATA){
			
				DJEvtRecvIOData acsRecvData = (DJEvtRecvIOData)obj;
				
				if (acsRecvData.acsIOData.m_u16IoType == XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF
						&& acsRecvData.acsIOData.m_u16IoDataLen > 0){ //Recv DTMF
					My_AddDtmfBuf(OneTrk, acsRecvData.recvIOData[0]);
					
					DrawMain_DTMF(OneTrk);
					
					StopPlayFile ( OneTrk.VocDevID );
					
					if (OneTrk.DtmfCount >= 6){
						String PlayFile4 = cfg_VocPath;
						PlayFile4 += "\\bank.004";
						
						OneTrk.u8PlayTag++;
						
						PlayFile(OneTrk.VocDevID, PlayFile4, OneTrk.u8PlayTag, false);
						
						OneTrk.DtmfBuf[0] = 0;
						OneTrk.DtmfCount = 0;
						
						Change_State (OneTrk, TRUNK_STATE.TRK_SELECT );
					}
				}
			}
			break;
		}
		
		case TRUNK_STATE.TRK_SELECT: {
			
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_RECVIODATA){
				
				DJEvtRecvIOData acsRecvData = (DJEvtRecvIOData)obj;
				
				if (acsRecvData.acsIOData.m_u16IoType == XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF
						&& acsRecvData.acsIOData.m_u16IoDataLen > 0){ //Recv DTMF
					
					My_AddDtmfBuf(OneTrk, acsRecvData.recvIOData[0]);
					
					DrawMain_DTMF(OneTrk);
					
					OneTrk.u8PlayTag++;
					
					String StrPlayFilePath = cfg_VocPath;
					
					switch(acsRecvData.recvIOData[0]){
					case (byte)'1': {
						StopPlayFile ( OneTrk.VocDevID );
						
						StrPlayFilePath += "\\bank.005";
						PlayFile(OneTrk.VocDevID, StrPlayFilePath, OneTrk.u8PlayTag, true);
						
						PlayIndex ( OneTrk.VocDevID, 5, OneTrk.u8PlayTag, true );
						PlayIndex ( OneTrk.VocDevID, 12, OneTrk.u8PlayTag, true );
						PlayIndex ( OneTrk.VocDevID, 8, OneTrk.u8PlayTag, true );
						PlayIndex ( OneTrk.VocDevID, 11, OneTrk.u8PlayTag, true );
						PlayIndex ( OneTrk.VocDevID, 9, OneTrk.u8PlayTag, true );
						PlayIndex ( OneTrk.VocDevID, 10, OneTrk.u8PlayTag, true );
						PlayIndex ( OneTrk.VocDevID, 15, OneTrk.u8PlayTag, true );
						PlayIndex ( OneTrk.VocDevID, 8, OneTrk.u8PlayTag, true );

						PlayIndex ( OneTrk.VocDevID, 16, OneTrk.u8PlayTag, true );		// bank.008

						Change_State ( OneTrk, TRUNK_STATE.TRK_PLAYRESULT );
						
						break;
					}
					
					case (byte)'2': {
						StopPlayFile ( OneTrk.VocDevID );

						StrPlayFilePath += "\\bank.006";
						
						PlayFile ( OneTrk.VocDevID, StrPlayFilePath, OneTrk.u8PlayTag, true );
						
						PlayIndex ( OneTrk.VocDevID, 0, OneTrk.u8PlayTag, true );
						PlayIndex ( OneTrk.VocDevID, 15, OneTrk.u8PlayTag, true );
						PlayIndex ( OneTrk.VocDevID, 4, OneTrk.u8PlayTag, true );
						PlayIndex ( OneTrk.VocDevID, 8, OneTrk.u8PlayTag, true );

						String FilePath8 = cfg_VocPath;
						
						FilePath8 += "\\bank.008";
				
						PlayFile ( OneTrk.VocDevID, FilePath8, OneTrk.u8PlayTag, true );

						Change_State ( OneTrk, TRUNK_STATE.TRK_PLAYRESULT );
						
						break;
					}
					
					case (byte)'3': {
						
						StopPlayFile ( OneTrk.VocDevID );

						String FilePath7 = cfg_VocPath;
						FilePath7 += "\\bank.007";
						PlayFile ( OneTrk.VocDevID, FilePath7, OneTrk.u8PlayTag, true );
						
						String FilePathD3 = cfg_VocPath;
						FilePathD3 += "\\D3";
						PlayFile ( OneTrk.VocDevID, FilePathD3, OneTrk.u8PlayTag, true );

						String FilePathD13 = cfg_VocPath;
						FilePathD13 += "\\D13";
						PlayFile ( OneTrk.VocDevID, FilePathD13, OneTrk.u8PlayTag, true );

						String FilePathD7 = cfg_VocPath;
						FilePathD7 += "\\D7";
						PlayFile ( OneTrk.VocDevID, FilePathD7, OneTrk.u8PlayTag, true );

						String FilePathD12 = cfg_VocPath;
						FilePathD12 += "\\D12";
						PlayFile ( OneTrk.VocDevID, FilePathD12, OneTrk.u8PlayTag, true );

						String FilePath8 = cfg_VocPath;
						FilePath8 += "\\bank.008";
						PlayFile ( OneTrk.VocDevID, FilePath8, OneTrk.u8PlayTag, true );

						Change_State ( OneTrk, TRUNK_STATE.TRK_PLAYRESULT );
						
						break;
					}
					
					case (byte)'4': {					
						StopPlayFile ( OneTrk.VocDevID );

						String RecordFile = cfg_VocPath;
						RecordFile += "\\DemoRec.";
						RecordFile += Integer.toString(OneTrk.iSeqID);
						
						RecordFile ( OneTrk.VocDevID, RecordFile, 8000*10, false );

						Change_State ( OneTrk, TRUNK_STATE.TRK_RECORDFILE );
						
						break;
					}
					
					default: {
						break;
					}
					
					}
				}
			}
			break;
		}
		
		case TRUNK_STATE.TRK_PLAYRESULT: {
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_PLAY) {
				
				DJEvtPlayData acsPlay = (DJEvtPlayData)obj;
				
				if(acsPlay.acsMediaProcData.m_u8TaskID == OneTrk.u8PlayTag){

					privateData.m_u32DataSize = 0;
					NewJDialog.g_DJApi.XMS_ctsClearCall(g_acsHandle, OneTrk.deviceID, 0, privateData);
					
					Change_State ( OneTrk, TRUNK_STATE.TRK_HANGON );
				}
			}
			break;
		}
		
		case TRUNK_STATE.TRK_PLAYRECORD: {
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_PLAY){
				
				DJEvtPlayData acsPlay = (DJEvtPlayData)obj;
				
				if(acsPlay.acsMediaProcData.m_u8TaskID == OneTrk.u8PlayTag){

					privateData.m_u32DataSize = 0;
					NewJDialog.g_DJApi.XMS_ctsClearCall(g_acsHandle, OneTrk.deviceID, 0, privateData);
					
					Change_State ( OneTrk, TRUNK_STATE.TRK_HANGON );
				}
			}
			break;
		}
		
		case TRUNK_STATE.TRK_RECORDFILE: {
		
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_RECVIODATA){
				
				DJEvtRecvIOData recvData = (DJEvtRecvIOData)obj;
				
				if (recvData.acsIOData.m_u16IoType == XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF
						&& recvData.acsIOData.m_u16IoDataLen > 0){
					My_AddDtmfBuf ( OneTrk, recvData.recvIOData[0] );
					DrawMain_DTMF ( OneTrk );

					StopRecordFile ( OneTrk.VocDevID );
					
				}
			}
				
			if (nEvtType == XMS_EVT_TYPE.XMS_EVT_RECORD){
				
				OneTrk.u8PlayTag++;
				
				String RecordFilePath = cfg_VocPath;
				
				RecordFilePath += "\\DemoRec.";
				RecordFilePath += Integer.toString(OneTrk.iSeqID);
				
				PlayFile(OneTrk.VocDevID, RecordFilePath, OneTrk.u8PlayTag, false);
				
				Change_State ( OneTrk, TRUNK_STATE.TRK_PLAYRECORD );
			}	
			break;
		}
			
	}
	}
	
	public int	 PlayIndex ( DeviceID_t	VocDevID, int u16Index, byte u8PlayTag, boolean bIsQueue ){	
		PlayProperty_t  playProperty = new PlayProperty_t();
		
		if ( bIsQueue ){
			playProperty.m_u16PlayType = XMS_PLAY_TYPE.XMS_PLAY_TYPE_INDEX_QUEUE;
		}		
		else{
			playProperty.m_u16PlayType = XMS_PLAY_TYPE.XMS_PLAY_TYPE_INDEX;	
		}

		playProperty.m_u8TaskID = u8PlayTag;

		playProperty.m_u16PlayIndex = (short)u16Index;
		
		PrivateData_t privateData = new PrivateData_t();
		
		privateData.m_u32DataSize = 0;
		int nRet = NewJDialog.g_DJApi.XMS_ctsPlay ( g_acsHandle, VocDevID, playProperty, privateData );

		return nRet;
	}
	
	public void My_AddDtmfBuf(TRUNK_STRUCT OneTrk, byte ch){
		if (OneTrk.DtmfCount < 32-1){
			OneTrk.DtmfBuf[OneTrk.DtmfCount] = ch;
			OneTrk.DtmfCount++;
			OneTrk.DtmfBuf[OneTrk.DtmfCount] = 0;
		}
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
					DrawMain_VocInfo ( OneTrunk );

					g_Param_CAS.m_VocDevID = FreeVocDeviceID;
					NewJDialog.g_DJApi.XMS_ctsSetParam ( g_acsHandle, OneTrunk.deviceID, (short)XMS_CAS_PARAM_TYPE.CAS_PARAM_UNIPARAM, (short)0, g_Param_CAS);
				}
			}
		}
			

		if ( nEvtType == XMS_EVT_TYPE.XMS_EVT_CAS_MFC_END ){	/* receive MFC end, release Voice Device */
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
	
	public void Change_Voc_State(VOICE_STRUCT OneVoc, int NewState){
		OneVoc.State = NewState;
		
		if ( (AllDeviceRes[OneVoc.deviceID.m_s8ModuleID].RemoveState == REMOVE_STATE.DSP_REMOVE_STATE_START)
				&& (NewState == VOICE_STATE.VOC_FREE) ){
				
				OneVoc.State = VOICE_STATE.VOC_WAIT_REMOVE;

				CheckRemoveReady ( OneVoc.deviceID.m_s8ModuleID );
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
	
	public void SetGtD_AnalogTrunk(DeviceID_t VocDev){
		g_CmdVoc.m_u8GtdCtrlValid = 1 ;						//Enable GTD
		g_CmdVoc.m_VocGtdControl.m_u8ChannelEnable = 1;		//Enable Gtd channel
		g_CmdVoc.m_VocGtdControl.m_u8DTMFEnable = 1;			// Detect DTMF
		g_CmdVoc.m_VocGtdControl.m_u8GTDEnable = 1;			// Detect GTD 
		g_CmdVoc.m_VocGtdControl.m_u8FSKEnable = 1;			// Detect FSK for receive CallerID

		g_CmdVoc.m_VocGtdControl.m_u8EXTEnable = 0x2;		// Enable PVD Detect

		g_CmdVoc.m_VocGtdControl.m_u8GTDID[0] = (byte)'G';
		g_CmdVoc.m_VocGtdControl.m_u8GTDID[1] = (byte)'H';
		g_CmdVoc.m_VocGtdControl.m_u8GTDID[2] = (byte)'I';
		g_CmdVoc.m_VocGtdControl.m_u8GTDID[3] = (byte)'J';
		g_CmdVoc.m_VocGtdControl.m_u8GTDID[4] = (byte)'K';

		int nRet = NewJDialog.g_DJApi.XMS_ctsSetParam(g_acsHandle, VocDev, (short)XMS_VOC_PARAM_TYPE.VOC_PARAM_UNIPARAM, (short)0, g_CmdVoc);
		NewJDialog.inst.ListBox_AddMsg("Set GTD ret = " + Integer.toString(nRet));
	}
	
	public void PrepareForCallerID(TRUNK_STRUCT OneTrk){
		if (OneTrk.deviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH
				&& OneTrk.deviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK){
			
			DeviceID_t OneFreeVoc = SearchOneFreeVoice(OneTrk);
			
			if (OneFreeVoc != null){
				OneTrk.VocDevID = OneFreeVoc;
				GetVoiceStructByDevice(OneFreeVoc.m_s8ModuleID, OneFreeVoc.m_s16ChannelID).UsedDevID = OneTrk.deviceID;
				
				My_DualLink(OneTrk.deviceID, OneTrk.VocDevID);
				
				DrawMain_VocInfo ( OneTrk );
				
				SetGtD_AnalogTrunk(OneTrk.VocDevID); //Set GTG
			}
		}
	}
	
	public void DispEventInfo(DeviceID_t dev, Object obj, int nEvtType){
		
		String strDisplay = GetString.GetString_EvtType(nEvtType);
		
		switch(nEvtType){
		case XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE: {
			
			DJEvtQueryDeviceData acsQueryData = (DJEvtQueryDeviceData)obj;
			
			strDisplay = strDisplay + "(" + acsQueryData.acsDevListHead.m_s32DeviceMain +
					"," + acsQueryData.acsDevListHead.m_s32ModuleID + "," +  
					acsQueryData.acsDevListHead.m_s32DeviceNum + ")";
			break;
		}
		case XMS_EVT_TYPE.XMS_EVT_UNIFAILURE: {

			DJEvtUnifailureData acsUnfailure = (DJEvtUnifailureData)obj;
			
			strDisplay = strDisplay + " " + GetString.GetString_ErrorCode(acsUnfailure.unifailureData.m_s32AcsEvtErrCode) + 
						  "(" + acsUnfailure.unifailureData.m_s32AcsEvtErrCode + ")" + " Dev=(" + 
						  GetString.GetString_DeviceMain(dev.m_s16DeviceMain) + "," +
						  dev.m_s8ModuleID + "," + dev.m_s16ChannelID +")";
			break;
		}
		
		case XMS_EVT_TYPE.XMS_EVT_RECVIODATA: {
			
			DJEvtRecvIOData recvData = (DJEvtRecvIOData)obj;
			
			strDisplay = strDisplay + " Dev=(" + GetString.GetString_DeviceMain(dev.m_s16DeviceMain) + 
			  "," + dev.m_s8ModuleID + "," + dev.m_s16ChannelID + ")";
			
			strDisplay += " RecvDataType:" + GetString.GetString_IODataType(recvData.acsIOData.m_u16IoType) + 
				" RecvDataLen:" + Integer.toString(recvData.acsIOData.m_u16IoDataLen);
			
			break;
		}
		default: {
			strDisplay = strDisplay + " Dev=(" + GetString.GetString_DeviceMain(dev.m_s16DeviceMain) + 
			  "," + dev.m_s8ModuleID + "," + dev.m_s16ChannelID + ")";
		}
		
		}
		
		NewJDialog.inst.ListBox_AddMsg(strDisplay);
		
		strDisplay = null;
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
	
	void RefreshMapTable(){
		int iModuleCount = 0, iVocCount = 0, iTrkCount = 0, iPcmCount = 0, iModSeqID = 0;
		
		for (int i = 0; i < MAX_DSP_MODULE_NUMBER_OF_XMS; i++){
			if (AllDeviceRes[i].lFlag != 0){
				AllDeviceRes[i].iSeqID = iModuleCount;
				MapTable_Module[iModuleCount] = (byte)i; //Rember all DSP moduleid
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
					
					if (AllDeviceRes[i].pTrunk[j].deviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_UNUSABLE){
						AllDeviceRes[i].pTrunk[j].iModSeqID = iModSeqID;
						iModSeqID++;
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
		g_iTotalTrunk = iTrkCount;
		g_iTotalVoice = iVocCount;
		g_iTotalPcm = iPcmCount;
	}
	
	public int CalDispRow ( int iSeqID )
	{
		int	iRet;

		if ( cfg_iDispChnl == 30 )
		{
			if ( (iSeqID % 16) == 0 )
				return -1;
		
			iRet = (iSeqID / 32) * 30 + (iSeqID % 32);
			iRet --;
			if ( (iSeqID % 32) > 16 )
				iRet --;
			return iRet;

		}

		if ( cfg_iDispChnl == 31 )
		{
			if ( (iSeqID % 32) == 0 )
				return -1;

			iRet = (iSeqID / 32) * 31 + (iSeqID % 32);
			iRet --;
			return iRet;
		}

		return iSeqID;
	}
	
	public void ReDrawAll(){
		
		NewJDialog.inst.AddRowToCount(g_iTotalModule);
		NewJDialog.inst.AddRowToMain(g_iTotalTrunk);
		NewJDialog.inst.AddRowToPcm(g_iTotalPcm);
		
		for (int i = 0; i < g_iTotalTrunk; i++){
			int iDispRow = CalDispRow(i);
			if (iDispRow < 0){
				continue;
			}
			
			NewJDialog.inst.DrawMain(iDispRow, 1, Integer.toString(MapTable_Trunk[i].m_s8ModuleID) + 
					", " + Integer.toString(MapTable_Trunk[i].m_s16ChannelID));
			
			TRUNK_STRUCT OneTrk = GetTrunkStructByDevice(MapTable_Trunk[i].m_s8ModuleID, MapTable_Trunk[i].m_s16ChannelID);
			NewJDialog.inst.DrawMain(iDispRow, 2, GetString.GetString_DeviceSub(OneTrk.deviceID.m_s16DeviceSub));
			
			DrawMain_LineState ( OneTrk );
			DrawMain_State ( OneTrk );
			DrawMain_CallInfo ( OneTrk );
			DrawMain_DTMF ( OneTrk );
		}
		
		for (int i = 0; i < g_iTotalPcm; i++){
			DrawPcm_TypeAndAlarm(GetPcmStructByDevice(MapTable_Pcm[i].m_s8ModuleID, MapTable_Pcm[i].m_s16ChannelID));
		}
		
		for (int i = 0; i < g_iTotalModule; i++){
			NewJDialog.inst.DrawCount(i+1, 1, Integer.toString(MapTable_Module[i]));
			DrawCount_Pcm(MapTable_Module[i]);
			DrawCount_Trunk(MapTable_Module[i]);
			DrawCount_Voc(MapTable_Module[i]);
			DrawCount_ErrFlag(MapTable_Module[i]);
			DrawCount_RemoveState(MapTable_Module[i]);
		}
	}
	
	public void DrawCount_Pcm(byte s8ModuleID){
		NewJDialog.inst.DrawCount(0, 2, Integer.toString(g_iTotalPcm)+"/ " + Integer.toString(g_iTotalPcmOpened));
		
		NewJDialog.inst.DrawCount(AllDeviceRes[s8ModuleID].iSeqID + 1, 2, Integer.toString((int)AllDeviceRes[s8ModuleID].lPcmNum) + 
				"/ " + Integer.toString((int)AllDeviceRes[s8ModuleID].lPcmOpened));
	}
	
	public void DrawCount_Trunk(byte s8ModuleID){
		NewJDialog.inst.DrawCount(0, 3, Integer.toString(g_iTotalTrunk)+"/ " + Integer.toString(g_iTotalTrunkOpened));
		
		NewJDialog.inst.DrawCount(AllDeviceRes[s8ModuleID].iSeqID + 1, 3, Integer.toString((int)AllDeviceRes[s8ModuleID].lTrunkNum) + 
				"/ " + Integer.toString((int)AllDeviceRes[s8ModuleID].lTrunkOpened));
	}
	
	public void DrawCount_Voc(byte s8ModuleID){
		NewJDialog.inst.DrawCount(0, 4, Integer.toString(g_iTotalVoice)+"/ " + Integer.toString(g_iTotalVoiceOpened));
		NewJDialog.inst.DrawCount(0, 5, Integer.toString(g_iTotalVoiceFree));
		
		NewJDialog.inst.DrawCount(AllDeviceRes[s8ModuleID].iSeqID+1, 4, Integer.toString((int)AllDeviceRes[s8ModuleID].lVocNum) + 
				"/ " + Integer.toString((int)AllDeviceRes[s8ModuleID].lVocOpened));
		NewJDialog.inst.DrawCount(AllDeviceRes[s8ModuleID].iSeqID+1, 5, Integer.toString(AllDeviceRes[s8ModuleID].lVocFreeNum));
	}
	
	public void	DrawCount_ErrFlag(byte s8ModuleID){
		if(AllDeviceRes[s8ModuleID].bErrFlag == true){
			NewJDialog.inst.DrawCount(AllDeviceRes[s8ModuleID].iSeqID + 1, 6, "T");
		}
		else{
			NewJDialog.inst.DrawCount(AllDeviceRes[s8ModuleID].iSeqID + 1, 6, "");
		}
	}

	public void	DrawCount_RemoveState(byte s8ModuleID)
	{
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
		
		NewJDialog.inst.DrawCount(AllDeviceRes[s8ModuleID].iSeqID+1, 7, str);
	}
	
	public void DrawPcm_TypeAndAlarm(PCM_STRUCT OnePcm){
		int	 AlarmVal;

		AlarmVal = OnePcm.s32AlarmVal;

		// E1 Type
		NewJDialog.inst.DrawPcm(OnePcm.iSeqID, 1, GetString.GetString_PcmType(OnePcm.u8E1Type)); 

		// Alarm
		NewJDialog.inst.DrawPcm(OnePcm.iSeqID, 2, "0x" + Integer.toHexString(AlarmVal)); 

		if ( (AlarmVal & XMS_E1PORT_MASK_STATE.XMS_E1PORT_MASK_LOST_SIGNAL) != 0 )
			NewJDialog.inst.DrawPcm(OnePcm.iSeqID, 3, " X"); 
		else
			NewJDialog.inst.DrawPcm(OnePcm.iSeqID, 3, "O" ); 

		if ( (AlarmVal & XMS_E1PORT_MASK_STATE.XMS_E1PORT_MASK_FAS_ALARM) !=0 )
			NewJDialog.inst.DrawPcm(OnePcm.iSeqID, 4, " X"); 
		else
			NewJDialog.inst.DrawPcm(OnePcm.iSeqID, 4, "O"); 

		if ( (AlarmVal & XMS_E1PORT_MASK_STATE.XMS_E1PORT_MASK_REMOTE_ALARM) != 0 )
			NewJDialog.inst.DrawPcm(OnePcm.iSeqID, 5, " X"); 
		else
			NewJDialog.inst.DrawPcm(OnePcm.iSeqID, 5, "O"); 
	}
	
	public void DrawMain_LineState(TRUNK_STRUCT OneTrk){
		int	 iDispRow;

		iDispRow = CalDispRow(OneTrk.iSeqID); 
		if ( iDispRow < 0 )	return;

		NewJDialog.inst.DrawMain(iDispRow, 3, GetString.GetString_LineState(OneTrk.iLineState)); 
	}
	
	public void DrawMain_State(TRUNK_STRUCT OneTrk){
		int	 iDispRow;

		iDispRow = CalDispRow(OneTrk.iSeqID); 
		if ( iDispRow < 0 )	return;
		
		NewJDialog.inst.DrawMain(iDispRow, 4, GetString.GetString_State(OneTrk.State)); 
	}

	public void DrawMain_CallInfo(TRUNK_STRUCT OneTrk){
		int	 iDispRow;

		iDispRow = CalDispRow(OneTrk.iSeqID); 
		if ( iDispRow < 0 )	return;
		
		String strCallee = new String(OneTrk.CalleeCode);
		NewJDialog.inst.DrawMain(iDispRow, 5, strCallee.substring(0, Global.GetByteArrLen(OneTrk.CalleeCode)));
		
		String strCaller = new String(OneTrk.CallerCode);
		NewJDialog.inst.DrawMain(iDispRow, 6, strCaller.substring(0, Global.GetByteArrLen(OneTrk.CallerCode)));
	}
	
	public void DrawMain_DTMF(TRUNK_STRUCT OneTrk){
		int	 iDispRow;

		iDispRow = CalDispRow(OneTrk.iSeqID); 
		if ( iDispRow < 0 )	return;
		
		String strDtmf = new String(OneTrk.DtmfBuf);
		
		NewJDialog.inst.DrawMain(iDispRow, 7, strDtmf.substring(0, OneTrk.DtmfCount));
	}
	
	public void	My_BuildIndex (DeviceID_t VocDevID){
		int			r;
		PlayProperty_t  playProperty = new PlayProperty_t();
		PrivateData_t privateData = new PrivateData_t();
		
		privateData.m_u32DataSize = 0;
		r = NewJDialog.g_DJApi.XMS_ctsInitPlayIndex ( g_acsHandle, VocDevID, privateData );
		if (r < 0)
		{
			NewJDialog.inst.ListBox_AddMsg("XMS_ctsInitPlayIndex() FAIL. ret = " + Integer.toString(r));
			return ;
		}

		for (int i = 0; i < 17; i++) {
			String FileName= null;
			if ( i == 16 ){
				playProperty.m_u16PlayType = XMS_BUILD_INDEX_TYPE.XMS_BUILD_INDEX_FILE;
				FileName = cfg_VocPath + "\\bank.008";
			} else {
				playProperty.m_u16PlayType = XMS_BUILD_INDEX_TYPE.XMS_BUILD_INDEX_RAM;
				FileName = "\\D";
				FileName = cfg_VocPath + FileName;
				FileName += Integer.toString(i);
			}

			CharsToByte(playProperty.m_s8PlayContent, FileName.toCharArray(), FileName.length());
		
			r = NewJDialog.g_DJApi.XMS_ctsBuildPlayIndex(g_acsHandle, VocDevID, playProperty, privateData);
			if ( r < 0 ){
				NewJDialog.inst.ListBox_AddMsg("XMS_ctsBuildPlayIndex() FAIL. ret = " + Integer.toString(r));
				return ;
			}
		}
	}
	
	public void CloseDeviceOK(DeviceID_t dev){
		
		AllDeviceRes[dev.m_s8ModuleID].bErrFlag = true;
		DrawCount_ErrFlag (dev.m_s8ModuleID);

		if(dev.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD){
			AllDeviceRes[dev.m_s8ModuleID].bOpenFlag = false;
		}

		if(dev.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH){
			TRUNK_STRUCT OneTrunk = GetTrunkStructByDevice(dev.m_s8ModuleID, dev.m_s16ChannelID);

			Change_State(OneTrunk, TRUNK_STATE.TRK_WAITOPEN);

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
	
	public void Remove_OneDsp(){
		int nSelectedRow = NewJDialog.inst.GetSelectedRow();
		if (nSelectedRow <= 0){
			JOptionPane.showConfirmDialog( null , "Please select a valid DSP module in the upper list!" , "Warning", JOptionPane.YES_NO_OPTION ) ;
			return ;
		} else {
			byte s8DspModID = MapTable_Module[nSelectedRow-1];		// because the first Row is Total, so minus 1
			AllDeviceRes[s8DspModID].RemoveState = REMOVE_STATE.DSP_REMOVE_STATE_START;
			DrawCount_RemoveState ( s8DspModID );

			// handle device : INTERFACE_CH
			for ( int i = 0; i < AllDeviceRes[s8DspModID].lTrunkNum; i ++ )
			{
				if ( AllDeviceRes[s8DspModID].pTrunk[i].State == TRUNK_STATE.TRK_FREE )
					Change_State ( AllDeviceRes[s8DspModID].pTrunk[i], TRUNK_STATE.TRK_WAIT_REMOVE );
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
		for (int i = 0; i < g_iTotalModule; i ++)
		{
			OpenAllDevice_Dsp ( MapTable_Module[i] );
			
			DrawCount_ErrFlag (MapTable_Module[i]);
			DrawCount_RemoveState (MapTable_Module[i]);
		}
	}
}

class TYPE_CHANNEL_MAP_TABLE
{
    public byte      m_s8ModuleID	= -1 ;    /*device module type*/
    public short     m_s16ChannelID = -1 ;    /*device chan id*/
}

class VOICE_STRUCT{
	// ----------------
	public DeviceID_t	deviceID  = new DeviceID_t();
	public int			iSeqID	  = 0;

	public DeviceID_t	UsedDevID = new DeviceID_t();

	// ----------------
	public int			State 	  = -1;
}

class PCM_STRUCT{
	// ----------------
	public DeviceID_t	deviceID 	= new DeviceID_t ();
	public int			iSeqID	 	= 0;
	public boolean		bOpenFlag	= false;		// flag of OpenDevice OK

	//
	public byte			u8E1Type	= 0;
	public int			s32AlarmVal	= 0;
}

class TRUNK_STRUCT{
	// ----------------
	public DeviceID_t	deviceID 	= new DeviceID_t();
	public int			iSeqID	 	= 0;
	public int			iModSeqID 	= 0;
	public int			iLineState	= 0;

	public DeviceID_t	VocDevID	= new DeviceID_t();
	public byte			u8PlayTag 	= 0;

	// -----------------
	public int			State		= -1;

	public int			DtmfCount	= 0;
	public byte			DtmfBuf[]	= new byte[32];

	public byte 		CallerCode[]= new byte[32];
	public byte 		CalleeCode[]= new byte[32];
	
	public void InitDtmfBuf(){
		DtmfCount = 0;
		for (int i = 0; i < 32; i++){
			DtmfBuf[i] = 0;
		}
	}
	
	public void InitCallCode(){
		for (int i = 0; i < 32; i ++){
			CallerCode[i] = 0;
			CalleeCode[i] = 0;
		}
	}

} 

class TYPE_XMS_DSP_DEVICE_RES_DEMO{
	public static final int 		MAX_VOC_RES_NUM_EACH_DSP 	= 128; 
	public static final int 		MAX_PCM_RES_NUM_EACH_DSP 	= 4;   
	public static final int 		MAX_TRUNK_RES_NUM_EACH_DSP 	= 128; 
		
    public long lFlag			 	= 0;							

    public DeviceID_t 	deviceID 	= new DeviceID_t();				
    public int 			iSeqID		= 0;			    			
    public boolean  	bOpenFlag	= false;		    			
    public boolean 		bErrFlag	= false;		    			
    public int			RemoveState = -1;							

    public int lVocNum				= 0;							
    public int lVocOpened			= 0;							
    public int lVocFreeNum			= 0;							
    public VOICE_STRUCT[] pVoice 	= new VOICE_STRUCT[MAX_VOC_RES_NUM_EACH_DSP];	

    public long lPcmNum				= 0;							
    public long lPcmOpened			= 0;							
    public PCM_STRUCT[] pPcm		= new PCM_STRUCT[MAX_PCM_RES_NUM_EACH_DSP];		

    public long lTrunkNum			= 0;							
    public long lTrunkOpened		= 0;							
    public TRUNK_STRUCT[] pTrunk	= new TRUNK_STRUCT[MAX_TRUNK_RES_NUM_EACH_DSP];
}

class REMOVE_STATE{
	public static final int DSP_REMOVE_STATE_NONE	=	0;		// Do not remove the DSP hardware
	public static final int DSP_REMOVE_STATE_START	=	1;		// Ready to remove DSP hardware, wait all the Devices' Resource release
	public static final int DSP_REMOVE_STATE_READY	=	2;		// All the Devices' Resource have released, start delete DSP hardware
}

class VOICE_STATE {
	public static final int VOC_WAITOPEN 			= 	0;
	public static final int VOC_FREE 				= 	1;
	public static final int VOC_USED 				= 	2;
	public static final int VOC_WAIT_REMOVE 		= 	3;
}

class TRUNK_STATE {
	public static final int TRK_WAITOPEN 			= 	0;
	public static final int TRK_FREE 				= 	1;			
	public static final int TRK_WELCOME 			= 	2;
	public static final int TRK_ACCOUNT 			= 	3;
	public static final int TRK_PASSWORD 			= 	4;
	public static final int TRK_SELECT 				= 	5;
	public static final int TRK_PLAYRESULT 			= 	6;
	public static final int TRK_RECORDFILE 			= 	7;
	public static final int TRK_PLAYRECORD 			= 	8;
	public static final int TRK_HANGON 				= 	9;

	// new add for XMS
	public static final int TRK_WAIT_ANSWERCALL		= 	10;
	public static final int TRK_WAIT_LINKOK			=	11;

	public static final int TRK_WAIT_REMOVE			= 	12;
}

