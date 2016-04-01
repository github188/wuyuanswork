//OVF_GLOBAL.H
/*################################################################################
#Project Description:
#      OVIF 协议SDK
#
# The File Description:
#      OVIF 协议 预定义头
# Note:
#      
#
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_GLOBAL_H
#define OVF_GLOBAL_H

//////////
#ifndef INT 
#define INT int
#endif//INT
#ifndef UINT
#define UINT unsigned int
#endif//UINT
#ifndef CHAR
#define CHAR char
#endif//CHAR
#ifndef SHORT
#define SHORT short
#endif//SHORT
#ifndef USHORT
#define USHORT unsigned short
#endif//USHORT
#ifndef BOOL
#define BOOL int
#endif//BOOL
#ifndef NULL
#define NULL (void*)0
#endif//NULL
#ifndef VOID
#define VOID void
#endif//VOID
#ifndef TRUE
#define TRUE 1
#endif//TRUE
#ifndef FALSE
#define FALSE 0
#endif//FALSE
#ifndef FLOAT
#define FLOAT float
#endif//FLOAT
#ifndef ULONG
#define ULONG unsigned long
#endif
//////////GLOBAL DEDFINE///////////
#ifndef HDOVF
#define HDOVF     void *
#endif//HDOVF
#ifndef SOCKETIN
#define SOCKETIN struct sockaddr_in 
#endif//SOCKETIN

#define OVFCHARLENTH            64                           //OVF大多数字窜长度为64
#define OVFBCHARLENTH			128
#define OVFMAXLEVEL             32                           //OVF定义的大多数级别不会超过32
#define OVFMAXCHANNEL           16                           //OVF定义单一设备最大通道16
#define IPCAMWSDEVICETYPE      "dn:NetworkVideoTransmitter"  //OVF IPCAM设备名称
#define DVRWSDEVICETYPE        " "
#define NVRWSDEVICETYPE        " "

typedef struct tagFLOATRANGE
{
	FLOAT Min;	
	FLOAT Max;	
}FLOATRANGE;
typedef struct tagINTRANGE
{ 
    INT  Min;
    INT  Max;
}INTRANGE;
typedef struct tagINTLIST
{
	INT   ItemsSize;
	INT   Items[OVFMAXLEVEL];
}INTLIST;
typedef struct tagINTRECT
{
	INT    x;	
	INT    y;	
    INT    width;	
	INT    height;	
}INTRECT;
typedef struct tagINTRECTRANGE
{
    INTRANGE  XRange;	
    INTRANGE  YRange;	
	INTRANGE  WidthRange;	
	INTRANGE  HeightRange;	
}INTRECTRANGE;
#endif//OVF_GLOBAL_H

