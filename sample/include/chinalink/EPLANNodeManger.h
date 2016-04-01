
#pragma  once
#include "utils/HKDataBase.h"

#define HKUDPLAN_PORT_TEMP    5000
//Huqing 06-11 EPLANNodeManger
void    InitLANEPNodeManger( HKLANNETCALLBACK funCallBack );

void    DelectLANEPNodeManger();
    
short     JoinLAN( char * szIP, unsigned short nPort );
    
void    LeaveLAN( unsigned short nDstID );
    
int     WriteLANPipeData( unsigned short nDstID, const HKPacketInfo *pPackInfo, char *pData, unsigned short nLen );
       
short   GetLANEPNodeMangerInfo( unsigned short nDstID, char *pbuf, unsigned short nLen );

void    EPLANReFlash( char * pBuf, unsigned short nLen );

int 	EPLANConRemoteHostInfo( unsigned short nDstID );//Huqing Lan Connect 
