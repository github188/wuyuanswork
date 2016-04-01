//IPCAM_export.h

#ifndef __IPCAM_EXPORT__
#define __IPCAM_EXPORT__


////////////全局定义/////////////////////////
#include "IPCAM_Global.h"
////////////扩展库///////////////////////////

//Web服务器
#include "IPCAM_ExtModules/IPCAM_WebServer/IPCAM_WebServer.h"
//XML
#include "IPCAM_ExtModules/IPCAM_Xml/LIB_Xml.h"
//onvif服务器
//#include "IPCAM_ExtModules/IPCAM_Onvif/OVF_Export.h"
#include "IPCAM_ExtModules/ExMod_OnvifServer/onvif_api.h"
//RTSP标准库支持
#include "IPCAM_ExtModules/IPCAM_Rtsp/LIB_Rtsp.h"
//PTZ协议支持
#include "IPCAM_ExtModules/ExMod_PtzCtrl/ExMod_PtzCtrl.h"
//DDNS
#include "IPCAM_ExtModules/ExMod_Ddns/ExMod_Ddns.h"

//20150317 Onvif 初始化
#include "IPCAM_Modules/ModOnvifServer/OnvifServerPtz.h"

//系统上下文
#include "IPCAM_Modules/ModSysContext/IPCAM_SysContext.h"
//多语言模块 
#include "IPCAM_Modules/ModMulLang/IPCAM_MulLang.h"
//网络服务
#include "IPCAM_Modules/ModNetWork/IPCAM_Netexport.h"
//RTSP初始化
//#include "IPCAM_Modules/ModRtsp/IPCAM_NetSvRtsp.h"
//ONVIF初始化
//#include "IPCAM_Modules/ModOnvif/IPCAM_Onvif.h"

//程序日志的写入与读取
#include "IPCAM_Modules/ModLog/IPCAM_Log.h"
#endif//__IPCAM_EXPORT__


