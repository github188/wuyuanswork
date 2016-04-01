//IPCAM_SysConfig.h

#ifndef __IPCAM_SYSCONFIG__
#define __IPCAM_SYSCONFIG__
#include "IPCAM_SysQueue.h"

#define MAX_MV_REGION                   4     //移动侦测区域个数
#define MAX_WEEK_NUM			        7     //最大星期数;
#define MAX_TIMESECTION_NUM             3     //时间段最大个数
#define MAX_CHANNEL_NUM                 4     //最大通道数
#define MAX_USER_NUM                    10    //最大可注册的用户数量
#define MAX_PTZ_SCRIPT_NUM              2     //最多可存放PTZ脚本数量

#define PTZ_SCRIPT_DIR                 "ptz/"//	"ptz-script" //云台脚本目录

#define APP_TOP_DIR                     "/sys_app/"

#define SYSTEM_DEFAULT_FILE 		   "/mnt/mtd/ndvr/"


typedef struct {
	short left;
	short right;
	short top;
	short bottom;
}NDVRRECT;

typedef struct _IPCAM_MVCONFIG{
	short lev          [MAX_MV_REGION];
	char  isActive     [MAX_MV_REGION];
	NDVRRECT rect      [MAX_MV_REGION];
}IPCAM_CONFIGMV,*LPIPCAM_CONFIGMV;


/////////////////厂家参数/////////////////////////////////////////////////////
typedef struct tagCFGFACTORY
{
    CHAR        strDevName[24];            //显示名称
	CHAR		strFactoryName[32];		   //厂家名称
	CHAR       	strDevSerialNumb[64];      //出厂序列号
    CHAR        strDevRegcode[26];         //设备注册码
	CHAR		strDevVer[16];			  //设备CPU 类型
	CHAR		strHardVer[64];			  //硬件版本号
	CHAR		strSoftVer[64];			  //软件版本号
	
}CFG_FACTORYINFO,*LPCFG_FACTORYINFO;
////////////////用户管理////////////////////////////////
typedef enum{
 PRIV_ROOT    =0,                           //厂家账户,不能改名也不能改密码，全权限
 PRIV_ADMIN   =1,                           //管理员账户，不能改名但可修改密码，全权限
 PRIV_GUEST   =2,                           //普通账户
}ENU_USERPRIV;
typedef struct{	
     CHAR         userName[16];       	     //用户名称  有一个厂家用户，不提供给用户，不能被修改，另外有多个管理员用户，其余为普通用户
     USHORT       UserID;
	 CHAR         userPassword[16];          //用户密码
	 CHAR         Priority;           		 //用户权限规定为3级   0:1:2   0权限只有一个超级用户 1:管理员权限可以有多个 2 浏览权限挥衋dmin用户有管理权限
     CHAR         Enable;             		 //用户使能
}CFG_USERS,*LPCFG_USERS;
typedef struct{	
	USHORT        UserCount;
	CFG_USERS     User[MAX_USER_NUM];
}CFG_USERINFO,*LPCFG_USERINFO;
/////////////////网络参数//////////////////////////////////////////////////////

typedef	enum{
		WIFFWEPCLOSE=0,
		WIFFWEP64   =1,
		WIFFWEP128  =2,
		WIFFWPA_PSK =3,
		WIFFWPA2_PSK=4
}ENU_WIFFWEPTYPE;
typedef enum{
		WIFFMANAGED     =0,
		WIFFPOINTTOPOINT=1
}ENU_WIFFISHOST;
typedef	enum{
        NETPARAM_IP_MODE 	=0,
        NETPARAM_DHCP_MODE 	=1,
        NETPARAM_PPPOE_MODE =2
}ENU_IPFETCHMODE;

typedef struct{
	UCHAR   SevName[64];
	UCHAR   UsrName[32];
	UCHAR   UsrPwd[32];

}DDNSSERVER;
typedef enum {
	UNENABLE 	= 0,		//使能开关 关闭状态
	ENABLE		= 1			//使能开关 打开状态
}ENU_ENABLESINGEL;

