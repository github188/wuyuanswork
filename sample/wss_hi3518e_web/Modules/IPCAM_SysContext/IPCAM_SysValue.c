//IPCAM_SysValue.c

/*##############################################################################
#工程描述:
#       IP网络摄像机
#
#文件描述:
# 
#作者信息:
#      领航员数码科技有限公司 zqw  201-04-18   创建
#版权信息:
#       Copyright(c) 2008~201x 
#  	    领航员数码科技有限公司 All rights reserved.
###############################################################################*/

#include "IPCAM_Export.h"


typedef struct _SYSTEMSTATUS
{
	INT			SystemStatus;
	INT			DiskStatus;
	INT			SDStatus;	
	INT			DatabaseStatus;
	INT			EncStatus[IPCAM_LOCAL_CHN];
	INT			SDStoreStatus[IPCAM_LOCAL_CHN];		
}IPCAM_SYSTEMSTATUS , *LPIPCAM_SYSTEMSTATUS;


static IPCAM_SYSTEMSTATUS g_SystemStatus = {0};


INT IPCAM_SetSystemStatus(INT nStatus)
{
	g_SystemStatus.SystemStatus = nStatus;

	return TRUE;
}
INT IPCAM_GetSystemStatus()
{	
	INT nStatus = 0;
	nStatus = g_SystemStatus.SystemStatus;
	return nStatus;
}

INT IPCAM_SetDiskStatus(INT nStatus)
{	
	g_SystemStatus.DiskStatus = nStatus;
	return TRUE;
}
INT IPCAM_GetDiskStatus()
{	
	INT nStatus = 0;	
	nStatus = g_SystemStatus.DiskStatus;
	return nStatus;
}

INT IPCAM_SetSDStatus(INT nStatus)
{
	g_SystemStatus.SDStatus= nStatus;
	return TRUE;

}
INT IPCAM_GetSDStatus()
{	
	INT nStatus = 0;
	nStatus = g_SystemStatus.SDStatus;
	return nStatus;
}

INT IPCAM_SetDatabaseStatus(INT nStatus)
{
	g_SystemStatus.DatabaseStatus = nStatus;
	return TRUE;

}
INT IPCAM_GetDatabaseStatus()
{	
	INT nStatus = 0;
	nStatus = g_SystemStatus.DatabaseStatus;
	return nStatus;
}



INT IPCAM_SetEncStatus(INT ch_num , INT nStatus)
{
	g_SystemStatus.EncStatus[ch_num]= nStatus;
	return TRUE;

}
INT IPCAM_GetEncStatus(INT ch_num)
{	
	INT nStatus = 0;
	nStatus = g_SystemStatus.EncStatus[ch_num];
	return nStatus;
}


INT IPCAM_SetSDStoreStatus(INT ch_num , INT nStatus)
{
	g_SystemStatus.SDStoreStatus[ch_num]= nStatus;
	return TRUE;

}
INT IPCAM_GetSDStoreStatus(INT ch_num)
{	
	INT nStatus = 0;
	nStatus = g_SystemStatus.SDStoreStatus[ch_num];
	return nStatus;

}





static INT g_VideoConnectCount[3] = {0};
static pthread_mutex_t g_VideoConnectCountMutex = PTHREAD_MUTEX_INITIALIZER;
INT IPCAM_AddOneVideoConnectCount(int channel)
{
	pthread_mutex_lock(&g_VideoConnectCountMutex);
	g_VideoConnectCount[channel]++;
	pthread_mutex_unlock(&g_VideoConnectCountMutex);
	return TRUE;
}

INT IPCAM_DelOneVideoConnectCount(int channel)
{
	pthread_mutex_lock(&g_VideoConnectCountMutex);
	g_VideoConnectCount[channel]--;
	if (g_VideoConnectCount[channel] < 0){
		g_VideoConnectCount[channel]	= 0;
	}
	pthread_mutex_unlock(&g_VideoConnectCountMutex);
	return TRUE;
}
INT IPCAM_GetVideoConnectCount(INT channel)
{
	int iRet = 0;
	pthread_mutex_lock(&g_VideoConnectCountMutex);
	iRet = g_VideoConnectCount[channel];
	pthread_mutex_unlock(&g_VideoConnectCountMutex);
	return iRet;
}

INT IPCAM_GetMaxVideoConnectCount()
{
	INT iRet = 0;
	pthread_mutex_lock(&g_VideoConnectCountMutex);
	iRet = g_VideoConnectCount[0];//g_VideoConnectCount[0] > g_VideoConnectCount[1] ? g_VideoConnectCount[0] : g_VideoConnectCount[1];
	pthread_mutex_unlock(&g_VideoConnectCountMutex);
	return iRet;
}


