#pragma  once

#include "utils/HKDataBase.h"

#define SOCKET_ERROR    -1
#define INVALID_SOCKET  -1

bool    CreateHKTCPClient( struct  _CLINetInfo *pcliNetInfo,HKHOSTInfo *pLocalInfo );

void    DestroyHKTCPClient( struct  _CLINetInfo *pcliNetInfo );

int     HKTCPConnect( struct  _CLINetInfo *pcliNetInfo, HKHOSTInfo *pDstInfo,unsigned int nDstID );

void    HKTCPReConnect( struct  _CLINetInfo *pcliNetInfo );

void    HKTCPDisConnect( struct  _CLINetInfo *pcliNetInfo,unsigned int nDstID );

int     HKTCPCLISendNetDataA( struct  _CLINetInfo *pcliNetInfo,unsigned int nDstID,unsigned short nLevel,RTSHead *rtsHead,char *pData,unsigned short nLen,bool bBlock ) ;

int     HKTCPCLISendNetDataB( struct  _CLINetInfo *pcliNetInfo,unsigned int nDstID,unsigned short nLevel,char *pData,unsigned short nLen,bool bBlock );

int     SetHKTCPCLINetBaseOption( struct  _CLINetInfo *pcliNetInfo,unsigned int nID,unsigned short nCmd );

void    HKTCPCLIAddPipe( struct  _CLINetInfo *pcliNetInfo,unsigned int nHKID,unsigned int nPIPEID );
void    HKTCPCLIRemPipe( struct  _CLINetInfo *pcliNetInfo,unsigned int nHKID,unsigned int nPIPEID );
