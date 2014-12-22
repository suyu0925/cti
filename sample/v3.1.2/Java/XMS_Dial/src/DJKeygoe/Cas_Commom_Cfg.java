package DJKeygoe;

import java.io.IOException;

public class Cas_Commom_Cfg {
	public static void CharsToByte(byte[] DestArr, char []SourArr, int nLen){
		for (int i = 0; i < nLen; i++){
			DestArr[i] = (byte)SourArr[i];
		}
	}
	
	public static int CAS_Common_Cfg_ReadCfg (CmdParamData_CAS_t pParam_CAS){
		String strCasFilePath = new String("C:\\DJKeygoe\\Samples\\CAS_Common_Code\\XMS_CAS_Cfg.INI");
		int iTmp = 0;
		
		try{
			String strTableCount = JIniFile.getProfileString(strCasFilePath, "Rule", "CalledTableCount", "0");
			iTmp = (byte)Integer.parseInt(strTableCount);
			if (iTmp < 0 || iTmp > 16){
				return -1;
			}
			pParam_CAS.m_u8CalledTableCount = (byte)iTmp;
			
			String strCalledLen = JIniFile.getProfileString(strCasFilePath, "Rule", "CalledLen", "5");
			iTmp = (byte)Integer.parseInt(strCalledLen);
			if (iTmp <= 0 || iTmp > 32){
				return -2;
			}
			pParam_CAS.m_u8CalledLen = (byte)iTmp;
			
			String strCalledTimeOut = JIniFile.getProfileString(strCasFilePath, "Rule", "CalledTimeOut", "0");
			iTmp = (byte)Integer.parseInt(strCalledTimeOut);
			if (iTmp < 0 || iTmp > 10){
				return -3;
			}
			pParam_CAS.m_u8CalledTimeOut = (byte)iTmp;
			
			String strNeedRead = JIniFile.getProfileString(strCasFilePath, "Rule", "NeedCaller", "1");
			iTmp = (byte)Integer.parseInt(strNeedRead);
			if (iTmp != 0){
				iTmp = 1;
			}
			pParam_CAS.m_u8NeedCaller = (byte)iTmp;
			
			String strAreaCodeLen = JIniFile.getProfileString(strCasFilePath, "Rule", "AreaCodeLen", "0");
			iTmp = (byte)Integer.parseInt(strAreaCodeLen);
			if (pParam_CAS.m_u8NeedCaller != 0){
				if(iTmp < 0 || iTmp > 10){
					return -4;
				}
			}
			pParam_CAS.m_u8AreaCodeLen = (byte)iTmp;
			
			String strCtrlMode = JIniFile.getProfileString(strCasFilePath, "Rule", "ControlMode", "0");
			iTmp = (byte)Integer.parseInt(strCtrlMode);
			if (iTmp != 0 && iTmp != 1 && iTmp != 2){
				iTmp = 0;
			}
			pParam_CAS.m_u8ControlMode = (byte)iTmp;
			
			for (int i = 0; i < pParam_CAS.m_u8CalledTableCount; i++){
				String var = "NumHead[" + Integer.toString(i) + "]";
				String strCalledTable = JIniFile.getProfileString(strCasFilePath, "CalledTable", var, "168");
				
				if (strCalledTable.length() > 13){
					pParam_CAS.m_CalledTable[i].m_u8NumHeadLen = 13;
				}
				else {
					pParam_CAS.m_CalledTable[i].m_u8NumHeadLen = (byte)strCalledTable.length();
				}
				
				CharsToByte(pParam_CAS.m_CalledTable[i].m_u8NumHead, strCalledTable.toCharArray(), pParam_CAS.m_CalledTable[i].m_u8NumHeadLen);
				
				var = "NumLen[" + Integer.toString(i) + "]";
				String strNumLen = JIniFile.getProfileString(strCasFilePath, "CalledTable", var, "5");
				
				iTmp = (byte)Integer.parseInt(strNumLen);
				if (iTmp < 0 || iTmp > 16){
					return -5;
				}
				pParam_CAS.m_CalledTable[i].m_u8NumLen = (byte) iTmp;
			}
		} catch(IOException e){
			e.printStackTrace();
		}

		pParam_CAS.m_u8KA = 1;
		pParam_CAS.m_u8KD = 3;

		return	0;		// OK
	}

}
