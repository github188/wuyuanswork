#pragma  once

#include "utils/HKDataBase.h"

#define SOCKET_ERROR    -1
#define INVALID_SOCKET  -1
//---sys

bool    CreateUDPLan( struct  _CLINetInfo *pcliNetInfo,HKHOSTInfo *pLocalInfo );

void    DestroyUDPLan( struct  _CLINetInfo *pcliNetInfo );

int     LanConnect( struct  _CLINetInfo *pcliNetInfo, HKHOSTInfo *rDstInfo,unsigned short nDstID );

void    LanReConnect( struct  _CLINetInfo *pcliNetInfo );

void    LanDisConnect( struct  _CLINetInfo *pcliNetInfo,unsigned short nDstID );

int     LanSendNetDataA( struct  _CLINetInfo *pcliNetInfo,unsigned int nDstID,unsigned short nLevel,RTSHead *rtsHead,char *pData,unsigned short nLen,bool bBlock ) ;

int     LanSendNetDataB( struct  _CLINetInfo *pcliNetInfo,unsigned int nDstID,unsigned short nLevel,char *pData,unsigned short nLen,bool bBlock );

int     SetLanNetBaseOption( struct  _CLINetInfo *pcliNetInfo,unsigned int nID,unsigned short nCmd );

void	GetLocalMac( char *pMacData );

short 	AddLanEP( struct  _CLINetInfo *pcliNetInfo,char *ip,unsigned short nPort,char *pMac );
void	RemLanEP( struct  _CLINetInfo *pcliNetInfo,unsigned short nDstID );
short   RemLanEPEx( struct  _CLINetInfo *pcliNetInfo,char *ip,unsigned short nPort );


