
#include "hk_message.h"

extern int g_NetWorkMode;

/*******************************************************
 * func: send message to queue.
 *      message: message data.
 * return:
 *      0 on success, and negative number on error.
 *******************************************************/
static int send_message_out(const char *message)
{
    if (NULL == message)
    {
        printf("[%s, %d] error, null pointer !\n", __func__, __LINE__); 
        return -1;
    }
    printf("[%s, %d] message: %s, len: %d\n", __func__, __LINE__, message, strlen(message));

	struct hk_msgqueue_st msg_data;
	int msgid = 0, ret = 0; //message queue identifier

	/*create a message queue identifier associated with the value of the key argument*/
	msgid = msgget((key_t)HK_MSG_KEY, 0666 | IPC_CREAT);
	if (-1 == msgid) 
	{
		fprintf(stderr, "[%s, %d] msgget error: %d, %s\n", __func__, __LINE__, errno, strerror(errno));
        return errno;
	}
    printf("......%s, msgid: %d......\n", __func__, msgid);

    /*send messages to a message queue*/
    msg_data.msg_type = 1;
    strcpy(msg_data.msg_text, message);
    ret = msgsnd(msgid, (void *)&msg_data, MAX_TEXT, 0);
    if (-1 == ret)
    {
        fprintf(stderr, "[%s, %d] msgsnd error: %d, %s\n", __func__, __LINE__, errno, strerror(errno));
        msgctl(msgid, IPC_RMID, 0); //delet message queue.
        return errno;
    }

    return 0;
}

int HK_MessageQueue_Init(void)
{
    int msgid = 0; //message queue identifier

    /*create a message queue identifier associated with the value of the key argument*/
    msgid = msgget((key_t)HK_MSG_KEY, 0666 | IPC_CREAT);
    if (-1 == msgid) 
    {
        fprintf(stderr, "[%s, %d] msgget error: %d, %s\n", __func__, __LINE__, errno, strerror(errno));
        return errno;
    }
    printf("......%s, msgid: %d......\n", __func__, msgid);

    return msgid;
}

/***********************************************************
 * func: send message to queue.
 *      netmode: 0 (wire); 1(sta); 2(AP).
 * return:
 *      0 on success, and negative number on error.
 **********************************************************/
int HK_MessageQueue_Send(int netmode)
{
    printf("...%s...netmode: %d...\n", __func__, netmode);
    int ret = 0;
    char msg_buffer[MAX_TEXT] = {0};
    bzero(msg_buffer, MAX_TEXT);

    if (NETMODE_WIRE == netmode) //wire connection.
    {
        strcpy(msg_buffer, "NETMODE_WIRE");
        msg_buffer[strlen(msg_buffer)] = '\0';
        printf("[%s, %d]...Net Work Mode: %s...\n", __func__, __LINE__, msg_buffer);    
    }
    else if (NETMODE_WIFISTA == netmode)
    {
        strcpy(msg_buffer, "NETMODE_WIFISTA");
        msg_buffer[strlen(msg_buffer)] = '\0';
        printf("[%s, %d]...Net Work Mode: %s...\n", __func__, __LINE__, msg_buffer);    
    }
    else if (NETMODE_WIFIAP == netmode)
    {
        strcpy(msg_buffer, "NETMODE_WIFIAP");
        msg_buffer[strlen(msg_buffer)] = '\0';
        printf("[%s, %d]...Net Work Mode: %s...\n", __func__, __LINE__, msg_buffer);    
    }

    ret = send_message_out( msg_buffer );
    if (ret)
    {
        printf("[%s, %d] send message queue failed !\n", __func__, __LINE__); 
        return -1;
    }

    printf("...send message queue ok...\n");
    return 0;
}


/*********************************************************************
 * func: receive message from queue, and parse message info.
 ********************************************************************/
void *HK_Get_NetWorkMode(void *arg)
{
    int msgid = 0, ret = 0; //message queue identifier
    struct hk_msgqueue_st msg_data; 
    int msg_recv_size = MAX_TEXT; //message buffer size.
    int msg_recv_type = 0; //receive the first message in queue.
    int msg_len = 0; //received message length.
    char RcvMsgBuf[256] = {0};

    /*create a message queue identifier associated with the value of the key argument*/
    msgid = msgget((key_t)HK_MSG_KEY, 0666 | IPC_CREAT);
    if (-1 == msgid) 
    {
        fprintf(stderr, "[%s, %d] msgget error: %d, %s\n", __func__, __LINE__, errno, strerror(errno));
        return NULL;
    }
    printf("[%s, %d] ...msgid: %d...\n", __func__, __LINE__, msgid);

    /*receive messages from a message queue*/
    while (1)
    {
        ret = msgrcv(msgid, (void *)&msg_data, msg_recv_size, msg_recv_type, 0);
        if (-1 == ret)
        {
            fprintf(stderr, "[%s, %d] msgrcv error: %d, %s\n", __func__, __LINE__, errno, strerror(errno));
            msgctl(msgid, IPC_RMID, 0); //delete message queue.
            return NULL;
        }
        msg_len = strlen(msg_data.msg_text);
        //printf("......recv message: %s, mes_len: %d......\n", msg_data.msg_text, msg_len);

        if (msg_len > 0)
        {
            memset(RcvMsgBuf, '\0', sizeof(RcvMsgBuf));
            strncpy(RcvMsgBuf, msg_data.msg_text, msg_len); 
            RcvMsgBuf[msg_len] = '\0';
            printf("[%s, %d] received message:%s, msg_len:%d...\n", __func__, __LINE__, RcvMsgBuf, msg_len);
            if (0 == strncmp(RcvMsgBuf, "NETMODE_WIRE", msg_len))
            {
                g_NetWorkMode = NETMODE_WIRE;  //wire connection.
            }
            else if (0 == strncmp(RcvMsgBuf, "NETMODE_WIFISTA", msg_len))
            {
                g_NetWorkMode = NETMODE_WIFISTA;  //wifi station.
            }
            else if (0 == strncmp(RcvMsgBuf, "NETMODE_WIFIAP", msg_len))
            {
                g_NetWorkMode = NETMODE_WIFIAP;  //wifi AP.
            }
        }
        printf("[%s, %d] ...g_NetWorkMode: %d...\n", __func__, __LINE__, g_NetWorkMode);
        sleep(2);
    }

    ret = msgctl(msgid, IPC_RMID, 0); //delete message queue.
    if (-1 == ret) 
    {
        fprintf(stderr, "msgctl(IPC_RMID) failed: %d, %s\n", errno, strerror(errno));
        return NULL;
    }

    return 0;
}


/**********************************************************
 * func: create a thread to receive message from queue.
 *********************************************************/
int HK_MessageQueue_Recv(void)
{
    int ret = 0;
    pthread_t Msg_Event;
    void *thread_result;

    /** thread to receive and parse message info **/
    ret = pthread_create(&Msg_Event, NULL, (void *)HK_Get_NetWorkMode, NULL);
    if (0 != ret)
    {
        printf("pthread_create failed with:%d, %s\n", errno, strerror(errno));
        pthread_detach(Msg_Event);
        return -1;
    }
    pthread_detach(Msg_Event);

    return 0;
}

