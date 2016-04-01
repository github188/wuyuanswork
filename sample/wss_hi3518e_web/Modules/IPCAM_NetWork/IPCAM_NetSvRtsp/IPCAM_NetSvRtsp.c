//IPCAM_Mjpeg.c
/*##############################################################################
#Project Description:
#	   
#
# The File Description:
# 
# Authors:
# Fifo2005@gmail.com									   2011-08-29  First
#Copyright:
#		Copyright(c) 2008~200x 
#	  Fifo2005@gmail All rights reserved.
###############################################################################*/
#include<pthread.h>
#include<sys/syscall.h>
#define gettid() syscall(__NR_gettid) 
#include "IPCAM_Export.h"
//#include "Appro_interface.h"

////////////////////////////wss
typedef enum {
	VIDEO_CHANNEL_1       =0,
	VIDEO_CHANNEL_2       =1,
	VIDEO_CHANNEL_3       =2,
	VIDEO_CHANNEL_4       =3,
	VIDEO_CHANNEL_ALL     =4,
}ENU_VIDEOCHANL;
/////////////////////////////

///////////////////////////////wangshaoshu hk
/** buffer **/
#define	VBUFSIZE		(400*1024*sizeof(char)) //h264.
#define	ABUFSIZE		(1024*sizeof(char))		//g711.
////////////////////////////////


#define  RTSP_PATH_CHANNEL_1	   "1.3GP"
#define  RTSP_PATH_CHANNEL_2	   "2.3GP"
#define  RTSP_PATH_CHANNEL_1_VIDEO "1.video"
#define  RTSP_PATH_CHANNEL_2_VIDEO "2.video"
#define  RTSP_PATH_CHANNEL_1_AUDIO "1.audio"
#define  RTSP_PATH_CHANNEL_2_AUDIO "2.audio"

#define MAX_RETRY	   200
#define VIDEO_UNIT	   90000ull
#define AUDIO_UNIT	   8000ull

pthread_mutex_t   rtsp_mutex = PTHREAD_MUTEX_INITIALIZER;

#define RTSP_CHECKSTATUS(bCanSafSend,bCanSafExit,hStream)\
		switch(RTSP_StreamGetStatus(hStream)){\
		case RTSP_PLAY:\
		case RTSP_REPLAY:\
			bCanSafExit=FALSE;\
			bCanSafSend=TRUE;\
			break;\
		case RTSP_PAUSE:\
			bCanSafExit=FALSE;\
			bCanSafSend=FALSE;\
			break;\
		case RTSP_TEARDOWN:\
		case RTSP_ERROR:  \
		case RTSP_DESTROY:\
			bCanSafExit=TRUE;\
			bCanSafSend=FALSE;\
			break;\
		default:\
			break;\
		}  \


ENU_VIDEOCHANL RtspCheckChannel(INT  hRtspStream)
{
	ENU_VIDEOCHANL nChannel=VIDEO_CHANNEL_1;
	CHAR		  *pzPath  =RTSP_StreamGetPath(hRtspStream);
	
	if( !strcasecmp(pzPath,RTSP_PATH_CHANNEL_1)||
		!strcasecmp(pzPath,RTSP_PATH_CHANNEL_1_VIDEO)||
		!strcasecmp(pzPath,RTSP_PATH_CHANNEL_1_AUDIO)){
		nChannel = VIDEO_CHANNEL_1;

	}
	else if(!strcasecmp(pzPath,RTSP_PATH_CHANNEL_2)||
			!strcasecmp(pzPath,RTSP_PATH_CHANNEL_2_VIDEO)||
			!strcasecmp(pzPath,RTSP_PATH_CHANNEL_2_AUDIO)){
		nChannel = VIDEO_CHANNEL_2;

	} 
	return nChannel;
}
ULONG  RtspGetRTDtInval(ENU_RTSPMEDIA MediaType,struct timeval TVFirst,struct timeval TVSecond)
{ 
	ULLONG	  TT1 = 0;
	ULLONG	  TT2 = 0;
   
   if(TVFirst.tv_sec==0 &&TVFirst.tv_usec==0) 
	return 0;

	TT1 = TVFirst .tv_sec * 1000000 + TVFirst .tv_usec;
	TT2 = TVSecond.tv_sec * 1000000 + TVSecond.tv_usec;
	if (TT1 > TT2)return 0;

	if(RTSP_MEDIA_VIDEO==MediaType)
		return	((((ULLONG)VIDEO_UNIT)*(TT2-TT1)/1000000)/100)*100;
	if(RTSP_MEDIA_AUDIO==MediaType)
		return	((((ULLONG)AUDIO_UNIT)*(TT2-TT1)/1000000)/100)*100;

	 return 0;
   
}

