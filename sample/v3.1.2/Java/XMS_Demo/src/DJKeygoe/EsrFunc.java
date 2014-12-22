package DJKeygoe;

interface CBInterface{
	public abstract void UserProcess(Acs_Evt_t acsEvtData, Object obj);
	}

public class EsrFunc implements CBInterface{ 
	
	public void UserProcess(Acs_Evt_t acsEvtData, Object obj){
		
		int nEvtType = acsEvtData.m_s32EventType;
		DeviceID_t device = acsEvtData.m_DeviceID;
		
		switch(nEvtType){
			case XMS_EVT_TYPE.XMS_EVT_OPEN_STREAM: {
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData.m_DeviceID, obj, nEvtType);
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_START: {
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData.m_DeviceID, obj, nEvtType);
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE: {
				
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData.m_DeviceID, obj, nEvtType);
				
				DJEvtQueryDeviceData acsQueryDevice = (DJEvtQueryDeviceData)obj;
				
				if (NewJDialog.GlobalVar.cfg_iPartWork == 0 || 
						device.m_s8ModuleID == NewJDialog.GlobalVar.cfg_iPartWorkModuleID){
					
					switch(acsQueryDevice.acsDevListHead.m_s32DeviceMain){
							case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD:{
								NewJDialog.GlobalVar.AddDeviceRes_Board(acsQueryDevice);
								break;
							}
							
							case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH:{
								NewJDialog.GlobalVar.AddDeviceRes_Trunk(acsQueryDevice);
								break;
							}
							
							case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE:{
								NewJDialog.GlobalVar.AddDeviceRes_Voice(acsQueryDevice);
								break;
							}
							
							case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT:{
								NewJDialog.GlobalVar.AddDeviceRes_Pcm(acsQueryDevice);
								break;
							}
						
						default:{
							break;
							}
						}
					}
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_END: {
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData.m_DeviceID, obj, nEvtType);
				
				if (NewJDialog.GlobalVar.cfg_iPartWork == 0 || 
						device.m_s8ModuleID == NewJDialog.GlobalVar.cfg_iPartWorkModuleID){
					NewJDialog.GlobalVar.AllDeviceRes[device.m_s8ModuleID].lFlag = 1;
					NewJDialog.GlobalVar.OpenAllDevice_Dsp(device.m_s8ModuleID);
					
					NewJDialog.GlobalVar.RefreshMapTable ( );
					NewJDialog.GlobalVar.ReDrawAll ();
					
					NewJDialog.GlobalVar.DrawCount_ErrFlag (device.m_s8ModuleID);
					NewJDialog.GlobalVar.DrawCount_RemoveState (device.m_s8ModuleID);
				}
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_QUERY_REMOVE_ONE_DSP_END: {
				
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData.m_DeviceID, obj, nEvtType);
				
				NewJDialog.GlobalVar.AllDeviceRes[device.m_s8ModuleID].lFlag = 0;		// Remove DSP Over
				
				NewJDialog.GlobalVar.RefreshMapTable ( );
				NewJDialog.GlobalVar.ReDrawAll ();
				
				NewJDialog.GlobalVar.DrawCount_ErrFlag (device.m_s8ModuleID);
				NewJDialog.GlobalVar.DrawCount_RemoveState (device.m_s8ModuleID);
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE_END: {
				
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData.m_DeviceID, obj, nEvtType);
				
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_OPEN_DEVICE:{ //Open Device OK!
				
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData.m_DeviceID, obj, nEvtType);
				
				byte bDspModuleID = device.m_s8ModuleID;
				short sChannelID = device.m_s16ChannelID;
				
				switch(device.m_s16DeviceMain){
				
				case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD: {
					NewJDialog.GlobalVar.AllDeviceRes[bDspModuleID].deviceID.m_CallID.m_s32FlowChannel = 
						device.m_CallID.m_s32FlowChannel;
					
					NewJDialog.GlobalVar.AllDeviceRes[bDspModuleID].deviceID.m_CallID.m_s32FlowType = 
						device.m_CallID.m_s32FlowType;
					
					NewJDialog.GlobalVar.SetGTD_ToneParam(NewJDialog.GlobalVar.AllDeviceRes[bDspModuleID].deviceID);
					break;
				}
				
				case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH: {
					TRUNK_STRUCT OneTrk = NewJDialog.GlobalVar.GetTrunkStructByDevice(bDspModuleID, sChannelID);
					
					OneTrk.deviceID.m_CallID.m_s32FlowChannel = device.m_CallID.m_s32FlowChannel;
					OneTrk.deviceID.m_CallID.m_s32FlowType = device.m_CallID.m_s32FlowType;
					NewJDialog.GlobalVar.InitTrunkChannel(OneTrk);
					
					PrivateData_t privateData = new PrivateData_t();
					
					privateData.m_u32DataSize = 0;
					NewJDialog.g_DJApi.XMS_ctsResetDevice(NewJDialog.GlobalVar.g_acsHandle, OneTrk.deviceID, privateData);
					NewJDialog.g_DJApi.XMS_ctsGetDevState(NewJDialog.GlobalVar.g_acsHandle, OneTrk.deviceID, privateData);
					
					// modify the count
					NewJDialog.GlobalVar.g_iTotalTrunkOpened ++;
					NewJDialog.GlobalVar.AllDeviceRes[OneTrk.deviceID.m_s8ModuleID].lTrunkOpened ++;
					
					NewJDialog.GlobalVar.DrawCount_Trunk ( OneTrk.deviceID.m_s8ModuleID );
					
					if (OneTrk.deviceID.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH 
							&& OneTrk.deviceID.m_s16DeviceSub == XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK){
						
						short u16ParamType = XMS_ANALOGTRUNK_PARAM_TYPE.ANALOGTRUNK_PARAM_UNIPARAM;
						
						NewJDialog.GlobalVar.g_AnalogTrk.m_u16CallInRingCount = 3; //����3��
						NewJDialog.GlobalVar.g_AnalogTrk.m_u16CallInRingTimeOut = 6000;
						
						int nRet = NewJDialog.g_DJApi.XMS_ctsSetParam(NewJDialog.GlobalVar.g_acsHandle, OneTrk.deviceID, u16ParamType, (short)0, NewJDialog.GlobalVar.g_AnalogTrk);
						NewJDialog.inst.ListBox_AddMsg("Set AnalogTrunk  ret = " + Integer.toString(nRet));
						// Search Free Voice for get CallerID(FSK)
						// if you needn't CallerID, ignore next line
						NewJDialog.GlobalVar.PrepareForCallerID ( OneTrk ); //
					}
					
					break;
				}
				
				case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE: {
					VOICE_STRUCT OneVoc = NewJDialog.GlobalVar.GetVoiceStructByDevice(bDspModuleID, sChannelID);
					OneVoc.deviceID.m_CallID.m_s32FlowChannel = device.m_CallID.m_s32FlowChannel;
					
					OneVoc.deviceID.m_CallID.m_s32FlowType = device.m_CallID.m_s32FlowType;
					
					NewJDialog.GlobalVar.Change_Voc_State (OneVoc, VOICE_STATE.VOC_FREE);
					
					PrivateData_t privateData = new PrivateData_t();
					
					privateData.m_u32DataSize = 0;
					NewJDialog.g_DJApi.XMS_ctsResetDevice(NewJDialog.GlobalVar.g_acsHandle, OneVoc.deviceID, privateData);
					NewJDialog.g_DJApi.XMS_ctsGetDevState(NewJDialog.GlobalVar.g_acsHandle, OneVoc.deviceID, privateData);
					
					if (NewJDialog.GlobalVar.g_iTotalVoiceOpened == 0){
						NewJDialog.GlobalVar.My_BuildIndex (OneVoc.deviceID);
					}
					
					NewJDialog.GlobalVar.g_iTotalVoiceFree++;
					NewJDialog.GlobalVar.g_iTotalVoiceOpened++;
					NewJDialog.GlobalVar.AllDeviceRes[bDspModuleID].lVocFreeNum++;
					NewJDialog.GlobalVar.AllDeviceRes[bDspModuleID].lVocOpened++;
					
					NewJDialog.GlobalVar.DrawCount_Voc(bDspModuleID);
					break;
				}
				
				case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT: {
					PCM_STRUCT OnePcm = NewJDialog.GlobalVar.GetPcmStructByDevice(bDspModuleID, sChannelID);
					
					OnePcm.deviceID.m_CallID.m_s32FlowChannel = device.m_CallID.m_s32FlowChannel;
					OnePcm.deviceID.m_CallID.m_s32FlowType = device.m_CallID.m_s32FlowType;
					
					PrivateData_t privateData = new PrivateData_t();
					
					privateData.m_u32DataSize = 0;
					NewJDialog.g_DJApi.XMS_ctsResetDevice(NewJDialog.GlobalVar.g_acsHandle, OnePcm.deviceID, privateData);
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
			
			case XMS_EVT_TYPE.XMS_EVT_DEVICESTATE: {
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData.m_DeviceID, obj, nEvtType);
				
				DJEvtDeviceStateData acsDeviceState = (DJEvtDeviceStateData)obj;
				
				switch(device.m_s16DeviceMain){
				
				case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT: {
					PCM_STRUCT OnePcm = NewJDialog.GlobalVar.GetPcmStructByDevice(device.m_s8ModuleID,
							device.m_s16ChannelID);
					
					OnePcm.u8E1Type = (byte)((acsDeviceState.acsGenerProcData.m_s32DeviceState >> 16) & 0xFF);
					OnePcm.s32AlarmVal = (acsDeviceState.acsGenerProcData.m_s32DeviceState) & 0xFFFF;
					
					NewJDialog.GlobalVar.DrawPcm_TypeAndAlarm(OnePcm);
					break;
				}
				case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH: {
					TRUNK_STRUCT OneTrk = NewJDialog.GlobalVar.GetTrunkStructByDevice(device.m_s8ModuleID,
							device.m_s16ChannelID);
					
					OneTrk.iLineState = acsDeviceState.acsGenerProcData.m_s32DeviceState;
					
					NewJDialog.GlobalVar.DrawMain_LineState(OneTrk);
					break;
				}
				}
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_UNIFAILURE: {
				
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData.m_DeviceID, obj, nEvtType);
				
				break;
			}
			
			case XMS_EVT_TYPE.XMS_EVT_CLOSE_DEVICE: {
				
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData.m_DeviceID, obj, nEvtType);
				
				NewJDialog.GlobalVar.CloseDeviceOK(acsEvtData.m_DeviceID);
				break;
			}
			
			default:{
				
				NewJDialog.GlobalVar.DispEventInfo(acsEvtData.m_DeviceID, obj, nEvtType);
				
				if (device.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH){
				
					NewJDialog.GlobalVar.TrunkWork(device, acsEvtData, obj);
				}
				else if (device.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE){
					DeviceID_t dev = NewJDialog.GlobalVar.GetVoiceStructByDevice(device.m_s8ModuleID, 
							device.m_s16ChannelID).UsedDevID;
					
					if (dev != null && dev.m_s16DeviceMain == XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH){
						NewJDialog.GlobalVar.TrunkWork(dev, acsEvtData, obj);
					}
				}
				break;
			}
		}
	
	}
}