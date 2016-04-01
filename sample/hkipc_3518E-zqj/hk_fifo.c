
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include<fcntl.h>

#define SWITCH_PIPE_f       "/tmp/hkfifo-switch_f"

#define MSG_SIZE 100
#define PRG_NAME "HKSwitch"
int m_bRun = 1;
void InitFifo();

int TEST_TFTIME()
{
    InitFifo();
    while (1)
    {
        sleep(2);
    }
}



int CreateTestThread(void)
{
    {
        int ret = -1;
        pthread_t itfid;

        ret = pthread_create(&itfid, NULL, (void *)TEST_TFTIME, NULL);
        if (0 != ret)
        {
            printf("create TF record thread failed!\n");
            return -1;
        }
    }
    return 1;
}


void InitFifo()
{
    printf("...........fifo.......................\n");
    char buf[MSG_SIZE];

    mkfifo(SWITCH_PIPE_f, 0777);

    int sip_control_pipe = 0;
    char buffer[MSG_SIZE];
    sip_control_pipe = open(SWITCH_PIPE_f, O_RDONLY );
    if (sip_control_pipe <= 0 )
    {
        printf( "server open control pipe for read err.\n");
        return;
    }
    while ( m_bRun )
    {
        int ret,len;
        if( sip_control_pipe == 0 )
        {
            sip_control_pipe = open(SWITCH_PIPE_f, O_RDONLY );
        }
        memset(buffer, 0, sizeof(buffer));
        if( read(sip_control_pipe, buffer, MSG_SIZE) <=  0 )
        {
            close(sip_control_pipe);
            sip_control_pipe = 0;
            mkfifo(SWITCH_PIPE_f, 0777);
            sleep(1);
            printf( "Read Fifo Err ,Reset FIFOddd %s\n",buffer );
            continue;
        }   
        hk_test_tf_info();
        printf(".....test tf.......\n");
    }
}
