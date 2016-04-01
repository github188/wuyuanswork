//OVF_DeviceManager.h
/*################################################################################
#Project Description:
#      OVIF 协议SDK
#
# The File Description:
#      OVIF 协议 设备管理
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
#ifndef OVF_DEVICEMANAGER_H
#define OVF_DEVICEMANAGER_H
//OVF服务信息
#include "OVF_DeviceManager_OvfInfo.h"
//网络配置
#include "OVF_DeviceManager_NetWork.h"
//帐户配置
#include "OVF_DeviceManager_User.h"
//IO配置
#include "OVF_DeviceManager_Io.h"
//系统配置及相关操作
#include "OVF_DeviceManager_System.h"
//系统安全及证书操作
#include "OVF_DeviceManager_Security.h"
typedef struct tagCALLBACKDEVMS
{
//OVF相关特性获取

  BOOL  (*GetImg)                (char*     addr); 
	BOOL  (*GetDevServerCap)                (LPDEVSVCAP     lpDevSvCap);    //获取设备可支持的OVF特性服务
	BOOL  (*GetSystemUrl)                   (LPSYSTEMURL    lpSystemUrl);   //获取系统一些附加的URL
	
	BOOL  (*GetDPAddress)                   (LPNETHOST      lpNetHost);     //设备发现代理服务器
    BOOL  (*SetDPAddress)                   (LPNETHOST        NetHost);
//网络.参数
    BOOL  (*GetNetInterface)                (LPNETINTERFACES lpNetInterfaces);
    BOOL  (*SetNetInterface)                (CHAR* InterfaceToken, LPNETINTERFACE NetInterface);
    BOOL  (*GetNetConfigExt)                (LPNETEXTCONFIG lpNetExtConfig);
    BOOL  (*SetNetConfigExt)                (LPNETEXTCONFIG   NetExtConfig,ENU_NETCFG_CMD SetCmd);
//网络.协议
    BOOL  (*GetNetProtocols)                (LPNETPROTOCALS lpNetProtocals);
    BOOL  (*SetNetProtocols)                (LPNETPROTOCALS   NetProtocals);
//网络.零配置
    BOOL  (*GetNetZeroConfig)               (LPNETZEROCONFIG lpNetZeroConfig);
    BOOL  (*SetNetZeroConfig)               (LPNETZEROCONFIG   NetZeroConfig);
//网络.IP过滤
    BOOL  (*GetNetIPAddressFilter)          (LPIPADDRFILTER  lpNetAddrFilter);
    BOOL  (*SetNetIPAddressFilter)          (LPIPADDRFILTER    NetAddrFilter);
    BOOL  (*AddNetIPAddressFilter)          (LPIPADDRFILTER    NetAddrFilter);
    BOOL  (*RemNetIPAddressFilter)          (LPIPADDRFILTER    NetAddrFilter);
//网络.WIFI扩展函数
    BOOL  (*WifiGetDot11Cap)                (LPDOT11CAP       lpNetDot11Cap);
    BOOL  (*WifiGetDot11Status)             (CHAR *InterfaceToken,LPNETDOT11STATUS lpNetDot11Status);
    BOOL  (*WifiScanHotPoint)               (CHAR *InterfaceToken,LPDOT11HOTPOINTS lpNetDot11HotPoints);
//IO.输出
    BOOL  (*GetRelayOutputs)                (LPIORELAYOUTPUTS   lpIoRelayOutPuts );
    BOOL  (*SetRelayOutput )                (CHAR *IoToken,LPIORELAYOUTSET   IoRelayOutSet);
    BOOL  (*SetRelayActive)                 (CHAR *IoToken,ENU_IORELAYLOGIC  IoRelayLogic);
//用户.远程用户
    BOOL  (*GetRemoteUser)                  (LPREMOTEUSER lpRemoteUser);
    BOOL  (*SetRemoteUser)                  (LPREMOTEUSER   RemoteUser);
//用户.系统用户
    BOOL  (*GetUsers)                       (LPUSERS  lpUsers );
    BOOL  (*SetUsers)                       (LPUSERS    Users );
    BOOL  (*AddUsers)                       (LPUSERS    Users );
    BOOL  (*DelUsers)                       (LPUSERS    Users );
//系统.维护
    BOOL  (*SysReboot)                      ();
    BOOL  (*SysGetLog)                      (LOGTYPE LogType,LPSYSTEMLOGS lpSystemLog);
    BOOL  (*SysBackup)                      (LPBACKUPFILES lpBackupFiles);
    BOOL  (*SysGetSuportInfo)               (LPSUPORTINFO  lpSuportInfo);
    BOOL  (*SysGetDeviceInfo)               (LPDEVICEINFO  lpDeviceInfo);
    BOOL  (*SysSetFactoryDefault)           (ENU_FACTORYDEFFAULT FactoryDefaultType);
    BOOL  (*SysGetDateTime)                 (LPDATETIME lpGetDatetime);
    BOOL  (*SysSetDateTime)                 (LPDATETIME   SetDatetime);
    BOOL  (*SysStartFirewareUpGrade)        (LPUPGRADE    lpFirewareUpdate);
    BOOL  (*SysUpGradeFireware)             (LPATTACHMENTDATA  DataFireware);
    BOOL  (*SysStartSystemRestore)          (LPRESTORESYSTEM  lpRestoreSystem);
    BOOL  (*SysRestoreSystem)               (LPATTACHMENTDATA  DataRestore);
    
//安全.SSL (保留)
//安全.证书(保留)
//安全.11x (保留)
}CALLBACKDEVMS,*LPCALLBACKDEVMS;


#endif//OVF_DEVICEMANAGER_H

