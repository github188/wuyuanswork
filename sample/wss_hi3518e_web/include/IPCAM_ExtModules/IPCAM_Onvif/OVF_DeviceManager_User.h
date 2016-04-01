//OVF_DeviceManager_User.h
/*################################################################################
#Project Description:
#      OVIF 协议SDK
#
# The File Description:
#      OVIF 协议 设备管理.用户管理
# Note:
#      1.OVIF 对帐户管理的权限仅定义了5级，另定义一个远程帐户。
#
#
# Authors:
#       Fifo2005@gmail.com                                       2011.12.30 First
#       
#Copyright:
#       Copyright(c) 2008~2001x 
#  	    Fifo2005@gmail.com All rights reserved.
###############################################################################*/
#ifndef OVF_DEVICEMAGER_USER_H
#define OVF_DEVICEMAGER_USER_H
typedef enum 
{USER_LEVEL_ADMIN       = 0,
 USER_LEVEL_OPERATOR    = 1, 
 USER_LEVEL_USER        = 2,
 USER_LEVEL_ANONYMOUS   = 3,
 USER_LEVEL_EXTENDED    = 4,
}ENU_USERLEVEL;
typedef struct tagUSER
{
	CHAR          UserName[OVFCHARLENTH];	
	CHAR          UserPwd[OVFCHARLENTH];	
	ENU_USERLEVEL UserLevel;                //权限级别
}USER,LPUSER;
typedef struct tagUSERS
{
    INT           UserSize;
    USER          Users[OVFMAXCHANNEL];
}USERS,*LPUSERS;
typedef struct tagREMOTUSER
{
	CHAR          UserName[OVFCHARLENTH];	
	CHAR          UserPwd[OVFCHARLENTH];	
	BOOL          UserUseDerivedPwd;
}REMOTEUSER,*LPREMOTEUSER;                  //远程访问帐户
#endif//OVF_DEVICEMAGER_USER_H