VOID * RTSP_LoopAudio (VOID * lParam)
{
	struct timeval tm1;
	struct timeval tm2;
	UINT	mSec = 0;	
	int	nLastAudioFrame = 0;
	LPCFG_AUDIOINFO pAudioInfo =NULL;
	int nFrameRate;
	INT			         nChnStream        = 0 ;
	ENU_VIDEOCHANL       nChannelID     = VIDEO_CHANNEL_1;
	LPIPCAM_AUDIOBUFFER  pADataInstance = NULL;
	INT                  rIndex         = 0;
	nChnStream			= (int*)lParam;
	IPCAM_PTHREAD_DETACH;
	if(NULL==(pADataInstance=calloc(sizeof(CHAR),sizeof(IPCAM_AUDIOBUFFER))))
	{
		return NULL;
	}
	
	IPCAM_DEBUG("[RTSP]:Audio Beginning ...");
	IPCAM_setTskName("RTSP_LoopAudio");
	gettimeofday(&tm1,NULL);	
	while (1)
	{
		if(TRUE == IPCAM_GetStreamData(VIDEO_LOCAL_RECORD,nChannelID,VOIDEO_MEDIATYPE_AUDIO,&rIndex,(HANDDATABUFFER)pADataInstance))		
		{			
			//printf("Audio----get------nChannelID=%d,---len=%d,pADataInstance->dwFrameNumber=%d,nLastAudioFrame=%d\n",nChannelID,pADataInstance->dwFameSize,pADataInstance->dwFrameNumber,nLastAudioFrame);
		#if 1
			if(1 == (pADataInstance->dwFrameNumber-nLastAudioFrame))
			{
				gettimeofday(&tm2,NULL);			
				mSec= (tm2.tv_sec*1000 +tm2 .tv_usec/1000) - (tm1.tv_sec*1000 + tm1.tv_usec /1000);	
				//printf("RTSP audio sendtime =%d---------------\n",mSec);
				gettimeofday(&tm1,NULL);	
			}
			nLastAudioFrame = pADataInstance->dwFrameNumber;
		#endif
			if(RTSP_StreamSendData(nChnStream,RTSP_MEDIA_AUDIO, pADataInstance->AudioBuffer, pADataInstance->dwFameSize,nFrameRate,mSec)<0)
			{
				break;
			}
		}			
		usleep(5*1000);
	}
	if( pADataInstance )
	{
		free(pADataInstance);
	}
	IPCAM_DEBUG("[RTSP]:Audio Exit.");
	IPCAM_PTHREAD_EXIT;
}

INT  RTSP_GetFrameRate( INT* pPreFrameRate, INT* pCurFrameRate,  struct timeval * pre_tm1, INT * nFrameRate)
{
	INT					nSub = 0;
	INT					nRet;
	struct timeval 		cur_tm1;
	UINT				mSec = 0;	
	INT					nPreFrameRate   = *pPreFrameRate;
	gettimeofday(&cur_tm1,NULL);			
	mSec= (cur_tm1.tv_sec*1000 +cur_tm1 .tv_usec/1000) - (pre_tm1->tv_sec*1000 + pre_tm1->tv_usec /1000);	
	*pCurFrameRate +=1;
	if(mSec>=1000)
	{
		 if(*pCurFrameRate > 30)
		 {
			*pCurFrameRate = 0;	
			gettimeofday(pre_tm1,NULL);	
			return FALSE;	
		 }
		 
		nSub = *pCurFrameRate - nPreFrameRate ;
		if(nSub <= 2  && nSub >= -2)
		{
			*nFrameRate = nPreFrameRate;
		}
		else
		{
			*nFrameRate = *pCurFrameRate;
			*pPreFrameRate = *pCurFrameRate;
		}
		*pCurFrameRate = 0;
#if 0
		if((CurFrameRate[nChn]>=12)&&(CurFrameRate[nChn]<16))
		{
			*nFrameRate = 12;
		}
		else if((CurFrameRate[nChn]>=16)&&(CurFrameRate[nChn]<20))
		{
			*nFrameRate = 18;
		}
		else if((CurFrameRate[nChn]>=20)&&(CurFrameRate[nChn]<24))
		{
			*nFrameRate = 20;
		}
		else if(CurFrameRate[nChn]>=24)
		{
			*nFrameRate = 25;
		}
		else
		{
			*nFrameRate = 25;
		}
		printf("888888888888888------FrameRate=%d----\n",*nFrameRate);
#endif
		return TRUE;
	}
	return FALSE;
}





