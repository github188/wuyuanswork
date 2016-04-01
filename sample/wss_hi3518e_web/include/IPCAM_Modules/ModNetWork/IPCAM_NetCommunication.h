//IPCAM_NetCommunication.h
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
#ifndef IPCAM_NET_COMMUNICATION_H
#define IPCAM_NET_COMMUNICATION_H

#define  	MAX_STREAM_SLICE	    			1024
#define	    MAX_STREAM_BUFLEN		    		(150*1024)//(350 * 1024)

#define     PORT_UDP_RESP               		40001               //UDP设备搜寻回应端口
#define     PORT_UDP_SEARCH               		40002               //UDP设备搜寻信号端口
#define 	MULTICASE_ADDR						"230.1.1.1"
////////////网络消息定义/////////////////////////////////////////////////
#define 	MSG_USERLOGIN_REQ		    		0x0101		//用户登陆请求
#define 	MSG_USERLOGIN_RESP			        0x0102		//用户登陆回应	
#define 	MSG_PULSE_REQ		    		    0x0103		//脉搏请求
#define 	MSG_PULSE_RESP			            0x0104		//脉搏回应

#define 	MSG_USERQUERY_REQ		    		0x0201		//用户查询请求	
#define 	MSG_USERQUERY_RESP			        0x0202		//用户查询回应	

#define 	MSG_USERADD_REQ			        	0x0203		//用户添加请求	
#define 	MSG_USERADD_RESP		    		0x0204		//用户添加回应	

#define 	MSG_USERDELETE_REQ			        0x0205		//用户删除请求	
#define 	MSG_USERDELETE_RESP			        0x0206		//用户删除回应

#define     MSG_USERLISTQUARY_REQ     		    0X0207      //用户列表查询
#define     MSG_USERLISTQUARY_RESP 		        0X0208      //用户列表查询响应
#define     MSG_USERLISTNEXT_REQ      		    0X0209      //列表下一页
#define     MSG_USERLISTNEXT_RESP   		    0X020A      
#define     MSG_USERMODIFY_REQ        		    0X020B      //用户修改
#define     MSG_USERMODIFY_RESP       		    0X020C      //用户修改响应


#define 	MSG_LOGEVENTQUERY_REQ	        	0x0303		//日志告警查询请求
#define 	MSG_LOGEVENTQUERY_RESP	 	        0x0304		//日志告警查询回应	
#define 	MSG_LOGEVENTCLEAN_REQ	     		0x0305		//日志告警清除请求	
#define 	MSG_LOGEVENTCLEAN_RESP	 	        0x0306		//日志告警清除回应
#define 	MSG_LOGEVENTNEXT_REQ	     		0x0307		//日志告警下一项纪录
#define 	MSG_LOGEVENTNEXT_RESP	     		0x0308		//日志告警下一项纪录
#define 	MSG_LOGEVENTQUERY_NOTFY	        	0x0309		//日志告警及时信号,不回复

#define 	MSG_VIDEOSET_REQ		     		0x0401		//视频设置请求	
#define 	MSG_VIDEOSET_RESP		     		0x0402		//视频设置回应
#define 	MSG_VIDEOQUARY_REQ	     	  	    0x0403		//视频查询请求	
#define 	MSG_VIDEOQUARY_RESP	     		    0x0404		//视频查询回应
#define 	MSG_PICTURESET_REQ	     			0x0405      //图像设置请求
#define 	MSG_PICTURESET_RESP	     		    0x0406      //图像设置回应
#define 	MSG_PICTUREQUERY_REQ	     		0x0407      //图像查询请求
#define 	MSG_PICTUREQUERY_RESP	     		0x0408      //图像查询回应
#define		MSG_RTSPPAWDAUTH_REQ				0x0409		//rtsp密码认证登陆 CGI回调时用
#define		MSG_RTSPPAWDAUTH_RESP				0x040a		//


#define 	MSG_AUDIOSET_REQ		     		0x0501		//音频设置请求	
#define 	MSG_AUDIOSET_RESP		     		0x0502		//音频设置回应
#define 	MSG_AUDIOQUARY_REQ	     	  	    0x0503		//音频查询请求	
#define 	MSG_AUDIOQUARY_RESP	     		    0x0504		//音频查询回应

