/*
Description:            打印状态下相关功能函数
Author:                 丛海旭
Date:                   2013-12-9
*/

/*
80列打印机80列
16列打印机16列

*代表预留空格


**************************自动打印格式******************************************
中文80列打印格式如下：
                                   包装明细表
--------------------------------------------------------------------------------
总累计次数    日期      时间   配方 配方累计次数  目标值   包装结果      误差   
                                                  (公斤)    (公斤)     (公斤)   
        1   2014/02/15  06:21   *2         215   **12.00   **12.05   ****0.05   
       12   2014/02/15  06:34   *3          21   **22.00   **22.03   ****0.03   
123456789   2014/03/12  15:26   *1   123456789   **40.00   **39.99   ***-0.01   

中文32列打印格式如下：

           包装明细表
单位:公斤
总累计次数 配方  目标值    结果
--------------------------------
        1   *5  **19.99  **19.99
123456789   *1  **19.99  **40.03



中文16列打印格式如下：

   包装明细表
单位:公斤
 次数 配方 结果
----------------
    1 *5 **19.99
12345 *1 **40.03


英文80列打印格式如下：
                                 Packing Detail
--------------------------------------------------------------------------------
Total Times    Date      Time   Rec.  Rec.Times   Target    Result      Error   
                                                    (kg)      (kg)       (kg)   
        1   2014/02/15  06:21   *2         215   **12.00   **12.05   ****0.05   
       12   2014/02/15  06:34   *3          21   **22.00   **22.03   ****0.03   
123456789   2014/03/12  15:26   *1   123456789   **40.00   **39.99   ***-0.01   

英文32列打印格式如下：

         Packing Detail
Unit:kg
Total Times Rec  Target   Result
--------------------------------
        1   *5  **19.99  **19.99
123456789   *1  **19.99  **40.03

英文16列打印格式如下：

 Packing Detail
Unit:kg
Times Rec Result
----------------
    1 *5 **19.99
12345 *1 **40.03

********************************************************************************

*************************总累计报表打印*****************************************
中文80列打印格式如下：
                                   总累计报表
--------------------------------------------------------------------------------
       日期              时间          总累计次数         总累计重量            
    2014/02/01          15:36          123456789          98765432.1  吨         

中文32列打印格式如下：

           总累计报表
时间: 2014/02/01 15:36
单位: 吨
--------------------------------
总累计次数:            123456789
总累计重量:           98765432.1
--------------------------------

中文16列打印格式如下：

   总累计报表
2014/02/01 15:36
单位: 吨
----------------
总次数:123456789
总重: 98765432.1
----------------


英文80列打印格式如下：
                                 Total Report
                                                                2014/02/01 15:36
--------------------------------------------------------------------------------
       Date              Time         Total Times         Total Value           
    2014/02/01          15:36          123456789          98765432.1 t          


英文32列打印格式如下：

          Total Report
Time:2014/02/01 15:36
Unit:t
--------------------------------
Total Times:           123456789
Total Value:          98765432.1
--------------------------------

英文16列打印格式如下：

  Total Report
2014/02/01 15:36
Unit:t
----------------
Times: 123456789
Val.: 98765432.1
----------------
********************************************************************************

*************************配方累计报表打印***************************************
中文80列打印格式如下：
                                  配方累计报表
                                                                2014/02/01 15:36
--------------------------------------------------------------------------------
  配方      目标值      配方累计次数         配方累计重量                总误差 
            (公斤)                               (公斤)                  (公斤)
   *2    **12.00 kg               1             12.02 kg             ****0.02 kg
   *3    **22.00 kg       *******20        *****43.97 kg             ***-0.03 kg


中文32列打印格式如下：

          配方累计报表
时间: 2014/02/01 15:36
单位: 公斤
--------------------------------
配方:                         *1
目标值:                  **40.00
配方累计次数:                  8
配方累计重量:             320.00
总误差:                  ***0.00
--------------------------------


中文16列打印格式如下：

  配方累计报表
2014/02/01 15:36
单位:公斤
----------------
配方:         *1
目标值:  **40.00
次数:          8
重量:     320.00
总误差:  ***0.00
----------------
……
……
……


英文80列打印格式如下：
                                  Rec. Report
                                                                2014/02/01 15:36
--------------------------------------------------------------------------------
  Rec.      Target        Rec. Times           Rec. Value                 Error 
             (kg)                                 (kg)                     (kg) 
   *2    **12.00 kg               1             12.02 kg             ****0.02 kg
   *3    **22.00 kg       *******20        *****43.97 kg             ***-0.03 kg


英文32列打印格式如下：

          Rec. Report
Time: 2014/02/01 15:36
Unit: 公斤
--------------------------------
Rec.:                         *1
Target:                  **40.00
Rec. Times:                    8
Rec. Value:               320.00
Error:                   ***0.00
--------------------------------


英文16列打印格式如下：

  Rec. Report
2014/02/01 15:36
Unit:kg
----------------
Rec.:         *1
Target:  **40.00
Times:         8
Val.:     320.00
Error:   ***0.00
----------------
……
……
……
********************************************************************************

*************************配方设置报表打印***************************************
中文80列打印格式如下：
                                  配方设置报表
                                                                2014/02/01 15:36
--------------------------------------------------------------------------------
  配方     目标值    大投提前量    中投提前量         落差值          零区值    
           (公斤)       (公斤)         (公斤)         (公斤)          (公斤)    
   *2    **12.00       ***5.00        ***2.00        ***0.10         ***1.00    
   *3    **22.00       **12.00        **12.00        **12.00         ***1.00    
   *1    **40.00       **12.00        **12.00        **12.00         ***2.00    


中文32列打印格式如下：

          配方设置报表
时间: 2014/02/01 15:36
单位: 公斤
--------------------------------
配方:                         *1
目标值:                  **40.00
大投提前量:              **30.00
中投提前量:              **10.00
落差值:                  ***0.50
零区值:                  ***2.00
--------------------------------


中文16列打印格式如下：

  配方设置报表
2014/02/01 15:36
单位:公斤
----------------
配方:         *1
目标值:  **40.00
大投:    **30.00
中投:    **10.00
落差值:  ***0.50
零区值:  ***2.00
----------------
……
……
……


英文80列打印格式如下：
                                    Rec. Set
                                                                2014/02/01 15:36
--------------------------------------------------------------------------------
  Rec.     Target         SP1            SP2            SP3        Null zone    
             (kg)         (kg)           (kg)           (kg)            (kg)    
   *2    **12.00       ***5.00        ***2.00        ***0.10         ***1.00    
   *3    **22.00       **12.00        **12.00        **12.00         ***1.00    
   *1    **40.00       **12.00        **12.00        **12.00         ***2.00    


英文32列打印格式如下：

            Rec. Set
Time: 2014/02/01 15:36
Unit: 公斤
--------------------------------
Rec.:                         *1
Target:                  **40.00
SP1:                     **30.00
SP2:                     **10.00
SP3:                     ***0.50
Null zone:               ***2.00
--------------------------------


英文16列打印格式如下：

    Rec. Set
2014/02/01 15:36
Unit:kg
----------------
Rec.:         *1
Target:  **40.00
SP1:     **30.00
SP2:     **10.00
SP3:     ***0.50
Nullzone:***2.00
----------------
……
……
……
********************************************************************************

*/

#include "include.h"
#include "Adaptation.h"

#define PRTTYPELEN_DEBUG    212
#define PRTTYPELEN_80       80  //80列打印
#define PRTTYPELEN_32       32  //32列打印
#define PRTTYPELEN_16       16  //16列打印





bool gb_PrintStartFlg_UART0;      //开始打印标志
volatile bool gvb_PrintingFlg_UART0;        //串口正在打印标志
volatile u8 gvu8_PrintCnt_UART0;            //打印多少行
bool gb_PrintAllRecFlg_UART0;      //打印所有配方开始标志
u32 gu32_PrintRecNum_UART0;       //打印配方数据
bool gb_FirstPrintFlg_UART0;      //第一次打印标志 用来打印一些台头说明
u8 gu8_PrintMode_UART0;           //打印方式 0自动打印 1打印累计报表 2打印累计设置 3打印总累计报表

bool gb_PrintStartFlg_UART1;      //开始打印标志
volatile bool gvb_PrintingFlg_UART1;        //串口正在打印标志
volatile u8 gvu8_PrintCnt_UART1;            //打印多少行
bool gb_PrintAllRecFlg_UART1;      //打印所有配方开始标志
u32 gu32_PrintRecNum_UART1;       //打印配方数据
bool gb_FirstPrintFlg_UART1;      //第一次打印标志 用来打印一些台头说明
u8 gu8_PrintMode_UART1;           //打印方式 0自动打印 1打印累计报表 2打印累计设置 3打印总累计报表

bool gb_PrintAllFlg;        //打印所有配方数据
u32 gu32_PackingResult;     //包装结果，自动打印时使用
u32 gu32_PrintRecNumStart;  //打印所有配方时的起始配方


const char cc_AutoPrt_16_Eng[5][19] = {//英文16列自动打印台头
    {"\r\n"},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {" Packing Detail\r\n"},
    {"Unit:  \r\n"},
    {"Times Rec Result\r\n"},
    {"----------------\r\n"} };
const char cc_AutoPrt_16_Chn[5][19] = {//中文16列自动打印台头
    {0x1C,0x26,0x0D,0x0A},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"   包装明细表\r\n"},
    {"单位:    \r\n"},
    {" 次数 配方 结果\r\n"},
    {"----------------\r\n"} };
const char cc_AutoPrt_32_Eng[5][35] = {//英文32列自动打印台头
    {"\r\n"},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"         Packing Detail\r\n"},
    {"Unit:  \r\n"},
    {"Total Times Rec  Target   Result\r\n"},
    {"--------------------------------\r\n"} };
const char cc_AutoPrt_32_Chn[5][35] = {//中文32列自动打印台头
    {0x1C,0x26,0x0D,0x0A},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"           包装明细表\r\n"},
    {"单位:    \r\n"},
    {"总累计次数 配方  目标值    结果\r\n"},
    {"--------------------------------\r\n"} };
const char cc_AutoPrt_80_Eng[5][83] = {//英文80列自动打印台头
    {"\r\n"},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"                                 Packing Detail\r\n"},
    {"--------------------------------------------------------------------------------\r\n"},
    {"Total Times    Date      Time   Rec.  Rec.Times   Target    Result      Error\r\n"},
    {"                                                    (  )      (  )       (  )\r\n"} };
const char cc_AutoPrt_80_Chn[5][83] = {//中文80列自动打印台头
    {0x1C,0x26,0x0D,0x0A},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"                                   包装明细表\r\n"},
    {"--------------------------------------------------------------------------------\r\n"},
    {"总累计次数    日期      时间   配方 配方累计次数  目标值   包装结果      误差\r\n"},
    {"                                                  (    )    (    )     (    )\r\n"} };


#ifdef DEBUG_MONITORTIME_PRINT
        const char cc_DebugAutoPrt_101_Chn[5][215] = {//调试用
            {"滤波后线性拟合数据个数   ;卡尔曼滤波    ;小投预测    ;谷值后跳过点数  ;小投预测采样最少点数  ;小投k值取最近  个;自适应(  )B7.2(    )B7.3(   )B7.4(    )B7.6(    )B7.7(   )B7.8(   )                                 \r\n"},
            {"AD速度(   ) 滤波(加料  定值  卸料  禁比 ) 定值判稳(  ) 判稳(时间    范围 ) 卸料由(    )控制  中投截止点(      ) T1(   ) T2a(   ) T3(   ) T4(   ) T5(   ) F1.5(    ms)                                               \r\n"},
            {"--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\r\n"},
            {" 中加  慢加   定值 卸料完   结果   目标值  中投值  小投值  T2b  包数 总用时 预测   峰值    谷值            自适应SP2                             自适应SP3                            小投预测截止点            总数\r\n"},
            {" (秒)  (秒)   (秒)   (秒)  (    )  (    )  (    )  (    )  (秒)       (秒)  (ms)  (    )  (    ) ( SP2K    过冲中  流量ms 小投K统计 调整值)  (落差统计   调整)              (状态 本次k值 平均k值  结果   重量) (包)\r\n"} };
//示例        12.34512.34512.345 12.345 123.456 123.456 123.456 123.456 1.234 123 123.456 12.3 123.456 123.456  123.456 123.456 123.456  12.345   +12.345   123.456  -12.345               0x12 123.456 123.456 12345 123.345 1234\r\n

    const char cc_DebugAutoPrtDebug_101_Chn[185] =
//            {"---------      秒内共完成  包------减去每包定值时间   秒--------最快1分钟可完成    包-------------------------------------------------------------------------------------------------\r\n"};
            {"---------      秒内共完成  包-----------------------------------最快1分钟可完成    包-------------------------------------------------------------------------------------------------\r\n"};
     
#endif

const char cc_PrtStatistic[25][185] = {   //打印统计数据
            {"=============================================================================================================================================================\r\n"},
            {"=        共用时***分钟**秒  完成****包  平均每小时产量****包(*****kg)  平均每分钟**.*包                                                                     =\r\n"},
            {"=                                                                                                                                                           =\r\n"},
            {"=        最低欠差结果:123.456kg  是第****包                                                                                                                 =\r\n"},
            {"=        欠差数据:              ----> 共****包  **.*%                                                                                                       =\r\n"},
            {"=        ---------------------------------------------                                                                                                      =\r\n"},
            {"=                      24.985                                                                                                                               =\r\n"},
            {"=                         ~     ----> 共****包  **.*%                                                                                                       =\r\n"},
            {"=                      24.990                                                                                                                               =\r\n"},
            {"=                         ~     ----> 共****包  **.*%                                                                                                       =\r\n"},
            {"=                      24.995                                                                                                                               =\r\n"},
            {"=                         ~     ----> 共****包  **.*%                                                                                                       =\r\n"},
            {"=        重量分布情况: 25.000                                                                                                                               =\r\n"},
            {"=                         ~     ----> 共****包  **.*%                                                                                                       =\r\n"},
            {"=                      25.005                                                                                                                               =\r\n"},
            {"=                         ~     ----> 共****包  **.*%                                                                                                       =\r\n"},
            {"=                      25.010                                                                                                                               =\r\n"},
            {"=                         ~     ----> 共****包  **.*%                                                                                                       =\r\n"},
            {"=                      24.015                                                                                                                               =\r\n"},
            {"=        ---------------------------------------------                                                                                                      =\r\n"},
            {"=        超差数据:              ----> 共****包  **.*%                                                                                                       =\r\n"},
            {"=        最高超差结果:123.456kg  是第****包                                                                                                                 =\r\n"},
            {"=                                                                                                                                                           =\r\n"},
            {"=        平均每包重量123.456kg  误差带1.234kg                                                                                                               =\r\n"},
            {"=============================================================================================================================================================\r\n"} };

#define PRTCNT_STATISTIC_LINE   (sizeof(cc_PrtStatistic)/sizeof(cc_PrtStatistic[0]))
#define PRTCNT_STATISTIC_ROW    (sizeof(cc_PrtStatistic[0])/sizeof(cc_PrtStatistic[0][0]))


