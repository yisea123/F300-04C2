#include "include.h"

u32  gu32_SystemState;         //系统工作状态
ULDATA ulParameter;            //数据输入变量
u8  gu8_Item;                  //设置时区分各个项目
bool gb_PrintCodeIngFlg;        //打码标志，用来屏蔽加料等
bool gb_StopPrintCodeFlg;       //停止打码

#ifdef DEBUG_ADCNVT_TIMES
    u32 gu32_AdConventTimes;        //调试用AD转换次数
#endif


//
/***********************************************************
函数名称: void PrintCodeFun(u32 fu32_PCSwitch,   //打码开关
                   u32 fu32_PCTime,     //打码时间
                   u32 fu32_PCRDelay,   //打码启动延时
                   u32 fu32_Sys10ms,    //系统时间，单位10ms
                   bool fb_PackFlg,     //夹袋输出
                   bool *fbp_StopPCFlg, //停止打码，如正在打码时停止信号输入
                   bool *fbp_PCOutFlg,  //打码开关量输出变量
                   bool *fbp_RCDelayFlg //打码启动延时或打码输出时有效，用来屏蔽卸料等
               )
功    能: 打码功能
说    明: 打码开关未开或打码时间为零此功能无效
          当打码时间未到,此时已松袋,立即结束打码输出
          停止输入立即结束打码
          改为独立的可移植函数，使用各变量含义见下面函数入口变量注释
          chx 2013-9-29
入口参数: 
调用程序: 
返 回 值: 无
设    计: 丛海旭              时    间:2013-9-29
修    改:                     时    间:
***********************************************************/
void PrintCodeFun(u32 fu32_PCSwitch,   //打码开关
                   u32 fu32_PCTime,     //打码时间
                   u32 fu32_PCRDelay,   //打码启动延时
                   u32 fu32_Sys10ms,    //系统时间，单位10ms
                   bool fb_PackFlg,     //夹袋输出
                   bool *fbp_StopPCFlg, //停止打码，如正在打码时停止信号输入
                   bool *fbp_PCOutFlg,  //打码开关量输出变量
                   bool *fbp_RCDelayFlg //打码启动延时或打码输出时有效，用来屏蔽卸料等
               )
{
    static bool  bPrnDelayEn = false;      //打码延时启动标志
    static bool  bHadPrn = false;              //已打印标志
    static u32 baktime1 = 0;
    static u32 baktime2 = 0;
    
    if((fu32_PCSwitch&0x01)==0 || fu32_PCTime==0) //开关关闭或打码时间为零则此功能无效
    {
        *fbp_RCDelayFlg = false;
        return;
    }
    
    if(*fbp_StopPCFlg)       //停止信号输入立即结束打码
    {
        *fbp_PCOutFlg = false;
        bPrnDelayEn = false;
        bHadPrn = true;
        *fbp_StopPCFlg = false;
    }
    //此处也加一个赋值*fbp_RCDelayFlg的语句，因为有可能走下面的return后最后的赋值语句走不到
    *fbp_RCDelayFlg = ((bPrnDelayEn)||(*fbp_PCOutFlg)) ? true : false;
    
    if(fb_PackFlg)
    {
        if(bHadPrn)
        {
            return;
        }
        if(!bPrnDelayEn)
        {
            bPrnDelayEn = true;        //延时启动
            baktime1 = gu32_Sys10ms;       //读当前时间
        }
        if((*fbp_PCOutFlg == false) && (gu32_Sys10ms - baktime1 >= (10*fu32_PCRDelay)))
        {
            *fbp_PCOutFlg = true;
            baktime2 = gu32_Sys10ms;
        }
        
        if(*fbp_PCOutFlg && (gu32_Sys10ms - baktime2 >= (10*fu32_PCTime)))
        {
            *fbp_PCOutFlg = false;
            bPrnDelayEn = false;
            bHadPrn = true;
        }
    }
    else
    {
        *fbp_PCOutFlg = false;
        bPrnDelayEn = false;
        bHadPrn = false;      //恢复已打印标志
    }
    *fbp_RCDelayFlg = ((bPrnDelayEn)||(*fbp_PCOutFlg)) ? true : false;
}

