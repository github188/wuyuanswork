#ifndef __EXMOD_DDNS_H__
#define __EXMOD_DDNS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define     DDNS_CMD_LEN  	1024
#define     DDNS_RCV_LEN   	2048
#define 	MAX_DDNS_USER_LEN   	32				// DDNS
#define 	MAX_DDNS_PWD_LEN    	32				// DDNS
#define 	MAX_DDNS_NAME_LEN   	32				// DDNS
#define     MAX_IP_ADDR_LEN         40      		//IP

typedef enum _DDNS_TYPE
{
	_DDNS_ORAY = 0
	,_DDNS_NOIP
	,_DDNS_DYNDNS
	,_DDNS_CHANGEIP
	,_DDNS_APRESS
}_DDNS_TYPE;

typedef struct sdk_ddns_cfg_s {
	unsigned char enable;					// DDNS 0-1-
	unsigned char type;						// DDNSSDK_DDNS_TYPE_E
	unsigned char user_type;				// SDK_DDNS_ORAY_USERTYPE ()
	
	unsigned char interval;					// (:)
	unsigned char port;						// DDNS
	char server[MAX_DDNS_NAME_LEN];			// DDNS(IP)
	char user[MAX_DDNS_USER_LEN];			// 
	char pwd[MAX_DDNS_PWD_LEN];				// 
	char domain[MAX_DDNS_NAME_LEN];			// (dyndns,domain',')
	char client_ip[MAX_IP_ADDR_LEN];		// IP
}sdk_ddns_cfg_t;

int DdnsSockComm(sdk_ddns_cfg_t *ddns);
int DdnsThreadStart(sdk_ddns_cfg_t *ddns);
void DdnsThreadStop(void);

#ifdef __cplusplus
}
#endif


#endif//__DDNS_CLIENT_H__
