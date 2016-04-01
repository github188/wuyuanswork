

#ifndef _IPCAM_NETSVRTSP_H
#define _IPCAM_NETSVRTSP_H

BOOL    IPCAM_RtspInit          (INT nRtspPort , INT bRtspPasswdAuth);
VOID    IPCAM_RtspDeinit        ();
BOOL    IPCAM_RtspIsRTSP        (CHAR *RecBuf,INT nBufLength);
BOOL    IPCAM_RtspStart         (INT socketID,struct sockaddr_in *client_addr,CHAR *RecBuf,INT nBufLength);
BOOL   	RtspCallbackAuthCheck(CHAR *pzName ,CHAR *pzPassword);

#endif//_IPCAM_NETSVRTSP_H





