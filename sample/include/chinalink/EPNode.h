#pragma  once
#include "utils/HKDataBase.h"
#include "utils/HKCmdPacket.h"

bool	NewEP( struct  _CLINetInfo *pcliNetInfo,HKHOSTInfo *pLocalHostInfo );
void	DelEP( struct  _CLINetInfo *pcliNetInfo, unsigned int nDstID );
int	EPConnect( struct  _CLINetInfo *pcliNetInfo,HKHOSTInfo *pRemtorHostInfo, unsigned int nDstID );
void    EPReConnect( struct  _CLINetInfo *pcliNetInfo, unsigned int nDstID );
void	EPDisConnect( struct  _CLINetInfo *pcliNetInfo, unsigned int nDstID );
int    EPTestConnect( struct _CLINetInfo *pcliNetInfo, HKHOSTInfo *pHostInfo, HKFrameHead *pFrameHead, unsigned int nDstID ); 
int	SendNetData( struct  _CLINetInfo *pcliNetInfo,unsigned int nDstID,unsigned short nLevel,RTSHead *rtsHead,char *pData,unsigned short nLen );
void   DoTryNatIP( struct _CLINetInfo *pcliNetInfo, char *pIP, unsigned short nPort );
unsigned short  AddLANInfoGroup( struct _CLINetInfo *pcliNetInfo, char * szIP, unsigned short nPort, char * szMacIP );//Huqing 06-17 Add Lan Info
void    DelLANInfoGroup( struct _CLINetInfo *pcliNetInfo, unsigned short nDstID );
unsigned short    DelLANInfoGroupEX( struct _CLINetInfo *pcliNetInfo, char * szIP, unsigned short nPort );
void	EPHKUDPSetSTUN( struct  _CLINetInfo *pcliNetInfo, char * szIP, unsigned short nPort  );

void	DoUDPAddPipe( struct  _CLINetInfo *pcliNetInfo,unsigned int nHKID,unsigned int nPIPEID );
void    DoUDPRemPipe( struct  _CLINetInfo *pcliNetInfo,unsigned int nHKID,unsigned int nPIPEID );

void EPSetHKID( struct _CLINetInfo *pcliNetInfo, unsigned int nHKID );
