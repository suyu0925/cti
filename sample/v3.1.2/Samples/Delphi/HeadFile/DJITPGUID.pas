unit DJITPGUID;

interface

const  MODULE_TYPE_PROXY      = $00;           //Proxy模块
const  MODULE_TYPE_DSP    	  = $01;          //DSP功能模块
const  MODULE_TYPE_MEDIA	    = $02;           //媒体处理模块
const  MODULE_TYPE_SS7        = $03;           //七号处理模块
const  MODULE_TYPE_CFG 	      = $04;           //配置模块
const  MODULE_TYPE_MONITOR 	  = $05;           //监控模块
const  MODULE_TYPE_FLOW       = $06;	       //流程模块
const  MODULE_TYPE_PRI        = $07;	       //ISDN信令模块
const  MODULE_TYPE_USER       = $08;           //用户模块
const  MODULE_TYPE_INTERFACE  = $09;           //界面模块
const  MODULE_TYPE_VOIP       = $0A;           //VoIP模块
const  MODULE_TYPE_3G324M     = $0B;           //3G-324M模块
const  MODULE_TYPE_MEDIAEX	  = $0C;	       //媒体编解码模块
const  MODULE_TYPE_FAXTIFF    = $0E;           //FAXTIFF模块
const  MODULE_TYPE_ACS        = $0F;           //API模块
const  MODULE_TYPE_SIGMON     = $10;           //信令监控模块
const  MODULE_TYPE_CTXM       = $11;           //交换矩阵模块
//DSP功能模块功能ID定义***************************************
const  DSP_MAIN_FUNCTION_CONFIG      = $01;           //全局设备管理
const  DSP_MAIN_FUNCTION_SPEECH      = $02;           //语音功能
const  DSP_MAIN_FUNCTION_FAX         = $03;           //传真功能
const  DSP_MAIN_FUNCTION_DIGITAL     = $04;           //数字中继功能
const  DSP_MAIN_FUNCTION_INTERFACE   = $05;           //坐席功能模块
const  DSP_MAIN_FUNCTION_PRILINK     = $06;           //会议功能模块
const  DSP_MAIN_FUNCTION_SS7LINK     = $07;           //数字中继功能模块
const  DSP_MAIN_FUNCTION_CTCLK       = $08;           //CT_BUS时钟
const  DSP_MAIN_FUNCTION_CTTS        = $09;           //CT_BUS资源
const  DSP_MAIN_FUNCTION_CONNECTTS   = $0A;           //时隙连接
const  DSP_MAIN_FUNCTION_FIRMWARE    = $0B;           //固件操作
const  DSP_MAIN_FUNCTION_VOIP        = $0C;           //VoIP功能
const  DSP_MAIN_FUNCTION_3G324M      = $0D;           //G-324M功能
const  DSP_MAIN_FUNCTION_LICENSE     = $0E;           //license alarm
const  DSP_MAIN_FUNCTION_RTPX	= $0F;		//Data exchange 功能

const  DSP_MAIN_FUNCTION_CONFERENCE  = $10;           //for conference event
const  DSP_MAIN_FUNCTION_DEBUG_INFOR  = $11;     //for DSP debug information, add by zcq at 20090813
const  DSP_SUB_FUNCTION_LICENSE_INQUIRE     = $01;           //license alarm


const  SUB_FUNCTION_ALL                = $FF;        //所有子功能

const  DSP_SUB_FUNCTION_SPEECH_INPUT   = $01;        //输入功能(EC,AGC等)
const  DSP_SUB_FUNCTION_SPEECH_OUTPUT  = $02;        //输出功能(混音,AGC等)
const  DSP_SUB_FUNCTION_SPEECH_PLAY    = $03;        //放音功能
const  DSP_SUB_FUNCTION_SPEECH_RECORD  = $04;        //录音功能
const  DSP_SUB_FUNCTION_SPEECH_GTD     = $05;        //各种音频处理功能
const  DSP_SUB_FUNCTION_SPEECH_CONF    = $06;        //会议处理功能


