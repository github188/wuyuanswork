//IPCAM_NetNtp.h

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
#  	   All rights reserved.
###############################################################################*/

#ifndef IPCAM_NETNTP_H
#define IPCAM_NETNTP_H

#define NTP_SERVER_NAME 		"clock.isc.org"
#define NTP_PATH				"/mnt/mtd/ntpdate"

BOOL IPCAM_StartNtp(CHAR *ServerName, INT TimeZone);

#endif


