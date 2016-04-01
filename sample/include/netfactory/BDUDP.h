#pragma  once

#include "utils/HKDataBase.h"

#define SOCKET_ERROR    -1
#define INVALID_SOCKET  -1
//---sys

bool    CreateBDCast( struct  _CLINetInfo *pcliNetInfo,HKHOSTInfo *pLocalInfo );

void    DestroyBDCast( struct  _CLINetInfo *pcliNetInfo );

int     BDCastSendNetDataA( struct  _CLINetInfo *pcliNetInfo,unsigned int nDstID,unsigned short nLevel,RTSHead *rtsHead,char *pData,unsigned short nLen,bool bBlock ) ;

int     BDCastSendNetDataB( struct  _CLINetInfo *pcliNetInfo,unsigned int nDstID,unsigned short nLevel,char *pData,unsigned short nLen,bool bBlock );

bool    BDCastRun( struct  _CLINetInfo *pcliNetInfo );


