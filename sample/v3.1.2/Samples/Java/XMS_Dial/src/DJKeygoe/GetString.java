package DJKeygoe;

public class GetString {
	
	public static String GetString_EvtType(int nEvtType){
		switch(nEvtType){
		case XMS_EVT_TYPE.XMS_EVT_OPEN_STREAM: 					return "OPEN_STREAM";                     
		case XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE: 				return "QUERY_DEVICE";                   
		case XMS_EVT_TYPE.XMS_EVT_QUERY_DEVICE_END:             return "QUERY_DEVICE_END";   
		case XMS_EVT_TYPE.XMS_EVT_OPEN_DEVICE:                  return "OPEN_DEVICE";   
		case XMS_EVT_TYPE.XMS_EVT_CLOSE_DEVICE:                 return "CLOSE_DEVICE:";   					
		case XMS_EVT_TYPE.XMS_EVT_RESET_DEVICE:                 return "RESET_DEVICE";   
		case XMS_EVT_TYPE.XMS_EVT_DEVICESTATE:                  return "DEVICESTATE";   
		case XMS_EVT_TYPE.XMS_EVT_SETDEV_GROUP:                 return "SETDEV_GROUP";   
		case XMS_EVT_TYPE.XMS_EVT_SETPARAM:                     return "SETPARAM";   
		case XMS_EVT_TYPE.XMS_EVT_GETPARAM:                     return "GETPARAM";   
		case XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_START:          return "QUERY_ONE_DSP_START";   
		case XMS_EVT_TYPE.XMS_EVT_QUERY_ONE_DSP_END:            return "QUERY_ONE_DSP_END";   
		case XMS_EVT_TYPE.XMS_EVT_QUERY_REMOVE_ONE_DSP_START:   return "QUERY_REMOVE_ONE_DSP_START";   
		case XMS_EVT_TYPE.XMS_EVT_QUERY_REMOVE_ONE_DSP_END:     return "QUERY_REMOVE_ONE_DSP_END";   
		case XMS_EVT_TYPE.XMS_EVT_OPEN_STREAM_EXT:              return "OPEN_STREAM_EXT";   
		case XMS_EVT_TYPE.XMS_EVT_LICENSE_QUERY:                return "LICENSE_QUERY";   
		case XMS_EVT_TYPE.XMS_EVT_CLOSE_STREAM_EXT:             return "CLOSE_STREAM_EXT";   
		case XMS_EVT_TYPE.XMS_EVT_MASTER_STATE:                 return "MASTER_STATE";   
		case XMS_EVT_TYPE.XMS_EVT_SLAVE_WORK_STATE:				return "SLAVE_WORK_STATE";
		case XMS_EVT_TYPE.XMS_EVT_E1STATE:                      return "E1STATE";  
		case XMS_EVT_TYPE.XMS_EVT_CTBUS_CLK_REF_SRC_STATE:      return "CTBUS_CLK_REF_SRC_STATE";   
		case XMS_EVT_TYPE.XMS_EVT_USER_DEF:                     return "USER_DEF";   
		case XMS_EVT_TYPE.XMS_EVT_BAKSYS_STOP:                  return "BAKSYS_STOP";   
		case XMS_EVT_TYPE.XMS_EVT_ACS_TIMER:                    return "ACS_TIMER";  
		                                        
		case XMS_EVT_TYPE.XMS_EVT_CALLOUT:						return "CALLOUT";
		case XMS_EVT_TYPE.XMS_EVT_CALLIN:						return "CALLIN";
		case XMS_EVT_TYPE.XMS_EVT_ALERTCALL:		        	return "ALERTCALL";
		case XMS_EVT_TYPE.XMS_EVT_ANSWERCALL:		        	return "ANSWERCALL";
		case XMS_EVT_TYPE.XMS_EVT_LINKDEVICE:					return "LINKDEVICE";
		case XMS_EVT_TYPE.XMS_EVT_UNLINKDEVICE:					return "UNLINKDEVICE";
		case XMS_EVT_TYPE.XMS_EVT_CLEARCALL:					return "CLEARCALL";
		case XMS_EVT_TYPE.XMS_EVT_ANALOG_INTERFACE:             return "ANALOG_INTERFACE:";   
		case XMS_EVT_TYPE.XMS_EVT_CAS_MFC_START:				return "CAS_MFC_START";
		case XMS_EVT_TYPE.XMS_EVT_CAS_MFC_END:					return "CAS_MFC_END";
		case XMS_EVT_TYPE.XMS_EVT_SENDSIGMSG:					return "SENDSIGMSG";
		case XMS_EVT_TYPE.XMS_EVT_SIGMON:       				return "SIGMON";
		case XMS_EVT_TYPE.XMS_EVT_3G324M:      					return "3G324M";
		case XMS_EVT_TYPE.XMS_EVT_CTX_REG:                      return "CTX_REG";   
		case XMS_EVT_TYPE.XMS_EVT_CTX_LINK:                     return "CTX_LINK";  
		case XMS_EVT_TYPE.XMS_EVT_CTX_APPDATA:                  return "CTX_APPDATA";   
		case XMS_EVT_TYPE.XMS_EVT_DRS_CALL_NUMS:                return "DRS_CALL_NUMS";  
		                                        
		case XMS_EVT_TYPE.XMS_EVT_SS7RawFrame:					return "SS7RawFrame";
		case XMS_EVT_TYPE.XMS_EVT_SS7SendRawFrame:				return "SS7SendRawFrame";
		                                        	
		case XMS_EVT_TYPE.XMS_EVT_JOINTOCONF:					return "JOINTOCONF";
		case XMS_EVT_TYPE.XMS_EVT_LEAVEFROMCONF:				return "LEAVEFROMCONF";
		case XMS_EVT_TYPE.XMS_EVT_CLEARCONF:					return "CLEARCONF";
		                                        	
		case XMS_EVT_TYPE.XMS_EVT_SET_PAYLOAD:					return "SET_PAYLOAD";
		case XMS_EVT_TYPE.XMS_EVT_SET_RTPADDR:					return "SET_RTPADDR";
		case XMS_EVT_TYPE.XMS_EVT_SET_RTCPADDR:					return "SET_RTCPADDR";
		case XMS_EVT_TYPE.XMS_EVT_SET_RTPCODEC:					return "SET_RTPCODEC";
		case XMS_EVT_TYPE.XMS_EVT_SET_MEDIAINFO:				return "SET_MEDIAINFO";
		case XMS_EVT_TYPE.XMS_EVT_REFER_RESULT:					return "REFER_RESULT";
		case XMS_EVT_TYPE.XMS_EVT_REGIST:						return "REGIST";
		case XMS_EVT_TYPE.XMS_EVT_REGIST_RESP:					return "REGIST_RESP";
		                                        
		case XMS_EVT_TYPE.XMS_EVT_PLAY:			        		return "PLAY";
		case XMS_EVT_TYPE.XMS_EVT_INITINDEX:					return "INITINDEX";
		case XMS_EVT_TYPE.XMS_EVT_BUILDINDEX:					return "BUILDINDEX";
		case XMS_EVT_TYPE.XMS_EVT_CONTROLPLAY:					return "CONTROLPLAY";
		case XMS_EVT_TYPE.XMS_EVT_RECORD:						return "RECORD";
		case XMS_EVT_TYPE.XMS_EVT_CONTROLRECORD:				return "CONTROLRECORD";
		case XMS_EVT_TYPE.XMS_EVT_RECORDCSP:  					return "RECORDCSP";
		case XMS_EVT_TYPE.XMS_EVT_CONTROLRECORDCSP:    			return "CONTROLRECORDCSP";
		case XMS_EVT_TYPE.XMS_EVT_3GPP_PLAY:					return "3GPP_PLAY";
		case XMS_EVT_TYPE.XMS_EVT_3GPP_CONTROLPLAY:				return "3GPP_CONTROLPLAY";
		case XMS_EVT_TYPE.XMS_EVT_3GPP_RECORD:	    			return "3GPP_RECORD";
		case XMS_EVT_TYPE.XMS_EVT_3GPP_CONTROLRECORD:   		return "3GPP_CONTROLRECORD";
		case XMS_EVT_TYPE.XMS_EVT_PLAYCSPREQ: 					return "PLAYCSPREQ";
		case XMS_EVT_TYPE.XMS_EVT_3GPP_INIT_INDEX:              return "3GPP_INIT_INDEX";
		case XMS_EVT_TYPE.XMS_EVT_3GPP_BUILD_INDEX:             return "3GPP_BUILD_INDEX";  
		                                        
		case XMS_EVT_TYPE.XMS_EVT_3GVCONF_JOIN:					return "3GVCONF_JOIN";
		case XMS_EVT_TYPE.XMS_EVT_3GVCONF_LEAVE:				return "3GVCONF_LEAVE";
		case XMS_EVT_TYPE.XMS_EVT_3GVCONF_CLEAR:				return "3GVCONF_CLEAR";
		case XMS_EVT_TYPE.XMS_EVT_3GVCONF_GETLAYOUT:			return "3GVCONF_GETLAYOUT";
		case XMS_EVT_TYPE.XMS_EVT_3GVCONF_SETLAYOUT:			return "3GVCONF_SETLAYOUT";
		case XMS_EVT_TYPE.XMS_EVT_3GVCONF_GETVISIBLELIST:		return "3GVCONF_GETVISIBLELIST";
		case XMS_EVT_TYPE.XMS_EVT_3GVCONF_SETVISIBLELIST:		return "3GVCONF_SETVISIBLELIST";
		case XMS_EVT_TYPE.XMS_EVT_3GVCONF_STOP:					return "3GVCONF_STOP";
		                                        
		case XMS_EVT_TYPE.XMS_EVT_SENDFAX:			        	return "SENDFAX";
		case XMS_EVT_TYPE.XMS_EVT_RECVFAX:						return "RECVFAX";
		                                        
		case XMS_EVT_TYPE.XMS_EVT_SENDIODATA:					return "SENDIODATA";
		case XMS_EVT_TYPE.XMS_EVT_RECVIODATA:					return "RECVIODATA";
		                                        
		case XMS_EVT_TYPE.XMS_EVT_MODMONITOR:					return "MODMONITOR";
		case XMS_EVT_TYPE.XMS_EVT_DEV_TIMER:					return "DEV_TIMER";
		case XMS_EVT_TYPE.XMS_EVT_MODRELATE:					return "MODRELATE";
		case XMS_EVT_TYPE.XMS_EVT_VOIPMON: 						return "VOIPMON";
		                                        
		case XMS_EVT_TYPE.XMS_EVT_UNIFAILURE:					return "UNIFAILURE";
		}
		
		String strRet = "0x" + Integer.toHexString(nEvtType);
		return strRet;
	}
	
