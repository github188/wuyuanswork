#if 1
#include<stdio.h>
#include<stdlib.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

#include "IPCAM_Export.h"

#ifdef __cplusplus
};
#endif

extern int IsValidVideoSrcToken(CHAR *pToken);

BOOL ImgGetOptions(CHAR *VideoSourceToken, LPOPTIONSIMAGINGS lpOptionsImagings)
{
#if 0
	LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();

	if (NULL == VideoSourceToken || NULL == lpOptionsImagings)
	{
		return FALSE;
	}
#endif
	//if (IsValidVideoSrcToken(VideoSourceToken) < 0)
	//{
	//    return FALSE;
	//}

	lpOptionsImagings->ImgBrightnessRange.Max      = 255 ;

	lpOptionsImagings->ImgBrightnessRange.Min      = 0;

	lpOptionsImagings->ImgColorSaturationRange.Max = 255;

	lpOptionsImagings->ImgColorSaturationRange.Min = 0;

	lpOptionsImagings->ImgContrastRange.Max        = 255;

	lpOptionsImagings->ImgContrastRange.Min        = 0;

	lpOptionsImagings->ImgSharpness.Max            = 255;
	lpOptionsImagings->ImgSharpness.Min            = 0;

	lpOptionsImagings->BacklightCompMode[0]        = MODE_BACKLIGTHCOMP_ON;
	lpOptionsImagings->BacklightCompRange.Max      = 100;
	lpOptionsImagings->BacklightCompRange.Min      = 0;

	lpOptionsImagings->OptionsExposure.ExpoMaxGain.Max = 100;
	lpOptionsImagings->OptionsExposure.ExpoMaxGain.Min = 100;
	lpOptionsImagings->OptionsExposure.ExpoMinGain.Max = 0;
	lpOptionsImagings->OptionsExposure.ExpoMinGain.Min = 0;
	lpOptionsImagings->OptionsExposure.ExpoModes[0]       = MODE_EXPOSURE_AUTO;
	lpOptionsImagings->OptionsExposure.ExpoIris.Max    = 100;
	lpOptionsImagings->OptionsExposure.ExpoIris.Min    = 0;
	lpOptionsImagings->OptionsExposure.ExpoMaxIris.Max = 100;
	lpOptionsImagings->OptionsExposure.ExpoMaxIris.Min = 0;
	lpOptionsImagings->OptionsExposure.ExpoGain.Max    = 100;
	lpOptionsImagings->OptionsExposure.ExpoGain.Min    = 0;
	lpOptionsImagings->OptionsExposure.ExpoMaxTime.Max = 100;
	lpOptionsImagings->OptionsExposure.ExpoMaxTime.Min = 0;
	lpOptionsImagings->OptionsExposure.ExpoTime.Max    = 100;

	lpOptionsImagings->OptionsWhiteBalance.wbModes[0]   = WHITEBALANCE_MODE_AUTO;
	lpOptionsImagings->OptionsWhiteBalance.wbModeSize = sizeof(OPTIONSWIDEDYNAMIC);
	lpOptionsImagings->OptionsWhiteBalance.wbYbGain.Max   = 100;
	lpOptionsImagings->OptionsWhiteBalance.wbYbGain.Min   = 0;
	lpOptionsImagings->OptionsWhiteBalance.wbYrGain.Max   = 100;
	lpOptionsImagings->OptionsWhiteBalance.wbYrGain.Min   = 0;
	lpOptionsImagings->OptionsWideDynamic.wdLevel.Max     = 100;
	lpOptionsImagings->OptionsWideDynamic.wdLevel.Min     = 0;
	lpOptionsImagings->IrCutModeSize       = 2;
	lpOptionsImagings->IrCutFilterModes[0] = IRCUT_MODE_AUTO;
	lpOptionsImagings->IrCutFilterModes[1] = IRCUT_MODE_AUTO;

	return TRUE;
}

BOOL ImgGetSetting(CHAR *VideoSourceToken, LPOPTIONSIMAGINGS lpImgSetting)
{
	int nBright;
	int nSaturation;
	int nContrast;
	int nSharpness;
	if (NULL == VideoSourceToken || NULL == lpImgSetting)
	{
		return FALSE;
	}
	//if (IsValidVideoSrcToken(VideoSourceToken) < 0)
	//{
	//    return FALSE;
	//}

	//LPIPCAM_SYSCONTEXT SysContext=IPCAM_GetSystemContext();
	
	nBright = conf_get_int("/mnt/sif/hkipc.conf", "BrightnessLevel");		
	nSaturation = conf_get_int("/mnt/sif/hkipc.conf", "CamSaturationLevel");	
	nContrast = conf_get_int("/mnt/sif/hkipc.conf", "CamContrastLevel");	
	//nSharpness = conf_get_int("/mnt/sif/hkipc.conf", "SharpnessLevel");	
	
	lpImgSetting->ImgBrightnessRange.Max      = nBright*256/64;//SysContext->ipcam_SysConfig->ConfigVideo.bzBright;
	lpImgSetting->ImgColorSaturationRange.Max = nSaturation*256/64;//SysContext->ipcam_SysConfig->ConfigVideo.bzSaturation;
	lpImgSetting->ImgContrastRange.Max        = nContrast*256/64;//SysContext->ipcam_SysConfig->ConfigVideo.bzContrast;
	//lpImgSetting->ImgSharpness.Max        =  nSharpness;//SysContext->ipcam_SysConfig->ConfigVideo.bzSharpness;

#if 0//wss
	if(3==SysContext->ipcam_SysConfig->ConfigVideo.VideoIrCut.nMode)
	{
		lpImgSetting->IrCutFilterModes[0] = 2;
	}

	if(1==SysContext->ipcam_SysConfig->ConfigVideo.VideoIrCut.nMode)
	{
		lpImgSetting->IrCutFilterModes[0] = 0;
	}

	if(2==SysContext->ipcam_SysConfig->ConfigVideo.VideoIrCut.nMode)
	{
		lpImgSetting->IrCutFilterModes[0] = 1;
	}
#else
	lpImgSetting->IrCutFilterModes[0] = 2;
#endif
	
	return TRUE;
}

