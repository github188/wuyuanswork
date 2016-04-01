//IPCAM_global.h

/*##############################################################################
#工程描述:
#       IP网络摄像机
#
#文件描述:
# 
#作者信息:
#      领航员数码科技有限公司 zqw  201-04-18   创建
#版权信息:
#       Copyright(c) 2008~201x 
#  	    领航员数码科技有限公司 All rights reserved.
###############################################################################*/

#ifndef __IPCAM_GLOBAL__
#define __IPCAM_GLOBAL__

//sys include.h

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <stdint.h>
#include <errno.h>
#include <dirent.h> 
#include <netdb.h> 
#include <semaphore.h>

#include <linux/un.h>
#include <linux/videodev.h>
#include <linux/fb.h>
#include <linux/un.h>
#include <linux/soundcard.h>

#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/sysinfo.h>
#include <arpa/inet.h>
#include <netinet/in.h> 
#include <netinet/tcp.h>
#include <sys/vfs.h>

#include <iconv.h>


// GLOBAL define
#ifndef  NULL
#define NULL (void *) 0
#endif
#ifndef  BOOL
#define  BOOL int
#endif
#ifndef TRUE
#define TRUE	0x01
#endif
#ifndef FALSE
#define  FALSE	0x00
#endif
#ifndef CHAR
#define  CHAR char
#endif
#ifndef UCHAR 
#define  UCHAR unsigned char
#endif
#ifndef  SHORT 
#define   SHORT short
#endif
#ifndef USHORT 
#define  USHORT unsigned short
#endif
#ifndef INT
#define INT   int
#endif
#ifndef UINT
#define UINT unsigned int
#endif
#ifndef LONG 
#define LONG long
#endif
#ifndef ULONG
#define ULONG unsigned long
#endif
#ifndef LLONG
#define LLONG long long
#endif
#ifndef ULLONG
#define ULLONG unsigned long long
#endif
#ifndef VOID 
#define VOID void
#endif
#ifndef HANDLE
#define HANDLE  void *
#endif

#ifndef HIWORD 
#define HIWORD(dword) (USHORT)(dword>>16)
#endif
#ifndef LOWORD
#define LOWORD(dword) (USHORT)(dword&0xFFFF)
#endif
#ifndef DWORDHI
#define DWORDHI(dword,word) (dword=word<<16)
#endif
#ifndef DWORDLO
#define DWORDLO(dword,word) (dword|=word   )
#endif
#ifndef MAKELONG
#define MAKELONG(low, high) ((DWORD)(((WORD)(low)) | (((DWORD)((WORD)(high))) << 16)))
#endif

#define IPCAM_EXT_DEBUG  1
#if IPCAM_EXT_DEBUG
#define IPCAM_TRACE         printf("[ %s, %d ]=> ",__FILE__,  __LINE__);printf("\r\n");
#define IPCAM_DEBUG(msg...) printf("[ %s, %d ]=> ",__FILE__,  __LINE__);printf(msg);printf("\r\n");
#define IPCAM_ERROR(msg...) fprintf(stderr, "[ %s, %d ]=> ",__FILE__,  __LINE__);printf(msg);printf("\r\n")
#define IPCAM_ASSERT(exp...) assert(exp)	

#define IPCAM_TEST_THREAD_INIT() \
	IPCAM_System("rm -rf /appex/thread");\
	IPCAM_System("mkdir /appex/thread -p")

#define IPCAM_TEST_THREAD_STATUS(fmt, args...)\
	do{\
		CHAR Command[128]; \
		sprintf (Command, "echo \"FILE [%s] LINE [%d]"fmt"\n\" > /appex/thread/%d.txt", __FILE__, __LINE__, ##args, pthread_self()); \
		IPCAM_System(Command); \
	}while(0)

#define IPCAM_TEST_THREAD_STATUS_DEL()\
	do{\
		CHAR Command[128];\
		sprintf (Command, "rm -rf /appex/thread/%d.txt", pthread_self()); \
		IPCAM_System(Command);\
	}while(0)
#else
#define IPCAM_TRACE         
#define IPCAM_DEBUG(msg...)  (void)(msg)
#define IPCAM_ASSERT(exp...) (void)(exp)
#endif


#define	IPCAM_PTHREAD_DETACH			do{ pthread_detach(pthread_self()); }while(0)
#define	IPCAM_PTHREAD_EXIT			do{ pthread_exit((void*)pthread_self()); }while(0)


#define	IPCAM_CREATE_THREAD(Func, Args)	do{					\
		pthread_t		__pth__;									\
		if(pthread_create(&__pth__, NULL, (void *)Func, (void *)Args))	\
        return FALSE; \
      }while(0)
	
#define	IPCAM_CREATE_THREADEX(Func, Args,Ret)	do{					\
		pthread_t		__pth__;									\
		if (0 == pthread_create(&__pth__, NULL, (void *)Func, (void *)Args))	\
			Ret = TRUE; \
		else \
			Ret = FALSE; \
      }while(0)

#define	IPCAM_SLEEPEX(OSDSec, OSDUsec)	do{			\
		struct timeval	__DVRSleepTV__;				\
		__DVRSleepTV__.tv_sec	= OSDSec;			\
		__DVRSleepTV__.tv_usec	= OSDUsec;			\
		select(1, NULL, NULL, NULL, &__DVRSleepTV__);		\
	}while(0)

//////////////////////////////




#endif

