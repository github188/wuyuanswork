#pragma  once

#include "utils/HKDataBase.h"
#include "utils/HKCmdPacket.h"

#define SOCKET_ERROR    -1
#define INVALID_SOCKET  -1

bool    CreateHKUDP( struct  _CLINetInfo *pcliNetInfo,HKHOSTInfo *pLocalInfo );

void    DestroyHKUDP( struct  _CLINetInfo *pcliNetInfo );

int		HKUDPTestConnect( struct  _CLINetInfo *pcliNetInfo,HKHOSTInfo *pDstInfo,HKFrameHead *pFrame,unsigned int nDstID );

int     HKUDPConnect( struct  _CLINetInfo *pcliNetInfo, HKHOSTInfo *pDstInfo,unsigned int nDstID );

void    HKUDPReConnect( struct  _CLINetInfo *pcliNetInfo );

void    HKUDPDisConnect( struct  _CLINetInfo *pcliNetInfo,unsigned int nDstID );

int     HKUDPSendNetDataA( struct  _CLINetInfo *pcliNetInfo,unsigned int nDstID,unsigned short nLevel,RTSHead *rtsHead,char *pData,unsigned short nLen,bool bBlock ) ;

int     HKUDPSendNetDataB( struct  _CLINetInfo *pcliNetInfo,unsigned int nDstID,unsigned short nLevel,char *pData,unsigned short nLen,bool bBlock );

void    HKUDPTryConnect( struct  _CLINetInfo * pcliNetInfo,char *pIP,unsigned short nPort );
void	HKUDPSetSTUN( struct  _CLINetInfo *pcliNetInfo,char *pIP,unsigned short nPort );

int     SetHKUDPNetBaseOption( struct  _CLINetInfo *pcliNetInfo,unsigned int nID,unsigned short nCmd );

void	HKUDPAddPipe( struct  _CLINetInfo *pcliNetInfo,unsigned int nHKID,unsigned int nPIPEID );
void    HKUDPRemPipe( struct  _CLINetInfo *pcliNetInfo,unsigned int nHKID,unsigned int nPIPEID );

void    HKUDPSetHKID( struct  _CLINetInfo *pcliNetInfo,unsigned int nHKID );
