#ifndef HK_SYSTEM_H__
#define HK_SYSTEM_H__

#include <stdio.h>
#if defined(_WIN32)
#  include <windows.h>
#else
#  include <unistd.h>
#  include <pthread.h>
#endif

#ifdef SYSM_1_3
#  define SYSM_MAJOR_VESION 0x0103
#else
#  define SYSM_MAJOR_VESION 0
#endif

#define HK_KEY_VALUES 64	//key值大小
#define HK_MIN_VALUES 2048	//单个buf最大值
#define HK_MAX_VALUES 4096	//整个buf最大值
#define HK_SQL_SIZE	512	

#include "rs.h"
#include "version.h"

#ifdef unix
#  define AFX_EXT_CLASS
#elif !defined(AFX_EXT_CLASS)
#  define AFX_EXT_CLASS __declspec(dllimport) 
#endif
#include "utils/HKCmdDefine.h"
#include "utils/HKLog.h"
#include "chinalink.h"

#if HK_SYSM_VER < 0x0103
#  include "hashtab/sqlite3.h"
#else
#  include "utils/sqlite3.h"
#endif

#if defined(__cplusplus)
extern "C" {
#endif

typedef void (*sys_evt_func_t)(int, const char*, unsigned int);
typedef struct SystemEvents
{
    void (*OnSystemLogin)(int ec);
    void (*OnSystemLogout)(int ec);
} SystemEvents;

typedef struct RSObject DevClass;

HK_SYSTEM_API void SysRegisterDev(DevClass* dev);
HK_SYSTEM_API void SysUnregisterDev(DevClass* dev);

HK_SYSTEM_API int SysListDevClasses(const char* buf[], size_t bufsize);
HK_SYSTEM_API int SysListDevices(const char* buf[], size_t bufsize, const char* clsname);

#if HK_SYSM_VER < 0x0103
HK_SYSTEM_API int SysInit(sys_evt_func_t cbf, int enable_lan);
#else
HK_SYSTEM_API int SysInit(sys_evt_func_t cbf);
#endif

HK_SYSTEM_API int LanNetworking(int enable);

HK_SYSTEM_API void SysVer( const char* version, const char* type );	//升级

HK_SYSTEM_API int SysLogin(const char* user, const char* pwd
        , const char* usersettings, const char* host, int port, const char* netsettings);
HK_SYSTEM_API void SysLogout();

HK_SYSTEM_API void SysExit();

typedef int (*ASCallback)(int, const char*);
HK_SYSTEM_API int SysRegistAS(int hkAS, ASCallback newcb);

typedef int (*ASCallback_Lan)(unsigned int, int, const char*);
HK_SYSTEM_API int SysRegistASLan(int hkAS, ASCallback_Lan cb, ASCallback_Lan newcb);

typedef int (*lan0_f_t)(unsigned int, int, const char*, unsigned int);
HK_SYSTEM_API int SysRegistASLan_0(int hkAS, lan0_f_t cb, lan0_f_t newcb);

/**
 * const char* c1 = "id=hk202;To=0;ftN0=video.vbVideo.MPEG4;opN0=EncodeType=MPEG4;;ftN1=net.0;ftN2=HKPCPresent.HKPCPresent;opN2=%s;";
 * const char* c2 = "id=hk202;To=0;ftN0=video.vbAudio.G723;ftN1=net.0;ftN2=HKPCPresent.HKPCPresent;opN2=%s;";
 * char sid[2][64];
 * RSCDial(HK_AS_MONS, sid, c1, c2, NULL);
 * printf(sid[0]);
 * printf(sid[1]);
 *
 **/
HK_SYSTEM_API int ExecDial(unsigned int asc, const char* sid, const char* arg);
HK_SYSTEM_API void RSCHangup(unsigned int asc, const char* sid);
//HK_SYSTEM_API const char* SysGetProfile();
HK_SYSTEM_API char* GenerateSID(char buf[64]);

HK_SYSTEM_API int SysAddLanEP(const char* host, unsigned short port);
//HK_SYSTEM_API int SysNetConfig(unsigned int hkid, const char* ip, const char* netmask, const char* gateway);

HK_SYSTEM_API int NetSend(const char* as, const char* data, unsigned int size);
HK_SYSTEM_API int NetSendLan(int hkid, int hkAS, const char* data, unsigned int size);

HK_SYSTEM_API void LanPresent(const char* msg, unsigned int len);

HK_SYSTEM_API int RSCDoEvent(const char* ftn, int obj, const char* ev, unsigned int len);

// HK_SYSTEM_API const char* SysStrError(int);

typedef struct sqlite3 SystemDB;

extern SystemDB *g_sqlite_sys;	//DB

HK_SYSTEM_API SystemDB* DBOpen(const char* dbname);
HK_SYSTEM_API void DBClose(SystemDB* db);

typedef int (*DBQueryCallback)(void*, int argc, char** argv, char** columns);

HK_SYSTEM_API int DBQuery(SystemDB* db, const char* sql, DBQueryCallback, void*);
HK_SYSTEM_API int DBExecute(SystemDB* db, const char* sql);

HK_SYSTEM_API int DBKey( SystemDB* db, const char* keyBuf, unsigned int iLen );		//db 加密
HK_SYSTEM_API int DBRekey( SystemDB* db, const char* keyBuf, unsigned int iLen );	//修改db加密的key


typedef struct sqlite3_stmt DBsqlite3_stmt;
HK_SYSTEM_API DBsqlite3_stmt* DBOpenSqlite3_stmt( );		//获取执行结构
HK_SYSTEM_API int DBsqlite3_step( DBsqlite3_stmt* Stmt );	//执行SQL
HK_SYSTEM_API const void *DBsqlite3_column_blob( DBsqlite3_stmt*, int iCol );	//获取字段值
HK_SYSTEM_API int DBsqlite3_column_bytes( DBsqlite3_stmt*, int iCol );			//字段值的字节数
HK_SYSTEM_API int DBsqlite3_finalize( DBsqlite3_stmt* Stmt);	//释放结构内存
HK_SYSTEM_API int DBsqlite3_bind_blob( DBsqlite3_stmt* Stmt, int size, const void* buf, int nBufLen );	//增加数据时进行数据绑定

HK_SYSTEM_API int DBsqlite3_prepare( SystemDB *db, const char *zSql, int nByte,DBsqlite3_stmt **ppStmt,const char **pzTail );


#define UUID_STR_LENGTH 37
HK_SYSTEM_API char* GetUUID(char buf[], const char* pfx);

#ifdef WIN32

//open db
HK_SYSTEM_API int SystemOpenDB( const char *patch );
//close db
HK_SYSTEM_API int SystemCloseDB();
//登录名保存
HK_SYSTEM_API int SystemLoginCtrl( const char *username );
//读取登录名称
HK_SYSTEM_API int SystemReadLoginCtrl( char buf[HK_MAX_VALUES] );
//读取用户名配制信息
HK_SYSTEM_API char *SystemReadConfig( char buf[HK_MAX_VALUES], const char *username );
//修改用户名配制信息
HK_SYSTEM_API int SystemConfig( const char *name, const char *pConfin, int len );
//清除本地用户名
HK_SYSTEM_API int SystemDeleteLogin( const char *name );

//读取配制信息
//const char *type, 为空的时候读取最后一次使用的类型.
//返回值<0 为空..
HK_SYSTEM_API int SystemNetReadConfig( char buf[HK_MAX_VALUES], const char *name, const char *nettype );
//修改和添加配制信息
//返回值<0 为失败..
HK_SYSTEM_API int SystemNetConfig( const char *name, const char *nettype, const char *pConfin, int len );
//清除本地网络配制信息
//返回值<0 为失败..
HK_SYSTEM_API int SystemNetDeleteLogin( const char *name, const char *nettype );

//系统信息保存与修改
HK_SYSTEM_API int DoSysInsertOrUpdateSysinfo( const char *sysname, const char *sysinfo, int len );
//读取系统配制信息
HK_SYSTEM_API int DoSysReadSysinfo( const char *sysname,char buf[HK_MAX_VALUES] );

//修改用户密码
HK_SYSTEM_API void DoSysUpdatePasswd( const char *userid, const char *oldPasswd, const char *newPasswd );
//手动升级
HK_SYSTEM_API void DoSysUpdatePc();
//充值
HK_SYSTEM_API void DoAddMoneyCard( const char *devid, const char *moneyCard );

//登录成功后申请帐号.
HK_SYSTEM_API void DoApplicationAccounts( const char* user, const char* pwd, const char* usersettings );

//登录成功后激活帐号
HK_SYSTEM_API void DoActivationAccounts( const char *devid, const char *passwd, const char *email );

#endif

// asname: HKIMServer
// classname: File
// evname: TransProgress
// type: 0 表示完全订阅，1订阅节点名，2订阅设备名，3订阅设备实例SID
// value:	认证ID 有可能节点，或设备ID，SID
HK_SYSTEM_API int SysSubscribe(int hkAS, const char* cls, const char* evname, int type, const char* value);
HK_SYSTEM_API int SysUnsubscribe(int hkAS, const char* cls, const char* evname, int type, const char* value);

HK_SYSTEM_API const char* get_mac_address(const char* eth0);

// HK_SYSTEM_API int logwrite(FILE* xf, int lv, const char* pfx, unsigned int nl, const char* rng, unsigned int n, const char* fmt, ...);
#define HKLG_DEBUG(...)        HKLOG(L_DBG, __VA_ARGS__)
    // logwrite(0, 0,        0, __LINE__, 0, 0, __VA_ARGS__)
#define HKLG_ERROR(...)        HKLOG(L_ERR, __VA_ARGS__)
    // logwrite(0, 1, __FILE__, __LINE__, 0, 0, __VA_ARGS__)

typedef void (*func_argv_t)(int, void*, int, char**);
typedef int (*func_pred_t)(void*, func_argv_t, void*, int, char**);

#ifdef _MSC_VER
#  include <hksys/pthread.h>
#endif

HK_SYSTEM_API struct timedq* tq_create();
HK_SYSTEM_API void tq_destroy(struct timedq* q);

HK_SYSTEM_API void* tq_post(struct timedq* q, unsigned int msec, func_argv_t f, void* a, unsigned int argc, const char* argv[]);
HK_SYSTEM_API void* tq_post_v(struct timedq* q, unsigned int msec, func_argv_t f, void* my, ...);
HK_SYSTEM_API void* tq_send(struct timedq* q, unsigned int msec, func_argv_t f, void* my, ...);

HK_SYSTEM_API char* GetGuestUser(char buf[], unsigned int len);

#if defined(__cplusplus)
}
#endif

#endif // HK_SYSTEM_H__

