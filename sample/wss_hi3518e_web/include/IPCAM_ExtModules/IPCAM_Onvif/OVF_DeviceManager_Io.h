//OVF_DeviceManager_io.h
/*################################################################################
#Project Description:
#      OVIF 协议SDK
#
# The File Description:
#      OVIF 协议 设备管理.关联IO
# Note:
#      1.OVIF 似乎没有定义输入的关联IO.
#
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_DEVICEMANAGER_IO_H
#define OVF_DEVICEMANAGER_IO_H
typedef enum 
{IO_RELAYSTATE_CLOSE      = 0 ,
 IO_RELAYSTATE_OPEN       = 1 ,
}ENU_IORELAYSTATE;
typedef enum 
{IO_RELAYMODE_MONOST      = 0 ,
 IO_RELAYMODE_BIST        = 1 ,
}ENU_IORELAYMODE;
typedef enum 
{IO_RELAYLOGIC_ACT        = 0 ,
 IO_RELAYLOGIC_INACT      = 1 ,
}ENU_IORELAYLOGIC;

typedef struct tagRELAYOUTPUTSET
{
	ENU_IORELAYMODE   IoRelayMode;
	CHAR              IoDelayTime[OVFCHARLENTH];
	ENU_IORELAYMODE   IoIdleState;	
}IORELAYOUTPUTSET,*LPIORELAYOUTSET;
typedef struct tagRELAYOUTPUT
{
	CHAR              IoRelayouttoken[OVFCHARLENTH];
	IORELAYOUTPUTSET  IoRelayoutputSet;	
}IORELAYOUTPUT,*LPIORELAYOUTPUT;
typedef struct tagRELAYOUTPUTSETS
{
    INT               IoRelayOutSize;
    IORELAYOUTPUT     IoRelayOutputs[OVFMAXCHANNEL];
}IORELAYOUTPUTS,*LPIORELAYOUTPUTS;


#endif//OVF_DEVICEMANAGER_IO_H


