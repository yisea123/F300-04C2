#ifndef _PROFIBUS_DP_H
#define _PROFIBUS_DP_H

#include "71x_type.h"
#include "71x_lib.h" 

#define UART_UART       0   //扩展板类型；双串口
#define PBUS_UART       1   //扩展板类型：PROFIBUS-DP + 串口

#define GSD_1           0
#define GSD_2           1   //GSD文件选择

//SE接口板与CPU芯片的引脚连接
#define SE_REQ_IT     GPIO_BitRead(GPIO2,9)   //0：SE初始化完毕         1：SE初始化等待      
#define SE_S_RTS      GPIO_BitRead(GPIO1,11)  //0：SE等待（允许）接收   1：SE拒绝接收        
#define SE_LINK       GPIO_BitRead(GPIO1,12)  //0：SE已经成功连接DP总线 1：SE未成功连接DP总线

#define Pbus_InitFail()      (SE_REQ_IT)    //true:SE接口板初始化失败  false:初始化成功
#define Pbus_NotLinked()     (SE_LINK)      //true:PROFISBU总线未连接  false:PROFIBUS总线已经连接
//#define Pbus_NotLinked()     (SE_S_RTS)      //true:PROFISBU总线未连接  false:PROFIBUS总线已经连接



extern u8 gu8_ExtType;     //扩展板类型
extern u32 gu32_GSDType;   //GSD文件
extern u32 gu32_FollowMasterSwitch;    //工作参数标定参数由主站控制开关

extern bool Pbus_CheckExt(void);
extern void UARTInit_Pbus(void);
u8 Pbus_Checksum(u8 *fu8p_Array, u8 fu8_i);
void Pbus_StartSend(u8 *fu8_Array, u8 fu8_TxdLen, u8 fu8_RxdLen);
void IRQ_Pbus(void);
void Com_Pbus_DP(void);

#endif
