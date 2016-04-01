//OVF_Devicemanager_network.h
/*################################################################################
#Project Description:
#      OVIF 协议SDK
#
# The File Description:
#      OVIF SDK 设备管理.网络
# Note:
#      1.OVIF 所有网络端接口有定义IPV6,但这里暂时保留。
#
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_DEVICEMANAGER_NETWORK_H
#define OVF_DEVICEMANAGER_NETWORK_H


typedef enum {
    IPTYPE_V4                 = 0,
    IPTYPE_V6                 = 1,
    IPTYPE_DNS                = 2,
}ENU_NETIPTYPE;
typedef enum {
    DDNS_UPDATENULL           = 0,
    DDNS_UPDATECLIENT         = 1,
    DDNS_UPDATESERVER         = 2,
}ENU_NETUPDATETYPE;
typedef enum 
{
    DO11SEC_NULL              = 0, 
    DO11SEC_WEP               = 1, 
    DO11SEC_PSK               = 2,
    DO11SEC_DOT1X             = 3, 
    DO11SEC_EXT               = 4,
}ENU_DOT11SECURITYMODE;
typedef enum 
{
    DO11CIP_CCMP              = 0,
    DO11CIP_TKIP              = 1, 
    DO11CIP_ANY               = 2,
    DO11CIP_EXT               = 3,
 }ENU_DOT11CIP;
typedef enum 
 {  DOT11SIGNAL_NULL          = 0,
    DOT11SIGNAL_VERBAD        = 1,
    DOT11SIGNAL_BAD           = 2,
    DOT11SIGNAL_GOOD          = 3,
    DOT11SIGNAL_VERYGOOD      = 4,
    DOT11SIGNAL_EXTENDED      = 5,
 }ENU_DOT11SIGNAL;

typedef enum
{
    NETCFG_CMD_SETHOSTNAME    = 0,
    NETCFG_CMD_SETHOSTNAMEDHCP= 1,
	NETCFG_CMD_SETDNS         = 2,
	NETCFG_CMD_SETNTP         = 3,
	NETCFG_CMD_SETDNYDNS      = 4,
	NETCFG_CMD_SETGATEWAY     = 5,
}ENU_NETCFG_CMD;
typedef enum  
{
    DO11STATION_ADHOC          = 0, 
    DO11STATION_INFRASTRUCTURE = 1,
    DO11STATION_EXT            = 2,
 }ENU_DOT11STATION;
typedef enum 
 {NET_PROTOCOLTYPE_HTTP        = 0, 
  NET_PROTOCOLTYPE_HTTPS       = 1,
  NET_PROTOCOLTYPE_RTSP        = 2
 }ENU_NETPROTOCALTYPE;
typedef enum 
{   IPADDRFILTER_ALLOW         = 0,
    IPADDRFILTER_DENY          = 1,
}ENU_IPADDRFILTER;

typedef struct tagNETEXTTION
{
	INT                  NetSize;
	CHAR               **NetReserve1;
}NETEXTION,*LPNETEXTION;
typedef struct tagNETHOST
{
	ENU_NETIPTYPE         NetType;	
	CHAR                  NetIPV4    [2][OVFCHARLENTH];
	CHAR                  NetIPV6    [2][OVFCHARLENTH];	
	CHAR                  NetDNSname [2][OVFCHARLENTH];	
	NETEXTION            *NetReserve1;	
	CHAR                 *NetReserve2;
}NETHOST,*LPNETHOST;
typedef struct tagNVFINTERFACEINFO
{
	CHAR                  InfoName[OVFCHARLENTH];	
	CHAR                  InfoHwAddress[OVFCHARLENTH];	
	INT                   InfoMTU;	
}NVFINTERFACEINFO;
typedef struct tagIPV4ADDRESS
{
	CHAR                  ipv4Address [OVFCHARLENTH];	
	INT                   ipv4Length;	                     //strlen(ipv4Address)
}IPV4ADDRESS;
typedef struct tagIPV4CONFIG
{
    INT                   ipv4SizeManual;	
	IPV4ADDRESS           ipv4Manual;	
	IPV4ADDRESS           ipv4LinkLocal;	                 //本地链接，环路链接 （仅读取）
	IPV4ADDRESS           ipv4FromDHCP;	                     //DHCP地址，(仅读取）
	BOOL                  ipv4DHCP;	
	INT                   ipv4Reserve1;	
	CHAR                **ipv4Reserve2;
	CHAR                 *ipv4Reserve3;	            
    
}IPV4CONFIG;
typedef	struct tagWIFIHEXBIN
{
    CHAR                  BinData[OVFCHARLENTH];
	INT                   BinSize;
}WIFIHEXBIN;
typedef struct tagWIFIPSK
{
	WIFIHEXBIN            PskBinKey;	
	CHAR                  PskPassphrase[128];	
	NETEXTION             PskExtension;	
	CHAR                 *PskReserve1;	
}WIFIPSK;

typedef struct tagWIFISECURITY                                 //WIFI安全规范
{
	ENU_DOT11SECURITYMODE WifiSecMode;	
	ENU_DOT11CIP          WifiCipAlgorithm;	
	WIFIPSK               WifiSecPSK;	
	CHAR                  WifiDot1X[256];	

}WIFISECURITY;
typedef struct tagWIFICONFIG
{
	WIFIHEXBIN            WifiSSID;	
	ENU_DOT11STATION      WifiMode;
	CHAR                  WifiAlias[OVFCHARLENTH];	
	INT                   WifiPriority;	
	WIFISECURITY          WifiSecurity;	

}WIFICONFIG;
typedef struct tagNETINTERFACE
{
	CHAR                  NetToken[OVFCHARLENTH];	
	BOOL                  NetEnabled;
	NVFINTERFACEINFO      NetInfo;                         //仅读取
    VOID                 *NetLinkRes;                      //包含有网卡物理配置参数，无实际运用意义，此处略去
	IPV4CONFIG            NetIPv4;
    VOID                 *NetIPV6Res;                      //IPV6，保留
    WIFICONFIG            NetWifiConfig;
    CHAR                 *NetAttbRes;                      //特性，保留
    BOOL                  NetIsWifi;                       //WIfi  标志 （仅读取）
}NETINTERFACE,*LPNETINTERFACE;
typedef struct tagNETINTERFACES
{
    INT                   NetInterfaceSize;
    NETINTERFACE          NetInterfaces[2];
}NETINTERFACES,*LPNETINTERFACES;
typedef struct tagNETEXTCONFIG                              //附加的网络参数配置
{   //网络.主机名
    CHAR                  NetHostName[OVFCHARLENTH];
    BOOL                  NetHostNameFormDHCP;
    //网络.DNS
    INT                   NetDnsIPV4Size;
    CHAR                  NetDnsIPV4 [2][OVFCHARLENTH];
    BOOL                  NetDnsFromDHCP;
//  BOOL                  NetDnsType    ;                    //ENU_NETIPTYPE:IPV4/IPV6
    //网络.网关
    CHAR                  NetGateway [5][OVFCHARLENTH];
    INT                   NetGatewaySize;
    //网络.NTP
    CHAR                  NetNtpIPV4 [2][OVFCHARLENTH];
    CHAR                  NetNtpDns  [2][OVFCHARLENTH];      //NTP Name:ntp.micsoft.com
    BOOL                  NetNtpFromDHCP;
    ENU_NETIPTYPE         NetNtpType    ;
	INT                   NetNtpSize;
    //网络.DDNS
    CHAR                  NetDynamicDns [OVFCHARLENTH];
    CHAR                  NetDynamicDnsTTL[OVFCHARLENTH];
    BOOL                  NetDynamicDnsType;                 //ENU_ENUNETIPTYPE
	INT					  NetsizeSearchDomain;	
	CHAR				  NetSearchDomain[2][OVFCHARLENTH];
    
}NETEXTCONFIG,*LPNETEXTCONFIG;               

typedef struct tagNETPROTOCAL
{
	ENU_NETPROTOCALTYPE   NetProtocalType;	
	BOOL                  NetProtocalEnabled;	
	INT                   NetProtocalPort;	
}NETPROTOCAL,*LPNETPROTOCAL;

typedef struct tagNETPROTOCALS
{
    INT                   NetProtocalTypeSize;
    NETPROTOCAL           NetProtocals[3];
}NETPROTOCALS,*LPNETPROTOCALS;
typedef struct tagNETZEROCONFIG
{
	CHAR                  NetInterfaceToken[OVFCHARLENTH];
	BOOL                  NetZeroEnabled;	
	INT                   NetSizeAddresses;
	CHAR                  NetAddresses[2][OVFCHARLENTH];
}NETZEROCONFIG,*LPNETZEROCONFIG;
typedef struct tagIPADDRFILTER
{
	ENU_IPADDRFILTER      NetFilterType;
	INT                   NetSizeIPv4Address;	
	IPV4ADDRESS           NetIPv4Address[OVFMAXCHANNEL][OVFCHARLENTH];	
}IPADDRFILTER,*LPIPADDRFILTER;
typedef struct tagDOT11CAP
{
	BOOL                  NetIsTKIP;	
	BOOL                  NetIsScanAvailable;
	BOOL                  NetIsMultipleConfig;
	BOOL                  NetIsAdHocStationMode;
	BOOL                  NetIsWEP;
}DOT11CAP,*LPDOT11CAP;
typedef struct tagDOT11STATUTS                               //WIFI参数
{
	WIFIHEXBIN            WifiBinSSID;	
	CHAR                  WifiSSID[OVFCHARLENTH];
    ENU_DOT11CIP          WifiPairCipher;	
	ENU_DOT11CIP          WifiGroupCipher;	
	ENU_DOT11SIGNAL       WifiSignalStrength;	
	CHAR                  WifiActiveConfigAlias[OVFCHARLENTH];//可附加的用于配置的token
	
}NETDOT11STATUS,*LPNETDOT11STATUS;
typedef struct tagDot11HOTPOINT
{
	WIFIHEXBIN            WifiBinSSID;
	CHAR                  WifiSSID[OVFCHARLENTH];	
	ENU_DOT11SECURITYMODE WifiSecurity;	
    ENU_DOT11CIP          WifiPairCipher;	
	ENU_DOT11CIP          WifiGroupCipher;	
	ENU_DOT11SIGNAL       WifiSignalStrength;	
}DOT11HOTPOINT,*LPDOT11HOTPOINT;
typedef struct tagDot11HOTPOINTS
{
	INT                   Dot11HotPointSize;
    DOT11HOTPOINT         Dot11HotPoints[OVFMAXCHANNEL];
}DOT11HOTPOINTS,*LPDOT11HOTPOINTS;
#endif//OVF_DEVICEMANAGER_NETWORK_H


