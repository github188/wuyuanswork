#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pthread.h>
#include "hk_zigbee.h"

#define SET_DEVTYPE(s,val1,val2) do{s[0] = val1;s[1] = val2;}while(0);


int g_uart_fd = -1; /*串口文件描述符*/
unsigned char pstrzb[MAX_CMD_BUF_SIZE] = {0};/*临时保存从串口收到的数据*/
static int g_status = STATUS_OFFLINE; /*临时保存设备当前状态，用来返回给上层*/
static char *zb_mac; /*保存网关自身的mac地址*/
static int select_flag = 0; /* 获取设备状态标识位，因为对设备上线时的反馈和客户端主动去获取设备状态的反馈的操作不一样，所以启用此标识 */
static int find_flag = 0; /*从串口reply中解析需要的数据，此标志位的值表示解析到了哪一步*/
static int g_offset = 0; /*串口数据保存在变量里的偏移量，即已接受到的数据长度，因为需要
                           的数据串口可能要分几次发送，当偏移量达到一定长度再去解析，效率更高*/
Node *head = NULL; /*单链表，用于存放注册上网络了的设备的信息，具体结构查看头文件hk_zigbee.h*/

/*创建链表，带头结点*/
static void create_head(Node **head) 
{
    *head = (Node *)malloc(sizeof(Node));
    (*head)->data = (Devdesc *)malloc(sizeof(Devdesc));
    (*head)->next = NULL;
}

/*尾插法*/
static void insert_tail(Node **head, Devdesc *devdesc)
{
    Node *p,*t;
    t = *head;
    p=(Node *)malloc(sizeof(Node));
    p->data = (Devdesc *)malloc(sizeof(Devdesc));
    memcpy(p->data,devdesc,sizeof(Devdesc));
    while(t->next != NULL)
    {
        t=t->next;
    }
    t->next = p;
    p->next = NULL;
}

/*清空链表*/
static void earse_list(Node** head)
{
   Node* p = *head;
   while(p)
   {
      *head = p->next;
      free(p->data);
      free(p);
      p = *head;
   }
}

static void print_list(Node *head)
{
    Node *p = head->next;
    while(p)
    {
        printf("dev type : %02x%02x ; dev channel : %02x ; dev status : %02d\n",
                p->data->devtype[0],p->data->devtype[1],p->data->devchannel,p->data->devstatus);
        p = p->next;
    }
}
/*
 * 此函数用来检测新上线的设备是否已经插入到链表中，如果在，则更新短地址并返回1，不在则返回-1
 * 4个参数分别为链表名，设备mac地址即长地址，设备短地址,通道
 *
 * */
static int check_updata(Node *head,uint8 *devlongaddr,uint8 *devshortaddr,uint8 devchannel,int status)
{
    Node *p = head;
    while(p != NULL)
    {
        if( p->data->devlongaddr[0] == devlongaddr[0] && p->data->devlongaddr[1] == devlongaddr[1]
         && p->data->devlongaddr[2] == devlongaddr[2] && p->data->devlongaddr[3] == devlongaddr[3] 
         && p->data->devlongaddr[4] == devlongaddr[4] && p->data->devlongaddr[5] == devlongaddr[5] 
         && p->data->devlongaddr[6] == devlongaddr[6] && p->data->devlongaddr[7] == devlongaddr[7] )
        {
            if(p->data->devchannel == devchannel)
            {
                /*更新短地址*/
                p->data->devshortaddr[0] = devshortaddr[0];
                p->data->devshortaddr[1] = devshortaddr[1];
                p->data->devstatus = status;
                return 1;
            }
        }
        p = p->next;
    }
    return -1;
}

/*
 * 字符转换成对应的十六进制值
 * */
static unsigned char chartobyte(const char c)
{
    if('a' <= c && c <= 'f')
        return (c - 'a' + 10);
    else if('A' <= c && c <= 'F')
        return (c - 'A' + 10);
    return (c - '0');
}

/*
 * 每两个字符组成一个字节，字符串转字节数组
 *  
 * */
static unsigned char strtobyte(const char c1,const char c2)
{
    return (chartobyte(c1) * 16 + chartobyte(c2));
}

/*
 * 校验位计算，把字节数组每个值进行异或
 * */
