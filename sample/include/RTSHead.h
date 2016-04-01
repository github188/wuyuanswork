#pragma  once // modfiy by ali 2008-12-5


#pragma pack(1)
#define OLDMCUVER 0x01
#define MCUVER 0x02
#define  HK_DATAPROI_LEVEL 4

#define MAX_ONEPK_SIZE    2048
#define HK_ACK_LEN        5
#define HK_ACK_TIMEOUT    200
#define HK_ACK_ALLTIME    15
#define HK_SEQ_START      1
#define HK_SEQ_END        65500
#define BACK_SIZE         250
#define HK_ONE_RATE       0.2
#define HK_PORT_START   5000
#define HK_PORT_END     10000

#define HK_MAX_PACKETSIZE  9000  
#define HK_MAX_POOLSIZE    65535
#define HK_VER 0x01
#define HK_MASKX		   233
#ifdef _HKIPC
#define  HK_MAXBH  30
#define  HK_WARNBH 15
#define  HK_BTBH     29

#define SOCKET int
#ifndef NULL
#define NULL  0
#endif

#ifndef bool
#define bool int
#define false 0
#define true 1
#endif
#endif
#define ENDSEQ( nSeq )  if( (nSeq) == 65501 ){ nSeq = HK_SEQ_START; }
enum _HK_INCMD   // 内部信令组
{
	HK_IACMD	= 1,
	HK_IBCMD	= 2,			// 系统内部使用！！！！包括申请内码，分配路由，等等
	HK_OCMD		= 3,
	HK_SRTP		= 4,			// 媒体
	HK_INBIND	= 5,			// 带内

	HK_REQ_BH	= 6,			// 心跳
	HK_RSP_BH	= 7,			// 响应

	HK_TRY		= 8,			// 尝试
	HK_OK		= 9,			// 成功
	HK_ACK		= 10,	        // 失败
	HK_INFO		= 11,			
	HK_QUIT		= 12,			// 退出

	HK_REQ_STUN = 13,
	HK_RSP_STUN	= 14,

	HK_INEND	= 15    // 内部信令最多15
};

enum _NETOP_CMD
{
	NETOP_UPDATEHKID	= 10,
	NETOP_SETSTUNSRV	= 11,
	NETOP_NEWSESSION	= 12,
	NETOP_DELSESSION	= 13,
	NETOP_ENABLEREAD	= 14,
	NETOP_ENABLEWRITE	= 15,
	NETOP_DISABLEREAD	= 16,
	NETOP_DISABLEWRITE	= 17,
	NETOP_DOSYSFAIL		= 18,
	NETOP_DOTRYNAT		= 19,
	NETOP_LISTENIP		= 20,
	NETOP_ADDEP			= 21,
	NETOP_REMEP			= 22,
	NETOP_ADDPIPE		= 23,
	NETOP_REMPIPE		= 24,
	NETOP_INITMAC		= 25,
	NEOP_SETHKID		= 26,
	NEOP_NETINFO		= 27,
};

enum _HK_INCMDEX     // 内部信令扩展 配合 HK_IBCMD 使用！
{
	HK_INCMDEX_SEQACK				= 1,
	HK_INCMDEX_RESEND				= 2,
	HK_INCMDEX_REQHKID				= 3,
	HK_INCMDEX_RPSHKID				= 4,

	HK_INCMDEX_ADDPIPE				= 5, // 路由 通知下一跳（多路）
	HK_INCMDEX_REMPIPE				= 6, // 删除
	HK_INCMDEX_RUNPIPE				= 7, // 万事具备，可以发送，
	HK_INCMDEX_STOPPIPE				= 8,

	HK_INCMDEX_CONNECT				= 9, // 实体连接
	HK_INCMDEX_DISCONNECT			= 10,
	HK_INCMDEX_CONNECTED			= 11,
	HK_INCMDEX_CONFAIL				= 12,
	HK_INCMDEX_CONNECTWARING		= 13, //Huqing 06-10 连接警告
	HK_INCMDEX_TESTCONNECT			= 14, //Huqing 06-12 Ping Connnect

