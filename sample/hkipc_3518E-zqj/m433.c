#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

#include "m433.h"
#include "hkipc_hk.h"

/* Light xhd and ysm */
short int g_LightOpenOnAlarm = 0;
short int g_LightOpenOnAlarmCountTime = 0;
short int g_LightOpenReason = 0;
short int g_LightCloseReason = 0;
static short int g_LightOpenOnTime = 0;
static short int g_LightCurrentStatus = 0;
static short int g_LightOpenTimeHour = 0;
static short int g_LightOpenTimeMin = 0;
static short int g_LightCloseTimeHour = 0;
static short int g_LightCloseTimeMin = 0;
static char g_starttime[128] = {0};
static char g_endtime[128] = {0};
extern unsigned int g_PowerKeyState;
extern short g_sdIsOnline;

/* M433 */
int g_M433_Fd = 0;
unsigned int g_M433_AD_Val = 0;
static int g_M433_State = 0;
static struct M433DEV m433dev;
struct itimerval m433_tick;
struct transe_t tx;

struct m433_data_t m433_data = {
    .keep_run = 1,
    .current_ad = 0,
    .alarm_flag = 0,
    .test_flag = 0,
};


static int m433_save_param()
{
    int i = 0;
    FILE *fp = NULL;

    fp = fopen(M433_PATH,"w");
    if(fp == NULL)
    {
        fprintf(stderr,"fopen w %s failed\r\n",M433_PATH);
        return -1;
    }
    for(i = 0;i < REFERENCE_MAX;i++)
        fprintf(fp,M433_CODE"%d=0x%x\r\n",i,m433_data.reference_table[i]);
    fclose(fp);
    return 0;
}

void m433_delete_code(int index, char *cIndex, int iCode)
{
    //printf("iCode=%d....data=%d.....\n",iCode, m433_data.reference_table[index]);
    if( iCode == m433_data.reference_table[index] )
    {
        m433_data.reference_table[index] = 0x0;

        conf_set(M433_PATH, cIndex, "0x0");
    }
}

static int m433_get_param()
{
    int i = 0;
    FILE *fp = NULL;

    fp = fopen(M433_PATH, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "fopen r %s failed\r\n", M433_PATH);
        m433_data.reference_table[0] = 0x0;
        m433_data.reference_table[1] = 0x0;
        m433_data.reference_table[2] = 0x0;
        m433_data.reference_table[3] = 0x0;
        return 0;
    }

    for (i = 0; i < REFERENCE_MAX; i++)
    {
        fscanf(fp, M433_CODE"%d=0x%x\r\n", &i, &m433_data.reference_table[i]);
    }

    fclose(fp);
    return 0;
}

static int m433_set_code()
{
    ioctl(g_M433_Fd, FILLTABLE, m433_data.reference_table);
    return 0;
}

