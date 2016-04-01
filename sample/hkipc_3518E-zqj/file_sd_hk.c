#include <time.h>
#include <sys/times.h>

#include "hkipc_hk.h"

#include "rs.h"
#include "sys.h"
#include "utils/HKMonCmdDefine.h"
#include "utils/HKCmdPacket.h"
//#include "utils/HKDataBase.h"

extern bool b_hkSaveSd;
static RSObject file_sd_inst;
static RSObjectIRQEvent ev_irq = NULL;
//static pthread_rwlock_t fd_rwlock;
//static pthread_mutex_t plock_mutex;

Dict *g_TFPacket=NULL;
int g_iTfCount=0;

static pthread_mutex_t g_MutexLock_TF = PTHREAD_MUTEX_INITIALIZER;

static pthread_mutex_t g_MutexLock_CloseReadTF = PTHREAD_MUTEX_INITIALIZER;
short g_TF_start=0;
static short g_Delete_Flag = 0;
short g_TF_flag = 0;
char *g_cDataBuf = NULL;
int g_KeySplit = 0;

#define max_count	5
#pragma pack(1)

typedef struct HK_VHeader_v2
{
    unsigned int fragx:2;
    unsigned int flipex:2;
    unsigned int resolution:4;
    unsigned int encode:5;
    unsigned int flip:1;
    unsigned int version:2;
} __attribute__ ((packed))  HK_VHeader;

HK_VHeader g_hkHeader;
HKFrameHead *frameRec=NULL;
extern HK_SD_PARAM_ hkSdParam;
extern int GetStorageInfo();
extern short g_sdIsOnline;

typedef struct FrameHead
{   // 
    unsigned char cFrameMark[3];    
    unsigned char cFrameType;       //DER_MASK

    unsigned int nDataType;         // 
    unsigned int nID;                   // 
    unsigned int nLength;               // 
    unsigned int nDurationTicks;        // 
    unsigned int nFrameCount;           // 
} __attribute__ ((packed)) FrameHead_;

typedef struct FileHead
{   // 
    unsigned char    cFileMark[3];       //'HEK',
    unsigned short  nFileHeadVer;       // 
    unsigned long long lStartDateTime;  //
    unsigned int    nDurationTicks; // 
    unsigned int    nFrameCount;        //
    unsigned int    nIndexSize;         //
    unsigned int    nUserInfoSize;      //
    char            szUserName[50];     // 

    unsigned char   bIsFinish;          // 
    unsigned int    iFileSize;          //
    char            szOther[100];       // 
}__attribute__ ((packed)) FileHead_;

typedef struct FrameIndex
{   //
    unsigned long nLength;              //
    unsigned int nDurationTicks;        // 
    unsigned int nDurationFrame;        //
}__attribute__ ((packed)) FrameIndex_;

enum HK_MEDIA_FILE_FRAME_DATA_TYPE
{
    HK_MFF_VIDEO = 1,
    HK_MFF_AUDIO = 2,
    HK_MFF_MPEG4 = 4,
    HK_MFF_MJPEG = 8,
    HK_MFF_H264 = 16,
    HK_MFF_G723 = 32,
    HK_MFF_G729 = 64,
    HK_MFF_G711 = 128,
    HK_MFF_G726 = 256,
    HK_MFF_PCMA = 512,
    HK_MFF_PCMU = 1024
};

#pragma pack()

extern int NetFileIsFull();

FrameIndex_ m_frameIndex;
FileHead_ m_fileHead;
FrameHead_ m_frameHead;

static void sd_deleteRec();
static void SetIRQEventCallback(RSObjectIRQEvent cb) 
{
	ev_irq = cb;
}

static const char* Retrieve()
{
	return "File.SDStorage.in,File.SDStorage.out";
}

static const char* GetObjectInfo()
{
	return "Type=File;";
}

FILE *g_fpRead=NULL;
typedef struct File_list
{
	FILE *fpRead;
	short rflag;

}file_rlist;

file_rlist file_r[max_count] = {0};

static int Read(int obj, char *buf, unsigned int bufsiz, long *flags)
{
    if (0 == g_sdIsOnline)
        return -1;

    //pthread_mutex_lock( &g_MutexLock_CloseReadTF );
    obj -= 1;
    if( NetFileIsFull() <= 0 )
    {
        usleep(5000);
        //pthread_mutex_unlock( &g_MutexLock_CloseReadTF );
        return 0;
    }
    else
        usleep(40);

    if( file_r[obj].fpRead == NULL )
    {
        file_r[obj].rflag = 0;
        //pthread_mutex_unlock( &g_MutexLock_CloseReadTF );
        return -1;
    }

    unsigned int nRead=0;
    *flags = 0;

    int nReadSize = 1024 * 5;
    if(file_r[obj].fpRead != NULL )
        nRead = fread( buf, 1, nReadSize, file_r[obj].fpRead );  //read ..
    if( nRead <= 0 )
    {
        if(file_r[obj].fpRead != NULL )
            fclose( file_r[obj].fpRead );
        file_r[obj].fpRead = NULL;
        file_r[obj].rflag = 0;

        //pthread_mutex_unlock( &g_MutexLock_CloseReadTF );
        return -1;
    }
    *flags = HK_BOAT_NLOST;
    int iLeve = 3;
    *flags |= (iLeve<<8);

    //pthread_mutex_unlock( &g_MutexLock_CloseReadTF );
    return nRead;
}

static VideoDataRecord_TF *hostVideoDataPTF = NULL;
static int sccPushVideoData_TF(int pStreamType, const char *pData,unsigned int nSize,short IFrame,int iResType,int iStreamType,VideoDataRecord_TF  *mVideoDataBuffer);

static void sccResetVideDataTF(int pStreamType, VideoDataRecord_TF  *mVideoDataBuffer);

static int TFsccInitVideoData(int pStreamType)
{
    if ((0 == pStreamType) && (NULL == hostVideoDataPTF))
    {
        hostVideoDataPTF = calloc(1, sizeof(VideoDataRecord_TF));
        if (NULL == hostVideoDataPTF)
        {
            HK_DEBUG_PRT("calloc error with:%d, %s\n", errno, strerror(errno));
            return -1;
        }

        hostVideoDataPTF->g_videoBuf = calloc(1, MAX_VIDEODATA_HOSTSTREAM_TF);
        if (NULL == hostVideoDataPTF->g_videoBuf)
        {
            HK_DEBUG_PRT("calloc error with:%d, %s\n", errno, strerror(errno));
            free(hostVideoDataPTF);
            hostVideoDataPTF = NULL;
            return -1;
        }
        return 0;
    }
    return 0;
}


