#if 1
#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "IPCAM_Export.h"

#ifdef __cplusplus
};
#endif

#define AUDIOENCODECONFIGTOKEN0 "AudioEncodeConfigToken0"
#define AUDIOSOURCECONFIGTOKEN0 "AudioSourceConfigToken0"
#define PTZCONFIGTOKEN0         "PtzConfigToken0"
#define PTZNODETOKEN0           "onvif_ptz_0"
#define TOKEN0                  "token0"
#define MEDIAPROFILNAME0        "mediaprofilename0"
#define VIDEOENCODECONFIGTOKEN0 "VideoEncConfigToken0"
#define VIDEOSOURCECONFIGTOKEN0 "VideoSourceConfigToken0"
#define RELAYOUTPUT0			"RelayOutputs0"

#define AUDIOENCODECONFIGTOKEN1 "AudioEncodeConfigToken1"
#define AUDIOSOURCECONFIGTOKEN1 "AudioSourceConfigToken1"
#define PTZCONFIGTOKEN1         "PtzConfigToken1"
#define PTZNODETOKEN1           "onvif_ptz_1"
#define TOKEN1                  "token1"
#define MEDIAPROFILNAME1        "mediaprofilename1"
#define VIDEOENCODECONFIGTOKEN1 "VideoEncodeConfigToken1"
#define VIDEOSOURCECONFIGTOKEN1 "VideoSourceConfigToken1"
#define RELAYOUTPUT1			"RelayOutputs1"


#define AUDIOCONFGNAME0     "audioConfigName0"
#define AUDIOCONFIGTOKEN0   "audioConfigToken0"
#define AUDIOENCCONFIGTOKEN "AudioEncConfigToken"
#define AUDIOENCCONFIGNAME  "AudioEncConfigName"
#define AUDIONODETOKEN0     "audionodetoken0"

typedef enum
{
    Token = 0,
    Audio_Encode_Token,
    Audio_Src_Token,
    PTZ_Config_Token,
    Video_Encode_Token,
    Video_Src_Token,
	PTZ_Node_Token,
	Device_RelayO_Token,
    Token_End
} TOKENTPYE;

const char *tokentable[2][Token_End] =
{
    {
        TOKEN0,
        AUDIOENCODECONFIGTOKEN0,
        AUDIOSOURCECONFIGTOKEN0,
        PTZCONFIGTOKEN0,
        VIDEOENCODECONFIGTOKEN0,
        VIDEOSOURCECONFIGTOKEN0,
		PTZNODETOKEN0,
		RELAYOUTPUT0

    },
    {
        TOKEN1,
        AUDIOENCODECONFIGTOKEN1,
        AUDIOSOURCECONFIGTOKEN1,
        PTZCONFIGTOKEN1,
        VIDEOENCODECONFIGTOKEN1,
        VIDEOSOURCECONFIGTOKEN1,
		PTZNODETOKEN1,
		RELAYOUTPUT0
    }
};

int IsValidToken(CHAR *token, int tokentype)
{
    if (token == NULL || tokentype >= Token_End || tokentype < Token)
    {
        return -1;
    }
    if (strcmp(token, tokentable[0][tokentype]) == 0)
    {
        return 0;
    }
    else if (strcmp(token, tokentable[1][tokentype]) == 0)
    {
        return 1;
    }
    return -1;
}

int IsValidVideoSrcToken(CHAR *token)
{
    return IsValidToken(token, Video_Src_Token);
}
int AudioEnCtypeIPCtoOVFmap(int EncType)
{
	if(10 == EncType)return 0;
	if(12 == EncType)return 2;
}
int AudioEnCtypeOVFtoIPCmap(int EncType)
{
	if(0 == EncType)return 10;
	if(2 == EncType)return 12;
}
BOOL GetProfileCap(LPMEDIAPROFILECAP lpMediaProfileCap)
{
	 // printf("=============================GetProfileCap+++ start==========================================");
    lpMediaProfileCap->MaxProfiles              = 2;
    lpMediaProfileCap->RTPMulticast             = TRUE;
    lpMediaProfileCap->RTP_USCORETCP            = TRUE;
    lpMediaProfileCap->RTP_USCORERTSP_USCORETCP = TRUE;
    lpMediaProfileCap->NonAggregateControl      = TRUE;

    return TRUE;
}

BOOL GetProfiles(LPMEDIAPROFILES lpMediaProfiles)
{ 
	   
	 //  printf("=============================GetProfiles++++==================================");
	
    lpMediaProfiles->ProfileSize = 2;
    lpMediaProfiles->ProFiles[0].fixed = FALSE;
    strncpy(lpMediaProfiles->ProFiles[0].token                 , TOKEN0                 , strlen(TOKEN0));
    strncpy(lpMediaProfiles->ProFiles[0].Name                  , MEDIAPROFILNAME0       , strlen(MEDIAPROFILNAME0));
	strncpy(lpMediaProfiles->ProFiles[0].AudioEncodeConfigToken, AUDIOENCODECONFIGTOKEN0, strlen(AUDIOENCODECONFIGTOKEN0));
	strncpy(lpMediaProfiles->ProFiles[0].AudioSourceConfigToken, AUDIOSOURCECONFIGTOKEN0, strlen(AUDIOSOURCECONFIGTOKEN0));
	strncpy(lpMediaProfiles->ProFiles[0].PtzConfigToken        , PTZCONFIGTOKEN0        , strlen(PTZCONFIGTOKEN0));
	strncpy(lpMediaProfiles->ProFiles[0].VideoEncodeConfigToken, VIDEOENCODECONFIGTOKEN0, strlen(VIDEOENCODECONFIGTOKEN0));
	strncpy(lpMediaProfiles->ProFiles[0].VideoSourceConfigToken, VIDEOSOURCECONFIGTOKEN0, strlen(VIDEOSOURCECONFIGTOKEN0));

	lpMediaProfiles->ProFiles[1].fixed = FALSE;
    strncpy(lpMediaProfiles->ProFiles[1].token                 , TOKEN1                 , strlen(TOKEN1));
    strncpy(lpMediaProfiles->ProFiles[1].Name                  , MEDIAPROFILNAME1       , strlen(MEDIAPROFILNAME1));
	strncpy(lpMediaProfiles->ProFiles[1].AudioEncodeConfigToken, AUDIOENCODECONFIGTOKEN1, strlen(AUDIOENCODECONFIGTOKEN1));
	strncpy(lpMediaProfiles->ProFiles[1].AudioSourceConfigToken, AUDIOSOURCECONFIGTOKEN1, strlen(AUDIOSOURCECONFIGTOKEN1));
	strncpy(lpMediaProfiles->ProFiles[1].PtzConfigToken        , PTZCONFIGTOKEN1        , strlen(PTZCONFIGTOKEN1));
	strncpy(lpMediaProfiles->ProFiles[1].VideoEncodeConfigToken, VIDEOENCODECONFIGTOKEN1, strlen(VIDEOENCODECONFIGTOKEN1));
	strncpy(lpMediaProfiles->ProFiles[1].VideoSourceConfigToken, VIDEOSOURCECONFIGTOKEN1, strlen(VIDEOSOURCECONFIGTOKEN1));

	

    return TRUE;
}

