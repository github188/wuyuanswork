
#include "IPCAM_Export.h"

extern CALLBACKOVFDISCOVERY Discovery;
extern CALLBACKDEVMS        CallBackDevMs;
extern CALLBACKIMAGING      g_CallBackImaging;
extern CALLBACKMEDIA        g_CallBackMedia;
extern CALLBACKPTZ          g_CallBackPtz  ;
static CALLBACKOVF          CallBackOvf = { 0};


//BOOL   IPCAM_OnvifInit            (IPCAM_SYSCONTEXT  *gSystemText,HDOVF * pHdovf)
BOOL   IPCAM_OnvifInit            (HDOVF * pHdovf)
{
	UINT  IPaddr;
	HDOVF onvifhandle =NULL;
	char NetIp[64] = {0};	
	conf_get("/mnt/sif/net.cfg", "IPAddress",NetIp, 64);	
#if 1
	InitCallBackDevMs();
	InitCallBackImaging();
	InitCallBackMedia();
	InitCallBackPtz();
#endif
	CallBackOvf.CallBackDiscovery = &Discovery;
	CallBackOvf.CallBackDevManage = &CallBackDevMs;
	CallBackOvf.CallBackImaging   = &g_CallBackImaging;
	CallBackOvf.CallBackMedia     = &g_CallBackMedia;
	CallBackOvf.CallBackPtz       = &g_CallBackPtz;
	//IPCAM_DEBUG("[IPCAM_OnvifInit]NetIpAddr=%s" ,gSystemText->ipcam_SysConfig->ConfigNet.NetIpAddr );
	//IPaddr = inet_addr(gSystemText->ipcam_SysConfig->ConfigNet.NetIpAddr);
	IPaddr = inet_addr(NetIp);	
	IPaddr = htonl(IPaddr);	
	onvifhandle = OVF_Init(IPaddr, NET_ONVIF_SERVER_PORT ,10, &CallBackOvf);	
	if (onvifhandle == NULL) 
	{
	  return FALSE;
    }	
	if(pHdovf) *pHdovf=onvifhandle;
	printf("[IPCAM_OnvifInit]----------------- success\n");
	//IPCAM_DEBUG("[IPCAM_OnvifInit]------%s------------ success" ,gSystemText->ipcam_SysConfig->ConfigNet.NetIpAddr);
	return TRUE;
}