#define 	MSG_MOTIONPARMSET_REQ	        	0x0601		//运动检测参数设置请求	
#define 	MSG_MOTIONPARMSET_RESP	 	        0x0602		//运动检测参数设置回应
#define 	MSG_MOTIONPARMQUERY_REQ		        0x0603		//运动检测参数查询请求	
#define 	MSG_MOTIONPARMQUERY_RESP	        0x0604		//运动检测参数查询回应	

#define 	MSG_MASKPARMSET_REQ	        	    0x0701		//画面遮盖参数设置请求	
#define 	MSG_MASKPARMSET_RESP	 	        0x0702		//画面遮盖参数设置回应
#define 	MSG_MASKPARMQUERY_REQ		        0x0703		//画面遮盖参数查询请求	
#define 	MSG_MASKPARMQUERY_RESP	            0x0704		//画面遮盖参数查询回应	

#define     MSG_PTZPARAMSET_REQ          		0x0901      //PTZ 参数设置
#define     MSG_PTZPARAMSET_RESP         		0x0902      //PTZ 参数设置相应
#define     MSG_PTZPARAMQUERY_REQ        	    0x0903      //PTZ 参数读取
#define     MSG_PTZPARAMQUERY_RESP       	    0x0904      //PTZ 参数读取回应

#define     MSG_PTZWRITE_REQ              		0x0905      //PTZ 写
#define     MSG_PTZWRITE_RESP             		0x0906      //PTZ 写响应
#define     MSG_PTZNAMEQUARY_REQ          	    0x0907      //PTZ 协议查询
#define     MSG_PTZNAMEQUARY_RESP         	    0x0908      //PTZ 协议回复

#define 	MSG_IOQUERY_REQ				        0x0A01		//IO报警查询请求	
#define 	MSG_IOQUERY_RESP			     	0x0A02		//IO报警查询回应
#define 	MSG_IOSET_REQ				    	0x0A03		//IO报警设置请求	
#define 	MSG_IOSET_RESP				    	0x0A04		//IO报警设置回应	

#define 	MSG_CLOCKSET_REQ			    	0x0B01		//时钟校对请求	
#define 	MSG_CLOCKSET_RESP			    	0x0B02		//时钟校对回应
#define 	MSG_CLOCKQUERY_REQ			        0x0B03		//时钟查询请求	
#define 	MSG_CLOCKQUERY_RESP			        0x0B04		//时钟查询回应	

#define 	MSG_NETPARMSET_REQ			        0x0C01		//网络参数设置请求	
#define 	MSG_NETPARMSET_RESP			        0x0C02		//网络参数设置回应
#define 	MSG_NETPARMQUERY_REQ		        0x0C03		//网络参数查询请求	
#define 	MSG_NETPARMQUERY_RESP		        0x0C04		//网络参数查询回应
#define     MSG_NETWIFIPARAMSET_REQ             0x0C05      //WIFI参数设置
#define     MSG_NETWIFIPARAMSET_RESP            0x0C06      //WIFI参数设定响应
#define     MSG_NETWIFIPARAMQUARY_REQ           0x0C07      //WIFI参数查询
#define     MSG_NETWIFIPARAMQUARY_RESP          0x0C08      //WIFI参数查询响应

#define     MSG_DEVICEABILITYSET_REQ            0X0D01      //设备性能设置请求
#define     MSG_DEVICEABILITYSET_RESP           0X0D02      //设备性能设置响应
#define     MSG_DEVICEABILITYGET_REQ            0X0D03      //设备性能查询请求
#define     MSG_DEVICEABILITYGET_RESP           0X0D04      //设备性能查询响应