//DSP DSS1子功能定义
const  DSP_SUB_FUNCTION_DSS1_CFG_CMD_TO_DSP        = $01;      //DSS1配置命令，        Q931->DSP
const  DSP_SUB_FUNCTION_DSS1_GET_CFG_TO_DSP        = $02;      //获取DSS1配置信息命令，Q931->DSP
const  DSP_SUB_FUNCTION_DSS1_CFG_INFO_TO_Q931      = $02;      //DSS1配置信息，        DSP->Q931
const  DSP_SUB_FUNCTION_DSS1_CONTROL_CMD_TO_DSP    = $03;      //DSS1控制命令          Q931->DSP
const  DSP_SUB_FUNCTION_DSS1_STATE_EVENT_TO_Q931   = $03;      //DSS1状态事件          DSP->Q931
const  DSP_SUB_FUNCTION_DSS1_SIGNAL_DATA_TO_DSP    = $04;      //DSS1信令数据          Q931->DSP
const  DSP_SUB_FUNCTION_DSS1_SIGNAL_DATA_TO_Q931   = $04;      //DSS1信令数据          DSP->Q931
const  DSP_SUB_FUNCTION_DSS1_DATA_REQ_TO_Q931      = $05;      //DSS1数据请求包        DSP->Q931
const  DSP_SUB_FUNCTION_DSS1_DEBUG_DATA_TO_Q931    = $06;      //DSS1调试信息包        DSP->Q931
//DSP DSS1子功能定义 end

//DSP 固件子功能定义
const  DSP_SUB_FUNCTION_FIRMWARE_READ_FLASH        = $01;      //读FLASH命令
const  DSP_SUB_FUNCTION_FIRMWARE_WRITE_FLASH       = $02;      //写FLASH命令
const  DSP_SUB_FUNCTION_FIRMWARE_ERASE_FLASH       = $03;      //擦除FLASH命令
const  DSP_SUB_FUNCTION_FIRMWARE_FINISH_FLASH      = $04;      //更新FLASH完成命令
const  DSP_SUB_FUNCTION_FIRMWARE_READ_SDRAM        = $06;      //读SDRAM命令
const  DSP_SUB_FUNCTION_REBOOT                     = $07;      //DSP重启命令
//DSP 固件子功能定义

//******************************************************************************

const  MEDIA_MAIN_FUNCTION_STREAMPLAY    = $01;           //流放音
//媒体功能模块功能ID定义***************************************
const  MEDIA_MAIN_FUNCTION_STREAMRECORD  = $02;           //流录音

//SS7信令功能模块功能ID定义***************************************
const  SS7_MAIN_FUNCTION_ISUP      = $01;           //七号信令
const  SS7_MAIN_FUNCTION_TUP       = $02;
const  SS7_MAIN_FUNCTION_SCCP      = $03;           //七号信令SCCP
const  SS7_MAIN_FUNCTION_LINK      = $10;           //七号信令链路
const  SS7_MAIN_FUNCTION_FLOW      = $11;           //流程标识交互

//PRI信令功能模块功能ID定义***************************************
const  PRI_MAIN_FUNCTION_Q931      = $01;           //Q.931信令


//配置模块功能ID定义***************************************

const  CONFIG_MAIN_FUNCTION_INIT        = $01;           //初始化模块
const  CONFIG_MAIN_FUNCTION_START       = $02;           //启动模块
const  CONFIG_MAIN_FUNCTION_STOP        = $03;           //停止模块
const  CONFIG_MAIN_FUNCTION_RELATE      = $04;           //关联模块
const  CONFIG_MAIN_FUNCTION_UNRELATE    = $05;           //停止关联模块
const  CONFIG_MAIN_FUNCTION_MONCONFIG   = $06;           //监视配置
const  CONFIG_MAIN_FUNCTION_MONSTART    = $07;           //监视启动
const  CONFIG_MAIN_FUNCTION_MONSTOP     = $08;           //监视停止
const  CONFIG_MAIN_FUNCTION_HEART       = $09;           //心跳包
const  CONFIG_MAIN_FUNCTION_VALIDITY    = $0A;           //系统连接验证包
const  CONFIG_MAIN_FUNCTION_RELEAT      = $0B;
const  CONFIG_MAIN_FUNCTION_HOTSTANDBY  = $0C;           //向模块发送的主从关系
const  CONFIG_MAIN_FUNCTION_HOTINFO     = $0D;           //向模块发送从模块信息
const  CONFIG_MAIN_FUNCTION_IPINFO      = $0E;           //向模块发送主IP信息
const  CONFIG_MAIN_FUNCTION_MODSTATE_REPORT    = $0F;
const  CONFIG_MAIN_FUNCTION_ADDNO2IP_NOTIFY    = $10;    //向VOIP模块发送添加第二IP信息

