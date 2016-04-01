
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 256
#define HK_MSG_KEY 1234

typedef enum hk_netmode_e
{
    NETMODE_WIRE    = 0, //wire connection;
    NETMODE_WIFISTA = 1, //wifi station;
    NETMODE_WIFIAP  = 2  //wifi AP mode.
}HK_NETMODE_E;


/***************************
 * 用于消息收发的结构体
 *  msg_type：消息类型，
 *  msg_text：消息正文
 ***************************/
typedef struct hk_msgqueue_st
{
	long int msg_type;
	char msg_text[MAX_TEXT];
}HK_MSGQUEUE_ST;

int HK_MessageQueue_Send(int netmode);
int HK_MessageQueue_Recv(void);

