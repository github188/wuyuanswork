
//#include <list>
//#include <vector.h>
#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include "IPCAM_SysBuffer.h"

//using namespace std;

#define BUF_COUNT	(1024)//(2 * 1024)
#define BUF_LEN		(1024)

typedef struct tagDATA_PACK
{
	unsigned int dwIndex;
	int			 bHead;
	BOOL		 bKey;
	int			 nFrameLength;
	int			 nPackLen;
	char		 lpData[BUF_LEN];
}DATA_PACK,*LPDATA_PACK;


 typedef struct tagCONTEXT_INFO
 {
	int nWriteIndex;
	pthread_mutex_t hMutex;
	LPDATA_PACK arPack[BUF_COUNT];
	int nIPos;
	unsigned int dwIndex;
 }CONTEXT_INFO,*LPCONTEXT_INFO;


 typedef struct tagREAD_CONTEXT
 {
	unsigned int dwIndex;
	int nReadPos;
 }READ_CONTEXT,*LPREAD_CONTEXT;


 void* CreateReadContext()
 {
	LPREAD_CONTEXT lpContext = (LPREAD_CONTEXT)malloc(sizeof(READ_CONTEXT));
	if(!lpContext)
		return NULL;
	memset(lpContext,0,sizeof(READ_CONTEXT));
	lpContext->nReadPos = -1;
	return lpContext;
 }
 void ReleaseReadContext(void* lpContext)
 {
	 if(!lpContext)
		 return;
	 free((LPREAD_CONTEXT)lpContext);
 }

void* CreateContext()
{
	int i;
	LPCONTEXT_INFO lpInfo = (LPCONTEXT_INFO)malloc(sizeof(CONTEXT_INFO));
	if (!lpInfo)
	{
		return NULL;
	}
	lpInfo->nIPos = -1;
	lpInfo->nWriteIndex = 0;
	lpInfo->dwIndex = 0;
	pthread_mutex_init(&lpInfo->hMutex,NULL);
	for(i = 0; i < BUF_COUNT;i++)
	{
		lpInfo->arPack[i] =(LPDATA_PACK)malloc(sizeof(DATA_PACK));
		if(lpInfo->arPack[i])
		{
			memset(lpInfo->arPack[i],0,sizeof(DATA_PACK));
		}
	}
	return lpInfo;
}



BOOL WriteFrame(void* hContext, void* lpData,int nLength,BOOL bKey)
{
	LPCONTEXT_INFO lpInfo = (LPCONTEXT_INFO)hContext;
	if (!lpInfo)
	{
		return FALSE;
	}

	BOOL bRet = FALSE;
	pthread_mutex_lock(&lpInfo->hMutex);
	if(!bKey && lpInfo->nIPos == -1)
	{
		pthread_mutex_unlock(&lpInfo->hMutex);
		return FALSE;
	}
	if(bKey)
	{
		lpInfo->nIPos = lpInfo->nWriteIndex;
	}
	lpInfo->arPack[lpInfo->nWriteIndex]->bHead = TRUE;
	lpInfo->arPack[lpInfo->nWriteIndex]->bKey = bKey;
	lpInfo->arPack[lpInfo->nWriteIndex]->dwIndex = lpInfo->dwIndex;
	lpInfo->arPack[lpInfo->nWriteIndex]->nFrameLength = nLength;
	lpInfo->arPack[lpInfo->nWriteIndex]->nPackLen = nLength <= BUF_LEN ? nLength : BUF_LEN;
	memcpy(lpInfo->arPack[lpInfo->nWriteIndex]->lpData,lpData,lpInfo->arPack[lpInfo->nWriteIndex]->nPackLen);
	int nWrite = lpInfo->arPack[lpInfo->nWriteIndex]->nPackLen;
	lpInfo->nWriteIndex  = (lpInfo->nWriteIndex + 1) % BUF_COUNT;
	while(nWrite < nLength)
	{
		lpInfo->arPack[lpInfo->nWriteIndex]->bHead = FALSE;
		lpInfo->arPack[lpInfo->nWriteIndex]->dwIndex = lpInfo->dwIndex;
		lpInfo->arPack[lpInfo->nWriteIndex]->nFrameLength = nLength;
		lpInfo->arPack[lpInfo->nWriteIndex]->nPackLen = (nLength - nWrite) <= BUF_LEN ? (nLength - nWrite) : BUF_LEN;
		memcpy(lpInfo->arPack[lpInfo->nWriteIndex]->lpData ,(char*)lpData + nWrite,lpInfo->arPack[lpInfo->nWriteIndex]->nPackLen);
		nWrite += lpInfo->arPack[lpInfo->nWriteIndex]->nPackLen;
		lpInfo->nWriteIndex  = (lpInfo->nWriteIndex + 1) % BUF_COUNT;
	}
	lpInfo->dwIndex++;
	pthread_mutex_unlock(&lpInfo->hMutex);
	return TRUE;
}

