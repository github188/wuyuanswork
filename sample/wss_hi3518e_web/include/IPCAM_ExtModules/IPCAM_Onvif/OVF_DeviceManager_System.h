//OVF_DeviceManager_System.h
/*################################################################################
#Project Description:
#      OVIF 协议SDK
#
# The File Description:
#      OVIF 协议 设备管理.系统管理
# Note:
#      1.
#
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_DEVICEMAGER_SYSTEM_H
#define OVF_DEVICEMAGER_SYSTEM_H

typedef enum 
{LOGTYPEOVF_SYSTEM      = 0,                               //系统
 LOGTYPEOVF_ACCESS      = 1,                               //访问记录
 }LOGTYPE;                                              //LOG
typedef enum 
{FACTORY_DEFAULT_HARD= 0,                               //硬件
 FACTORY_DEFAULT_SOFT= 1,                               //软件
}ENU_FACTORYDEFFAULT;                                   //恢复默认配置
typedef enum
{SETDTTYPE_MANUAL    = 0,                               //手工
 SETDTTYPE_NTP       = 1                                //NTP
}ENU_SETDTTYPE;                                         //时间配置类型

typedef struct tagATTACHMENTDATA
{
	CHAR             fiName[OVFCHARLENTH];
	CHAR            *Data;	                              //xmime contentType 规格数据(注意:此数据需要调用者静态分配)
}ATTACHMENTDATA,*LPATTACHMENTDATA;

typedef struct tagBACKUPFILES
{
    INT              nFiles;
    ATTACHMENTDATA   BackupFile[5];
}BACKUPFILES,*LPBACKUPFILES;
typedef struct tagSYSTEMLOGS
{ 
    ATTACHMENTDATA   LogFile;
}SYSTEMLOGS,*LPSYSTEMLOGS,
 SUPORTINFO,*LPSUPORTINFO;

typedef struct tagDEVICEINFO
{
	CHAR              DevManufacturer[OVFCHARLENTH];       //厂家信息
	CHAR              DevModel[OVFCHARLENTH];	           //型号
    CHAR              DevFirmwareVersion[OVFCHARLENTH];    //Firmware版本
	CHAR              DevSerialNumber[OVFCHARLENTH];	   //系列号
	CHAR              DevHardwareId[OVFCHARLENTH];	       //设备ID号
}DEVICEINFO,*LPDEVICEINFO;
typedef struct tagDATETIMES
{
    INT               Year;
    INT               Month;
    INT               Date;
    INT               Hour;
    INT               Minute;
    INT               Second;
}DATETIMES;
typedef struct tagDATATIME
{
	ENU_SETDTTYPE     SetDateTimeType;
	BOOL              IsDaylightSavings;
	CHAR              TimeZone[OVFCHARLENTH];
	DATETIMES         UTCDateTime;                           //国际标准时间
	//仅读取
    DATETIMES         LocalTime;                   
}DATETIME,*LPDATETIME;
typedef struct tagUPGRADE
{
	CHAR              UploadUri[OVFCHARLENTH];
	CHAR              UploadDelay[OVFCHARLENTH];             //延时
	CHAR              ExpectedDownTime[OVFCHARLENTH];        //异常中断时间
}UPGRADE,*LPUPGRADE;
typedef struct tagRESTORESYSTEM
{
	CHAR              UploadUri[OVFCHARLENTH];	
	CHAR              ExpectedDownTime[OVFCHARLENTH];
}RESTORESYSTEM,*LPRESTORESYSTEM;
#endif//OVF_DEVICEMAGER_SYSTEM_H
//