	HK_INCMDEX_UPDATENATADDR		= 15,  //更新或提交NATADDR！
	HK_INCMDEX_REPORTLOCAL			= 16,

	HK_INCMDEX_ACKADDPIPE			= 17,
	HK_INCMDEX_MCUINFO				= 18,
	HK_INCMDEX_UNREGISTER			= 19,

	HK_INCMDEX_ADDPIPESUCCESS		= 20,
	HK_INCMDEX_ADDPIPEFAIL			= 21,
	HK_INCMDEX_REMPIPESUCCESS		= 22,
	HK_INCMDEX_REMPIPEFAIL			= 23,

	HK_INCMDEX_FINDNEIGHBOUR		= 24,
	HK_INCMDEX_ACKNEIGHBOUR			= 25,
	HK_INCMDEX_ADDNEIGHBOUR			= 26,
	HK_INCMDEX_REMNEIGHBOUR			= 27,
	HK_INCMDEX_TRYCONNECT			= 28,
	HK_INCMDEX_RQACKSEQ				= 29,
	HK_INCMDEX_RSPACKSEQ			= 30,

	HK_INCMDEX_PIPELOSTDATAREMDST	= 31, //Huqing 05-20 pipe不可丢包类中移除DST
	HK_INCMDEX_ACKDATAID			= 32,  //Huqing 05-21 目标端确认不可丢包
	HK_INCMDEX_PIPECHANGEROUNT		= 33, //Huqing 06-05 Pipe设置或改变路由
	HK_INCMDEX_SYSROUTERCHANGE      = 34,  //Huqing 11-10
};

enum _MASKTYPE
{
	HK_MASK_SIG = 0,  // 纯版本
	HK_MASK_MUL = 1   // 混合版本
};

enum _HK_SOAP
{
	HK_SOAP_STREAM = 0,
	HK_SOAP_BH
};

enum _HK_STREAM_ST
{
	HK_STREAM_ERROR = 1,
	HK_STREAM_WARNING,
};

#ifdef RTSARM
typedef struct _HKRedHead
{
	unsigned short seq;
}__attribute__ ((packed))  HKRedHead;

typedef struct _HKRedBody
{
	unsigned short mask:1;
	unsigned short proi:3;
	unsigned short windsize:12;
#ifdef __cplusplus
	_HKRedBody()
	{
		mask = 0;
		proi = 0;
		windsize = 0;
	}
	_HKRedBody& operator = ( _HKRedBody &rHead )
	{
		if( &rHead == this )
		{
			return ( *this );
		}
		mask = rHead.mask;
		proi = rHead.proi;
		windsize = rHead.windsize;
		return ( *this );
	}
#endif
}__attribute__ ((packed)) HKRedBody;

typedef struct  _RTSHead // 最新的 RTS结构！ 不包含任何载体类型！13Byte
{
#if(1)                                         
	unsigned char     ver:2;
	unsigned char     flag:2;                  // 00 不可以丢失，01标示可以丢失，10 非关键帧 11 关键帧，
	unsigned char     cmd:4;                   // 内部命令字
	unsigned short    seq:12;                  // 内部SEQ
	unsigned short	  dt:1;					   // 方向
	unsigned short	  rout:3;                  // 路由
	unsigned short    len:16;				   // 包大小
	unsigned int      hkid:32;                 // 内码ID

#ifdef __cplusplus
	_RTSHead()
	{
		ver     = MCUVER;
		flag    = 0;
		dt		= 0;
		rout	= 0;
		cmd     = HK_OCMD;
		seq     = 0;
		len     = 9;
		hkid    = 0;
	}
#endif
#endif
#if(0)
	unsigned int ver:2;
	unsigned int v:6;
	unsigned int flg:1;
	unsigned int pt:4;
	unsigned int mt:3;
	unsigned int len:16;
	unsigned int ssid:32;
	_RTSHead()
	{
		ver    = MCUVER;
		flg    = FLG_RTP;
		ssid   = 0;
		len    = 8;
		v      = 0;
		pt     = 0;
		mt     = HK_MT_VIDEO;
	}
#endif
#if(0)
	unsigned int    p:2;
	unsigned int   ch:6;
	unsigned int  seq:8;
	unsigned int  Len:16;
	unsigned int ssid:32;
#endif
#if(0)
	unsigned int ver:2;
	unsigned int flg:1;
	unsigned int ssid:13;
	unsigned int ch:8:

	_RTSHead()
	{
		ver    = MCUVER;
		flg    = FLG_RTP;
		ssid   = 0;
		ch     = 0;
	}
#endif
#if(0)
	unsigned int timesample;
#endif
} __attribute__ ((packed)) RTSHead;
#else
typedef struct _HKRedHead
{
	unsigned short seq;
}HKRedHead;

