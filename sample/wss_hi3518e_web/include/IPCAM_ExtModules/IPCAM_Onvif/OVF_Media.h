//OVF_Media.h
/*################################################################################
#Project Description:
#      OVIF 协议SDK
#
# The File Description:
#      OVIF SDK PTZ操作
# Note:
#      1.OVIF 定义的Stream 是已令牌环方式完成句柄操作。
#      2.Stream 句柄下可挂Imaging /ptz 等句柄(令牌环)，实际上PTZ的操作是透过Stream来完成。
#      3.OVIF 声明的Timeout 都是CHAR*类型的，没有明确定义其格式规范
#      
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_MEDIA_H
#define OVF_MEDIA_H
typedef enum                                            //OVIF协议声明支持的音频编码
{ 
    AUDIOENC_G711        = 0,
    AUDIOENC_G726        = 1,
    AUDIOENC_AAC         = 2
}ENU_AUDIOENCTYPE;
typedef enum                                            //OVIF协议声明支持的视频编码
{
    VIDEOENC_JPEG        = 0, 
    VIDEOENC_MPEG4       = 1,
    VIDEOENC_H264        = 2,
 }ENU_VIDEOENCTYPE;

typedef enum 
{
    MP4PROFILE_SP        = 0,
    MP4PROFILE_ASP       = 1
}ENU_MP4PROFILE;

typedef enum 
{
    H264PROFILE_BASELINE = 0,
    H264PROFILE_MAIN     = 1,
    H264PROFILE_EXTENDED = 2,
    H264PROFILE_HIGH     = 3,
}ENU_H264PROFILE;

typedef struct tagAUDIOSOURCE                            //音频输入源,输出节点
{
	CHAR            AudioToken[OVFCHARLENTH];            //令牌
    INT             Channels;	                         //声道数
}AUDIONODE,*LPAUDIONODE;                          
typedef struct tagAUDIOSOURCES                           //音频输入源组
{
    INT             AudioNodeSize;
    AUDIONODE       AudioNodes[16];                      //最多定义16个声音输入通道
}AUDIONODES,*LPAUDIONODES;   
typedef struct tagAUDIOCONFIG
{
	CHAR           ConfigName[OVFCHARLENTH];
	INT            ConfigUseCount;	
	CHAR           ConfigToken[OVFCHARLENTH];	
	CHAR           AudioNodeToken[OVFCHARLENTH];
	BOOL           ForcePersistence;                     //开机默认
    //输出独有
    CHAR           AudioOutputSendPrimacy[OVFCHARLENTH]; //输出模式:全工半工模式定义为URL (OVIF 文档声明数种联机方式，但相关文档无法打开)
    INT            AudioOutputLevel;                     //输出音量
}AUDIOCONFIG,*LPAUDIOCONFIG;
typedef struct tagAUDIOCONFIGS
{
    INT               ConfigSize;
    AUDIOCONFIG       Configs[16];
}AUDIOCONFIGS,*LPAUDIOCONFIGS;
typedef struct tagAUDIOSOURCECONFIGOPTIONS
{
	INT              AudioNodeTokensAvailableSize;	
	CHAR             AudioNodeTokensAvailable[16][OVFCHARLENTH];	
    //输出独有
    INT              OutputSendPrimacyOptionsSize;	
	CHAR             OutputSendPrimacyOptions[16][OVFCHARLENTH];
	INTRANGE         OutputLevelRange;	
 }AUDIOCONFIGOPTIONS,*LPAUDIOCONFIGOPTIONS;
typedef struct tagMULTICASTCONFIG
{
	IPV4ADDRESS           Address;
	INT                   Port;
	INT                   TTL;	
	BOOL                  AutoStart;	                  //开机自动
}MUTICASTCONFIG;
typedef struct tagAUDIOCODINGCONFIG
{
	CHAR                  ConfigName[OVFCHARLENTH];
	INT                   ConfigUseCount;
	CHAR                  Configtoken[OVFCHARLENTH];	
    //以下定义仅对编码端
	ENU_AUDIOENCTYPE      AudioEncType;	
	INT                   AudioEncBitrate;	
	INT                   AudioEncSampleRate;	
	MUTICASTCONFIG        Multicast;	
	CHAR                  RTSPSessionTimeout[OVFCHARLENTH];	
    //以下定义仅对设置
    BOOL                  ForcePersistence;
}AUDIOCODINGCONFIG,*LPAUDIOCODINGCONFIG;
typedef struct tagAUDIOCODINGCONFIGS
{
    INT                   ConfigSize;
    AUDIOCODINGCONFIG     ConfigEncs[16];
}AUDIOCODINGCONFIGS,*LPAUDIOCODINGCONFIGS;
typedef struct tagAUDIOENCCONFIGOPTION
{
	ENU_AUDIOENCTYPE       EncType;	
	INTLIST                EncBitrateList;
	INTLIST                EncSampleRateList;	
}AUDIOENCCONFIGOPTION,*LPAUDIOENCCONFIGOPTION;
typedef struct tagAUDIOENCCONFIGOPTIONS
{
    INT                    AudioEncConfigOptionSize;
    AUDIOENCCONFIGOPTION   AudioEncConfigOption[OVFMAXCHANNEL];
}AUDIOENCCONFIGOPTIONS,*LPAUDIOENCCONFIGOPTIONS;
typedef struct tagAUDIODECOPTON
{
	INTLIST                DecOptionBitrate;	
	INTLIST                DecOptonSampleRateRange;	
}AUDIODECOPTION;
typedef struct tagAUDIODECCONFIGOPTION
{
    AUDIODECOPTION         AACDecOptions;	
	AUDIODECOPTION         G711DecOptions;	
	AUDIODECOPTION         G726DecOptions;	   
}AUDIODECCONFIGOPTION,*LPAUDIODECCONFIGOPTON;
typedef struct tagAUDIODECCONFIGOPTIONS
{
    INT                     AudioDecConfigOptionSize;
    AUDIODECCONFIGOPTION    AudioDecConfigOptions[OVFMAXCHANNEL];
}AUDIODECCONFIGOPTIONS,*LPAUDIODECCONFIGOPTIONS;
//视频结构
typedef struct tagRESOLUTION
{
	INT                      Width;	
	INT                      Height;
}RESOLUTION;
typedef struct tagVIDEOSOURCE
{
	CHAR                     VideoToken[OVFCHARLENTH];	
	FLOAT                    VideoSourceFramerate;	
	RESOLUTION               VideoSourceResolution;	
	/////原ONVIF定义有图像及传感器参数，因IMGING部分已有定义及API，此处省略	
}VIDEOESOURCE,*LPVIDEOSOURCE;
typedef struct tagVIDEOSOURCES
{
    INT                      VideoSourceSize;
    VIDEOESOURCE             VideoSources[OVFMAXCHANNEL];
}VIDEOSOURCES,*LPVIDEOSOURCES;
typedef struct tagVIDEOSOURCECONFIG
{
	CHAR                     ConfigName[OVFCHARLENTH];	
	INT                      ConfigUseCount;	
	CHAR                     ConfigToken[OVFCHARLENTH];	
	CHAR                     SourceToken[OVFCHARLENTH];	
    INTRECT                  SourceBounds;	
	//仅设置时使用
	INT                      ForcePersistence;
}VIDEOSOURCECONFIG,*LPVIDEOSOURCECONFIG;
typedef struct tagVIDEOSOURCECONFIGS
{
    INT                      ConfigSize;
    VIDEOSOURCECONFIG        VideoSourceConfigs[OVFCHARLENTH];
}VIDEOSOURCECONFIGS,*LPVIDEOSOURCECONFIGS;
typedef struct tagVIDEOSOURCECONFIGOPTIONS
{
	INTRECTRANGE             BoundsRange;	
	INT                      VideoSourceTokenSize;	
	CHAR                     VideoSourceTokens[OVFMAXCHANNEL][OVFCHARLENTH];	
}VIDEOSOURCECONFIGOPTIONS,*LPVIDEOSOURCECONFIGOPTIONS;


typedef struct tagVIDEORATECONTROL
{
	INT                      FrameRateLimit;	
	INT                      EncodingInterval;	
	INT                      BitrateLimit;	
}VIDEORATECONTROL;

typedef struct tagMP4CONFIG
{
	INT                      GovLength;	
	ENU_MP4PROFILE           Mpeg4Profile;	
}MP4CONFIG;

typedef struct tagAVSCONFIG
{
	INT                      GovLength;	
	ENU_H264PROFILE          H264Profile;	
}AVSCONFIG;
typedef struct tagVIDEOENCCONFIG
{
	CHAR                     ConfigName[OVFCHARLENTH];
	INT                      ConfigUseCount;	
	CHAR                     ConfigToken[OVFCHARLENTH];
	ENU_VIDEOENCTYPE         EncType;	
	RESOLUTION               EncResolution;
	FLOAT                    EncQuality;	
	VIDEORATECONTROL         RateControl;	
	MP4CONFIG                ConfigMPEG4;	
	AVSCONFIG                ConfigH264;	
	MUTICASTCONFIG           Multicast;	
	CHAR                     RtspSessionTimeout[OVFCHARLENTH];
	//仅设置
	BOOL                     ForcePersistence;
}VIDEOENCCONFIG,*LPVIDEOENCCONFIG;
typedef struct tagVIDEOENCCONFIGS            //视频.编码.配置
{
    INT                      VideoEncConfigSize;
    VIDEOENCCONFIG           VideoEncConfigs[OVFCHARLENTH];
}VIDEOENCCONFIGS,*LPVIDEOENCCONFIGS;  
typedef struct tagJPEGOPTIONS
{
	INT                      ResolutionsAvailableSize;
	RESOLUTION               ResolutionsAvailable[OVFMAXCHANNEL];
	INTRANGE                 FrameRateRange;	
	INTRANGE                 EncodingIntervalRange;
}JPEGOPTIONS;
typedef struct tagMP4OPTIONS
{
	INT                      ResolutionsAvailableSize;	
	RESOLUTION               ResolutionsAvailables[OVFMAXCHANNEL];
	INTRANGE                 GovLengthRange;
	INTRANGE                 FrameRateRange;
	INTRANGE                 EncodingIntervalRange;
	INT                      Mpeg4ProfilesSupportedSize;
	ENU_MP4PROFILE           Mpeg4ProfilesSupported[OVFMAXCHANNEL];	
}MP4OPTIONS;
typedef struct tagAVSOPTIONS
{
	INT                      ResolutionsAvailableSize;	
	RESOLUTION               ResolutionsAvailables[OVFMAXCHANNEL];
	INTRANGE                 GovLengthRange;
	INTRANGE                 FrameRateRange;
	INTRANGE                 EncodingIntervalRange;
	INT                      AVSProfilesSupportedSize;
	ENU_H264PROFILE          AVSProfilesSupporteds[OVFMAXCHANNEL];
}AVSOPTIONS;
typedef struct tagVIDEOENCCONFIGOPTIONS
{
	INTRANGE                 EncQualityRange;
	JPEGOPTIONS              EncJpegOptions;
	MP4OPTIONS               EncMP4Options;	
	AVSOPTIONS               EncAVSOptions;
}VIDEOENCCONFIGOPTONS,*LPVIDEOENCCONFIGOPTIONS;
typedef struct tagMEDIAURL
{
	CHAR                     MediaUri[OVFCHARLENTH];	
	BOOL                     InvalidAfterConnect;	
	BOOL                     InvalidAfterReboot;	
	CHAR                     Timeout[OVFCHARLENTH];	
}MEDIAURL,*LPMEDIAURL;
//PROFILE 相关
typedef struct tagMEDIAPROFILE
{
	CHAR                      Name[OVFCHARLENTH];	
	CHAR                      token[OVFCHARLENTH]; 
	BOOL                      fixed; 
    //以下为为各个模块套入结构，OVIF有详细定义各个结构，
    //但各结构已定义独立API，这里仅保留各操作的令牌
    CHAR                      VideoSourceConfigToken[OVFCHARLENTH];
    CHAR                      VideoEncodeConfigToken[OVFCHARLENTH];
    CHAR                      AudioSourceConfigToken[OVFCHARLENTH];
    CHAR                      AudioEncodeConfigToken[OVFCHARLENTH];
    CHAR                      PtzConfigToken[OVFCHARLENTH];
   
}MEDIAPROFILE,*LPMEDIAPROFILE;
typedef struct tagMEDIAPROFILES
{
    INT                       ProfileSize;
    MEDIAPROFILE              ProFiles[OVFMAXCHANNEL];
}MEDIAPROFILES,*LPMEDIAPROFILES;
typedef struct tagMEDIAPROFILECAP
{
    INT                       MaxProfiles;
    BOOL                      RTPMulticast;	            //RTP多播:FALSE
	BOOL                      RTP_USCORETCP;	        //RTP TCP负载:TRUE
	BOOL                      RTP_USCORERTSP_USCORETCP;	//支持RTP/RTSP/TCP:TRUE
	BOOL                      NonAggregateControl;	    //可能是指多线连接:TRUE
}MEDIAPROFILECAP,*LPMEDIAPROFILECAP;
//回调接口
typedef struct  tagCALLBACKMEDIA
{   //媒体.profile
    BOOL  (*GetProfileCap)                 (LPMEDIAPROFILECAP lpMediaProfileCap);
	BOOL  (*GetProfiles)                   (LPMEDIAPROFILES lpMediaProfiles);
    BOOL  (*GetProfile)                    (CHAR *MediaProfileToken,LPMEDIAPROFILE lpMediaProfile);  
	BOOL  (*CreateProfile)                 (LPMEDIAPROFILE   MediaProfile);
	BOOL  (*DelProfile)                    (LPMEDIAPROFILE   MediaProfile);
    //媒体.音频.输入.设备
    BOOL  (*GetAudioSources)               (LPAUDIONODES   lpAudioSources);
    BOOL  (*GetAudioSourceConfigs)         (LPAUDIOCONFIGS lpAudioSourceConfigs);
    BOOL  (*GetAudioSourceConfigOptions)   (CHAR *ConfigAudioSourceToken,CHAR *MediaProfileToken,LPAUDIOCONFIGOPTIONS lpAudioSourceConfigOptions);
    BOOL  (*GetAudioSourceConfig)          (CHAR *ConfigAudioSourceToken,LPAUDIOCONFIG lpAudioSourceConfig);
    BOOL  (*SetAudioSourceConfig)          (CHAR *ConfigAudioSourceToken,LPAUDIOCONFIG   AudioSourceConfig);
    //媒体.音频.输出.设备
    BOOL  (*GetAudioOutputs)               (LPAUDIONODES   lpAudioOutput);
    BOOL  (*GetAudioOutputConfigs)         (LPAUDIOCONFIGS lpAudioOutputs);
    BOOL  (*GetAudioOutputConfigOptions)   (CHAR *ConfigAudioOutputToken,CHAR *MediaProfileToken,LPAUDIOCONFIGOPTIONS lpAudioSourceConfigOptions);
    BOOL  (*GetAudioOutputConfig)          (CHAR *ConfigAudioOutputToken,LPAUDIOCONFIG lpAudioOutputConfig);
    BOOL  (*SetAudioOutputConfig)          (CHAR *ConfigAudioOutputToken,LPAUDIOCONFIG   AudioOutputConfig);  
    //媒体.音频.输入.编码
    BOOL  (*GetAudioEncConfigs)            (LPAUDIOCODINGCONFIGS lpAudioCodingConfigs);
    BOOL  (*GetAudioEncConfigOptions)      (CHAR *ConfigAudioEncToken,CHAR *MediaProfileToken,LPAUDIOENCCONFIGOPTIONS lpAudioEncConfigOptons);
    BOOL  (*GetAudioEncConfig)             (CHAR *ConfigAudioEncToken,LPAUDIOCODINGCONFIG lpAudioCodingConfig);
    BOOL  (*SetAudioEncConfig)             (CHAR *ConfigAudioEncToken,LPAUDIOCODINGCONFIG   AudioCodingConfig);
    //媒体.音频.输出.解码
    BOOL  (*GetAudioDecConfigs)            (LPAUDIOCODINGCONFIGS lpAudioCodingConfigs);
    BOOL  (*GetAudioDecConfigsOptions)     (CHAR *ConfigAudioDecToken,CHAR *MediaProfileToken,LPAUDIODECCONFIGOPTON lpAudioDecConfigOption);
    BOOL  (*GetAudioDecConfig)             (CHAR *ConfigAudioDecToken,LPAUDIOCODINGCONFIG lpAudioCodingConfig);
    BOOL  (*SetAudioDecConfig)             (CHAR *ConfigAudioDecToken,LPAUDIOCODINGCONFIG   AudioCodingConfig);
    //媒体.视频.输入.设备
    BOOL  (*GetVideoSources)               (LPVIDEOSOURCES  lpVideoSources);
    BOOL  (*GetVideoSourceConfigs)         (LPVIDEOSOURCECONFIGS lpVideoSourcesConfigs);
    BOOL  (*GetVideoSourceConfigOptions)   (CHAR *ConfigVideoSourceToken,CHAR *MediaProfileToken,LPVIDEOSOURCECONFIGOPTIONS lpVideoSourceConfigOptions);
    BOOL  (*GetVideoSourceConfig)          (CHAR *ConfigVideoSourceToken,LPVIDEOSOURCECONFIG lpVideoSourceConfig);
    BOOL  (*SetVideoSourceConfig)          (CHAR *ConfigVideoSourceToken,LPVIDEOSOURCECONFIG   VideoSOurceConfig);
    //媒体.视频.输入.编码
    BOOL  (*GetVideoEncConfigs)            (LPVIDEOENCCONFIGS lpVideoEncConfigs);
    BOOL  (*GetVideoEncConfigOptions)      (CHAR *ConfigVideoEncToken,CHAR *MediaProfileToken,LPVIDEOENCCONFIGOPTIONS lpVideoEncConfigOptions);
    BOOL  (*GetVideoEncConfig)             (CHAR *ConfigVideoEncToken,LPVIDEOENCCONFIG lpVideoEncConfig);
    BOOL  (*SetVideoEncConfig)             (CHAR *ConfigVideoEncToken,LPVIDEOENCCONFIG   VideoEncConfig);
    //媒体.关联云台
    BOOL  (*TachPtz)                       (CHAR *MediaProfileToken,CHAR *PtzConfigToken);
    BOOL  (*UnTachPtz)                     (CHAR *MediaProfileToken);
    //媒体.流
    BOOL  (*GetStreamURL)                  (CHAR *MediaProfileToken,LPMEDIAURL lpMediaURL);
    BOOL  (*GetSnapshotURL)                (CHAR *MediaProfileToken,LPMEDIAURL lpMediaURL);
    BOOL  (*MulticastStreamingStart)       (CHAR *MediaProfileToken);
    BOOL  (*MulticastStreamingStop)        (CHAR *MediaProfileToken);
    BOOL  (*SetSynchronizationPoint)       (CHAR *MediaProfileToken);      
    //媒体.音频输入输出，视频输入输出兼容配置 (保留)
    //媒体.视频分析接口                       (保留)
    //媒体.音频，视频元数据接口               (保留)
}CALLBACKMEDIA,*LPCALLBACKMEDIA;
#endif//OVF_MEDIA_H

