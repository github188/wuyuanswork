//IPCAM_NetCommunicationT.h
/*##############################################################################
#工程描述:
#       IP网络摄像机
#
#文件描述:
#      网络摄像机协议接口。
#      该部分协议对应结构为设备和客户端共有，客户端SDK原则上只需要支持最重要的网
#      络、流媒体、云台控制及产品信息即可，其他参数部分应尽可能在CGI参数接口里面
#      提供。
# 
#作者信息:
#         创建
#版权信息:
#       Copyright(c) 2008~201x 
#  	   All rights reserved.
#注意    :
#      这个文件为IPCAM 与PC SDK 共享文档，修改要注意不要引用系统其他部分定义量
#      增加定义注意规范。 
###############################################################################*/
#ifndef IPCAM_NET_COMMUNICATIONT_H
#define IPCAM_NET_COMMUNICATIONT_H


typedef struct 
{
	UCHAR       		devModel[20];               //出厂型号
	UCHAR				devSerialNumb[64];          //出厂编号
    UCHAR       		devRegcode[26];             //设备注册码
	CHAR				devName[24];                //设备显示名称
	CHAR				szFactoryName[32];			//厂家名称
}T_IPCFACTORYPARAM;

typedef struct 
{
	USHORT          AbiVideoChannels;      			//视频路数
	USHORT          AbiVideoSubMedia;      			//是否支持次子码率
	USHORT		    AbiAudioChannels;      			//音频路数
    USHORT          AbiVideoEncodeType;    			//保留

	USHORT          AbiVideoMax_X   ;      			//视频最大横向分辨率
	USHORT          AbiVideoMax_Y   ;      			//视频最大纵向分辨率
	ULONG           AbiVideoResultion[32];   		//主码流视频分别率（高16位宽，低16位高）
    ULONG       	AbiVideoResultionSub[32];		//次码流视频分别率（高16位宽，低16位高）
	USHORT          AbiIoAlarmInSize;      			//IO报警输入个数
	USHORT          AbiIoAlarmOutSize;     			//IO报警输出个数
	
}T_IPCABILITYYPARAM;
//网络
typedef struct{
	UCHAR			ipFetchMode;	       //静态IP或者动态DHCP分配IP
	UCHAR			ipAddr    [24];		   //IP 地址
	UCHAR			gwAddr    [24];		   //网关
	UCHAR			netMask   [24];		   //子网掩码
	UCHAR			macAddr   [24];		   //MAC 地址
	UCHAR           NetDnsSvI [16];        //DNS 
	UCHAR           NetDnsSvII[16];
	UCHAR           HostName  [16];        //主机名
}T_IPCNETPARAM;

typedef struct{
	UCHAR          channel;                //通道号
	UCHAR          videoType;              //视频制式PAL, N 制,(IPC不使用该域)
	UCHAR	       frameRate;			   //帧率
	UCHAR          rateType;               //VBR CBR
	UCHAR 	       rateLevel;		       //画质或者码流级别  分5个级别     
}T_IPCVIDEOPARAM;

