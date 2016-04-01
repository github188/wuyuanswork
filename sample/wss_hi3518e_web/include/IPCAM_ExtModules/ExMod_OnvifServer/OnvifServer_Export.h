
typedef enum
{
	ONVIF_PTZ_CMD_UNKNOWN = 0,	//// 未知的命令
	ONVIF_PTZ_STOP			= 1,	//// 停止所有云台动作

	ONVIF_UP_START			=2,		//// 向上开始
	ONVIF_UP_STOP,					//// 向上停止
	ONVIF_DOWN_START,					//// 向下开始
	ONVIF_DOWN_STOP,					//// 向下停止

	ONVIF_LEFT_START,				//// 向左开始
	ONVIF_LEFT_STOP,					//// 向左停止
	ONVIF_RIGHT_START,				//// 向右开始
	ONVIF_RIGHT_STOP,					//// 向右停止

	ONVIF_LEFT_UP_START,				//// 左上开始
	ONVIF_LEFT_UP_STOP,				//// 左上停止
	ONVIF_RIGHT_UP_START,				//// 右上开始
	ONVIF_RIGHT_UP_STOP,				//// 右上停止
	ONVIF_LEFT_DOWN_START,			//// 左下开始
	ONVIF_LEFT_DOWN_STOP,				//// 左下停止
	ONVIF_RIGHT_DOWN_START,			//// 右下开始
	ONVIF_RIGHT_DOWN_STOP,			//// 右下停?
	//// 其他命令待续.....
} ONVIF_PTZ_COMMAND;
typedef  int  (*CBPTZTEST)();

