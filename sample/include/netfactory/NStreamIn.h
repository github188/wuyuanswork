#pragma  once
#include "utils/HKDataBase.h"

bool NStreamInRun( struct  _NStreamIn *pNStreamIn,unsigned short nPori,unsigned short nSize );
void NStreamInStop( struct  _NStreamIn *pNStreamIn );
bool NStreamInDataBuf( struct  _NStreamIn *pNStreamIn,char *pDataBuf,unsigned short nLen );
void    DoInEventMessage( struct  _NStreamIn *pNStreamIn,char *pBuf,int len );

