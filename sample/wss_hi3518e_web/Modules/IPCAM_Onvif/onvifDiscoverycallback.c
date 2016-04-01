#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

#include "IPCAM_Export.h"

#ifdef __cplusplus
};
#endif

static INT GetDiscoveryInfo (LPOVFDISCONVERYINFO lpDiscoveryInfo)
{
	char *pstr = NULL;
	char *ptem = NULL;
	char macaddr22[12] = {0};
	ptem = macaddr22;
	int  len = 0;
	int index = 0;
	
	char NetIp[64] = {0};	
	char NetMac[24] = {0};
	
	conf_get("/mnt/sif/net.cfg", "IPAddress",NetIp, 64);		
	conf_get("/mnt/sif/net.cfg", "MacAddress",NetMac, 24);	
	/*LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	if(SysContext==NULL)
	{
		return FALSE;
	}*/
	//pstr = SysContext->ipcam_SysConfig->ConfigNet.NetMacAddr;
	
	//pstr = "00:20:14:09:22:08";
	pstr = NetMac;//"00:20:14:09:19:18";
	len  = strlen(pstr);
  while(len)
  {
  	 if(*pstr !=':')
  	 {
  	 	   ptem[index]=*pstr;
  	 	   index++;
  	 }
  	 pstr++;
  	 len--;
  	 
  	 
  }
   ptem[index] = '\0';
   strcpy(lpDiscoveryInfo->DevGuid,"464A4854-4656-5242-4530-");
   strcpy(lpDiscoveryInfo->DevGuid+strlen(lpDiscoveryInfo->DevGuid),ptem);
 //   strncpy(lpDiscoveryInfo->DevGuid    ,SysContext->ipcam_SysConfig->ConfigFactory.strDevSerialNumb, OVFCHARLENTH);
    strncpy(lpDiscoveryInfo->DevLocation,"shengzhen/baoan/xixiang", OVFCHARLENTH);
 //   strncpy(lpDiscoveryInfo->DevName    ,SysContext->ipcam_SysConfig->ConfigFactory.strDevName, OVFCHARLENTH);
 
 strncpy(lpDiscoveryInfo->DevName ,"HK_IPCAM", OVFCHARLENTH);
   // sprintf(lpDiscoveryInfo->DevRootUrl ,"http://%s:%d", SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr,NET_ONVIF_SERVER_PORT);
   
   sprintf(lpDiscoveryInfo->DevRootUrl ,"http://%s:%d", NetIp,NET_ONVIF_SERVER_PORT);
    strncpy(lpDiscoveryInfo->DevType,IPCAMWSDEVICETYPE, OVFCHARLENTH);
    
    return TRUE;
}

CALLBACKOVFDISCOVERY Discovery = 
{
    GetDiscoveryInfo
};