	public static String GetString_DeviceMain(int nDevMain){
		switch(nDevMain){
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_CONFIG:				return "CONFIG";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOICE:				return "VOC  ";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_FAX:					return "FAX  ";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DIGITAL_PORT:			return "DIGIT";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_INTERFACE_CH:			return "INTCH";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_DSS1_LINK:			return "DSS1 ";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_SS7_LINK:				return "SS7  ";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_BOARD:				return "BRD  ";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_CTBUS_TS:				return "CTBUS";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_RTP:					return "RTP ";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_MEDIAEX:				return "MEDIAEX ";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_CONFERENCE:			return "CONF ";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VIDEO:				return "VIDEO";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_CTX:					return "CTX ";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_RTPX:					return "RTPX";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VOIP:					return "VOIP ";
		case XMS_DEVMAIN_TYPE.XMS_DEVMAIN_VIDEOCONF:			return "VIDEOCONF";
		}
		
		String strRet = "0x" + Integer.toHexString(nDevMain);
		return strRet;
	}
	
	public static String GetString_DeviceSub(short nDevSub){
		switch(nDevSub){
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_BASE:                       return "Base";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK:               return "Trunk";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER:                return "User";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_HIZ:                 return "Hiz";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_EMPTY:               return "Empty";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_PCM:                     return "E1_PCM";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_CAS:                     return "E1_CAS";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_DSS1:                    return "E1_DSS1";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_TUP:                 return "SS7_TUP";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_ISUP:                return "SS7_ISUP";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_VOC2W:			      return "ANALOG_VOC2W";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_VOC4W:			      return "ANALOG_VOC4W";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_EM:			      return "ANALOG_EM";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_MAG:			      return "ANALOG_MAG";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_DCH:				      return "E1_DCH";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_BCH:				      return "E1_BCH";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_UNUSABLE:				      return "UNUSABLE";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_HIZ_CAS:				      return "HIZ_CAS";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_HIZ_PRI:				      return "HIZ_PRI";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_HIZ_SS7:					  return "HIZ_SS7";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_HIZ_PRI_LINK:			      return "HIZ_PRI_LINK";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_HIZ_SS7_64K_LINK:  		  return "HIZ_SS7_64K_LINK";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_HIZ_SS7_2M_LINK:   		  return "HIZ_SS7_2M_LINK";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_SS7_LINK:		              return "SS7_LINK";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_LINESIDE:		              return "LINESIDE";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_REC:	              return "ANALOG_REC";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_HIZ_HDLC_N64K_LINK:         return "HIZ_HDLC_N64K_LINK";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_SS7_2M_LINK:                return "SS7_2M_LINK";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_HIZ_HDLC:                   return "HIZ";
		case XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_DIGITAL_REC:	              return "DIGITAL_REC";
		}
		
		String strRet = "0x" + Integer.toHexString(nDevSub);
		return strRet;
	}
	