const  CONFIG_MAIN_FUNCTION_INTERFACE   = $10;           //界面模块发送过来的数据

const  CONFIG_MAIN_FUNCTION_USER        = $11;          //用户模块发送过来的数据
const  CONFIG_MAIN_FUNCTION_CFG         = $12;           //另一个配置管理发送过来的数据
const  CONFIG_MAIN_FUNCTION_SLAVE_WORK_NOTIFY  = $13;    //向FLOW模块发送备机正常工作通知消息


const CONFIG_SUB_FUNCTION_INTERFACE_REQALL      = $01;    //请求所有模块数据
const CONFIG_SUB_FUNCTION_INTERFACE_REQSINGAL   = $02;    //请求某个模块数据
const CONFIG_SUB_FUNCTION_INTERFACE_REQINIT     = $03;    //请求某个模块初始化包数据
const CONFIG_SUB_FUNCTION_INTERFACE_SETPARM     = $04;    //设置某个模块参数(例如IP,是否使能等)
const CONFIG_SUB_FUNCTION_INTERFACE_SETINIT     = $05;    //设置模块初始化包
const CONFIG_SUB_FUNCTION_INTERFACE_START       = $06;    //模块初始化和启动
const CONFIG_SUB_FUNCTION_INTERFACE_STOP        = $07;    //模块停止
const CONFIG_SUB_FUNCTION_INTERFACE_REQRELATE   = $08;    //请求模块关联信息
const CONFIG_SUB_FUNCTION_INTERFACE_TRANRELATE  = $09;    //模块关联信息
const CONFIG_SUB_FUNCTION_INTERFACE_ADD         = $0a;    //增加一个模块
const CONFIG_SUB_FUNCTION_INTERFACE_SUB         = $0b;    //删除一个模块
const CONFIG_SUB_FUNCTION_INTERFACE_PASSWORD    = $0c;       //发送系统名字和系统登陆密码

const CONFIG_SUB_FUNCTION_INTERFACE_REQRELATE_NEW   = $0d;    //请求模块关联信息(new)
const CONFIG_SUB_FUNCTION_INTERFACE_REQRELATE_ALL   = $0e;    //请求所有的模块关联信息
const CONFIG_SUB_FUNCTION_INTERFACE_HEART       = $10;   //心跳包

//配置模块间子功能定义
const CONFIG_SUB_FUNCTION_CFG_MODULE_INFO                 = $01;      //模块信息
const CONFIG_SUB_FUNCTION_CFG_SET_HOTSTANDBY              = $02;      //改变主从关系
const CONFIG_SUB_FUNCTION_CFG_REPLY_HOTSTANDBY            = $03;    //改变主从关系应答
const CONFIG_SUB_FUNCTION_CFG_HEART                       = $04;    //配置管理间的心跳包
//用户模块子功能定义
const CONFIG_SUB_FUNCTION_USER_REQALL      = $01;        //请求所有模块数据
const CONFIG_SUB_FUNCTION_USER_REQSINGAL   = $02;        //请求某个模块数据
const CONFIG_SUB_FUNCTION_USER_REQRELATE   = $03;        //请求某个模块关联信息

const CONFIG_SUB_FUNCTION_USER_SET_HOTSTANDBY   = $04;        //用户设置配置模块为主

const CONFIG_SUB_FUNCTION_READNODE				 = $01;	// 请求读节点信息 用法同界面主功能FACE_MAIN_FUNCTION_READNODE
const CONFIG_SUB_FUNCTION_GETCHANNELSTATE	 = $02;	// 请求获取通道状态
const CONFIG_SUB_FUNCTION_MODDOWNRELATE		 = $03;	// 请求mainmod框架下行关联
const CONFIG_SUB_FUNCTION_GETCHASSISINFO	 = $04;	// 请求DSP机框槽位信息

//界面模块功能ID定义***************************************
const FACE_MAIN_FUNCTION_REQNODE                = $01;    //请求节点定义
const FACE_MAIN_FUNCTION_READNODE               = $02;    //读节点数据
const FACE_MAIN_FUNCTION_WRITENODE              = $03;    //写节点数据
const FACE_MAIN_FUNCTION_SAVECONFIG             = $04;    //保存节点配置
const FACE_MAIN_FUNCTION_LOADCONFIG             = $05;    //转载节点配置
const FACE_MAIN_FUNCTION_LICENCE				        = $06;    //装载认证文件

