#include "hk_uart.h"
#include "hkipc_hk.h"

//#define DEBUG_ZIGBEE

#pragma pack(1)

/********************************************
 * Command Code:         Key Name:
 * FF  00  34  00  FF    左转
 * FF  00  31  00  FF    右转
 * FF  00  32  00  FF    前进
 * FF  00  33  00  FF    后退
 * FF  00  40  00  FF    停止
 * FF  00  20  00  FF    自动清扫（清扫）
 * FF  00  21  00  FF    重点清扫
 * FF  00  2F  00  FF    拖地模式
 * FF  00  22  00  FF    语音开关（反馈 0xe0，0xe1）
 * FF  00  23  00  FF    模式  (反馈 0xd1,  0xd2)
 * FF  00  24  00  FF    回充
 * FF  00  25  00  FF    当前工作模式查询
 * FF  00  26  00  FF    当前清扫模式查询
 * FF  00  7A  00  FF    电量查询
 *
 *
 * Format: 0xFF + 0x00 + CMD + 0x00 + 0xFF.
 
********************************************/
#if DEV_CODWIP 
char g_UartSendCmd[CMD_NUM][9] = {
    /*{'*', '$', 'T', '8', '0', 't', '7', '4', '.'}*/
    {0x2A, 0x24, 0x54, 0x38, 0x30, 0x74, 0x37, 0x34, 0x2E}
};
#else
char g_UartSendCmd[CMD_NUM][CMD_BITNUM] = {
    {0xFF, 0x00, 0x40, 0x00, 0xFF}, /*stop*/
    {0xFF, 0x00, 0x32, 0x00, 0xFF}, /*forward*/
    {0xFF, 0x00, 0x33, 0x00, 0xFF}, /*backward*/
    {0xFF, 0x00, 0x34, 0x00, 0xFF}, /*left*/
    {0xFF, 0x00, 0x31, 0x00, 0xFF}, /*right*/
    {0xFF, 0x00, 0x20, 0x00, 0xFF}, /*auto clean*/
    {0xFF, 0x00, 0x21, 0x00, 0xFF}, /*important parts clean*/
    {0xFF, 0x00, 0x2F, 0x00, 0xFF}, /*mop mode*/
    {0xFF, 0x00, 0x22, 0x00, 0xFF}, /*voice switch*/
    {0xFF, 0x00, 0x23, 0x00, 0xFF}, /*mode*/
    {0xFF, 0x00, 0x24, 0x00, 0xFF}, /*charge-back*/
    {0xFF, 0x00, 0x25, 0x00, 0xFF}, /*current work mode query*/
    {0xFF, 0x00, 0x26, 0x00, 0xFF}, /*current clean mode query*/
    {0xFF, 0x00, 0x7A, 0x00, 0xFF}, /*battery status*/
    {0xFF, 0x00, 0xAA, 0x00, 0xFF}, /*ANDSON: Motion Detect alarm*/
    {0xFF, 0x00, 0xAB, 0x00, 0xFF}, /*ANDSON: IO alarm*/
    {0xFF, 0x00, 0xAC, 0x00, 0xFF}, /*ANDSON: PIR alarm*/
    {0xFF, 0x00, 0xAD, 0x00, 0xFF}, /*ANDSON: 433 alarm*/
    {0xFF, 0x01, 0x00, 0x00, 0xFF}, /*jsw: set time Hour*/
    {0xFF, 0x02, 0x00, 0x00, 0xFF}, /*jsw: set time Minutes*/
    {0xFF, 0x00, 0x42, 0x00, 0xFF}, //set wifi
};
#endif

int g_UartFd = -1;

