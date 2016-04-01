#ifndef __BUFFER_H__
#define __BUFFER_H__

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif



typedef struct tagPOS
{
	short nKeyIndex;
	short nFrameIndex;
}POS,*LPPOS;

void* CreateReadContext();
 void ReleaseReadContext(void* lpContext);

void* CreateContext();
BOOL WriteFrame(void* hContext, void* lpData,int nLength,BOOL bKey);
BOOL ReadFrame(void* hContext,void* hReadContext, void* lpData,int* nLength,BOOL* bKey);
void ReleaseContext(void* hContext);


#endif