/*********************************************************************
函数名称: void RCCU_Config(void)
功    能: 系统时钟配置
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2010-12-3
修    改:                      时    间: 
*********************************************************************/
void RCCU_Config(void)
{
    RCCU_Div2Config(ENABLE);                        // 使能2分频//RCCU_CFR中的DIV2控制位置位
    RCCU_MCLKConfig(RCCU_DEFAULT);                  // Configure MCLK = RCLK内核和存储器时钟
    RCCU_PCLK1Config(RCCU_DEFAULT);                  // Configure FCLK = RCLK
    RCCU_PCLK2Config(RCCU_DEFAULT);                  // Configure PCLK = RCLK
    RCCU_PLL1Config(RCCU_PLL1_Mul_16, RCCU_Div_2) ;      // Configure the PLL1 (* 16 , / 2)  
    while(RCCU_FlagStatus(RCCU_PLL1_LOCK) == RESET);// Wait PLL to lock
    RCCU_RCLKSourceConfig(RCCU_PLL1_Output) ;       // Select PLL1_Output as RCLK clock
    //至此时钟配置完毕，MCLK = FCLK = PCLK = 11.0592/2*16/2 = 44.2368MHz
}

/*********************************************************************
函数名称: void Flash_All3t(void)
功    能: 上电闪烁3次
说    明: 程序中包括恢复出厂设置的处理
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-11
修    改:                      时    间: 
*********************************************************************/
void Flash_All3t(void)
{
    u16 i, j;
    u32 lu32_Key;
    u16 lu16_PressedKey = 0;
    
    CmpDay();   //获取gb_SysClosedFlg变量的值
FLASH_3T:
    lu32_Key = 0;
    for (i = 0; i <= 5; i++)
    {
        //闪烁3次
        if (i % 2 == 0)
            VFD_FillDispRam(gu32_ModelSetSwitch, gu32_ModelArry[0]);
        else
            VFD_ClrDispRam(gu32_ModelSetSwitch, gu32_ModelArry[0]);
            
        VFD_WriteDispRamArry();
        
        //闪烁时如果AD初始化未成功则继续初始化
        if (!gb_AdOKFlg)
            gb_AdOKFlg = AD_Init(FRAM_ReadDW(FMAddr_AdSamplingRate));            //AD初始化
        
        //闪烁时进行AD转换，填充AD队列，防止闪烁完成后重量从0迅速变化到当前重量的过程
        //另外保证根据不同AD转换次数时间相同
        for (j = 0; j < 60 * cu8_MultiAd[FRAM_ReadDW(FMAddr_AdSamplingRate) <= 3 ? FRAM_ReadDW(FMAddr_AdSamplingRate) : 1]; j++)
        {
            lu32_Key = Key_Deal();             //读按键
            OPBuzzer();
            if (lu32_Key != K_NONE)
            {
                switch(lu32_Key)
                {
                    case K_7:       //按7号键备份和恢复参数
                        lu16_PressedKey = K_7;
                        break;
//                    case K_1:       //按1键恢复参数
//                        lu16_PressedKey = K_1;
//                        break;
//                    case K_4:       //按4键备份参数
//                        lu16_PressedKey = K_4;
//                        break;
//                    case K_8:       //按8键再按5键进入显示测试
//                        lu16_PressedKey = K_8;
//                        break;
//                    case K_5:       //按8键再按5键进入显示测试
//                        if (lu16_PressedKey == K_8)
//                            lu16_PressedKey = K_5;
//                        else if (lu16_PressedKey == K_5)
//                            lu16_PressedKey = K_5;
//                        else 
//                            lu16_PressedKey = K_NONE;
//                        break;
//                    case K_AZERO_BZERO:     //同时按AB清零键进入串口升级程序
//                        lu16_PressedKey = K_AZERO_BZERO;
//                        break;
                    case K_ENTER:   //按ENTER键进入初始化界面
                        lu16_PressedKey = K_ENTER;
                        break;
                    default:
                        lu16_PressedKey = K_NONE;
                        break;
                }
            }
            
            if (gb_AdOKFlg)
                AD_GetFedVal(gs_Setup.AdFilterLevel);
            else
                delay(4);
            if (lu16_PressedKey == K_ENTER || lu16_PressedKey == K_7)  //有按键马上跳出循环
                break;
        }
        if (lu16_PressedKey == K_ENTER || lu16_PressedKey == K_7)  //有按键马上跳出循环
            break;
    }
    if (lu16_PressedKey == K_ENTER && gb_SysClosedFlg == false)     //初始化
    {
        gb_KeyLockFlg = false;
        gu32_SystemState = RESETSTATE;
        Reset_Parameter();      //恢复出厂设置操作
        lu16_PressedKey = 0;
        goto FLASH_3T;          //重新闪烁3次
    }
    if (lu16_PressedKey == K_7 && gb_SysClosedFlg == false)     //参数备份和恢复
    {
        gb_KeyLockFlg = false;
        gu32_SystemState = BORRSTATE;
        BorR_Parameter();      //参数备份和恢复操作
        lu16_PressedKey = 0;
        goto FLASH_3T;          //重新闪烁3次
    }
}