static unsigned char check_cmd_use_xor(const unsigned char *pstr,const int len)
{
    int i = 0;
    unsigned char val = pstr[0];
    while(i < len)
    {
        val ^= pstr[i+1];
        i++;
    }
    printf("cmd check result xor = %02x (%d)\n",val,i);
    return val;
}

/*把设备反馈给网关的mac地址上传到客户端*/
static int upload_mac_to_client(const unsigned char *addr,const int status)
{
    printf("dev status :%d\n",status);
    return 0;
}

/*解析设备的回复，提取有用的数据并插入到链表中*/
static int parse_reply(const unsigned char *pstr,const int cmd_len)
{
#if 1 
    printf("Reply: \n");
    int i = 0;
    while(i < cmd_len)
    {
        printf("%02x ",pstr[i]);
        i++;
    }
    printf("\n");
#endif
    Devdesc devdesc;
    memset(&devdesc,0,sizeof(Devdesc));
    if(pstr[cmd_len-1] == check_cmd_use_xor(pstr,cmd_len-2))
    {

#if DEBUG
        printf("the recv cmd data is correct\n");
#endif
        devdesc.msg_type = pstr[2];
#if DEBUG
        printf("msg type = 0x%02x\n",devdesc.msg_type);
#endif
        if(devdesc.msg_type == 0x03)
        {
            devdesc.devshortaddr[0] = pstr[3];
            devdesc.devshortaddr[1] = pstr[4];
#if DEBUG
            printf("short addr = %02x:%02x\n",devdesc.devshortaddr[0],devdesc.devshortaddr[1]);
#endif
            devdesc.devlongaddr[0] = pstr[5];
            devdesc.devlongaddr[1] = pstr[6];
            devdesc.devlongaddr[2] = pstr[7];
            devdesc.devlongaddr[3] = pstr[8];
            devdesc.devlongaddr[4] = pstr[9];
            devdesc.devlongaddr[5] = pstr[10];
            devdesc.devlongaddr[6] = pstr[11];
            devdesc.devlongaddr[7] = pstr[12];
#if DEBUG
            printf("the dev mac = %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",devdesc.devlongaddr[0],\
                    devdesc.devlongaddr[1],devdesc.devlongaddr[2],devdesc.devlongaddr[3],devdesc.devlongaddr[4],\
                    devdesc.devlongaddr[5],devdesc.devlongaddr[6],devdesc.devlongaddr[7]);
#endif
            devdesc.devtype[0] = pstr[13];
            devdesc.devtype[1] = pstr[14];
#if DEBUG
            printf("the dev type = %02x%02x \n",devdesc.devtype[0],devdesc.devtype[1]);
#endif
            devdesc.devreusebyte = pstr[15];
            devdesc.devchannel = pstr[15];
#if DEBUG
            printf("the dev reuse byte = 0x%02x \n",devdesc.devreusebyte);
#endif
            devdesc.devctrlcmd = pstr[16];
#if DEBUG
            printf("the dev ctrl cmd = 0x%02x \n",devdesc.devctrlcmd);
#endif
            if(((pstr[13] << 8) | pstr[14]) == CMD_CLASS_KAIGUAN || ((pstr[13] << 8) | pstr[14]) == CMD_CLASS_CHAZUO)
            {
                if(pstr[16] == CMD_SWITCH_ON)
                    devdesc.devstatus = STATUS_ON;
                else if(pstr[16] == CMD_SWITCH_OFF)
                    devdesc.devstatus = STATUS_OFF;
            }
            else if(((pstr[13] << 8) | pstr[14]) == CMD_CLASS_CHUANGLIAN)
            {
                if(pstr[16] == CMD_TRISTATE_UP)
                    devdesc.devstatus = STATUS_ON;
                else if(pstr[16] == CMD_TRISTATE_OVER)
                    devdesc.devstatus = STATUS_STOP;
                else if(pstr[16] == CMD_TRISTATE_DOWN)
                    devdesc.devstatus = STATUS_OFF;
            }
            else
            {
                if(pstr[16] == CMD_ALARMMONI_ENABLE)
                    devdesc.devstatus = STATUS_ONALARMING;
                else if(pstr[16] == CMD_ALARMMONI_DISABLE)
                    devdesc.devstatus = STATUS_UNALARMING;
                else if(pstr[16] == CMD_ALARMMONI_ALARMING)
                    devdesc.devstatus = STATUS_ALARMING;
            }
            g_status = devdesc.devstatus;

            if(cmd_len - 1 > 17)
            {
                int i = cmd_len -1 -17;
#if DEBUG
                printf("reserved data length  = %d\n",i);
#endif
                int j = 0;
                while(i-- && j < MAX_RESERVED_LEN)
                {
                    devdesc.devcmddata[j] = pstr[16+j+1];
#if DEBUG
                    printf("the reserved data = 0x%02x \n",devdesc.devcmddata[j]);
#endif
                    j++;
                }
            }

            if(check_updata(head,devdesc.devlongaddr,devdesc.devshortaddr,devdesc.devchannel,devdesc.devstatus) < 0)
            {
                insert_tail(&head,&devdesc);
                upload_mac_to_client(devdesc.devlongaddr,devdesc.devstatus);
            }
        }
        return 4;
    }
    printf("the msg parse failed 502\n");
    return -4;
}

