//OVF_Imaging.h
/*################################################################################
#Project Description:
#      OVIF 协议SDK
#
# The File Description:
#      OVIF SDK 摄像头管理
# Note:
#      1.OVIF 定义的摄像头管理部门除摄像头(传感器)静态参数外，还包含摄像头聚焦移动操作。
#
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_IMAGING_H
#define OVF_IMAGING_H

typedef enum 
{ST_FOCUSMOV_IDLE           = 0, 
 ST_FOCUSMOV_MOVING         = 1,
 ST_FOCUSMOV_UNKNOWN        = 2
}ENU_FOCUSMOVSTATUS;                                   //聚焦移动状态          


typedef enum 
{MODE_AUTOFOCUS_AUTO        = 0,
 MODE_AUTOFOCUS_MANUAL      = 1
 }ENU_AUTOFOCUSMODE;                                   //对焦模式

typedef enum  
{MODE_WIDEDYNAMIC_OFF       = 0,
 MODE_WIDEDYNAMIC_ON        = 1
}ENU_WIDEDYNAMICMODE;                                  //宽动态模式



typedef enum 
{MODE_BACKLIGTHCOMP_OFF     = 0,
 MODE_BACKLIGTHCOMP_ON      = 1
 }ENU_BACKLIGHTCOMPMODE;                               //背光补偿


typedef enum 
{MODE_EXPOSUREPRIT_LOWNOISE = 0,                       //低噪声
 MODE_EXPOSUREPRIT_FPS      = 1                        //固定帧率
 }ENU_EXPOSUREPRITMODE;                                //曝光优先方式

typedef enum 
{MODE_EXPOSURE_AUTO         = 0,
 MODE_EXPOSURE_MANUAL       = 1
}ENU_EXPOSUREMODE;                                     //曝光模式

typedef enum 
{ WHITEBALANCE_MODE_AUTO    = 0,
  WHITEBALANCE_MODE_MANUAL  = 1
}ENU_WHITEBALANCEMODE;                                 //白平衡模式

typedef enum 
{IRCUT_MODE_ON              = 0,
 IRCUT_MODE_OFF             = 1,
 IRCUT_MODE_AUTO            = 2,
}ENU_IRCUTMODE;                                        //IR CUT 模式




typedef struct tagOPTIONSEXPOSURE
{
	INT                      ExpoModeSize;	    
	ENU_EXPOSUREMODE         ExpoModes[5];	           //曝光模式
	INT                      ExpoPriSize;	
	ENU_EXPOSUREPRITMODE     ExpoPris[5];              //曝光优先模式
    FLOATRANGE               ExpoMinTime;	           //曝光时间
	FLOATRANGE               ExpoMaxTime;	
	FLOATRANGE               ExpoMinGain;	           //增益
	FLOATRANGE               ExpoMaxGain;	
	FLOATRANGE               ExpoMinIris;	           //光圈
	FLOATRANGE               ExpoMaxIris;	
	FLOATRANGE               ExpoTime;	 
	FLOATRANGE               ExpoGain;	
	FLOATRANGE               ExpoIris;	
}OPTIONSEXPOSURE;
typedef struct tagOPTIONSFOCUS                          //聚焦配置
{
    INT                      FocusModeSize;	
	ENU_AUTOFOCUSMODE        FocusModes[5];	            //聚焦模式
	FLOATRANGE               FocusDefaultSpeed;
	FLOATRANGE               FocusNearLimit;	
	FLOATRANGE               FocusFarLimit;	
}OPTIONSFOCUS;
typedef struct tagOPTIONSWIDEDYNAMIC
{
	INT                      wdModeSize;
	ENU_WIDEDYNAMICMODE      wdModes[5];
	FLOATRANGE               wdLevel;	
}OPTIONSWIDEDYNAMIC;
typedef struct tagOPTIONSWHITEBALANCE
{
	INT                      wbModeSize;	
	ENU_WHITEBALANCEMODE     wbModes[5];	
	FLOATRANGE               wbYrGain;	                  //亮差增益
	FLOATRANGE               wbYbGain;	                  //色差增益
}OPTIONSWHITEBALANCE;
typedef struct tagOPTIONSIMAGINGS
{
    //以下定义为范围模式，在设置或获取单个设备句柄时使用低位。
    FLOATRANGE               ImgBrightnessRange;          //亮度
    FLOATRANGE               ImgColorSaturationRange;     //色度
    FLOATRANGE               ImgContrastRange;            //对比度
	FLOATRANGE               ImgSharpness;	              //锐度

	INT                      IrCutModeSize;
	ENU_IRCUTMODE            IrCutFilterModes[5];          //配置和读取时使用最低位。
    //以下CCD/CMOS/镜头参数从没见使用，此处定义保留   
    INT                      BacklightCompSize;
    ENU_BACKLIGHTCOMPMODE    BacklightCompMode[5];
    FLOATRANGE               BacklightCompRange;           //背光补偿
    OPTIONSEXPOSURE          OptionsExposure;              //快门
	OPTIONSFOCUS             OptionsFocus;	               //聚焦
	OPTIONSWIDEDYNAMIC       OptionsWideDynamic;	       //宽动态
	OPTIONSWHITEBALANCE      OptionsWhiteBalance;	       //白平衡
}OPTIONSIMAGINGS,*LPOPTIONSIMAGINGS;

typedef struct tagOPTIONSFOCUSMOV
{
    FLOATRANGE               AbsolutePosition;	
	FLOATRANGE               AbsoluteSpeed;	

	FLOATRANGE               RelativeDistance;	
	FLOATRANGE               RelativeSpeed;	

	FLOATRANGE               ContinuousSpeed;

}OPTIONSFOCUSMOV,*LPOPTIONSFOCUSMOV;
typedef struct tagFOCUSMOVSTATUS
{
	FLOAT                    FocusPosition;
	ENU_FOCUSMOVSTATUS       FocusMoveStatus;
	CHAR                     FocusError;	
}FOCUSMOVSTATUS,*LPFOCUSMOVSTATUS;
//回调接口
typedef struct  tagCALLBACKIMAGING
{   //图像.图像像质和传感器参数
	void (*SetIcut)                     (int mode);
	BOOL  (*ImgGetOptions)             (CHAR *VideoSourceToken,LPOPTIONSIMAGINGS lpOptionsImagings);
    BOOL  (*ImgGetSetting)             (CHAR *VideoSourceToken,LPOPTIONSIMAGINGS lpImgSetting);                        //使用配置区域结构的mix 字段
    BOOL  (*ImgSetSetting)             (CHAR *VideoSourceToken,LPOPTIONSIMAGINGS   ImgSetting,BOOL isFoce2Persistence);//使用配置区域结构的mix 字段
    //图像.镜头聚焦(IPCAM极少自带镜头控制，以下定义保留)
    BOOL  (*MovFocusGetOptions)        (CHAR *VideoSourceToken,LPOPTIONSFOCUSMOV lpFocusMovOptions);                   //使用配置区域结构的mix 字段
    BOOL  (*MovFocusMove)              (CHAR *VideoSourceToken,LPOPTIONSFOCUSMOV   FocusMovOptions);                   //使用配置区域结构的mix 字段
    BOOL  (*MovFocusStop)              (CHAR *VideoSourceToken);
    BOOL  (*MovFocusGetStatus)         (CHAR *VideoSourceToken, LPFOCUSMOVSTATUS lpFocusMovStatus);
    
}CALLBACKIMAGING,*LPCALLBACKIMAGING;
#endif//OVF_IMAGING_H