typedef struct{
	UCHAR           channel;               //通道号
	UINT	        bright;			       //亮度
	UINT	        contrast;		       //对比度
	UINT	        saturation;		       //饱和度
	UINT		 sharpness;			//锐度
}T_IPCPICTUERPARAM;
typedef struct {
    UCHAR           channel;
    UCHAR           bzAiType;              //输入方式:0 mic,1 line
	UCHAR           bzEncodeType; 	       //音频压缩类型 默认0 
	UCHAR           bzSampleSize; 	       //采样宽度：8 ， 16 ， 32 
	UCHAR           usSampleSpeed; 	       //采样频率：8K 
	UCHAR           bzStereo;  		       ////1表示立体声 0 表示单声道
} T_IPCAUDIOPARAM;
typedef struct {
    UCHAR           channel;
    UINT            uzTime ;               //本地时间
	 INT            uzTimeZone;            //时区
	UINT            uzIsUsedNtp;           //0=FALSE 1:TRUE
	CHAR            NtpServer[64];         //指定时间服务器
} T_IPCTIMEPARAM;
typedef enum
{
	OSD_POZITON_NULL    =0,
	OSD_POZITON_LEFTTOP   ,
	OSD_POZITON_MIDTOP    ,
	OSD_POZITON_RIGHTTOP  ,
	OSD_POZITON_LEFTMID   ,
	OSD_POZITON_MIDMID    ,
	OSD_POZITON_RIGHTMID  ,
	OSD_POZITON_LEFTBOTTOM,
	OSD_POZITON_MIDBOTTOM ,
	OSD_POZITON_RIGHTBOTTOM ,
}ENU_OSDPOZITION;
typedef enum
{
	OSD_TIMESTYE_NULL    =0,
	OSD_TIMESTYE_01        ,   //1970-01-01 23:59:59
	OSD_TIMESTYE_02        ,   //1970/01/01 23:59:59
	OSD_TIMESTYE_03        ,   //1970/01/01 星期5 23:59:59
	OSD_TIMESTYE_04        ,   //Jul.01 1970 Fri 23:59:59
	OSD_TIMESTYE_05		   ,   //1970年01月01日 23:59:59
}ENU_OSDTIMESTYE;
typedef struct {
    UCHAR           channel;
    UCHAR           uzChannelName[16] ;        //通道名称(字符为空不显示) 
	ENU_OSDPOZITION ChannelNamePoziton;        //显示位置(位置为空不显示，有些设备调整显示位置无效)
	ENU_OSDTIMESTYE ShowTimeOsdStype;          //时间显示类型为空时不显示
	ENU_OSDPOZITION TimeOsdPoziton;            //显示位置(位置为空不显示，有些设备调整显示位置无效)
} T_IPCOSDPARAM;
////////////////云台控制/////////////////////////////////
typedef struct { 
	UCHAR           channel;
	UCHAR           ptzScriptName[32];     //当前云台脚本文件名称(只读)
	UCHAR           ptzAddress;
    UCHAR           ptzSpeed;
}T_IPCPTZPARAM;
typedef	struct { 

	USHORT          channel;               //通道选择
	USHORT          cmd;                   //云台命令
	ULONG           timeount;              //毫秒级
} T_IPCPTZCOMMAND;
///////////////报警或系统消息///////////////////////////
typedef	struct { 

	UCHAR           channel;               //通道
	USHORT          cmd;                   //消息类型
	ULONG           time;                  //时间撮
} T_IPCSIGNALNOTIFY;
///////////////以下为次要接口客户端SDK可不与支持////////////
//IO.移动侦测相关
typedef struct{
	
	UINT            outputRelationAlarm;   //联动输出IO报警 0-1BIT 表示相关IO
}T_IPCREALPARAM;
typedef struct{

	UCHAR           channel;                //通道选择
	UCHAR 	        isOpen;			        //移动侦测使能
	UINT	        outputRelationAlarm;    //联动输出IO报警 //联动输出IO报警 0-1BIT 表示相关IO
	CHAR            ChannelName[24];        //报警通道名称
}T_IPCIOALARMPARAM;
typedef struct{

	UCHAR           channel;                //通道选择
	UCHAR 	        isOpen[4];			    //移动侦测使能,每个视频通道可设置4个区域
	UINT 	        sensitivity[4];	        //灵敏度 0 -5
    UCHAR	        area[4][4];             //移动侦测区域,4组
	UINT	        outputRelationAlarm[4]; //联动输出IO报警 
	CHAR            ChannelName[4][24];     //报警通道名称
}T_IPCMOTIONALARMPARAM,T_IPCMASKPARAM;      //移动侦测和视图遮盖使用相同结构
//账户管理相关
typedef struct{
	
    CHAR             userName[16];          //用户名称  有一个厂家用户，不提供给用户，不能被修改，另外有一个管理员用户，其余为普通用户
    CHAR             userPassword[16];      //用户密码
    CHAR             Priority;              //用户权限规定为2级    浏览权限和管理权限，只有admin用户有管理权限
    CHAR             Enable;                //用户使能
} T_IPCUSERPARAM;  

#ifndef MAX_PTZ_SCRIPT_NUM
	#define MAX_PTZ_SCRIPT_NUM 2
#endif
//内置PTZ协议查询
typedef struct {
	T_IPCPTZPARAM       ptzName[MAX_PTZ_SCRIPT_NUM];  //设备内总共的脚本名称
}T_IPCPTZNAME;
//wifi参数
typedef struct{
    UCHAR           WifiIsHost;             //ENU_WIFFISHOST
	UCHAR           WifiEncryptType;	    //ENU_WIFFWEPTYPE
	UCHAR           WifiPassword[130];      //65 修改为128位支持
	UCHAR           WifiSsid[50];
	UCHAR           WifiKeySystem;		    //0:十六进制  1:ASCII
}T_IPCNETWIFIPARAM;

typedef struct{
	INT					iServerPort;
	INT					ipFetchMode;	       //静态IP或者动态DHCP分配IP				
	UCHAR				NetIpAddr[16];				//IP 地址
	UCHAR				NetGwAddr[16];				//gateway
	UCHAR				NetSubMask[16];				//net mask
	UCHAR				NetMacAddr[24];				//MAC addr
	UCHAR				NetDnsSvI [16];				//DNS1
	UCHAR				NetDnsSvII[16];				//DNS2

	UCHAR				devModel[20];               //出厂型号
	UCHAR				devSerialNumb[64];          //出厂编号
	UCHAR				devRegcode[26];             //设备注册码
	CHAR				devName[24];                //设备显示名称
	CHAR				szFactoryName[32];			//厂家名称

	CHAR                nVideoChannel;              //视频通道数
	CHAR                bIsVideoSubChannel;         //是否有视频子码流
	CHAR                nAudioChannel;              //音频通道数
}T_DEVSEARCHINFO;

