#ifndef _IPCAM_NETPPPOE_H_
#define _IPCAM_NETPPPOE_H_
#include "IPCAM_Export.h"


#if 0
#define IPCAM_PPPOE_CHAPSECRETS		"/etc/ppp/chap-secrets"
#define IPCAM_PPPOE_USRPASSWD		"/etc/ppp/pap-secrets"
#define IPCAM_PPPOE_USRPASSWD_BAK	"/etc/ppp/chap-secrets-bak"

#define IPCAM_PPPOE_CONF			"/etc/ppp/pppoe.conf"

#define IPCAM_PPPOE_COMMAND_STATUS  "pppoe-status | grep \"inet addr:\""

#define IPCAM_PPPOE_COMMAND_START	"pppoe-start"

#define IPCAM_PPPOE_COMMAND_STOP	"pppoe-stop &"

#define IPCAM_PPPOE_DEVPPP0FILE		"/var/run/ppp0.pid"

#define IPCAM_PPPOE_DEVPPP1FILE		"/var/run/ppp1.pid"

INT IPCAM_NetPppoeStart();
INT IPCAM_NetPppoeStatus();
INT IPCAM_NetPppoeStop();
INT IPCAM_NetPppoeSet();
#endif


#endif

