
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <errno.h>

#include "gpiodriver.h"

#define SAR_DEVICE_NAME "/dev/sar_adc"

int SarAdc_PowerDown()
{
#if (DEV_CHEANGDU )
    unsigned int groupnum = 5;
    unsigned int bitnum   = 7;

    g_sdIsOnline=0;
    be_present(0);
    sd_record_stop();
    usleep(2000);
#else
    unsigned int groupnum = 0;
    unsigned int bitnum   = 5;
#endif
    unsigned int val_set   = 0;
    Hi_SetGpio_SetDir( groupnum, bitnum, GPIO_WRITE );
    Hi_SetGpio_SetBit( groupnum, bitnum, val_set ); //pull down.
    printf("...%s, %d...Set GPIO %d_%d  set Value: %d....\n\n", __func__, __LINE__, groupnum, bitnum, val_set);
}

#if 0
float AdcGetValueAverage(int CH)
{
    int Adc_Ch = -1;
    int Adc_Value = -1;
    int Ret=-1;
    float x - 0, t = 0;
    int s[10] = {0};
    int y = 0, i = 0, j = 0;

    for (i = 0; i < 10; i++)
    {
        switch(CH)
        {
            case 1:
                {	
                    //GpioADCIR1();
                    Adc_Ch = 1;
                }
                break;

            case 2:
                {	
                    //GpioADCIR2();
                    Adc_Ch = 1;
                }
                break;

            case 3:
                {	
                    //GpioADCIR3();
                    Adc_Ch = 0;
                }
                break;

            case 4:
                {	
                    //GpioADCBattery();
                    Adc_Ch = 0;
                }
                break;
            default:
                {
                    printf("switch(SAdc.State.Process)");
                    Adc_Ch = -1;
                }	
                break;
        }

        if (-1 != Adc_Ch)
        {	
            ioctl(fd, SET_CH, &Adc_Ch); 

            Ret = poll(fds, 1, 1500);
            if (Ret == 0)
            {
                printf("...time out !\n");
            }
            else
            {
                read(fd, &Adc_Value, sizeof(Adc_Value));	
                //printf("CH:%d Adc_Value:%f", CH, Adc_Value*0.003);
                s[i] = Adc_Value;
            }
        }
    }

    for (i = 0; i < 9; i++)
    {	
        for (j = 0; j < 9 - i; j++)	
        {		
            if (s[j] < s[j+1]) 	
            {			
                t = s[j]; 	
                s[j] = s[j+1];		
                s[j+1] = t;		
            }	
        }	
    }

    for(x = 0, y = 1; y < 9; y++)
    {	 
        x = x + s[y];
    }

    x = x / 8;
    printf("CH: %d Adc_AverageValue:%f", CH, x*0.003);

    return x;
}
#endif

#if 0
float AdcGetValueAverage(int fd, int CH)
{
    int Adc_Ch = -1;
    int Adc_Value = -1;
    float x = 0, t = 0;
    int s[10] = {0};
    int y = 0, i = 0, j = 0;

    for (i = 0; i < 10; i++)
    {
        read(fd, &Adc_Value, sizeof(Adc_Value));	
        //printf("CH:%d Adc_Value:%f", CH, Adc_Value*0.003);
        s[i] = Adc_Value;
    }

    for (i = 0; i < 9; i++)
    {	
        for (j = 0; j < 9 - i; j++)	
        {		
            if (s[j] < s[j+1]) 	
            {			
                t = s[j]; 	
                s[j] = s[j+1];		
                s[j+1] = t;		
            }	
        }	
    }

    for(x = 0, y = 1; y < 9; y++)
    {	 
        x = x + s[y];
    }

    x = x / 8;
    printf("CH: %d Adc_AverageValue:%f", CH, x*0.003);

    return x;
}
#endif


/***********************************************************
 * func: receive infrared remoter signal, and decode it.
 ***********************************************************/
#if 1
void *Handle_Sar_Adc_Result(void* arg)
{
    //printf("SAR ADC thread start !\n");

    int i = 0, j = 0, count = 10;
    int sarFd = 0; 
    int adc_result = 0;
    float ADC_Val = 0, ADC_CapacityVal = 0;

    if (-1 == (sarFd = open(SAR_DEVICE_NAME, O_RDWR, 0)))
    {
        //printf("open %s error: %d, %s\n", SAR_DEVICE_NAME, errno, strerror(errno));
        return;
    }

    while (1)
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < count; j++)
            {
                read(sarFd, &adc_result, 1);
                //printf("adc_result: %d..........\n", adc_result);
                if (adc_result > 30) 
                    adc_result = 30;

                ADC_Val += adc_result;
                usleep(500);
            }

            //printf("adc_result: %d.......222...\n", adc_result);

            ADC_Val = ADC_Val / count;
            ADC_CapacityVal += (ADC_Val * 0.0032 * 100 * 0.917); //accuracy: (3.3V / 1023).
            ADC_Val = 0;
            usleep(500);
        }
        ADC_CapacityVal = ADC_CapacityVal / 3;
        printf("[%s] ...ADC_Val: %f, ADC_CapacityVal: %f\n", __func__, ADC_Val, ADC_CapacityVal);

        if (ADC_CapacityVal <= 3.6) //capacity is lower than 3.3V, system is going down.
        {
            printf("[%s, %d] Note: The battery is low power, device power down !!!\n", __func__, __LINE__);
            SarAdc_PowerDown();
        }

        ADC_Val = 0;
        ADC_CapacityVal = 0;
        usleep(1000*100);
    }
    close(sarFd);
    return 0;
}
#endif
#if 0
void *Handle_Sar_Adc_Result(void* arg)
{
    printf("SAR ADC thread start !\n");

    int i = 0, j = 0, count = 10;
    int sarFd = 0; 
    int adc_result = 0;
    float ADC_AverageVal = 0, ADC_CapacityVal = 0;

    if (-1 == (sarFd = open(SAR_DEVICE_NAME, O_RDWR, 0)))
    {
        printf("open %s error: %d, %s\n", SAR_DEVICE_NAME, errno, strerror(errno));
        return;
    }

    while (1)
    {
        ADC_CapacityVal = AdcGetValueAverage(sarFd, 1);
        printf("[%s, %d] ...ADC_CapacityVal： %f\n", __func__, __LINE__, ADC_CapacityVal);
        usleep(1000*200);
    }
    close(sarFd);
    return 0;
}
#endif

int HK_SAR_ADC(void)
{
    int ret = 0;
    pthread_t adc_event;
    void *thread_result;

    system("insmod /mnt/sif/bin/sar_adc.ko");

    /** check battery capacity **/
    ret = pthread_create(&adc_event, NULL, (void *)Handle_Sar_Adc_Result, NULL);
    if (0 != ret)
    {
        printf("pthread_create failed with:%d, %s\n", errno, strerror(errno));
        pthread_detach(adc_event);
        return -1;
    }
    pthread_detach(adc_event);

    return 0;
}