/*从回复中寻找数据开始标识*/
static int find_reply_head(const char *pstr)
{
    if(find_flag > 0)
        return 1;
    int i = 0;
    while(i < g_offset)
    {
        if(pstr[i] == CMD_CLASS_HEAD)
        {
#if DEBUG
            printf("have found head in the message\n");
#endif
            find_flag = 1;
            return 1;
        }
        i++;
    }
    return -1;
}

/*从回复中解析出整个回复的正确长度，这个长度不包括校验位很头和长度本身，共3个字节*/
static int find_reply_len(const unsigned char *pstr,int *cmd_len)
{
    if(find_flag > 1)
        return 2;
    int i = 0;
    while(i < g_offset)
    {
        if(pstr[i] == CMD_CLASS_HEAD)
        {
            if(g_offset - i > 0)
            {
                find_flag = 2;
                *cmd_len = pstr[i+1];
#if DEBUG
                printf("have found len int the message\n");
#endif
                return 2;
            }
            else
                break;
        }
        i++;
    }
    return -2;
}

/*根据数据长度找到回复的尾部，解析出来就是完整的回复了，并保存到字节数组中*/
static int find_reply_tail(const unsigned char *pstr,const int cmd_len,unsigned char *cmd)
{
    if(find_flag > 2)
        return 3;
    int i = 0,j = 0;
    int flag = 0;
    while(i < g_offset)
    {
        if(pstr[i] == CMD_CLASS_HEAD)
        {
            if(g_offset - i >= cmd_len + 3)
            {
                while(i < g_offset)
                {
                    cmd[j] = pstr[i];
                    j++;
                    i++;
                }
                find_flag = 3;
#if DEBUG
                printf("have found finished\n");
#endif
                return 3;
            }
        }
        i++;
    }
    return -3;
}


static int extract_msg()
{
    if(strstr(pstrzb,"Starting") != NULL)
    {
        if(strstr(pstrzb,"_A") != NULL)
        {
            strtok(pstrzb,"-");
            zb_mac = strtok(NULL,"_");
#if DEBUG
            printf("zigbee gateway self mac = %s\n",zb_mac);
#endif
            memset(pstrzb,0,MAX_CMD_BUF_SIZE);
            return 1;
        }
    }
    else     
    {
        static int reply_len = 0;
        if(find_reply_head(pstrzb) == 1)
        {
            if((find_reply_len(pstrzb,&reply_len)) > 0)
            {
#if DEBUG
                printf("command length = %d\n",reply_len);
#endif
                unsigned char cmd[512] = {0};
                if(find_reply_tail(pstrzb,reply_len,cmd) > 0)
                {
                    find_flag = 0;
                    g_offset = 0;
                    memset(pstrzb,0,MAX_CMD_BUF_SIZE);
                    parse_reply(cmd,reply_len+3);
                    reply_len = 0;
                    return 5;
                }
            }
        }
    }
    return 0;
}

static int send_uart_msg(const unsigned char *cmd,const int len)
{
#if 1
    printf("Request : \n");
    int i = 0;
    while(i < len)
    {
        printf("%02x ",cmd[i]);
        i++;
    }
    printf("\n");
#endif

    int r = write(g_uart_fd,cmd,len);
    if(r <= 0)
    {
        printf("cmd send failed !!!\n");
        return -1;
    }
    return 0;
}