int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)
{
    struct termios newtio,oldtio;

    if (tcgetattr(fd, &oldtio) != 0) 
    { 
        perror("set <%s> failed !");
        return -1;
    }

    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag |= CLOCAL | CREAD; 
    newtio.c_cflag &= ~CSIZE; 

    switch (nBits)
    {
        case 7:
            newtio.c_cflag |= CS7;
            break;
        case 8:
            newtio.c_cflag |= CS8;
            break;
    }

    switch (nEvent)
    {
        case 'O':
            newtio.c_cflag |= PARENB;
            newtio.c_cflag |= PARODD;
            newtio.c_iflag |= (INPCK | ISTRIP);
            break;
        case 'E': 
            newtio.c_iflag |= (INPCK | ISTRIP);
            newtio.c_cflag |= PARENB;
            newtio.c_cflag &= ~PARODD;
            break;
        case 'N': 
            newtio.c_cflag &= ~PARENB;
            break;
    }

    switch (nSpeed)
    {
        case 2400:
            cfsetispeed(&newtio, B2400);
            cfsetospeed(&newtio, B2400);
            break;
        case 4800:
            cfsetispeed(&newtio, B4800);
            cfsetospeed(&newtio, B4800);
            break;
        case 9600:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
        case 115200:
            cfsetispeed(&newtio, B115200);
            cfsetospeed(&newtio, B115200);
            break;
        default:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
    }

    if (1 == nStop)
        newtio.c_cflag &= ~CSTOPB;
    else if (2 == nStop)
        newtio.c_cflag |= CSTOPB;

    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN] = 0;
    tcflush(fd,TCIFLUSH);

    if ((tcsetattr(fd, TCSANOW, &newtio)) != 0)
    {
        perror("com set error !");
        return -1;
    }
    //printf("set done!\n");
    return 0;
}


int UART_Definit()
{
    if (g_UartFd > 0)
    {
        close(g_UartFd); 
        g_UartFd = -1;
    }
    return 0;
}

int UART_Init()
{
    unsigned int UartBitRate = 0;
#if (DEV_ANDSON)
    UartBitRate = 115200;
#else
    UartBitRate = 9600;
#endif
    //g_UartFd = open("/dev/ttyAMA1", O_RDWR);
    g_UartFd = open("/dev/ttyAMA1", O_RDWR|O_NOCTTY|O_NDELAY);
    if (g_UartFd < 0)
    {
        printf("open uart error: %s\n", strerror(errno));
        UART_Definit();
        return -1;
    }

    if (set_opt(g_UartFd, UartBitRate, 8, 'N', 1) < 0)
    {
        printf("set uart option failed !\n"); 
        UART_Definit();
        return -1;
    }
    printf("...init uart success, bitrate:%u, fd:%d\n", UartBitRate, g_UartFd);
    return 0;
}


int UART_ControlXY(int nCmd, int nX, int nY)
{
    printf("[%s, %d] ...nCmd:%d, nX:%d, nY:%d...\n", __func__, __LINE__, nCmd, nX, nY);
    int len = 0;
    short RecvCmdBuf = 0;
    char SendCmdBuf[9] = {0}; //data format
    
    char tmp[16] = {0};
    tmp[0] = 0x30; //48 ==> '0'.
    SendCmdBuf[0] = 0x01;
    SendCmdBuf[1] = 0x88;
    SendCmdBuf[2] = 0x02;
    SendCmdBuf[3] = 0x02;
    SendCmdBuf[4] = nX; //menu.
    SendCmdBuf[5] = nY;
    SendCmdBuf[6] = 0x03;
    SendCmdBuf[7] = 0x00;
    SendCmdBuf[8] = 0x00;

    
    len = write(g_UartFd, SendCmdBuf, 9);
    UART_DBG_PRINT("XY...uart write data[], %#x, len:%d...\n", SendCmdBuf[4], len);

    return len;
}

