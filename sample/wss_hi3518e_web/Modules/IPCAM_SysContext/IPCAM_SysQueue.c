
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
#include "IPCAM_SysBuffer.h"


///////////////////////////////////////////////////////////////////////////////////////////
///上面是内部循环队列内部涵数
///下面是关于内存循环队列接口涵数
///////////////////////////////////////////////////////////////////////////////////////////

static INT IPCAM_PutVideoData(VOID* hContext, VOID* pDataInstance)
{
	BOOL bRet = FALSE;
	BOOL bKey = FALSE;
	UINT nBufSize = 0;
	LPIPCAM_VIDEOBUFFER  pVideoBuffer = (LPIPCAM_VIDEOBUFFER)pDataInstance;
	if(NULL == pVideoBuffer){	
		return FALSE;
	}
	nBufSize = sizeof(IPCAM_VIDEOBUFFER) - MAX_VIDEO_BUFFSIZE + pVideoBuffer->dwFameSize;
	bKey = (0 == pVideoBuffer->dwFrameType) ? TRUE : FALSE; 	
	bRet = 	WriteFrame(hContext , pVideoBuffer , nBufSize , bKey);
	//IPCAM_DEBUG("[IPCAM_PutVideoData] bRet=%d , bKey=%d" , bRet , bKey);
	return bRet;
}


static INT IPCAM_PutAudioData(void *pBufferqueue , void* pDataInstance)
{
	LPIPCAM_AUDIOBUFFER  pAudioBuffer = NULL;
	LPIPCAM_SYSBUFFER	 pBufferQueue = NULL;
	UINT                 nCurPointer  = 0;
    
	pBufferQueue = (LPIPCAM_SYSBUFFER     )pBufferqueue;
	pAudioBuffer = (LPIPCAM_AUDIOBUFFER)pDataInstance;
	if(pBufferQueue==NULL||pAudioBuffer==NULL)return FALSE;
	//set nCurpointer 
	nCurPointer = pBufferQueue->a_wIndex;
	if(pAudioBuffer->dwFameSize>0){
		pthread_mutex_lock(&pBufferQueue->AudioBuffer[nCurPointer%AUDIO_MAX_NUM].audio_mutex);
		pBufferQueue->AudioBuffer[nCurPointer%AUDIO_MAX_NUM].dwFameSize    = pAudioBuffer->dwFameSize;
		pBufferQueue->AudioBuffer[nCurPointer%AUDIO_MAX_NUM].dwBufferType  = pAudioBuffer->dwBufferType;
		pBufferQueue->AudioBuffer[nCurPointer%AUDIO_MAX_NUM].dwSec         = pAudioBuffer->dwSec;
		pBufferQueue->AudioBuffer[nCurPointer%AUDIO_MAX_NUM].dwUsec        = pAudioBuffer->dwUsec;
		pBufferQueue->AudioBuffer[nCurPointer%AUDIO_MAX_NUM].dwFrameNumber = pAudioBuffer->dwFrameNumber;
		pBufferQueue->AudioBuffer[nCurPointer%AUDIO_MAX_NUM].bzEncType     = pAudioBuffer->bzEncType;
		memcpy(&pBufferQueue->AudioBuffer[nCurPointer%AUDIO_MAX_NUM].AudioBuffer, pAudioBuffer->AudioBuffer, pAudioBuffer->dwFameSize);
		pBufferQueue->a_wIndex = (pBufferQueue->a_wIndex+1)%AUDIO_MAX_NUM;				
		pthread_mutex_unlock(&pBufferQueue->AudioBuffer[nCurPointer%AUDIO_MAX_NUM].audio_mutex);
		return TRUE;	
	}
	return FALSE;	
}