#define 	MSG_STARTUPNP_REQ					0X0E01		//启动upnp请求		CGI
#define 	MSG_STARTUPNP_RESP 					0X0E02		//启动upnp响应		CGI
#define 	MSG_REBOOT_REQ						0X0E03		//设备重启请求		CGI
#define 	MSG_REBOOT_RESP						0X0E04		//设备重启回应		CGI
#define 	MSG_STARTDDNS_REQ					0X0E05		//启动ddns请求		CGI
#define 	MSG_STARTDDNS_RESP					0X0E06		//启动ddns回应		CGI
#define 	MSG_LOADCFG_REQ						0X0E07		//恢复出厂设置请求	CGI
#define 	MSG_LOADCFG_RESP					0X0E08		//恢复出厂设置回应	CGI
#define 	MSG_SAVECFG_REQ						0X0E09		//保存配置请求		CGI
#define 	MSG_SAVECFG_RESP					0X0E0A		//保存配置回应		CGI
#define 	MSG_STARTNTP_REQ					0X0E0B		//启动ntp请求		CGI
#define  	MSG_STARTNTP_RESP					0X0E0C		//启动ntp回应		CGI
#define 	MSG_SETSYSTIME_REQ					0X0E0D		//设置系统时间请求	CGI
#define		MSG_SETSYSTIME_RESP					0X0E0E		//设置系统时间回应	CGI
#define 	MSG_SETSERVICEPORT_REQ				0X0E0F		//改变服务端口请求	CGI
#define 	MSG_SETSERVICEPORT_RESP				0X0E10		//改变服务商品回应	CGI
#define 	MSG_SETPPPOE_PARAM_REQ				0X0E11		//设置pppoe参数请求	CGI
#define 	MSG_SETPPPOE_PARAM_RESP				0X0E12		//设置pppoe参数回应	CGI
#define 	MSG_OPENIRCUT_REQ					0X0E13		//打开IR-CUT请求
#define 	MSG_OPENIRCUT_RESP					0X0E14		//打开IR-CUT回应
#define 	MSG_CLOSEIRCUT_REQ					0X0E15		//关闭IR-CUT请求
#define 	MSG_CLOSEIRCUT_RESP					0X0E16		//关闭IR-CUT回应

#define 	MSG_ALARMSTATUS_REQ					0X0F01		//报警查询请求(包含应该程序的所有报警)
#define 	MSG_ALARMSTATUS_RESP				0X0F02		//报警查询回应


#define     MSG_SEARCHQUERY_REQ                 0x2001      //设备搜索
#define     MSG_SEARCHQUERY_RESP                0x2002      //设备搜素响应
#define     MSG_DEVREGIST_REQ                   0x2003      //设备注册
#define     MSG_DEVREGIST_RESP                  0x2004      //设备注册响应

#define		MSG_FACTORYINFOSET_REQ			    0x2005		//厂家信息设置
#define		MSG_FACTORYINFOSET_RESP				0x2006		//厂家信息设置回应
#define     MSG_FACTORYINFOQUARY_REQ            0x2007
#define     MSG_FACTORYINFOQUARY_RESP           0x2008      //

#define		MSG_UPDATE_REQ						0x2101		//升级云台协议
#define		MSG_UPDATE_RESP						0x2102		//升级应用程序

#define     MSG_OSDQUARY_REQ                    0x2201      //OSD参数查询
#define     MSG_OSDQUARY_RESP                   0x2202      //OSD参数查询回应
#define     MSG_OSDSET_REQ                      0x2203      //OSD参数设置
#define     MSG_OSDSET_RESP                     0x2204      //OSD参数设置回应
//DVR.回放
#define     MSG_REPLAY_REQ                      0X5001      //DVR回放
#define     MSG_REPLAY_RESP                     0X5002      //DVR回放响应
#define     MSG_REPLAY_SUB_PAUSE                0x50A1      //DVR回放.正常播放
#define     MSG_REPLAY_SUB_NOMAL                0x50A2      //DVR回放.两倍快进
#define     MSG_REPLAY_SUB_FASTx2               0x50A3      //DVR回放.两倍快进
#define     MSG_REPLAY_SUB_FASTx4               0x50A4      //DVR回放.四倍快进
#define     MSG_REPLAY_SUB_FASTx8               0x50A5      //DVR回放.八倍快进
#define     MSG_REPLAY_SUB_BACK                 0x50A6      //DVR回放.正常退播
#define     MSG_REPLAY_SUB_BACKx2               0x50A7      //DVR回放.两倍退播
#define     MSG_REPLAY_SUB_BACKx4               0x50A8      //DVR回放.四倍退播
#define     MSG_REPLAY_SUB_BACKx8               0x50A9      //DVR回放.八倍退播
#define     MSG_REPLAY_SUB_SETFILE              0x50AA      //DVR回放.重新指定文件
//DVR.检索
#define     MSG_FILESEARCH_REQ                  0x5101      //DVR.文件查询
#define     MSG_FILESEARCH_RESP                 0x5102      //DVR.文件查询回应
//DVR.下载
#define     MSG_FILEDOWNLOAD_REQ                0X5201      //DVR.文件下载
#define     MSG_FILEDOWNLOAD_RESP               0X5202      //DVR.文件下载响应