int UART_CtrlCmd_Send(ENUM_UART_CMD enCmd, int iParam)
{
    int len = 0;

#if 0 //test.
    char SendCmdBuf[8] = {0};
    strcpy(SendCmdBuf, "ABCDEFG");
    len = write(g_UartFd, SendCmdBuf, 8);
    printf("...uart send data:%s, len:%d...\n", SendCmdBuf, len);
#endif

#if 0
    //UART_DBG_PRINT("......enCmd: %d......\n", enCmd);
    if (CMD_STOP == enCmd)
    {
        g_UartSendCmd[CMD_STOP][2] = 0x40; //stop.
    }
    else if (CMD_FORWARD == enCmd)
    {
        g_UartSendCmd[CMD_FORWARD][2] = 0x32; //forward.
    }
    else if (CMD_BACKWARD == enCmd)
    {
        g_UartSendCmd[CMD_BACKWARD][2] = 0x33; //back ward.
    }
    else if (CMD_LEFT == enCmd)
    {
        g_UartSendCmd[CMD_LEFT][2] = 0x34; //left.
    }
    else if (CMD_RIGHT == enCmd)
    {
        g_UartSendCmd[CMD_RIGHT][2] = 0x31; //right.
    }
    else if (CMD_ANDSON_MD == enCmd)
    {
        g_UartSendCmd[CMD_ANDSON_MD][2] = 0xAA; //motion detect.
    }
#endif
    if ( CMD_ANDSON_HOUR == enCmd)
    {
        g_UartSendCmd[CMD_ANDSON_HOUR][2] = iParam;// atoi(s);

    }
    else if(CMD_ANDSON_MINUTES == enCmd)
    {
        g_UartSendCmd[CMD_ANDSON_MINUTES][2] = iParam;// atoi(s);
    }

    len = write(g_UartFd, g_UartSendCmd[enCmd], sizeof(g_UartSendCmd[enCmd]));
    //len = write(g_UartFd, g_UartSendCmd[enCmd], 9);
    if (len <= 0)
    {
        UART_DBG_PRINT("enCmd:%d, uart send data failed with (%d):%s!\n", enCmd, errno, strerror(errno));
        return -1;
    }
    //UART_DBG_PRINT("enCmd:%d, Uart Send [2]:%#x, len:%d\n", enCmd, g_UartSendCmd[enCmd][2], len);
    return len;
}


/** receive response info from slave machine **/
void *Handle_Uart_Recv(void *arg)
{
    int ret = 0;
    fd_set uart_fds;
    struct timeval tv;
    int len = 0;
    char UartRecvBuf[32] = {0};
    int iCount = 61;
    printf("...uart thread start...\n");
    while (1)
    {
        sleep(3);
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        FD_ZERO(&uart_fds);
        FD_SET(g_UartFd, &uart_fds);

        ret = select(g_UartFd+1, &uart_fds, NULL, NULL, &tv);
        if (ret <= 0 )
        {
            usleep(1000);
            printf("......select........\n");
            continue;
        }
        if (FD_ISSET(g_UartFd, &uart_fds))
        {
            memset(UartRecvBuf, 0, sizeof(UartRecvBuf));
            len = read(g_UartFd, UartRecvBuf, sizeof(UartRecvBuf));
            //len = read(g_UartFd, UartRecvBuf, 512);
            if (len > 0)
            {
            #ifdef DEBUG_ZIGBEE
                recv_uart_msg(UartRecvBuf);
            #endif

            #ifdef DEV_ROBOT
                if(  iCount < 20 )
                {
                    iCount++;
                    continue;
                }
            #endif
                int i = 0;
                //while(i < len)
                if( len > 0 )
                {
                    iCount = 1;
                    //if( UartRecvBuf[i]== 245 )
                    //{
                        //sccSendPowerToApp( 109 );
                    //}
                    //if((UartRecvBuf[i]== 106 ||UartRecvBuf[i]== 107 ||UartRecvBuf[i]== 108) && iCount != 1 )
                    if(UartRecvBuf[i]== 106 ||UartRecvBuf[i]== 107 ||UartRecvBuf[i]== 108||UartRecvBuf[i]== 127 )
                    {
                        sccSendPowerToApp( UartRecvBuf[i] );
                        //printf("[%s, %d] %02x, =%d\n ", __func__, __LINE__, UartRecvBuf[i],UartRecvBuf[i]);
                    }
                    else
                    {

                        //sccSendPowerToApp( UartRecvBuf[i] );
                        //sccSendPowerToApp( 110);
                        //printf("[%s, %d] %02x, =%d \n", __func__, __LINE__, UartRecvBuf[i],UartRecvBuf[i]);
                    }
                    i++;
                }
                //printf("\n");
            }
        }
    }
    return 0;
}

