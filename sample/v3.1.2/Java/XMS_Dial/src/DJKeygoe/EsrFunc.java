package DJKeygoe;

interface CBInterface{
	public abstract void UserProcess(Acs_Evt_t acsEvtData, Object obj);
	}

public class EsrFunc implements CBInterface{
	
	public void UserProcess(Acs_Evt_t acsEvtData, Object obj){
		
		int nEvtType = acsEvtData.m_s32EventType;
		
		switch(nEvtType){
			case XMS_EVT_TYPE.XMS_EVT_OPEN_STREAM: {
				
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData, null, nEvtType);
				
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE: {
			
				DJEvtQueryDeviceData queryDeviceData = (DJEvtQueryDeviceData)obj;
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData, queryDeviceData, nEvtType);
				
				if (NewJDialog.GlobalVar.cfg_iPartWork == 0 || 
					acsEvtData.m_DeviceID.m_s8ModuleID == NewJDialog.GlobalVar.cfg_iPartWorkModuleID){
					
					switch(queryDeviceData.acsDevListHead.m_s32DeviceMain){
							case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD:{
								NewJDialog.GlobalVar.AddDeviceRes_Board(queryDeviceData);
								break;
							}
							
							case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH:{
								NewJDialog.GlobalVar.AddDeviceRes_Trunk(queryDeviceData);
								break;
							}
							
							case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE:{
								NewJDialog.GlobalVar.AddDeviceRes_Voice(queryDeviceData);
								break;
							}
							
							case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT:{
								NewJDialog.GlobalVar.AddDeviceRes_Pcm(queryDeviceData);
								break;
							}
						
						default:{
							break;
							}
						}
					}
				queryDeviceData = null;
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_END: {

				NewJDialog.GlobalVar.DispEventInfo(acsEvtData, null, nEvtType);
				
				if (NewJDialog.GlobalVar.cfg_iPartWork == 0 || 
						acsEvtData.m_DeviceID.m_s8ModuleID == NewJDialog.GlobalVar.cfg_iPartWorkModuleID){
					NewJDialog.GlobalVar.AllDeviceRes[acsEvtData.m_DeviceID.m_s8ModuleID].lFlag = 1;
					NewJDialog.GlobalVar.OpenAllDevice_Dsp(acsEvtData.m_DeviceID.m_s8ModuleID);
					
					NewJDialog.GlobalVar.RefreshMapTable ( );
					NewJDialog.GlobalVar.ReDrawAll ();
					
					NewJDialog.GlobalVar.DrawCount_ErrFlag (acsEvtData.m_DeviceID.m_s8ModuleID);
					NewJDialog.GlobalVar.DrawCount_RemoveState (acsEvtData.m_DeviceID.m_s8ModuleID);
				}
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_QUERY_REMOVE_ONE_DSP_END: {

				NewJDialog.GlobalVar.DispEventInfo(acsEvtData, null, nEvtType);
				
				NewJDialog.GlobalVar.AllDeviceRes[acsEvtData.m_DeviceID.m_s8ModuleID].lFlag = 0;		// Remove DSP Over
				
				NewJDialog.GlobalVar.RefreshMapTable ( );
				NewJDialog.GlobalVar.ReDrawAll ();
				
				NewJDialog.GlobalVar.DrawCount_ErrFlag (acsEvtData.m_DeviceID.m_s8ModuleID);
				NewJDialog.GlobalVar.DrawCount_RemoveState (acsEvtData.m_DeviceID.m_s8ModuleID);
				
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_OPEN_DEVICE:{ //Open Device OK!
				
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData, null, nEvtType);
				
				byte bDspModuleID = acsEvtData.m_DeviceID.m_s8ModuleID;
				short sChannelID = acsEvtData.m_DeviceID.m_s16ChannelID;
				
				switch(acsEvtData.m_DeviceID.m_s16DeviceMain){
				
				case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD: {
					NewJDialog.GlobalVar.AllDeviceRes[bDspModuleID].deviceID.m_CallID.m_s32FlowChannel = 
						acsEvtData.m_DeviceID.m_CallID.m_s32FlowChannel;
					
					NewJDialog.GlobalVar.AllDeviceRes[bDspModuleID].deviceID.m_CallID.m_s32FlowType = 
						acsEvtData.m_DeviceID.m_CallID.m_s32FlowType;
					
					NewJDialog.GlobalVar.SetGTD_ToneParam(NewJDialog.GlobalVar.AllDeviceRes[bDspModuleID].deviceID);
					break;
				}
				
				case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH: {
					TRUNK_STRUCT OneTrk = NewJDialog.GlobalVar.GetTrunkStructByDevice(bDspModuleID, sChannelID);
					
					OneTrk.deviceID.m_CallID.m_s32FlowChannel = acsEvtData.m_DeviceID.m_CallID.m_s32FlowChannel;
					OneTrk.deviceID.m_CallID.m_s32FlowType = acsEvtData.m_DeviceID.m_CallID.m_s32FlowType;
					
					if ( OneTrk.deviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER ){
						NewJDialog.GlobalVar.InitUserChannel ( OneTrk );

						NewJDialog.g_DJApi.XMS_ctsResetDevice ( NewJDialog.GlobalVar.g_acsHandle, OneTrk.deviceID, null );
						NewJDialog.g_DJApi.XMS_ctsGetDevState ( NewJDialog.GlobalVar.g_acsHandle, OneTrk.deviceID, null );

						NewJDialog.GlobalVar.Change_State ( OneTrk, TRUNK_STATE.TRK_NOTHANDLE );		// This is Analog_User, do not handle in TrunkWork()

						// modify the count
						NewJDialog.GlobalVar.g_iTotalUserOpened ++;
						NewJDialog.GlobalVar.DrawCount_User (OneTrk.deviceID.m_s8ModuleID);

					} else {
						NewJDialog.GlobalVar.InitTrunkChannel(OneTrk);
						
						PrivateData_t privateData = new PrivateData_t();
						
						privateData.m_u32DataSize = 0;
						NewJDialog.g_DJApi.XMS_ctsResetDevice(NewJDialog.GlobalVar.g_acsHandle, OneTrk.deviceID, privateData);
						NewJDialog.g_DJApi.XMS_ctsGetDevState(NewJDialog.GlobalVar.g_acsHandle, OneTrk.deviceID, privateData);
					}
					// modify the count
					NewJDialog.GlobalVar.g_iTotalTrunkOpened ++;
					NewJDialog.GlobalVar.AllDeviceRes[OneTrk.deviceID.m_s8ModuleID].lTrunkOpened ++;
					
					NewJDialog.GlobalVar.DrawCount_Trunk ( OneTrk.deviceID.m_s8ModuleID );
					
					
					if (OneTrk.deviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH 
							&& OneTrk.deviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK){
						
						short u16ParamType = XMS_ANALOGTRUNK_PARAM_TYPE.ANALOGTRUNK_PARAM_UNIPARAM;
						
						NewJDialog.GlobalVar.g_AnalogTrk.m_u16CallInRingCount = 1; //����3��
						NewJDialog.GlobalVar.g_AnalogTrk.m_u16CallInRingTimeOut = 6000;
						
						int nRet = NewJDialog.g_DJApi.XMS_ctsSetParam(NewJDialog.GlobalVar.g_acsHandle, OneTrk.deviceID, u16ParamType, (short)0, NewJDialog.GlobalVar.g_AnalogTrk);
						NewJDialog.Dialog.ListBox_AddMsg("Set AnalogTrunk  ret = " + Integer.toString(nRet));
						// Search Free Voice for get CallerID(FSK)
						// if you needn't CallerID, ignore next line	
					}else if (OneTrk.deviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH
							&& OneTrk.deviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER){
						short u16ParamType = XMS_ANALOGUSER_PARAM_TYPE.ANALOGUSER_PARAM_UNIPARAM;
						
						NewJDialog.GlobalVar.g_AnalogUser.m_u8CallerIdOption  = 1; 
						NewJDialog.GlobalVar.g_AnalogUser.m_u8RingCadenceType = 0; 
						NewJDialog.GlobalVar.g_AnalogUser.m_u8CallOutRingTimeOut = 30 ;
						
						int nRet = NewJDialog.g_DJApi.XMS_ctsSetParam(NewJDialog.GlobalVar.g_acsHandle, OneTrk.deviceID, u16ParamType, (short)0, NewJDialog.GlobalVar.g_AnalogUser);
						NewJDialog.Dialog.ListBox_AddMsg("Set AnalogTrunk  ret = " + Integer.toString(nRet));
					}
					
					break;
				}
				
				case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE: {
					VOICE_STRUCT OneVoc = NewJDialog.GlobalVar.GetVoiceStructByDevice(bDspModuleID, sChannelID);
					OneVoc.deviceID.m_CallID.m_s32FlowChannel = acsEvtData.m_DeviceID.m_CallID.m_s32FlowChannel;
					
					OneVoc.deviceID.m_CallID.m_s32FlowType = acsEvtData.m_DeviceID.m_CallID.m_s32FlowType;
					
					NewJDialog.GlobalVar.Change_Voc_State (OneVoc, VOICE_STATE.VOC_FREE);
					
					NewJDialog.GlobalVar.g_iTotalVoiceFree++;
					NewJDialog.GlobalVar.g_iTotalVoiceOpened++;
					NewJDialog.GlobalVar.AllDeviceRes[bDspModuleID].lVocFreeNum++;
					NewJDialog.GlobalVar.AllDeviceRes[bDspModuleID].lVocOpened++;
					
					NewJDialog.GlobalVar.DrawCount_Voc(bDspModuleID);
					
					OneVoc = null;
					break;
				}
				
				case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT: {
					PCM_STRUCT OnePcm = NewJDialog.GlobalVar.GetPcmStructByDevice(bDspModuleID, sChannelID);
					
					OnePcm.deviceID.m_CallID.m_s32FlowChannel = acsEvtData.m_DeviceID.m_CallID.m_s32FlowChannel;
					OnePcm.deviceID.m_CallID.m_s32FlowType = acsEvtData.m_DeviceID.m_CallID.m_s32FlowType;
					
					PrivateData_t privateData = new PrivateData_t();
					
					privateData.m_u32DataSize = 0;
					NewJDialog.g_DJApi.XMS_ctsGetDevState(NewJDialog.GlobalVar.g_acsHandle, OnePcm.deviceID, privateData);
					
					NewJDialog.GlobalVar.DrawPcm_TypeAndAlarm (OnePcm);
					
					NewJDialog.GlobalVar.g_iTotalPcmOpened ++;
					NewJDialog.GlobalVar.AllDeviceRes[bDspModuleID].lPcmOpened++;
					
					NewJDialog.GlobalVar.DrawCount_Pcm  ( OnePcm.deviceID.m_s8ModuleID );
					break;
				}
				
				}
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_RESET_DEVICE:{
				//DJEvtResetDeviceData resetStateData = (DJEvtResetDeviceData)obj;
				
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData, null, nEvtType);
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_DEVICESTATE: {
				DJEvtDeviceStateData deviceStateData = (DJEvtDeviceStateData)obj;
				
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData, null, nEvtType);
				
				switch(acsEvtData.m_DeviceID.m_s16DeviceMain){
				
				case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT: {
					PCM_STRUCT OnePcm = NewJDialog.GlobalVar.GetPcmStructByDevice(acsEvtData.m_DeviceID.m_s8ModuleID,
							acsEvtData.m_DeviceID.m_s16ChannelID);
					
					OnePcm.u8E1Type = (byte)((deviceStateData.acsGenerProcData.m_s32DeviceState >> 16) & 0xFF);
					OnePcm.s32AlarmVal = (deviceStateData.acsGenerProcData.m_s32DeviceState) & 0xFFFF;
					
					NewJDialog.GlobalVar.DrawPcm_TypeAndAlarm(OnePcm);
					break;
				}
				case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH: {
					TRUNK_STRUCT OneTrk = NewJDialog.GlobalVar.GetTrunkStructByDevice(acsEvtData.m_DeviceID.m_s8ModuleID,
							acsEvtData.m_DeviceID.m_s16ChannelID);
					
					OneTrk.iLineState = deviceStateData.acsGenerProcData.m_s32DeviceState;
					
					NewJDialog.GlobalVar.DrawMain_LineState(OneTrk);
					
					if ( acsEvtData.m_DeviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER ){
						byte s8DspID = acsEvtData.m_DeviceID.m_s8ModuleID;
						short s16ChannelID = acsEvtData.m_DeviceID.m_s16ChannelID;
						TRUNK_STRUCT OneUser = NewJDialog.GlobalVar.GetTrunkStructByDevice(s8DspID, s16ChannelID);
						NewJDialog.GlobalVar.DrawUser_LineState( OneUser );
					}
					break;
				}
				}
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_UNIFAILURE: {
				
				DJEvtUnifailureData unifailureData = (DJEvtUnifailureData)obj;
				
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData, unifailureData, nEvtType);
				
				unifailureData = null;
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_CLOSE_DEVICE: {
				
				NewJDialog.GlobalVar.CloseDeviceOK(acsEvtData);
				break;
			}
			
			default:{

				NewJDialog.GlobalVar.DispEventInfo(acsEvtData, null, nEvtType);
				
				if (acsEvtData.m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH){
				
					NewJDialog.GlobalVar.ChannelWork(acsEvtData.m_DeviceID, acsEvtData, obj);
				}
				else if (acsEvtData.m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE){
					DeviceID_t dev = NewJDialog.GlobalVar.GetVoiceStructByDevice(acsEvtData.m_DeviceID.m_s8ModuleID, 
							acsEvtData.m_DeviceID.m_s16ChannelID).UsedDevID;
					
					if (dev != null && dev.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH){
						NewJDialog.GlobalVar.ChannelWork(dev, acsEvtData, obj);
						
					}
					
					dev = null;
				}
				break;
			}
			
		}
	}
}