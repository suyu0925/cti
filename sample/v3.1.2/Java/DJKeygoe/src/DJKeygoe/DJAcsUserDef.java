package DJKeygoe;

public class DJAcsUserDef {
}


/*Acs_Fax_InterCmd*/
class Acs_Fax_InterCmd
{
	public ITP_RES_CHAN         m_ITPFaxRes;/*fax res*/
	public ITP_RES_CHAN         m_ITPFaxVocRes;/*fax voice res*/
	public SendFaxParm_t        m_ITPSendFaxParm = new SendFaxParm_t();/*send fax parm*/
}/*Acs_Fax_InterCmd*/

/*Acs_FaxEnd_InterCmd*/
class Acs_FaxEnd_InterCmd
{
	public ITP_RES_CHAN         m_ITPFaxVocRes;/*fax voice res*/
    public int                	m_s32EvtState;
    public int                	m_s32ErrCode;
    public byte                 m_u8ErrStep;
    public byte                 m_u8T30CmdState;
    public byte                 m_u8T30RcvState;
    public short                m_u16TotalPages;
    public byte                 m_s8RemoteID[] = new byte[20];
}/*Acs_FaxEnd_InterCmd*/

class LostCallInfo
{
	public byte szCalling[]	 = new byte[20];/**/
	public byte szCalled[]	 = new byte[20];/**/
	public byte szOrigCalled[] = new byte[20];/**/
	public byte szLostTime[]   = new byte[40];/**/
}/*LostCallInfo*/

class Fax_VoIP_InterCmd
{
	public DeviceID_t       m_FaxDevice = new DeviceID_t();
	public byte             m_s8T38Shake;
	public byte             m_s8Rfu1[] = new byte[3];
}/*Fax_VoIP_InterCmd*/

class CallUserInfor 
{
	public DeviceID_t    	m_DeviceID = new DeviceID_t();
	public byte	            m_szCaller[] = new byte[32];
}/*CallUserInfor*/

class InterCmdStru
{
	public byte		        m_s8Buff[] = new byte[1024];
}/*InterCmdStru*/

class LinkStru
{
	public DeviceID_t	 DstDev = new DeviceID_t(); /*dst dev*/
	public ITP_RES_CHAN  SRtpx;
	public ITP_RES_CHAN  DRtpx;
	public ITP_RES_CHAN  MEx;
}

/*MediaType*/
class MediaType
{
	public byte 	m_u8MediaType;
	public byte 	rfu;
	public short 	m_u16Kbps;
}/*MediaType*/


/*CmdParamData_ReadVoltage_t*/
class CmdParamData_ReadVoltage_t
{    
	public byte   m_u8ReadFlag;      /*Read voltage control flag, 0: stop read; 1: start read*/
	public byte   m_s8Reserved1[] = new byte[3];
	public int    m_u32TimeSpan;     /*Keygoe report voltage event time span, unit: ms*/
	public byte   m_s8Voltage;       /*Current voltage value*/ 
	public byte   m_u8Reserved2[] = new byte[3];   /*reserved*/
}/*CmdParamData_ReadVoltage_t*/