	public static String GetString_ErrorCode(int nErrorCode){
		switch(nErrorCode){
		//case XMS_ERROR_CODE_DEF.ACSPOSITIVE_ACK:                	 return "ACSPOSITIVE_ACK"; //Success

		case XMS_ERROR_CODE_DEF.ACSERR_LOADLIBERR:             	 	 return "LOADLIBERR";
		case XMS_ERROR_CODE_DEF.ACSERR_BADPARAMETER:              	 return "BADPARAMETER";
		case XMS_ERROR_CODE_DEF.ACSERR_NOSERVER:                  	 return "NOSERVER";
		case XMS_ERROR_CODE_DEF.ACSERR_MAXCONN_EXCEED:            	 return "MAXCONN_EXCEED";
		case XMS_ERROR_CODE_DEF.ACSERR_BADHDL:                    	 return "BADHDL";
		case XMS_ERROR_CODE_DEF.ACSERR_FAILSEND:                     return "FAILSEND";
		case XMS_ERROR_CODE_DEF.ACSERR_LINKBROKEN:               	 return "LINKBROKEN";
		case XMS_ERROR_CODE_DEF.ACSERR_NOMESSAGE:                	 return "NOMESSAGE";
		case XMS_ERROR_CODE_DEF.ACSERR_GETRESFAIL:                   return "GETRESFAIL";
		case XMS_ERROR_CODE_DEF.ACSERR_NOSUPPORTCMD:                 return "NOSUPPORTCMD";
		case XMS_ERROR_CODE_DEF.ACSERR_DEVICEERR:                    return "DEVICEERR";
		case XMS_ERROR_CODE_DEF.ACSERR_CTX_REGOVERRUN:     		     return "CTX_REGOVERRUN";
		case XMS_ERROR_CODE_DEF.ACSERR_CTX_REG_NAMEEXIS:             return "CTX_REG_NAMEEXIS";
		case XMS_ERROR_CODE_DEF.ACSERR_CTX_UNREG_NOREG:		     	 return "CTX_UNREG_NOREG";
		case XMS_ERROR_CODE_DEF.ACSERR_CTX_TRAN_NODEST:		     	 return "CTX_TRAN_NODEST";
		case XMS_ERROR_CODE_DEF.ACSERR_CTX_TRAN_NOSRC:		         return "CTX_TRAN_NOSRC";
		case XMS_ERROR_CODE_DEF.ACSERR_CTX_LINK_FAIL:                return "CTX_LINK_FAIL";
		case XMS_ERROR_CODE_DEF.ACSERR_CTX_APPDATA_NODEST:           return "CTX_APPDATA_NODEST";
		case XMS_ERROR_CODE_DEF.ACSERR_CTX_APPDATA_NOSRC:       	 return "CTX_APPDATA_NOSRC";
		case XMS_ERROR_CODE_DEF.ACSERR_NOTMASTER:                    return "NOTMASTER";
		case XMS_ERROR_CODE_DEF.ACSERR_PUTTEXTINPIC_OPENPICFAIL:     return "PUTTEXTINPIC_OPENPICFAIL";
		case XMS_ERROR_CODE_DEF.ACSERR_PUTTEXTINPIC_SAVEPICFAIL:     return "PUTTEXTINPIC_SAVEPICFAIL";
		}
		
		String strRet = "0x" + Integer.toHexString(nErrorCode);
		return strRet;
	}
	