//PRECOMMAND 网络连接预处理命令(主要用做判定当前连接的请求类型)
#define     MSG_CONNECT_SESSION            		0XFF01
#define     MSG_CONNECT_GETVIDEO           		0XFF02
#define     MSG_CONNECT_GETAUDIO           		0XFF03
#define     MSG_CONNECT_ALARM              		0XFF04
#define     MSG_CONNECT_PUTVIDEO           		0XFF05
#define     MSG_CONNECT_PUTAUDIO           		0XFF06
#define     MSG_CONNECT_UPDATE             		0XFF07       //update
#define     MSG_CONNECT_DVRPLAY            		0XFF08       //dvr play
#define     MSG_CONNECT_DVRDOWNLOAD        		0XFF09       //file download
#define     MSG_CONNECT_DVRFILESEARCH     		0XFF0A       //DVR 文件查询
#define 	MSG_CONNECT_LOGSEARCH				0XFF0B		 //日志查询
#define     MSG_CONNECT_REFUSE             		0XFFFF       //refuse

#define 	MSG_DATA_VIDEO				   		0xFE01	     //-实时视频数据	
#define 	MSG_DATA_AUDIO				   		0xFE02	     //-实时音频数据
#define     MSG_DATE_FILEDOWLOAD                0xFE03       //文件下载数据负载
#define     MSG_DATE_FILESEARCH                 0xFE04       //文件搜寻数据负载
#define     MSG_DATE_DVRREPLAY_VIDEO            0xFE05       //文件回放数据负载.视频
#define     MSG_DATE_DVRREPLAY_AUDIO            0xFE06       //文件回放数据负载.音频
#define     MSG_DATE_END                        0xFE07       //数据结束
#define     MSG_DATA_HEAD                       0xFE08       //数据结束
#define     MSG_DATA_TS							0xFE09       //数据结束
#define     MSG_DATA_PS							0xFE0A       //数据结束


#define	    ERR_UNKNOW			    			(0xFFFF)
#define     ERR_STREAM_NODATA                   (0xff01)
#define	    ERR_NO_ERROR						(0x0001)
#define	    ERR_NO_THIS_USER					(0x0002)
#define	    ERR_PASSOWRD						(0x0003)
#define	    ERR_USER_EXISTED					(0x0004)
#define	    ERR_DEL_ADMIN						(0x0005)	
#define	    ERR_NO_PRIORITY						(0x0006)
#define     ERR_DVRFILE_SEARCH                  (0x0007)     //错误.DVR文件搜寻错误
#define     ERR_DVRFILE_DOWNLAOD                (0x0008)     //错误.DVR文件下载错误
////////////网络消息.协议结构定义////////////////////////////////////////////
#define     __start_code__              ((USHORT)0xE0AF)

#include "IPCAM_NetCommunicationT.h"
typedef struct {                      //包头
	USHORT     sync;
	USHORT	   msgType;
	USHORT     subType;
	USHORT	   len;
	USHORT	   errCode;
    USHORT     reserve;
	char	lpData[];
	      
}T_MSGHEAD; 
typedef struct {
	T_MSGHEAD  head;
	CHAR       msgbuf[532];
}T_MSGBUF;

