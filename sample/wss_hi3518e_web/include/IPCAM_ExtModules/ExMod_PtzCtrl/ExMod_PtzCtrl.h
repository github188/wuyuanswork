#ifndef EXMOD_PTZCTRL_H
#define EXMOD_PTZCTRL_H


#ifdef __cplusplus
extern "C" {
#endif


#ifndef HPTZ 
#define HPTZ  void*
#endif
#ifndef UCHAR 
#define UCHAR unsigned char 
#endif
#ifndef CHAR 
#define CHAR char
#endif
#ifndef INT
#define INT int
#endif
#ifndef ULONG
#define ULONG unsigned long
#endif
#ifndef BOOL 
#define BOOL unsigned int
#endif
#ifndef NULL
#define NULL (void *) 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

//// ÔÆÌ¨¿ØÖÆÃüÁî
typedef enum
{
	PTZ_COMMAND_UNKNOWN = 0,	//// Î´ÖªµÄÃüÁî
	PTZ_STOP			= 1,	//// Í£Ö¹ËùÓĞÔÆÌ¨¶¯×÷


	UP_START			=2,		//// ÏòÉÏ¿ªÊ¼
	UP_STOP,					//// ÏòÉÏÍ£Ö¹
	DOWN_START,					//// ÏòÏÂ¿ªÊ¼
	DOWN_STOP,					//// ÏòÏÂÍ£Ö¹

	LEFT_START,				//// Ïò×ó¿ªÊ¼
	LEFT_STOP,					//// Ïò×óÍ£Ö¹
	RIGHT_START,				//// ÏòÓÒ¿ªÊ¼
	RIGHT_STOP,					//// ÏòÓÒÍ£Ö¹

	LEFT_UP_START,				//// ×óÉÏ¿ªÊ¼
	LEFT_UP_STOP,				//// ×óÉÏÍ£Ö¹
	RIGHT_UP_START,				//// ÓÒÉÏ¿ªÊ¼
	RIGHT_UP_STOP,				//// ÓÒÉÏÍ£Ö¹
	LEFT_DOWN_START,			//// ×óÏÂ¿ªÊ¼
	LEFT_DOWN_STOP,				//// ×óÏÂÍ£Ö¹
	RIGHT_DOWN_START,			//// ÓÒÏÂ¿ªÊ¼
	RIGHT_DOWN_STOP,			//// ÓÒÏÂÍ£Ö

	SCAN_ON,					//// ÏßÉ¨Ãè¿ª
	SCAN_OFF,					//// ÏßÉ¨Ãè¹Ø

	IRIS_OPEN_START,			//// ¿ª¹âÈ¦¿ªÊ¼
	IRIS_OPEN_STOP,				//// ¿ª¹âÈ¦Í£Ö¹
	IRIS_CLOSE_START,			//// ¹Ø¹âÈ¦¿ªÊ¼
	IRIS_CLOSE_STOP,			//// ¹Ø¹âÈ¦Í£

	FOCUS_NEAR_START,			//// ½¹¾à½ü¿ªÊ¼
	FOCUS_NEAR_STOP,			//// ½¹¾à½üÍ£Ö¹
	FOCUS_FAR_START,			//// ½¹¾àÔ¶¿ªÊ¼
	FOCUS_FAR_STOP,				//// ½¹¾àÔ¶Í£Ö¹

	ZOOM_WIDE_START,			//// Í¼Ïó±äĞ¡¿ªÊ¼
	ZOOM_WIDE_STOP,				//// Í¼Ïó±äĞ¡Í£Ö¹
	ZOOM_TELE_START,			//// Í¼Ïó±ä´ó¿ªÊ¼
	ZOOM_TELE_STOP,				//// Í¼Ïó±ä´óÍ£Ö¹

	CAMERA_ON,					//// ÉãÏñ»úµçÔ´¿ª
	CAMERA_OFF,					//// ÉãÏñ»úµçÔ´¹Ø
	LAMP_ON,					//// µÆ¹â¿ª
	LAMP_OFF,					//// µÆ¹â¹Ø
	WIPER_ON,					//// ÓêË¢¿ª
	WIPER_OFF,					//// ÓêË¢¹Ø

	PRESET_POINT,				//// ÉèÖÃÔ¤ÖÃÎ»
	SET_POINT,					//// µ÷ÓÃÔ¤ÖÃÎ»
	//// ÆäËûÃüÁî´ıĞø.....
} X_PTZ_COMMAND;


typedef struct {
CHAR    protocolName[20];     //ÔÆÌ¨Ğ­ÒéÃû³Æ
ULONG   baudRate;             //²¨ÌØÂÊ
CHAR    dataSize;             //Êı¾İÎ»
CHAR    parity;               //ÆæÅ¼Ğ£Ñé
CHAR    stopBit;              //Í£Ö¹Î»
CHAR    flowControl;          //Á÷¿Ø
}IPCAM_PTZINFO;


HPTZ  PTZM_Init           (CHAR *filePath);
BOOL  PTZM_DeInit         (HPTZ hPtz);
BOOL  PTZM_GetPtzProParam (HPTZ hPtz,IPCAM_PTZINFO *ptzInfo);
BOOL  PTZM_SetPtzProParam (HPTZ hPtz,UCHAR address,UCHAR speed);
BOOL  PTZM_GetPtzCommand  (HPTZ hPtz,X_PTZ_COMMAND command,UCHAR *param,UCHAR * buffer,INT *nSize);//param£º²¿·ÖÃüÁî´øÓĞ²ÎÊı


#ifdef __cplusplus
}  /* End of the 'extern "C"' block */
#endif

#endif