typedef struct _HKRedBody
{
	unsigned short mask:1;
	unsigned short proi:3;
	unsigned short windsize:12;
#ifdef __cplusplus
	_HKRedBody()
	{
		mask = 0;
		proi = 0;
		windsize = 0;
	}
	_HKRedBody& operator = ( _HKRedBody &rHead )
	{
		if( &rHead == this )
		{
			return ( *this );
		}
		mask = rHead.mask;
		proi = rHead.proi;
		windsize = rHead.windsize;
		return ( *this );
	}
#endif
}HKRedBody;

typedef struct  _RTSHead // 最新的 RTS结构！ 不包含任何载体类型！13Byte
{
#if(1)                                         
	unsigned char     ver:2;
	unsigned char     flag:2;                  // 00 不可以丢失，01标示可以丢失，10 非关键帧 11 关键帧，
	unsigned char     cmd:4;                   // 内部命令字
	unsigned short    seq:12;                  // 内部SEQ
	unsigned short	  dt:1;					   // 方向
	unsigned short	  rout:3;                  // 路由
	unsigned short    len:16;				   // 包大小
	unsigned int      hkid:32;                 // 内码ID

#ifdef __cplusplus
	_RTSHead()
	{
		ver     = MCUVER;
		flag    = 0;
		dt		= 0;
		rout	= 0;
		cmd     = HK_OCMD;
		seq     = 0;
		len     = 9;
		hkid    = 0;
	}
#endif
#endif
#if(0)
	unsigned int ver:2;
	unsigned int v:6;
	unsigned int flg:1;
	unsigned int pt:4;
	unsigned int mt:3;
	unsigned int len:16;
	unsigned int ssid:32;
	_RTSHead()
	{
		ver    = MCUVER;
		flg    = FLG_RTP;
		ssid   = 0;
		len    = 8;
		v      = 0;
		pt     = 0;
		mt     = HK_MT_VIDEO;
	}
#endif
#if(0)
	unsigned int    p:2;
	unsigned int   ch:6;
	unsigned int  seq:8;
	unsigned int  Len:16;
	unsigned int ssid:32;
#endif
#if(0)
	unsigned int ver:2;
	unsigned int flg:1;
	unsigned int ssid:13;
	unsigned int ch:8:

	_RTSHead()
	{
		ver    = MCUVER;
		flg    = FLG_RTP;
		ssid   = 0;
		ch     = 0;
	}
#endif
#if(0)
	unsigned int timesample;
#endif
}RTSHead;
#endif




#define HK_REDHEAD_LEN    sizeof( HKRedHead )
#define HK_REDBODY_LEN    sizeof( HKRedBody )
#define HK_RTPHEAD_LEN    sizeof( RTSHead )

#define HK_FULL_LEN       ( HK_REDHEAD_LEN + HK_REDBODY_LEN + HK_RTPHEAD_LEN )
#define HK_HEAD_LEN       ( HK_REDHEAD_LEN + HK_REDBODY_LEN )

#pragma  pack(8)
