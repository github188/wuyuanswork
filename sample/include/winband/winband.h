// create by * 2010.8.16

#pragma  once
#include "utils/HKCmdPacket.h"
//-------video

#ifdef __cplusplus
extern "C"
{
#endif

int      vid_open();
void     vid_close();
int      vid_isopen();
int	     vid_setlightmode( unsigned short ntype );
int      vid_getlightmode();
int		 vid_setreslution( unsigned short pixH,unsigned short pixW );
int      vid_getreslution();
int 	 read_mjpeg( unsigned char *pBuf,int nBufLen );

//-------audio
int      ad_open();
void     ad_close();
int      read_pcm( char *pBuf,int nBufLen );
int      write_pcm( char *pBuf,int nBufLen );

//------wifi
/*int       wf_open();
void      wf_close();
void      wf_reflush();
int       wf_getapcount();
char *    wf_getapinfo( int index );
int 	  wf_setauth( int nAuthType,int index,char *name,char *psw );
void      wf_setfixedip( char *pIP,char *pMaskIP );

enum
{
    WIFIST_NONE = 0,
    WIFIST_FAIL,  
    WIFIST_OK,
};
typedef void ( *wifiCALLBACK )( unsigned short nWifiState,char *param );

*/
//int StartWifiAP( HKFrameHead* hf,wifiCALLBACK wificb );
int ScanWifiAP( HKFrameHead* hf );
void StopWifi();
int GetWifiStatus();
int InitWifiAP();
//------ptz

void 	  moveptz( int dir ); // dir 1 left,2:right,3:up,4:down
void 	  enable_autoptz();
void 	  disable_autoptz();


//------reboot
void     sys_reboot();
#ifdef __cplusplus
}
#endif
//-------ptz