typedef enum {
ALARMTYPE_IO     =0,
ALARMTYPE_MV     =1,
}ENU_ALARMTYPE;

typedef struct {
	UCHAR	Channel;
	UCHAR 	AlarmType;							//=ENU_ALARAMTYPE
	ULONG   AlarmParam;							//Md=报警区域，IO=报警端口							//bit 0表示md区域1被触发，目前只支持 bit 0
	ULONG   AlaramTime;							//报警触发时间
}T_ALARMSTATUS;

typedef enum{
LOGTYPE_USR			= 1,						
LOGTYPE_SYS			= 2,
LOGTYPE_APP 		= 3,
}ENU_LOGTYPE;
typedef struct {
	UCHAR   LogType;							//请求包时表示检索类型ENU_LOGTYPE  	  0表示不检索此项，
												//日志包时表示ENU_LOGTYPE
	ULONG   SerialNu;							//请求包时表示检索起始时间    0表示不检索此项
												//日志包时表示包的序号数	  为0时表示已经发送完成
	ULONG   LogTime;							//请求包时表示检索结束时间	  SerialNu != -1时这项一定要写
												//日志包时表示日志的录制时间
	CHAR    LogUsr[10];							//请求包时表示要检索的用户      strlen() == 0;时表示不检索此项
												//日志包时表示日志的用户
	CHAR    LogMsg[120];						//请求包时不用填写
												//日志包时表示日志内容
}T_LOGINFO;

///////DVR 相关///////////////////////////////////////////////
typedef enum{
	UPDATE_TYPE_BOOT    =0X01, //启动
	UPDATE_TYPE_LINUX   =0X02, //内核
	UPDATE_TYPE_ROOTFS  =0X03, //文件系统
	UPDATE_TYPE_APP     =0X04, //运用镜像
	UPDATE_TYPE_PTZ     =0X05, //PTZ脚本

}ENU_UPDATETYPE;
typedef struct{
	INT                 nFileType;                  //文件类型 (ENU_UPDATETYPE)
	INT					iFileLen;                   //文件长度
	CHAR				szUpdateFileName[128];      //文件名称(板上存储名称，非全路径)

}T_DEVUPDATE;


typedef struct{                                     //DVR.回放

	ULONG                StartTime ;                //文件起始时间
	ULONG                EndTime;                   //文件结束时间
	CHAR                 FilePath[128];             //文件名称  
}T_DVRREPLAY;
typedef enum{
	FT_V_IOALM    =0,										//IO报警录像文件
	FT_V_MDALM    =1,										//移动帧测报警录像文件
	FT_V_TMREC    =2,										//定时录相文件
	FT_V_NULL	  =3,										//文件查询时不按类型查询
}ENU_FILETYPE;
typedef struct{                                     //DVR.文件查询
	USHORT               nChn;                      //文件录像通道      //1CH=00,2CH=01,...所有通道 0XFFFF
	USHORT               FileType;                  //文件类型:			ENU_FILETYPE       
	ULONG                FileSize;                  //文件大小
	ULONG                StartTime ;                //文件起始时间
	ULONG                EndTime;                   //文件结束时间
	CHAR                 FileName[128];             //文件名称
}T_DVRFILESEARCH;

typedef struct{                                     //DVR.文件下载
    INT                  FileSize;                  //文件大小
    CHAR                 FileName[128];             //文件名称
}T_DVRFILEDOWNLOAD;
typedef enum {
    DVR_FILDOWNLOAD_ERR     =0X01,
	DVR_FILDOWNLOAD_FILINFO =0X02,                 //文件信息(T_DVRFILEDOWNLOADRESP)
	DVR_FILDOWNLOAD_DATA    =0X03,                 //文件数据
    DVR_FILDOWNLOAD_ENDDATA =0X04,                 //数据结束(IPC_DvrDonloadFil()函数返回)
}ENU_DVRFILDOWNLOADRET;
typedef enum {
 PLAYBACK_PAUSE             =0x50A1,               //DVR回放.正常播放
 PLAYBACK_NOMAL             =0x50A2,               //DVR回放.两倍快进
 PLAYBACK_FASTx2            =0x50A3,               //DVR回放.两倍快进
 PLAYBACK_FASTx4            =0x50A4,               //DVR回放.四倍快进
 PLAYBACK_FASTx8            =0x50A5,               //DVR回放.八倍快进
 PLAYBACK_BACK              =0x50A6,               //DVR回放.正常退播
 PLAYBACK_BACKx2            =0x50A7,               //DVR回放.两倍退播
 PLAYBACK_BACKx4            =0x50A8,               //DVR回放.四倍退播
 PLAYBACK_BACKx8            =0x50A9,               //DVR回放.八倍退播
}ENU_PLAYBACKCTRL;
#endif