void SetIcut( int mode)
{
#if 0
	LPIPCAM_SYSCONTEXT pContex=IPCAM_GetSystemContext();
	if( 2 == mode)
	{
		pContex->ipcam_SysConfig->ConfigVideo.VideoIrCut.nMode =3;
		// printf("===============================aoto==========================\n"); 
	}					
	////白天模式
	if( 0 == mode)
	{
		//  printf("===============================baitian==========================\n");
		pContex->ipcam_SysConfig->ConfigVideo.VideoIrCut.nMode =1;
	}
	////黑夜模式
	if( 1 == mode)
	{
		//  printf("===============================wanshang==========================\n");
		pContex->ipcam_SysConfig->ConfigVideo.VideoIrCut.nMode =2;
	}
#endif
}

BOOL ImgSetSetting(CHAR *VideoSourceToken, LPOPTIONSIMAGINGS lpImgSetting, BOOL isFoce2Persistence)
{
	int nSaturation = 0;
	 int nBrightness = 0;
	 int nContrast = 0;
	 
	if (NULL == VideoSourceToken || NULL == lpImgSetting)
	{
	    return FALSE;
	}
	
	//if (IsValidVideoSrcToken(VideoSourceToken) < 0)
	//{
	//    return FALSE;
	//}

	if (NULL == VideoSourceToken || NULL == lpImgSetting)
	{
	    return FALSE;
	}

	if(0 == lpImgSetting->ImgBrightnessRange.Max && 0 == lpImgSetting->ImgContrastRange.Max && 0 == lpImgSetting->ImgColorSaturationRange.Max)
	{
	#if 0
		IPCAM_VISetVideoParam(128, 128, 128,128);
	#endif	
		HISI_SetCSCAttr(nSaturation,nBrightness,nContrast,0);
	}

	nBrightness = (unsigned char)(lpImgSetting->ImgBrightnessRange.Max*64/256);
	
	nSaturation = (unsigned char)(lpImgSetting->ImgColorSaturationRange.Max*64/256);
	
	nContrast = (unsigned char)(lpImgSetting->ImgContrastRange.Max*64/256);
	printf("[ImgSetSetting] ImgBrightnessRange=%d====ImgContrastRange=%d=====ImgColorSaturationRange=%d\n",(unsigned char)lpImgSetting->ImgBrightnessRange.Max, (unsigned char)lpImgSetting->ImgContrastRange.Max, (unsigned char)lpImgSetting->ImgColorSaturationRange.Max);
#if 0
	IPCAM_VISetVideoParam((unsigned char)lpImgSetting->ImgBrightnessRange.Max, (unsigned char)lpImgSetting->ImgContrastRange.Max, (unsigned char)lpImgSetting->ImgColorSaturationRange.Max,128);
#endif	
	HISI_SetCSCAttr(nSaturation,nBrightness,nContrast,0);
	conf_set_int("/mnt/sif/hkipc.conf", "BrightnessLevel",nBrightness);		
	conf_set_int("/mnt/sif/hkipc.conf", "CamSaturationLevel",nSaturation);	
	conf_set_int("/mnt/sif/hkipc.conf", "CamContrastLevel",nContrast);	
	//IPCAM_VISetBackLightLevel(lpImgSetting->BacklightCompMode[0]);	
	
	//lpImgSetting->BacklightCompRange.Max = 100;
	//lpImgSetting->BacklightCompRange.Min = 0;
	//lpImgSetting->BacklightCompSize      = 1;
	
	return TRUE;
}

CALLBACKIMAGING     g_CallBackImaging = {0};

VOID InitCallBackImaging()
{                                 
	g_CallBackImaging.SetIcut = SetIcut;
	g_CallBackImaging.ImgGetOptions = ImgGetOptions;
	g_CallBackImaging.ImgGetSetting = ImgGetSetting;
	g_CallBackImaging.ImgSetSetting = ImgSetSetting;
}

#endif
