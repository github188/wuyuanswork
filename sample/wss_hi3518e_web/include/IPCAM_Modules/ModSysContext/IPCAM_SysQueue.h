//IPCAM_SysQueue.h

#ifndef __IPCAM_SYSQUEUE__
#define __IPCAM_SYSQUEUE__


#define MAX_VIDEO_BUFFSIZE 		  (400*1024)
#define MAX_AUDIO_BUFFSIZE 		  (4*1024)
#define MAX_MJPEG_BUFFSIZE		  (400*1024)


#define IPCAM_LOCAL_CHN 		  (2)  
#define IPCAM_NETWORK_CHN	 	  (0)

#define VIDEO_MAX_NUM			  (5)  // 32
#define AUDIO_MAX_NUM			  (50)
#define MJPEG_MAX_NUM			  (2)
#define VIDEO_MAX_IPB             (20)
#define VIDEO_MIX_IPB             (5)

#define VIDEO_I_FRAME			  (0)
#define VIDEO_P_FRAME			  (1)
#define VIDEO_B_FRAME			  (2)



#define VIDEO_LOCAL_RECORD		  (0)
#define VIDEO_NET_RECORD		  (1)


#define VOIDEO_MEDIATYPE_VIDEO	  (0)
#define VOIDEO_MEDIATYPE_AUDIO	  (1)
#define VOIDEO_MEDIATYPE_MJPEG	  (2)



typedef struct _IPCAM_VIDEO_BUFFER{
	CHAR	bzEncType;                                 //编码类型
	CHAR	dwBufferType;                              //本地视频 ， IPC网络视频
	CHAR	dwFrameType;                               // 0 I Frame , 1 P frame  ,2  B frame 
	ULONG	dwFameSize;                                //帧尺寸
	ULONG	dwFrameNumber;                             //帧序号，始终递增
	USHORT	dwWidth;
	USHORT 	dwHeight;	
	UINT 	dwSec;		                               //帧的时间戳,精确到毫秒级
	UINT 	dwUsec;		                               //帧的时间戳,精确到微秒级
	CHAR	VideoBuffer[MAX_VIDEO_BUFFSIZE];           ////实际帧数据100K	
	pthread_mutex_t	video_mutex;
}IPCAM_VIDEOBUFFER , *LPIPCAM_VIDEOBUFFER;
typedef struct _IPCAM_AUDIO_BUFFER{
 	CHAR	    bzEncType;                             //编码类型
	UINT		dwBufferType;                          //0本地视频 ， 1 IPC网络视频
	UINT		dwFameSize;
	UINT		dwFrameNumber;
	UINT		dwSec;
	UINT		dwUsec;
	UCHAR	    AudioBuffer[MAX_AUDIO_BUFFSIZE];        //4K
	pthread_mutex_t	audio_mutex;
}IPCAM_AUDIOBUFFER , *LPIPCAM_AUDIOBUFFER;

typedef struct _IPCAM_JPG_BUFFER{
	UINT		dwBufferType; 	                        ///////本地视频 ， IPC网络视频
	UINT		dwFameSize;		                        ////15k
	UINT		dwFrameNumber;
	UINT		dwWidth;
	UINT 	    dwHeight;	
	UINT		dwSec;
	UINT		dwUsec;
	CHAR	    MjpegBuffer[MAX_MJPEG_BUFFSIZE];         /////350K	
	pthread_mutex_t	jpg_mutex;
}IPCAM_MJPEGBUFFER , *LPIPCAM_MJPEGBUFFER;

typedef struct  _IPCAM_SYSBUFFER {
	VOID* 					pVideoList[IPCAM_LOCAL_CHN];	
	IPCAM_MJPEGBUFFER	 	MjpegBuffer[MJPEG_MAX_NUM]; 
	IPCAM_AUDIOBUFFER		AudioBuffer[AUDIO_MAX_NUM]; 
	INT						j_wIndex;
	INT						a_wIndex;
} IPCAM_SYSBUFFER, *LPIPCAM_SYSBUFFER;



/*********************************************************************************************************
功能:下面是内存管理模块提供接口
***********************************************************************************************************/


