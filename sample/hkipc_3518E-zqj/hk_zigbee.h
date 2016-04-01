#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef __LIST_H__
#define __LIST_H__

#define uint8   unsigned char 
#define uint16  unsigned short int 
#define uint32  unsigned long 

#define MAX_RESERVED_LEN 128 //保留字段的最大长度 


#define LIANYONG  1 //lianyong zigbee

/*  zigbee  device code   */
#define CMD_CLASS_HEAD        0xFE

#define CMD_CLASS_KAIGUAN    ( 0x01 << 8 | 0x00 )       // 开关
#define CMD_CLASS_CHUANGLIAN ( 0x02 << 8 | 0x00 )         // 窗帘
#define CMD_CLASS_WENSHIDU   ( 0x03 << 8 | 0x00 )           // 温湿度，现在用作红外报警器
#define CMD_CLASS_BAOJINGQI  ( 0x04 << 8 | 0x00 )        // 报警器
#define CMD_CLASS_TIAOGUANG  ( 0x08 << 8 | 0x00 )          // 调光设备
#define CMD_CLASS_HONGWAI    ( 0x06 << 8 | 0x00 )        // 红外遥控器
#define CMD_CLASS_CHAZUO     ( 0x07 << 8 | 0x00 )          // 插座
#define CMD_CLASS_MENCI      ( 0x01 << 8 | 0x10 )          // 门磁
#define CMD_CLASS_YANWU      ( 0x03 << 8 | 0x10 )           // 烟雾报警器
#define CMD_CLASS_RANQI      ( 0x04 << 8 | 0x10 )               // 燃气探测器
#define CMD_CLASS_SOS        ( 0x06 << 8 | 0x10 )                // SOS

/*外部接口使用的命令start*/
#define LIGHT_ON               1
#define LIGHT_OFF              2
#define LIGHT_STATUS           18

#define CHUANGLIAN_UP          3
#define CHUANGLIAN_DOWN        4
#define CHUANGLIAN_STOP        5
#define CHUANGLIAN_STATUS      19

#define HONGWAIBAOJING_ALARM   6
#define HONGWAIBAOJING_STATUS  7
#define HONGWAIBAOJING_ENABLE  8
#define HONGWAIBAOJING_DISABLE 9

#define CHAZUO_ON              10
#define CHAZUO_OFF             11
#define CHAZUO_STATUS          20

#define ZIGBEE_LEARN_MODE      12
#define ZIGBEE_REBOOT          21

#define HONGWAIQIU_TX          13
#define HONGWAIQIU_LEARN       14
#define HONGWAIQIU_DATA        15
#define HONGWAIQIU_START       16
#define HONGWAIQIU_STOP        17

/*外部接口使用的命令end*/

/*设备状态*/
#define STATUS_ON              1
#define STATUS_OFF             2
#define STATUS_STOP            3
#define STATUS_ONALARMING      4
#define STATUS_UNALARMING      5
#define STATUS_ALARMING        6
#define STATUS_OFFLINE        -1


/* control cmd*/
#define UART_MSG_NONE           0x0 
#define PRINT_HUMAN_READABLE    0x1     //ascii字符串消息
#define REP_DEV_DESC            0x2     //设备注册消息
#define REP_DEV_MSG             0x3     //设备发送的消息
#define REP_DEV_ANNCE           0x4     //有设备加入到网络
#define SEND_IDENTIFY           101   //向设备发送识别消息，设备收到该消息后会返回设备描述信息
#define SEND_DEV_MSG            102   //向设备发送消息
#define LEAVE_REQUEST           103   //暂时没用
#define ACTION_SHOW_BANNER      201   //令zb网关输出序列号
#define ACTION_REBOOT           202   //令zb网关重启
#define ACTION_ENABLE_JOINING   203   //暂时没用
#define ACTION_DISABLE_JOINING  204   //暂时没用

#define DEV_CMD_DEVDESC         0x00  // 设备描述， 包括地址、类型、数量等
#define DEV_CMD_RSSI            0x01  //发送该命令给zigbee会返回信号强度存放在SerialAppDevMsg_t的num字段
#define DEV_CMD_ASCII           0x02  // ascii字符串消息,  存放于 opacity 字段
#define DEV_CMD_BUSY            97    //表示设备忙
#define DEV_CMD_INVALID         98    //表示非法无效消息
#define DEV_CMD_ERROR           99   //表示设备遇到错误

// 100 以上的 用于各zigbee设备的各自命令
#define DEV_CMD_BASE  100

/*开关插座控制命令*/
#define CMD_SWITCH_ST             (DEV_CMD_BASE+1)  //查询状态
#define CMD_SWITCH_ON             (DEV_CMD_BASE+2)  //开
#define CMD_SWITCH_OFF            (DEV_CMD_BASE+3)  //关

/*窗帘控制命令*/
#define CMD_TRISTATE_ST           (DEV_CMD_BASE+1) //查询状态
#define CMD_TRISTATE_UP           (DEV_CMD_BASE+2) //上
#define CMD_TRISTATE_OVER         (DEV_CMD_BASE+3) //停止
#define CMD_TRISTATE_DOWN         (DEV_CMD_BASE+4) // 下

/*红外球控制命令*/
#define CMD_DC6008_TX             (DEV_CMD_BASE+1) //发送码值
#define CMD_DC6008_STUDYMODE      (DEV_CMD_BASE+2) // 学习模式
#define CMD_DC6008_STUDYDATA      (DEV_CMD_BASE+3) // 学习到的码值
#define CMD_DC6008_TEST_START     (DEV_CMD_BASE+4) // 开始测试
#define CMD_DC6008_TEST_STOP      (DEV_CMD_BASE+5) //停止测试

/*报警类设备控制命令*/
#define CMD_ALARMMONI_ALARMING    (DEV_CMD_BASE+1)  //报警
#define CMD_ALARMMONI_GETABILITY  (DEV_CMD_BASE+2)  //查询状态
#define CMD_ALARMMONI_ENABLE      (DEV_CMD_BASE+3)  //布防
#define CMD_ALARMMONI_DISABLE     (DEV_CMD_BASE+4)  //撤防


#define MAX_CMD_BUF_SIZE 512
#define DEBUG 0

typedef struct DEVDESC
{
    uint8 msg_type;
    uint8 devshortaddr[2];  //设备短地址，网关记录的地址
    uint8 devlongaddr[8];   //设备长地址，mac地址
    uint8 devtype[2];      //设备类型
    uint8 devchannel;
    uint8 devreusebyte;    //复用字段
    uint8 devctrlcmd;      //控制指令
    uint8 devcmddata[MAX_RESERVED_LEN];  //保留字段，指令数据，目前应用到红外万能遥控器码值和调色灯颜色，可变长度
    int   devstatus;       //设备状态，在线或者离线
}Devdesc;

struct Node{
  Devdesc *data;
  struct Node* next;
};
typedef struct Node Node;

#endif

