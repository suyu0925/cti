using System;
using System.Text;
using System.Runtime.InteropServices;

namespace DJKeygoe
{

    public class Analog_Common_Code
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
        public static unsafe int Analog_Common_Cfg_ReadCfg(ref TYPE_ANALOG_GTD_PARAM pParam_Analog)
        {
            ClsIniFile clsIniFile = new ClsIniFile("C:\\DJKeygoe\\Samples\\Analog_Common_Code\\XMS_Analog_Cfg.INI");

            // ------------------------ [Freq] ------------------------
            int iTmp = clsIniFile.GetFileInt("Freq", "Freq0", 450);
            if ((iTmp < 300) || (iTmp > 3400))
                return -1;							// m_u16Freq0 Invalid, should be 300-3400 Hz
            pParam_Analog.m_u16Freq0 = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("Freq", "Freq1", 500);
            if ((iTmp < 300) || (iTmp > 3400))
                return -2;							// m_u16Freq1 Invalid, should be 300-3400 Hz
            pParam_Analog.m_u16Freq1 = (ushort)iTmp;

            // ------------------------ [DialTone] ------------------------
            iTmp = clsIniFile.GetFileInt("DialTone", "FreqIndexMask", 3);
            if ((iTmp < 0) || (iTmp > 0xFF))
                return -3;							// m_u16DialTone_FreqIndexMask Invalid, should be 0x00-0xFF
            pParam_Analog.m_u16DialTone_FreqIndexMask = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("DialTone", "On_Time", 1000);
            if ((iTmp < 100) || (iTmp > 5000))
                return -4;							// m_u16DialTone_On_Time Invalid, should be 100-5000 ms
            pParam_Analog.m_u16DialTone_On_Time = (ushort)iTmp;

            // ------------------------ [RingBackTone] ------------------------
            iTmp = clsIniFile.GetFileInt("RingBackTone", "FreqIndexMask", 3);
            if ((iTmp < 0) || (iTmp > 0xFF))
                return -5;							// m_u16RingBackTone_FreqIndexMask Invalid, should be 0x00-0xFF
            pParam_Analog.m_u16RingBackTone_FreqIndexMask = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("RingBackTone", "On_Time", 1000);
            if ((iTmp < 100) || (iTmp > 5000))
                return -5;							// m_u16RingBackTone_On_Time Invalid, should be 100-5000 ms
            pParam_Analog.m_u16RingBackTone_On_Time = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("RingBackTone", "Off_Time", 4000);
            if ((iTmp < 100) || (iTmp > 5000))
                return -6;							// m_u16RingBackTone_Off_Time Invalid, should be 100-5000 ms
            pParam_Analog.m_u16RingBackTone_Off_Time = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("RingBackTone", "TimeDeviation", 10);
            if ((iTmp < 0) || (iTmp > 50))
                return -7;							// m_u16RingBackTone_TimeDeviation Invalid, should be 0%-50%
            pParam_Analog.m_u16RingBackTone_TimeDeviation = (ushort)iTmp;

            // ------------------------ [BusyTone0] ------------------------
            iTmp = clsIniFile.GetFileInt("BusyTone0", "FreqIndexMask", 3);
            if ((iTmp < 0) || (iTmp > 0xFF))
                return -8;							// m_u16BusyTone0_FreqIndexMask Invalid, should be 0x00-0xFF
            pParam_Analog.m_u16BusyTone0_FreqIndexMask = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("BusyTone0", "On_Time", 1000);
            if ((iTmp < 100) || (iTmp > 5000))
                return -8;							// m_u16BusyTone0_On_Time Invalid, should be 100-5000 ms
            pParam_Analog.m_u16BusyTone0_On_Time = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("BusyTone0", "Off_Time", 4000);
            if ((iTmp < 100) || (iTmp > 5000))
                return -10;							// m_u16BusyTone0_Off_Time Invalid, should be 100-5000 ms
            pParam_Analog.m_u16BusyTone0_Off_Time = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("BusyTone0", "TimeDeviation", 10);
            if ((iTmp < 0) || (iTmp > 50))
                return -11;							// m_u16BusyTone0_TimeDeviation Invalid, should be 0%-50%
            pParam_Analog.m_u16BusyTone0_TimeDeviation = (ushort)iTmp;

            // ------------------------ [BusyTone1] ------------------------
            iTmp = clsIniFile.GetFileInt("BusyTone1", "FreqIndexMask", 3);
            if ((iTmp < 0) || (iTmp > 0xFF))
                return -8;							// m_u16BusyTone1_FreqIndexMask Invalid, should be 0x00-0xFF
            pParam_Analog.m_u16BusyTone1_FreqIndexMask = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("BusyTone1", "On_Time", 1000);
            if ((iTmp < 100) || (iTmp > 5000))
                return -8;							// m_u16BusyTone1_On_Time Invalid, should be 100-5000 ms
            pParam_Analog.m_u16BusyTone1_On_Time = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("BusyTone1", "Off_Time", 4000);
            if ((iTmp < 100) || (iTmp > 5000))
                return -10;							// m_u16BusyTone1_Off_Time Invalid, should be 100-5000 ms
            pParam_Analog.m_u16BusyTone1_Off_Time = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("BusyTone1", "TimeDeviation", 10);
            if ((iTmp < 0) || (iTmp > 50))
                return -11;							// m_u16BusyTone1_TimeDeviation Invalid, should be 0%-50%
            pParam_Analog.m_u16BusyTone1_TimeDeviation = (ushort)iTmp;

            // ------------------------ [BusyTone2] ------------------------
            iTmp = clsIniFile.GetFileInt("BusyTone2", "FreqIndexMask", 3);
            if ((iTmp < 0) || (iTmp > 0xFF))
                return -8;							// m_u16BusyTone2_FreqIndexMask Invalid, should be 0x00-0xFF
            pParam_Analog.m_u16BusyTone2_FreqIndexMask = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("BusyTone2", "On_Time", 1000);
            if ((iTmp < 100) || (iTmp > 5000))
                return -8;							// m_u16BusyTone2_On_Time Invalid, should be 100-5000 ms
            pParam_Analog.m_u16BusyTone2_On_Time = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("BusyTone2", "Off_Time", 4000);
            if ((iTmp < 100) || (iTmp > 5000))
                return -10;							// m_u16BusyTone2_Off_Time Invalid, should be 100-5000 ms
            pParam_Analog.m_u16BusyTone2_Off_Time = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("BusyTone2", "TimeDeviation", 10);
            if ((iTmp < 0) || (iTmp > 50))
                return -11;							// m_u16BusyTone2_TimeDeviation Invalid, should be 0%-50%
            pParam_Analog.m_u16BusyTone2_TimeDeviation = (ushort)iTmp;

            // ------------------------ [Other] ------------------------
            iTmp = clsIniFile.GetFileInt("Other", "NoDialToneAfterOffHook", 5000);
            if ((iTmp < 1000) || (iTmp > 10000))
                return -11;							// m_u16NoDialToneAfterOffHook Invalid, should be 1-10 sec
            pParam_Analog.m_u16NoDialToneAfterOffHook = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("Other", "Ringback_NoAnswerTime", 40000);
            if ((iTmp < 10000) || (iTmp > 60000))
                return -11;							// m_u16Ringback_NoAnswerTime Invalid, should be 10-60 sec
            pParam_Analog.m_u16Ringback_NoAnswerTime = (ushort)iTmp;

            iTmp = clsIniFile.GetFileInt("Other", "SendFSKCallerIDTime", 1500);
            if ((iTmp < 1000) || (iTmp > 5000))
                return -11;							// m_u16SendFSKCallerIDTime Invalid, should be 1000-5000 ms
            pParam_Analog.m_u16SendFSKCallerIDTime = (ushort)iTmp;

            return 0;		// OK
        }
    };
}