
#ifndef __HK_SYSAUDIO_H__
#define __HK_SYSAUDIO_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

#include "IPCAM_Export.h"
#include "sample_comm.h"
#include "acodec.h"

#define PATH_SYSAUDIO "/mnt/sif/SysAudio"

/**system audio notify type**/
typedef enum sys_notify_type_t
{
    NOTIFY_DISABLE  = 0, //close audio notify.
    NOTIFY_POWERON  = 1, //device system start.
    NOTIFY_POWEROFF = 2, //device system shutdown.
    NOTIFY_SYSREST  = 3, //system reset to factory settings.
    NOTIFY_WIFISET  = 4, //client set wifi connection.
    NOTIFY_RINGIN   = 5, //phone call in.
    NOTIFY_RINGOUT  = 6, //phone call out.
    NOTIFY_EXT      = 7  //extension.
} ENUM_NOTIFY_TYPE;


inline static int Get_RingFilePath(int nType, char *pPath)
{
    switch (nType)
    {
        case 1: //system start.
            strcpy(pPath, PATH_SYSAUDIO"/PowerOn.pcm");
            break;
        case 2: //system shutdown.
        case 3: //reset.
            strcpy(pPath, PATH_SYSAUDIO"/PowerOff.pcm");
            break;
        case 4: //set wifi.
            strcpy(pPath, PATH_SYSAUDIO"/WifiSetting.pcm");
            break;
        case 5: //phone call in.
            strcpy(pPath, PATH_SYSAUDIO"/RingIn.pcm");
            break;
        case 6: //phone call out.
            strcpy(pPath, PATH_SYSAUDIO"/RingOut.pcm");
            break;
        case 0:
        default:
            break;
    }
    //printf("...%s...nType: %d, pPath: %s...\n", __func__, nType, pPath);

    return 0;
}

#endif  /**hk_sysaudio.h**/