/*********************************************************************
函数名称: void System_Init(void)
功    能: 系统初始化
说    明: 
调    用: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2010-12-3
修    改:                      时    间: 
*********************************************************************/
void System_Init(void)
{
    APB_ClockConfig(APB1,ENABLE,APB1_ALL_Periph);
    APB_ClockConfig(APB2,ENABLE,APB2_ALL_Periph);       //开外设
    RCCU_Config();              //系统时钟配置
    IO_Init();      //开关量口初始化
    Buzzer_Init();  //蜂鸣器初始化
    RTC_Init();     //时钟芯片初始化
    FRAM_Init();    //FRAM芯片初始化
    VFD_Init();     //VFD初始化
    VFD_ClrDispRam(gu32_ModelSetSwitch, gu32_ModelArry[0]);
    VFD_WriteDispRamArry();     //清显示
    EIC_Init();                 //初始化中断寄存器
    Timer0_Init();              //定时器0初始化，程序用时钟
    Timer1_Init();      //预测SP2截止点使用定时器
    
    gb_AdOKFlg = AD_Init(FRAM_ReadDW(FMAddr_AdSamplingRate));            //AD初始化
    Buzzer_PowerOn();
    EIC_IRQConfig(ENABLE);      //开放总中断
    //定时锁机相关变量
    gu32_GetedRandom = FRAM_ReadDW(FMAddr_GetedRandom);         //读取随机数已经获取过标志
    gu32_ShutDownSwitch = FRAM_ReadDW(FMAddr_ShutDownSwitch);   //读取定时锁机开关
    gu32_ShutDownCode = FRAM_ReadDW(FMAddr_ShutDownCode);       //读取定时锁机密码
    gu32_BuyerID = FRAM_ReadDW(FMAddr_BuyerID);                 //读取用户ID
    gu32_LeaveDays = FRAM_ReadDW(FMAddr_LeaveDays);             //读取剩余天数
    gu32_RandomID =  FRAM_ReadDW(FMAddr_RandomID);              //读取随机ID
    UpdataGrandShutCode();
    
    gu32_ModelSetSwitch = FRAM_ReadDW(FMAddr_ModelSetSwitch);   //型号自定义开关
    FRAM_ContReadDW(FMAddr_ModelSet0, gu32_ModelArry, 7);        //读型号设置和logo开关
    
    Flash_All3t();              //上电闪烁
    Init_Parameter();           //初始化变量
    
    if (Pbus_CheckExt())
    {   //检测到连接的是DP+串口板
        gu8_ExtType = PBUS_UART;
        if (gs_Setup.ComMode_1 != COM_PBUS)
        {   //通讯模式改成PROFIBUS
            gs_Setup.ComMode_1 = COM_PBUS;
            FRAM_WriteDW(FMAddr_ComMode_1, gs_Setup.ComMode_1);
        }
    }
    else
    {   //检测到连接的是双串口版
        gu8_ExtType = UART_UART;
        if (gs_Setup.ComMode_1 == COM_PBUS)
        {   //如果之前是PROFIBUS的板，改成双串口后，通讯格式默认为PRINT
            gs_Setup.ComMode_1 = COM_PRINT;
            FRAM_WriteDW(FMAddr_ComMode_1, gs_Setup.ComMode_1);
        }
    }
    
    Uart0_Init();                //串口0初始化
    Uart1_Init();                //串口1初始化
    
    gu32_SystemState = STOPSTATE;
}