static INT IPCAM_PutJpgData(VOID* hContext, VOID* pDataInstance)
{	
	UINT                nCurPointer  = 0;
	LPIPCAM_SYSBUFFER 	pBufferQueue = (LPIPCAM_SYSBUFFER)hContext;
	LPIPCAM_MJPEGBUFFER pMjpegBuffer = (LPIPCAM_MJPEGBUFFER)pDataInstance;
	if(pBufferQueue==NULL||pMjpegBuffer==NULL)		return FALSE;
	nCurPointer = pBufferQueue->j_wIndex;
	if(pMjpegBuffer->dwFameSize>0)
	{
		pthread_mutex_lock(&pBufferQueue->MjpegBuffer[nCurPointer%MJPEG_MAX_NUM].jpg_mutex);
		pBufferQueue->MjpegBuffer[nCurPointer%MJPEG_MAX_NUM].dwFameSize    = pMjpegBuffer->dwFameSize;
		pBufferQueue->MjpegBuffer[nCurPointer%MJPEG_MAX_NUM].dwBufferType  = pMjpegBuffer->dwBufferType;
		pBufferQueue->MjpegBuffer[nCurPointer%MJPEG_MAX_NUM].dwSec         = pMjpegBuffer->dwSec;
		pBufferQueue->MjpegBuffer[nCurPointer%MJPEG_MAX_NUM].dwUsec        = pMjpegBuffer->dwUsec;	
		pBufferQueue->MjpegBuffer[nCurPointer%MJPEG_MAX_NUM].dwFrameNumber = pMjpegBuffer->dwFrameNumber;	
		pBufferQueue->MjpegBuffer[nCurPointer%MJPEG_MAX_NUM].dwHeight      = pMjpegBuffer->dwHeight;
		pBufferQueue->MjpegBuffer[nCurPointer%MJPEG_MAX_NUM].dwWidth       = pMjpegBuffer->dwWidth;
		memcpy(&pBufferQueue->MjpegBuffer[nCurPointer%MJPEG_MAX_NUM].MjpegBuffer , pMjpegBuffer->MjpegBuffer, pMjpegBuffer->dwFameSize  );					
		pBufferQueue->j_wIndex = (pBufferQueue->j_wIndex+1)%MJPEG_MAX_NUM;		
		pthread_mutex_unlock(&pBufferQueue->MjpegBuffer[nCurPointer%MJPEG_MAX_NUM].jpg_mutex);					
		return TRUE;		
	}
	return FALSE;	
}


static INT IPCAM_GetJpgData(void* hContext,int* pBufferIndex, void* lpData)
{
	INT                 num                       = 0;
	UINT                dwFrameNumberTemp         = 0;
	UINT                rIndex                    = 0;	
	
	LPIPCAM_MJPEGBUFFER  	pMjpegBuffer = (LPIPCAM_MJPEGBUFFER)lpData;
	LPIPCAM_SYSBUFFER 		pBufferQueue = (LPIPCAM_SYSBUFFER)hContext;   
	if(pBufferQueue==NULL || pMjpegBuffer==NULL)return FALSE;
	


	rIndex = *pBufferIndex%MJPEG_MAX_NUM;
	//队列没有新数据进入队列	
	if((pMjpegBuffer->dwFrameNumber+1)>pBufferQueue->MjpegBuffer[rIndex].dwFrameNumber)
	{
		return FALSE;
	}

	num = rIndex;
	if(pBufferQueue->MjpegBuffer[num].dwFameSize > 0)
	{
		pthread_mutex_lock(&pBufferQueue->MjpegBuffer[num].jpg_mutex);
		pMjpegBuffer->dwBufferType  = pBufferQueue->MjpegBuffer[num].dwBufferType;
		pMjpegBuffer->dwFameSize    = pBufferQueue->MjpegBuffer[num].dwFameSize;
		pMjpegBuffer->dwFrameNumber = pBufferQueue->MjpegBuffer[num].dwFrameNumber;
		pMjpegBuffer->dwSec         = pBufferQueue->MjpegBuffer[num].dwSec;
		pMjpegBuffer->dwUsec        = pBufferQueue->MjpegBuffer[num].dwUsec;
		memcpy(pMjpegBuffer->MjpegBuffer , pBufferQueue->MjpegBuffer[num].MjpegBuffer , pBufferQueue->MjpegBuffer[num].dwFameSize);
		*pBufferIndex = (rIndex+1)%AUDIO_MAX_NUM;
		pthread_mutex_unlock(&pBufferQueue->MjpegBuffer[num].jpg_mutex);	
		return TRUE;			
	}
	return FALSE;
}


static INT IPCAM_GetVideoData(void* hContext,LPPOS Pos, void* lpData)
{
	LPIPCAM_VIDEOBUFFER  pVideoBuffer = (LPIPCAM_VIDEOBUFFER)lpData;  
	BOOL bKey = FALSE;
	BOOL bRet = FALSE;
	int  DataSize = sizeof(IPCAM_VIDEOBUFFER);
	
	if(NULL == pVideoBuffer)
	{
		return FALSE;
	}
	bRet = ReadFrame(hContext,Pos, pVideoBuffer,&DataSize,&bKey);
	//IPCAM_DEBUG("[IPCAM_GetVideoData] bRet=%d , pos=%d ,int=%d" , bRet , sizeof(POS) , sizeof(int));
	return bRet;
}