	public static String GetString_LineState(int iLineState){
		switch(iLineState){
		case DEVICE_CALL_STATE.DEVICE_COMMON_STATE_START:   return "Start"; // 通用状态开始识别号: TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR
		case DEVICE_CALL_STATE.DCS_FREE:                    return "Free"; // 空闲状态(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
		case DEVICE_CALL_STATE.DCS_LOCAL_BLOCK:             return "LocalBlock"; // 本地阻塞(TUP,ISUP)
		case DEVICE_CALL_STATE.DCS_REMOTE_BLOCK:            return "RemoteBlock"; // 远端阻塞(TUP,ISUP)
		case DEVICE_CALL_STATE.DCS_BLOCK:                   return "Block"; // 本地和远端阻塞(ISUP)
		case DEVICE_CALL_STATE.DCS_UNAVAILABLE:             return "Unavailable"; // 不可用(TUP,ISUP,PRI)
		
		case DEVICE_CALL_STATE.DCS_CALLOUT:                 return "Callout"; // 开始呼出(TUP,ISUP,PRI,VOIP,ANA_TRK)
		case DEVICE_CALL_STATE.DCS_CALLIN:                  return "Callin"; // 呼叫进入(TUP,ISUP,PRI,VOIP,ANA_TRK)
		case DEVICE_CALL_STATE.DCS_ALERTING:                return "Alerting"; // 地址收齐对用户振铃等(TUP,ISUP)
		
		case DEVICE_CALL_STATE.DCS_CONNECT:                 return "Connect"; // 连通(不分主被叫方式)(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
		
		case DEVICE_CALL_STATE.DCS_DISCONNECT:              return "Disconnect"; // 收到拆线(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
		case DEVICE_CALL_STATE.DCS_WAIT_FREE:               return "WaitFree"; // 对拆线的响应(TUP,ISUP,PRI,VOIP)
		}
		
		String strRet = "0x" + Integer.toHexString(iLineState);
		return strRet;
	}
	