static int recv_uart_msg(const unsigned char *buf,const int len)
{
    if(find_flag >= 3)
        return 1;
    int i = 0;
    while(i < len)
    {
        pstrzb[g_offset] = buf[i];
        g_offset++;
        i++;
    }
    if(select_flag == 0)
    {
        if(g_offset > 17)
        {
            extract_msg(); //解析数据
        }
    }
    return 0;
}


static int set_opt(int fd, const int nSpeed, const int nBits, const char nEvent, const int nStop)
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
    return 0;
}

static int UART_Init()
{
    unsigned int UartBitRate = 0;
    UartBitRate = 115200;
    g_uart_fd = open("/dev/ttyAMA1", O_RDWR|O_NOCTTY|O_NDELAY);
    if (g_uart_fd < 0)
    {
        printf("open uart error: %s\n", strerror(errno));
        return -1;
    }

    if (set_opt(g_uart_fd, UartBitRate, 8, 'N', 1) < 0)
    {
        printf("set uart option failed !\n"); 
		close(g_uart_fd);
		g_uart_fd = -1;
        return -1;
    }
    printf("...init uart success, bitrate:%u, fd:%d\n", UartBitRate, g_uart_fd);

    return 0;
}

static int free_arg()
{
    if(head != NULL)
    {
        earse_list(&head);
    }
    return 0;
}

void *Handle_Zigbee_Recv(void *arg)
{
    int ret = 0;
    fd_set uart_fds;
    struct timeval tv;
    int len = 0;
    unsigned char UartRecvBuf[32] = {0};
    printf("...uart thread start...\n");
    while (1)
    {
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        FD_ZERO(&uart_fds);
        FD_SET(g_uart_fd, &uart_fds);

        ret = select(g_uart_fd+1, &uart_fds, NULL, NULL, &tv);
        if (ret <= 0 )
        {
            usleep(1000);
            continue;
        }

        if (FD_ISSET(g_uart_fd, &uart_fds))
        {
            memset(UartRecvBuf, 0, sizeof(UartRecvBuf));
            len = read(g_uart_fd, UartRecvBuf, sizeof(UartRecvBuf));
            if (len > 0)
            {
                recv_uart_msg(UartRecvBuf,len);
#if DEBUG 
                int i = 0;
                while(i < len)
                {
                    printf("%02x ",UartRecvBuf[i]);
                    i++;
                }
                printf("\n");
#endif
            }
        }
    }
    free_arg();
    return NULL;
}

int HK_Zigbee_Thread_Init()
{
    create_head(&head);
    int ret = 0;
    pthread_t Uart_Event;
    void *thread_result;
    ret = UART_Init(); //init uart options.
    if (ret < 0)
    {
        return -1;
    }

    /** receive response info from slave machine **/
    ret = pthread_create(&Uart_Event, NULL, (void *)Handle_Zigbee_Recv, NULL);
    if (0 != ret)
    {
        printf("pthread_create failed with:%d, %s\n", errno, strerror(errno));
        pthread_detach(Uart_Event);
        return -1;
    }
    return 0;
}

