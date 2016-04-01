#ifdef WIN32
#include <Windows.h>
#include <process.h>
#else
#include<pthread.h>
#include <unistd.h>
#define scanf_s scanf 
#endif
#include <stdio.h>
#include "voiceRecog.h"
#include "hkipc_hk.h"
#include "hk_sysaudio.h"
#include "hk_uart.h"

extern  WIFICfg   mywifiCfg;
extern volatile int g_AudioSetWifi;
extern int g_AUDIO_SET_WIFI_TIME;

volatile int g_AudioSetWifiOK = 0;

const char *recorderRecogErrorMsg(int _recogStatus)
{
	char *r = (char *)"unknow error";
	switch(_recogStatus)
	{
	case VR_ECCError:
		r = (char *)"ecc error";
		break;
	case VR_NotEnoughSignal:
		r = (char *)"not enough signal";
		break;
	case VR_NotHeaderOrTail:
		r = (char *)"signal no header or tail";
		break;
	case VR_RecogCountZero:
		r = (char *)"trial has expires, please try again";
		break;
	}
	return r;
}

//识别开始回调函数
void recorderRecognizerStart(void *_listener, float _soundTime)
{
	printf("------------------recognize start\n");
}

//识别结束回调函数
void recorderRecognizerEnd(void *_listener, float _soundTime, int _recogStatus, char *_data, int _dataLen)
{
	struct SSIDWiFiInfo wifi;
	struct WiFiInfo macWifi;
	int i;
	enum InfoType it;
	struct PhoneInfo phone;
	char s[100];
	if (_recogStatus == VR_SUCCESS)
	{		
		enum InfoType infoType = vr_decodeInfoType(_data, _dataLen);
		if(infoType == IT_PHONE)
		{
			vr_decodePhone(_recogStatus, _data, _dataLen, &phone);
			printf("imei:%s, phoneName:%s", phone.imei, phone.phoneName);
		}
		else if(infoType == IT_SSID_WIFI)
		{
			vr_decodeSSIDWiFi(_recogStatus, _data, _dataLen, &wifi);
			printf("ssid:%s, pwd:%s\n", wifi.ssid, wifi.pwd);

            //int iFlag = AudioSetWifi(wifi.ssid, wifi.pwd);
            //if( iFlag != -1 )
            //{
            //    printf("ssid:%s, pwd:%s..Success..\n", wifi.ssid, wifi.pwd);
            //}
            g_AudioSetWifiOK = AudioSetWifi(wifi.ssid, wifi.pwd);
            if (1 == g_AudioSetWifiOK)
            {
                g_AudioSetWifi = g_AUDIO_SET_WIFI_TIME; //exit voice recognize.
                printf("audio set wifi [ssid:%s, pwd:%s]...Success...\n", wifi.ssid, wifi.pwd);
                return;
            }
		}
		else if(infoType == IT_STRING)
		{
			vr_decodeString(_recogStatus, _data, _dataLen, s, sizeof(s));
			printf("string:%s\n", s);
		}
		else if(infoType == IT_WIFI)
		{
			vr_decodeWiFi(_recogStatus, _data, _dataLen, &macWifi);
			printf("mac wifi:");
			for (i = 0; i < macWifi.macLen; i ++)
			{
				printf("0x%.2x ", macWifi.mac[i] & 0xff);
			}
			printf(", %s\n", macWifi.pwd);
		}
		else
		{
			printf("------------------recognized data:%s\n", _data);
		}
	}
	else
	{
		printf("------------------recognize invalid data, errorCode:%d, error:%s\n", _recogStatus, recorderRecogErrorMsg(_recogStatus));
	}
}

void *runRecorderVoiceRecognize( void * _recognizer)  
{
    printf( "runRecorderVoiceRecognize start  \n" );
    vr_runRecognizer(_recognizer);
    printf( "runRecorderVoiceRecognize end  \n" );
}

static void *g_recognizer = NULL;
static short g_runLinster = 0;

void write_audioData( char *pAudioData, short nLen )
{
    if( g_runLinster == 0 ) 
        return;
    vr_writeData( g_recognizer, pAudioData, nLen );
    //recorderShortWrite123( pAudioData, nLen );
}

#if 0
#define SAVE_RECORDER_DATA 1
#ifdef SAVE_RECORDER_DATA
#include "util.h"
#define MAX_RECORDER_DATA_SIZE 1024 * 1024 * 1
char recorderData[MAX_RECORDER_DATA_SIZE];
int recorderDataPos = 0;
int fileNo = 0;
#endif