typedef struct{
	
	T_MSGHEAD		   head;
	T_IPCVIDEOPARAM    videoParam;	
}IPCAM_VIDEO_PARAM_SET_REQ,  IPCAM_VIDEO_PARAM_SET_RESP,
 IPCAM_VIDEO_PARAM_QUARY_REQ,IPCAM_VIDEO_PARAM_QUARY_RESP;
typedef struct{

    T_MSGHEAD	       head;
	T_IPCPICTUERPARAM  picParam;
}IPCAM_PICTURE_PARAM_SET_REQ,IPCAM_PICTURE_PARAM_SET_RESP,
 IPCAM_PICTURE_PARAM_QUARY_REQ,IPCAM_PICTURE_PARAM_QUARY_RESP;
typedef struct{
	T_MSGHEAD		    head;
    T_IPCNETPARAM       netparam;
}IPCAM_NET_PARAM_SET_REQ,  IPCAM_NET_PARAM_SET_RESP,
 IPCAM_NET_PARAM_QUARY_REQ,IPCAM_NET_PARAM_QUARY_RESP;
typedef struct{
	T_MSGHEAD		    head;
    T_IPCNETWIFIPARAM   WifiParam;
}IPCAM_NET_WIFIPARAM_SET_REQ,  IPCAM_NET_WIFIPARAM_SET_RESP,
 IPCAM_NET_WIFIPARAM_QUARY_REQ,IPCAM_NET_WIFIPARAM_QUARY_RESP;
typedef struct{
	T_MSGHEAD		     head;
    T_IPCIOALARMPARAM    ioAlarm;
}IPCAM_IO_ALARM_SET_REQ,  IPCAM_IO_ALARM_SET_RESP,
 IPCAM_IO_ALARM_QUARY_REQ,IPCAM_IO_ALARM_QUARY_RESP;

typedef struct{
	T_MSGHEAD		      head;
    T_IPCMOTIONALARMPARAM motionAlaram;
}IPCAM_MOTION_ALARM_SET_REQ, IPCAM_MOTION_ALARM_SET_RESP,
IPCAM_MOTION_ALARM_QUARY_REQ,IPCAM_MOTION_ALARM_QUARY_RESP;
typedef	struct { 
	T_MSGHEAD		      head;
    T_IPCMASKPARAM        MaskParam;
}IPCAM_MASK_SET_REQ, IPCAM_MASK_SET_RESP,
 IPCAM_MASK_QUARY_REQ,IPCAM_MASK_QUARY_RESP;
typedef	struct { 
	T_MSGHEAD		      head;
	T_IPCPTZPARAM         ptzName;
} IPCAM_PTZ_PARAM_SET_REQ,  IPCAM_PTZ_PARAM_SET_RESP,
  IPCAM_PTZ_PARAM_QUARY_REQ,IPCAM_PTZ_PARAM_QUARY_RESP;

typedef	struct { 
	T_MSGHEAD		      head;
	T_IPCPTZPARAM         ptzScriptName[10];
	INT                   ptzScriptCount;
}IPCAM_PTZ_NAME_QUARY_REQ,IPCAM_PTZ_NAME_QUARY_RESP;
typedef	struct { 
	T_MSGHEAD		      head;
    T_IPCPTZCOMMAND       ptzcommand;
} IPCAM_PTZ_COMMAND_REQ,IPCAM_PTZ_COMMAND_RESP;

typedef	struct {           //DVR.回放
    T_MSGHEAD		   head;
    T_DVRREPLAY            file;
}DVR_REPLAY_REQ,DEV_REPLAY_RESP;

typedef	struct {          //DVR.文件检索
    T_MSGHEAD		   head;
    T_DVRFILESEARCH        file;
}DVR_FILE_QUARY_REQ,DEV_FILE_QUARY_RESP;

typedef	struct {           //DVR.文件下载
    T_MSGHEAD		   head;
    T_DVRFILEDOWNLOAD      file;
}DVR_FILE_DOWNLOAD_REQ,DEV_FILE_DOWNLOAD_RESP;

