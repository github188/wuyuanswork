//OVF_Export.h
/*################################################################################
#Project Description:
#      OVIF 协议SDK
#
# The File Description:
#      OVIF SDK 导出文件
# Note:
#      1.编程方仅需导入本文件即可。
#      2.OVF_Init/DeInit 用于启动和卸载OVIF服务模块,OVIF服务模块内建服务，占用一个
#        TCP端口和一个UDP端口,UDP端口是随机的，OVIF的设备发现操作使用固定的组播通道
#        参见OVF_Discovery部分定义，该端口是独占方式。
#      3.编程方按回调函数结构和和函数定义注入函数，不注入函数结构，则该设备对模块
#        不支持，不注入对应函数，者对应操作不支持。
#        
#      4.命名规则:
         4.1 函数和参数使用匈牙利命名法。
         4.2 带有lpxxx前缀的为输入变量，反之是输出变量.
#      5.函数带参的结构指针除非特别申明，均由OVIF模块内部管理，回调内部只需使用即可。
#      6.OVF 标准定义有个有独立的IO管理器，但与Device内的IO管理和Imaging内和Media内
#        相关操作重复，此API接口去除。
       7.OVF 在声明IVT(ipcam)这类设备协议族时未声明支持事件处理，但在NVR(DVR)等设备形态
       有声明也定义了相关协议。
       8.声明为保留的部分留作兼容使用，编码可不用支持
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_EXPORT_H
#define OVF_EXPORT_H

#include "OVF_Global.h"

//////设备发现接口
#include "OVF_Discovery.h"
//////设备管理接口
#include "OVF_DeviceManager.h"
//////媒体控制接口
#include "OVF_Media.h"
//////摄像头控制接口
#include "OVF_Imaging.h"
//////云台控制接口
#include "OVF_Ptz.h"
//////事件服务接口
//////IO  控制接口
//////存储控制接口
//////视频分析接口

///////

//////ONVIF 模块接口
typedef struct tagCALLBACKOVF
{
	CALLBACKOVFDISCOVERY      *CallBackDiscovery;                                   //设备发现相关回调入口:OVF_Discovery.h
	CALLBACKDEVMS             *CallBackDevManage;                                   //设备管理回调入口    :OVF_DevManager.h
	CALLBACKIMAGING           *CallBackImaging;                                     //摄像头,CCD/CMOS etc.:OVF_Imaging.h
	CALLBACKMEDIA             *CallBackMedia;                                       //媒体处理            :OVF_Media.h
	CALLBACKPTZ               *CallBackPtz;                                         //Ptz接口             :OVF_Ptz.h
}CALLBACKOVF,*LPCALLBACKOVF;
//模块入口
HDOVF   OVF_Init            (UINT usIP,USHORT usPort,USHORT TimeOut,CALLBACKOVF*lpCallBack ); //TCP的服务器端口,TimeOut单位为秒,usPort为0时不主动创建服务，使用IsONVIF(),和StartONVIF执行一次ONVIF请求
VOID    OVF_DeInit          (HDOVF  hOVF);                                          //卸载OVF服务模块
//属性接口
BOOL    OVF_EnableDiscovery (HDOVF  hOVF ,BOOL IsEnable);                           //关闭或打开设备搜寻服务
//一次性服务接口
BOOL    OVF_IsONVIF         (HDOVF  hOVF ,CHAR*Buff,USHORT BufLenth);               //
BOOL    OVF_StartONVIF      (HDOVF  hOVF ,CHAR*Buff,USHORT BufLenth,INT nSocket,SOCKETIN *SocketIn);
//其他辅助功能函数
VOID    OVF_Sleep           (UINT   Seconds);
VOID    OVF_MSleep          (UINT   Milliseconds);
BOOL    OVF_CreateUUIDS     (CHAR  *sUUID);                                         //创建一个全球标志量
#endif//OVF_EXPORT_H