int recorderShortWrite123(const void *_data, unsigned long _sampleCout)
{
	char *data = (char *)_data;
	const int bytePerFrame = 1;

#ifdef SAVE_RECORDER_DATA
	if (((int)_sampleCout) * bytePerFrame < MAX_RECORDER_DATA_SIZE - recorderDataPos)
	{
		memcpy(recorderData + recorderDataPos, data, ((int)_sampleCout) * bytePerFrame);
		recorderDataPos += (((int)_sampleCout) * bytePerFrame);
	  //  printf("there is recorde data copy in..!");
    }
	else
	{
		char fileName[64];
		sprintf(fileName, "/mnt/mmc/recorder%d.wav", fileNo);
		fileNo ++;
		printf("%s %d saved\n", fileName, recorderDataPos);
		generateWave( fileName, recorderData, recorderDataPos, 8000 );
		recorderDataPos = 0;
	}
#endif
}
#endif


int run_recorderVoiceRecog();
int CreateVoiceRecogThread(void)
{
    pthread_t tfid;
    int ret = 0;

    ret = pthread_create(&tfid, NULL, (void *)run_recorderVoiceRecog, NULL);
    if (ret != 0)
    {
        //pthread_detach(tfid);
        printf("pthread_create VoiceRecog failed, %d, %s\n", errno, strerror(errno));
        return -1;
    }
    printf("...VoiceRecogThread End............\n");
    //pthread_detach(tfid);
    return 0;
}

int run_recorderVoiceRecog()
{
	int sampleRate = 44100;
	g_recognizer = vr_createVoiceRecognizer2(MemoryUsePriority, sampleRate);

    int freqs[] = {4000,4200,4600,4800,5000,5200,5400,5600,5800,6000,6200,6400,6600,6800,7000,7200,7400,7600,7800};

    vr_setRecognizeFreqs(g_recognizer, freqs, sizeof(freqs)/sizeof(int));
    vr_setRecognizerListener(g_recognizer, NULL, recorderRecognizerStart, recorderRecognizerEnd);
    //int freqs[] = {5600,5800,6000,6200,6400,6600,6800,7000,7200,7400,7600,7800,8000,8200,8400,8600,8800,9000,9200};	
    //int freqs[] = {6500,6700,6900,7100,7300,7500,7700,7900,8100,8300,8500,8700,8900,9100,9300,9500,9700,9900,10100};
    //int freqs[] = {1600,1800,2000,2200,2400,2600,2800,3000,3200,3400,3600,3800,4000,4200,4400,4600,4800,5000,5200};
    int freqs2[] = {15000,15200,15400,15600,15800,16000,16200,16400,16600,16800,17000,17200,17400,17600,17800,18000,18200,18400,18600};

    vr_setRecognizeFreqs2(g_recognizer, freqs2, sizeof(freqs2)/sizeof(int));
    vr_setRecognizerFreq2Listener(g_recognizer, NULL, recorderRecognizerStart, recorderRecognizerEnd);
	
	pthread_t ntid;
	pthread_create(&ntid, NULL, runRecorderVoiceRecognize, g_recognizer);
	
	printf("recognize start !!!\n");
    g_runLinster = 1; 
	do
    {
        sleep(1);
        if ((g_AudioSetWifi == g_AUDIO_SET_WIFI_TIME) || (1 == g_AudioSetWifiOK))
        {
            break;
        }
    } 
	while (1);

	vr_stopRecognize( g_recognizer );
	do 
	{		
    #ifdef WIN32
		Sleep(1000);
    #else
		sleep(1);
    #endif
	} while (!vr_isRecognizerStopped(g_recognizer));

	vr_destroyVoiceRecognizer(g_recognizer);
    printf("END recognizer is quiting\n");

    if (1 == g_AudioSetWifiOK)
    {
        printf("=====> voice set wifi ok, system restart now <=====\n");
    #if DEV_ROBOT
        UART_CtrlCmd_Send(CMD_SET_WIFI, 0);
        sleep(3);
    #else
        HK_Audio_Notify( NOTIFY_WIFISET ); //voice notify.
    #endif
        printf("von re..\n");
        wrap_sys_restart();
    }

    pthread_detach(pthread_self());
    return 1;
}

