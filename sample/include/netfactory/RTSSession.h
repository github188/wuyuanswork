#pragma  once
#include "utils/HKDataBase.h"

bool RTSRun( struct _RTSSession *pSession,struct _RTSParam *pRtsParam );
void RTSStop( struct _RTSSession *pSession );

int  RTSSendNetDataA( struct _RTSSession *pSession,unsigned int nLevel,RTSHead *rtsHead,char *pData,unsigned short nLen
                        ,bool bBlock );
int  RTSSendNetDataB( struct _RTSSession *pSession,unsigned int nDstID,unsigned short nLevel,char *pData,unsigned short nLen
                        ,bool bBlock );
int  RTSReceNetData( struct _RTSSession *pSession,char *pData,unsigned short nLen );
void RTSDoEventMessage( struct _RTSSession *pSession,char *pData,unsigned short nLen );

void  RTSAddPipe( struct _RTSSession *pSession,unsigned int  nPIPEID );
void RTSRemPipe( struct _RTSSession *pSession,unsigned int  nPIPEID );