static int Contrl_Zigbee_Dev(const unsigned char *devmacaddr,const unsigned char msgtype ,const int channel,
                             const unsigned char command,const char *value)
{
    unsigned char cmd[256] = {0};
    cmd[0] = CMD_CLASS_HEAD;
    Node *p = head;
    while(p != NULL)
    {
        if( p->data->devlongaddr[0] == devmacaddr[0] && p->data->devlongaddr[1] == devmacaddr[1] 
         && p->data->devlongaddr[2] == devmacaddr[2] && p->data->devlongaddr[3] == devmacaddr[3]
         && p->data->devlongaddr[4] == devmacaddr[4] && p->data->devlongaddr[5] == devmacaddr[5]
         && p->data->devlongaddr[6] == devmacaddr[6] && p->data->devlongaddr[7] == devmacaddr[7] )
        {
            cmd[2]  = msgtype;

            cmd[3]  = p->data->devshortaddr[0];
            cmd[4]  = p->data->devshortaddr[1];

            cmd[5]  = p->data->devlongaddr[0];
            cmd[6]  = p->data->devlongaddr[1];
            cmd[7]  = p->data->devlongaddr[2];
            cmd[8]  = p->data->devlongaddr[3];
            cmd[9]  = p->data->devlongaddr[4];
            cmd[10] = p->data->devlongaddr[5];
            cmd[11] = p->data->devlongaddr[6];
            cmd[12] = p->data->devlongaddr[7];

            cmd[13] = p->data->devtype[0];
            cmd[14] = p->data->devtype[1];

            int key = (cmd[13] << 8 | cmd[14]);
            switch(key)
            {
                case CMD_CLASS_KAIGUAN:
                case CMD_CLASS_CHAZUO:
                case CMD_CLASS_CHUANGLIAN:
                    {
                        /*智能灯开关或者插座或者窗帘*/
                        cmd[15] = channel;
                        cmd[16] = command;
                        cmd[1] = 0x0f;
                        cmd[17] = check_cmd_use_xor(cmd,cmd[1]+1);
                        break;
                    }
                case CMD_CLASS_WENSHIDU:
                    break;
                case CMD_CLASS_BAOJINGQI:
                    break;
                case CMD_CLASS_TIAOGUANG:
                    break;
                case CMD_CLASS_HONGWAI:
                    {
                        cmd[15] = channel;
                        cmd[16] = command;
                        switch(cmd[16])
                        {
                            case CMD_DC6008_TX:
                                {
                                    int len = strlen(value);
                                    int i = 0;
                                    while(i < len)
                                    {
                                        cmd[17 + i/2] = strtobyte(value[i],value[i+1]);
                                        i += 2;
                                    }
                                    cmd[1] = 0x0f + len/2;
                                    cmd[17+i/2] = check_cmd_use_xor(cmd,cmd[1]+1);
                                    break;
                                }
                            case CMD_DC6008_STUDYMODE:
                                {
                                    cmd[1] = 0x0f;
                                    cmd[17] = check_cmd_use_xor(cmd,cmd[1]+1);
                                }
                                break;
                            default :
                                break;
                        }
                    }
                    break;
                case CMD_CLASS_MENCI:
                    break;
                case CMD_CLASS_YANWU:
                    break;
                case CMD_CLASS_RANQI:
                    break;
                case CMD_CLASS_SOS:
                    break;
                default:
                    break;
            }
            if(select_flag == 1)
            {
                send_uart_msg(cmd,cmd[1]+3);
                usleep(15000);
                int i = 30;
                while(i--)
                {
                    g_status = STATUS_OFFLINE;
                    if(g_offset > 17)
                    {
                        if(extract_msg() > 0)
                            break;
                    }
                    usleep(5000);
                }
            }
            else
                send_uart_msg(cmd,cmd[1]+3);
            return 1;
        }
        else
            p = p->next;
    }
    g_status = STATUS_OFFLINE;
    printf("The device is not found 402\n");
    return 0;
}

static int Zb_Gateway_Learn_Mode()
{
    unsigned char cmd[4] = {0xfe,0x01,0xce,0x31};
    send_uart_msg(cmd,4);
    return 0;
}

static int Zb_Gateway_Reboot_Mode()
{
    unsigned char cmd[4] = {0xfe,0x01,0xca,0x35};
    send_uart_msg(cmd,4);
    return 0;
}

static int Zb_Kaiguan_On(const unsigned char *devmacaddr,const int channel)
{
    Contrl_Zigbee_Dev(devmacaddr,SEND_DEV_MSG,channel,CMD_SWITCH_ON,NULL);
    return 0;
}

static int Zb_Kaiguan_Off(const unsigned char *devmacaddr,const int channel)
{
    Contrl_Zigbee_Dev(devmacaddr,SEND_DEV_MSG,channel,CMD_SWITCH_OFF,NULL);
    return 0;
}

static int Zb_Kaiguan_Status(const unsigned char *devmacaddr,const int channel)
{
    Contrl_Zigbee_Dev(devmacaddr,SEND_DEV_MSG,channel,CMD_SWITCH_ST,NULL);
    return 0;
}

static int Zb_Chazuo_On(const unsigned char *devmacaddr)
{
    Contrl_Zigbee_Dev(devmacaddr,SEND_DEV_MSG,0,CMD_SWITCH_ON,NULL);
    return 0;
}

static int Zb_Chazuo_Off(const unsigned char *devmacaddr)
{
    Contrl_Zigbee_Dev(devmacaddr,SEND_DEV_MSG,0,CMD_SWITCH_OFF,NULL);
    return 0;
}