static char* GetTimeChar(char* buf, char* cFileName)
{
    unsigned int iTime = time(0);
    int tz = conf_get_int(HOME_DIR"/time.conf", "zone");
    iTime = iTime - tz;
    conf_set_int("/mnt/sif/time.conf", "time_", iTime);

	time_t timep;
	struct tm *p;
	time(&timep);
 	p = gmtime(&timep);
	//sprintf(buf, "%d%02d%02d%02d%02d%02d", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    char cTimeFile[64]={0};
	sprintf(cFileName, "%d%02d%02d%02d%02d%02d", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    char cTime[64]={0};
	sprintf(cTime, "%d%02d%02d", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
    sprintf(buf,"%s/%s", cTime, cFileName );

    sprintf(cTimeFile,"/mnt/mmc/snapshot/%s", cTime );
    struct stat cst;
    if (stat(cTimeFile, &cst) == 0)
    {
        printf(" Tf File Name=%s..\n", cTimeFile);
    }
    else
    {
        mkdir(cTimeFile, 0755);
        printf("Create Tf File Name=%s..\n", buf);
    }

	return buf;
}

#define FILE_HEADER_MASK   "HEK"
#define FILE_INDEX_MASK    "IDEX"
#define FILE_USERINFO_AREA 1024*10
#define FILE_HEAD_VER 1

#define MIN_USEFUL_BYTES 1
#define HK_FRAME_I 1
#define HK_FRAME_OTHERS 0

static int sd_open( char *cTime, char *cFileName );
//FILE *g_fp=NULL;

int g_fp=NULL;
static int Open(const char* name, const char* args, int* threq)
{
    int ret = 0;
    if( g_sdIsOnline == 0 )
        return 0;
    if (strcmp(name,"File.SDStorage.in")==0 )
    {
        return 0;
        if (args != NULL)
        {
            if(strcmp(args, "audioin")==0 )
            {
                //printf("....OPEN.audio=%s...\n",args);
                ret = max_count + 2;
                return ret;
            }

            int isdOpen;
            memset(&m_fileHead, 0, sizeof(m_fileHead));
            m_fileHead.nFileHeadVer = FILE_HEAD_VER;
            memcpy(m_fileHead.cFileMark, FILE_HEADER_MASK, 3);

            isdOpen = sd_open( args, NULL );//time
            if ( isdOpen == -1 )
                return 0;
            ret = max_count+1;
        }
    }
    else if (strcmp(name, "File.SDStorage.out")==0)
    {
        if (args == NULL)
            return 0;
        pthread_mutex_lock( &g_MutexLock_CloseReadTF );
        char cPatch[64]={0};
        HKFrameHead* frameOpenRec = CreateFrameA(args, strlen(args));
        char *recfile = GetParamStr( frameOpenRec, HK_KEY_REC_FILE );
        if( NULL==recfile)
        {
            DestroyFrame(frameOpenRec);
            pthread_mutex_unlock( &g_MutexLock_CloseReadTF );
            return 0;
        }

        FILE *fp = NULL;
        if (!(fp = popen("ls -rt /mnt/mmc/snapshot", "r"))) 
        {
            printf("Read TF File popen failed.\n");
            pthread_mutex_unlock( &g_MutexLock_CloseReadTF );
            return 0; 
        }
        char tmpbuf[512] = {0};
        char buf[512]={0};
        while (fgets(buf, sizeof(buf), fp)) 
        {
            sscanf(buf, "%[^\n]", tmpbuf);
            sprintf(cPatch, "/mnt/mmc/snapshot/%s/%s", tmpbuf,recfile );
            if (0 == access(cPatch, F_OK | R_OK )) //check 
            {
                break;
            }
        }
        if(fp!= NULL)
        {
            pclose(fp);
            fp=NULL;
        }

        int i = 0;
        //snprintf(cPatch, sizeof(cPatch), "/mnt/mmc/snapshot/%s", recfile);
        for (i = 0; i < max_count; i++)
        {
            if (file_r[i].rflag == 0)
            {
                FILE *fpRead = NULL;
                if((fpRead=fopen(cPatch, "rb"))==NULL )
                {
                    printf("scc.SD.open fail...cPatch=NULL...\n");
                    pthread_mutex_unlock( &g_MutexLock_CloseReadTF );
                    return 0;
                }
                file_r[i].rflag =1;
                file_r[i].fpRead = fpRead;
                *threq=1;
                DestroyFrame(frameOpenRec);
                int iObj = i+1;
                printf("scc Open SD success obj=%d...\n",iObj);
                pthread_mutex_unlock( &g_MutexLock_CloseReadTF );
                return iObj;
            }
        }
        printf("scc obj=0........\n");
        DestroyFrame(frameOpenRec);

        pthread_mutex_unlock( &g_MutexLock_CloseReadTF );
        return 0;
    }
    return ret;
}

//unsigned long long g_ulDataLen = 0;
unsigned int g_ulDataLen = 0;
static void Close(int obj)
{
    printf("scc sd file Close obj=%d...\n", obj);
    if(obj > max_count)
    {
        WriteFileHeader(&m_fileHead);
        g_ulDataLen = 0;
        if( NULL != g_fp )
        {
            close(g_fp);
            g_fp = NULL;
        }
        return;
    }
    else if(obj > 0 )
    {
        pthread_mutex_lock( &g_MutexLock_CloseReadTF );
        obj -= 1;
        if(NULL!=file_r[obj].fpRead)
        {
            fclose(file_r[obj].fpRead);
            file_r[obj].fpRead=NULL;
            file_r[obj].rflag=0;
        }
        pthread_mutex_unlock( &g_MutexLock_CloseReadTF );
        printf("scc sd file Close.End..\n");
    }
}

unsigned long m_lPreTick=0;
bool m_bCurIsIVOP=true;

unsigned long GetTickCount()
{
    struct tms tm_s;
    return times(&tm_s)*10;
    /*struct timeval now;
    gettimeofday( &now,NULL );
    return now.tv_sec*1000+now.tv_usec/1000; */
}

void WriteFrameHead(FILE* pFile, long nID, int nLength, unsigned int nDataType/* = HK_MFF_VIDEO | HK_MFF_MPEG4*/,int iStreamType)
{
    int nRelativeTime = 0;

    unsigned long lNowTick = GetTickCount();
    if(m_lPreTick != 0)
        nRelativeTime = lNowTick - m_lPreTick;
    m_lPreTick = lNowTick;

    m_fileHead.nDurationTicks += nRelativeTime;
    m_fileHead.iFileSize += sizeof(FrameHead_);
    ++m_fileHead.nFrameCount;

    memset(m_frameHead.cFrameMark,0x0,3);
    m_frameHead.cFrameMark[2] = 0x01;

    m_frameHead.cFrameType = m_bCurIsIVOP ? HK_FRAME_I : HK_FRAME_OTHERS;
    m_frameHead.nDataType = nDataType;
    m_frameHead.nID = nID;
    if(4== iStreamType)
    {
        m_frameHead.nLength = nLength+2;
    }
    else
    {
        m_frameHead.nLength = nLength;
    }
    m_frameHead.nDurationTicks = m_fileHead.nDurationTicks;
    m_frameHead.nFrameCount = m_fileHead.nFrameCount;
    //fwrite(&m_frameHead, 1, sizeof(m_frameHead), pFile);
    write(pFile, &m_frameHead, sizeof(m_frameHead));
}

int Write_(long nID, const void* pBuffer, int nLength,int iFream, unsigned int nDataType/* = HK_MFF_VIDEO | HK_MFF_MPEG4*/,int iStreamType)
{
    time_t temp;
    time(&temp);
    m_fileHead.lStartDateTime = (unsigned long long)temp;

    if(iFream==1)
    {
        m_bCurIsIVOP = true;
    }
    else
    {
        m_bCurIsIVOP = false;           
    }

    WriteFrameHead(g_fp, nID, nLength, nDataType, iStreamType);
    if( iStreamType == 4 )//add head video
        m_fileHead.iFileSize += m_fileHead.iFileSize+nLength+2;
    else
        m_fileHead.iFileSize += nLength;
    if(iStreamType == 4 )//video
    {
        //fwrite(&g_hkHeader, 1, 2, g_fp);
        write(g_fp, &g_hkHeader, 2);
    }

    //if( fwrite(pBuffer, 1, nLength, g_fp) <= 0 )
    if( write(g_fp, pBuffer, nLength) <= 0 )
    {
        //hk_SdInfoEmail(1);//email sd error
        hkSdParam.allSize = 14;
        return -1;
    }
    //WriteFileHeader(&m_fileHead);
    return 1;
}

int WriteFileHeader(FileHead_* pFileHead)
{
    if( NULL == pFileHead || NULL == g_fp )
    {
        return -1;
    }

    int iPosCur = lseek(g_fp, 0, SEEK_CUR);
    //fpos_t posCur;
    //fgetpos(g_fp, &posCur);
    lseek(g_fp, 0, SEEK_SET);

    //if( fwrite((void*)pFileHead, 1, sizeof(FileHead_), g_fp) <= 0 )
    if( write(g_fp,(void*)pFileHead, sizeof(FileHead_)) <= 0 )
    {
        return -1;
    }

    lseek(g_fp, iPosCur, SEEK_SET);
    //fsetpos(g_fp, &posCur);
    return 1;
}

static int sccISIframe(const char *buffer, int length)
{
    int i = 0;
    for( i=0; i<length-100; i++)
    {
        if( (*( buffer+ i  ) == 0x00 )
                && (*(buffer+ i + 1) == 0x00 )
                && (*(buffer + i + 2 ) == 0x00 )
                && ( *(buffer + i + 3 ) == 0x01) )
        {
            if( *(buffer+i+4)==0x6||*(buffer+i+4)==0x68||*(buffer+i+4)==0x67||*(buffer+i+4)==0x65|| ( *(buffer+i+4)==0x27 )||( *(buffer+i+4)==0x28 ) )
            {
                return 1;
            }
            else if( *(buffer+i+4)==0x61||*(buffer+i+4)==0x41|| *(buffer+ i + 4) == 0x21 ||  *(buffer+ i + 4) == 0x25 )
            {
                return 0;
            }
        }
    }
    return 1;
}



static unsigned int g_nLen=0;
static int g_nFlgX=0;

static char *g_cDataBufc=NULL;
static int OnDataBuf( int iIndex, const char *data, unsigned int iLen )
{
    if( iIndex==3)
    {
        memset(g_cDataBufc, 0, sizeof(g_cDataBufc));
        memcpy(g_cDataBufc, data, iLen);
        g_nFlgX= iIndex;
        g_nLen = iLen;
        return 1;
    }
    if( iIndex==2)
    {
        if( g_nFlgX!=3)
        {
            memset(g_cDataBufc, 0, sizeof(g_cDataBufc));
            g_nFlgX= 0;
            g_nLen = 0;
            return 0;
        }
        iLen -= 2;
        memcpy(g_cDataBufc+g_nLen, data+2, iLen);
        g_nLen += iLen;
        g_nFlgX= iIndex;
        return 1;
    }
    if( iIndex==1)
    {
        if( g_nFlgX!=2)
        {
            memset(g_cDataBufc, 0, sizeof(g_cDataBufc));
            g_nFlgX= 0;
            g_nLen = 0;
            return 0;
        }
        iLen -= 2;
        memcpy(g_cDataBufc+g_nLen, data+2, iLen);
        g_nLen += iLen;

        int flag = sccISIframe( g_cDataBufc, g_nLen);
        //flags=1;

        sccPushVideoData_TF(0,g_cDataBufc,g_nLen, flag, 4, 4, hostVideoDataPTF);
        g_nLen = 0;
        g_nFlgX= 0;
        return 1;
    }
    return 0;
}


static int Write(int obj, const char* buf, unsigned int len, long flags)
{
    printf("hkSdParam.leftSize:%d, hkSdParam.audio:%d, hkSdParam.loopWrite:%d, obj:%d, flags:%d...\n", hkSdParam.leftSize, hkSdParam.audio, hkSdParam.loopWrite, obj, flags);
    if( g_sdIsOnline == 0 )
    {
        return -1;
    }
	
	/*
    if(hkSdParam.leftSize <= HK_SD_SPLITE)//MB
    {
        RSCHangup(HK_AS_MONS, "MotionAlarmSDRecord");

        if (hkSdParam.audio == 1)
            RSCHangup( HK_AS_MONS, "MotionAlarmSDAudio" );

        g_ulDataLen = 0;
        if (hkSdParam.loopWrite == 1)
            b_hkSaveSd=true;

        return -1;
    }
	*/
	
    if( obj == max_count+2)//audio
    {
        sccPushVideoData_TF(0, buf, len, 1, 4, 10, hostVideoDataPTF);
        return len;
    }

    HK_VHeader hkHeader;
    memcpy( &hkHeader, buf, 2 );
    if( hkHeader.fragx != 0 )
    {
        if( g_cDataBufc ==NULL)
        {
            g_cDataBufc = malloc( 200*1024);
        }
        if( g_cDataBufc != NULL )
        {
            OnDataBuf( hkHeader.fragx, buf, len );
        }
        return len;
    }
    int iIsframe = sccISIframe( buf, len);
    //iIsframe=1;
    sccPushVideoData_TF(0, buf, len, iIsframe, 4, 4, hostVideoDataPTF);
    return len;
}

static int DoEvent( const char* devname, int obj, const char* ev ) 
{
#if 0
	HKFrameHead *pFrameHead;
    int ec, mc;
	// char* ev;
    HKLG_DEBUG("DoEvent(%s, %d, %s)", devname, obj, ev);

//	printf("File_sd DoEvent in..........\n");
    if (ev == NULL)
        return 1;
	
	pFrameHead = CreateFrameA((char*)ev, strlen(ev) );
	ev = GetParamStr( pFrameHead, HK_KEY_EVENT );
	pthread_rwlock_wrlock(&fd_rwlock);

	if (strcmp(ev, HK_EVENT_ALARM) == 0)
	{
		alarm_on = 1;
    }

    pthread_rwlock_unlock(&fd_rwlock);
	DestroyFrame(pFrameHead);
#endif
    return 0;
}

static int sd_open( char *cTime, char *cFileName )
{
    if (0 == g_sdIsOnline)
    {
        return -1;
    }

    char cPatch[64] = {0};
    if( g_fp != NULL)
    {
        close(g_fp);
        g_fp = NULL;
    }
    if (NULL == g_fp)
    {
        snprintf(cPatch, sizeof(cPatch), "/mnt/mmc/snapshot/%s.hkv", cTime);
        //if ( (g_fp = fopen(cPatch, "w+b")) == NULL )
        if ( (g_fp = open(cPatch, O_RDWR|O_CREAT, 600)) == NULL )
        {
            //b_hkSaveSd=true;
            printf( "open file fail\n" );
            wrap_sys_restart( );
            return -1;
        }
        char keyBuf[12]={0};
        sprintf(keyBuf, "%d",g_iTfCount++ );
        char tmpbuf[512] = {0};
        snprintf(tmpbuf, sizeof(tmpbuf), "%s.hkv", cTime);
        DictSetStr( g_TFPacket, keyBuf, tmpbuf );

        memset(&m_fileHead, 0, sizeof(m_fileHead));
        m_fileHead.nFileHeadVer = FILE_HEAD_VER;
        memcpy(m_fileHead.cFileMark, FILE_HEADER_MASK, 3);

        WriteFileHeader(&m_fileHead);

        if (hkSdParam.sdrecqc == 1)
            HI_MPI_VENC_RequestIDRInst(0);
        else
            HI_MPI_VENC_RequestIDRInst(1);
    }
    return 0;
}

int g_deleteTfData = 0;

static void sd_deleteRec()
{
    g_Delete_Flag = 1;

    char keyBuf[64]={0};
    char cPatch[64]={0};

    sprintf(keyBuf, "%d", g_deleteTfData++);
    char *cFile = DictGetStr(g_TFPacket, keyBuf );
    if( cFile != NULL )
    {
        snprintf(cPatch,sizeof(cPatch), "rm -r /mnt/mmc/snapshot/%s", cFile);
        system(cPatch);
        system("sync");//delete from file name
        DictDeleteKey(g_TFPacket, keyBuf);
    }
    sprintf(keyBuf, "%d", g_deleteTfData++);
    cFile = DictGetStr(g_TFPacket, keyBuf );
    if( cFile != NULL )
    {
        snprintf(cPatch,sizeof(cPatch), "rm -r /mnt/mmc/snapshot/%s", cFile);
        system(cPatch);
        system("sync");
        DictDeleteKey(g_TFPacket, keyBuf);
    }
    sprintf(keyBuf, "%d", g_deleteTfData++);
    cFile = DictGetStr(g_TFPacket, keyBuf );
    if( cFile != NULL )
    {
        snprintf(cPatch,sizeof(cPatch), "rm -r /mnt/mmc/snapshot/%s", cFile);
        system(cPatch);
        system("sync");
        DictDeleteKey(g_TFPacket, keyBuf);
    }

    g_Delete_Flag = 0;
    return;
    

    /*
    char cPatch[64]={0};
    strcpy(cPatch,"/mnt/mmc/snapshot");
    char cDel[128]={0}; 
    snprintf(cDel,sizeof(cDel),"rm -r %s/$(ls %s -rt | sed -n '1p')",cPatch, cPatch );
    system(cDel);
    system("sync");
    //printf("scc..delTF=%s.......\n", cDel);

    snprintf(cDel,sizeof(cDel),"rm -r %s/$(ls %s -rt | sed -n '2p')",cPatch, cPatch );
    system(cDel);
    system("sync");
    //printf("scc..delTF=%s.......\n", cDel);

    snprintf(cDel,sizeof(cDel),"rm -r %s/$(ls %s -rt | sed -n '3p')",cPatch, cPatch );
    system(cDel);
    system("sync");
    //printf("scc..delTF=%s.......\n", cDel);

    printf("scc..delTF=%s.......\n", cDel);

    g_Delete_Flag = 0;
    */
}

static int Sd_check()
{
    struct stat st;
    if (stat("/mnt/mmc/snapshot", &st) == 0)
    {
        return 1;
    }
    return 0;
}

void SD_RSLoadObjects(RegisterFunctType reg) 
{
    memset(&file_r, 0,sizeof(file_r));
    struct stat a, b;
    stat("/mnt", &a);
    if ( ((stat("/mnt/mmc", &b) == 0) && (a.st_dev != b.st_dev)) )
    {
        file_sd_inst.SetIRQEventCallback = &SetIRQEventCallback;
        file_sd_inst.Retrieve      = &Retrieve;
        file_sd_inst.GetObjectInfo = &GetObjectInfo;
        file_sd_inst.Open          = &Open;
        file_sd_inst.Read          = &Read;
        file_sd_inst.Write         = &Write;
        file_sd_inst.DoEvent       = &DoEvent;
        file_sd_inst.Close         = &Close;
        file_sd_inst.Convert       = NULL;
        ev_irq = NULL;

        (*reg)(&file_sd_inst);

        mkdir("/mnt/mmc/snapshot", 0755);
        if( Sd_check()==1 )
        {
            //sd_initSd();
        }
        else
        {
            g_sdIsOnline = 0;
        }
    }
}

static int sccGetVideoDataSlaveTF(int pStreamType, char *pVideoData, unsigned int *nSize, unsigned int *iFream, int *iResType, int *iStreamType);


//int g_testTf=0;
static int GetTfDataWrite()
{
    int len = 0;
    int iFream = 0;
    int iResType = 0;
    int iStreamType = 0;

    int iflag = sccGetVideoDataSlaveTF( 0, g_cDataBuf, &len, &iFream, &iResType, &iStreamType );

    //g_testTf = len;
    //printf("Get flag=%d,,fream=%d..len=%d.streamType=%d.\n", iflag, iFream, len, iStreamType);
    if ( (len <= 0) || (iflag==0) )
    {
        return 0;
    }
    //unsigned long long LenTemp = g_ulDataLen/1024;
    unsigned int LenTemp = g_ulDataLen/1048576;//1024*1024 //count write data size.

    /**record split**/
    if (hkSdParam.splite <= 0)
        hkSdParam.splite = 50;

#if (DEV_BAFU)
    if ((LenTemp >= (hkSdParam.splite)) || (1 == g_KeySplit))
#else
    if ( LenTemp >= (hkSdParam.splite) )
#endif
    {
    #if (DEV_BAFU)
        g_KeySplit = 0;
    #endif

        WriteFileHeader(&m_fileHead);
        if (g_fp != NULL)
        {
            close(g_fp);
            g_fp = NULL;
        }

        int isdOpen;
        char nm[64]={0};
        g_ulDataLen = 0;
        char cFileName[64]={0};
        GetTimeChar(nm, cFileName);

        isdOpen = sd_open( nm, cFileName );
        //HK_DEBUG_PRT("LenTemp:%d, hkSdParam.splite:%d, nm:%s, isdOpen:%d\n", LenTemp, hkSdParam.splite, nm, isdOpen);
        if( isdOpen == -1 )
            return 0;
    }

    if (g_fp != NULL)
    {
        if (4 != iStreamType)
        {
            //printf("scc........audio........\n");
            g_ulDataLen += len;
            Write_( 0, g_cDataBuf, len, 0, HK_MFF_AUDIO|HK_MFF_G711, 0 );
            return len;
        }

        g_hkHeader.resolution = iResType;
        g_ulDataLen += len;
        //printf("scc.iFream=%d...streamType=%d....\n", iFream, iStreamType);
        Write_( 0, g_cDataBuf, len, iFream, HK_MFF_VIDEO|HK_MFF_MPEG4, iStreamType );
        return len;
    }
    return len;
}

int g_GetAllTfFile=0;

static void sccReadSdFileData()
{
    printf("sccReadSdFileData......start...........\n");
    if( g_TFPacket == NULL)
        g_TFPacket = DictCreate( 0, 0 );

    int iCount=0;
    FILE *fp = NULL;
    g_GetAllTfFile =1;
    if (!(fp = popen("ls /mnt/mmc/snapshot", "r"))) 
    {
        printf("OnLocalReadSdData popen failed with:\n");
        g_GetAllTfFile =0;
        return; 
    }

    char tmpbuf[512] = {0};
    char buf[512]={0};
    Dict *TFPacketFile=DictCreate( 0, 0 );
    int iTfFileCount = 0;
    char keyBuf[12]={0};
    while (fgets(buf, sizeof(buf), fp)) 
    {
        sscanf(buf, "%[^\n]", tmpbuf);
        sprintf(keyBuf, "%d", iTfFileCount++ );
        DictSetStr( TFPacketFile, keyBuf, tmpbuf );
        //printf("...%s.....11..%d...\n", tmpbuf,iTfFileCount);
    }
    if (fp)  
    {
        pclose(fp);
        fp = NULL;
    }

    g_iTfCount=0;
    int ic=0;
    for(ic=0; ic < iTfFileCount; ic++ )
    {
        char ckeyBuf[12]={0};
        sprintf(ckeyBuf, "%d", ic );
        char *cFileName = DictGetStr( TFPacketFile, ckeyBuf );

        char cPatch[128]={0};
        sprintf(cPatch, "ls -rt /mnt/mmc/snapshot/%s", cFileName );
        //printf("file name=%s..........\n", cPatch);
        FILE *cfp = NULL;
        int iFileCount=0;
        if (!(cfp = popen(cPatch, "r"))) 
        {
            printf("..............OnLocalReadSdData popen failed with:\n");
            continue;
        }
        else
        {
            char cbuf[512]={0};
            char cfPatch[128]={0};
            while (fgets(cbuf, sizeof(cbuf), cfp)) 
            {
                iFileCount =1;
                char cName[64]={0};
                char keyBuf[12]={0};
                sprintf(keyBuf, "%d", iCount++ );
                sscanf(cbuf, "%[^\n]", cName);
                sprintf(cfPatch, "%s/%s", cFileName, cName );
                DictSetStr( g_TFPacket, keyBuf, cfPatch );

                //printf("get file name =%s...key=%s...\n", cfPatch, keyBuf);
                g_iTfCount++;
            }
            if( iFileCount == 0 )
            {
                printf("scc Delete from File = %s.......\n", tmpbuf);
                snprintf(cfPatch,sizeof(cfPatch), "rm -rf /mnt/mmc/snapshot/%s", tmpbuf);
                system(cfPatch);
                system("sync");//delete from file
            }
            if (cfp)  
            {
                pclose(cfp);
                cfp = NULL;
            }
        }
    }
    if( TFPacketFile != NULL )
        DictDestroy(TFPacketFile);

    printf("sccReadSdFileData......End=%d...........\n",g_iTfCount);
    g_GetAllTfFile =0;
}

/*
static void sccReadSdFileData()
{
    if( g_TFPacket == NULL)
        g_TFPacket = DictCreate( 0, 0 );

    int iCount=0;
    FILE *fp = NULL;
    g_GetAllTfFile =1;
    if (!(fp = popen("ls -rt /mnt/mmc/snapshot", "r"))) 
    {
        printf("OnLocalReadSdData popen failed with:\n");

        g_GetAllTfFile =0;
        return; 
    }

    char tmpbuf[512] = {0};
    char buf[512]={0};
    g_iTfCount=0;
    while (fgets(buf, sizeof(buf), fp)) 
    {
        sscanf(buf, "%[^\n]", tmpbuf);
        char cPatch[64]={0};
        sprintf(cPatch, "ls -rt /mnt/mmc/snapshot/%s", tmpbuf );
        printf("TF file=%s.........\n", tmpbuf);
        FILE *cfp = NULL;
        int iFileCount=0;
        if (!(cfp = popen(cPatch, "r"))) 
        {
            printf("..............OnLocalReadSdData popen failed with:\n");
            continue;
        }
        else
        {
            char cbuf[512]={0};
            while (fgets(cbuf, sizeof(cbuf), cfp)) 
            {

                iFileCount =1;
                char cName[64]={0};
                char keyBuf[12]={0};
                sprintf(keyBuf, "%d", iCount++ );
                sscanf(cbuf, "%[^\n]", cName);
                //printf("get file name =%s...key=%s...\n", cName, keyBuf);
                sprintf(cPatch, "%s/%s", tmpbuf, cName );
                DictSetStr( g_TFPacket, keyBuf, cPatch );

                g_iTfCount++;
            }
            if( iFileCount == 0 )
            {
                printf("scc Delete from File = %s.......\n", tmpbuf);
                snprintf(cPatch,sizeof(cPatch), "rm -rf /mnt/mmc/snapshot/%s", tmpbuf);
                system(cPatch);
                system("sync");//delete from file
            }
            if (cfp)  
            {
                pclose(cfp);
                cfp = NULL;
            }
        }
    }
    if (fp)  
    {
        pclose(fp);
        fp = NULL;
    }

    g_GetAllTfFile =0;
    printf("sccReadSdFileData......End=%d...........\n",g_iTfCount);
}
*/

int TFTIME(HI_VOID)
{
    int iCount = 0;
    int iret = 0;

#if ENABLE_ONVIF
    IPCAM_setTskName("TF_Thread");  
#endif

    g_cDataBuf = (char *)malloc(200*1024*sizeof(char));
    if (NULL == g_cDataBuf)
    {
        printf("...%s...malloc error, %s\n", __func__, strerror(errno)); 
        return 0;
    }
    sccReadSdFileData();

    while ( 1 )
    {
        if (g_TF_start == 0)//close
        {
            sleep(2);
            continue;
        }

        iret = GetTfDataWrite();
        usleep(10000);
        iCount++;

        if ( (iCount > 3000) && (g_sdIsOnline != 0) )  
        {
            iCount=0;
            GetStorageInfo();
            if (hkSdParam.leftSize <= HK_SD_SPLITE+400)//MB
            {
                if( hkSdParam.loopWrite == 1 )
                {
                    sd_deleteRec();
                }
            }
        }
    }

    if (g_cDataBuf) 
    {
        free(g_cDataBuf);
        g_cDataBuf = NULL;
    }
    g_TF_flag =0;
    g_TF_start=0;

    if( hkSdParam.loopWrite == 1 )
    {
            b_hkSaveSd=true;
    }
    pthread_detach(pthread_self()); 
    return 1;
}

int CreateTFThread(void)
{
    if (0 == g_TF_flag)
    {
        int ret = -1;
        pthread_t tfid;
        g_TF_flag = 1;

        ret = pthread_create(&tfid, NULL, (void *)TFTIME, NULL);
        if (0 != ret)
        {
            HK_DEBUG_PRT("create TF record thread failed!\n");
            return -1;
        }
    }
    return 1;
}

static int sd_video_start()
{
    char nm[64] = {0};
    char cFileName[64]={0};
    int result = TFsccInitVideoData(0);
    if (-1 == result)
    {
        HK_DEBUG_PRT("......TFsccInitVideoData failed !\n");
        return 0;
    }
    sccResetVideDataTF(0, hostVideoDataPTF);
    CreateTFThread();

    GetTimeChar(nm, cFileName);
    memset(&m_fileHead, 0, sizeof(m_fileHead));
    m_fileHead.nFileHeadVer = FILE_HEAD_VER;
    memcpy(m_fileHead.cFileMark, FILE_HEADER_MASK, 3);

    int isdOpen = sd_open( nm, cFileName );//time
    if (isdOpen == -1)
        return 0;

    g_hkHeader.fragx = 0;
    g_hkHeader.flipex = 0;
    g_hkHeader.resolution = 0;
    g_hkHeader.encode = 4;
    g_hkHeader.flip = 0;
    g_hkHeader.version = 2;

    //start video thread
    sccStartVideoThread();
}

void sd_record_stop()
{
    printf(".........sd_record_stop...\n");
    if (g_TF_start == 0)
        return;

    g_TF_start = 0;
    sleep(1);
    g_ulDataLen = 0;

    WriteFileHeader(&m_fileHead);
    if( NULL != g_fp )
    {
        close(g_fp);
        g_fp = NULL;
    }
    return;
}

int sd_record_start()
{
    printf("[%s, %d]..........sd_record_start, g_TF_Start:%d... \n", __func__, __LINE__, g_TF_start);
    if (1 == g_TF_start)
    {
        HK_DEBUG_PRT("......SD card is already in recording thread !\n");
        return 1;
    }

    sd_video_start();
    g_TF_start = 1;

    return 0;

    /*
    int result = -1;
    char a[256] = {0}, nm[64] = {0};

    if( ((hkSdParam.splite <= 0) || (hkSdParam.leftSize <= HK_SD_SPLITE)) && (hkSdParam.loopWrite == 0) )
        return -1;

    result = TFsccInitVideoData(0);
    if (-1 == result)
    {
        HK_DEBUG_PRT("......TFsccInitVideoData failed !\n");
        return 0;
    }

    sccResetVideDataTF(0, hostVideoDataPTF);

    GetTimeChar(nm);
    int iSdrcqc = conf_get_int(HOME_DIR"/sdvideo.conf", HK_KEY_SDRCQC);
    if( iSdrcqc == 1 )
    {
        snprintf(a,sizeof(a), "ftN0=video.vbVideo.MPEG4;ftN1=File.SDStorage.in;opN1=%s;", nm);
    }
    else
    {
        snprintf(a,sizeof(a), "ftN0=video.vbVideo.M_JPEG;ftN1=File.SDStorage.in;opN1=%s;", nm);
    }

    result = ExecDial(HK_AS_MONS, "MotionAlarmSDRecord", a);
    if( result >= 0 && hkSdParam.audio==1 )
    {
        char cAudio[256]={0};
        snprintf(cAudio,sizeof(cAudio), "ftN0=audio.vbAudio.Out;ftN1=File.SDStorage.in;opN1=%s;", "audioin");
        result = ExecDial( HK_AS_MONS, "MotionAlarmSDAudio", cAudio);
    }
   
    return 1;
    */
}

//int g_iCountTest=0;
static int g_PushCount = 0;
int sccPushTfData(int pStreamType, char *pData, unsigned int nSize, short iFrame, int iResType, int iStreamType )
{
    //g_iCountTest = nSize;
    if ( g_TF_start == 0 || g_Delete_Flag == 1)
        return 0;

    if (g_PushCount >= 100)
    {
        g_PushCount = 0;
        sd_record_stop();
        sccResetVideDataTF(0, hostVideoDataPTF);
        b_hkSaveSd=true;
        return 0;
    }

    pthread_mutex_lock( &g_MutexLock_TF );
    sccPushVideoData_TF( pStreamType, pData, nSize, iFrame, iResType, iStreamType, hostVideoDataPTF );
    pthread_mutex_unlock( &g_MutexLock_TF );

    return 0;
}


static int sccPushVideoData_TF(int pStreamType,const char *pData,unsigned int nSize,short IFrame,int iResType,int iStreamType,VideoDataRecord_TF  *mVideoDataBuffer)
{
    //printf("...nSize: %d...\n", nSize);
    if(mVideoDataBuffer == NULL || nSize <= 0)
        return 0;

     //fprintf(stderr,"nSize = %d\r\n",nSize);
    if ( (mVideoDataBuffer->g_allDataSize + nSize) > MAX_VIDEODATA_HOSTSTREAM_TF || (nSize > 199600) \
            || (abs(mVideoDataBuffer->g_writeIndex - mVideoDataBuffer->g_readIndex) > (POOLSIZE_TF-1)) )
    {
        mVideoDataBuffer->g_bLost = 1;
        fprintf(stderr, "SD.......again again \r\n");
        g_PushCount++;
        usleep(100);
        return 0;
    }

    g_PushCount = 0;
    if( IFrame < 0 )
    {
        mVideoDataBuffer->g_bLost = true;
        printf("SD..no I P Frame**********************\n");
        return 0;
    }

    if( mVideoDataBuffer->g_bLost && IFrame != 1 )
    {
        //printf( "sd..lost--ccccccc\n" );
        return 0;
    }

    if( mVideoDataBuffer->g_writeIndex == POOLSIZE_TF ) mVideoDataBuffer->g_writeIndex = 0;

    mVideoDataBuffer->g_bLost = 0;
    if( mVideoDataBuffer->g_bAgain )
    {
        if( mVideoDataBuffer->g_CurPos + nSize < mVideoDataBuffer->g_readPos )
        {
            memcpy( mVideoDataBuffer->g_videoBuf + mVideoDataBuffer->g_CurPos ,pData,nSize );
            mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_writeIndex].IFrame = IFrame;
            mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_writeIndex].iEnc = iResType;
            mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_writeIndex].StreamType = iStreamType;

            mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_writeIndex].nPos = mVideoDataBuffer->g_CurPos;
            //printf( "again[%d][%d-%d]\n",g_writeIndex,g_CurPos,nSize );
            mVideoDataBuffer->g_CurPos += nSize;
            mVideoDataBuffer->g_allDataSize += nSize;
            mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_writeIndex].nSize = nSize;
            mVideoDataBuffer->g_writeIndex ++ ;
            mVideoDataBuffer->g_haveFrameCnt++;
        }
        else
        {
            mVideoDataBuffer->g_bLost = 1;
            printf( "lost--a\n" );
            usleep(10);
            return 0;
        }
    }
    else
    {
        if( mVideoDataBuffer->g_writePos + nSize < MAX_VIDEODATA_HOSTSTREAM_TF )
        {
            //printf( "push1[%d][%d-%d]\n",g_writeIndex,g_writePos,nSize );
            memcpy( mVideoDataBuffer->g_videoBuf + mVideoDataBuffer->g_writePos,pData,nSize );
            mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_writeIndex].IFrame = IFrame;
            mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_writeIndex].iEnc = iResType;
            mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_writeIndex].StreamType = iStreamType;

            mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_writeIndex].nPos  = mVideoDataBuffer->g_writePos;
            mVideoDataBuffer->g_allDataSize += nSize;
            mVideoDataBuffer->g_writePos += nSize;
            mVideoDataBuffer->g_CurPos += nSize;//mVideoDataBuffer->g_writePos;
            mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_writeIndex].nSize = nSize;
            mVideoDataBuffer->g_writeIndex ++ ;
            mVideoDataBuffer->g_haveFrameCnt ++;
        }
        else if( nSize < mVideoDataBuffer->g_readPos )
        {
            mVideoDataBuffer->g_CurPos = 0;
            mVideoDataBuffer->g_bAgain = 1;
            memcpy( mVideoDataBuffer->g_videoBuf,pData,nSize );
            //printf( "push2[%d][%d-%d]\n",g_writeIndex,g_writePos,nSize );
            mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_writeIndex].IFrame = IFrame;
            mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_writeIndex].iEnc = iResType;
            mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_writeIndex].StreamType = iStreamType;

            mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_writeIndex].nPos  = 0;
            mVideoDataBuffer->g_CurPos += nSize;
            mVideoDataBuffer->g_allDataSize += nSize;
            mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_writeIndex].nSize = nSize;
            mVideoDataBuffer->g_writeIndex ++ ;
            mVideoDataBuffer->g_haveFrameCnt ++;
        }
        else
        {
            mVideoDataBuffer->g_bLost = 1;
            printf( "SD...lost--b\n" );
            usleep(10);
            return 0;
        }
    }

    if( mVideoDataBuffer->g_haveFrameCnt >= POOLSIZE_TF )
    {
        mVideoDataBuffer->g_bLost = 1;
        printf("SD.....lost--dd\n");
        usleep(10);
    }
    return 0;
}