static INT IPCAM_GetVideoDataEx(void* hContext,void *Pos, void* lpData)
{
	LPIPCAM_VIDEOBUFFER  pVideoBuffer = (LPIPCAM_VIDEOBUFFER)lpData;  
	BOOL bKey = FALSE;
	BOOL bRet = FALSE;
	int  DataSize = sizeof(IPCAM_VIDEOBUFFER);
	
	if(NULL == pVideoBuffer)
	{
		return FALSE;
	}
	bRet = ReadFrame(hContext,Pos, pVideoBuffer,&DataSize,&bKey);
	//IPCAM_DEBUG("[IPCAM_GetVideoData] bRet=%d , pos=%d ,int=%d" , bRet , sizeof(POS) , sizeof(int));
	return bRet;
}


static INT IPCAM_GetAudioData(void *pVqueue , UINT* pBufferIndex , void* pVDataInstance)
{
	INT                 num               = 0;
	UINT                dwFrameNumberTemp = 0;
	LPIPCAM_SYSBUFFER      pbufferqueue      = NULL;
	LPIPCAM_AUDIOBUFFER pAudioBuffer      = NULL;
	UINT                rIndex            = 0;
    
	pbufferqueue = (LPIPCAM_SYSBUFFER     )pVqueue;
	pAudioBuffer = (LPIPCAM_AUDIOBUFFER)pVDataInstance;
    
	if(pbufferqueue==NULL ||pAudioBuffer==NULL)return FALSE;

	rIndex = *pBufferIndex%AUDIO_MAX_NUM;	
	//队列没有新数据进入队列
	if((pAudioBuffer->dwFrameNumber +1)>pbufferqueue->AudioBuffer[rIndex].dwFrameNumber){
		return FALSE;
	}
	num = rIndex;
	if(pbufferqueue->AudioBuffer[num].dwFameSize>0)
	{
		pthread_mutex_lock(&pbufferqueue->AudioBuffer[num].audio_mutex);			
        pAudioBuffer->bzEncType     = pbufferqueue->AudioBuffer[num].bzEncType;
		pAudioBuffer->dwBufferType  = pbufferqueue->AudioBuffer[num].dwBufferType;
		pAudioBuffer->dwFameSize    = pbufferqueue->AudioBuffer[num].dwFameSize;
		pAudioBuffer->dwFrameNumber = pbufferqueue->AudioBuffer[num].dwFrameNumber;
		pAudioBuffer->dwSec         = pbufferqueue->AudioBuffer[num].dwSec;
		pAudioBuffer->dwUsec        = pbufferqueue->AudioBuffer[num].dwUsec;
		memcpy(pAudioBuffer->AudioBuffer , pbufferqueue->AudioBuffer[num].AudioBuffer , pbufferqueue->AudioBuffer[num].dwFameSize);
		*pBufferIndex = (rIndex+1)%AUDIO_MAX_NUM;
		pthread_mutex_unlock(&pbufferqueue->AudioBuffer[num].audio_mutex);	
		return TRUE;
	}
	return FALSE;	
}


/**************************************************************************************
*******************
******************下面是内存队列提供的接口涵数
*******************
**************************************************************************************/
static LPIPCAM_SYSBUFFER g_SysBuffer = NULL;

HANDSYSBUFFER   Context_InitSysteBuffer()
{
	INT chn = 0;
	INT i = 0;
	g_SysBuffer	= (LPIPCAM_SYSBUFFER)malloc(sizeof(IPCAM_SYSBUFFER));
	if(NULL == g_SysBuffer)
	{
		return NULL;
	}

	for(chn=0;chn<IPCAM_LOCAL_CHN;chn++)
	{	
		////创建视频队列
		g_SysBuffer->pVideoList[chn]= CreateContext();
		if(NULL == g_SysBuffer->pVideoList[chn])
		{
			return NULL;
		}	
	}
	for(i=0;i<MJPEG_MAX_NUM;i++)
	{
		pthread_mutex_init(&g_SysBuffer->MjpegBuffer[i].jpg_mutex, NULL);		
	}

	for(i=0;i<AUDIO_MAX_NUM;i++)
	{
		pthread_mutex_init(&g_SysBuffer->AudioBuffer[i].audio_mutex, NULL);
	}

	IPCAM_DEBUG("Context_InitSysteBuffer is ok!");	
	return (HANDSYSBUFFER)g_SysBuffer;
}