static int Zb_Chazuo_Status(const unsigned char *devmacaddr)
{
    Contrl_Zigbee_Dev(devmacaddr,SEND_DEV_MSG,0,CMD_SWITCH_ST,NULL);
    return 0;
}

static int Zb_Chuanglian_Up(const unsigned char *devmacaddr)
{
    Contrl_Zigbee_Dev(devmacaddr,SEND_DEV_MSG,0,CMD_TRISTATE_UP,NULL);
    return 0;
}

static int Zb_Chuanglian_Down(const unsigned char *devmacaddr)
{
    Contrl_Zigbee_Dev(devmacaddr,SEND_DEV_MSG,0,CMD_TRISTATE_DOWN,NULL);
    return 0;
}

static int Zb_Chuanglian_Status(const unsigned char *devmacaddr)
{
    Contrl_Zigbee_Dev(devmacaddr,SEND_DEV_MSG,0,CMD_TRISTATE_ST,NULL);
    return 0;
}

static int Zb_Chuanglian_Stop(const unsigned char *devmacaddr)
{
    Contrl_Zigbee_Dev(devmacaddr,SEND_DEV_MSG,0,CMD_TRISTATE_OVER,NULL);
    return 0;
}

static int Zb_Hongwaiqiu_Learn(const unsigned char *devmacaddr)
{
    Contrl_Zigbee_Dev(devmacaddr,SEND_DEV_MSG,0,CMD_DC6008_STUDYMODE,NULL);
    return 0;
}

static int Zb_Hongwaiqiu_Tx(const unsigned char *devmacaddr,const char *value)
{
    Contrl_Zigbee_Dev(devmacaddr,SEND_DEV_MSG,0,CMD_DC6008_TX,value);
    return 0;
}

static int Zb_Hongwaiqiu_Data(const unsigned char *devmacaddr,const char *value)
{
    return 0;
}

int zigb_Opt_Control(const int Model,const unsigned char *devmacaddr,const int Cmd,const int channel,const char *value )
{
    switch( Model )
    {
        case LIANYONG :
            {
                switch(Cmd)
                {
                    case LIGHT_ON:
                        Zb_Kaiguan_On(devmacaddr,channel);
                        break;
                    case LIGHT_STATUS:
                        select_flag = 1;
                        Zb_Kaiguan_Status(devmacaddr,channel);
                        break;
                    case LIGHT_OFF:
                        Zb_Kaiguan_Off(devmacaddr,channel);
                        break;

                    case CHAZUO_ON:
                        Zb_Chazuo_On(devmacaddr);
                        break;
                    case CHAZUO_OFF:
                        Zb_Chazuo_Off(devmacaddr);
                        break;
                    case CHAZUO_STATUS:
                        select_flag = 1;
                        Zb_Chazuo_Status(devmacaddr);
                        break;

                    case CHUANGLIAN_UP:
                        Zb_Chuanglian_Up(devmacaddr);
                        break;
                    case CHUANGLIAN_DOWN:
                        Zb_Chuanglian_Down(devmacaddr);
                        break;
                    case CHUANGLIAN_STOP:
                        Zb_Chuanglian_Stop(devmacaddr);
                        break;
                    case CHUANGLIAN_STATUS:
                        select_flag = 1;
                        Zb_Chuanglian_Status(devmacaddr);
                        break;

                    case HONGWAIQIU_LEARN:
                        Zb_Hongwaiqiu_Learn(devmacaddr);
                        break;
                    case HONGWAIQIU_TX:
                        Zb_Hongwaiqiu_Tx(devmacaddr,value);
                        break;
                    case HONGWAIQIU_DATA:
                        Zb_Hongwaiqiu_Data(devmacaddr,value);
                        break;

                    case ZIGBEE_LEARN_MODE:
                        Zb_Gateway_Learn_Mode();
                        break;
                    case ZIGBEE_REBOOT:
                        Zb_Gateway_Reboot_Mode();
                        break;

                    default :
                        break;
                }
                break;
            }
        default :
            break;
    }
    if(select_flag == 1)
    {
        select_flag = 0;
    }
    else
        usleep(100000);
#if DEBUG
    printf(".................%d\n",g_status);
#endif
    return g_status;
}


