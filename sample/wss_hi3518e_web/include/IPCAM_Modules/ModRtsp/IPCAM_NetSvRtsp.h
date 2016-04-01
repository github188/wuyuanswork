/////////////////////////媒体流协议结构定义/////////////////////
typedef enum{
 STREAM_ENCTYPE_VIDEO_MJPEG       =0,
 STREAM_ENCTYPE_VIDEO_MPEG4       =1,
 STREAM_ENCTYPE_VIDEO_h264        =2,
 STREAM_ENCTYPE_AUDIO_PCM8X8K     =6,
 STREAM_ENCTYPE_AUDIO_PCM16X8K    =7,
 STREAM_ENCTYPE_AUDIO_ADPCM16X8K  =8,
 STREAM_ENCTYPE_AUDIO_AMR16X8K    =9,
 STREAM_ENCTYPE_AUDIO_G711UL      =10,
 STREAM_ENCTYPE_AUDIO_G711AL      =11,
 STREAM_ENCTYPE_AUDIO_AAC         =12,

}ENU_STREAMENCTYPE;
typedef enum{
STREAM_VIDEO_I_FRAME			 =0,
STREAM_VIDEO_P_FRAME			 =1,
STREAM_VIDEO_B_FRAME			 =3,
}ENU_STREAMFRAMTYPE;

#ifndef _IPCAM_NETSVRTSP_H
#define _IPCAM_NETSVRTSP_H

BOOL    IPCAM_RtspInit          (INT nRtspPort , INT bRtspPasswdAuth);
VOID    IPCAM_RtspDeinit        ();
BOOL    IPCAM_RtspIsRTSP        (CHAR *RecBuf,INT nBufLength);
BOOL    IPCAM_RtspStart         (INT socketID,struct sockaddr_in *client_addr,CHAR *RecBuf,INT nBufLength);
BOOL   	RtspCallbackAuthCheck(CHAR *pzName ,CHAR *pzPassword);

#endif//_IPCAM_NETSVRTSP_H