typedef struct tagCFGNETINFO
{
	//中英文
	INT		LanguageType ;	
	//网络参数
	UCHAR	NetIpFetchMode;	    //IP地址获取方式，ENU_IPFETCHMODE
	CHAR	NetIpAddr[16];		//IP 地址
	CHAR	NetHostName[24];    //主机名
	CHAR	NetGwAddr[16];		//gateway
	CHAR	NetSubMask[16];		//net mask
	CHAR	NetMacAddr[24];		//MAC addr
	SHORT	NetDnsEnable;		//使能DNS
	CHAR   NetDnsSvI [16];      //DNS 
	CHAR   NetDnsSvII[16];
	USHORT  NetDhcpTimeInterval;	 //dhcp检查间隔 小时
	
    //系统服务端口
	USHORT	NetWebPort;			//系统WEB服务端口
	USHORT	NetRtspPort;		//系统RTSP流端口
	USHORT  NetServerPort;      //系统服务转发端口
	USHORT  NetDataPort;		//系统私有协议服务端口
	USHORT  NetOnvifPort;		//onvif server port 
	
    //WIFI  配置
    UCHAR   WifiIsHost;         //ENU_WIFFISHOST
	UCHAR   WifiEncryptType;	//ENU_WIFFWEPTYPE
	UCHAR   WifiPassword[130];  //65 修改为128位支持
	UCHAR   WifiSsid[50];
	UCHAR   WifiKeySystem;		//0:十六进制  1:ASCII
	//PPOE 参数
	CHAR   PpoeEnable;
    CHAR   PpoeName[50];
	CHAR   PpoePassword [50];
	CHAR   PppoeIp[64];
	//DDNS 参数
    CHAR   DdnsEnable;           //使能DDNS
	CHAR   DdnsSevIndex;         //服务器类型
    USHORT DdnsTimeInterval;     //ddns时间间隔 分钟
    DDNSSERVER DdnsServerList[4];//可用的DDNS服务器表
    //NTP  参数
    UCHAR  NtpEnable;
	UCHAR  NtpSevIndex;			//标记启用哪个服务器
	CHAR  NtpServer[2][50];
	USHORT NtpPort;
	SHORT  NtpTimeZone;
	USHORT NtpTimeInterval;		 //ntp时间间隔 小时
	UINT   NtpSysTime;
	
	//UPNP 参数
	CHAR   UpnpEnable;
	//Rtsp 参数
	CHAR   RtspEnable;
	CHAR   RtspPasswdAuth;

}CFG_NETINFO,*LPCFG_NETINFO;
//////////////视频参数///////////////////////////////////

typedef enum
{
	ENC_RCLEVEL1	= 0,
	ENC_RCLEVEL2	= 1,
	ENC_RCLEVEL3	= 2,
	ENC_RCLEVEL4	= 3,
	ENC_RCLEVEL5	= 4,
	ENC_RCLEVEL6	= 5,
	ENC_RCLEVEL7	= 6,
	ENC_RCLEVEL8	= 7,
	ENC_RCLEVEL9	= 8,
	ENC_RCLEVEL10	= 9,
	ENC_RCLEVEL11	=10,
	ENC_RCLEVEL12	=11,
	ENC_RCLEVEL_NUM,
}ENU_RCLEVEL;                            //率控级别,值对应CBR 不同设定码率，VBR 不同质量
typedef enum
{
	//ENC_OFF = 0,
	ENC_VBR = 0,
	ENC_CBR	= 1,

}ENU_RCTYPE;                             //率控
typedef enum
{
    ENC_JPEG  = 0,
	ENC_MPEG4 = 1,
	ENC_AVC   = 2,

}ENU_ECNTYPE;                            //编码方式
typedef enum
{
	DISPLAY_OFF  = 0,
	DISPLAY_NTSC = 1,
	DISPLAY_PAL  = 2,	
}DISPLAY_TYPE;                           //制式
//0:disable, 1:NTSC, 2:PAL

