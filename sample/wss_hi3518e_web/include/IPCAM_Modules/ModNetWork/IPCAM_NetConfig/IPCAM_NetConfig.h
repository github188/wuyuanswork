//IPCAM_NetConfig.h

/*##############################################################################
#工程描述:
#       IP网络摄像机
#
#文件描述:
# 
#作者信息:
#       创建
#版权信息:
#       Copyright(c) 2008~201x 
#  	    All rights reserved.
###############################################################################*/

#ifndef __IPCAM_NETCONFIG__
#define __IPCAM_NETCONFIG__

#include "IPCAM_Export.h"
/*****************************************
回调函数类型:NETCONFIGCALLBACK 
返回值:0 正常 >0出错
注意:如果返回值大如0，相应的将会向客户端的请求返回一个错误回应。
 ******************************************/
typedef INT(*NETCONFIGCALLBACK)(INT socket,ULONG msgType,VOID *data);
INT IPCAM_NetConfig(NETMSGPACKET	*sp, INT sock,NETCONFIGCALLBACK func);

#endif