///*********************************************************************
//函数名称: void WorkStateDeal(void)
//功    能: 各个工作状态下的按键处理
//说    明: 
//入口参数: 
//返 回 值: 
//设    计: 丛海旭               时    间: 2010-12-30
//修    改:                      时    间: 
//*********************************************************************/
void WorkStateDeal(void)
{
    gu32_KeyCode = Key_Deal();
    //防止串口通讯中断中对485s操作置接收后跳出中断操作SPI总线GPIO1端口，导致重新置发送,VFD_KeyDeal函数中会操作SPI总线，
    //有可能影响485S，所以放在该函数后面    chx 2011-12-29
    if (gb_S485Recieve == true)
    {
        Sio_485_Enable();
        gb_S485Recieve = false;
    }
    OPBuzzer();      //蜂鸣器响声处理
    switch (gu32_SystemState)
    {
        case RUNSTATE:              //运行状态
            IO_InScan();            //输入开关量扫描
            Key_RunState();
            break;
        case STOPSTATE:             //停止状态
            IO_InScan();            //输入开关量扫描
            Key_StopState();
            break;
        case SETUPSTATE:            //工作参数设置
            Key_SetupState();
            break;
        case CALIBSTATE:            //标定
            Key_CalibState();
            break;
        case BATCHSTATE:            //批次数设置
            Key_BatchState();
            break;
        case TIMESTATE:             //时间
            Key_DateTimeState();
            break;
        case DATESTATE:             //日期
            Key_DateTimeState();
            break;
        case RECIPESTATE:           //配方设置
            Key_RecipeState();
            break;
        case SUMSTATE:              //累计查询
            Key_SumState();
            break;
        case IOTESTSTATE:           //IO测试
            Key_IoTestState();
            break;
        case IODEFINESTATE:         //IO自定义
            Key_IoDefState();
            break;
        case SHUTDOWNSTATE:         //定时锁机设置
            Key_ShutdownState();
            break;
        case DEBUGSTATE:            //调试界面 串口匹配
            Key_DebugState();
            break;
        case PRINTSTATE:            //打印界面
            Key_PrintState();
            break;
        default:
            break;
    }
}