#define HANDSYSBUFFER 		void*
#define HANDDATABUFFER 		void*
/***************************************************
功能:
初始化系统内存BUFFER管理
返回：
返回NULL ：初始化失败
返回非NULL：初始化成功
****************************************************/
HANDSYSBUFFER   Context_InitSysteBuffer();
void            Context_DelInitSysteBuffer();

/***************************************************
功能:
把视频数据，音频数据，JPG数据投入在内存管理器内暂存
参数:
1,HandSysBuffer:传递Context_InitSysteBuffer()初始化成功返回指针
2,IsLocalRecord:标识是否是本地录像(VIDEO_LOCAL_RECORD)
或网络录像(VIDEO_NET_RECORD)
3,nchannel:标识录像通道号范围(0,1,2,3)
4,mediaType:标识录像类型:
视频类型：VOIDEO_MEDIATYPE_VIDEO
音频类型：VOIDEO_MEDIATYPE_AUDIO
图像类型：VOIDEO_MEDIATYPE_MJPEG
5,pDataBuffer:向内存管理器投放录像数据流结构体对应该：
视频类型：VOIDEO_MEDIATYPE_VIDEO        对应：LPIPCAM_VIDEOBUFFER 结构
音频类型：VOIDEO_MEDIATYPE_AUDIO        对应：LPIPCAM_AUDIOBUFFER结构
图像类型：VOIDEO_MEDIATYPE_MJPEG		对应：LPIPCAM_MjpegBuffer结构
返回：
返回FALSE ，投放数据流数据失败
返回TRUE：投放数据流数据成功
****************************************************/
INT  IPCAM_PutStreamData( INT IsLocalRecord, INT  nchannel , INT  mediaType, HANDDATABUFFER pDataBuffer);

/***************************************************
功能:
把视频数据，音频数据，JPG数据在内存管理器内获取
参数:

IsLocalRecord:标识是否是本地录像(VIDEO_LOCAL_RECORD)
或网络录像(VIDEO_NET_RECORD)

nchannel:标识录像通道号范围(1,2,3,4)

mediaType:标识录像类型:
视频类型：VOIDEO_MEDIATYPE_VIDEO
音频类型：VOIDEO_MEDIATYPE_AUDIO
图像类型：VOIDEO_MEDIATYPE_MJPEG
pBufferIndex：指定索引取数据队列数据

pDataBuffer:获取内存管理器录像数据流结构体对应该：
视频类型：VOIDEO_MEDIATYPE_VIDEO       对应：LPIPCAM_VIDEOBUFFER 结构
音频类型：VOIDEO_MEDIATYPE_AUDIO       对应：LPIPCAM_AUDIOBUFFER结构
图像类型：VOIDEO_MEDIATYPE_MJPEG		对应：LPIPCAM_MjpegBuffer结构
返回：
返回FALSE ，投放数据流数据失败
返回TRUE：投放数据流数据成功
****************************************************/
INT  IPCAM_GetStreamData( INT IsLocalRecord, INT nchannel , INT mediaType , INT* pBufferIndex , HANDDATABUFFER pDataBuffer);

INT  IPCAM_GetStreamDataEX( INT localType, INT channel , INT mediaType , INT* pBufferIndex, HANDDATABUFFER pVDataInstance,HANDLE pReadVHandle);

/***************************************************
功能:
消除数据队列
参数:
IsLocalRecord:标识是否是本地录像(VIDEO_LOCAL_RECORD)
或网络录像(VIDEO_NET_RECORD)
nchannel:标识录像通道号范围(1,2,3,4)
mediaType:标识录像类型:
视频类型：VOIDEO_MEDIATYPE_VIDEO
音频类型：VOIDEO_MEDIATYPE_AUDIO
图像类型：VOIDEO_MEDIATYPE_MJPEG

返回：
返回FALSE ，消除数据队列失败
返回TRUE：消除数据队列成功
****************************************************/
INT IPCAM_ClearStreamDataQueue(UCHAR localType, UCHAR nchannel , UCHAR mediaType);

#endif