VOID * RTSP_LoopVideo (VOID * lParam)
{
	BOOL			bCanSafExit	= FALSE;
	BOOL			bCanSafSend	= TRUE;
	INT 				nChnStream 	   = 0 ;

	ENU_VIDEOCHANL       nChannelID     = VIDEO_CHANNEL_1;
	LPIPCAM_VIDEOBUFFER  pVDataInstance = NULL;	
	HANDLE phandle = NULL;
	INT                  rIndex         = 0;
	INT                  nRet           = 0;
	UINT			nLastFrameNumber = 0;

	struct timeval		tm1;
	struct timeval		tm2;
	INT 				uSec2;

	//////////////////////////////////////////
	struct timeval      tm3;	
	struct timeval      tm4;		
	INT			mSec;	
	INT 			FrameNumber = 0;
	int 	FrameRate = 25;
	static int s_FrameCount = 0;
	///////////////////////////////////////////

	//////////////////////////////////////////
	INT nPreFrameRate = 25;
	INT nCurFrameRate = 25;
	INT nThreadID = gettid();
	INT	nATime = 0;
	//////////////////////////////////////////

	IPCAM_PTHREAD_DETACH;
	nChnStream		  = (INT*)lParam;
	nChannelID	   = RtspCheckChannel(nChnStream);
#if 1
	if(NULL==(pVDataInstance=calloc(sizeof(CHAR),sizeof(IPCAM_VIDEOBUFFER)))) return ;
	//	IPCAM_DEBUG("[RTSP]:ChannelID_%d Video Beginning ...",nChannelID);
	IPCAM_setTskName("ipcam_RtspVideo8899");
#endif
	struct sched_param param;
	param.sched_priority = (sched_get_priority_min(SCHED_FIFO) + sched_get_priority_max(SCHED_FIFO)) / 2;
	if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &param) != 0)
	{
		IPCAM_DEBUG("can not set thread prio\r\n");
	}
	phandle = IPCAM_GetReadHandle();
	if(!phandle)
	{
		goto END_VIDEOSEND;
	}

	/////////////////////////
	gettimeofday(&tm3,NULL);
	///////////////////////////

	static BOOL bRtspPlay = FALSE;
	while (!bCanSafExit)
	{
		RTSP_CHECKSTATUS(bCanSafSend,bCanSafExit,nChnStream);
		nRet = IPCAM_GetStreamDataEX(VIDEO_LOCAL_RECORD,nChannelID,VOIDEO_MEDIATYPE_VIDEO,&rIndex,(HANDDATABUFFER)pVDataInstance,phandle);
		if(FALSE == nRet)
		{
			usleep(1000*10);
			continue;
		}

		if(TRUE ==  RTSP_GetFrameRate(&nPreFrameRate, &nCurFrameRate ,  &tm3, &FrameRate))
		{
			//printf("888888888888888-----nThreadID=%d nChannelID=%d,-FrameRate=%d----\n", nThreadID , nChannelID ,FrameRate);		
			gettimeofday(&tm3,NULL);	
		}
		//printf("IPCAM_GetStreamDataEX---dwframenum=%d\n",pVDataInstance->dwFrameNumber);
		nRet = RTSP_StreamSendData(nChnStream,RTSP_MEDIA_VIDEO,pVDataInstance->VideoBuffer,pVDataInstance->dwFameSize,FrameRate,nATime);	
		//nRet = RTSP_StreamSendData(nChnStream,RTSP_MEDIA_VIDEO,RtspVideoBuf,iLen,FrameRate,nATime);	
		//nLastFrameNumber = pVDataInstance->dwFrameNumber;
		if(nRet<0)
		{
			IPCAM_DEBUG("========send exception myrtsp pthread exit==========pthread_no=%d==========[RTSP_LoopVideo] maliang11111,nChannelID=%d" ,gettid(), nChannelID);
			break;
		}
	#if  0
		/////////////////////////////////////
		if(1 == (pVDataInstance->dwFrameNumber - nLastFrameNumber))
		{
			gettimeofday(&tm2,NULL);	
			uSec2= (tm2.tv_sec*1000 + tm2.tv_usec/1000) - (tm1.tv_sec*1000 + tm1.tv_usec /1000);	
			if(60 < uSec2)
			{
				IPCAM_DEBUG("GET FRAME nChnStream=%d ,time = %d , type=%d ,num=%d ,size=%d" , nChannelID ,uSec2 ,pVDataInstance->dwFrameType ,pVDataInstance->dwFrameNumber ,pVDataInstance->dwFameSize);
			}
			gettimeofday(&tm1,NULL);
		}
		//////////////////////////////////
		nLastFrameNumber = pVDataInstance->dwFrameNumber;

	#endif			
  		 // printf("get--video---------------number=%d\n",pVDataInstance->dwFrameNumber );
		//usleep(5*1000);
	}

