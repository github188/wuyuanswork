#ifndef _SKYWEBINTERFAC_H_
#define _SKYWEBINTERFAC_H_

#include<stdio.h>
#include<stdarg.h>
#include<stdlib.h>
#include<string.h>
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

#ifndef BOOL
#define BOOL int
#endif//BOOL

#ifndef TRUE
#define TRUE 1
#endif//TRUE


#ifndef FALSE
#define FALSE 0
#endif//FALSE

#ifndef HWEBS
#define HWEBS void *
#endif//HWEBS

#ifndef HWEBCGI
#define HWEBCGI void *
#endif//HWEBCGI

#ifndef VOID
#define VOID void 
#endif
#define HTML_MAX_LEN 100*1024
typedef enum{
    METHOD_UNKNOWN  =0,
    METHOD_GET      =1,
    METHOD_POST     =2,
}ENU_WEBMETHOD;

typedef enum{
    IMAGE_MJPEG     =1,
    IMAGE_JPEG      =2,
}ENU_PICGETTYPE;

#define CHANNEL_1       0
#define CHANNEL_2       1
#define CHANNEL_3       2

typedef struct 
{
	int   client_sock;			      
	char  client_ip[16];			       
	int   client_port;
	char  *data;
	int   data_len;
	int   channel;
}WEBCLIENTINFO,*LPWEBCLIENTINFO;

typedef INT  (*CB_ONCGI)   (HWEBCGI hWebCgi,CHAR *CgiPath);
typedef VOID (*CB_ONMJPEG) (INT Socket, INT Channel, ENU_PICGETTYPE PicType);
typedef INT  (*CB_ONAUTH)  (CHAR * UserName,CHAR * Password);
//Web服务
HWEBS            WEBS_Init      (INT web_port,CB_ONCGI   callback_Cgi,
                                 CB_ONMJPEG callback_MjpegStream,
                                 CB_ONAUTH   callback_AuthCheck);
VOID             WEBS_DeInit    (HWEBS hWebs);

VOID             WEBS_Start     (HWEBS hWebs,WEBCLIENTINFO *ClientInfo, void *Param);
//BOOL             WEBS_IsHTML    (char *pRequrd);
//CGI 辅助函数
VOID			 CGI_GetRemotIP (HWEBCGI hWebCgi,CHAR **ip);
ENU_WEBMETHOD    CGI_GetMethod  (HWEBCGI hWebCgi);
VOID             CGI_GetUserPwd (HWEBCGI hWebCgi,CHAR *User,CHAR *Password);
VOID             CGI_GetBrowse  (HWEBCGI hWebCgi,CHAR *Browse);
BOOL             CGI_GetLunguage(HWEBCGI hWebCgi,CHAR *Lunguage);
VOID CGI_GetCookie(HWEBCGI hWebCgi,CHAR **Cookie);
BOOL CGI_GetFormVal(HWEBCGI hWebCgi,CHAR *Name,CHAR**Val);
BOOL CGI_GetFormValM(HWEBCGI hWebCgi,CHAR *NameArry,CHAR*Format,...);
BOOL CGI_Printf(HWEBCGI hWebCgi,CHAR *Format,...);
//MJPEG辅助函数
BOOL  MJPEG_SendPic(int *Socket,CHAR* Pic,UINT PicLength,ENU_PICGETTYPE PicType);


#endif//_CTWEBSRVER_H_