	public static String GetString_State(int iState){
		switch(iState){
		case TRUNK_STATE.TRK_WAITOPEN: 			return "WaitOpen";
		case TRUNK_STATE.TRK_FREE:				return "Free";			
		case TRUNK_STATE.TRK_NOTHANDLE: 		return "NotHandle";
		case TRUNK_STATE.TRK_CALLOUT: 			return "CallOut";
		case TRUNK_STATE.TRK_SIM_CALLOUT: 		return "SimCallOut";
		case TRUNK_STATE.TRK_SIM_LINK:			return "SimLinkOk";
		case TRUNK_STATE.TRK_SIM_ANALOG_OFFHOOK:return "OffHook";
		case TRUNK_STATE.TRK_SIM_ANALOG_DIALING:return "Dialing";
		case TRUNK_STATE.TRK_LINK: 				return "Link";
		case TRUNK_STATE.TRK_PLAYDTMF: 			return "PlayDTMF";

			// new add for XMS
		case TRUNK_STATE.TRK_HANGUP:			return "HangUp";
		case TRUNK_STATE.TRK_FAIL:				return "Fail";
		case TRUNK_STATE.TRK_WAIT_REMOVE:		return "DSP remove";
		}
		
		String strRet = "0x" + Integer.toHexString(iState);
		return strRet;
	}
	