END_VIDEOSEND:	
	IPCAM_FreeReadHandle(phandle);
#if 1
	if(pVDataInstance)free(pVDataInstance);
		IPCAM_DEBUG("[RTSP]:Video exit ...exit33 rtsp video pthread_no=%d",gettid());
#endif
	IPCAM_PTHREAD_EXIT;
	
	bRtspPlay = FALSE;
	return NULL;
}


BOOL   RtspCallbackNewStream(INT  hRtspStream,CHAR pzPath )
{
	INT iRet = 0;
	ENU_RTSPMEDIA MediaType   =RTSP_StreamGetMediaType (hRtspStream);
//	IPCAM_DEBUG("RtspCallbackNewStream[], MediaType:%d", MediaType);
	if(RTSP_MEDIA_VIDEO&MediaType)
	{		
		IPCAM_CREATE_THREADEX(RTSP_LoopVideo,hRtspStream, iRet);
		if (FALSE == iRet)	return FALSE;

		IPCAM_CREATE_THREADEX(RTSP_LoopAudio,hRtspStream, iRet);
		if (FALSE == iRet)	return FALSE;	
	}
	return TRUE; 
}
BOOL   RtspCallbackAuthCheck(CHAR *pzName ,CHAR *pzPassword)
{
	//这里可套用系统密码验证函数进行密码验证，也可在初始化时关闭验证(有些播放器不支持密码认证)
	INT 		prv = -1;
	//return NetCfgLoginCheck(pzName, pzPassword, &prv);
	return TRUE;
}

LPIPCAM_VIDEOBUFFER g_mH264VideoBuf = NULL;
LPIPCAM_VIDEOBUFFER g_sH264VideoBuf   = NULL;
LPIPCAM_AUDIOBUFFER g_AudioBuf              = NULL;

BOOL IPCAM_RtspInit(INT nRtspPort , INT bRtspPasswdAuth)
{	
#if 1
	g_mH264VideoBuf = (LPIPCAM_VIDEOBUFFER)malloc(sizeof(IPCAM_VIDEOBUFFER));
	if(NULL == g_mH264VideoBuf)
	{
		return NULL;
	}
	g_sH264VideoBuf = (LPIPCAM_VIDEOBUFFER)malloc(sizeof(IPCAM_VIDEOBUFFER));
	if(NULL == g_sH264VideoBuf)
	{
		return NULL;
	}	
	g_AudioBuf = (LPIPCAM_AUDIOBUFFER)malloc(sizeof(IPCAM_AUDIOBUFFER));
	if(NULL == g_AudioBuf)
	{
		return NULL;
	}
#endif	
	if(nRtspPort<1000 || nRtspPort<0 || nRtspPort > 65535)
	{
		nRtspPort = DEV_NET_RTSP_PORT;
	}
//	IPCAM_DEBUG("pNetInfo->NetRtspPort = %d ,bRtspPasswdAuth=%d" , nRtspPort ,bRtspPasswdAuth );
    return RTSP_Init(nRtspPort,RtspCallbackNewStream,bRtspPasswdAuth, RtspCallbackAuthCheck);
}
VOID IPCAM_RtspDeinit ()
{
	 RTSP_DeInit();
}

BOOL IPCAM_RtspIsRTSP(CHAR *RecBuf,INT nBufLength)
{
 	return  RTSP_IsRTSP(RecBuf,nBufLength);
}

//#endif