typedef struct               //用户登录请求
{
	T_MSGHEAD		      head;
	UCHAR	      		  userName[16];
	UCHAR	      		  password[16];	
}IPCAM_LOGIN_REQ,IPCAM_LOGIN_RESP;

typedef struct             //用户查询，以及修改，包括添加删除
{
	T_MSGHEAD		     head;
	T_IPCUSERPARAM       userlist[10];
}IPCAM_USER_QUERY_REQ,IPCAM_USER_QUERY_RESP,
 IPCAM_USER_SET_REQ,  IPCAM_USER_SET_RESP;

typedef struct{				//设备搜索
	T_MSGHEAD			head;
	T_DEVSEARCHINFO		DevSearchInfo;
}IPCAM_DEV_SEARCH_REG, IPCAM_DEV_SEARCH_RESP;

typedef struct{
	T_MSGHEAD			head;
	T_DEVUPDATE			DevUpdate;
}IPCAM_DEV_UPDATE_REG, IPCAM_DEV_UPDATE_RESP;

typedef struct{
	T_MSGHEAD			head;
	T_IPCFACTORYPARAM	FactoryParam;
}IPCAM_FACTORY_PARAM_REQ;

typedef struct{
	T_MSGHEAD			head;
	T_IPCAUDIOPARAM		AudioParam;
}IPCAM_AUDIO_PARAM_REQ;
typedef struct 
{
	T_MSGHEAD		     head;
	T_IPCSIGNALNOTIFY    SignalNotify;
}IPCAM_SIGNAL_NOTIFY;
typedef struct 
{
	T_MSGHEAD			head;
	T_IPCABILITYYPARAM	DevAbility;
}IPCAM_DEVABILITY_REQ, IPCAM_DEVABILITY_RESP;
typedef struct
{
	T_MSGHEAD			head;
	T_ALARMSTATUS		AlarmStatus;
}IPCAM_ALARMSTATUS_REQ;
typedef struct 
{
	T_MSGHEAD head;
	T_LOGINFO LogInfo;
}IPCAM_LOG_REQ, IPCAM_LOG_RESP;
typedef struct
{
	T_MSGHEAD head;
	T_IPCTIMEPARAM IpcTime;
}IPCAM_TIME_REQ, IPCAM_TIME_RESP;
typedef struct 
{
	T_MSGHEAD head;
	T_IPCOSDPARAM OsdInfo;
}IPCAM_OSDSET_REQ, IPCAM_OSDSET_RESP;


typedef struct{
	T_MSGHEAD   MsgHead;                   //标准包头
	ULONG 	    FrameNumber;	 	       //帧序号，始终递增
	ULONG	    FrameSize;		           //帧尺寸
	USHORT 	    SliceNum;		 	       //分片的序号
	USHORT	    SliceSize;			       //片尺寸

	USHORT	    Reserve1;		           //保留字节
	USHORT 	    Reserve2;			       //保留字节

	USHORT 	    EncType;                   //编码类型 //,ENU_STREAMENCTYPE
	USHORT      Reserve3;                  //保留字节
	
	time_t		time;			           //帧的时间戳,精确到毫秒级
	time_t		usec;
	UCHAR		Data[MAX_STREAM_BUFLEN];   // frame valid data
}NETAUDIODATAPS,*LPNETAUDODATAPS;



typedef struct{
	T_MSGHEAD   MsgHead;                   //标准包头
	ULONG 	    FrameNumber;	 	       //帧序号，始终递增
	ULONG	    FrameSize;		           //帧尺寸
	USHORT 	    SliceNum;		 	       //分片的序号
	USHORT	    SliceSize;			       //片尺寸

	USHORT	    Reserve1;		           //保留字节
	USHORT 	    Reserve2;			       //保留字节
	USHORT 	    EncType;                   //编码类型 //,ENU_STREAMENCTYPE

	USHORT      Reserve3;                  //保留字节
	
	time_t		time;			           //帧的时间戳,精确到毫秒级
	time_t		usec;
	UCHAR		Data[MAX_STREAM_SLICE];    // frame valid data
}NETAUDIODATATS,*LPNETAUDODATATS;