typedef enum
{
	ENC_RSLEVEL_PAL_QCIF   = 0,
	ENC_RSLEVEL_PAL_CIF    = 1,
	ENC_RSLEVEL_PAL_D1     = 2,
	ENC_RSLEVEL_NTSC_QCIF  = 3,
	ENC_RSLEVEL_NTSC_CIF   = 4,
	ENC_RSLEVEL_NTSC_D1    = 5,
	ENC_RSLEVEL_CMOS_QQVGA = 6,            //直连CCD 使用相同分辨率解析
	ENC_RSLEVEL_CMOS_QVGA  = 7,
	ENC_RSLEVEL_CMOS_VGA   = 8,
	ENC_RSLEVEL_CMOS_720P  = 9,
	ENC_RSLEVEL_CMOS_960P  =10,	
	ENC_RSLEVEL_CMOS_1204P =11,	
	ENC_RSLEVEL_CMOS_1080P =12,	
	ENC_RSLEVEL_NUM,
}ENU_RSLEVEL;                              //分辨率分级
typedef enum{
    ENC_FPS_01             = 0,            //1fps
    ENC_FPS_02             = 1,            //6 fps
    ENC_FPS_03             = 2,            //10fps
    ENC_FPS_04             = 3,            //15fps
    ENC_FPS_05             = 4,            //20fps
    ENC_FPS_06             = 5,            //25fps
    ENC_FPS_07             = 6,            //30fps
    
}ENU_FRAMERATELEVEL;                      //帧率级别
typedef enum{
  VIDEO_POWER_50HZ = 50,
  VIDEO_POWER_60HZ = 60,
}ENU_VIDEOPOWERMODE;
typedef struct{
	 UINT	Resolution;		                //分辨率模式值               : ENU_RSLEVEL
	 UINT	FrameRate;			            //帧率
	 UINT	nBitRate;						//码率	 
	 UCHAR	RcMode;		                    //率控 .CBR或VBR	         : ENU_ENCRCTYPE
	 UINT 	RcLevel;		                //率控 .CBR或VBR等级ENU_ENCRCLEVEL
	 UCHAR 	IsVideo;		                //video open
	 UCHAR  IsMjpeg;                        //串流附加Jpeg流
	 UCHAR  EncType;                        //编码类型=ENC_TYPE_AVC etc..:ENU_ECNTYPE

}VIDEOSTREAMSET;

typedef struct {
	 UCHAR             bEnable;     //使用遮盖
	 UCHAR 			   strName[24]; //遮盖名称
	 UCHAR			   nX0; 		//坐标百分比[0-100]
	 UCHAR 			   nY0;   		//坐标百分比[0-100]
	 UCHAR 			   nX1;   		//坐标百分比[0-100]
	 UCHAR 			   nY1;  		//坐标百分比[0-100]
}VIDEOMASK,*LPVIDEOMASK;


typedef struct {
	 UCHAR             bEnable;     //使用IRCUT
	 UCHAR 			   nMode;   	//使用IRCUT 模式
	 UINT			   nTime1; 		//使用开始时间
	 UINT 			   nTime2;   	//使用结束时间
}VIDEOIRCUT,*LPVIDEOIRCUT;


typedef enum{
	IRCUT_TIMER = 0,
	IRCUT_DAYTIME,
	IRCUT_NIGHTTIME,
	IRCUT_AUTO,
}VIDEO_IRCUTMODE;

typedef enum {
	ENCPROFILE_BASE      =0,
	ENCPROFILE_MAIN		 =1,
	ENCPROFILE_HIGH      =2,
}ENU_PROFILETYPE;

typedef enum {
	SERNSOR_MOD_DAY 	= 0,
	SERNSOR_MOD_NIGHT	= 1,
}ENU_DAYNIGHT;

typedef enum {
	SERNSOR_MOD_INDOOR 	= 0,
	SERNSOR_MOD_OUTDOOR	= 1,
	SERNSOR_MOD_AUTO	= 2,
}ENU_OUTDOOR;


typedef struct tagCFGVIDEOINFO
{
	 //Sernsor 特性
	 UCHAR			   bzDayNight;			// 0 : night mode 	1: day mode
	 //自动白平衡
	 UCHAR			   bWhiteBalance;		// 0 : indoor	1: outdoor	2: Auto


	 INT 			   nSernsorType;		//ENU_CAPTURETYPE 是什么类型sernsor
	 ///是属于
	 UCHAR			   bSernsorMode;		//
	 ////3a是否启动
	 UCHAR			   bAwebEnable;			//开启是否启动自动白平衡
 
	 //视频画面特性
	 UCHAR			bzBright;			//亮度
	 UCHAR			bzContrast;		    //对比度
	 UCHAR			bzSaturation;		//饱和度
	 
	 UCHAR 			   bzBackLight;			// median=128 ,hight>128, low<128  
	 UCHAR			   bzSharpness;			// median=128 ,hight>128, low<128  
	 
	 
     //视频输入电气特性
	 UCHAR             FlipVertical;        //垂直翻转(特点输入头可用)
	 UCHAR             FlipHorizontal;      //水平翻转(特点输入头可用)
	 UCHAR             FreqPower;           //电源频率(50hz/60hz ,特定输入头使用)

	 UCHAR			bMainStream;			///1表示主码流  0表示子码流 

	 //视频OSD参数设置
	 INT               OsdIsEnableTime;     //开时间显示
	 INT               OsdIsEnableName;     //开设备名称(设备位置显示)
	 BOOL              OsdIsEnglish   ;     //OSD 使用英文标注时间
	 
	 //视频复合视屏设置
	 UCHAR			   CompositeVideo;      //0:关闭 1:NTSC 2:PAL
	 //视频遮盖
	 VIDEOMASK         VideoMask[4];     	//使用遮盖4个区域	 
     //视频通道设定
	VIDEOSTREAMSET	   ChannelInfo[4];      //视频通道参数video_set[4];			// 0 ~ 3
	VIDEOIRCUT		   VideoIrCut;
	//encode profile
	ENU_PROFILETYPE	   EncProfileType;	////0 =baseline , 1 =mainline, 2 =highline
}CFG_VIDEOINFO,*LPCFG_VIDEOINFO;