const char cc_PrtTotal_16_Eng[8][19] = {//英文16列打印总累计台头
    {"\r\n"},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"  Total Report\r\n"},
    {"                \r\n"},
    {"Unit:           \r\n"},
    {"----------------\r\n"},
    {"Times:          \r\n"},
    {"Val.:           \r\n"},
    {"----------------\r\n"} };
const char cc_PrtTotal_16_Chn[8][19] = {//中文16列打印总累计台头
    {0x1C,0x26,0x0D,0x0A},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"   总累计报表\r\n"},
    {"                \r\n"},
    {"单位:           \r\n"},
    {"----------------\r\n"},
    {"总次数:         \r\n"},
    {"总重:           \r\n"},
    {"----------------\r\n"} };
const char cc_PrtTotal_32_Eng[8][35] = {//英文32列打印总累计台头
    {"\r\n"},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"          Total Report\r\n"},
    {"Time:                           \r\n"},
    {"Unit:                           \r\n"},
    {"--------------------------------\r\n"},
    {"Total Times:                    \r\n"},
    {"Total Value:                    \r\n"},
    {"--------------------------------\r\n"} };
const char cc_PrtTotal_32_Chn[8][35] = {//中文32列打印总累计台头
    {0x1C,0x26,0x0D,0x0A},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"           总累计报表\r\n"},
    {"时间:                           \r\n"},  
    {"单位:                           \r\n"},  
    {"--------------------------------\r\n"},  
    {"总累计次数:                     \r\n"},  
    {"总累计重量:                     \r\n"},  
    {"--------------------------------\r\n"} };
const char cc_PrtTotal_80_Eng[5][83] = {//英文80列打印总累计台头
    {"\r\n"},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"                                 Total Report\r\n"},
    {"                                                                                \r\n"},
    {"--------------------------------------------------------------------------------\r\n"},
    {"       Date              Time         Total Times           Total Value\r\n"} };
const char cc_PrtTotal_80_Chn[5][83] = {//中文80列打印总累计台头
    {0x1C,0x26,0x0D,0x0A},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"                                   总累计报表\r\n"},
    {"                                                                                \r\n"},
    {"--------------------------------------------------------------------------------\r\n"},
    {"       日期              时间          总累计次数            总累计重量\r\n"} };


const char cc_PrtRecReport_16_Eng[11][19] = {//英文16列打印配方累计报表台头
    {"\r\n"},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"  Rec. Report\r\n"},
    {"                \r\n"},
    {"Unit:           \r\n"},
    {"----------------\r\n"},
    {"Rec.:           \r\n"},
    {"Target:         \r\n"},
    {"Times:          \r\n"},
    {"Val.:           \r\n"},
    {"Error:          \r\n"},
    {"----------------\r\n"} };
const char cc_PrtRecReport_16_Chn[11][19] = {//中文16列打印配方累计报表台头
    {0x1C,0x26,0x0D,0x0A},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"  配方累计报表\r\n"},
    {"                \r\n"},
    {"单位:           \r\n"},
    {"----------------\r\n"},
    {"配方:           \r\n"},
    {"目标值:         \r\n"},
    {"次数:           \r\n"},
    {"重量:           \r\n"},
    {"总误差:         \r\n"},
    {"----------------\r\n"}  };
const char cc_PrtRecReport_32_Eng[11][35] = {//英文32列打印配方累计报表台头
    {"\r\n"},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"          Rec. Report\r\n"},
    {"Time:                           \r\n"},
    {"Unit:                           \r\n"},
    {"--------------------------------\r\n"},
    {"Rec.:                           \r\n"},
    {"Target:                         \r\n"},
    {"Rec. Times:                     \r\n"},
    {"Rec. Value:                     \r\n"},
    {"Error:                          \r\n"},
    {"--------------------------------\r\n"} };
const char cc_PrtRecReport_32_Chn[11][35] = {//中文32列打印配方累计报表台头
    {0x1C,0x26,0x0D,0x0A},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"          配方累计报表\r\n"},
    {"时间:                           \r\n"},
    {"单位:                           \r\n"},
    {"--------------------------------\r\n"},
    {"配方:                           \r\n"},
    {"目标值:                         \r\n"},
    {"配方累计次数:                   \r\n"},
    {"配方累计重量:                   \r\n"},
    {"总误差:                         \r\n"},
    {"--------------------------------\r\n"}  };
const char cc_PrtRecReport_80_Eng[6][83] = {//英文80列打印配方累计报表台头
    {"\r\n"},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"                                  Rec. Report\r\n"},
    {"                                                                                \r\n"},
    {"--------------------------------------------------------------------------------\r\n"},
    {"  Rec.      Target        Rec. Times           Rec. Value                 Error\r\n"},
    {"             (  )                                 (  )                     (  ) \r\n"}  };
const char cc_PrtRecReport_80_Chn[6][83] = {//中文80列打印配方累计报表台头
    {0x1C,0x26,0x0D,0x0A},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"                                  配方累计报表\r\n"},
    {"                                                                                \r\n"},
    {"--------------------------------------------------------------------------------\r\n"},
    {"  配方      目标值      配方累计次数         配方累计重量                总误差\r\n"},
    {"            (    )                               (    )                  (    ) \r\n"} };


const char cc_PrtRecSet_16_Eng[12][19] = {//英文16列打印配方设置台头
    {"\r\n"},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"    Rec. Set\r\n"},
    {"                \r\n"},
    {"Unit:           \r\n"},
    {"----------------\r\n"},
    {"Rec.:           \r\n"},
    {"Target:         \r\n"},
    {"SP1:            \r\n"},
    {"SP2:            \r\n"},
    {"SP3:            \r\n"},
    {"Nullzone:       \r\n"},
    {"----------------\r\n"} };
const char cc_PrtRecSet_16_Chn[12][19] = {//中文16列打印配方设置台头
    {0x1C,0x26,0x0D,0x0A},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"  配方设置报表\r\n"},
    {"                \r\n"},
    {"单位:           \r\n"},
    {"----------------\r\n"},
    {"配方:           \r\n"},
    {"目标值:         \r\n"},
    {"大投:           \r\n"},
    {"中投:           \r\n"},
    {"落差值:         \r\n"},
    {"零区值:         \r\n"},
    {"----------------\r\n"} };
const char cc_PrtRecSet_32_Eng[12][35] = {//英文32列打印配方设置台头
    {"\r\n"},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"            Rec. Set\r\n"},
    {"Time:                           \r\n"},
    {"Unit:                           \r\n"},
    {"--------------------------------\r\n"},
    {"Rec.:                           \r\n"},
    {"Target:                         \r\n"},
    {"SP1:                            \r\n"},
    {"SP2:                            \r\n"},
    {"SP3:                            \r\n"},
    {"Null zone:                      \r\n"},
    {"--------------------------------\r\n"} };
const char cc_PrtRecSet_32_Chn[12][35] = {//中文32列打印配方设置台头
    {0x1C,0x26,0x0D,0x0A},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"          配方设置报表\r\n"},
    {"时间:                           \r\n"},
    {"单位:                           \r\n"},
    {"--------------------------------\r\n"},
    {"配方:                           \r\n"},
    {"目标值:                         \r\n"},
    {"大投提前量:                     \r\n"},
    {"中投提前量:                     \r\n"},
    {"落差值:                         \r\n"},
    {"零区值:                         \r\n"},
    {"--------------------------------\r\n"} };
const char cc_PrtRecSet_80_Eng[6][83] = {//英文80列打印配方设置台头
    {"\r\n"},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"                                    Rec. Set\r\n"},
    {"                                                                                \r\n"},
    {"--------------------------------------------------------------------------------\r\n"},
    {"  Rec.     Target         SP1            SP2            SP3        Null zone\r\n"},
    {"             (  )         (  )           (  )           (  )            (  )\r\n"} };
const char cc_PrtRecSet_80_Chn[6][83] = {//中文80列打印配方设置台头
    {0x1C,0x26,0x0D,0x0A},   //打印机相关命令使用如进入汉字模式，退出汉字模式
    {"                                  配方设置报表\r\n"},
    {"                                                                                \r\n"},
    {"--------------------------------------------------------------------------------\r\n"},
    {"  配方     目标值    大投提前量    中投提前量         落差值          零区值\r\n"},
    {"           (    )       (    )         (    )         (    )          (    )\r\n"} };


//单位的中文字符串
const char cc_Unit_Chn[4][5] = {" 克 ","公斤"," 吨 "," 磅 "};
const char cc_Unit_Eng[4][3] = {"g ","kg","t ","lb"};

//自动打印行数
#define PRTCNT_AUTO_FIRST       (sizeof(cc_AutoPrt_16_Eng)/sizeof(cc_AutoPrt_16_Eng[0])+1)
#define PRTCNT_AUTO             1

//总累计报表16列打印行数
#define PRTCNT_TOTAL_16_FIRST       (sizeof(cc_PrtTotal_16_Eng)/sizeof(cc_PrtTotal_16_Eng[0]))
//总累计报表32列打印行数
#define PRTCNT_TOTAL_32_FIRST       PRTCNT_TOTAL_16_FIRST
//总累计报表80列打印行数
#define PRTCNT_TOTAL_80_FIRST       (sizeof(cc_PrtTotal_80_Eng)/sizeof(cc_PrtTotal_80_Eng[0])+1)
#define PRTCNT_TOTAL_80             1

//配方累计报表16列打印行数
#define PRTCNT_RECREPORT_16_FIRST       (sizeof(cc_PrtRecReport_16_Eng)/sizeof(cc_PrtRecReport_16_Eng[0]))
#define PRTCNT_RECREPORT_16             (PRTCNT_RECREPORT_16_FIRST - 5)
//配方累计报表32列打印行数
#define PRTCNT_RECREPORT_32_FIRST       PRTCNT_RECREPORT_16_FIRST
#define PRTCNT_RECREPORT_32             PRTCNT_RECREPORT_16
//配方累计报表80列打印行数
#define PRTCNT_RECREPORT_80_FIRST       (sizeof(cc_PrtRecReport_80_Eng)/sizeof(cc_PrtRecReport_80_Eng[0])+1)
#define PRTCNT_RECREPORT_80              1

//配方设置报表16列打印行数
#define PRTCNT_RECSET_16_FIRST       (sizeof(cc_PrtRecSet_16_Eng)/sizeof(cc_PrtRecSet_16_Eng[0]))
#define PRTCNT_RECSET_16             (PRTCNT_RECSET_16_FIRST - 5)
//配方设置报表32列打印行数
#define PRTCNT_RECSET_32_FIRST       PRTCNT_RECSET_16_FIRST
#define PRTCNT_RECSET_32             PRTCNT_RECSET_16
//配方设置报表80列打印行数
#define PRTCNT_RECSET_80_FIRST       (sizeof(cc_PrtRecSet_80_Eng)/sizeof(cc_PrtRecSet_80_Eng[0])+1)
#define PRTCNT_RECSET_80             1

//根据打印类型区分第一次带台头打印的行数
const u8 cc_PRTCNT_TOTAL_FIRST_ARRAY[] = {PRTCNT_TOTAL_16_FIRST, PRTCNT_TOTAL_32_FIRST, PRTCNT_TOTAL_80_FIRST};
const u8 cc_PRTCNT_RECREPORT_FIRST_ARRAY[] = {PRTCNT_RECREPORT_16_FIRST, PRTCNT_RECREPORT_32_FIRST, PRTCNT_RECREPORT_80_FIRST};
const u8 cc_PRTCNT_RECSET_FIRST_ARRAY[] = {PRTCNT_RECSET_16_FIRST, PRTCNT_RECSET_32_FIRST, PRTCNT_RECSET_80_FIRST};
//根据打印类型区分后续打印的行数
const u8 cc_PRTCNT_RECREPORT_ARRAY[] = {PRTCNT_RECREPORT_16, PRTCNT_RECREPORT_32, PRTCNT_RECREPORT_80};
const u8 cc_PRTCNT_RECSET_ARRAY[] = {PRTCNT_RECSET_16, PRTCNT_RECSET_32, PRTCNT_RECSET_80};


/*********************************************************************
函数名称: void ErrorToAsc(u8 *fu8p_Array, u32 fu32_Point, u32 fu32_Target, u32 fu32_Result)
功    能: 计算目标值和结果的误差转为ASCII码
说    明: 算上小数点和符号，最多可占8字节
入口参数: *fu8p_Array 串口数组指针
          fu32_Point 小数点
          fu32_Target 目标值
          fu32_Result 结果
返 回 值: 
设    计: 丛海旭               时    间: 2014-3-5
修    改:                      时    间: 
*********************************************************************/
void ErrorToAsc(u8 *fu8p_Array, u32 fu32_Point, u32 fu32_Target, u32 fu32_Result)
{
    u8 i;
    
    BIN4toNASC_Point(abs(fu32_Result - fu32_Target), fu8p_Array + 1, 6, fu32_Point);
    if (fu32_Result < fu32_Target)
    {   //误差为负，负号处理
        for (i = 0; i < 7; i++)
        {
            if ((*fu8p_Array++) != ' ')
            {
                *(fu8p_Array - 2) = '-';
                break;
            }
        }
    }
}

/*********************************************************************
函数名称: void UnitToAsc(u8 *fu8p_Array, u32 fu32_Unit)
功    能: 单位转为ASCII码 占两个字节
说    明: 
入口参数: *fu8p_Array 串口数组指针
返 回 值: 
设    计: 丛海旭               时    间: 2014-3-5
修    改:                      时    间: 
*********************************************************************/
void UnitToAsc(u8 *fu8p_Array, u32 fu32_Unit)
{
    switch(fu32_Unit)
    {
        case UNIT_g:
            *fu8p_Array = 'g';
            *(++fu8p_Array) = ' ';
            break;
        case UNIT_kg:
            *fu8p_Array = 'k';
            *(++fu8p_Array) = 'g';
            break;
        case UNIT_t:
            *fu8p_Array = 't';
            *(++fu8p_Array) = ' ';
            break;
        case UNIT_lb:
            *fu8p_Array = 'l';
            *(++fu8p_Array) = 'b';
            break;
        default:
            break;
    }
}

