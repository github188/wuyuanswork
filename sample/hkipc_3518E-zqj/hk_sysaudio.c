
#include "hk_sysaudio.h"
#include "gpiodriver.h"

extern HI_S32 SAMPLE_Audio_AdecAo();
extern HI_S32 SAMPLE_Audio_AiAenc(int iSamplerate);

int HK_AudioOut_Enable(void)
{
    unsigned int groupnum = 5;
    unsigned int bitnum = 0; //GPIO:5_0 (audio out).
    unsigned int val_set = 1; //pull up.

    Hi_SetGpio_SetDir( groupnum, bitnum, GPIO_WRITE );
    Hi_SetGpio_SetBit( groupnum, bitnum, val_set );
    printf("....Set GPIO %d_%d  set Value: %d....\n", groupnum, bitnum, val_set);

    return 0;
}


int StartPcmAdec(int nNotifyType)
{
	HI_S32 s32Ret = 0;
	AUDIO_STREAM_S stAudioStream;    
	HI_U32 u32Len = 640;
	HI_U32 u32ReadLen;
	HI_S32 s32AdecChn = 0;
	HI_U8 *pu8AudioStream = NULL;

	/***close client audio talk***/
	LPCM_Audio_Close();
	/***open pcm Adec***/
	//LPCM_Audio_AdecAo();
	LPCM_Audio_Open();
	
    struct stat buf;
    unsigned int sFileSize = 0;
	char FilePathName[128] = {0};
    Get_RingFilePath(nNotifyType, FilePathName);
    printf("[%s, %d] nNotifyType:%d, FilePathName:%s\n", __func__, __LINE__, nNotifyType, FilePathName);

	FILE *pfd = fopen(FilePathName, "rb");
	if (NULL == pfd)
	{
		printf("%s: fopen file %s failed, %d, %s\n", __FUNCTION__, FilePathName, errno, strerror(errno));
		return -1;
	}

    s32Ret = stat(FilePathName, &buf);
    if (s32Ret < 0)
    {
        printf("...%s...error, stat failed with: %d, %s\n", __func__, errno, strerror(errno)); 
        return -1;
    }
    sFileSize = buf.st_size;
    //printf("===> file: %s, filesize: %d\n", FilePathName, sFileSize);

	pu8AudioStream = (HI_U8*)malloc(sizeof(HI_U8)*MAX_AUDIO_STREAM_LEN);
	if (NULL == pu8AudioStream)
	{
		printf("%s: malloc failed!\n", __FUNCTION__);
		//return NULL;
		return -1;
	}

	while(1)
	{
		/* read from file */
		stAudioStream.pStream = pu8AudioStream;
		u32ReadLen = fread(stAudioStream.pStream, 1, u32Len, pfd);
		if (u32ReadLen <= 0)
		{			
			fseek(pfd, 0, SEEK_SET);/*read file again*/
			//continue;
            break;
		}

		/* here only demo adec streaming sending mode, but pack sending mode is commended */
		stAudioStream.u32Len = u32ReadLen;
		s32Ret = HI_MPI_ADEC_SendStream(s32AdecChn, &stAudioStream, HI_TRUE);
		if (s32Ret)
		{
			printf("%s: HI_MPI_ADEC_SendStream(%d) failed with %#x!\n", __FUNCTION__, s32AdecChn, s32Ret);
			break;
		}

        sFileSize -= u32ReadLen;
        //printf("===> file: %s, filesize: %d\n", FilePathName, sFileSize);
		if (sFileSize <= 0)
        {
            printf("!!! notify audio end !!!\n");
			break;
        }
		
		usleep(10*1000);
	}
	
	free(pu8AudioStream);
	pu8AudioStream = NULL;
	fclose(pfd);
	LPCM_Audio_Close();
	//IPCAM_PTHREAD_EXIT;
    //sleep(1);
	return 0;
}


int HK_Audio_Notify(int nNotifyType)
{
    //HK_AudioOut_Enable();
	StartPcmAdec( nNotifyType ); 
	
	IPCAM_DEBUG("=========>Audio Notify End<=========\n");
	usleep(1*1000);  
	return 0;
}