static int sccGetVideoData_TF(int pStreamType, char *pVideoData, unsigned int *nSize, unsigned int *iFream, int *iResType, int *iStreamType, VideoDataRecord_TF *mVideoDataBuffer);

static int sccGetVideoDataSlaveTF(int pStreamType, char *pVideoData, unsigned int *nSize, unsigned int *iFream, int *iResType, int *iStreamType)
{
    int ret = 0;
    if((pStreamType == 0) && (hostVideoDataPTF != NULL))
    {
        pthread_mutex_lock( &g_MutexLock_TF );
        ret = sccGetVideoData_TF( pStreamType, pVideoData, nSize, iFream, iResType, iStreamType, hostVideoDataPTF );
        pthread_mutex_unlock( &g_MutexLock_TF );
    }
    return ret;
}

static int sccGetVideoData_TF(int pStreamType, char *pVideoData, unsigned int *nSize, unsigned int *iFream, int *iResType, int *iStreamType, VideoDataRecord_TF *mVideoDataBuffer)
{
    *nSize = 0;
    
    if ((mVideoDataBuffer->g_allDataSize == 0) || (mVideoDataBuffer->g_haveFrameCnt == 0) || (mVideoDataBuffer->g_readIndex == mVideoDataBuffer->g_writeIndex))
    {
        mVideoDataBuffer->g_bAgain = 0;
        mVideoDataBuffer->g_writePos = 0;
        mVideoDataBuffer->g_readPos = 0;
        mVideoDataBuffer->g_CurPos = 0;
        mVideoDataBuffer->g_allDataSize= 0;
        mVideoDataBuffer->g_haveFrameCnt = 0;
        mVideoDataBuffer->g_writeIndex = 0;
        mVideoDataBuffer->g_readIndex = 0;
        //fprintf(stderr,"====so=====GET 1 NO DATA \r\n");

        return 0;
    }
    
    if( mVideoDataBuffer->g_readIndex == POOLSIZE_TF ) mVideoDataBuffer->g_readIndex = 0;

    if (mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].nSize == 0)
    {
        printf( "SD.......have some err!\n" );
        //mVideoDataBuffer->g_readIndex ++;
        return 0;
    }

    memcpy( pVideoData, mVideoDataBuffer->g_videoBuf + mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].nPos, mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].nSize  );
    //*pVideoData =   mVideoDataBuffer->g_videoBuf + mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].nPos;
    *nSize = mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].nSize;
    *iFream = mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].IFrame;
    *iResType =mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].iEnc; 
    *iStreamType = mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].StreamType;
    //if(mVideoDataBuffer->g_readPos > mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].nPos )
    if(mVideoDataBuffer->g_bAgain == 1 && mVideoDataBuffer->g_CurPos > mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].nPos )
    {
        mVideoDataBuffer->g_writePos = mVideoDataBuffer->g_CurPos;
        mVideoDataBuffer->g_bAgain = 0;
    }

    mVideoDataBuffer->g_haveFrameCnt --;
    mVideoDataBuffer->g_allDataSize -= mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].nSize ;
    mVideoDataBuffer->g_readPos = mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].nPos;
    mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].nSize = 0;
    mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].nPos = 0;
    mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].IFrame = 0;
    mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].iEnc = 0;
    mVideoDataBuffer->g_VideoData[mVideoDataBuffer->g_readIndex].StreamType = 0;

    mVideoDataBuffer->g_readIndex ++ ;

    return *nSize;
}