#ifdef DEBUG_MONITORTIME_PRINT
/*********************************************************************
函数名称: void PrtAuto_Contents(u8 *fu8p_Array)
功    能: 自动打印内容
说    明: 
入口参数: *fu8p_Array 串口数组指针
          fu32_Result 包装结果
          fu32_Wild  080列 116列
          fu32_Eng   0中文 1英文
          fu8_PrintCnt 打印行数
返 回 值: 
设    计: 丛海旭               时    间: 2014-3-4
修    改:                      时    间: 
*********************************************************************/
void PrtAutoDebug_Contents(u8 *fu8p_Array)
{
    u32 lu32_Temp;
    
    //打印台头
    memcpy(fu8p_Array, 
          &cc_DebugAutoPrtDebug_101_Chn[0],
          (PRTTYPELEN_DEBUG + 2));
    //     秒内共完成  包
    BIN4toNASC_Point(gu32_PackingResult, &fu8p_Array[9], 5, 3);   
    //     秒内共完成  包
    BIN4toNASC_Echo0(gs_DebugRunTimeTemp.u32SumCnt, &fu8p_Array[25], 2);   
//    //减去每包定值时间   秒
//    BIN4toNASC_Point(gs_Rec.TimeT4, &fu8p_Array[51], 2, 1);   
    //最快1分钟可完成    包 带1位小数点
    lu32_Temp = 600000ul / (gu32_PackingResult / gs_DebugRunTimeTemp.u32SumCnt - gs_Rec.TimeT4 * 100);
    BIN4toNASC_Point(lu32_Temp, &fu8p_Array[79], 3, 1);   
    
    if (fu8p_Array == gu8_TxdArray_UART0)
        gvb_PrintingFlg_UART0 = true;
    else
        gvb_PrintingFlg_UART1 = true;
    StartSend_Com(fu8p_Array);
}
#endif

