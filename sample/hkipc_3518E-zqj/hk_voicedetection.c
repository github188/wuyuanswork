#include <stdio.h>

extern int audio_alarm;
int get_chkaudioalarm_buf_flag = 0;
char chkAudioBuf[320*5] = {0};

int Get_VoiceAlarmLv()
{
    audio_alarm = conf_get_int("/mnt/sif/hkipc.conf","audioalarmlv");
    if( audio_alarm==0 )
        audio_alarm=1;
    printf("Get_VoiceAlarmLv  :  %d\n",audio_alarm);
    return audio_alarm;
}

int Set_VoiceAlarmLv(int nValues)
{
    conf_set_int("/mnt/sif/hkipc.conf","audioalarmlv",nValues);
    audio_alarm = nValues;
    if(audio_alarm > 1)
        CreateAudioThread();  
    return 0;
}

static int hk_chkAudioAlarmSens(int nValue)
{
    int Sens = -1;
    switch(nValue)
    {
        case 4:
            Sens = 16000;
            break;
        case 3:
            Sens = 25000;
            break;
        case 2:
            Sens = 45000; 
            break;
    }
    return Sens;
}

static int sense_chk(char *buf,unsigned long len) 
{
    int i = 0;
    int max = 0;
    int min = 0;
    short *pbuf=(short *)buf;
    len = len/sizeof(short);
    for(i = 0;i < len; i++)
    {
        if(pbuf[i]>0)
        {
            max=pbuf[i]>max?pbuf[i]:max;
        }
        else
        {
            min=pbuf[i]<min?pbuf[i]:min;
        }
    }
    return (max-min);
}


int audioSense(int alarmLv)  
{
    if(alarmLv < 2)
        return -1;
    int Sens = 0;
    Sens = hk_chkAudioAlarmSens(alarmLv); 
    if(Sens < 0)
        return -1;

    if(get_chkaudioalarm_buf_flag == 1)
    {
        int ret = sense_chk(chkAudioBuf,strlen(chkAudioBuf));
        get_chkaudioalarm_buf_flag = 0;
        if(ret > Sens)
        {
            return 1;
        }
    }
    return 0;
}