typedef union{
	
	T_MSGHEAD		               MsgHead;
	T_MSGBUF                       MsgBuf;
	NETAUDIODATATS 				   MsgAudio;		
	IPCAM_LOGIN_REQ                MsgUserLogin;
    //账户管理
	IPCAM_USER_QUERY_REQ           MsgUserInfo;	
	//厂家设定 SET
	IPCAM_FACTORY_PARAM_REQ		   MsgFactoryParam;
	//VIDEO SET
	IPCAM_VIDEO_PARAM_SET_REQ	   MsgVideoParam;
	//音频参数查询
	IPCAM_AUDIO_PARAM_REQ          MsgAudioParam;
    //PICTURE SET
	IPCAM_PICTURE_PARAM_QUARY_REQ  MsgPictureParam;
	//NET PARAM SET
	IPCAM_NET_PARAM_SET_REQ	       MsgNetParam;
    //NET WIFI SET
    IPCAM_NET_WIFIPARAM_SET_REQ    MsgNetWifiParam;
	//IO ALARM SET
	IPCAM_IO_ALARM_SET_REQ	       MsgAlarmParam;
	//MOTION ALARM SET
	IPCAM_MOTION_ALARM_SET_REQ	   MsgMotionParam;
	//遮盖
	IPCAM_MASK_SET_REQ             MsgMaskParam;
	//PTZ SET
	IPCAM_PTZ_PARAM_SET_REQ	       MsgPtzParam;
	//PTZ SCRIPT SEARCH
	IPCAM_PTZ_NAME_QUARY_REQ       MsgPtzNameParam;
	//PTZ COMMAND 
	IPCAM_PTZ_COMMAND_REQ	       MsgPtzCommand;
	//设备搜索
	IPCAM_DEV_SEARCH_REG		   MsgDevSearch;
	//设备升级
	IPCAM_DEV_UPDATE_REG		   MsgDevUpdate;
	//NOTIFY
	IPCAM_SIGNAL_NOTIFY            MsgSignalNotify;
	//设备性能
	IPCAM_DEVABILITY_REQ		   MsgDevAbility;
	//报警状态查询
	IPCAM_ALARMSTATUS_REQ		   MsgAlarmStatus;
	//日志查询
	IPCAM_LOG_REQ				   MsgLog;
	//时间查询设定
	IPCAM_TIME_REQ				   MsgTime;
	//OSD查询与设置
	IPCAM_OSDSET_REQ			   MsgOsd;
		
	//DVR.文件查询
	DVR_FILE_QUARY_REQ             MsgFileSearch;
	//DVR.文件下载
    DVR_FILE_DOWNLOAD_REQ          MsgFileDowLoad;
    //DVR.回放
    DVR_REPLAY_REQ                 MsgReplay;
	


}NETMSGPACKET,*LPNETMSGPACKET;
#define  	SIZEOFNETMSGHEAD	         (sizeof(T_MSGHEAD))
#define     SIZEOFNETMSGPACK             (sizeof(NETMSGPACKET))  

/////////////////////////媒体流协议结构定义/////////////////////
typedef enum{
 STREAM_ENCTYPE_VIDEO_MJPEG       =0,
 STREAM_ENCTYPE_VIDEO_MPEG4       =1,
 STREAM_ENCTYPE_VIDEO_h264        =2,
 STREAM_ENCTYPE_AUDIO_PCM8X8K     =6,
 STREAM_ENCTYPE_AUDIO_PCM16X8K    =7,
 STREAM_ENCTYPE_AUDIO_ADPCM16X8K  =8,
 STREAM_ENCTYPE_AUDIO_AMR16X8K    =9,
 STREAM_ENCTYPE_AUDIO_G711UL      =10,
 STREAM_ENCTYPE_AUDIO_G711AL      =11,
 STREAM_ENCTYPE_AUDIO_AAC         =12,

}ENU_STREAMENCTYPE;
typedef enum{
STREAM_VIDEO_I_FRAME			 =0,
STREAM_VIDEO_P_FRAME			 =1,
STREAM_VIDEO_B_FRAME			 =3,
}ENU_STREAMFRAMTYPE;

