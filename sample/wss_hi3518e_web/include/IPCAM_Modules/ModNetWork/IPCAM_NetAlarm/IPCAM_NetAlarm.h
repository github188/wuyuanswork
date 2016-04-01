#ifndef _IPCAM_NETALARM_H_
#define _IPCAM_NETALARM_H_
#define IPCAM_NETALARM_MAX_SOCKETFD			50
typedef struct{
	UCHAR	IsEnable;
	INT		CliSocket;
}AlarmClientInfo;


INT IPCAM_NetAlmAddSocket(INT AlmSocketFd);
INT IPCAM_NetAlmServiceInit();


#endif