const FACE_MAIN_FUNCTION_PROXY                  = $08;    //配置界面代理

const FACE_MAIN_FUNCTION_QUERY_CTBUS            = $0A;    //查询DSP通道CT-BUS号
const FACE_MAIN_FUNCTION_QUERY_SLOT             = $0B;    //查询DSP时隙连接关系


const FACE_SUB_FUNCTION_PROXY_ADDMODULE         = $01;   //通过代理增加一个模块
const FACE_SUB_FUNCTION_PROXY_SUBMODULE         = $02;   //通过代理删除一个模块
const FACE_SUB_FUNCTION_PROXY_GETMODULECONFIG		= $03;	 //通过代理获取一个模块配置文件内容
const FACE_SUB_FUNCTION_PROXY_SETMODULECONFIG		= $04;   //通过代理设置一个模块配置文件内容
const FACE_SUB_FUNCTION_PROXY_RESUMEMODULECONFIG= $05;   //通过代理恢复一个模块配置文件内容
const FACE_SUB_FUNCTION_PROXY_STOPALL					  = $06;	 //通过代理停止服务（为了覆盖当前所有配置）
const FACE_SUB_FUNCTION_PROXY_SAVECFGFILE				= $07;	 //通过代理保存配置文件
const FACE_SUB_FUNCTION_PROXY_STARTALL				  = $08;	 //通过代理启动服务（= $06的反操作）
const FACE_SUB_FUNCTION_PROXY_GET_LOGMODCONFIG  = $09;	 //通过代理获取日志server配置
const FACE_SUB_FUNCTION_PROXY_SET_LOGMODCONFIG  = $0a;	 //通过代理设置日志server配置
const FACE_SUB_FUNCTION_PROXY_GET_LOGMODINFO    = $0b;	 //通过代理获取日志server信息
const FACE_SUB_FUNCTION_PROXY_RESETMODULE       = $0c;   //通过代理重启模块
const FACE_MAIN_FUNCTION_HEART                  = $09;   //界面的心跳包

//hn add for get link status at 20081212
const FACE_MAIN_FUNCTION_QUERY_LINK_STATUS    = $0a;    //查询时隙连接状态
const FACE_SUB_FUNCTION_QUERY_UPLINK          = $01;    //查询上联的时隙连接关系
const FACE_SUB_FUNCTION_QUERY_DOWNLINK        = $02;    //查询下拉的时隙连接关系

//end add
//流程执行模块功能ID定义*************************************
const  CTX_MAIN_FUNCTION_CTXCMD                = $FA;	   //交换中心命令
//流程执行模块子功能ID定义*************************************
const  CTX_SUB_FUNCTION_CTXREG                 = $01;     //ACS发送交换中心注册命令
const  CTX_SUB_FUNCTION_CTXLINK                = $02;     //ACS发送交换中心Link命令
const  CTX_SUB_FUNCTION_CTXAPPDATA             = $03;     //ACS发送注册交换中AppData心命令
const  CTX_SUB_FUNCTION_REPORTSLOT             = $07;     //流程模块向交换中心发送DSP信息

//流程执行模块功能ID定义*************************************
const  FLOW_MAIN_FUNCTION_SYNCMD                = $FB;	   //流程同步命令
//流程执行模块功能ID定义:流程事件*************************************
const  FLOW_MAIN_FUNCTION_ACSEVT                = $FC;	   //流程事件
const  FLOW_SUB_FUNCTION_MASTER_STATE           = $01;     //ACS上报Master状态事件
const  FLOW_SUB_FUNCTION_SLAVE_WORK_STATE       = $02;     //ACS上报Slave Work状态事件


//流程执行模块功能ID定义:流程命令*************************************
const  FLOW_MAIN_FUNCTION_ACSCMD                = $FD;	   //流程命令
const  FLOW_MAIN_FUNCTION_TIMEREVT              = $FE;	   //定时器事件
const  MOD_MAIN_FUNCTION_MODHEART               = $FF;	   //各模块之间的心跳包

