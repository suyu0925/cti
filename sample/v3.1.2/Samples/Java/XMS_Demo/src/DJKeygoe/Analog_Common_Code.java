package DJKeygoe;

public class Analog_Common_Code {
	public static int	Analog_Common_Cfg_ReadCfg (TYPE_ANALOG_GTD_PARAM g_Param_Analog){
		String strCfgFilePath = new String("C:\\DJKeygoe\\Samples\\Analog_Common_Code\\XMS_Analog_Cfg.INI");
		int iTmp;

		try{
			String strFreq0 = JIniFile.getProfileString(strCfgFilePath, "Freq", "Freq0", "450");
			iTmp = Integer.parseInt(strFreq0);
			if (iTmp < 300 || iTmp > 3400){
				return -1;
			}
			g_Param_Analog.m_u16Freq0 = (short)iTmp;
			
			String strFreq1 = JIniFile.getProfileString(strCfgFilePath, "Freq", "Freq1", "500");
			iTmp = Integer.parseInt(strFreq1);
			if (iTmp < 300 || iTmp > 3400){
				return -2;
			}
			g_Param_Analog.m_u16Freq1 = (short)iTmp;
			
			String strDialTone = JIniFile.getProfileString(strCfgFilePath, "DialTone", "FreqIndexMask", "3");
			iTmp = Integer.parseInt(strDialTone);
			if (iTmp < 0 || iTmp > 0xFF){
				return -3;
			}
			g_Param_Analog.m_u16DialTone_FreqIndexMask = (short)iTmp;
			
			String strOnTime = JIniFile.getProfileString(strCfgFilePath, "DialTone", "On_Time", "1000");
			iTmp = Integer.parseInt(strOnTime);
			if (iTmp < 100 || iTmp > 5000){
				return -4;
			}
			g_Param_Analog.m_u16DialTone_On_Time = (short)iTmp;
			
			String strRingBackTone = JIniFile.getProfileString(strCfgFilePath, "RingBackTone", "FreqIndexMask", "3");
			iTmp = Integer.parseInt(strRingBackTone);
			if (iTmp < 0 || iTmp > 0xFF){
				return -5;
			}
			g_Param_Analog.m_u16RingBackTone_FreqIndexMask = (short)iTmp;
			
			String strRingBackToneOnTime = JIniFile.getProfileString(strCfgFilePath, "RingBackTone", "On_Time", "1000");
			iTmp = Integer.parseInt(strRingBackToneOnTime);
			if (iTmp < 100 || iTmp > 5000){
				return -5;
			}
			g_Param_Analog.m_u16RingBackTone_On_Time = (short)iTmp;
			
			String strRingBackToneOffTime = JIniFile.getProfileString(strCfgFilePath, "RingBackTone", "Off_Time", "4000");
			iTmp = Integer.parseInt(strRingBackToneOffTime);
			if (iTmp < 100 || iTmp > 5000){
				return -6;
			}
			g_Param_Analog.m_u16RingBackTone_Off_Time = (short)iTmp;
		
			String strRingBackToneDev = JIniFile.getProfileString(strCfgFilePath, "RingBackTone", "TimeDeviation", "10");
			strRingBackToneDev = strRingBackToneDev.substring(0,strRingBackToneDev.indexOf('%')); 
			iTmp = Integer.parseInt(strRingBackToneDev);
			if (iTmp < 0 || iTmp > 50){
				return -7;
			}
			g_Param_Analog.m_u16RingBackTone_TimeDeviation = (short)iTmp;
			
			// ------------------------ [BusyTone0] ------------------------
			String strBusyTone0 = JIniFile.getProfileString(strCfgFilePath, "BusyTone0", "FreqIndexMask", "3");
			iTmp = Integer.parseInt(strBusyTone0);
			if (iTmp < 0 || iTmp > 0xFF){
				return -8;
			}
			g_Param_Analog.m_u16BusyTone0_FreqIndexMask = (short)iTmp;
			
			String strBusyTone0OnTime = JIniFile.getProfileString(strCfgFilePath, "BusyTone0", "On_Time", "1000");
			iTmp = Integer.parseInt(strBusyTone0OnTime);
			if (iTmp < 100 || iTmp > 5000){
				return -8;
			}
			g_Param_Analog.m_u16BusyTone0_On_Time = (short)iTmp;
			
			String strBusyTone0OffTime = JIniFile.getProfileString(strCfgFilePath, "BusyTone0", "Off_Time", "4000");
			iTmp = Integer.parseInt(strBusyTone0OffTime);
			if (iTmp < 100 || iTmp > 5000){
				return -8;
			}
			g_Param_Analog.m_u16BusyTone0_Off_Time = (short)iTmp;
			
			
			String strBusyTone0TimeDev = JIniFile.getProfileString(strCfgFilePath, "BusyTone0", "TimeDeviation", "10");
			strBusyTone0TimeDev = strRingBackToneDev.substring(0,strBusyTone0TimeDev.indexOf('%'));
			
			iTmp = Integer.parseInt(strBusyTone0TimeDev);
			if (iTmp < 0 || iTmp > 50){
				return -11;
			}
			g_Param_Analog.m_u16BusyTone0_TimeDeviation = (short)iTmp;

			// ------------------------ [BusyTone1] ------------------------
			String strBusyTone1 = JIniFile.getProfileString(strCfgFilePath, "BusyTone1", "FreqIndexMask", "3");
			iTmp = Integer.parseInt(strBusyTone1);
			if (iTmp < 0 || iTmp > 0xFF){
				return -8;
			}
			g_Param_Analog.m_u16BusyTone1_FreqIndexMask = (short)iTmp;
			
			String strBusyTone1OnTime = JIniFile.getProfileString(strCfgFilePath, "BusyTone1", "On_Time", "1000");
			iTmp = Integer.parseInt(strBusyTone1OnTime);
			if (iTmp < 100 || iTmp > 5000){
				return -8;
			}
			g_Param_Analog.m_u16BusyTone1_On_Time = (short)iTmp;
			
			String strBusyTone1OffTime = JIniFile.getProfileString(strCfgFilePath, "BusyTone1", "Off_Time", "4000");
			iTmp = Integer.parseInt(strBusyTone1OffTime);
			if (iTmp < 100 || iTmp > 5000){
				return -8;
			}
			g_Param_Analog.m_u16BusyTone1_Off_Time = (short)iTmp;
			
			String strBusyTone1TimeDev = JIniFile.getProfileString(strCfgFilePath, "BusyTone1", "TimeDeviation", "10");
			strBusyTone1TimeDev = strRingBackToneDev.substring(0,strBusyTone1TimeDev.indexOf('%'));
			iTmp = Integer.parseInt(strBusyTone1TimeDev);
			if (iTmp < 0 || iTmp > 50){
				return -11;
			}
			g_Param_Analog.m_u16BusyTone1_TimeDeviation = (short)iTmp;
			
			// ------------------------ [BusyTone2] ------------------------
			String strBusyTone2 = JIniFile.getProfileString(strCfgFilePath, "BusyTone2", "FreqIndexMask", "3");
			iTmp = Integer.parseInt(strBusyTone2);
			if (iTmp < 0 || iTmp > 0xFF){
				return -8;
			}
			g_Param_Analog.m_u16BusyTone2_FreqIndexMask = (short)iTmp;
			
			String strBusyTone2OnTime = JIniFile.getProfileString(strCfgFilePath, "BusyTone2", "On_Time", "1000");
			iTmp = Integer.parseInt(strBusyTone2OnTime);
			if (iTmp < 100 || iTmp > 5000){
				return -8;
			}
			g_Param_Analog.m_u16BusyTone2_On_Time = (short)iTmp;
			
			String strBusyTone2OffTime = JIniFile.getProfileString(strCfgFilePath, "BusyTone2", "Off_Time", "4000");
			iTmp = Integer.parseInt(strBusyTone2OffTime);
			if (iTmp < 100 || iTmp > 5000){
				return -10;
			}
			g_Param_Analog.m_u16BusyTone2_Off_Time = (short)iTmp;
			
			String strBusyTone2TimeDev = JIniFile.getProfileString(strCfgFilePath, "BusyTone2", "TimeDeviation", "10");
			strBusyTone2TimeDev = strRingBackToneDev.substring(0,strBusyTone2TimeDev.indexOf('%'));
			iTmp = Integer.parseInt(strBusyTone2TimeDev);
			if (iTmp < 0 || iTmp > 50){
				return -11;
			}
			g_Param_Analog.m_u16BusyTone2_TimeDeviation = (short)iTmp;

			// ------------------------ [Other] ------------------------
			String strDialToneAftOffH = JIniFile.getProfileString(strCfgFilePath, "Other", "NoDialToneAfterOffHook", "5000");
			iTmp = Integer.parseInt(strDialToneAftOffH);
			if (iTmp < 1000 || iTmp > 10000){
				return -11;
			}
			g_Param_Analog.m_u16NoDialToneAfterOffHook = (short)iTmp;
			
			
			String strRingBackNoAns = JIniFile.getProfileString(strCfgFilePath, "Other", "Ringback_NoAnswerTime", "40000");
			iTmp = Integer.parseInt(strRingBackNoAns);
			if (iTmp < 10000 || iTmp > 60000){
				return -11;
			}
			g_Param_Analog.m_u16Ringback_NoAnswerTime = (short)iTmp;
			
			String strSendFskTime = JIniFile.getProfileString(strCfgFilePath, "Other", "SendFSKCallerIDTime", "1500");
			iTmp = Integer.parseInt(strSendFskTime);
			if (iTmp < 1000 || iTmp > 5000){
				return -11;
			}
			g_Param_Analog.m_u16SendFSKCallerIDTime = (short)iTmp;
			return 0;		// OK
		} catch(Exception ee){
			ee.printStackTrace();
		}
		return 0;
	}
	
