//IPCAM_NetDevUpdate.h
/*
** =====================================================================================
**       Filename:  	IPCAM_NetDevUpdate.h
**    	 Description:
**						ÍøÒ³Éý¼¶
**       Version:  		0.0 
**       Created:  		
**       Revision:  	none
**       Compiler:  	gcc
**		 Author:  		
**		 Company:  		
** =====================================================================================
*/

#ifndef __RL_IPCAM_NETDEV_UPDATE_H__
#define __RL_IPCAM_NETDEV_UPDATE_H__


#define IPCAM_HOME_DIR					"/app"
#define APP_PTHNAME						IPCAM_HOME_DIR
#define WEB_BACKUPPTHNAME				IPCAM_HOME_DIR"/backup"
#define PTZ_PTHNAME						IPCAM_HOME_DIR"/ptz"
#define WEB_UPDATE_TMPDIR				"/appex/upgrade/webupdate"
#define WEB_UPDATE_BACKUPDIR			"/appex/upgrade/backup"
#define WEB_UPDATE_FILENAME				"_tmpupdate.tar.gz"


#define COMMAND_UPDATE_DEL		 		"rm -rf "
#define COMMAND_UPDATE_DEL_TMPFILE 		"rm -rf "WEB_UPDATE_TMPDIR"/"WEB_UPDATE_FILENAME

#define CLEANUP_DEL_REBOOT				0X01
#define CLEANUP_DEL 					0X02
#define RECV_IPNCPATH					"/app/ipnc"
#define IPNCPATH						"/appex/"


BOOL IPCAM_StartDevUpdate(CLINETNETINFO* pClientInfo);

#endif

