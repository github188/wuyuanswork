//IPCAM_NetWebCallback.c

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


#ifndef _NETWEBCALLBACK_H
#define _NETWEBCALLBACK_H

//#include "IPCAM_Export.h"


INT  CallBack_Cgi(HWEBCGI hWebCgi,CHAR *CgiPath);
INT  Callback_Mjpeg    (INT Socket,INT Channel ,INT GetType);
INT     CallBackNetConfig (INT socket,ULONG msgType,void *data);
INT                   Callback_AuthCheck(CHAR *pzUserName,CHAR* pzPassword);

#endif//_NETWEBCALLBACK_H

