using System;
using System.Collections.Generic;
using System.Text;

namespace DJKeygoe
{
    using DJ_U8 = Byte;
    using DJ_S8 = SByte;
    using DJ_U16 = UInt16;
    using DJ_U32 = UInt32;
    using DJ_S32 = Int32;

        /*Acs_Fax_InterCmd*/
        public struct Acs_Fax_InterCmd
        {
	        public ITP_RES_CHAN         m_ITPFaxRes;/*fax res*/ //C#class 都是ref
            public ITP_RES_CHAN         m_ITPFaxVocRes;/*fax voice res*/
            public SendFaxParm_t        m_ITPSendFaxParm;/*send fax parm*/
        };/*Acs_Fax_InterCmd*/

        /*Acs_FaxEnd_InterCmd*/
        public unsafe struct Acs_FaxEnd_InterCmd
        {
            public ITP_RES_CHAN   m_ITPFaxVocRes;/*fax voice res*/
            public DJ_S32                m_s32EvtState;
            public DJ_S32                m_s32ErrCode;
            public DJ_U8                  m_u8ErrStep;
            public DJ_U8                  m_u8T30CmdState;
            public DJ_U8                  m_u8T30RcvState;
            public DJ_U16                m_u16TotalPages;
            public fixed DJ_S8          m_s8RemoteID[20];
        };/*Acs_FaxEnd_InterCmd*/

        public unsafe struct LostCallInfo
        {
	        public fixed DJ_S8 szCalling[20];/**/
	        public fixed DJ_S8 szCalled[20];/**/
	        public fixed DJ_S8 szOrigCalled[20];/**/
	        public fixed DJ_S8 szLostTime[40];/**/
        };/*LostCallInfo*/

        public unsafe struct Fax_VoIP_InterCmd
        {
	        public DeviceID_t             m_FaxDevice;
	        public DJ_S8                     m_s8T38Shake;
	        public fixed DJ_S8             m_s8Rfu1[3];
        };/*Fax_VoIP_InterCmd*/

        public unsafe struct CallUserInfor
        {
	        public DeviceID_t    m_DeviceID;
	        public fixed DJ_S8   m_szCaller[32];
        };/*CallUserInfor*/

        public unsafe struct InterCmdStru
        {
	        public fixed DJ_S8          m_s8Buff[1024];
        };/*InterCmdStru*/

        public unsafe struct LinkStru
        {
	        public  DeviceID_t			   DstDev; /*dst dev*/
            public ITP_RES_CHAN         SRtpx;
            public ITP_RES_CHAN         DRtpx;
            public ITP_RES_CHAN         MEx;
        };/*LinkStru*/

        /*MediaType*/
        public struct MediaType
        {
	        public DJ_U8    m_u8MediaType;
	        public DJ_U8    rfu;
	        public DJ_U16  m_u16Kbps;
        };/*MediaType*/

        /*CmdParamData_ReadVoltage_t*/
        public unsafe struct CmdParamData_ReadVoltage_t
        {    
	        public DJ_U8             m_u8ReadFlag;      /*Read voltage control flag, 0: stop read; 1: start read*/
            public fixed DJ_S8     m_s8Reserved1[3];
	        public DJ_U32           m_u32TimeSpan;     /*Keygoe report voltage event time span, unit: ms*/
	        public DJ_S8             m_s8Voltage;       /*Current voltage value*/ 
            public fixed DJ_U8    m_u8Reserved2[3];   /*reserved*/
        };/*CmdParamData_ReadVoltage_t*/
}