BOOL GetProfile(CHAR *MediaProfileToken,LPMEDIAPROFILE lpMediaProfile)
{
	if(!strcmp(MediaProfileToken,TOKEN0)){
		lpMediaProfile->fixed = FALSE;
		strncpy(lpMediaProfile->token , MediaProfileToken,OVFCHARLENTH);
		strncpy(lpMediaProfile->Name,MEDIAPROFILNAME0 , strlen(MEDIAPROFILNAME0));
		strncpy(lpMediaProfile->AudioEncodeConfigToken, AUDIOENCODECONFIGTOKEN0, strlen(AUDIOENCODECONFIGTOKEN0));
		strncpy(lpMediaProfile->AudioSourceConfigToken, AUDIOSOURCECONFIGTOKEN0, strlen(AUDIOSOURCECONFIGTOKEN0));
		strncpy(lpMediaProfile->PtzConfigToken        , PTZCONFIGTOKEN0        , strlen(PTZCONFIGTOKEN0));
		strncpy(lpMediaProfile->VideoEncodeConfigToken, VIDEOENCODECONFIGTOKEN0, strlen(VIDEOENCODECONFIGTOKEN0));
		strncpy(lpMediaProfile->VideoSourceConfigToken, VIDEOSOURCECONFIGTOKEN0, strlen(VIDEOSOURCECONFIGTOKEN0));
	}else if(!strcmp(MediaProfileToken,TOKEN1)){
		lpMediaProfile->fixed  = FALSE;
		strncpy(lpMediaProfile->token                  , TOKEN1                 , strlen(TOKEN1));
		strncpy(lpMediaProfile->Name                   , MEDIAPROFILNAME1       , strlen(MEDIAPROFILNAME1));
		strncpy(lpMediaProfile->AudioEncodeConfigToken , AUDIOENCODECONFIGTOKEN1, strlen(AUDIOENCODECONFIGTOKEN1));
		strncpy(lpMediaProfile->AudioSourceConfigToken , AUDIOSOURCECONFIGTOKEN1, strlen(AUDIOSOURCECONFIGTOKEN1));
		strncpy(lpMediaProfile->PtzConfigToken         , PTZCONFIGTOKEN1        , strlen(PTZCONFIGTOKEN1));
		strncpy(lpMediaProfile->VideoEncodeConfigToken , VIDEOENCODECONFIGTOKEN1, strlen(VIDEOENCODECONFIGTOKEN1));
		strncpy(lpMediaProfile->VideoSourceConfigToken , VIDEOSOURCECONFIGTOKEN1, strlen(VIDEOSOURCECONFIGTOKEN1));

	}
	else
		 return FALSE;
    return TRUE;
}
BOOL GetAudioSources(LPAUDIONODES   lpAudioSources)
{   
	if (lpAudioSources == NULL)
    {
        return FALSE;
    }
    lpAudioSources->AudioNodeSize = 1;
    strncpy(lpAudioSources->AudioNodes[0].AudioToken,AUDIOSOURCECONFIGTOKEN0, strlen(AUDIOSOURCECONFIGTOKEN0));
    lpAudioSources->AudioNodes[0].Channels = 1;
    return TRUE;
}

BOOL GetAudioSourceConfigs(LPAUDIOCONFIGS lpAudioSourceConfigs)
{
    if (lpAudioSourceConfigs == NULL)
    {
        return FALSE;
    }
    lpAudioSourceConfigs->ConfigSize = 1;
    strncpy(lpAudioSourceConfigs->Configs[0].ConfigToken, AUDIOSOURCECONFIGTOKEN0, strlen(AUDIOSOURCECONFIGTOKEN0));
    strncpy(lpAudioSourceConfigs->Configs[0].AudioNodeToken, AUDIOSOURCECONFIGTOKEN0,   strlen(AUDIOSOURCECONFIGTOKEN0));
    strncpy(lpAudioSourceConfigs->Configs[0].ConfigName,     AUDIOSOURCECONFIGTOKEN0,   strlen(AUDIOSOURCECONFIGTOKEN0));

    lpAudioSourceConfigs->Configs[0].ConfigUseCount   = 2;
    lpAudioSourceConfigs->Configs[0].ForcePersistence = 1;
    lpAudioSourceConfigs->Configs[0].AudioOutputLevel = 50;
    return TRUE;
}

BOOL GetAudioSourceConfigOptions(CHAR *ConfigAudioSourceToken, CHAR *MediaProfileToken, LPAUDIOCONFIGOPTIONS lpAudioSourceConfigOptions)
{
    int ret = 0;
	if (NULL != ConfigAudioSourceToken)
	{
		ret = IsValidToken(ConfigAudioSourceToken, Audio_Src_Token);
		if (ret < 0)
		{
			return FALSE;
		}
	}
	if (NULL != MediaProfileToken)
	{
		ret = IsValidToken(MediaProfileToken,Token);
		if (ret < 0)
		{
			return FALSE;
		}
	}   
	strncpy(lpAudioSourceConfigOptions->AudioNodeTokensAvailable[0],AUDIOSOURCECONFIGTOKEN0,OVFCHARLENTH);
	lpAudioSourceConfigOptions->AudioNodeTokensAvailableSize =1;	
	
    return TRUE;
}

BOOL GetAudioSourceConfig(CHAR *ConfigAudioSourceToken, LPAUDIOCONFIG lpAudioSourceConfig)
{
    int ret = 0;
    if (ConfigAudioSourceToken == NULL || lpAudioSourceConfig == NULL)
    {
        return FALSE;
    }
    ret = IsValidToken(ConfigAudioSourceToken, Audio_Src_Token);
    if (ret < 0)
    {
        return FALSE;
    }
	strncpy(lpAudioSourceConfig->ConfigToken, AUDIOSOURCECONFIGTOKEN0, strlen(AUDIOSOURCECONFIGTOKEN0));
    strncpy(lpAudioSourceConfig->AudioNodeToken, AUDIOSOURCECONFIGTOKEN0,  OVFCHARLENTH);
    strncpy(lpAudioSourceConfig->ConfigName,     AUDIOSOURCECONFIGTOKEN0,   strlen(AUDIOSOURCECONFIGTOKEN0));
    lpAudioSourceConfig->ConfigUseCount   = 2;
    lpAudioSourceConfig->ForcePersistence = 1;
    lpAudioSourceConfig->AudioOutputLevel = 50;
    return TRUE;
}

