//OVF_DeviceManager_OvfInfo.h
/*################################################################################
#Project Description:
#      OVIF 协议SDK
#
# The File Description:
#      OVIF 协议 设备管理.OVIF参数及兼容性
# Note:
#      1.
#
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_DEVICEMANAGER_OVFINFO_H
#define OVF_DEVICEMANAGER_OVFINFO_H
typedef struct tagDEVMSVCAP_NET
{
	BOOL SupIPFilter ;	                      //IP过滤:FALSE?TRUE
	BOOL SupZeroConfiguration ;	              //网络零配置:FALSE?TRUE
	BOOL SupIPVersion6 ;	                  //IPV6:FALSE
	BOOL SupDynDNS ;	                      //动态域名:TRUE
	BOOL SupDot11Configuration ;	          //802.11X配置:FALSE
	BOOL SupHostnameFromDHCP ;	              //DHCP获取主机名:FALSE
	BOOL SupNTP ;	                          //NTP:TRUE
}DEVMSVCAP_NET;
typedef struct tagDEVMSVCAP_SECURT
{
	BOOL SupTLS1_x002e0 ;	                  //支持SSL加密，下同:FALSE
	BOOL SupTLS1_x002e1 ;	 
	BOOL SupTLS1_x002e2 ;	 
	BOOL SupOnboardKeyGeneration ;	          //:FALSE 
	BOOL SupAccessPolicyConfig ;	          //访问规则:TRUE?FALSE
	BOOL SupDot1X ;	                          //802.11x加密规则:FALSE
	BOOL SupRemoteUserHandling ;	          //远程登录帐户管理:TRUE?FALSE
	BOOL SupX_x002e509Token ;	              //509令牌:FALSE
	BOOL SupSAMLToken ;	                      //SAML令牌:FALSE
	BOOL SupKerberosToken ;	                  //Kerberos令牌:FALSE
	BOOL SupUsernameToken ;	                  //帐户令牌:FALSE?TRUE
	BOOL SupHttpDigest ;	                  //http数字签名:FALSE?TRUE
	BOOL SupRELToken ;	                      //rel令牌:FALSE?TRUE
}DEVMSVCAP_SECURT;
typedef struct tagDEVMSVCAP_SYS
{
	BOOL SupDiscoveryResolve ;	              //发现操作,下同:TRUE 
	BOOL SupDiscoveryBye ;	              
	BOOL SupRemoteDiscovery ;	 
	BOOL SupSystemBackup ;	                  //系统备份:TRUE?FALSE
	BOOL SupSystemLogging ;	                  //log :TRUE?FALSE
	BOOL SupFirmwareUpgrade ;	              //系统升级:TRUE?FALSE
	BOOL SupHttpFirmwareUpgrade ;	          //http在线升级:TRUE?FALSE
	BOOL SupHttpSystemBackup ;	              //http系统备份:TRUE?FALSE
	BOOL SupHttpSystemLogging ;	              //http log查阅:TRUE?FALSE
	BOOL SupHttpSupportInformation ;	      //http 系统信息查看:TRUE?FALSE
	
}DEVMSVCAP_SYS;
typedef struct tagDEVMSVCAP_ANALYTICS
{
	CHAR SupXAddr[OVFCHARLENTH];	          //视频分析服务路径:NULL
	BOOL SupRuleSupport;	                  //支持视频分析规则:FALSE
	BOOL SupAnalyticsModuleSupport;	          //视频分析模块支持:FALSE
}DEVMSVCAP_ANALYTICS;
typedef struct tagDEVMSCAP_IO
{
	INT  InputConnectors;	                  //输入端子
	INT  RelayOutputs;	                      //关联输出端子
}DEVMSCAP_IO;
typedef struct tagDEVMSCAP_EVENT
{
	CHAR   SupXAddr[OVFCHARLENTH];	          //事件服务URL:NULL
	BOOL   SupWSSubscriptionPolicySupport;    //WS描述之事件订阅支持:FALSE
	BOOL   SupWSPullPointSupport;    	      //WS描述之事件推送支持:FALSE
	BOOL   SupWSPausableSubscriptionManagerInterfaceSupport;	//WS描述的订阅脉搏接口支持:FALSE

}DEVMSCAP_EVENT;
typedef struct tagDEVMSCAP_IMAG
{
	CHAR   SupXAddr[OVFCHARLENTH];              //图像配置URL
}DEVMSCAP_IMAG;
typedef struct tagDEVMSCAP_LIVESTREAM
{
	BOOL SupRTPMulticast;	                    //RTP多播:TRUE
	BOOL SupRTP_USCORETCP;	                    //RTP的TCP负载:TRUE
	BOOL SupRTP_USCORERTSP_USCORETCP;	        //RTSP的TCP负载:TRUE    
}DEVMSCAP_LIVESTREAM;
typedef struct tagDEVMSCAP_MEDIA
{
	CHAR  SupXAddr[OVFCHARLENTH];       
	DEVMSCAP_LIVESTREAM Streaming;	           //媒体信息

}DEVMSCAP_MEDIA;
typedef struct tagDEVMSCAP_PTZ
{
	CHAR  SupXAddr[OVFCHARLENTH];              //服务路径  	     

}DEVMSCAP_PTZ;
typedef struct tagDEVMSCAP_DEV
{
	CHAR                XAddr[OVFCHARLENTH];   //服务URL
	DEVMSVCAP_NET       Network;	           //设备管理
	DEVMSVCAP_SYS       System;	               //系统服务
	DEVMSCAP_IO         IO;	                   //IO
	DEVMSVCAP_SECURT    Security;	           //安全

}DEVMSCAP_DEV;
typedef struct tagDEVMSVCAP
{
    DEVMSCAP_DEV         CapDevice;            //设备管理
    DEVMSVCAP_ANALYTICS  CapAnalytics;         //分析
    DEVMSCAP_EVENT       CapEvent;             //事件
    DEVMSCAP_IMAG        CapImag;              //图像
    DEVMSCAP_MEDIA       CapMedia;             //媒体
    DEVMSCAP_PTZ         CapPTZ;               //ptz云控
}DEVMSVCAP,*LPDEVSVCAP;
/////////其他服务//////////////
typedef enum  {
 LOG_SYSTEM = 0, 
 LOG_ACCESS = 1
}ENU_TYPELOG;

typedef struct tagSYSTEMURLLOG
{
	ENU_TYPELOG LogType;	                   //Log类型
	CHAR        LogUri[OVFCHARLENTH];	       //Log读取URL
	INT         Reserve1;	                   //保留
	CHAR **     Reserve2;                      //保留
	CHAR       *Reserve3;	                   //保留
}SYSTEMURLLOG;
typedef struct tagSYSTEMURL
{
    INT           urlSystemLogSize;
	SYSTEMURLLOG  urlSystemLog[2];	
	CHAR          urlSupportInfo [OVFCHARLENTH];//系统支持，厂家技术支持
	CHAR          urlSystemBackup[OVFCHARLENTH];//系统备份

}SYSTEMURL,*LPSYSTEMURL;
//////////////////////////////////


#endif//OVF_DEVICEMANAGER_ONVFINFO_H