	public static String GetString_PcmType(int iPcmType)
	{
		switch ( iPcmType )
		{
		case 0:											return "Disable";

		case XMS_E1_TYPE.XMS_E1_TYPE_Analog30:			return "T_Analog30";
		case XMS_E1_TYPE.XMS_E1_TYPE_PCM31:				return "T_PCM31";
		case XMS_E1_TYPE.XMS_E1_TYPE_PCM30:				return "T_PCM30";
		case XMS_E1_TYPE.XMS_E1_TYPE_CAS:				return "T_CAS";
		case XMS_E1_TYPE.XMS_E1_TYPE_PRI:				return "T_PRI";
		case XMS_E1_TYPE.XMS_E1_TYPE_SS7_TUP_0_Link:	return "T_TUP_0_LK";
		case XMS_E1_TYPE.XMS_E1_TYPE_SS7_TUP_1_Link:	return "T_TUP_1_LK";
		case XMS_E1_TYPE.XMS_E1_TYPE_SS7_TUP_2_Link:	return "T_TUP_2_L";
		case XMS_E1_TYPE.XMS_T1_TYPE_D4:				return "T_D4";
		case XMS_E1_TYPE.XMS_T1_TYPE_ESF:				return "T_ESF";
		case XMS_E1_TYPE.XMS_J1_TYPE_D4:				return "J_D4";
		case XMS_E1_TYPE.XMS_J1_TYPE_ESF:				return "J_ESF";
		case XMS_E1_TYPE.XMS_SLC_TYPE_96:				return "SLC_TYPE_96";
		case XMS_E1_TYPE.XMS_E1_TYPE_SS7_ISUP_0_Link:	return "T_ISUP_0_LK";
		case XMS_E1_TYPE.XMS_E1_TYPE_SS7_ISUP_1_Link:	return "T_ISUP_1_LK";
		case XMS_E1_TYPE.XMS_E1_TYPE_SS7_ISUP_2_Link:	return "T_ISUP_2_LK";
		case XMS_E1_TYPE.XMS_E1_TYPE_6D25B:				return "T_6D25B";
		case XMS_E1_TYPE.XMS_E1_TYPE_1D30B:             return "T_1D30B"; /*E1 Frame, 1 DChannel, 30 BChannel*/
		case XMS_E1_TYPE.XMS_E1_TYPE_11D20B:            return "T_11D20B"; /*E1 Frame, 11 DChannel, 20 BChannel*/
		case XMS_E1_TYPE.XMS_E1_TYPE_HIZ_CAS:           return "T_HIZ_CAS"; /*E1 Frame, HIZ CAS*/
		case XMS_E1_TYPE.XMS_E1_TYPE_HIZ_PRI:           return "T_HIZ_PRI"; /*E1 Frame, HIZ PRI*/	
		case XMS_E1_TYPE.XMS_E1_TYPE_HIZ_SS7:           return "T_HIZ_SS7"; /*E1 Frame, HIZ SS7*/
		case XMS_E1_TYPE.XMS_E1_TYPE_HIZ_64K_SS7:   	return "T_HIZ_64K_SS7"; /*E1 Frame, HIZ pure 64k SS7*/
		case XMS_E1_TYPE.XMS_E1_TYPE_HIZ_2M_SS7:        return "T_HIZ_2M_SS7"; /*E1 Frame, HIZ 2M SS7*/
		case XMS_E1_TYPE.XMS_E1_TYPE_LINESIDE:          return "T_LINESIDE"; /*E1 Frame, lineside*/
		case XMS_E1_TYPE.XMS_E1_TYPE_HIZ_N64K_HDLC:     return "T_HIZ_N64K_HDLC"; /*E1 Frame, HIZ N*64K HDLC*/	
		case XMS_E1_TYPE.XMS_E1_TYPE_2M_SS7:			return "T_2M_SS7"; /*E1 Frame, 2M SS7*/
		}

		String strRet = "0x" + Integer.toHexString(iPcmType);
		return strRet;
	}
	
	public static String GetString_IODataType(short s16IODataType){
		switch(s16IODataType){
		case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DTMF: 		return "DTMF";
		case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_MR2F: 		return "MR2F";
		case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_MR2B: 		return "MR2B";
		case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_GTG: 		return "GTG/GTD";
		case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_FSK: 		return "FSK";
		case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DPD: 		return "DPD";
		case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_PVD: 		return "PVD";
		
		case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_MSK: 		return "MSK";
		case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_VSD: 		return "VSD";
		case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_MSKREND: 	return "MSKREND";
		case XMS_MEDIA_IO_TYPE.XMS_IO_TYPE_DRS: 		return "DRS";
		}
		
		String strRet = "0x" + Integer.toHexString(s16IODataType);
		return strRet;
	}
	
	public static String GetString_UserState(int iUserState){
		switch(iUserState){
		case USER_STATE.USER_WAITOPEN:					return "Wait Open";
		case USER_STATE.USER_FREE:						return "Free";
		case USER_STATE.USER_OFFHOOK:					return "OffHook";
		case USER_STATE.USER_CALLOUT:					return "CallOut";
		case USER_STATE.USER_LINK:						return "Link";
		case USER_STATE.USER_WAITHANGUP:				return "WaitHangUp";
		case USER_STATE.USER_WAIT_REMOVE:				return "Remove DSP";
		case USER_STATE.USER_RING:						return "Ring";
		}
		
		String strRet = "0x" + Integer.toHexString(iUserState);
		return strRet;
	}
	
	
}