BOOL ReadFrame(void* hContext,void* hReadContext, void* lpData,int* nLength,BOOL* bKey)
{
	if(!lpData || !nLength || !bKey)
		return FALSE;
	LPCONTEXT_INFO lpInfo = (LPCONTEXT_INFO)hContext;
	if (!lpInfo)
	{
		return FALSE;
	}
	LPREAD_CONTEXT lpContext = (LPREAD_CONTEXT)hReadContext;
	if(!lpContext)
		return FALSE;

	pthread_mutex_lock(&lpInfo->hMutex);

	if(lpInfo->nIPos == -1 || lpInfo->nWriteIndex == lpContext->nReadPos)
	{
		pthread_mutex_unlock(&lpInfo->hMutex);
		return FALSE;
	}
	if(lpContext->nReadPos == -1 || (lpContext->dwIndex + 1 != lpInfo->arPack[lpContext->nReadPos]->dwIndex))
	{
		lpContext->nReadPos = lpInfo->nIPos;
	}
	*nLength = lpInfo->arPack[lpContext->nReadPos]->nFrameLength;
	lpContext->dwIndex = lpInfo->arPack[lpContext->nReadPos]->dwIndex;
	*bKey = lpInfo->arPack[lpContext->nReadPos]->bKey;

	int nRead = 0;
	do{		
		memcpy((char*)lpData + nRead,lpInfo->arPack[lpContext->nReadPos]->lpData,lpInfo->arPack[lpContext->nReadPos]->nPackLen);
		nRead += lpInfo->arPack[lpContext->nReadPos]->nPackLen;

		lpContext->nReadPos = (lpContext->nReadPos + 1) % BUF_COUNT;
	}while(nRead < *nLength);
	pthread_mutex_unlock(&lpInfo->hMutex);
	return TRUE;

}
void ReleaseContext(void* hContext)
{
	int i;
	LPCONTEXT_INFO lpInfo = (LPCONTEXT_INFO)hContext;
	if (!lpInfo)
	{
		return ;
	}
	
	pthread_mutex_destroy(&lpInfo->hMutex);
	
	for(i = 0; i < BUF_COUNT; i++)
	{
		if (lpInfo->arPack[i])
		{			
			free(lpInfo->arPack[i]);
		}		
	}	
	free(lpInfo);
}

#if 0
int main()
{
	BOOL bRead = FALSE;
	char  lpWriteBuf[1024];
	char  lpReadBuf[1024];
	int  nLen = 0;
	BOOL bKey = 0;
	void* lpBufContext = CreateContext();
	void* lpReadContext = CreateReadContext();
	if(!lpBufContext || !lpReadContext)
	{
		return 0;
	}

	WriteFrame(lpBufContext,lpWriteBuf,1024,TRUE);

	bRead = ReadFrame(lpBufContext,lpReadContext,lpReadBuf,&nLen,&bKey);
	printf("bRead=%d,nLen = %d,bKey=%d\n",bRead,nLen,bKey);

	return 0;
}
#endif
