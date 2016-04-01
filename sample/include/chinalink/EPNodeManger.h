#pragma  once
#include "utils/HKDataBase.h"

#define HK_PORT_TEMP    4444
#define HK_PORT1      8020
#define HK_PORT2      80
#define HK_PORT3      81
#define HK_PORT4    8080
#define HK_PORT5     443
#define HK_PORT6    161
#define HK_PORT7    2628
#define HK_PORT8    8000
void 	InitEPNodeManger( HKNETCALLBACK funCallBack );

void    DelectEPNodeManger();

int 	WritePipeData( const HKPacketInfo *pPackInfo,char *pData,unsigned short nLen );

void 	EPAddLocalHostInfo( HKHOSTInfo *pHostInfo );

bool 	EPConRemoteHostInfo( HKHOSTInfo *pHostInfo, unsigned int nDstID, unsigned int nConEPID );

bool    AddRemoteHostInfo( HKHOSTInfo *pHostInfo, unsigned short nStatus, unsigned int nDstID, unsigned short nDataID, unsigned int nTempEPID );

bool    CommitRemoteHostInfo( unsigned int nDstID );

bool     CreateLocalSrv( );

void    DelSysConnect( );

void SetMonHostInfoList( char *pBuf, unsigned short nLen );

void SetConPriority( int nPriority );