static int g_query_work_mode=0;
//2s 
int HK_Check_Battery(void)
{
    int len = 0;
    char UartRecvBuf[32] = {0};

    if( g_query_work_mode == 1)
    {
        g_query_work_mode = 0;
        UART_CtrlCmd_Send(CMD_QUERY_BATTERY, 0);
    }
    else
    {
        g_query_work_mode = 1;
        UART_CtrlCmd_Send(CMD_QUERY_WORK_MODE, 0);
    }

    /*
    if( g_query_work_mode != 1)
        UART_CtrlCmd_Send(CMD_QUERY_BATTERY, 0);

    //if( g_query_work_mode == 1)
    //    UART_CtrlCmd_Send(CMD_QUERY_WORK_MODE, 0);
    if( g_query_work_mode++ >= 10)
        g_query_work_mode=1;
        */
}


/*****************************************************
 * func: init and create uart recv data.
 *****************************************************/
int HK_UART_Thread(unsigned int *nRecv)
{
    int ret = 0;
    pthread_t Uart_Event;
    void *thread_result;

    ret = UART_Init(); //init uart options.
    if (ret < 0)
    {
        UART_DBG_PRINT("uart init failed !\n");
        UART_Definit();
        return -1;
    }
   
    /** receive response info from slave machine **/
    ret = pthread_create(&Uart_Event, NULL, (void *)Handle_Uart_Recv, NULL);
    if (0 != ret)
    {
        printf("pthread_create failed with:%d, %s\n", errno, strerror(errno));
        pthread_detach(Uart_Event);
        return -1;
    }
    pthread_detach(Uart_Event);

#if 0 //error.
    if (pthread_join(Uart_Event, &thread_result) == 0)
    {
        printf("thread Uart_Event = %d, result = %d\n", Uart_Event, (int)thread_result);
    }
    pthread_detach(Uart_Event);
#endif
    
    return 0;
}

/**test**/
int test_uart( )
{
#if 0
    int fd = 0, len = 0;
    char RevBuf[20] = {0};

    fd = open("/dev/ttyAMA1", O_RDWR);
    if (fd < 0)
    {
        printf("open the com error!\n");
        return -1;
    }

    set_opt(fd, 9600, 8, 'N', 1);

    while (1)
    {
        len=read(fd, RevBuf, 20);
        printf("uart read data--------RevBuf=%s, strlen:%d\n", RevBuf, strlen(RevBuf));

        sleep(1);
        len = write(fd, "*ANDSON.", 8);
        printf("uart write data, len:%d\n", len);
        sleep(1);
    }
    //printf("....len=%d...\n", len);
    close(fd);
    return len;
#endif


#if 0
    g_UartFd = open("/dev/ttyAMA1", O_RDWR);
    if (g_UartFd < 0)
    {
        printf("open the com error!\n");
        UART_Definit();
        return -1;
    }

    if (set_opt(g_UartFd, 9600, 8, 'N', 1) < 0)
    {
        printf("set uart option failed !\n"); 
        UART_Definit();
        return -1;
    }
#else
    UART_Init(); //init uart options.
#endif

    int len = 0;
    char RevBuf[20] = {0};
    while (1)
    {
        len = read(g_UartFd, RevBuf, 20);
        printf("uart read data--------RevBuf=%s, strlen:%d\n", RevBuf, strlen(RevBuf));

        sleep(1);
        len = write(g_UartFd, "*ANDSON.", 8);
        printf("uart write data, len:%d\n", len);
        sleep(1);
    }
    //printf("....len=%d...\n", len);
    close(g_UartFd);

    return 0;
}

