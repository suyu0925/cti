using System;
using System.Text;
using System.Runtime.InteropServices;

namespace DJKeygoe
{
    public class CAS_Common_Code
    {
        /*************************************************************************************
        return 
	        0:	OK.
	        -1:	Fail, m_u8CalledTableCount Invalid
	        -2: Fail, m_u8CalledLen Invalid
	        -3: Fail, m_u8CalledTimeOut Invalid
	        -4: Fail, m_u8AreaCodeLen Invalid
	        -5: Fail, m_CalledTable[x].m_u8NumLen Invalid
        *************************************************************************************/
        public static unsafe int CAS_Common_Cfg_ReadCfg(ref CmdParamData_CAS_t pParam_CAS)
        {
            ClsIniFile clsIniFile = new ClsIniFile("C:\\DJKeygoe\\Samples\\CAS_Common_Code\\XMS_CAS_Cfg.INI");

            //int			i;
            //char		TmpStr[32], TmpName[32];

            // ------------------------ [Rule] ------------------------
            // m_u8CalledTableCount
            int iTmp = clsIniFile.GetFileInt("Rule", "CalledTableCount", 0);
            if ((iTmp < 0) || (iTmp > 16))
                return -1;							// m_u8CalledTableCount Invalid
            pParam_CAS.m_u8CalledTableCount = (byte)iTmp;

            // m_u8CalledLen
            iTmp = clsIniFile.GetFileInt("Rule", "CalledLen", 5);
            if ((iTmp <= 0) || (iTmp > 32))
                return -2;							// m_u8CalledLen Invalid
            pParam_CAS.m_u8CalledLen = (byte)iTmp;

            // m_u8CalledTimeOut
            iTmp = clsIniFile.GetFileInt("Rule", "CalledTimeOut", 0);
            if ((iTmp < 0) || (iTmp > 10))
                return -3;							// m_u8CalledTimeOut Invalid
            pParam_CAS.m_u8CalledTimeOut = (byte)iTmp;

            // m_u8NeedCaller
            iTmp = clsIniFile.GetFileInt("Rule", "NeedCaller", 0);
            if (iTmp != 0)
                iTmp = 1;
            pParam_CAS.m_u8NeedCaller = (byte)iTmp;

            // m_u8AreaCodeLen
            iTmp = clsIniFile.GetFileInt("Rule", "AreaCodeLen", 0);
            if (pParam_CAS.m_u8NeedCaller != 0)		// need caller
            {
                if ((iTmp < 0) || (iTmp > 10))
                    return -4;						// m_u8AreaCodeLen Invalid
            }
            pParam_CAS.m_u8AreaCodeLen = (byte)iTmp;

            // m_u8ControlMode
            iTmp = clsIniFile.GetFileInt("Rule", "ControlMode", 0);
            if ((iTmp != 0) && (iTmp != 1) && (iTmp != 2))
                iTmp = 0;
            pParam_CAS.m_u8ControlMode = (byte)iTmp;

            // ------------------------ [CalledTable] ------------------------
            //memset ( pParam_CAS->m_CalledTable, 0, sizeof(DJDataDefClass.CAS_CalledTableDesc_t) * 16 );
            //fixed(CAS_CalledTableDesc_t* pCalledTable = &pParam_CAS.m_CalledTable[0])
            fixed (byte* p = pParam_CAS.m_CalledTable)
            {
                CAS_CalledTableDesc_t* pCalledTable = (CAS_CalledTableDesc_t*)p;
                for (int i = 0; i < pParam_CAS.m_u8CalledTableCount; ++i)
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

                    TmpName = null;
                    strBlderTemp = null;
                    TmpNameEx = null;
                    strTemp = null;
                }
            }

            // ------------------------ Other ------------------------
            // Call Out Parameter, set to default value directly.
            pParam_CAS.m_u8KA = 1;
            pParam_CAS.m_u8KD = 3;

            return 0;		// OK
        }
    };
}