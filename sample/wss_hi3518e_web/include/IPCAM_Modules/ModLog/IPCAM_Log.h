#ifndef _IPCAM_LOG_H_
#define _IPCAM_LOG_H_
#define IPCAM_SQLIE_NAME		"/sys_fac/ipcam.db"
#define IPCAM_LOG_TABLE			"log"
typedef struct {
int 			Year;
unsigned char 	Mon;
unsigned char 	Day;
unsigned char 	Hour;
unsigned char 	Min;
unsigned char	Sec;
}LOGTIME, *LPLOGTIME;

//INT  LOG_Init();
INT  LOG_DelInit();
void LOG_Close();
INT  LOG_Write(int type, char* user, char* time, char* message);
INT LOG_Read(int nMode , int LogType, char* strUser , char* startTime ,char* endTime ,void* Callback);

#endif