/*********************************************************************
函数名称: void Disp_MainFun(void)
功    能: 主循环显示处理
说    明: 
入口参数: 
返 回 值: 
设    计: 丛海旭               时    间: 2013-12-11
修    改:                      时    间: 
*********************************************************************/
void Disp_MainFun(void)
{
    static u32 su32_TimeTemp = 0;
    
    if (gu32_Sys10ms - su32_TimeTemp < 4)  //40ms刷新一次显示 v1.01
        return;
    su32_TimeTemp = gu32_Sys10ms;
    VFD_Init();     //VFD初始化 v1.01
    VFD_ClrDispRam(gu32_ModelSetSwitch, gu32_ModelArry[0]);       //清显示缓存
    switch(gu32_SystemState)
    {
        case RUNSTATE:
        case STOPSTATE:
            Disp_StopRunState();         //停止状态下的显示处理
            break;
        case RECIPESTATE:
            Disp_RecipeState();          //配方设置状态下的显示处理
            break;
        case SETUPSTATE:
            Disp_SetupState();           //工作参数设置状态下的显示处理
            break;
        case IOTESTSTATE:
            Disp_IoTestState();          //开关量测试状态下的显示处理
            break;
        case IODEFINESTATE:
            Disp_IoDefState();           //开关量自定义状态下的显示处理
            break;
        case CALIBSTATE:
            Disp_CalibState();           //标定状态下的显示处理
            break;
        case TIMESTATE:
            Disp_DateTimeState();            //时间设置状态下的显示处理
            break;
        case DATESTATE:
            Disp_DateTimeState();            //日期设置状态下的显示处理
            break;
        case SHUTDOWNSTATE:
            Disp_ShutdownState();            //关机状态下的显示处理
            break;
        case BATCHSTATE:
            Disp_BatchState();           //批次设置状态下的显示处理
            break;
        case SUMSTATE:
            Disp_SumState();            //累计查看显示处理
            break;
        case DEBUGSTATE:            //调试界面 串口匹配
            Disp_DebugState();
            break;
        case PRINTSTATE:            //打印界面
            Disp_PrintState();
            break;
        default:
            break;
    }
    
    if (gb_DispErrorFlg)        //显示error
    {   //错误报警时不显示单位
        Disp_Error();           //error报警显示处理
        VFD_CopyMainDispArryToDispRam();    //主显示缓存
        VFD_CopyAuxDispArryToDispRam();     //副显示缓存
        VFD_CopyFlgDispArryToDispRam();     //标志灯缓存
    }
    else
        VFD_CopyDispArryToDispRam();         //将显示数组存入显示缓存
    VFD_WriteDispRamArry();                    //写显示缓存 
}

/*********************************************************************
函数名称: void Lift_Push_Bag(bool *fbp_LiftStart, bool *fbp_PushStart)
功    能: 提袋推袋处理
说    明: 
入口参数: *fbp_LiftStart 提袋启动标志位  
          *fbp_PushStart 推袋启动标志位
返 回 值: 
设    计: 丛海旭               时    间: 2014-2-27
修    改:                      时    间: 
*********************************************************************/
void Lift_Push_Bag(bool *fbp_LiftStart, bool *fbp_PushStart)
{
    static u32 su32_LiftTimeTemp;
    static bool sb_LiftDelayFlg = false;    //提袋延时已启动
    static u32 su32_PushTimeTemp;
    static bool sb_PushDelayFlg = false;    //推袋延时已启动
    
    //提袋启动
    if (*fbp_LiftStart == true)
    {   //提袋输出有效时间不为0 提袋才有作用
        if (gs_Rec.TimeT10 != 0)
        {
            if (sb_LiftDelayFlg)
            {   //提袋延时已经启动
                if (gu32_Sys10ms - su32_LiftTimeTemp >= gs_Rec.TimeT9 * 10)
                {   //提袋延时时间到启动提袋输出
                    sb_LiftDelayFlg = false;
                    gb_LiftBagFlg = true;
                    su32_LiftTimeTemp = gu32_Sys10ms;
                }
            }
            else if (gb_LiftBagFlg)
            {   //提袋输出已经有效
                if (gu32_Sys10ms - su32_LiftTimeTemp >= gs_Rec.TimeT10 * 10)
                {   //提袋输出结束
                    gb_LiftBagFlg = false;
                    *fbp_LiftStart = false;
                }
            }
            else
            {
                //提袋延时时间不为0先走延时
                if (gs_Rec.TimeT9 != 0)
                {
                    su32_LiftTimeTemp = gu32_Sys10ms;
                    sb_LiftDelayFlg = true;
                    gb_LiftBagFlg = false;
                }
                else
                {
                    sb_LiftDelayFlg = false;
                    gb_LiftBagFlg = true;
                    su32_LiftTimeTemp = gu32_Sys10ms;
                }
            }
        }
        else
            *fbp_LiftStart = false;
    }
    //推袋启动
    if (*fbp_PushStart == true)
    {   //推袋输出有效时间不为0 提袋才有作用
        if (gs_Rec.TimeT12 != 0)
        {
            if (sb_PushDelayFlg)
            {   //推袋延时已经启动
                if (gu32_Sys10ms - su32_PushTimeTemp >= gs_Rec.TimeT11 * 10)
                {   //推袋延时时间到启动提袋输出
                    sb_PushDelayFlg = false;
                    gb_PushBagFlg = true;
                    su32_PushTimeTemp = gu32_Sys10ms;
                }
            }
            else if (gb_PushBagFlg)
            {   //推袋输出已经有效
                if (gu32_Sys10ms - su32_PushTimeTemp >= gs_Rec.TimeT12 * 10)
                {   //推袋输出结束
                    gb_PushBagFlg = false;
                    *fbp_PushStart = false;
                }
            }
            else
            {
                //推袋延时时间不为0先走延时
                if (gs_Rec.TimeT11 != 0)
                {
                    su32_PushTimeTemp = gu32_Sys10ms;
                    sb_PushDelayFlg = true;
                    gb_PushBagFlg = false;
                }
                else
                {
                    sb_PushDelayFlg = false;
                    gb_PushBagFlg = true;
                    su32_PushTimeTemp = gu32_Sys10ms;
                }
            }
        }
        else
            *fbp_PushStart = false;
    }
}