static void sccResetVideDataTF(int pStreamType, VideoDataRecord_TF *mVideoDataBuffer)
{
    HK_DEBUG_PRT("...... sd reset video data, pStreamType: %d ......\n", pStreamType);
    pthread_mutex_lock( &g_MutexLock_TF );

    mVideoDataBuffer->g_writePos     = 0;
    mVideoDataBuffer->g_readPos      = 0;
    mVideoDataBuffer->g_allDataSize  = 0;
    mVideoDataBuffer->g_bLost        = 0;
    mVideoDataBuffer->g_bAgain       = 0;
    mVideoDataBuffer->g_CurPos       = 0;
    mVideoDataBuffer->g_readIndex    = 0;
    mVideoDataBuffer->g_writeIndex   = 0;
    mVideoDataBuffer->g_haveFrameCnt = 0;
    memset(mVideoDataBuffer->g_videoBuf, 0, sizeof(mVideoDataBuffer->g_videoBuf));

    pthread_mutex_unlock( &g_MutexLock_TF );
}

int hk_test_tf_info()
{

    system("touch /mnt/sif/deo.conf");

    conf_set_int(HOME_DIR"/deo.conf", "tfStart", g_TF_start);
    conf_set_int(HOME_DIR"/deo.conf", "tfThFlag", g_TF_flag);
    conf_set_int(HOME_DIR"/deo.conf", "sdOnline", g_sdIsOnline);
    conf_set_int(HOME_DIR"/deo.conf", "loop_write", hkSdParam.loopWrite);
    conf_set_int(HOME_DIR"/deo.conf", "splite", hkSdParam.splite);

    conf_set_int(HOME_DIR"/deo.conf", HK_KEY_SDRCQC, hkSdParam.sdrecqc);
    //conf_set_int(HOME_DIR"/deo.conf", "size", g_iCountTest);

    //conf_set_int(HOME_DIR"/deo.conf", "getSize", g_testTf);
}
