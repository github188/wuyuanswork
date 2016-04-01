//IPCAM_SysValue.h
#ifndef __IPCAM_SYSVALUE__
#define __IPCAM_SYSVALUE__

//#include "IPCAM_Export.h"

//硬盘信息
//客户端连接列表及时间校正
//基本录像状态
//网络端口
//版本信息
//网络校时信息



typedef struct _LOCALSQL
{
	INT				nSQLenable;
	CHAR			strSQLpath[256];
}IPCAM_LOCALSQL , *LPIPCAM_LOCALSQL;

typedef struct _LOCALSYSTEMFILE
{
	CHAR			ConfigFilePath[256];
	CHAR			DatabaseFilePath[256];
}IPCAM_LOCALSYSTEMFILE , *LPIPCAM_LOCALSYSTEMFILE;

typedef struct _SYSTEMTIME
{
    ULONG           SystemTimeStart;
    ULONG           SystemTimeCur ;
    
}IPCAM_SYSTEMTIME,*LPIPCAM_SYSTEMTIME;

typedef struct tagSYSNETINFO{
	UCHAR	NetIpAddr[16];		//IP 地址
	UCHAR	NetGwAddr[16];		//gateway
	UCHAR	NetSubMask[16];		//net mask
	UCHAR	NetMacAddr[24];		//MAC addr
	UCHAR   NetDnsSvI [16];     //DNS1
	UCHAR   NetDnsSvII[16];	    //DNS2
	INT 	ServicePort;
}IPCAM_SYSNETINFO, *LPIPCAM_SYSNETINFO;
//next struct add by jsk at 7-2
typedef struct {
	UCHAR UPNP_Status;  			/*ENABLE -->开启  UNENABLE-->关闭*/
	UINT  UPNP_RotePort;
	UCHAR UPNP_DisplayName[12];		/*路由upnp配置中可以看得到的名称*/
	UCHAR UPNP_Roteaddr[20];
	UCHAR UPNP_Protocols[5]; 		/*UDP / TCP*/
}IPCAM_UPNPINFO, *LPIPCAM_UPNPINFO;
typedef struct {
	UCHAR  AlarmFlag;	//报警标志位   ENABLE  UNENABLE
	time_t AlmLastTime;	//上次接收并处理报警时间
	time_t AlmClsTime;
}ALARMINFO;
typedef struct tagALARMSTATUS{
	ALARMINFO  AlarmIO;			
	ALARMINFO  AlarmMd;
	ALARMINFO  AlarmNet;
	ALARMINFO  AlarmIoOut;
	ALARMINFO  AlarmVideo;
	ALARMINFO  AlarmAudio;
	UCHAR  	   AlarmJpgProc;	//正在进行处理jpg ENABLE  没有处理 UNENABLE
	UCHAR      AlarmRecProc;	//record == ENABLE 
	UCHAR 	   TimerRecProc;	//record == enalble
}IPCAM_ALARMSTATUS, *LPIPCAM_ALARMSTATUS;
typedef struct tagSdState{
	UCHAR 	SD_State;		/*ENABLE -->挂载 UNENABLE -->未挂载*/
	LONG	SD_Total;		/*总大小 MB*/
	LONG 	SD_Free;		/*剩余大小 MB*/
}IPCAM_SDINFO, *LPIPCAM_SDINFO;
typedef struct {
	CHAR PtzName[20];
}IPCAM_PTZSTATUS;

typedef enum
{
    SYSTEM_VALUE_STATUS_STOP = 0, 
    SYSTEM_VALUE_STATUS_RUN , 
    SYSTEM_VALUE_STATUS_START ,  
    SYSTEM_VALUE_STATUS_ERROR,  
    SYSTEM_VALUE_STATUS_UNKOWN,
} SYSTEM_STATUS;


typedef struct _IPCAM_SYSVALUE{
	IPCAM_LOCALSQL              localSQL;
	IPCAM_LOCALSYSTEMFILE 	    localSystemFile;
	//IPCAM_SYSTEMSTATUS			localSystemStatus;
	IPCAM_SYSTEMTIME            localSystemTmStatus;
	IPCAM_SYSNETINFO			localSystemNetInfo;
	IPCAM_ALARMSTATUS			localAlarmStatus;
	IPCAM_PTZSTATUS				localPtzStatus;//云台名称
	IPCAM_UPNPINFO				localUpnpInfo;
	IPCAM_SDINFO				localSdinfo;
   	INT  regist ; 
} IPCAM_VARIABLE,*LPIPCAM_VARIABLE;

INT IPCAM_SetSystemStatus(INT nStatus);
INT IPCAM_GetSystemStatus();

INT IPCAM_SetSDStatus(INT nStatus);
INT IPCAM_GetSDStatus();
INT IPCAM_SetDatabaseStatus(INT nStatus);
INT IPCAM_GetDatabaseStatus();
INT IPCAM_SetEncStatus(INT ch_num , INT nStatus);
INT IPCAM_GetEncStatus(INT ch_num);
INT IPCAM_SetSDStoreStatus(INT ch_num , INT nStatus);
INT IPCAM_GetSDStoreStatus(INT ch_num);


#define IPCAM_MAX_CONNECTVIDEO		2
#define IPCAM_MAX_CONNECTAUDIOIN	1
#define IPCAM_MAX_CONNECTAUDIOOUT	2

INT IPCAM_AddOneVideoConnectCount(int channel);
INT IPCAM_DelOneVideoConnectCount(int channel);
INT IPCAM_GetVideoConnectCount(INT channel);
INT IPCAM_GetMaxVideoConnectCount();
#endif
