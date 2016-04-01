//OVF_PTZ.h
/*################################################################################
#Project Description:
#      OVIF 协议SDK
#
# The File Description:
#      OVIF SDK PTZ操作
# Note:
#      1.OVIF 定义的PTZ操作实际是挂在一个流的句柄上的。
#      2.OVIF 定义的PTZ移动方式都是按坐标方式移动，这点比较奇怪，但定义了一组辅助
#        命令接口(AuxComd)，或许可以使用该接口来做模糊移动,这种方式能否兼容，编写这
#        个文档时还没有条件可测试。
#      3.由于OVF 定义的移动方式不可用，因此这部分仅少量函数支持(注意函数标注)
#      4.OVIF 定义的PTZ操作无485硬件参数配置入口
#      5.OVIF 定义的PTZ操作无云台地址这个命名。
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_PTZ_H
#define OVF_PTZ_H

typedef enum 
{
 PTZMOV_IDLE     = 0, 
 PTZMOV_MOVING   = 1,
 PTZMOV_UNKNOWN  = 2
}ENU_PTZMOVSTATUS;                //PTZ移动状态  
typedef struct tagSPACE2DDESP
{
	CHAR         Space2dDespURL[OVFBCHARLENTH];
	FLOATRANGE   Space2dXRange;
	FLOATRANGE   Space2dYRange;
}SPACE2DDESP;                     //SPACE 2D 描述
typedef struct tagSPACE1DDESP
{
	CHAR         Space1dURI[OVFBCHARLENTH];	
	FLOATRANGE   Space1XRange;	
}SPACE1DDESP;                     //SPACE 1D 描述
typedef struct tagVECTOR2D
{
	FLOAT         x;	
	FLOAT         y;	
	CHAR          space[OVFBCHARLENTH];
}VECTOR2D;                        //vector 2d 描述

typedef struct tagVECTOR1D
{
	FLOAT         x;	
	CHAR          space[OVFBCHARLENTH];
}VECTOR1D;                        //vector 1d 描述
typedef struct tagPTZSpeed
{
	VECTOR2D      PanTilt;
    VECTOR1D      Zoom;	
}PTZSPEED ,*LPPTZSPEED,
 PTZVECTOR,*LPPTZVECTOR;
typedef struct tagPTZCONFIG
{
	CHAR          PtzCfgName[OVFCHARLENTH];
	INT           PtzCfgUseCount;	
	CHAR          PtzCfgToken[OVFCHARLENTH];
	CHAR          PtzCfgNodeToken[OVFCHARLENTH];
    //以下定义保留
	CHAR          DefAbsPantTiltPosSpace[OVFBCHARLENTH];
	CHAR          DefAbsZoomPosSpace[OVFBCHARLENTH];
	CHAR          DefRelativePanTiltTranslationSpace[OVFBCHARLENTH];
	CHAR          DefRelativeZoomTranslationSpace[OVFBCHARLENTH];	
	CHAR          DefContinuousPanTiltVelocitySpace[OVFBCHARLENTH];	
	CHAR          DefContinuousZoomVelocitySpace[OVFBCHARLENTH];	
	PTZSPEED      DefPTZSpeed;	
	CHAR          DefPTZTimeout[OVFCHARLENTH];
	SPACE2DDESP   LimitsPanTilt;	
	SPACE1DDESP   LimitsZoom;	
}PTZCONFIG,*LPPTZCONFIG;
typedef struct tagPTZCONFIGS
{
    INT           PtzCfgSize;
    PTZCONFIG     PtzCfgs[OVFMAXCHANNEL];
}PTZCONFIGS,*LPPTZCONFIGS;
typedef struct tagPTZSPACES
{
	INT           SizeAbsolutePanTiltPositionSpace;	
	SPACE2DDESP   AbsolutePanTiltPositionSpace[5];	
	INT           SizeAbsoluteZoomPositionSpace;	
	SPACE1DDESP   AbsoluteZoomPositionSpace[5];	
	INT           SizeRelativePanTiltTranslationSpace;	
	SPACE2DDESP   RelativePanTiltTranslationSpace[5];	
	INT           SizeRelativeZoomTranslationSpace;	
	SPACE1DDESP   RelativeZoomTranslationSpace[5];	
	INT           SizeContinuousPanTiltVelocitySpace;
	SPACE2DDESP   ContinuousPanTiltVelocitySpace[5];
	INT           SizeContinuousZoomVelocitySpace;
	SPACE1DDESP   ContinuousZoomVelocitySpace[5];
	INT           SizePanTiltSpeedSpace;
	SPACE1DDESP   PanTiltSpeedSpace[5];
	INT           SizeZoomSpeedSpace;
	SPACE1DDESP   ZoomSpeedSpace[5];	
}PTZSPACES;                           //PTZ 坐标空间
typedef struct tagPTZCONFIGOPTIONS
{
	PTZSPACES     Spaces;	
	FLOATRANGE    PTZTimeout;
}PTZCONFIGOPTIONS,*LPPTZCONFIGOPTIONS;    //PTZ 配置属性表
typedef struct tagPTZNODE
{
	CHAR         Nodetoken[OVFCHARLENTH];	
	CHAR         NodeName[OVFCHARLENTH];	
	INT          MaxPresets;	
	BOOL         HomeSupported;	
	INT          AuxCommandsSize;	
	CHAR         AuxCommands[OVFCHARLENTH][OVFCHARLENTH];
    //(以下保留)
    PTZSPACES    NodePTZSpaces;	                         
}PTZNODE,*LPPTZNODE;                      //PTZ 设备节点
typedef struct tagPTZNODES
{
    INT          NodeSize;
    PTZNODE      Nodes[OVFMAXCHANNEL];
}PTZNODES,*LPPTZNODES;                    //PTZ 设备节点组
typedef struct tagPTZPRESET
{
	CHAR        PresetName[OVFCHARLENTH];
    CHAR        PresetToken[OVFCHARLENTH];
    //以下定义保留
	PTZVECTOR   PresetPTZPosition;	
}PTZPRESET,*LPPTZPRESET;                 //PTZ 预设位
typedef struct tagPTZPRESETS
{
    INT         PresetSize;
    PTZPRESET   Presets[128];
}PTZPRESETS,*LPPTZPRESETS;                //PTZ 预设位组
typedef struct tagPTZSTATUS
{
	PTZVECTOR        Position;
    ENU_PTZMOVSTATUS PanTilt;
    ENU_PTZMOVSTATUS Zoom;
	CHAR             Error[OVFCHARLENTH];
	INT              UtcTime;
}PTZSTATUS,*LPPTZSTATUS;
//////////////////////////////PTZ接口//////////////////////////////////////////////////
typedef struct  tagCALLBACKPTZ
{
  //PTZ.配置
    BOOL    (*PtzGetConfigs)              (LPPTZCONFIGS lpPtzConfigs);
    BOOL    (*PtzGetConfig )              (CHAR * PtzConfigToken,LPPTZCONFIG  lpPtzConfig);  
    BOOL    (*PtzSetConfig )              (CHAR * PtzConfigToken,LPPTZCONFIG    PtzConfig); //(保留) 
    BOOL    (*PtzGetConfigOptions)        (LPPTZCONFIGOPTIONS lpPtzConfigOptions);          //(保留)     
  //PTZ.设备节点
    BOOL    (*PtzGetNodes)                (LPPTZNODES lpPtzNodes);
    BOOL    (*PtzGetNode )                (CHAR * PtzPtzNodeToken,LPPTZNODE PtzNode);
  //PTZ.预至位
    BOOL    (*PtzGetPresets)              (CHAR * MediaProfileToken,LPPTZPRESETS lpPtzPresets);
    BOOL    (*PtzSetPreset )              (CHAR * MediaProfileToken,CHAR *PresetToken,CHAR *PresetName);
    BOOL    (*PtzRemPreset )              (CHAR * MediaProfileToken,CHAR *PresetToken);
    BOOL    (*PtzGotoPreset)              (CHAR * MediaProfileToken,CHAR *PresetToken,LPPTZSPEED   PtzSpeed);//Speed为OVIF 定义实际运用无意义(下同)
    BOOL    (*PtzSetHomePosition)         (CHAR * MediaProfileToken);
    BOOL    (*PtzGotoHomePosition)        (CHAR * MediaProfileToken,LPPTZSPEED  PtzSpeed);
  //PTZ.移动 (所有相关函数保留)
    BOOL    (*PtzMovAbsolute)             (CHAR * MediaProfileToken,LPPTZVECTOR lpTranslation,LPPTZSPEED  PtzSpeed);
    BOOL    (*PtzMovRelative)             (CHAR * MediaProfileToken,LPPTZVECTOR lpPosition   ,LPPTZSPEED  PtzSpeed);
    BOOL    (*PtzMovContinuous)           (CHAR * MediaProfileToken,LPPTZSPEED  Velocity,CHAR * PtzTimeOut);
  //PTZ.附加命令
    BOOL    (*PtzSendAuxComd)             (CHAR * MediaProfileToken,CHAR * Command);
  //PTZ.停止
    BOOL    (*PtzStop)                    (CHAR * MediaProfileToken,BOOL IsStopPanTilt,BOOL IsStopRoom);
  //PTZ.状态 (所有相关函数保留)
    BOOL    (*PtzGetStatus)               (CHAR * MediaProfileToken,LPPTZSTATUS lpPtzStatus);
}CALLBACKPTZ,*LPCALLBACKPTZ;
#endif//OVF_PTZ_H