void   Context_DelInitSysteBuffer()
{
	INT chn = 0;
	INT i 	= 0;	

	for(chn=0;chn<IPCAM_LOCAL_CHN;chn++)
	{
		////注销视频队列
		ReleaseContext(g_SysBuffer->pVideoList[chn]);
	}
	for(i=0;i<MJPEG_MAX_NUM;i++)
	{
		pthread_mutex_destroy(&g_SysBuffer->MjpegBuffer[i].jpg_mutex);		
	}
	for(i=0;i<AUDIO_MAX_NUM;i++)
	{
		pthread_mutex_destroy(&g_SysBuffer->AudioBuffer[i].audio_mutex);
	}	
	
	if(g_SysBuffer)
	{
		free(g_SysBuffer);	
	}
	
	IPCAM_DEBUG("Context_DelInitSysteBuffer is ok!");
}


INT  IPCAM_PutStreamData( INT	 localType, INT channel , INT mediaType, HANDDATABUFFER pDataInstance)
{
	INT	nRet = 0;
    
	if(pDataInstance ==NULL)return FALSE;
	switch(localType){
		case VIDEO_LOCAL_RECORD:
			switch(mediaType)
			{
					case VOIDEO_MEDIATYPE_VIDEO:
						nRet = IPCAM_PutVideoData(g_SysBuffer->pVideoList[channel], pDataInstance);
						break;
					case VOIDEO_MEDIATYPE_AUDIO:
						nRet = IPCAM_PutAudioData(g_SysBuffer, pDataInstance);												
						break;	
					case VOIDEO_MEDIATYPE_MJPEG:
						nRet = IPCAM_PutJpgData(g_SysBuffer, pDataInstance);						
						break;
					default:
						IPCAM_DEBUG("IPCAM_PutStreamData localType is error!");
						return FALSE;	
			}			
			break;
		default:
			IPCAM_DEBUG("IPCAM_PutStreamData  is error!");
			return FALSE;	
	}
	return nRet;
	
}


INT  IPCAM_GetStreamDataEX( INT localType, INT channel , INT mediaType , INT* pBufferIndex, HANDDATABUFFER pVDataInstance,HANDLE pReadVHandle)
{
       
		INT nRet = 0;

	if(pVDataInstance==NULL||pBufferIndex==NULL)return FALSE;
	switch(localType){
		case VIDEO_LOCAL_RECORD:
			switch(mediaType){//put local stream data
					case VOIDEO_MEDIATYPE_VIDEO:				
						//nRet = IPCAM_GetVideoData(g_SysBuffer->pVideoList[channel] , pReadVHandle, pVDataInstance);
						nRet = IPCAM_GetVideoDataEx(g_SysBuffer->pVideoList[channel] , pReadVHandle, pVDataInstance);
						break;
					case VOIDEO_MEDIATYPE_AUDIO:
						nRet = IPCAM_GetAudioData(g_SysBuffer, pBufferIndex,pVDataInstance);
						break;
					case VOIDEO_MEDIATYPE_MJPEG:
						nRet = IPCAM_GetJpgData(g_SysBuffer, pBufferIndex , pVDataInstance);						
						break;	
					default:
						IPCAM_DEBUG("IPCAM_GetStreamData  localType is error!");
						break;
			}
			break;	

		default:
			IPCAM_DEBUG("IPCAM_GetStreamData  NetWorkBuffer is error!");
			return FALSE;
	}
	return nRet;

}

HANDLE IPCAM_GetReadHandle()
{
     HANDLE *phandle = NULL;
     phandle = CreateReadContext();
     return  phandle;
}

void IPCAM_FreeReadHandle(HANDLE phandle)
{
       ReleaseReadContext(phandle);
}

INT  IPCAM_GetStreamData( INT localType, INT channel , INT mediaType , INT* pBufferIndex, HANDDATABUFFER pVDataInstance)
{

	INT nRet = 0;

	if(pVDataInstance==NULL||pBufferIndex==NULL)return FALSE;
	switch(localType){
		case VIDEO_LOCAL_RECORD:
			switch(mediaType){//put local stream data
					case VOIDEO_MEDIATYPE_VIDEO:				
						nRet = IPCAM_GetVideoData(g_SysBuffer->pVideoList[channel] , (LPPOS)pBufferIndex, pVDataInstance);						
						break;
					case VOIDEO_MEDIATYPE_AUDIO:
						nRet = IPCAM_GetAudioData(g_SysBuffer, pBufferIndex,pVDataInstance);
						break;
					case VOIDEO_MEDIATYPE_MJPEG:
						nRet = IPCAM_GetJpgData(g_SysBuffer, pBufferIndex , pVDataInstance);						
						break;	
					default:
						IPCAM_DEBUG("IPCAM_GetStreamData  localType is error!");
						break;
			}
			break;	

		default:
			IPCAM_DEBUG("IPCAM_GetStreamData  NetWorkBuffer is error!");
			return FALSE;
	}
	return nRet;	
}
