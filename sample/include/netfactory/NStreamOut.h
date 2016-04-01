#pragma  once
#include "utils/HKDataBase.h"

bool NStreamOutRun( struct  _NStreamOut *pNStreamOut,unsigned short nSize );
void NStreamOutStop( struct  _NStreamOut *pNStreamOut );
bool PushDataBufB( struct  _NStreamOut *pNStreamOut,unsigned short level,char *pBuf,unsigned short len,unsigned short nFlag );
bool PushDataBufA( struct  _NStreamOut *pNStreamOut,unsigned short level,RTSHead *head,char *pBuf,unsigned short len );
unsigned int CutDataBuf( struct  _NStreamOut *pNStreamOut,unsigned short level,char *pDataBuf,unsigned int nCutSize );
void DoOutEventMessage( struct  _NStreamOut *pNStreamOut,char *pBuf,int len );	