typedef enum {//与IPCAM_NetCommunication.h文件匹配
	ENU_AUDIO_PCM8X8K	 	=6,
	ENU_AUDIO_PCM16X8K	 	=7,
	ENU_AUDIO_ADPCM16X8K  	=8,
	ENU_AUDIO_AMR16X8K	 	=9,
	ENU_AUDIO_G711UL 	 	=10,
	ENU_AUDIO_G711AL 	 	=11,
	ENU_AUDIO_AAC		 	=12,
}ENU_AUDIOENCODE;				// 音频压缩类型


////////////////音频参数//////////////////////////////////
typedef struct _IPCAM_AUDIOCONFIG{
    UCHAR  bzAudioEnable;                   //音频使能
    UCHAR  bzAiType;						
	UCHAR  bzEncodeType; 	                //音频压缩类型 默认10    ENU_AUDIOENCODE
	UCHAR  bzSampleSize; 	                //采样宽度：8 ， 16 ， 32 
	UCHAR  usSampleSpeed; 	                //采样频率：8K 
	UCHAR  bzStereo;  		                ////1表示立体声 0 表示单声道
} CFG_AUDIOINFO, *LPCFG_AUDIOINFO;
////////////////云台控制/////////////////////////////////
typedef struct { 	
	UCHAR          ptzName[48];             //云台脚本文件名称
	UCHAR          address;
    UCHAR          speed;
}CFG_PTZ,*LPCFG_PTZ;

////////////////本地录像////////////////////////////////
typedef struct {
	UCHAR         hour;
	UCHAR         minute;
	UCHAR         second;
}RECTIME,*LPRECTIME;
typedef struct{
  	CHAR           isOpen;                   //启用当前时间段//
	RECTIME        startTime;	             // the section 1 start time//
	RECTIME        endTime;		             //the section 1 end time/
} RECTIMESET,*LPRECTIMESET;

typedef struct{
	UCHAR        timeCheckType ;              //类型，0,时间段，1,全天///
	RECTIMESET   recordTime[MAX_TIMESECTION_NUM];//三个时间段
}RECPARAMTER,*LPRECPARAMTER;

typedef struct {
	UCHAR TmRecEnable;
	ULONG TmRecStart;
	ULONG TmRecEnd;
}TMRECTIME;
typedef struct {
	TMRECTIME TmRecDay[3];
}TMRECDAYTIME;
typedef struct tagCFGRECORDINFO
{
	UCHAR   RecEnable;
    UCHAR   RecFullCover;                    //占满覆盖 sd卡存储已满，是否删除旧文件
	UCHAR   RecCheckByIoAlarm;
	UCHAR   RecCheckByMoAlarm;
    UCHAR   RecDevisionType;                 //0:按尺寸存 1:按时间存
    UCHAR   RecDevisionValue;                //0:5 1:10 2:15 3:20
	RECPARAMTER timeParamSet[MAX_WEEK_NUM];
	TMRECDAYTIME RecTimer[MAX_WEEK_NUM];
}CFG_RECORDINFO, *LPCFG_RECORDINFO;
///////////////报警处理/////////////////////////////////////
typedef struct{
	INT    IsEnable;
	time_t TmBegin;
	time_t TmEnd;
}MOTMSECTION;
typedef struct {
	USHORT map;
}IOMAPINFO,*PIOMAPINFO;
typedef struct{
	UCHAR 	IsSendtoSd; 
	UCHAR   IsSendtoMail;			              //是否发送到邮件
	UCHAR   IsSendtoFtp;			              //是否发送到ftp
}MOTIONDATECTGRAB;


typedef struct {
	 UCHAR			   nX0; 		//坐标百分比[0-100]
	 UCHAR 			   nY0;   		//坐标百分比[0-100]
	 UCHAR 			   nX1;   		//坐标百分比[0-100]
	 UCHAR 			   nY1;  		//坐标百分比[0-100]
}MDAREA;