/*********************************************************************
函数名称: void SpecialFun(void)
功    能: 特殊功能处理 主循环中 可与其他过程同步进行的功能
说    明: 
入口参数: 
返 回 值: 
设    计: chx                  时    间: 2015-2-3
修    改:                      时    间: 
*********************************************************************/
void SpecialFun(void)
{
    //手动卸料累计的相关计算处理
    DiscSumDeal();
    //拍袋处理
    FlapBag();
    //夹松袋处理
    Deal_Pack();
    //提袋和推袋的处理
    Lift_Push_Bag(&gb_LiftBagStartFlg, &gb_PushBagStartFlg);
    //打码处理
    PrintCodeFun(gs_Rec.PrintCodeSwitch,    //打码开关                                    
                 gs_Rec.PrintCodeTime,      //打码时间                                    
                 gs_Rec.PrintCodeRunDelay,  //打码启动延时                                
                 gu32_Sys10ms,            //系统时间，单位10ms                          
                 gb_PackFlg,              //夹袋输出                                    
                 &gb_StopPrintCodeFlg,    //停止打码，如正在打码时停止信号输入          
                 &gb_PrintCodeOutFlg,     //打码开关量输出变量                          
                 &gb_PrintCodeIngFlg);    //打码启动延时或打码输出时有效，用来屏蔽卸料等
    ConveyorDeal(&gb_ConveyorStartFlg);
}


int main(void) 
{
    System_Init();          //系统初始化
    Disp_Version();         //显示版本号
    do
	{
     	CmpDay();
     	Sys_Closed_Set();
	}while(gb_ReCmpFlg);       //定时锁机判断
//测试累计
//    gu32_SumWt = 123456789;                //累计重量 最大15位
//    gu32_SumNum = 123456789;               //累计次数
//    gu32_Sp2StopTime01ms = 50000;
//    Sp2StopTimeStart();             //for test
    while(1)
    {
    #ifdef DEBUG_ADCNVT_TIMES
        //调试用 副显示AD转换次数/秒
        gu32_AdConventTimes = AD_ConvertTimes(gu32_Sys10ms);
    #endif
        
        //AD转换得到重量值
        GetWt();
        //通讯处理
        Commumication();
        //各个工作状态下的按键等处理
        WorkStateDeal();
        //显示处理
        Disp_MainFun();
        //特殊功能处理 可与其他过程同步进行的功能
//        SpecialFun();
        //开关量输出处理
        if (gu32_SystemState != IOTESTSTATE)
            IO_OutPut();
        //定时锁机的处理
//        Auto_ShutDown();
    }
}

