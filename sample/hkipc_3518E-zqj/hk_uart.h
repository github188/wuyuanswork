
#ifndef __HK_UART_H__
#define __HK_UART_H__

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>
#include <errno.h> 
#include <sys/types.h>  
#include <sys/stat.h>  

#define PRINT_ENABLE    1
#if PRINT_ENABLE
    #define UART_DBG_PRINT(fmt...)  \
        do {                        \
            printf("[%s - %d]: ", __FUNCTION__, __LINE__);\
            printf(fmt);            \
        }while(0)
#else
    #define UART_DBG_PRINT(fmt...)  \
        do { ; } while(0)
#endif

#define CMD_NUM        32
#define CMD_BITNUM     5 //32*5 array.

/*uart control command*/
typedef enum uart_command {
    CMD_STOP             = 0,
    CMD_FORWARD          = 1,
    CMD_BACKWARD         = 2,
    CMD_LEFT             = 3,
    CMD_RIGHT            = 4, 
    CMD_AUTOCLEAN        = 5,
    CMD_SPOTCLEAN        = 6,
    CMD_MOPPING          = 7,
    CMD_VOICE            = 8,
    CMD_MODE             = 9,
    CMD_AUTOCHARGE       = 10,
    CMD_QUERY_WORK_MODE  = 11,
    CMD_QUERY_CLEAN_MODE = 12,
    CMD_QUERY_BATTERY    = 13,
    CMD_ANDSON_MD        = 14, /*ANDSON: Motion Detect*/
    CMD_ANDSON_IO        = 15, /*ANDSON: IO alarm*/ 
    CMD_ANDSON_PIR       = 16, /*ANDSON: PIR alarm*/
    CMD_ANDSON_433       = 17, /*ANDSON: 433 alarm*/
    CMD_ANDSON_HOUR      = 18, /*ANDSON: set jsw time Hour*/
    CMD_ANDSON_MINUTES   = 19, /*ANDSON: set jsw time Minutes*/
    CMD_SET_WIFI         = 20,  //set wifi
    CMD_EXT  //extension
} ENUM_UART_CMD;

/*robot current work mode*/
typedef enum uart_work_mode {
    MODE_CEASE     = 0xF0, /*sleep mode*/
    MODE_SWEEP     = 0xF1, /*sweep mode*/
    MODE_SPOT      = 0xF2, /*spot part clean mode*/
    MODE_TELE      = 0xF3, /*remote control mode*/
    MODE_DOCKING   = 0xF4, /*to re-charge mode*/
    MODE_CHARGEING = 0xF5, /*charging mode*/
    MODE_MOPPING   = 0xF6, /*mop floor mode*/
    MODE_ERR       = 0xF7  /*error mode*/
} ENUM_WORK_MODE;

/*robot information response code*/
typedef enum uart_response_code {
    RESP_VOICE_ON     = 0xE0,
    RESP_VOICE_OFF    = 0xE1,
    RESP_MUTE_CLEAN   = 0xD1,
    RESP_SPOT_CLEAN   = 0xD2,
    RESP_STANDBY      = 0xC0,
    RESP_CHARGE_ONE   = 0x6A,
    RESP_CHARGE_TWO   = 0x6B,
    RESP_CHARGE_THREE = 0x6C,
    RESP_CHARGE_FULL  = 0x7F,
    RESP_IDENTIFY_ERR = 0xEE 
} ENUM_RESPOND_CODE;


/** uart operate interfaces **/
int UART_CtrlCmd_Send(ENUM_UART_CMD enCmd, int iParam);
int UART_CtrlCmd_Recv(unsigned int *nRecv);

#endif  /* hk_uart.h (zqj) */