typedef struct {
	 UCHAR 	mdIsOpen;		                      //移动侦测区域开闭状态0~关闭,1~开启 （位表示 b001,b011,b111 etc）
	 CHAR	mdAreaName[24];						  //移动侦测区域命名
	 UCHAR	mdSensitive;	                      //移动侦测灵敏度：0~32
	 MDAREA	mdArea;								  //移动侦测区域范围
}MOTIONDETECTION,*LPMOTIONDETECTION;
	
typedef struct tagCFGALARMINFO
{

	 MOTIONDETECTION 		MotiDetection[4]; 
	 UCHAR  				mdEnableTmSection   ;           //移动侦测时间段
     MOTMSECTION   			mdTmSectionCheck[MAX_WEEK_NUM];	//时段检查按周制

     UCHAR 					IoAlarmEnable;              //使能IO报警
     UCHAR 					IoAlarmCheckInterval;       //IO报警间隔时间

	 IOMAPINFO     			IoMap[16];	                // I/O relation policy      //IO联动映射
	 IOMAPINFO     			MoMap;                      // move i/O  relation 
	 
     //报警后处理
	 USHORT            		GrabNum;			        //连续抓拍图片张数  0:不抓拍
     USHORT            		GrabIntervalTime;          	//抓拍间隔时间

	 USHORT 				VideoTime;					//录制视频时长 单位分 0:表示不录制
	 USHORT 				VideoChannel;				//0 主码流  1 次码流		

	 MOTIONDATECTGRAB  		GrabRecordInfo[2];          //抓拍记录及上传服务器相关配置 0:grab picture    1: grab video

}CFG_ALARMINFO,*LPCFG_ALARMINFO;
/////////////////上传服务////////////////////////////////
#define MAX_UPLOAD_SERVERS 2

typedef enum {
PORT_FTPTYPE	= 0,
PASV_FTPTYPE    = 1
}ENU_FTPSERVEICETYPE;

typedef struct{
	CHAR    ServerName[64];
	USHORT  ServerPort;
	CHAR    UserName[32];
	CHAR    Password[32];
	CHAR    ServerType;
}UPLOAD_FTPSERVER;
typedef struct{
	CHAR ServerName[64];
	USHORT ServerPort;
	CHAR UserName[32];
	CHAR Password[32];
	CHAR MailFrom[64];          
	CHAR MailTo[64];
}UPLOAD_MAILSERVER;

typedef struct{
   CHAR Enable;
   time_t t_start;
   time_t t_end;
}JPEG_SEND_DATEINFO;
typedef struct tagCFGUPLOADINFO
{ 
	//ftp 服务器上传相关
	 UCHAR             FtpEnable;
     UCHAR             FtpType;		//ENU_FtpServiceType
	 UPLOAD_FTPSERVER  FtpServerList[MAX_UPLOAD_SERVERS];

     //MAIL服务器上传相关
     UCHAR             MailEnable;
     UPLOAD_MAILSERVER MailServerList[MAX_UPLOAD_SERVERS];
     //图像定时上传相关
	 UCHAR              JpgTimeSendEnable;
	 UCHAR 	            JpgTimeSendEnableByDay;
	 SHORT              JpgTimeSendInterval;
	 JPEG_SEND_DATEINFO JpgTimeSendTmCheck[7];

}CFG_UPLOADINFO,*LPCFG_UPLOADINFO;
////////////////////////////////////////////////////////


//自动维护
typedef struct tarCFG_AUTOMAINTAININFO
{
	UCHAR			  AutoRebootEnable;
	UCHAR			  Day;
	RECTIME			  Time;	
}CFG_AUTOMAINTAININFO, *LPCFG_AUTOMAINTAININFO;


typedef struct  _IPCAM_SYSCONFIG{
    CFG_FACTORYINFO                    ConfigFactory;
  	CFG_USERINFO            	       ConfigUser;
    CFG_NETINFO                        ConfigNet;
    CFG_VIDEOINFO   	               ConfigVideo;
	CFG_AUDIOINFO                      ConfigAudio;
	CFG_PTZ            	               ConfigPtz;
	CFG_RECORDINFO          	       ConfigRecord;
    CFG_ALARMINFO                      ConfigAlarm;
    CFG_UPLOADINFO                     ConfigUpload;
	CFG_AUTOMAINTAININFO 			   ConfigAutoMaintain;
} IPCAM_SYSCONFIG ,*LPIPCAM_SYSCONFIG; 


#endif