extern int HK_Snap_Warning_Pictures(void);
static void arbitration(unsigned int code)
{
    static char DevRoll = 4;
    static char TeleConRoll = 0;
    static char MatchDevCode = 0;
    int ret = 0;
    int i = 0;
    int arg = 0;
    static int cnt = 0;   

    m433_data.current_ad = g_M433_AD_Val;
    g_M433_AD_Val = 0;

    if (m433_data.current_ad == m433_data.reference_table[2]) 
    {
        m433_data.alarm_flag = 0;
        m433dev.normal_mode = 0;
    }

    //printf("--- mode: %d, alarm flag: %d ---\n", m433dev.normal_mode, m433_data.alarm_flag);
    if (m433dev.normal_mode == 0)
    {
        //printf("--- learn mode ---\n");
       // m433_data.alarm_flag = 0;

        for (i = 0; i < REFERENCE_MAX; i++)
        {
            if (i < 4)
            {
                if ((m433dev.telecontrol >> i) & 0x1) //遥控码控制标记为
                {
                    printf("--- judge learn Telecontrol code ---\n");
                    if (m433_data.reference_table[i] != 0)
                    {
                        if (m433_data.reference_table[i] == m433_data.current_ad)
                        {
                            printf("=== Telecontrol had learned ===\n");
                            break;
                        }
                        else
                        {
                            if (i == 3)
                            {
                                printf("--- full reset telecontrol[%d] = 0x%x\n", TeleConRoll, m433_data.current_ad);
                                m433_data.reference_table[TeleConRoll++] == m433_data.current_ad;
                                if (TeleConRoll == 4)
                                    TeleConRoll = 0;
                                break;
                                //alarm_handler();//接收到遥控码学习完成
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                    else //if(m433_data.reference_table[i] == 0 )
                    {
                        printf("--- temp set telecontrol[%d] = 0x%x ---\n", i, m433_data.current_ad);
                        m433_data.reference_table[i] = m433_data.current_ad;
                        m433dev.normal_mode = 1;
                        m433dev.telecontrol = 0;
                        tx.code = m433_data.reference_table[i];
                        tx.mode = LEARN_MODE;
                        tx.flag = TELECONTROL; 
                        //alarm_handler();//接收到遥控码学习完成
                        break;
                    }
                }
                else
                {
                    if (i == 3)
                        printf("--- not telecontrol code ---\n");
                }
            }
            else  //i >= 4
            {
                //printf("--- dev code ---\n");
                if (m433_data.current_ad == m433_data.reference_table[i])
                {
                    printf("=== had learned ===\n");
                    tx.code = m433_data.reference_table[i];
                    tx.mode = LEARN_MODE;
                    tx.flag = FLAG_LEARN; 
                    //alarm_handler();//接收到设备码学习完成
                    m433dev.normal_mode = 1;
                    m433_data.alarm_flag = 1;
                    sccOnAlarm(0,100,m433_data.current_ad);
                    m433_save_param();
                    break;
                }
                else
                {
                    if(m433_data.reference_table[i] == 0)
                    {
                        m433_data.reference_table[i] = m433_data.current_ad;
                        printf("--- temp set learn dev code table[%d] = 0x%x ---\n", i, m433_data.reference_table[i]);
                        m433dev.normal_mode = 1;
                        tx.code = m433_data.reference_table[i];
                        tx.mode = LEARN_MODE;
                        tx.flag = FLAG_LEARN; 
                        sccOnAlarm(0,100,m433_data.current_ad);
                        m433_save_param();
                        //alarm_handler();//接收到设备码学习完成
                        break;
                    }
                    else
                    {
                        if(i == REFERENCE_MAX - 1)
                        {
                            printf("--- full reset table[%d] = 0x%x ---\n", DevRoll, m433_data.current_ad);
                            m433_data.reference_table[DevRoll++] = m433_data.current_ad;
                            m433dev.normal_mode = 1;
                            if(DevRoll == REFERENCE_MAX)
                                DevRoll = 4;
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
        }
    }
    else //正常模式
    {
        //printf("--- normal mode alarm flag = %d---\n", m433_data.alarm_flag);
        for (i = 0; i < REFERENCE_MAX; i++) //对比码表码值
        {
            if (m433_data.current_ad == m433_data.reference_table[i]) //如果有和接收码值一致时
            {
                ///g_M433_AD_Valprintf("--- match code, i:%d ---\n", i);
                if (i == 0)
                {
                    m433_data.alarm_flag = 1;
                    printf("--- alarm set ---\r\n");
                    MatchDevCode = 1;
                    break;
                }
                else if(i == 1)
                {
                    m433_data.alarm_flag = 0;
                    printf("--- alarm unset ---\r\n"); 
                    MatchDevCode = 1;
                    break;
                }
                else if (i == 3 || m433_data.test_flag == 1)
                {
                    tx.code = m433_data.reference_table[i];
                    tx.mode = TEST_MODE;
                    tx.flag = FLAG_TEST; 
                    m433_data.test_flag = 0;
                    MatchDevCode = 1;
                    //sccOnAlarm(0,6,m433_data.current_ad);
                    //printf("test alarming!\r\n"); 
                    break;
                }
                else if (i > 3)
                {
                    if (m433_data.alarm_flag == 1)
                    {
                        tx.code = m433_data.reference_table[i];
                        tx.mode = NORMAL_MODE;
                        tx.flag = FLAG_ALARM; 
                        sccOnAlarm(0,6,m433_data.current_ad);
                        //printf("alarming!\r\n");
                        MatchDevCode = 1;
                    #if (DEV_INFRARED) //snapshot 3 pictures and save into SD card while 433 alarming.
                        if (1 == g_sdIsOnline)
                        {
                            g_EnableSnapImg = 1;
                            HK_Snap_Warning_Pictures();
                        }
                    #endif
                        break;
                    }
                    else
                    {
                        MatchDevCode = 1;
                        //printf("--- match dev code ---\n");
                        break;
                    }
                }
            }
        }
        if (MatchDevCode == 0)
            printf("--- without match code ---\n");
        else
            MatchDevCode = 0;
    }
}

static int g_signoCount=0;
void sig_handler(int signo)
{
    if(signo == SIGSEGV)
    {
        if( g_signoCount++ > 100 )
        {
            printf("--- catch signal ---\n");
            sd_record_stop();
            sleep(2);
            system("umount /mnt/mmc");
            sleep(2);
            system("reboot");
        }
    }
    if (signo == SIGUSR2)
    {
        m433_tick.it_value.tv_sec = 0;
        m433_tick.it_value.tv_usec = 0;
        m433_tick.it_interval.tv_sec = 0;
        m433_tick.it_interval.tv_usec = 0;
        if (setitimer(ITIMER_REAL, &m433_tick, NULL) < 0)
        {
            printf("Set timer failed, %d, %s\n", errno, strerror(errno));
        }

        read(g_M433_Fd, &g_M433_AD_Val, 1);
        //printf("--- g_M433_AD_Val = 0x%x ---\n", g_M433_AD_Val);
        arbitration( g_M433_AD_Val ); //parse 433 state and alarm.
        g_M433_AD_Val = 0;
        m433dev.normal_mode = 1;
    }
    else if (signo == SIGALRM)
    {
        m433dev.normal_mode = 1;
        printf("learn mode time out\n");
    }
    /*
    else if(signo == SIGSEGV)
    {
        printf("Waring !!! A SIGSEGV is created \n");
        //system("sync");
        //sd_record_stop();
        //system("umount /mnt/mmc");
        //sleep(10);
        //system("reboot");
    }
    */
}

void install_sighandler( void (*handler)(int) )
{
    signal(SIGUSR2,handler);
    signal(SIGALRM,handler);
    signal(SIGSEGV,handler);
}

void uninit_m433()
{
    if( g_M433_Fd > 0  )
    {
        m433_set_code(); 
        close(g_M433_Fd);
        g_M433_Fd = 0;
    }
}

int init_m433(pid_t pid)
{
    int ret = 0;
    printf("433 pid: %d\n", pid);
    g_M433_Fd = open("/dev/m433dev", O_RDWR); //打开文件节点
    if (g_M433_Fd < 0)
    {
        printf("can't open!\n");
        return -1;
    }

    ioctl(g_M433_Fd, M433SIG, &pid);//传入进程pid
    ioctl(g_M433_Fd, PROBE, &ret); //探测设备
    printf("--- probe ret = %d ---\n", ret);
    if (ret != 1)
    {
        printf("433 HW detect faild, %d, %s !\n", errno, strerror(errno));
        close(g_M433_Fd);
        g_M433_Fd = 0;
        return -2;
    }

    m433_get_param();
    m433_set_code();
    ioctl(g_M433_Fd, START, &ret);//开启设备
    printf("--- start ret = %d ---\n", ret);
    if (ret != 1)
    {
        printf("=== HW init faile ===\n");
        close(g_M433_Fd);
        g_M433_Fd = 0;
        return -3;
    }

    //printf("[%s, %d] m433 state:%d, alarm_flag: %d\n", __func__, __LINE__, g_M433_State, m433_data.alarm_flag);
    //signal(SIGALRM,sig_handler);
    g_M433_State = conf_get_int("/mnt/sif/hkipc.conf", "m433_state");
    if (g_M433_State == 0)
    {
        m433dev.normal_mode = 1;
        m433_data.alarm_flag = 0;
        g_M433_State = 1;
    }
    else if(g_M433_State == 2)
    {
        m433dev.normal_mode = 1;
        m433_data.alarm_flag = 1;
    }
    printf("[%s, %d] m433 state:%d, alarm_flag: %d\n", __func__, __LINE__, g_M433_State, m433_data.alarm_flag);
    memset(&m433_tick, 0, sizeof(m433_tick));
    return 0;
}

static int set_g_M433_State(int operation)
{
    int i = 0;
    switch(operation)
    {
        case FLAG_ALARM:
            printf("set operate : alarm mode\n");
            m433dev.normal_mode = 1;
            m433_data.alarm_flag = 1;
            conf_set_int("/mnt/sif/hkipc.conf", "m433_state", 2);
            g_M433_State = 2;
            break;

        case FLAG_UNALARM:
            printf("set operate : unalarm mode\n");
            m433dev.normal_mode = 1;
            m433_data.alarm_flag = 0;
            conf_set_int("/mnt/sif/hkipc.conf", "m433_state", 1);
            g_M433_State = 1;
            break;

        case FLAG_LEARN:
            printf("set operate : learn mode\n");
            m433dev.normal_mode = 0;
            m433_tick.it_value.tv_sec = 20;
            m433_tick.it_value.tv_usec = 0;
            m433_tick.it_interval.tv_sec = 0;
            m433_tick.it_interval.tv_usec = 0;
            if(setitimer(ITIMER_REAL, &m433_tick, NULL) < 0)
                printf("Set timer failed!\n");
            break;

        case FLAG_TEST:
            printf("set operate : test mode\n");
            //read(g_M433_Fd, &g_M433_AD_Val, 1);
            int i = 0;
            for(;i < REFERENCE_MAX;i++)
            {
                if(m433_data.reference_table[i] == g_M433_AD_Val)
                {
                    sccOnAlarm(0,6,g_M433_AD_Val);
                    //printf("test alarming  0x%x\n",g_M433_AD_Val);
                }
            }
            g_M433_AD_Val = 0;
            break;

        case CLEARTABLE:
            for(i = 0; i < REFERENCE_MAX; i++)
            {
                m433_data.reference_table[i] = 0;
            }
            for(i = 0; i < REFERENCE_MAX; i++)
            {
                printf("[%4d] code vale 0x%x\n",i, m433_data.reference_table[i]);
            }
            break;
        default:
            break;
    }	

    return 0;
}


static int SetLightOpenOrClose(const int iFlag)
{
    if(iFlag == 1)
    {
        g_LightOpenReason |= USER_OPEN;
        g_LightCloseReason &= (~USER_OPEN);
        g_PowerKeyState = 1;
        g_LightCurrentStatus = iFlag;
        conf_set_int(DM_LIGHT_CONF,LIGHT_CUR_STATUS,1);
    }
    else if(iFlag == 2)
    {
        g_LightCloseReason |= USER_OPEN;
        g_LightOpenReason &= (~USER_OPEN);
        g_LightCurrentStatus = iFlag;
        conf_set_int(DM_LIGHT_CONF,LIGHT_CUR_STATUS,2);
        g_PowerKeyState = 0;
    }
    return 0;
}

static int SetLightOpenOnAlarm(const int iFlag)
{
    g_LightOpenOnAlarm = iFlag;
    conf_set_int(DM_LIGHT_CONF,OPEN_LIGHT_ARLAMING,iFlag);
    g_LightOpenOnAlarmCountTime = 0;
    if(g_LightOpenOnAlarm == 1)
        printf("alarming will open the light (200 OK)\n");
    else
    {
        SetLightOpenOrClose( 2 );
        printf("alarming not open the light (201 OK)\n");
    }
    return 0;
}

int sccLightOpenOnTime()
{
    if(g_LightOpenOnTime != 1)
        return -1;
    time_t t;
    struct tm *tt;
    time(&t);
    tt = localtime(&t);

    if(g_LightOpenTimeHour > g_LightCloseTimeHour)
    {
        if(   ( tt->tm_hour > g_LightOpenTimeHour && tt->tm_hour <= 23 ) 
           || ( tt->tm_hour >= 0 && tt->tm_hour < g_LightCloseTimeHour ) 
           || ( tt->tm_hour == g_LightOpenTimeHour && tt->tm_min >= g_LightOpenTimeMin ) 
           || ( tt->tm_hour == g_LightCloseTimeHour && tt->tm_min < g_LightCloseTimeMin )
          )
        {
            goto open_light;
        }
        else
            goto close_light;
    }
    else if(g_LightOpenTimeHour < g_LightCloseTimeHour)
    {
        if(   ( tt->tm_hour > g_LightOpenTimeHour && tt->tm_hour < g_LightCloseTimeHour )
           || ( tt->tm_hour == g_LightOpenTimeHour && tt->tm_min >= g_LightOpenTimeMin  )
           || ( tt->tm_hour == g_LightCloseTimeHour && tt->tm_min < g_LightCloseTimeMin )
           )
        {
            goto open_light;
        }
        else
            goto close_light;
    }
    else if(g_LightOpenTimeHour == g_LightCloseTimeHour)
    {
        if( g_LightOpenTimeHour ==  tt->tm_hour )
        {
            if(g_LightOpenTimeMin > g_LightCloseTimeMin)
            {
                if(tt->tm_min >= g_LightCloseTimeMin && tt->tm_min < g_LightOpenTimeMin)
                {
                    goto close_light;
                }
                else
                    goto open_light;
            }
            else if(g_LightOpenTimeMin < g_LightCloseTimeMin)
            {
                if(tt->tm_min < g_LightCloseTimeMin && tt->tm_min >= g_LightOpenTimeMin)
                {
                    goto open_light;
                }
            }
            goto close_light;
        }
    }
    return 0;

open_light:
    {
        g_LightCloseReason &= (~ONTIME_OPEN);
        g_LightOpenReason |= ONTIME_OPEN;
        g_PowerKeyState = 1;
        return 1;
    }
close_light:
    {
        if(g_LightOpenReason == ONTIME_OPEN)
        {
            g_PowerKeyState = 0;
        }
        g_LightCloseReason |= ONTIME_OPEN;
        g_LightOpenReason &= (~ONTIME_OPEN);
        return 0;
    }
    return 0;
}

int LightOpenOnAlarmCountTime()
{
    if(g_LightOpenOnAlarm == 1)
    {
        if(g_LightOpenOnAlarmCountTime++ > 60)
        {
            if(g_LightOpenReason == ALARMING_OPEN)
            {
                SetLightOpenOrClose(2);
            }
            g_LightCloseReason &= (~ALARMING_OPEN);
            g_LightCloseReason |= ALARMING_OPEN;
        }
    }
    return 0;
}

//int iFlag; 1-open; 2-Close
int sccSetOpenOrCloseLight( int iFlag, char *cStartTime, char *cEndTime )
{
    printf("iFlag = %d ; cStartTime = %s ; cEndTime = %s\n",iFlag,cStartTime,cEndTime);

    strncpy(g_starttime,cStartTime,sizeof(g_starttime));
    strncpy(g_endtime,cEndTime,sizeof(g_endtime));

    char temp[128] = {0};
    strcpy(temp,cStartTime);
    conf_set(DM_LIGHT_CONF,STARTTIME,temp);
    g_LightOpenTimeHour = atoi(strtok(temp,SPLITFLAG));
    g_LightOpenTimeMin = atoi(strtok(NULL,SPLITFLAG));

    memset(temp,0,128);
    strcpy(temp,cEndTime);
    conf_set(DM_LIGHT_CONF,ENDTIME,temp);
    g_LightCloseTimeHour = atoi(strtok(temp,SPLITFLAG));
    g_LightCloseTimeMin = atoi(strtok(NULL,SPLITFLAG));

    if(iFlag == 2)
    {
        g_LightOpenOnTime = 1;
        if(sccLightOpenOnTime() == 1)
            SetLightOpenOrClose(iFlag);
    }

    g_LightOpenOnTime = iFlag;
    conf_set_int(DM_LIGHT_CONF,TIMEOPEN,g_LightOpenOnTime);


    printf("set light... iFlag = %d ; g_LightOpenTimeHour = %d ; g_LightOpenTimeMin = %d ; g_LightCloseTimeHour = %d ; g_LightCloseTimeMin = %d ; g_LightOpenOnTime = %d\n", \
            iFlag,g_LightOpenTimeHour,g_LightOpenTimeMin,g_LightCloseTimeHour,g_LightCloseTimeMin,g_LightOpenOnTime);

    return 0;
}

int sccGetOpenOrCloseLight( int *iFlag, char cStartTime[128], char cEndTime[128] )
{
    strcpy(cStartTime,g_starttime);
    strcpy(cEndTime,g_endtime);
    *iFlag = g_LightOpenOnTime;
    printf(".............scc get light open on time : cStartTime -> cEndTime %s -> %s......................\n",cStartTime,cEndTime);
    return 0;
}

int Init_Light_Conf()
{
    char temp[128] = {0};

    conf_get(DM_LIGHT_CONF,STARTTIME,g_starttime,sizeof(g_starttime));
    conf_get(DM_LIGHT_CONF,ENDTIME,g_endtime,sizeof(g_endtime));
    g_LightOpenOnTime = conf_get_int(DM_LIGHT_CONF,TIMEOPEN);

    g_LightOpenTimeHour = 0;
    g_LightOpenTimeMin = 0;
    g_LightCloseTimeHour = 0;
    g_LightCloseTimeMin = 0;

    if(strlen(g_starttime) > 0)
    {
        strcpy(temp,g_starttime);
        g_LightOpenTimeHour = atoi(strtok(temp,SPLITFLAG));
        g_LightOpenTimeMin = atoi(strtok(NULL,SPLITFLAG));
    }

    memset(temp,0,128);
    if(strlen(g_endtime) > 0)
    {
        strcpy(temp,g_endtime);
        g_LightCloseTimeHour = atoi(strtok(temp,SPLITFLAG));
        g_LightCloseTimeMin = atoi(strtok(NULL,SPLITFLAG));
    }

    g_LightOpenOnAlarm = conf_get_int(DM_LIGHT_CONF,OPEN_LIGHT_ARLAMING);

    g_LightCurrentStatus = conf_get_int(DM_LIGHT_CONF,LIGHT_CUR_STATUS);
    SetLightOpenOrClose(g_LightCurrentStatus);
    printf("Init Light Config :\n\tg_LightOpenOnTime=%d;g_LightOpenTimeHour:g_LightOpenTimeMin=%d:%d;g_LightCloseTimeHour:g_LightCloseTimeMin=%d:%d;g_LightOpenOnAlarm=%d;g_LightCurrentStatus=%d\n",
            g_LightOpenOnTime,g_LightOpenTimeHour,g_LightOpenTimeMin,g_LightCloseTimeHour,g_LightCloseTimeMin,g_LightOpenOnAlarm,g_LightCurrentStatus);
    return 0; 
}


int sccSetSysInfo(int reserve1, int reserve2,int iCmd,int iValues)
{
    switch(iCmd)
    {
        case 111:
            Set_VoiceAlarmLv(iValues);
            break;
        case 204:
            set_g_M433_State(FLAG_LEARN);
            break;
        case 205:
            set_g_M433_State(FLAG_ALARM);
            break;
        case 206:
            set_g_M433_State(FLAG_UNALARM);
            break;
        case 207:
            {
                g_M433_AD_Val = iValues;
                set_g_M433_State(FLAG_TEST);
                break;
            }
        case 208:
            SetLightOpenOrClose(iValues);
            break;
        case 209:
            SetLightOpenOnAlarm(iValues);
            break;
        default :
            break;
    }
    return 0;
}

int sccGetSysInfo(int reserve1,int reserve2,int iCmd,int *iValues)
{
    *iValues = 0;
    switch(iCmd)
    {
        case 111:
            *iValues = Get_VoiceAlarmLv();
            break;
        case 204:
            *iValues = g_LightOpenOnAlarm;
            break;
        case 208:
            *iValues = g_LightOpenOnTime;
            break;
        case 209:
            {
                printf("get m433 state  =  %d\n", g_M433_State);
                *iValues = g_M433_State;
                break;
            }
        default :
            break;

    }
    return 0;
}

