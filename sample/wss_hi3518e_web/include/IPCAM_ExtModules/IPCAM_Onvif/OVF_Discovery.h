//OVF_Disconvery.h
/*################################################################################
#Project Description:
#      OVIF 协议SDK
#
# The File Description:
#      OVIF 协议 设备发现
# Note:
#      1.OVIF 设备发现固定使用组播地址239.255.255.250:3702 接收客户端的设备查找信息
#        并回复查找
#
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/

#ifndef OVF_DISCOVERY_H
#define OVF_DISCOVERY_H

#include "OVF_Global.h"
//////////DISCONVERY
typedef struct tagOVFDISCONVERYINFO
{
	CHAR    DevGuid       [OVFCHARLENTH];    //设备的全球唯一ID:464A4854-4656-5242-4530-313035394100
	CHAR    DevName       [OVFCHARLENTH];    //设备名称:IPCAM_DEV
	CHAR    DevRootUrl    [OVFCHARLENTH];    //设备访问根路径:http://192.168.1.1/device OR http://name.3322.com/device
	CHAR    DevLocation   [OVFCHARLENTH];    //设备安装位置:SHENGZHEN/FUTIAN/TIANAN(级数不益过多)
    CHAR    DevType       [OVFCHARLENTH];    //WS标组设备类型:IPCAM=IPCAMWSDEVICETYPE
    CHAR    DevTypeII     [OVFCHARLENTH];    //厂家定义的设备类型:IPCAM_NO20111212
}OVFDISCONVERYINFO,*LPOVFDISCONVERYINFO;

//回调接口
typedef struct  tagCALLBACKOVFDISCOVERY
{   //获取设备发现相关参数
	BOOL  (*GetDiscoveryInfo)                (LPOVFDISCONVERYINFO lpDiscoveryInfo);
}CALLBACKOVFDISCOVERY,*LPCALLBACKOVFDISCOVERY;

#endif//OVF_DISCOVERY_H


