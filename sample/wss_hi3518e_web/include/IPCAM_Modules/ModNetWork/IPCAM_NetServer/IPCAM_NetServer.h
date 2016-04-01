//IPCAM_NetServer.h

/*##############################################################################
#工程描述:
#       IP网络摄像机
#
#文件描述:
# 
#作者信息:
#         创建
#版权信息:
#       Copyright(c) 2008~201x 
#  	    All rights reserved.
###############################################################################*/


#ifndef IPCAM_NETWORK_H
#define IPCAM_NETWORK_H
//#include "IPCAM_Export.h"


INT IPCAM_StartWebServer();
INT  IPCAM_StopNetServer(); 



VOID IPCAM_SemClean();
VOID IPCAM_SemWaitNetSvParm(void);
VOID IPCAM_SemPostNetSvParm(void);
INT  IPCAM_SemTryWaitNetSvParm(INT WaitTime);

//#define WAITTING_NETSVPARAMSEM IPCAM_SemWaitNetSvParm();

#define WAITTING_NETSVPARAMSEM IPCAM_SemTryWaitNetSvParm(3)
#define CLEANING_NETSVPARAMSEM IPCAM_SemClean();
#define POSTTING_NETSVPARAMSEM IPCAM_SemPostNetSvParm();
#endif