BOOL SetAudioSourceConfig(CHAR *ConfigAudioSourceToken, LPAUDIOCONFIG lpAudioSourceConfig)
{
    int ret = 0;
    if (ConfigAudioSourceToken == NULL || lpAudioSourceConfig == NULL)
    {
        return FALSE;
    }
    ret = IsValidToken(ConfigAudioSourceToken, Audio_Src_Token);
    if (ret < 0)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL GetAudioOutputs(LPAUDIONODES lpAudioOutput)
{
    return TRUE;
}

BOOL GetAudioOutputConfigs(LPAUDIOCONFIGS lpAudioOutputs)
{
    return TRUE;
}

BOOL GetAudioOutputConfigOptions(CHAR *ConfigAudioOutputToken,CHAR *MediaProfileToken,LPAUDIOCONFIGOPTIONS lpAudioSourceConfigOptions)
{
    return TRUE;
}

BOOL GetAudioOutputConfig(CHAR *ConfigAudioOutputToken,LPAUDIOCONFIG lpAudioOutputConfig)
{
    return TRUE;
}

BOOL SetAudioOutputConfig(CHAR *ConfigAudioOutputToken,LPAUDIOCONFIG   AudioOutputConfig)
{
    return TRUE;
}

//音频参数暂时写死，后面再配置
BOOL GetAudioEncConfigs(LPAUDIOCODINGCONFIGS lpAudioCodingConfigs)
{
    if (lpAudioCodingConfigs == NULL)
    {
        return FALSE;
    }
	//LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
    lpAudioCodingConfigs->ConfigSize = 1;
	strncpy(lpAudioCodingConfigs->ConfigEncs[0].Configtoken, AUDIOENCODECONFIGTOKEN0, strlen(AUDIOENCODECONFIGTOKEN0));
	strncpy(lpAudioCodingConfigs->ConfigEncs[0].ConfigName,  AUDIOENCODECONFIGTOKEN0, strlen(AUDIOENCODECONFIGTOKEN0));
	strncpy(lpAudioCodingConfigs->ConfigEncs[0].RTSPSessionTimeout,"PT30M",OVFCHARLENTH);
    lpAudioCodingConfigs->ConfigEncs[0].AudioEncBitrate    =  16; //SysContext->ipcam_SysConfig->ConfigAudio.bzSampleSize;
    lpAudioCodingConfigs->ConfigEncs[0].AudioEncSampleRate = 8;//SysContext->ipcam_SysConfig->ConfigAudio.usSampleSpeed;
    lpAudioCodingConfigs->ConfigEncs[0].AudioEncType       = 0;//AudioEnCtypeIPCtoOVFmap(SysContext->ipcam_SysConfig->ConfigAudio.bzEncodeType);
    lpAudioCodingConfigs->ConfigEncs[0].ConfigUseCount = 2;
    lpAudioCodingConfigs->ConfigEncs[0].ForcePersistence = TRUE;
    lpAudioCodingConfigs->ConfigEncs[0].Multicast.AutoStart = TRUE;
    return TRUE;
}

//音频参数暂时写死，后面再配置
BOOL GetAudioEncConfigOptions(CHAR *ConfigAudioEncToken, CHAR *MediaProfileToken, LPAUDIOENCCONFIGOPTIONS lpAudioEncConfigOptons)
{
    int ret = 0;
	if(NULL != ConfigAudioEncToken){
		ret = IsValidToken(ConfigAudioEncToken, Audio_Encode_Token);
		if (ret < 0)
		{
			return FALSE;
		}
	}
	if(NULL != MediaProfileToken ){
		ret = IsValidToken(MediaProfileToken, Token);
		if (ret < 0)
		{
			return FALSE;
		}
	}
	//LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
    lpAudioEncConfigOptons->AudioEncConfigOptionSize = 1;
    lpAudioEncConfigOptons->AudioEncConfigOption[0].EncType = 0;//AudioEnCtypeIPCtoOVFmap(SysContext->ipcam_SysConfig->ConfigAudio.bzEncodeType);
    lpAudioEncConfigOptons->AudioEncConfigOption[0].EncBitrateList.ItemsSize  = 1;
    lpAudioEncConfigOptons->AudioEncConfigOption[0].EncBitrateList.Items[0]   = 16; //SysContext->ipcam_SysConfig->ConfigAudio.bzSampleSize;
    lpAudioEncConfigOptons->AudioEncConfigOption[0].EncSampleRateList.ItemsSize = 1;
    lpAudioEncConfigOptons->AudioEncConfigOption[0].EncSampleRateList.Items[0]= 8;//SysContext->ipcam_SysConfig->ConfigAudio.usSampleSpeed;
    return TRUE;
}

//音频参数暂时写死，后面再配置
BOOL GetAudioEncConfig(CHAR *ConfigAudioEncToken, LPAUDIOCODINGCONFIG lpAudioCodingConfig)
{
    int ret = 0;
    if (ConfigAudioEncToken == NULL || lpAudioCodingConfig == NULL)
    {
        return FALSE;
    }
    ret = IsValidToken(ConfigAudioEncToken, Audio_Encode_Token);
    if (ret < 0)
    {
        return FALSE;
    }
	//LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	strncpy(lpAudioCodingConfig->Configtoken, AUDIOENCODECONFIGTOKEN0, strlen(AUDIOENCODECONFIGTOKEN0));
	strncpy(lpAudioCodingConfig->ConfigName,  AUDIOENCODECONFIGTOKEN0, strlen(AUDIOENCODECONFIGTOKEN0));
	strncpy(lpAudioCodingConfig->RTSPSessionTimeout,"PT30M",OVFCHARLENTH);
    lpAudioCodingConfig->AudioEncBitrate    =  16;//SysContext->ipcam_SysConfig->ConfigAudio.bzSampleSize;
    lpAudioCodingConfig->AudioEncSampleRate = 8; //SysContext->ipcam_SysConfig->ConfigAudio.usSampleSpeed;
    lpAudioCodingConfig->AudioEncType       = 0;//AudioEnCtypeIPCtoOVFmap(SysContext->ipcam_SysConfig->ConfigAudio.bzEncodeType);
    lpAudioCodingConfig->ConfigUseCount = 2;
    lpAudioCodingConfig->ForcePersistence = TRUE;
    lpAudioCodingConfig->Multicast.AutoStart = TRUE;
    return TRUE;
}

BOOL SetAudioEncConfig(CHAR *ConfigAudioEncToken, LPAUDIOCODINGCONFIG lpAudioCodingConfig)
{
    int ret = 0;
    if (ConfigAudioEncToken == NULL || lpAudioCodingConfig == NULL)
    {
        return FALSE;
    }
    ret = IsValidToken(ConfigAudioEncToken, Audio_Encode_Token); 
    if (ret < 0)
    {
        return FALSE;
    }
	//LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	//if(SysContext->ipcam_SysConfig->ConfigAudio.usSampleSpeed!=lpAudioCodingConfig->AudioEncSampleRate)return 2;//?这里的speed范围
	if(8 != lpAudioCodingConfig->AudioEncSampleRate)return 2;
    return TRUE;
}

//音频参数暂时写死，后面再配置
BOOL GetAudioDecConfigs(LPAUDIOCODINGCONFIGS lpAudioCodingConfigs)//?
{
    if (lpAudioCodingConfigs == NULL)
    {
        return FALSE;
    }
	//LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	lpAudioCodingConfigs->ConfigEncs[0].AudioEncBitrate    = 16;//SysContext->ipcam_SysConfig->ConfigAudio.bzSampleSize;
	lpAudioCodingConfigs->ConfigEncs[0].AudioEncSampleRate = 8;//SysContext->ipcam_SysConfig->ConfigAudio.usSampleSpeed;
	lpAudioCodingConfigs->ConfigEncs[0].AudioEncType       = 0;//AudioEnCtypeIPCtoOVFmap(SysContext->ipcam_SysConfig->ConfigAudio.bzEncodeType);
    return TRUE;
}

BOOL GetAudioDecConfigsOptions(CHAR *ConfigAudioDecToken, CHAR *MediaProfileToken, LPAUDIODECCONFIGOPTON lpAudioDecConfigOption)//?
{
    if (ConfigAudioDecToken == NULL)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL GetAudioDecConfig(CHAR *ConfigAudioDecToken, LPAUDIOCODINGCONFIG lpAudioCodingConfig)
{
    if (ConfigAudioDecToken == NULL || lpAudioCodingConfig == NULL)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL SetAudioDecConfig(CHAR *ConfigAudioDecToken, LPAUDIOCODINGCONFIG AudioCodingConfig)
{
    if (ConfigAudioDecToken == NULL || AudioCodingConfig == NULL)
    {
        return FALSE;
    }
    return TRUE;
}


BOOL GetVideoSources(LPVIDEOSOURCES  lpVideoSources)//?
{
	//  printf("======================================GetVideoSources=================================\n");
    if (lpVideoSources == NULL)
    {
        return FALSE;
    }
    int MainWidth   = 1280;
    int MainHeight  = 720;
    int ChildWidth  = 640;
    int ChildHeight = 480;
	//LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
  	lpVideoSources->VideoSourceSize				=1;
  	strncpy(lpVideoSources->VideoSources[0].VideoToken,VIDEOSOURCECONFIGTOKEN0,OVFCHARLENTH);
	 lpVideoSources->VideoSources[0].VideoSourceFramerate =25;
	 SetFramHightandWidth(&MainWidth,&MainHeight,&ChildWidth,&ChildHeight);
//	lpVideoSources->VideoSources[0].VideoSourceResolution.Height =720;
	//lpVideoSources->VideoSources[0].VideoSourceResolution.Width=1280;
	  lpVideoSources->VideoSources[0].VideoSourceResolution.Height =MainHeight;
	  lpVideoSources->VideoSources[0].VideoSourceResolution.Width=MainWidth;
    return TRUE;
}

BOOL GetVideoSourceConfigs(LPVIDEOSOURCECONFIGS lpVideoSourcesConfigs)//?
{
//	  printf("===============================================GetVideoSourceConfigs==================================\n");
    if (lpVideoSourcesConfigs == NULL)
    {
        return FALSE;
    }
    int MainWidth   = 1280;
    int MainHeight  = 720;
    int ChildWidth  = 640;
    int ChildHeight = 480;
	lpVideoSourcesConfigs->ConfigSize	=1;
	strncpy(lpVideoSourcesConfigs->VideoSourceConfigs[0].ConfigToken, VIDEOSOURCECONFIGTOKEN0, strlen(VIDEOSOURCECONFIGTOKEN0));
	strncpy(lpVideoSourcesConfigs->VideoSourceConfigs[0].ConfigName,VIDEOSOURCECONFIGTOKEN0,OVFCHARLENTH);
	lpVideoSourcesConfigs->VideoSourceConfigs[0].ConfigUseCount =2;
	strncpy(lpVideoSourcesConfigs->VideoSourceConfigs[0].SourceToken,"videosource0",OVFCHARLENTH);
	SetFramHightandWidth(&MainWidth,&MainHeight,&ChildWidth,&ChildHeight);
	lpVideoSourcesConfigs->VideoSourceConfigs[0].SourceBounds.height =MainHeight;
	lpVideoSourcesConfigs->VideoSourceConfigs[0].SourceBounds.width  =MainWidth;
//	pVideoSourcesConfigs->VideoSourceConfigs[0].SourceBounds.height =720;
//	lpVideoSourcesConfigs->VideoSourceConfigs[0].SourceBounds.width  =1280;
	lpVideoSourcesConfigs->VideoSourceConfigs[0].SourceBounds.y	  =0;
	lpVideoSourcesConfigs->VideoSourceConfigs[0].SourceBounds.x      =0;


    return TRUE;
}

BOOL GetVideoSourceConfigOptions(CHAR *ConfigVideoSourceToken, CHAR *MediaProfileToken, LPVIDEOSOURCECONFIGOPTIONS lpVideoSourceConfigOptions)
{
//	printf("===============================================GetVideoSourceConfigOptions===================================");
	int ret = 0;
    if (NULL!= ConfigVideoSourceToken  )
    {
		ret = IsValidToken(ConfigVideoSourceToken, Video_Src_Token);
		if (ret < 0)
		{
			return FALSE;
		}
    }
	if (NULL!= MediaProfileToken  )
    {
		ret = IsValidToken(MediaProfileToken, Token);
		if (ret < 0)
		{
			return FALSE;
		}
    }
    
    int MainWidth   = 1280;
    int MainHeight  = 720;
    int ChildWidth  = 640;
    int ChildHeight = 480;
  	SetFramHightandWidth(&MainWidth,&MainHeight,&ChildWidth,&ChildHeight);
	lpVideoSourceConfigOptions->VideoSourceTokenSize =1;
	strncpy(lpVideoSourceConfigOptions->VideoSourceTokens[0],"videosource0",OVFCHARLENTH);
//	lpVideoSourceConfigOptions->BoundsRange.HeightRange.Max =720;//?
  lpVideoSourceConfigOptions->BoundsRange.HeightRange.Max =MainHeight;
 // lpVideoSourceConfigOptions->BoundsRange.HeightRange.Max =480;
//	lpVideoSourceConfigOptions->BoundsRange.HeightRange.Min =112;
	//lpVideoSourceConfigOptions->BoundsRange.WidthRange.Max  =1280;
	lpVideoSourceConfigOptions->BoundsRange.WidthRange.Max  =MainWidth;
 // lpVideoSourceConfigOptions->BoundsRange.WidthRange.Max  =640;
	lpVideoSourceConfigOptions->BoundsRange.WidthRange.Min  =160;
	lpVideoSourceConfigOptions->BoundsRange.XRange.Max		=0;
	lpVideoSourceConfigOptions->BoundsRange.YRange.Min		=0;
	lpVideoSourceConfigOptions->BoundsRange.YRange.Max		=0;
	lpVideoSourceConfigOptions->BoundsRange.YRange.Min		=0;
    return TRUE;
}

BOOL GetVideoSourceConfig(CHAR *ConfigVideoSourceToken, LPVIDEOSOURCECONFIG lpVideoSourceConfig)//?
{
	
	  int MainWidth   = 1280;
    int MainHeight  = 720;
    int ChildWidth  = 640;
    int ChildHeight = 480;
    int ret = 0;
    if (ConfigVideoSourceToken == NULL || lpVideoSourceConfig == NULL)
    {
        return FALSE;
    }
    ret = IsValidToken(ConfigVideoSourceToken, Video_Src_Token);
    if (ret < 0)
    {
        return FALSE;
    }
    
	strncpy(lpVideoSourceConfig->ConfigToken, VIDEOSOURCECONFIGTOKEN0,strlen(VIDEOSOURCECONFIGTOKEN0));
	strncpy(lpVideoSourceConfig->ConfigName,VIDEOSOURCECONFIGTOKEN0,OVFCHARLENTH);
	lpVideoSourceConfig->ConfigUseCount =2;
	strncpy(lpVideoSourceConfig->SourceToken,"videosource0",OVFCHARLENTH);
	SetFramHightandWidth(&MainWidth,&MainHeight,&ChildWidth,&ChildHeight);
	lpVideoSourceConfig->SourceBounds.height =MainHeight;
	lpVideoSourceConfig->SourceBounds.width  =MainWidth;
	//lpVideoSourceConfig->SourceBounds.height =720;
	//lpVideoSourceConfig->SourceBounds.width  =1280;
	lpVideoSourceConfig->SourceBounds.y	  =0;
	lpVideoSourceConfig->SourceBounds.x      =0;

    return TRUE;
}

BOOL SetVideoSourceConfig(CHAR *ConfigVideoSourceToken, LPVIDEOSOURCECONFIG lpVideoSourceConfig)
{
//	  printf("=====================================SetVideoSourceConfig=============================\n");
    int ret = 0;
    if (ConfigVideoSourceToken == NULL || lpVideoSourceConfig == NULL)
    {
        return FALSE;
    }
	ret = IsValidToken(ConfigVideoSourceToken, Video_Src_Token);
    if (ret < 0)
    {
        return FALSE;
    }
	if (720 == lpVideoSourceConfig->SourceBounds.height )
	{
		return 2;
	}
    
    return TRUE;
}

#if 0
BOOL GetVideoEncConfigs(LPVIDEOENCCONFIGS lpVideoEncConfigs)//?
{
	//   printf("=====================================GetVideoEncConfigs=============================\n");
    if (lpVideoEncConfigs == NULL)
    {
        return FALSE;
    }
	LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	lpVideoEncConfigs->VideoEncConfigSize =2;
	strncpy(lpVideoEncConfigs->VideoEncConfigs[0].ConfigToken, VIDEOENCODECONFIGTOKEN0, strlen(VIDEOENCODECONFIGTOKEN0));
 // lpVideoEncConfigs->VideoEncConfigs[0].ConfigUseCount =1;
	lpVideoEncConfigs->VideoEncConfigs[0].ConfigUseCount =1;
	strncpy(lpVideoEncConfigs->VideoEncConfigs[0].RtspSessionTimeout,"PT30M",OVFCHARLENTH);
	lpVideoEncConfigs->VideoEncConfigs[0].EncType       = SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[0].EncType;
	//lpVideoEncConfigs->VideoEncConfigs[0].RateControl.FrameRateLimit = 13;
	lpVideoEncConfigs->VideoEncConfigs[0].RateControl.FrameRateLimit = 25;
	//lpVideoEncConfigs->VideoEncConfigs[0].RateControl.EncodingInterval=1;
	lpVideoEncConfigs->VideoEncConfigs[0].RateControl.EncodingInterval=1;
	lpVideoEncConfigs->VideoEncConfigs[0].EncQuality  =3;
	//lpVideoEncConfigs->VideoEncConfigs[0].EncQuality  =6;
	//lpVideoEncConfigs->VideoEncConfigs[0].RateControl.BitrateLimit=16;
	lpVideoEncConfigs->VideoEncConfigs[0].RateControl.BitrateLimit=4096;
	strncpy(lpVideoEncConfigs->VideoEncConfigs[0].ConfigName , "VideoEncoderConfiguration0",OVFCHARLENTH);
	lpVideoEncConfigs->VideoEncConfigs[0].EncResolution.Width =1280;
	lpVideoEncConfigs->VideoEncConfigs[0].EncResolution.Height=720;
	lpVideoEncConfigs->VideoEncConfigs[0].ConfigH264.GovLength=75;
	//lpVideoEncConfigs->VideoEncConfigs[0].ConfigH264.GovLength=50;
	//lpVideoEncConfigs->VideoEncConfigs[0].ConfigH264.H264Profile=0;
	lpVideoEncConfigs->VideoEncConfigs[0].ConfigH264.H264Profile=0;
	lpVideoEncConfigs->VideoEncConfigs[0].Multicast.AutoStart = FALSE;
	lpVideoEncConfigs->VideoEncConfigs[0].Multicast.TTL		  = 0;

	strncpy(lpVideoEncConfigs->VideoEncConfigs[1].ConfigToken, VIDEOENCODECONFIGTOKEN1, strlen(VIDEOENCODECONFIGTOKEN1));
	lpVideoEncConfigs->VideoEncConfigs[1].ConfigUseCount =2;
	strncpy(lpVideoEncConfigs->VideoEncConfigs[1].RtspSessionTimeout,"PT0H12M0S",OVFCHARLENTH);
	lpVideoEncConfigs->VideoEncConfigs[1].EncType       = SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[1].EncType;
	//lpVideoEncConfigs->VideoEncConfigs[1].RateControl.FrameRateLimit = 13;
	lpVideoEncConfigs->VideoEncConfigs[1].RateControl.FrameRateLimit = 30;
	lpVideoEncConfigs->VideoEncConfigs[1].RateControl.EncodingInterval=25;
	lpVideoEncConfigs->VideoEncConfigs[1].EncQuality  =80;
	//lpVideoEncConfigs->VideoEncConfigs[1].RateControl.BitrateLimit=16;
	lpVideoEncConfigs->VideoEncConfigs[1].RateControl.BitrateLimit=300;
	strncpy(lpVideoEncConfigs->VideoEncConfigs[1].ConfigName , "VideoEncoderConfiguration1",OVFCHARLENTH);
//	lpVideoEncConfigs->VideoEncConfigs[1].EncResolution.Width =1280;
	//lpVideoEncConfigs->VideoEncConfigs[1].EncResolution.Height=720;
	lpVideoEncConfigs->VideoEncConfigs[1].EncResolution.Width =640;
	lpVideoEncConfigs->VideoEncConfigs[1].EncResolution.Height=480;
	lpVideoEncConfigs->VideoEncConfigs[1].ConfigH264.GovLength=25;
	lpVideoEncConfigs->VideoEncConfigs[1].ConfigH264.H264Profile=0;
  //lpVideoEncConfigs->VideoEncConfigs[1].ConfigH264.H264Profile=1;
	lpVideoEncConfigs->VideoEncConfigs[1].Multicast.AutoStart = FALSE;
	lpVideoEncConfigs->VideoEncConfigs[1].Multicast.TTL		  = 0;
    return TRUE;
}
#endif

//参数还要设置，现在不知道参数情况
void SetFramHightandWidth(int *MainWidth,int *MainHeight,int *ChildWidth,int *ChildHeight)
{    
	// LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	// int Bitrate= SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[0].Resolution;
	int nResolution =  conf_get_int("/mnt/sif/hkipc.conf", "CifOrD1");	  
	switch(nResolution)
	{
		case 9:
			*MainWidth  = 1280;
			*MainHeight = 720;	
			break;    
		case 10:	    	    
			*MainWidth   = 1280;
			*MainHeight  = 960;	   		    
			break;
		case 5:
			*MainWidth   = 640;
			*MainHeight  = 480;
			//  printf("0000000000000000000000000000000000mainwidth=%d,ChildWidth=%d0000000000000000000000000000000\n",*MainWidth,*MainHeight);   		
			break;
		default :
			printf("main fram nResolution is wrong\n");
			break;
	}

	// int childBitrate= SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[1].Resolution;
	int nchildResolution =  conf_get_int("/mnt/sif/subipc.conf", "enc");
	switch(nchildResolution)
	{
		case 3:
			*ChildWidth  = 320;
			*ChildHeight = 240;
			break;
		case 5:	    	    
			*ChildWidth  = 640;
			*ChildHeight = 480;
			// printf("0000000000000000000000000000000000ChildWidth =%d,ChildHeight=%d0000000000000000000000000000000\n",*ChildWidth, *ChildHeight);   		
			break;
		default:
			printf("child fram nchildResolution is wrong\n");
			break;
	}
}


BOOL GetVideoEncConfigs(LPVIDEOENCCONFIGS lpVideoEncConfigs)//?
{
	int EncType;
	int FrameRate;
	int RcLevel = 2;		//HK暂时没做
	int BitRate;
	int EncProfileType = 1;   //HK 暂时没做

	//   printf("=====================================GetVideoEncConfigs=============================\n");
   int MainWidth   = 1280;
   int MainHeight  = 720;
   int ChildWidth  = 640;
   int ChildHeight = 480;
   if (lpVideoEncConfigs == NULL)
   {
        return FALSE;
   }
	//LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	EncType = 2;
	FrameRate = conf_get_int("/mnt/sif/hkipc.conf", "BitRate");	
	BitRate = conf_get_int("/mnt/sif/hkipc.conf", "VinFormat");
	lpVideoEncConfigs->VideoEncConfigSize =2;
	strncpy(lpVideoEncConfigs->VideoEncConfigs[0].ConfigToken, VIDEOENCODECONFIGTOKEN0, strlen(VIDEOENCODECONFIGTOKEN0));
	// lpVideoEncConfigs->VideoEncConfigs[0].ConfigUseCount =1;
	lpVideoEncConfigs->VideoEncConfigs[0].ConfigUseCount =1;
	strncpy(lpVideoEncConfigs->VideoEncConfigs[0].RtspSessionTimeout,"PT0H12M0S",OVFCHARLENTH);
	lpVideoEncConfigs->VideoEncConfigs[0].EncType       = EncType;//SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[0].EncType;
	//lpVideoEncConfigs->VideoEncConfigs[0].RateControl.FrameRateLimit = 13;
	lpVideoEncConfigs->VideoEncConfigs[0].RateControl.FrameRateLimit = FrameRate;//SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[0].FrameRate;
	//lpVideoEncConfigs->VideoEncConfigs[0].RateControl.EncodingInterval=1;
	lpVideoEncConfigs->VideoEncConfigs[0].RateControl.EncodingInterval=100;
	//	lpVideoEncConfigs->VideoEncConfigs[0].EncQuality  =80;
	lpVideoEncConfigs->VideoEncConfigs[0].EncQuality  = RcLevel;//SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[0].RcLevel;
	//lpVideoEncConfigs->VideoEncConfigs[0].EncQuality  =6;
	//lpVideoEncConfigs->VideoEncConfigs[0].RateControl.BitrateLimit=16;
	//	lpVideoEncConfigs->VideoEncConfigs[0].RateControl.BitrateLimit=5000;
	lpVideoEncConfigs->VideoEncConfigs[0].RateControl.BitrateLimit= BitRate;//SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[0].nBitRate; 
	strncpy(lpVideoEncConfigs->VideoEncConfigs[0].ConfigName , "VideoEncoderConfiguration0",OVFCHARLENTH);
	SetFramHightandWidth(&MainWidth,&MainHeight,&ChildWidth,&ChildHeight);
	lpVideoEncConfigs->VideoEncConfigs[0].EncResolution.Width =MainWidth;
	lpVideoEncConfigs->VideoEncConfigs[0].EncResolution.Height=MainHeight;
	//printf("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqmainwidth=%d,mainheight=%dqqqqqchilewidth=%d,chileheight=%dqqqqqqqqqqqqqqqqqqqqqq\n",lpVideoEncConfigs->VideoEncConfigs[0].EncResolution.Width,lpVideoEncConfigs->VideoEncConfigs[0].EncResolution.Height,lpVideoEncConfigs->VideoEncConfigs[1].EncResolution.Width,lpVideoEncConfigs->VideoEncConfigs[1].EncResolution.Height);
	//	printf("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzwidht=%d,height=%d,child_width=%d,child_hight=%dwwwwwwwwwwwwwwwwwwww\n",MainWidth,MainHeight,ChildWidth,ChildHeight); 
	lpVideoEncConfigs->VideoEncConfigs[0].ConfigH264.GovLength = 25;
	//lpVideoEncConfigs->VideoEncConfigs[0].ConfigH264.GovLength=50;
	//lpVideoEncConfigs->VideoEncConfigs[0].ConfigH264.H264Profile=0;
	lpVideoEncConfigs->VideoEncConfigs[0].ConfigH264.H264Profile= EncProfileType;//SysContext->ipcam_SysConfig->ConfigVideo.EncProfileType;
	lpVideoEncConfigs->VideoEncConfigs[0].Multicast.AutoStart = FALSE;
	lpVideoEncConfigs->VideoEncConfigs[0].Multicast.TTL		  = 0;

	strncpy(lpVideoEncConfigs->VideoEncConfigs[1].ConfigToken, VIDEOENCODECONFIGTOKEN1, strlen(VIDEOENCODECONFIGTOKEN1));
	lpVideoEncConfigs->VideoEncConfigs[1].ConfigUseCount =1;  
	strncpy(lpVideoEncConfigs->VideoEncConfigs[1].RtspSessionTimeout,"PT0H12M0S",OVFCHARLENTH);
	lpVideoEncConfigs->VideoEncConfigs[1].EncType       = EncType;//SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[1].EncType;
	//lpVideoEncConfigs->VideoEncConfigs[1].RateControl.FrameRateLimit = 13;
	lpVideoEncConfigs->VideoEncConfigs[1].RateControl.FrameRateLimit =  FrameRate;//SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[1].FrameRate;
	lpVideoEncConfigs->VideoEncConfigs[1].RateControl.EncodingInterval=100;
	//lpVideoEncConfigs->VideoEncConfigs[1].EncQuality  =80;
	lpVideoEncConfigs->VideoEncConfigs[1].EncQuality  = RcLevel;//SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[1].RcLevel;
	//lpVideoEncConfigs->VideoEncConfigs[1].RateControl.BitrateLimit=16;
	//	lpVideoEncConfigs->VideoEncConfigs[1].RateControl.BitrateLimit=300;
	lpVideoEncConfigs->VideoEncConfigs[1].RateControl.BitrateLimit= BitRate;//SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[1].nBitRate;
	strncpy(lpVideoEncConfigs->VideoEncConfigs[1].ConfigName , "VideoEncoderConfiguration1",OVFCHARLENTH);
	//	lpVideoEncConfigs->VideoEncConfigs[1].EncResolution.Width =1280;
	//lpVideoEncConfigs->VideoEncConfigs[1].EncResolution.Height=720;
	lpVideoEncConfigs->VideoEncConfigs[1].EncResolution.Width =ChildWidth;
	lpVideoEncConfigs->VideoEncConfigs[1].EncResolution.Height=ChildHeight;
	lpVideoEncConfigs->VideoEncConfigs[1].ConfigH264.GovLength=25;
	lpVideoEncConfigs->VideoEncConfigs[1].ConfigH264.H264Profile= EncProfileType;//SysContext->ipcam_SysConfig->ConfigVideo.EncProfileType;
	//lpVideoEncConfigs->VideoEncConfigs[1].ConfigH264.H264Profile=1;
	lpVideoEncConfigs->VideoEncConfigs[1].Multicast.AutoStart = FALSE;
	lpVideoEncConfigs->VideoEncConfigs[1].Multicast.TTL		  = 0; 
	
      return TRUE;
}

BOOL GetVideoEncConfigOptions(CHAR *ConfigVideoEncToken, CHAR *MediaProfileToken, LPVIDEOENCCONFIGOPTIONS lpVideoEncConfigOptions)
{
//	printf("=====================================GetVideoEncConfigOptions=============================\n");
	int ret = 0;
	if (ConfigVideoEncToken == NULL)
	{
	    return FALSE;
	}

	ret = IsValidToken(ConfigVideoEncToken, Video_Encode_Token);
	if (ret < 0)
	{
	    return FALSE;
	}
    
	int MainWidth   = 1280;
	int MainHeight  = 720;
	int ChildWidth  = 640;
	int ChildHeight = 480;
	SetFramHightandWidth(&MainWidth,&MainHeight,&ChildWidth,&ChildHeight);
	lpVideoEncConfigOptions->EncQualityRange.Max=6;
	lpVideoEncConfigOptions->EncQualityRange.Min=1;
	lpVideoEncConfigOptions->EncJpegOptions.ResolutionsAvailableSize=1;
	lpVideoEncConfigOptions->EncJpegOptions.FrameRateRange.Max=25;
	lpVideoEncConfigOptions->EncJpegOptions.FrameRateRange.Min=1;
	lpVideoEncConfigOptions->EncJpegOptions.ResolutionsAvailable->Height=MainHeight;
	lpVideoEncConfigOptions->EncJpegOptions.ResolutionsAvailable->Width=MainWidth;
	lpVideoEncConfigOptions->EncJpegOptions.EncodingIntervalRange.Max=120;
	lpVideoEncConfigOptions->EncJpegOptions.EncodingIntervalRange.Min=1;

	//lpVideoEncConfigOptions->EncMP4Options.Mpeg4ProfilesSupportedSize=1;
	//lpVideoEncConfigOptions->EncMP4Options.ResolutionsAvailableSize=1;
	//lpVideoEncConfigOptions->EncMP4Options.GovLengthRange.Max=100;
	//lpVideoEncConfigOptions->EncMP4Options.GovLengthRange.Min=1;
	//lpVideoEncConfigOptions->EncMP4Options.ResolutionsAvailables->Height=720;
	//lpVideoEncConfigOptions->EncMP4Options.ResolutionsAvailables->Width=1280;
	//lpVideoEncConfigOptions->EncMP4Options.FrameRateRange.Max=25;
	//lpVideoEncConfigOptions->EncMP4Options.FrameRateRange.Min=1;
	//lpVideoEncConfigOptions->EncMP4Options.Mpeg4ProfilesSupported[0]=0;

	if(!strcmp(ConfigVideoEncToken,VIDEOENCODECONFIGTOKEN0))
	{
		lpVideoEncConfigOptions->EncAVSOptions.AVSProfilesSupportedSize=1;
		lpVideoEncConfigOptions->EncAVSOptions.ResolutionsAvailableSize=1;
		lpVideoEncConfigOptions->EncAVSOptions.AVSProfilesSupporteds[0] =0;
		lpVideoEncConfigOptions->EncAVSOptions.AVSProfilesSupporteds[1] =1;
		lpVideoEncConfigOptions->EncAVSOptions.ResolutionsAvailables->Height=MainHeight;
		lpVideoEncConfigOptions->EncAVSOptions.ResolutionsAvailables->Width =MainWidth;
		lpVideoEncConfigOptions->EncAVSOptions.GovLengthRange.Min=1;
		lpVideoEncConfigOptions->EncAVSOptions.GovLengthRange.Max=100;
		lpVideoEncConfigOptions->EncAVSOptions.FrameRateRange.Max=60;
		lpVideoEncConfigOptions->EncAVSOptions.FrameRateRange.Min=1;
		lpVideoEncConfigOptions->EncAVSOptions.EncodingIntervalRange.Min=1;
		lpVideoEncConfigOptions->EncAVSOptions.EncodingIntervalRange.Max=120;
	}
	else if(!strcmp(ConfigVideoEncToken,VIDEOENCODECONFIGTOKEN1))
	{
		lpVideoEncConfigOptions->EncAVSOptions.AVSProfilesSupportedSize=1;
		lpVideoEncConfigOptions->EncAVSOptions.ResolutionsAvailableSize=1;
		lpVideoEncConfigOptions->EncAVSOptions.AVSProfilesSupporteds[0] =0;
		lpVideoEncConfigOptions->EncAVSOptions.AVSProfilesSupporteds[1] =1;
		lpVideoEncConfigOptions->EncAVSOptions.ResolutionsAvailables->Height = ChildHeight;
		lpVideoEncConfigOptions->EncAVSOptions.ResolutionsAvailables->Width = ChildWidth;
		lpVideoEncConfigOptions->EncAVSOptions.GovLengthRange.Min=1;
		lpVideoEncConfigOptions->EncAVSOptions.GovLengthRange.Max=100;
		lpVideoEncConfigOptions->EncAVSOptions.FrameRateRange.Max=60;
		lpVideoEncConfigOptions->EncAVSOptions.FrameRateRange.Min=1;
		lpVideoEncConfigOptions->EncAVSOptions.EncodingIntervalRange.Min=1;
		lpVideoEncConfigOptions->EncAVSOptions.EncodingIntervalRange.Max=120;
	}
	else
		return FALSE;

    return TRUE;
}

BOOL GetVideoEncConfig(CHAR *ConfigVideoEncToken, LPVIDEOENCCONFIG lpVideoEncConfig)
{   
	int EncType;
	int FrameRate;
	int RcLevel = 2;		//HK暂时没做
	int BitRate;
	int EncProfileType = 1;   //HK 暂时没做
	 // printf("=====================================GetVideoEncConfig=============================\n");
    int ret = 0;
    int MainWidth   = 1280;
    int MainHeight  = 720;
    int ChildWidth  = 640;
    int ChildHeight = 480;
    if (ConfigVideoEncToken == NULL || lpVideoEncConfig == NULL)
    {
        return FALSE;
    }
    ret = IsValidToken(ConfigVideoEncToken, Video_Encode_Token);
    if (ret < 0)
    {
        return FALSE;
    }
	//LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext(); 	
	EncType = 2;
	FrameRate = conf_get_int("/mnt/sif/hkipc.conf", "BitRate");	
	BitRate = conf_get_int("/mnt/sif/hkipc.conf", "VinFormat");
	if(!strcmp(ConfigVideoEncToken,VIDEOENCODECONFIGTOKEN0)){
		strncpy(lpVideoEncConfig->ConfigToken, VIDEOENCODECONFIGTOKEN0, strlen(VIDEOENCODECONFIGTOKEN0));
		lpVideoEncConfig->ConfigUseCount =1;
		strncpy(lpVideoEncConfig->RtspSessionTimeout,"PT0H12M0S",OVFCHARLENTH);
		lpVideoEncConfig->EncType       = EncType;//SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[0].EncType;
		lpVideoEncConfig->RateControl.FrameRateLimit = FrameRate;//SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[0].FrameRate;
		lpVideoEncConfig->RateControl.EncodingInterval=100;
		lpVideoEncConfig->EncQuality  = RcLevel;//SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[0].RcLevel + 1;
		lpVideoEncConfig->RateControl.BitrateLimit= BitRate;//SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[0].nBitRate;
		strncpy(lpVideoEncConfig->ConfigName , "VideoEncoderConfiguration0",OVFCHARLENTH);
		SetFramHightandWidth(&MainWidth,&MainHeight,&ChildWidth,&ChildHeight);
		lpVideoEncConfig->EncResolution.Width =MainWidth;
		lpVideoEncConfig->EncResolution.Height=MainHeight;
		lpVideoEncConfig->ConfigH264.GovLength=25;
		lpVideoEncConfig->ConfigH264.H264Profile= EncProfileType;//SysContext->ipcam_SysConfig->ConfigVideo.EncProfileType;
		lpVideoEncConfig->Multicast.AutoStart = FALSE;
		lpVideoEncConfig->Multicast.TTL	= 0;
	}
	else if(!strcmp(ConfigVideoEncToken,VIDEOENCODECONFIGTOKEN1)){
		strncpy(lpVideoEncConfig->ConfigToken, VIDEOENCODECONFIGTOKEN1, strlen(VIDEOENCODECONFIGTOKEN1));
		lpVideoEncConfig->ConfigUseCount =1;
		strncpy(lpVideoEncConfig->RtspSessionTimeout,"PT0H12M0S",OVFCHARLENTH);
		lpVideoEncConfig->EncType	      = EncType;//SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[1].EncType;
		lpVideoEncConfig->RateControl.FrameRateLimit = FrameRate;//SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[1].FrameRate;
		lpVideoEncConfig->RateControl.EncodingInterval=100;
		lpVideoEncConfig->EncQuality  = RcLevel; //SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[1].RcLevel+1;
		lpVideoEncConfig->RateControl.BitrateLimit= BitRate;//SysContext->ipcam_SysConfig->ConfigVideo.ChannelInfo[1].nBitRate;
		strncpy(lpVideoEncConfig->ConfigName , "VideoEncoderConfiguration1",OVFCHARLENTH);
		SetFramHightandWidth(&MainWidth,&MainHeight,&ChildWidth,&ChildHeight);
		lpVideoEncConfig->EncResolution.Width =ChildWidth;
		lpVideoEncConfig->EncResolution.Height=ChildHeight;
		lpVideoEncConfig->ConfigH264.GovLength=25;
		lpVideoEncConfig->ConfigH264.H264Profile= EncProfileType;//SysContext->ipcam_SysConfig->ConfigVideo.EncProfileType;
		lpVideoEncConfig->Multicast.AutoStart  = FALSE;
		lpVideoEncConfig->Multicast.TTL	      = 0;
	}
	else
		return FALSE;
    return TRUE;
}

BOOL SetVideoEncConfig(CHAR *ConfigVideoEncToken, LPVIDEOENCCONFIG lpVideoEncConfig)
{
//	   printf("=====================================SetVideoEncConfig=============================\n");
    int ret = 0;
    if (ConfigVideoEncToken == NULL || lpVideoEncConfig == NULL)
    {
        return FALSE;
    }
    ret = IsValidToken(ConfigVideoEncToken, Video_Encode_Token);
    if (ret < 0)
    {
        return FALSE;
    }
	if(lpVideoEncConfig->ConfigH264.GovLength>100||lpVideoEncConfig<0)return 2;//?这个参数也没有

	if(!strcmp(ConfigVideoEncToken,VIDEOENCODECONFIGTOKEN0))
	{
	#if 0
		IPCAM_VISetFrameRate(0 , lpVideoEncConfig->RateControl.FrameRateLimit);
		IPCAM_VISetBitRate(0 , lpVideoEncConfig->RateControl.BitrateLimit);
		IPCAM_VISetQLevel(0, lpVideoEncConfig->EncQuality-1);
	#else
	#endif
	}
	else if(!strcmp(ConfigVideoEncToken,VIDEOENCODECONFIGTOKEN1))
	{
	#if 0
		IPCAM_VISetFrameRate(1 , lpVideoEncConfig->RateControl.FrameRateLimit);
		IPCAM_VISetBitRate(1 ,  lpVideoEncConfig->RateControl.BitrateLimit);
		IPCAM_VISetQLevel(1,  lpVideoEncConfig->EncQuality-1);
	#else
	#endif
	}
	
      return TRUE;
}

BOOL TachPtz(CHAR *MediaProfileToken, CHAR *PtzConfigToken) //
{
    if (MediaProfileToken == NULL)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL UnTachPtz(CHAR *MediaProfileToken)//?
{
    int ret = 0;
    if (MediaProfileToken == NULL)
    {
        return FALSE;
    }
    ret = IsValidToken(MediaProfileToken, Token);
    if (ret < 0)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL GetStreamURL(CHAR *MediaProfileToken, LPMEDIAURL lpMediaURL)
{
	char NetIp[64] = {0};
	unsigned short NetRtspPort;
//	printf("============================GetStreamURL_=================================\n");
	//LPCFG_NETINFO pNetInfo = &(IPCAM_GetSystemContext()->ipcam_SysConfig->ConfigNet);
	
    int ret = 0;
    if (MediaProfileToken == NULL || lpMediaURL == NULL)
    {
        return FALSE;
    }
    ret = IsValidToken(MediaProfileToken, Token);
    if (ret < 0)
    {
        return FALSE;
    }
	//LPIPCAM_SYSCONTEXT SysContext = IPCAM_GetSystemContext();
	NetRtspPort = conf_get_int("/mnt/sif/port.conf", "NetRtspPort");		
	conf_get("/mnt/sif/net.cfg", "IPAddress",NetIp, 64);
	if(!strcmp(MediaProfileToken,TOKEN0))
	{	
		sprintf(lpMediaURL->MediaUri,"rtsp://%s:%d/1.3gp",NetIp, NetRtspPort);
		//sprintf(lpMediaURL->MediaUri,"rtsp://%s:%d/1.3gp",SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr, SysContext->ipcam_SysConfig->ConfigNet.NetRtspPort);
	//	printf("main============================================%s\n",lpMediaURL->MediaUri);
	}
	else
	{
		//sprintf(lpMediaURL->MediaUri,"rtsp://%s:%d/2.3gp",SysContext->ipcam_SysConfig->ConfigNet.NetIpAddr, SysContext->ipcam_SysConfig->ConfigNet.NetRtspPort);		
		sprintf(lpMediaURL->MediaUri,"rtsp://%s:%d/2.3gp",NetIp, NetRtspPort);
   	//	printf("child============================================%s\n",lpMediaURL->MediaUri);
	}
//	printf("1010101010101010101010101010010101001010100101010100101010\n");
//	strncpy(lpMediaURL->Timeout,"PT60S",OVFCHARLENTH);
   lpMediaURL->InvalidAfterConnect = FALSE;
   lpMediaURL->InvalidAfterReboot = FALSE;
   strncpy(lpMediaURL->Timeout,"PT10S",OVFCHARLENTH);
    return TRUE;
}

BOOL GetSnapshotURL(CHAR *MediaProfileToken, LPMEDIAURL lpMediaURL)
{   
	//  printf("=====================================GetSnapshotURL=============================\n");
    int ret = 0;
    if (MediaProfileToken == NULL || lpMediaURL == NULL)
    {
        return FALSE;
    }
    ret = IsValidToken(MediaProfileToken, Token);
    if (ret < 0)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL MulticastStreamingStart(CHAR *MediaProfileToken)
{   
	//   printf("=====================================MulticastStreamingStart=============================\n");
    int ret = 0;
    if (MediaProfileToken == NULL)
    {
        return FALSE;
    }
    ret = IsValidToken(MediaProfileToken, Token);
    if (ret < 0)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL MulticastStreamingStop(CHAR *MediaProfileToken)
{  
	  //printf("=====================================MulticastStreamingStop=============================\n");
    int ret = 0;
    if (MediaProfileToken == NULL)
    {
        return FALSE;
    }
    ret = IsValidToken(MediaProfileToken, Token);
    if (ret < 0)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL SetSynchronizationPoint(CHAR *MediaProfileToken)
{
    int ret = 0;
    if (MediaProfileToken == NULL)
    {
        return FALSE;
    }
    ret = IsValidToken(MediaProfileToken, Token);
    if (ret < 0)
    {
        return FALSE;
    }
    return TRUE;
}


CALLBACKMEDIA   g_CallBackMedia = {0};

VOID InitCallBackMedia()
{   
	//  printf("=====================================InitCallBackMedia start=============================\n");
    g_CallBackMedia.GetProfileCap = GetProfileCap;
    g_CallBackMedia.GetProfiles   = GetProfiles;
    g_CallBackMedia.GetProfile    = GetProfile;

    g_CallBackMedia.GetAudioSources             = GetAudioSources;
    g_CallBackMedia.GetAudioSourceConfigs       = GetAudioSourceConfigs;
    g_CallBackMedia.GetAudioSourceConfigOptions = GetAudioSourceConfigOptions;
    g_CallBackMedia.GetAudioSourceConfig        = GetAudioSourceConfig;
    g_CallBackMedia.SetAudioSourceConfig        = SetAudioSourceConfig;

    g_CallBackMedia.GetAudioOutputs             = GetAudioOutputs;
    g_CallBackMedia.GetAudioOutputConfigs       = GetAudioOutputConfigs;
    g_CallBackMedia.GetAudioOutputConfigOptions = GetAudioOutputConfigOptions;
    g_CallBackMedia.GetAudioOutputConfig        = GetAudioOutputConfig;
    g_CallBackMedia.SetAudioOutputConfig        = SetAudioOutputConfig;

    g_CallBackMedia.GetAudioEncConfigs       = GetAudioEncConfigs;
    g_CallBackMedia.GetAudioEncConfigOptions = GetAudioEncConfigOptions;
    g_CallBackMedia.GetAudioEncConfig        = GetAudioEncConfig;
    g_CallBackMedia.SetAudioEncConfig        = SetAudioEncConfig;

    g_CallBackMedia.GetAudioDecConfigs        = GetAudioDecConfigs;
    g_CallBackMedia.GetAudioDecConfigsOptions = GetAudioDecConfigsOptions;
    g_CallBackMedia.GetAudioDecConfig         = GetAudioDecConfig;
    g_CallBackMedia.SetAudioDecConfig         = SetAudioDecConfig;

    g_CallBackMedia.GetVideoSources             = GetVideoSources;
    g_CallBackMedia.GetVideoSourceConfigs       = GetVideoSourceConfigs;
    g_CallBackMedia.GetVideoSourceConfigOptions = GetVideoSourceConfigOptions;
    g_CallBackMedia.GetVideoSourceConfig        = GetVideoSourceConfig;
    g_CallBackMedia.SetVideoSourceConfig        = SetVideoSourceConfig;

    g_CallBackMedia.GetVideoEncConfigs       = GetVideoEncConfigs;
    g_CallBackMedia.GetVideoEncConfigOptions = GetVideoEncConfigOptions;
    g_CallBackMedia.GetVideoEncConfig        = GetVideoEncConfig;
    g_CallBackMedia.SetVideoEncConfig        = SetVideoEncConfig;

    g_CallBackMedia.TachPtz   = TachPtz;
    g_CallBackMedia.UnTachPtz = UnTachPtz;

    g_CallBackMedia.GetStreamURL            = GetStreamURL;
    g_CallBackMedia.GetSnapshotURL          = GetSnapshotURL;
    g_CallBackMedia.MulticastStreamingStart = MulticastStreamingStart;
    g_CallBackMedia.MulticastStreamingStop  = MulticastStreamingStop;
    g_CallBackMedia.SetSynchronizationPoint = SetSynchronizationPoint;
    
  //  printf("=====================================InitCallBackMedia end=============================\n");
}
#endif