/*********************************************************************
函数名称: void PrtAuto_Contents(u8 *fu8p_Array, u32 fu32_Result, u32 fu32_PrtType, u32 fu32_Eng, u8 fu8_PrintCnt)
功    能: 自动打印内容
说    明: 
入口参数: *fu8p_Array 串口数组指针
          fu32_Result 包装结果
          fu32_Wild  080列 116列
          fu32_Eng   0中文 1英文
          fu8_PrintCnt 打印行数
返 回 值: 
设    计: 丛海旭               时    间: 2014-3-4
修    改:                      时    间: 
*********************************************************************/
void PrtAuto_Contents(u8 *fu8p_Array, u32 fu32_Result, u32 fu32_PrtType, u32 fu32_Eng, u8 fu8_PrintCnt)
{
    u32 lu32_TargetTemp = 0;
    memset(fu8p_Array, ' ', TXDLEN_PRINT);
#ifdef DEBUG_MONITORTIME_PRINT
    //80列打印  80列
    if (fu8_PrintCnt <= PRTCNT_AUTO)
    {   //打印内容
        if (fu8p_Array == gu8_TxdArray_UART0)
            gb_FirstPrintFlg_UART0 = false;   //打印过内容证明已经打印过台头
        else
            gb_FirstPrintFlg_UART1 = false;   //打印过内容证明已经打印过台头
        //中加时间
        BIN4toNASC_Point(gs_DebugRunTimeTemp.u32Sp2Time, &fu8p_Array[0], 5, 3);
        //慢加时间
        BIN4toNASC_Point(gs_DebugRunTimeTemp.u32Sp3Time, &fu8p_Array[6], 5, 3);
        //定值
        BIN4toNASC_Point(gs_DebugRunTimeTemp.u32RunCmpTime - gs_DebugRunTimeTemp.u32Sp3Time - gs_DebugRunTimeTemp.u32Sp2Time, &fu8p_Array[12], 5, 3);
        //一次过程时间
        BIN4toNASC_Point(gs_DebugRunTimeTemp.u32OneTareTime, &fu8p_Array[19], 5, 3);
        //加料结果
        BIN4toNASC_Point(fu32_Result, &fu8p_Array[26], 6, gs_Cal.Point);   
        //目标值
        BIN4toNASC_Point(gu32_DebugTarget, &fu8p_Array[34], 6, gs_Cal.Point);   
        //中投提前量
        BIN4toNASC_Point(gu32_DebugMiddle, &fu8p_Array[42], 6, gs_Cal.Point);   
        //小投提前量
        BIN4toNASC_Point(gu32_DebugSmall, &fu8p_Array[50], 6, gs_Cal.Point);   
    #ifdef DEBUG_SMARTT2B
        //小投禁止比较时间
        BIN4toNASC_Point(gu32_T2bTime, &fu8p_Array[58], 4, 3);   
    #else
        //小投禁止比较时间
        BIN4toNASC_Point(gs_Rec.TimeT2b, &fu8p_Array[58], 2, 1);   
    #endif
        //包数
        BIN4toNASC_Echo0(gs_DebugRunTimeTemp.u32SumCnt, &fu8p_Array[64], 3);   
        //总用时
        BIN4toNASC_Point(gs_DebugRunTimeTemp.u32TotalTime, &fu8p_Array[68], 6, 3);   
        //预测中投截止点时间
        if (gs_Setup.ResultHoldSwitch != 0)
            BIN4toNASC_Point(gs_DebugRunTimeTemp.u32PredictSp2StopTime, &fu8p_Array[76], 3, 1);
        //峰值
        BIN4toNASC_Point(gs_DebugRunTimeTemp.u32MaxWt, &fu8p_Array[81], 6, gs_Cal.Point);   
        //谷值
        BIN4toNASC_Point(gs_DebugRunTimeTemp.u32MinWt, &fu8p_Array[89], 6, gs_Cal.Point);   
        //SP2K
        BIN4toNASC_Point(gs_Adapt.s32SP2KProb, &fu8p_Array[98], 6, 3);   
        //过冲中
        BIN4toNASC_Point(gs_Adapt.s32RushWtMiddleProb + gs_Rec.Small, &fu8p_Array[106], 6, gs_Cal.Point);
        //流量ms
        BIN4toNASC_Point((gs_Adapt.fSP2Flux * 1000), &fu8p_Array[114], 6, 3);
        //小投K统计
        BIN4toNASC_Point(gs_Adapt.s32SP3KProb, &fu8p_Array[124], 5, 3);
        //SP2调整值
        if (gs_Adapt.s32SP2AdaptSig < 0)
        {
            memset(&fu8p_Array[132], '-', 1);
        }
        else if (gs_Adapt.s32SP2AdaptSig > 0)
        {
            memset(&fu8p_Array[132], '+', 1);
        }
        BIN4toNASC_Point(gs_Adapt.s32SP2AdaptVal, &fu8p_Array[133], 6, gs_Cal.Point);   
        //SP3统计落差
        BIN4toNASC_Point(gs_Adapt.u32SP3Prob, &fu8p_Array[142], 6, gs_Cal.Point);   
        //SP3调整值
        if (gs_Adapt.s32SP3AdaptVal < 0)
        {
            memset(&fu8p_Array[151], '-', 1);
            gs_Adapt.s32SP3AdaptVal = 0 - gs_Adapt.s32SP3AdaptVal;
        }
        else if (gs_Adapt.s32SP3AdaptVal > 0)
        {
            memset(&fu8p_Array[151], '+', 1);
        }
            
        BIN4toNASC_Point(gs_Adapt.s32SP3AdaptVal, &fu8p_Array[152], 5, gs_Cal.Point);   
        
//        //中投截止点~峰值时间
//        BIN4toNASC_Point(gs_DebugRunTimeTemp.u32Sp2StopToMaxTime, &fu8p_Array[98], 4, 3);   
//        //峰值~谷值时间
//        BIN4toNASC_Point(gs_DebugRunTimeTemp.u32MaxToMinTime, &fu8p_Array[105], 4, 3);   
//        //中投最大k 滤波后
//        BIN4toNASC_Point(gs_DebugRunTimeTemp.s32Sp2MaxKFed, &fu8p_Array[111], 6, 3);
//        //拐点k
//        BIN4toNASC_Point(gs_DebugRunTimeTemp.s32MaxKFedReLinear, &fu8p_Array[119], 6, 3);
//        //拐点b
//        if (gs_DebugRunTimeTemp.s32MaxBFedReLinear < 0)
//        {
//            gs_DebugRunTimeTemp.s32MaxBFedReLinear = -gs_DebugRunTimeTemp.s32MaxBFedReLinear;
//            memset(&fu8p_Array[127], '-', 1);
//        }
//        BIN4toNASC_Point(gs_DebugRunTimeTemp.s32MaxBFedReLinear, &fu8p_Array[128], 6, gs_Cal.Point);
        
        
        //状态
        memcpy(&fu8p_Array[173], "0x", 2);
        HextoASC(&gs_PredictSp3Temp.u8State, &fu8p_Array[175], 1);
        //本次K值
        BIN4toNASC_Point(gs_PredictSp3Temp.s32KThisTime, &fu8p_Array[178], 6, 3);
        //平均K值
        BIN4toNASC_Point(gs_PredictSp3Temp.s32KAverage, &fu8p_Array[186], 6, 3);
        //结果
        BIN4toNASC_Echo0(gs_PredictSp3Temp.u32PredictTarget, &fu8p_Array[194], 5);
        //重量
        BIN4toNASC_Point(gs_DebugRunTime.s32SP3RealStopWt, &fu8p_Array[200], 6, gs_Cal.Point);
        //总包数
        BIN4toNASC_Echo0(gu32_DebugSumNumTemp, &fu8p_Array[208], 4);
        
        
        
        
        fu8p_Array[PRTTYPELEN_DEBUG] = ENDCHAR1;
        fu8p_Array[PRTTYPELEN_DEBUG+1] = ENDCHAR2;
    }
    else
    {   //打印台头
        memcpy(fu8p_Array, 
              &cc_DebugAutoPrt_101_Chn[PRTCNT_AUTO_FIRST-fu8_PrintCnt][0],
              (PRTTYPELEN_DEBUG + 2));
              
        if ((PRTCNT_AUTO_FIRST-fu8_PrintCnt) == 0)
        {   //台头信息填充
            //滤波后线性拟合数据个数   ;
            BIN4toNASC_Echo0(gs_Rec.TimeT10, &fu8p_Array[22], 3);
            if (gs_Setup.PowerOnZeroSwitch != 0)    //卡尔曼
                memcpy(&fu8p_Array[36], "打开", 4);
            else
                memcpy(&fu8p_Array[36], "关闭", 4);
            if (gs_Setup.DiscSumSwitch != 0)    //小投预测
                memcpy(&fu8p_Array[49], "打开", 4);
            else
                memcpy(&fu8p_Array[49], "关闭", 4);
            //谷值后跳过点数  ;
            BIN4toNASC_Echo0(gs_Rec.TimeT6, &fu8p_Array[68], 2);
            //小投预测采样最少点数  ;
            BIN4toNASC_Echo0(gs_Rec.TimeT7, &fu8p_Array[91], 2);
            //小投k值取最近  个;
            BIN4toNASC_Echo0(gs_Rec.TimeT12, &fu8p_Array[107], 2);
            //自适应开关
            if (gs_Setup.AdaptSW != 0)
                memcpy(&fu8p_Array[119], "开", 2);
            else
                memcpy(&fu8p_Array[119], "关", 2);
            //B7.2
            BIN4toNASC_Point(gs_Setup.AdaptSP2LimitRng, &fu8p_Array[127], 3, 1);
            //B7.3
            BIN4toNASC_Echo0(gs_Setup.AdaptSP2Level, &fu8p_Array[137], 3);
            //B7.4
            BIN4toNASC_Echo0(gs_Setup.AdaptSP2TimeThreshold, &fu8p_Array[146], 4);
            //B7.6
            BIN4toNASC_Point(gs_Setup.AdaptSP3LimitRng, &fu8p_Array[156], 3, 1);
            //B7.7
            BIN4toNASC_Echo0(gs_Setup.AdaptSP3Scope, &fu8p_Array[166], 3);
            //B7.8
            BIN4toNASC_Echo0(gs_Setup.AdaptSP2Scope, &fu8p_Array[175], 3);
            
        }
        if ((PRTCNT_AUTO_FIRST-fu8_PrintCnt) == 1)
        {   //台头第一行信息填充
            switch(gs_Setup.AdSamplingRate)
            {   //AD速度
                case 0:
                    lu32_TargetTemp = 120;
                    break;
                case 1:
                    lu32_TargetTemp = 240;
                    break;
                case 2:
                    lu32_TargetTemp = 480;
                    break;
                case 3:
                    lu32_TargetTemp = 960;
                    break;
            }
            BIN4toNASC(lu32_TargetTemp, &fu8p_Array[7], 3);
            //加料滤波
            BIN4toNASC(gs_Setup.AdFilterLevel, &fu8p_Array[21], 1);
            //定值滤波
            BIN4toNASC(gs_Setup.AdFilterLevelComp, &fu8p_Array[27], 1);
            //卸料滤波
            BIN4toNASC(gs_Setup.AdFilterLevelDisc, &fu8p_Array[33], 1);
            //T2B滤波
            BIN4toNASC(gs_Setup.TraceZeroRng, &fu8p_Array[39], 1);
            //定值判稳
            memcpy(&fu8p_Array[51], ((gs_Rec.OUSwitch != 0) ? "是" : "否"), 2);
            //判稳时间
            BIN4toNASC_Point(gs_Setup.JudgeStabOverTime, &fu8p_Array[64], 2, 1);
            //判稳范围
            BIN4toNASC(gs_Setup.JudgeStabRng, &fu8p_Array[72], 1);
        #ifdef DISC_TIME_CONTROL
            memcpy(&fu8p_Array[82], "时间", 4);
        #else
            memcpy(&fu8p_Array[82], "重量", 4);
        #endif
            if (gs_Setup.ResultHoldSwitch != 0)
                memcpy(&fu8p_Array[104], " 预测 ", 6);
            else
                memcpy(&fu8p_Array[104], "不预测", 6);
            //T1
            BIN4toNASC_Point(gs_Rec.TimeT1, &fu8p_Array[115], 2, 1);
            //T2a
            BIN4toNASC_Point(gs_Rec.TimeT2a, &fu8p_Array[124], 2, 1);
            //T3
            BIN4toNASC_Point(gs_Rec.TimeT3, &fu8p_Array[132], 2, 1);
            //T4
            BIN4toNASC_Point(gs_Rec.TimeT4, &fu8p_Array[140], 2, 1);
            //T5
            BIN4toNASC_Point(gs_Rec.TimeT5, &fu8p_Array[148], 2, 1);
        #ifdef DISC_TIME_CONTROL
            BIN4toNASC_Echo0(gs_Rec.NearZero, &fu8p_Array[158], 4);
        #else
            memSET(&fu8p_Array[153], " ", 12);
        #endif
        }
        if ((PRTCNT_AUTO_FIRST-fu8_PrintCnt) == 4)
        {   //台头第四行有单位需要填充
            memcpy(&fu8p_Array[28], 
                   &cc_Unit_Chn[gs_Cal.Unit][0],
                   4);
            memcpy(&fu8p_Array[36], 
                   &cc_Unit_Chn[gs_Cal.Unit][0],
                   4);
            memcpy(&fu8p_Array[44], 
                   &cc_Unit_Chn[gs_Cal.Unit][0],
                   4);
            memcpy(&fu8p_Array[52], 
                   &cc_Unit_Chn[gs_Cal.Unit][0],
                   4);
            memcpy(&fu8p_Array[83], 
                   &cc_Unit_Chn[gs_Cal.Unit][0],
                   4);
            memcpy(&fu8p_Array[91], 
                   &cc_Unit_Chn[gs_Cal.Unit][0],
                   4);
//            BIN4toNASC_Echo0(gs_Rec.TimeT11, &fu8p_Array[120], 2);
//            BIN4toNASC_Echo0(gs_Rec.TimeT11, &fu8p_Array[129], 2);
        }
    }
    
    if (fu8p_Array == gu8_TxdArray_UART0)
        gvb_PrintingFlg_UART0 = true;
    else
        gvb_PrintingFlg_UART1 = true;
    StartSend_Com(fu8p_Array);
#else
    if (fu32_PrtType == PRTTYPE_16)
    {   //16列打印 16列
        if (fu8_PrintCnt <= PRTCNT_AUTO)
        {   //打印内容
            if (fu8p_Array == gu8_TxdArray_UART0)
                gb_FirstPrintFlg_UART0 = false;   //打印过内容证明已经打印过台头
            else
                gb_FirstPrintFlg_UART1 = false;   //打印过内容证明已经打印过台头
            BIN4toNASC_Echo0(gu32_SumNum, &fu8p_Array[0], 5); //包装次数最大5位 0~4
            BIN4toNASC_Echo0(gu32_RecNum, &fu8p_Array[6], 2); //配方号2字节 6~7
            BIN4toNASC_Point(fu32_Result, &fu8p_Array[9], 6, gs_Cal.Point);   //重量数据7字节 9~15
            fu8p_Array[PRTTYPELEN_16] = ENDCHAR1;
            fu8p_Array[PRTTYPELEN_16+1] = ENDCHAR2;
        }
        else
        {   //打印台头
            memcpy(fu8p_Array, 
                  (fu32_Eng == PRINTER_ENG) ? &cc_AutoPrt_16_Eng[PRTCNT_AUTO_FIRST-fu8_PrintCnt][0] : &cc_AutoPrt_16_Chn[PRTCNT_AUTO_FIRST-fu8_PrintCnt][0],
                  (PRTTYPELEN_16 + 2));
            if ((PRTCNT_AUTO_FIRST-fu8_PrintCnt) == 2)
            {   //台头第二行有单位需要填充
                memcpy(&fu8p_Array[5], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
            }
        }
    }
    else if (fu32_PrtType == PRTTYPE_32)
    {//32列打印
        if (fu8_PrintCnt <= PRTCNT_AUTO)
        {   //打印内容
            if (fu8p_Array == gu8_TxdArray_UART0)
                gb_FirstPrintFlg_UART0 = false;   //打印过内容证明已经打印过台头
            else
                gb_FirstPrintFlg_UART1 = false;   //打印过内容证明已经打印过台头
            BIN4toNASC_Echo0(gu32_SumNum, &fu8p_Array[0], 9); //包装次数最大9位 0~8
            BIN4toNASC_Echo0(gu32_RecNum, &fu8p_Array[12], 2); //配方号2字节 12~13
            if (gs_Rec.CombinedNum > 1) //单秤组合次数大于1，目标值变化
                lu32_TargetTemp = gs_Rec.Target * gs_Rec.CombinedNum;
            else
                lu32_TargetTemp = gs_Rec.Target;
            BIN4toNASC_Point(lu32_TargetTemp, &fu8p_Array[16], 6, gs_Cal.Point);   //目标值7字节 16~22
            BIN4toNASC_Point(fu32_Result, &fu8p_Array[25], 6, gs_Cal.Point);   //重量数据7字节 25~31
            fu8p_Array[PRTTYPELEN_32] = ENDCHAR1;
            fu8p_Array[PRTTYPELEN_32+1] = ENDCHAR2;
        }
        else
        {   //打印台头
            memcpy(fu8p_Array, 
                  (fu32_Eng == PRINTER_ENG) ? &cc_AutoPrt_32_Eng[PRTCNT_AUTO_FIRST-fu8_PrintCnt][0] : &cc_AutoPrt_32_Chn[PRTCNT_AUTO_FIRST-fu8_PrintCnt][0],
                  (PRTTYPELEN_32 + 2));
            if ((PRTCNT_AUTO_FIRST-fu8_PrintCnt) == 2)
            {   //台头第二行有单位需要填充
                memcpy(&fu8p_Array[5], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
            }
        }
    }
    else 
    {   //80列打印  80列
        if (fu8_PrintCnt <= PRTCNT_AUTO)
        {   //打印内容
            if (fu8p_Array == gu8_TxdArray_UART0)
                gb_FirstPrintFlg_UART0 = false;   //打印过内容证明已经打印过台头
            else
                gb_FirstPrintFlg_UART1 = false;   //打印过内容证明已经打印过台头
            BIN4toNASC_Echo0(gu32_SumNum, &fu8p_Array[0], 9); //总包装次数最大9位 0~8
            RTC_DateToASC_Full(&fu8p_Array[12]);    //日期占10字节12~21
            RTC_TimeToASC_Full(&fu8p_Array[24]);    //时间占5字节24~28
            BIN4toNASC_Echo0(gu32_RecNum, &fu8p_Array[32], 2); //配方号 32~33
            BIN4toNASC_Echo0(gu32_SumNum_Rec[gu32_RecNum], &fu8p_Array[37], 9); //配方包装次数最大9位 37~45
            if (gs_Rec.CombinedNum > 1) //单秤组合次数大于1，目标值变化
                lu32_TargetTemp = gs_Rec.Target * gs_Rec.CombinedNum;
            else
                lu32_TargetTemp = gs_Rec.Target;
            BIN4toNASC_Point(lu32_TargetTemp, &fu8p_Array[49], 6, gs_Cal.Point);   //目标值7字节 49~55
            BIN4toNASC_Point(fu32_Result, &fu8p_Array[59], 6, gs_Cal.Point);   //包装结果7字节 59~65
            ErrorToAsc(&fu8p_Array[69], gs_Cal.Point, lu32_TargetTemp, fu32_Result);  //误差8字节 69~76
            fu8p_Array[PRTTYPELEN_80] = ENDCHAR1;
            fu8p_Array[PRTTYPELEN_80+1] = ENDCHAR2;
        }
        else
        {   //打印台头
            memcpy(fu8p_Array, 
                  (fu32_Eng == PRINTER_ENG) ? &cc_AutoPrt_80_Eng[PRTCNT_AUTO_FIRST-fu8_PrintCnt][0] : &cc_AutoPrt_80_Chn[PRTCNT_AUTO_FIRST-fu8_PrintCnt][0],
                  (PRTTYPELEN_80 + 2));
            if ((PRTCNT_AUTO_FIRST-fu8_PrintCnt) == 4)
            {   //台头第四行有单位需要填充
                memcpy((fu32_Eng == PRINTER_ENG) ? &fu8p_Array[53] : &fu8p_Array[51], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
                memcpy((fu32_Eng == PRINTER_ENG) ? &fu8p_Array[63] : &fu8p_Array[61], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
                memcpy((fu32_Eng == PRINTER_ENG) ? &fu8p_Array[74] : &fu8p_Array[72], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
            }
        }
    }
    if (fu8p_Array == gu8_TxdArray_UART0)
        gvb_PrintingFlg_UART0 = true;
    else
        gvb_PrintingFlg_UART1 = true;
    StartSend_Com(fu8p_Array);
#endif
}

/*********************************************************************
函数名称: void PrtStatistic_Contents(u8 *fu8p_Array, u8 fu8_PrintCnt)
功    能: 统计数据打印处理函数
说    明: 
入口参数: 
出口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2015-08-14
修    改:                      时    间: 
*********************************************************************/
void PrtStatistic_Contents(u8 *fu8p_Array, u8 fu8_PrintCnt)
{
    #define PERCENTAGE_FLG  10      //1个#号代表的百分比 1.0%
    
    memset(fu8p_Array, ' ', TXDLEN_PRINT);
    memcpy(fu8p_Array, 
          &cc_PrtStatistic[PRTCNT_STATISTIC_LINE-fu8_PrintCnt][0],
          (PRTCNT_STATISTIC_ROW + 2));
    switch (fu8_PrintCnt)
    {
        case PRTCNT_STATISTIC_LINE - 1:
            BIN4toNASC_Echo0(gs_Statistic.u32TotalTime/6000, &fu8p_Array[15], 3);    //分钟
            BIN4toNASC_Echo0(gs_Statistic.u32TotalTime%6000/100, &fu8p_Array[22], 2);    //秒
            BIN4toNASC_Echo0(gs_Statistic.u32SumNum, &fu8p_Array[32], 4);    //包
            BIN4toNASC_Echo0(gs_Statistic.u32NumAHour, &fu8p_Array[54], 4);    //每小时包
            BIN4toNASC_Echo0(gs_Statistic.u32NumAHour * gs_Rec.Target / 1000, &fu8p_Array[61], 5);    //每小时重量
            BIN4toNASC_Point(gs_Statistic.u32NumAMin, &fu8p_Array[81], 3, 1);   //平均每分钟包数
            break;
        case PRTCNT_STATISTIC_LINE - 3: //最低欠差值
            BIN4toNASC_Point(gs_Statistic.u32MostUnderResult, &fu8p_Array[22], 6, gs_Cal.Point);   //最低欠差值
            BIN4toNASC_Echo0(gs_Statistic.u32MostUnderNum, &fu8p_Array[37], 4);    //对应包数
            break;
        case PRTCNT_STATISTIC_LINE - 4: 
            BIN4toNASC_Echo0(gs_Statistic.u32Dst_Under_Num, &fu8p_Array[40], 4);    //包数
            BIN4toNASC_Point(gs_Statistic.u32Dst_Under_Per, &fu8p_Array[48], 3, 1);   //百分数
            memset(&fu8p_Array[55], '#', (gs_Statistic.u32Dst_Under_Per+PERCENTAGE_FLG/2)/PERCENTAGE_FLG);
            break;
        case PRTCNT_STATISTIC_LINE - 6:
            BIN4toNASC_Point(gs_Rec.Target - 3 * ONESTEP, &fu8p_Array[23], 5, gs_Cal.Point);   //
            break;
        case PRTCNT_STATISTIC_LINE - 7: 
            BIN4toNASC_Echo0(gs_Statistic.u32Dst_U_2_Num, &fu8p_Array[40], 4);    //包数
            BIN4toNASC_Point(gs_Statistic.u32Dst_U_2_Per, &fu8p_Array[48], 3, 1);   //百分数
            memset(&fu8p_Array[55], '#', (gs_Statistic.u32Dst_U_2_Per+PERCENTAGE_FLG/2)/PERCENTAGE_FLG);
            break;
        case PRTCNT_STATISTIC_LINE - 8:
            BIN4toNASC_Point(gs_Rec.Target - 2 * ONESTEP, &fu8p_Array[23], 5, gs_Cal.Point);   //
            break;
        case PRTCNT_STATISTIC_LINE - 9: 
            BIN4toNASC_Echo0(gs_Statistic.u32Dst_2_1_Num, &fu8p_Array[40], 4);    //包数
            BIN4toNASC_Point(gs_Statistic.u32Dst_2_1_Per, &fu8p_Array[48], 3, 1);   //百分数
            memset(&fu8p_Array[55], '#', (gs_Statistic.u32Dst_2_1_Per+PERCENTAGE_FLG/2)/PERCENTAGE_FLG);
            break;
        case PRTCNT_STATISTIC_LINE - 10:
            BIN4toNASC_Point(gs_Rec.Target - ONESTEP, &fu8p_Array[23], 5, gs_Cal.Point);   //
            break;
        case PRTCNT_STATISTIC_LINE - 11: 
            BIN4toNASC_Echo0(gs_Statistic.u32Dst_1_0_Num, &fu8p_Array[40], 4);    //包数
            BIN4toNASC_Point(gs_Statistic.u32Dst_1_0_Per, &fu8p_Array[48], 3, 1);   //百分数
            memset(&fu8p_Array[55], '#', (gs_Statistic.u32Dst_1_0_Per+PERCENTAGE_FLG/2)/PERCENTAGE_FLG);
            break;
        case PRTCNT_STATISTIC_LINE - 12:
            BIN4toNASC_Point(gs_Rec.Target, &fu8p_Array[23], 5, gs_Cal.Point);   //
            break;
        case PRTCNT_STATISTIC_LINE - 13: 
            BIN4toNASC_Echo0(gs_Statistic.u32Dst_0_1_Num, &fu8p_Array[40], 4);    //包数
            BIN4toNASC_Point(gs_Statistic.u32Dst_0_1_Per, &fu8p_Array[48], 3, 1);   //百分数
            memset(&fu8p_Array[55], '#', (gs_Statistic.u32Dst_0_1_Per+PERCENTAGE_FLG/2)/PERCENTAGE_FLG);
            break;
        case PRTCNT_STATISTIC_LINE - 14:
            BIN4toNASC_Point(gs_Rec.Target + ONESTEP, &fu8p_Array[23], 5, gs_Cal.Point);   //
            break;
        case PRTCNT_STATISTIC_LINE - 15: 
            BIN4toNASC_Echo0(gs_Statistic.u32Dst_1_2_Num, &fu8p_Array[40], 4);    //包数
            BIN4toNASC_Point(gs_Statistic.u32Dst_1_2_Per, &fu8p_Array[48], 3, 1);   //百分数
            memset(&fu8p_Array[55], '#', (gs_Statistic.u32Dst_1_2_Per+PERCENTAGE_FLG/2)/PERCENTAGE_FLG);
            break;
        case PRTCNT_STATISTIC_LINE - 16:
            BIN4toNASC_Point(gs_Rec.Target + 2 * ONESTEP, &fu8p_Array[23], 5, gs_Cal.Point);   //
            break;
        case PRTCNT_STATISTIC_LINE - 17: 
            BIN4toNASC_Echo0(gs_Statistic.u32Dst_2_O_Num, &fu8p_Array[40], 4);    //包数
            BIN4toNASC_Point(gs_Statistic.u32Dst_2_O_Per, &fu8p_Array[48], 3, 1);   //百分数
            memset(&fu8p_Array[55], '#', (gs_Statistic.u32Dst_2_O_Per+PERCENTAGE_FLG/2)/PERCENTAGE_FLG);
            break;
        case PRTCNT_STATISTIC_LINE - 18:
            BIN4toNASC_Point(gs_Rec.Target + 3 * ONESTEP, &fu8p_Array[23], 5, gs_Cal.Point);   //
            break;
        case PRTCNT_STATISTIC_LINE - 20: //欠差数据
            BIN4toNASC_Echo0(gs_Statistic.u32Dst_Over_Num, &fu8p_Array[40], 4);    //包数
            BIN4toNASC_Point(gs_Statistic.u32Dst_Over_Per, &fu8p_Array[48], 3, 1);   //百分数
            memset(&fu8p_Array[55], '#', (gs_Statistic.u32Dst_Over_Per+PERCENTAGE_FLG/2)/PERCENTAGE_FLG);
            break;
        case PRTCNT_STATISTIC_LINE - 21: //最高超差值
            BIN4toNASC_Point(gs_Statistic.u32MostOverResult, &fu8p_Array[22], 6, gs_Cal.Point);   //最高超差值
            BIN4toNASC_Echo0(gs_Statistic.u32MostOverNum, &fu8p_Array[37], 4);    //对应包数
            break;
        case PRTCNT_STATISTIC_LINE - 23: //平均每包重量
            BIN4toNASC_Point(gs_Statistic.ResultAverage, &fu8p_Array[21], 6, gs_Cal.Point);   //平均每包重量
            BIN4toNASC_Point(gs_Statistic.u32ErrorBand, &fu8p_Array[38], 4, gs_Cal.Point);    //误差带
            break;
        default:
            break;
    }
    if (fu8p_Array == gu8_TxdArray_UART0)
        gvb_PrintingFlg_UART0 = true;
    else
        gvb_PrintingFlg_UART1 = true;
    StartSend_Com(fu8p_Array);
}

/*********************************************************************
函数名称: void PrtRecReport_Contents(u8 *fu8p_Array, u32 fu32_Result, u32 fu32_PrtType, u32 fu32_Eng, u8 fu8_PrintCnt)
功    能: 配方累计报表内容
说    明: 
入口参数: *fu8p_Array 串口数组指针
          fu32_Result (1~20)配方号
          fu32_Wild  080列 116列
          fu32_Eng   0中文 1英文
          fu8_PrintCnt 打印行数
返 回 值: 
设    计: 丛海旭               时    间: 2014-3-4
修    改:                      时    间: 
*********************************************************************/
void PrtRecReport_Contents(u8 *fu8p_Array, u32 fu32_Result, u32 fu32_PrtType, u32 fu32_Eng, u8 fu8_PrintCnt)
{
    memset(fu8p_Array, ' ', TXDLEN_PRINT);
    if (fu32_PrtType == PRTTYPE_16)
    {   //16列打印 16列
        if (fu8_PrintCnt <= PRTCNT_RECREPORT_16)
        {   //打印内容
            if (fu8p_Array == gu8_TxdArray_UART0)
                gb_FirstPrintFlg_UART0 = false;   //打印过内容证明已经打印过台头
            else
                gb_FirstPrintFlg_UART1 = false;   //打印过内容证明已经打印过台头
            memcpy(fu8p_Array, 
                  (fu32_Eng == PRINTER_ENG) ? &cc_PrtRecReport_16_Eng[PRTCNT_RECREPORT_16_FIRST-fu8_PrintCnt][0] : &cc_PrtRecReport_16_Chn[PRTCNT_RECREPORT_16_FIRST-fu8_PrintCnt][0],
                  (PRTTYPELEN_16 + 2));
            switch (fu8_PrintCnt)
            {
                case PRTCNT_RECREPORT_16: //配方
                    BIN4toNASC_Echo0(fu32_Result, &fu8p_Array[PRTTYPELEN_16-2], 2); //配方号
                    break;
                case PRTCNT_RECREPORT_16 - 1: //目标值
                    BIN4toNASC_Point(FRAM_ReadDW(FMAddr_Target(fu32_Result)), &fu8p_Array[PRTTYPELEN_16-7], 6, gs_Cal.Point);   //重量数据
                    break;
                case PRTCNT_RECREPORT_16 - 2: //次数
                    BIN4toNASC_Echo0(gu32_SumNum_Rec[fu32_Result], &fu8p_Array[PRTTYPELEN_16-9], 9); //配方包装次数最大9位
                    break;
                case PRTCNT_RECREPORT_16 - 3: //重量
                    BIN4toNASC_Point(gu32_SumWt_Rec[fu32_Result], &fu8p_Array[PRTTYPELEN_16-10], 9, gs_Cal.Point);   //配方包装重量10字节
                    break;
                case PRTCNT_RECREPORT_16 - 4: //总误差
                    ErrorToAsc(&fu8p_Array[PRTTYPELEN_16-8], gs_Cal.Point, gu32_SumNum_Rec[fu32_Result] * FRAM_ReadDW(FMAddr_Target(fu32_Result)), gu32_SumWt_Rec[fu32_Result]);  //误差8字节
                    break;
                case PRTCNT_RECREPORT_16 - 5:
                default:
                    break;
            }
        }
        else
        {   //打印台头
            memcpy(fu8p_Array, 
                  (fu32_Eng == PRINTER_ENG) ? &cc_PrtRecReport_16_Eng[PRTCNT_RECREPORT_16_FIRST-fu8_PrintCnt][0] : &cc_PrtRecReport_16_Chn[PRTCNT_RECREPORT_16_FIRST-fu8_PrintCnt][0],
                  (PRTTYPELEN_16 + 2));
            if ((PRTCNT_RECREPORT_16_FIRST-fu8_PrintCnt) == 2)
            {   //台头第2行有日期时间需填充
                RTC_DateToASC_Full(&fu8p_Array[0]);    //日期占10字节
                RTC_TimeToASC_Full(&fu8p_Array[11]);    //时间占5字节
            }
            if ((PRTCNT_RECREPORT_16_FIRST-fu8_PrintCnt) == 3)
            {   //台头第3行有单位需要填充
                memcpy(&fu8p_Array[5], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
            }
        }
    }
    else if (fu32_PrtType == PRTTYPE_32)
    {   //32列打印
        if (fu8_PrintCnt <= PRTCNT_RECREPORT_32)
        {   //打印内容
            if (fu8p_Array == gu8_TxdArray_UART0)
                gb_FirstPrintFlg_UART0 = false;   //打印过内容证明已经打印过台头
            else
                gb_FirstPrintFlg_UART1 = false;   //打印过内容证明已经打印过台头
            memcpy(fu8p_Array, 
                  (fu32_Eng == PRINTER_ENG) ? &cc_PrtRecReport_32_Eng[PRTCNT_RECREPORT_32_FIRST-fu8_PrintCnt][0] : &cc_PrtRecReport_32_Chn[PRTCNT_RECREPORT_32_FIRST-fu8_PrintCnt][0],
                  (PRTTYPELEN_32 + 2));
            switch (fu8_PrintCnt)
            {
                case PRTCNT_RECREPORT_32: //配方
                    BIN4toNASC_Echo0(fu32_Result, &fu8p_Array[PRTTYPELEN_32-2], 2); //配方号
                    break;
                case PRTCNT_RECREPORT_32 - 1: //目标值
                    BIN4toNASC_Point(FRAM_ReadDW(FMAddr_Target(fu32_Result)), &fu8p_Array[PRTTYPELEN_32-7], 6, gs_Cal.Point);   //重量数据
                    break;
                case PRTCNT_RECREPORT_32 - 2: //次数
                    BIN4toNASC_Echo0(gu32_SumNum_Rec[fu32_Result], &fu8p_Array[PRTTYPELEN_32-9], 9); //配方包装次数最大9位
                    break;
                case PRTCNT_RECREPORT_32 - 3: //重量
                    BIN4toNASC_Point(gu32_SumWt_Rec[fu32_Result], &fu8p_Array[PRTTYPELEN_32-10], 9, gs_Cal.Point);   //配方包装重量10字节
                    break;
                case PRTCNT_RECREPORT_32 - 4: //总误差
                    ErrorToAsc(&fu8p_Array[PRTTYPELEN_32-8], gs_Cal.Point, gu32_SumNum_Rec[fu32_Result] * FRAM_ReadDW(FMAddr_Target(fu32_Result)), gu32_SumWt_Rec[fu32_Result]);  //误差8字节
                    break;
                case PRTCNT_RECREPORT_32 - 5:
                default:
                    break;
            }
        }
        else
        {   //打印台头
            memcpy(fu8p_Array, 
                  (fu32_Eng == PRINTER_ENG) ? &cc_PrtRecReport_32_Eng[PRTCNT_RECREPORT_32_FIRST-fu8_PrintCnt][0] : &cc_PrtRecReport_32_Chn[PRTCNT_RECREPORT_32_FIRST-fu8_PrintCnt][0],
                  (PRTTYPELEN_32 + 2));
            if ((PRTCNT_RECREPORT_32_FIRST-fu8_PrintCnt) == 2)
            {   //台头第2行有日期时间需填充
                RTC_DateToASC_Full(&fu8p_Array[6]);    //日期占10字节
                RTC_TimeToASC_Full(&fu8p_Array[17]);    //时间占5字节
            }
            if ((PRTCNT_RECREPORT_32_FIRST-fu8_PrintCnt) == 3)
            {   //台头第3行有单位需要填充
                memcpy(&fu8p_Array[5], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
            }
        }
    }
    else
    {   //80列打印  80列
        if (fu8_PrintCnt <= PRTCNT_RECREPORT_80)
        {   //打印内容
            if (fu8p_Array == gu8_TxdArray_UART0)
                gb_FirstPrintFlg_UART0 = false;   //打印过内容证明已经打印过台头
            else
                gb_FirstPrintFlg_UART1 = false;   //打印过内容证明已经打印过台头
            BIN4toNASC_Echo0(fu32_Result, &fu8p_Array[3], 2); //配方号2字节 3~4
            BIN4toNASC_Point(FRAM_ReadDW(FMAddr_Target(fu32_Result)), &fu8p_Array[9], 6, gs_Cal.Point);   //目标值7字节 9~15
            UnitToAsc( &fu8p_Array[17], gs_Cal.Unit);   //单位2字节 17~18
            BIN4toNASC_Echo0(gu32_SumNum_Rec[fu32_Result], &fu8p_Array[26], 9); //配方包装次数最大9位 26~34
            BIN4toNASC_Point(gu32_SumWt_Rec[fu32_Result], &fu8p_Array[43], 9, gs_Cal.Point);   //配方包装重量10字节 43~52
            UnitToAsc( &fu8p_Array[54], gs_Cal.Unit);   //单位2字节 54~55
            ErrorToAsc(&fu8p_Array[69], gs_Cal.Point, gu32_SumNum_Rec[fu32_Result] * FRAM_ReadDW(FMAddr_Target(fu32_Result)), gu32_SumWt_Rec[fu32_Result]);  //误差8字节 69~76
            UnitToAsc( &fu8p_Array[78], gs_Cal.Unit);   //单位2字节 78~79
            fu8p_Array[PRTTYPELEN_80] = ENDCHAR1;
            fu8p_Array[PRTTYPELEN_80+1] = ENDCHAR2;
        }
        else
        {   //打印台头
            memcpy(fu8p_Array, 
                  (fu32_Eng == PRINTER_ENG) ? &cc_PrtRecReport_80_Eng[PRTCNT_RECREPORT_80_FIRST-fu8_PrintCnt][0] : &cc_PrtRecReport_80_Chn[PRTCNT_RECREPORT_80_FIRST-fu8_PrintCnt][0],
                  (PRTTYPELEN_80 + 2));
            if ((PRTCNT_RECREPORT_80_FIRST-fu8_PrintCnt) == 2)
            {   //台头第二行日期时间需要填充
                RTC_DateToASC_Full(&fu8p_Array[TXDLEN_PRINT-18]);    //日期占10字节
                RTC_TimeToASC_Full(&fu8p_Array[TXDLEN_PRINT-7]);    //时间占5字节
            }
            if ((PRTCNT_RECREPORT_80_FIRST-fu8_PrintCnt) == 5)
            {   //台头第5行有单位需要填充
                memcpy((fu32_Eng == PRINTER_ENG) ? &fu8p_Array[14] : &fu8p_Array[13], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
                memcpy((fu32_Eng == PRINTER_ENG) ? &fu8p_Array[51] : &fu8p_Array[50], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
                memcpy((fu32_Eng == PRINTER_ENG) ? &fu8p_Array[76] : &fu8p_Array[74], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
            }
        }
    }
    if (fu8p_Array == gu8_TxdArray_UART0)
        gvb_PrintingFlg_UART0 = true;
    else
        gvb_PrintingFlg_UART1 = true;
    StartSend_Com(fu8p_Array);
}


/*********************************************************************
函数名称: void PrtTotal_Contents(u8 *fu8p_Array, u32 fu32_PrtType, u32 fu32_Eng, u8 fu8_PrintCnt)
功    能: 配方累计报表内容
说    明: 
入口参数: *fu8p_Array 串口数组指针
          fu32_Wild  080列 116列
          fu32_Eng   0中文 1英文
          fu8_PrintCnt 打印行数
返 回 值: 
设    计: 丛海旭               时    间: 2014-3-7
修    改:                      时    间: 
*********************************************************************/
void PrtTotal_Contents(u8 *fu8p_Array, u32 fu32_PrtType, u32 fu32_Eng, u8 fu8_PrintCnt)
{
    memset(fu8p_Array, ' ', TXDLEN_PRINT);
    if (fu32_PrtType == PRTTYPE_16)
    {   //16列打印 16列
        memcpy(fu8p_Array, 
              (fu32_Eng == PRINTER_ENG) ? &cc_PrtTotal_16_Eng[PRTCNT_TOTAL_16_FIRST-fu8_PrintCnt][0] : &cc_PrtTotal_16_Chn[PRTCNT_TOTAL_16_FIRST-fu8_PrintCnt][0],
              (PRTTYPELEN_16 + 2));
        switch (fu8_PrintCnt)
        {
            case PRTCNT_TOTAL_16_FIRST - 2: //日期时间
                RTC_DateToASC_Full(&fu8p_Array[0]);    //日期占10字节
                RTC_TimeToASC_Full(&fu8p_Array[11]);    //时间占5字节
                break;
            case PRTCNT_TOTAL_16_FIRST - 3: //单位
                memcpy(&fu8p_Array[5], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gu32_SumWtUnit][0] : &cc_Unit_Chn[gu32_SumWtUnit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
                break;
            case PRTCNT_TOTAL_16_FIRST - 5: //总次数
                BIN4toNASC_Echo0(gu32_SumNum, &fu8p_Array[PRTTYPELEN_16-9], 9); //包装次数最大9位
                break;
            case PRTCNT_TOTAL_16_FIRST - 6: //总重量
                BIN4toNASC_Point(gu32_SumWt, &fu8p_Array[PRTTYPELEN_16-10], 9, gu32_SumWtPoint);   //包装重量10字节
                break;
            default:
                break;
        }
    }
    else if (fu32_PrtType == PRTTYPE_32)
    {   //32列打印
        memcpy(fu8p_Array, 
              (fu32_Eng == PRINTER_ENG) ? &cc_PrtTotal_32_Eng[PRTCNT_TOTAL_32_FIRST-fu8_PrintCnt][0] : &cc_PrtTotal_32_Chn[PRTCNT_TOTAL_32_FIRST-fu8_PrintCnt][0],
              (PRTTYPELEN_32 + 2));
        switch (fu8_PrintCnt)
        {
            case PRTCNT_TOTAL_32_FIRST - 2: //日期时间
                RTC_DateToASC_Full(&fu8p_Array[6]);    //日期占10字节
                RTC_TimeToASC_Full(&fu8p_Array[17]);    //时间占5字节
                break;
            case PRTCNT_TOTAL_32_FIRST - 3: //单位
                memcpy(&fu8p_Array[5], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gu32_SumWtUnit][0] : &cc_Unit_Chn[gu32_SumWtUnit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
                break;
            case PRTCNT_TOTAL_32_FIRST - 5: //总次数
                BIN4toNASC_Echo0(gu32_SumNum, &fu8p_Array[PRTTYPELEN_32-9], 9); //包装次数最大9位
                break;
            case PRTCNT_TOTAL_32_FIRST - 6: //总重量
                BIN4toNASC_Point(gu32_SumWt, &fu8p_Array[PRTTYPELEN_32-10], 9, gu32_SumWtPoint);   //包装重量10字节
                break;
            default:
                break;
        }
    }
    else
    {   //80列打印  80列
        if (fu8_PrintCnt <= PRTCNT_TOTAL_80)
        {   //打印内容
            RTC_DateToASC_Full(&fu8p_Array[4]);     //日期占10字节 4~13
            RTC_TimeToASC_Full(&fu8p_Array[24]);    //时间占5字节 24~28
            BIN4toNASC_Echo0(gu32_SumNum, &fu8p_Array[39], 9); //包装次数最大9位 39~47
            BIN4toNASC_Point(gu32_SumWt, &fu8p_Array[58], 9, gu32_SumWtPoint);   //包装重量10字节 58~77
            memcpy(&fu8p_Array[69],  //单位 中文4字节 英文2字节
                   (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gu32_SumWtUnit][0] : &cc_Unit_Chn[gu32_SumWtUnit][0],
                   (fu32_Eng == PRINTER_ENG) ? 2 : 4);
            fu8p_Array[PRTTYPELEN_80-2] = ENDCHAR1;
            fu8p_Array[PRTTYPELEN_80-1] = ENDCHAR2;
        }
        else
        {   //打印台头
            memcpy(fu8p_Array, 
                  (fu32_Eng == PRINTER_ENG) ? &cc_PrtTotal_80_Eng[PRTCNT_TOTAL_80_FIRST-fu8_PrintCnt][0] : &cc_PrtTotal_80_Chn[PRTCNT_TOTAL_80_FIRST-fu8_PrintCnt][0],
                  (PRTTYPELEN_80 + 2));
            if ((PRTCNT_TOTAL_80_FIRST-fu8_PrintCnt) == 2)
            {   //台头第二行日期时间需要填充
                RTC_DateToASC_Full(&fu8p_Array[TXDLEN_PRINT-18]);    //日期占10字节
                RTC_TimeToASC_Full(&fu8p_Array[TXDLEN_PRINT-7]);    //时间占5字节
            }
        }
    }
    if (fu8p_Array == gu8_TxdArray_UART0)
        gvb_PrintingFlg_UART0 = true;
    else
        gvb_PrintingFlg_UART1 = true;
    StartSend_Com(fu8p_Array);
}

/*********************************************************************
函数名称: void PrtRecSet_Contents(u8 *fu8p_Array, u32 fu32_Result, u32 fu32_PrtType, u32 fu32_Eng, u8 fu8_PrintCnt)
功    能: 配方累计报表内容
说    明: 
入口参数: *fu8p_Array 串口数组指针
          fu32_Result (1~20)配方号
          fu32_Wild  080列 116列
          fu32_Eng   0中文 1英文
          fu8_PrintCnt 打印行数
返 回 值: 
设    计: 丛海旭               时    间: 2014-3-7
修    改:                      时    间: 
*********************************************************************/
void PrtRecSet_Contents(u8 *fu8p_Array, u32 fu32_Result, u32 fu32_PrtType, u32 fu32_Eng, u8 fu8_PrintCnt)
{
    memset(fu8p_Array, ' ', TXDLEN_PRINT);
        
    if (fu32_PrtType == PRTTYPE_16)
    {   //16列打印 16列
        if (fu8_PrintCnt <= PRTCNT_RECSET_16)
        {   //打印内容
            if (fu8p_Array == gu8_TxdArray_UART0)
                gb_FirstPrintFlg_UART0 = false;   //打印过内容证明已经打印过台头
            else
                gb_FirstPrintFlg_UART1 = false;   //打印过内容证明已经打印过台头
            memcpy(fu8p_Array, 
                  (fu32_Eng == PRINTER_ENG) ? &cc_PrtRecSet_16_Eng[PRTCNT_RECSET_16_FIRST-fu8_PrintCnt][0] : &cc_PrtRecSet_16_Chn[PRTCNT_RECSET_16_FIRST-fu8_PrintCnt][0],
                  (PRTTYPELEN_16 + 2));
            switch (fu8_PrintCnt)
            {
                case PRTCNT_RECSET_16: //配方
                    BIN4toNASC_Echo0(fu32_Result, &fu8p_Array[PRTTYPELEN_16-2], 2); //配方号
                    break;
                case PRTCNT_RECSET_16 - 1: //目标值
                    BIN4toNASC_Point(FRAM_ReadDW(FMAddr_Target(fu32_Result)), &fu8p_Array[PRTTYPELEN_16-7], 6, gs_Cal.Point);   //重量数据
                    break;
                case PRTCNT_RECSET_16 - 2: //大投
                    BIN4toNASC_Point(FRAM_ReadDW(FMAddr_Large(fu32_Result)), &fu8p_Array[PRTTYPELEN_16-7], 6, gs_Cal.Point);   //重量数据
                    break;
                case PRTCNT_RECSET_16 - 3: //中投
                    BIN4toNASC_Point(FRAM_ReadDW(FMAddr_Middle(fu32_Result)), &fu8p_Array[PRTTYPELEN_16-7], 6, gs_Cal.Point);   //重量数据
                    break;
                case PRTCNT_RECSET_16 - 4: //落差值
                    BIN4toNASC_Point(FRAM_ReadDW(FMAddr_Small(fu32_Result)), &fu8p_Array[PRTTYPELEN_16-7], 6, gs_Cal.Point);   //重量数据
                    break;
                case PRTCNT_RECSET_16 - 5: //零区值
                    BIN4toNASC_Point(FRAM_ReadDW(FMAddr_NearZero(fu32_Result)), &fu8p_Array[PRTTYPELEN_16-7], 6, gs_Cal.Point);   //重量数据
                    break;
                default:
                    break;
            }
        }
        else
        {   //打印台头
            memcpy(fu8p_Array, 
                  (fu32_Eng == PRINTER_ENG) ? &cc_PrtRecSet_16_Eng[PRTCNT_RECSET_16_FIRST-fu8_PrintCnt][0] : &cc_PrtRecSet_16_Chn[PRTCNT_RECSET_16_FIRST-fu8_PrintCnt][0],
                  (PRTTYPELEN_16 + 2));
            if ((PRTCNT_RECSET_16_FIRST-fu8_PrintCnt) == 2)
            {   //台头第2行有日期时间需填充
                RTC_DateToASC_Full(&fu8p_Array[0]);    //日期占10字节
                RTC_TimeToASC_Full(&fu8p_Array[11]);    //时间占5字节
            }
            if ((PRTCNT_RECSET_16_FIRST-fu8_PrintCnt) == 3)
            {   //台头第3行有单位需要填充
                memcpy(&fu8p_Array[5], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
            }
        }
    }
    else if (fu32_PrtType == PRTTYPE_32)
    {   //32列打印
        if (fu8_PrintCnt <= PRTCNT_RECSET_32)
        {   //打印内容
            if (fu8p_Array == gu8_TxdArray_UART0)
                gb_FirstPrintFlg_UART0 = false;   //打印过内容证明已经打印过台头
            else
                gb_FirstPrintFlg_UART1 = false;   //打印过内容证明已经打印过台头
            memcpy(fu8p_Array, 
                  (fu32_Eng == PRINTER_ENG) ? &cc_PrtRecSet_32_Eng[PRTCNT_RECSET_32_FIRST-fu8_PrintCnt][0] : &cc_PrtRecSet_32_Chn[PRTCNT_RECSET_32_FIRST-fu8_PrintCnt][0],
                  (PRTTYPELEN_32 + 2));
            switch (fu8_PrintCnt)
            {
                case PRTCNT_RECSET_32: //配方
                    BIN4toNASC_Echo0(fu32_Result, &fu8p_Array[PRTTYPELEN_32-2], 2); //配方号
                    break;
                case PRTCNT_RECSET_32 - 1: //目标值
                    BIN4toNASC_Point(FRAM_ReadDW(FMAddr_Target(fu32_Result)), &fu8p_Array[PRTTYPELEN_32-7], 6, gs_Cal.Point);   //重量数据
                    break;
                case PRTCNT_RECSET_32 - 2: //大投
                    BIN4toNASC_Point(FRAM_ReadDW(FMAddr_Large(fu32_Result)), &fu8p_Array[PRTTYPELEN_32-7], 6, gs_Cal.Point);   //重量数据
                    break;
                case PRTCNT_RECSET_32 - 3: //中投
                    BIN4toNASC_Point(FRAM_ReadDW(FMAddr_Middle(fu32_Result)), &fu8p_Array[PRTTYPELEN_32-7], 6, gs_Cal.Point);   //重量数据
                    break;
                case PRTCNT_RECSET_32 - 4: //落差值
                    BIN4toNASC_Point(FRAM_ReadDW(FMAddr_Small(fu32_Result)), &fu8p_Array[PRTTYPELEN_32-7], 6, gs_Cal.Point);   //重量数据
                    break;
                case PRTCNT_RECSET_32 - 5: //零区值
                    BIN4toNASC_Point(FRAM_ReadDW(FMAddr_NearZero(fu32_Result)), &fu8p_Array[PRTTYPELEN_32-7], 6, gs_Cal.Point);   //重量数据
                    break;
                default:
                    break;
            }
        }
        else
        {   //打印台头
            memcpy(fu8p_Array, 
                  (fu32_Eng == PRINTER_ENG) ? &cc_PrtRecSet_32_Eng[PRTCNT_RECSET_32_FIRST-fu8_PrintCnt][0] : &cc_PrtRecSet_32_Chn[PRTCNT_RECSET_32_FIRST-fu8_PrintCnt][0],
                  (PRTTYPELEN_32 + 2));
            if ((PRTCNT_RECSET_32_FIRST-fu8_PrintCnt) == 2)
            {   //台头第2行有日期时间需填充
                RTC_DateToASC_Full(&fu8p_Array[6]);    //日期占10字节
                RTC_TimeToASC_Full(&fu8p_Array[17]);    //时间占5字节
            }
            if ((PRTCNT_RECSET_32_FIRST-fu8_PrintCnt) == 3)
            {   //台头第3行有单位需要填充
                memcpy(&fu8p_Array[5], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
            }
        }
    }
    else
    {   //80列打印  80列
        if (fu8_PrintCnt <= PRTCNT_RECREPORT_80)
        {   //打印内容
            if (fu8p_Array == gu8_TxdArray_UART0)
                gb_FirstPrintFlg_UART0 = false;   //打印过内容证明已经打印过台头
            else
                gb_FirstPrintFlg_UART1 = false;   //打印过内容证明已经打印过台头
            BIN4toNASC_Echo0(fu32_Result, &fu8p_Array[3], 2); //配方号2字节 3~4
            BIN4toNASC_Point(FRAM_ReadDW(FMAddr_Target(fu32_Result)), &fu8p_Array[9], 6, gs_Cal.Point);   //目标值7字节 9~15
            BIN4toNASC_Point(FRAM_ReadDW(FMAddr_Large(fu32_Result)), &fu8p_Array[23], 6, gs_Cal.Point);   //大投7字节 23~29
            BIN4toNASC_Point(FRAM_ReadDW(FMAddr_Middle(fu32_Result)), &fu8p_Array[38], 6, gs_Cal.Point);  //中投7字节 38~44
            BIN4toNASC_Point(FRAM_ReadDW(FMAddr_Small(fu32_Result)), &fu8p_Array[53], 6, gs_Cal.Point);   //落差7字节 53~59
            BIN4toNASC_Point(FRAM_ReadDW(FMAddr_NearZero(fu32_Result)), &fu8p_Array[69], 6, gs_Cal.Point);  //零区7字节 69~75
            fu8p_Array[PRTTYPELEN_80] = ENDCHAR1;
            fu8p_Array[PRTTYPELEN_80+1] = ENDCHAR2;
        }
        else
        {   //打印台头
            memcpy(fu8p_Array, 
                  (fu32_Eng == PRINTER_ENG) ? &cc_PrtRecSet_80_Eng[PRTCNT_RECSET_80_FIRST-fu8_PrintCnt][0] : &cc_PrtRecSet_80_Chn[PRTCNT_RECSET_80_FIRST-fu8_PrintCnt][0],
                  (PRTTYPELEN_80 + 2));
            if ((PRTCNT_RECSET_80_FIRST-fu8_PrintCnt) == 2)
            {   //台头第二行日期时间需要填充
                RTC_DateToASC_Full(&fu8p_Array[TXDLEN_PRINT-18]);    //日期占10字节
                RTC_TimeToASC_Full(&fu8p_Array[TXDLEN_PRINT-7]);    //时间占5字节
            }
            if ((PRTCNT_RECSET_80_FIRST-fu8_PrintCnt) == 5)
            {   //台头第5行单位需要填充
                memcpy((fu32_Eng == PRINTER_ENG) ? &fu8p_Array[14] : &fu8p_Array[12], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
                memcpy((fu32_Eng == PRINTER_ENG) ? &fu8p_Array[27] : &fu8p_Array[25], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
                memcpy((fu32_Eng == PRINTER_ENG) ? &fu8p_Array[42] : &fu8p_Array[40], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
                memcpy((fu32_Eng == PRINTER_ENG) ? &fu8p_Array[57] : &fu8p_Array[55], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
                memcpy((fu32_Eng == PRINTER_ENG) ? &fu8p_Array[73] : &fu8p_Array[71], 
                       (fu32_Eng == PRINTER_ENG) ? &cc_Unit_Eng[gs_Cal.Unit][0] : &cc_Unit_Chn[gs_Cal.Unit][0],
                       (fu32_Eng == PRINTER_ENG) ? 2 : 4);
            }
        }
    }
    if (fu8p_Array == gu8_TxdArray_UART0)
        gvb_PrintingFlg_UART0 = true;
    else
        gvb_PrintingFlg_UART1 = true;
    StartSend_Com(fu8p_Array);
}

/*********************************************************************
函数名称: void PrintStart(u8 fu8_PrintMode, u32 fu32_Result, u8 fu8_ComNum)
功    能: 开始打印
说    明: 
入口参数: fu8_PrintMode 0自动打印 1打印累计报表 2打印累计设置 3打印总累计报表
          fu32_Result 本次包装结果 fu8_PrintMode == PRINT_AUTO
          fu32_Result (1~20)配方号 (>20)所有配方 fu8_PrintMode == PRINT_REC_REPORT
          fu32_Result (1~20)配方号 (>20)所有配方 == PRINT_REC_SET
          fu8_ComNum = 1 串口1启动打印
                       2 串口2启动打印
                       0 串口1和2都启动打印
返 回 值: 
设    计: 丛海旭               时    间: 2014-3-4
修    改:                      时    间: 
*********************************************************************/
void PrintStart(u8 fu8_PrintMode, u32 fu32_Result, u8 fu8_ComNum)
{
    if (gs_Setup.ComMode_2 == COM_PRINT && (fu8_ComNum == 2 || fu8_ComNum == 0))
    {
        if (gb_PrintStartFlg_UART0)  //上一组打印还没有完成
            ;
        else if (fu8_PrintMode == PRINT_AUTO && gs_Setup.PrintSwitch_2 == 0) //自动打印开关没有打开
            ;
        else
        {
            gb_PrintStartFlg_UART0 = true;  //开始打印
            gu8_PrintMode_UART0 = fu8_PrintMode;
            switch (gu8_PrintMode_UART0)
            {
            #ifdef DEBUG_MONITORTIME_PRINT
                case PRINT_AUTO_DEBUG:  //调试用
                    gu32_PackingResult = fu32_Result;
                    gvu8_PrintCnt_UART0 = PRTCNT_AUTO;
                    break;
            #endif
                case PRINT_AUTO:    //自动打印
                    gu32_PackingResult = fu32_Result;
                    if (gb_FirstPrintFlg_UART0)   //第一次打印要打印台头
                        gvu8_PrintCnt_UART0 = PRTCNT_AUTO_FIRST;
                    else
                        gvu8_PrintCnt_UART0 = PRTCNT_AUTO;
                    break;
                case PRINT_TOTAL_REPORT:    //总累计报表打印
                    //总累计要打印台头
                    gvu8_PrintCnt_UART0 = cc_PRTCNT_TOTAL_FIRST_ARRAY[gs_Setup.PrintType_2];
                    break;
                case PRINT_REC_REPORT:  //配方报表打印
                    if (fu32_Result >= 1 && fu32_Result <= 20)
                        gu32_PrintRecNum_UART0 = fu32_Result;
                    if (gb_FirstPrintFlg_UART0)   //第一次打印要打印台头
                        gvu8_PrintCnt_UART0 = cc_PRTCNT_RECREPORT_FIRST_ARRAY[gs_Setup.PrintType_2];
                    else
                        gvu8_PrintCnt_UART0 = cc_PRTCNT_RECREPORT_ARRAY[gs_Setup.PrintType_2];
                    break;
                case PRINT_REC_SET: //配方设置打印
                    if (fu32_Result >= 1 && fu32_Result <= 20)
                        gu32_PrintRecNum_UART0 = fu32_Result;
                    if (gb_FirstPrintFlg_UART0)   //第一次打印要打印台头
                        gvu8_PrintCnt_UART0 = cc_PRTCNT_RECSET_FIRST_ARRAY[gs_Setup.PrintType_2];
                    else
                        gvu8_PrintCnt_UART0 = cc_PRTCNT_RECSET_ARRAY[gs_Setup.PrintType_2];
                    break;
            }
        }
    }
    if (gs_Setup.ComMode_1 == COM_PRINT&& (fu8_ComNum == 1 || fu8_ComNum == 0))
    {
        if (gb_PrintStartFlg_UART1)  //上一组打印还没有完成
            ;
        else if (fu8_PrintMode == PRINT_AUTO && gs_Setup.PrintSwitch_1 == 0) //自动打印开关没有打开
            ;
        else
        {
            gb_PrintStartFlg_UART1 = true;  //开始打印
            gu8_PrintMode_UART1 = fu8_PrintMode;
            switch (gu8_PrintMode_UART1)
            {
            #ifdef DEBUG_MONITORTIME_PRINT
                case PRINT_AUTO_DEBUG:  //调试用
                    gu32_PackingResult = fu32_Result;
                    gvu8_PrintCnt_UART1 = PRTCNT_AUTO;
                    break;
            #endif
                case PRINT_STATISTIC:    //统计数据打印
                    //统计数据打印
                    gvu8_PrintCnt_UART1 = PRTCNT_STATISTIC_LINE;
                    break;
                case PRINT_AUTO:    //自动打印
                    gu32_PackingResult = fu32_Result;
                    if (gb_FirstPrintFlg_UART1)   //第一次打印要打印台头
                        gvu8_PrintCnt_UART1 = PRTCNT_AUTO_FIRST;
                    else
                        gvu8_PrintCnt_UART1 = PRTCNT_AUTO;
                    break;
                case PRINT_TOTAL_REPORT:    //总累计报表打印
                    //总累计要打印台头
                    gvu8_PrintCnt_UART1 = cc_PRTCNT_TOTAL_FIRST_ARRAY[gs_Setup.PrintType_1];
                    break;
                case PRINT_REC_REPORT:  //配方报表打印
                    if (fu32_Result >= 1 && fu32_Result <= 20)
                        gu32_PrintRecNum_UART1 = fu32_Result;
                    if (gb_FirstPrintFlg_UART1)   //第一次打印要打印台头
                        gvu8_PrintCnt_UART1 = cc_PRTCNT_RECREPORT_FIRST_ARRAY[gs_Setup.PrintType_1];
                    else
                        gvu8_PrintCnt_UART1 = cc_PRTCNT_RECREPORT_ARRAY[gs_Setup.PrintType_1];
                    break;
                case PRINT_REC_SET: //配方设置打印
                    if (fu32_Result >= 1 && fu32_Result <= 20)
                        gu32_PrintRecNum_UART1 = fu32_Result;
                    if (gb_FirstPrintFlg_UART1)   //第一次打印要打印台头
                        gvu8_PrintCnt_UART1 = cc_PRTCNT_RECSET_FIRST_ARRAY[gs_Setup.PrintType_1];
                    else
                        gvu8_PrintCnt_UART1 = cc_PRTCNT_RECSET_ARRAY[gs_Setup.PrintType_1];
                    break;
            }
        }
    }
}

/*********************************************************************
函数名称: void PrintDeal(u8 *fu8p_Array)
功    能: 打印程序处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-3-4
修    改:                      时    间: 
*********************************************************************/
void PrintDeal(u8 *fu8p_Array)
{
    static bool sb_PrintBlankRows_UART0 = false; //打印空行的标志位
    static bool sb_PrintBlankRows_UART1 = false; //打印空行的标志位
    
    if (fu8p_Array == gu8_TxdArray_UART0)
    {//扩展口2打印处理
        if (gb_PrintStartFlg_UART0 == false)  //没有打印数据 跳出
            ;
        else if (gvb_PrintingFlg_UART0)    //串口正在打印 跳出
            ;
        else if (gvu8_PrintCnt_UART0 > 0)      //有数据需要打印
        {
            if (sb_PrintBlankRows_UART0)
            {   //目前打印的是空行
                gvb_PrintingFlg_UART0 = true;
                StartSend_Com(fu8p_Array);
            }
            else
            {
                switch (gu8_PrintMode_UART0)
                {
                #ifdef DEBUG_MONITORTIME_PRINT
                    case PRINT_AUTO_DEBUG:  //调试用
                        PrtAutoDebug_Contents(fu8p_Array);
                        break;
                #endif
                    case PRINT_AUTO:    //自动打印
                        PrtAuto_Contents(fu8p_Array, gu32_PackingResult, gs_Setup.PrintType_2, gs_Setup.PrintLanguage_2, gvu8_PrintCnt_UART0);
                        break;
                    case PRINT_REC_REPORT:  //配方报表打印
                        PrtRecReport_Contents(fu8p_Array, gu32_PrintRecNum_UART0, gs_Setup.PrintType_2, gs_Setup.PrintLanguage_2, gvu8_PrintCnt_UART0);
                        break;
                    case PRINT_REC_SET: //配方设置打印
                        PrtRecSet_Contents(fu8p_Array, gu32_PrintRecNum_UART0, gs_Setup.PrintType_2, gs_Setup.PrintLanguage_2, gvu8_PrintCnt_UART0);
                        break;
                    case PRINT_TOTAL_REPORT:    //总累计报表打印
                        PrtTotal_Contents(fu8p_Array, gs_Setup.PrintType_2, gs_Setup.PrintLanguage_2, gvu8_PrintCnt_UART0);
                        break;
                }
            }
        }
        else    //打印结束
        {
            if (gb_PrintAllRecFlg_UART0 && sb_PrintBlankRows_UART0 == false)
            {
                //打印所有配方状态，此时要检查有没有其他配方需打印
                gu32_PrintRecNum_UART0 = NextRecNum(gu32_PrintRecNum_UART0);
                if (gu32_PrintRecNum_UART0 != gu32_PrintRecNumStart)
                {   //获取到的下一个目标不为0的配方如果和开始打印的配方相同则代表所有配方已经打印完毕
                    gb_PrintStartFlg_UART0 = false;
                    PrintStart(gu8_Item, gu32_PrintRecNum_UART0, 2);
                }
                else
                {   //如果有打印走纸行数则打印空行 自动打印不打印走纸行数
                    if (gu8_PrintMode_UART0 != PRINT_AUTO && gs_Setup.PrintBlankRows_2 != 0 && sb_PrintBlankRows_UART0 == false)
                    {
                        sb_PrintBlankRows_UART0 = true;
                        gvu8_PrintCnt_UART0 = gs_Setup.PrintBlankRows_2;
                        fu8p_Array[0] = ENDCHAR1;
                        fu8p_Array[1] = ENDCHAR2;
                    }
                    else
                    {   //结束打印空行
                        gb_PrintStartFlg_UART0 = false;
                        sb_PrintBlankRows_UART0 = false;
                    }
                }
            }
            else
            {   //如果有打印走纸行数则打印空行 自动打印不打印走纸行数
                if (gu8_PrintMode_UART0 != PRINT_AUTO && gs_Setup.PrintBlankRows_2 != 0 && sb_PrintBlankRows_UART0 == false)
                {
                    sb_PrintBlankRows_UART0 = true;
                    gvu8_PrintCnt_UART0 = gs_Setup.PrintBlankRows_2;
                    fu8p_Array[0] = ENDCHAR1;
                    fu8p_Array[1] = ENDCHAR2;
                }
                else
                {
                    gb_PrintStartFlg_UART0 = false;
                    sb_PrintBlankRows_UART0 = false;
                #ifdef DEBUG_MONITORTIME_PRINT
                    //时间已经达到1分钟，打印调试总结数据
                    if (gs_DebugRunTimeTemp.u32TotalTime > 60000)
                    {
                        PrintStart(PRINT_AUTO_DEBUG, gs_DebugRunTimeTemp.u32TotalTime, 2);
                        gs_DebugRunTimeTemp.u32TotalTime = 0;
                    }
                #endif
                }
            }
        }
    }
    else
    {//扩展口1打印处理
        if (gb_PrintStartFlg_UART1 == false)  //没有打印数据 跳出
            ;
        else if (gvb_PrintingFlg_UART1)    //串口正在打印 跳出
            ;
        else if (gvu8_PrintCnt_UART1 > 0)      //有数据需要打印
        {
            if (sb_PrintBlankRows_UART1)
            {   //目前打印的是空行
                gvb_PrintingFlg_UART1 = true;
                StartSend_Com(fu8p_Array);
            }
            else
            {
                switch (gu8_PrintMode_UART1)
                {
                #ifdef DEBUG_MONITORTIME_PRINT
                    case PRINT_AUTO_DEBUG:  //调试用
                        PrtAutoDebug_Contents(fu8p_Array);
                        break;
                #endif
                    case PRINT_AUTO:    //自动打印
                        PrtAuto_Contents(fu8p_Array, gu32_PackingResult, gs_Setup.PrintType_1, gs_Setup.PrintLanguage_1, gvu8_PrintCnt_UART1);
                        break;
                    case PRINT_STATISTIC:    //统计数据打印
                        PrtStatistic_Contents(fu8p_Array, gvu8_PrintCnt_UART1);
                        break;
                    case PRINT_REC_REPORT:  //配方报表打印
                        PrtRecReport_Contents(fu8p_Array, gu32_PrintRecNum_UART1, gs_Setup.PrintType_1, gs_Setup.PrintLanguage_1, gvu8_PrintCnt_UART1);
                        break;
                    case PRINT_REC_SET: //配方设置打印
                        PrtRecSet_Contents(fu8p_Array, gu32_PrintRecNum_UART1, gs_Setup.PrintType_1, gs_Setup.PrintLanguage_1, gvu8_PrintCnt_UART1);
                        break;
                    case PRINT_TOTAL_REPORT:    //总累计报表打印
                        PrtTotal_Contents(fu8p_Array, gs_Setup.PrintType_1, gs_Setup.PrintLanguage_1, gvu8_PrintCnt_UART1);
                        break;
                }
            }
        }
        else    //打印结束
        {
            if (gb_PrintAllRecFlg_UART1 && sb_PrintBlankRows_UART1 == false)
            {   
                //打印所有配方状态，此时要检查有没有其他配方需打印
                gu32_PrintRecNum_UART1 = NextRecNum(gu32_PrintRecNum_UART1);
                if (gu32_PrintRecNum_UART1 != gu32_PrintRecNumStart)
                {   //获取到的下一个目标不为0的配方如果和开始打印的配方相同则代表所有配方已经打印完毕
                    gb_PrintStartFlg_UART1 = false;
                    PrintStart(gu8_Item, gu32_PrintRecNum_UART1, 1);
                }
                else
                {   //如果有打印走纸行数则打印空行 自动打印不打印走纸行数
                    if (gu8_PrintMode_UART1 != PRINT_AUTO && gs_Setup.PrintBlankRows_1 != 0 && sb_PrintBlankRows_UART1 == false)
                    {
                        sb_PrintBlankRows_UART1 = true;
                        gvu8_PrintCnt_UART1 = gs_Setup.PrintBlankRows_1;
                        fu8p_Array[0] = ENDCHAR1;
                        fu8p_Array[1] = ENDCHAR2;
                    }
                    else
                    {   //结束打印空行
                        gb_PrintStartFlg_UART1 = false;
                        sb_PrintBlankRows_UART1 = false;
                    }
                }
            }
            else
            {   //如果有打印走纸行数则打印空行 自动打印不打印走纸行数
                if (gu8_PrintMode_UART1 != PRINT_AUTO && gs_Setup.PrintBlankRows_1 != 0 && sb_PrintBlankRows_UART1 == false)
                {
                    sb_PrintBlankRows_UART1 = true;
                    gvu8_PrintCnt_UART1 = gs_Setup.PrintBlankRows_1;
                    fu8p_Array[0] = ENDCHAR1;
                    fu8p_Array[1] = ENDCHAR2;
                }
                else
                {
                    gb_PrintStartFlg_UART1 = false;
                    sb_PrintBlankRows_UART1 = false;
                #ifdef DEBUG_MONITORTIME_PRINT
                    //时间已经达到1分钟，打印调试总结数据
                    if (gs_DebugRunTimeTemp.u32TotalTime > 60000)
                    {
                        PrintStart(PRINT_AUTO_DEBUG, gs_DebugRunTimeTemp.u32TotalTime, 1);
                        gs_DebugRunTimeTemp.u32TotalTime = 0;
                    }
                #endif
                }
            }
        }
    }
}





/*********************************************************************
函数名称: void PrintResult_Old(u8 fu8p_Array, u32 fu32_Result)
功    能: 每秤包装结果的打印
说    明: 该函数为旧版51单片机的打印格式
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-1-21
修    改:                      时    间: 
*********************************************************************/
void PrintResult_Old(u8 *fu8p_Array, u32 fu32_Result)
{
    u8 i;
    
    memset(fu8p_Array, ' ', TXDLEN_PRINT);  //清串口打印发送数组为空格
        
    fu8p_Array[0] = STARTCHAR;         //起始符
    fu8p_Array[1] = 0x30 + ((fu8p_Array == gu8_TxdArray_UART0 ? gs_Setup.TareNumber_2 : gs_Setup.TareNumber_1) / 10);
    fu8p_Array[2] = 0x30 + ((fu8p_Array == gu8_TxdArray_UART0 ? gs_Setup.TareNumber_2 : gs_Setup.TareNumber_1) % 10);       //秤号
    fu8p_Array[3] = ',';
    fu8p_Array[4] = 0x30 + (gu32_RecNum / 10);                 //配方号
    fu8p_Array[5] = 0x30 + (gu32_RecNum % 10);                 //配方号
    fu8p_Array[6] = ',';
    //累计次数转为ASCII码，9位，存入[7~15]中
    BIN4toNASC(gu32_SumNum, &fu8p_Array[7], 9);
    for (i = 7; i < 15; i++)        //消隐
    {
        if (fu8p_Array[i] == 0x30)
            fu8p_Array[i] = ' ';
        else
            break;
    }
    fu8p_Array[16] = ',';
    
    //重量转为ASCII码，7位包含1位小数点，存入[17~23]中
    fu8p_Array[17] = 0x30;
    BIN4toNASC(fu32_Result, &fu8p_Array[18], 6);
    if (gs_Cal.Point != 0)          //小数点处理
    {
        for (i = 0; i < 6 - gs_Cal.Point; i++)
            fu8p_Array[17+i] = fu8p_Array[18+i];
        fu8p_Array[17+i] = '.';
    }
    for (i = 17; i < 23; i++)        //消隐
    {
        if (fu8p_Array[i] == 0x30 && fu8p_Array[i+1] != '.')
            fu8p_Array[i] = ' ';
        else
            break;
    }
    fu8p_Array[24] = ENDCHAR1;
    fu8p_Array[25] = ENDCHAR2;
    StartSend_Com(fu8p_Array);
}

/*********************************************************************
函数名称: void SetPrintSumArry(u8 *fu8p_Array, u8 fu8_i)
功    能: 构造打印数组
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2011-5-5
修    改:                      时    间: 
*********************************************************************/
void SetPrintSumArry(u8 *fu8p_Array, u8 fu8_i)
{
    #define PRINTNUM 25
    u8 i;
    
    
    memset(fu8p_Array, ' ', TXDLEN_PRINT);
    switch (fu8_i)
    {
        case 0:
        case 4:     //------------------
            memset(fu8p_Array, '-', PRINTNUM-1);
            fu8p_Array[PRINTNUM-1] = ENDCHAR1;
            fu8p_Array[PRINTNUM] = ENDCHAR2;
            break;
        case 1:     //累计重量
            fu8p_Array[0] = 'T';
            fu8p_Array[1] = 'o';
            fu8p_Array[2] = 't';
            fu8p_Array[3] = 'a';
            fu8p_Array[4] = 'l';
            fu8p_Array[5] = ':';
            switch (gu32_SumWtUnit) //累计单位
            {
                case UNIT_lb:
                    fu8p_Array[PRINTNUM-3] = 'l';
                    fu8p_Array[PRINTNUM-2] = 'b';
                    break;
                case UNIT_g:
                    fu8p_Array[PRINTNUM-3] = ' ';
                    fu8p_Array[PRINTNUM-2] = 'g';
                    break;
                case UNIT_kg:
                    fu8p_Array[PRINTNUM-3] = 'k';
                    fu8p_Array[PRINTNUM-2] = 'g';
                    break;
                case UNIT_t:
                default:
                    fu8p_Array[PRINTNUM-3] = ' ';
                    fu8p_Array[PRINTNUM-2] = 't';
                    break;
            }
            //累计重量转为ASCII码存入fu8p_Array中
            fu8p_Array[PRINTNUM-13] = 0x30;
            BIN4toNASC(gu32_SumWt, &fu8p_Array[PRINTNUM-12], 9);
            if (gu32_SumWtPoint != 0)          //小数点处理
            {
                for (i = 0; i < 9 - gu32_SumWtPoint; i++)
                    fu8p_Array[PRINTNUM-13+i] = fu8p_Array[PRINTNUM-12+i];
                fu8p_Array[PRINTNUM-13+i] = '.';
            }
            for (i = PRINTNUM-13; i < PRINTNUM-4; i++)        //消隐
            {
                if (fu8p_Array[i] == 0x30 && fu8p_Array[i+1] != '.')
                    fu8p_Array[i] = ' ';
                else
                    break;
            }
            fu8p_Array[PRINTNUM-1] = ENDCHAR1;
            fu8p_Array[PRINTNUM] = ENDCHAR2;
            break;
        case 2: //累计次数
            fu8p_Array[0] = 'S';
            fu8p_Array[1] = 'u';
            fu8p_Array[2] = 'm';
            fu8p_Array[3] = ':';
            //累计次数
            BIN4toNASC(gu32_SumNum, &fu8p_Array[PRINTNUM-10], 9);
            for (i = PRINTNUM-10; i < PRINTNUM-2; i++)        //消隐
            {
                if (fu8p_Array[i] == 0x30)
                    fu8p_Array[i] = ' ';
                else
                    break;
            }
            fu8p_Array[PRINTNUM-1] = ENDCHAR1;
            fu8p_Array[PRINTNUM] = ENDCHAR2;
            break;
        case 3:
            RTC_ReadDateTime(&SysDataTime);        //读系统日期和时间
            fu8p_Array[0] = '2';
            fu8p_Array[1] = '0';
            fu8p_Array[2] = 0x30 + (SysDataTime.year >> 4);
            fu8p_Array[3] = 0x30 + (SysDataTime.year & 0x0F);
            fu8p_Array[4] = '.';
            fu8p_Array[5] = 0x30 + (SysDataTime.month >> 4);
            fu8p_Array[6] = 0x30 + (SysDataTime.month & 0x0F);
            fu8p_Array[7] = '.';
            fu8p_Array[8] = 0x30 + (SysDataTime.date >> 4);
            fu8p_Array[9] = 0x30 + (SysDataTime.date & 0x0F);
            
            fu8p_Array[12] = 0x30 + (SysDataTime.hour >> 4);
            fu8p_Array[13] = 0x30 + (SysDataTime.hour & 0x0F);
            fu8p_Array[14] = ':';
            fu8p_Array[15] = 0x30 + (SysDataTime.min >> 4);
            fu8p_Array[16] = 0x30 + (SysDataTime.min & 0x0F);
            
            fu8p_Array[PRINTNUM-1] = 0x0D;
            fu8p_Array[PRINTNUM] = 0x0A;
            break;
        case 5:
        case 6:
            fu8p_Array[0] = ENDCHAR1;
            fu8p_Array[1] = ENDCHAR2;
        default:
            break;
    }
    if (fu8_i < 7)
        StartSend_Com(fu8p_Array);
}

/*********************************************************************
函数名称: void PrintSum(void)
功    能: 打印累计值
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-1-21
修    改:                      时    间: 
*********************************************************************/
void PrintSum(void)
{
    u8 i = 0;
    u8 j = 0;
    
    VFD_ClrDispRam(gu32_ModelSetSwitch, gu32_ModelArry[0]);       //清显示缓存
    VFD_MainDisp_Str(" PRINT");         //显示PRINT
    VFD_CopyDispArryToDispRam();         //将显示数组存入显示缓存
    VFD_WriteDispRamArry();                    //写显示缓存 
    
    while ((gs_Setup.ComMode_1 == COM_PRINT && i < 7) || (gs_Setup.ComMode_2 == COM_PRINT && j < 7))
    {
//        AD_A();
//        AD_B();
        OPBuzzer();
        
        if (gs_Setup.ComMode_1 == COM_PRINT && gvb_SioTxingFlg_UART1 == false && i < 7)
        {
            SetPrintSumArry(gu8_TxdArray_UART1, i);
            i++;
        }
        else if (gs_Setup.ComMode_1 != COM_PRINT)
            i++;
        
        
        if (gs_Setup.ComMode_2 == COM_PRINT && gvb_SioTxingFlg_UART0 == false && j < 7)       //没在发送时发送下一条
        {
            SetPrintSumArry(gu8_TxdArray_UART0, j);
            j++;
        }
        else if (gs_Setup.ComMode_2 != COM_PRINT)
            j++;
    }
}

/*********************************************************************
函数名称: void PrintBlankRows(void)
功    能: 打印空行，回车换行，打印机走一行纸
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-04-11
修    改:                      时    间: 
*********************************************************************/
void PrintBlankRows(void)
{
    if (gs_Setup.ComMode_2 == COM_PRINT)
    {//扩展口2打印处理
        if (gb_PrintStartFlg_UART0 || gvb_PrintingFlg_UART0)  //有数据正在打印
            ;
        else
        {
            gu8_TxdArray_UART0[0] = ENDCHAR1;
            gu8_TxdArray_UART0[1] = ENDCHAR2;
            StartSend_Com(gu8_TxdArray_UART0);
        }
    }
    if (gs_Setup.ComMode_1 == COM_PRINT)
    {//扩展口1打印处理
        if (gb_PrintStartFlg_UART1 || gvb_PrintingFlg_UART1)  //有数据正在打印
            ;
        else
        {
            gu8_TxdArray_UART1[0] = ENDCHAR1;
            gu8_TxdArray_UART1[1] = ENDCHAR2;
            StartSend_Com(gu8_TxdArray_UART1);
        }
    }
}

/*********************************************************************
函数名称: void Key_PrintState(void)
功    能: 打印状态相关处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-3-3
修    改:                      时    间: 
*********************************************************************/
void Key_PrintState(void)
{
    u8 luc_DataLen = 0;      //输入数据位数
    
    if (gu32_KeyCode == K_RIGHT)
    {
        gu8_Item++;
        if (gu8_Item > PRINT_REC_SET)
            gu8_Item = PRINT_TOTAL_REPORT;
        ulParameter.ul = gu32_RecNum;
        gb_PrintAllFlg = false;
        gb_FlashFlg = false;
        gb_FirstPrintFlg_UART0 = true;
        gb_PrintAllRecFlg_UART0 = false;
        gb_FirstPrintFlg_UART1 = true;
        gb_PrintAllRecFlg_UART1 = false;
        gb_FirstNumKeyFlg = true;
    }
    switch (gu8_Item)
    {
        case PRINT_REC_REPORT:
        case PRINT_REC_SET:
            luc_DataLen = 2;    //可输入配方号
            break;
        case PRINT_TOTAL_REPORT:
            break;
        default:
            break;
    }
    if (gu32_KeyCode != K_ZERO) //ZERO键用作打印走纸
        ulParameter.ul = Key_NumInput(ulParameter.ul, luc_DataLen);
    
    switch (gu32_KeyCode)
    {
        case K_ZERO:    //走纸一行
            PrintBlankRows();
            break;
        case K_ENTER:   //打印
            if (gb_FlashFlg)
            {   //配方号不符合范围不能打印
                ErrorDeal(0, 100);    //显示error
                ulParameter.ul = gu32_RecNum;
            }
            else 
            {
                if (gb_PrintAllFlg)
                {   //打印所有配方数据 打印台头
                    gb_FirstPrintFlg_UART0 = true;
                    gb_PrintAllRecFlg_UART0 = true;
                    gb_FirstPrintFlg_UART1 = true;
                    gb_PrintAllRecFlg_UART1 = true;
                    //打印所有目标值不为0的配方
                    if (gs_Rec.Target != 0)
                    {
                        gu32_PrintRecNumStart = gu32_RecNum;    //保存起始配方号，用来判断是否有所配方都打印完成
                        PrintStart(gu8_Item, gu32_RecNum, 0);  //从当前配方开始打印
                    }
                    else
                    {   //当前配方目标值为0，获取下一个目标值不为0的配方号
                        gu32_PrintRecNumStart = NextRecNum(gu32_RecNum);
                        if (gu32_PrintRecNumStart != gu32_RecNum)
                        {   //如果获取到的下一个不为0的配方号和目前配方号相等，代表所有配方目标值都为0，不打印
                            PrintStart(gu8_Item, gu32_PrintRecNumStart, 0);  //从目标值不为0的配方号开始打印
                        }
                    }
                }
                else
                {
                    gb_FirstPrintFlg_UART0 = true;
                    gb_FirstPrintFlg_UART1 = true;
                    gb_PrintAllRecFlg_UART0 = false;
                    gb_PrintAllRecFlg_UART1 = false;
                    PrintStart(gu8_Item, ulParameter.ul, 0);
                }
            }
            gb_FirstNumKeyFlg = true;
            break;
        case K_INC: //调到下一个目标值不为0的配方号
            ulParameter.ul = NextRecNum(ulParameter.ul);
            break;
        case K_SET:
            if (gu8_Item == PRINT_REC_REPORT || gu8_Item == PRINT_REC_SET)
                gb_PrintAllFlg = (!gb_PrintAllFlg);
            break;
        case K_ESC:
            if (ulParameter.ul != gu32_RecNum)  //显示不是当前配方按ESC返回当前配方号显示
                ulParameter.ul = gu32_RecNum;
            else if (gb_PrintAllFlg)    //退出打印所有配方状态
                gb_PrintAllFlg = false;
            else    //退出
            {
                gu32_SystemState = STOPSTATE;
                gb_FlashFlg = false;
            }
            break;
        default:
            break;
    }
}


/*********************************************************************
函数名称: void Disp_PrintState(void)
功    能: 打印相关显示处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2014-3-3
修    改:                      时    间: 
*********************************************************************/
void Disp_PrintState(void)
{
    switch (gu8_Item)
    {
        case PRINT_TOTAL_REPORT:
            VFD_MainDisp_Str("PRT1");
            VFD_AuxDisp_Str("---");
            break;
        case PRINT_REC_REPORT:
            if (ulParameter.ul > 20 || ulParameter.ul < 1)
                gb_FlashFlg = true;
            else
                gb_FlashFlg = false;
            VFD_MainDisp_Str("PRT2");
            if (gb_PrintAllFlg) //打印所有配方报表
                VFD_AuxDisp_Str("ALL");
            else
                Disp_Aux_Rec(ulParameter.ul);
            break;
        case PRINT_REC_SET:
            if (ulParameter.ul > 20 || ulParameter.ul < 1)
                gb_FlashFlg = true;
            else
                gb_FlashFlg = false;
            VFD_MainDisp_Str("PRT3");
            if (gb_PrintAllFlg) //打印所有配方报表
                VFD_AuxDisp_Str("ALL");
            else
                Disp_Aux_Rec(ulParameter.ul);
            break;
        default:
            break;
    }
    
    Flash_AuxDisp(0x03);
}