//视音频协议
typedef struct {
	T_MSGHEAD   MsgHead;                   //标准包头
	ULONG 	    FrameNumber;	 	       //帧序号，始终递增
	ULONG	    FrameSize;		           //帧尺寸
	ULONG 	    SliceNum;		 	       //分片的序号
	ULONG	    SliceSize;			       //片尺寸
	USHORT	    ResolutionX;		       //I帧P帧组合的序号，始终递增
	USHORT 	    ResolutionY;			   //在一个帧组合中的序号

	USHORT 	    EncType;                   //编码类型 0-MJPEG 1-MPEG4 ,2-H264 ENU_STREAMENCTYPE
	USHORT      FrameType;                 //帧类型，0-I帧, 1-P帧
	time_t		time;			           //帧的时间戳,精确到毫秒级
	time_t		usec;
}NETVIDEODATAPSHEAD,NETAUDIODATAPSHEAD;
typedef struct {
	T_MSGHEAD   MsgHead;                   //标准包头
	ULONG 	    FrameNumber;	 	       //帧序号，始终递增
	ULONG	    FrameSize;		           //帧尺寸
	USHORT 	    Reserve1;		 	       //保留
	USHORT	    Reserve2;			       //保留
	USHORT	    ResolutionX;		       //I帧P帧组合的序号，始终递增
	USHORT 	    ResolutionY;			   //在一个帧组合中的序号

	USHORT 	    EncType;                   //编码类型 0-MJPEG 1-MPEG4 ,2-H264 ENU_STREAMENCTYPE
	USHORT      FrameType;                 //帧类型，0-I帧, 1-P帧
	time_t		time;			           //帧的时间戳,精确到毫秒级
	time_t		usec;
	UCHAR	    Data[MAX_STREAM_BUFLEN];   //实际帧数据
} NETVIDEODATAPS,*LPVIDEODATAPS;           //PS 结构码流

typedef struct{
	T_MSGHEAD   MsgHead;                   //标准包头
	ULONG 	    FrameNumber;	 	       //帧序号，始终递增
	ULONG	    FrameSize;		           //帧尺寸
	USHORT 	    SliceNum;		 	       //分片的序号
	USHORT	    SliceSize;			       //片尺寸
	USHORT	    ResolutionX;		       //I帧P帧组合的序号，始终递增
	USHORT 	    ResolutionY;			   //在一个帧组合中的序号

	USHORT 	    EncType;                   //编码类型 0-MJPEG 1-MPEG4 ,2-H264, ENU_STREAMENCTYPE
	USHORT      FrameType;                 //帧类型，0-I帧, 1-P帧
	time_t		time;			           //帧的时间戳,精确到毫秒级
	time_t		usec;
//	UCHAR		Data[MAX_STREAM_SLICE];    // frame valid data
}NETVIDEODATATS_HEAD,*LPVIDEODATATS_HEAD;            //TS码流结构

typedef struct{
	T_MSGHEAD   MsgHead;                   //标准包头
	ULONG 	    FrameNumber;	 	       //帧序号，始终递增
	ULONG	    FrameSize;		           //帧尺寸
	USHORT 	    SliceNum;		 	       //分片的序号
	USHORT	    SliceSize;			       //片尺寸
	USHORT	    ResolutionX;		       //I帧P帧组合的序号，始终递增
	USHORT 	    ResolutionY;			   //在一个帧组合中的序号

	USHORT 	    EncType;                   //编码类型 0-MJPEG 1-MPEG4 ,2-H264, ENU_STREAMENCTYPE
	USHORT      FrameType;                 //帧类型，0-I帧, 1-P帧
	time_t		time;			           //帧的时间戳,精确到毫秒级
	time_t		usec;
	UCHAR		Data[MAX_STREAM_SLICE];    // frame valid data
}NETVIDEODATATS,*LPVIDEODATATS;         //TS码流结构


#define SIZEOFNETVIDEOTS (sizeof(NETVIDEODATATS))
#define SIZEOFNETAUDIOTS (sizeof(NETAUDIODATATS))

#endif