	/***nDestDataLen:prevent in the case of overflow***/
	public static int ConvertRawFskToCallerID(byte SourData[], int nSourDataLen, byte DestData[], int nDestDataLen){
		
		SourData[nSourDataLen] = 0;
		
		if (nSourDataLen == 0){
			return -1;
		}
				
		SourData[nSourDataLen] = 0;
		
		// find the Format
		int i = 0;
		
		for (i=0; i<nDestDataLen; i++){
			DestData[i] = 0;
		}
		
		for (i = 0; i < nSourDataLen; i++){
			if ( SourData[i] == 0x04 ) {		// single format
				break;
			}
			
			if ( SourData[i] == 0x80 ) {		// multiple format
				break;
			}
		}
		
		if (i == nSourDataLen || i == nSourDataLen -1){
			return -1;
		}
		
		// start fetch the Caller ID
		int nPos = i;
		int nLen = SourData[nPos+1];
		
		if (nLen > nDestDataLen)
			nLen = nDestDataLen;

		// "count-pos-2"    is the length of now received
		int j = 0;
		for (i = nPos+2,j = 0; (i<(nSourDataLen-1)) && (j<nLen); i ++,j++)
		{
			DestData[j] = (byte)(SourData[i] & 0x7F);
			if ( j == nDestDataLen - 1 )				// it will be overflow
				break;
		}
		DestData[j] = 0;

		if ( (nSourDataLen-nPos-3) < nLen  )
		{
			return -1;		// not a good Caller ID
		}

		int ChkSum = 0;
		for ( i = nPos; i < nPos+nLen+3; i ++ )
				ChkSum += SourData[i];

	// multiple format
		if ( SourData[nPos] == 0x80 ) 
		{
			HandleMultiple ( DestData );
		}
	// end of multiple

		if ( ChkSum == 0 )
			return	0;		// OK
		else
			return -1;		// Fail
	}
	
