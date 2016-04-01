//LIB_RTSP.H
/*##############################################################################
#Project Description:
#      
#
# The File Description:
# 该库支持TCP负载流，运用时可作为TCP综合服务的一部分，库可支持视频类型为MPEG1,
# MPEG4 ,H264,音频支持PCM8X8000,AMR等，能兼容QT,Real,VLC等主流播放器。RTSP_Init()
# 调用初始化RTSP库,调用须提供RTSPCALLBACK的模块回调入口，回调内用户须创建流发生
# 线程以及对流控消息的有效响应(参看实例代码)，RTSP_StreamCreate(),RTSP_StreamInit()
# 用于创建流服务，pStreamSample为码流样本，视频码流样本需要Iframe，用于初始化流服务.
# 如果RTSP_StreamCreate()调用时已提供码流样本则RTSP_StreamInit()可不必调用。
# RTSP_Start()提供TCP的RTSP伴随服务,RTSP_StreamSendData()发送流数据，RTSP_StreamGetStatus()
# 用于在发送线程中检查流服务状态。
# Authors:
#       
#       
#Copyright:
#       Copyright(c) 2008~200x 
#  	  Fifo2005@gmail All rights reserved.
###############################################################################*/
 
#ifndef __LIB_RTSP_H
#define __LIB_RTSP_H

#ifndef HRTSPSERVER 
#define HRTSPSERVER INT
#endif//HRTSPSERVER
#ifndef HRTSPSTREAM
#define HRTSPSTREAM INT
#endif//HRTSPSTREAM


#ifndef CHAR
#define CHAR char
#endif//CHAR
#ifndef INT 
#define INT int
#endif
#ifndef UINT 
#define UINT unsigned int
#endif
#ifndef VOID
#define VOID void
#endif
#ifndef BOOL 
#define BOOL int
#endif
#ifndef TRUE
#define TRUE (INT) 1
#endif
#ifndef FALSE
#define FALSE (INT)0
#endif
typedef enum {
  STREAM_NULL          =0,
  STREAM_VIDEO_MPEG1   =1,
  STREAM_VIDEO_MPEG4   =2,
  STREAM_VIDEO_H264X   =3,
  STREAM_AUDIO_PCM     =4,
  STREAM_AUDIO_G722    =5,
  STREAM_AUDIO_G723    =6,
  STREAM_AUDIO_AAC     =7,
  STREAM_AUDIO_AMR     =8,
  STREAM_AUDIO_ULAW    =9,
  STREAM_AUDIO_ALAW    =10,
}ENU_STREAMTYPE;

typedef enum{
    RTSP_PLAY          =5,
    RTSP_REPLAY        =6,
    RTSP_PAUSE         =7,
    RTSP_TEARDOWN      =8,
    RTSP_ERROR         =11,  
    RTSP_DESTROY       =15,    
}ENU_RTSPMSG;

typedef enum{
    RTSP_MEDIA_NULL   =0,
    RTSP_MEDIA_TEXT   =1,
    RTSP_MEDIA_VIDEO  =2,
    RTSP_MEDIA_AUDIO  =4,  
}ENU_RTSPMEDIA;

typedef  INT  (*CBNEWSTREAM)(VOID * obj,CHAR* uMsg);
typedef  INT  (*CBAUTHCHECK)(CHAR *UserName,CHAR *Password); //LIBRTSP传递客户端用户名.帐号,函数返回TRUE 通过验证，FALSE 未通过

INT  			RTSP_Init                   (int Rtsp_port,CBNEWSTREAM  CallBackStream,BOOL isAuthCheck,CBAUTHCHECK CallBackAuth);
VOID    		RTSP_DeInit ();
INT             RTSP_StreamSendData       (INT  hRtspStream,ENU_RTSPMEDIA  MediaType, CHAR *pBuf, INT nLen,int nFrameRate,int nASendTime);
ENU_RTSPMSG     RTSP_StreamGetStatus      (INT  hRtspStream);
UINT            RTSP_StreamGetMediaType   (INT  hRtspStream);
CHAR           *RTSP_StreamGetPath        (INT  hRtspStream);
UINT               RTSP_StremExit(INT  hRtspStream);
VOID            RTSP_StreamSetDTInterval  (INT  hRtspStream,ENU_RTSPMEDIA  MediaType,INT DTInterval);

BOOL            RTSP_IsRTSP               (CHAR *pBuff,INT nBuffLen);

#endif