//流程执行模块子功能ID定义*************************************
const  FLOW_SUB_FUNCTION_INTERCMD               = $01;     //流程内部命令
const  FLOW_SUB_FUNCTION_REQDEVICE              = $02;     //ACS请求资源列表
const  FLOW_SUB_FUNCTION_OPENDEVICE             = $03;     //ACS打开设备
const  FLOW_SUB_FUNCTION_CLOSEDEVICE            = $04;     //ACS关闭设备
const  FLOW_SUB_FUNCTION_RESETDEVICE            = $05;     //ACS复位设备
const  FLOW_SUB_FUNCTION_GETDEVSTATE            = $06;     //ACS获取设备状态
const  FLOW_SUB_FUNCTION_SETDEVGROUP            = $07;     //ACS设置资源组号
const  FLOW_SUB_FUNCTION_SETPARAM               = $08;     //ACS设置参数
const  FLOW_SUB_FUNCTION_GETPARAM               = $09;     //ACS设置参数 ...
const  FLOW_SUB_FUNCTION_MAKECALLOUT            = $0A;     //ACS发起呼叫
const  FLOW_SUB_FUNCTION_ALERTCALL              = $0B;     //ACS Alert呼叫
const  FLOW_SUB_FUNCTION_ANSWERCALLIN           = $0C;     //ACS应答呼入
const  FLOW_SUB_FUNCTION_LINKDEV                = $0D;     //ACS连接设备
const  FLOW_SUB_FUNCTION_UNLINKDEV              = $0E;     //ACS拆除设备连接
const  FLOW_SUB_FUNCTION_CLEARCALL              = $0F;     //ACS清除呼叫
const  FLOW_SUB_FUNCTION_JOINTOCONF             = $10;     //ACS加入会议
const  FLOW_SUB_FUNCTION_LEAVEFROMCONF          = $11;     //ACS离开会议
const  FLOW_SUB_FUNCTION_CLEARCONF              = $12;     //ACS删除会议
const  FLOW_SUB_FUNCTION_PLAYFILE               = $13;     //ACS放音
const  FLOW_SUB_FUNCTION_INITPLAYINDEX          = $14;     //ACS初始化索引
const  FLOW_SUB_FUNCTION_BUILDINDEX             = $15;     //ACS建立放音索引
const  FLOW_SUB_FUNCTION_CONTROLPLAY            = $16;     //ACS控制放音
const  FLOW_SUB_FUNCTION_RECORDFILE             = $17;    //ACS录音
const  FLOW_SUB_FUNCTION_CONTROLRECORD          = $18;     //ACS控制录音
const  FLOW_SUB_FUNCTION_SENDFAX                = $19;     //ACS发送传真
const  FLOW_SUB_FUNCTION_STOPSENDFAX            = $1A;     //ACS停止发送传真
const  FLOW_SUB_FUNCTION_RECVFAX                = $1B;     //ACS接收传真
const  FLOW_SUB_FUNCTION_STOPRECVFAX            = $1C;     //ACS停止接收传真
const  FLOW_SUB_FUNCTION_CHANGEMONITORFILTER    = $1D;     //ACS改变事件filter
const  FLOW_SUB_FUNCTION_SENDIODATA             = $1E;     //ACS发送IO数据
const  FLOW_SUB_FUNCTION_SENDSIGMSG             = $1F;     //ACS发送信令消息
const  FLOW_SUB_FUNCTION_RECORDCSP              = $20;     //ACS内存录音
const  FLOW_SUB_FUNCTION_CONTROLRECORDCSP       = $21;     //ACS控制内存录音
const  ACS_SUB_FUNCTION_DBGON                   = $22;     //调试使能
const  ACS_SUB_FUNCTION_DBGOFF                  = $23;     //调试禁止
const  FLOW_SUB_FUNCTION_PLAY3GPP               = $24;     //播放3gpp
const  FLOW_SUB_FUNCTION_CONTROLPLAY3GPP        = $25;     //控制播放3gpp
const  FLOW_SUB_FUNCTION_RECORD3GPP             = $26;     //播放3gpp
const  FLOW_SUB_FUNCTION_CONTROLRECORD3GPP      = $27;     //控制播放3gpp
const  FLOW_SUB_FUNCTION_PLAYCSP                = $28;     //ACS启动CSP放音
const  FLOW_SUB_FUNCTION_SENDPLAYCSP            = $29;     //ACS发送CSP放音数据
const  FLOW_SUB_FUNCTION_CTXREG                 = $2A;     //ACS发送Ctx Reg事件
const  FLOW_SUB_FUNCTION_CTXLINK                = $2B;     //ACS发送CTX Link事件
const  FLOW_SUB_FUNCTION_CTXAPPDATA             = $2C;     //ACS发送CTX AppData事件
const  FLOW_SUB_FUNCTION_LICQUERY               = $2E;     //ACS发送License query
const  FLOW_SUB_FUNCTION_LINKQUERY              = $2F;     //ACS发送Link query
const  FLOW_SUB_FUNCTION_INIT3GPPINDEX          = $30;     //ACS初始化3gpp索引
const  FLOW_SUB_FUNCTION_BUILD3GPPINDEX         = $31;     //ACS建立3gpp索引
const  FLOW_SUB_FUNCTION_SENDRAWFRAME           = $32;     //ACS发送原始Frame数据
const  FLOW_SUB_FUNCTION_JOIN3GCONF             = $33;     //ACS发送加入3G会议
const  FLOW_SUB_FUNCTION_LEAVE3GCONF            = $34;     //ACS发送离开3G会议
const  FLOW_SUB_FUNCTION_CLEAR3GCONF            = $35;     //ACS发送清除3G会议
const  FLOW_SUB_FUNCTION_GET3GCONFLAYOUT        = $36;     //ACS发送获取3G会议Layout
const  FLOW_SUB_FUNCTION_SET3GCONFLAYOUT        = $37;     //ACS发送设置3G会议Layout
const  FLOW_SUB_FUNCTION_GET3GCONFVISABLE       = $38;     //ACS发送获取3G会议visable
const  FLOW_SUB_FUNCTION_SET3GCONFVISABLE       = $39;     //ACS发送设置3G会议visable
const  FLOW_SUB_FUNCTION_RESTART3GCONF          = $3A;     //ACS发送重启3G会议
const  FLOW_SUB_FUNCTION_SETMASTER              = $3B;     //ACS设置Master命令
const  ACS_SUB_FUNCTION_TRAPEN                  = $40;     //监控
const  FLOW_SUB_FUNCTION_BAKSYSSTART            = $50;     //ACS发送BakSysStart事件
const  FLOW_SUB_FUNCTION_VOIPMONDATA            = $51;     //ACS发送VoIP数据
const  FLOW_SUB_FUNCTION_SYNDATA                = $FC;     //主从流程模块之间的数据
const  FLOW_SUB_FUNCTION_MASTERCHG              = $FE;     //发送主从状态事件
const  FLOW_SUB_FUNCTION_RESETCHAN              = $FF;     //发送复位通道事件