	// multiple format
	public static void HandleMultiple (byte IDStr[] ){
		byte s8Data[] = new byte[20];
		
		for (int i = 0, j = 0; IDStr[i] != 0; ){
			if (IDStr[i] == 1 || IDStr[i] == 2 || IDStr[i] == 4 || IDStr[i] == 7 || IDStr[i] == 8){
				i += 2;
			}
			else{
				s8Data[j] = IDStr[i];
				i++;
				j++;
			}
		}
	}
	// end of multiple
}


class TYPE_ANALOG_GTD_PARAM 
{
	// Freq
	public short		m_u16Freq0;
	public short		m_u16Freq1;

	// DailTone
	public short		m_u16DialTone_FreqIndexMask;
	public short		m_u16DialTone_On_Time;

	// RingBackTone
	public short		m_u16RingBackTone_FreqIndexMask;
	public short		m_u16RingBackTone_On_Time;
	public short		m_u16RingBackTone_Off_Time;
	public short		m_u16RingBackTone_TimeDeviation;		// in percentage

	// BusyTone0
	public short		m_u16BusyTone0_FreqIndexMask;
	public short		m_u16BusyTone0_On_Time;
	public short		m_u16BusyTone0_Off_Time;
	public short		m_u16BusyTone0_TimeDeviation;				// in percentage

	// BusyTone1
	public short		m_u16BusyTone1_FreqIndexMask;
	public short		m_u16BusyTone1_On_Time;
	public short		m_u16BusyTone1_Off_Time;
	public short		m_u16BusyTone1_TimeDeviation;				// in percentage

	// BusyTone2
	public short		m_u16BusyTone2_FreqIndexMask;
	public short		m_u16BusyTone2_On_Time;
	public short		m_u16BusyTone2_Off_Time;
	public short		m_u16BusyTone2_TimeDeviation;				// in percentage

	// other 
	public short		m_u16NoDialToneAfterOffHook;
	public short		m_u16Ringback_NoAnswerTime;

	public short		m_u16SendFSKCallerIDTime;					// for Analog_User Channel
}
