#pragma  once

#include "utils/HKDataBase.h"

bool    CreateHKTCPServer( struct  _CLINetInfo *pcliNetInfo,HKHOSTInfo *pLocalInfo );

void    DestroyHKTCPServer( struct  _CLINetInfo *pcliNetInfo );

void    HKTCPSrvDisConnect( struct  _CLINetInfo *pcliNetInfo,unsigned int nDstID );

int     HKTCPSRVSendNetDataA( struct  _CLINetInfo *pcliNetInfo,unsigned int nDstID,unsigned short nLevel,RTSHead *rtsHead,char *pData,unsigned short nLen,bool bBlock ) ;

int     HKTCPSRVSendNetDataB( struct  _CLINetInfo *pcliNetInfo,unsigned int nDstID,unsigned short nLevel,char *pData,unsigned short nLen,bool bBlock );

int     SetHKTCPSRVNetBaseOption( struct  _CLINetInfo *pcliNetInfo,unsigned int nID,unsigned short nCmd );

void    HKTCPSRVAddPipe( struct  _CLINetInfo *pcliNetInfo,unsigned int nHKID,unsigned int nPIPEID );
void    HKTCPSRVRemPipe( struct  _CLINetInfo *pcliNetInfo,unsigned int nHKID,unsigned int nPIPEID );

void    HKTCPSRVSetHKID( struct  _CLINetInfo *pcliNetInfo,unsigned int nHKID );