//IP信令模块功能ID定义*******************************************

//faxTiff模块主功能
const FAXTIFF_MAIN_FUNCTION_CHANGE  = $01;

//faxTiff模块子功能
//命令包定义
const FAXTIFF_SUB_FUNCTION_CHANGE_DECOMPOSE	= $01;  //分解
const FAXTIFF_SUB_FUNCTION_CHANGE_COMPOSE	  = $02;  //合成
const FAXTIFF_SUB_FUNCTION_PAGE_REQ		      = $03;  //分解页请求
const FAXTIFF_SUB_FUNCTION_TRANS_CONTROL    = $04;  //转换控制
const FAXTIFF_SUB_FUNCTION_TRANS_ADDFILE	  = $05;  //增加文件
const FAXTIFF_SUB_FUNCTION_TRANS_ADDHEADER  = $06;  //增加传真头
const FAXTIFF_SUB_FUNCTION_TRANS_INIT		    = $07;  //初始化

//事件包定义
const FAXTIFF_SUB_FUNCTION_DECOMPOSE_RESULT	= $01;  //分解结果
const FAXTIFF_SUB_FUNCTION_COMPOSE_RESULT	  = $02;  //合成结果
const FAXTIFF_SUB_FUNCTION_TRANS_STATE	    = $03;  //转换状态
const FAXTIFF_SUB_FUNCTION_LOCALFORMAT	    = $04;  //本地格式
//****************************************************************

const MEDIAEX_MAIN_FUNCTION_REPORT_RTPPORT   = $01;
const MEDIAEX_SUB_FUNCTION_REPORT_RTPPORT    = $02;

implementation

end.
