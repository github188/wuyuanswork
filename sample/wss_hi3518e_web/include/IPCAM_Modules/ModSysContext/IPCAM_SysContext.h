//IPCAM_SysContext.h

#ifndef __IPCAM_SYSCONTEXT__
#define __IPCAM_SYSCONTEXT__
//#include "IPCAM_export.h"

//wifi
#if 0
typedef struct hk_remote_wffi_info
{
    char nettype;	//0:Infra; 1:Adhoc	
    char enctype;   //1:AUTO; 2:TKIP; 3:AES
    char authmode;  //0:none; 1:wep; 2:wpa/wpa2; 3:wpa-psk/wpa2-psk
    char ssid[37];  //wifi node name.
    //char bssid[SSID_LEN]; //wifi mac address.
    int  iSignal;
}REMOTE_INFO;       

typedef struct hk_remote_wifi_find
{
    int count;
    REMOTE_INFO wifi_info[50];
}REMOTE_WIFI_FIND;
#endif
/////////////////////////////////////////////////////////////////
#include "IPCAM_SysConfig.h"
#include "IPCAM_SysQueue.h"
#include "IPCAM_SysValue.h"

#define DEV_NET_ETH0				"eth0"
#define DEV_NET_PPP0				"ppp0"
#define DEV_NET_PPP1				"ppp1"

/////设备版本号

/////网络端口
#define DEV_NET_SERVER_PORT			4001
#define DEV_NET_RTSP_PORT			8554
#define DEV_NET_ONVIF_PORT			8888
#define DEV_NET_WEB_PORT			80


#define MAX_MAIN_LINE 8192

/////工厂参数设置
#define DEFAULT_FAC_DEVNAME				"IPCAM"
#define DEFAULT_FAC_FACNAME				"Shenzheng"
#define DEFAULT_FAC_SNNUMB				"NO201301108"
#define DEFAULT_FAC_REGCODE				"NO201301108"
#define DEFAULT_FAC_DEVCPU				"hi3518"


////网络参数
#define DEFAULT_NET_IPAADDR			"192.168.2.193"
#define DEFAULT_NET_MASKADDR		"255.255.255.0"
#define DEFAULT_NET_MACADDR			"00:20:14:09:19:18"
#define DEFAULT_NET_GWADDR			"192.168.2.1"
#define DEFAULT_NET_DNSI			"192.168.2.1"//"127.0.0.1"
#define DEFAULT_NET_DNSII			"192.168.2.1"//"8.8.8.8"

#define DEFAULT_FTP_SERVER			""
#define DEFAULT_FTP_USRNAME			""
#define DEFAULT_FTP_PASSWD			""
#define DEFAULT_FTP_SERVICEPORT		21

#define DEFAULT_MAIL_SERVER			""
#define DEFAULT_MAIL_USRNAME		""
#define DEFAULT_MAIL_PASSWD		""	
#define DEFAULT_MAIL_MAILTO			""
#define DEFAULT_MAIL_MAILFROM		""
#define DEFAULT_MAIL_SERVICEPORT	25

#define SUPER_ADMIN_USRNAME			"hk"
#define SUPER_ADMIN_PASSWD			"hk"
#define ADMIN_USRNAME				"admin"
#define ADMIN_PASSWD				"admin"

#define DEV_MODEL					"HK01"
#define HOSTNAME					"HK"

#define DEFAULT_PPPOE_USRNAME		""
#define DEFAULT_PPPOE_PASSWD		""
#define DEFAULT_PPPOE_PPPOEIP		""

#define DEFAULT_DDNS0_SERNAME		"www.ddns1.com"
#define DEFAULT_DDNS0_USRNAME		"username1"
#define DEFAULT_DDNS0_PASSWD		"*******"

#define DEFAULT_DDNS1_SERNAME		"www.ddns2.com"
#define DEFAULT_DDNS1_USRNAME		"username2"
#define DEFAULT_DDNS1_PASSWD		"*******"

#define NTP_SERVERI					"clock.isc.org" //复旦大学NTP服务器
#define NTP_SERVERII				"time.nist.gov"



#define	CFG_FILE_PATH "/sys_fac/ipcam.cfg"


typedef struct  _IPCAM_SYSCONTEXT{
	LPIPCAM_SYSCONFIG  	ipcam_SysConfig;
	LPIPCAM_SYSBUFFER 	ipcam_SysBuffer;
	LPIPCAM_VARIABLE  	ipcam_SysVariable;
} IPCAM_SYSCONTEXT,*LPIPCAM_SYSCONTEXT;

// IPCAM_InitSystemContext涵数内部主要是调用内部三个涵数的实现。
//内部主要是给IPCAM_SYSCONTEXT 全局变量赋值。
INT 	IPCAM_InitSystemContext (char *filename); 
void	IPCAM_DelInitSystemContext ();
INT     IPCAM_SaveSystemContext(char *filename);
LPIPCAM_SYSCONTEXT  IPCAM_GetSystemContext() ;

int IPCAM_setTskName(char * name);


#endif


